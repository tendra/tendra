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


+SUBSET "sig" := {
    # for unix95:signal.h
    +USE "unix95", "sys/types.h" ;

    +IMPLEMENT "posix", "signal.h", "sigset_t" ;

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
