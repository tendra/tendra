/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* dragonfly/assembler.c */

#include <shared/xalloc.h>

#include "config.h"

#include "exptypes.h"
#include <construct/exp.h>
#include "instr.h"
#include "out.h"
#include "expmacs.h"
#include "operand.h"
#include <construct/machine.h>
#include "localflags.h"
#include <reader/basicread.h>
#include "coder.h"


/* PROCEDURES */

void
dot_align(int n)
{
  if (format == FORMAT_ELF) {
    outs(".align ");
    outn((long)n);
    outnl();
    return;
  }
  if (n == 1)
    return;
  outs(".align ");
  switch (n) {
    case 16:
      n = 4;
      break;
    case 8:
      n = 3;
      break;
    case 4:
      n = 2;
      break;
    default:
      n = 1;
      break;
  }
  outn((long)n);
  outnl();
  return;
}


void
outbyte(void)
{
  outs(".byte ");
  return;
}

void
outshort(void)
{
  outs(".value ");
  return;
}

void
outlong(void)
{
  outs(".long ");
  return;
}

void
align_label(int f, exp jr)
{
  if (format == FORMAT_ELF) {
    if (is80486 && !is80586 && ptno(jr) != last_jump_label) {
      /* repeat jump */
      if (f == 1) {
        outs(".align 4");
      }
      /* preceded by a jmp or ret */
      if (f == 2) {
        outs(".align 16");
      }
      outs("\n");
      return;
    }
  }
  if (is80486 && !is80586 && ptno(jr) != last_jump_label) {
    /* repeat jump */
    if (f == 1)	{
      outs(".align 3,0x90");
    }
    /* preceded by a jmp or ret */
    if (f == 2)	{
      outs(".align 4,0x90");
    }
    if (f == 3) {
      outs(".align 2,0x90");
    }
    outs("\n");
  }
  if (is80586 && ptno(jr) != last_jump_label) {
    if (f >= 1 && f <= 3) {
      outs(".align 2,0x90\n");
    }
  }
  return;
}

void
eval_postlude(char *s, exp c)
{
  UNUSED(s);
  UNUSED(c);
  return;
}

void
out_readonly_section(void)
{
  if (format == FORMAT_ELF) {
    outs(".section .rodata");
  } else {
    outs(".text");
  }
  return;
}

void
out_dot_comm(char *id, shape sha)
{
  outs(".comm ");
  outs(id);
  outs(",");
  outn((long)(((shape_size(sha) / 8) + 3) / 4)* 4);
  outnl();
  return;
}

void
out_dot_lcomm(char *id, shape sha)
{
  outs(".lcomm ");
  outs(id);
  outs(",");
  outn((long)(((shape_size(sha) / 8) + 3) / 4)* 4);
  outnl();
  return;
}

void
out_bss(char *id, shape sha)
{
  outs(".bss ");
  outs(id);
  outs(",");
  outn((long)(((shape_size(sha) / 8) + 3) / 4)* 4);
  outnl();
  return;
}

void
pic_prelude(void)
{
  return;
}

void
out_rename(char *oldid, char *newid)
{
  UNUSED(oldid);
  UNUSED(newid);
  return;
}

void
out_switch_jump(int tab, where a, int min)
{
  outs(" jmp *");
  outs(local_prefix);
  outn((long)tab);
  outs("-");
  outn((long)(4 * min));
  outs("(,");
  operand(32, a, 1, 0);
  outs(",4)");
  outnl();
  return;
}

void
out_switch_table(int tab, int min, int max, int *v, int absent)
{
  int i;

  dot_align(4);
  outnl();

  outs(local_prefix);
  outn((long)tab);
  outs(":");
  outnl();

  for (i = min; i <= max; ++i) {
    outs(".long ");
    if (v[i - min] != -1) {
      outs(local_prefix);
      outn((long)v[i - min]);
    }
    else {
      if (absent == -1) {
        outn((long)0);
      } else {
        outs(local_prefix);
        outn((long)absent);
      }
    }
    outnl();
  }
  outnl();
  return;
}

void
proc_size(char *s)
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

void
proc_type(char *s)
{
  outs(".type ");
  outs(s);
  outs(",@function");
  outnl();
  return;
}

void
outend(void)
{
  outs(".text");
  outnl();
  dot_align(16);
  outnl();
  outs("___tdf_end:");
  outnl();
  out_close();
}

void
outopenbr(void)
{
  return;
}


void
outclosebr(void)
{
  return;
}

void
outdivsym(void)
{
  outs("/");
  return;
}

void
out_initialiser(char *id)
{
  if (format == FORMAT_ELF) {
    outs(".section .init");
    outnl();
    outs(" call ");
    outs(id);
  } else {
    outs(".stabs \"___TDFI_LIST__\",22,0,0,");
    outs(id);
    outnl();
    outnl();
  }
  return;
}


void
out_main_prelude(void) /* FORMAT_AOUT */
{
  int nl1 = next_lab();
  int nl2 = next_lab();
  min_rfree |= 0x8;
  outs(" movl $___TDFI_LIST__+4, %ebx\n");
  outs(local_prefix);
  outn((long)nl1);
  outs(":\n");
  outs(" movl (%ebx),%eax\n");
  outs(" cmpl $0,%eax\n");
  simple_branch("je", nl2);
  outs(" call *%eax\n");
  outs(" addl $4,%ebx\n");
  simple_branch("jmp", nl1);
  outs(local_prefix);
  outn((long)nl2);
  outs(":\n");
  return;
}

void
out_main_postlude(void) /* FORMAT_AOUT */
{
  char *sdummy = "Idummy";
  char *pdummy = (char *)xcalloc(((int)strlen(local_prefix) +
				  (int)strlen(sdummy) + 1), sizeof(char));
  strcpy(pdummy, local_prefix);
  strcat(pdummy, sdummy);
  outs(".text\n");
  outs(pdummy);
  outs(":\n");
  outs(" ret\n");
  out_initialiser(pdummy);
  return;
}
