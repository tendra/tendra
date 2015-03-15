/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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

#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/ostream.h>
#include <exds/cstring.h>
#include <exds/dstring.h>
#include <exds/error.h>

#include "syntax.h"

/*
 * This is used by the error type.
 */
struct ErrorListT {
	ErrorListT *next;
	enum {
		ERROR_TAG_STRING,
		ERROR_TAG_TAG
	} tag;
	union {
		NStringT string;
		ETagT *tag;
	} u;
};


#define TAG_TABLE_SIZE		(127)
#define ERROR_TABLE_SIZE	(127)
#define STRING_TABLE_SIZE	(127)

static ETagT	*tag_table[TAG_TABLE_SIZE];
static ErrorT	*error_table[ERROR_TABLE_SIZE];
static EStringT	*string_table[STRING_TABLE_SIZE];
static const char *program_name    = NULL;
static ErrorInitProcP init_proc  = NULL;
static ETagT	*etag_program	 = NULL;
static ETagT	*etag_severity	 = NULL;
static ETagT	*etag_error_name = NULL;
static ETagT	*etag_dollar	 = NULL;
static ETagT	*etag_ocb	     = NULL;
static ETagT 	*etag_ccb	     = NULL;
static ErrorListT *error_prefix	 = NULL;
static ESeverityT min_severity	 = ERROR_SEVERITY_ERROR;
static ESeverityT max_reported	 = ERROR_SEVERITY_INFORMATION;
static EStringDataT	severity_data[] = {
	{ {"error severity information", "Info"} },
	{ {"error severity warning",	 "Warning"} },
	{ {"error severity error",		 "Error"} },
	{ {"error severity fatal",		 "Fatal"} },
	{ {"error severity internal",	 "Internal"} },
	ERROR_END_STRING_LIST
};

static void
error_deallocate_error_list(ErrorListT *error_list)
{
	while (error_list) {
		ErrorListT *tmp = error_list;

		if (error_list->tag == ERROR_TAG_STRING) {
			nstring_destroy(&error_list->u.string);
		}

		error_list = error_list->next;
		DEALLOCATE(tmp);
	}
}

static ErrorListT *
error_parse_message(const char *message)
{
	ErrorListT *error_list;
	ErrorListT **error_list_next = &error_list;
	char *message_copy    = cstring_duplicate(message);
	char *scan            = message_copy;

	message = message_copy;

	/* TODO this really ought to use lexi, after it settles a little */
	while (*scan) {
		if (*scan++ == '$' && *scan == '{') {
			if (scan > message + 1) {
				ErrorListT *tmp = ALLOCATE(ErrorListT);

				tmp->tag  = ERROR_TAG_STRING;
				scan[-1] = '\0';
				nstring_copy_cstring(&tmp->u.string, message);
				*error_list_next = tmp;
				error_list_next  = &tmp->next;
			}

			scan++;
			message = scan;
			while (*scan != '}') {
				if (*scan == '\0' || *scan == '$' || *scan == '{' ||
					(!isprint((unsigned char) *scan) && *scan != ' ')) {

					*error_list_next = NULL;
					error_deallocate_error_list(error_list);

					return NULL;
				}
				scan++;
			}

			if (scan++ > message) {
				ErrorListT *tmp = ALLOCATE(ErrorListT);
				char *tag;

				tmp->tag   = ERROR_TAG_TAG;
				scan[-1]   = '\0';
				tag        = cstring_duplicate(message);
				tmp->u.tag = error_define_tag(tag);

				if (tmp->u.tag->name != tag) {
					DEALLOCATE(tag);
				}

				*error_list_next = tmp;
				error_list_next  = &tmp->next;
			}
			message = scan;
		}
	}

	if (scan > message) {
		ErrorListT *tmp = ALLOCATE(ErrorListT);

		tmp->tag = ERROR_TAG_STRING;
		nstring_copy_cstring(&tmp->u.string, message);
		*error_list_next = tmp;
		error_list_next  = &tmp->next;
	}

	*error_list_next = NULL;
	DEALLOCATE(message_copy);

	return error_list;
}

static void
write_error_list(OStreamT *ostream, ErrorListT *error_list, ErrorT *error,
	ErrorprocP proc, void *closure)
{
	while (error_list) {
		switch (error_list->tag) EXHAUSTIVE {
		case ERROR_TAG_STRING:
			write_nstring(ostream, &error_list->u.string);
			break;
		case ERROR_TAG_TAG:
			if (error_list->u.tag == etag_program) {
				write_cstring(ostream, program_name);
			} else if (error_list->u.tag == etag_severity) {
				EStringT * estring = severity_data[error->severity].estring;

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
				proc(ostream, error_list->u.tag, closure);
			}
			break;
		}

		error_list = error_list->next;
	}
}


/*
 * Externally visible functions
 */

