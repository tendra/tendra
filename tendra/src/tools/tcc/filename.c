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


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "filename.h"
#include "list.h"
#include "flags.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"
#include "table.h"


/*
 * CASE SENSITIVITY FLAG
 *
 * This flag may be set to true to make tcc ignore case in filename suffixes.
 */

boolean case_insensitive = 0;


/*
 * CONVERT A STRING TO LOWER CASE
 *
 * This routine converts the string s to lower case.
 */

static void
to_lower_case(char *s)
{
	char c;
	while (c = *s, c != 0) {
		*s = (char) tolower(c);
		s++;
	}
	return;
}


/*
 * FILE STORAGE LOCATIONS
 *
 * Output files may be stored either in the temporary directory, tempdir, or
 * the work directory, workdir.
 */

const char *tempdir = NULL;
const char *workdir = NULL ;


/*
 * FIND THE BASE NAME OF A FILE
 *
 * This routine returns the basename of the file name s.
 */
/* TODO use basename() */

const char *
find_basename(const char *s)
{
	const char *r = s;
	for (; *s; s++) {
		if (*s == '/')r = s + 1;
	}
	return(r);
}


/*
 * FIND THE FULL NAME OF A FILE
 *
 * This routine returns the full name of the file name s.
 */

const char *
find_fullname(const char *s)
{
	static const char *pwd = NULL;
	if (*s == '/') {
		return (s);
	}
	if (pwd == NULL) {
		if (getcwd(buffer, buffer_size)) {
			pwd = string_concat(buffer, "/");
		} else {
			error(WARNING,
			      "Can't determine current working directory");
			pwd = "";
		}
	}
	return (string_concat(pwd, s));
}


/*
 * SPLIT OFF THE SUFFIX OF A FILE NAME
 *
 * This routine splits the file name s into two part, the base part and the
 * file suffix, and returns the latter.
 */

static char *
split_name(char *s)
{
	int i, n = (int)strlen(s);
	for (i = n - 1; i >= 0; i--) {
		if (s[i] == '.') {
			s[i] = 0;
			if (case_insensitive) {
				/* Allow for case insensitive systems */
				to_lower_case(s + (i + 1));
			}
			return (s + (i + 1));
		}
	}
	return ("");
}


/*
 * CREATE A NEW FILENAME
 *
 * This routine allocates a new filename structure.
 */

static filename *
new_filename(void)
{
	static int no_free = 0;
	static filename *free_objs = NULL;
	if (no_free == 0) {
		no_free = 1000;
		free_objs = alloc_nof(filename, no_free);
	}
	return (free_objs + (--no_free));
}


/*
 * ADD A FILENAME TO A LIST
 *
 * This routine joins the two filename lists, p and q, returning the result.
 */

filename *
add_filename(filename *p, filename *q)
{
	filename *r;
	if (p == NULL) {
		return (q);
	}
	if (q == NULL) {
		return (p);
	}
	for (r = p; r->next != NULL; r = r->next) {
		;	/* empty */
	}
	r->next = q;
	return (p);
}


/*
 * CONVERT A SUFFIX KEY LETTER TO A FILE TYPE
 *
 * This routine converts the letter s, which is a file suffix, to a file type.
 * This routine needs to be kept in step with Table 1 and Table 2.
 */
/* TODO keys ought perhaps to be an enum, and thus s not a char */

enum filetype
find_type_suffix(char s)
{
	enum filetype t;

	t = table_findbykey(s);
	if (t == UNKNOWN_TYPE) {
		error(SERIOUS, "Unknown file type, '%c'", s);
		return UNKNOWN_TYPE;
	}

	/* TODO: perhaps overkill to put this in filetype_table */
	if (table_stage(t)) {
		return DEFAULT_TYPE;
	}

	if (checker && !table_checker(t)) {
		return DEFAULT_TYPE;
	}

	return t;
}


/*
 * CONVERT A STAGE IDENTIFIER KEY LETTER TO A FILE TYPE
 *
 * This routine converts the letter s, which is a stage identifier, to a file
 * type. This routine needs to be kept in step with Table 1 and Table 2.
 */
/* TODO keys ought perhaps to be an enum, and thus s not a char */

enum filetype
find_type_stage(char s)
{
	enum filetype t;

	if (s == ALL_KEY) {
		return ALL_TYPES;
	}

	t = table_findbykey(s);

	if (checker && !table_checker(t)) {
		error(SERIOUS, "File type '%c' non-applicable for the checker", s);
		return UNKNOWN_TYPE;
	}

	if (t == UNKNOWN_TYPE) {
		error(SERIOUS, "Unknown file type, '%c'", s);
		return UNKNOWN_TYPE;
	}

	return t;
}


/*
 * FIND A FILE SUFFIX
 *
 * This routine converts a file type, t, into the corresponding file suffix. It
 * needs to be kept in step with Table 1 and Table 2.
 */
/* TODO Have this search table.h instead. We can probably eliminate keys in favour of strings */

