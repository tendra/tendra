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

/*
 * error.c - Error reporting.
 *
 * This file implements the error reporting facility specified in the file
 * "error.h".  See that file for more details.
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "error.h"
#include "syntax.h"
#include "internals.h"

#define TAG_TABLE_SIZE		(127)
#define ERROR_TABLE_SIZE	(127)
#define STRING_TABLE_SIZE	(127)

static ETagT *		tag_table[TAG_TABLE_SIZE];
static ErrorT *		error_table[ERROR_TABLE_SIZE];
static EStringT *		string_table[STRING_TABLE_SIZE];
static char *		program_name         = NULL;
static ErrorInitProcP	init_proc	     = NULL;
static ETagT *		etag_program	     = NULL;
static ETagT *		etag_severity	     = NULL;
static ETagT *		etag_error_name      = NULL;
static ETagT *		etag_dollar	     = NULL;
static ETagT *		etag_ocb	     = NULL;
static ETagT *		etag_ccb	     = NULL;
static ErrorListT *	error_prefix	     = NULL;
static ESeverityT	min_severity	     = ERROR_SEVERITY_ERROR;
static ESeverityT	max_reported	     = ERROR_SEVERITY_INFORMATION;
static EStringDataT	severity_data[]    = {
    { {"error severity information",	"Info"} },
    { {"error severity warning",	"Warning"} },
    { {"error severity error",		"Error"} },
    { {"error severity fatal",		"Fatal"} },
    { {"error severity internal",	"Internal"} },
    ERROR_END_STRING_LIST
};

static void
error_deallocate_error_list(ErrorListT * error_list)
{
    while (error_list) {
	ErrorListT * tmp = error_list;

	if (error_list->tag == ERROR_TAG_STRING) {
	    nstring_destroy(&(error_list->u.string));
	}
	error_list = error_list->next;
	DEALLOCATE(tmp);
    }
}

static ErrorListT *
error_parse_message(char * message)
{
    ErrorListT *  error_list;
    ErrorListT * *error_list_next = &error_list;
    char *    message_copy    = cstring_duplicate(message);
    char *    scan            = message = message_copy;

    while (*scan) {
	if ((*scan++ == '$') && (*scan == '{')) {
	    if (scan > (message + 1)) {
		ErrorListT * tmp = ALLOCATE(ErrorListT);

		tmp->tag  = ERROR_TAG_STRING;
		scan[-1] = '\0';
		nstring_copy_cstring(&(tmp->u.string), message);
		*error_list_next = tmp;
		error_list_next  = &(tmp->next);
	    }
	    scan++;
	    message = scan;
	    while (*scan != '}') {
		if ((*scan == '\0') || (*scan == '$') || (*scan == '{') ||
		    ((!isprint((unsigned char)*scan)) && (*scan != ' '))) {
		    *error_list_next = NULL;
		    error_deallocate_error_list(error_list);
		    return(NULL);
		}
		scan++;
	    }
	    if (scan++ > message) {
		ErrorListT * tmp = ALLOCATE(ErrorListT);
		char *   tag;

		tmp->tag   = ERROR_TAG_TAG;
		scan[-1] = '\0';
		tag        = cstring_duplicate(message);
		tmp->u.tag = error_define_tag(tag);
		if (tmp->u.tag->name != tag) {
		    DEALLOCATE(tag);
		}
		*error_list_next = tmp;
		error_list_next  = &(tmp->next);
	    }
	    message = scan;
	}
    }
    if (scan > message) {
	ErrorListT * tmp = ALLOCATE(ErrorListT);

	tmp->tag = ERROR_TAG_STRING;
	nstring_copy_cstring(&(tmp->u.string), message);
	*error_list_next = tmp;
	error_list_next  = &(tmp->next);
    }
    *error_list_next = NULL;
    DEALLOCATE(message_copy);
    return(error_list);
}

static void
write_error_list(OStreamT * ostream, ErrorListT * error_list, ErrorT * error,
		 ErrorprocP proc, void * closure)
{
    while (error_list) {
	switch (error_list->tag)EXHAUSTIVE {
	  case ERROR_TAG_STRING:
	    write_nstring(ostream, &(error_list->u.string));
	    break;
	  case ERROR_TAG_TAG:
	    if (error_list->u.tag == etag_program) {
		write_cstring(ostream, program_name);
	    } else if (error_list->u.tag == etag_severity) {
		EStringT * estring =
		    severity_data[(error->severity)].estring;

		write_cstring(ostream, error_string_contents(estring));
	    } else if (error_list->u.tag == etag_error_name) {
		write_cstring(ostream, error->name);
	    } else if (error_list->u.tag == etag_dollar) {
		write_char(ostream, '$');
	    } else if (error_list->u.tag == etag_ocb) {
		write_char(ostream, '{');
	    } else if (error_list->u.tag == etag_ccb) {
		write_char(ostream, '}');
	    } else if (proc) {
		((*proc)(ostream, error_list->u.tag, closure));
	    }
	    break;
	}
	error_list = error_list->next;
    }
}

static void
write_error_list_text(OStreamT * ostream, ErrorListT * error_list)
{
    NStringT * nstring;
    char * contents;
    unsigned length;

    write_char(ostream, '"');
    while (error_list) {
	switch (error_list->tag)EXHAUSTIVE {
	  case ERROR_TAG_STRING:
	    nstring  = &(error_list->u.string);
	    contents = nstring_contents(nstring);
	    length   = nstring_length(nstring);

	    while (length--) {
		switch (*contents) {
		  case '\n':
		    write_cstring(ostream, "\\n\\");
		    write_newline(ostream);
		    break;
		  case '"':
		    write_cstring(ostream, "\\\"");
		    break;
		  default:
		    assert(*contents != '\0');
		    write_char(ostream, *contents);
		    break;
		}
		contents++;
	    }
	    break;
	  case ERROR_TAG_TAG:
	    write_cstring(ostream, "${");
	    write_cstring(ostream, error_list->u.tag->name);
	    write_char(ostream, '}');
	    break;
	}
	error_list = error_list->next;
    }
    write_char(ostream, '"');
}

static void
write_error_table(OStreamT * ostream)
{
    unsigned i;

    for (i = 0; i < ERROR_TABLE_SIZE; i++) {
	ErrorT * error = error_table[i];

	while (error) {
	    write_char(ostream, '\'');
	    write_cstring(ostream, error->name);
	    write_char(ostream, '\'');
	    write_newline(ostream);
	    write_cstring(ostream, "    ");
	    write_error_list_text(ostream, error->error_list);
	    write_newline(ostream);
	    error = error->next;
	}
    }
}

static void
write_string_table(OStreamT * ostream)
{
    unsigned i;

    for (i = 0; i < STRING_TABLE_SIZE; i++) {
	EStringT * string = string_table[i];

	while (string) {
	    char * contents = string->contents;

	    write_char(ostream, '\'');
	    write_cstring(ostream, string->name);
	    write_char(ostream, '\'');
	    write_newline(ostream);
	    write_cstring(ostream, "    ");
	    write_char(ostream, '"');
	    while (*contents) {
		switch (*contents) {
		  case '\n':
		    write_cstring(ostream, "\\n\\");
		    write_newline(ostream);
		    break;
		  case '"':
		    write_cstring(ostream, "\\\"");
		    break;
		  default:
		    write_char(ostream, *contents);
		    break;
		}
		contents++;
	    }
	    write_char(ostream, '"');
	    write_newline(ostream);
	    string = string->next;
	}
    }
}

/*
 * Externally visible functions
 */

