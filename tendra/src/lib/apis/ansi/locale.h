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
+IMPLEMENT "ansi", "stddef.h", "null" (!?) ;

+CONST int LC_ALL, LC_COLLATE, LC_CTYPE, LC_MONETARY, LC_NUMERIC, LC_TIME ;

+FUNC char *setlocale ( int, const char * ) ;

+IFNDEF __JUST_POSIX
+IFNDEF __JUST_XPG3

+FIELD struct lconv {
    char *decimal_point ;
    char *thousands_sep ;
    char *grouping ;
    char *int_curr_symbol ;
    char *currency_symbol ;
    char *mon_decimal_point ;
    char *mon_thousands_sep ;
    char *mon_grouping ;
    char *positive_sign ;
    char *negative_sign ;
    char int_frac_digits ;
    char frac_digits ;
    char p_cs_precedes ;
    char p_sep_by_space ;
    char n_cs_precedes ;
    char n_sep_by_space ;
    char p_sign_posn ;
    char n_sign_posn ;
} ;

+FUNC struct lconv *localeconv ( void ) ;

+ENDIF
+ENDIF
