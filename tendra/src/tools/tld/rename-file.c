/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**** rename-file.c --- Routines for parsing rename file.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
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
 *
 **** Change Log:*/

/****************************************************************************/

#include "rename-file.h"
#include "dstring.h"
#include "msgcat.h"
#include "istream.h"
#include "nstring-list.h"
#include "syntax.h"
#include "tenapp.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int RenameTagT, *RenameTagP;
#define RTOK_SHAPE		(0)
#define RTOK_NAME		(1)
#define RTOK_SEMI		(2)
#define RTOK_EOF		(3)
#else
typedef enum {
    RTOK_SHAPE,
    RTOK_NAME,
    RTOK_SEMI,
    RTOK_EOF
} RenameTagT, *RenameTagP;
#endif /* defined (FS_NO_ENUM) */

typedef struct RenameTokenT {
    RenameTagT			tag;
    union {
		NStringT		shape;
		NameKeyT		name;
    } u;
} RenameTokenT, *RenameTokenP;

/*--------------------------------------------------------------------------*/

static BoolT
rename_file_skip_white_space(IStreamP istream,
							 char *c_ref)
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
			break;
		}
    }
  eof:
    return (FALSE);
}

static void
rename_file_read_unique(IStreamP istream,
						RenameTokenP token)
{
    NameKeyP          name   = &(token->u.name);
    unsigned          length = 1;
    DStringT          dstring;
    NStringT          nstring;
    NStringListT      list;
    NStringListEntryP entry;
    unsigned          i;

    dstring_init (&dstring);
    nstring_list_init (&list);
    for (;;) {
		char c;

      redo:
		switch (c = ISTREAM_READ_CHAR (istream)) {
		case '\0':
			ISTREAM_HANDLE_NULL (istream, redo, eof);
			dstring_append_char (&dstring, '\0');
			break;
		case '\n':
			istream_inc_line (istream);
			MSG_rename_unexpected_newline (istream);
			break;
		case ']':
			dstring_to_nstring (&dstring, &nstring);
			nstring_list_append (&list, &nstring);
			dstring_destroy (&dstring);
			name_key_init_unique (name, length);
			for (i = 0, entry = nstring_list_head (&list); entry;
				 i ++, entry = nstring_list_entry_deallocate (entry)) {
				NStringP component = nstring_list_entry_string (entry);

				name_key_set_component (name, i, component);
			}
			token->tag = RTOK_NAME;
			return;
		case '[':
			MSG_rename_illegal_char (istream, c);
			break;
		case '.':
			dstring_to_nstring (&dstring, &nstring);
			nstring_list_append (&list, &nstring);
			dstring_destroy (&dstring);
			dstring_init (&dstring);
			length ++;
			break;
		case '\\':
			switch (istream_read_escaped_char (istream, &c)) EXHAUSTIVE {
			case ISTREAM_STAT_READ_CHAR:
				dstring_append_char (&dstring, c);
				break;
			case ISTREAM_STAT_SYNTAX_ERROR:
				MSG_rename_illegal_escape (istream);
				break;
			case ISTREAM_STAT_NO_CHAR:
				/*NOTHING*/
				break;
			}
			break;
		default:
			dstring_append_char (&dstring, c);
			break;
		}
    }
  eof:
    MSG_rename_unexpected_eof (istream);
    dstring_destroy (&dstring);
    for (entry = nstring_list_head (&list); entry;
		 entry = nstring_list_entry_deallocate (entry)) {
		nstring_destroy (nstring_list_entry_string (entry));
    }
    token->tag = RTOK_EOF;
}

static void
rename_file_read_shape(IStreamP istream, RenameTokenP token)
{
    DStringT dstring;

    dstring_init (&dstring);
    for (;;) {
		char c;

      redo:
		switch (c = ISTREAM_READ_CHAR (istream)) {
		case '\0':
			ISTREAM_HANDLE_NULL (istream, redo, eof);
			dstring_append_char (&dstring, '\0');
			break;
		case '\n':
			istream_inc_line (istream);
			MSG_rename_unexpected_newline (istream);
			break;
		case '\'':
			dstring_to_nstring (&dstring, &(token->u.shape));
			dstring_destroy (&dstring);
			token->tag = RTOK_SHAPE;
			return;
		case '\\':
			switch (istream_read_escaped_char (istream, &c)) EXHAUSTIVE {
			case ISTREAM_STAT_READ_CHAR:
				dstring_append_char (&dstring, c);
				break;
			case ISTREAM_STAT_SYNTAX_ERROR:
				MSG_rename_illegal_escape (istream);
				break;
			case ISTREAM_STAT_NO_CHAR:
				/*NOTHING*/
				break;
			}
			break;
		default:
			dstring_append_char (&dstring, c);
			break;
		}
    }
  eof:
    MSG_rename_unexpected_eof (istream);
    dstring_destroy (&dstring);
    token->tag = RTOK_EOF;
}

