/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "producer.h"
#include "c_types.h"
#include "exp_ops.h"
#include "error.h"
#include "catalog.h"
#include "operator.h"
#include "quality.h"
#include "syntax.h"


/*
 *    CHECKING CONTROL FLAG
 *
 *    This flag may be set to true to temporarily disable the checks in
 *    this module.
 */

int suppress_quality = 0;


/*
 *    TABLE OF OPERATIONS
 *
 *    This table gives the list of operations checked by check_paren.  They
 *    are listed in order of decreasing precedence.  Calls to check_paren
 *    give an entry point into this table beyond which checks are applied.
 *    For example, left shift operations are checked from PAREN_PLUS which
 *    detects 'a << b + c', 'a << b - c', 'a + b << c' and 'a - b << c'.
 */

static struct {
    unsigned tag;
    int op;
} paren_ops [] = {
    { exp_or_tag, lex_or_H1 },		/* PAREN_OR */
    { exp_xor_tag, lex_xor_H1 },		/* PAREN_XOR */
    { exp_and_tag, lex_and_H1 },		/* PAREN_AND */
    { exp_compare_tag, lex_eq },	/* PAREN_EQUALITY */
    { exp_test_tag, lex_eq },		/* PAREN_RELATION */
    { exp_plus_tag, lex_plus },		/* PAREN_PLUS */
    { exp_minus_tag, lex_minus }	/* PAREN_MINUS */
};


/*
 *    FIND AN EXPRESSION TAG
 *
 *    This routine finds the tag associated with the expression e for unusual
 *    parenthesis analysis etc.  Note that an integer constant expression may
 *    have been evaluated to give a simple integer constant, however the top
 *    level operation giving rise to this constant is held in the etag field.
 */

static unsigned
exp_tag(EXP e)
{
    unsigned tag = TAG_exp (e);
    if (tag == exp_int_lit_tag) {
		/* Allow for evaluated constants */
		tag = DEREF_unsigned (exp_int_lit_etag (e));
    }
    return (tag);
}


/*
 *    CHECK FOR DUBIOUS SHIFTS AND BIT OPERATIONS
 *
 *    For various pairs of operations, op1 and op2, the resolution of the
 *    expression 'a op1 b op2 c' to '(a op1 b) op2 c' or 'a op1 (b op2 c)'
 *    is not obvious.  This routine checks whether the expression 'a op b'
 *    is of this form, checking the operations starting from position n in
 *    the table paren_ops.
 */

void
check_paren(int n, int op, EXP a, EXP b)
{
    if (!suppress_quality) {
		int i;
		
		/* Check first operand */
		unsigned tag = exp_tag (a);
		for (i = n ; i < ARRAY_SIZE (paren_ops) ; i++) {
			if (tag == paren_ops [i].tag) {
				int op1 = paren_ops [i].op;
				if (op1 == lex_eq) op1 = op_token (a, op1);
				report (crt_loc, ERR_expr_paren_left (op1, op));
				break;
			}
		}
		
		/* Check second operand */
		tag = exp_tag (b);
		for (i = n ; i < ARRAY_SIZE (paren_ops) ; i++) {
			if (tag == paren_ops [i].tag) {
				int op2 = paren_ops [i].op;
				if (op2 == lex_eq) op2 = op_token (b, op2);
				report (crt_loc, ERR_expr_paren_right (op, op2));
				break;
			}
		}
    }
    return;
}


/*
 *    CHECK FOR DUBIOUS RELATIONS
 *
 *    This routine checks for dubious relations such as 'a < b < c' which
 *    do not have their mathematical meaning.
 */

void
check_relation(int op, EXP a, EXP b)
{
    if (!suppress_quality) {
		/* Check first operand */
		unsigned tag = exp_tag (a);
		if (tag == exp_compare_tag) {
			int tst = op_token (a, op);
			report (crt_loc, ERR_expr_rel_paren (tst, op));
		} else if (tag == exp_test_tag) {
			int tst = op_token (a, op);
			report (crt_loc, ERR_expr_rel_paren (tst, op));
		}
		
		/* Check second operand */
		tag = exp_tag (b);
		if (tag == exp_compare_tag) {
			int tst = op_token (b, op);
			report (crt_loc, ERR_expr_rel_paren (op, tst));
		} else if (tag == exp_test_tag) {
			int tst = op_token (b, op);
			report (crt_loc, ERR_expr_rel_paren (op, tst));
		}
    }
    return;
}


/*
 *    CHECK FOR DUBIOUS LOGICAL EXPRESSIONS
 *
 *    The resolution of 'a && b || c' to '(a && b) || c' is odd.  This
 *    routine checks a logical or expression to see if it is of this form.
 */

void
check_logic(EXP a, EXP b)
{
    if (!suppress_quality) {
		if (exp_tag (a) == exp_log_and_tag) {
			int op1 = lex_logical_Hand_H1;
			int op2 = lex_logical_Hor_H1;
			report (crt_loc, ERR_expr_paren_left (op1, op2));
		}
		if (exp_tag (b) == exp_log_and_tag) {
			int op1 = lex_logical_Hor_H1;
			int op2 = lex_logical_Hand_H1;
			report (crt_loc, ERR_expr_paren_right (op1, op2));
		}
    }
    return;
}
