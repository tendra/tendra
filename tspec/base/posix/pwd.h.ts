# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "posix", "sys/types.h.ts" ;

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
