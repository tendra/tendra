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
#include <shared/check.h>
#include <shared/xalloc.h>

#include <main/driver.h>
#include <main/print.h>

#include "cross.h"
#include "frames.h"
#include "pseudo.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "reg_defs.h"
#include "inst_fmt.h"

extern bool in_noat_block;

void
setprologue(int lvl)
{
  if(as_file){
    asm_printop(".prologue %d",lvl);
  }
  out_value(0,iprologue, make_INT64(0,lvl),0);
  /*out_value(0,iprologue,lvl,0);*/
}


void
setnoreorder(void)
{
  if(as_file){
    asm_printop(".set noreorder");
  }
  out_value(0,iset, make_INT64(0,set_noreorder) ,0);
}

void
setreorder(void)
{
  if(as_file){
    asm_printop(".set reorder");
  }
  out_value(0,iset, make_INT64(0,set_reorder) ,0);
}

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
    asm_printop(".set noat");
  }
  out_value(0,iset, make_INT64(0,set_noat),0);
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
    asm_printop(".set at");
  }
  out_value(0,iset, make_INT64(0,set_at),0);
}

void
setframe(int32 st, int32 loc)
{
  if(Has_fp){
    if(as_file){
      asm_printop(".frame $fp, %d, $26, %d",st,loc);
    }
    out_frame(0,iframe,st,FP,26);
  }
  else{
    if(as_file){
      asm_printop(".frame $sp, %d, $26, %d", st,loc);
    }
    out_frame(0,iframe,st,SP,26);
  }
}

void
set_text_section(void)
{
  if(as_file){
    asm_printop(".text");
  }
  out_common(0,itext);
  set_align(128);
}


void
set_file(char *fname, int fno)
{
  if(as_file){
    asm_printop(".file %d \"%s\"",fno,fname+1);
  }
}


void
set_lineno(int lineno, int fileno)
{
  if(as_file){
    asm_printop(".loc %d %d",fileno,lineno);
  }
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
	 asm_printop(".align 0");
       }
       binasm_data = out_value(0,ialign,make_INT64(0,0),0);
       break;
     case 16:
       if(as_file){
	 asm_printop(".align 1");
       }
       binasm_data = out_value(0,ialign,make_INT64(0,1),0);
       break;
     case 32:
       if(as_file){
	 asm_printop(".align 2");
       }
       binasm_data = out_value(0,ialign,make_INT64(0,2),0);
       break;
     case 64:
       if(as_file){
	 asm_printop(".align 3");
       }
       binasm_data = out_value(0,ialign,make_INT64(0,3),0);
       break;
     case 128:
       if(as_file){
	 asm_printop(".align 4");
       }
       binasm_data = out_value(0,ialign,make_INT64(0,4),0);
       break;
     default:;
    }
    current_alignment = al;
  }
  UNUSED(binasm_data); /* XXX */
}  
