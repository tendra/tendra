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


#ifndef DEFS_INCLUDED
#define DEFS_INCLUDED

#include "namedecs.h"
#include "errors.h"
#include "includes.h"

typedef struct{
    int t;
    union Lex_v{int v; char * name; Tokdec * tokname;} val;
} LEX;

typedef struct{char *name; int t; void(*f)(void);} Constructs;
typedef struct{char *name; int t;} Terminals;

#define BUFFLEN 600
extern char buff[BUFFLEN];
extern unsigned long cLINE;
extern LEX lex_v;
extern long radix;
extern int lnum;
extern int bind;
extern long stoi(char * s, int n);

#define MINSI			0x80000000
#define MAXSI			0x7fffffff
#define MAXUSI			0xffffffff
#define MINSS			0x8000
#define MAXSS			0x7fff
#define MAXUSS			0xffff
#define MINSC			128
#define MAXSC			127
#define MAXUSC			255
#define MINSL			0x80000000
#define MAXSL			0x7fffffff
#define MAXUSL			0xffffffff
#define MANT_DOUBLE		53
#define MINEXP_DOUBLE		1022
#define MAXEXP_DOUBLE		1023
#define MANT_FLOAT		24
#define MINEXP_FLOAT		126
#define MAXEXP_FLOAT		127

#define UL(x)			((unsigned long)(x))
#define UI(x)			((unsigned int)(x))
#define UC(x)			((unsigned char)(x))

#define access_t		lex_access__cons
#define alignment_t		lex_alignment__cons
#define bitfield_variety_t	lex_bitfield__variety__cons
#define bool_t			lex_bool__cons
#define error_code_t		lex_error__code__cons
#define error_treatment_t	lex_error__treatment__cons
#define exp_t			lex_exp__cons
#define floating_variety_t	lex_floating__variety__cons
#define nat_t			lex_nat__cons
#define ntest_t			lex_ntest__cons
#define rounding_mode_t		lex_rounding__mode__cons
#define shape_t			lex_shape__cons
#define signed_nat_t		lex_signed__nat__cons
#define string_t		lex_string__cons
#define tag_t			lex_tag__cons
#define token_t			lex_token__cons
#define transfer_mode_t		lex_transfer__mode__cons
#define variety_t		lex_variety__cons

#define access_sort		lex_access__sort
#define al_tag_sort		lex_al__tag__sort
#define alignment_sort		lex_alignment__sort
#define bitfield_variety_sort	lex_bitfield__variety__sort
#define bool_sort		lex_bool__sort
#define error_treatment_sort	lex_error__treatment__sort
#define exp_sort		lex_exp__sort
#define floating_variety_sort	lex_floating__variety__sort
#define label_sort		lex_label__sort
#define nat_sort		lex_nat__sort
#define ntest_sort		lex_ntest__sort
#define rounding_mode_sort	lex_rounding__mode__sort
#define shape_sort		lex_shape__sort
#define signed_nat_sort		lex_signed__nat__sort
#define string_sort		lex_string__sort
#define tag_sort		lex_tag__sort
#define token_sort		lex_token__sort
#define transfer_mode_sort	lex_transfer__mode__sort
#define variety_sort		lex_variety__sort

#define access_tok		lex_access__tok
#define al_tag_tok		lex_al__tag__tok
#define alignment_tok		lex_alignment__tok
#define bitfield_variety_tok	lex_bitfield__variety__tok
#define bool_tok		lex_bool__tok
#define error_treatment_tok	lex_error__treatment__tok
#define exp_tok			lex_exp__tok
#define floating_variety_tok	lex_floating__variety__tok
#define label_tok		lex_label__tok
#define nat_tok			lex_nat__tok
#define ntest_tok		lex_ntest__tok
#define rounding_mode_tok	lex_rounding__mode__tok
#define shape_tok		lex_shape__tok
#define signed_nat_tok		lex_signed__nat__tok
#define string_tok		lex_string__tok
#define tag_tok			lex_tag__tok
#define token_tok		lex_token__tok
#define transfer_mode_tok	lex_transfer__mode__tok
#define variety_tok		lex_variety__tok


#endif
