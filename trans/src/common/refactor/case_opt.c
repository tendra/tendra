/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Optimisation of case_tag's
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/xalloc.h>

#include <local/szs_als.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>

#include <construct/installglob.h>
#include <construct/exp.h>
#include <construct/me_fns.h>
#include <construct/install_fns.h>

#include <main/flags.h>

#include <refactor/optimise.h>
#include <refactor/const.h>
#include <refactor/refactor.h>

static int density(exp *, int, int, int);
static exp exhaustive_conditional_maker(int, int, exp);
static exp inexhaustive_conditional_maker(int, int, exp, exp);
static exp set_up_sequence(exp, exp, ntest, int, exp, int);
static exp set_up_assign(exp, int);
static exp set_up_unsigned_test(exp, exp, int, ntest);
static exp like_me_q1(int, ntest, exp, exp, exp, unsigned char);

static int  no_of_nodes;
static exp *node_start;
static exp *node_end;
static double *node_weight;
static unsigned char *node_start_flag;
static unsigned char *node_end_flag;

/*
 * jump_table density is the percentage of entries which must be filled
 * in a jump table in order for it to be created
 * So 0 would try to make everything into a jump table whereas 100
 * would mean only full jump tables could be put out
 */
static unsigned jump_table_density  =  60;
static unsigned min_jump_table_size =  10;
static unsigned max_jump_table_size = 100;
static unsigned min_no_of_default_destinations = 3;

/*
 * case_optimisation takes a case_tag and an ident_tag and
 * splits up the case_tag into parts which it thinks should
 * be done as jump tables.
 */
exp
case_optimisation(exp body, exp id, shape shape_of_case, exp control_expression)
{
	exp t;
	exp *ELEMENTS;
	int i;
	int n;
	int no_of_cases = 1;
	int jump_table_present = 0;

	no_of_nodes = 0;
	/* Calculate the number of cases in the case_tag */
	for (t = body; !t->last; t = bro(t)) {
		no_of_cases = no_of_cases + 1;
	}

	ELEMENTS = (exp *)xcalloc(no_of_cases, sizeof(exp));
	node_start = (exp *)xcalloc(no_of_cases, sizeof(exp));
	node_end = (exp *)xcalloc(no_of_cases, sizeof(exp));
	node_weight = (double *)xcalloc(no_of_cases, sizeof(double));

	/*
	 * Set up the values of these arrays
	 */

	/* First set up the ELEMENTS array */
	t = body;
	for (i = 0; i < no_of_cases; i++) {
		ELEMENTS[i] = t;
		t = bro(t);
	}

	/*
	 * Calculation of where should do jump tables
	 * This sets up the arrays node_weight, node_start and node_end
	 */
	for (n = 0; n < no_of_cases; n = i + 1) {
		int z;
		double node_weight_sum = 0.0;

		i = no_of_cases - 1;
		while (density(ELEMENTS, n, i, is_signed(sh(control_expression)))
		       < jump_table_density) {
			i--;
		}

		for (z = n; z <= i; z++) {
			if (son(ELEMENTS[z]) != NULL) {
				if (is_signed(sh(control_expression))) {
					node_weight_sum +=
					    ((double)no(son(ELEMENTS[z])) -
					     (double)no(ELEMENTS[z]));
				} else {
					node_weight_sum +=
					    ((double)(unsigned long)no(son(ELEMENTS[z]))
					     - (double)(unsigned long)no(ELEMENTS[z]));
				}
			}

			node_weight_sum += 1.0;
		}

		if (node_weight_sum < (double)min_jump_table_size) {
			i = n;
		}

		if (node_weight_sum > (double)max_jump_table_size) {
			i = n;
		}

		if ((i - n) < min_no_of_default_destinations) {
			i = n;
		}

		/*
		 * Lump together into a jump_table or a single
		 * Sets up the node_start pointers
		 */
		node_start[no_of_nodes] = ELEMENTS[n];

		/* Sets up the node_end pointers */
		node_end[no_of_nodes] = (son(ELEMENTS[i]) == NULL
		                         ? ELEMENTS[i] : son(ELEMENTS[i]));

		/* sets up the node_weight of the node */
		node_weight[no_of_nodes] = 0.0;
		for (z = n; z <= i; z++) {
			if (son(ELEMENTS[z]) != NULL) {
				if (is_signed(sh(control_expression))) {
					node_weight[no_of_nodes] +=
					    ((double)no(son(ELEMENTS[z])) -
					     (double)no(ELEMENTS[z]));
				} else {
					node_weight[no_of_nodes] +=
					    ((double)(unsigned long)no(son(ELEMENTS[z])) -
					     (double)(unsigned long)no(ELEMENTS[z]));
				}
			}
			node_weight[no_of_nodes] += 1.0;
		}

		if (n != i) {
			jump_table_present = 1;
		}

		no_of_nodes = no_of_nodes + 1;

		/* Chops up the list for later use */
		bro(ELEMENTS[i]) = NULL;

		/*
		 * Sets the last of ELEMENTS[i] so can be substituted directly into
		 * new case_tag's
		 */
		ELEMENTS[i]->last = true;
	}

	if (has & HAS_BYTEOPS) {
		if (!jump_table_present) {
			kill_exp(son(id), son(id));
			son(id) = control_expression;
			sh(id) = sh(control_expression);

			t = body;
			for (;;) {
				sh(t) = sh(control_expression);
				if (son(t) != NULL) {
					sh(son(t)) = sh(control_expression);
				}

				if (t->last) {
					break;
				}
			}
		} else {
			kill_exp(control_expression, control_expression);
		}
	} else {
		kill_exp(control_expression, control_expression);
		UNUSED(jump_table_present);
	}

	assert(no_of_nodes > 0);

	/* Set up the node_start_flag and node_end_flag arrays */
	node_start_flag = xcalloc(no_of_nodes, sizeof (unsigned char));
	node_end_flag   = xcalloc(no_of_nodes, sizeof (unsigned char));

	for (i = 0; i < no_of_nodes; i++) {
		node_start_flag[i] = node_end_flag[i] = 0;
	}

	if (shape_of_case == f_bottom) {
		t = exhaustive_conditional_maker(0, no_of_nodes - 1, id);
	}

	if (shape_of_case == f_top) {
		exp COND__TAG;
		exp LABST__TAG;
		exp TOP__TAG;
		exp CLEAR__TAG;

		TOP__TAG = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, top_tag);
		CLEAR__TAG = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, clear_tag);
		LABST__TAG = me_b3(sh(TOP__TAG), CLEAR__TAG, TOP__TAG, labst_tag);
		t = inexhaustive_conditional_maker(0, no_of_nodes - 1, id, LABST__TAG);
		COND__TAG = me_b3(f_top, t, LABST__TAG, cond_tag);
		t = COND__TAG;
	}

	xfree(ELEMENTS);
	xfree(node_start);
	xfree(node_end);
	xfree(node_weight);
	xfree(node_start_flag);
	xfree(node_end_flag);

	return t;
}

