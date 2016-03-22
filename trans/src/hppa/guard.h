/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef GUARDDECS_INCLUDED
#define GUARDDECS_INCLUDED

#include "procrec.h"
#include "addr.h"

extern space guardreg(int, space);
extern space guardfreg(int, space);
extern space guard(where, space);
extern space needreg(int, space);

#endif /* GUARDDECS_INCLUDED */
