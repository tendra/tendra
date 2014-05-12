# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" ;
+IMPLEMENT "posix/posix1", "sys/types.h.ts", "ssize_t" ;
+IMPLEMENT "posix/posix", "sys/types.h.ts", "guid" ;
+IMPLEMENT "posix/posix", "sys/types.h.ts", "off_t" ;
+IMPLEMENT "posix/posix", "sys/types.h.ts", "pid_t" ;

+IMPLEMENT "cae/xsh4-base", "stdio.h.ts", "optopt" ;

+IMPLEMENT "posix/posix2", "unistd.h.ts" ;
+IMPLEMENT "cae/xpg3", "unistd.h.ts", "u_plus" ;

+DEFINE _XOPEN_XPG4 %% %% ; # XXX: how to require just that something is defined, with no value?

+IFNDEF _XOPEN_VERSION
+DEFINE _XOPEN_VERSION.1	4 ;
+ENDIF

+FUNC void swab ( const void *, void *, ssize_t ) ;	# different

+CONST int _POSIX2_VERSION, _SC_2_C_BIND, _SC_2_C_VERSION, _SC_2_UPE ;
+CONST int _XOPEN_XCU_VERSION, _SC_XOPEN_CRYPT, _SC_XOPEN_ENH_I18N ;
+CONST int _SC_XOPEN_SHM ;
