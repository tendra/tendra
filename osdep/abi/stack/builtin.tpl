/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec __trans_next_caller_offset : [EXP, SHAPE, SHAPE] EXP;
Tokdec __trans_next_callee_offset : [EXP, SHAPE, SHAPE] EXP;

/*
 * Tokens for general procedures are given no definitions here since
 * they are inlined directly by the translator.
 */

Tokdef .~abi_next_caller_offset = [this_offset:EXP, this_sh:SHAPE, next_sh:SHAPE] EXP
	__trans_next_caller_offset[this_offset, this_sh, next_sh];

Tokdef .~abi_next_callee_offset = [this_offset:EXP, this_sh:SHAPE, next_sh:SHAPE] EXP
	__trans_next_callee_offset[this_offset, this_sh, next_sh];

Keep (
	.~abi_next_caller_offset, .~abi_next_callee_offset
)

