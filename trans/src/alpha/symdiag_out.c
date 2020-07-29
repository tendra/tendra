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

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/token.h>

#include <construct/exp.h>

#include <diag3/diagtypes.h>
#include <diag3/diag_fns.h>
#include <diag3/diagglob.h>
#include <diag3/mark_scope.h>
#include <diag3/diaginfo1.h>

#include <symtab/symconst.h>

#include <flpt/flpt.h>

#include <utility/int64.h>

#include "procrec.h"
#include "bits.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "locate.h"
#include "stabs_diag3.h"
#include "symdiag_out.h"
#include "pseudo.h"

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

  UNUSED(outfile);

  if(inf->key == DIAG_INFO_SOURCE){
    source = &inf->data.source.beg;
    fname = source->file->file.ints.chars;
    if(!streq(fname,currentfile)){
      /* if the file is _not_ the same as the current file */
      set_file(fname,1);
      currentfile = fname;
    }
    set_lineno(source->line_no.nat_val.small_nat,1);
    return;
  }
  if(inf->key != DIAG_INFO_ID) return;
}


