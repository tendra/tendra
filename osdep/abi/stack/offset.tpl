/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdef .~abi_next_caller_offset = [this_offset:EXP, this_sh:SHAPE, next_sh:SHAPE] EXP
	offset_pad(
		parameter_alignment(next_sh),
		offset_add(
			this_offset,
			shape_offset(this_sh)
		)
	);

Tokdef .~abi_next_callee_offset = [this_offset:EXP, this_sh:SHAPE, next_sh:SHAPE] EXP
	offset_pad(
		parameter_alignment(next_sh),
		offset_add(
			this_offset,
			shape_offset(this_sh)
		)
	);

Keep (
	.~abi_next_caller_offset, .~abi_next_callee_offset
)

