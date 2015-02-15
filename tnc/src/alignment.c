/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>

#include "config.h"
#include "types.h"
#include "alignment.h"
#include "check.h"
#include "node.h"
#include "shape.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
    These are the basic alignments from the TDF specification.
*/

node *al_code = NULL;
node *al_frame =  NULL;
node *al_alloca = NULL;
node *al_var_param = NULL;
node *al_top =  NULL;
static node *al_offset = NULL;
static node *al_pointer = NULL;
static node *al_proc = NULL;


/*
    For the node p, representing a shape or an alignment, this returns
    the alignment of p.
*/

node *
al_shape(node *p)
{
	node *q;
	sortname s;

	if (p == NULL)
		return NULL;

	s = p->cons->sortnum;

	if (s == SORT_alignment) {
		switch (p->cons->encoding) {
		case ENC_alignment:
			return al_shape(p->son);
		case ENC_alignment_apply_token:
			return al_shape(expand_tok(p));
		}
		return copy_node(p);
	}

	if (s == SORT_shape) {
		switch (p->cons->encoding) {
		case ENC_bottom:
			is_fatal = 0;
			input_error("Can't have alignment of bottom in %s",
			    checking);
			return NULL;
		case ENC_offset:
			return copy_node(al_offset);
		case ENC_pointer:
			return copy_node(al_pointer);
		case ENC_proc:
			return copy_node(al_proc);
		case ENC_top:
			return copy_node(al_top);
		case ENC_nof:
			return al_shape(p->son->bro);
		case ENC_shape_apply_token:
			return al_shape(expand_tok(p));
		}
	}

	q = new_node();
	q->cons = cons_no(SORT_alignment, ENC_alignment);
	q->son = copy_node(p);

	return NULL;
}


/*
    For the node p of the form ( pointer a ) this routine returns a.
*/

node *
ptr_to(node *p)
{
	p = expand_tok(p);

	if (p && p->cons == cons_no(SORT_shape, ENC_pointer))
		return p->son;

	return NULL;
}


/*
    For the node p of the form ( offset a b ) this routine returns a.
*/

node *
offset_from(node *p)
{
	p = expand_tok(p);

	if (p && p->cons == cons_no(SORT_shape, ENC_offset))
		return p->son;

	return NULL;
}


/*
    For the node p of the form ( offset a b ) this routine returns b.
*/

node *
offset_to(node *p)
{
	p = expand_tok(p);

	if (p && p->cons == cons_no(SORT_shape, ENC_offset))
		return p->son->bro;

	return NULL;
}


/*
    This routine is not yet implemented.
*/

void
al_equals(node *p, node *q)
{
	UNUSED(p);
	UNUSED(q);
}


/*
    This routine is not yet implemented.
*/

void
al_includes(node *p, node *q)
{
	UNUSED(p);
	UNUSED(q);
}


/*
    The value of ( unite_alignments p q ) is returned.
*/

node *
al_union(node *p, node *q)
{
	if (p == NULL || p->cons->sortnum != SORT_alignment)
		return NULL;

	if (q == NULL || q->cons->sortnum != SORT_alignment)
		return NULL;

	if (p->cons->encoding == ENC_alignment &&
	    p->son->cons == cons_no(SORT_shape, ENC_top))
		return q;

	if (q->cons->encoding == ENC_alignment &&
	    q->son->cons == cons_no(SORT_shape, ENC_top))
		return p;

	return NULL;
}


/*
    The basic alignments, al_top, al_offset, al_pointer and al_proc, are
    initialized.
*/

void
init_alignments(void)
{
	/* Set up al_top */
	al_top =  new_node();
	al_top->cons = cons_no(SORT_alignment, ENC_alignment);
	al_top->son = copy_node(sh_top);

	/* Set up al_offset */
	al_offset =  new_node();
	al_offset->cons = cons_no(SORT_alignment, ENC_alignment);
	al_offset->son = sh_offset(al_top, al_top);

	/* Set up al_pointer */
	al_pointer =  new_node();
	al_pointer->cons = cons_no(SORT_alignment, ENC_alignment);
	al_pointer->son = sh_pointer(al_top);

	/* Set up al_proc */
	al_proc =  new_node();
	al_proc->cons = cons_no(SORT_alignment, ENC_alignment);
	al_proc->son = copy_node(sh_proc);
}
