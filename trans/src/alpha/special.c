/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
   special.c
   inlines some of the simpler standard library functions
*/

#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include <local/ash.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>

#include "addrtypes.h"
#include "move.h"
#include "pseudo.h"
#include "getregs.h"
#include "guard.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "alpha_ins.h"
#include "labels.h"
#include "procrectypes.h"
#include "bitsmacs.h"
#include "reg_defs.h"
#include "special.h"


static int
specno( char *n)
{
	/* these are the procs I could do
				   something about */
  return 0;
}

needs
specialneeds(int i)
{
    /* these are the needs for their expansion */
  switch (i) {
    default: 
	error(ERR_INTERNAL, "not special fn");
  }
  UNREACHED;
}

int
specialfn(exp fn)
{
    /* could I treat this function load specially ? */
  if (fn->tag == name_tag && son(fn)->tag == ident_tag &&
      isglob (son (fn)) && son (son (fn)) == NULL) {
    char *extname = brog(son (fn)) -> name;
    return specno (extname);
  }
  return 0;
}


int
specialmake(int n, exp par, space sp, where dest, int exitlab)
{
  switch (n) {
    default: 
	error(ERR_INTERNAL, "not special");
  }
  return exitlab;
}
