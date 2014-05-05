# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix", "unistd.h.ts" ;

+IFNDEF _XOPEN_VERSION
+DEFINE _XOPEN_VERSION		3 ;
+ENDIF

+SUBSET "u_plus" := {
    +IMPLEMENT "posix", "stdio.h.ts", "ctuid" (!?) ;

    +CONST int _SC_PASS_MAX, _SC_XOPEN_VERSION ;

    +FUNC int chroot ( const char * ) ;
    +FUNC int fsync ( int ) ;
    +FUNC char *getpass ( const char * ) ;
    +FUNC int nice ( int ) ;
    +IF 0
    /* These are optional */
    +FUNC char *crypt ( const char *, const char * ) ;
    +FUNC void encrypt ( char [64], int ) ;
    +ENDIF
} ;

+IFNDEF ~building_libs
+FUNC void swab ( char *, char *, int ) ;
+ELSE
+FUNC void __old_swab | swab.1 ( char *, char *, int ) ;
%%%
#define __old_swab( A, B, C )	swab ( A, B, C )
%%%
+ENDIF
