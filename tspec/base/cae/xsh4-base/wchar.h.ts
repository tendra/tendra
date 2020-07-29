# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c95", "wchar.h.ts", "wint_t" ;
+IMPLEMENT "c/c95", "wchar.h.ts", "mse" ;
+IMPLEMENT "c/c95", "wctype.h.ts", "mse2" (!?) ;

+FUNC wint_t fputwc ( wint_t, FILE * ) ;
+FUNC wint_t putwc ( wint_t, FILE * ) ;
+FUNC wint_t putwchar ( wint_t ) ;

+FUNC wchar_t *getws ( wchar_t * ) ;
+FUNC int putws ( const wchar_t * ) ;

+FUNC wchar_t *wcstok ( wchar_t *, const wchar_t * ) ;
+FUNC wchar_t *wcswcs ( const wchar_t *, const wchar_t * ) ;
+FUNC size_t wcsftime ( wchar_t *, size_t, const char *, const struct tm * ) ;
+FUNC int wcswidth ( const wchar_t *, size_t ) ;
+FUNC int wcwidth ( wchar_t ) ;
