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

#define TAG_TABLE_SIZE (127)
#define ERROR_TABLE_SIZE (127)
#define STRING_TABLE_SIZE (127)

/*--------------------------------------------------------------------------*/

static ETagP		tag_table [TAG_TABLE_SIZE];
static ErrorP		error_table [ERROR_TABLE_SIZE];
static EStringP		string_table [STRING_TABLE_SIZE];
static CStringP		program_name         = NIL (CStringP);
static ErrorInitProcP	init_proc	     = NIL (ErrorInitProcP);
static ETagP		etag_program	     = NIL (ETagP);
static ETagP		etag_severity	     = NIL (ETagP);
static ETagP		etag_error_name      = NIL (ETagP);
static ETagP		etag_dollar	     = NIL (ETagP);
static ETagP		etag_ocb	     = NIL (ETagP);
static ETagP		etag_ccb	     = NIL (ETagP);
static ErrorListP	error_prefix	     = NIL (ErrorListP);
static ESeverityT	min_severity	     = ERROR_SEVERITY_ERROR;
static ESeverityT	max_reported	     = ERROR_SEVERITY_INFORMATION;
static EStringDataT	severity_data []     = {
    UB {"error severity information",	"Info"} UE,
    UB {"error severity warning",	"Warning"} UE,
    UB {"error severity error",		"Error"} UE,
    UB {"error severity fatal",		"Fatal"} UE,
    UB {"error severity internal",	"Internal"} UE,
    ERROR_END_STRING_LIST
};

/*--------------------------------------------------------------------------*/

static void
error_deallocate_error_list PROTO_N ((error_list))
			    PROTO_T (ErrorListP error_list)
{
    while (error_list) {
	ErrorListP tmp = error_list;

	if (error_list->tag == ERROR_TAG_STRING) {
	    nstring_destroy (&(error_list->u.string));
	}
	error_list = error_list->next;
	DEALLOCATE (tmp);
    }
}

static ErrorListP
error_parse_message PROTO_N ((message))
		    PROTO_T (CStringP message)
{
    ErrorListP  error_list;
    ErrorListP *error_list_next = &error_list;
    CStringP    message_copy    = cstring_duplicate (message);
    CStringP    scan            = message = message_copy;

    while (*scan) {
	if ((*scan ++ == '$') && (*scan == '{')) {
	    if (scan > (message + 1)) {
		ErrorListP tmp = ALLOCATE (ErrorListT);

		tmp->tag  = ERROR_TAG_STRING;
		scan [-1] = '\0';
		nstring_copy_cstring (&(tmp->u.string), message);
		*error_list_next = tmp;
		error_list_next  = &(tmp->next);
	    }
	    scan ++;
	    message = scan;
	    while (*scan != '}') {
		if ((*scan == '\0') || (*scan == '$') || (*scan == '{') ||
		    ((!syntax_is_printable (*scan)) && (*scan != ' '))) {
		    *error_list_next = NIL (ErrorListP);
		    error_deallocate_error_list (error_list);
		    return (NIL (ErrorListP));
		}
		scan ++;
	    }
	    if (scan ++ > message) {
		ErrorListP tmp = ALLOCATE (ErrorListT);
		CStringP   tag;

		tmp->tag   = ERROR_TAG_TAG;
		scan [-1]  = '\0';
		tag        = cstring_duplicate (message);
		tmp->u.tag = error_define_tag (tag);
		if (tmp->u.tag->name != tag) {
		    DEALLOCATE (tag);
		}
		*error_list_next = tmp;
		error_list_next  = &(tmp->next);
	    }
	    message = scan;
	}
    }
    if (scan > message) {
	ErrorListP tmp = ALLOCATE (ErrorListT);

	tmp->tag = ERROR_TAG_STRING;
	nstring_copy_cstring (&(tmp->u.string), message);
	*error_list_next = tmp;
	error_list_next  = &(tmp->next);
    }
    *error_list_next = NIL (ErrorListP);
    DEALLOCATE (message_copy);
    return (error_list);
}

