# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "c/c89", "stddef.h.ts", "size_t" ;

# iconv_open() iconv_t result comparable with (iconv_t)-1, so not opaque
+TYPE ( scalar ) iconv_t ;

+FUNC iconv_t iconv_open ( const char *, const char * ) ;
+FUNC size_t iconv ( iconv_t, const char **, size_t *, char **, size_t * ) ;
+FUNC int iconv_close ( iconv_t ) ;
