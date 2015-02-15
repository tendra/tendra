/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>

#include "config.h"

#include "c_types.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "inst_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "type_ops.h"
#include "virt_ops.h"
#include "error.h"
#include "catalog.h"
#include "buffer.h"
#include "capsule.h"
#include "char.h"
#include "debug.h"
#include "encode.h"
#include "file.h"
#include "hash.h"
#include "label.h"
#include "lex.h"
#include "mangle.h"
#include "operator.h"
#include "option.h"
#include "print.h"
#include "syntax.h"
#include "unmangle.h"
#include "ustring.h"
#ifndef NDEBUG


/*
    This flag enables the extended debug printing routines.
*/

int debugging = 0;


/*
    This routine deals with those cases in print_offset which are only
    output in debugging mode.
*/

int
print_offset_aux(OFFSET off, BUFFER *bf, int sp)
{
	if (!IS_NULL_off(off)) {
		switch (TAG_off(off)) {
		case off_type_tag: {
			TYPE t = DEREF_type(off_type_type(off));
			sp = print_type(t, bf, sp);
			break;
		}
		default: {
			sp = print_lex(lex_member_Hcap, bf, sp);
			break;
		}
		}
	}
	return sp;
}


/*
    This routine prints the unary operation 'op a' to the buffer bf.
*/

static int
print_unary(EXP a, int op, BUFFER *bf, int sp)
{
	IGNORE print_lex(op, bf, sp);
	sp = print_exp(a, 1, bf, 0);
	return sp;
}


/*
    This routine prints the binary operation 'a op b' to the buffer bf.
*/

static int
print_binary(EXP a, EXP b, int op, BUFFER *bf, int sp)
{
	sp = print_exp(a, 1, bf, sp);
	sp = print_lex(op, bf, sp);
	sp = print_exp(b, 1, bf, sp);
	return sp;
}


/*
    This routine prints the cast operation 'op < t > ( a )' to the
    buffer bf.
*/

static int
print_cast(TYPE t, EXP a, int op, BUFFER *bf, int sp)
{
	sp = print_lex(op, bf, sp);
	sp = print_lex(lex_less, bf, sp);
	sp = print_type(t, bf, sp);
	sp = print_lex(lex_greater, bf, sp);
	sp = print_exp(a, 1, bf, sp);
	return sp;
}


/*
    This routine prints the list of expressions p, enclosed in brackets,
    to the buffer bf.
*/

static int
print_exp_list(LIST(EXP)p, BUFFER *bf, int sp)
{
	sp = print_lex(lex_open_Hround, bf, sp);
	if (IS_NULL_list(p)) {
		sp = 0;
	} else {
		while (!IS_NULL_list(p)) {
			EXP a = DEREF_exp(HEAD_list(p));
			sp = print_exp(a, 1, bf, sp);
			bfputc(bf, ',');
			p = TAIL_list(p);
		}
	}
	sp = print_lex(lex_close_Hround, bf, sp);
	return sp;
}


/*
    This routine deals with those cases in print_exp which are only
    output in debugging mode.
*/

