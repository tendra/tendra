/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
*/


/* 	$Id$	 */

#ifndef lint
static char vcid[] = "$Id$";
#endif /* lint */
/* 
   psu_ops.c
   Output various psuedo operations to assembler 
*/

/**/

#include "config.h"
#include "cross.h"
#include "frames.h"
#include "pseudo.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "reg_defs.h"
#include "xalloc.h"
#include "bool.h"
#if DO_SCHEDULE
#include "scheduler.h"
#endif
#include "inst_fmt.h"
#include "main.h"
#include "eval.h"

void setprologue
    PROTO_N ( ( lvl ) )
    PROTO_T ( int lvl )
{
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(20,sizeof(char));
#endif
  if(as_file){
#if !DO_SCHEDULE
    fprintf(as_file,"\t.prologue %d\n",lvl);
#else
    sprintf(outline,"\t.prologue %d\n",lvl);
#endif
  }
  output_instruction(class_null,outline,out_value(0,iprologue,
						  make_INT64(0,lvl),0));
  /*out_value(0,iprologue,lvl,0);*/
  return;
}


void setnoreorder
    PROTO_Z ()
{
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(20,sizeof(char));
#endif
  if(as_file){
#if !DO_SCHEDULE
    fprintf (as_file, "\t.set\tnoreorder\n");
#else
    sprintf(outline,"\t.set\tnoreorder\n");
#endif
  }
  output_instruction(class_null,outline,out_value(0,iset,
						  make_INT64(0,set_noreorder)
						  ,0));
  return;
}

void setreorder
    PROTO_Z ()
{
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(20,sizeof(char));
#endif
  if(as_file){
#if !DO_SCHEDULE
    fprintf (as_file, "\t.set\treorder\n");
#else
    sprintf(outline,"\t.set\treorder\n");
#endif
  }
  output_instruction(class_null,outline,out_value(0,iset,
						  make_INT64(0,set_reorder)
						  ,0));
  return;
}

void setnomove
    PROTO_Z ()
{
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(20,sizeof(char));
#endif
  if(as_file){
#if !DO_SCHEDULE
    fprintf (as_file, "\t.set\tnomove\n");
#else
    sprintf(outline,"\t.set\tnomove\n");
#endif
  }
  output_instruction(class_null,outline,out_value(0,iset,
						  make_INT64(0,set_nomove),0));
  return;
}

void setmove
    PROTO_Z ()
{
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(20,sizeof(char));
#endif
  if(as_file){
#if !DO_SCHEDULE
    fprintf (as_file, "\t.set\tmove\n");
#else
    sprintf(outline,"\t.set\tmove\n");
#endif
  }
  output_instruction(class_null,outline,out_value(0,iset,
						  make_INT64(0,set_move),0));
  return;
}

#if 0
void setvolatile
    PROTO_Z ()
{
/*    fprintf (as_file, "\t.set\tvolatile\n");*/
  return;
}

void setnovolatile
    PROTO_Z ()
{
  fprintf (as_file, "\t.set\tnovolatile\n");
  return;
}
#endif

void setnoat
    PROTO_Z ()
{
  char *outline;
  if (in_noat_block == TRUE) {
    return;
  }
  else {
    in_noat_block = TRUE;
  }
  outline = (char*)xcalloc(20,sizeof(char));
  sprintf(outline,"\t.set\tnoat\n");
  if(as_file){
#if !DO_SCHEDULE
    fprintf (as_file, "\t.set\tnoat\n");
#endif
  }
  output_instruction(class_null,outline,out_value(0,iset,
						  make_INT64(0,set_noat),0));
  return;
}

void setat
    PROTO_Z ()
{
  char *outline;
  if (in_noat_block == FALSE) {
    return;
  }
  else {
    in_noat_block = FALSE;
  }
  outline = (char*)xcalloc(20,sizeof(char));
  sprintf(outline,"\t.set\tat\n");
  if(as_file){
#if !DO_SCHEDULE
    fprintf (as_file, "\t.set\tat\n");
#endif
  }
  output_instruction(class_null,outline,out_value(0,iset,
						  make_INT64(0,set_at),0));
  return;
}

void comment
    PROTO_N ( ( mess ) )
    PROTO_T ( char *mess )
{
  if(as_file){
    fprintf (as_file, " # %s\n", mess);
  }
  return;
}

