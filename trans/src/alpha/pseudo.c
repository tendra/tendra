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

#include <shared/bool.h>
#include <shared/xalloc.h>

#include "cross.h"
#include "frames.h"
#include "pseudo.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "reg_defs.h"
#include "inst_fmt.h"

extern  FILE * as_file;
extern bool in_noat_block;

void
setprologue(int lvl)
{
  if(as_file){
    fprintf(as_file,"\t.prologue %d\n",lvl);
  }
  out_value(0,iprologue, make_INT64(0,lvl),0);
  /*out_value(0,iprologue,lvl,0);*/
  return;
}


void
setnoreorder(void)
{
  if(as_file){
    fprintf (as_file, "\t.set\tnoreorder\n");
  }
  out_value(0,iset, make_INT64(0,set_noreorder) ,0);
  return;
}

void
setreorder(void)
{
  if(as_file){
    fprintf (as_file, "\t.set\treorder\n");
  }
  out_value(0,iset, make_INT64(0,set_reorder) ,0);
  return;
}

void
setnomove(void)
{
  if(as_file){
    fprintf (as_file, "\t.set\tnomove\n");
  }
  out_value(0,iset, make_INT64(0,set_nomove),0);
  return;
}

void
setmove(void)
{
  if(as_file){
    fprintf (as_file, "\t.set\tmove\n");
  }
  out_value(0,iset, make_INT64(0,set_move),0);
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
  if (in_noat_block == true) {
    return;
  }
  else {
    in_noat_block = true;
  }
  if(as_file){
    fprintf (as_file, "\t.set\tnoat\n");
  }
  out_value(0,iset, make_INT64(0,set_noat),0);
  return;
}

void
setat(void)
{
  if (in_noat_block == false) {
    return;
  }
  else {
    in_noat_block = false;
  }
  if(as_file){
    fprintf (as_file, "\t.set\tat\n");
  }
  out_value(0,iset, make_INT64(0,set_at),0);
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
  if(Has_fp){
    if(as_file){
      fprintf(as_file,"\t.frame\t$fp, %d, $26, %d\n",st,loc);
    }
    out_frame(0,iframe,st,FP,26);
  }
  else{
    if(as_file){
      fprintf (as_file, "\t.frame\t$sp, %d, $26, %d\n", st,loc);
    }
    out_frame(0,iframe,st,SP,26);
  }
  return;
}

void
set_text_section(void)
{
  if(as_file){
    fprintf(as_file, "\t.text\n");
  }
  out_common(0,itext);
  set_align(128);
  return;
}

void
setmask(int32 mask, int32 disp)
{
  if(as_file){
    fprintf (as_file, "\t.mask\t0x%x,%d\n", mask, disp);
  }
  out_mask(0,imask,mask,disp);
  return;
}


void
setfmask(int32 mask, int32 disp)
{
  if(as_file){
    fprintf (as_file, "\t.fmask\t0x%x,%d\n", mask, disp);
  }
  out_mask(0,ifmask,mask,disp);
  return;
}



void
set_file(char *fname, int fno)
{
  if(as_file){
    fprintf(as_file,"\t.file\t%d \"%s\"\n",fno,fname+1);
  }
  return;
}


void
set_lineno(int lineno, int fileno)
{
  if(as_file){
    fprintf(as_file,"\t.loc\t%d %d\n",fileno,lineno);
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
  char * binasm_data;
  if(al!=current_alignment){
    switch(al){
     case 8:
       if(as_file){
	 fprintf(as_file,"\t.align 0\n");
       }
       binasm_data = out_value(0,ialign,make_INT64(0,0),0);
       break;
     case 16:
       if(as_file){
	 fprintf(as_file,"\t.align 1\n");
       }
       binasm_data = out_value(0,ialign,make_INT64(0,1),0);
       break;
     case 32:
       if(as_file){
	 fprintf(as_file,"\t.align 2\n");
       }
       binasm_data = out_value(0,ialign,make_INT64(0,2),0);
       break;
     case 64:
       if(as_file){
	 fprintf(as_file,"\t.align 3\n");
       }
       binasm_data = out_value(0,ialign,make_INT64(0,3),0);
       break;
     case 128:
       if(as_file){
	 fprintf(as_file,"\t.align 4\n");
       }
       binasm_data = out_value(0,ialign,make_INT64(0,4),0);
       break;
     default:;
    }
    current_alignment = al;
  }
  return;
}  