static char *
file_suffix(int t)
{
	static char suff[3];
	suff[0] = 0;
	suff[1] = 0;
	suff[2] = 0;
	/* TODO: rearrange for simplicity */
	switch (t) {
	case C_SOURCE:
		suff[0] = table_key(C_SOURCE);
		break;
	case PREPROC_C:
		suff[0] = table_key(PREPROC_C);
		break;
	case CPP_SOURCE:
		suff[0] = table_key(CPP_SOURCE);
		break;
	case PREPROC_CPP:
		suff[0] = table_key(PREPROC_CPP);
		break;
	case INDEP_TDF:
		suff[0] = table_key(INDEP_TDF);
		break;
	case INDEP_TDF_AUX:
		suff[0] = table_key(INDEP_TDF);
		suff[1] = EXTRA_KEY;
		break;
	case DEP_TDF:
		suff[0] = table_key(DEP_TDF);
		break;
	case AS_SOURCE:
		suff[0] = table_key(AS_SOURCE);
		break;
	case BINARY_OBJ:
		suff[0] = table_key(BINARY_OBJ);
		break;
	case BINARY_OBJ_AUX:
		if ((use_sparc_cc == 1) && use_system_cc) {
			suff[0] = '.';
			suff[1] = table_key(BINARY_OBJ);
		} else {
			suff[0] = table_key(BINARY_OBJ_AUX);
		}
		break;
	case PRETTY_TDF:
		suff[0] = table_key(PRETTY_TDF);
		break;
	case PL_TDF:
		suff[0] = table_key(PL_TDF);
		break;
	case MIPS_G_FILE:
		suff[0] = table_key(MIPS_G_FILE);
		break;
	case MIPS_T_FILE:
		suff[0] = table_key(MIPS_T_FILE);
		break;
	case C_SPEC:
		suff[0] = table_key(C_SPEC);
		break;
	case CPP_SPEC:
		suff[0] = table_key(CPP_SPEC);
		break;
	}
	if (suff[0]) {
		if (case_insensitive && isupper(suff[0])) {
			/* Make allowances for case insensitive systems */
			/* TODO do we really care to support case-insensitive filesystems? */
			to_lower_case(suff);
			suff[1] = suff[0];
		}
		return (suff);
	}
	error(SERIOUS, "Illegal file type");
	return (file_suffix(DEFAULT_TYPE));
}


/*
 * NEXT FILENAME IS ACTUALLY AN INPUT OPTION
 *
 * Some command-line options, for example, system libraries, are treated like
 * input files. This flag is set to indicate that the next input file is
 * actually an input option.
 */

boolean option_next = 0;


/*
 * COUNT OF NUMBER OF INPUT FILES
 *
 * The number of calls to find_filename is recorded. Input options are excluded
 * from this count.
 */

int no_input_files = 0;


/*
 * ALLOCATE A NEW UNIQUE IDENTIFIER
 *
 * Each file is assigned a unique number which identifies it and all the files
 * derived from it. This macro assigns a new unique number.
 */

static int uniq_no = 0;
#define new_unique()	(uniq_no++)


/*
 * CREATE A FILENAME FROM A PATHNAME
 *
 * This routine creates a new filename structure, corresponding to the file
 * with name s and type t. If t is UNKNOWN_TYPE then the actual file type is
 * deduced from the file suffix. This routine needs to be kept in step with
 * Table 1, Table 2 and Table 3.
 */
/* TODO have this search table.h instead */

filename *
find_filename(const char *s, enum filetype t)
{
	filename *p = new_filename();
	char *b = string_copy(find_basename(s));
	char *e = split_name(b);

	/* Find the file type */
	/* TODO rewrite the logic here */
	if (suffix_overrides && t == UNKNOWN_TYPE) {
		enum filetype i;

		for (i = 0; i < TYPE_ARRAY_SIZE; i++) {
			if (table_suffix(i)!= NULL && streq(e, table_suffix(i))) {
				if (checker) {
					/* TODO perhaps we can categorise checkable and non-checkable types */
					if (i == PL_TDF || i == TDF_ARCHIVE) {
						continue;
					}
				}
				t = i;
				break;
			}
		}
	}
	/* TODO this is silly */
	if (t == UNKNOWN_TYPE) {
		if (e[0]) {
			if (e[1]) {
				if (e[2]) {
					/* Length >= 3 */
					if (streq(e, CPP_2_SUFFIX)) {
						t = CPP_SOURCE;
					} else if (streq(e, PREPROC_CPP_2_SUFFIX)) {
						t = PREPROC_CPP;
					} else if (streq(e, AS_2_SUFFIX)) {
						t = AS_SOURCE;
					} else {
						t = DEFAULT_TYPE;
					}
				} else {
					/* Length == 2 */
					if (e[1] == EXTRA_KEY) {
						t = find_type_suffix(e[0]);
					} else if (streq(e, CPP_1_SUFFIX)) {
						t = CPP_SOURCE;
					} else if (streq(e, PREPROC_CPP_1_SUFFIX)) {
						t = PREPROC_CPP;
					} else if (streq(e, CPP_SPEC_1_SUFFIX)) {
						t = CPP_SPEC;
					} else if (checker) {
						t = DEFAULT_TYPE;
					} else if (streq(e, PL_TDF_SUFFIX)) {
						t = PL_TDF;
					} else if (streq(e, TDF_ARCHIVE_SUFFIX)) {
						t = TDF_ARCHIVE;
					} else {
						t = DEFAULT_TYPE;
					}
				}
			} else {
				/* Length == 1 */
				t = find_type_suffix(e[0]);
			}
		} else {
			/* Length == 0 */
			t = DEFAULT_TYPE;
		}
	}

	/* Return the result */
	p->name = s;
	p->bname = b;
	p->uniq = new_unique();
	p->type = t;
	if (option_next) {
		p->storage = INPUT_OPTION;
		option_next = 0;
	} else {
		p->storage = INPUT_FILE;
		no_input_files++;
	}
	p->final = 0;
	p->aux = NULL;
	p->next = NULL;
	return (p);
}