/*
 * density is used for calculating whether the elements of the
 * case_tag should be made into jump tables.
 */
static int
density(exp *ELEMENTS, int start, int end, int sgn)
{
	double numerator, denominator;
	int index;

	if (son(ELEMENTS[end]) == NULL) {
		if (sgn) {
			denominator = (double) no(ELEMENTS[end]) -
			              (double) no(ELEMENTS[start]);
		} else {
			denominator = (double) (unsigned long) no(ELEMENTS[end]) -
			              (double) (unsigned long) no(ELEMENTS[start]);
		}
	} else {
		if (sgn) {
			denominator = (double) no(son(ELEMENTS[end])) -
			              (double) no(ELEMENTS[start]);
		} else {
			denominator =
			    (double) (unsigned long) no(son(ELEMENTS[end])) -
			    (double) (unsigned long) no(ELEMENTS[start]);
		}
	}

	denominator = denominator + 1.0;
	numerator = 0.0;

	for (index = start; index <= end; index++) {
		if (son(ELEMENTS[index]) == NULL) {
			numerator = numerator + 1.0;
		} else {
			if (sgn) {
				numerator = numerator +
				            ((double)no(son(ELEMENTS[index])) -
				             (double)no(ELEMENTS[index])) + 1.0;
			} else {
				numerator = numerator +
				            ((double)(unsigned long)no(son(ELEMENTS[index])) -
				             (double)(unsigned long)no(ELEMENTS[index])) + 1.0;
			}
		}
	}

	return (int) (100.0 * (numerator / denominator));
}

/*
 * set_up_sequence creates a simple sequence with a test_tag.
 */
