# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+USE "cae/xsh4-base", "setjmp.h.ts" ;

+FUNC ~bottom _longjmp ( jmp_buf, int ) ;
+FUNC int _setjmp ( jmp_buf ) ;

