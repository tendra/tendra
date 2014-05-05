# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "posix1", "sys/types.h.ts" ;

+IFNDEF _POSIX_VERSION
+DEFINE _POSIX_VERSION.1 %% 199009L %% ;
+ENDIF

# Main body from posix
+IMPLEMENT "posix", "unistd.h.ts", "u_proto" ;
+IMPLEMENT "posix", "unistd.h.ts", "tcpgrp" ;

# These have changed
+FUNC char *getcwd ( char *, size_t ) ;
+FUNC ssize_t read ( int, void *, size_t ) ;
+FUNC ssize_t write ( int, const void *, size_t ) ;

+CONST int _SC_STREAM_MAX, _SC_TZNAME_MAX ;
