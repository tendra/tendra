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


/* 	$Id: pseudo.c,v 1.1.1.1 1998/01/17 15:56:01 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: pseudo.c,v 1.1.1.1 1998/01/17 15:56:01 release Exp $";
#endif /* lint */
/* 
   psu_ops.c
   Output various psuedo operations to assembler 
*/

/*
$Log: pseudo.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:01  release
 * First version to be checked into rolling release.
 *
 * Revision 1.9  1995/12/04  09:12:44  john
 * Fix to diagnostics
 *
 * Revision 1.8  1995/08/30  16:14:58  john
 * Fix for use of AT register
 *
 * Revision 1.7  1995/05/23  13:25:06  john
 * Reformatting
 *
 * Revision 1.6  1995/05/16  10:54:43  john
 * Cosmetic changes
 *
 * Revision 1.5  1995/04/10  14:13:47  john
 * Minor changes
 *
 * Revision 1.4  1995/04/07  11:05:25  john
 * Changed assembler output.
 *
 * Revision 1.3  1995/03/29  14:08:19  john
 * Added inclusion of bool.h
 *
 * Revision 1.2  1995/03/29  10:31:38  john
 * Added code for handling of new noat/at block
 *
 * Revision 1.1.1.1  1995/03/23  10:39:18  john
 * Entered into CVS
 *
 * Revision 1.9  1995/03/23  10:11:35  john
 * Changed to support scheduler
 *
*/

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
extern  FILE * as_file;
extern bool in_noat_block;

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
