/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * c-code.h - SID C code stuff.
 * See the file "c-code.c" for details.
 */

#ifndef H_C_CODE
#define H_C_CODE

#include "c-out-info.h"
#include <exds/common.h>
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
    CCT_BASIC,
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
	EntryT *			basic;
    } u;
} CCodeItemT;

typedef struct CCodeT {
    CCodeItemT *			head;
    CCodeItemT *		       *tail;
    unsigned			line;
    const char *		file;
    TypeTupleT			param;
    TypeTupleT			result;
} CCodeT;

CCodeT *		c_code_create(const char *, unsigned);
void		c_code_append_string(CCodeT *, NStringT *);
void		c_code_append_basic(CCodeT *, NStringT *);
void		c_code_append_label(CCodeT *, NStringT *);
void		c_code_append_identifier(CCodeT *, NStringT *);
void		c_code_append_modifiable(CCodeT *, NStringT *);
void		c_code_append_reference(CCodeT *, NStringT *);
void		c_code_append_exception(CCodeT *);
void		c_code_append_advance(CCodeT *);
void		c_code_append_terminal(CCodeT *);
void		c_code_check(CCodeT *, bool, bool, bool, TypeTupleT *,
				     TypeTupleT *, TableT *);
const char *	c_code_file(CCodeT *);
unsigned		c_code_line(CCodeT *);
TypeTupleT *	c_code_param(CCodeT *);
TypeTupleT *	c_code_result(CCodeT *);
void		c_code_deallocate(CCodeT *);

void		c_output_c_code_action(COutputInfoT *, CCodeT *,
					       TypeTupleT *, TypeTupleT *,
					       SaveRStackT *, RuleT *);
void		c_output_c_code_basic(COutputInfoT *, CCodeT *, TypeTupleT *,
					      SaveRStackT *, RuleT *);
void		c_output_c_code_assign(COutputInfoT *, CCodeT *, EntryT *,
					       EntryT *, EntryT *, bool, bool);
void		c_output_c_code_param_assign(COutputInfoT *, CCodeT *,
						     EntryT *, EntryT *);
void		c_output_c_code_result_assign(COutputInfoT *, CCodeT *,
						      EntryT *, EntryT *);
void		c_output_c_code(COutputInfoT *, CCodeT *);

#endif /* !defined (H_C_CODE) */
