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


/* 	$Id: labels.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: labels.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $";
#endif /* lint */

/*   
  labels.c
  create and set program labels;
  The setting of a label clears all memory of the contents of
  the registers - see regexps.c
*/

/*
$Log: labels.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/04/07  11:04:31  john
 * Changes to assembler output.
 *
 * Revision 1.1.1.1  1995/03/23  10:39:12  john
 * Entered into CVS
 *
 * Revision 1.4  1995/03/23  10:08:36  john
 * Added support for scheduler
 *
*/

#include "config.h"
#include "regexps.h"
#include "ibinasm.h"
#include "out_ba.h"
#if DO_SCHEDULE
#include "scheduler.h"
#endif
#include "inst_fmt.h"
#include "labels.h"
#include "xalloc.h"
extern  FILE * as_file;

int   last_label = 31;

int   new_label
    PROTO_Z ()
{
        last_label++;
  return last_label;
}

void set_label
    PROTO_N ( ( l ) )
    PROTO_T ( int l )
{
#if DO_SCHEDULE
  Instruction new_ins = getinst();
  Instruction_data ins_dat  = get_new_ins_data();
#endif
  char * binasm_data;
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(80,sizeof(char));
  setclass(new_ins,class_null);
  setlabel(new_ins,l);
  setsets_pc(new_ins,true);
#endif
  clear_all ();
  if (as_file){
#if !DO_SCHEDULE    
    fprintf (as_file, "$%d:\n", l);
#else
    sprintf(outline,"$%d:\n",l);
#endif
  }
  
/*  setdata(new_ins,outline);*/
  binasm_data = out_common(-l,ilabel);
#if DO_SCHEDULE
  set_instruction_text(ins_dat,outline);
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
/*
  setbase_label(new_ins,l);
  setoffset_label(new_ins,0);
  setsize_label(new_ins,0);*/
  process_instruction(new_ins);
#endif
  /*add_instruction(new_ins);*/
  return;
}

void set_label_no_clear
    PROTO_N ( ( l ) )
    PROTO_T ( int l )
{
  if (as_file)
    fprintf (as_file, "$%d:\n", l);
  out_common(-l,ilabel);
}
