/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec ~va_list    : [] SHAPE;
Tokdec ~__va_start : [EXP] EXP;
Tokdec ~va_arg     : [EXP, SHAPE] EXP;
Tokdec ~va_end     : [EXP] EXP;

Tokdec ~next_caller_offset : [EXP, SHAPE, SHAPE] EXP;
Tokdec ~next_callee_offset : [EXP, SHAPE, SHAPE] EXP;

Tokdec c89.stdarg.va_list    : [] SHAPE;
Tokdec c89.stdarg.__va_start : [EXP] EXP;
Tokdec c89.stdarg.va_arg     : [EXP, SHAPE] EXP;
Tokdec c89.stdarg.va_end     : [EXP] EXP;

/*
 * Tokens for traditional procedures
 */

Tokdef ~va_list = [] SHAPE
	c89.stdarg.va_list;

Tokdef ~__va_start = [i:EXP] EXP
	c89.stdarg.__va_start[i];

Tokdef ~va_arg = [l:EXP, s:SHAPE] EXP
	c89.stdarg.va_arg[l, s];

Tokdef ~va_end = [l:EXP] EXP
	c89.stdarg.va_end[l];

