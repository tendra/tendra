/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef UTILITY_H
#define UTILITY_H

#include <stddef.h>

/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with error reporting, memory allocation
 * and system calls.
 */
char *string_printf(char *, ...);
void create_dir(char *);
time_t date_stamp(char *);
void set_filename(char *);

/*
 * INPUT BUFFER
 *
 * This buffer is used to store input in various contexts.
 */
extern char *buffer;
#define buffsize 5000

/*
 * ERROR VARIABLES
 *
 * These variables are concerned with error reporting.
 */
extern int warnings;
extern time_t progdate;
extern char *filename;

#endif

