# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "cae/xpg3", "sys/types.h.ts" ;

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
