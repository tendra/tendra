# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "cae/xsh4v2-unix", "signal.h.ts", "stack_t";

+SUBSET "sig" := {
    # for xsh4v2-unix:signal.h
    +USE "cae/xsh4v2-unix", "sys/types.h.ts" ;

    +IMPLEMENT "posix/posix", "signal.h.ts", "sigset_t" ;

    +TYPE mcontext_t ;

    +FIELD ( struct ) ucontext_t {
		ucontext_t *uc_link ;
		sigset_t uc_sigmask ;
		stack_t uc_stack ;
		mcontext_t uc_mcontext ;
    } ;
} ;

+FUNC int getcontext ( ucontext_t * ) ;
+FUNC int setcontext ( const ucontext_t * ) ;
+FUNC void makecontext ( ucontext_t *, void (*) ( int ), int, ... ) ;
+FUNC int swapcontext ( ucontext_t *, const ucontext_t * ) ;

