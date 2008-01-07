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


#ifndef CONSTANT_INCLUDED
#define CONSTANT_INCLUDED


/*
 *    CONSTANT EVALUATION MACROS
 *
 *    All the calculation routines are based on lists of unsigned int's
 *    holding values in the range [0,0xffff].  The type unsigned long is
 *    guaranteed to contain at least the range [0,0xffffffff].  All
 *    calculations are performed in this double precision type to allow for
 *    overflows.  The macros LO_HALF, HI_HALF, EXTEND_VALUE and COMBINE_VALUES
 *    are used for converting to and from the extended type.
 */

#define NAT_DIGITS		16
#define NAT_MASK		((unsigned) 0xffff)

#define LO_HALF(A)		((unsigned) ((A) & NAT_MASK))
#define HI_HALF(A)		(LO_HALF ((A) >> NAT_DIGITS))

#define EXTEND_VALUE(A)	((unsigned long) (A))
#define COMBINE_VALUES(A, B)	(EXTEND_VALUE (A) +\
				  (EXTEND_VALUE (B) << NAT_DIGITS))
#define EXTENDED_MAX		COMBINE_VALUES (NAT_MASK, NAT_MASK)


/*
 *    CONSTANT EVALUATION DECLARATIONS
 *
 *    The routines in this module are concerned with constructing and
 *    performing calculations with integer constant expressions.
 */

extern void init_constant(void);
extern void init_float(FLOAT_TYPE);
extern FLOAT get_float(TYPE, int);

extern NAT make_nat_literal(NAT, unsigned, unsigned);
extern NAT make_large_nat(LIST (unsigned));
extern NAT make_nat_value(unsigned long);
extern NAT make_small_nat(int);
extern unsigned long get_nat_value(NAT);
extern NAT negate_nat(NAT);
extern NAT binary_nat_op(unsigned, NAT, NAT);
extern int compare_nat(NAT, NAT);
extern int eq_nat(NAT, NAT);


/*
 *    Return values for check_nat_range.  Note that there is code that
 *    depends on this order, so be cautious when changing it.
 */

enum {
	NAT_FIT,				/* n definitely fits into t */
	NAT_MAYFIT_SIGNED,		/* n may fit into t and t is not unsigned */
	NAT_MAYFIT_UNSIGNED,	/* n may fit into t and t is unsigned */
	NAT_NOFIT_SIGNED,		/* n definitely does not fit into t and t is not
							   unsigned */
	NAT_NOFIT_UNSIGNED,		/* n definitely does not fit into t and t is
							   unsigned */
	NAT_NEVERFIT_SIGNED,	/* n definitely does not fit into any type and t
							   is not unsigned */
	NAT_NEVERFIT_UNSIGNED	/* n definitely does not fit into any type and t
							   is unsigned */
};

extern int check_nat_range(TYPE, NAT);
extern int check_type_size(TYPE, NAT);
extern NAT max_type_value(TYPE, int);
extern void check_bounds(int, TYPE, EXP);
extern unsigned eval_const_cond(EXP);
extern unsigned no_bits(unsigned);
extern int divides_nat(EXP, EXP);
extern int is_zero_nat(NAT);
extern int is_negative_nat(NAT);
extern int is_error_nat(NAT);
extern int is_calc_nat(NAT);
extern int is_zero_exp(EXP);
extern int is_npc_exp(EXP);
extern int is_literal(EXP);


/*
 *    CONSTANT EVALUATION ROUTINES
 *
 *    These routines are concerned with the evaluation of integer constant
 *    expressions.  They are so designed that the int_lit expressions are
 *    precisely the constant-expressions from the grammar.
 */

extern EXP make_test_nat(EXP);
extern EXP make_unary_nat(unsigned, EXP);
extern EXP make_binary_nat(unsigned, EXP, EXP);
extern EXP make_compare_nat(NTEST, EXP, EXP);
extern EXP make_cond_nat(EXP, EXP, EXP);
extern EXP make_cast_nat(TYPE, EXP, ERROR *, unsigned);
extern EXP make_int_exp(TYPE, unsigned, NAT);
extern NAT make_nat_exp(EXP, ERROR *);
extern EXP calc_nat_value(NAT, TYPE);

#define SMALL_NAT_SIZE		257
#define SMALL_NAT_ALLOC		17
#define SMALL_FLT_SIZE		2

extern NAT small_neg_nat [SMALL_NAT_SIZE];
extern NAT small_nat [SMALL_NAT_SIZE];
extern string small_number [SMALL_FLT_SIZE];


#endif
