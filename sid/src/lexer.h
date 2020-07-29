/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * lexer.h - SID lexical analyser.
 *
 * See the file "lexer.c" for more information.
 */

#ifndef H_LEXER
#define H_LEXER

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dstring.h>
#include <exds/istream.h>
#include  "lexi_lexer.h"

struct lexi_state lexi_current_state ;

/*
 * Note:
 *
 * It is important that any changes to this enumerated type declaration are
 * reflected in the "parser.sid" file.
 */
typedef enum {
	LEXER_TOK_BLT_HTYPES,
	LEXER_TOK_BLT_HTERMINALS,
	LEXER_TOK_BLT_HPRODUCTIONS,
	LEXER_TOK_BLT_HENTRY,
	LEXER_TOK_IDENTIFIER,
	LEXER_TOK_BASIC,
	LEXER_TOK_TYPEMARK,
	LEXER_TOK_OPEN_HTUPLE,
	LEXER_TOK_CLOSE_HTUPLE,
	LEXER_TOK_ARROW,
	LEXER_TOK_TERMINATOR,
	LEXER_TOK_BEGIN_HACTION,
	LEXER_TOK_END_HACTION,
	LEXER_TOK_DEFINE,
	LEXER_TOK_BEGIN_HRULE,
	LEXER_TOK_END_HRULE,
	LEXER_TOK_ALT_HSEP,
	LEXER_TOK_HANDLER_HSEP,
	LEXER_TOK_EMPTY,
	LEXER_TOK_PRED_HRESULT,
	LEXER_TOK_IGNORE,
	LEXER_TOK_SCOPEMARK,
	LEXER_TOK_BEGIN_HSCOPE,
	LEXER_TOK_END_HSCOPE,
	LEXER_TOK_SEPARATOR,
	LEXER_TOK_REFERENCE,
	LEXER_TOK_EOF,
	LEXER_TOK_ERROR
} LexerTokenT;

typedef struct LexT {
	LexerTokenT t;
	union {
		NStringT string;
	} u;
} LexT;

typedef struct LexerStreamT {
	IStreamT istream;
	LexT token;
	LexerTokenT saved_terminal;
} LexerStreamT;

void	lexer_init(LexerStreamT *, IStreamT *);
void	lexer_close(LexerStreamT *);
const char	*lexer_stream_name(LexerStreamT *);
unsigned	lexer_stream_line(LexerStreamT *);
LexerTokenT	lexer_get_terminal(LexerStreamT *);
void	lexer_next_token(LexerStreamT *);
NStringT	*lexer_string_value(LexerStreamT *);
void	lexer_save_terminal(LexerStreamT *, LexerTokenT);
void	lexer_restore_terminal(LexerStreamT *);


/*
 * Interfaces for the generated lexer.
 */
int lexi_getchar(void);
int read_identifier(int c);
int read_basic(void);
int read_builtin(void);
int lexi_unknown_token(int c0);

/* XXX remove once lexi provides opaque pointers */
LexerStreamT *lexer_stream;

#endif /* !defined (H_LEXER) */
