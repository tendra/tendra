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
#include <main/print.h>

#include "translate.h"
#include "eval.h"
#include "labels.h"

long dwarf_lab_num = 0;

void out8(void)
{
  asm_printf("\t.byte ");
}

void out16(void)
{
  if (needs_debug_align) {
    dot_align(2);
  }
  asm_printf("\t.half ");
}

void out32(void)
{
  if (needs_debug_align) {
    dot_align(4);
  }
  asm_printf("\t.word ");
}

void dot_align(long n)
{
  asm_printop(".align %ld", n);
}

void out_string(char *s)
{
  asm_printop(".asciz \"%s\"", s);
}

void start_string(char *s)
{
  asm_printf("\t.asciz \"%s", s);
}

void end_string(void)
{
  asm_printf("\"\n");
}

void enter_section(char *s)
{
  asm_printop(".section \".%s\"", s);
}

void exit_section(void)
{
  enum section old = current_section;
  current_section = no_section;
  insection (old);
}

void out_dwf_label(long l, int set)
{
  if (!l)
    error(ERR_INTERNAL, "unknown label");
  asm_printf(".Ldw%ld", l);
  if (set) {
    asm_printf(":\n");
  }
}

void out_code_label(long l)
{
  asm_printf("%s%d", lab_prefix, l);
}

void out_dwf_dist_to_label(long l)
{
  out_dwf_label (l, 0);
  asm_printf(" - . - 4");
}

void out_dwf_labdiff(long lo, long hi)
{
  if (hi == lo)
    asm_printf("%d", 0);
  else {
    out_dwf_label (hi, 0); 
    asm_printf(" - ");
    out_dwf_label (lo, 0);
  }
}

void out_ext_label(char *s)
{
  asm_printop(".global %s\n", s);
  asm_label("%s", s);
}

void out_producer(char *s)
{
  asm_printop(".asciz \"%s %s\"", s, "trans.sparc installer");
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
}

void dw2_data_aranges(void)
{
  long lab_data, lab_ro;
  if (first_data) {
    lab_data = next_dwarf_label ();
    if (do_prom) {
      asm_printf("\t.reserve ");
      out_dwf_label (lab_data, 0);
      asm_printf(", 0,\".bss\",4\n");
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
    out32 (); outlab (first_data); asm_printf("\n");
    out32 (); out_dwf_label (lab_data, 0); asm_printf(" - ");
	outlab (first_data); asm_printf("\n");
  }
  if (first_ro) {
    out32 (); outlab (first_ro); asm_printf("\n");
    out32 (); out_dwf_label (lab_ro, 0); asm_printf(" - ");
	outlab (first_ro); asm_printf("\n");
  }
  exit_section ();
}