int
print_exp_aux(EXP e, int paren, BUFFER *bf, int sp)
{
	if (!IS_NULL_exp(e)) {
		assert(ORDER_exp == 88);
		if (paren) {
			sp = print_lex(lex_open_Hround, bf, sp);
		}
		switch (TAG_exp(e)) {
		case exp_paren_tag: {
			EXP a = DEREF_exp(exp_paren_arg(e));
			sp = print_exp(a, !paren, bf, sp);
			break;
		}
		case exp_copy_tag: {
			EXP a = DEREF_exp(exp_copy_arg(e));
			sp = print_exp(a, 0, bf, sp);
			break;
		}
		case exp_assign_tag: {
			EXP a = DEREF_exp(exp_assign_ref(e));
			EXP b = DEREF_exp(exp_assign_arg(e));
			sp = print_binary(a, b, lex_assign, bf, sp);
			break;
		}
		case exp_init_tag: {
			IDENTIFIER id = DEREF_id(exp_init_id(e));
			EXP a = DEREF_exp(exp_init_arg(e));
			sp = print_id_short(id, qual_none, bf, sp);
			sp = print_lex(lex_assign, bf, sp);
			sp = print_exp(a, 0, bf, sp);
			break;
		}
		case exp_preinc_tag: {
			EXP a = DEREF_exp(exp_preinc_ref(e));
			EXP b = DEREF_exp(exp_preinc_op(e));
			sp = print_binary(a, b, lex_assign, bf, sp);
			break;
		}
		case exp_postinc_tag: {
			EXP a = DEREF_exp(exp_postinc_ref(e));
			EXP b = DEREF_exp(exp_postinc_op(e));
			sp = print_binary(a, b, lex_assign, bf, sp);
			break;
		}
		case exp_indir_tag: {
			EXP a = DEREF_exp(exp_indir_ptr(e));
			sp = print_unary(a, lex_star, bf, sp);
			break;
		}
		case exp_address_tag: {
			EXP a = DEREF_exp(exp_address_arg(e));
			sp = print_unary(a, lex_and_H1, bf, sp);
			break;
		}
		case exp_address_mem_tag: {
			EXP a = DEREF_exp(exp_address_mem_arg(e));
			sp = print_unary(a, lex_and_H1, bf, sp);
			break;
		}
		case exp_func_tag: {
			EXP a = DEREF_exp(exp_func_fn(e));
			LIST(EXP)p = DEREF_list(exp_func_args(e));
			sp = print_exp(a, 1, bf, sp);
			sp = print_exp_list(p, bf, sp);
			break;
		}
		case exp_func_id_tag: {
			IDENTIFIER id = DEREF_id(exp_func_id_id(e));
			LIST(EXP)p = DEREF_list(exp_func_id_args(e));
			sp = print_id_short(id, qual_none, bf, sp);
			sp = print_exp_list(p, bf, sp);
			break;
		}
		case exp_call_tag: {
			EXP a = DEREF_exp(exp_call_ptr(e));
			EXP b = DEREF_exp(exp_call_arg(e));
			sp = print_binary(a, b, lex_dot_Hstar, bf, sp);
			break;
		}
		case exp_negate_tag:
		case exp_compl_tag:
		case exp_not_tag:
		case exp_abs_tag: {
			int op = op_token(e, lex_unknown);
			EXP a = DEREF_exp(exp_negate_etc_arg(e));
			sp = print_unary(a, op, bf, sp);
			break;
		}
		case exp_plus_tag:
		case exp_minus_tag:
		case exp_mult_tag:
		case exp_div_tag:
		case exp_rem_tag:
		case exp_and_tag:
		case exp_or_tag:
		case exp_xor_tag:
		case exp_log_and_tag:
		case exp_log_or_tag:
		case exp_lshift_tag:
		case exp_rshift_tag:
		case exp_max_tag:
		case exp_min_tag: {
			int op = op_token(e, lex_unknown);
			EXP a = DEREF_exp(exp_plus_etc_arg1(e));
			EXP b = DEREF_exp(exp_plus_etc_arg2(e));
			sp = print_binary(a, b, op, bf, sp);
			break;
		}
		case exp_test_tag: {
			int op = op_token(e, lex_unknown);
			EXP a = DEREF_exp(exp_test_arg(e));
			sp = print_exp(a, 1, bf, sp);
			IGNORE print_lex(op, bf, sp);
			bfprintf(bf, " 0");
			sp = 1;
			break;
		}
		case exp_compare_tag: {
			int op = op_token(e, lex_unknown);
			EXP a = DEREF_exp(exp_compare_arg1(e));
			EXP b = DEREF_exp(exp_compare_arg2(e));
			sp = print_binary(a, b, op, bf, sp);
			break;
		}
		case exp_cast_tag: {
			TYPE t = DEREF_type(exp_type(e));
			EXP a = DEREF_exp(exp_cast_arg(e));
			sp = print_cast(t, a, lex_cast, bf, sp);
			break;
		}
		case exp_base_cast_tag: {
			TYPE t = DEREF_type(exp_type(e));
			EXP a = DEREF_exp(exp_base_cast_arg(e));
			sp = print_cast(t, a, lex_cast, bf, sp);
			break;
		}
		case exp_dyn_cast_tag: {
			TYPE t = DEREF_type(exp_type(e));
			EXP a = DEREF_exp(exp_dyn_cast_arg(e));
			sp = print_cast(t, a, lex_dynamic_Hcast, bf, sp);
			break;
		}
		case exp_add_ptr_tag: {
			EXP a = DEREF_exp(exp_add_ptr_ptr(e));
			OFFSET off = DEREF_off(exp_add_ptr_off(e));
			sp = print_exp(a, 0, bf, sp);
			sp = print_lex(lex_plus, bf, sp);
			sp = print_offset(off, bf, sp);
			break;
		}
		case exp_offset_size_tag: {
			OFFSET off = DEREF_off(exp_offset_size_off(e));
			TYPE t = DEREF_type(exp_offset_size_step(e));
			sp = print_offset(off, bf, sp);
			sp = print_lex(lex_div, bf, sp);
			sp = print_type(t, bf, sp);
			break;
		}
		case exp_constr_tag: {
			EXP a = DEREF_exp(exp_constr_call(e));
			sp = print_exp(a, 0, bf, sp);
			break;
		}
		case exp_destr_tag: {
			EXP a = DEREF_exp(exp_destr_call(e));
			sp = print_exp(a, 0, bf, sp);
			break;
		}
		case exp_alloc_tag: {
			EXP a = DEREF_exp(exp_alloc_call(e));
			sp = print_exp(a, 0, bf, sp);
			break;
		}
		case exp_dealloc_tag: {
			EXP a = DEREF_exp(exp_dealloc_call(e));
			sp = print_exp(a, 0, bf, sp);
			break;
		}
		case exp_rtti_tag: {
			EXP a = DEREF_exp(exp_rtti_arg(e));
			int op = DEREF_int(exp_rtti_op(e));
			sp = print_lex(op, bf, sp);
			sp = print_exp(a, 1, bf, sp);
			break;
		}
		case exp_rtti_type_tag: {
			TYPE t = DEREF_type(exp_rtti_type_arg(e));
			int op = DEREF_int(exp_rtti_type_op(e));
			sp = print_lex(op, bf, sp);
			sp = print_type(t, bf, sp);
			break;
		}
		case exp_rtti_no_tag: {
			TYPE t = DEREF_type(exp_rtti_no_arg(e));
			sp = print_lex(lex_typeid, bf, sp);
			sp = print_type(t, bf, sp);
			break;
		}
		case exp_dynamic_tag: {
			EXP a = DEREF_exp(exp_dynamic_arg(e));
			sp = print_exp(a, 0, bf, sp);
			break;
		}
		case exp_aggregate_tag: {
			LIST(EXP)p = DEREF_list(exp_aggregate_args(e));
			sp = print_lex(lex_initialization, bf, sp);
			sp = print_exp_list(p, bf, sp);
			break;
		}
		case exp_initialiser_tag: {
			LIST(EXP)p = DEREF_list(exp_initialiser_args(e));
			sp = print_lex(lex_initialization, bf, sp);
			sp = print_exp_list(p, bf, sp);
			break;
		}
		case exp_nof_tag: {
			EXP a = DEREF_exp(exp_nof_start(e));
			EXP b = DEREF_exp(exp_nof_pad(e));
			EXP c = DEREF_exp(exp_nof_end(e));
			if (!IS_NULL_exp(a)) {
				sp = print_exp(a, 0, bf, sp);
				bfprintf(bf, ", ");
			}
			sp = print_exp(b, 0, bf, sp);
			bfprintf(bf, ", ...");
			if (!IS_NULL_exp(c)) {
				bfprintf(bf, ", ");
				sp = print_exp(c, 0, bf, sp);
			}
			break;
		}
		case exp_comma_tag: {
			LIST(EXP)p = DEREF_list(exp_comma_args(e));
			sp = print_exp_list(p, bf, sp);
			break;
		}
		case exp_set_tag: {
			EXP a = DEREF_exp(exp_set_arg(e));
			sp = print_exp(a, 0, bf, sp);
			break;
		}
		case exp_unused_tag: {
			EXP a = DEREF_exp(exp_unused_arg(e));
			sp = print_exp(a, 0, bf, sp);
			break;
		}
		case exp_if_stmt_tag: {
			EXP c = DEREF_exp(exp_if_stmt_cond(e));
			EXP a = DEREF_exp(exp_if_stmt_true_code(e));
			EXP b = DEREF_exp(exp_if_stmt_false_code(e));
			sp = print_exp(c, 1, bf, sp);
			sp = print_lex(lex_question, bf, sp);
			sp = print_binary(a, b, lex_colon, bf, sp);
			break;
		}
		case exp_exception_tag: {
			EXP a = DEREF_exp(exp_exception_arg(e));
			sp = print_lex(lex_throw, bf, sp);
			sp = print_exp(a, 1, bf, sp);
			break;
		}
		case exp_thrown_tag: {
			sp = print_lex(lex_catch, bf, sp);
			break;
		}
		case exp_op_tag: {
			int op = DEREF_int(exp_op_lex(e));
			EXP a = DEREF_exp(exp_op_arg1(e));
			EXP b = DEREF_exp(exp_op_arg2(e));
			if (IS_NULL_exp(b)) {
				sp = print_unary(a, op, bf, sp);
			} else {
				sp = print_binary(a, b, op, bf, sp);
			}
			break;
		}
		case exp_opn_tag: {
			int op = DEREF_int(exp_opn_lex(e));
			LIST(EXP)p = DEREF_list(exp_opn_args(e));
			sp = print_lex(op, bf, sp);
			sp = print_exp_list(p, bf, sp);
			break;
		}
		case exp_uncompiled_tag: {
			if (sp)bfputc(bf, ' ');
			bfprintf(bf, "...");
			sp = 1;
			break;
		}
		case exp_fail_tag: {
			string s = DEREF_string(exp_fail_msg(e));
			if (sp)bfputc(bf, ' ');
			bfputs(bf, s);
			sp = 1;
			break;
		}
		case exp_dummy_tag: {
			EXP a = DEREF_exp(exp_dummy_value(e));
			if (IS_NULL_exp(a)) {
				sp = print_lex(lex_exp_Hcap, bf, sp);
			} else {
				sp = print_exp(a, 0, bf, sp);
			}
			break;
		}
		default : {
			sp = print_lex(lex_exp_Hcap, bf, sp);
			break;
		}
		}
		if (paren)sp = print_lex(lex_close_Hround, bf, sp);
	}
	return sp;
}


