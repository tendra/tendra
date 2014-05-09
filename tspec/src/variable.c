/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <time.h>
#include <string.h>

#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "utility.h"
#include "variable.h"

/*
 * CURRENT OBJECT
 *
 * This is the current object, which is affected by any file property
 * changes.
 */
object *crt_object = NULL;

/*
 * A human-readable descrption of the API's formal name.
 */
const char *api_info;

/*
 * SET A STRING VARIABLE
 *
 * This routine sets the string variable with identifier v to have value s.
 */
void
set_string(char *v, char *s)
{
	if (0 == strcmp(v, "$APINAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			i->api = s;
			i->prefix = NULL;
		}
	} else if (0 == strcmp(v, "$INFO")) {
		char *p;

		for (p = s; *p != '\0'; p++) {
			if (*p == ' ') {
				*p = '@'; /* for tcc */
			}
		}

		api_info = s;
	} else if (0 == strcmp(v, "$BLOCKNAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			if (*s) {
				i->block = hack_name(s, "_Aa0");
			} else {
				i->block = NULL;
			}
		}
	} else if (0 == strcmp(v, "$FILE")) {
		filename = s;
	} else if (0 == strcmp(v, "$FILENAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			i->file = s;
			i->prefix = NULL;
		}
	} else if (0 == strcmp(v, "$INCLNAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			if (*s) {
				char *dir = output_incl_dir;
				char *sub = NULL;
				i->incl = include_name(dir, i->api, s, sub);
			} else {
				i->incl = NULL;
			}
		}
	} else if (0 == strcmp(v, "$LINKAGE")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			if (*s) {
				i->linkage = s;
			} else {
				i->linkage = NULL;
			}
		}
	} else if (0 == strcmp(v, "$METHOD")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			i->method = s;
			if (i->src && 0 == strcmp(s, "TNC")) {
				int n = (int) strlen(i->src) - 1;
				i->src[n] = 'p';
			}
		}
	} else if (0 == strcmp(v, "$NAMESPACE")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			if (*s) {
				i->nspace = s;
			} else {
				i->nspace = NULL;
			}
		}
	} else if (0 == strcmp(v, "$PREFIX")) {
		if (crt_object) {
			crt_object->u.u_info->prefix = s;
		}
	} else if (0 == strcmp(v, "$PROTECT")) {
		if (crt_object) {
			crt_object->u.u_info->protect = s;
		}
	} else if (0 == strcmp(v, "$SOURCENAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			if (*s) {
				char *dir = output_src_dir;
				char *sub = NULL;
				i->src = src_name(dir, i->api, s, sub);
			} else {
				i->src = NULL;
			}
		}
	} else if (0 == strcmp(v, "$SUBSETNAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			i->subset = s;
			i->prefix = NULL;
		}
	} else if (0 == strcmp(v, "$VERSION")) {
		if (crt_object)crt_object->u.u_info->version = s;
	} else {
		error(ERROR_SERIOUS, "Unknown string variable, '%s'", v);
	}
}

/*
 * SET AN INTEGER VARIABLE
 *
 * This routine sets the integer variable with identifier v to have value n.
 */
void
set_integer(char *v, int n)
{
	if (0 == strcmp(v, "$INTERFACE")) {
		if (crt_object) {
			crt_object->u.u_info->tokens = (bool) n;
		}
	} else if (0 == strcmp(v, "$LINE")) {
		crt_line_no = n;
	} else if (0 == strcmp(v, "$UNIQUE")) {
		unique_names = (bool) n;
	} else if (0 == strcmp(v, "$VERBOSE")) {
		verbose = n;
	} else {
		error(ERROR_SERIOUS, "Unknown integer variable, '%s'", v);
	}
}

