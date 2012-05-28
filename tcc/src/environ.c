/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <shared/error.h>
#include <shared/string.h>

#include "config.h"
#include "filename.h"
#include "list.h"
#include "environ.h"
#include "flags.h"
#include "options.h"
#include "suffix.h"
#include "utility.h"
#include "hash.h"


/*
 * THE CURRENT ENVIRONMENTS PATH
 *
 * The environment path is a colon-separated list of directories which are
 * searched for tcc environments.
 */

static char *envpath = "";

/*
 * ENVIRONMENT
 *
 * This list carries the associative array of environment variables set through
 * environment files.
 */
struct hash *envvars;
int environ_count;


/*
 * UPDATE THE ENVIRONMENTS PATH
 *
 * This routine initialises and updates the environments path. This is given by
 * the contents of the system variable TCCENV, plus the default directory
 * (environ_dir), plus the current directory.
 */

void
find_envpath(void)
{
	char *p = buffer;
	char *tcc_env = getenv(TCCENV_VAR);
	if (tcc_env) {
		IGNORE sprintf(p, "%s:", tcc_env);
		p += strlen(p);
	}
	IGNORE sprintf(p, "%s", environ_dir);
	if (!streq(buffer, envpath)) {
		envpath = xstrdup(buffer);
	}
}


/*
 * PRINT THE ENVIRONMENTS PATH
 *
 * This routine prints the environment path.
 */

void
show_envpath(void)
{
	find_envpath();
	printf("Environment path is '%s'", envpath);
}


/*
 * READ AN ENVIRONMENT - AUXILIARY ROUTINE
 *
 * This routine reads the environment named nm, returning zero if it is
 * successful. A return value of 1 indicates that the environment could not be
 * found, otherwise 2 is returned.
 *
 * In the revision to this function, the strategy is to minimize copying chars.
 * This routine opens the file, and examines each env file a line at a time.
 * Line analysis scans past the key, until the first whitespace is found. Then,
 * the routine scans forward to the start of the value, and cut the line buffer
 * in half by making the whitespace a '\0' character. The routine continues
 * scanning the value, performing appropriate substitutions for <vars>.
 *
 * TODO: The two resulting strings in the buffer (key and value) must be
 * strdup'd. A future revision to this function may just read entire file into
 * memory, and convert key whitespace to NULL characters, thereby breaking up
 * the lines into appropriate tokens, and avoiding copying strings around in
 * memory.
*/

