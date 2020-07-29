/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/error.h>
#include <shared/string.h>
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
	if (streq(v, "$APINAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			i->api = s;
			i->prefix = NULL;
		}
	} else if (streq(v, "$INFO")) {
		char *p;

		for (p = s; *p != '\0'; p++) {
			if (*p == ' ') {
				*p = '@'; /* for tcc */
			}
		}

		api_info = s;
	} else if (streq(v, "$BLOCKNAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			if (*s) {
				i->block = hack_name(s, "_Aa0");
			} else {
				i->block = NULL;
			}
		}
	} else if (streq(v, "$FILE")) {
		filename = s;
	} else if (streq(v, "$FILENAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			i->file = s;
			i->prefix = NULL;
		}
	} else if (streq(v, "$INCLNAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			if (*s) {
				i->incl = include_name(i->api, s, NULL);
			} else {
				i->incl = NULL;
			}
		}
	} else if (streq(v, "$LINKAGE")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			if (*s) {
				i->linkage = s;
			} else {
				i->linkage = NULL;
			}
		}
	} else if (streq(v, "$METHOD")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			i->method = s;
			if (i->src && streq(s, "TNC")) {
				int n = (int) strlen(i->src) - 1;
				i->src[n] = 'p';
			}
		}
	} else if (streq(v, "$NAMESPACE")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			if (*s) {
				i->nspace = s;
			} else {
				i->nspace = NULL;
			}
		}
	} else if (streq(v, "$PREFIX")) {
		if (crt_object) {
			crt_object->u.u_info->prefix = s;
		}
	} else if (streq(v, "$PROTECT")) {
		if (crt_object) {
			crt_object->u.u_info->protect = s;
		}
	} else if (streq(v, "$SOURCENAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			if (*s) {
				i->src = src_name(i->api, s, NULL);
			} else {
				i->src = NULL;
			}
		}
	} else if (streq(v, "$SUBSETNAME")) {
		if (crt_object) {
			info *i = crt_object->u.u_info;
			i->subset = s;
			i->prefix = NULL;
		}
	} else if (streq(v, "$VERSION")) {
		if (crt_object)crt_object->u.u_info->version = s;
	} else {
		error(ERR_SERIOUS, "Unknown string variable, '%s'", v);
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
	if (streq(v, "$INTERFACE")) {
		if (crt_object) {
			crt_object->u.u_info->tokens = (bool) n;
		}
	} else if (streq(v, "$LINE")) {
		crt_line_no = n;
	} else if (streq(v, "$UNIQUE")) {
		unique_names = (bool) n;
	} else if (streq(v, "$VERBOSE")) {
		verbose = n;
	} else {
		error(ERR_SERIOUS, "Unknown integer variable, '%s'", v);
	}
}

