/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef FILE_H
#define FILE_H

extern FILE *input;
extern FILE *output;
extern char *input_file;


/*
    FILE MANIPULATION ROUTINES
*/

void open_input(char *, int);
void open_output(char *);
void add_directory(char *);


#endif /* FILE_H */
