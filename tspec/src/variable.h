/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef VARIABLE_H
#define VARIABLE_H

#ifndef OBJECT_H
#include "object.h"
#endif

/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with setting various system variables.
 */
void set_string(char *, char *);
void set_integer(char *, int);

extern object *crt_object;

#endif

