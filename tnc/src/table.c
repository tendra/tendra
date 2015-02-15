/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>
#include <shared/xalloc.h>

#include "config.h"
#include "types.h"
#include "help.h"
#include "high.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


construct **var_table;
construct **cons_table;
static int *cons_sizes;
construct **cons_hash_tables;
static construct **var_hash_tables;


long *sort_count;
char *sort_letters;
int *sort_encoding;
int *sort_extension;
long *sort_tokens;
long *sort_conds;
long *sort_removed;
decode_func *sort_decode;
read_func *sort_read;


construct bytestream_cons = { SORT_bytestream, 0, NULL, NULL, NULL, NULL };
construct false_cons = { SORT_tdfbool, 0, NULL, NULL, NULL, NULL };
construct optional_cons = { SORT_option, 0, NULL, NULL, NULL, NULL };
construct string_cons = { SORT_tdfstring, -1, NULL, NULL, NULL, NULL };
construct token_cons = { SORT_token, 0, NULL, NULL, NULL, NULL };
construct true_cons = { SORT_tdfbool, 1, NULL, NULL, NULL, NULL };
construct unknown_cons = { SORT_unknown, 0, "....", NULL, NULL, NULL };
construct exp_shape = { SORT_exp, 0, "~exp_with_shape", NULL, NULL, NULL };
construct shape_of = { SORT_shape, -1, "~shape_of", NULL, NULL, NULL };


construct *removals = NULL;


boolean show_tokdecs = 1;
boolean show_tokdefs = 1;
boolean show_aldecs = 1;
boolean show_aldefs = 1;
boolean show_tagdecs = 1;
boolean show_tagdefs = 1;


boolean order_names = 1;


static int
hash(char *s)
{
	int n = 0;

	for (; *s; s++)
		n += *s;

	return n % hash_size;
}


void
new_sort(sortname s, int sz)
{
	int i;

	construct *p = xmalloc_nof(construct, sz);

	for (i = 0; i < sz; i++) {
		(p + i)->sortnum = s;
		(p + i)->encoding = i;
		(p + i)->alias = NULL;
		(p + i)->ename = NULL;
		(p + i)->name = NULL;
		(p + i)->next = NULL;
		get_char_info(p + i) = NULL;
	}

	cons_table[s] = p;
	cons_sizes[s] = sz;
}


void
new_cons(char *nm, sortname s, int n, char *args)
{
	construct *p = cons_no(s, n);
	p->name = nm;

	if (add_to_cons_hash(p, s))
		fatal_error("Construct %s already defined", nm);

	get_char_info(p) = args;
}


static node *
de_dummy(void)
{
	fatal_error("Invalid decode function");
	return NULL;
}


static node *
read_dummy(long n)
{
	UNUSED(n);

	fatal_error("Invalid read function");
	return NULL;
}


void
init_tables(void)
{
	int i;

	/* Allocate tables */
	cons_table = xmalloc_nof(construct *, SORT_no);
	cons_sizes = xmalloc_nof(int, SORT_no);
	cons_hash_tables = xmalloc_nof(construct *, SORT_no * hash_size);
	var_table = xmalloc_nof(construct *, SORT_no);
	var_hash_tables = xmalloc_nof(construct *, SORT_no * hash_size);
	sort_count = xmalloc_nof(long, SORT_no);
	sort_letters = xmalloc_nof(char, SORT_no + 1);
	sort_encoding = xmalloc_nof(int, SORT_no);
	sort_extension = xmalloc_nof(int, SORT_no);
	sort_tokens = xmalloc_nof(long, SORT_no);
	sort_conds = xmalloc_nof(long, SORT_no);
	sort_removed = xmalloc_nof(long, SORT_no);
	sort_decode = xmalloc_nof(decode_func, SORT_no);
	sort_read = xmalloc_nof(read_func, SORT_no);

	/* Clear out tables */
	for (i = 0; i < SORT_no; i++) {
		cons_table[i] = NULL;
		cons_sizes[i] = 0;
		var_table[i] = NULL;
		sort_count[i] = 0;
		sort_letters[i] = 'F';
		sort_encoding[i] = 0;
		sort_extension[i] = 0;
		sort_tokens[i] = -2;
		sort_conds[i] = -2;
		sort_removed[i] = 0;
		sort_decode[i] = de_dummy;
		sort_read[i] = read_dummy;
	}

	sort_letters[SORT_no] = 0;

	/* Initialize construct hash tables */
	for (i = 0; i < SORT_no * hash_size; i++) {
		cons_hash_tables[i] = NULL;
		var_hash_tables[i] = NULL;
	}
}


