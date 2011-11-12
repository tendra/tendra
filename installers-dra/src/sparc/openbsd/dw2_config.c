/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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

void out8(void)
{
  outs ( "\t.byte " ) ;
  return;
}

void out16(void)
{
#ifdef NEEDS_DEBUG_ALIGN
  dot_align(2);
#endif
  outs ( "\t.half " ) ;
  return;
}

void out32(void)
{
#ifdef NEEDS_DEBUG_ALIGN
  dot_align(4);
#endif
  outs ( "\t.word " ) ;
  return;
}

void dot_align(long n)
{
  outs ( "\t.align " ) ;
  outn (n);
  outnl();
  return;
}

void out_string(char *s)
{
  outs ("\t.asciz \"");
  outs (s);
  outs ("\"");
  d_outnl ();
  return;
}

void start_string(char *s)
{
  outs ("\t.asciz \"");
  outs (s);
  return;
}

void end_string(void)
{
  outs ("\"");
  d_outnl ();
  return;
}

void enter_section(char *s)
{
  outs ("\t.section \".");
  outs (s);
  outs ("\"");
  d_outnl ();
  return;
}

void exit_section(void)
{
  enum section old = current_section;
  current_section = no_section;
  insection (old);
  return;
}

void outnl_comment(char *s)
{
  outs ("\t!");
  outs (s);
  d_outnl ();
  return;
}

void outnl_comment_i(char *s, long i)
{
  outs ("\t!");
  outs (s);
  outs (" ");
  outn (i);
  d_outnl ();
  return;
}

void out_dwf_label(long l, int set)
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

void out_code_label(long l)
{
  outs (lab_prefix);
  outn (l);
  return;
}

void out_dwf_dist_to_label(long l)
{
  out_dwf_label (l, 0);
  outs (" - . - 4");
  return;
}

void out_dwf_labdiff(long lo, long hi)
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

void out_ext_label(char *s)
{
  outs ("\t.global\t");
  outs (s);
  d_outnl ();
  outs (s);
  outs(":");
  d_outnl ();
  return;
}

void out_producer(char *s)
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

void note_data(int ll, bool ro)
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

void dw2_data_aranges(void)
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
