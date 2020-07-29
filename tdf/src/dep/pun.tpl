/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec .~abi_ptr_to_ptr : [ALIGNMENT, ALIGNMENT, EXP] EXP;
Tokdec .~abi_ptr_to_int : [ALIGNMENT, VARIETY, EXP] EXP;
Tokdec .~abi_int_to_ptr : [VARIETY, ALIGNMENT, EXP] EXP;
Tokdec .~abi_f_to_ptr   : [ALIGNMENT, EXP] EXP;
Tokdec .~abi_ptr_to_f   : [ALIGNMENT, EXP] EXP;

Tokdef .~ptr_to_ptr = [a1:ALIGNMENT, a2:ALIGNMENT, p:EXP] EXP
	.~abi_ptr_to_ptr[a1, a2, p];

Tokdef .~ptr_to_int = [a:ALIGNMENT, v:VARIETY, p:EXP] EXP
	.~abi_ptr_to_int[a, v, p];

Tokdef .~int_to_ptr = [v:VARIETY, a:ALIGNMENT, i:EXP] EXP
	.~abi_int_to_ptr[v, a, i];

Tokdef .~f_to_ptr = [a:ALIGNMENT, fn:EXP] EXP
	.~abi_f_to_ptr[a, fn];

Tokdef .~ptr_to_f = [a:ALIGNMENT, p:EXP] EXP
	.~abi_ptr_to_f[a, p];

Keep (
	.~ptr_to_ptr, .~ptr_to_int, .~int_to_ptr, .~f_to_ptr, .~ptr_to_f
)

