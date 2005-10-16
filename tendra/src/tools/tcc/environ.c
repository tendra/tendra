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


#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "config.h"
#include "cstring.h"
#include "msgcat.h"

#include "filename.h"
#include "list.h"
#include "environ.h"
#include "flags.h"
#include "options.h"
#include "suffix.h"
#include "utility.h"


/*
 *  THE CURRENT ENVIRONMENTS PATH
 *
 *  The environment path is a colon-separated list of directories which
 *  are searched for tcc environments.
 */

static char *envpath = ".";


/*
 *  UPDATE THE ENVIRONMENTS PATH
 *
 *  This routine initialises and updates the environments path.  This is
 *  given by the contents of the system variable TCCENV, plus the default
 *  directory (environ_dir), plus the current directory.
 */

void
find_envpath(void)
{
	char *p = buffer;
	char *tcc_env = getenv (TCCENV_VAR);
	if (tcc_env) {
		IGNORE sprintf (p, "%s:", tcc_env);
		p += strlen (p);
	}
	IGNORE sprintf (p, "%s:.", environ_dir);
	if (!streq (buffer, envpath))
		envpath = string_copy (buffer);
	return;
}


/*
 *  PRINT THE ENVIRONMENTS PATH
 *
 *  This routine prints the environment path.
 */

void
show_envpath(void)
{
	find_envpath ();
	MSG_environment_path_is (envpath);
	return;
}


/*
 *  READ AN ENVIRONMENT - AUXILIARY ROUTINE
 *
 *  This routine reads the environment named nm, returning zero if it
 *  is successful.  A return value of 1 indicates that the environment
 *  could not be found, otherwise 2 is returned.
 *
 *  In the revision to this function, the strategy is to minimize
 *  copying chars.  This routine opens the file, and examines each env
 *  file a line at a time.  Line analysis scans past the key, until
 *  the first whitespace is found.  Then, the routine scans forward to
 *  the start of the value, and cut the line buffer in half by making
 *  the whitespace a '\0' character.  The routine continues scanning
 *  the value, performing appropriate substitutions for <vars>.
 *
 *  TODO: The two resulting strings in the buffer (key and value) must
 *  be strdup'd.  A future revision to this function may just read
 *  entire file into memory, and convert key whitespace to NULL
 *  characters, thereby breaking up the lines into appropriate tokens,
 *  and avoiding copying strings around in memory.
 */