char *
sort_name(sortname s)
{
	if (is_high(s)) {
		high_sort *h = high_sorts + high_no(s);
		return h->name;
	} else if (s == SORT_unknown || s < 0) {
		return "....";
	} else {
		construct *p = cons_no(SORT_sortname, s);
		return p->name;
	}
}


construct *
add_to_cons_hash(construct *p, sortname s)
{
	construct *q;
	int n = hash(p->name);
	construct *h = cons_hash_tables[hash_size * s + n];

	for (q = h; q != NULL; q = q->next)
		if (strcmp(p->name, q->name) == 0)
			return q;

	p->next = h;
	cons_hash_tables[hash_size * s + n] = p;

	return NULL;
}


construct *
search_cons_hash(char *p, sortname s)
{
	construct *q;
	int n = hash(p);
	construct *h = cons_hash_tables[hash_size * s + n];

	for (q = h; q != NULL; q = q->next)
		if (strcmp(p, q->name) == 0)
			return q;

	return NULL;
}


construct *
add_to_var_hash(construct *p, sortname s)
{
	construct *q;
	int n = hash(p->name);
	construct *h = var_hash_tables[hash_size * s + n];

	for (q = h; q != NULL; q = q->next)
		if (strcmp(p->name, q->name) == 0)
			return q;

	p->next = h;
	var_hash_tables[hash_size * s + n] = p;

	return NULL;
}


construct *
search_var_hash(char *p, sortname s)
{
	construct *q;
	int n = hash(p);
	construct *h = var_hash_tables[hash_size * s + n];

	for (q = h; q != NULL; q = q->next)
		if (strcmp(p, q->name) == 0)
			return q;

	return NULL;
}


void
remove_var_hash(char *p, sortname s)
{
	int n = hash(p);
	construct *h = var_hash_tables[hash_size * s + n];

	if (h == NULL)
		return;

	if (strcmp(p, h->name) == 0) {
		/* It is the first element */
		var_hash_tables[hash_size * s + n] = h->next;
		h->next = removals;
		removals = h;
		(sort_removed[s]) ++;

		return;
	}

	while (h->next) {
		if (strcmp(p, h->next->name) == 0) {
			/* It is a subsequent element */
			construct *q = h->next->next;

			h->next->next = removals;
			removals = h->next;
			h->next = q;
			(sort_removed[s]) ++;

			return;
		}

		h = h->next;
	}

	/* Not found */
}


/*
    The constructs of sort s in the hash table tab are sorted into
    alphabetical order.  They are formed into a list where the
    constructs with hash value 0 should be.  After sorting the hash
    table cannot be used.
*/

void
sort_table(construct **tab, sortname s)
{
	int i;
	construct *q = NULL;

	for (i = 0; i < hash_size; i++) {
		construct *p = tab[hash_size * s + i];
		tab[hash_size * s + i] = NULL;

		while (p) {
			construct *p_next = p->next;
			construct *r_last = NULL, *r = q;
			p->next = NULL;

			while (r && strcmp(r->name, p->name) < 0) {
				r_last = r;
				r = r->next;
			}

			if (r_last == NULL) {
				p->next = q;
				q = p;
			} else {
				r_last->next = p;
				p->next = r;
			}

			p = p_next;
		}
	}

	tab[hash_size * s] = q;
}


void
sort_all(void)
{
	if (order_names) {
		sort_table(var_hash_tables, SORT_al_tag);
		sort_table(var_hash_tables, SORT_tag);
		sort_table(var_hash_tables, SORT_token);
	}
}


void
apply_to_all(apply_func f, sortname s)
{
	int i;

	for (i = 0; i < hash_size; i++) {
		construct *p = var_hash_tables[hash_size * s + i];
		while (p) {
			construct *q = p->next;
			(*f)(p);
			p = q;
		}
	}
}
