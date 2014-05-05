# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "stdlib.h.ts", "bottom" ;

# 4.6 NON-LOCAL JUMPS <setjmp.h>
+NAT ~jmp_buf_size ;
+TYPE ~jmp_buf_elt ;
+TYPEDEF ~jmp_buf_elt jmp_buf [ ~jmp_buf_size ] ;

# 4.6.1.1 The setjmp macro
+FUNC int setjmp ( jmp_buf ) ;

# 4.6.2.1 The longjmp function
+FUNC ~bottom longjmp ( jmp_buf, int ) ;

