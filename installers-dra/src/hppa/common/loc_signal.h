/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
$Log: loc_signal.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:45  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.1  1995/09/15  14:11:46  wfs
 * SIGSEGV defined for exception token stuff.
 *
 * Revision 5.0  1995/08/25  14:12:27  wfs
 * Preperation for August 95 Glue release
 *
*/

#ifndef SIGFPE
#define SIGFPE     8
#endif
#ifndef SIGBUS
#define SIGBUS     10
#endif
#ifndef SIGSEGV
#define SIGSEGV    11
#endif
#ifndef SIGUSR1
#define SIGUSR1    16
#endif

