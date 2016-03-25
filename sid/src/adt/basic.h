/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
 * basic.h --- Basic ADT.
 *
 * See the file "basic.c" for more information.
 */

#ifndef H_BASIC
#define H_BASIC

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/bitvec.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "entry.h"
#include "../grammar.h"
#include <exds/ostream.h>
#include "types.h"

/*
 * A terminal is represented by a BasicT. The term basic used to refer to
 * terminals in previous versions of SID.
 */
typedef struct BasicT {
	/*
	 * This is used to generate the token definition when outputting the
	 * parser.
	 */
    unsigned			terminal;

	/*
	 * The tuple of types e.g. for a terminal declared by:
	 *
	 * 	identifier : () -> (:StringT);
	 *
	 * .result contains a tuple of one element that indicates the only
	 * result is a StringT.
	 */
    TypeTupleT			result;

	/*
	 * The code given in the %terminals% extraction section of the action
	 * information file (the .act file). This is stored as a void * because
	 * the true type will depend on the output language used.
	 */
    void *			result_code;

	/*
	 * Indicates if the terminal is ignored or not, i.e. declared with a
	 * preceding ! in the .sid file.
	 */
    bool			ignored;
} BasicT;

typedef struct BasicClosureT {
    BitVecT *			bitvec;
    GrammarT *			grammar;
} BasicClosureT;

BasicT *		basic_create(GrammarT *, bool);
unsigned		basic_terminal(BasicT *);
TypeTupleT *	basic_result(BasicT *);
void *		basic_get_result_code(BasicT *);
void		basic_set_result_code(BasicT *, void *);
bool		basic_get_ignored(BasicT *);
void		basic_iter_for_table(BasicT *, bool,
					     void(*)(EntryT *, void *),
					     void *);

void		write_basics(OStreamT *, BasicClosureT *);

#endif /* !defined (H_BASIC) */
