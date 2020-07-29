/*
 * Copyright 2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef MIPS_SIGFPE
 
#define MIPS_SIGFPE  8
#define MIPS_SIGSEGV 11

/* XXX: Really these ought to be passed in at runtime instead. */
#define MIPS_SIGUSR1 (assembler == ASM_ULTRIX ? 30 : 16)

#endif
