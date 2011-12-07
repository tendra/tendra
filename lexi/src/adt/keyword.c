/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>

#include <shared/xalloc.h>
#include <shared/error.h>

#include "keyword.h"
#include "zone.h"
#include "instruction.h"

struct keyword_tag {
	const char *name;
	instruction *instr;

	/* All keywords are formed into a list using the next field */
	keyword *next;
};


/*
    ADD A KEYWORD

    This routine adds the keyword nm with its associated data to the list
    of all keywords.
*/

void
add_keyword(zone* z, const char *nm, instruction* instr)
{
    keyword *p = z->keywords, *q = NULL;

	assert(nm != NULL);
	assert(strlen(nm) > 0);

    while (p) {
	int c = strcmp(nm, p->name);
	if (c == 0) {
	    error(ERROR_SERIOUS, "Keyword '%s' already defined", nm);
	    return;
	}
	if (c < 0)break;
	q = p;
	p = p->next;
    }
    p = xmalloc(sizeof *p);
    p->name = nm;
    p->instr = instr;
    if (q == NULL) {
	p->next = z->keywords;
	z->keywords = p;
    } else {
	p->next = q->next;
	q->next = p;
    }
    return;
}

void
keywords_iterate(keyword *kw, void (*f)(keyword *, void *), void *opaque)
{
	keyword *k;

	assert(kw != NULL);
	assert(f != NULL);

	for (k = kw; k; k = k->next) {
		f(k, opaque);
	}
}

instruction *
keyword_instruction(keyword *kw)
{
	assert(kw != NULL);

	return kw->instr;
}

const char *
keyword_name(keyword *kw)
{
	assert(kw != NULL);

	return kw->name;
}
