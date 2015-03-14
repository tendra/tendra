/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <reader/exp.h>

#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/tags.h>
#include <construct/install_fns.h>

#include "instrs.h"
#include "special_exps.h"
#include "utility.h"

/*
 * Make an exp representing the contents of an external tag with
 * name n of shape s and variable if v.
 */
static exp
make_extn(char* n, shape s, int v)
{
	dec * g = alloc_nof(dec, 1);
	exp id = getexp(s, 0, 1, 0, 0, 0, 0, ident_tag);
	exp nme = getexp(s, 0, 1, id, 0, 0, 0, name_tag);
	setglob(id);
	if (v) {
		setvar(id);
	}
	brog(id) = g;
	g -> dec_exp = id;
	g -> dec_id = n;
	g -> extnamed = 1;
	return nme;
}

/*
 * Make an exp representing a dummy double destination used to force a
 * floating point overflow (if any) for expression with zero destination.
 */
exp
get_dummy_double_dest(void)
{
	return make_extn("___m68k_dummy_double", doublesh, 1);
}

/*
 * Make an exp representing the stack limit
 */
exp
get_stack_limit(void)
{
	return make_extn("___m68k_stack_limit", ulongsh, 1);
}

/*
 * Make an exp representing the error handler
 */
exp
get_error_handler(void)
{
	return make_extn("___m68k_errhandler", ulongsh, 1);
}

/*
 * Make an exp representing env_size
 */
exp
get_env_size(dec *decl)
{
	/* allocate space for 10 digits 2 prefix characters and a NULL */
	char* lab_name = alloc_nof(char, 13);
	sprintf(lab_name, "#%c%lu", LPREFIX,(unsigned long)decl);
	return make_extn(lab_name, ulongsh, 1);
}