static void
write_error_list PROTO_N ((ostream, error_list, error, proc, closure))
		 PROTO_T (OStreamP   ostream X
			  ErrorListP error_list X
			  ErrorP     error X
			  ErrorProcP proc X
			  GenericP   closure)
{
    while (error_list) {
	switch (error_list->tag) EXHAUSTIVE {
	  case ERROR_TAG_STRING:
	    write_nstring (ostream, &(error_list->u.string));
	    break;
	  case ERROR_TAG_TAG:
	    if (error_list->u.tag == etag_program) {
		write_cstring (ostream, program_name);
	    } else if (error_list->u.tag == etag_severity) {
		EStringP estring =
		    severity_data [(error->severity)].estring;

		write_cstring (ostream, error_string_contents (estring));
	    } else if (error_list->u.tag == etag_error_name) {
		write_cstring (ostream, error->name);
	    } else if (error_list->u.tag == etag_dollar) {
		write_char (ostream, '$');
	    } else if (error_list->u.tag == etag_ocb) {
		write_char (ostream, '{');
	    } else if (error_list->u.tag == etag_ccb) {
		write_char (ostream, '}');
	    } else if (proc) {
		((*proc) (ostream, error_list->u.tag, closure));
	    }
	    break;
	}
	error_list = error_list->next;
    }
}

static void
write_error_list_text PROTO_N ((ostream, error_list))
		      PROTO_T (OStreamP   ostream X
			       ErrorListP error_list)
{
    NStringP nstring;
    CStringP contents;
    unsigned length;

    write_char (ostream, '"');
    while (error_list) {
	switch (error_list->tag) EXHAUSTIVE {
	  case ERROR_TAG_STRING:
	    nstring  = &(error_list->u.string);
	    contents = nstring_contents (nstring);
	    length   = nstring_length (nstring);

	    while (length --) {
		switch (*contents) {
		  case '\n':
		    write_cstring (ostream, "\\n\\");
		    write_newline (ostream);
		    break;
		  case '"':
		    write_cstring (ostream, "\\\"");
		    break;
		  default:
		    ASSERT (*contents != '\0');
		    write_char (ostream, *contents);
		    break;
		}
		contents ++;
	    }
	    break;
	  case ERROR_TAG_TAG:
	    write_cstring (ostream, "${");
	    write_cstring (ostream, error_list->u.tag->name);
	    write_char (ostream, '}');
	    break;
	}
	error_list = error_list->next;
    }
    write_char (ostream, '"');
}

static void
write_error_table PROTO_N ((ostream))
		  PROTO_T (OStreamP ostream)
{
    unsigned i;

    for (i = 0; i < ERROR_TABLE_SIZE; i ++) {
	ErrorP error = error_table [i];

	while (error) {
	    write_char (ostream, '\'');
	    write_cstring (ostream, error->name);
	    write_char (ostream, '\'');
	    write_newline (ostream);
	    write_cstring (ostream, "    ");
	    write_error_list_text (ostream, error->error_list);
	    write_newline (ostream);
	    error = error->next;
	}
    }
}

static void
write_string_table PROTO_N ((ostream))
		   PROTO_T (OStreamP ostream)
{
    unsigned i;

    for (i = 0; i < STRING_TABLE_SIZE; i ++) {
	EStringP string = string_table [i];

	while (string) {
	    CStringP contents = string->contents;

	    write_char (ostream, '\'');
	    write_cstring (ostream, string->name);
	    write_char (ostream, '\'');
	    write_newline (ostream);
	    write_cstring (ostream, "    ");
	    write_char (ostream, '"');
	    while (*contents) {
		switch (*contents) {
		  case '\n':
		    write_cstring (ostream, "\\n\\");
		    write_newline (ostream);
		    break;
		  case '"':
		    write_cstring (ostream, "\\\"");
		    break;
		  default:
		    write_char (ostream, *contents);
		    break;
		}
		contents ++;
	    }
	    write_char (ostream, '"');
	    write_newline (ostream);
	    string = string->next;
	}
    }
}

/*--------------------------------------------------------------------------*/

