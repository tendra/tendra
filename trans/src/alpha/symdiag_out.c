/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  Functions for the inclusion of diagnostic information in 
  symbolic assembler files.  Only file and line number information 
  is available.
*/

#include <stdio.h>
#include <string.h>

#include <shared/xalloc.h>

#include <local/exptypes.h>
#include <local/expmacs.h>

#include "cross_config.h"

#include <reader/codetypes.h>

#include <construct/shapemacs.h>
#include <construct/exp.h>
#include <construct/tags.h>

#include <diag/diagtypes.h>
#include <diag/diag_fns.h>
#include <diag/diagglob.h>
#include <diag/mark_scope.h>

#include "procrectypes.h"
#include "procrecs.h"
#include "bitsmacs.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "syms.h"
#include "locate.h"
#include "symbol.h"
#include "diag_out.h"
#include "symdiag_out.h"
#include "pseudo.h"

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


