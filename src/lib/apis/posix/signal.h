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
+IMPLEMENT "ansi", "signal.h" ;
+USE "posix", "sys/types.h" ;

+SUBSET "sigset_t" := { +TYPE sigset_t ; } ;

+FIELD struct sigaction | struct_sigaction {
    void ( *sa_handler ) ( int ) ;
    sigset_t sa_mask ;
    int sa_flags ;
} ;

+CONST int SIGALRM, SIGCHLD, SIGCONT, SIGHUP, SIGKILL, SIGPIPE, SIGQUIT ;
+CONST int SIGSTOP, SIGTSTP, SIGTTIN, SIGTTOU, SIGUSR1, SIGUSR2 ;
+CONST int SIG_BLOCK, SIG_SETMASK, SIG_UNBLOCK ;
+CONST int SA_NOCLDSTOP ;

+FUNC int kill ( pid_t, int ) ;
+FUNC int sigaction ( int, const struct sigaction *, struct sigaction * ) ;
+FUNC int sigaddset ( sigset_t *, int ) ;
+FUNC int sigdelset ( sigset_t *, int ) ;
+FUNC int sigemptyset ( sigset_t * ) ;
+FUNC int sigfillset ( sigset_t * ) ;
+FUNC int sigismember ( sigset_t *, int ) ;
+FUNC int sigpending ( sigset_t * ) ;
+FUNC int sigprocmask ( int, const sigset_t *, sigset_t * ) ;
+FUNC int sigsuspend ( const sigset_t * ) ;
