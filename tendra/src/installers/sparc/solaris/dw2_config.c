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


/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/solaris/dw2_config.c,v 1.3 1998/03/11 11:04:05 pwe Exp $
--------------------------------------------------------------------------
$Log: dw2_config.c,v $
 * Revision 1.3  1998/03/11  11:04:05  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/01/21  10:30:14  pwe
 * labdiff change
 *
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1998/01/09  15:00:02  pwe
 * prep restructure
 *
 * Revision 1.6  1997/12/04  19:54:46  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.5  1997/11/06  09:29:25  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.4  1997/10/23  09:33:37  pwe
 * prep extra_diags
 *
 * Revision 1.3  1997/10/10  18:33:29  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.2  1997/08/23  13:55:13  pwe
 * initial ANDF-DE
 *
 * Revision 1.1  1997/04/17  12:00:24  pwe
 * dwarf2 support
 *
--------------------------------------------------------------------------
*/

#include "config.h"
#include "dw2_config.h"
#include "translat.h"
#include "eval.h"
#include "flags.h"
#include "labels.h"
#include "basicread.h"
#include "target_v.h"

long dwarf_lab_num = 0;

void out8 
    PROTO_Z ()
{
  outs ( "\t.byte " ) ;
  return;
}

void out16 
    PROTO_Z ()
{
#ifdef NEEDS_DEBUG_ALIGN
  dot_align(2);
#endif
  outs ( "\t.half " ) ;
  return;
}

void out32 
    PROTO_Z ()
{
#ifdef NEEDS_DEBUG_ALIGN
  dot_align(4);
#endif
  outs ( "\t.word " ) ;
  return;
}

void dot_align 
    PROTO_N ( ( n ) )
    PROTO_T ( long n )
{
  outs ( "\t.align " ) ;
  outn (n);
  outnl();
  return;
}

void out_string 
    PROTO_N ( ( s ) )
    PROTO_T ( char * s )
{
  outs ("\t.asciz \"");
  outs (s);
  outs ("\"");
  d_outnl ();
  return;
}

void start_string
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  outs ("\t.asciz \"");
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
    PROTO_N ( ( s ) )
    PROTO_T ( char * s )
{
  outs ("\t.section \".");
  outs (s);
  outs ("\"");
  d_outnl ();
  return;
}

void exit_section 
    PROTO_Z ()
{
  enum section old = current_section;
  current_section = no_section;
  insection (old);
  return;
}

void outnl_comment 
    PROTO_N ( ( s ) )
    PROTO_T ( char * s )
{
  outs ("\t!");
  outs (s);
  d_outnl ();
  return;
}

void outnl_comment_i 
    PROTO_N ( ( s, i ) )
    PROTO_T ( char * s X long i )
{
  outs ("\t!");
  outs (s);
  outs (" ");
  outn (i);
  d_outnl ();
  return;
}

void out_dwf_label 
    PROTO_N ( ( l, set ) )
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
    PROTO_N ( ( l ) )
    PROTO_T ( long l )
{
  outs (lab_prefix);
  outn (l);
  return;
}

void out_dwf_dist_to_label 
    PROTO_N ( ( l ) )
    PROTO_T ( long l )
{
  out_dwf_label (l, 0);
  outs (" - . - 4");
  return;
}

void out_dwf_labdiff 
    PROTO_N ( ( lo, hi ) )
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
    PROTO_N ( ( s ) )
    PROTO_T ( char * s )
{
  outs ("\t.global\t");
  outs (s);
  d_outnl ();
  outs (s);
  outs(":");
  d_outnl ();
  return;
}

void out_producer 
    PROTO_N ( ( s ) )
    PROTO_T ( char * s )
{
  outs ("\t.asciz \"");
  outs (s);
  outs ("   with TenDRA SPARC/Solaris installer ");
  outn ( target_version ) ;
  outs ( "." ) ;
  outn ( target_revision ) ;
  outs ("\"");
  d_outnl ();
  return;
}


static int first_data = 0;
static int first_ro = 0;

void note_data 
    PROTO_N ( ( ll, ro ) )
    PROTO_T ( int ll X bool ro )
{
  if (ro) {
    if (!first_ro)
      first_ro = ll;
  }
  else {
    if (!first_data)
      first_data = ll;
  }
  return;
}

void dw2_data_aranges 
    PROTO_Z ()
{
  long lab_data, lab_ro;
  if (first_data) {
    lab_data = next_dwarf_label ();
    if (do_prom) {
      outs ("\t.reserve\t");
      out_dwf_label (lab_data, 0);
      outs (", 0,\".bss\",4");
      d_outnl();
    }
    else {
      insection (data_section);
      out_dwf_label (lab_data, 1);
    }
  }
  if (first_ro) {
    lab_ro = next_dwarf_label ();
    insection (rodata_section);
    out_dwf_label (lab_ro, 1);
  }
  insection (text_section);
  enter_section ("debug_aranges");
  if (first_data) {
    out32 (); outlab (first_data); d_outnl ();
    out32 (); out_dwf_label (lab_data, 0); outs (" - ");
	outlab (first_data); d_outnl ();
  }
  if (first_ro) {
    out32 (); outlab (first_ro); d_outnl ();
    out32 (); out_dwf_label (lab_ro, 0); outs (" - ");
	outlab (first_ro); d_outnl ();
  }
  exit_section ();
  return;
}
