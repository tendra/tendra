/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
    SHAPE CHECKING MACRO DEFINITIONS

    This file contains the definitions for the shape checking macros
    generated in check_exp.h.
*/

#define CHECK_exp_apply_token		chk_token(exp);

#define CHECK_exp_cond\
	IGNORE check1(ENC_integer, control);\
	chk_cond(exp);

#define CHECK_abs			CHECK_negate

#define CHECK_add_to_ptr\
	node *sh1 = check1(ENC_pointer, arg1);\
	node *sh2 = check1(ENC_offset, arg2);\
	al_includes(ptr_to(sh1), offset_from(sh2));\
	exp->shape = sh_pointer(offset_to(sh2));

#define CHECK_and\
	exp->shape = normalize(check2(ENC_integer, arg1, arg2));

#define CHECK_apply_proc\
	exp->shape = normalize(result_shape);\
	IGNORE check1(ENC_proc, p);\
	UNUSED(params);\
	UNUSED(var_param);

#define CHECK_apply_general_proc\
	exp->shape = normalize(result_shape);\
	IGNORE check1(ENC_proc, p);\
	UNUSED(postlude);

#define CHECK_assign\
	node *sh1 = check1(ENC_pointer, arg1);\
	al_includes(ptr_to(sh1), al_shape(arg2));\
	exp->shape = sh_top;

#define CHECK_assign_with_mode		CHECK_assign

#define CHECK_bitfield_assign\
	node *sh1 = check1(ENC_pointer, arg1);\
	node *sh2 = check1(ENC_offset, arg2);\
	node *sh3 = check1(ENC_bitfield, arg3);\
	al_includes(ptr_to(sh1), offset_from(sh2));\
	al_includes(offset_to(sh2), al_shape(sh3));\
	exp->shape = sh_top;

#define CHECK_bitfield_assign_with_mode	CHECK_bitfield_assign

#define CHECK_bitfield_contents\
	node *sh = sh_bitfield(v);\
	node *sh1 = check1(ENC_pointer, arg1);\
	node *sh2 = check1(ENC_offset, arg2);\
	al_includes(ptr_to(sh1), offset_from(sh2));\
	al_includes(offset_to(sh2), al_shape(sh));\
	exp->shape = sh;

#define CHECK_bitfield_contents_with_mo	CHECK_bitfield_contents

#define CHECK_case\
	IGNORE check1(ENC_integer, control);\
	if (exhaustive && exhaustive->cons->encoding == ENC_true) {\
	    exp->shape = sh_bottom ;\
	} else {\
	    exp->shape = sh_top ;\
	}

#define CHECK_change_bitfield_to_int\
	exp->shape = sh_integer(v);\
	IGNORE check1(ENC_bitfield, arg1);

#define CHECK_change_floating_variety\
	exp->shape = sh_floating(r);\
	IGNORE check1(ENC_floating, arg1);

#define CHECK_change_variety\
	exp->shape = sh_integer(r);\
	IGNORE check1(ENC_integer, arg1);

#define CHECK_change_int_to_bitfield\
	exp->shape = sh_bitfield(bv);\
	IGNORE check1(ENC_integer, arg1);

#define CHECK_complex_conjugate\
	exp->shape = normalize(c->shape);

#define CHECK_component\
	exp->shape = normalize(sha);\
	IGNORE check1(ENC_compound, arg1);\
	IGNORE check1(ENC_offset, arg2);

#define CHECK_concat_nof\
	exp->shape = normalize(check2(ENC_nof, arg1, arg2));

#define CHECK_conditional\
	exp->shape = normalize(lub(first->shape, alt->shape));

#define CHECK_contents\
	node *sh1 = check1(ENC_pointer, arg1);\
	al_includes(ptr_to(sh1), al_shape(s));\
	exp->shape = normalize(s);

#define CHECK_contents_with_mode	CHECK_contents

#define CHECK_current_env\
	exp->shape = sh_pointer(al_frame);

#define CHECK_div0			CHECK_and

#define CHECK_div1			CHECK_and

#define CHECK_div2			CHECK_and

#define CHECK_env_offset\
	exp->shape = sh_offset(fa, y);\
	chk_tag(exp, t, 0);

#define CHECK_env_size\
	exp->shape = sh_offset(al_frame, al_top);\
	IGNORE check1(ENC_proc, proctag);

#define CHECK_fail_installer\
	exp->shape = sh_bottom ;\
	UNUSED(message);

#define CHECK_float_int\
	exp->shape = sh_floating(f);\
	IGNORE check1(ENC_integer, arg1);

#define CHECK_floating_abs\
	exp->shape = normalize(check1(ENC_floating, arg1));

#define CHECK_floating_div\
	exp->shape = normalize(check2(ENC_floating, arg1, arg2));

#define CHECK_floating_minus		CHECK_floating_div

#define CHECK_floating_maximum		CHECK_floating_div

#define CHECK_floating_minimum		CHECK_floating_div

