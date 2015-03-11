/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef PARSE_INCLUDED
#define PARSE_INCLUDED


/*
    TYPE REPRESENTING A PARSER STATE

    This type is used to represent the information to be saved before the
    separate compilation of any saved preprocessing tokens and restored
    afterwards.
*/

typedef struct pstate_tag {
	LOCATION loc;
	OPTIONS *opts;
	int flag[10];
	DECL_SPEC dspec[2];
	NAMESPACE nspace[2];
	STACK(NAMESPACE)nstack[3];
} PARSE_STATE;


/*
    TOKEN EXPANSION STATES

    These values are used as arguments to expand_token to indicate the
    current parsing state.
*/

enum {
	EXPAND_NORMAL,
	EXPAND_AHEAD,
	EXPAND_RESCAN,
	EXPAND_TEMPLATE,
	EXPAND_IDENTIFIER,
	EXPAND_COLON_COLON,
	EXPAND_CHECK_COLON,
	EXPAND_DESTRUCTOR,
	EXPAND_STRING
};


/*
    TOKEN PARSER DECLARATIONS

    The routines in this module are concerned with reading the next lexical
    token from the input file.  They include expand_token which is the top
    level lexical analysis and preprocessing routine.
*/

extern void init_parser(PPTOKEN *);
extern int expand_token(int);
extern int expand_preproc(int);
extern void rescan_template(NAMESPACE);
extern PPTOKEN *patch_tokens(int);
extern PPTOKEN *restore_parser(void);
extern PPTOKEN *read_loc_tokens(PPTOKEN *);
extern void snip_tokens(PPTOKEN *, PPTOKEN *);
extern void save_state(PARSE_STATE *, int);
extern void restore_state(PARSE_STATE *);
extern int crt_state_depth;


/*
    CURRENT TOKEN INFORMATION

    These variables are used to store information about the current lexical
    token as read by expand_token.  crt_lex_token gives the current token
    number, with any additional information being stored in crt_token.
    last_lex_token gives the previous value of crt_lex_token.  Finally
    saved_lex_token is used as a temporary store in exception handling.
*/

extern PPTOKEN *crt_token;
extern NAMESPACE crt_lookup;
extern int crt_lex_token;
extern int saved_lex_token;
extern int last_lex_token;
extern int have_syntax_error;


/*
    PARSER MACROS

    These macros are used by the SID parser to access the output of the
    lexical analysis and preprocessing routines.  CURRENT_TERMINAL gives
    the value of the current lexical token.  ADVANCE_LEXER reads the next
    lexical token.  RESCAN_LEXER rescans the current token.  SAVE_LEXER
    and RESTORE_LEXER are used in exception handling.
*/

#define CURRENT_TERMINAL	crt_lex_token
#define RESTORE_LEXER		crt_lex_token = saved_lex_token;
#define next_token()		expand_token(EXPAND_AHEAD)
#define RESCAN_LEXER		crt_lex_token = expand_token(EXPAND_RESCAN)

#define ADVANCE_LEXER					\
    {							\
	last_lex_token = crt_lex_token;			\
	crt_lex_token = expand_token(EXPAND_NORMAL);	\
    }


#define SAVE_LEXER(T)				\
    {						\
	saved_lex_token = crt_lex_token;	\
	crt_lex_token = (T);			\
    }


#endif
