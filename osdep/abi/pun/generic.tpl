/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec .~ptr_width : [] NAT;

/* representation preserving conversion */
Tokdef PUN = [from_sh:SHAPE, to_sh:SHAPE, val:EXP] EXP
component (to_sh,
	Cons [ shape_offset(from_sh) .max. shape_offset(to_sh) ] (
		offset_zero(alignment(from_sh)) : val
	),
	offset_zero(alignment(to_sh))
);

/* variety for converted pointers */
Tokdef PTR_V = [] VARIETY
	var_width (true, .~ptr_width);


/*
 * Common conversion routines
 */

Tokdef .~abi_ptr_to_ptr = [a1:ALIGNMENT, a2:ALIGNMENT, p:EXP] EXP
	PUN [ pointer(a1), pointer(a2), p ];

Tokdef .~abi_ptr_to_int = [a:ALIGNMENT, v:VARIETY, p:EXP] EXP
	([v] PUN [ pointer(a), integer(PTR_V), p ]);

Tokdef .~abi_int_to_ptr = [v:VARIETY, a:ALIGNMENT, i:EXP] EXP
	PUN [ integer(PTR_V), pointer(a), [PTR_V] i ];

Tokdef .~abi_f_to_ptr = [a:ALIGNMENT, fn:EXP] EXP
	PUN [ proc, pointer(a), fn ];

Tokdef .~abi_ptr_to_f = [a:ALIGNMENT, p:EXP] EXP
	PUN [ pointer(a), proc, p ];

Keep (
	.~abi_ptr_to_ptr,
	.~abi_ptr_to_int, .~abi_int_to_ptr,
	.~abi_f_to_ptr, .~abi_ptr_to_f
)

