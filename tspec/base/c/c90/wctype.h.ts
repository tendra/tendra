# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+SUBSET "mse2" := {
    # scalar: wctype() wctype_t result comparable with 0
    +IMPLEMENT "c/c90", "wchar.h.ts", "wint" ;
    +TYPE ( scalar ) wctype_t ;

    # 7.15.2.1.n
    +FUNC int iswalnum ( wint_t ) ;
    +FUNC int iswalpha ( wint_t ) ;
    +FUNC int iswcntrl ( wint_t ) ;
    +FUNC int iswdigit ( wint_t ) ;
    +FUNC int iswgraph ( wint_t ) ;
    +FUNC int iswlower ( wint_t ) ;
    +FUNC int iswprint ( wint_t ) ;
    +FUNC int iswpunct ( wint_t ) ;
    +FUNC int iswspace ( wint_t ) ;
    +FUNC int iswupper ( wint_t ) ;
    +FUNC int iswxdigit ( wint_t ) ;

    # 7.15.2.2.n
    +FUNC wctype_t wctype ( const char * ) ;
    +FUNC int iswctype ( wint_t, wctype_t ) ;

    # 7.15.2.3.1.n
    +FUNC wint_t towlower ( wint_t ) ;
    +FUNC wint_t towupper ( wint_t ) ;
} ;

# scalar: wctrans() wctrans_t result comparable with 0
+TYPE ( scalar ) wctrans_t ;

# 7.15.2.3.2.n
+FUNC wctrans_t wctrans ( const char * ) ;
+FUNC wint_t towctrans ( wint_t, wctrans_t ) ;

