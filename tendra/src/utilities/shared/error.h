/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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


#ifndef ERROR_INCLUDED
#define ERROR_INCLUDED


/*
 *    ERROR SEVERITY LEVELS
 *
 *    These macros give the various error types recognised by the error
 *    routines.
 */

#define ERROR_NONE		0x00
#define ERROR_WARNING		0x01
#define ERROR_SERIOUS		0x02
#define ERROR_FATAL		0x03


/*
 *    DECLARATIONS FOR ERROR ROUTINES
 */

extern void error PROTO_W ((int, CONST char *, ...));
extern void error_posn PROTO_W ((int, CONST char *, int, CONST char *, ...));
extern void set_progname(CONST char *, CONST char *) ;
extern void report_version(void) ;

extern CONST char *progname;
extern CONST char *progvers;
extern int exit_status;
extern int maximum_errors;
extern int crt_line_no;
extern CONST char *crt_file_name;


/*
 *    DECLARATIONS FOR ASSERTION ROUTINES
 */

#ifdef ASSERTS
extern void assertion(CONST char *, CONST char *, int) ;
#if FS_STDC_HASH
#define ASSERT(A)	if (!(A)) assertion (#A, __FILE__, __LINE__)
#define FAIL(A)	assertion (#A, __FILE__, __LINE__)
#else
#define ASSERT(A)	if (!(A)) assertion ("A", __FILE__, __LINE__)
#define FAIL(A)	assertion ("A", __FILE__, __LINE__)
#endif
#else
#define ASSERT(A)	((void) 0)
#define FAIL(A)	((void) 0)
#endif


#endif
