/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#ifndef PRINT_INCLUDED
#define PRINT_INCLUDED


/*
    OBJECT PRINTING DECLARATIONS

    The routines in this module are used to print objects of the various
    basic types used in the program.  They are used primarily in error
    reporting, but print_pptok is also used by the stand-alone preprocessor
    action.
*/

extern int print_access(DECL_SPEC, BUFFER *, int);
extern int print_btype(BASE_TYPE, BUFFER *, int);
extern int print_ctype(CLASS_TYPE, QUALIFIER, int, BUFFER *, int);
extern int print_cv(CV_SPEC, BUFFER *, int);
extern int print_dspec(DECL_SPEC, BUFFER *, int);
extern int print_etype(ENUM_TYPE, int, BUFFER *, int);
extern int print_exp(EXP, int, BUFFER *, int);
extern int print_flt(FLOAT, BUFFER *, int);
extern int print_ftype(FLOAT_TYPE, BUFFER *, int);
extern int print_graph(GRAPH, int, BUFFER *, int);
extern int print_hashid(HASHID, int, int, BUFFER *, int);
extern int print_id_short(IDENTIFIER, QUALIFIER, BUFFER *, int);
extern int print_id_long(IDENTIFIER, QUALIFIER, BUFFER *, int);
extern int print_itype(INT_TYPE, BUFFER *, int);
extern int print_lex(int, BUFFER *, int);
extern int print_loc(LOCATION *, LOCATION *, BUFFER *, int);
extern int print_nat(NAT, int, BUFFER *, int);
extern int print_nspace(NAMESPACE, QUALIFIER, int, BUFFER *, int);
extern int print_ntype(BUILTIN_TYPE, BUFFER *, int);
extern int print_offset(OFFSET, BUFFER *, int);
extern int print_pptok(PPTOKEN *, BUFFER *, int);
extern int print_sort(TOKEN, int, BUFFER *, int);
extern int print_str(STRING, BUFFER *, int);
extern int print_tok_value(TOKEN, BUFFER *, int);
extern int print_token(IDENTIFIER, QUALIFIER, LIST(TOKEN), BUFFER *, int);
extern int print_type(TYPE, BUFFER *, int);
extern int print_type_list(LIST(TYPE), BUFFER *, int);
extern void print_char(unsigned long, int, int, BUFFER *);
extern void print_source(LOCATION *, int, int, const char *, FILE *);
extern const char *ntype_name[];
extern int print_type_alias;
extern int print_uniq_anon;
extern int print_id_desc;
extern int print_c_style;
extern BUFFER print_buff;


#endif
