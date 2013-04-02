/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
   file.h
   definitions for file handling.
*/
#ifndef FILE_H
#define FILE_H

#include <stdio.h>

typedef enum
{
  WRITE,READ
  } FileMode;

extern FILE * open_file(char *,FileMode);
extern void close_file(FILE *);

#endif