/*
 * FIND WHERE TO STORE FILES OF A GIVEN TYPE
 *
 * This routine returns the storage class for files of type t. Note that this
 * may be PRESERVED_FILE which is only a legal storage type when it is passed
 * to make_filename (which turns it into OUTPUT_FILE).
 */
/* TODO silly name */
int
where(enum filetype t)
{
	if (!table_keep(t)) {
		return (TEMP_FILE);
	}
	if (!table_stop(t)) {
		return (PRESERVED_FILE);
	}
	return (OUTPUT_FILE);
}


/*
 * CREATE A FILENAME FROM ANOTHER FILENAME
 *
 * This routine creates a new filename structure by forming the file derived
 * from p which has type t and storage s.
 */
/* TODO have this search table.h instead */

filename *
make_filename(filename *p, enum filetype t, enum file_storage s)
{
	boolean f = 0;
	char *e;
	const char *d;
	const char *b = NULL;
	const char *nm = NULL;
	filename *q = new_filename();

	/* Examine the storage class */
	switch (s) EXHAUSTIVE {
	case INPUT_FILE:
	case INPUT_OPTION:
		/* This shouldn't occur */
		d = NULL;
		break;
	case OUTPUT_FILE:
		/* Check output file name */
		if (final_name) {
			static boolean used_final_name = 0;
			if (used_final_name) {
				error(WARNING,
				      "Can only name one file with '-o'");
			} else {
				nm = final_name;
				b = find_basename(nm);
#ifdef EXECUTABLE_SUFFIX
				if (t == EXECUTABLE &&
				    strchr(b, '.') == NULL) {
					/* Add '.exe' suffix if necessary */
					nm = string_concat(nm,
							   EXECUTABLE_SUFFIX);
					b = string_concat(b, EXECUTABLE_SUFFIX);
				}
#endif
				used_final_name = 1;
				f = 1;
			}
		}
		d = workdir;
		break;
	case PRESERVED_FILE:
		/* Preserved files are turned into output files */
		d = workdir;
		s = OUTPUT_FILE;
		break;
	case TEMP_FILE:
		/* Temporary files */
		d = tempdir;
		break;
	}

	/* Find the file name */
	if (nm == NULL) {
		if (p != NULL && p->type == t) {
			nm = find_basename(p->name);
			if (d != NULL) {
				IGNORE sprintf(buffer, "%s/%s", d, nm);
				nm = string_copy(buffer);
			}
			b = p->bname;
		} else if (s == TEMP_FILE && p != NULL && !verbose) {
			switch (t) {
			case BINARY_OBJ_AUX:
			case BINARY_OBJ:
				break;
			case C_SPEC:
				break;
			case CPP_SPEC:
				break;
			case INDEP_TDF_AUX:
			case INDEP_TDF:
				if (make_archive || make_complex ||
				    tokdef_name) {
					break;
				}
				goto default_lab;
			default:
default_lab:
				b = p->bname;
				e = file_suffix(t);
				IGNORE sprintf(buffer, "%s/%s.%s", d,
					       TEMP_NAME, e);
				nm = string_copy(buffer);
				break;
			}
		}
	}

	/* Find the file name */
	if (nm == NULL) {
		if (p == NULL || make_up_names) {
			static int seq = 0;
			IGNORE sprintf(buffer, MADE_UP_NAME, seq++);
			b = string_copy(buffer);
		} else {
			b = p->bname;
		}
		e = file_suffix(t);
		if (d == NULL) {
			IGNORE sprintf(buffer, "%s.%s", b, e);
		} else {
			IGNORE sprintf(buffer, "%s/%s.%s", d, b, e);
		}
		nm = string_copy(buffer);
	}

	/* Fill in the fields of the result */
	SET(b);
	q->name = nm;
	q->bname = b;
	q->uniq = (p ? p->uniq : new_unique());
	q->type = t;
	q->storage = s;
	q->final = f;
	q->aux = NULL;
	q->next = NULL;
	return (q);
}