int
read_env_aux(char *nm, hashtable *ht)
{
	/* Find the environment */
	FILE *f;
	char *p, *q;
	int  line_num;

	if (*nm == 0) {
		return (1);
	} else if (*nm == '/') {
		f = fopen (nm, "r");
	} else {
		p = envpath;
		do {
			q = buffer;
			while (*p && *p != ':') {
				*(q++) = *(p++);
			}
			*(q++) = '/';
			IGNORE strcpy (q, nm);
			f = fopen (buffer, "r");
		} while (f == null && *(p++));
	}
	if (f == null)
		return (1);
	/*
	 *  Parse each line of the env file
	 */
	line_num = 0;

	while (fgets (buffer, buffer_size, f) != null)
	{
		char c;          /* temp char */
		char *p;         /* current pointer to scan buffer */
		char *key_start; /* points to +, <, > start of key */
		int  key_length; /* length of key */
		char *val_start; /* start of value associated with key */
		char *val_end;   /* end of value */
		char *esc_start; /* start of substitution field, always a '<' */
		char *esc_end;   /* end of substitution field, always a '>' */
		int  esc_len;    /* number of chars to escape over */
		char *sub;       /* character substitution for escape
							sequences */
		int  count;      /* counter to stop scan at buffer_size */
		int  line_len;   /* length of this buffer */
		char *end = NULL;       /* end of line */
		char *cmd;       /* final command string being built */
		list  dummy;     /* final command */
		htnode* hn;      /* wrapper for command storage */

		line_len = strlen(buffer);
		count = 1;
		p = buffer;
		c = *p++;
		line_num++;
		if (c == '<' || c == '>' || c == '+' || c == '?') {
			key_start = (p-1);
			key_length = 0;
			while (c = *p++, is_alphanum(c)) {
				if (count++ == buffer_size)
					MSG_exceeded_max_line_size (nm, line_num);
				key_length++;
			}

			/* mark off key from val */
			*(p-1) = '\0';

			/* skip over spacing between key and value */
			while (c==' ' || c == '\t') {
				c = *p++;
				if (count++ == buffer_size)
					MSG_exceeded_max_line_size (nm, line_num);
			}

			/* sanity check */
			if (c== '\0') {
				MSG_no_value_assigned_to_key (nm, line_num, key_start);
				continue;
			}

			/* All values assigned to a key must be in quotes */
			if (c != '"') {
				MSG_value_assigned_to_key_must_be_quoted (nm, line_num, key_start);
				continue;
			}
			val_start = p;

			/* remove leading quotation mark from val */
			*(val_start-1) = ' ';

			/* read the value, until the matching close quote */
			while (c = *p++, (c != '"' && c != '\n' && c != '\0')) {
				if (count++ == buffer_size)
					MSG_exceeded_max_line_size (nm, line_num);

				if (c=='<') {
					int sub_len;    /* length of substitution */
					int diff;       /* difference between two lengths */
					int delta;      /* direction of growth */
					int cnt;        /* counter */
					int shift_max;  /* amount to move */
					char *pivot;    /* where to start shifting */

					/* mark start of <> sequence */
					esc_start = (p-1);
					esc_len = 2; /* accounts for <, > */

					/* expand quote */
					while (c = *p++, c!= '>') {
						esc_len++;
						if (count++ == buffer_size)
							MSG_exceeded_max_line_size (nm, line_num);
						if (c== '\n' || c== '\0') {
							MSG_unmatched_escape_sequence_missing_ra (nm, line_num);
						}
						if (c== '<') {
							MSG_nested_la_ra_escape_sequences_prohibited (nm, line_num);
							continue;
						}
					}

					/* mark end of <> sequence */
					esc_end = (p-1);

					/* find a substitution; all error handling done in
					   function */
					sub = dereference_var(esc_start+1, esc_end, ht,
										  nm, line_num);

					/* find length of substitution */
					sub_len = strlen(sub);

					/* do we grow or shrink */
					diff = (sub_len - esc_len);

					/* find the number of characters that must be
					   moved */
					shift_max = strlen (esc_end);

					if (!end)
						end = (buffer + line_len);

					if (diff > 0) { /* grow */
						pivot = end;
						delta = -1;
					}
					else { /* shrink */
						delta = 1;
						pivot = esc_end + 1;
					}

					/* adjust end pointers and length counters */
					end += diff;
					line_len += diff;
					count += diff;
					if (count == buffer_size)
						MSG_exceeded_max_line_size (nm, line_num);

					/* make room for the substitution */
					for (cnt = 0; cnt < shift_max; cnt++) {
						*(pivot + (cnt * delta) + diff) =
							*(pivot + (cnt * delta));
					}

					/* perform substitution on resized line */
					for (cnt = 0; cnt < sub_len; cnt++)
						*(esc_start + cnt) = sub[cnt];

					/* advance our scanning pointer */
					p = esc_end + diff;

				} /* if escape '<' sequence */

			} /* while *p != '"' */

			/* did we end the val scan on new line or EOF? */
			if (c=='\n' || c=='\0') {
				MSG_value_assigned_to_key_not_terminated_with_end_quote
					   (nm, line_num, key_start);
				continue;
			}

			/* mark end of the value */
			val_end = (p-1);

			/* set close quote to null */
			*(val_end) = '\0';

			/* build the command string */
			cmd = string_append (key_start, val_start, ' ');
			key_start = string_copy (key_start);
			val_start = (cmd + key_length + 2);

			/* if the key/value pair is a tccenv variable, it's
			   a finished command, and should be executed */
			hn = lookup_table(ht, key_start);
			if (hn && (hn->flag & TCCENV))
			{
				/* process the command */
				dummy.item = cmd;
				dummy.next = null;
				process_options (&dummy, environ_optmap, 1);
			}

			/* update hashtable with new key/value pair*/
			hn = update_table(ht, key_start, val_start,
							  USR, nm, line_num);

		} /* if the line is a +, >, < env action command */

	} /* for each line in the env file */
	return (0);
} /* read_env_aux() */


