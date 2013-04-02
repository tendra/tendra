/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OUTDECS_INCLUDED
#define OUTDECS_INCLUDED

#include <stdio.h>

extern FILE *outf;

#define outs( X ) fputs( (X), outf )
#define outc( X ) fputc( (X), outf )
#define outn( X ) fprintf(outf, "%ld", (long) (X) )
#define outnl()   fputc( '\n', outf )
#endif
