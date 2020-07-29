# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "cae/xpg3", "sys/types.h.ts" ;
+USE "cae/xpg3", "sys/ipc.h.ts" ;

+CONST int MSG_NOERROR ;

/* These are unsigned short in xpg3, unsigned long in sysv */
+IF %% __STRICT_SYSV %%
+TYPEDEF unsigned long ~msg_q_t ;
+TYPEDEF unsigned long ~msg_l_t ;
+ELSE
+IF %% __STRICT_XPG3 %%
+TYPEDEF unsigned short ~msg_q_t.1 ;
+TYPEDEF unsigned short ~msg_l_t.1 ;
+ELSE
+TYPE ( int ) ~msg_q_t.2 ;
+TYPE ( int ) ~msg_l_t.2 ;
+ENDIF
+ENDIF

/* This type has been abstracted */
+IF %% __STRICT_XPG3 %%
+TYPEDEF pid_t ~msg_pid_t ;
+ELSE
+TYPE ( int ) ~msg_pid_t.1 ;
+ENDIF

+FIELD struct msqid_ds {
    struct ipc_perm msg_perm ;
    ~msg_q_t msg_qnum ;
    ~msg_l_t msg_qbytes ;
    ~msg_pid_t msg_lspid ;
    ~msg_pid_t msg_lrpid ;
    time_t msg_stime ;
    time_t msg_rtime ;
    time_t msg_ctime ;
} ;

+FUNC int msgget ( key_t, int ) ;
+FUNC int msgrcv ( int, void *, size_t, long, int ) ;
+FUNC int msgsnd ( int, const void *, size_t, int ) ;

+IFNDEF ~building_libs
+FUNC int msgctl ( int, int, struct msqid_ds * ) ;
+ELSE
+FUNC int __old_msgctl | msgctl.1 ( int, int, struct msqid_ds * ) ;
%%%
#define __old_msgctl( A, B, C )		msgctl ( A, B, C )
%%%
+ENDIF
