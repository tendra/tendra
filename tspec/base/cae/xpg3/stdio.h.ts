# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix/posix", "stdio.h.ts" ;
+IMPLEMENT "c/c89", "stdlib.h.ts", "system" ;
+IMPLEMENT "posix/posix", "unistd.h.ts", "getopt" ;

+FUNC int getw ( FILE * ) ;
+FUNC int putw ( int, FILE * ) ;
+FUNC char *tempnam ( const char *, const char * ) ;
