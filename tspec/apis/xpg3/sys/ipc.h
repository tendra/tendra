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
+USE "xpg3", "sys/types.h" ;

/* These types have been abstracted */
+IF %% __STRICT_XPG3 %%
+TYPEDEF uid_t ~ipc_uid_t ;
+TYPEDEF gid_t ~ipc_gid_t ;
+TYPEDEF mode_t ~ipc_mode_t ;
+ELSE
+TYPE ( arith ) ~ipc_uid_t.1 ;
+TYPE ( arith ) ~ipc_gid_t.1 ;
+TYPE ( arith ) ~ipc_mode_t.1 ;
+MACRO uid_t __ipc_uid2uid ( ~ipc_uid_t ) ;
+MACRO ~ipc_uid_t __uid2ipc_uid ( uid_t ) ;
+MACRO gid_t __ipc_gid2gid ( ~ipc_gid_t ) ;
+MACRO ~ipc_gid_t __gid2ipc_gid ( gid_t ) ;
+MACRO mode_t __ipc_mode2mode ( ~ipc_mode_t ) ;
+MACRO ~ipc_mode_t __mode2ipc_mode ( mode_t ) ;
+IFNDEF ~building_libs
%%
#pragma accept conversion __ipc_uid2uid
#pragma accept conversion __uid2ipc_uid
#pragma accept conversion __ipc_gid2gid
#pragma accept conversion __gid2ipc_gid
#pragma accept conversion __ipc_mode2mode
#pragma accept conversion __mode2ipc_mode
%%
%%%
#include <sys/ipc.h>
#define __ipc_uid2uid( X )	( uid_t ) ( X )
#define __uid2ipc_uid( X )	( __local_ipc_uid_t ) ( X )
#define __ipc_gid2gid( X )	( gid_t ) ( X )
#define __gid2ipc_gid( X )	( __local_ipc_gid_t ) ( X )
#define __ipc_mode2mode( X )	( mode_t ) ( X )
#define __mode2ipc_mode( X )	( __local_ipc_mode_t ) ( X )
%%%
+ENDIF
+ENDIF

+FIELD struct ipc_perm {
    ~ipc_uid_t uid ;
    ~ipc_gid_t gid ;
    ~ipc_uid_t cuid ;
    ~ipc_gid_t cgid ;
    ~ipc_mode_t mode ;
} ;

+CONST int IPC_CREAT, IPC_EXCL, IPC_NOWAIT ;
+CONST key_t IPC_PRIVATE ;
+CONST int IPC_RMID, IPC_SET, IPC_STAT ;
