# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "posix/posix", "sys/types.h.ts" ;
+USE "c/c89", "time.h.ts", "time_t" (!?) ;

+FIELD struct utimbuf {
    time_t actime ;
    time_t modtime ;
} ;

+FUNC int utime ( const char *, const struct utimbuf * ) ;
