/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <time.h>
#include <stdlib.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <out/print.h>

#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "variable.h"
#include "utility.h"

struct dep {
	char *api;
	struct dep *next;
};

static int
dep_contains(const struct dep *deps, const char *api)
{
	const struct dep *p;

	for (p = deps; p != NULL; p = p->next) {
		if (streq(p->api, api)) {
			return 1;
		}
	}

	return 0;
}

static void
dep_populate(struct dep **deps, object *input)
{
	object *p = input->u.u_obj;
	info *i = p->u.u_info;

	for (p = i->elements; p != NULL; p = p->next) {
		char *api;

		switch (p->objtype) {
		case OBJ_SET:
		case OBJ_USE:
		case OBJ_IMPLEMENT:
			break;

		default:
			continue;
		}

		api = xstrdup(p->u.u_info->api);
		api[strcspn(api, ":")] = '\0';

		if (!dep_contains(*deps, api)) {
			struct dep *new;

			new = xmalloc(sizeof *new);
			new->api  = api;
			new->next = *deps;
			*deps = new;
		} else {
			free(api);
		}

		dep_populate(deps, p);
	}
}

static void
dep_print(FILE *f, const struct dep *deps)
{
	const struct dep *p;

	fprintf(f, "<LIB          \"");

	for (p = deps; p != NULL; p = p->next) {
		fprintf(f, "-l%s", basename(p->api));

		if (p->next != NULL) {
			fprintf(f, " ");
		}
	}

	fprintf(f, "\"\n");
}

static void
dep_free(struct dep *deps)
{
	struct dep *p, *next;

	for (p = deps; p != NULL; p = next) {
		next = p->next;

		free(p->api);
		free(p);
	}
}

void
print_env(object *input)
{
	struct dep *deps;
	const char *api;
	FILE *f;

	object *ss = input->u.u_obj;
	info *i = ss->u.u_info;

	api = basename(i->api);

	{
		char *nm = string_printf(ENV_FILE, output_dir, "env", api);

		create_dir(nm);
		if (verbose) {
			IGNORE printf("Creating environment %s ...\n", nm);
		}

		f = fopen(nm, "w");
		if (f == NULL) {
			error(ERR_SERIOUS, "Can't open output file, %s", nm);
			return;
		}

		free(nm);
	}

	deps = NULL;

	dep_populate(&deps, input);

	fprintf(f, "/*\n");
	fprintf(f, " * tcc environment for %s version %s\n", i->api, i->version);
	fprintf(f, " * Generated from %s by %s %s\n", ss->filename, progname, progvers);
	fprintf(f, " * Copyright terms for the input source also apply to this generated code.\n");
	fprintf(f, " */\n");
	fprintf(f, "\n");

	fprintf(f, "<INCL         \"-N%s:<PREFIX_TSPEC>/TenDRA/include/%s.api\"\n", i->api, i->api);
	fprintf(f, "+FLAG_INSTALL \"-Y%s\"\n", api);
	fprintf(f, "+API_NAME     \"-A%s\"\n", api);

	dep_print(f, deps);

	if (api_info != NULL) {
		fprintf(f, "+INFO         \"%s\"\n", api_info);
	}

	fprintf(f, "\n");

	dep_free(deps);

	fclose(f);
}

