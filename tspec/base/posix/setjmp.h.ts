# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "setjmp.h.ts" ;

+NAT ~sigjmp_buf_size ;
+TYPE ~sigjmp_buf_elt ;
+TYPEDEF ~sigjmp_buf_elt sigjmp_buf [ ~sigjmp_buf_size ] ;

+FUNC ~bottom siglongjmp ( sigjmp_buf, int ) ;
+FUNC int sigsetjmp ( sigjmp_buf, int ) ;
