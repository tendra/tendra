/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:48 $
$Revision: 1.1.1.1 $
$Log: dwarf_queue.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/08/14  14:30:24  pwe
 * transferred from DJCH
 *
**********************************************************************/

#include <shared/xalloc.h>

#include "config.h"

#include "basicread.h"
#include "dwarf_out.h"
#include "dwarf_type.h"
#include "dwarf_queue.h"

#ifndef NULL
#define NULL((t_q_elem *)0)
#endif

typedef struct t_q_t {
	diag_type val;
	struct t_q_t *next;
} t_q_elem;

typedef t_q_elem *t_q_ptr;

static t_q_ptr t_q_head = NULL;
static t_q_ptr t_q_tail = NULL;

void
add_type_q(diag_type t)
{
	t_q_ptr new = (t_q_ptr)xcalloc(1, sizeof(t_q_elem));

	if (t->key == DIAG_TYPE_UNINIT) {
		failer("bad queue add");
	}

	new->val = t;
	new->next = NULL;
	if (t_q_head == NULL) {
		/* first one */
		t_q_head = new;
	} else {
		t_q_tail->next = new;
	}

	t_q_tail = new;
}


void
dump_type_q(void)
{
	while (t_q_head != NULL) {
		/* may call add_type_q */
		out_dwarf_user_type(t_q_head->val);

		t_q_head = t_q_head->next;
	}
}
