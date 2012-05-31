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
#include <errno.h>

#include <shared/error.h>
#include <shared/string.h>

#include "config.h"
#include "filename.h"
#include "list.h"
#include "environ.h"
#include "flags.h"
#include "suffix.h"
#include "utility.h"
#include "hash.h"
#include "lexer.h"


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
 * READ AN ENVIRONMENT
 *
 * This routine reads the environment named nm, reporting an error if it is
 * unsuccessful.
 */

void
read_env(const char *nm)
{
	struct lexi_state state;
	FILE *f;

	/* note attempt to load -Y env file */
	environ_count++;

	/* Find the environment */
	if (*nm == 0) {
		error(ERROR_WARNING, "Empty environment name");
		return;
	}

	if (*nm == '/') {
		f = fopen(nm, "r");
		if (f == NULL) {
			error(ERROR_WARNING, "Can't open environment, '%s': %s",
				nm, strerror(errno));
		}
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
			if (f == NULL && errno != ENOENT) {
				error(ERROR_WARNING, "Can't open environment, '%s': %s",
					nm, strerror(errno));
			}

			if (f != NULL) {
				break;
			}
		}

		if (f == NULL) {
			error(ERROR_WARNING, "Can't find environment, '%s'", nm);
			return;
		}
	}

	assert(f != NULL);
	assert(nm != NULL);

	lex_init(&state, f);

	for (;;) {
		enum hash_order order;
		char *value;
		char *name;
		int op;
		int t;

		{
			op = lexi_read_token(&state);
			if (op == LEXI_EOF) {
				return;
			}

			switch (op) {
			case lex_prepend: order = HASH_PREPEND; break;
			case lex_append:  order = HASH_APPEND;  break;
			case lex_replace: order = HASH_ASSIGN;  break;

			default:
				error(ERROR_SERIOUS, "%s: Syntax error: expected operator", nm);
				return;
			}
		}

		{
			t = lexi_read_token(&state);
			if (t == LEXI_EOF) {
				error(ERROR_SERIOUS, "%s: Unexpected EOF", nm);
				return;
			}

			if (t != lex_name) {
				error(ERROR_SERIOUS, "%s: Syntax error: expected name", nm);
				return;
			}

			name = xstrdup(state.lex_state.buf);
		}

		{
			t = lexi_read_token(&state);
			if (t == LEXI_EOF) {
				error(ERROR_SERIOUS, "%s: Unexpected EOF", nm);
				return;
			}

			if (t != lex_string) {
				error(ERROR_SERIOUS, "%s: Syntax error: expected string", nm);
				return;
			}

			value = xstrdup(state.lex_state.buf);
		}

		envvar_set(&envvars, name, value, order, HASH_TCCENV);
	}
}

