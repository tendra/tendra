/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TOKENS_H
#define TOKENS_H

extern int tok, val;
extern int yylex(void);

enum {
	T_eof, T_number,
	T_add, T_sub, T_mul, T_div, T_mod, T_lparen, T_rparen,
	T_newline, T_error
};

#endif

