/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>

#include <local/out.h>

#include <refactor/const.h>

#include <main/driver.h>
#include <main/flags.h>

#include "comment.h"


void
comment(char * mess)
{
    if ( do_comment ) {
	fprintf(as_file, "!! " ) ;
	fprintf ( as_file,"%s\n", mess ) ;
    }
    return ;
}

void
comment1(char * mess, long p1)
{
    if ( do_comment ) {
	fprintf(as_file, "!! " ) ;
	fprintf ( as_file, mess, p1 ) ;
	fputc('\n',as_file);
    }
    return ;
}

void
comment2(char * mess, long p1, long p2)
{
    if ( do_comment ) {
	fprintf(as_file, "!! " ) ;
	fprintf ( as_file, mess, p1, p2 ) ;
	fputc('\n', as_file);
    }
    return ;
}

void
comment3(char * mess, long p1, long p2, long p3)
{
    if ( do_comment ) {
	fprintf(as_file, "!! " ) ;
	fprintf ( as_file, mess, p1, p2, p3 ) ;
	fputc('\n', as_file);
    }
    return ;
}

void
comment4(char * mess, long p1, long p2, long p3, long p4)
{
    if ( do_comment ) {
	fprintf(as_file, "!! " ) ;
	fprintf ( as_file, mess, p1, p2, p3, p4 ) ;
	fputc('\n', as_file);
    }
    return ;
}

