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

hashtable*
init_table(int tblsize, int keysize, int (*hashfcn) (char*, int, int))
{
	int i;
	hashtable* ht;
	optmap *t;
	ht = malloc (sizeof (hashtable));
	ht->tblsize = tblsize;
	ht->keysize = keysize;
	ht->hashfcn = hashfcn;
	ht->node = malloc(sizeof (htnode*) * tblsize);
	for (i = 0; i < tblsize; i++)
	{
		ht->node[i] = NULL;
	}
	for (t = environ_optmap; t->in != NULL; t++)
	{
		/* initialize hash table with tccenv keys */
		update_table (ht, t->in, NULL, TCCENV, NULL, -1);
	}
	return ht;
}

int
key_match(char *key, char *keyfield)
{
	int i;
	if (!key || !keyfield)
		return 0;
	/* advance pointers past command chars */
	while (*key && !is_alphanum(*key))
		key++;
	while (*keyfield && !is_alphanum(*keyfield))
		keyfield++;
	for (i=0; i < strlen(key); i++)
		if (key[i] != keyfield[i]) {
			return 0;
		}
	return 1;
}

htnode *
lookup_table (hashtable *ht, char *key)
{
	int  hashval;
	htnode *hn;

	if (! key) {
		MSG_looking_up_null_key_in_tccenv_hashtable ();
		return NULL;
	}
	hashval = ht->hashfcn (key, ht->tblsize, ht->keysize);
	hn = ht->node[hashval];
	while (hn != NULL && !key_match(key, hn->key))
	{
		hn = hn->next;
	}
	if (hn)
	{
		hn->flag |= READ;
	}
	return hn;
}

htnode*
update_table(hashtable *ht, char *key, char *val, unsigned int flag,
			 char *file, int line_num)
{
	int hashval;
	htnode *hn;
	hashval = ht->hashfcn (key, ht->tblsize, ht->keysize);
	hn = ht->node[hashval];
	/* locate matching node */
	while (hn != NULL && !key_match(key, hn->key))
	{
		hn = hn->next;
	}

	/* Case 1.  Node was not found; push */
	if (hn == NULL)
	{
		hn = malloc (sizeof (htnode));
		hn->flag = flag;
		hn->key  = key;
		hn->val  = val;
		hn->file = file;
		hn->line_num = line_num;
		hn->next = ht->node[hashval];
		ht->node[hashval] = hn;
	}
	else /* Case 2.  Update */
	{
		if (!val)
			hn->val = NULL;
		else
		{
			switch (*key)
			{
			case '+': /* assignment */
				hn->val = val;
				break;

			case '>': /* append */
				if (hn->val)
					hn->val = string_append (hn->val, val, ' ');
				hn->val = val;
				break;

			case '<': /* prepend */
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
	while (*key && !(is_alphanum(*key)))
	{
		key++;
	}

	if (!key)
	{
		MSG_hash_operation_requested_on_empty_key ();;
	}
	while (*key && !is_whitespace(*key) && i < keysize)
	{
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
 *  Substitution variables.  This is Table 5.
 *
 */
char *PATH_SUBS[] = {
	"TENDRA_MACHDIR",
	"TENDRA_BINDIR",
	"TENDRA_ENVDIR",
	"TENDRA_LIBDIR",
	"TENDRA_INCLDIR",
	"TENDRA_STARTUPDIR",
	"TENDRA_TMPDIR",
	"TENDRA_BASEDIR",
	NULL
};

size_t PATH_SUBS_elems = ARRAY_SIZE (PATH_SUBS);


/*
 *  Takes in a substitution variable as an argument, and returns its
 *  corresponding value.  This routine is used by the env substitution
 *  function (see format_path) to map variables to paths.
 *
 *  For example, input is "<TCCDIR_BASE>", and return value
 *  is "/usr/local/share/".  Variable lookup is prioritized:
 *
 *     a)  command line args have highest priority,
 *     b)  environment variables are used next,
 *     c)  for a select group of variables, sane defaults are
 *          used.
 */
char*
find_path_subst (char *var)
{
	char *ret;
	char **subs;
	int i = 0;

	subs = PATH_SUBS;
	while (*subs){
		if (!strcmp (var, *subs)) {
			if (env_paths[i] == NULL){
				MSG_env_variable_is_null (PATH_SUBS[i]);
			}
 			return env_paths[i];
		}
		i++;
		subs++;
	}
	if (!*subs)
		MSG_expected_y_option (var);
	ret = getenv (var);

	/* Perhaps this should not be fatal? */
	if (!ret)
		MSG_unknown_environment_variable (var);
	return ret;
}




/*
 *    TEMPORARY WORK SPACE
 *
 *    This variable gives a temporary work space of size buffer_size
 *    (see utility.h) which is used as a scratch work area.
 */

char *buffer;
