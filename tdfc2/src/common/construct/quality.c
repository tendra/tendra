/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include "config.h"

#include "c_types.h"
#include "exp_ops.h"
#include "error.h"
#include "catalog.h"
#include "operator.h"
#include "quality.h"
#include "syntax.h"


/*
    This flag may be set to true to temporarily disable the checks in
    this module.
*/

int suppress_quality = 0;


/*
    This table gives the list of operations checked by check_paren.  They
    are listed in order of decreasing precedence.  Calls to check_paren
    give an entry point into this table beyond which checks are applied.
    For example, left shift operations are checked from PAREN_PLUS which
    detects 'a << b + c', 'a << b - c', 'a + b << c' and 'a - b << c'.
*/

static struct {
	unsigned tag;
	int op;
} paren_ops[] = {
	{ exp_or_tag,      lex_or_H1  },	/* PAREN_OR */
	{ exp_xor_tag,     lex_xor_H1 },	/* PAREN_XOR */
	{ exp_and_tag,     lex_and_H1 },	/* PAREN_AND */
	{ exp_compare_tag, lex_eq     },	/* PAREN_EQUALITY */
	{ exp_test_tag,    lex_eq     },	/* PAREN_RELATION */
	{ exp_plus_tag,    lex_plus   },	/* PAREN_PLUS */
	{ exp_minus_tag,   lex_minus  } 	/* PAREN_MINUS */
};


/*
    This routine finds the tag associated with the expression e for unusual
    parenthesis analysis etc.  Note that an integer constant expression may
    have been evaluated to give a simple integer constant, however the top
    level operation giving rise to this constant is held in the etag field.
*/

static unsigned
exp_tag (EXP e)
{
	unsigned tag = TAG_exp(e);
	if (tag == exp_int_lit_tag) {
		/* Allow for evaluated constants */
		tag = DEREF_unsigned(exp_int_lit_etag(e));
	}
	return tag;
}


/*
    For various pairs of operations, op1 and op2, the resolution of the
    expression 'a op1 b op2 c' to '( a op1 b ) op2 c' or 'a op1 ( b op2 c )'
    is not obvious.  This routine checks whether the expression 'a op b'
    is of this form, checking the operations starting from position n in
    the table paren_ops.
*/

void
check_paren(int n, int op, EXP a, EXP b)
{
	if (!suppress_quality) {
		int i;

		/* Check first operand */
		unsigned tag = exp_tag(a);
		for (i = n; i < array_size(paren_ops); i++) {
			if (tag == paren_ops[i].tag) {
				int op1 = paren_ops[i].op;
				if (op1 == lex_eq) {
					op1 = op_token(a, op1);
				}
				report(crt_loc, ERR_expr_paren_left(op1, op));
				break;
			}
		}

		/* Check second operand */
		tag = exp_tag(b);
		for (i = n; i < array_size(paren_ops); i++) {
			if (tag == paren_ops[i].tag) {
				int op2 = paren_ops[i].op;
				if (op2 == lex_eq) {
					op2 = op_token(b, op2);
				}
				report(crt_loc, ERR_expr_paren_right(op, op2));
				break;
			}
		}
	}
	return;
}


/*
    This routine checks for dubious relations such as 'a < b < c' which
    do not have their mathematical meaning.
*/

void
check_relation(int op, EXP a, EXP b)
{
	if (!suppress_quality) {
		/* Check first operand */
		unsigned tag = exp_tag(a);
		if (tag == exp_compare_tag) {
			int tst = op_token(a, op);
			report(crt_loc, ERR_expr_rel_paren(tst, op));
		} else if (tag == exp_test_tag) {
			int tst = op_token(a, op);
			report(crt_loc, ERR_expr_rel_paren(tst, op));
		}

		/* Check second operand */
		tag = exp_tag(b);
		if (tag == exp_compare_tag) {
			int tst = op_token(b, op);
			report(crt_loc, ERR_expr_rel_paren(op, tst));
		} else if (tag == exp_test_tag) {
			int tst = op_token(b, op);
			report(crt_loc, ERR_expr_rel_paren(op, tst));
		}
	}
	return;
}


/*
    The resolution of 'a && b || c' to '( a && b ) || c' is odd.  This
    routine checks a logical or expression to see if it is of this form.
*/

void
check_logic(EXP a, EXP b)
{
	if (!suppress_quality) {
		if (exp_tag(a) == exp_log_and_tag) {
			int op1 = lex_logical_Hand_H1;
			int op2 = lex_logical_Hor_H1;
			report(crt_loc, ERR_expr_paren_left(op1, op2));
		}
		if (exp_tag(b) == exp_log_and_tag) {
			int op1 = lex_logical_Hor_H1;
			int op2 = lex_logical_Hand_H1;
			report(crt_loc, ERR_expr_paren_right(op1, op2));
		}
	}
	return;
}
