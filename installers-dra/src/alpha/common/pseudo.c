/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* 
   psu_ops.c
   Output various psuedo operations to assembler 
*/

#include <stdio.h>

#include <shared/xalloc.h>

#include "config.h"

#include "cross.h"
#include "frames.h"
#include "pseudo.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "reg_defs.h"
#include "bool.h"
#include "inst_fmt.h"

#if DO_SCHEDULE
#include "scheduler.h"
#endif

extern  FILE * as_file;
extern bool in_noat_block;

void
setprologue(int lvl)
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


void
setnoreorder(void)
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

void
setreorder(void)
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

void
setnomove(void)
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

void
setmove(void)
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
void
setvolatile(void)
{
/*    fprintf (as_file, "\t.set\tvolatile\n");*/
  return;
}

void
setnovolatile(void)
{
  fprintf (as_file, "\t.set\tnovolatile\n");
  return;
}
#endif

void
setnoat(void)
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

void
setat(void)
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

void
comment(char *mess)
{
  if(as_file){
    fprintf (as_file, " # %s\n", mess);
  }
  return;
}

void
setframe(int32 st, int32 loc)
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

void
set_text_section(void)
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

void
setmask(int32 mask, int32 disp)
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


void
setfmask(int32 mask, int32 disp)
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



void
set_file(char *fname, int fno)
{
  if(as_file){
#if !DO_SCHEDULE
    fprintf(as_file,"\t.file\t%d \"%s\"\n",fno,fname+1);
#endif
  }
  return;
}


void
set_lineno(int lineno, int fileno)
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
void
set_align(int al)
{
  extern int current_alignment;
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
