/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
*/


/* sol86/assembler.c */

/**********************************************************************
$Author$
$Date$
$Revision$*/


#include "config.h"
#include "common_types.h"
#include "out.h"
#include "expmacs.h"
#include "exp.h"
#include "operand.h"
#include "machine.h"
#include "localflags.h"
#include "flags.h"
#include "basicread.h"


/* PROCEDURES */

void dot_align
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  outs(".align "); outn((long)n); outnl();
  return;
}


void outbyte
    PROTO_Z ()
{
  outs(".byte ");
  return;
}

void outshort
    PROTO_Z ()
{
  outs(".value ");
  return;
}

void outlong
    PROTO_Z ()
{
  outs(".long ");
  return;
}

void align_label
    PROTO_N ( (f, jr) )
    PROTO_T ( int f X exp jr )
{
  if (is80486 && !is80586 && ptno(jr) != last_jump_label) {

/* forward jump and continued into
    if (f==0)
      outs(".align 8");
*/
    if (f == 1)	/* repeat jump */
      outs(".align 4");
    if (f == 2)	/* preceded by a jmp or ret */
      outs(".align 16");
    outs("\n");
  };
  return;
}

void eval_postlude
    PROTO_N ( (s, c) )
    PROTO_T ( char * s X exp c )
{
    outs(".size ");
    outs (s);
    outs (",");
    outn((long)(shape_size(sh(c))+7)/8);
    outnl();
    outs(".type ");
    outs (s);
    outs (",@object");
    outnl();
    return;
}

void out_readonly_section
    PROTO_Z ()
{
  outs (".section .rodata");
  return;
}

void out_dot_comm
    PROTO_N ( (id, sha) )
    PROTO_T ( char * id X shape sha )
{
	outs (".comm ");
	outs (id);
	outs (",");
	outn ((long)((( shape_size(sha)/ 8) + 3) / 4) * 4);

	outnl ();
  return;
}

void out_dot_lcomm
    PROTO_N ( (id, sha) )
    PROTO_T ( char * id X shape sha )
{
	outs (".lcomm ");
	outs (id);
	outs (",");
	outn ((long)((( shape_size(sha)/ 8) + 3) / 4) * 4);

	outnl ();
  return;
}

void out_bss
    PROTO_N ( (id, sha) )
    PROTO_T ( char * id X shape sha )
{
	outs (".bss ");
	outs (id);
	outs (",");
	outn ((long)((( shape_size(sha)/ 8) + 3) / 4) * 4);

	outnl ();
  return;
}

static long pic_label;

void pic_prelude
    PROTO_Z ()
{
  long n = next_lab();
  pic_label = n;
  outs(" call .L"); outn(n); outnl();
  outs(".L"); outn(n); outs(":"); outnl();
  outs(" popl %ebx"); outnl();
  outs(" addl $_GLOBAL_OFFSET_TABLE_+[.-.L"); outn(n); outs("],%ebx");
    outnl();
  return;
}

void out_rename
    PROTO_N ( (oldid, newid) )
    PROTO_T ( char * oldid X char * newid )
{
  UNUSED(oldid); UNUSED(newid);
  return;
}


void out_switch_jump
    PROTO_N ( (tab, a, min) )
    PROTO_T ( int tab X where a X int min )
{
  if (PIC_code)  {
    outs(" leal ");
    outs(local_prefix);
    outn((long)tab);
    outs("@GOTOFF(%ebx,");
    operand (32, a, 1, 0);
    outs(",4),%eax");
    outnl();
    outs(" movl ");
    outs("-");
    outn((long)(4 * min));
    outs ("(%eax),%eax");
    outnl();
    outs(" addl %ebx,%eax");
    outnl();
    outs(" subl $_GLOBAL_OFFSET_TABLE_+[.-.L"); outn(pic_label);
      outs("],%eax"); outnl();
    outs(" jmp *%eax");
    outnl();
    return;
    /* MODIFY FOR NEW CASE !!!!! */
  }
  else  {
    outs (" jmp *");
    outs(local_prefix);
    outn((long)tab);
    outs("-");
    outn((long)(4 * min));
    outs ("(,");
    operand (32, a, 1, 0);
    outs (",4)");
    outnl ();
    return;
  };
}

void out_switch_table
    PROTO_N ( (tab, min, max, v, absent) )
    PROTO_T ( int tab X int min X int max X int * v X int absent )
{
  int i;

  dot_align(4);
  outnl();

  outs(local_prefix);
  outn ((long)tab);
  outs (":");
  outnl ();

  for (i = min; i <= max; ++i) {
    outs (".long ");
    if (v[i - min] != -1)  {
      outs(local_prefix);
      outn ((long)v[i - min]);
      if (PIC_code) {
        outs("-");
        outs(local_prefix);
        outn(pic_label);
      }
    }
    else  {
      if (absent == -1)
	outn((long)0);
      else {
        outs(local_prefix);
        outn ((long)absent);
	if (PIC_code) {
	  outs("-");
	  outs(local_prefix);
	  outn(pic_label);
	}
      };
    };
    outnl ();
  };
}

void proc_size
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  outs(".align 4");
  outnl();
  outs(".size ");
  outs(s);
  outs(", .-");
  outs(s);
  outnl();
}

void proc_type
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  outs(".type ");
  outs(s);
  outs(",@function");
  outnl();
  return;
}

void outend
    PROTO_Z ()
{
  int   st;

  dot_align(16);

  st = fclose (fpout);
  if (st == EOF) {
    failer ("failed to close file");
    exit (EXIT_FAILURE);
  };
}

void outopenbr
    PROTO_Z ()
{
  outs("[");
  return;
}

void outclosebr
    PROTO_Z ()
{
  outs("]");
  return;
}

void outdivsym
    PROTO_Z ()
{
  outs("/");
  return;
}

void out_initialiser
    PROTO_N ( (id) )
    PROTO_T ( char* id )
{
  outs (".section .init\n");
  outs (" call ");
  outs (id);
  if (PIC_code)
    outs ("@PLT");
  outnl ();
  return;
}





