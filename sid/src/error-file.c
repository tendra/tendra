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


/**** error-file.c --- Error file parsing routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the error file parsing facility specified in the file
 * "error-file.h".  See that file for more details.
 *
 **** Change Log:
 * $Log: error-file.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1994/12/12  11:44:37  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.2  1994/08/22  09:36:44  smf
 * Fixed bug DR114:ids-too-long.
 *
 * Revision 1.1.1.1  1994/07/25  16:05:49  smf
 * Initial import of library shared files.
 *
**/

/****************************************************************************/

#include "error-file.h"
#include "dstring.h"
#include "error.h"
#include "gen-errors.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int ErrorFileTagT, *ErrorFileTagP;
#define EFTOKEN_NAME		(0)
#define EFTOKEN_STRING		(1)
#define EFTOKEN_BLT_STRINGS	(2)
#define EFTOKEN_BLT_PREFIX	(3)
#define EFTOKEN_BLT_ERRORS	(4)
#define EFTOKEN_EOF		(5)
#else
typedef enum {
    EFTOKEN_NAME,
    EFTOKEN_STRING,
    EFTOKEN_BLT_STRINGS,
    EFTOKEN_BLT_PREFIX,
    EFTOKEN_BLT_ERRORS,
    EFTOKEN_EOF
} ErrorFileTagT, *ErrorFileTagP;
#endif /* defined (FS_NO_ENUM) */

typedef struct ErrorFileLexT {
    ErrorFileTagT		tag;
    union {
	CStringP		string;
    } u;
} ErrorFileLexT, *ErrorFileLexP;

#ifdef FS_NO_ENUM
typedef int ErrorFileTokenT, *ErrorFileTokenP;
#define EFN_BUILTIN	(0)
#define EFN_NAME	(1)
#define EFN_STRING	(2)
#else
typedef enum {
    EFN_BUILTIN,
    EFN_NAME,
    EFN_STRING
} ErrorFileTokenT, *ErrorFileTokenP;
#endif /* defined (FS_NO_ENUM) */

/*--------------------------------------------------------------------------*/

