/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef FILE_INCLUDED
#define FILE_INCLUDED


/*
 * FILE HANDLING ROUTINES
 *
 * This file contains the low level file reading and writing routines.
 */

extern FILE *pp_file;
extern place here;
extern int printflag;
extern int column;
extern int maximum;
extern int lastc;
extern int read_error;
extern int dump;

extern void open_files(char *, char *);
extern long fetch(int);
extern void byte_align(void);
extern void set_place(place *);
extern void skip_bits(long);
extern void init_spaces(int);
extern void spaces(int);

#define posn(X)	((X).byte * CHAR_BIT + (X).bit)


#endif