/*
    This routine prints an indentation of indent steps followed by the
    string text to the file f.
*/

static void
print_indent(int indent, const char *text, FILE *f)
{
	while (indent > 1) {
		fputc_v('\t', f);
		indent -= 2;
	}
	if (indent) {
		unsigned long i = tab_width / 2;
		while (i) {
			fputc_v(' ', f);
			i--;
		}
	}
	fputs_v(text, f);
	return;
}


/*
    This routine prints the expression e, enclosed in parentheses if paren
    is true and preceded by a space if sp is true, to the file f.
*/

static void
print_expr(EXP e, int paren, int sp, FILE *f)
{
	BUFFER *bf = clear_buffer(&print_buff, f);
	if (paren) {
		sp = print_lex(lex_open_Hround, bf, sp);
	}
	IGNORE print_exp(e, 0, bf, sp);
	if (paren) {
		IGNORE print_lex(lex_close_Hround, bf, sp);
	}
	output_buffer(bf, 1);
	return;
}


/*
    This routine prints the integer constant n to the file f.
*/

static void
print_nat_val(NAT n, FILE *f)
{
	BUFFER *bf = clear_buffer(&print_buff, f);
	IGNORE print_nat(n, 0, bf, 0);
	output_buffer(bf, 1);
	return;
}


/*
    This routine prints the declaration id to the file f.
*/

static void
print_decl(IDENTIFIER id, FILE *f)
{
	EXP e;
	BUFFER *bf = clear_buffer(&print_buff, f);
	print_id_desc++;
	IGNORE print_id_long(id, qual_none, bf, 0);
	print_id_desc--;
	e = DEREF_exp(id_variable_init(id));
	if (!IS_NULL_exp(e)) {
		bfprintf(bf, " = ");
		IGNORE print_exp(e, 0, bf, 0);
	}
	output_buffer(bf, 1);
	return;
}


