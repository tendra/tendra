/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */

#include <assert.h>
#include <stdarg.h>

#include "config.h"
#include "cstring.h"
#include "msgcat.h"

#include "options.h"
#include "list.h"
#include "flags.h"
#include "main.h"
#include "suffix.h"
#include "utility.h"
#include "environ.h"


/*
 *    HASH TABLE
 *
 *    These functions provide access to a hash table of tccenv(5)
 *    keys and values.  When created, the hash table is populated
 *    with tccenv keys taken from the environ_optmap[] array, and
 *    flaged as tccenv-derived instead of user-created.
 */

hashtable *
init_table(int tblsize, int keysize, int (*hashfcn) (char*, int, int))
{
	int i;
	hashtable* ht;
	optmap *t;
	ht = malloc (sizeof(*ht));
	ht->tblsize = tblsize;
	ht->keysize = keysize;
	ht->hashfcn = hashfcn;
	ht->node = malloc(tblsize * sizeof(*ht->node));
	for (i = 0; i < tblsize; i++) {
		ht->node[i] = NULL;
	}
	for (t = environ_optmap; t->in != NULL; t++) {
		/* initialize hash table with tccenv keys */
		update_table (ht, t->in, NULL, TCCENV, NULL, -1);
	}
	return ht;
}

static int
key_match(char *key, char *keyfield)
{
	if (!key || !keyfield)
		return 0;
	/* advance pointers past command chars */
	while (*key && !is_alphanum(*key))
		key++;
	while (*keyfield && !is_alphanum(*keyfield))
		keyfield++;
	return strncmp (key, keyfield, strlen (key)) == 0;
}

htnode *
lookup_table(hashtable *ht, char *key)
{
	int  hashval;
	htnode *hn;

	if (! key) {
		MSG_looking_up_null_key_in_tccenv_hashtable ();
		return NULL;
	}
	hashval = ht->hashfcn (key, ht->tblsize, ht->keysize);
	hn = ht->node[hashval];
	while (hn != NULL && !key_match(key, hn->key)) {
		hn = hn->next;
	}
	if (hn) {
		hn->flag |= READ;
	}
	return hn;
}

htnode *
update_table(hashtable *ht, char *key, char *val, unsigned int flag,
			 char *file, int line_num)
{
	int hashval;
	htnode *hn;
	hashval = ht->hashfcn (key, ht->tblsize, ht->keysize);
	hn = ht->node[hashval];
	/* locate matching node */
	while (hn != NULL && !key_match(key, hn->key)) {
		hn = hn->next;
	}

	/* Case 1.  Node was not found; push */
	if (hn == NULL) {
		hn = malloc (sizeof(*hn));
		hn->flag = flag;
		hn->key  = key;
		hn->val  = val;
		hn->file = file;
		hn->line_num = line_num;
		hn->next = ht->node[hashval];
		ht->node[hashval] = hn;
	}
	else /* Case 2.  Update */ {
		if (!val)
			hn->val = NULL;
		else {
			switch (*key) {
			case ACTION_REPLACE:
				hn->val = val;
				break;

			case ACTION_APPEND:
				if (hn->val)
					hn->val = string_append (hn->val, val, ' ');
				hn->val = val;
				break;

			case ACTION_PREPEND:
				if (hn->val)
					hn->val = string_append (val, hn->val, ' ');
				hn->val = val;
				break;

			default:
				/* this should never happend, since read_env_aux
				   screens for this */
				MSG_attempt_to_update_hashtable_with_invalid_key
					(key);
			}
		}

	}
	return hn;
}

/*
 *  Hash function.  The function takes in a char * to a key,
 *  presumed to be in the form of <cmd><tccenv_var>, e.g.,
 *  "+AS /usr/bin/as".  The hash calculated skips over the
 *  leading command char, either +, <, >, or ?.
 */
