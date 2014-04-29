/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEX_H
#define LEX_H

#include <stdio.h>

/*
 * PROCEDURE DECLARATIONS
 *
 * These routines and variables give the interface with the lexical
 * analyser.
 */
int read_token(void);
void preproc(FILE *, char *, char *, char *);
void init_keywords(void);

extern int input_pending;
extern FILE *input_file;
extern int crt_lex_token;
extern int saved_lex_token;
extern char *token_value;

/*
 * PARSER MACROS
 *
 * These macros are used by the SID parser to access the lexical
 * analysis routines.
 */
#define CURRENT_TERMINAL crt_lex_token
#define ADVANCE_LEXER    crt_lex_token = read_token()
#define SAVE_LEXER(T)    (saved_lex_token = crt_lex_token, crt_lex_token = (T))
#define RESTORE_LEXER    (crt_lex_token = saved_lex_token)
#define LEX_EOF          256

#endif

