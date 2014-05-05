# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "stddef.h.ts", "null" ;
+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" ;

# 4.12 DATE AND TIME <time.h>

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

+IFNDEF __JUST_POSIX
+SUBSET "clock_t" := { +TYPE ( arith ) clock_t ; } ;
+ENDIF

# XXX: not present in X3.???-1988 draft
+EXP int CLOCKS_PER_SEC ;

# 4.12.2.n Time manipulation functions
+IFNDEF __JUST_POSIX
+FUNC clock_t clock ( void ) ;
+IFNDEF __JUST_XPG3
+FUNC double difftime ( time_t, time_t ) ;
+ENDIF
+ENDIF
+FUNC time_t mktime ( struct tm * ) ;
+FUNC time_t time ( time_t * ) ;

# 4.12.3.n Time conversion functions
+FUNC char *asctime ( const struct tm * ) ;
+FUNC char *ctime ( const time_t * ) ;
+FUNC struct tm *gmtime ( const time_t * ) ;
+FUNC struct tm *localtime ( const time_t * ) ;
+FUNC size_t strftime ( char *, size_t, const char *, const struct tm * ) ;

