# $Id$

# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+FUNC char *basename ( char * ) ;	/* Corrigenda U013 1170/05: no const */
+FUNC char *dirname ( char * ) ;	/* Corrigenda U013 1170/04: no const */

+EXP (extern) char *__loc1 ;

+FUNC char *regcmp ( const char *, ... ) ;
+FUNC char *regex ( const char *, const char *, ... ) ;