static exp
set_up_sequence(exp left, exp right, ntest test, int integer_value, exp id,
                int probability)
{
	exp SEQ__TAG;
	exp ZERO__TAG;
	exp TEST__TAG;
	exp NAME__TAG;
	exp VAL__TAG;
	exp CONT__TAG;

	/* sets up the test_tag */
	NAME__TAG = me_obtain(id);
	CONT__TAG = me_u3(sh(id), NAME__TAG, cont_tag);
	VAL__TAG  = me_shint(sh(CONT__TAG), integer_value);
	TEST__TAG = like_me_q1(probability, test, right, CONT__TAG, VAL__TAG, test_tag);

	/* sets up the seq_tag for the conditional */
	ZERO__TAG = me_u3(f_top, TEST__TAG, 0);
	SEQ__TAG  = me_b3(sh(left), ZERO__TAG, left, seq_tag);

	return SEQ__TAG;
}

/*
 * set_up_conditional creates a conditional based on a simple integer test.
 */
static exp
set_up_conditional(exp left, exp right, ntest test, int integer_value, exp id,
                   int probability)
{
	exp CLEAR__TAG;
	exp LABST__TAG;
	exp NAME__TAG;
	exp VAL__TAG;
	exp TEST__TAG;
	exp ZERO__TAG;
	exp SEQ__TAG;
	exp COND__TAG;
	exp CONT__TAG;

	/* Sets up the labst_tag for the conditional */
	CLEAR__TAG = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, clear_tag);
	LABST__TAG = me_b3(sh(right), CLEAR__TAG, right, labst_tag);

	/* sets up the test_tag */
	NAME__TAG = me_obtain(id);
	CONT__TAG = me_u3(sh(id), NAME__TAG, cont_tag);
	VAL__TAG  = me_shint(sh(CONT__TAG), integer_value);
	TEST__TAG = like_me_q1(probability, test, LABST__TAG, CONT__TAG,
	                       VAL__TAG, test_tag);

	/* sets up the seq_tag for the conditional */
	ZERO__TAG = me_u3(f_top, TEST__TAG, 0);
	SEQ__TAG  = me_b3(sh(left), ZERO__TAG, left, seq_tag);

	/* sets up the cond_tag */
	COND__TAG = me_b3(f_bottom, SEQ__TAG, LABST__TAG, cond_tag);

	return COND__TAG;
}

/*
 * set_up_exhaustive_case does exactly what it suggests.
 */
static exp
set_up_exhaustive_case(exp body_of_case, exp id)
{
	exp NAME__TAG;
	exp CASE__TAG;
	exp CONT__TAG;
	exp r;

	NAME__TAG = me_obtain(id);
	CONT__TAG = me_u3(sh(id), NAME__TAG, cont_tag);
	CASE__TAG = getexp(f_bottom, NULL, 0, CONT__TAG, NULL, 0, 0, case_tag);

	bro(CONT__TAG) = body_of_case;
	CONT__TAG->last = false;

	for (r = body_of_case; !r->last; r = bro(r))
		;

	bro(r) = CASE__TAG;

	return CASE__TAG;
}

/*
 * set_up_inexhaustive_case does exactly what it suggests.
 */
static exp
set_up_inexhaustive_case(exp body_of_case, exp id, exp default_exp)
{
	exp NAME__TAG;
	exp GOTO__TAG;
	exp CASE__TAG;
	exp ZERO__TAG;
	exp SEQ__TAG;
	exp CONT__TAG;
	exp r;

	NAME__TAG = me_obtain(id);
	CONT__TAG = me_u3(sh(id), NAME__TAG, cont_tag);

	/* shape of case is f_top since it is not exhaustive */
	CASE__TAG = getexp(f_top, NULL, 0, CONT__TAG, NULL, 0, 0, case_tag);
	bro(CONT__TAG) = body_of_case;
	CONT__TAG->last = false;

	for (r = body_of_case; !r->last; r = bro(r))
		;

	bro(r) = CASE__TAG;
	GOTO__TAG = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, goto_tag);
	pt(GOTO__TAG) = default_exp;
	no(son(default_exp)) ++;
	ZERO__TAG = me_u3(f_top, CASE__TAG, 0);

	/* doesn't matter what shape zero_tag is */
	SEQ__TAG = me_b3(f_bottom, ZERO__TAG, GOTO__TAG, seq_tag);

	return SEQ__TAG;
}

