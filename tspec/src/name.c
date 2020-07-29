/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "utility.h"
#include "variable.h"

#include <shared/string.h>

/*
 * STANDARD FLAGS
 *
 * These flags are set by the command-line options and determine the
 * action of the program.
 */
bool basename_apis  = 0;
bool force_output   = 0;
bool local_input    = 0;
bool restrict_depth = 1;
bool restrict_use   = 0;
bool unique_names   = 0;
int verbose         = 0;

/*
 * FIND THE BASENAME OF A FILE NAME
 *
 * This routine returns the basename (i.e. just the final component) of
 * the filename nm.
 */
char *
basename(char *nm)
{
    char *b = nm;

    for ( ; *nm != '\0'; nm++) {
		if (*nm == '/') {
			b = nm + 1;
		}
    }

    return b;
}

/*
 * STRIP A TSPEC EXTENSION
 *
 * This routine strips the ".ts" extension from a given name, if present,
 * and returns a copy sans-extension.
 *
 * This routine leaks memory; it is a hack. A better approach would be to
 * deal with the prefix during opening of files, rather than removing it
 * during code generation output.
 */
char *
strip_extension(char *nm)
{
    const char ext[] = ".ts";
    char *s;
    char *p;

    if (nm == NULL) {
		return NULL;
    }

    s = xstrdup(nm);

    p = strstr(s, ext);
    if (p == NULL) {
		/* There is no ".ts" extension */
		return s;
    }

    if (p[strlen(ext)] != '\0') {
		/* ".ts" is not the end of the string */
		return s;
    }

    *p = '\0';

    return s;
}

/*
 * FIND THE DIRECTORY COMPONENT OF A FILE NAME
 *
 * This routine returns a copy of the directory component of the filename
 * nm.
 */
char *
dirname(char *nm)
{
    char *p, *end = NULL;
    char *dir = xstrdup(nm);

    for (p = dir; *p != '\0'; p++) {
		if (*p == '/') {
			end = p;
		}
    }

    if (end == NULL || end == dir) {
		return NULL;
	}

    *end = 0;

    return dir;
}

/*
 * HACK A NAME
 *
 * This routine hacks the name nm according to the given key.
 */
char *
hack_name(char *nm, char *key)
{
    char *p = xstrdup(nm), *q;

    for (q = p; *q != '\0'; q++) {
		int c = *q;

		if (isalpha(c) && isupper(c)) {
			/* The second letter of key maps upper case letters */
			if (key[1] == 'a') {
				*q = (char) tolower(c);
			}
		} else if (isalpha(c) && islower(c)) {
			/* The third letter of key maps lower case letters */
			if (key[2] == 'A') {
				*q = (char) toupper(c);
			}
		} else if (isdigit(c)) {
			/* The fourth letter of key maps digits */
			*q = (char) (c - '0' + key[3]);
		} else if (strchr(key + 4, c)) {
			/* The rest of key gives special characters */
		} else {
			/* The first letter of key is the default */
			*q = key[0];
		}
    }

    return p;
}

/*
 * FIND A TOKEN NAME
 *
 * This routine makes up a token name for an object named nm.  If
 * unique_names is false this is just nm, otherwise it is prefixed by
 * a string depending on the current input file.
 */
char *
token_name(char *nm)
{
    if (strncmp(nm, HIDDEN_NAME, HIDDEN_LEN) == 0) {
		nm = xstrcat("~", nm + HIDDEN_LEN);
    }

    if (unique_names && crt_object) {
		info *i = crt_object->u.u_info;
		char *pfx = i->prefix;

		if (pfx == NULL) {
			pfx = token_prefix(i->api, i->file, i->subset);
			i->prefix = pfx;
		}

		if (*pfx != '\0') {
			return string_printf("%s.%s", pfx, nm);
		}
    }

    return nm;
}

/*
 * FIND TOKEN PREFIX
 *
 * This routine finds the token prefix for the API subset api:file:subset.
 */
