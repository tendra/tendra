/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ACSII_INCLUDED
#define ACSII_INCLUDED


#include <ctype.h>


/* USEFUL CHARACTERS */
#define TAB		('\t')
#define NEWLINE		('\n')
#define SPACE		(' ')
#define QUOTE		('"')
#define COMMA		(',')
#define DOT		('.')
#define ZERO		('0')
#define COLON		(':')
#define SLASH		('\\')


/* PRINTABLE CHARACTERS */
#define printable(X)	isprint(X)


/* TAB WIDTH */
#define TBSIZE		8


/* CONVERT CHARACTER TO DIGIT AND VICE VERSA */
#define digit(X)	((int)((X) - ZERO))
#define charact(X)	((char)(ZERO + (X)))


/* IS A CHARACTER A DIGIT? */
#define is_digit(X)	isdigit(X)


#endif