/*
 * like_me_q1 sets up a test_tag and is very similar to me_q1.
 * me_q1 is found in me_fns.c
 */
static exp
like_me_q1(int prob, ntest nt, exp lab, exp arg1, exp arg2, unsigned char nm)
{
	exp r;

	r = getexp(f_top, NULL, 0, arg1, lab, 0, 0, nm);
	no(r) = prob;
	settest_number(r, nt);
	setbro(arg1, arg2);
	arg1->last = false;
	++no(son(lab));
	setfather(r, arg2);

	return r;
}

/*
 * find_the_split_value is used by exhaustive_conditional_maker
 * and inexhaustive_conditional_maker in order to calculate
 * where to do a comparison.
 */
static int
find_the_split_value(int start, int end)
{
	int w;
	int split_value;
	double halfway_value;
	double best_diff;
	double count;

	count = 0.0;
	halfway_value = 0.0;

	for (w = start; w <= end; w++) {
		halfway_value += node_weight[w];
	}

	halfway_value = halfway_value / 2.0;
	best_diff = node_weight[start] - halfway_value;
	if (best_diff < 0.0) {
		best_diff = - best_diff;
	}

	split_value = start;
	for (w = start; w <= end; w++) {
		count += node_weight[w];
		if ((count - halfway_value) < best_diff &&
		    (halfway_value - count) < best_diff) {
			split_value = w;
			best_diff = count - halfway_value;
			if (best_diff < 0.0) {
				best_diff = - best_diff;
			}
		}
	}

	return split_value;
}

/*
 * exhaustive_conditional_maker is the recursive routine for making the
 * internal transformed tdf in the case of an exhaustive case_tag.
 */
static exp
exhaustive_conditional_maker(int start, int end, exp id)
{
	int split_value;
	exp option_left;
	exp option_right;
	exp t;

	/* first test to see if we have only one node */
	if (start == end) {
		/* Check to see if not a jump table */
		if (bro(node_start[start]) == NULL) {
			t = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0,
			           goto_tag);
			pt(t) = pt(node_start[start]);
			return t;
		} else {
			/* We must have to make a jump table */
			return set_up_exhaustive_case(node_start[start], id);
		}
	}

	split_value = find_the_split_value(start, end);
	if (split_value == end) {
		split_value --;
	}

	option_left  = exhaustive_conditional_maker(split_value + 1, end, id);
	option_right = exhaustive_conditional_maker(start, split_value, id);

	return set_up_conditional(option_left, option_right,
	                          f_greater_than_or_equal,
	                          no(node_start[split_value + 1]), id, 1000);
}

/*
 * inexhaustive_conditional_maker is the recursive routine for making the
 * internal transformed tdf in the case of an inexhaustive case_tag.
 */
