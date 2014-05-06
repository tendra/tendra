# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix/posix", "limits.h.ts" ;
+USE "posix/posix1", "sys/types.h.ts" (!?) ;

+CONST ssize_t _POSIX_SSIZE_MAX ;
+CONST int _POSIX_STREAM_MAX, _POSIX_TZNAME_MAX ;
+CONST ssize_t SSIZE_MAX ;
+IF 0
+CONST int STREAM_MAX, TZNAME_MAX ;
+ENDIF