/*
    This routine prints the label lab to the file f.
*/

static void
print_label(IDENTIFIER lab, FILE *f)
{
	int op = DEREF_int(id_label_op(lab));
	if (op == lex_identifier) {
		HASHID nm = DEREF_hashid(id_name(lab));
		if (IS_hashid_name_etc(nm)) {
			string s = DEREF_string(hashid_name_etc_text(nm));
			fputs_v(strlit(s), f);
		} else {
			fputs_v("????", f);
		}
	} else if (op == lex_case) {
		NAT n = find_case_nat(lab);
		fputs_v("case ", f);
		print_nat_val(n, f);
	} else {
		fputs_v(token_names[op], f);
	}
	return;
}


/*
    This routine prints the statement e at an indentation of indent to the
    file f.  block is false to suppress braces around compound statements.
*/

static void
print_stmt(EXP e, int indent, int block, FILE *f)
{
	if (IS_NULL_exp(e)) {
		/* Empty statements */
		print_indent(indent, ";\n", f);
		return;
	}
	assert(ORDER_exp == 88);
	switch (TAG_exp(e)) {
	case exp_sequence_tag: {
		/* Compound statements */
		LIST(EXP)p = DEREF_list(exp_sequence_first(e));
		p = TAIL_list(p);
		if (block) {
			print_indent(indent, "{\n", f);
		}
		while (!IS_NULL_list(p)) {
			EXP a = DEREF_exp(HEAD_list(p));
			print_stmt(a, indent + block, 1, f);
			p = TAIL_list(p);
		}
		if (block) {
			print_indent(indent, "}\n", f);
		}
		break;
	}
	case exp_solve_stmt_tag: {
		/* Solve statements */
		EXP a = DEREF_exp(exp_solve_stmt_body(e));
		print_stmt(a, indent, block, f);
		break;
	}
	case exp_decl_stmt_tag: {
		/* Declaration statements */
		EXP a = DEREF_exp(exp_decl_stmt_body(e));
		IDENTIFIER id = DEREF_id(exp_decl_stmt_id(e));
		print_indent(indent, "", f);
		print_decl(id, f);
		fputs_v(" : {\n", f);
		print_stmt(a, indent + 1, 0, f);
		print_indent(indent, "}\n", f);
		break;
	}
	case exp_if_stmt_tag: {
		/* Conditional statements */
		EXP c = DEREF_exp(exp_if_stmt_cond(e));
		EXP a = DEREF_exp(exp_if_stmt_true_code(e));
		EXP b = DEREF_exp(exp_if_stmt_false_code(e));
		print_indent(indent, "if ", f);
		print_expr(c, 1, 0, f);
		fputs_v(" {\n", f);
		print_stmt(a, indent + 1, 0, f);
		if (!IS_NULL_exp(b)) {
			print_indent(indent, "} else {\n", f);
			print_stmt(b, indent + 1, 0, f);
		}
		print_indent(indent, "}\n", f);
		break;
	}
	case exp_while_stmt_tag: {
		/* While statements */
		EXP c = DEREF_exp(exp_while_stmt_cond(e));
		EXP a = DEREF_exp(exp_while_stmt_body(e));
		IDENTIFIER blab = DEREF_id(exp_while_stmt_break_lab(e));
		IDENTIFIER clab = DEREF_id(exp_while_stmt_cont_lab(e));
		EXP bs = DEREF_exp(id_label_stmt(blab));
		EXP cs = DEREF_exp(id_label_stmt(clab));
		print_indent(indent, "while ", f);
		print_expr(c, 1, 0, f);
		fputs_v(" {\n", f);
		print_stmt(a, indent + 1, 0, f);
		print_stmt(cs, indent + 1, 0, f);
		print_indent(indent, "}\n", f);
		print_stmt(bs, indent, 0, f);
		break;
	}
	case exp_do_stmt_tag: {
		/* Do statements */
		EXP c = DEREF_exp(exp_do_stmt_cond(e));
		EXP a = DEREF_exp(exp_do_stmt_body(e));
		IDENTIFIER blab = DEREF_id(exp_do_stmt_break_lab(e));
		IDENTIFIER clab = DEREF_id(exp_do_stmt_cont_lab(e));
		EXP bs = DEREF_exp(id_label_stmt(blab));
		EXP cs = DEREF_exp(id_label_stmt(clab));
		print_indent(indent, "do {\n", f);
		print_stmt(a, indent + 1, 0, f);
		print_stmt(cs, indent + 1, 0, f);
		print_indent(indent, "} while ", f);
		print_expr(c, 1, 0, f);
		fputs_v(" ;\n", f);
		print_stmt(bs, indent, 0, f);
		break;
	}
	case exp_switch_stmt_tag: {
		/* Switch statements */
		EXP c = DEREF_exp(exp_switch_stmt_control(e));
		EXP a = DEREF_exp(exp_switch_stmt_body(e));
		IDENTIFIER blab = DEREF_id(exp_switch_stmt_break_lab(e));
		EXP bs = DEREF_exp(id_label_stmt(blab));
		print_indent(indent, "switch ", f);
		print_expr(c, 1, 0, f);
		fputs_v(" {\n", f);
		print_stmt(a, indent + 1, 0, f);
		print_indent(indent, "}\n", f);
		print_stmt(bs, indent, 0, f);
		break;
	}
	case exp_hash_if_tag: {
		/* Target dependent conditional statements */
		EXP c = DEREF_exp(exp_hash_if_cond(e));
		EXP a = DEREF_exp(exp_hash_if_true_code(e));
		EXP b = DEREF_exp(exp_hash_if_false_code(e));
		fputs_v("#if ", f);
		print_expr(c, 0, 0, f);
		fputs_v("\n", f);
		print_stmt(a, indent, 0, f);
		if (!IS_NULL_exp(b)) {
			fputs_v("#else\n", f);
			print_stmt(b, indent, 0, f);
		}
		fputs_v("#endif\n", f);
		break;
	}
	case exp_return_stmt_tag: {
		/* Return statements */
		EXP a = DEREF_exp(exp_return_stmt_value(e));
		print_indent(indent, "return", f);
		if (!IS_NULL_exp(a))print_expr(a, 1, 1, f);
		fputs_v(" ;\n", f);
		break;
	}
	case exp_goto_stmt_tag: {
		/* Goto statements */
		IDENTIFIER lab = DEREF_id(exp_goto_stmt_label(e));
		print_indent(indent, "goto ", f);
		print_label(lab, f);
		fputs_v(" ;\n", f);
		break;
	}
	case exp_label_stmt_tag: {
		/* Labelled statements */
		EXP a = DEREF_exp(exp_label_stmt_body(e));
		IDENTIFIER lab = DEREF_id(exp_label_stmt_label(e));
		IDENTIFIER nlab = DEREF_id(exp_label_stmt_next(e));
		print_indent(indent, "", f);
		print_label(lab, f);
		fputs_v(" : {\n", f);
		print_stmt(a, indent + 1, 0, f);
		if (!IS_NULL_id(nlab)) {
			print_indent(indent + 1, "goto ", f);
			print_label(nlab, f);
			fputs_v(" ;\n", f);
		}
		print_indent(indent, "}\n", f);
		break;
	}
	case exp_try_block_tag: {
		/* Try blocks */
		EXP a = DEREF_exp(exp_try_block_body(e));
		LIST(EXP)p = DEREF_list(exp_try_block_handlers(e));
		EXP b = DEREF_exp(exp_try_block_ellipsis(e));
		print_indent(indent, "try {\n", f);
		print_stmt(a, indent + 1, 0, f);
		print_indent(indent, "}\n", f);
		while (!IS_NULL_list(p)) {
			EXP c = DEREF_exp(HEAD_list(p));
			print_stmt(c, indent + 1, 0, f);
			p = TAIL_list(p);
		}
		if (!IS_NULL_exp(b)) {
			print_indent(indent, "catch ( ... ) {\n", f);
			print_stmt(b, indent + 1, 0, f);
			print_indent(indent, "}\n", f);
		}
		break;
	}
	case exp_handler_tag: {
		/* Exception handlers */
		IDENTIFIER id = DEREF_id(exp_handler_except(e));
		EXP a = DEREF_exp(exp_handler_body(e));
		print_indent(indent, "catch ( ", f);
		if (!IS_NULL_id(id)) {
			print_decl(id, f);
		}
		fputs_v(" ) {\n", f);
		print_stmt(a, indent + 1, 0, f);
		print_indent(indent, "}\n", f);
		break;
	}
	case exp_reach_tag:
	case exp_unreach_tag: {
		/* Reached statements */
		EXP a = DEREF_exp(exp_reach_etc_body(e));
		print_stmt(a, indent, block, f);
		break;
	}
	case exp_location_tag: {
		/* Location statements */
		EXP a = DEREF_exp(exp_location_arg(e));
		print_stmt(a, indent, block, f);
		break;
	}
	default : {
		/* Expression statements */
		print_indent(indent, "", f);
		print_expr(e, 0, 0, f);
		fputs_v(" ;\n", f);
		break;
	}
	}
	return;
}


