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

#include "config.h"
#include "common_types.h"
#include "xalloc.h"
#include "basicread.h"
#include "dwarf_out.h"
#include "dwarf_type.h"
#include "dwarf_queue.h"

#ifndef NULL
#define NULL ((t_q_elem *) 0)
#endif

typedef struct t_q_t
{
  diag_type val;
  struct t_q_t *next;
} t_q_elem;

typedef t_q_elem * t_q_ptr;

static t_q_ptr t_q_head = NULL;
static t_q_ptr t_q_tail = NULL;

void add_type_q
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
  t_q_ptr new = (t_q_ptr) xcalloc(1,sizeof(t_q_elem));

  if (t->key == DIAG_TYPE_UNINIT)
    failer("bad queue add");

  new->val = t;
  new->next = NULL;
  if (t_q_head == NULL)		/* first one */
    t_q_head = new;
  else
    t_q_tail->next = new;

  t_q_tail = new;
}

void dump_type_q
    PROTO_Z ()
{
  while (t_q_head != NULL)
  {
    out_dwarf_user_type(t_q_head->val);	/* may call add_type_q */
    t_q_head = t_q_head->next;
  }
}
