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


/*** entry.c --- Identifier table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the identifier table routines used by SID.
 *
 *** Change Log:
 * $Log: entry.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:08  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:33  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "entry.h"
#include "action.h"
#include "basic.h"
#include "gen-errors.h"
#include "name.h"
#include "rule.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#undef entry_traced
#endif /* defined (FS_FAST) */
static void
entry_traced PROTO_N ((entry))
	     PROTO_T (EntryP entry)
{
    entry->traced = TRUE;
}
#ifdef FS_FAST
#define entry_traced(e) ((e)->traced = TRUE)
#endif /* defined (FS_FAST) */

/*--------------------------------------------------------------------------*/

EntryP
entry_create_from_string PROTO_N ((key, number, type))
			 PROTO_T (NStringP   key X
				  unsigned   number X
				  EntryTypeT type)
{
    EntryP entry = ALLOCATE (EntryT);

    entry->next   = NIL (EntryP);
    key_init_from_string (entry_key (entry), key, number);
    entry->mapped = FALSE;
    nstring_init (&(entry->mapping));
    entry->type   = type;
    entry->name   = name_create ();
    entry->traced = FALSE;
    return (entry);
}

EntryP
entry_create_from_number PROTO_N ((key, type, traced, next))
			 PROTO_T (unsigned   key X
				  EntryTypeT type X
				  BoolT      traced X
				  EntryP     next)
{
    EntryP entry = ALLOCATE (EntryT);

    entry->next   = next;
    key_init_from_number (entry_key (entry), key);
    entry->mapped = FALSE;
    nstring_init (&(entry->mapping));
    entry->type   = type;
    entry->name   = name_create ();
    entry->traced = traced;
    return (entry);
}

#ifdef FS_FAST
#undef entry_set_basic
#endif /* defined (FS_FAST) */
void
entry_set_basic PROTO_N ((entry, basic))
		PROTO_T (EntryP entry X
			 BasicP basic)
{
    ASSERT (entry_is_basic (entry));
    entry->u.basic = basic;
}
#ifdef FS_FAST
#define entry_set_basic(e, b) ((e)->u.basic = (b))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_set_rule
#endif /* defined (FS_FAST) */
void
entry_set_rule PROTO_N ((entry, rule))
	       PROTO_T (EntryP entry X
			RuleP  rule)
{
    ASSERT (entry_is_rule (entry));
    entry->u.rule = rule;
}
#ifdef FS_FAST
#define entry_set_rule(e, r) ((e)->u.rule = (r))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_set_action
#endif /* defined (FS_FAST) */
void
entry_set_action PROTO_N ((entry, action))
		 PROTO_T (EntryP  entry X
			  ActionP action)
{
    ASSERT (entry_is_action (entry));
    entry->u.action = action;
}
#ifdef FS_FAST
#define entry_set_action(e, a) ((e)->u.action = (a))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_set_type
#endif /* defined (FS_FAST) */
void
entry_set_type PROTO_N ((entry, type))
	       PROTO_T (EntryP entry X
			TypeP  type)
{
    ASSERT (entry_is_type (entry));
    entry->u.type = type;
}
#ifdef FS_FAST
#define entry_set_type(e, t) ((e)->u.type = (t))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_set_non_local
#endif /* defined (FS_FAST) */
void
entry_set_non_local PROTO_N ((entry, type))
		    PROTO_T (EntryP entry X
			     EntryP type)
{
    ASSERT (entry_is_non_local (entry));
    entry->u.non_local = type;
}
#ifdef FS_FAST
#define entry_set_non_local(e, t) ((e)->u.non_local = (t))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_next
#endif /* defined (FS_FAST) */
EntryP
entry_next PROTO_N ((entry))
	   PROTO_T (EntryP entry)
{
    return (entry->next);
}
#ifdef FS_FAST
#define entry_next(e) ((e)->next)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_next_ref
#endif /* defined (FS_FAST) */
EntryP *
entry_next_ref PROTO_N ((entry))
	       PROTO_T (EntryP entry)
{
    return (&(entry->next));
}
#ifdef FS_FAST
#define entry_next_ref(e) (&((e)->next))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_key
#endif /* defined (FS_FAST) */
KeyP
entry_key PROTO_N ((entry))
	  PROTO_T (EntryP entry)
{
    return (&(entry->key));
}
#ifdef FS_FAST
#define entry_key(e) (&((e)->key))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_type
#endif /* defined (FS_FAST) */
EntryTypeT
entry_type PROTO_N ((entry))
	   PROTO_T (EntryP entry)
{
    return (entry->type);
}
#ifdef FS_FAST
#define entry_type(e) ((e)->type)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_change_type
#endif /* defined (FS_FAST) */
void
entry_change_type PROTO_N ((entry, type))
		  PROTO_T (EntryP     entry X
			   EntryTypeT type)
{
    entry->type = type;
}
#ifdef FS_FAST
#define entry_change_type(e, t) ((e)->type= (t))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_basic
#endif /* defined (FS_FAST) */
BoolT
entry_is_basic PROTO_N ((entry))
	       PROTO_T (EntryP entry)
{
    return (entry->type == ET_BASIC);
}
#ifdef FS_FAST
#define entry_is_basic(e) ((e)->type == ET_BASIC)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_action
#endif /* defined (FS_FAST) */
BoolT
entry_is_action PROTO_N ((entry))
		PROTO_T (EntryP entry)
{
    return (entry->type == ET_ACTION);
}
#ifdef FS_FAST
#define entry_is_action(e) ((e)->type == ET_ACTION)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_rule
#endif /* defined (FS_FAST) */
BoolT
entry_is_rule PROTO_N ((entry))
	      PROTO_T (EntryP entry)
{
    return (entry->type == ET_RULE);
}
#ifdef FS_FAST
#define entry_is_rule(e) ((e)->type == ET_RULE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_type
#endif /* defined (FS_FAST) */
BoolT
entry_is_type PROTO_N ((entry))
	      PROTO_T (EntryP entry)
{
    return (entry->type == ET_TYPE);
}
#ifdef FS_FAST
#define entry_is_type(e) ((e)->type == ET_TYPE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_non_local
#endif /* defined (FS_FAST) */
BoolT
entry_is_non_local PROTO_N ((entry))
		   PROTO_T (EntryP entry)
{
    return (entry->type == ET_NON_LOCAL);
}
#ifdef FS_FAST
#define entry_is_non_local(e) ((e)->type == ET_NON_LOCAL)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_basic
#endif /* defined (FS_FAST) */
BasicP
entry_get_basic PROTO_N ((entry))
		PROTO_T (EntryP entry)
{
    ASSERT (entry_is_basic (entry));
    return (entry->u.basic);
}
#ifdef FS_FAST
#define entry_get_basic(e) ((e)->u.basic)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_action
#endif /* defined (FS_FAST) */
ActionP
entry_get_action PROTO_N ((entry))
		 PROTO_T (EntryP entry)
{
    ASSERT (entry_is_action (entry));
    return (entry->u.action);
}
#ifdef FS_FAST
#define entry_get_action(e) ((e)->u.action)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_rule
#endif /* defined (FS_FAST) */
RuleP
entry_get_rule PROTO_N ((entry))
	       PROTO_T (EntryP entry)
{
    ASSERT (entry_is_rule (entry));
    return (entry->u.rule);
}
#ifdef FS_FAST
#define entry_get_rule(e) ((e)->u.rule)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_name
#endif /* defined (FS_FAST) */
NameP
entry_get_name PROTO_N ((entry))
	       PROTO_T (EntryP entry)
{
    return (entry->name);
}
#ifdef FS_FAST
#define entry_get_name(e) ((e)->name)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_type
#endif /* defined (FS_FAST) */
TypeP
entry_get_type PROTO_N ((entry))
	       PROTO_T (EntryP entry)
{
    ASSERT (entry_is_type (entry));
    return (entry->u.type);
}
#ifdef FS_FAST
#define entry_get_type(e) ((e)->u.type)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_non_local
#endif /* defined (FS_FAST) */
EntryP
entry_get_non_local PROTO_N ((entry))
		    PROTO_T (EntryP entry)
{
    ASSERT (entry_is_non_local (entry));
    return (entry->u.non_local);
}
#ifdef FS_FAST
#define entry_get_non_local(e) ((e)->u.non_local)
#endif /* defined (FS_FAST) */

