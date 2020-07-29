# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "time.h.ts" ;
+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" ;

+EXP int CLK_TCK ;
+FUNC void tzset ( void ) ;
+EXP (extern) char *tzname [] ;

