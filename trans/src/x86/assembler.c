/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <local/out.h>
#include <local/cpu.h>

#include <main/flags.h>
#include <main/print.h>

#include <reader/exp.h>
#include <reader/basicread.h>

#include <construct/exp.h>
#include <construct/machine.h>
#include <construct/install_fns.h>

#include "localtypes.h"
#include "instr.h"
#include "instrs.h"
#include "ops.h"
#include "operand.h"
#include "make_code.h"
#include "assembler.h"

static int pic_label;

void
out_align(int n)
{
	if (format == FORMAT_ELF) {
		asm_printf(".align %d\n", n);
		return;
	}

	if (n == 1) {
		return;
	}

	switch (n) {
	case 16: n = 4; break;
	case 8:  n = 3; break;
	case 4:  n = 2; break;
	default: n = 1; break;
	}

	asm_printf(".align %d\n", n);
}

void
out_byte(void)
{
	asm_printf(".byte ");
}

void
out_short(void)
{
	asm_printf(".value ");
}

void
out_long(void)
{
	asm_printf(".long ");
}

void
out_align_label(int f, exp jr)
{
	UNUSED(jr);

	if (format == FORMAT_ELF) {
		if (cpu & CPU_80486 && ~cpu & CPU_80586) {
#if 0
			/* forward jump and continued into */
			if (f == 0) {
				asm_printf(".align 8\n");
			}
#endif

			/* repeat jump */
			if (f == 1) {
				asm_printf(".align 4\n");
			}

			/* preceded by a jmp or ret */
			if (f == 2) {
				asm_printf(".align 16\n");
			}
		}
	} else {
		if (cpu & CPU_80486 && ~cpu & CPU_80586) {
#if 0
			/* forward jump and continued into */
			if (f == 0) {
				asm_printf(".align 8\n");
			}
#endif

			/* repeat jump */
			if (f == 1)	{
				asm_printf(".align 3,0x90\n");
			}

			/* preceded by a jmp or ret */
			if (f == 2)	{
				asm_printf(".align 4,0x90\n");
			}

			if (f == 3) {
				asm_printf(".align 2,0x90\n");
			}
		}

		if (cpu & CPU_80586) {
			if (f >= 1 && f <= 3) {
				asm_printf(".align 2,0x90\n");
			}
		}
	}
}

void
out_eval_postlude(char *s, exp c)
{
	if (format == FORMAT_AOUT) {
		return;
	}

	asm_printf(".size %s, %ld\n", s, (long) (shape_size(sh(c)) + 7) / 8);
	asm_printf(".type %s, @object\n", s);
}

void
out_sect(const char *sect)
{
	if (streq(sect, "rodata") && format != FORMAT_ELF) {
		sect = "text";
	}

	if (streq(sect, "bss") || streq(sect, "data") || streq(sect, "text")) {
		asm_printf(".%s\n", sect);
	} else {
		asm_printf(".section .%s\n", sect);
	}
}
 
void
out_linkage(const char *linkage, const char *name)  
{
	asm_printf(".%s %s\n", linkage, name);
}

void
out_dot_comm(char *name, shape sha)
{
	asm_printf(".comm %s, %ld\n",
		name, (long) (((shape_size(sha) / 8) + 3) / 4) * 4);
}

void
out_dot_lcomm(char *name, shape sha)
{
	switch (assembler) {
	case ASM_SUN:
		/*
		 * This .bss syntax with operands is not supported by GAS on x86;
		 * I believe this was for Solaris on x86, and perhaps also SCO.
		 * But this is unclear, due to how often this code was copied around.
		 */
		asm_printf(".bss %s, %ld\n",
			name, (long) (((shape_size(sha) / 8) + 3) / 4) * 4);
		break;

	case ASM_GAS:
		asm_printf(".lcomm %s, %ld\n",
			name, (long) (((shape_size(sha) / 8) + 3) / 4) * 4);
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
		return;
	}
}

void
out_pic_prelude(void)
{
	if (PIC_code) {
		int n = next_lab();
		pic_label = n;
		asm_printop("%s %s%d", call, local_prefix, n);
		asm_label("%s%d", local_prefix, n);
		asm_printop("%s %s", popl, "%ebx");
		asm_printop("%s $_GLOBAL_OFFSET_TABLE_+ [.-%s%d],%s",
			addl, local_prefix, n, "%ebx");
	}
}

