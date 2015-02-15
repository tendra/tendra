/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/error.h>

#include <main/driver.h>
#include <main/print.h>

#include "memtdf.h"
#include "codegen.h"
#include "macro.h"
#include "stack.h"
#include "stdio.h"
#include "translate.h"
#include "instruct.h"

#ifdef SHOW_FRAME_POINTER
static char *frame_pointer = "FP";
static char *top_pointer = "TP";
#endif

static char * spr_mq = "SPR_MQ";
static char * spr_xer = "SPR_XER";
static char * spr_rtcu = "SPR_RTCU";
static char * spr_rtcl = "SPR_RTCL";
static char * spr_dec = "SPR_DEC";
static char * spr_lr = "SPR_LR";
static char * spr_ctr = "SPR_CTR";

static char * number_array[32] ={
    "0","1","2","3","4","5","6","7","8","9","10","11","12","13","14",
    "15","16","17","18","19","20","21","22","23","24","25","26","27",
    "28","29","30","31"
};

static char * reg_array[32] = {
    "r0","SP","RTOC","r3","r4","r5","r6","r7","r8","r9","r10","r11",
    "r12","r13","r14","r15","r16","r17","r18","r19","r20","r21","r22",
    "r23","r24","r25","r26","r27","r28","r29","r30","r31"
};

static char * freg_array[32] = {
    "fp0","fp1","fp2","fp3","fp4","fp5","fp6","fp7","fp8","fp9","fp10",
    "fp11","fp12","fp13","fp14","fp15","fp16","fp17","fp18","fp19",
    "fp20","fp21","fp22","fp23","fp24","fp25","fp26","fp27","fp28",
    "fp29","fp30","fp31"
};

static char * cr_array[8] = {
    "cr0","cr1","cr2","cr3","cr4","cr5","cr6","cr7"
};

static void init_spr_macros(void);

int do_macros = 0;
void init_macros(void)
{
  int r;
  int number_per_line =0;
  asm_printf("#\tRegister macros for easier reading and debugging\n");

#define NUMBER_OF_MACROS_PER_LINE 5
  for (r = 0;r<=31;r++)
  {
    asm_printf(".set %s,%d",reg_array[r],r);
    number_per_line ++;
    if (number_per_line ==NUMBER_OF_MACROS_PER_LINE)
    {
      asm_printf("\n");
      number_per_line = 0;
    }
    else
    {
      asm_printf(";");
    }
  }
  asm_printf("\n");

  number_per_line=0;

  for (r = 0;r<=31;r++)
  {
    asm_printf(".set %s,%d",freg_array[r],r);
    number_per_line ++;
    if (number_per_line ==NUMBER_OF_MACROS_PER_LINE)
    {
      asm_printf("\n");
      number_per_line = 0;
    }
    else
    {
      asm_printf(";");
    }
  }
  asm_printf("\n");
  number_per_line=0;

  for (r = 0;r<=7;r++)
  {
    asm_printf(".set %s,%d",cr_array[r],r);
    number_per_line ++;
    if (number_per_line ==NUMBER_OF_MACROS_PER_LINE)
    {
      asm_printf("\n");
      number_per_line = 0;
    }
    else
    {
      asm_printf(";");
    }
  }
  asm_printf("\n");
  init_spr_macros();
#ifdef SHOW_FRAME_POINTER
  asm_printf(".set %s,31\n",frame_pointer);
  asm_printf(".set %s,30\n",top_pointer);
#endif
}

char * reg_macro(int reg)
{
  if (!do_macros)
    return number_array[reg];
  else
  {
#ifdef SHOW_FRAME_POINTER
    if (reg == 31 && p_has_fp)
      return frame_pointer;
    if (reg == 30 && p_has_tp)
      return top_pointer;
#endif
    return reg_array[reg];
  }
}

char * freg_macro(int reg)
{
  if (!do_macros)
    return number_array[reg];
  else
    return freg_array[reg];
}
char * cr_macro(int creg)
{
  if (!do_macros)
    return number_array[creg];
  else
    return cr_array[creg];
}
char * spr_macro(int spr)
{
  if (!do_macros)
    return number_array[spr];
  else
  {
    switch (spr)
    {
     case SPR_XER:return spr_xer;
     case SPR_MQ:return spr_mq;
     case SPR_RTCU:return spr_rtcu;
     case SPR_RTCL:return spr_rtcl;
     case SPR_DEC:return spr_dec;
     case SPR_LR:return spr_lr;
     case SPR_CTR:return spr_ctr;
     default:
      error(ERR_SERIOUS, "Unknown spr code");
    }
  }
  return 0;
}

static void init_spr_macros(void)
{
  asm_printf(".set %s,%d;",spr_mq,SPR_MQ);
  asm_printf(".set %s,%d;",spr_xer,SPR_XER);
  asm_printf(".set %s,%d;",spr_rtcu,SPR_RTCU);
  asm_printf(".set %s,%d\n",spr_rtcl,SPR_RTCL);
  asm_printf(".set %s,%d;",spr_dec,SPR_DEC);
  asm_printf(".set %s,%d;",spr_lr,SPR_LR);
  asm_printf(".set %s,%d\n",spr_ctr,SPR_CTR);
}