int
hash(char *key, int tblsize, int keysize)
{
	int i = 1;
	int hashval = 0;

	/* skip leading +, <, >, ?, / chars */
	while (*key && !(is_alphanum(*key))) {
		key++;
	}

	if (!key) {
		MSG_hash_operation_requested_on_empty_key ();
	}
	while (*key && !is_whitespace(*key) && i < keysize) {
		hashval += (hashval * 37) + (int) *key;
		key++;
		i++;
	}

	hashval %= tblsize;
	if (hashval < 0)
		hashval += tblsize;
	return hashval;
}

/*
 *    PRINT A COMMENT
 *
 *    This routine prints the comment s (a printf-style string, which
 *    may be followed by any number of arguments) to the standard output.
 */

void
comment(int e, char *s, ...) /* VARARGS */
{
	FILE *f;
	va_list args;
	va_start (args, s);
	f = (e ? stdout : stderr);
	IGNORE fflush (f);
	IGNORE vfprintf (f, s, args);
	IGNORE fflush (f);
	va_end (args);
	return;
}


/*
 *  TENDRA variables.  This is Table 5.
 */

static struct {
	const char *var;
	char *value;
} tendra_paths [] = {
	{ "TENDRA_MACHDIR", NULL },
	{ "TENDRA_BINDIR", NULL },
	{ "TENDRA_ENVDIR", NULL },
	{ "TENDRA_LIBDIR", NULL },
	{ "TENDRA_INCLDIR", NULL },
	{ "TENDRA_STARTUPDIR", NULL },
	{ "TENDRA_TMPDIR", NULL },
	{ "TENDRA_BASEDIR", NULL },
};


/*
 *  GET A TENDRA PATH VARIABLE
 *
 *  Takes in a TENDRA variable name as an argument, and returns its
 *  corresponding value.  This routine is used by the dereference_var
 *  function to map variables to paths.
 *
 *  For example, input is "TENDRA_LIBDIR", and return value
 *  is "/usr/local/lib/TenDRA/lib".  Variable lookup is prioritized:
 *
 *     a)  command line arguments have highest priority,
 *     b)  environment variables (from environment files) are used next,
 *     c)  and finally getenv() is queried. 
 */

char *
get_tendra_var(char *var)
{
	char *ret;
	unsigned i;

	for (i = 0; i < ARRAY_SIZE (tendra_paths); i++) {
		if (streq (var, tendra_paths [i].var)) {
			if (tendra_paths [i].value != NULL)
				return (tendra_paths [i].value);
			break;
		}
	}
	/* Ignore other variables starting with TENDRA */
	if (i == ARRAY_SIZE (tendra_paths))
		return (NULL);

	MSG_expected_y_option (var);
	ret = getenv (var);
	/* Perhaps this should not be fatal? */
	if (ret == NULL)
		MSG_unknown_environment_variable (var);
	return (ret);
}


/*
 *  SET A TENDRA PATH VARIABLE
 *
 *  This function sets the variable var to a copy of value.  If the variable
 *  does not exist, it returns 0 for failure, otherwise 1.
 */

int
set_tendra_var(const char *var, char *value)
{
	unsigned i;

	for (i = 0; i < ARRAY_SIZE (tendra_paths); i++) {
		if (streq (var, tendra_paths [i].var)) {
			tendra_paths [i].value = string_copy (value);
			return (1);
		}
	}
	return (0);
}


/*
 *  SET A TENDRA PATH VARIABLE
 *
 *  This function is used to set a TENDRA_ variable from an environment
 *  file.  The first character is a digit specifying the variable's index in
 *  the tendra_paths array, the rest is the new value.
 */

void
set_tendra_var_env(char *arg)
{
	unsigned index = arg [0] - '0';
	assert (index < ARRAY_SIZE (tendra_paths));

	if (tendra_paths [index].value == NULL)
		tendra_paths [index].value = arg + 1;
}


/*
 *    TEMPORARY WORK SPACE
 *
 *    This variable gives a temporary work space of size buffer_size
 *    (see utility.h) which is used as a scratch work area.
 */

char *buffer;
