/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
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


/**** error.c --- Error reporting.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the error reporting facility specified in the file
 * "error.h".  See that file for more details.
 *
 **** Change Log:
 * $Log: error.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:17  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:44:41  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:05:51  smf
 * Initial import of library shared files.
 *
**/

/****************************************************************************/

#include "error.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

#define TAG_TABLE_SIZE		(127)
#define ERROR_TABLE_SIZE	(127)
#define STRING_TABLE_SIZE	(127)

/*--------------------------------------------------------------------------*/

static ETagT *	tag_table[TAG_TABLE_SIZE];
static ErrorT *	error_table[ERROR_TABLE_SIZE];
static EStringT *	string_table[STRING_TABLE_SIZE];
static char *		program_name         = NIL(char *);
static ErrorInitProcP	init_proc	     = NIL(ErrorInitProcP);
static ETagT *	etag_program	     = NIL(ETagT *);
static ETagT *	etag_severity	     = NIL(ETagT *);
static ETagT *	etag_error_name      = NIL(ETagT *);
static ETagT *	etag_dollar	     = NIL(ETagT *);
static ETagT *	etag_ocb	     = NIL(ETagT *);
static ETagT *	etag_ccb	     = NIL(ETagT *);
static ErrorListT *error_prefix	     = NIL(ErrorListT *);
static ESeverityT	min_severity	     = ERROR_SEVERITY_ERROR;
static ESeverityT	max_reported	     = ERROR_SEVERITY_INFORMATION;
static EStringDataT	severity_data[]    = {
    UB {"error severity information",	"Info"} UE,
    UB {"error severity warning",	"Warning"} UE,
    UB {"error severity error",		"Error"} UE,
    UB {"error severity fatal",		"Fatal"} UE,
    UB {"error severity internal",	"Internal"} UE,
    ERROR_END_STRING_LIST
};

/*--------------------------------------------------------------------------*/

static void
error_deallocate_error_list(ErrorListT *error_list)
{
    while (error_list) {
	ErrorListT *tmp = error_list;

	if (error_list->tag == ERROR_TAG_STRING) {
	    nstring_destroy(& (error_list->u.string));
	}
	error_list = error_list->next;
	DEALLOCATE(tmp);
    }
}

static ErrorListT *
error_parse_message(char * message)
{
    ErrorListT * error_list;
    ErrorListT **error_list_next = &error_list;
    char *    message_copy    = cstring_duplicate(message);
    char *    scan            = message = message_copy;

    while (*scan) {
	if ((*scan++ == '$') && (*scan == '{')) {
	    if (scan > (message + 1)) {
		ErrorListT *tmp = ALLOCATE(ErrorListT);

		tmp->tag  = ERROR_TAG_STRING;
		scan[-1] = '\0';
		nstring_copy_cstring(& (tmp->u.string), message);
		*error_list_next = tmp;
		error_list_next  = & (tmp->next);
	    }
	    scan++;
	    message = scan;
	    while (*scan != '}') {
		if ((*scan == '\0') || (*scan == '$') || (*scan == '{') ||
		   ((!syntax_is_printable(*scan)) && (*scan != ' '))) {
		    *error_list_next = NIL(ErrorListT *);
		    error_deallocate_error_list(error_list);
		    return(NIL(ErrorListT *));
		}
		scan++;
	    }
	    if (scan++ > message) {
		ErrorListT *tmp = ALLOCATE(ErrorListT);
		char *   tag;

		tmp->tag   = ERROR_TAG_TAG;
		scan[-1] = '\0';
		tag        = cstring_duplicate(message);
		tmp->u.tag = error_define_tag(tag);
		if (tmp->u.tag->name != tag) {
		    DEALLOCATE(tag);
		}
		*error_list_next = tmp;
		error_list_next  = & (tmp->next);
	    }
	    message = scan;
	}
    }
    if (scan > message) {
	ErrorListT *tmp = ALLOCATE(ErrorListT);

	tmp->tag = ERROR_TAG_STRING;
	nstring_copy_cstring(& (tmp->u.string), message);
	*error_list_next = tmp;
	error_list_next  = & (tmp->next);
    }
    *error_list_next = NIL(ErrorListT *);
    DEALLOCATE(message_copy);
    return(error_list);
}

