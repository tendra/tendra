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


#ifndef PREPROC_INCLUDED
#define PREPROC_INCLUDED


/*
 *    PREPROCESSING DECLARATIONS
 *
 *    The routines in this module are concerned with the processing of
 *    preprocessing directives.  They include preprocess_file which is the
 *    stand-alone preprocessing action of the program.
 */

extern int read_preproc_dir(int, int);
extern void patch_preproc_dir(PPTOKEN *);
extern int read_include(int, int);
extern unsigned check_macro(HASHID, int);
extern IDENTIFIER make_assert(HASHID, int);
extern void read_ident(int);
extern void read_weak(int);
extern void preprocess_file(void);
extern void start_preproc_if (void);
extern int clear_preproc_if (void);
extern int patch_cond(int, int);


/*
 *    PREPROCESSING VARIABLES
 *
 *    These variables are used by the preprocessing routines.
 */

extern int preproc_only;
extern int preproc_space;
extern int pragma_number;
extern int in_preproc_dir;
extern int no_preproc_dir;
extern int in_pragma_dir;
extern int in_hash_if_exp;
extern EXP crt_hash_if_exp;
extern LOCATION preproc_loc;
extern IDENTIFIER token_macro;


/*
 *    CONDITIONAL COMPILATION STATES
 *
 *    These values are used to identify the various conditional compilation
 *    states.  The condition may be true, false, being skipped, or unresolved.
 *    In addition a conditional compilation may or may not have associated
 *    '#else' and '#elif' statements.  There is a special value for indicating
 *    the end of an individual file.
 */

#define PP_FALSE			((unsigned) 0x00)
#define PP_TRUE				((unsigned) 0x01)
#define PP_PAST				((unsigned) 0x02)
#define PP_SKIP				((unsigned) 0x03)
#define PP_UNRESOLVED			((unsigned) 0x04)
#define PP_COND_MASK			((unsigned) 0x0f)
#define PP_HAVE_ELSE			((unsigned) 0x10)
#define PP_HAVE_ELIF			((unsigned) 0x20)
#define PP_TOKEN			((unsigned) 0x40)
#define PP_END				((unsigned) 0xff)


#endif
