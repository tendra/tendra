/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/xalloc.h>

#include <tdf/tag.h>

#include <reader/readglob.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>
#include <reader/main_reads.h>
#include <reader/externs.h>

#include <refactor/refactor.h>

#include "dg_aux.h"
#include "mark_scope.h"
#include "dg_fns.h"
#include "diag_fns.h"

/* need contents for var locations, TDF_DIAG3 */
exp
diag_locate(exp e)
{
	exp id = son(e);

	if (isglob(id)) {
		if (nextg(id)->var) {
			e = f_contents(nextg(id)->shape, e);
		}
	} else {
		if (isvar(id)) {
			e = f_contents(sh(son(id)), e);
		}
	}

	return e;
}

