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


#ifndef IDENTIFIER_INCLUDED
#define IDENTIFIER_INCLUDED


/*
 *    IDENTIFIER DECLARATIONS
 *
 *    The routines in this module are concerned with the construction and
 *    manipulation of identifiers.
 */

extern void use_id(IDENTIFIER, int);
extern void use_func_id(IDENTIFIER, int, int);
extern void reuse_id(IDENTIFIER, int);
extern void define_id(IDENTIFIER);
extern IDENTIFIER chase_alias(IDENTIFIER);
extern EXP make_id_exp(IDENTIFIER);
extern EXP implicit_id_exp(IDENTIFIER, int);
extern EXP make_this_exp(void);
extern EXP make_this_ref(NAMESPACE *);
extern EXP make_this_decl(IDENTIFIER);
extern int is_this_exp(EXP);
extern IDENTIFIER this_param(IDENTIFIER, int);
extern EXP make_ellipsis_exp(void);
extern void make_ellipsis_decl(void);
extern IDENTIFIER ellipsis_param(IDENTIFIER);
extern IDENTIFIER report_ambiguous(IDENTIFIER, int, int, int);
extern DECL_SPEC find_ambig_dspec(LIST (IDENTIFIER));
extern ERROR check_id_name(IDENTIFIER, int);
extern IDENTIFIER declare_func(DECL_SPEC, IDENTIFIER, TYPE, TYPE *, int, LIST (TYPE));
extern QUALIFIER crt_id_qualifier;
extern int crt_templ_qualifier;
extern int suppress_usage;


/*
 *    IDENTIFIER CONTEXTS
 *
 *    These values are used to indicate the contexts for an identifier
 *    to check_id_name.
 */

#define CONTEXT_OBJECT			0
#define CONTEXT_FUNCTION		1
#define CONTEXT_PARAMETER		2
#define CONTEXT_MEMBER			3
#define CONTEXT_FUNC_MEMBER		4
#define CONTEXT_CLASS			5
#define CONTEXT_ENUM			6
#define CONTEXT_ENUMERATOR		7
#define CONTEXT_TEMPL_PARAM		8
#define CONTEXT_WEAK_PARAM		9


#endif
