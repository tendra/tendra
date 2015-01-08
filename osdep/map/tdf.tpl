/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec .~abi_va_list   : [] SHAPE;
Tokdec .~abi__va_start : [EXP] EXP;
Tokdec .~abi_va_arg    : [EXP, SHAPE] EXP;
Tokdec .~abi_va_end    : [EXP] EXP;

Tokdec .~abi_next_caller_offset : [EXP, SHAPE, SHAPE] EXP;
Tokdec .~abi_next_callee_offset : [EXP, SHAPE, SHAPE] EXP;

/*
 * TDF mapping tokens
 */

/*
 * Tokens for traditional procedures
 */

Tokdef ~va_list = [] SHAPE
	.~abi_va_list;

Tokdef ~__va_start = [i:EXP] EXP
	.~abi_va_start;

Tokdef ~va_arg = [l:EXP, s:SHAPE] EXP
	.~abi_va_arg;

Tokdef ~va_end = [l:EXP] EXP
	.~abi_va_end;

/*
 * Tokens for general procedures
 */

Tokdef ~next_caller_offset = [this_offset:EXP, this_sh:SHAPE, next_sh:SHAPE] EXP
	.~abi_next_caller_offset;

Tokdef ~next_callee_offset = [this_offset:EXP, this_sh:SHAPE, next_sh:SHAPE] EXP
	.~abi_next_callee_offset;

Keep (
	~next_caller_offset, ~next_callee_offset,
	~va_list, ~__va_start, ~va_arg, ~va_end
)

