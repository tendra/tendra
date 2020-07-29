/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include <stddef.h>

#include <shared/string.h>
#include <shared/xalloc.h>

#include "list.h"
#include "utility.h"


/*
 * SPARE LISTS
 *
 * This is a list of list structures which have been freed using free_list.
 * new_list tries to allocate new list structures from this list before using
 * its internal array.
 */
static list *spare_lists = NULL;


/*
 * CREATE A NEW LIST
 *
 * This routine allocates a new list structure.
 */
static list *
new_list(void)
{
	static int no_free = 0;
	static list *free_objs = NULL;

	if (spare_lists) {
		list *p = spare_lists;
		spare_lists = p->next;

		return p;
	}

	if (no_free == 0) {
		no_free = 1000;
		free_objs = xmalloc_nof(list, no_free);
	}

	return free_objs + (--no_free);
}


/*
 * FREE A LIST
 *
 * This list returns p to free.
 */
void
free_list(list *p)
{
	spare_lists = add_list(p, spare_lists);
}


/*
 * JOIN TWO LISTS
 *
 * This routine joins two lists, p and q, and returns the result.
 */
list *
add_list(list *p, list *q)
{
	list *r;

	if (p == NULL)
		return q;

	if (q == NULL)
		return p;

	for (r = p; r->next != NULL; r = r->next)
		;

	r->next = q;
	return p;
}


/*
 * ADD AN ITEM TO A LIST
 *
 * This routine adds a new item, s, to the end of the list p and returns the
 * result.
 * XXX: better name?
 */
list *
add_item(list *p, const char *s)
{
	list *q;

	q = new_list();
	q->s = s;
	q->next = NULL;

	return add_list(p, q);
}


/*
 * INSERT AN ITEM INTO A LIST
 *
 * This routine adds a new item, s, to the start of the list p and returns the
 * result.
 * TODO argument order inconsistent against add_item()
 * XXX: better name?
 */
list *
insert_item(const char *s, list *p)
{
	list *q;

	q = new_list();
	q->s = s;
	q->next = NULL;

	return add_list(q, p);
}


/*
 * CONVERT A STRING TO A LIST
 *
 * This routine converts a string to a list by breaking it at all white spaces
 * (spaces and tabs).
 */
list *
make_list(const char *s)
{
	list *r = NULL;
	char *p = xstrdup(s);

	for (;;) {
		while (*p == ' ' || *p == '\t')
			*(p++) = '\0';

		if (*p == '\0')
			break;

		r = add_item(r, p);

		while (*p && *p != ' ' && *p != '\t')
			p++;
	}

	return r;
}
