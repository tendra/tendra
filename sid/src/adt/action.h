/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
 * action.h - Action ADT.
 *
 * See the file "action.c" for more information.
 */

#ifndef H_ACTION
#define H_ACTION

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "entry.h"
#include "types.h"

typedef struct ActionT {
	/*
	 * .param and .result hold respectively the input parameters and output
	 * parameters of the action. A TypeTupleT contains list of pairs of
	 * (name, type).
	 */
    TypeTupleT			param;
    TypeTupleT			result;

	/*
	 * The body of the action. The type depends on the output language
	 * specific type for blocks of code.
	 */
    void *			code;

	/*
	 * Indicates if the action is ignored or not, i.e. declared with a
	 * preceding ! in the .sid file.
	 */
    bool           ignored;
} ActionT;

ActionT *		action_create(bool);
TypeTupleT *	action_param(ActionT *);
TypeTupleT *	action_result(ActionT *);
void *		action_get_code(ActionT *);
void		action_set_code(ActionT *, void *);
bool		action_get_ignored(ActionT *);
void		action_iter_for_table(ActionT *, bool,
					      void(*)(EntryT *, void *),
					      void *);

#endif /* !defined (H_ACTION) */
