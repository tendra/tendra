/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TDF_TAG_H
#define TDF_TAG_H

enum {
	ident_tag               = 1,

	seq_tag                 = 3,
	cond_tag                = 4,
	labst_tag               = 5,
	rep_tag                 = 6,
	goto_tag                = 7,
	test_tag                = 8,
	ass_tag                 = 9,
	apply_tag               = 11,
	res_tag                 = 12,
	goto_lv_tag             = 13,
	return_to_label_tag     = 14,

	solve_tag               = 15,
	assvol_tag              = 16,
	compound_tag            = 17,
	nof_tag                 = 18,
	local_free_all_tag      = 19,
	local_free_tag          = 20,
	last_local_tag          = 21,
	long_jump_tag           = 22,
	concatnof_tag           = 23,
	ncopies_tag             = 24,
	case_tag                = 25,
	movecont_tag            = 26,
	testbit_tag             = 27,
	alloca_tag              = 28,

#ifndef TDF_DIAG4
	diagnose_tag            = 29,
#endif

	prof_tag                = 30,
	ignorable_tag           = 31,
	bfass_tag               = 32,
	bfassvol_tag            = 33,
	condassign_tag          = 34,
	apply_general_tag       = 35,
	tail_call_tag           = 36,
	untidy_return_tag       = 37,
	same_callees_tag        = 38,

	plus_tag                = 39,
	neg_tag                 = 40,
	shl_tag                 = 41,
	mod_tag                 = 43,
	rem2_tag                = 44,
	abs_tag                 = 45,
	round_tag               = 46,
	offset_pad_tag          = 47,
	offset_div_tag          = 48,
	offset_max_tag          = 49,
	minptr_tag              = 50,
	fpower_tag              = 51,
	fplus_tag               = 52,
	fminus_tag              = 53,
	fmult_tag               = 54,
	fdiv_tag                = 55,
	fabs_tag                = 56,
	fneg_tag                = 57,
	float_tag               = 58,
	chfl_tag                = 59,
	and_tag                 = 60,
	or_tag                  = 61,
	xor_tag                 = 62,
	not_tag                 = 63,
	component_tag           = 64,
	max_tag                 = 65,
	min_tag                 = 66,
	bitf_to_int_tag         = 67,
	bfcont_tag              = 68,
	fmax_tag                = 69,
	shr_tag                 = 70,
	fmin_tag                = 71,
	div0_tag                = 72,
	bfcontvol_tag           = 73,
	absbool_tag             = 74,
	addptr_tag              = 75,
	chvar_tag               = 76,
	minus_tag               = 77,
	mult_tag                = 78,
	subptr_tag              = 79,
	realpart_tag            = 80,
	div1_tag                = 81,
	div2_tag                = 82,
	offset_add_tag          = 83,
	offset_div_by_int_tag   = 84,
	offset_mult_tag         = 85,
	offset_negate_tag       = 86,
	offset_subtract_tag     = 87,
	rem0_tag                = 88,
	rotl_tag                = 89,
	rotr_tag                = 90,
	power_tag               = 91,
	imag_tag                = 92,
	make_complex_tag        = 93,
	int_to_bitf_tag         = 94,
	conj_tag                = 95,

	hold_tag                = 101,
	hold2_tag               = 102, /* 102 also used as hold */
	initial_value_tag       = 103, /* removed in common part */

	cont_tag                = 113,
	field_tag               = 114,
	val_tag                 = 115,
	reff_tag                = 116,
	name_tag                = 117,
	proc_tag                = 118,
	top_tag                 = 119,
	contvol_tag             = 120,
	current_env_tag         = 121,
	env_offset_tag          = 122,
	make_lv_tag             = 123,
	clear_tag               = 124,
	null_tag                = 125,
	real_tag                = 126,
	string_tag              = 127,
	general_proc_tag        = 128,
	env_size_tag            = 129,
	give_stack_limit_tag    = 130,
	make_stack_limit_tag    = 131,
	general_env_offset_tag  = 132,

	caller_tag              = 200,
	caller_name_tag         = 201,
	make_dynamic_callee_tag = 204,
	make_callee_list_tag    = 205,
	set_stack_limit_tag     = 206,
	formal_callee_tag       = 207,
	trap_tag                = 208,
	asm_tag                 = 209
};

#define is_o(t)	((t) >= cont_tag && (t) <= make_stack_limit_tag)
#define is_a(t)	((t) >= plus_tag && (t) <= make_stack_limit_tag)

#endif

