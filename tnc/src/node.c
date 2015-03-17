/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/xalloc.h>

#include "config.h"
#include "types.h"
#include "node.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"

bool dont_check = 0;


static node *free_nodes = NULL;


static construct *free_constructs = NULL;


char *local_prefix = "<none>";


node *
new_node(void)
{
	node *p = free_nodes;

	if (p == NULL) {
		int i, m = 1000;

		p = xmalloc_nof(node, m);

		for (i = 0; i < m - 1; i++) {
			(p + i) ->bro = p + (i + 1);
			(p + i) ->son = NULL;
		}

		(p + (m - 1)) ->bro = NULL;
		(p + (m - 1)) ->son = NULL;
		free_nodes = p;
	}

	free_nodes = p->bro;
	p->cons = NULL;
	p->son = NULL;
	p->bro = NULL;
	p->shape = NULL;

	return p;
}


void
free_node(node *p)
{
	while (p) {
		node *q = p->bro;

		if (p->son)
			free_node(p->son);

		p->bro = free_nodes;
		free_nodes = p;
		p = q;
	}
}


node *
completion(node *p)
{
	node *q = new_node();
	construct *v = make_construct(SORT_completion);

	v->next = removals;
	removals = NULL;
	q->cons = v;
	q->son = p;

	return q;
}


static bool
eq_node_aux(node *p, node *q, construct *ap, construct *aq, int args)
{
	while (p != NULL && q != NULL) {
		if (p->cons != q->cons) {
			sortname s = p->cons->sortnum;

			if (s != q->cons->sortnum)
				return 0;

			switch (s) {
			case SORT_bytestream:
			case SORT_option:
				/* Just check son */
				break;

			case SORT_tdfbool:
			case SORT_small_tdfint:
			case SORT_repeat:
				/* Check value or number of repeats */
				if (p->cons->encoding != q->cons->encoding)
					return 0;

				break;
			case SORT_tdfint:
			case SORT_tdfstring:
				/* Check value */
				if (strcmp(p->cons->name, q->cons->name) != 0)
					return 0;

				break;
			default:
				{
					/* Check lists of local variables */
					bool ok = 0;
					construct *xp = ap;
					construct *xq = aq;

					while (xp && !ok) {
						if (xp == p->cons &&
						    xq == q->cons)
							ok = 1;

						xp = xp->next;
						xq = xq->next;
					}

					if (!ok)
						return 0;
				}
				break;
			}
		}

		if (!eq_node_aux(p->son, q->son, ap, aq, 1))
			return 0;

		if (!args)
			return 1;

		p = p->bro;
		q = q->bro;
	}

	if (p == q)
		return 1;

	return 0;
}


static bool
eq_cons_list(construct *ap, construct *aq)
{
	while (ap != NULL && aq != NULL) {
		if (ap->sortnum != aq->sortnum)
			return 0;

		ap = ap->next;
		aq = aq->next;
	}

	if (ap == aq)
		return 1;

	return 0;
}



bool
eq_node(node *p, node *q)
{
	construct *ap = NULL;
	construct *aq = NULL;

	if (dont_check)
		return 1;

	if (p == q)
		return 1;

	if (p == NULL || q == NULL)
		return 0;

	if (p->cons->sortnum == SORT_completion) {
		ap = p->cons->next;
		p = p->son;
	}

	if (q->cons->sortnum == SORT_completion) {
		aq = q->cons->next;
		q = q->son;
	}

	if (!eq_cons_list(ap, aq))
		return 0;

	return eq_node_aux(p, q, ap, aq, 0);
}




construct *
new_construct(void)
{
	construct *p = free_constructs;

	if (p == NULL) {
		int i, m = 100;
		p = xmalloc_nof(construct, m);

		for (i = 0; i < m - 1; i++)
			(p + i) ->next = p + (i + 1);

		(p + (m - 1)) ->next = NULL;
		free_constructs = p;
	}

	free_constructs = p->next;
	p->alias = NULL;
	p->next = NULL;

	return p;
}


construct *
make_construct(sortname s)
{
	construct *p = new_construct();

	p->sortnum = s;

	if (s >= 0)
		p->encoding = (sort_count[s]) ++;
	else
		p->encoding = 0;

	p->name = NULL;
	p->ename = NULL;
	p->next = NULL;

	switch (s) {
	case SORT_al_tag:
		{
			/* Initialize alignment tag */
			al_tag_info *q = get_al_tag_info(p);
			q->def = NULL;
		}
		break;
	case SORT_tag:
		{
			/* Initialize tag */
			tag_info *q = get_tag_info(p);
			q->var = 3;
			q->vis = 0;
			q->dec = NULL;
			q->def = NULL;
		}
		break;
	case SORT_token:
		{
			/* Initialize token */
			tok_info *q = get_tok_info(p);
			q->dec = 0;
			q->res = SORT_unknown;
			q->args = NULL;
			q->sig = NULL;
			q->def = NULL;
			q->pars = NULL;
			q->depth = 0;
		}
		break;
	}

	return p;
}


void
free_construct(construct **p)
{
	construct *q = *p;

	if (q) {
		while (q->next)
			q = q->next;

		q->next = free_constructs;
		free_constructs = *p;
	}

	*p = NULL;
}


void
set_token_sort(construct *p, sortname rs, char *args, node *sig)
{
	tok_info *info = get_tok_info(p);

	if (info->res != SORT_unknown) {
		bool error = 0;

		if (info->res != rs)
			error = 1;

		if (args) {
			if (info->args == NULL || strcmp(args, info->args) != 0)
				error = 1;

		} else
			if (info->args)
				error = 1;

		if (error) {
			is_fatal = 0;
			input_error("Token %s declared inconsistently", p->name);
		}
	}

	info->res = rs;
	info->args = args;
	info->sig = sig;
}


void
set_tag_type(construct *p, int is_var)
{
	tag_info *info = get_tag_info(p);

	if (info->var != 3) {
		if (info->var != is_var) {
			is_fatal = 0;
			input_error("Tag %s declared inconsistently", p->name);
		}
	}
#if 0
	info->var = is_var;
#endif
}


void
copy_construct(construct *p)
{
	sortname s = p->sortnum;
	construct *q = make_construct(s);

	if (s == SORT_tag) {
		tag_info *pi = get_tag_info(p);
		tag_info *qi = get_tag_info(q);
		qi->var = pi->var;
		qi->vis = pi->vis;
	}

	q->name = p->name;
	p->alias = q;
	(sort_removed[s]) ++;
}


char *
skip_text(char *s)
{
	int n = 0;

	while (*s) {
		if (*s == '[')
			n++;

		if (*s == ']') {
			if (n == 0)
				return s;

			n--;
		}

		s++;
	}

	fatal_error("Illegal decoding string");
	return NULL; /* Not reached */
}


bool
is_local_name(char *s)
{
	/* XXX: handmade strncmp() ? */

	char *t = local_prefix;

	while (*s == *t) {
		s++;
		t++;
	}

	if (*t == '\0')
		return 1;

	return 0;
}
