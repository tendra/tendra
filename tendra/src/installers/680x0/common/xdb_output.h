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
 *    		 Crown Copyright (c) 1996
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
/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------*/


#ifndef XDB_OUTPUT_INCLUDED
#define XDB_OUTPUT_INCLUDED


/*
 *    TYPE REPRENTING DIAGNOSTIC DIRECTIVES
 */

typedef struct {
    int instr;
    long old_size;
    long new_size;
} diag_directive;

extern diag_directive dd [];


/*
 *    INDEX TO ARRAY OF DIAGNOSTIC DIRECTIVES
 *
 *    These macros correspond to the entries in the table above.
 */

#define  xdb_array		0
#define  xdb_begin		1
#define  xdb_const		2
#define  xdb_dvar		3
#define  xdb_end		4
#define  xdb_entry		5
#define  xdb_enum		6
#define  xdb_field		7
#define  xdb_file		8
#define  xdb_fparam		9
#define  xdb_function		10
#define  xdb_functype		11
#define  xdb_import		12
#define  xdb_label		13
#define  xdb_memenum		14
#define  xdb_module		15
#define  xdb_pointer		16
#define  xdb_set		17
#define  xdb_srcfile		18
#define  xdb_struct		19
#define  xdb_subrange		20
#define  xdb_svar		21
#define  xdb_tagdef		22
#define  xdb_typedef		23
#define  xdb_union		24
#define  xdb_variant		25


/*
 *    DIAGNOSTIC FORMS SUPPORTED
 */

#define  DIAG_XDB_OLD		0
#define  DIAG_XDB_NEW		1
#define  DIAG_STAB		2
#define  DIAG_UNKNOWN		3


extern bool diag_format;
extern long crt_diag_proc_lab;

extern void init_diag(void) ;
extern void copy_diag(void) ;
extern void slt_exit(void) ;
extern void dnt_begin(void) ;
extern int dnt_end(void) ;
extern void diag_string(FILE *, char *) ;
extern void diag_source(char *, long, int) ;
extern void diag_source_file(char *, long) ;
extern void diag_globl_variable(diag_type, char *, int, char *, int) ;
extern void diag_local_variable(diag_type, char *, long) ;
extern void diag_type_defn(char *, diag_type) ;
extern void diag_proc_main(diag_type, exp, char *, int, char *) ;

#endif
