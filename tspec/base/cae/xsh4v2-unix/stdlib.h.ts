# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+FUNC long a64l ( const char * ) ;
+FUNC char *l64a ( long ) ;

+FUNC char *ecvt ( double, int, int *, int * ) ;
+FUNC char *fcvt ( double, int, int *, int * ) ;
+FUNC char *gcvt ( double, int, char * ) ;

+FUNC int getsubopt ( char **, char * const *, char ** ) ;

+FUNC int grantpt ( int ) ;

+FUNC char *initstate ( unsigned, char *, int ) ;
+FUNC long random ( void ) ;
+FUNC void srandom ( unsigned ) ;
+FUNC char *setstate ( char * ) ;

+FUNC int mkstemp ( char * ) ;
+FUNC char *mktemp ( char * ) ;

+FUNC char *ptsname ( int ) ;
+FUNC int ttyslot ( void ) ;
+FUNC int unlockpt ( int ) ;

+FUNC char *realpath ( const char *, char * ) ;

+FUNC void *valloc ( size_t ) ;

