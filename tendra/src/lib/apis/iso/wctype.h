#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#

+SUBSET "mse2" := {
    # scalar: wctype() wctype_t result comparable with 0
    +IMPLEMENT "iso", "wchar.h", "wint" ;
    +TYPE ( int ) wctype_t ;

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
+TYPE ( int ) wctrans_t ;

# 7.15.2.3.2.n
+FUNC wctrans_t wctrans ( const char * ) ;
+FUNC wint_t towctrans ( wint_t, wctrans_t ) ;
