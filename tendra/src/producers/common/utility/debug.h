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
 *
 * $TenDRA$
 */


#ifdef RUNTIME
#ifndef DEBUG_INCLUDED
#define DEBUG_INCLUDED


/*
 *    DEBUGGING ROUTINE DECLARATIONS
 *
 *    The routines in this module are designed to aid in program development;
 *    they do not form part of the program proper.  They are only defined if
 *    the macro RUNTIME is defined.
 */

extern void DEBUG_access(DECL_SPEC);
extern void DEBUG_btype(BASE_TYPE);
extern void DEBUG_cinfo(CLASS_INFO);
extern void DEBUG_ctype(CLASS_TYPE);
extern void DEBUG_cusage(CLASS_USAGE);
extern void DEBUG_cv(CV_SPEC);
extern void DEBUG_dspec(DECL_SPEC);
extern void DEBUG_etype(ENUM_TYPE);
extern void DEBUG_exp(EXP);
extern void DEBUG_flt(FLOAT);
extern void DEBUG_ftype(FLOAT_TYPE);
extern void DEBUG_func(IDENTIFIER);
extern void DEBUG_graph(GRAPH);
extern void DEBUG_hashid(HASHID);
extern void DEBUG_hash_table(string);
extern void DEBUG_id(IDENTIFIER);
extern void DEBUG_id_long(IDENTIFIER);
extern void DEBUG_inst(INSTANCE);
extern void DEBUG_itype(INT_TYPE);
extern void DEBUG_lex(int);
extern void DEBUG_loc(LOCATION *);
extern void DEBUG_mangle(IDENTIFIER);
extern void DEBUG_member(MEMBER);
extern void DEBUG_members(NAMESPACE);
extern void DEBUG_nat(NAT);
extern void DEBUG_nspace(NAMESPACE);
extern void DEBUG_ntest(NTEST);
extern void DEBUG_ntype(BUILTIN_TYPE);
extern void DEBUG_offset(OFFSET);
extern void DEBUG_pptok(PPTOKEN *);
extern void DEBUG_pptoks(PPTOKEN *);
extern void DEBUG_sort(TOKEN);
extern void DEBUG_stmt(EXP);
extern void DEBUG_str(STRING);
extern void DEBUG_type(TYPE);
extern void DEBUG_unmangle(CONST char *);
extern void DEBUG_virt(VIRTUAL);

extern void DEBUG_source(int);
extern void DEBUG_where(void);

#if c_class_IMPLEMENTATION
extern void debug(c_class *);
#endif

#define DEBUG_file	stdout
#define DEBUG_text(A)	fputs_v ((A), DEBUG_file)
#define DEBUG_mark	fprintf_v (DEBUG_file, "%s: %d\n", __FILE__, __LINE__)

extern int print_exp_aux(EXP, int, BUFFER *, int);
extern int print_offset_aux(OFFSET, BUFFER *, int);
extern void debug_option(char *);
extern int debugging;


#endif
#endif
