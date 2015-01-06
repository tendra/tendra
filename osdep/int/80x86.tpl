/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "var64.tpl"

Tokdef .~rep_atomic_width = [] NAT 32;
Tokdef .~best_div         = [] NAT 2;
Tokdef .~little_endian    = [] BOOL true;

Keep (
	.~rep_var_width,
	.~rep_atomic_width, .~best_div, .~little_endian
)

