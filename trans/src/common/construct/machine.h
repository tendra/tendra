/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONSTRUCT_MACHINE_H
#define CONSTRUCT_MACHINE_H

#include <shared/bool.h>

#include <construct/installtypes.h>

/*
 * LOCAL AND GLOBAL NAME PREFIXES
 */
extern char *local_prefix;
extern char *name_prefix;

/*
 * DOES A PROCEDURE RETURN THE GIVEN SHAPE IN A REGISTER?
 */
bool reg_result(shape sha);

#endif