static exp
inexhaustive_conditional_maker(int start, int end, exp id, exp default_exp)
{
	int split_value;
	exp option_left;
	exp option_right;
	exp spare;

	if (start == end) {
		/* Single range to single destination */
		if (node_start[start] == node_end[start]) {
			if ((node_start_flag[start] == 1) && (node_end_flag[start] == 1)) {
				spare = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, goto_tag);
				pt(spare) = pt(node_start[start]);
				return spare;
			} else {
				option_left = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, goto_tag);
				pt(option_left) = default_exp;
				no(son(default_exp))++;
				no(son(pt(node_start[start])))--;
				return set_up_sequence(option_left,
					pt(node_start[start]), f_not_equal, no(node_start[start]), id, 1000);
			}
		}

		/* Multi range to single destination */
		if (son(node_start[start]) == node_end[start]) {
			if ((node_start_flag[start] == 1) && (node_end_flag[start] == 1)) {
				spare = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, goto_tag);
				pt(spare) = pt(node_start[start]);
				return spare;
			}

			if ((node_start_flag[start] == 1) && (node_end_flag[start] == 0)) {
				option_left = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, goto_tag);
				pt(option_left) = default_exp;
				no(son(default_exp))++;
				no(son(pt(node_start[start])))--;
				node_end_flag[start] = 1;

				return set_up_sequence(option_left,
					pt(node_start[start]), f_greater_than, no(node_end[start]), id, 1000);
			}

			if ((node_start_flag[start] == 0) && (node_end_flag[start] == 1)) {
				option_left = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, goto_tag);
				pt(option_left) = default_exp;
				no(son(default_exp)) ++;
				no(son(pt(node_start[start])))--;
				node_start_flag[start] = 1;
				return set_up_sequence(option_left,
					pt(node_start[start]), f_less_than, no(node_start[start]), id, 1000);
			}

			/* We may as well do a subtraction and a comparison */
			node_start_flag[start] = node_end_flag[start] = 1;

			{
				exp SEQUENCE__TAG;
				exp ZERO__TAG;
				exp GOTO__TAG;
				int   subtract_value = no(node_start[start]);

				GOTO__TAG = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, goto_tag);
				pt(GOTO__TAG) = default_exp;
				no(son(default_exp)) ++;
				no(son(pt(node_start[start])))--;
				ZERO__TAG = me_b3(f_top,
				  set_up_assign(id, -subtract_value),
				  set_up_unsigned_test(pt(node_start[start]), id,
							   (no(node_end[start]) - subtract_value), f_greater_than), 0);

				SEQUENCE__TAG = me_b3(f_bottom, ZERO__TAG, GOTO__TAG, seq_tag);

				return SEQUENCE__TAG;
			}
		}

		/* We must have to do a jump table */
		if ((node_start_flag[start] == 1) && (node_end_flag[start] == 1)) {
			return set_up_inexhaustive_case(node_start[start], id, default_exp);
		}

		if ((node_start_flag[start] == 1) && (node_end_flag[start] == 0)) {
			option_left = set_up_inexhaustive_case(node_start[start], id, default_exp);
			node_end_flag[start] = 1;
			return set_up_sequence(option_left, default_exp,
			                       f_less_than_or_equal, no(node_end[start]), id, 1000);
		}

		if ((node_start_flag[start] == 0) && (node_end_flag[start] == 1)) {
			option_left = set_up_inexhaustive_case(node_start[start], id, default_exp);
			node_start_flag[start] = 1;
			return set_up_sequence(option_left, default_exp,
			                       f_greater_than_or_equal, no(node_start[start]), id, 1000);
		}

		/*
		 * Put in a jump table by doing a subtraction first and comparison
		 * for both sides.
		 */
		node_start_flag[start] = node_end_flag[start] = 1;
		{
			exp ZERO__TAG;
			exp SEQUENCE__TAG;
			exp SPARE__TAG;
			exp r;
			int subtract_value;
			subtract_value = no(node_start[start]);

			ZERO__TAG = me_b3(f_top, set_up_assign(id, -subtract_value),
			          set_up_unsigned_test(default_exp, id,
						   (no(node_end[start]) - subtract_value),
						   f_less_than_or_equal), 0);

			for (r = node_start[start]; r != NULL; r = bro(r)) {
				no(r) = no(r) - subtract_value;
				if (son(r) != NULL) {
					no(son(r)) = no(son(r)) -
					             subtract_value;
				}
			}

			SPARE__TAG = set_up_inexhaustive_case(node_start[start], id, default_exp);
			SEQUENCE__TAG = me_b3(sh(SPARE__TAG), ZERO__TAG, SPARE__TAG, seq_tag);

			return SEQUENCE__TAG;
		}
	}

	/*
	 * assert that node_start_flag[split_value + 1] and
	 * node_end_flag[split_value] should be zero or split_value = end
	 */
	split_value = find_the_split_value(start, end);

	/*
	 * This is the case when we have a simple single range node in
	 * the 1:n split.
	 */
	if (split_value == start && (node_start[start] == node_end[start])) {
		option_left = inexhaustive_conditional_maker(start + 1, end, id, default_exp);
		no(son(pt(node_start[start])))--;

		return set_up_sequence(option_left, pt(node_start[start]),
		                       f_not_equal, no(node_start[start]), id, 1000);
	}

	/*
	 * This is the case when we have a simple single range node in
	 * the n:1 split.
	 */
	if (split_value >= end - 1 && (node_start[end] == node_end[end])) {
		option_left = inexhaustive_conditional_maker(start, end - 1, id, default_exp);
		no(son(pt(node_start[end])))--;
		return set_up_sequence(option_left, pt(node_start[end]),
		                       f_not_equal, no(node_start[end]), id, 1001);
	}

	/*
	 * This is the case when we have a multi range to the in the
	 * 1:n split where the left hand comparison has been done
	 */
	if (split_value == start &&
		(son(node_start[start]) == node_end[start]) &&
		node_start_flag[start] == 1)
	{

		/* If we have a close together split there is no need to recompare */
		if (no(node_end[start]) == (no(node_start[start + 1]) - 1)) {
			node_start_flag[start + 1] = 1;
		}

		option_left = inexhaustive_conditional_maker(start + 1, end, id, default_exp);
		no(son(pt(node_start[start])))--;
		return set_up_sequence(option_left, pt(node_start[start]),
		                       f_greater_than, no(node_end[start]), id,
		                       1001);
	}

	/*
	 * This is the case when we have a multi range to the in the
	 * n:1 split where the right hand comparison has been done.
	 */
	if (split_value >= end - 1 &&
	    (son(node_start[end]) == node_end[end]) &&
	    node_end_flag[end] == 1)
	{
		/* If we have a close together split there is no need to recompare. */
		if (no(node_end[end - 1]) == (no(node_start[end]) - 1)) {
			node_end_flag[end - 1] = 1;
		}

		option_left = inexhaustive_conditional_maker(start, end - 1, id, default_exp);
		no(son(pt(node_start[end])))--;
		return set_up_sequence(option_left, pt(node_start[end]),
		                       f_less_than, no(node_start[end]), id, 1000);
	}

	if (split_value == end) {
		split_value --;
	}

	/*
	 * If we have a multi range or a jump table to the left or right of the
	 * split, it is better to do one of those comparisons because it will
	 * save a comparison whereas doing a comparison against a single range
	 * saves nothing.
	 */
	if (node_start[split_value] == node_end[split_value]) {
		/* do the comparison against split_value+1 */
		node_start_flag[split_value + 1] = 1;

		/* If we have a close together split there is no need to recompare. */
		if (no(node_end[split_value]) ==
		    (no(node_start[split_value + 1]) - 1)) {
			node_end_flag[split_value] = 1;
		}

		option_right = inexhaustive_conditional_maker(start, split_value, id, default_exp);
		option_left = inexhaustive_conditional_maker(split_value + 1, end, id, default_exp);

		return set_up_conditional(option_left, option_right,
		                          f_greater_than_or_equal,
		                          no(node_start[split_value + 1]), id, 1000);
	} else {
		/* do the comparison against split_value */
		node_end_flag[split_value] = 1;
		/* If we have a close together split there is no need to recompare. */
		if (no(node_end[split_value]) ==
		    (no(node_start[split_value + 1]) - 1)) {
			node_start_flag[split_value + 1] = 1;
		}

		option_right = inexhaustive_conditional_maker(start, split_value, id, default_exp);
		option_left = inexhaustive_conditional_maker(split_value + 1, end, id, default_exp);

		return set_up_conditional(option_left, option_right, f_greater_than,
		                          no(node_end[split_value]), id, 1000);
	}
}