void setframe
    PROTO_N ( ( st,loc ) )
    PROTO_T ( int32 st X int32 loc )
{
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(80,sizeof(char));
#endif
  if(Has_fp){
    if(as_file){
#if !DO_SCHEDULE
      fprintf(as_file,"\t.frame\t$fp, %d, $26, %d\n",st,loc);
#else
      sprintf(outline,"\t.frame\t$fp, %d, $26, %d\n",st,loc);
#endif
    }
    output_instruction(class_null,outline,out_frame(0,iframe,st,FP,26));
  }
  else{
    if(as_file){
#if !DO_SCHEDULE
      fprintf (as_file, "\t.frame\t$sp, %d, $26, %d\n", st,loc);
#else
      sprintf(outline,"\t.frame\t$sp, %d, $26, %d\n", st,loc);
#endif
    }
    output_instruction(class_null,outline,out_frame(0,iframe,st,SP,26));
  }
  return;
}

void set_text_section
    PROTO_Z ()
{
  if(as_file){
#if !DO_SCHEDULE
    fprintf(as_file, "\t.text\n");
#endif
  }
#if DO_SCHEDULE
  output_instruction(class_null,"\t.text\n",out_common(0,itext));
#else
  out_common(0,itext);
#endif
  set_align(128);
  return;
}

void setmask
    PROTO_N ( ( mask,disp ) )
    PROTO_T ( int32 mask X int32 disp )
{
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(20,sizeof(char));
#endif
  if(as_file){
#if !DO_SCHEDULE
    fprintf (as_file, "\t.mask\t0x%x,%d\n", mask, disp);
#else
    sprintf (outline, "\t.mask\t0x%x,%d\n", mask, disp);
#endif
  }
  output_instruction(class_null,outline,out_mask(0,imask,mask,disp));
  return;
}


void setfmask
    PROTO_N ( ( mask, disp ) )
    PROTO_T ( int32 mask X int32 disp )
{
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(20,sizeof(char));
#endif
  if(as_file){
#if !DO_SCHEDULE
    fprintf (as_file, "\t.fmask\t0x%x,%d\n", mask, disp);
#else
    sprintf(outline,"\t.fmask\t0x%x,%d\n", mask, disp);
#endif
  }
  output_instruction(class_null,outline,out_mask(0,ifmask,mask,disp));
  return;
}



void set_file
    PROTO_N ( ( fname,fno ) )
    PROTO_T ( char *fname X int fno )
{
  if(as_file){
#if !DO_SCHEDULE
    fprintf(as_file,"\t.file\t%d \"%s\"\n",fno,fname+1);
#endif
  }
  return;
}


void set_lineno
    PROTO_N ( ( lineno,fileno ) )
    PROTO_T ( int lineno X int fileno )
{
  if(as_file){
#if DO_SCHEDULE
    fprintf(as_file,"\t.loc\t%d %d\n",fileno,lineno);
#endif
  }
  return;
}




/*
  This function outputs an appropriate .align directive 
  depending on the value of al.
*/
void set_align
    PROTO_N ( ( al ) )
    PROTO_T ( int al )
{
#if DO_SCHEDULE
  Instruction new_ins = getinst();
  Instruction_data ins_dat = get_new_ins_data();
#endif
  char * binasm_data;
#if DO_SCHEDULE
  char *outline = (char*)xcalloc(80,sizeof(char));
#endif
  if(al!=current_alignment){
    switch(al){
     case 8:
       if(as_file){
#if !DO_SCHEDULE
	 fprintf(as_file,"\t.align 0\n");
#else
	 sprintf(outline,"\t.align 0\n");
#endif
       }
       binasm_data = out_value(0,ialign,make_INT64(0,0),0);
       break;
     case 16:
       if(as_file){
#if !DO_SCHEDULE
	 fprintf(as_file,"\t.align 1\n");
#else
	 sprintf(outline,"\t.align 1\n");
#endif
       }
       binasm_data = out_value(0,ialign,make_INT64(0,1),0);
       break;
     case 32:
       if(as_file){
#if !DO_SCHEDULE
	 fprintf(as_file,"\t.align 2\n");
#else
	 sprintf(outline,"\t.align 2\n");
#endif
       }
       binasm_data = out_value(0,ialign,make_INT64(0,2),0);
       break;
     case 64:
       if(as_file){
#if !DO_SCHEDULE
	 fprintf(as_file,"\t.align 3\n");
#else
	 sprintf(outline,"\t.align 3\n");
#endif	
       }
       binasm_data = out_value(0,ialign,make_INT64(0,3),0);
       break;
     case 128:
       if(as_file){
#if DO_SCHEDULE
	 sprintf(outline,"\t.align 4\n");
#else
	 fprintf(as_file,"\t.align 4\n");
#endif
       }
       binasm_data = out_value(0,ialign,make_INT64(0,4),0);
       break;
     default:;
    }
#if DO_SCHEDULE
    setclass(new_ins,class_null);
    set_instruction_text(ins_dat,outline);
    set_instruction_binasm(ins_dat,binasm_data);
    setdata(new_ins,ins_dat);
    process_instruction(new_ins);
#endif
    current_alignment = al;
  }
  return;
}  
