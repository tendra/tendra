/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/error.h>

#include <local/dw2_config.h>

#include <reader/basicread.h>

#include <main/driver.h>
#include <main/flags.h>

#include "translate.h"
#include "eval.h"
#include "labels.h"

long dwarf_lab_num = 0;

void out8(void)
{
  outs ( "\t.byte " ) ;
  return;
}

void out16(void)
{
  if (needs_debug_align) {
    dot_align(2);
  }
  outs ( "\t.half " ) ;
  return;
}

void out32(void)
{
  if (needs_debug_align) {
    dot_align(4);
  }
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
    error(ERROR_INTERNAL, "unknown label");
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
    outn (0);
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
  outs ("   TenDRA SPARC/Solaris installer ");
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
