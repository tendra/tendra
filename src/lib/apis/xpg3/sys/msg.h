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
+USE "xpg3", "sys/ipc.h" ;

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
