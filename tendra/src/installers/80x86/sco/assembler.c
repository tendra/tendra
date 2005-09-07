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


/* sco/assembler.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:51 $
$Revision: 1.1.1.1 $
$Log: assembler.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.8  1997/03/24  12:43:33  pwe
 * outn int->long
 *
 * Revision 1.7  1995/10/09  15:14:29  pwe
 * dynamic initialisation etc
 *
 * Revision 1.6  1995/03/16  09:13:41  pwe
 * sco_gas now install time option
 *
 * Revision 1.5  1995/01/30  12:57:17  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.4  1994/10/28  11:17:30  jmf
 * Changed out_switch_jump to subtract lower
 *
 * Revision 1.3  1994/07/15  14:00:48  jmf
 * Round .comm to 8 (?but bss may not start aligned 8.
 *
 * Revision 1.2  1994/07/13  07:57:06  jmf
 * Added Log
 *
**********************************************************************/



#include "config.h"
#include "common_types.h"
#include "out.h"
#include "expmacs.h"
#include "operand.h"
#include "machine.h"
#include "localflags.h"
#include "basicread.h"


int sco_gas = 0;

/* PROCEDURES */

void
dot_align(int n)
{
  if (!sco_gas && n> 4) {
    n = 4;
  }
  outs(".align ");
  outn((long)n);
  outnl();
  return;
}


void
outbyte(void)
{
  outs(".byte ");
  return;
}

void
outshort(void)
{
  outs(".value ");
  return;
}

void
outlong(void)
{
  outs(".long ");
  return;
}

void
align_label(int f, exp jr)
{
  UNUSED(f);
  UNUSED(jr);
  if (is80486 && !is80586) {
    outs(".align 4\n");
  }
  return;
}

void
eval_postlude(char *s, exp c)
{
  UNUSED(s);
  UNUSED(c);
  return;
}

void
out_readonly_section(void)
{
  outs(".text");
  return;
}

void
out_dot_comm(char *id, shape sha)
{
	outs(".comm ");
	outs(id);
	outs(",");
	if (sco_gas) {
	  outn((long)(((shape_size(sha) / 8) + 3) / 4) * 4);
	} else {
	  outn((long)(((shape_size(sha) / 8) + 7) / 8) * 8);
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
	if (sco_gas) {
	  outn((long)(((shape_size(sha) / 8) + 3) / 4) * 4);
	} else {
	  outn((long)(((shape_size(sha) / 8) + 7) / 8) * 8);
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
	if (sco_gas) {
	  outn((long)(((shape_size(sha) / 8) + 3) / 4) * 4);
	} else {
	  outn((long)(((shape_size(sha) / 8) + 7) / 8) * 8);
	}

	outnl();
  return;
}

void
pic_prelude(void)
{
  return;
}

void
out_rename(char *oldid, char *newid)
{
  UNUSED(oldid);
  UNUSED(newid);
  return;
}


void
out_switch_jump(int tab, where a, int min)
{
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
}

void
proc_size(char *s)
{
  UNUSED(s);
  return;
}

void
proc_type(char *s)
{
  UNUSED(s);
  return;
}

void
outend(void)
{
  int st;

  if (sco_gas) {
    outs(".text");
    outnl();
    dot_align(16);
  }

  st = fclose(fpout);
  if (st == EOF) {
    failer("failed to close file");
    exit(EXIT_FAILURE);
  }
}

void
outopenbr(void)
{
  return;
}

void
outclosebr(void)
{
  return;
}

void
outdivsym(void)
{
  outs("/");
  return;
}

void
out_initialiser(char *id)
{
  outs(".section .init,\"x\"\n");
  outs(" call ");
  outs(id);
  outnl();
  outnl();
  return;
}


