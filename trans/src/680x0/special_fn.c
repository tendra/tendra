/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/check.h>
#include <shared/error.h>

#include <reader/exptypes.h>
#include <reader/expmacs.h>
#include <reader/exptypes.h>

#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/installglob.h>
#include <construct/installtypes.h>
#include <construct/special_fn.h>

#include <main/flags.h>

#include "utility.h"


/*
    LOOK FOR SPECIAL FUNCTIONS

    An expression is examined to see if it is a recognised special
    function.  The functions recognised are : strcpy of a constant
    string (which is turned into a move instruction), and alloca
    (which is inlined).
*/

bool
special_fn(exp a1, exp a2, shape s, exp *e)
{
    dec *d = brog(son(a1));
    char *id = d->dec_u.dec_val.dec_id;

    if (id == NULL) return 0;

    if (eq(id, "_setjmp"))has_setjmp = 1;
    if (eq(id, "_longjmp"))has_setjmp = 1;

    if (!do_alloca) return 0;

    if ((/* eq(id, "_alloca") || */ eq(id, "___builtin_alloca")) &&
	 a2 != NULL && last(a2)) {
	exp r = getexp(s, NULL, 0, a2, NULL, 0, 0L, alloca_tag);
	setfather(r, son(r));
	has_alloca = 1;
	*e = r;
	kill_exp(a1, a1);
	return 1;
    }

    return 0;
}