void
error_init(char * name, ErrorInitProcP proc)
{
    static char * prefix = "${program name}: ${severity}: ";

    program_name = name;
    while (*name) {
	if (*name++ == '/') {
	    program_name = name;
	}
    }
    init_proc       = proc;
    etag_program    = error_define_tag("program name");
    etag_severity   = error_define_tag("severity");
    etag_error_name = error_define_tag("this error name");
    etag_dollar     = error_define_tag("dollar");
    etag_ocb        = error_define_tag("open brace");
    etag_ccb        = error_define_tag("close brace");
    error_prefix    = error_parse_message(prefix);
    error_intern_strings(severity_data);
    ostream_buffer(ostream_error);
}

void
error_call_init_proc(void)
{
    if (init_proc) {
	(*init_proc)();
	init_proc = NULL;
    }
}

ETagT *
error_define_tag(char * name)
{
    unsigned hash   = (cstring_hash_value(name)% TAG_TABLE_SIZE);
    ETagT *   *entryp = &(tag_table[hash]);
    ETagT *    entry;

    while ((entry = *entryp) != NULL) {
	if (!strcmp(entry->name, name)) {
	    return(entry);
	}
	entryp = &(entry->next);
    }
    entry       = ALLOCATE(ETagT);
    entry->next = NULL;
    entry->name = name;
    *entryp     = entry;
    return(entry);
}

ErrorT *
error_define_error(char * name, ESeverityT severity, char * message,
		   void * data)
{
    ErrorListT * error_list = error_parse_message(message);
    unsigned   hash       = (cstring_hash_value(name)% ERROR_TABLE_SIZE);
    ErrorT *    *entryp     = &(error_table[hash]);
    ErrorT *     entry;

    while ((entry = *entryp) != NULL) {
	assert(!!strcmp(entry->name, name));
	entryp = &(entry->next);
    }
    assert(error_list);
    entry             = ALLOCATE(ErrorT);
    entry->next       = NULL;
    entry->name       = name;
    entry->severity   = severity;
    entry->error_list = error_list;
    entry->data       = data;
    *entryp           = entry;
    return(entry);
}

void
error_intern_tags(ETagDataT * vector)
{
    while (vector->name) {
	ETagT * tag = error_define_tag(vector->name);

	vector->tag = tag;
	vector++;
    }
}

