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