static BoolT
error_file_skip_white_space PROTO_N ((istream, c_ref))
			    PROTO_T (IStreamP istream X
				     char    *c_ref)
{
    BoolT comment = FALSE;

    for (;;) {
	char c;

      redo:
	switch (c = ISTREAM_READ_CHAR (istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL (istream, redo, eof);
	    break;
	  case '\n':
	    istream_inc_line (istream);
	    comment = FALSE;
	    break;
	  case '#':
	    comment = TRUE;
	    break;
	  default:
	    if ((!comment) && (!syntax_is_white_space (c))) {
		*c_ref = c;
		return (TRUE);
	    }
	}
    }
  eof:
    return (FALSE);
}

static void
error_file_null_character PROTO_N ((istream, type))
			  PROTO_T (IStreamP        istream X
				   ErrorFileTokenT type)
{
    switch (type) EXHAUSTIVE {
      case EFN_NAME:
	E_errf_null_character_in_name (istream);
	UNREACHED;
      case EFN_BUILTIN:
	E_errf_null_char_in_builtin (istream);
	UNREACHED;
      case EFN_STRING:
	E_errf_null_character_in_string (istream);
	UNREACHED;
    }
}

static void
error_file_newline PROTO_N ((istream, type))
		   PROTO_T (IStreamP        istream X
			    ErrorFileTokenT type)
{
    switch (type) EXHAUSTIVE {
      case EFN_NAME:
	E_errf_newline_in_name (istream);
	UNREACHED;
      case EFN_BUILTIN:
	E_errf_newline_in_builtin (istream);
	UNREACHED;
      case EFN_STRING:
	E_errf_newline_in_string (istream);
	UNREACHED;
    }
}

static void
error_file_illegal_escape PROTO_N ((istream, type))
			  PROTO_T (IStreamP        istream X
				   ErrorFileTokenT type)
{
    switch (type) EXHAUSTIVE {
      case EFN_NAME:
	E_errf_illegal_escape_in_name (istream);
	UNREACHED;
      case EFN_BUILTIN:
	E_errf_illegal_esc_in_builtin (istream);
	UNREACHED;
      case EFN_STRING:
	E_errf_illegal_escape_in_string (istream);
	UNREACHED;
    }
}

static void
error_file_eof PROTO_N ((istream, type))
	       PROTO_T (IStreamP        istream X
			ErrorFileTokenT type)
{
    switch (type) EXHAUSTIVE {
      case EFN_NAME:
	E_errf_eof_in_name (istream);
	UNREACHED;
      case EFN_BUILTIN:
	E_errf_eof_in_builtin (istream);
	UNREACHED;
      case EFN_STRING:
	E_errf_eof_in_string (istream);
	UNREACHED;
    }
}

static void
error_file_read_until PROTO_N ((istream, term, type, token))
		      PROTO_T (IStreamP        istream X
			       char            term X
			       ErrorFileTokenT type X
			       ErrorFileLexP   token)
{
    DStringT dstring;

    dstring_init (&dstring);
    for (;;) {
	char c;

      redo:
	switch (c = ISTREAM_READ_CHAR (istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL (istream, redo, eof);
	    error_file_null_character (istream, type);
	    UNREACHED;
	  case '\n':
	    istream_inc_line (istream);
	    error_file_newline (istream, type);
	    UNREACHED;
	  default:
	    if (c == term) {
		CStringP tmp;

		tmp = dstring_to_cstring (&dstring);
		dstring_destroy (&dstring);
		token->u.string = tmp;
		return;
	    } else if (c == '\\') {
		switch (istream_read_escaped_char (istream, &c)) EXHAUSTIVE {
		  case ISTREAM_STAT_READ_CHAR:
		    if (c == '\0') {
			error_file_null_character (istream, type);
			UNREACHED;
		    }
		    dstring_append_char (&dstring, c);
		    break;
		  case ISTREAM_STAT_SYNTAX_ERROR:
		    error_file_illegal_escape (istream, type);
		    UNREACHED;
		  case ISTREAM_STAT_NO_CHAR:
		    /*NOTHING*/
		    break;
		}
	    } else {
		dstring_append_char (&dstring, c);
	    }
	    break;
	}
    }
  eof:
    error_file_eof (istream, type);
    UNREACHED;
}

static void
error_file_check_builtin PROTO_N ((istream, token))
			 PROTO_T (IStreamP      istream X
				  ErrorFileLexP token)
{
    if (cstring_ci_equal (token->u.string, "strings")) {
	token->tag = EFTOKEN_BLT_STRINGS;
    } else if (cstring_ci_equal (token->u.string, "prefix")) {
	token->tag = EFTOKEN_BLT_PREFIX;
    } else if (cstring_ci_equal (token->u.string, "errors")) {
	token->tag = EFTOKEN_BLT_ERRORS;
    } else {
	E_errf_unknown_builtin (istream, token->u.string);
	UNREACHED;
    }
    DEALLOCATE (token->u.string);
}

static void
error_file_next_token PROTO_N ((istream, token))
		      PROTO_T (IStreamP      istream X
			       ErrorFileLexP token)
{
    char c;

    if (error_file_skip_white_space (istream, &c)) {
	switch (c) {
	  case '%':
	    error_file_read_until (istream, '%', EFN_BUILTIN, token);
	    error_file_check_builtin (istream, token);
	    break;
	  case '\'':
	    error_file_read_until (istream, '\'', EFN_NAME, token);
	    token->tag = EFTOKEN_NAME;
	    break;
	  case '"':
	    error_file_read_until (istream, '"', EFN_STRING, token);
	    token->tag = EFTOKEN_STRING;
	    break;
	  default:
	    E_errf_illegal_character (istream, c);
	    UNREACHED;
	}
    } else {
	token->tag = EFTOKEN_EOF;
    }
}

static void
error_file_parse_strings PROTO_N ((istream, token))
			 PROTO_T (IStreamP      istream X
				  ErrorFileLexP token)
{
    while (error_file_next_token (istream, token),
	   (token->tag == EFTOKEN_NAME)) {
	CStringP name = token->u.string;

	if (error_file_next_token (istream, token),
	    (token->tag != EFTOKEN_STRING)) {
	    E_errf_expected_string (istream);
	    UNREACHED;
	} else if (!error_redefine_string (name, token->u.string)) {
	    E_errf_unknown_string (istream, name);
	    UNREACHED;
	}
	DEALLOCATE (name);
    }
}

static void
error_file_parse_prefix PROTO_N ((istream, token))
			PROTO_T (IStreamP      istream X
				 ErrorFileLexP token)
{
    error_file_next_token (istream, token);
    if (token->tag != EFTOKEN_STRING) {
	E_errf_expected_string (istream);
	UNREACHED;
    } else if (!error_set_prefix_message (token->u.string)) {
	E_errf_illegal_message (istream, token->u.string);
	UNREACHED;
    }
    DEALLOCATE (token->u.string);
    error_file_next_token (istream, token);
}

static void
error_file_parse_errors PROTO_N ((istream, token))
			PROTO_T (IStreamP      istream X
				 ErrorFileLexP token)
{
    while (error_file_next_token (istream, token),
	   (token->tag == EFTOKEN_NAME)) {
	CStringP name = token->u.string;

	error_file_next_token (istream, token);
	if (token->tag != EFTOKEN_STRING) {
	    E_errf_expected_string (istream);
	    UNREACHED;
	} else {
	    switch (error_redefine_error (name, token->u.string)) EXHAUSTIVE {
	      case ERROR_STATUS_BAD_ERROR:
		E_errf_unknown_error (istream, name);
		UNREACHED;
	      case ERROR_STATUS_BAD_MESSAGE:
		E_errf_illegal_message (istream, token->u.string);
		UNREACHED;
	      case ERROR_STATUS_SUCCESS:
		/*NOTHING*/
		break;
	    }
	}
	DEALLOCATE (name);
	DEALLOCATE (token->u.string);
    }
}

/*--------------------------------------------------------------------------*/

void
error_file_parse PROTO_N ((name, must_open))
		 PROTO_T (CStringP name X
			  BoolT    must_open)
{
    IStreamT      istream;
    ErrorFileLexT token;

    if (istream_open (&istream, name)) {
	error_file_next_token (&istream, &token);
	while (token.tag != EFTOKEN_EOF) {
	    switch (token.tag) {
	      case EFTOKEN_BLT_STRINGS:
		error_file_parse_strings (&istream, &token);
		break;
	      case EFTOKEN_BLT_PREFIX:
		error_file_parse_prefix (&istream, &token);
		break;
	      case EFTOKEN_BLT_ERRORS:
		error_file_parse_errors (&istream, &token);
		break;
	      default:
		E_errf_expected_section (&istream);
		UNREACHED;
	    }
	}
	istream_close (&istream);
    } else if (must_open) {
	E_errf_cannot_open (name);
	UNREACHED;
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
**/