static void
write_error_list(OStreamT *  ostream,			  ErrorListT *error_list, 
			  ErrorT *    error, 
			  ErrorProcP proc, 
			  void *   closure)
{
    while (error_list) {
	switch (error_list->tag)EXHAUSTIVE {
	  case ERROR_TAG_STRING:
	    write_nstring(ostream, & (error_list->u.string));
	    break;
	  case ERROR_TAG_TAG:
	    if (error_list->u.tag == etag_program) {
		write_cstring(ostream, program_name);
	    } else if (error_list->u.tag == etag_severity) {
		EStringT *estring =
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

/*--------------------------------------------------------------------------*/

void
error_init(char *       name,		    ErrorInitProcP proc)
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
	init_proc = NIL(ErrorInitProcP);
    }
}

ETagT *
error_define_tag(char * name)
{
    unsigned hash   = (cstring_hash_value(name)% TAG_TABLE_SIZE);
    ETagT *  *entryp = & (tag_table[hash]);
    ETagT *   entry;

    while ((entry = *entryp) != NIL(ETagT *)) {
	if (cstring_equal(entry->name, name)) {
	    return(entry);
	}
	entryp = & (entry->next);
    }
    entry       = ALLOCATE(ETagT);
    entry->next = NIL(ETagT *);
    entry->name = name;
    *entryp     = entry;
    return(entry);
}

ErrorT *
error_define_error(char *   name,			    ESeverityT severity, 
			    char *   message, 
			    void *   data)
{
    ErrorListT *error_list = error_parse_message(message);
    unsigned   hash       = (cstring_hash_value(name)% ERROR_TABLE_SIZE);
    ErrorT *   *entryp     = & (error_table[hash]);
    ErrorT *    entry;

    while ((entry = *entryp) != NIL(ErrorT *)) {
	ASSERT(!cstring_equal(entry->name, name));
	entryp = & (entry->next);
    }
    ASSERT(error_list);
    entry             = ALLOCATE(ErrorT);
    entry->next       = NIL(ErrorT *);
    entry->name       = name;
    entry->severity   = severity;
    entry->error_list = error_list;
    entry->data       = data;
    *entryp           = entry;
    return(entry);
}

void
error_intern_tags(ETagDataT *vector)
{
    while (vector->name) {
	ETagT *tag = error_define_tag(vector->name);

	vector->tag = tag;
	vector++;
    }
}

void
error_intern_errors(ErrorDataT *vector)
{
    while (vector->s.name) {
	ErrorT *error = error_define_error(vector->s.name, vector->s.severity,
					   vector->s.message, vector->s.data);

	vector->error = error;
	vector++;
    }
}

ErrorStatusT
error_redefine_error(char * name,			      char * message)
{
    error_call_init_proc();
    {
	unsigned hash  = (cstring_hash_value(name)% ERROR_TABLE_SIZE);
	ErrorT *  entry = (error_table[hash]);

	while (entry) {
	    if (cstring_equal(entry->name, name)) {
		ErrorListT *error_list = error_parse_message(message);

		if (error_list == NIL(ErrorListT *)) {
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
	ErrorT *  entry = (error_table[hash]);

	while (entry) {
	    if (cstring_equal(entry->name, name)) {
		return(entry);
	    }
	    entry = entry->next;
	}
	return(NIL(ErrorT *));
    }
}

void *
error_data(ErrorT *error)
{
    return(error->data);
}

void
error_report(ErrorT *    error,		      ErrorProcP proc, 
		      void *   closure)
{
    if ((error->severity) >= min_severity) {
	write_error_list(ostream_error, error_prefix, error, NIL(ErrorProcP),
			  NIL(void *));
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
error_set_severity_message(ESeverityT severity,				    char *   message)
{
    severity_data[severity].estring->contents = message;
}

BoolT
error_set_prefix_message(char * message)
{
    ErrorListT *error_list = error_parse_message(message);

    if (error_list == NIL(ErrorListT *)) {
	return(FALSE);
    }
    error_deallocate_error_list(error_prefix);
    error_prefix = error_list;
    return(TRUE);
}

EStringT *
error_define_string(char * name,			     char * contents)
{
    unsigned  hash   = (cstring_hash_value(name)% STRING_TABLE_SIZE);
    EStringT **entryp = & (string_table[hash]);
    EStringT * entry;

    while ((entry = *entryp) != NIL(EStringT *)) {
	ASSERT(!cstring_equal(entry->name, name));
	entryp = & (entry->next);
    }
    entry           = ALLOCATE(EStringT);
    entry->next     = NIL(EStringT *);
    entry->name     = name;
    entry->contents = contents;
    *entryp         = entry;
    return(entry);
}

void
error_intern_strings(EStringDataT *vector)
{
    while (vector->s.name) {
	EStringT *estring = error_define_string(vector->s.name,
						vector->s.contents);

	vector->estring = estring;
	vector++;
    }
}

BoolT
error_redefine_string(char * name,			       char * contents)
{
    unsigned hash  = (cstring_hash_value(name)% STRING_TABLE_SIZE);
    EStringT *entry = (string_table[hash]);

    while (entry) {
	if (cstring_equal(entry->name, name)) {
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
    EStringT *entry = (string_table[hash]);

    while (entry) {
	if (cstring_equal(entry->name, name)) {
	    return(entry);
	}
	entry = entry->next;
    }
    return(NIL(EStringT *));
}

char *
error_string_contents(EStringT *estring)
{
    return(estring->contents);
}


/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
**/
