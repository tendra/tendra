# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "posix", "sys/types.h.ts" ;

/* This type is abstracted */
+IF %% __STRICT_POSIX %%
+TYPEDEF gid_t ~grp_gid_t ;
+ELSE
+TYPE ( arith ) ~grp_gid_t.1 ;
+MACRO gid_t __grp_gid2gid ( ~grp_gid_t ) ;
+MACRO ~grp_gid_t __gid2grp_gid ( gid_t ) ;
+IFNDEF ~building_libs
%%
#pragma accept conversion __grp_gid2gid
#pragma accept conversion __gid2grp_gid
%%
%%%
#include <grp.h>
#define __grp_gid2gid( X )	( gid_t ) ( X )
#define __gid2grp_gid( X )	( __local_grp_gid_t ) ( X )
%%%
+ENDIF
+ENDIF

+FIELD struct group {
    char *gr_name ;
    ~grp_gid_t gr_gid ;
    char **gr_mem ;
} ;

+FUNC struct group *getgrnam ( const char * ) ;
+FUNC struct group *getgrgid ( gid_t ) ;
