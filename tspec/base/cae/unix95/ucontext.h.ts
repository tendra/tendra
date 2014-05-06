# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+SUBSET "sig" := {
    # for unix95:signal.h
    +USE "cae/unix95", "sys/types.h.ts" ;

    +IMPLEMENT "posix", "signal.h.ts", "sigset_t" ;

    +TYPE mcontext_t ;

    +FIELD ( struct ) stack_t {
	void *ss_sp ;
	size_t ss_size ;
	int ss_flags ;
    } ;

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