char *
token_prefix(char *api, char *file, char *subset)
{
	int n;

    UNUSED(subset);

    if (!unique_names) {
		return NULL;
	}

	if (file == NULL) {
		return api;
	}

	IGNORE sprintf(buffer, "%s.%s", api, strip_extension(basename(file)));
	n = (int) strlen(buffer) - 2;
	if (n >= 0 && buffer [n] == '.') {
		buffer [n] = 0;
	}

	return hack_name(buffer, "_Aa0.");
}

/*
 * FIND A SUBSET NAME
 *
 * This routine finds the name associated with the API subset with API
 * api, header file and subset subset.
 */
char *
subset_name(char *api, char *file, char *subset)
{
    char *sn;

    if (subset != NULL) {
		char *f = (file ? strip_extension(file) : "");
		sn = string_printf("%s:%s:%s", api, f, subset);
    } else if (file != NULL) {
		sn = string_printf("%s:%s", api, strip_extension(file));
    } else {
		sn = string_printf("%s", api);
    }

    return sn;
}

/*
 * FIND AN INCLUDE OUTPUT FILE NAME
 *
 * This routine finds the include output file name for the API subset
 * api:file:subset using the directory dir as a base.
 */
char *
include_name(char *api, char *file, char *subset)
{
    char *nm;
    char *dir;

    if (subset != NULL) {
        dir = "subset";
    } else {
        dir = "include";
    }

    if (subset != NULL) {
		char s[20];
		IGNORE strncpy(s, subset, 18);
		s[OUTPUT_LENGTH] = 0;
		nm = string_printf(OUTPUT_SUBSET, output_dir, dir, api, s);
    } else if (file != NULL) {
		nm = string_printf(OUTPUT_FILE, output_dir, dir, api, strip_extension(file));
    } else {
		nm = string_printf(OUTPUT_API, output_dir, dir, api);
    }

    return nm;
}

/*
 * FIND A SOURCE OUTPUT FILE NAME
 *
 * This routine finds the source output file name for the API subset
 * api:file:subset using the directory dir as a base.
 */
char *
src_name(char *api, char *file, char *subset)
{
    char *nm;
    char *dir = "src";

    if (subset != NULL) {
		char s[20];
		IGNORE strncpy(s, subset, 18);
		s[OUTPUT_LENGTH] = 0;
		nm = string_printf(SOURCE_SUBSET, output_dir, dir, api, s);
    } else if (file != NULL) {
		int n;
		nm = string_printf(SOURCE_FILE, output_dir, dir, api, strip_extension(basename(file)));
		n = (int) strlen(nm) - 4;
		if (n >= 0 && streq(nm + n, ".h.c")) {
			IGNORE strcpy(nm + n, ".c");
		}
    } else {
		nm = string_printf(SOURCE_API, output_dir, dir, api);
    }

    return nm;
}

/*
 * FIND A MACRO NAME
 *
 * This routine finds the protection (or other) macro for the API subset
 * api:file:subset using the macro prefix pfx.
 */
char *
macro_name(char *pfx, char *api, char *file, char *subset)
{
    if (subset != NULL) {
		char *f = file ? strip_extension(file) : "";
		IGNORE sprintf(buffer, "%s_%s_%s_%s", pfx, api, f, subset);
    } else if (file != NULL) {
		IGNORE sprintf(buffer, "%s_%s_%s", pfx, api, strip_extension(file));
    } else {
		IGNORE sprintf(buffer, "%s_%s", pfx, api);
    }

    return hack_name(buffer, "_AA0");
}

/*
 * FIND A DECLARATION BLOCK NAME
 *
 * This routine finds the declaration block name for the API subset
 * api:file:subset.
 */
char *
block_name(char *api, char *file, char *subset)
{
	char * pfx = subset ? "subset" : "api";

	if (file != NULL) {
		int len;

		IGNORE sprintf(buffer, "%s__%s__%s", pfx, api, strip_extension(file));
		/* remove any trailing ".h" */
		len = (int) strlen(buffer);
		if (streq(buffer + len - 2, ".h")) {
			buffer[len - 2] = '\0';
		}
	} else {
		IGNORE sprintf(buffer, "%s__%s", pfx, api);
	}

	return hack_name(buffer, "_Aa0");
}

