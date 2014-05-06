/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef PARAMETER_H
#define PARAMETER_H

#include <construct/installtypes.h>

#include <local/exptypes.h>

extern void output_parameters(exp);
extern bool suspected_varargs;
extern int saved_varargs_register;
extern int saved_varargs_offset;
#endif
