/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
 * c-out-types.h --- Output type objects.
 *
 * See the file "c-out-types.c" for more information.
 */

#ifndef H_C_OUT_TYPES
#define H_C_OUT_TYPES

#include "c-output.h"
#include "../adt/rstack.h"
#include "../adt/rule.h"
#include "../adt/table.h"
#include "../adt/types.h"

void	c_output_assign(COutputInfoT *, EntryT *, EntryT *, SaveRStackT *,
				SaveRStackT *, unsigned);
void	c_output_type_decl(COutputInfoT *, TypeTupleT *, TypeTupleT *);
void	c_output_type_defn(COutputInfoT *, TypeTupleT *, TypeTupleT *);
void	c_output_result_assign(COutputInfoT *, TypeTupleT *, unsigned);
void	c_output_alt_names(COutputInfoT *, TypeTupleT *, TypeTupleT *,
				   SaveRStackT *, unsigned);
void	c_output_rule_params(COutputInfoT *, TypeTupleT *, TypeTupleT *,
				     SaveRStackT *);
void	c_output_rename(COutputInfoT *, TypeTupleT *, TypeTupleT *,
				SaveRStackT *, unsigned);
void	c_output_tail_decls(COutputInfoT *, TypeTupleT *, SaveRStackT *,
				    TypeTupleT *, SaveRStackT *, unsigned);
bool	c_output_required_copies(COutputInfoT *, TypeTupleT *, TypeTupleT *,
					 RStackT *, SaveRStackT *, unsigned,
					 TableT *);

#endif /* !defined (H_C_OUT_TYPES) */
