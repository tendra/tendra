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
+USE "posix", "sys/types.h" ;

/* These types are abstracted */
+IF %% __STRICT_POSIX %%
+TYPEDEF uid_t ~passwd_uid_t ;
+TYPEDEF gid_t ~passwd_gid_t ;
+ELSE
+TYPE ( arith ) ~passwd_uid_t.1 ;
+TYPE ( arith ) ~passwd_gid_t.1 ;
+MACRO uid_t __passwd_uid2uid ( ~passwd_uid_t ) ;
+MACRO ~passwd_uid_t __uid2passwd_uid ( uid_t ) ;
+MACRO gid_t __passwd_gid2gid ( ~passwd_gid_t ) ;
+MACRO ~passwd_gid_t __gid2passwd_gid ( gid_t ) ;
+IFNDEF ~building_libs
%%
#pragma accept conversion __passwd_uid2uid
#pragma accept conversion __uid2passwd_uid
#pragma accept conversion __passwd_gid2gid
#pragma accept conversion __gid2passwd_gid
%%
%%%
#include <pwd.h>
#define __passwd_uid2uid( X )	( uid_t ) ( X )
#define __uid2passwd_uid( X )	( __local_passwd_uid_t ) ( X )
#define __passwd_gid2gid( X )	( gid_t ) ( X )
#define __gid2passwd_gid( X )	( __local_passwd_gid_t ) ( X )
%%%
+ENDIF
+ENDIF

+FIELD struct passwd {
    char *pw_name ;
    ~passwd_uid_t pw_uid ;
    ~passwd_gid_t pw_gid ;
    char *pw_dir ;
    char *pw_shell ;
} ;

+FUNC struct passwd *getpwnam ( const char * ) ;
+FUNC struct passwd *getpwuid ( uid_t ) ;
