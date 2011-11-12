/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  symdiags.c

  Functions for the inclusion of diagnostic information in 
  symbolic assembler files.  Only file and line number information 
  is available.
*/

#include <shared/xalloc.h>

#include "config.h"

#include "codetypes.h"
#include "exptypes.h"
#include "shapemacs.h"
#include "expmacs.h"
#include "exp.h"
#include "procrectypes.h"
#include "procrecs.h"
#include "tags.h"
#include "bitsmacs.h"
#include "diagtypes.h"
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
void
output_symbolic_diagnostic(FILE *outfile, diag_info *inf)
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