#define CHECK_floating_mult\
	exp->shape = normalize(checkn(ENC_floating, arg1, 1));

#define CHECK_floating_negate		CHECK_floating_abs

#define CHECK_floating_plus		CHECK_floating_mult

#define CHECK_floating_power\
	exp->shape = normalize(check1(ENC_floating, arg1));\
	IGNORE check1(ENC_integer, arg2);

#define CHECK_floating_test\
	exp->shape = sh_top ;\
	IGNORE check2(ENC_floating, arg1, arg2);

#define CHECK_goto			exp->shape = sh_bottom;

#define CHECK_goto_local_lv\
	exp->shape = sh_bottom ;\
	IGNORE check1(ENC_pointer, arg1);

#define CHECK_identify\
	exp->shape = normalize(body->shape);\
	chk_tag(exp, name_intro, 1);\
	UNUSED(definition);

#define CHECK_ignorable\
	exp->shape = normalize(arg1->shape);

#define CHECK_imaginary_part\
	exp->shape = NULL ;\
	UNUSED(arg1);

#define CHECK_initial_value\
	exp->shape = normalize(init->shape);

#define CHECK_integer_test\
	exp->shape = sh_top ;\
	IGNORE check2(ENC_integer, arg1, arg2);

#define CHECK_labelled\
	node *sh = starter->shape ;\
	node *place = places->child ;\
	while (place) {\
	    sh = lub(sh, place->shape);\
	    place = place->next ;\
	}\
	exp->shape = normalize(sh);

#define CHECK_last_local\
	exp->shape = sh_pointer(al_alloca);\
	IGNORE check1(ENC_offset, x);

#define CHECK_local_alloc\
	exp->shape = sh_pointer(al_alloca);\
	IGNORE check1(ENC_offset, arg1);

#define CHECK_local_alloc_check		CHECK_local_alloc

#define CHECK_local_free\
	exp->shape = sh_top ;\
	IGNORE check1(ENC_offset, a);\
	IGNORE check1(ENC_pointer, p);

#define CHECK_local_free_all		exp->shape = sh_top;

#define CHECK_long_jump\
	exp->shape = sh_bottom ;\
	IGNORE check1(ENC_pointer, arg1);\
	IGNORE check1(ENC_pointer, arg2);

#define CHECK_make_complex\
	exp->shape = sh_floating(c);\
	IGNORE check1(ENC_floating, arg1);\
	IGNORE check1(ENC_floating, arg2);

#define CHECK_make_compound\
	exp->shape = sh_compound(arg1);\
	IGNORE check1(ENC_offset, arg1);\
	UNUSED(arg2);

#define CHECK_make_floating\
	exp->shape = sh_floating(f);\
	UNUSED(base);\
	UNUSED(mantissa);\
	UNUSED(negative);

#define CHECK_make_general_proc\
	exp->shape = sh_proc ;\
	IGNORE check1(ENC_bottom, body);\
	UNUSED(result_shape);

#define CHECK_make_int			exp->shape = sh_integer(v);

#define CHECK_make_local_lv		exp->shape = sh_pointer(al_code);

#define CHECK_make_nof\
	long ns = arg1->cons->encoding ;\
	node *sh = checkn(ENC_shape_none, arg1, 0);\
	if (sh)exp->shape = sh_nof(make_nat(ns), sh);

#define CHECK_make_nof_int\
	node *sh = sh_integer(v);\
	exp->shape = sh_nof(string_length(str), sh);

#define CHECK_make_null_local_lv	exp->shape = sh_pointer(al_code);

#define CHECK_make_null_proc		exp->shape = sh_proc;

#define CHECK_make_null_ptr		exp->shape = sh_pointer(a);

#define CHECK_make_proc\
	exp->shape = sh_proc ;\
	IGNORE check1(ENC_bottom, body);\
	UNUSED(result_shape);

#define CHECK_make_stack_limit\
	exp->shape = NULL ;\
	UNUSED(stack_base);\
	UNUSED(frame_size);\
	UNUSED(alloc_size);

#define CHECK_make_top			exp->shape = sh_top;

#define CHECK_make_value		exp->shape = normalize(s);

#define CHECK_maximum			CHECK_and

#define CHECK_minimum			CHECK_and

#define CHECK_minus			CHECK_and

#define CHECK_move_some\
	node *sh1 = check1(ENC_pointer, arg1);\
	node *sh2 = check1(ENC_pointer, arg2);\
	node *sh3 = check1(ENC_offset, arg3);\
	al_includes(ptr_to(sh1), offset_from(sh3));\
	al_includes(ptr_to(sh2), offset_to(sh3));\
	exp->shape = sh_top;

#define CHECK_mult			CHECK_and

#define CHECK_n_copies\
	exp->shape = sh_nof(n, arg1->shape);

#define CHECK_negate\
	exp->shape = normalize(check1(ENC_integer, arg1));

