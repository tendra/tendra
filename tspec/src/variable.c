/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
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
