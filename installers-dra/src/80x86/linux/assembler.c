/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

#include <string.h>

#include <shared/xalloc.h>

#include "config.h"

#include "exptypes.h"
#include "exp.h"
#include "out.h"
#include "expmacs.h"
#include "exp.h"
#include "localflags.h"
#include "shapemacs.h"
#include "operand.h"
#include "machine.h"
#include "flags.h"
#include "basicread.h"
#include "coder.h"
#include "assembler.h"
#include "instr.h"
#include "instr386.h"
#include "install_fns.h"

void
dot_align(int n)
{
	if (linux_elf) {
		outs(".align ");
		outn((long)n);
		outnl();
		return;
	}

	if (n == 1)
		return;

	outs(".align ");
	switch (n) {
	case 16:
		n = 4;
		break;
	case 8:
		n = 3;
		break;
	case 4:
		n = 2;
		break;
	default:
		n = 1;
		break;
	}

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
	if (linux_elf) {
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
	} else {
		if (is80486 && !is80586 && ptno(jr) != last_jump_label) {
#if 0
			/* forward jump and continued into */
			if ( f== 0)
				outs(".align 16,7,1");
#endif
			/* repeat jump */
			if (f == 1)
				outs(".align 3,0x90");

			/* preceded by a jmp or ret */
			if (f == 2)
				outs(".align 4,0x90");

			if (f == 3)
				outs(".align 2,0x90");

			outs("\n");
		}

		if (is80586 && ptno(jr) != last_jump_label)
			if (f >= 1 && f <= 3)
				outs(".align 2,0x90\n");
	}
}

void
eval_postlude(char *s, exp c)
{
	if (!linux_elf)
		return;

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
	if (linux_elf)
		outs(".section .rodata");
	else
		outs(".text");
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

	if (linux_elf) {
		outs(".section .note.GNU-stack,\"\",@progbits");
		outnl();
	}

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
	if (linux_elf) {
		outs(".section .init");
		outnl();
		outs(" call ");
		outs(id);

		if (PIC_code)
			outs("@PLT");

		outnl();
		outnl();
	} else {
		outs(".stabs \"___TDFI_LIST__\",22,0,0,");
		outs(id);
		outnl();
		outnl();
	}
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
