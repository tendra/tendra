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
 * c-lexer.h --- SID C lexical analyser.
 *
 * See the file "c-lexer.c" for details.
 */

#ifndef H_C_LEXER
#define H_C_LEXER

#include "c-code.h"
#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dstring.h>
#include <exds/istream.h>
#include "c-lexi_lexer.h"


extern struct c_lexi_state c_lexer_current_state ;

/*
 * Note:
 *
 * It is important that any changes to this enumerated type declaration are
 * reflected in the "c-parser.sid" file.
 */
typedef enum {
    C_TOK_BLT_PREFIXES,
    C_TOK_BLT_MAPS,
    C_TOK_BLT_PERSISTENTS,
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

	/* Action code block tokens */
	C_TOK_ACT_AT,
	C_TOK_ACT_EXCEPTION,
	C_TOK_ACT_TERMINAL,
	C_TOK_ACT_ADVANCE,
	C_TOK_ACT_LABEL,
	C_TOK_ACT_REFERENCE,
	C_TOK_ACT_IDENTIFIER,
	C_TOK_ACT_MODIFIABLE,
	C_TOK_ACT_CODESTRING,
	C_TOK_ACT_EOF,
	C_TOK_ACT_CODESTART,
	C_TOK_ACT_CODEEND,

	C_TOK_ERROR
} CTokenT;

typedef struct CLexT {
    CTokenT			t;
    union {
	NStringT		string;
	CCodeT *			code;
    } u;
} CLexT;

typedef struct CLexerStreamT {
    IStreamT			istream;
    CLexT			token;
    CTokenT			saved_terminal;
} CLexerStreamT;

/* XXX Remove once lexi provides identifier support */
extern int c_lexer_support_read_id(int c, int rettok, enum c_lexi_groups bodygroup);
extern int c_lexer_read_builtin(int c0, int c1);
extern int c_lexer_act_read_string(int c);
extern int c_lexer_unknown_token(int c);

/* Lexi interface support */
extern int c_lexi_getchar(void);

extern void		c_lexer_init(CLexerStreamT *, IStreamT *);
extern void		c_lexer_close(CLexerStreamT *);
extern char *		c_lexer_stream_name(CLexerStreamT *);
extern unsigned		c_lexer_stream_line(CLexerStreamT *);
extern CTokenT		c_lexer_get_terminal(CLexerStreamT *);
extern void		c_lexer_next_token(CLexerStreamT *);
extern NStringT *		c_lexer_string_value(CLexerStreamT *);
extern CCodeT *		c_lexer_code_value(CLexerStreamT *);
extern void		c_lexer_save_terminal(CLexerStreamT *, CTokenT);
extern void		c_lexer_restore_terminal(CLexerStreamT *);

/* XXX remove once lexi provides opaque pointers */
extern CLexerStreamT *c_lexer_stream;

#endif /* !defined (H_C_LEXER) */
