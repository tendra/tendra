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


/*** name.c --- Name ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the name manipulation routines.
 */

#include "msgcat.h"
#include "name.h"

/*--------------------------------------------------------------------------*/

NameP
name_create(void)
{
	NameP name = ALLOCATE (NameT);
	
	name->clash    = FALSE;
	name->used     = FALSE;
	name->labelled = FALSE;
	return (name);
}

BoolT
name_test_and_set_clash(NameP name)
{
	BoolT clash = name->clash;
	
	name->clash = TRUE;
	return (clash);
}

#ifdef FS_FAST
#undef name_reset_clash
#endif /* defined (FS_FAST) */
void
name_reset_clash(NameP name)
{
	name->clash = FALSE;
}
#ifdef FS_FAST
#define name_reset_clash(n) ((n)->clash = FALSE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef name_is_used
#endif /* defined (FS_FAST) */
BoolT
name_is_used(NameP name)
{
	return (name->used);
}
#ifdef FS_FAST
#define name_is_used(n) ((n)->used)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef name_used
#endif /* defined (FS_FAST) */
void
name_used(NameP name)
{
	name->used = TRUE;
}
#ifdef FS_FAST
#define name_used(n) ((n)->used = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef name_not_used
#endif /* defined (FS_FAST) */
void
name_not_used(NameP name)
{
	name->used = FALSE;
}
#ifdef FS_FAST
#define name_not_used(n) ((n)->used = FALSE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef name_get_label
#endif /* defined (FS_FAST) */
unsigned
name_get_label(NameP name)
{
	ASSERT (name->labelled);
	return (name->label);
}
#ifdef FS_FAST
#define name_get_label(n) ((n)->label)
#endif /* defined (FS_FAST) */

void
name_set_label(NameP name, unsigned label)
{
	name->labelled = TRUE;
	name->label    = label;
}

#ifdef FS_FAST
#undef name_reset_label
#endif /* defined (FS_FAST) */
void
name_reset_label(NameP name)
{
	name->labelled = FALSE;
}
#ifdef FS_FAST
#define name_reset_label(n) ((n)->labelled = FALSE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef name_has_label
#endif /* defined (FS_FAST) */
BoolT
name_has_label(NameP name)
{
	return (name->labelled);
}
#ifdef FS_FAST
#define name_has_label(n) ((n)->labelled)
#endif /* defined (FS_FAST) */
