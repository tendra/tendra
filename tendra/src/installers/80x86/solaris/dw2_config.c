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


/**********************************************************************
$Author: release $
$Date: 1998/03/17 16:54:15 $
$Revision: 1.4 $
$Log: dw2_config.c,v $
 * Revision 1.4  1998/03/17  16:54:15  release
 * Couple of minor fixes.
 *
 * Revision 1.3  1998/03/11  11:03:13  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/01/21  10:30:02  pwe
 * labdiff change
 *
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1998/01/09  14:47:55  pwe
 * prep restructure
 *
 * Revision 1.5  1997/12/04  20:01:30  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.4  1997/10/23  09:37:29  pwe
 * extra_diags
 *
 * Revision 1.3  1997/10/10  18:26:02  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.2  1997/03/24  11:15:46  pwe
 * dwarf2 option/default
 *
 * Revision 1.1  1997/03/20  16:24:39  pwe
 * dwarf2
 *
**********************************************************************/

#include "dw2_config.h"
#include "flags.h"
#include "machine.h"
#include "basicread.h"
#include "target_v.h"

long dwarf_lab_num = 0;

void out_string
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  outs (".string \"");
  outs (s);
  outs ("\"");
  d_outnl ();
  return;
}

void start_string
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  outs (".string \"");
  outs (s);
  return;
}

void end_string
    PROTO_Z ()
{
  outs ("\"");
  d_outnl ();
  return;
}

void enter_section
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  outs (".section .");
  outs (s);
  d_outnl ();
  return;
}

void exit_section
    PROTO_Z ()
{
  outs (".previous");
  d_outnl ();
  return;
}

void outnl_comment
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  outs ("\t/");
  outs (s);
  d_outnl ();
  return;
}

void outnl_comment_i
    PROTO_N ( (s, i) )
    PROTO_T ( char * s X long i )
{
  outs ("\t/");
  outs (s);
  outs (" ");
  outn (i);
  d_outnl ();
  return;
}

void out_dwf_label
    PROTO_N ( (l, set) )
    PROTO_T ( long l X int set )
{
  if (!l)
    failer ("unknown label");
  outs (".Ldw");
  outn (l);
  if (set) {
    outs (":");
    d_outnl ();
  }
  return;
}

void out_code_label
    PROTO_N ( (l) )
    PROTO_T ( long l )
{
  outs (local_prefix);
  outn (l);
  return;
}

void out_dwf_dist_to_label
    PROTO_N ( (l) )
    PROTO_T ( long l )
{
  out_dwf_label (l, 0);
  outs (" - . - 4");
  return;
}

void out_dwf_labdiff
    PROTO_N ( (lo, hi) )
    PROTO_T ( long lo X long hi )
{
  if (hi == lo)
    outn ((long)0);
  else {
    out_dwf_label (hi, 0);
    outs (" - ");
    out_dwf_label (lo, 0);
  }
  return;
}

void out_ext_label
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  outs (".globl ");
  outs (s);
  d_outnl ();
  outs (s);
  outs(":");
  d_outnl ();
  return;
}

void out_producer
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  outs (".string \"");
  outs (s);
  outs ("   with TenDRA 80x86/Solaris installer ");
  outn ((long)target_version) ;
  outs (".") ;
  outn ((long)target_revision) ;
  outs ("\"");
  d_outnl ();
  return;
}


static char * first_data = NULL;
static char * first_ro = NULL;

void note_data
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  if (!first_data)
    first_data = s;
  return;
}

void note_ro
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  if (!first_ro)
    first_ro = s;
  return;
}

void dw2_data_aranges
    PROTO_Z ()
{
  long lab_data = 0, lab_ro = 0;
  if (first_data) {
    lab_data = next_dwarf_label ();
    if (do_prom) {
      outs (".bss ");
      out_dwf_label (lab_data, 0);
      outs (", 0");
      d_outnl();
    }
    else {
      outs(".data");
      d_outnl();
      out_dwf_label (lab_data, 1);
    }
  }
  if (first_ro) {
    lab_ro = next_dwarf_label ();
    out_readonly_section();
    d_outnl();
    out_dwf_label (lab_ro, 1);
  }
  outs(".text");
  d_outnl();
  enter_section ("debug_aranges");
  if (first_data) {
    out32 (); outs (first_data); d_outnl ();
    out32 (); out_dwf_label (lab_data, 0); outs (" - ");
	outs (first_data); d_outnl ();
  }
  if (first_ro) {
    out32 (); outs (first_ro); d_outnl ();
    out32 (); out_dwf_label (lab_ro, 0); outs (" - ");
	outs (first_ro); d_outnl ();
  }
  exit_section ();
  return;
}
