/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


#ifndef MACRO_INCLUDED
#define MACRO_INCLUDED


/*
 *    TYPE REPRESENTING THE LOCATION OF A LIST OF TOKENS
 *
 *    This type represents the location of a list of tokens and it used in
 *    expand_macro.  The toks field gives a pointer to this list, while the
 *    next field allows these locations to be formed into lists.
 */

typedef struct tok_loc_tag {
    PPTOKEN **toks;
    struct tok_loc_tag *next;
} TOKEN_LOC;


/*
 *    MACRO EXPANSION DECLARATIONS
 *
 *    The routines in this module are concerned with the manipulation of
 *    lists of preprocessing tokens, including the expansion of macros.
 */

extern void init_macros(int, int);
extern void term_macros(void);
extern PPTOKEN *recognise_strings(PPTOKEN *, HASHID, int);
extern PPTOKEN *expand_macro(HASHID, TOKEN_LOC *, int);
extern PPTOKEN *read_line(int, int);
extern PPTOKEN *expand_tok_list(PPTOKEN *);
extern PPTOKEN *clean_tok_list(PPTOKEN *);
extern PPTOKEN *new_pptok(void);
extern void free_tok_list(PPTOKEN *);
extern int quote_tok_list(PPTOKEN *, int, int);
extern void token_parts(int, PPTOKEN *);


/*
 *    MACRO EXPANSION VARIABLES
 *
 *    These variables are used in the macro expansion routines.
 */

extern NAMESPACE assert_namespace;
extern PPTOKEN *free_tokens;
extern TOKEN_LOC *file_loc;


/*
 *    BUILT-IN MACRO FLAG
 *
 *    This flag is used as part of the storage field of a macro to indicate
 *    a built-in macro.
 */

#define dspec_builtin		dspec_static


#endif