#define CHECK_not			CHECK_negate

#define CHECK_obtain_tag		chk_tag(exp, t, 0);

#define CHECK_offset_add\
	node *sh1 = check1(ENC_offset, arg1);\
	node *sh2 = check1(ENC_offset, arg2);\
	al_includes(offset_to(sh1), offset_from(sh2));\
	exp->shape = sh_offset(offset_from(sh1), offset_to(sh2));

#define CHECK_offset_div\
	node *sh = check2(ENC_offset, arg1, arg2);\
	al_equals(offset_from(sh), offset_to(sh));\
	exp->shape = sh_integer(v);

#define CHECK_offset_div_by_int\
	node *sh1 = check1(ENC_offset, arg1);\
	al_equals(offset_from(sh1), offset_to(sh1));\
	IGNORE check1(ENC_integer, arg2);\
	exp->shape = normalize(sh1);

#define CHECK_offset_max\
	node *sh1 = check1(ENC_offset, arg1);\
	node *sh2 = check1(ENC_offset, arg2);\
	node *al1 = al_union(offset_from(sh1), offset_from(sh2));\
	node *al2 = offset_to(sh1);\
	al_equals(al2, offset_to(sh2));\
	exp->shape = sh_offset(al1, al2);

#define CHECK_offset_mult\
	node *sh1 = check1(ENC_offset, arg1);\
	al_equals(offset_from(sh1), offset_to(sh1));\
	IGNORE check1(ENC_integer, arg2);\
	exp->shape = normalize(sh1);

#define CHECK_offset_negate\
	node *sh1 = check1(ENC_offset, arg1);\
	al_equals(offset_from(sh1), offset_to(sh1));\
	exp->shape = normalize(sh1);

#define CHECK_offset_pad\
	node *sh1 = check1(ENC_offset, arg1);\
	node *al1 = al_union(offset_from(sh1), a);\
	exp->shape = sh_offset(al1, offset_to(sh1));

#define CHECK_offset_subtract\
	node *sh1 = check1(ENC_offset, arg1);\
	node *sh2 = check1(ENC_offset, arg2);\
	al_equals(offset_from(sh1), offset_from(sh2));\
	exp->shape = sh_offset(offset_to(sh1), offset_to(sh2));

#define CHECK_offset_test\
	exp->shape = sh_top ;\
	IGNORE check2(ENC_offset, arg1, arg2);

#define CHECK_offset_zero		exp->shape = sh_offset(a, a);

#define CHECK_or			CHECK_and

#define CHECK_plus			CHECK_and

#define CHECK_pointer_test\
	exp->shape = sh_top ;\
	IGNORE check2(ENC_pointer, arg1, arg2);

#define CHECK_power			CHECK_shift_left

#define CHECK_proc_test\
	exp->shape = sh_top ;\
	IGNORE check2(ENC_proc, arg1, arg2);

#define CHECK_profile\
	exp->shape = sh_top ;\
	UNUSED(uses);

#define CHECK_real_part\
	exp->shape = NULL ;\
	UNUSED(arg1);

#define CHECK_rem0			CHECK_and

#define CHECK_rem1			CHECK_and

#define CHECK_rem2			CHECK_and

#define CHECK_repeat\
	exp->shape = normalize(body->shape);\
	IGNORE check1(ENC_top, start);

#define CHECK_return\
	exp->shape = sh_bottom ;\
	UNUSED(arg1);

#define CHECK_return_to_label\
	exp->shape = sh_bottom ;\
	UNUSED(lab_val);

#define CHECK_round_with_mode\
	exp->shape = sh_integer(r);\
	IGNORE check1(ENC_floating, arg1);

#define CHECK_rotate_left		CHECK_shift_left

#define CHECK_rotate_right		CHECK_shift_left

#define CHECK_sequence\
	exp->shape = normalize(result->shape);\
	UNUSED(statements);

#define CHECK_set_stack_limit\
	exp->shape = sh_top ;\
	UNUSED(lim);

#define CHECK_shape_offset\
	exp->shape = sh_offset(al_shape(s), al_top);

#define CHECK_shift_left\
	exp->shape = normalize(check1(ENC_integer, arg1));\
	IGNORE check1(ENC_integer, arg2);

#define CHECK_shift_right		CHECK_shift_left

#define CHECK_subtract_ptrs\
	node *sh1 = check1(ENC_pointer, arg1);\
	node *sh2 = check1(ENC_pointer, arg2);\
	exp->shape = sh_offset(ptr_to(sh2), ptr_to(sh1));

#define CHECK_tail_call\
	exp->shape = sh_bottom ;\
	IGNORE check1(ENC_proc, p);

#define CHECK_untidy_return\
	exp->shape = sh_bottom ;\
	UNUSED(arg1);

#define CHECK_variable\
	exp->shape = normalize(body->shape);\
	chk_tag(exp, name_intro, 1);\
	UNUSED(init);

#define CHECK_xor			CHECK_and
