/*
 * Copyright (c) 2002, 2003, 2004 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * This code is derived from software contributed to The TenDRA Project by
 * Jeroen Ruigrok van der Werven.
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


#include "config.h"
#include <ctype.h>
#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "utility.h"
#include "variable.h"


/*
    STANDARD FLAGS

    These flags are set by the command-line options and determine the
    action of the program.
*/

boolean allow_long_long = 0;
boolean force_output = 0;
boolean local_input = 0;
boolean restrict_depth = 1;
boolean restrict_use = 0;
boolean unique_names = 0;
int verbose = 0;


/*
    FIND THE BASENAME OF A FILE NAME

    This routine returns the basename (i.e. just the final component) of
    the filename nm.
*/

char *
basename(char *nm)
{
    char *b = nm;
    for (; *nm; nm++) {
	if (*nm == '/')b = nm + 1;
    }
    return(b);
}


/*
    FIND THE DIRECTORY COMPONENT OF A FILE NAME

    This routine returns a copy of the directory component of the filename
    nm.
*/

char *
dirname(char *nm)
{
    char *p, *end = null;
    char *dir = string_copy(nm);
    for (p = dir; *p; p++) {
	if (*p == '/')end = p;
    }
    if (end == null || end == dir) return(null);
    *end = 0;
    return(dir);
}


/*
    FIND A RELATIVE PATHNAME

    This routine prints the relative pathname from the file from to the
    file to, ignoring the first n characters.
*/

char *
relative(char *from, char *to, int n)
{
    char *s = buffer;
    if (from == null) return(to);
    if (to == null) return(from);
    for (from = from + n; *from; from++) {
	if (*from == '/') {
	    IGNORE strcpy(s, "../");
	    s += 3;
	}
    }
    IGNORE strcpy(s, to + n);
    return(buffer);
}


/*
    HACK A NAME

    This routine hacks the name nm according to the given key.
*/

char *
hack_name(char *nm, char *key)
{
    char *p = string_copy(nm), *q;
    for (q = p; *q; q++) {
	char c = *q;
	if (isalpha(c) && isupper(c)) {
	    /* The second letter of key maps upper case letters */
	    if (key [1] == 'a')*q = (char)tolower(c);
	} else if (isalpha(c) && islower(c)) {
	    /* The third letter of key maps lower case letters */
	    if (key [2] == 'A')*q = (char)toupper(c);
	} else if (isdigit(c)) {
	    /* The fourth letter of key maps digits */
	    *q = (char)(c - '0' + key [3]);
	} else if (strchr(key + 4, c)) {
	    /* The rest of key gives special characters */
	} else {
	    /* The first letter of key is the default */
	    *q = key [0];
	}
    }
    return(p);
}


/*
    FIND A TOKEN NAME

    This routine makes up a token name for an object named nm.  If
    unique_names is false this is just nm, otherwise it is prefixed by
    a string depending on the current input file.
*/

char *
token_name(char *nm)
{
    if (strneq(nm, HIDDEN_NAME, HIDDEN_LEN)) {
	nm = string_concat("~", nm + HIDDEN_LEN);
    }
    if (unique_names && crt_object) {
	info *i = crt_object->u.u_info;
	char *pfx = i->prefix;
	if (pfx == null) {
	    pfx = token_prefix(i->api, i->file, i->subset);
	    i->prefix = pfx;
	}
	if (*pfx) return(string_printf("%s.%s", pfx, nm));
    }
    return(nm);
}


/*
    FIND TOKEN PREFIX

    This routine finds the token prefix for the API subset api:file:subset.
*/

char *
token_prefix(char *api, char *file, char *subset)
{
    UNUSED(subset);
    if (unique_names) {
	int n;
	if (file == null) return(api);
	IGNORE sprintf(buffer, "%s.%s", api, basename(file));
	n = (int)strlen(buffer) - 2;
	if (n >= 0 && buffer [n] == '.')buffer [n] = 0;
	return(hack_name(buffer, "_Aa0."));
    }
    return(null);
}


/*
    FIND A SUBSET NAME

    This routine finds the name associated with the API subset with API
    api, header file and subset subset.
*/

char *
subset_name(char *api, char *file, char *subset)
{
    char *sn;
    if (subset) {
	char *f = (file ? file : "");
	sn = string_printf("%s:%s:%s", api, f, subset);
    } else if (file) {
	sn = string_printf("%s:%s", api, file);
    } else {
	sn = string_printf("%s", api);
    }
    return(sn);
}


/*
    FIND AN INCLUDE OUTPUT FILE NAME

    This routine finds the include output file name for the API subset
    api:file:subset using the directory dir as a base.
*/

char *
include_name(char *dir, char *api, char *file, char *subset)
{
    char *nm;
    if (subset) {
	char s [20];
	IGNORE strncpy(s, subset, 18);
	s [ OUTPUT_LENGTH ] = 0;
	nm = string_printf(OUTPUT_SUBSET, dir, api, s);
    } else if (file) {
	nm = string_printf(OUTPUT_FILE, dir, api, file);
    } else {
	nm = string_printf(OUTPUT_API, dir, api);
    }
    return(nm);
}


/*
    FIND A SOURCE OUTPUT FILE NAME

    This routine finds the source output file name for the API subset
    api:file:subset using the directory dir as a base.
*/

char *
src_name(char *dir, char *api, char *file, char *subset)
{
    char *nm;
    if (subset) {
	char s [20];
	IGNORE strncpy(s, subset, 18);
	s [ OUTPUT_LENGTH ] = 0;
	nm = string_printf(SOURCE_SUBSET, dir, api, s);
    } else if (file) {
	int n;
	nm = string_printf(SOURCE_FILE, dir, api, basename(file));
	n = (int)strlen(nm) - 4;
	if (n >= 0 && streq(nm + n, ".h.c")) {
	    IGNORE strcpy(nm + n, ".c");
	}
    } else {
	nm = string_printf(SOURCE_API, dir, api);
    }
    return(nm);
}


/*
    FIND A MACRO NAME

    This routine finds the protection (or other) macro for the API subset
    api:file:subset using the macro prefix pfx.
*/

char *
macro_name(char *pfx, char *api, char *file, char *subset)
{
    if (subset) {
	char *f = (file ? file : "");
	IGNORE sprintf(buffer, "%s_%s_%s_%s", pfx, api, f, subset);
    } else if (file) {
	IGNORE sprintf(buffer, "%s_%s_%s", pfx, api, file);
    } else {
	IGNORE sprintf(buffer, "%s_%s", pfx, api);
    }
    return(hack_name(buffer, "_AA0"));
}


/*
    FIND A DECLARATION BLOCK NAME

    This routine finds the declaration block name for the API subset
    api:file:subset.
*/

char *
block_name(char *api, char *file, char *subset)
{
    char * pfx = (subset ? "subset" : "api");
    if (file) {
	int len;
	IGNORE sprintf(buffer, "%s__%s__%s", pfx, api, file);
	/* remove any trailing ".h" */
	len = (int)strlen(buffer);
	if (streq(buffer + len - 2, ".h"))
	    buffer [ len - 2 ] = '\0';
    } else {
	IGNORE sprintf(buffer, "%s__%s", pfx, api);
    }
    return(hack_name(buffer, "_Aa0"));
}
