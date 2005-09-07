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


/* svr4/assembler.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:53 $
$Revision: 1.1.1.1 $
$Log: assembler.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1997/03/24  12:43:46  pwe
 * outn int->long
 *
 * Revision 1.6  1995/10/23  17:34:52  pwe
 * dynamic initialisation PIC, and sco diags
 *
 * Revision 1.5  1995/10/09  15:14:48  pwe
 * dynamic initialisation etc
 *
 * Revision 1.4  1995/07/07  15:22:39  pwe
 * prepare for 4.0, and correct PIC switch
 *
 * Revision 1.3  1995/02/20  09:50:56  pwe
 * alignment of bitfield global data
 *
 * Revision 1.2  1995/01/30  12:57:39  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  12:16:59  jmf
 * Initial revision
 *
 * Revision 1.2  1994/07/13  07:51:05  jmf
 * Added Log
 *
**********************************************************************/


#include "config.h"
#include "common_types.h"
#include "out.h"
#include "expmacs.h"
#include "exp.h"
#include "localflags.h"
#include "shapemacs.h"
#include "operand.h"
#include "machine.h"
#include "flags.h"
#include "basicread.h"



/* PROCEDURES */

void
outbyte(void)
{
  outs(".byte ");
  return;
}

void
outshort(void)
{
  outs(".2byte ");
  return;
}

void
outlong(void)
{
  outs(".4byte ");
  return;
}

void
align_label(int f, exp jr)
{
  if (is80486 && !is80586 && ptno(jr)!= last_jump_label) {

/* forward jump and continued into
    if (f==0)
      outs(".align 16,7,1");
*/
    if (f == 1) {	/* repeat jump */
      outs(".align 16,7,1");
    }
    if (f == 2) {	/* preceded by a jmp or ret */
      outs(".align 16,7,1");
    }
    if (f == 3) {
      outs(".align 4");
    }
    outs("\n");
  }
  if (is80586 && ptno(jr)!= last_jump_label) {
    if (f >= 1 && f <= 3) {
      outs(".align 4\n");
    }
  }
  return;
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
    return;
}

void
out_readonly_section(void)
{
  outs(".section .rodata");
  return;
}

void
out_dot_comm(char *id, shape sha)
{
	outs(".comm ");
	outs(id);
	outs(",");
        outn((long)shape_size(sha) / 8);
	outs(",");
        if (is80486 && (name(sha) == realhd ||
            (name(sha) == nofhd && ptno(sha) == realhd) ||
	    shape_size(sha) >= 512)) {
                /* the pt field of an nof is used to hold the
		   shapemacs.h hd description of the shape and is set in
		   f_nof */
          outn((long)8);
	} else if (shape_align(sha) < 8) {	/* alignment of bitfields */
	  int nbytes = (shape_size(sha) + 7) / 8;
	  outn((long)((nbytes < 4) ? nbytes : 4));
	} else {
	  outn((long)shape_align(sha) / 8);
	}

	outnl();
  return;
}

void
out_dot_lcomm(char *id, shape sha)
{
	outs(".lcomm ");
	outs(id);
	outs(",");
        outn((long)shape_size(sha) / 8);
	outs(",");
        if (is80486 && (name(sha) == realhd ||
            (name(sha) == nofhd && ptno(sha) == realhd) ||
	    shape_size(sha) >= 512)) {
                /* the pt field of an nof is used to hold the
		   shapemacs.h hd description of the shape and is set in
		   f_nof */
          outn((long)8);
	} else if (shape_align(sha) < 8) {	/* alignment of bitfields */
	  int nbytes = (shape_size(sha) + 7) / 8;
	  outn((long)((nbytes < 4) ? nbytes : 4));
	} else {
	  outn((long)shape_align(sha) /8);
	}

	outnl();
  return;
}

void
out_bss(char *id, shape sha)
{
	outs(".bss ");
	outs(id);
	outs(",");
	outn((long)(((shape_size(sha) / 8) + 3) / 4) * 4);

	outnl();
  return;
}

static int pic_label;

void
pic_prelude(void)
{
  int n = next_lab();
  pic_label = n;
  outs(" call .L");
  outn((long)n);
  outnl();
  outs(".L");
  outn((long)n);
  outs(":");
  outnl();
  outs(" popl %ebx");
  outnl();
  outs(" addl $_GLOBAL_OFFSET_TABLE_+ [.-.L");
  outn((long)n);
  outs("],%ebx");
  outnl();
  return;
}

void
out_rename(char *oldid, char *newid)
{
  outs(".set ");
  outs(oldid);
  outs(",");
  outs(newid);
  outnl();
  return;
}

void
out_switch_jump(int tab, where a, int min)
{
  if (PIC_code) {
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
    outn((long)pic_label);
    outs("],%eax");
    outnl();
    outs(" jmp *%eax");
    outnl();
    return;
    /* MODIFY FOR NEW CASE !!!!! */
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
    return;
  }
}

void
out_switch_table(int tab, int min, int max, int *v, int absent)
{
  int i;

  if (PIC_code) {
    outs(".section .rodata");
    outnl();
    outs(".align 4");
    outnl();

    outs(local_prefix);
    outn((long)tab);
    outs(":");
    outnl();

    for (i = min; i <= max; ++i) {
      outs(".long ");
      if (v[i - min]!= -1) {
        outs(local_prefix);
        outn((long)v[i - min]);
        outs("-");
        outs(local_prefix);
        outn((long)pic_label);
      } else {
	if (absent == -1) {
	  outn((long)0);
	} else {
          outs(local_prefix);
          outn((long)absent);
          outs("-");
          outs(local_prefix);
          outn((long)pic_label);
	}
      }
      outnl();
    }
    outs(".text");
    outnl();
    return;
  } else {
    outs(".section .rodata");
    outnl();
    outs(".align 4");
    outnl();

    outs(local_prefix);
    outn((long)tab);
    outs(":");
    outnl();

    for (i = min; i <= max; ++i) {
      outs(".long ");
      if (v[i - min] != -1) {
        outs(local_prefix);
        outn((long)v[i - min]);
      } else {
	if (absent == -1) {
          outn((long)0);
	} else {
          outs(local_prefix);
          outn((long)absent);
	}
      }
      outnl();
    }
    outs(".text");
    outnl();
    return;
  }
}

void
proc_size(char *s)
{
  outs(".align 16,7,4");
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
  return;
}

void
dot_align(int n)
{
  outs(".align ");
  outn((long)n);
  outnl();
  return;
}

void
outend(void)
{
  /* close the output */
  int st = fclose(fpout);
  if (st == EOF) {
    failer("failed to close file");
    exit(EXIT_FAILURE);
  }
}

void
outopenbr(void)
{
  outs("[");
  return;
}


void
outclosebr(void)
{
  outs("]");
  return;
}

void
outdivsym(void)
{
  outs("\\/");
  return;
}

void
out_initialiser(char *id)
{
  outs(".section .init\n");
  outs(" call ");
  outs(id);
  if (PIC_code) {
    outs("@PLT");
  }
  outnl();
  outnl();
  return;
}
