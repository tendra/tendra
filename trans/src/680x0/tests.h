/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TESTS_INCLUDED
#define TESTS_INCLUDED

#include <reader/exp.h>

#include <construct/installtypes.h>

extern bool no_side(exp);
extern bool push_arg(exp);
extern bool regable(exp);

extern bool cpd_param(shape);
extern bool is_ptr_void(shape);
extern bool issigned(shape);
extern bool varsize(shape);

#define  result_in_reg(X)	reg_result(X)

#endif
