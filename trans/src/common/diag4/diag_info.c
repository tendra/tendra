/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/xalloc.h>


#include <reader/readglob.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>
#include <reader/sort.h>
#include <reader/main_reads.h>

#include <refactor/refactor.h>

#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/tags.h>

#include "dg_aux.h"
#include "mark_scope.h"
#include "dg_fns.h"
#include "diag_fns.h"


/* PROCEDURES */


exp
diag_locate(exp e)
{
	/* need contents for var locations, TDF_DIAG3 */
	exp id = son(e);
	if (isglob(id)) {
		if (brog(id)->dec_var) {
			e = f_contents(brog(id)->dec_shape, e);
		}
	} else {
		if (isvar(id)) {
			e = f_contents(sh(son(id)), e);
		}
	}
	return e;
}

