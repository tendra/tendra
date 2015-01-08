/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "va.tpl"

/*
 * Tokens for general procedures
 */

Tokdef ~next_caller_offset = [this_offset:EXP, this_sh:SHAPE, next_sh:SHAPE] EXP
	offset_pad(
		parameter_alignment(next_sh),
		offset_add(
			this_offset,
			shape_offset(this_sh)
		)
	);

Tokdef ~next_callee_offset = [this_offset:EXP, this_sh:SHAPE, next_sh:SHAPE] EXP
	offset_pad(
		parameter_alignment(next_sh),
		offset_add(
			this_offset,
			shape_offset(this_sh)
		)
	);

Keep (
	~next_caller_offset, ~next_callee_offset,
	~va_list, ~__va_start, ~va_arg, ~va_end
)

