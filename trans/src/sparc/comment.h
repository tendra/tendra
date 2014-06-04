/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef COMMENT_INCLUDED
#define COMMENT_INCLUDED

#include <stdio.h>

#include <reader/exp.h>

#include <reader/code.h>

#include <construct/installtypes.h>

extern char *sparctrans;
extern bool do_comment;
extern void fail(char *);
extern FILE *as_file;

#define comment(st)	fprintf(as_file,"\t! %s\n",st);

#endif /* COMMENT_INCLUDED */
