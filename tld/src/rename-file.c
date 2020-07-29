/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rename-file.c - Routines for parsing rename file.
 *
 * This file provides the routines that parse the rename file.  The rename
 * file has the following format.
 *
 *	'shape'
 *		"name1" "name2";
 *		"name3" [unique.4];
 *
 * Where shape names are enclosed in single quotes, string names are enclosed
 * in double quotes, and uniques are written using the normal unique syntax.
 * A single shape name may be followed by any number of name pairs, each of
 * which is terminated by a semi-colon.
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dstring.h>
#include <exds/istream.h>
#include <exds/nstring-list.h>
#include <exds/error.h>

#include "adt/solve-cycles.h"

#include "rename-file.h"

typedef enum {
    RTOK_SHAPE,
    RTOK_NAME,
    RTOK_SEMI,
    RTOK_EOF
} RenameTagT;

typedef struct RenameTokenT {
    RenameTagT			tag;
    union {
	NStringT		shape;
	NameKeyT		name;
    } u;
} RenameTokenT;

static bool
rename_file_skip_white_space(IStreamT *istream,				      char    *c_ref)
{
    bool comment = false;

    for (;;) {
	char c;

      redo:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL(istream, redo, eof);
	    break;
	  case '\n':
	    istream_inc_line(istream);
	    comment = false;
	    break;
	  case '#':
	    comment = true;
	    break;
	  default:
	    if ((!comment) && (!isspace(c))) {
		*c_ref = c;
		return true;
	    }
	    break;
	}
    }
  eof:
    return false;
}

static void
rename_file_read_unique(IStreamT *    istream,				 RenameTokenT *token)
{
    NameKeyT *         name   = & (token->u.name);
    unsigned          length = 1;
    DStringT          dstring;
    NStringT          nstring;
    NStringListT      list;
    NStringListEntryT *entry;
    unsigned          i;

    dstring_init(&dstring);
    nstring_list_init(&list);
    for (;;) {
	char c;

      redo:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL(istream, redo, eof);
	    dstring_append_char(&dstring, '\0');
	    break;
	  case '\n':
	    istream_inc_line(istream);
		error_posn(ERR_SERIOUS, 
		istream_name(istream), (int) istream_line(istream), 
		"Unexpected newline");
	    break;
	  case ']':
	    dstring_to_nstring(&dstring, &nstring);
	    nstring_list_append(&list, &nstring);
	    dstring_destroy(&dstring);
	    name_key_init_unique(name, length);
 	    for (i = 0, entry = nstring_list_head(&list); entry;
		 i++, entry = nstring_list_entry_deallocate(entry)) {
		NStringT *component = nstring_list_entry_string(entry);

		name_key_set_component(name, i, component);
	    }
	    token->tag = RTOK_NAME;
	    return;
	  case '[':
	    break;
		error_posn(ERR_SERIOUS, istream_name(istream), 
			(int) istream_line(istream), 
			"illegal character '%c'", c);
	  case '.':
	    dstring_to_nstring(&dstring, &nstring);
	    nstring_list_append(&list, &nstring);
	    dstring_destroy(&dstring);
	    dstring_init(&dstring);
	    length++;
	    break;
	  case '\\':
	    switch (istream_read_escaped_char(istream, &c)) {
	      case ISTREAM_STAT_READ_CHAR:
		dstring_append_char(&dstring, c);
		break;
	      case ISTREAM_STAT_SYNTAX_ERROR:
		error_posn(ERR_SERIOUS, istream_name(istream), 
			(int) istream_line(istream), "illegal escape sequence");
		break;
	      case ISTREAM_STAT_NO_CHAR:
		/*NOTHING*/
		break;
	    }
	    break;
	  default:
	    dstring_append_char(&dstring, c);
	    break;
	}
    }
  eof:
	error_posn(ERR_SERIOUS, istream_name(istream), 
		(int) istream_line(istream), "unexpected end of file");
    dstring_destroy(&dstring);
    for (entry = nstring_list_head(&list); entry;
	 entry = nstring_list_entry_deallocate(entry)) {
	nstring_destroy(nstring_list_entry_string(entry));
    }
    token->tag = RTOK_EOF;
}

static void
rename_file_read_shape(IStreamT *    istream,				RenameTokenT *token)
{
    DStringT dstring;

    dstring_init(&dstring);
    for (;;) {
	char c;

      redo:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL(istream, redo, eof);
	    dstring_append_char(&dstring, '\0');
	    break;
	  case '\n':
	    istream_inc_line(istream);
		error_posn(ERR_SERIOUS, istream_name(istream), 
			(int) istream_line(istream), "Unexpected newline");
	    break;
	  case '\'':
	    dstring_to_nstring(&dstring, & (token->u.shape));
	    dstring_destroy(&dstring);
	    token->tag = RTOK_SHAPE;
	    return;
	  case '\\':
	    switch (istream_read_escaped_char(istream, &c)) {
	      case ISTREAM_STAT_READ_CHAR:
		dstring_append_char(&dstring, c);
		break;
	      case ISTREAM_STAT_SYNTAX_ERROR:
		error_posn(ERR_SERIOUS, istream_name(istream), 
			(int) istream_line(istream), "illegal escape sequence");
		break;
	      case ISTREAM_STAT_NO_CHAR:
		/*NOTHING*/
		break;
	    }
	    break;
	  default:
	    dstring_append_char(&dstring, c);
	    break;
	}
    }
  eof:
	error_posn(ERR_SERIOUS, istream_name(istream), 
		(int) istream_line(istream), "unexpected end of file");
    dstring_destroy(&dstring);
    token->tag = RTOK_EOF;
}