void
out_switch_jump(int tab, where a, int min)
{
	if (!PIC_code) {
		asm_printf("\tjmp *%s%d%+d(,", local_prefix, tab, -(4 * min));
		operand(32, a, 1, 0);
		asm_printf(",4)\n");
		return;
	}

	/* XXX: this was present for solaris x86. I'm not sure if it's still
	 * relevant. Possibly it's obsoleted by the code below. */
	if (assembler == ASM_SUN && PIC_code) {
		asm_printf("\tleal %s%d@GOTOFF(%s,", local_prefix, tab, "%ebx");
		operand(32, a, 1, 0);
		asm_printf(",4),%s\n", "%eax");

		asm_printop("%s -%d(%s),%s", movl, 4 * min, "%eax", "%eax");
		asm_printop("%s %s,%s", addl, "%ebx", "%eax");
		asm_printop("%s $_GLOBAL_OFFSET_TABLE_+ [.-.L%d],%s", subl, pic_label, "%eax");
		asm_printop("%s *%s", jmp, "%eax");
		/* MODIFY FOR NEW CASE !!!!! */
		return;
	}

	if (min != 0) {
		sub(slongsh, mw(zeroe,min), a, reg0);
		a = reg0;
	}

	if (eq_where(a, reg0)) {
		asm_printf("\tmovl ");
	} else {
		asm_printop("%s %s,%s", movl, "%ebx", "%eax");
		asm_printf("\tsubl ");
	}
	asm_printf("%s%d@GOTOFF(%s,", local_prefix, tab, "%ebx");
	operand(32, a, 1, 0);
	asm_printf(",4),%s\n", "%eax");

	if (eq_where(a, reg0)) {
		asm_printop("%s %s,%s", subl, "%ebx", "%eax");
		asm_printop("%s %s", negl, "%eax");
	}

	asm_printop("%s *%s", jmp, "%eax");
}

void
out_switch_table(int tab, int min, int max, int *v, int absent)
{
	int i;

	out_align(4);
	asm_printf("\n");

	asm_label("%s%d", local_prefix, tab);

	for (i = min; i <= max; ++i) {
		if (v[i - min] != -1) {
			if (PIC_code) {
				asm_printop(".long _GLOBAL_OFFSET_TABLE_+ [.-%s%d]",
					local_prefix, v[i - min]);
			} else {
				asm_printop(".long %s%d", local_prefix, v[i - min]);
			}

			continue;
		}

		if (absent == -1) {
			asm_printop(".long 0");
		} else {
			if (PIC_code) {
				asm_printop(".long _GLOBAL_OFFSET_TABLE_+ [.-%s%d]",
					local_prefix, absent);
			} else {
				asm_printop(".long %s%d", local_prefix, absent);
			}
		}
	}

	asm_printf("\n");
}

void
out_proc_size(char *s)
{
	asm_printf(".align 4\n");
	asm_printf(".size %s, .-%s\n", s, s);
}

void
out_proc_type(char *s)
{
	asm_printf(".type %s,@function\n", s);
}

void
out_end(void)
{
	if (assembler == ASM_SUN) {
		out_align(16);
		return;
	}

	out_sect("text");
	out_align(16);
	asm_printf("\n");
	asm_label("___tdf_end");

	/* TODO: linux-specific? */
	if (format == FORMAT_ELF) {
		out_sect("note.GNU-stack,\"\",@progbits\n");
	}
}

void
out_openbr(void)
{
	if (assembler == ASM_SUN) {
		asm_printf("[");
	}
}


void
out_closebr(void)
{
	if (assembler == ASM_SUN) {
		asm_printf("]");
	}
}

void
out_initialiser(char *name)
{
	if (format == FORMAT_ELF) {
		out_sect("init");

		asm_printf("\tcall %s", name);

		if (PIC_code) {
			asm_printf("@PLT");
		}

		asm_printf("\n");
	} else {
		asm_printf(".stabs \"___TDFI_LIST__\",22,0,0,%s\n", name);
	}

	asm_printf("\n");
}


void
out_main_prelude(void) /* FORMAT_AOUT */
{
	int nl1 = next_lab();
	int nl2 = next_lab();

	min_rfree |= 0x8;

	asm_printop("%s $___TDFI_LIST__+4, %s", movl, "%ebx");
	asm_label("%s%d", local_prefix, nl1);

	asm_printop("%s (%s),%s", movl, "%ebx", "%eax");
	asm_printop("%s $0,%s", cmpl, "%eax");
	simple_branch("je", nl2);
	asm_printop("%s *%s", call, "%eax");
	asm_printop("%s $4,%s", addl, "%ebx");
	simple_branch("jmp", nl1);

	asm_label("%s%d", local_prefix, nl2);
}

void
out_main_postlude(void) /* FORMAT_AOUT */
{
	char *sdummy = "Idummy";
	char *pdummy = xcalloc(strlen(local_prefix) + strlen(sdummy) + 1, 1);

	strcpy(pdummy, local_prefix);
	strcat(pdummy, sdummy);

	out_sect("text");
	asm_label("%s", pdummy);
	asm_printop("%s", ret);
	out_initialiser(pdummy);
}

