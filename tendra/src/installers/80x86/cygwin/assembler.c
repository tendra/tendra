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


/* linux/assembler.c */

/**********************************************************************
$Author: release $
$Date: 1998/02/25 12:32:45 $
$Revision: 1.1.1.1 $
$Log: assembler.c,v $
 * Revision 1.1.1.1  1998/02/25  12:32:45  release
 * Initial version
 *
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.10  1997/03/24  12:43:22  pwe
 * outn int->long
 *
 * Revision 1.9  1996/02/16  10:11:01  pwe
 * Linux/ELF struct result and PIC jump table
 *
 * Revision 1.8  1996/02/08  13:45:24  pwe
 * Linux elf v aout option
 *
 * Revision 1.7  1995/11/23  12:17:02  pwe
 * linux elf
 *
 * Revision 1.6  1995/10/13  15:20:07  pwe
 * solaris PIC and linux tcc
 *
 * Revision 1.5  1995/10/09  15:14:20  pwe
 * dynamic initialisation etc
 *
 * Revision 1.4  1995/04/12  13:22:04  pwe
 * end_tdf label added in case nothing but static strings
 *
 * Revision 1.3  1995/01/30  12:57:10  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.2  1995/01/27  17:24:41  jmf
 * Unknown change?
 *
 * Revision 1.1  1994/11/08  16:27:43  jmf
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
#include "coder.h"
#include "assembler.h"
#include "instr.h"
#include "instr386.h"
#include "xalloc.h"
#include "install_fns.h"
#include <string.h>



/* PROCEDURES */

void
dot_align(int n)
{
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
  if (is80486 && !is80586 && ptno(jr) != last_jump_label) {
/* forward jump and continued into
    if (f==0)
      outs(".align 8");
*/
    if (f == 1) {	/* repeat jump */
      outs(".align 4");
    }
    if (f == 2) {	/* preceded by a jmp or ret */
      outs(".align 16");
    }
    outs("\n");
  };
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
  outn((long)(((shape_size(sha) / 8) + 3) / 4) * 4);
  outnl();
  return;
}

void
out_dot_lcomm(char *id, shape sha)
{
  outs(".lcomm ");
  outs(id);
  outs(",");
  outn((long)(((shape_size(sha) / 8) + 3) / 4) * 4);
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
  if (PIC_code) {
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
    return;
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
  };
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
  return;
}

void
proc_size(char *s)
{
  outs(".align 4");
  outnl();
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
{		/* close the output */
  int st;
  outs(".text");
  outnl();
  dot_align(16);
  outnl();
  outs("___tdf_end:");
  outnl();
  st = fclose(fpout);
  if (st == EOF) {
    failer("failed to close file");
    exit(EXIT_FAILURE);
  };
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
  outs(".section .ctor\n");
  outs(" .long ");
  outs(id);
  if (PIC_code) {
    outs("@PLT");
  }
  outnl();
  outnl();
  return;
}


void
out_main_prelude(void)
{
  outs(" call ___main\n");
  return;
}

void
out_main_postlude(void)
{
  return;
}
