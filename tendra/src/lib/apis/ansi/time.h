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
+IMPLEMENT "ansi", "stddef.h", "null" ;
+IMPLEMENT "ansi", "stddef.h", "size_t" ;

+SUBSET "time_t" := { +TYPE ( arith ) time_t ; } ;

+FIELD struct tm {
    int tm_sec ;
    int tm_min ;
    int tm_hour ;
    int tm_mday ;
    int tm_mon ;
    int tm_year ;
    int tm_wday ;
    int tm_yday ;
    int tm_isdst ;
} ;

+EXP int CLOCKS_PER_SEC ;

+FUNC char *asctime ( const struct tm * ) ;
+FUNC char *ctime ( const time_t * ) ;
+FUNC struct tm *gmtime ( const time_t * ) ;
+FUNC struct tm *localtime ( const time_t * ) ;
+FUNC time_t mktime ( struct tm * ) ;
+FUNC size_t strftime ( char *, size_t, const char *, const struct tm * ) ;
+FUNC time_t time ( time_t * ) ;

+IFNDEF __JUST_POSIX
+SUBSET "clock_t" := { +TYPE ( arith ) clock_t ; } ;
+FUNC clock_t clock ( void ) ;
+IFNDEF __JUST_XPG3
+FUNC double difftime ( time_t, time_t ) ;
+ENDIF
+ENDIF
