/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rstack.h - Renaming stack ADT.
 *
 * See the file "rstack.c" for more information.
 */

#ifndef H_RSTACK
#define H_RSTACK

#include "table.h"
#include "types.h"

typedef struct TransStackEntryT {
    struct TransStackEntryT    *next;
    TypeRTransT			translator;
} TransStackEntryT;

typedef struct RStackT {
    TransStackEntryT *		head;
} RStackT;

typedef struct SaveRStackT {
    TransStackEntryT *		head;
} SaveRStackT;

void		 rstack_init(RStackT *);
void		 rstack_push_frame(RStackT *);
void		 rstack_compute_formal_renaming(RStackT *, TypeTupleT *);
void		 rstack_compute_formal_inlining(RStackT *, TypeTupleT *,
							TypeTupleT *);
void		 rstack_compute_local_renaming(RStackT *, TypeTupleT *,
						       TypeTupleT *, TableT *);
void		 rstack_add_translation(RStackT *, struct EntryT *,
						struct EntryT *,
						struct EntryT *, bool);
void		 rstack_save_state(RStackT *, SaveRStackT *);
struct EntryT	*rstack_get_translation(SaveRStackT *, struct EntryT *,
						 struct EntryT **, bool *);
void		 rstack_apply_for_non_locals(RStackT *, SaveRStackT *,
						     void(*)(struct EntryT *,
						     struct EntryT *,
						     void *), void *);
void		 rstack_pop_frame(RStackT *);
void		 rstack_destroy(RStackT *);

#endif /* !defined (H_RSTACK) */
