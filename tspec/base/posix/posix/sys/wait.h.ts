# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "posix/posix", "sys/types.h.ts" ;

+CONST int WNOHANG, WUNTRACED ;

+MACRO int WEXITSTATUS ( lvalue int ) ;
+MACRO int WIFEXITED ( lvalue int ) ;
+MACRO int WIFSIGNALED ( lvalue int ) ;
+MACRO int WIFSTOPPED ( lvalue int ) ;
+MACRO int WSTOPSIG ( lvalue int ) ;
+MACRO int WTERMSIG ( lvalue int ) ;

+FUNC pid_t wait ( int * ) ;
+FUNC pid_t waitpid ( pid_t, int *, int ) ;
