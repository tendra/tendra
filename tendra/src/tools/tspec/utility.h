/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED


/*
 *    PROCEDURE DECLARATIONS
 *
 *    These routines are concerned with error reporting, memory allocation
 *    and system calls.
 */

extern void error PROTO_W ((int, char *, ...));
extern pointer xalloc(int) ;
extern pointer xrealloc(pointer, int) ;
extern char *string_copy(char *) ;
extern char *string_concat(char *, char *) ;
extern char *string_printf PROTO_W ((char *, ...));
extern void create_dir(char *) ;
extern void check_name(char *) ;
extern time_t date_stamp(char *) ;


/*
 *    INPUT BUFFER
 *
 *    This buffer is used to store input in various contexts.
 */

extern char *buffer;
#define buffsize		5000


/*
 *    ERROR VARIABLES
 *
 *    These variables are concerned with error reporting.
 */

extern int exit_status;
extern int no_errors;
extern int warnings;
extern char *progname;
extern char *progvers;
extern time_t progdate;
extern char *filename;
extern int line_no;


/*
 *    ERROR TYPES
 *
 *    These values give the severity levels for the error reporting
 *    routine, error.
 */

#define ERR_FATAL		0
#define ERR_INTERNAL		1
#define ERR_SERIOUS		2
#define ERR_WARNING		3
#define ERR_INFO		4


/*
 *    UTILITY MACROS
 *
 *    These macros give convenient shorthands for various constructs.
 */

#define alloc_size(T, N)\
	((int) (N) * (int) sizeof (T))

#define alloc_nof(T, N)\
	(T *) xalloc (alloc_size (T, N))

#define realloc_nof(P, T, N)\
	(T *) xrealloc ((pointer) (P), alloc_size (T, N))

#define array_size(A)\
	((int) sizeof (A) / (int) sizeof (A [0]))


/*
 *    GENERAL ALLOCATION ROUTINE
 *
 *    This routine allocates a variable V of type T, allocating N at a time.
 */

#define alloc_variable(V, T, N)\
    {\
	static int no_free = 0 ;\
	static T *free_list = null ;\
	if (no_free == 0) {\
	    no_free = N ;\
	    free_list = alloc_nof (T, N) ;\
	}\
	V = free_list + (--no_free) ;\
    }


#endif
