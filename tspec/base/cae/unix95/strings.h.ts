# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Corrigenda U013 1170/02: define size_t
+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" ;

+FUNC int bcmp ( const void *, const void *, size_t ) ;
+FUNC void bcopy ( const void *, void *, size_t ) ;
+FUNC void bzero ( void *, size_t ) ;
+FUNC int ffs ( int ) ;
+FUNC char *index ( const char *, int ) ;
+FUNC char *rindex ( const char *, int ) ;
+FUNC int strcasecmp ( const char *, const char * ) ;
+FUNC int strncasecmp ( const char *, const char *, size_t ) ;
