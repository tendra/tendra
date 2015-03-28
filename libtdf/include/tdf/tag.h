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


/*
 *
 * NOTE that an exp can occur in just one place in the tree, because of
 * the backward pointers. Except for name_tag the general structure is
 * that an exp has a son which is NULL or its first argument exp. The
 * next argument is the bro of the first, the next the bro of that etc.
 * The last argument has the last field set and its bro is the head exp
 * of the construction. In a name_tag the son contains the ident_tag which
 * declares the identity or variable being used. case, env_offset and string
 * are also special cases.
 *
 * The pt field is used in goto and test-like constructions to hold the
 * labst being jumped to. It is used in ident and name constructions
 * to hold a list of uses of a declaration.
 *
 * A name_tag or an exp with at pt to a labst MUST NOT be removed from
 * the tree without the usage count being decreased. In the case of name_tag
 * the exp must be removed from the pt-list which starts in the pt
 * of the defining ident_tag. kill_exp does these operations. It
 * also applies kill_exp recursively to all arguments.
 *
 * For constructions not involving tags or labels, install_fns.c contains
 * examples of ways of constructing exps which may be used during
 * TDF transformations. However, at the time when the functions in
 * install_fns.c are being used, tags and labels are represented by
 * indexes into arrays. During TDF transformations this is no longer so.
 * name_tag refers directly to the ident_tag of the appropriate declaration,
 * and labels are represented by labst_tag exps. The form of a labst is
 * explained below, but remember that the count of uses must be kept
 * correctly up to date. The form of ident_tag and name_tag constructions
 * are also explained below, as are the uses of some functions defined
 * in me_fns.c to help in creating them.
 *
 * The props field is zero except for those properties defined in <reader/exp.h>.
 * Operations with ntests, rounding modes or error treatments
 * have these represented in the props field. as in <reader/exp.h>.
 *
 * An exp should normally have hold_refactor applied to it after being created.
 *
 *     abs_tag: Represents integer abs construction.
 *     	son(e) is arg1.
 *     	shape is sh(arg1).
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     absbool_tag: Represents comparison and conversion to boolean.
 *     	     Only produced (by refactor.c) is HAS_SETCC is set.
 *     	son(e) is arg1.
 *     	bro(arg1) is arg2.
 *     	shape is a variety shape.
 *     	ntest is represented in props, qv.
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *     	Delivers 1 in shape if arg1 ntest arg2, 0 otherwise.
 *
 *     addptr_tag: Adds pointer and offset to produce pointer.
 *     	son(e) is arg1 (pointer).
 *     	bro(arg1) is arg2 (offset).
 *     	shape is pointer(al2(sh(arg2))).
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     alloca_tag: Represents local_alloc construction.
 *     	son(e) is arg1.
 *     	shape is pointer(x).
 *     	no(e) is 0.
 *     	props(e) is 0.
 *     	pt(e) is NULL.
 *
 *     and_tag: represents and
 *     	son(e) is a brother list of argument, all of the same shape.
 *     		At least two arguments. After check any constants will
 *     		have been combined into one, which will be the last exp
 *     		if there is a constant contribution.
 *     	shape is shape of son(e). This may be changed in some installers
 *     		by chvar_tag transformations in check - only if
 *     		HAS_BYTEOPS is set.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     apply_tag: Represents apply_proc construction.
 *     	son(e) is arg1
 *     	bro(son(e)) is arg2 in the form of a brother list of zero or
 *     		more exps.
 *     	shape is result_shape.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *     asm_tag: Represents the ~asm group of token applications
 *     	son(e) is arg.
 *     	shape is top.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *     ass_tag: Represents assign construction.
 *     	son(e) is arg1.
 *     	bro(son(e)) is arg2.
 *     	shape is top.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     assvol_tag: Represents assign_to_volatile construction.
 *     	son(e) is arg1.
 *     	bro(son(e)) is arg2.
 *     	shape is top.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     bfass_tag and bfassvol_tag: represent bitfield assignment ops.
 *     bfcont_tag and bfcontvol_tag: represent bitfield contents ops.
 *     	These tags are removed by refactor.c and should not be seen
 *     	elsewhere.
 *
 *     bitf_to_int_tag: represents bitfield to int conversion.
 *     	son(e)arg1.
 *     	shape is variety being converted to.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     case_tag: Represents case construction.
 *     	son(e) is control.
 *     	bro(son(e)) is a brother list of exps representing branches.
 *     		Each element is zero-named exp with:
 *     			pt is destination labst_tag.
 *     			no is lower limit.
 *     			if upper limit is equal to lower
 *     			  then son is NULL
 *     			  else son is exp with no the upper limit.
 *     		The elements of this list are arranged in increasing
 *     		order of lower limit.
 *     	shape is bottom if exhausive, top otherwise.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     chfl_tag: represents change floating variety
 *     	son(e) is arg1.
 *     	shape is floating shape being converted to.
 *     	no(e) is 0;
 *     	pt(e) is NULL.
 *
 *     chvar_tag: represents change variety
 *     	son(e) is arg1.
 *     	shape is variety being converted to.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     clear_tag: represents make_value
 *     	son(e) is NULL.
 *     	shape is shape of value required.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     component_tag: represents component
 *     	Always removed by refactor.c. Should not occur elsewhere.
 *
 *     compound_tag: Represents the compound construction.
 *     	son(e) is arg2 in the form of a brother list of zero
 *     		or more pairs. The first of each pair will be a val_tag
 *     		with shape some offset. Its no field will be the offset
 *     		in which to put the next item of the pair.
 *     	shape is compound(arg1).
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     concatnof_tag: represents concat nof
 *     	son(e) is arg1.
 *     	bro(arg1) is arg2
 *     		arg1 and arg2 will be nof(m, s) and nof(n, s)
 *     	shape is nof(m + n, s)
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     cond_tag: Represents conditional construction.
 *     	son(e) is first.
 *     	bro(son(e)) is alt, which will be a labst_tag
 *     	shape is LUB of first and alt.
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     cont_tag: represents contents
 *     contvol_tag: represents contents with volatile qualifier.
 *     	son(e) is arg1 (a pointer).
 *     	shape is shape of value being extracted.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *     current_env_tag: represents current env
 *     	son(e) is NULL
 *     	shape is pointer(frame alignment).
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     diagnose_tag: represents a diagnosing operation.
 *     	dno(e) is diag_info (qv.).
 *     	son(e) is controlled exp.
 *     	shape is sh(son(e))
 *     	pt(e) is NULL.
 *
 *     div0_tag:
 *     div1_tag:
 *     div2_tag: represent div0/1/2
 *     	son(e) is arg1.
 *     	bro(arg1) is arg2.
 *     	shape is sh(arg1) unless changed by chvar_tag (HAS_BYTEOPS).
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *     env_offset_tag: represents env_offset
 *     	son(e) is ident_tag referred to.
 *     	shape is offset from frame alignment.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     fabs_tag: represents floating abs
 *     	son(e) is arg1.
 *     	shape is sh(arg1).
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *     fdiv_tag: represents floating division.
 *     	son(e) is arg1.
 *     	bro(arg1) is arg2.
 *     	shape is sh(arg1).
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *     field_tag: represents selection from a compound shape.
 *     	son(e) is arg1 (value of shape compound).
 *     	shape is shape of the component required.
 *     	no(e) is the offset (in bits) from the start of the
 *     		compound to the required component.
 *     	pt(e) is NULL.
 *
 *     float_tag: represents conversion from int to float.
 *     	son(e) is arg1 (int).
 *     	shape is the floating shape required.
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *     fmax_tag:
 *     fmin_tag: represents floating maximum and minimum
 *     	son(e) is arg1.
 *     	bro(arg1) is arg2.
 *     	shape is sh(arg1.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     fminus_tag: represents floating subtraction.
 *     	son(e) is arg1.
 *     	bro(arg1) is arg2.
 *     	shape is sh(arg1).
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *     fmult_tag: represents floating multiplication
 *     	son(e) is a brother list of argument, all of the same shape.
 *     		At least two arguments. After check any constants will
 *     		have been combined into one, which will be the last exp
 *     		if there is a constant contribution.
 *     	shape is shape of son(e).
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *     fneg_tag: represents floating negation.
 *     	son(e) is arg1.
 *     	shape is sh(arg1).
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *     fplus_tag: represents floating addition.
 *     	son(e) is a brother list of argument, all of the same shape.
 *     		At least two arguments. After check any constants will
 *     		have been combined into one, which will be the last exp
 *     		if there is a constant contribution.
 *     	shape is shape of son(e).
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *     fpower_tag: represents floating power
 *     	son(e) is arg1.
 *     	bro(arg1) is arg2.
 *     	shape is shape of son(e).
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *
 *     goto_tag: Represents goto construction.
 *     	son(e) is NULL.
 *     	shape is bottom.
 *     	pt(e) is destination labst_tag.
 *
 *     	Create using me_l1, then set the pt field and increment
 *     	the usage counter in the labst_tag.
 *
 *     goto_lv_tag: Represents the goto_local_lv construction.
 *     	son(e) is local_lv value.
 *     	shape is bottom.
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     hold_tag: used as a dummy father at some times.
 *     	son(e) is exp being so held.
 *
 *     ident_tag: Represents identify and variable constructions.
 *     	For identify: son(e) is definition, bro(son(e)) is body.
 *     	For variable: son(e) is init, bro(son(e)) is body.
 *     	The shape of the result is the shape of body.
 *             The no(e) is a count of the number of uses.
 *             The pt(e) is the start of a chain of uses through name_tag's.
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *     	Create an ident_tag using me_startid, add name_tag uses of it
 *     	using me_obtain, complete the definition using me_complete_id.
 *
 *     ignorable_tag: represents ignorable construction.
 *     	son(e) is exp being controlled.
 *     	shape is sh(son(e)).
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     imag_tag: represents imaginary part.
 *     	son(e) is complex number.
 *     	shape is floating shape with same control parameters as the
 *     	 complex.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     int_to_bitf_tag: represents integer to bitfield conversion.
 *     	son(e) is arg1 (int).
 *     	shape is bitfield required.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     labst_tag: Represents exps which are destination of jumps. Produced from
 *     	alt of conditional, body of repeat and each place of labelled.
 *     	son(e) is a holder.
 *     	bro(son(e)) is the destination exp.
 *     	shape is shape of bro(son(e)).
 *     	pt(e) is NULL.
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *     	The holder (i.e. the son of the labst) can have any name_tag;
 *     	its no field is the number of uses of the labst and
 *     	its bro is the destination exp. No other field is defined.
 *
 *
 *     last_local_tag: represents last_local construction.
 *     	son(e) is NULL.
 *     	shape is top.
 *     	pt(e) is pointer(x).
 *     	no(e) is 0.
 *
 *     local_free_all_tag: represents local_free_all construction.
 *     	son(e) is NULL.
 *     	shape is top.
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     local_free_tag: Represents local_free construction.
 *     	son(e) is arg2 (pointer).
 *     	bro(son(e)) is arg1 (offset).
 *     	shape is top.
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *
 *     long_jump_tag: Represents long_jump construction.
 *     	son(e) is arg1.
 *     	bro(son(e)) is arg2.
 *     	shape is bottom.
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     make_complex_tag: represent make complex number.
 *     	son(e) is arg1.
 *     	bro(arg1) is arg2.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     make_lv_tag: represents make label value.
 *     	son(e) is NULL.
 *     	shape is lv.
 *     	pt(e) is labst.
 *     	no(e) is 0.
 *
 *     	Remember to increment labst count.
 *
 *     max_tag:
 *     min_tag: represent maximum and minimum integer ops.
 *     	son(e) is arg1.
 *     	bro(arg1) is arg2.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     minptr_tag: Represents subtract_pointers construction.
 *     	son(e) is arg1
 *     	bro(son(e)) is arg2
 *     	shape is offset(al1(arg2),al1(arg1))
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     minus_tag: represents subtraction.
 *     	This is replaced by addition of negation by refactor.c.
 *
 *     mod_tag: Represents rem1 construction.
 *     	son(e) is arg1.
 *     	bro(son(e)) is arg2
 *     	shape is sh(arg1)
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *     	no(e) is 0.
 *
 *     movecont_tag: Represents move_some construction.
 *     	son(e) is arg1.
 *     	bro(son(e)) is arg2.
 *     	bro(bro(son(e))) is arg3.
 *     	shape is top.
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *     mult_tag: represents integer multiplication.
 *     	son(e) is a brother list of argument, all of the same shape.
 *     		At least two arguments. After check any constants will
 *     		have been combined into one, which will be the last exp
 *     		if there is a constant contribution.
 *     	shape is shape of son(e).
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *     name_tag: Represents obtain_tag
 *     	son(e) is declaration (an ident_tag).
 *     	no(e) is offset in bits from the start of that declaration's
 *     		value.
 *     	pt(e) is the next name_tag on the chain of uses of an ident_tag,
 *     		which started in th pt field of the ident_tag, or
 *     		NULL if the end of the chain.
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *     	Remember to increment ident_tag count or use me_obtain from
 *     	me_fns.c to create this.
 *
 *     ncopies_tag: represents ncopies.
 *     	son(e) is value to be copied.
 *     	no(e) is n, the number of copies.
 *     	shape is nof(n, sh(son(e))).
 *     	pt(e) is NULL.
 *
 *     neg_tag: Represents negate construction
 *     	son(e) is arg1.
 *     	shape is sh(arg1).
 *     	no(e) is 0.
 *     	pt(e) is destination labst if ov_err is error_jump, otherwise
 *     		NULL.
 *
 *     nof_tag: represents the make_nof construction.
 *     	son(e) is arg1 as a brother list of zero or more exps, each of
 *     		the same shape (under eq_shape).
 *     	shape is nof(n, shape of item)
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     not_tag: Represents logical complement construction
 *     	son(e) is arg1.
 *     	shape is sh(arg1).
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     null_tag: represent ptr NULL and proc null.
 *     	son(e) is NULL.
 *     	shape is pointer(approprite alignment).
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     offset_add_tag: Represents offset_add construction.
 *     	son(e) is arg1
 *     	bro(son(e)) is arg2.
 *     	shape is offset(max(al1(arg1),al1(arg2)),al2(arg2))
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     offset_div_tag: Represents offset_div construction.
 *     	son(e) is arg1
 *     	bro(son(e)) is arg2.
 *     	shape is integer(v).
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     offset_div_by_int_tag: Represents offset_div_by_int construction.
 *     	son(e) is arg1
 *     	bro(son(e)) is arg2.
 *     	shape is offset(x,x)
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     offset_max_tag: Represents offset_max construction.
 *     	son(e) is arg1
 *     	bro(son(e)) is arg2.
 *     	shape is offset(max(al1(arg1),al1(arg2)),max(al2(arg1),al2(arg2)))
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     offset_mult_tag: Represents offset_mult construction.
 *     	son(e) is arg1
 *     	bro(son(e)) is arg2.
 *     	shape is offset(x,x)
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     offset_negate_tag: Represents offset_negate construction.
 *     	son(e) is arg1
 *     	shape is offset(x,x)
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     offset_pad_tag: represents offset pad.
 *     	son(e) is arg1 (offset).
 *     	shape is offset of required padded shape.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     offset_subtract_tag: Represents offset_subtract construction.
 *     	son(e) is arg1
 *     	bro(son(e)) is arg2.
 *     	shape is offset(al2(arg1),al2(arg2))
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     or_tag: represents or
 *     	son(e) is a brother list of argument, all of the same shape.
 *     		At least two arguments. After check any constants will
 *     		have been combined into one, which will be the last exp
 *     		if there is a constant contribution.
 *     	shape is shape of son(e).
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     plus_tag: represents the combination of plus and minus constructions.
 *     	son(e) is a brother list of argument, all of the same shape.
 *     		At least two arguments. After check any constants will
 *     		have been combined into one, which will be the last exp
 *     		if there is a constant contribution.
 *     	shape is shape of son(e).
 *     	no(e) is 0.
 *     	pt(e) is destination labst if ov_err is error_jump, otherwise
 *     		NULL.
 *
 *     power_tag: represents integer power.
 *     	son(e) is arg1.
 *     	bro(arg1) is arg2.
 *     	shape is sh(arg1).
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *     proc_tag: represents make_proc
 *     	son(e) is body of procedure, starting with declarations
 *     		(ident_tag) of parameters.
 *     	shape is proc.
 *     	no(e) is 0.
 *     	pt(e) is shape of return.
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *
 *     prof_tag: represents profile exp.
 *     	son(e) is NULL.
 *     	shape is top.
 *     	no(e) is expected number of times through this point.
 *     	pt(e) is NULL.
 *
 *     real_tag: represents a floating point constant.
 *     	son(e) is NULL.
 *     	shape is a floating shape (not complex).
 *     	no(e) is index of number in flptnos.
 *     	pt(e) is NULL.
 *
 *     realpart_tag: represents operation to take the real part of a complex.
 *     	son(e) is arg1 (complex).
 *     	shape is floating derived from same controls as complex.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     reff_tag: represents increment of a pointer by a constant offset.
 *     	son(e) is arg1 (pointer).
 *     	shape is shape of resulting pointer.
 *     	no(e) is offset in bits.
 *     	pt(e) is NULL.
 *
 *     rem0_tag:
 *     rem2_tag: Represents rem0/2 construction.
 *     	son(e) is arg1.
 *     	bro(son(e)) is arg2
 *     	shape is sh(arg1)
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *     	no(e) is 0.
 *
 *     rep_tag: represents repeat construction.
 *     	son(e) is start.
 *     	bro(son(e)) is body, which will be a labst_tag.
 *     	shape is shape of body.
 *     	pt(e) is loop record of this repeat.
 *     	no(e) is 0.
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *     res_tag: Represents the return construction.
 *     	son(e) is arg1
 *     	shape is bottom.
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     rotl_tag:
 *     rotr_tag: represent rotate left and right.
 *     	son(e) is arg1 (value to be rotated).
 *     	bro(arg1) is arg2 (no of places).
 *     	shape is sh(arg10.
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     round_tag: represents round_with_mode construction.
 *     	son(e) is arg1.
 *     	shape is integer(r).
 *     	no(e) is 0.
 *     	pt(e) is destination labst if ov_err is error_jump, otherwise
 *     		NULL.
 *
 *     seq_tag: Represents the sequence construction.
 *     	bro(son(e)) is result.
 *             son(e) is statements in the form of a zero-named exp, with its
 *     	  son as the first statement, and the remaining statements
 *     	  chained through the bro fields.
 *     	shape is the shape of result.
 *     	pt(e) is NULL.
 *     	no(e) is 0.
 *
 *     	Use new_exp_list to start and empty sequence, add_exp_list to
 *     	add an exp. When all but the result exp have been added, use
 *     	clear_exp_list on the list. Then create the sequence with
 *     	f_sequence.
 *
 *     shl_tag: Represents shift_left construction.
 *     	son(e) is arg1.
 *     	bro(son(e)) is arg2
 *     	shape is sh(arg1)
 *     	no(e) is 0.
 *     	pt(e) is labst if error_jump, NULL otherwise.
 *
 *     	Remember to increment labst count if used.
 *
 *     shr_tag: Represents shift_right construction.
 *     	son(e) is arg1.
 *     	bro(son(e)) is arg2
 *     	shape is sh(arg1)
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     solve_tag: Represents the labelled construction.
 *     	son(e) is starter.
 *     	bro(son(e)) is the start of a brother list of one or more exps,
 *     		which will be labst_tag's for each of the places.
 *     	shape is LUB of starter and each of the places.
 *     	pt(e) is loop record of this solve.
 *     	no(e) is 0;
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *     string_tag: represents constant array of integers.
 *     	son(e) is NULL.
 *     	shape is nof(n, s).
 *     	nostr(e) is pointer to array of integers.
 *     	pt(e) is NULL.
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *     subptr_tag: represents subtract offset from pointer.
 *     	No longer used.
 *
 *     testbit_tag: Introduced by check to replace test(nt ,and(x, mask), 0)
 *     		if tn is equal or not_equal.
 *     	son(e) is x.
 *     	bro(son(e)) is mask (not necessarily constant).
 *     	shape is top.
 *     	no(e) is either between 0 and 100 inclusive, in which case
 *     		the probability of continuing to the next construction
 *     		(not jumping), or no(e) is 1000 in which case the
 *     		probability of jumping is not known.
 *     	pt(e) is destination labst_tag.
 *
 *     test_tag: Represents floating_test, integer_test, local_lv_test
 *     	offset_test, pointer_test, proc_test constructions.
 *     	son(e) is arg1.
 *     	bro(son(e)) is arg2.
 *     	shape is top.
 *     	no(e) is either between 0 and 100 inclusive, in which case
 *     		the probability of continuing to the next construction
 *     		(not jumping), or no(e) is 1000 in which case the
 *     		probability of jumping is not known.
 *
 *     	pt(e) is destination labst_tag.
 *
 *     	Create using me_q1 or me_q2 which will increment the usage
 *     	counter in the labst_tag.
 *
 *     	If a test_tag is removed from the tree it must be killed using
 *     	kill_exp which will decrease the labst usage count AND kill
 *     	the arguments. If the arguments must not be killed, the labst
 *     	count must be decreased explicitly.
 *
 *     top_tag: represents "do nothing" operation.
 *     	son(e) is NULL.
 *     	shape is top
 *     	no(e) is 0.
 *     	pt(e) is NULL.
 *
 *     val_tag: represents constant integers and offsets.
 *     	son(e) is NULL.
 *     	shape is integer or offset shape.
 *     	pt(e) is NULL.
 *     	no(e)
 *     	  if shape is integer and !isbigval(e), no(e) is the number.
 *     	  if shape is integer and isbigval(e), no(e) is the index of
 *     		a representation of the integer in flptnos.
 *     	  if shape is offset, no(e) is the offset measured in bits.
 *
 *     	Properties in the props field are defined in <reader/exp.h>
 *
 *     general_proc_tag:
 *     	son = (ident for caller-formal as in proc_tag)
 *     			....
 *     	      with body = (ident for callee_formal with
 *     	      			def = formal_callee_tag)
 *     	      			....
 *     	      		   with body of proc
 *     	props = procprops
 *     	shape is proc.
 *     	pt(e) is shape of return.
 *
 *     apply_general_tag:
 *             son = proc
 *             bro(son) = exp(tag=0; props = procprops; no = number of otagexps;
 *             		son = list of otagexps ie caller actuals)
 *             	   if tag is present in otagexp, then
 *             	   		name(otagexp) = caller_tag
 *             	   		son(otagexp) = actual
 *             	   	and postlude will have ident with
 *             	   		def = caller_name_tag
 *     				and no(def) = no of corresponding caller_tag
 *     					in the otagexp list, starting from 0
 *             	   else otagexp is the actual exp
 *             bro(bro(son)) = callees =(1) make_callee_list_tag with son list of exps
 *             	        		and number = number in list
 *             	        	 (2) make_dynamic_callee_tag with son ptr
 *             	        	 	and bro(son) size
 *             	        	 (3) same_callees_tag
 *     			and props = procprops
 *             bro(bro(bro(son))) = postlude with tags identified as above
 *
 *     tail_call_tag:
 *             son = proc
 *             bro(son)= (tag=0; props = procprops; son = callees as above)
 *
 *     untidy_return:
 *     	son = result exp
 *
 *     trap_tag:
 *     	no() = error_code
 *
 */

