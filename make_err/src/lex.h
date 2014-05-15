/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LEX_INCLUDED
#define LEX_INCLUDED


extern void process_file(char *);
extern int read_token(void);
extern char *first_comment;
extern char token_buff[];
extern int crt_lex_token;
extern int saved_lex_token;


#define CURRENT_TERMINAL	crt_lex_token
#define ADVANCE_LEXER		crt_lex_token = read_token()
#define SAVE_LEXER(T)		(saved_lex_token = crt_lex_token,\
                                  crt_lex_token = (T))
#define RESTORE_LEXER		(crt_lex_token = saved_lex_token)


#endif
