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


/* freebsd/assembler.c */

#include "config.h"
#include "common_types.h"
#include "out.h"
#include "expmacs.h"
#include "operand.h"
#include "machine.h"
#include "localflags.h"
#include "basicread.h"
#include "coder.h"


/* PROCEDURES */

void dot_align
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  if (n == 1)
    return;
  outs(".align ");
  switch (n) {
    case 16:
      n = 4; break;
    case 8:
      n = 3; break;
    case 4:
      n = 2; break;
    default:
      n = 1; break;
  };
  outn((long)n); outnl();
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
    if (f == 1)	/* repeat jump */
      outs(".align 3,0x90");
    if (f == 2)	/* preceded by a jmp or ret */
      outs(".align 4,0x90");
    if (f == 3)
      outs(".align 2,0x90");
    outs("\n");
  };
  if (is80586 && ptno(jr) != last_jump_label)  {
    if (f >= 1 && f <= 3)
      outs(".align 2,0x90\n");
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
  outs(".align 4");
  outnl();
  outs(".size ");
  outs(s);
  outs(", .-");
  outs(s);
  outnl();
  return;
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
  outs(".text");
  outnl();
  dot_align(16);
  outnl();
  outs("___tdf_end:");
  outnl();
  st = fclose (fpout);
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
  outs(".stabs \"___TDFI_LIST__\",22,0,0,");
  outs (id);
  outnl ();
  outnl ();
  return;
}


void out_main_prelude
    PROTO_Z ()
{
  int nl1 = next_lab ();
  int nl2 = next_lab ();
  min_rfree |= 0x8;
  outs (" movl $___TDFI_LIST__+4, %ebx\n");
  outs (local_prefix);
  outn ((long)nl1);
  outs (":\n");
  outs (" movl (%ebx),%eax\n");
  outs (" cmpl $0,%eax\n");
  simple_branch ("je", nl2);
  outs (" call *%eax\n");
  outs (" addl $4,%ebx\n");
  simple_branch ("jmp", nl1);
  outs (local_prefix);
  outn ((long)nl2);
  outs (":\n");
  return;
}

void out_main_postlude
    PROTO_Z ()
{
  char * sdummy = "Idummy";
  char * pdummy = (char *) xcalloc (((int)strlen(local_prefix) +
				(int)strlen(sdummy) + 1), sizeof (char));
  strcpy (pdummy, local_prefix);
  strcat (pdummy, sdummy);
  outs (".text\n");
  outs (pdummy);
  outs (":\n");
  outs (" ret\n");
  out_initialiser(pdummy);
  return;
}