static void
rename_file_read_string(IStreamP istream,
						RenameTokenP token)
{
    DStringT dstring;
    NStringT nstring;

    dstring_init (&dstring);
    for (;;) {
		char c;

      redo:
		switch (c = ISTREAM_READ_CHAR (istream)) {
		case '\0':
			ISTREAM_HANDLE_NULL (istream, redo, eof);
			dstring_append_char (&dstring, '\0');
			break;
		case '\n':
			istream_inc_line (istream);
			MSG_rename_unexpected_newline (istream);
			break;
		case '"':
			dstring_to_nstring (&dstring, &nstring);
			dstring_destroy (&dstring);
			name_key_init_string (&(token->u.name), &nstring);
			token->tag = RTOK_NAME;
			return;
		case '[': case ']': case '.':
			MSG_rename_illegal_char (istream, c);
			break;
		case '\\':
			switch (istream_read_escaped_char (istream, &c)) EXHAUSTIVE {
			case ISTREAM_STAT_READ_CHAR:
				dstring_append_char (&dstring, c);
				break;
			case ISTREAM_STAT_SYNTAX_ERROR:
				MSG_rename_illegal_escape (istream);
				break;
			case ISTREAM_STAT_NO_CHAR:
				/*NOTHING*/
				break;
			}
			break;
		default:
			dstring_append_char (&dstring, c);
			break;
		}
    }
  eof:
    MSG_rename_unexpected_eof (istream);
    dstring_destroy (&dstring);
    token->tag = RTOK_EOF;
}

static void
rename_file_next_token(IStreamP istream, RenameTokenP token)
{
    char c;

  again:
    if (rename_file_skip_white_space (istream, &c)) {
		switch (c) {
		case '[':
			rename_file_read_unique (istream, token);
			break;
		case '\'':
			rename_file_read_shape (istream, token);
			break;
		case '"':
			rename_file_read_string (istream, token);
			break;
		case ';':
			token->tag = RTOK_SEMI;
			break;
		default:
			MSG_rename_illegal_char (istream, c);
			goto again;
		}
    } else {
		token->tag = RTOK_EOF;
    }
}

static void
rename_file_parse_names(IStreamP istream,
						NStringP shape, ArgDataP arg_data,
						RenameTokenP token)
{
    rename_file_next_token (istream, token);
    while (token->tag == RTOK_NAME) {
		NameKeyT name;

		name_key_assign (&name, &(token->u.name));
		rename_file_next_token (istream, token);
		if (token->tag != RTOK_NAME) {
			MSG_rename_expected_name (istream);
			name_key_destroy (&name);
			if (token->tag != RTOK_SEMI) {
				return;
			}
			rename_file_next_token (istream, token);
		} else {
			NameKeyT to_name;

			name_key_assign (&to_name, &(token->u.name));
			arg_data_add_rename (arg_data, shape, &name, &to_name);
			rename_file_next_token (istream, token);
			if (token->tag != RTOK_SEMI) {
				MSG_rename_expected_semi (istream);
			} else {
				rename_file_next_token (istream, token);
			}
		}
    }
}

static void
rename_file_parse_1(IStreamP istream, ArgDataP arg_data)
{
    BoolT        need_error = TRUE;
    RenameTokenT token;
    NStringT     shape;

    rename_file_next_token (istream, &token);
    while (token.tag != RTOK_EOF) {
		switch (token.tag) {
		case RTOK_SHAPE:
			nstring_assign (&shape, &(token.u.shape));
			rename_file_parse_names (istream, &shape, arg_data, &token);
			nstring_destroy (&shape);
			need_error = TRUE;
			break;
		case RTOK_NAME:
			name_key_destroy (&(token.u.name));
			FALL_THROUGH;
		default:
			if (need_error) {
				MSG_rename_expected_shape (istream);
				need_error = FALSE;
			}
			rename_file_next_token (istream, &token);
			break;
		}
    }
}

/*--------------------------------------------------------------------------*/

void
rename_file_parse(char *name, ArgDataP arg_data)
{
    IStreamT istream;

    if (istream_open (&istream, name)) {
		rename_file_parse_1 (&istream, arg_data);
		istream_close (&istream);
    } else {
		MSG_cant_open_rename_file (name);
    }
    tenapp_checkerrors(MSG_SEV_ERROR);
}
