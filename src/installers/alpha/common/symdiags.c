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


/* 	$Id: symdiags.c,v 1.2 1998/02/04 10:43:33 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: symdiags.c,v 1.2 1998/02/04 10:43:33 release Exp $";
#endif /* lint */
/*
  symdiags.c

  Functions for the inclusion of diagnostic information in 
  symbolic assembler files.  Only file and line number information 
  is available.
*/
#include "config.h"
#include "common_types.h"
#include "exptypes.h"
#include "shapemacs.h"
#include "expmacs.h"
#include "exp.h"
#include "procrectypes.h"
#include "procrecs.h"
#include "tags.h"
#include "bitsmacs.h"
#include "diagtypes.h"
#include "xalloc.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "syms.h"
#include "diag_fns.h"
#include "locate.h"
#include "symbol.h"
#include "alphadiags.h"
#include "diagglob.h"
#include "mark_scope.h"
#include "symdiags.h"
#include "pseudo.h"
#include "cross_config.h"

#ifndef CROSS_INCLUDE
#include <symconst.h>
#else
#include CROSS_INCLUDE/symconst.h>
#endif


static char *currentfile="";	/* The current source file (.c) */


/*
  This function outputs a line number and, if necessary, a
  file identifying the place in the original source to look
  when debugging.
*/
void output_symbolic_diagnostic
    PROTO_N ( ( outfile,inf ) )
    PROTO_T ( FILE *outfile X diag_info *inf )
{
  sourcemark *source;
  char * fname;
  if(inf->key == DIAG_INFO_SOURCE){
    source = &inf->data.source.beg;
    fname = source->file->file.ints.chars;
    if(strcmp(fname,currentfile)){
      /* if the file is _not_ the same as the current file */
      set_file(fname,1);
      currentfile = fname;
    }
    set_lineno(source->line_no.nat_val.small_nat,1);
    return;
  }
  if(inf->key != DIAG_INFO_ID) return;
  return;	
}