/*
    This routine prints the bitmask value n using the attribute names
    given by s.
*/

static void
print_bitmask(unsigned long n, const char **s)
{
	int sp = 0;
	FILE *f = DEBUG_file;
	if (n) {
		int i;
		unsigned long m = 1;
		for (i = 0; i < 32; i++) {
			if (n & m) {
				const char *c = s[i];
				if (c) {
					if (sp) {
						fputs_v(" | ", f);
					}
					fputs_v(c, f);
					sp = 1;
				}
			}
			m <<= 1;
		}
	}
	if (!sp) {
		fputs_v("none", f);
	}
	fputc_v('\n', f);
	fflush_v(f);
	return;
}


/*
    This routine prints the contents of the bitstream bs to the file f.
*/

static void
print_bitstream(BITSTREAM *bs, FILE *f)
{
	if (bs) {
		string s = bs->text;
		unsigned i = bs->bits;
		unsigned n = bs->bytes;
		print_bitstream(bs->prev, f);
		fprintf_v(f, "0x%p = { ",(gen_ptr)bs);
		while (n) {
			unsigned j;
			unsigned c = (unsigned)*s;
			for (j = 0; j < 8; j++) {
				fputc_v(((c & 0x80) ? '1' : '0'), f);
				c <<= 1;
			}
			fputc_v(' ', f);
			n--;
			s++;
		}
		if (i) {
			unsigned j;
			unsigned c = (unsigned)*s;
			for (j = 0; j < i; j++) {
				fputc_v(((c & 0x80) ? '1' : '0'), f);
				c <<= 1;
			}
		}
		fputs_v(" }\n", f);
	}
	return;
}


/*
    These routines are used during debugging for printing objects of various
    types.
*/

