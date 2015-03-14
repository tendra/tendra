/* $Id */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <local/out.h>
#include <local/cpu.h>

#include <main/print.h>

#include <reader/exp.h>
#include <reader/basicread.h>

#include <construct/exp.h>
#include <construct/machine.h>
#include <construct/install_fns.h>

#include "localtypes.h"
#include "instr.h"
#include "instr386.h"
#include "operand.h"
#include "make_code.h"
#include "assembler.h"

static int pic_label;

void
dot_align(int n)
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
outbyte(void)
{
	asm_printf(".byte ");
}

void
outshort(void)
{
	asm_printf(".value ");
}

void
outlong(void)
{
	asm_printf(".long ");
}

void
align_label(int f, exp jr)
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
eval_postlude(char *s, exp c)
{
	if (format == FORMAT_AOUT) {
		return;
	}

	asm_printf(".size %s, %ld\n", s, (long) (shape_size(sh(c)) + 7) / 8);
	asm_printf(".type %s, @object\n", s);
}

void
out_readonly_section(void)
{
	if (format == FORMAT_ELF) {
		asm_printf(".section .rodata");
	} else {
		asm_printf(".text");
	}
}

void
out_dot_comm(char *id, shape sha)
{
	asm_printf(".comm %s, %ld\n",
		id, (long) (((shape_size(sha) / 8) + 3) / 4) * 4);
}

void
out_dot_lcomm(char *id, shape sha)
{
	asm_printf(".lcomm %s, %ld\n",
		id, (long) (((shape_size(sha) / 8) + 3) / 4) * 4);
}

void
out_bss(char *id, shape sha)
{
	asm_printf(".bss %s, %ld\n",
		id, (long) (((shape_size(sha) / 8) + 3) / 4) * 4);
}

void
pic_prelude(void)
{
	if (PIC_code) {
		int n = next_lab();
		pic_label = n;
		asm_printop("call %s%d", local_prefix, n);
		asm_label("%s%d", local_prefix, n);
		asm_printop("popl %s", "%ebx");
		asm_printop("addl $_GLOBAL_OFFSET_TABLE_+ [.-%s%d],%s",
			local_prefix, n, "%ebx");
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

		asm_printop("movl -%d(%s),%s", 4 * min, "%eax", "%eax");
		asm_printop("addl %s,%s", "%ebx", "%eax");
		asm_printop("subl $_GLOBAL_OFFSET_TABLE_+ [.-.L%d],%s", pic_label, "%eax");
		asm_printop("jmp *%s", "%eax");
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
		asm_printop("movl %s,%s", "%ebx", "%eax");
		asm_printf("\tsubl ");
	}
	asm_printf("%s%d@GOTOFF(%s,", local_prefix, tab, "%ebx");
	operand(32, a, 1, 0);
	asm_printf(",4),%s\n", "%eax");

	if (eq_where(a, reg0)) {
		asm_printop("subl %s,%s", "%ebx", "%eax");
		asm_printop("negl %s", "%eax");
	}

	asm_printop("jmp *%s", "%eax");
}

void
out_switch_table(int tab, int min, int max, int *v, int absent)
{
	int i;

	dot_align(4);
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
proc_size(char *s)
{
	asm_printf(".align 4\n");
	asm_printf(".size %s, .-%s\n", s, s);
}

void
proc_type(char *s)
{
	asm_printf(".type %s,@function\n", s);
}

void
outend(void)
{
	if (assembler == ASM_SUN) {
		dot_align(16);
		return;
	}

	asm_printf(".text\n");
	dot_align(16);
	asm_printf("\n");
	asm_label("___tdf_end");

	/* TODO: linux-specific? */
	if (format == FORMAT_ELF) {
		asm_printf(".section .note.GNU-stack,\"\",@progbits\n");
	}
}

void
outopenbr(void)
{
	if (assembler == ASM_SUN) {
		asm_printf("[");
	}
}


void
outclosebr(void)
{
	if (assembler == ASM_SUN) {
		asm_printf("]");
	}
}

static void
outdivsym(void)
{
	asm_printf("/");
}

void
out_initialiser(char *id)
{
	if (format == FORMAT_ELF) {
		asm_printf(".section .init\n");

		asm_printf("\tcall %s", id);

		if (PIC_code) {
			asm_printf("@PLT");
		}

		asm_printf("\n");
	} else {
		asm_printf(".stabs \"___TDFI_LIST__\",22,0,0,%s\n", id);
	}

	asm_printf("\n");
}


void
out_main_prelude(void) /* FORMAT_AOUT */
{
	int nl1 = next_lab();
	int nl2 = next_lab();

	min_rfree |= 0x8;

	asm_printop("\tmovl $___TDFI_LIST__+4, %s", "%ebx");
	asm_label("%s%d", local_prefix, nl1);

	asm_printop("movl (%s),%s", "%ebx", "%eax");
	asm_printop("cmpl $0,%s", "%eax");
	simple_branch("je", nl2);
	asm_printop("call *%s", "%eax");
	asm_printop("addl $4,%s", "%ebx");
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

	asm_printf(".text\n");
	asm_label("%s", pdummy);
	asm_printop("ret");
	out_initialiser(pdummy);
}

