# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "cae/xsh4-base", "search.h.ts" ;
+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" ;

+FUNC void insque ( void *, void * ) ;
+FUNC void remque ( void * ) ;
