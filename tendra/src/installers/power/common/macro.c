/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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
$Date: 1998/02/04 15:48:55 $
$Revision: 1.2 $
$Log: macro.c,v $
 * Revision 1.2  1998/02/04  15:48:55  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:02:08  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "memtdf.h"
#include "codegen.h"
#include "macro.h"
#include "stack.h"
#include "stdio.h"
#include "translat.h"
#include "instruct.h"
#include "comment.h"
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

static char * number_array[32]={
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

static void init_spr_macros PROTO_S ((void));

int do_macros = 0;
void init_macros  PROTO_Z ()
{
  int r;
  int number_per_line =0;
  fprintf(as_file,"#\tRegister macros for easier reading and debugging\n");
  
#define NUMBER_OF_MACROS_PER_LINE 5
  for (r = 0;r<=31;r++)
  {
    fprintf(as_file,".set %s,%d",reg_array[r],r);
    number_per_line ++;
    if(number_per_line ==NUMBER_OF_MACROS_PER_LINE)
    {
      fprintf(as_file,"\n");
      number_per_line = 0;
    }
    else
    {
      fprintf(as_file,";");
    }
  }
  fprintf(as_file,"\n");
  
  number_per_line=0;
  
  for(r = 0;r<=31;r++)
  {
    fprintf(as_file,".set %s,%d",freg_array[r],r);
    number_per_line ++;
    if(number_per_line ==NUMBER_OF_MACROS_PER_LINE)
    {
      fprintf(as_file,"\n");
      number_per_line = 0;
    }
    else
    {
      fprintf(as_file,";");
    }
  }
  fprintf(as_file,"\n");
  number_per_line=0;
  
  for(r = 0;r<=7;r++)
  {
    fprintf(as_file,".set %s,%d",cr_array[r],r);
    number_per_line ++;
    if(number_per_line ==NUMBER_OF_MACROS_PER_LINE)
    {
      fprintf(as_file,"\n");
      number_per_line = 0;
    }
    else
    {
      fprintf(as_file,";");
    }
  }
  fprintf(as_file,"\n");
  init_spr_macros();
#ifdef SHOW_FRAME_POINTER
  fprintf(as_file,".set %s,31\n",frame_pointer);
  fprintf(as_file,".set %s,30\n",top_pointer);
#endif
  return;
}

char * reg_macro PROTO_N ((reg)) PROTO_T (int reg)
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

char * freg_macro PROTO_N ((reg)) PROTO_T (int reg)
{    
  if (!do_macros)
    return number_array[reg];
  else
    return freg_array[reg];
}
char * cr_macro PROTO_N ((creg)) PROTO_T (int creg)
{ 
  if (!do_macros)
    return number_array[creg];
  else
    return cr_array[creg];
}
char * spr_macro PROTO_N ((spr)) PROTO_T (int spr)
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
      fail("Unknown spr code");
    }
  }
  return 0;
}

static void init_spr_macros PROTO_Z ()
{
  fprintf(as_file,".set %s,%d;",spr_mq,SPR_MQ);
  fprintf(as_file,".set %s,%d;",spr_xer,SPR_XER);
  fprintf(as_file,".set %s,%d;",spr_rtcu,SPR_RTCU);
  fprintf(as_file,".set %s,%d\n",spr_rtcl,SPR_RTCL);
  fprintf(as_file,".set %s,%d;",spr_dec,SPR_DEC);
  fprintf(as_file,".set %s,%d;",spr_lr,SPR_LR);
  fprintf(as_file,".set %s,%d\n",spr_ctr,SPR_CTR);
  return;
}

  
