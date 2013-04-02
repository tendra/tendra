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

extern FILE *as_file ;

#define fpout		as_file

#define outs( X )	fputs ( ( X ), as_file )
#define outc( X )	fputc ( ( X ), as_file )
#define outn( X )	fprintf ( as_file, "%ld", ( long ) ( X ) )
#define outf( X, Y )	fprintf ( as_file, ( X ), ( Y ) )
#define outnl()		fputc ( '\n', as_file )

#endif
