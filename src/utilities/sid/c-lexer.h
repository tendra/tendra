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


/*** c-lexer.h --- SID C lexical analyser.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "c-lexer.c" for details.
 *
 *** Change Log:
 * $Log: c-lexer.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:42  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:55:58  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:14  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_C_LEXER
#define H_C_LEXER

#include "os-interface.h"
#include "c-code.h"
#include "dstring.h"
#include "istream.h"

/**** Note:
 *
 * It is important that any changes to this enumerated type declaration are
 * reflected in the "c-parser.sid" file.
**/

#ifdef FS_NO_ENUM
typedef int CTokenT, *CTokenP;
#define C_TOK_BLT_PREFIXES		(0)
#define C_TOK_BLT_MAPS			(1)
#define C_TOK_BLT_ASSIGNMENTS		(2)
#define C_TOK_BLT_TERMINALS		(3)
#define C_TOK_BLT_HEADER		(4)
#define C_TOK_BLT_ACTIONS		(5)
#define C_TOK_BLT_TRAILER		(6)
#define C_TOK_BLT_RESULT_ASSIGN		(7)
#define C_TOK_SID_IDENTIFIER		(8)
#define C_TOK_C_IDENTIFIER		(9)
#define C_TOK_SEPARATOR			(10)
#define C_TOK_TYPEMARK			(11)
#define C_TOK_TERMINATOR		(12)
#define C_TOK_BEGIN_ACTION		(13)
#define C_TOK_DEFINE			(14)
#define C_TOK_END_ACTION		(15)
#define C_TOK_CODE			(16)
#define C_TOK_ARROW			(17)
#define C_TOK_OPEN_TUPLE		(18)
#define C_TOK_CLOSE_TUPLE		(19)
#define C_TOK_BLT_PARAM_ASSIGN		(20)
#define C_TOK_REFERENCE			(21)
#define C_TOK_EOF			(22)
#define C_TOK_ERROR			(23)
#else
typedef enum {
    C_TOK_BLT_PREFIXES,
    C_TOK_BLT_MAPS,
    C_TOK_BLT_ASSIGNMENTS,
    C_TOK_BLT_TERMINALS,
    C_TOK_BLT_HEADER,
    C_TOK_BLT_ACTIONS,
    C_TOK_BLT_TRAILER,
    C_TOK_BLT_RESULT_ASSIGN,
    C_TOK_SID_IDENTIFIER,
    C_TOK_C_IDENTIFIER,
    C_TOK_SEPARATOR,
    C_TOK_TYPEMARK,
    C_TOK_TERMINATOR,
    C_TOK_BEGIN_ACTION,
    C_TOK_DEFINE,
    C_TOK_END_ACTION,
    C_TOK_CODE,
    C_TOK_ARROW,
    C_TOK_OPEN_TUPLE,
    C_TOK_CLOSE_TUPLE,
    C_TOK_BLT_PARAM_ASSIGN,
    C_TOK_REFERENCE,
    C_TOK_EOF,
    C_TOK_ERROR
} CTokenT, *CTokenP;
#endif /* defined (FS_NO_ENUM) */

typedef struct CLexT {
    CTokenT			t;
    union {
	NStringT		string;
	CCodeP			code;
    } u;
} CLexT, *CLexP;

typedef struct CLexerStreamT {
    IStreamT			istream;
    CLexT			token;
    CTokenT			saved_terminal;
} CLexerStreamT, *CLexerStreamP;

/*--------------------------------------------------------------------------*/

extern void			c_lexer_init
	PROTO_S ((CLexerStreamP, IStreamP));
extern void			c_lexer_close
	PROTO_S ((CLexerStreamP));
extern CStringP			c_lexer_stream_name
	PROTO_S ((CLexerStreamP));
extern unsigned			c_lexer_stream_line
	PROTO_S ((CLexerStreamP));
extern CTokenT			c_lexer_get_terminal
	PROTO_S ((CLexerStreamP));
extern void			c_lexer_next_token
	PROTO_S ((CLexerStreamP));
extern NStringP			c_lexer_string_value
	PROTO_S ((CLexerStreamP));
extern CCodeP			c_lexer_code_value
	PROTO_S ((CLexerStreamP));
extern void			c_lexer_save_terminal
	PROTO_S ((CLexerStreamP, CTokenT));
extern void			c_lexer_restore_terminal
	PROTO_S ((CLexerStreamP));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define c_lexer_close(s) (istream_close (&((s)->istream)))
#define c_lexer_stream_name(s) (istream_name (&((s)->istream)))
#define c_lexer_stream_line(s) (istream_line (&((s)->istream)))
#define c_lexer_get_terminal(s) ((s)->token.t)
#define c_lexer_string_value(s) (&((s)->token.u.string))
#define c_lexer_code_value(s) ((s)->token.u.code)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_C_LEXER) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output")
 * eval: (include::add-path-entry "../c-output" "../generated")
 * end:
**/