static void
rename_file_read_string(IStreamT *    istream,				 RenameTokenT *token)
{
    DStringT dstring;
    NStringT nstring;

    dstring_init(&dstring);
    for (;;) {
	char c;

      redo:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL(istream, redo, eof);
	    dstring_append_char(&dstring, '\0');
	    break;
	  case '\n':
	    istream_inc_line(istream);
		error_posn(ERR_SERIOUS, istream_name(istream), 
			(int) istream_line(istream), "Unexpected newline");
	    break;
	  case '"':
	    dstring_to_nstring(&dstring, &nstring);
	    dstring_destroy(&dstring);
	    name_key_init_string(& (token->u.name), &nstring);
	    token->tag = RTOK_NAME;
	    return;
	  case '[': case ']': case '.':
		error_posn(ERR_SERIOUS, istream_name(istream), 
			(int) istream_line(istream), 
			"illegal character '%c'", c);
	    break;
	  case '\\':
	    switch (istream_read_escaped_char(istream, &c)) {
	      case ISTREAM_STAT_READ_CHAR:
		dstring_append_char(&dstring, c);
		break;
	      case ISTREAM_STAT_SYNTAX_ERROR:
		error_posn(ERR_SERIOUS, istream_name(istream), 
			(int) istream_line(istream), "illegal escape sequence");
		break;
	      case ISTREAM_STAT_NO_CHAR:
		/*NOTHING*/
		break;
	    }
	    break;
	  default:
	    dstring_append_char(&dstring, c);
	    break;
	}
    }
  eof:
	error_posn(ERR_SERIOUS, istream_name(istream), 
		(int) istream_line(istream), "unexpected end of file");
    dstring_destroy(&dstring);
    token->tag = RTOK_EOF;
}

static void
rename_file_next_token(IStreamT *    istream,				RenameTokenT *token)
{
    char c;

  again:
    if (rename_file_skip_white_space(istream, &c)) {
	switch (c) {
	  case '[':
	    rename_file_read_unique(istream, token);
	    break;
	  case '\'':
	     rename_file_read_shape(istream, token);
	    break;
	  case '"':
	    rename_file_read_string(istream, token);
	    break;
	  case ';':
	    token->tag = RTOK_SEMI;
	    break;
	  default:
		error_posn(ERR_SERIOUS, istream_name(istream), 
			(int) istream_line(istream), 
			"illegal character '%c'", c);
	    goto again;
	}
    } else {
	token->tag = RTOK_EOF;
    }
}

static void
rename_file_parse_names(IStreamT *    istream,				 NStringT *    shape ,
				 ArgDataT *    arg_data ,
				 RenameTokenT *token)
{
    rename_file_next_token(istream, token);
    while (token->tag == RTOK_NAME) {
	NameKeyT name;

	name_key_assign(&name, & (token->u.name));
	rename_file_next_token(istream, token);
	if (token->tag != RTOK_NAME) {
		error_posn(ERR_SERIOUS, istream_name(istream), 
			(int) istream_line(istream), "expected external name");
	    name_key_destroy(&name);
	    if (token->tag != RTOK_SEMI) {
		return;
	    }
	    rename_file_next_token(istream, token);
	} else {
	    NameKeyT to_name;

	    name_key_assign(&to_name, & (token->u.name));
	    arg_data_add_rename(arg_data, shape, &name, &to_name);
	    rename_file_next_token(istream, token);
	    if (token->tag != RTOK_SEMI) {
		error_posn(ERR_SERIOUS, istream_name(istream), 
			(int) istream_line(istream), "expected semi colon");
	    } else {
		rename_file_next_token(istream, token);
	    }
	}
    }
}

static void
rename_file_parse_1(IStreamT *istream,			     ArgDataT *arg_data)
{
    bool        need_error = true;
    RenameTokenT token;
    NStringT     shape;

    rename_file_next_token(istream, &token);
    while (token.tag != RTOK_EOF) {
	switch (token.tag) {
	  case RTOK_SHAPE:
	    nstring_assign(&shape, & (token.u.shape));
	    rename_file_parse_names(istream, &shape, arg_data, &token);
	    nstring_destroy(&shape);
	    need_error = true;
	    break;
	  case RTOK_NAME:
	    name_key_destroy(& (token.u.name));
	    FALL_THROUGH;
	  default:
	    if (need_error) {
		error_posn(ERR_SERIOUS, istream_name(istream), 
			(int) istream_line(istream), "expected shape name");
		need_error = false;
	    }
	    rename_file_next_token(istream, &token);
	    break;
	}
    }
}

void
rename_file_parse(char * name,			   ArgDataT *arg_data)
{
    IStreamT istream;

    if (istream_open(&istream, name)) {
	rename_file_parse_1(&istream, arg_data);
	istream_close(&istream);
    } else {
	error(ERR_FATAL, "cannot open rename file '%s': %s", 
		name, strerror(errno));
    }
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}
