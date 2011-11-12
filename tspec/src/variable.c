/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include <shared/error.h>
#include <shared/xalloc.h>

#include "config.h"
#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "utility.h"
#include "variable.h"


/*
    CURRENT OBJECT

    This is the current object, which is affected by any file property
    changes.
*/

object *crt_object = NULL;


/*
    SET A STRING VARIABLE

    This routine sets the string variable with identifier v to have value s.
*/

void
set_string(char *v, char *s)
{
    boolean known = 0;
    switch (v [1]) {
	case 'A': {
	    if (strcmp(v, "$APINAME") == 0) {
		if (crt_object) {
		    info *i = crt_object->u.u_info;
		    i->api = s;
		    i->prefix = NULL;
		}
		known = 1;
	    }
	    break;
	}
	case 'B': {
	    if (strcmp(v, "$BLOCKNAME") == 0) {
		if (crt_object) {
		    info *i = crt_object->u.u_info;
		    if (*s) {
			i->block = hack_name(s, "_Aa0");
		    } else {
			i->block = NULL;
		    }
		}
		known = 1;
	    }
	    break;
	}
	case 'F': {
	    if (strcmp(v, "$FILE") == 0) {
		filename = s;
		known = 1;
	    } else if (strcmp(v, "$FILENAME") == 0) {
		if (crt_object) {
		    info *i = crt_object->u.u_info;
		    i->file = s;
		    i->prefix = NULL;
		}
		known = 1;
	    }
	    break;
	}
	case 'I': {
	    if (strcmp(v, "$INCLNAME") == 0) {
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
		known = 1;
	    }
	    break;
	}
	case 'L': {
	    if (strcmp(v, "$LINKAGE") == 0) {
		if (crt_object) {
		    info *i = crt_object->u.u_info;
		    if (*s) {
			i->linkage = s;
		    } else {
			i->linkage = NULL;
		    }
		}
		known = 1;
	    }
	    break;
	}
	case 'M': {
	    if (strcmp(v, "$METHOD") == 0) {
		if (crt_object) {
		    info *i = crt_object->u.u_info;
		    i->method = s;
		    if (i->src && strcmp(s, "TNC") == 0) {
			int n = (int)strlen(i->src) - 1;
			i->src [n] = 'p';
		    }
		}
		known = 1;
	    }
	    break;
	}
	case 'N': {
	    if (strcmp(v, "$NAMESPACE") == 0) {
		if (crt_object) {
		    info *i = crt_object->u.u_info;
		    if (*s) {
			i->nspace = s;
		    } else {
			i->nspace = NULL;
		    }
		}
		known = 1;
	    }
	    break;
	}
	case 'P': {
	    if (strcmp(v, "$PREFIX") == 0) {
		if (crt_object)crt_object->u.u_info->prefix = s;
		known = 1;
	    } else if (strcmp(v, "$PROTECT") == 0) {
		if (crt_object)crt_object->u.u_info->protect = s;
		known = 1;
	    }
	    break;
	}
	case 'S': {
	    if (strcmp(v, "$SOURCENAME") == 0) {
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
		known = 1;
	    } else if (strcmp(v, "$SUBSETNAME") == 0) {
		if (crt_object) {
		    info *i = crt_object->u.u_info;
		    i->subset = s;
		    i->prefix = NULL;
		}
		known = 1;
	    }
	    break;
	}
	case 'V': {
	    if (strcmp(v, "$VERSION") == 0) {
		if (crt_object)crt_object->u.u_info->version = s;
		known = 1;
	    }
	    break;
	}
    }
    if (!known)error(ERROR_SERIOUS, "Unknown string variable, '%s'", v);
    return;
}


/*
    SET AN INTEGER VARIABLE

    This routine sets the integer variable with identifier v to have value n.
*/

void
set_integer(char *v, int n)
{
    boolean known = 0;
    switch (v [1]) {
	case 'I': {
	    if (strcmp(v, "$INTERFACE") == 0) {
		if (crt_object) {
		    crt_object->u.u_info->tokens = (boolean)n;
		}
		known = 1;
	    }
	    break;
	}
	case 'L': {
	    if (strcmp(v, "$LINE") == 0) {
		crt_line_no = n;
		known = 1;
	    }
	    break;
	}
	case 'U': {
	    if (strcmp(v, "$UNIQUE") == 0) {
		unique_names = (boolean)n;
		known = 1;
	    }
	    break;
	}
	case 'V': {
	    if (strcmp(v, "$VERBOSE") == 0) {
		verbose = n;
		known = 1;
	    }
	    break;
	}
    }
    if (!known)error(ERROR_SERIOUS, "Unknown integer variable, '%s'", v);
    return;
}
