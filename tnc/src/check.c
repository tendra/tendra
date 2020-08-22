/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/magic.h>

#include "types.h"
#include "alignment.h"
#include "check.h"
#include "eval.h"
#include "node.h"
#include "read.h"
#include "shape.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
    This flag is true to indicate that shape checking should be applied.
*/

bool do_check = 0;


/*
    The shape checking does not always take place immediately.  By
    printing the name of the expression being checked it is easier
    to find any errors.
*/

char *checking = "????";


/*
    The shape checking for the exp_apply_token construct p is implemented
    by this routine.
*/

static void
chk_token(node *p)
{
	tok_info *info = get_tok_info(p->child->cons);
	node *d = info->def;

	if (d) {
		if (d->cons->sortnum == SORT_completion)
			d = d->child;

		p->shape = normalize(d->shape);
	} else {
		p->shape = new_node();
		p->shape->cons = &shape_of;
		p->shape->child = copy_node(p->child);
	}
}


/*
    The shape checking for the exp_cond construct p is implemented by
    this routine.  Checking that the control argument is an integer is
    carried out for all _cond constructs as part of the main reading
    and decoding routines for the decode letter '@'.
*/

static void
chk_cond(node *p)
{
	node *s;
	node *q1 = p->child->next->child;
	node *q2 = p->child->next->next->child;
	node *s1 = q1->shape;
	node *s2 = q2->shape;

	if (q1->cons->encoding == ENC_fail_installer) {
		p->shape = normalize(s2);
		return;
	}

	if (q2->cons->encoding == ENC_fail_installer) {
		p->shape = normalize(s1);
		return;
	}

	s = lub(s1, s2);
	if (s == NULL)
		p->shape = NULL;
	else {
		long n = s->cons->encoding;

		if (n == ENC_bottom || n == ENC_top)
			p->shape = NULL;
		else
			p->shape = normalize(s);
	}
}


/*
    The shape checking for the obtain_tag construct p is implemented by
    this routine.  a gives the actual tag.
*/

static void
chk_tag(node *p, node *a, int intro)
{
	if (!intro && a->cons->encoding == ENC_make_tag) {
		tag_info *info = get_tag_info(a->child->cons);
		node *d = info->dec;

		if (d && d->cons->sortnum == SORT_completion)
			d = d->child;
		if (d)
			d = d->next;
		if (d)
			d = d->next;

		switch (info->var) {
		case 0:
			p->shape = normalize(d);
			break;
		case 1:
		case 2:
			p->shape = sh_pointer(d);
			break;
		default:
			if (text_input) {
				char *nm = a->child->cons->name;
				is_fatal = 0;
				input_error("Tag %s used but not declared", nm);
			}

			p->shape = NULL;
			break;
		}
	} else
		p->shape = NULL;
}


/*
    The main body of the shape checking for expressions is in the
    automatically generated file check_exp.h.  This calls a macro of
    the form check_<cons> for each construct <cons>.  The actual
    definitions of these macros (which vary between TDF specification
    releases) are in check_def.h.
*/

#include "check_def.h"
#include "check_exp.h"


/*
    The construct compound has an exp argument which needs to be
    shape checked.
*/

void
check_shape_fn(node *p)
{
	if (do_check && p && p->cons->encoding == ENC_compound) {
		checking = p->cons->name;
		IGNORE check1(ENC_offset, p->child);
	}
}


/*
    The construct computed_nat has an exp argument which needs to be
    shape checked.
*/

void
check_nat_fn(node *p)
{
	if (do_check && p && p->cons->encoding == ENC_computed_nat) {
		checking = p->cons->name;
		IGNORE check1(ENC_integer, p->child);
	}
}


/*
    The construct computed_signed_nat has an exp argument which needs
    to be shape checked.
*/

void
check_snat_fn(node *p)
{
	if (do_check && p && p->cons->encoding == ENC_computed_signed_nat) {
		checking = p->cons->name;
		IGNORE check1(ENC_integer, p->child);
	}
}


/*
    The flag intro_visible is set whenever a visible construct is
    encountered.
*/

void
check_access_fn(node *p)
{
    if (p && p->cons->encoding == ENC_visible)
	    intro_visible = 1;
}


/*
    This routine returns true if p is not NULL and does not contain
    any unknown constructs.  In encode mode we can't have any constructs
    which introduce local tags or tokens either.
*/

static bool
is_known(node *p)
{
	if (p == NULL)
		return 0;

	while (p) {
		sortname s = p->cons->sortnum;

		if (s == SORT_unknown)
			return 0;

		if (!text_output && s == SORT_exp)
			switch (p->cons->encoding) {
			case ENC_conditional:
			case ENC_identify:
			case ENC_labelled:
			case ENC_make_proc:
			case ENC_repeat:
			case ENC_variable:
				return 0;
			}

		if (p->child && !is_known(p->child))
			return 0;

		p = p->next;
	}

	return 1;
}


/*
    The construct p, representing a declared and defined tag, is checked
    for shape correctness.
*/

void
check_tagdef(construct *p)
{
	char *nm = p->name;
	tag_info *info = get_tag_info(p);
	node *dc = info->dec;
	node *df = info->def;

	if (df == NULL)
		return;

	if (df->cons->sortnum == SORT_completion)
		df = df->child;

	if (info->var)
		df = df->next;

	if (dc == NULL) {
		if (is_known(df->shape)) {
			/* Declaration = ?[u]?[X]S (from 4.0) */
			node *q = new_node();
			q->cons = &false_cons;
			q->next = new_node();
			q->next->cons = &false_cons;
			q->next->next = df->shape;
			info->dec->next = completion(q);
		} else {
			is_fatal = 0;
			input_error("Can't deduce shape of %s from definition", nm);
		}
	} else {
		if (dc->cons->sortnum == SORT_completion)
			dc = dc->child;

		/* Declaration = ?[u]?[X]S (from 4.0) */
		dc = dc->next->next;
		checking = nm;
		IGNORE check_shapes(dc, df->shape, 1);
	}
}
