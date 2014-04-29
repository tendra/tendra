/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef PRINT_H
#define PRINT_H

#ifndef CONFIG_H
#include "config.h"
#endif

#ifndef OBJECT_H
#include "object.h"
#endif

#ifndef TYPE_H
#include "type.h"
#endif

/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with printing objects to the output file.
 */
void print_set(object *, int);
void print_type(FILE *, type *, char *, int);
extern char *copyright;

#endif

