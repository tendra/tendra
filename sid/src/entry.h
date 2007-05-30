/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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


/*** entry.h --- Identifier table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "entry.c" for more information.
 *
 *** Change Log:
 * $Log: entry.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:11  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:34  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_ENTRY
#define H_ENTRY

#include "os-interface.h"
#include "dalloc.h"
#include "dstring.h"
#include "ostream.h"
#include "key.h"

/* To avoid circularity: */
#ifdef __TenDRA__
#pragma TenDRA begin
#pragma TenDRA complete struct/union analysis off
#endif
struct ActionT;
struct BasicT;
struct NameT;
struct RuleT;
struct TypeT;

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int EntryTypeT, *EntryTypeP;
#define ET_TYPE		(0)
#define ET_BASIC	(1)
#define ET_RULE		(2)
#define ET_ACTION	(3)
#define ET_NAME		(4)
#define ET_RENAME	(5)
#define ET_PREDICATE	(6)
#define ET_NON_LOCAL	(7)
#else
typedef enum {
    ET_TYPE,
    ET_BASIC,
    ET_RULE,
    ET_ACTION,
    ET_NAME,
    ET_RENAME,
    ET_PREDICATE,
    ET_NON_LOCAL
} EntryTypeT, *EntryTypeP;
#endif /* defined (FS_NO_ENUM) */

typedef struct EntryT {
    struct EntryT	       *next;
    KeyT			key;
    BoolT			mapped;
    NStringT			mapping;
    EntryTypeT			type;
    BoolT			traced;
    union {
	struct BasicT	       *basic;
	struct RuleT	       *rule;
	struct ActionT	       *action;
	struct TypeT	       *type;
	struct EntryT	       *non_local;
    } u;
    struct NameT	       *name;
} EntryT, *EntryP;

/*--------------------------------------------------------------------------*/

extern EntryP		entry_create_from_string(NStringP, unsigned,
						 EntryTypeT);
extern EntryP		entry_create_from_number(unsigned, EntryTypeT, BoolT,
						 EntryP);
extern void		entry_set_basic(EntryP, struct BasicT *);
extern void		entry_set_rule(EntryP, struct RuleT *);
extern void		entry_set_action(EntryP, struct ActionT *);
extern void		entry_set_type(EntryP, struct TypeT *);
extern void		entry_set_non_local(EntryP, EntryP);
extern EntryP		entry_next(EntryP);
extern EntryP	       *entry_next_ref(EntryP);
extern KeyP		entry_key(EntryP);
extern EntryTypeT	entry_type(EntryP);
extern void		entry_change_type(EntryP, EntryTypeT);
extern BoolT		entry_is_basic(EntryP);
extern BoolT		entry_is_action(EntryP);
extern BoolT		entry_is_rule(EntryP);
extern BoolT		entry_is_type(EntryP);
extern BoolT		entry_is_non_local(EntryP);
extern struct BasicT   *entry_get_basic(EntryP);
extern struct ActionT  *entry_get_action(EntryP);
extern struct RuleT    *entry_get_rule(EntryP);
extern struct NameT    *entry_get_name(EntryP);
extern struct TypeT    *entry_get_type(EntryP);
extern EntryP		entry_get_non_local(EntryP);
extern void		entry_set_mapping(EntryP, NStringP);
extern NStringP		entry_get_mapping(EntryP);
extern void		entry_iter(EntryP, BoolT, void(*)(EntryP, GenericP),
				   GenericP);
extern void		entry_not_traced(EntryP);
extern BoolT		entry_is_traced(EntryP);

#endif /* !defined (H_ENTRY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
