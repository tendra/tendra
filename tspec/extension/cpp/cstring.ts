# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$LINKAGE = "C++" ;
$NAMESPACE = "std" ;
+USE ("c/c90"), "string.h.ts" ;

%%
char *strchr ( char *, int ) ;
const char *strchr ( const char *, int ) ;
char *strrchr ( char *, int ) ;
const char *strrchr ( const char *, int ) ;
char *strpbrk ( char *, const char * ) ;
const char *strpbrk ( const char *, const char * ) ;
char *strstr ( char *, const char * ) ;
const char *strstr ( const char *, const char * ) ;
void *memchr ( void *, int, size_t ) ;
const void *memchr ( const void *, int, size_t ) ;
%%
