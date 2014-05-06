# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "cae/xpg4", "sys/wait.h.ts" ;
+IMPLEMENT "cae/unix95", "sys/types.h.ts", "id_t" ;
+IMPLEMENT "cae/unix95", "signal.h.ts", "siginfo_t" ;
+IMPLEMENT "posix/posix", "sys/types.h.ts", "pid_t" ;
+IMPLEMENT "cae/unix95", "sys/resource.h.ts", "rusage" ;

+ENUM idtype_t := { P_ALL, P_PID, P_PGID } ;

+FUNC int waitid ( idtype_t, id_t, siginfo_t *, int ) ;
+FUNC pid_t wait3 ( int *, int, struct rusage * ) ;

+CONST int WEXITED, WSTOPPED, WNOWAIT, WCONTINUED ;
+MACRO int WIFCONTINUED ( lvalue int ) ;
