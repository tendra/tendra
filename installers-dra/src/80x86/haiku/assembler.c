/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/xalloc.h>

#include "config.h"

#include "exptypes.h"
#include <construct/exp.h>
#include "out.h"
#include "expmacs.h"
#include <construct/exp.h>
#include "localflags.h"
#include <construct/shapemacs.h>
#include "operand.h"
#include <construct/machine.h>
#include <construct/flags.h>
#include <reader/basicread.h>
#include "coder.h"
#include "assembler.h"
#include "instr.h"
#include "instr386.h"
#include <construct/install_fns.h>

void
dot_align(int n)
{
	outs(".align ");
	outn((long)n);
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
	if (is80486 && !is80586 && ptno(jr) != last_jump_label) {
#if 0
		/* forward jump and continued into */
		if (f == 0)
			outs(".align 8");
#endif
		/* repeat jump */
		if (f == 1)
			outs(".align 4");

		/* preceded by a jmp or ret */
		if (f == 2)
			outs(".align 16");

		outs("\n");
	}
}

void
eval_postlude(char *s, exp c)
{
	outs(".size ");
	outs(s);
	outs(",");
	outn((long)(shape_size(sh(c)) + 7) / 8);
	outnl();
	outs(".type ");
	outs(s);
	outs(",@object");
	outnl();
}

void
out_readonly_section(void)
{
	outs(".section .rodata");
}

void
out_dot_comm(char *id, shape sha)
{
	outs(".comm ");
	outs(id);
	outs(",");
	outn((long)(((shape_size(sha) / 8) + 3) / 4) * 4);
	outnl();
}

void
out_dot_lcomm(char *id, shape sha)
{
	outs(".lcomm ");
	outs(id);
	outs(",");
	outn((long)(((shape_size(sha) / 8) + 3) / 4) * 4);
	outnl();
}

void
out_bss(char *id, shape sha)
{
	outs(".bss ");
	outs(id);
	outs(",");
	outn((long)(((shape_size(sha) / 8) + 3) / 4) * 4);
	outnl();
}

static int pic_label; /* XXX: useless */

void
pic_prelude(void)
{
	int n = next_lab();
	pic_label = n;
	outs(" call ");
	outs(local_prefix);
	outn((long)n);
	outnl();
	outs(local_prefix);
	outn((long)n);
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

void
out_rename(char *oldid, char *newid)
{
	/* XXX */
	UNUSED(oldid);
	UNUSED(newid);
}

void
out_switch_jump(int tab, where a, int min)
{
	if (PIC_code) {
		if (min != 0) {
			sub(slongsh, mw(zeroe,min), a, reg0);
			a = reg0;
		}

		if (eq_where(a, reg0))
			outs(" movl ");
		else {
			outs(" movl %ebx,%eax");
			outnl();
			outs(" subl ");
		}

		outs(local_prefix);
		outn((long)tab);
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
	} else {
		outs(" jmp *");
		outs(local_prefix);
		outn((long)tab);
		outs("-");
		outn((long)(4 * min));
		outs("(,");
		operand(32, a, 1, 0);
		outs(",4)");
		outnl();
	}
}

void
out_switch_table(int tab, int min, int max, int *v, int absent)
{
	int i;

	dot_align(4);
	outnl();

	outs(local_prefix);
	outn((long)tab);
	outs(":");
	outnl();

	for (i = min; i <= max; ++i) {
		outs(".long ");
		if (v[i - min]!= -1) {
			if (PIC_code) {
				outs(" _GLOBAL_OFFSET_TABLE_+ [.-");
				outs(local_prefix);
				outn((long)v[i - min]);
				outs("]");
			} else {
				outs(local_prefix);
				outn((long)v[i - min]);
			}
		} else {
			if (absent == -1) {
				outn((long)0);
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
	outs(".text");
	outnl();
	dot_align(16);
	outnl();
	outs("___tdf_end:");
	outnl();
	out_close();
}

void
outopenbr(void)
{
}

void
outclosebr(void)
{
}

void
outdivsym(void)
{
	outs("/");
}

void
out_initialiser(char *id)
{
	outs(".section .init\n");
	outs(" call ");
	outs(id);

	if (PIC_code)
		outs("@PLT");

	outnl();
	outnl();
}


void
out_main_prelude(void)
{
	/* if (!linux_elf) */
	int nl1 = next_lab();
	int nl2 = next_lab();
	min_rfree |= 0x8;
	outs(" movl $___TDFI_LIST__+4, %ebx\n");
	outs(local_prefix);
	outn((long)nl1);
	outs(":\n");
	outs(" movl (%ebx),%eax\n");
	outs(" cmpl $0,%eax\n");
	simple_branch("je", nl2);
	outs(" call *%eax\n");
	outs(" addl $4,%ebx\n");
	simple_branch("jmp", nl1);
	outs(local_prefix);
	outn((long)nl2);
	outs(":\n");
}

void
out_main_postlude(void)
{
	/* if (!linux_elf) */
	char *sdummy = "Idummy";
	char *pdummy = (char *)xcalloc(((int)strlen(local_prefix) + (int)strlen(sdummy) + 1), sizeof(char));
	strcpy(pdummy, local_prefix);
	strcat(pdummy, sdummy);
	outs(".text\n");
	outs(pdummy);
	outs(":\n");
	outs(" ret\n");
	out_initialiser(pdummy);
}
