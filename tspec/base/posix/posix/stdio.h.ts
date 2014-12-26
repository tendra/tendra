# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "stdio.h.ts" ;

+SUBSET "ctermid" := {
    +FUNC char *ctermid ( char * ) ;
} ;

+SUBSET "cuserid" := {
    +FUNC char *cuserid ( char * ) ;
} ;

+SUBSET "L_ctermid" := {
	+CONST int L_ctermid ;
} ;

+SUBSET "L_cuserid" := {
	+CONST int L_cuserid ;
} ;

+FUNC FILE *fdopen ( int, const char * ) ;
+FUNC int fileno ( FILE * ) ;
+FUNC int pclose ( FILE * ) ;
+FUNC FILE *popen ( const char *, const char * ) ;
