/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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
  labels.c
  create and set program labels;
  The setting of a label clears all memory of the contents of
  the registers - see regexps.c
*/

/**/

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
