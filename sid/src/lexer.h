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


/*** lexer.h --- SID lexical analyser.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "lexer.c" for more information.
 *
 *** Change Log:
 * $Log: lexer.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:42  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:57:28  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:24  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_LEXER
#define H_LEXER

#include "os-interface.h"
#include "dstring.h"
#include "istream.h"

/**** Note:
 *
 * It is important that any changes to this enumerated type declaration are
 * reflected in the "parser.sid" file.
**/

#ifdef FS_NO_ENUM
typedef int LexerTokenT, *LexerTokenP;
#define LEXER_TOK_BLT_TYPES		(0)
#define LEXER_TOK_BLT_TERMINALS		(1)
#define LEXER_TOK_BLT_PRODUCTIONS	(2)
#define LEXER_TOK_BLT_ENTRY		(3)
#define LEXER_TOK_IDENTIFIER		(4)
#define LEXER_TOK_TYPEMARK		(5)
#define LEXER_TOK_OPEN_TUPLE		(6)
#define LEXER_TOK_CLOSE_TUPLE		(7)
#define LEXER_TOK_ARROW			(8)
#define LEXER_TOK_TERMINATOR		(9)
#define LEXER_TOK_BEGIN_ACTION		(10)
#define LEXER_TOK_END_ACTION		(11)
#define LEXER_TOK_DEFINE		(12)
#define LEXER_TOK_BEGIN_RULE		(13)
#define LEXER_TOK_END_RULE		(14)
#define LEXER_TOK_ALT_SEP		(15)
#define LEXER_TOK_HANDLER_SEP		(16)
#define LEXER_TOK_EMPTY			(17)
#define LEXER_TOK_PRED_RESULT		(18)
#define LEXER_TOK_IGNORE		(19)
#define LEXER_TOK_SCOPEMARK		(20)
#define LEXER_TOK_BEGIN_SCOPE		(21)
#define LEXER_TOK_END_SCOPE		(22)
#define LEXER_TOK_SEPARATOR		(23)
#define LEXER_TOK_REFERENCE		(24)
#define LEXER_TOK_EOF			(25)
#define LEXER_TOK_ERROR			(26)
#else
typedef enum {
    LEXER_TOK_BLT_TYPES,
    LEXER_TOK_BLT_TERMINALS,
    LEXER_TOK_BLT_PRODUCTIONS,
    LEXER_TOK_BLT_ENTRY,
    LEXER_TOK_IDENTIFIER,
    LEXER_TOK_TYPEMARK,
    LEXER_TOK_OPEN_TUPLE,
    LEXER_TOK_CLOSE_TUPLE,
    LEXER_TOK_ARROW,
    LEXER_TOK_TERMINATOR,
    LEXER_TOK_BEGIN_ACTION,
    LEXER_TOK_END_ACTION,
    LEXER_TOK_DEFINE,
    LEXER_TOK_BEGIN_RULE,
    LEXER_TOK_END_RULE,
    LEXER_TOK_ALT_SEP,
    LEXER_TOK_HANDLER_SEP,
    LEXER_TOK_EMPTY,
    LEXER_TOK_PRED_RESULT,
    LEXER_TOK_IGNORE,
    LEXER_TOK_SCOPEMARK,
    LEXER_TOK_BEGIN_SCOPE,
    LEXER_TOK_END_SCOPE,
    LEXER_TOK_SEPARATOR,
    LEXER_TOK_REFERENCE,
    LEXER_TOK_EOF,
    LEXER_TOK_ERROR
} LexerTokenT, *LexerTokenP;
#endif /* defined (FS_NO_ENUM) */

typedef struct LexT {
    LexerTokenT			t;
    union {
	NStringT		string;
    } u;
} LexT, *LexP;

typedef struct LexerStreamT {
    IStreamT			istream;
    LexT			token;
    LexerTokenT			saved_terminal;
} LexerStreamT, *LexerStreamP;

/*--------------------------------------------------------------------------*/

extern void			lexer_init
	PROTO_S ((LexerStreamP, IStreamP));
extern void			lexer_close
	PROTO_S ((LexerStreamP));
extern CStringP			lexer_stream_name
	PROTO_S ((LexerStreamP));
extern unsigned			lexer_stream_line
	PROTO_S ((LexerStreamP));
extern LexerTokenT		lexer_get_terminal
	PROTO_S ((LexerStreamP));
extern void			lexer_next_token
	PROTO_S ((LexerStreamP));
extern NStringP			lexer_string_value
	PROTO_S ((LexerStreamP));
extern void			lexer_save_terminal
	PROTO_S ((LexerStreamP, LexerTokenT));
extern void			lexer_restore_terminal
	PROTO_S ((LexerStreamP));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define lexer_close(s) (istream_close (&((s)->istream)))
#define lexer_stream_name(s) (istream_name (&((s)->istream)))
#define lexer_stream_line(s) (istream_line (&((s)->istream)))
#define lexer_get_terminal(s) ((s)->token.t)
#define lexer_string_value(s) (&((s)->token.u.string))
#endif /* defined (FS_FAST) */

#endif /* !defined (H_LEXER) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../generated")
 * end:
**/