void
error_init(const char *name, ErrorInitProcP proc)
{
	static const char *prefix = "${program name}: ${severity}: ";

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
		init_proc();
		init_proc = NULL;
	}
}

ETagT *
error_define_tag(const char *name)
{
	unsigned hash   = cstring_hash_value(name) % TAG_TABLE_SIZE;
	ETagT **entryp = &tag_table[hash];
	ETagT *entry;

	while ((entry = *entryp) != NULL) {
		if (!strcmp(entry->name, name)) {
			return entry;
		}
		entryp = &entry->next;
	}

	entry       = ALLOCATE(ETagT);
	entry->next = NULL;
	entry->name = name;
	*entryp     = entry;
	return entry;
}

ErrorT *
error_define_error(const char *name, ESeverityT severity, const char *message,
	void *data)
{
	ErrorListT *error_list = error_parse_message(message);
	unsigned hash          = cstring_hash_value(name) % ERROR_TABLE_SIZE;
	ErrorT **entryp        = &error_table[hash];
	ErrorT *entry;

	while ((entry = *entryp) != NULL) {
		assert(!!(strcmp)(entry->name, name));
		entryp = &entry->next;
	}

	assert(error_list);
	entry             = ALLOCATE(ErrorT);
	entry->next       = NULL;
	entry->name       = name;
	entry->severity   = severity;
	entry->error_list = error_list;
	entry->data       = data;
	*entryp           = entry;

	return entry;
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
error_redefine_error(const char *name, const char *message)
{
	error_call_init_proc();

	{
		unsigned hash  = cstring_hash_value(name) % ERROR_TABLE_SIZE;
		ErrorT *entry  = error_table[hash];

		while (entry) {
			if (!strcmp(entry->name, name)) {
				ErrorListT *error_list = error_parse_message(message);

				if (error_list == NULL) {
					return ERROR_STATUS_BAD_MESSAGE;
				}

				error_deallocate_error_list(entry->error_list);
				entry->error_list = error_list;
				return ERROR_STATUS_SUCCESS;
			}

			entry = entry->next;
		}

		return ERROR_STATUS_BAD_ERROR;
	}
}

ErrorT *
error_lookup_error(const char *name)
{
	error_call_init_proc();

	{
		unsigned hash  = cstring_hash_value(name) % ERROR_TABLE_SIZE;
		ErrorT *entry  = error_table[hash];

		while (entry) {
			if (!strcmp(entry->name, name)) {
				return entry;
			}

			entry = entry->next;
		}

		return NULL;
	}
}

void *
error_data(ErrorT *error)
{
	return error->data;
}

void
error_report(ErrorT *error, ErrorprocP proc, void *closure)
{
	if (error->severity >= min_severity) {
		write_error_list(ostream_error, error_prefix, error, NULL, NULL);
		write_error_list(ostream_error, error->error_list, error, proc,
			closure);
		write_newline(ostream_error);
		ostream_flush(ostream_error);
	}

	if (error->severity > max_reported) {
		max_reported = error->severity;
	}

	if (error->severity >= ERROR_SEVERITY_FATAL) {
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
	return min_severity;
}

ESeverityT
error_max_reported_severity(void)
{
	return max_reported;
}

void
error_set_severity_message(ESeverityT severity, const char *message)
{
	severity_data[severity].estring->contents = message;
}

BoolT
error_set_prefix_message(const char *message)
{
	ErrorListT *error_list = error_parse_message(message);

	if (error_list == NULL) {
		return FALSE;
	}

	error_deallocate_error_list(error_prefix);
	error_prefix = error_list;

	return TRUE;
}

EStringT *
error_define_string(const char *name, const char *contents)
{
	unsigned hash     = cstring_hash_value(name) % STRING_TABLE_SIZE;
	EStringT **entryp = &string_table[hash];
	EStringT *entry;

	while ((entry = *entryp) != NULL) {
		assert(!!(strcmp)(entry->name, name));
		entryp = &entry->next;
	}

	entry           = ALLOCATE(EStringT);
	entry->next     = NULL;
	entry->name     = name;
	entry->contents = contents;
	*entryp         = entry;

	return entry;
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
error_redefine_string(const char *name, const char *contents)
{
	unsigned hash  = cstring_hash_value(name) % STRING_TABLE_SIZE;
	EStringT *entry = string_table[hash];

	while (entry) {
		if (!strcmp(entry->name, name)) {
			entry->contents = contents;
			return TRUE;
		}

		entry = entry->next;
	}

	return FALSE;
}

EStringT *
error_lookup_string(const char *name)
{
	unsigned hash   = cstring_hash_value(name) % STRING_TABLE_SIZE;
	EStringT *entry = string_table[hash];

	while (entry) {
		if (!strcmp(entry->name, name)) {
			return entry;
		}

		entry = entry->next;
	}

	return NULL;
}

const char *
error_string_contents(EStringT *estring)
{
	return estring->contents;
}
