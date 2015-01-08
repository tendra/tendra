/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec c89.stdarg.va_list    : [] SHAPE;
Tokdec c89.stdarg.__va_start : [EXP] EXP;
Tokdec c89.stdarg.va_arg     : [EXP, SHAPE] EXP;
Tokdec c89.stdarg.va_end     : [EXP] EXP;

/*
 * TDF mapping tokens
 *
 * The "ABI" implementation here is provided in terms of C89's stdarg;
 * this is a little unsatisfactory, because the interface presented here
 * is for generic TDF tokens which are not specific to any particular
 * language. However, it is convenient to use the stdarg API tokens here
 * rather than re-implement these for each machine.
 */

Tokdef .~abi_va_list = [] SHAPE
	c89.stdarg.va_list;

Tokdef .~abi_va_start = [i:EXP] EXP
	c89.stdarg.__va_start[i];

Tokdef .~abi_va_arg = [l:EXP, s:SHAPE] EXP
	c89.stdarg.va_arg[l, s];

Tokdef .~abi_va_end = [l:EXP] EXP
	c89.stdarg.va_end[l];

Keep (
	.~abi_va_list, .~abi_va_start, .~abi_va_arg, .~abi_va_end
)

