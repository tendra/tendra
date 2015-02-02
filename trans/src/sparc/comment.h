/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef COMMENT_INCLUDED
#define COMMENT_INCLUDED

#include <reader/exp.h>
#include <reader/code.h>

#include <construct/installtypes.h>

#define comment(st) 	fprintf(as_file,"\t! %s\n",st);
#define commenti(st)	fprintf(as_file,"\t! %s %d\n",st,i);

#endif /* COMMENT_INCLUDED */
