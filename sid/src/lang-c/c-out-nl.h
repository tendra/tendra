/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
 * c-out-nl.h - Output non local name list ADT objects.
 *
 * See the file "c-out-nl.c" for more information.
 */

#ifndef H_C_OUT_NL
#define H_C_OUT_NL

#include "c-output.h"
#include "../adt/non-local.h"
#include "../adt/rule.h"

void	c_output_non_locals(COutputInfoT *, NonLocalListT *);
void	c_output_declare_non_locals(COutputInfoT *, NonLocalListT *);
void	c_output_save_non_locals(COutputInfoT *, RuleT *, unsigned,
					 RStackT *, RStackT *, RuleT *, TableT *);
void	c_output_restore_non_locals(COutputInfoT *, RuleT *, unsigned,
					    RStackT *, RStackT *);

#endif /* !defined (H_C_OUT_NL) */
