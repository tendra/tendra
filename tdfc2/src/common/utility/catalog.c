/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include "config.h"

#include "c_types.h"
#include "exp_ops.h"
#include "str_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "hash.h"
#include "lex.h"
#include "literal.h"
#include "syntax.h"
#include "ustring.h"
#include "xalloc.h"


/*
    The error catalogue definition is automatically generated.  It consists
    of an array of ERR_DATA structures, ERR_CATALOG.
*/

#include "errors3.h"


/*
    This value gives the number of errors in the error catalogue.
*/

#define CATALOG_SIZE	array_size(ERR_CATALOG)
unsigned catalog_size = (unsigned)CATALOG_SIZE;


/*
    This hash table is used to hold the names of the various errors in
    the error catalogue.
*/

typedef struct err_hash_tag {
	int number;
	ERR_DATA *entry;
	struct err_hash_tag *next;
} ERR_HASH;

#define HASH_ERROR	128
static ERR_HASH *error_hash[HASH_ERROR + 1];
static ERR_HASH *all_error_hash = NULL;


/*
    This routine initialises the error hash table.
*/

static void
init_err_hash(void)
{
	int i;
	ERR_DATA *cat = ERR_CATALOG;
	ERR_HASH *err = xmalloc_nof(ERR_HASH, CATALOG_SIZE);
	all_error_hash = err;
	for (i = 0; i <= HASH_ERROR; i++) {
		error_hash[i] = NULL;
	}
	for (i = 0; i < CATALOG_SIZE; i++) {
		unsigned long h;
		const char *s = cat->name;
		if (s) {
			h = hash(ustrlit(s));
			h %= HASH_ERROR;
		} else {
			h = HASH_ERROR;
		}
		err->number = i;
		err->entry = cat;
		err->next = error_hash[h];
		error_hash[h] = err;
		cat++;
		err++;
	}
	return;
}


/*
    This routine finds the error number corresponding to the string literal
    expression s.  n gives a likely value to try first.  It returns -1 if
    s is not the name of a known error.
*/

int
find_error_no(STRING s, int n)
{
	unsigned kind = DEREF_unsigned(str_simple_kind(s));
	if (kind == STRING_NONE) {
		ERR_HASH *err;
		unsigned long h;
		string text = DEREF_string(str_simple_text(s));
		ulong len = DEREF_ulong(str_simple_len(s));
		if (n >= 0 && n < CATALOG_SIZE) {
			string nm = ustrlit(ERR_CATALOG[n].name);
			if (nm && ustreq(text, nm)) {
				if (len == (ulong)ustrlen(nm)) {
					return n;
				}
			}
		}
		if (all_error_hash == NULL) {
			init_err_hash();
		}
		h = hash(text);
		h %= HASH_ERROR;
		for (err = error_hash[h]; err != NULL; err = err->next) {
			string nm = ustrlit(err->entry->name);
			if (nm && ustreq(text, nm)) {
				if (len == (ulong)ustrlen(nm)) {
					return err->number;
				}
			}
		}
	}
	return -1;
}


/*
    This routine sets the severity level of error number n to the error
    severity corresponding to the option number opt.
*/

void
set_error_sev(int n, int opt)
{
	if (n >= 0 && n < CATALOG_SIZE) {
		ERR_CATALOG[n].usage = opt;
	}
	return;
}


/*
    Certain technical terms vary slightly between C and C++.  This routine
    looks up the term corresponding to the lexical token number t in the
    current language.  The default is the normal lexical token name.
*/

string
find_vocab(int t)
{
	const char *s = token_names[t];
#if LANGUAGE_C
	switch (t) {
	case lex_class:
		s = "struct/union"; break;
	}
#endif
	return ustrlit(s);
}


/*
    This routine initialises the error catalogue.
*/

void
init_catalog(void)
{
	assert(OPT_error == 0);
	return;
}


/*
    This routine terminates the error catalogue.
*/

void
term_catalog(void)
{
	xfree_nof(all_error_hash);
	all_error_hash = NULL;
	return;
}
