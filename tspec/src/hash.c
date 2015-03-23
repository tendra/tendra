/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <time.h>
#include <string.h>

#include "object.h"
#include "hash.h"
#include "type.h"
#include "utility.h"

/*
 * STANDARD HASH TABLES
 *
 * These hash tables represent the various namespaces permitted in C
 * plus the TDF token namespace.
 */
hash_table *exps;
hash_table *files;
hash_table *keywords;
hash_table *subsets;
hash_table *tags;
hash_table *tag_fields;
hash_table *tokens;
hash_table *types;
hash_table *type_fields;

void
init_hash(void)
{
	buffer      = xmalloc(buffsize + 100);
	exps        = make_hash_table("Expression");
	files       = make_hash_table("Output file");
	keywords    = make_hash_table("Keyword");
	subsets     = make_hash_table("Set");
	tags        = make_hash_table("Tag");
	tag_fields  = make_hash_table("Field selector struct/union");
	tokens      = make_hash_table("Token");
	types       = make_hash_table("Type");
	type_fields = make_hash_table("Field selector");
}

/*
 * HASHING ROUTINE
 *
 * This routine finds the hash value of the string nm.  This value must
 * lie in the range [ 0, hash_size ).
 */
static int
hash(char *nm)
{
	char *s;
	int n;

	n = 0;
	for (s = nm; *s != '\0'; s++) {
		n += *s;
	}

	return n % hash_size;
}

/*
 * CREATE A NEW HASH TABLE
 *
 * This routine creates a new hash table called nm.
 */
hash_table *
make_hash_table(char *nm)
{
	int i;
	hash_table *t;

	t = xmalloc_nof(hash_table, 1);
	t->name = nm;

	for (i = 0; i < hash_size; i++) {
		t->array [i] = NULL;
	}

	return t;
}

/*
 * LOOK UP A NAME IN A HASH TABLE
 *
 * This routine looks up the object nm (version v) in the hth column
 * of hash table t.  It returns the object if it is found, or NULL
 * otherwise.
 */
static object *
lookup_hash(hash_table *t, char *nm, int v, int h)
{
	hash_elem *e;

	for (e = t->array [h]; e != NULL; e = e->next) {
		if (!streq(nm, e->obj->name)) {
			continue;
		}

		if (v == e->vers || v == any_version) {
			return e->obj;
		}
	}

	return NULL;
}

/*
 * ADD AN OBJECT TO A HASH TABLE
 *
 * This routine adds the object p (version v) to the hash table t,
 * reporting an error and returning the old value if it is already
 * defined.  Otherwise it returns p.
 */
object *
add_hash(hash_table *t, object *p, int v)
{
	hash_elem *e;
	char *nm;
	int h;
	object *q;

	nm = p->name;
	h = hash(nm);
	q = lookup_hash(t, nm, v, h);

	if (q != NULL) {
		if (q->filename != NULL) {
			char *err = "%s '%s' already defined (%s, line %d)";
			error(ERR_SERIOUS, err, t->name, nm, q->filename, q->line_no);
		} else {
			error(ERR_SERIOUS, "%s '%s' already defined", t->name, nm);
		}

		return q;
	}

	e = xmalloc(sizeof *e);
	e->obj  = p;
	e->vers = v;

	e->next = t->array[h];
	t->array[h] = e;

	return p;
}

/*
 * SEARCH A HASH TABLE FOR AN OBJECT
 *
 * This routine searches the hash table t for the object named nm
 * (version v), returning it if it is found.  If it is not found then
 * NULL is returned.
 */
object *
search_hash(hash_table *t, char *nm, int v)
{
	int h;

	h = hash(nm);

	return lookup_hash(t, nm, v, h);
}

/*
 * SORT THE ELEMENTS OF A HASH LIST
 *
 * This routine sorts the elements of the hash table t into a single
 * alphabetical list.  The table cannot be used subsequently.
 */
hash_elem *
sort_hash(hash_table *t)
{
	int i;
	hash_elem *r;

	r = NULL;
	for (i = 0; i < hash_size; i++) {
		hash_elem *p;
		hash_elem *pn;

		for (p = t->array[i]; p != NULL; p = pn) {
			hash_elem *q, *s;

			pn = p->next;

			s = NULL;
			for (q = r; q != NULL; q = q->next) {
				if (strcmp(p->obj->name, q->obj->name) <= 0) {
					break;
				}

				s = q;
			}

			if (s == NULL) {
				p->next = r;
				r = p;
			} else {
				p->next = s->next;
				s->next = p;
			}
		}
	}
	return r;
}

