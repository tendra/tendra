/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/*** action.c --- Action ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the action manipulation routines.
 */

#include "action.h"
#include "basic.h"
#include "name.h"
#include "rule.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

ActionP
action_create(void)
{
	ActionP action = ALLOCATE (ActionT);
	
	types_init (action_param (action));
	types_init (action_result (action));
	action->code = NIL (GenericP);
	return (action);
}

#ifdef FS_FAST
#undef action_param
#endif /* defined (FS_FAST) */
TypeTupleP
action_param(ActionP action)
{
	return (&(action->param));
}
#ifdef FS_FAST
#define action_param(a) (&((a)->param))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef action_result
#endif /* defined (FS_FAST) */
TypeTupleP
action_result(ActionP action)
{
	return (&(action->result));
}
#ifdef FS_FAST
#define action_result(a) (&((a)->result))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef action_get_code
#endif /* defined (FS_FAST) */
GenericP
action_get_code(ActionP action)
{
	return (action->code);
}
#ifdef FS_FAST
#define action_get_code(a) ((a)->code)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef action_set_code
#endif /* defined (FS_FAST) */
void
action_set_code(ActionP action, GenericP code)
{
	action->code = code;
}
#ifdef FS_FAST
#define action_set_code(a, c) ((a)->code = (c))
#endif /* defined (FS_FAST) */

void
action_iter_for_table(ActionP action, BoolT full,
		void (*proc)(EntryP, GenericP), GenericP closure)
{
	if (full) {
		types_iter_for_table (action_param (action), proc, closure);
		types_iter_for_table (action_result (action), proc, closure);
	}
}