void
error_init PROTO_N ((name, proc))
	   PROTO_T (CStringP       name X
		    ErrorInitProcP proc)
{
    static CStringP prefix = "${program name}: ${severity}: ";

    program_name = name;
    while (*name) {
	if (*name ++ == '/') {
	    program_name = name;
	}
    }
    init_proc       = proc;
    etag_program    = error_define_tag ("program name");
    etag_severity   = error_define_tag ("severity");
    etag_error_name = error_define_tag ("this error name");
    etag_dollar     = error_define_tag ("dollar");
    etag_ocb        = error_define_tag ("open brace");
    etag_ccb        = error_define_tag ("close brace");
    error_prefix    = error_parse_message (prefix);
    error_intern_strings (severity_data);
    ostream_buffer (ostream_error);
}

void
error_call_init_proc PROTO_Z ()
{
    if (init_proc) {
	(*init_proc) ();
	init_proc = NIL (ErrorInitProcP);
    }
}

ETagP
error_define_tag PROTO_N ((name))
		 PROTO_T (CStringP name)
{
    unsigned hash   = (cstring_hash_value (name) % TAG_TABLE_SIZE);
    ETagP   *entryp = &(tag_table [hash]);
    ETagP    entry;

    while ((entry = *entryp) != NIL (ETagP)) {
	if (cstring_equal (entry->name, name)) {
	    return (entry);
	}
	entryp = &(entry->next);
    }
    entry       = ALLOCATE (ETagT);
    entry->next = NIL (ETagP);
    entry->name = name;
    *entryp     = entry;
    return (entry);
}

ErrorP
error_define_error PROTO_N ((name, severity, message, data))
		   PROTO_T (CStringP   name X
			    ESeverityT severity X
			    CStringP   message X
			    GenericP   data)
{
    ErrorListP error_list = error_parse_message (message);
    unsigned   hash       = (cstring_hash_value (name) % ERROR_TABLE_SIZE);
    ErrorP    *entryp     = &(error_table [hash]);
    ErrorP     entry;

    while ((entry = *entryp) != NIL (ErrorP)) {
	ASSERT (!cstring_equal (entry->name, name));
	entryp = &(entry->next);
    }
    ASSERT (error_list);
    entry             = ALLOCATE (ErrorT);
    entry->next       = NIL (ErrorP);
    entry->name       = name;
    entry->severity   = severity;
    entry->error_list = error_list;
    entry->data       = data;
    *entryp           = entry;
    return (entry);
}

void
error_intern_tags PROTO_N ((vector))
		  PROTO_T (ETagDataP vector)
{
    while (vector->name) {
	ETagP tag = error_define_tag (vector->name);

	vector->tag = tag;
	vector ++;
    }
}

void
error_intern_errors PROTO_N ((vector))
		    PROTO_T (ErrorDataP vector)
{
    while (vector->s.name) {
	ErrorP error = error_define_error (vector->s.name, vector->s.severity,
					   vector->s.message, vector->s.data);

	vector->error = error;
	vector ++;
    }
}

ErrorStatusT
error_redefine_error PROTO_N ((name, message))
		     PROTO_T (CStringP name X
			      CStringP message)
{
    error_call_init_proc ();
    {
	unsigned hash  = (cstring_hash_value (name) % ERROR_TABLE_SIZE);
	ErrorP   entry = (error_table [hash]);

	while (entry) {
	    if (cstring_equal (entry->name, name)) {
		ErrorListP error_list = error_parse_message (message);

		if (error_list == NIL (ErrorListP)) {
		    return (ERROR_STATUS_BAD_MESSAGE);
		}
		error_deallocate_error_list (entry->error_list);
		entry->error_list = error_list;
		return (ERROR_STATUS_SUCCESS);
	    }
	    entry = entry->next;
	}
	return (ERROR_STATUS_BAD_ERROR);
    }
}

ErrorP
error_lookup_error PROTO_N ((name))
		   PROTO_T (CStringP name)
{
    error_call_init_proc ();
    {
	unsigned hash  = (cstring_hash_value (name) % ERROR_TABLE_SIZE);
	ErrorP   entry = (error_table [hash]);

	while (entry) {
	    if (cstring_equal (entry->name, name)) {
		return (entry);
	    }
	    entry = entry->next;
	}
	return (NIL (ErrorP));
    }
}

GenericP
error_data PROTO_N ((error))
	   PROTO_T (ErrorP error)
{
    return (error->data);
}