static int
read_env_aux(const char *nm, struct hash **h)
{
	FILE *f;
	int   line_num;

	assert(nm != NULL);
	assert(h != NULL);

	/* Find the environment */
	if (*nm == 0) {
		return 1;
	} else if (*nm == '/') {
		f = fopen(nm, "r");
	} else {
		const char *s;
		const char *e;

		s = envpath;

		for (e = s; *s != '\0'; s = e + (e == s)) {
			e = s + strcspn(s, ":");

			if (e == s) {
				continue;
			}

			IGNORE sprintf(buffer, "%.*s/%s", (int) (e - s), s, nm);

			f = fopen(buffer, "r");
			if (f != NULL) {
				break;
			}
		}
	}

	if (f == NULL) {
		return 1;
	}

	/*
	 * Parse each line of the environment file
	 */
	line_num = 0;

	while (fgets(buffer, buffer_size, f) != NULL) {
		char  c;          /* temporary character */
		char *p;          /* current pointer to scan buffer */
		char *key_start;  /* points to +, <, > start of key */
		int   key_length; /* length of key */
		char *val_start;  /* start of value associated with key */
		char *val_end;    /* end of value */
		int   count;      /* counter to stop scan at buffer_size */
		int   line_len;   /* length of this buffer */
		char *end = NULL; /* end of line */

		line_len = strlen(buffer);
		count = 1;
		p = buffer;
		c = *p++;
		line_num++;

		/* Only process lines beginning with these characters */
		/* TODO: do we really want to silently ignore other non-empty lines? */
		if (c != '<' && c != '>' && c != '+' && c != '?') {
			continue;
		}

		key_start = p - 1;
		key_length = 0;
		while (c = *p++, is_alphanum(c)) {
			if (count++ == buffer_size) {
				error(ERROR_FATAL, "%s: line %d: Exceeded max line size",
					nm, line_num);
			}
			key_length++;
		}

		/* mark off key from val */
		*(p - 1) = '\0';

		/* skip over spacing between key and value */
		/* TODO: strcspn */
		while (c == ' ' || c == '\t') {
			c = *p++;
			if (count++ == buffer_size) {
				error(ERROR_FATAL, "%s: line %d: Exceeded max line size",
					nm, line_num);
			}
		}

		/* sanity check */
		if (c == '\0') {
			error(ERROR_WARNING, "%s: line %d: No value assigned to key %s",
			  nm, line_num, key_start);
			continue;
		}

		/* All values assigned to a key must be in quotes */
		if (c != '"') {
			error(ERROR_WARNING, "%s: line %d: Value assigned to key %s must be quoted",
				nm, line_num, key_start);
			continue;
		}

		val_start = p;

		/* remove leading quotation mark from val */
		*(val_start - 1) = ' ';

		/* read the value, until the matching close quote */
		while (c = *p++, (c != '"' && c != '\n' && c != '\0')) {
			int   diff;      /* difference between two lengths */
			char *esc_start; /* start of substituion field, always a '<' */
			char *esc_end;   /* end of susbtitution field, always a '>' */
			int   esc_len;   /* number of chars to escape over */

			if (count++ == buffer_size) {
				error(ERROR_FATAL, "%s: line %d: Exceeded max line size",
				  nm, line_num);
			}

			if (c != '<') {
				continue;
			}

			/* mark start of <> sequence */
			esc_start = p - 1;
			esc_len   = 2; /* accounts for <, > */

			/* expand quote */
			while (c = *p++, c != '>') {
				esc_len++;

				if (count++ == buffer_size) {
					error(ERROR_FATAL, "%s: line %d: Exceeded max line size",
					  nm, line_num);
				}

				if (c == '\n' || c == '\0') {
					error(ERROR_FATAL, "%s: line %d: Unmatched escape sequence, missing >",
					  nm, line_num);
				}

				if (c == '<') {
					error(ERROR_FATAL, "%s: line %d: Nested < > escape sequences prohibited",
					  nm, line_num);
					continue;
				}
			}

			/* mark end of <> sequence */
			esc_end = p - 1;

			{
				const char *sub; /* character substitution for escape sequences */
				int   sub_len;   /* length of substitution */
				int   shift_max; /* amount to move */
				char *pivot;     /* where to start shifting */
				int   delta;     /* direction of growth */

				/*
				 * find a substitution; all error handling done in function
				 */
				sub = envvar_dereference(*h, esc_start + 1, esc_end, nm, line_num);
	
				/* find length of substitution */
				sub_len = strlen(sub);
	
				/* do we grow or shrink */
				diff = sub_len - esc_len;
	
				/* find the number of characters that must be moved */
				shift_max = strlen(esc_end);
	
				if (!end) {
					end = buffer + line_len;
				}
	
				if (diff > 0) {
					/* grow */
					pivot = end;
					delta = -1;
				} else {
					/* shrink */
					delta = 1;
					pivot = esc_end + 1;
				}
	
				/* adjust end pointers and length counters */
				end      += diff;
				line_len += diff;
				count    += diff;
				if (count == buffer_size) {
					error(ERROR_FATAL, "%s: line %d: Exceeded max line size",
					  nm, line_num);
				}
	
				/* TODO: memmove and memcpy instead */
				{
					int cnt;

					/* make room for the substitution */
					for (cnt = 0; cnt < shift_max; cnt++){
						pivot[cnt * delta + diff] = pivot[cnt * delta];
					}
	
					/* perform subsitution on resized line */
					for (cnt = 0; cnt < sub_len; cnt++) {
						esc_start[cnt] = sub[cnt];
					}
				}
			}

			/* advance our scanning pointer */
			p = esc_end + diff;
		}

		/* did we end the val scan on new line or EOF? */
		if (c == '\n' || c == '\0') {
			error(ERROR_WARNING, "%s: line %d: Value assigned to key %s"
			   " not terminated with end quote",
			   nm, line_num, key_start);
			continue;
		}

		/* mark end of the value */
		val_end = p - 1;

		/* set close quote to null */
		*val_end = '\0';

		{
			char *cmd;
			enum hash_order order;

			/* build the command string */
			cmd = string_append(key_start, val_start, ' ');

			order = *key_start;
			key_start++;
			val_start = cmd + key_length + 1 + 1;

			/*
			 * If the key/value pair is a tccenv variable, it's a finished
			 * command, and should be executed.
			 */
			if (~envvar_flags(*h, key_start) & HASH_USR) {
				list dummy;

				/* process the command */
				dummy.s = cmd;
				dummy.next = NULL;
				process_options(&dummy, environ_optmap, HASH_TCCENV);
			}

			/* update envvars with new key/value pair*/
			envvar_set(h, key_start, val_start, order, HASH_TCCENV);
		}
	}

	return 0;
}


/*
 * READ AN ENVIRONMENT
 *
 * This routine reads the environment named nm, reporting an error if it is
 * unsuccessful.
 */

void
read_env(const char *nm)
{
	int e;

	/* note attempt to load -Y env file */
	environ_count++;

	e = read_env_aux(nm, &envvars);
	if (e == 1) {
		error(ERROR_WARNING, "Can't find environment, '%s'", nm);
	}
}
