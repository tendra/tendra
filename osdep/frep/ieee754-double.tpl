/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdef .~frep_float_rep      = [] NAT 1;
Tokdef .~frep_double_rep     = [] NAT 2;
Tokdef .~frep_longdouble_rep = [] NAT 2;

Keep (
	.~frep_float_rep, .~frep_double_rep, .~frep_longdouble_rep
)