void
error_report PROTO_N ((error, proc, closure))
	     PROTO_T (ErrorP     error X
		      ErrorProcP proc X
		      GenericP   closure)
{
    if ((error->severity) >= min_severity) {
	write_error_list (ostream_error, error_prefix, error, NIL (ErrorProcP),
			  NIL (GenericP));
	write_error_list (ostream_error, error->error_list, error, proc,
			  closure);
	write_newline (ostream_error);
	ostream_flush (ostream_error);
    }
    if ((error->severity) > max_reported) {
	max_reported = error->severity;
    }
    if ((error->severity) >= ERROR_SEVERITY_FATAL) {
	if (error->severity == ERROR_SEVERITY_INTERNAL) {
	    abort ();
	    UNREACHED;
	}
	exit (EXIT_FAILURE);
	UNREACHED;
    }
}

void
error_set_min_report_severity PROTO_N ((severity))
			      PROTO_T (ESeverityT severity)
{
    min_severity = severity;
}

ESeverityT
error_get_min_report_severity PROTO_Z ()
{
    return (min_severity);
}

ESeverityT
error_max_reported_severity PROTO_Z ()
{
    return (max_reported);
}

void
error_set_severity_message PROTO_N ((severity, message))
			   PROTO_T (ESeverityT severity X
				    CStringP   message)
{
    severity_data [severity].estring->contents = message;
}

BoolT
error_set_prefix_message PROTO_N ((message))
			 PROTO_T (CStringP message)
{
    ErrorListP error_list = error_parse_message (message);

    if (error_list == NIL (ErrorListP)) {
	return (FALSE);
    }
    error_deallocate_error_list (error_prefix);
    error_prefix = error_list;
    return (TRUE);
}

EStringP
error_define_string PROTO_N ((name, contents))
		    PROTO_T (CStringP name X
			     CStringP contents)
{
    unsigned  hash   = (cstring_hash_value (name) % STRING_TABLE_SIZE);
    EStringP *entryp = &(string_table [hash]);
    EStringP  entry;

    while ((entry = *entryp) != NIL (EStringP)) {
	ASSERT (!cstring_equal (entry->name, name));
	entryp = &(entry->next);
    }
    entry           = ALLOCATE (EStringT);
    entry->next     = NIL (EStringP);
    entry->name     = name;
    entry->contents = contents;
    *entryp         = entry;
    return (entry);
}

void
error_intern_strings PROTO_N ((vector))
		     PROTO_T (EStringDataP vector)
{
    while (vector->s.name) {
	EStringP estring = error_define_string (vector->s.name,
						vector->s.contents);

	vector->estring = estring;
	vector ++;
    }
}

BoolT
error_redefine_string PROTO_N ((name, contents))
		      PROTO_T (CStringP name X
			       CStringP contents)
{
    unsigned hash  = (cstring_hash_value (name) % STRING_TABLE_SIZE);
    EStringP entry = (string_table [hash]);

    while (entry) {
	if (cstring_equal (entry->name, name)) {
	    entry->contents = contents;
	    return (TRUE);
	}
	entry = entry->next;
    }
    return (FALSE);
}

EStringP
error_lookup_string PROTO_N ((name))
		    PROTO_T (CStringP name)
{
    unsigned hash  = (cstring_hash_value (name) % STRING_TABLE_SIZE);
    EStringP entry = (string_table [hash]);

    while (entry) {
	if (cstring_equal (entry->name, name)) {
	    return (entry);
	}
	entry = entry->next;
    }
    return (NIL (EStringP));
}

CStringP
error_string_contents PROTO_N ((estring))
		      PROTO_T (EStringP estring)
{
    return (estring->contents);
}

void
write_error_file PROTO_N ((ostream))
		 PROTO_T (OStreamP ostream)
{
    error_call_init_proc ();
    write_cstring (ostream, "%prefix%");
    write_newline (ostream);
    write_cstring (ostream, "    ");
    write_error_list_text (ostream, error_prefix);
    write_newline (ostream);
    write_newline (ostream);
    write_cstring (ostream, "%errors%");
    write_newline (ostream);
    write_error_table (ostream);
    write_newline (ostream);
    write_cstring (ostream, "%strings%");
    write_newline (ostream);
    write_string_table (ostream);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
**/
