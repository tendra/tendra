# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "c/c89", "stddef.h.ts", "size_t" (!?) ;

+CONST int GLOB_APPEND, GLOB_DOOFFS, GLOB_ERR, GLOB_MARK, GLOB_NOCHECK ;
+CONST int GLOB_NOESCAPE, GLOB_NOSORT, GLOB_ABORTED, GLOB_NOMATCH ;
+CONST int GLOB_NOSPACE, GLOB_NOSYS ;

+FIELD ( struct ) glob_t {
    size_t gl_pathc ;
    char **gl_pathv ;
    size_t gl_offs ;
} ;

+FUNC int glob ( const char *, int, int (*) ( const char *, int ), glob_t * ) ;
+FUNC void globfree ( glob_t * ) ;