void
error_intern_errors(ErrorDataT * vector)
{
    while (vector->s.name) {
	ErrorT * error = error_define_error(vector->s.name, vector->s.severity,
					   vector->s.message, vector->s.data);

	vector->error = error;
	vector++;
    }
}

ErrorStatusT
error_redefine_error(char * name, char * message)
{
    error_call_init_proc();
    {
	unsigned hash  = (cstring_hash_value(name)% ERROR_TABLE_SIZE);
	ErrorT *   entry = (error_table[hash]);

	while (entry) {
	    if (!strcmp(entry->name, name)) {
		ErrorListT * error_list = error_parse_message(message);

		if (error_list == NULL) {
		    return(ERROR_STATUS_BAD_MESSAGE);
		}
		error_deallocate_error_list(entry->error_list);
		entry->error_list = error_list;
		return(ERROR_STATUS_SUCCESS);
	    }
	    entry = entry->next;
	}
	return(ERROR_STATUS_BAD_ERROR);
    }
}

ErrorT *
error_lookup_error(char * name)
{
    error_call_init_proc();
    {
	unsigned hash  = (cstring_hash_value(name)% ERROR_TABLE_SIZE);
	ErrorT *   entry = (error_table[hash]);

	while (entry) {
	    if (!strcmp(entry->name, name)) {
		return(entry);
	    }
	    entry = entry->next;
	}
	return(NULL);
    }
}

void *
error_data(ErrorT * error)
{
    return(error->data);
}

void
error_report(ErrorT * error, ErrorprocP proc, void * closure)
{
    if ((error->severity) >= min_severity) {
	write_error_list(ostream_error, error_prefix, error, NULL,
			 NULL);
	write_error_list(ostream_error, error->error_list, error, proc,
			 closure);
	write_newline(ostream_error);
	ostream_flush(ostream_error);
    }
    if ((error->severity) > max_reported) {
	max_reported = error->severity;
    }
    if ((error->severity) >= ERROR_SEVERITY_FATAL) {
	if (error->severity == ERROR_SEVERITY_INTERNAL) {
	    abort();
	    UNREACHED;
	}
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

void
error_set_min_report_severity(ESeverityT severity)
{
    min_severity = severity;
}

ESeverityT
error_get_min_report_severity(void)
{
    return(min_severity);
}

ESeverityT
error_max_reported_severity(void)
{
    return(max_reported);
}

void
error_set_severity_message(ESeverityT severity, char * message)
{
    severity_data[severity].estring->contents = message;
}

BoolT
error_set_prefix_message(char * message)
{
    ErrorListT * error_list = error_parse_message(message);

    if (error_list == NULL) {
	return(FALSE);
    }
    error_deallocate_error_list(error_prefix);
    error_prefix = error_list;
    return(TRUE);
}

EStringT *
error_define_string(char * name, char * contents)
{
    unsigned  hash   = (cstring_hash_value(name)% STRING_TABLE_SIZE);
    EStringT * *entryp = &(string_table[hash]);
    EStringT *  entry;

    while ((entry = *entryp) != NULL) {
	assert(!!strcmp(entry->name, name));
	entryp = &(entry->next);
    }
    entry           = ALLOCATE(EStringT);
    entry->next     = NULL;
    entry->name     = name;
    entry->contents = contents;
    *entryp         = entry;
    return(entry);
}

void
error_intern_strings(EStringDataT *vector)
{
    while (vector->s.name) {
	EStringT * estring = error_define_string(vector->s.name,
					       vector->s.contents);

	vector->estring = estring;
	vector++;
    }
}

BoolT
error_redefine_string(char * name, char * contents)
{
    unsigned hash  = (cstring_hash_value(name)% STRING_TABLE_SIZE);
    EStringT * entry = (string_table[hash]);

    while (entry) {
	if (!strcmp(entry->name, name)) {
	    entry->contents = contents;
	    return(TRUE);
	}
	entry = entry->next;
    }
    return(FALSE);
}

EStringT *
error_lookup_string(char * name)
{
    unsigned hash  = (cstring_hash_value(name)% STRING_TABLE_SIZE);
    EStringT * entry = (string_table[hash]);

    while (entry) {
	if (!strcmp(entry->name, name)) {
	    return(entry);
	}
	entry = entry->next;
    }
    return(NULL);
}

char *
error_string_contents(EStringT * estring)
{
    return(estring->contents);
}

void
write_error_file(OStreamT * ostream)
{
    error_call_init_proc();
    write_cstring(ostream, "%prefix%");
    write_newline(ostream);
    write_cstring(ostream, "    ");
    write_error_list_text(ostream, error_prefix);
    write_newline(ostream);
    write_newline(ostream);
    write_cstring(ostream, "%errors%");
    write_newline(ostream);
    write_error_table(ostream);
    write_newline(ostream);
    write_cstring(ostream, "%strings%");
    write_newline(ostream);
    write_string_table(ostream);
}