/*
 *  Lookup value for tccenv(5) variables.  This function takes in an
 *  escape sequence from an env file, and attempts to find a
 *  definition.  For example, <TENDRA_BASEDIR> may be passed in, and
 *  be mapped to the value supplied previously by -y arguments.
 *
 *  The function looks up TENDRA_* variables first, since they are so
 *  common.  The TENDRA_* variable resolution also consults the shell
 *  environment, if no -y argument or +TENDRA_* declaration was given
 *  in an env file.  Failing that, the function consults the hash
 *  table of tccenv key/value mappings.  This function performs
 *  all error handling; it will return a valid char *, or fail.
 */
char *
dereference_var(char *esc_start, char *esc_end, hashtable *ht,
				 char *nm, int line_num)
{
	htnode* hn;
	char *sub = NULL;
	/* temporarily replace '>' with '\0' to facilitate lookup */
	char tmp = *esc_end;
	*esc_end = '\0';

	/*   Attempt to match TENDRA_* env arguments,
		 which are most likely to occur. */
	if (!strncmp ("TENDRA", esc_start, 6)) {
		sub = find_path_subst(esc_start);
	}

	/* If we fail to find a TENDRA_* env match, look
	   up in hashtable */
	if (!sub)
	{
		hn = lookup_table(ht, esc_start);
		if (hn == NULL)
		{
			*esc_end = tmp;
			MSG_undefined_variable_in_file (esc_start, nm, line_num);
		}
		sub = hn->val;
	}
	*esc_end = tmp;
	return sub;
}


int environ_count;
hashtable *environ_hashtable;

/*
 *   Reconcile the table of user-defined env options.  At present this
 *   function just makes sure that non-tccenv(5) variables declared by
 *   the user were used in the env files.  If not, it's likely a
 *   subtle bug or typo, and a warning issues if the version -v switch
 *   is used.
 *
 *   Future revisions may also attempt to supply definitions to hash
 *   keys that were not found during the O(N) initial pass through the
 *   env files.  (That is, the env reading would be O(2N), and attempt
 *   to finding all possible definitions, including those out of
 *   order.)
 */

void
reconcile_envopts(void)
{
	int i;
	htnode *hn;

	/* If no -Y args were given whatsoever, give a warning, since a
	 *  mysterious internal error ("tcc: Internal: The tool
	 *  'C_producer' is not available'") is about to follow during the
	 *  execute stage.  This mistake is so fundamental, we give a
	 *  warning even without verbose being set.
	 */
	if (environ_count == 0)
	{
		MSG_not_invoked_with_any_Yenv_arguments ();
 	}

	/* All subsequent warnings require a verbose flag */
	if (!verbose)
		return;

	/* If the global env table is NULL, no -Y args succeeded, or none
	   were given */
	if (!environ_hashtable)
	{
		/* -Y args given, but failed */
		if (environ_count > 0)
			MSG_failed_to_load_any_environment_files ();
		return;
	}

	for (i = 0; i < TCC_TBLSZE; i++)
	{
		hn = environ_hashtable->node[i];
		if (hn &&  (hn->flag & USR)  &&
			!(hn->flag & READ))
			MSG_environment_option_declared_but_never_used (hn->file, hn->line_num, hn->key);
	}
}


/*
 *  READ AN ENVIRONMENT
 *
 *  This routine reads the environment named nm, reporting an error if
 *  it is unsuccessful.
 */

void
read_env(char *nm)
{
	int e;
	static hashtable *ht;

	/* note attempt to load -Y env file */
	environ_count++;

	if (ht == NULL)
	{
		ht = init_table (TCC_TBLSZE, TCC_KEYSZE, &hash);
		environ_hashtable = ht; /* hack */
	}
	e = read_env_aux(nm, ht);
	if (e == 1)
		MSG_cant_find_environment (nm);
	return;
}
