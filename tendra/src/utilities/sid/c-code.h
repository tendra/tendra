/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
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


/*** c-code.h --- SID C code stuff.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "c-code.c" for details.
 */

#ifndef H_C_CODE
#define H_C_CODE

#include "config.h"
#include "c-out-info.h"
#include "cstring.h"
#include "dalloc.h"
#include "dstring.h"
#include "entry.h"
#include "rstack.h"
#include "rule.h"
#include "table.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

typedef enum {
	CCT_STRING,
	CCT_LABEL,
	CCT_IDENT,
	CCT_MOD_IDENT,
	CCT_REF_IDENT,
	CCT_EXCEPTION,
	CCT_ADVANCE,
	CCT_TERMINAL
} CCodeItemTypeT, *CCodeItemTypeP;

typedef struct CCodeItemT {
	struct CCodeItemT	       *next;
	CCodeItemTypeT		type;
	union {
		NStringT		string;
		EntryP			ident;
	} u;
} CCodeItemT, *CCodeItemP;

typedef struct CCodeT {
	CCodeItemP			head;
	CCodeItemP		       *tail;
	unsigned			line;
	char *				file;
	TypeTupleT			param;
	TypeTupleT			result;
} CCodeT, *CCodeP;

/*--------------------------------------------------------------------------*/

CCodeP	c_code_create(char *, unsigned);
void	c_code_append_string(CCodeP, NStringP);
void	c_code_append_label(CCodeP, NStringP);
void	c_code_append_identifier(CCodeP, NStringP);
void	c_code_append_modifiable(CCodeP, NStringP);
void	c_code_append_reference(CCodeP, NStringP);
void	c_code_append_exception(CCodeP);
void	c_code_append_advance(CCodeP);
void	c_code_append_terminal(CCodeP);
void	c_code_check(CCodeP, BoolT, BoolT, TypeTupleP, TypeTupleP, TableP);
char *	c_code_file(CCodeP);
unsigned c_code_line(CCodeP);
TypeTupleP c_code_param(CCodeP);
TypeTupleP c_code_result(CCodeP);
void	c_code_deallocate(CCodeP);

void	c_output_c_code_action(COutputInfoP, CCodeP, TypeTupleP, TypeTupleP, SaveRStackP,
										   RuleP);
void	c_output_c_code_basic(COutputInfoP, CCodeP, TypeTupleP, SaveRStackP);
void	c_output_c_code_assign(COutputInfoP, CCodeP, EntryP, EntryP, EntryP, BoolT, BoolT);
void	c_output_c_code_param_assign(COutputInfoP, CCodeP, EntryP, EntryP);
void	c_output_c_code_result_assign(COutputInfoP, CCodeP, EntryP, EntryP);
void	c_output_c_code(COutputInfoP, CCodeP);

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define c_code_file(c) ((c)->file)
#define c_code_line(c) ((c)->line)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_C_CODE) */
