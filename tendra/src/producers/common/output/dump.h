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


#ifndef DUMP_INCLUDED
#define DUMP_INCLUDED


/*
 *    DUMP FILE VERSION NUMBER
 *
 *    These macros give the major and minor version numbers for the dump
 *    files.  The minor number is increased for upwardly compatible changes
 *    and the major number for incompatible changes.
 */

#define DUMP_major	((unsigned long) (DUMP_VERSION / 100))
#define DUMP_minor	((unsigned long) (DUMP_VERSION % 100))


/*
 *    DUMP FILE DECLARATIONS
 *
 *    The routines in this module are concerned with the output of the
 *    status dump file.
 */

extern void dump_declare(IDENTIFIER, LOCATION *, int) ;
extern void dump_undefine(IDENTIFIER, LOCATION *, int) ;
extern void dump_destr(IDENTIFIER, LOCATION *) ;
extern void dump_token(IDENTIFIER, IDENTIFIER) ;
extern void dump_instance(IDENTIFIER, TYPE, TYPE) ;
extern void dump_use(IDENTIFIER, LOCATION *, int) ;
extern void dump_call(IDENTIFIER, LOCATION *, int) ;
extern void dump_override(IDENTIFIER, IDENTIFIER) ;
extern void dump_alias(IDENTIFIER, IDENTIFIER, LOCATION *) ;
extern void dump_using(NAMESPACE, NAMESPACE, LOCATION *) ;
extern void dump_builtin(IDENTIFIER) ;
extern void dump_token_param(IDENTIFIER) ;
extern void dump_promote(INT_TYPE, INT_TYPE) ;
extern void dump_base(CLASS_TYPE) ;
extern void dump_begin_scope(IDENTIFIER, NAMESPACE, NAMESPACE, LOCATION *) ;
extern void dump_end_scope(IDENTIFIER, NAMESPACE, LOCATION *) ;
extern void dump_string_lit(string, string, unsigned) ;
extern void dump_include(LOCATION *, string, int, int) ;
extern int dump_error(ERROR, LOCATION *, int, int) ;
extern void init_dump(string, string) ;
extern void term_dump(void) ;

#ifdef FILE_INCLUDED
extern void dump_start(LOCATION *, INCL_DIR *) ;
extern void dump_end(LOCATION *) ;
#endif

extern ulong dump_id_next;
extern int dump_anon_class;
extern int dump_template;
extern int dump_implicit;

extern int do_dump;
extern int do_error;
extern int do_header;
extern int do_keyword;
extern int do_local;
extern int do_macro;
extern int do_scope;
extern int do_string;
extern int do_usage;


#endif
