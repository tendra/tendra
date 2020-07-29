# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "cae/xsh4v2-unix", "sys/resource.h.ts", "rusage" ;
+IMPLEMENT "cae/xsh4v2-unix", "sys/types.h.ts", "id_t" ;
+IMPLEMENT "cae/xsh4v2-unix", "signal.h.ts", "siginfo_t" ;

+MACRO int WIFCONTINUED ( lvalue int ) ;
+CONST int WEXITED, WSTOPPED, WNOWAIT, WCONTINUED ;

+ENUM idtype_t := { P_ALL, P_PID, P_PGID } ;

+FUNC pid_t wait3 ( int *, int, struct rusage * ) ;
+FUNC int waitid ( idtype_t, id_t, siginfo_t *, int ) ;

