# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "stdlib.h.ts" ;

+SUBSET "putenv" := {
    +FUNC int putenv ( const char * ) ;
} ;
+SUBSET "setkey" := {
	+IF 0
	/* This is optional */
	+FUNC void setkey ( const char * ) ;
	+ENDIF
} ;

+IF 0
+SUBSET "rand48" := {
    /* These are in xpg3, but aren't declared (?) */
    +FUNC double drand48 ( void ) ;
    +FUNC double erand48 ( unsigned short [3] ) ;
    +FUNC long lrand48 ( void ) ;
    +FUNC long nrand48 ( unsigned short [3] ) ;
    +FUNC long mrand48 ( void ) ;
    +FUNC long jrand48 ( unsigned short [3] ) ;
    +FUNC void srand48 ( long ) ;
    +FUNC unsigned short *seed48 ( unsigned short [3] ) ;
    +FUNC void lcong48 ( unsigned short [7] ) ;
} ;
+ENDIF
