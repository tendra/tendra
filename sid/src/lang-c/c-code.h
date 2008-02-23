/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
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

/*
 * c-code.h - SID C code stuff.
 * See the file "c-code.c" for details.
 */

#ifndef H_C_CODE
#define H_C_CODE

#include "../os-interface.h"
#include "c-out-info.h"
#include <exds/cstring.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "../adt/entry.h"
#include "../adt/rstack.h"
#include "../adt/rule.h"
#include "../adt/table.h"
#include "../adt/types.h"

typedef enum {
    CCT_STRING,
    CCT_LABEL,
    CCT_IDENT,
    CCT_MOD_IDENT,
    CCT_REF_IDENT,
    CCT_EXCEPTION,
    CCT_ADVANCE,
    CCT_TERMINAL
} CCodeItemTypeT;

typedef struct CCodeItemT {
    struct CCodeItemT	       *next;
    CCodeItemTypeT		type;
    union {
	NStringT		string;
	EntryT *			ident;
    } u;
} CCodeItemT;

typedef struct CCodeT {
    CCodeItemT *			head;
    CCodeItemT *		       *tail;
    unsigned			line;
    char *			file;
    TypeTupleT			param;
    TypeTupleT			result;
} CCodeT;

extern CCodeT *		c_code_create(char *, unsigned);
extern void		c_code_append_string(CCodeT *, NStringT *);
extern void		c_code_append_label(CCodeT *, NStringT *);
extern void		c_code_append_identifier(CCodeT *, NStringT *);
extern void		c_code_append_modifiable(CCodeT *, NStringT *);
extern void		c_code_append_reference(CCodeT *, NStringT *);
extern void		c_code_append_exception(CCodeT *);
extern void		c_code_append_advance(CCodeT *);
extern void		c_code_append_terminal(CCodeT *);
extern void		c_code_check(CCodeT *, BoolT, BoolT, TypeTupleT *,
				     TypeTupleT *, TableT *);
extern char *		c_code_file(CCodeT *);
extern unsigned		c_code_line(CCodeT *);
extern TypeTupleT *	c_code_param(CCodeT *);
extern TypeTupleT *	c_code_result(CCodeT *);
extern void		c_code_deallocate(CCodeT *);

extern void		c_output_c_code_action(COutputInfoT *, CCodeT *,
					       TypeTupleT *, TypeTupleT *,
					       SaveRStackT *, RuleT *);
extern void		c_output_c_code_basic(COutputInfoT *, CCodeT *, TypeTupleT *,
					      SaveRStackT *);
extern void		c_output_c_code_assign(COutputInfoT *, CCodeT *, EntryT *,
					       EntryT *, EntryT *, BoolT, BoolT);
extern void		c_output_c_code_param_assign(COutputInfoT *, CCodeT *,
						     EntryT *, EntryT *);
extern void		c_output_c_code_result_assign(COutputInfoT *, CCodeT *,
						      EntryT *, EntryT *);
extern void		c_output_c_code(COutputInfoT *, CCodeT *);

#endif /* !defined (H_C_CODE) */
