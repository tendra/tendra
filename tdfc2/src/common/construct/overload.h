/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef OVERLOAD_INCLUDED
#define OVERLOAD_INCLUDED


/*
    STRUCTURE REPRESENTING A LIST OF OVERLOADED FUNCTIONS

    During the resolution of overloaded functions, the set of candidate
    functions is formed into a table.  Each element of the table consists
    of a function identifier plus a rank for this candidate (see below) and,
    for viable candidates, a list of conversion sequence ranks for each
    argument.
*/

#ifndef CONVERT_INCLUDED
#include <construct/convert.h>
#endif

typedef struct {
	IDENTIFIER func;
	IDENTIFIER base;
	int kind;
	unsigned rank;
	CONVERSION *convs;
	EXP cond;
} CANDIDATE;

typedef struct {
	CANDIDATE *elem;
	unsigned size;
	unsigned max_size;
	CONVERSION *convs;
	unsigned nconvs;
} CANDIDATE_LIST;


/*
    FUNCTION OVERLOADING DECLARATIONS

    The routines in this module are concerned with function overloading.
*/

extern void swap_ptypes(IDENTIFIER);
extern IDENTIFIER resolve_call(IDENTIFIER, LIST(EXP), QUALIFIER, int);
extern EXP resolve_cast(TYPE, EXP, ERROR *, int, int, LIST(IDENTIFIER));
extern void add_candidates(CANDIDATE_LIST *, IDENTIFIER, int, int);
extern IDENTIFIER koenig_candidates(CANDIDATE_LIST *, IDENTIFIER, TYPE, int);
extern void swap_candidates(CANDIDATE_LIST *, unsigned);
extern ERROR list_candidates(ERROR, CANDIDATE_LIST *, unsigned);
extern CANDIDATE *resolve_overload(CANDIDATE_LIST *, LIST(EXP), TYPE, int);
extern CANDIDATE *resolve_ambiguous(CANDIDATE_LIST *, LIST(EXP), TYPE, int);
extern IDENTIFIER make_ambig_func(CANDIDATE_LIST *, IDENTIFIER, LIST(EXP),
				  QUALIFIER, ERROR *);
extern IDENTIFIER resolve_func(IDENTIFIER, TYPE, int, int, LIST(IDENTIFIER),
			       int *);
extern void free_candidates(CANDIDATE_LIST *);
extern CANDIDATE_LIST candidates;
extern unsigned match_no_viable;
extern unsigned match_no_args;
extern int resolved_kind;
extern int match_this;


/*
    RANKING OF CANDIDATES

    These values give the ranking values for candidate functions.  These
    correspond to the candidates with the wrong number of parameters, those
    with the right number of parameters (the plausible candidates), the
    viable candidates, and the best viable candidate.  They are is ascending
    order.
*/

#define RANK_IGNORE		((unsigned)0)
#define RANK_NONE		((unsigned)1)
#define RANK_ARGS		((unsigned)2)
#define RANK_VIABLE		((unsigned)3)
#define RANK_TARGET		((unsigned)4)
#define RANK_BEST		((unsigned)5)


/*
    CANDIDATE KINDS

    These values give the various kinds of candidate functions, simple
    functions, constructors, user-defined conversions, non-member operators,
    member operators and built-in operators.
*/

#define KIND_FUNC		0
#define KIND_CONSTR		1
#define KIND_CONV		2
#define KIND_OP			3
#define KIND_MEM_OP		4
#define KIND_BUILTIN		5
#define KIND_MARK		8


#endif
