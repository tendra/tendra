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


/* minix/assembler.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: assembler.c,v $
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
  outs(".data1 ");
  return;
}

void outshort
    PROTO_Z ()
{
  outs(".data2 ");
  return;
}

void outlong
    PROTO_Z ()
{
  outs(".data4 ");
  return;
}

void align_label
    PROTO_N ( (f, jr) )
    PROTO_T ( int f X exp jr )
{
  UNUSED(f); UNUSED(jr);
  /* aligning jump labels is impossible with the ACK assembler,
     since it always fills the holes with zeros */
  return;
}

void eval_postlude
    PROTO_N ( (s, c) )
    PROTO_T ( char * s X exp c )
{
  UNUSED(s); UNUSED(c);
  return;
}

void out_readonly_section
    PROTO_Z ()
{
  outs (".sect .rom");
  outnl();
  return;
}

void out_dot_comm
    PROTO_N ( (id, sha) )
    PROTO_T ( char * id X shape sha )
{
  outs (".sect .data");
  outnl ();
  outs (".extern ");
  outs (id);
  outnl ();
  outs (".comm ");
  outs (id);
  outs (", ");
  outn ((long)((( shape_size(sha)/ 8) + 3) / 4) * 4);
  outnl ();
  return;
}

void out_dot_lcomm
    PROTO_N ( (id, sha) )
    PROTO_T ( char * id X shape sha )
{
  outs (".sect .bss");
  outnl ();
  outs (".comm ");
  outs (id);
  outs (", ");
  outn ((long)((( shape_size(sha)/ 8) + 3) / 4) * 4);
  outnl ();
  return;
}

void out_bss
    PROTO_N ( (id, sha) )
    PROTO_T ( char * id X shape sha )
{
  outs (".sect .bss");
  outnl ();
  outs (id);
  outs (":");
  outnl ();
  outs (".space ");
  outn ((long)((( shape_size(sha)/ 8) + 3) / 4) * 4);
  outnl ();
  return;
}

static int pic_label;

void pic_prelude
    PROTO_Z ()
{
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
  outs("jmp ");
  outs(local_prefix);
  outn((long)tab);
  outs("-");
  outn((long)(4 * min));
  outs("(");
  operand(32, a, 1, 0);
  outs("*4)");
  outnl();
  return;
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
    outs (".data4 ");
    if (v[i - min] != -1)  {
      outs(local_prefix);
      outn ((long)v[i - min]);
    }
    else  {
      if (absent == -1)
        outn ((long)0);
      else {
        outs(local_prefix);
        outn ((long)absent);
      };
    };
    outnl ();
  };
  outnl();
  return;
}

void proc_size
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  UNUSED(s);
  return;
}

void proc_type
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  UNUSED(s);
  return;
}

void outend
    PROTO_Z ()
{		/* close the output */
  int st = fclose (fpout);
  if (st == EOF) {
    failer ("failed to close file");
    exit(EXIT_FAILURE);
  };
}

void outopenbr
    PROTO_Z ()
{
  return;
}


void outclosebr
    PROTO_Z ()
{
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
  UNUSED(id);
  return;
}

void out_main_prelude
    PROTO_Z ()
{
  return;
}

void out_main_postlude
    PROTO_Z ()
{
  return;
}
