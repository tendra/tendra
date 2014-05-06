# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "string.h.ts" ;

# From xpg3 with prototypes
+FUNC void *memccpy ( void *, const void *, int, size_t ) ;

+FUNC char *strdup ( const char * ) ;
