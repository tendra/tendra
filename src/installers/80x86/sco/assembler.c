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

void dot_align
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  if (!sco_gas && n> 4)
    n = 4;
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
  UNUSED(f);
  UNUSED(jr);
  if (is80486 && !is80586) {
    outs(".align 4\n");
  };
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
  outs (".text");
  return;
}

void out_dot_comm
    PROTO_N ( (id, sha) )
    PROTO_T ( char * id X shape sha )
{
	outs (".comm ");
	outs (id);
	outs (",");
	if (sco_gas)
	  outn ((long)((( shape_size(sha)/ 8) + 3) / 4) * 4);
	else
	  outn ((long)((( shape_size(sha)/ 8) + 7) / 8) * 8);

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
	if (sco_gas)
	  outn ((long)((( shape_size(sha)/ 8) + 3) / 4) * 4);
	else
	  outn ((long)((( shape_size(sha)/ 8) + 7) / 8) * 8);

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
	if (sco_gas)
	  outn ((long)((( shape_size(sha)/ 8) + 3) / 4) * 4);
	else
	  outn ((long)((( shape_size(sha)/ 8) + 7) / 8) * 8);

	outnl ();
  return;
}

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
    }
    else  {
      if (absent == -1)
	outn((long)0);
      else {
        outs(local_prefix);
        outn ((long)absent);
      };
    };
    outnl ();

  };

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
{
  int   st;

  if (sco_gas) {
    outs(".text");
    outnl();
    dot_align(16);
  };

  st = fclose (fpout);
  if (st == EOF) {
    failer ("failed to close file");
    exit (EXIT_FAILURE);
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
  outs (".section .init,\"x\"\n");
  outs (" call ");
  outs (id);
  outnl ();
  outnl ();
  return;
}


