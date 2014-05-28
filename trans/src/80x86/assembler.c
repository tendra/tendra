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

#include <local/exptypes.h>
#include <local/out.h>
#include <local/expmacs.h>
#include <local/localflags.h>

#include <reader/basicread.h>

#include <construct/exp.h>
#include <construct/machine.h>
#include <construct/install_fns.h>

#include "instr.h"
#include "instr386.h"
#include "operand.h"
#include "coder.h"

static int pic_label;

void
dot_align(int n)
{
	if (format == FORMAT_ELF) {
		outs(".align ");
		outn((long) n);
		outnl();
		return;
	}

	if (n == 1) {
		return;
	}

	outs(".align ");

	switch (n) {
	case 16: n = 4; break;
	case 8:  n = 3; break;
	case 4:  n = 2; break;
	default: n = 1; break;
	}

	outn((long) n);
	outnl();
}

void
outbyte(void)
{
	outs(".byte ");
}

void
outshort(void)
{
	outs(".value ");
}

void
outlong(void)
{
	outs(".long ");
}

void
align_label(int f, exp jr)
{
	if (format == FORMAT_ELF) {
		if (cpu & CPU_80486 && ~cpu & CPU_80586 && ptno(jr) != last_jump_label) {
#if 0
			/* forward jump and continued into */
			if (f == 0) {
				outs(".align 8");
			}
#endif

			/* repeat jump */
			if (f == 1) {
				outs(".align 4");
			}

			/* preceded by a jmp or ret */
			if (f == 2) {
				outs(".align 16");
			}

			outs("\n");
		}
	} else {
		if (cpu & CPU_80486 && ~cpu & CPU_80586 && ptno(jr) != last_jump_label) {
#if 0
			/* forward jump and continued into */
			if (f == 0) {
				outs(".align 8");
			}
#endif

			/* repeat jump */
			if (f == 1)	{
				outs(".align 3,0x90");
			}

			/* preceded by a jmp or ret */
			if (f == 2)	{
				outs(".align 4,0x90");
			}

			if (f == 3) {
				outs(".align 2,0x90");
			}

			outs("\n");
		}

		if (cpu & CPU_80586 && ptno(jr) != last_jump_label) {
			if (f >= 1 && f <= 3) {
				outs(".align 2,0x90\n");
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

	outs(".size ");
	outs(s);
	outs(",");
	outn((long) (shape_size(sh(c)) + 7) / 8);
	outnl();
	outs(".type ");
	outs(s);
	outs(",@object");
	outnl();
}

void
out_readonly_section(void)
{
	if (format == FORMAT_ELF) {
		outs(".section .rodata");
	} else {
		outs(".text");
	}
}

void
out_dot_comm(char *id, shape sha)
{
	outs(".comm ");
	outs(id);
	outs(",");
	outn((long) (((shape_size(sha) / 8) + 3) / 4) * 4);
	outnl();
}

void
out_dot_lcomm(char *id, shape sha)
{
	outs(".lcomm ");
	outs(id);
	outs(",");
	outn((long) (((shape_size(sha) / 8) + 3) / 4) * 4);
	outnl();
}

void
out_bss(char *id, shape sha)
{
	outs(".bss ");
	outs(id);
	outs(",");
	outn((long) (((shape_size(sha) / 8) + 3) / 4) * 4);
	outnl();
}

void
pic_prelude(void)
{
	if (PIC_code) {
		int n = next_lab();
		pic_label = n;
		outs(" call ");
		outs(local_prefix);
		outn((long) n);
		outnl();
		outs(local_prefix);
		outn((long) n);
		outs(":");
		outnl();
		outs(" popl %ebx");
		outnl();
		outs(" addl $_GLOBAL_OFFSET_TABLE_+ [.-");
		outs(local_prefix);
		outn((long)n);
		outs("],%ebx");
		outnl();
	}
}

void
out_rename(char *oldid, char *newid)
{
	UNUSED(oldid);
	UNUSED(newid);
}

void
out_switch_jump(int tab, where a, int min)
{
	if (!PIC_code) {
		outs(" jmp *");
		outs(local_prefix);
		outn((long) tab);
		if (min >= 0) {
			outs("-");
		} else {
			/* XXX: should this ever happen? */
			outs("+");
			min = -min;
		}
		outn((long) (4 * min));
		outs("(,");
		operand(32, a, 1, 0);
		outs(",4)");
		outnl();
		return;
	}

	/* XXX: this was present for solaris x86. I'm not sure if it's still
	 * relevant. Possibly it's obsoleted by the code below. */
	if (assembler == ASM_SUN && PIC_code) {
		outs(" leal ");
		outs(local_prefix);
		outn((long)tab);
		outs("@GOTOFF(%ebx,");
		operand(32, a, 1, 0);
		outs(",4),%eax");
		outnl();
		outs(" movl ");
		outs("-");
		outn((long)(4 * min));
		outs("(%eax),%eax");
		outnl();
		outs(" addl %ebx,%eax");
		outnl();
		outs(" subl $_GLOBAL_OFFSET_TABLE_+ [.-.L");
		outn(pic_label);
		outs("],%eax");
		outnl();
		outs(" jmp *%eax");
		outnl();
		/* MODIFY FOR NEW CASE !!!!! */
		return;
	}

	if (min != 0) {
		sub(slongsh, mw(zeroe,min), a, reg0);
		a = reg0;
	}

	if (eq_where(a, reg0)) {
		outs(" movl ");
	} else {
		outs(" movl %ebx,%eax");
		outnl();
		outs(" subl ");
	}

	outs(local_prefix);
	outn((long) tab);
	outs("@GOTOFF(%ebx,");
	operand(32, a, 1, 0);
	outs(",4),%eax");
	outnl();

	if (eq_where(a, reg0)) {
		outs(" subl %ebx,%eax");
		outnl();
		outs(" negl %eax");
		outnl();
	}

	outs(" jmp *%eax");
	outnl();
}

void
out_switch_table(int tab, int min, int max, int *v, int absent)
{
	int i;

	dot_align(4);
	outnl();

	outs(local_prefix);
	outn((long) tab);
	outs(":");
	outnl();

	for (i = min; i <= max; ++i) {
		outs(".long ");

		if (v[i - min] != -1) {
			if (PIC_code) {
				outs(" _GLOBAL_OFFSET_TABLE_+ [.-");
				outs(local_prefix);
				outn((long)v[i - min]);
				outs("]");
			} else {
				outs(local_prefix);
				outn((long)v[i - min]);
			}

			outnl();
			continue;
		}

		if (absent == -1) {
			outn((long) 0);
		} else {
			if (PIC_code) {
				outs(" _GLOBAL_OFFSET_TABLE_+ [.-");
				outs(local_prefix);
				outn((long)absent);
				outs("]");
			} else {
				outs(local_prefix);
				outn((long)absent);
			}
		}
		outnl();
	}
	outnl();
}

void
proc_size(char *s)
{
	outs(".align 4");
	outnl();
	outs(".size ");
	outs(s);
	outs(", .-");
	outs(s);
	outnl();
}

void
proc_type(char *s)
{
	outs(".type ");
	outs(s);
	outs(",@function");
	outnl();
}

void
outend(void)
{
	if (assembler == ASM_SUN) {
		dot_align(16);
		return;
	}

	outs(".text");
	outnl();
	dot_align(16);
	outnl();
	outs("___tdf_end:");
	outnl();

	/* TODO: linux-specific? */
	if (format == FORMAT_ELF) {
		outs(".section .note.GNU-stack,\"\",@progbits");
		outnl();
	}
}

void
outopenbr(void)
{
	if (assembler == ASM_SUN) {
		outs("[");
	}
}


void
outclosebr(void)
{
	if (assembler == ASM_SUN) {
		outs("]");
	}
}

void
outdivsym(void)
{
	outs("/");
}

void
out_initialiser(char *id)
{
	if (format == FORMAT_ELF) {
		outs(".section .init");
		outnl();
		outs(" call ");
		outs(id);

		if (PIC_code) {
			outs("@PLT");
		}

	} else {
		outs(".stabs \"___TDFI_LIST__\",22,0,0,");
		outs(id);
	}

	outnl();
	outnl();
}


void
out_main_prelude(void) /* FORMAT_AOUT */
{
	int nl1 = next_lab();
	int nl2 = next_lab();

	min_rfree |= 0x8;

	outs(" movl $___TDFI_LIST__+4, %ebx\n");
	outs(local_prefix);
	outn((long) nl1);
	outs(":\n");

	outs(" movl (%ebx),%eax\n");
	outs(" cmpl $0,%eax\n");
	simple_branch("je", nl2);
	outs(" call *%eax\n");
	outs(" addl $4,%ebx\n");
	simple_branch("jmp", nl1);

	outs(local_prefix);
	outn((long) nl2);
	outs(":\n");
}

void
out_main_postlude(void) /* FORMAT_AOUT */
{
	char *sdummy = "Idummy";
	char *pdummy = xcalloc(strlen(local_prefix) + strlen(sdummy) + 1, 1);

	strcpy(pdummy, local_prefix);
	strcat(pdummy, sdummy);

	outs(".text\n");
	outs(pdummy);
	outs(":\n");
	outs(" ret\n");
	out_initialiser(pdummy);
}

