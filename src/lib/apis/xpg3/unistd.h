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
+IMPLEMENT "posix", "unistd.h" ;

+IFNDEF _XOPEN_VERSION
+DEFINE _XOPEN_VERSION		3 ;
+ENDIF

+SUBSET "u_plus" := {
    +IMPLEMENT "posix", "stdio.h", "ctuid" (!?) ;

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
