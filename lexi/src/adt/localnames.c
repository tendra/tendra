/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/xalloc.h>

#include <exds/common.h>
#include <exds/dstring.h>

#include "localnames.h"

static LocalNamesEntryT *
localnamesentry_create(char c, LocalNamesEntryT *parent)
{
	LocalNamesEntryT *locals;

	locals = xmalloc_nof(LocalNamesEntryT, 1);

	locals->c    = c;
	locals->next = NULL;
	locals->opt  = NULL;
	locals->type = NULL;
	locals->up   = parent;

	return locals;
}

extern void
localnames_init(LocalNamesT *p)
{
	p->max_depth = 0;
	p->top = NULL;
}


/*
 * Adding an entry to the trie
 *
 * This functions adds key "name" with value "type" to the trie.
 * It return 1 upon success and 0 upon failure. It is not possible to
 * add the empty string which is fine as no identifier can have zero length.
 */
int
localnames_add_nstring(LocalNamesT *locals, NStringT *name, struct EntryT *type)
{
	LocalNamesEntryT **crt;
	LocalNamesEntryT *parent;
	unsigned int i;
	char *p;

	/* TODO: assert(locals != NULL) */

	crt = &locals->top;
	parent = NULL;
	p = nstring_contents(name); /* BEWARE: not zero terminated! */

	for (i = 0; i < nstring_length(name); i++) {
		while (*crt != NULL && (*crt)->c < p[i]) {
			crt = &(*crt)->opt;
		}

		if (*crt == NULL || (*crt)->c != p[i]) {
			LocalNamesEntryT *newcrt;

			newcrt = localnamesentry_create(p[i], parent);
			newcrt->opt = *crt;
			*crt = newcrt;
		}

		parent = *crt;
		crt  = &(*crt)->next;
	}

	if (parent->type == NULL) {
		parent->type = type;
		locals->max_depth = (locals->max_depth > nstring_length(name)) ? locals->max_depth : nstring_length(name);
		return 1; /* Success */
	} else {
		return 0; /* Failure: key already present in trie */
	}
}

/*
 * This function search for an entry name in the trie
 *
 * This functions search key "name" and return its value.
 * It returns NULL if it cannot find the value.
 */
struct EntryT *
localnames_get_type(LocalNamesT *locals, NStringT *name)
{
	unsigned int i;
	struct EntryT *entry;
	LocalNamesEntryT *crt;
	char *p;

	entry = NULL;
	crt   = locals->top;

	p = nstring_contents(name); /* BEWARE: not zero terminated! */

	for (i = 0; i < nstring_length(name); i++) {
		while (crt != NULL && crt->c < p[i]) {
			crt = crt->opt;
		}

		if (crt == NULL || crt->c != p[i]) {
			return NULL;
		} else {
			entry = crt->type;
			crt   = crt->next;
		}
	}

	return entry;
}

/* Iterating over a trie without using recursive functions */
void
localnames_begin(LocalNamesIteratorT *it, LocalNamesT *locals)
{
	it->p = locals->top;
	it->depth = 0;

	if (it->p == NULL) {
		return;
	}

	it->depth++;
	while (it->p->next != NULL) {
		it->p = it->p->next;
		it->depth++;
	}
}

void
localnamesiterator_next(LocalNamesIteratorT *it)
{
	do {
		it->p = it->p->up;
		it->depth--;
	} while (it->p && it->p->type == NULL && it->p->opt == NULL);

	if (it->p && it->p->opt) {
		it->p = it->p->opt;
		while (it->p->next) {
			it->p = it->p->next;
			it->depth++;
		}
	}

	/* TODO: assert(it->p->type != NULL || it->p == NULL) */
}