void
entry_set_mapping PROTO_N ((entry, mapping))
		  PROTO_T (EntryP   entry X
			   NStringP mapping)
{
    if (entry->mapped) {
	nstring_destroy (&(entry->mapping));
    }
    nstring_assign (&(entry->mapping), mapping);
    entry->mapped = TRUE;
}

NStringP
entry_get_mapping PROTO_N ((entry))
		  PROTO_T (EntryP entry)
{
    if (entry->mapped) {
	return (&(entry->mapping));
    }
    return (NIL (NStringP));
}

void
entry_iter PROTO_N ((entry, full, proc, closure))
	   PROTO_T (EntryP   entry X
		    BoolT    full X
		    void   (*proc) PROTO_S ((EntryP, GenericP)) X
		    GenericP closure)
{
    if (!entry_is_traced (entry)) {
	entry_traced (entry);
	if (proc) {
	    (*proc) (entry, closure);
	}
	switch (entry_type (entry)) EXHAUSTIVE {
	  case ET_RULE: {
	      RuleP rule = entry_get_rule (entry);

	      rule_iter_for_table (rule, full, proc, closure);
	  }
	    break;
	  case ET_ACTION: {
	      ActionP action = entry_get_action (entry);

	      action_iter_for_table (action, full, proc, closure);
	  }
	    break;
	  case ET_BASIC: {
	      BasicP basic = entry_get_basic (entry);

	      basic_iter_for_table (basic, full, proc, closure);
	  }
	    break;
	  case ET_NON_LOCAL:
	    if (full) {
		entry_iter (entry_get_non_local (entry), TRUE, proc, closure);
	    }
	    break;
	  case ET_NAME:
	  case ET_TYPE:
	  case ET_RENAME:
	    /*NOTHING*/
	    break;
	  case ET_PREDICATE:
	    UNREACHED;
	}
    }
}

#ifdef FS_FAST
#undef entry_not_traced
#endif /* defined (FS_FAST) */
void
entry_not_traced PROTO_N ((entry))
		 PROTO_T (EntryP entry)
{
    entry->traced = FALSE;
}
#ifdef FS_FAST
#define entry_not_traced(e) ((e)->traced = FALSE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_traced
#endif /* defined (FS_FAST) */
BoolT
entry_is_traced PROTO_N ((entry))
		PROTO_T (EntryP entry)
{
    return (entry->traced);
}
#ifdef FS_FAST
#define entry_is_traced(e) ((e)->traced)
#endif /* defined (FS_FAST) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
