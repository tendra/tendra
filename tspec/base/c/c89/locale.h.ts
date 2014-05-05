# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "stddef.h.ts", "null" (!?) ;

# 4.4 LOCALIZATION <locale.h>
+CONST int LC_ALL, LC_COLLATE, LC_CTYPE, LC_MONETARY, LC_NUMERIC, LC_TIME ;

# 4.4.1.1 The setlocale function
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

# 4.4.2.1 The localeconv function
+FUNC struct lconv *localeconv ( void ) ;

+ENDIF
+ENDIF

