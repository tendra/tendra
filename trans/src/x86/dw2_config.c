/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/error.h>

#include <local/dw2_config.h>
#include <local/out.h>

#include <reader/basicread.h>

#include <construct/machine.h>

#include <main/flags.h>
#include <main/print.h>

#include "localtypes.h"

long dwarf_lab_num = 0;

void
out_string(char *s)
{
  asm_printf(".string \"%s\"\n", s);
}

void
start_string(char *s)
{
  asm_printf(".string \"%s", s);
}

void
end_string(void)
{
  asm_printf("\"\n");
}

void
enter_section(char *s)
{
  asm_printf(".section .%s\n", s);
}

void
exit_section(void)
{
  asm_printf(".previous\n");
}

void
out_dwf_label(long l, int set)
{
  if (!l) {
    error(ERR_INTERNAL, "unknown label");
  }
  if (set) {
    asm_label(".Ldw%ld", l);
  } else {
    asm_printf(".Ldw%ld", l);
  }
}

void
out_code_label(long l)
{
  asm_printf("%s%ld", local_prefix, l);
}

void
out_dwf_dist_to_label(long l)
{
  out_dwf_label(l, 0);
  asm_printf(" - . - 4");
}

void
out_dwf_labdiff(long lo, long hi)
{
  if (hi == lo) {
    asm_printf("%d", 0);
  } else {
    out_dwf_label(hi, 0);
    asm_printf(" - ");
    out_dwf_label(lo, 0);
  }
}

void
out_ext_label(char *s)
{
  asm_label(".globl %s", s);
}

void
out_producer(char *s)
{
  asm_printop(".string \"%s %s\"", s, "trans.x86 installer");
}


static char *first_data = NULL;
static char *first_ro = NULL;

void
note_data(char *s)
{
  if (!first_data) {
    first_data = s;
  }
}

void
note_ro(char *s)
{
  if (!first_ro) {
    first_ro = s;
  }
}

void
dw2_data_aranges(void)
{
  long lab_data = 0, lab_ro = 0;
  if (first_data) {
    lab_data = next_dwarf_label();
    if (do_prom) {
      asm_printf(".bss ");
      out_dwf_label(lab_data, 0);
      asm_printf(", 0\n");
    } else {
      asm_printf(".data\n");
      out_dwf_label(lab_data, 1);
    }
  }
  if (first_ro) {
    lab_ro = next_dwarf_label();
    out_readonly_section();
    asm_printf("\n");
    out_dwf_label(lab_ro, 1);
  }
  asm_printf(".text\n");
  enter_section("debug_aranges");
  if (first_data) {
    out32(); asm_printf("%s\n", first_data);
    out32(); out_dwf_label(lab_data, 0); asm_printf(" - %s\n", first_data);
  }
  if (first_ro) {
    out32(); asm_printf("%s\n", first_ro);
    out32(); out_dwf_label(lab_ro, 0); asm_printf(" - %s\n", first_ro);
  }
  exit_section();
}
