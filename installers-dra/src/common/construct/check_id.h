/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include "exptypes.h"

extern int check_id(exp e, exp scope);
extern int used_in(exp vardec, exp piece);
extern int simple_const(exp whole, exp e, int decl, int no_ass);
extern exp hc(exp r, exp t);
