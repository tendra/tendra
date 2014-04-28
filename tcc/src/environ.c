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
#include "list.h"
#include "options.h"


/*
 * ENVIRONMENT
 *
 * This list carries the associative array of environment variables set through
 * environment files.
 */
struct hash *envvars;


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

		s = envvar_get(envvars, "ENVPATH");

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
			op = lexi_next(&state);
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
			t = lexi_next(&state);
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
			t = lexi_next(&state);
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

		/* +FLAG is a special case */
		if (0 == strcmp(name, "FLAG")) {
			list *opts;

			/* TODO: only permit the order to be HASH_APPEND */

			opts = make_list(value);
			process_options(opts, main_optmap, HASH_TCCENV);
			free_list(opts);

			continue;
		}

		envvar_set(&envvars, name, value, order, HASH_TCCENV);
	}
}

