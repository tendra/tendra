/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef UTILITY_H
#define UTILITY_H


extern boolean is_fatal;
extern boolean text_input, text_output;

void fatal_error(char *, ...);
void input_error(char *, ...);
void warning(char *, ...);


char *string_copy(char *, int);
char *temp_copy(char *);


#define string_copy_aux(STR)\
    string_copy((STR), (int)strlen(STR))


char *ulong_to_octal(unsigned long);
unsigned long octal_to_ulong(char *);
boolean fits_ulong(char *, int);


#endif /* UTILITY_H */