/*
 * set_up_assign takes a variable and adds an integer to
 * it, and replaces it.
 */
static exp
set_up_assign(exp id, int number)
{
	exp NAME__TAG;
	exp VAL__TAG;
	exp CONT__TAG;
	exp PLUS__TAG;
	exp ASSIGN__TAG;

	NAME__TAG   = me_obtain(id);
	VAL__TAG    = me_shint(sh(id), number);
	CONT__TAG   = me_u3(sh(id), NAME__TAG, cont_tag);
	PLUS__TAG   = me_b3(sh(id), CONT__TAG, VAL__TAG, plus_tag);
	ASSIGN__TAG = me_b3(f_top, me_obtain(id), PLUS__TAG, ass_tag);

	return ASSIGN__TAG;
}

/*
 * set_up_unsigned_test returns a test_tag.
 *
 * The test is specified, along with the value to be tested against
 * the default_exp labst_tag and the var_tag to test against.
 */
static exp
set_up_unsigned_test(exp default_exp, exp id, int test_value, ntest test)
{
	exp NAME__TAG;
	exp CHVAR__TAG;
	exp CONT__TAG;
	exp VAL__TAG;
	exp TEST__TAG;

	NAME__TAG  = me_obtain(id);
	CONT__TAG  = me_u3(sh(id), NAME__TAG, cont_tag);
	CHVAR__TAG = hold_refactor(me_u3(ulongsh, CONT__TAG, chvar_tag));
	VAL__TAG   = me_shint(ulongsh, test_value);
	TEST__TAG  = like_me_q1(1000, test, default_exp, CHVAR__TAG, VAL__TAG, test_tag);

	return TEST__TAG;
}

