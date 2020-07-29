# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "signal.h.ts" ;

/* The specification of ucontext (BA_ENV) is rubbish */
+TYPE mcontext_t ;
+FIELD struct ucontext {
    struct ucontext *uc_link ;
    sigset_t uc_sigmask ;
    stack_t uc_stack ;
    mcontext_t uc_mcontext ;
} ;
+TYPEDEF struct ucontext ucontext_t ;

+FUNC int getcontext ( ucontext_t * ) ;
+FUNC int setcontext ( ucontext_t * ) ;
/* From errata */
+FUNC void makecontext ( ucontext_t *, void (*) (), int, ... ) ;
+FUNC int swapcontext ( ucontext_t *, ucontext_t * ) ;
