/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef UTILITY_H
#define UTILITY_H


extern bool is_fatal;
extern bool text_input, text_output;

void fatal_error(char *, ...);
void input_error(char *, ...);
void warning(char *, ...);


char *string_copy(char *, int);
char *temp_copy(char *);


char *ulong_to_octal(unsigned long);
unsigned long octal_to_ulong(char *);
bool fits_ulong(char *, int);


#endif /* UTILITY_H */