void
DEBUG_access(DECL_SPEC ds)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_access(ds, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_bits(BITSTREAM *bs)
{
	FILE *f = DEBUG_file;
	print_bitstream(bs, f);
	fflush_v(f);
	return;
}

void
DEBUG_btype(BASE_TYPE bt)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_btype(bt, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_cinfo(CLASS_INFO ci)
{
	static const char *cinfos[32] = {
		/* Keep in line with c_class.alg */
		"complete", "defined", "struct", "union", "template", "token",
		"pod", "nested", "merge", "rescan", "recursive", "incomplete",
		"base", "multiple_base", "virtual_base", "templ_base",
		"ambiguous", "empty", "private", "static", "function",
		"params", "polymorphic", "poly_base", "abstract",
		"trivial_constr", "trivial_destr", "trivial_copy",
		"trivial_assign", "const_copy", "const_assign", "usr_constr"
	};
	print_bitmask((unsigned long)ci, cinfos);
	return;
}

void
DEBUG_ctype(CLASS_TYPE ct)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_ctype(ct, qual_none, 0, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_cusage(CLASS_USAGE cu)
{
	static const char *cusages[32] = {
		/* Keep in line with c_class.alg */
		"address", "destr", "delete", "delete_array", NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL
	};
	print_bitmask((unsigned long)cu, cusages);
	return;
}

void
DEBUG_cv(CV_SPEC cv)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_cv(cv, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_dspec(DECL_SPEC ds)
{
	static const char *dspecs[32] = {
		/* Keep in step with c_class.alg */
		"used", "called", "defn", "inherit", "alias", "done", "static",
		"extern", "auto", "register", "mutable", "inline", "virtual",
		"explicit", "friend", "typedef", "public", "protected",
		"public2", "protected2", "c", "cpp", "ignore", "implicit",
		"instance", "main", "pure", "reserve", "temp", "template",
		"token", "trivial"
	};
	print_bitmask((unsigned long)ds, dspecs);
	return;
}

void
DEBUG_etype(ENUM_TYPE et)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_etype(et, 0, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_exp(EXP e)
{
	FILE *f = DEBUG_file;
	debugging++;
	print_expr(e, 0, 0, f);
	debugging--;
	fputc_v('\n', f);
	fflush_v(f);
	return;
}

void
DEBUG_flt(FLOAT f)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_flt(f, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_ftype(FLOAT_TYPE ft)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_ftype(ft, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_func(IDENTIFIER id)
{
	if (!IS_NULL_id(id)) {
		DEBUG_id_long(id);
		if (IS_id_function_etc(id)) {
			id = DEREF_id(id_function_etc_over(id));
			DEBUG_func(id);
		}
	}
	return;
}

void
DEBUG_graph(GRAPH gr)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_graph(gr, 0, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_hashid(HASHID nm)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_hashid(nm, 1, 1, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_hash_table(string s)
{
	unsigned long i = 0;
	unsigned long m = HASH_SIZE;
	if (s) {
		i = hash(s);
		m = i + 1;
		IGNORE lookup_name(s, i, 0, lex_unknown);
	}
	debugging++;
	while (i < m) {
		HASHID nm = hash_table[i];
		if (!IS_NULL_hashid(nm)) {
			BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
			bfprintf(bf, "%lu:", i);
			while (!IS_NULL_hashid(nm)) {
				IGNORE print_hashid(nm, 1, 1, bf, 1);
				nm = DEREF_hashid(hashid_next(nm));
			}
			bfputc(bf, '\n');
			output_buffer(bf, 1);
		}
		i++;
	}
	debugging--;
	return;
}

void
DEBUG_id(IDENTIFIER id)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_id_short(id, qual_none, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_id_long(IDENTIFIER id)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	print_id_desc++;
	IGNORE print_id_long(id, qual_none, bf, 0);
	print_id_desc--;
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_inst(INSTANCE inst)
{
	if (!IS_NULL_inst(inst)) {
		TYPE form = DEREF_type(inst_form(inst));
		DEBUG_type(form);
	}
	return;
}

void
DEBUG_insts(INSTANCE inst)
{
	while (!IS_NULL_inst(inst)) {
		DECL_SPEC acc = dspec_none;
		TYPE form = DEREF_type(inst_form(inst));
		if (IS_inst_templ(inst)) {
			acc = DEREF_dspec(inst_templ_access(inst));
		}
		DEBUG_dspec(acc);
		DEBUG_type(form);
		inst = DEREF_inst(inst_next(inst));
	}
	return;
}

void
DEBUG_itype(INT_TYPE it)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_itype(it, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_lex(int t)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_lex(t, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_loc(LOCATION *loc)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_loc(loc, NIL(LOCATION), bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_mangle(IDENTIFIER id)
{
	FILE *f = DEBUG_file;
	const char *s = NULL;
	if (!IS_NULL_id(id)) {
		int v = VAR_tag;
		if (IS_id_token(id)) {
			v = VAR_token;
		}
		s = strlit(mangle_name(id, v, 0));
	}
	if (s == NULL) {
		s = "(NULL)";
	}
	fprintf_v(f, "%s\n", s);
	fflush_v(f);
	return;
}

void
DEBUG_member(MEMBER mem)
{
	if (!IS_NULL_member(mem)) {
		IDENTIFIER id = DEREF_id(member_id(mem));
		IDENTIFIER alt = DEREF_id(member_alt(mem));
		DEBUG_id_long(id);
		DEBUG_id_long(alt);
	}
	return;
}

void
DEBUG_members(NAMESPACE ns)
{
	if (!IS_NULL_nspace(ns)) {
		MEMBER mem;
		FILE *f = DEBUG_file;
		if (IS_nspace_named_etc(ns)) {
			mem = DEREF_member(nspace_named_etc_first(ns));
		} else {
			mem = DEREF_member(nspace_last(ns));
		}
		DEBUG_nspace(ns);
		fputs_v("{\n", f);
		while (!IS_NULL_member(mem)) {
			IDENTIFIER id = DEREF_id(member_id(mem));
			IDENTIFIER alt = DEREF_id(member_alt(mem));
			if (!IS_NULL_id(id)) {
				fputs_v("    ", f);
				DEBUG_id_long(id);
			}
			if (!IS_NULL_id(alt) && !EQ_id(id, alt)) {
				fputs_v("    ", f);
				DEBUG_id_long(alt);
			}
			mem = DEREF_member(member_next(mem));
		}
		fputs_v("}\n", f);
	}
	return;
}

void
DEBUG_nat(NAT n)
{
	FILE *f = DEBUG_file;
	debugging++;
	print_nat_val(n, f);
	debugging--;
	fputc_v('\n', f);
	fflush_v(f);
	return;
}

void
DEBUG_nspace(NAMESPACE ns)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_nspace(ns, qual_none, 0, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_ntype(BUILTIN_TYPE nt)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_ntype(nt, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_offset(OFFSET off)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_offset(off, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_ntest(NTEST nt)
{
	int op = ntest_token(nt, lex_unknown);
	DEBUG_lex(op);
	return;
}

void
DEBUG_pptok(PPTOKEN *p)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_pptok(p, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_pptoks(PPTOKEN *p)
{
	while (p != NULL) {
		DEBUG_pptok(p);
		p = p->next;
	}
	return;
}

void
DEBUG_sort(TOKEN tok)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_sort(tok, 0, bf, 0);
	bfprintf(bf, " = ");
	IGNORE print_tok_value(tok, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_source(int lines)
{
	FILE *f = DEBUG_file;
	update_column();
	print_source(&crt_loc, lines, 1, "", f);
	fflush_v(f);
	return;
}

void
DEBUG_stmt(EXP e)
{
	FILE *f = DEBUG_file;
	debugging++;
	print_stmt(e, 0, 1, f);
	debugging--;
	fflush_v(f);
	return;
}

void
DEBUG_str(STRING s)
{
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	IGNORE print_str(s, bf, 0);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_type(TYPE t)
{
	int sp = 0;
	BUFFER *bf = clear_buffer(&print_buff, DEBUG_file);
	debugging++;
	if (!IS_NULL_type(t)) {
		CV_SPEC cv = DEREF_cv(type_qual(t));
		if (cv & cv_lvalue) {
			sp = print_lex(lex_lvalue, bf, sp);
		}
	}
	IGNORE print_type(t, bf, sp);
	debugging--;
	bfputc(bf, '\n');
	output_buffer(bf, 1);
	return;
}

void
DEBUG_unmangle(const char *s)
{
	LIST(string)p = NULL_list(string);
	CONS_string(ustrlit(s), p, p);
	unmangle_list(p, DEBUG_file, 0);
	DESTROY_list(p, SIZE_string);
	return;
}

void
DEBUG_virt(VIRTUAL vt)
{
	if (!IS_NULL_virt(vt)) {
		if (IS_virt_table(vt)) {
			unsigned n = 1;
			LIST(VIRTUAL)vs = DEREF_list(virt_table_entries(vt));
			while (!IS_NULL_list(vs)) {
				vt = DEREF_virt(HEAD_list(vs));
				fprintf_v(DEBUG_file, "%u: ", n);
				DEBUG_virt(vt);
				n++;
				vs = TAIL_list(vs);
			}
		} else {
			IDENTIFIER fn = DEREF_id(virt_func(vt));
			DEBUG_id_long(fn);
		}
	}
	return;
}

void
DEBUG_where(void)
{
	update_column();
	DEBUG_loc(&crt_loc);
	return;
}


/*
    This routine is a generic debugging routine for printing any c_class
    object.  It relies on run-time type information to determine the
    static type of p.
*/

#if c_class_IMPLEMENTATION

void
DEBUG_c_class(c_class *p, int indent)
{
	FILE *f = DEBUG_file;
	debugging++;
	if (p) {
		unsigned n = TYPEID(p);
		switch (n) {
		case TYPEID_ptr: {
			DEBUG_c_class(p->ag_ptr, indent);
			break;
		}
		case TYPEID_list:
		case TYPEID_stack: {
			print_indent(indent, "{\n", f);
			while (!IS_NULL_list(p)) {
				c_class *q = (HEAD_list(p))->ag_ptr;
				DEBUG_c_class(q, indent + 1);
				p = TAIL_list(p);
			}
			print_indent(indent, "}\n", f);
			break;
		}
		case TYPEID_exp: {
			print_stmt(p, indent, 1, f);
			break;
		}
		default : {
			print_indent(indent, "", f);
			switch (n) {
			case TYPEID_ctype:
				DEBUG_ctype(p);
				break;
			case TYPEID_err:
				report(crt_loc, p);
				break;
			case TYPEID_etype:
				DEBUG_etype(p);
				break;
			case TYPEID_flt:
				DEBUG_flt(p);
				break;
			case TYPEID_ftype:
				DEBUG_ftype(p);
				break;
			case TYPEID_graph:
				DEBUG_graph(p);
				break;
			case TYPEID_hashid:
				DEBUG_hashid(p);
				break;
			case TYPEID_id:
				DEBUG_id_long(p);
				break;
			case TYPEID_inst:
				DEBUG_inst(p);
				break;
			case TYPEID_itype:
				DEBUG_itype(p);
				break;
			case TYPEID_member:
				DEBUG_member(p);
				break;
			case TYPEID_nat:
				DEBUG_nat(p);
				break;
			case TYPEID_nspace:
				DEBUG_nspace(p);
				break;
			case TYPEID_off:
				DEBUG_offset(p);
				break;
			case TYPEID_str:
				DEBUG_str(p);
				break;
			case TYPEID_tok:
				DEBUG_sort(p);
				break;
			case TYPEID_type:
				DEBUG_type(p);
				break;
			case TYPEID_virt:
				DEBUG_virt(p);
				break;
			case TYPEID_free:
				fputs_v("FREE\n", f);
				break;
			default:
				fputs_v("UNKNOWN\n", f);
				break;
			}
			break;
		}
		}
	} else {
		print_indent(indent, "NULL\n", f);
	}
	fflush_v(f);
	debugging--;
	return;
}

void
debug(c_class *p)
{
	DEBUG_c_class(p, 0);
	return;
}

void
DEBUG(c_class *p)
{
	DEBUG_c_class(p, 0);
	return;
}

#endif /* c_class_IMPLEMENTATION */


/*
    The terminals used in the parser are listed in two places - in symbols.h
    and in syntax.sid.
*/

#define LEX_TOKEN(A, B, C)	print_terminal((A), #A, m);


/*
    This variable is used to keep count of the number of lexical tokens
    printed.
*/

static int terminal_no = 0;


/*
    This routine prints the single terminal, term, with the given return
    type.  The use argument may be set to false to indicate that the
    terminal is not used in the sid parser.
*/

static void
print_terminal(int t, char *term, int m)
{
	char c;
	FILE *f = DEBUG_file;
	unsigned long col = 0;
	unsigned long tab = tab_width;
	while (*term == ' ')term++;
	if (t != terminal_no) {
		error(ERR_WARN, "Value of '%s' wrong", term);
	}
	if (m) {
		term += strlen("lex_");
	} else {
		fprintf_v(f, "#define ");
		col = (unsigned long)strlen("#define ");
	}
	while (c = *(term++), (c != 0 && c != ' ')) {
		if (c == '_' && m) {
			c = '-';
		}
		fputc_v(c, f);
		col++;
	}
	if (m) {
		fprintf_v(f, " ;\n");
	} else {
		while (col < 5 * tab) {
			fputc_v('\t', f);
			col = tab *(col / tab + 1);
		}
		fprintf_v(f, "%d\n", terminal_no);
	}
	terminal_no++;
	return;
}


/*
    This routine prints all the terminals in a form acceptable to sid.
*/

static void
sid_terminals(int m)
{
	FILE *f = DEBUG_file;
	terminal_no = 0;
	fprintf_v ( f, "/* Automatically generated list of terminals */\n" ) ;
#include "symbols.h"
#undef LEX_TOKEN
	return;
}


/*
    This routine lists all the error names.
*/

static void
list_errors(void)
{
	FILE *f = DEBUG_file;
	ERR_DATA *p = ERR_CATALOG;
	init_option(0);
	while (p->name) {
		fprintf_v(f, "%s\n", p->name);
		p++;
	}
	return;
}


/*
    This routine lists all the option names.
*/

static void
list_options(void)
{
	FILE *f = DEBUG_file;
	OPT_DATA *p = OPT_CATALOG;
	while (p->name) {
		fprintf_v(f, "%s\n", p->name);
		p++;
	}
	return;
}


/*
    This routine prints a list of all option values in a form suitable
    as a usage list in the error catalogue.
*/

static void
define_options(void)
{
	int col = 0;
	int comma = 0;
	const char *s;
	FILE *f = DEBUG_file;
	OPT_DATA *p = OPT_CATALOG;
	fprintf_v(f, "    ");
	while (s = p->name, s != NULL) {
		char c;
		if (comma) {
			fputc_v(',', f);
			col++;
		}
		if (col > 60) {
			fprintf_v(f, "\n    ");
			comma = 0;
			col = 0;
		}
		if (comma) {
			fputc_v(' ', f);
			col++;
		}
		while (c = *(s++), c != 0) {
			if (c == '.') {
				c = '_';
			}
			fputc_v(c, f);
			col++;
		}
		comma = 1;
		p++;
	}
	fputc_v('\n', f);
	return;
}


/*
    This routine is called to handle the debug option '-d arg'.
*/

void
debug_option(char *arg)
{
	if (streq(arg, "error")) {
		list_errors();
	} else if (streq(arg, "lex")) {
		sid_terminals(0);
	} else if (streq(arg, "opt")) {
		define_options();
	} else if (streq(arg, "option")) {
		list_options();
	} else if (streq(arg, "sid")) {
		sid_terminals(1);
	} else {
		error(ERR_WARN, "Unknown option, '-d%s'", arg);
	}
	return;
}


#else /* !NDEBUG */


/*
    This routine is a dummy which is used when run-time routines are
    not enabled.
*/

#if c_class_IMPLEMENTATION

void
debug(c_class *p)
{
	error(ERR_INTERNAL, "Not compiled with debugging enabled");
	UNUSED(p);
	return;
}

#endif /* c_class_IMPLEMENTATION */


#endif /* !NDEBUG */
