/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/*** name-entry.h --- Name table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "name-entry.c" for more information.
 *
 *** Change Log:*/

/****************************************************************************/

#ifndef H_NAME_ENTRY
#define H_NAME_ENTRY

#include "os-interface.h"
#include "dalloc.h"
#include "name-key.h"

struct ShapeTableT;
struct ShapeEntryT;
struct CapsuleT;
struct LibCapsuleT;
struct NameTableT;
struct UnitTableT;

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int NameEntryTypeT, *NameEntryTypeP;
#define NT_INDIRECT		(0)
#define NT_INDIRECT_CYCLING	(1)
#define NT_INDIRECT_DONE	(2)
#define NT_DIRECT		(3)
#define NT_PLACEHOLDER		(4)
#else
typedef enum {
    NT_INDIRECT,
    NT_INDIRECT_CYCLING,
    NT_INDIRECT_DONE,
    NT_DIRECT,
    NT_PLACEHOLDER
} NameEntryTypeT, *NameEntryTypeP;
#endif /* defined (FS_NO_ENUM) */

typedef struct NameEntryT {
    struct NameEntryT	       *next;
    NameKeyT			key;
    NameEntryTypeT		type;
    union {
		struct {
			unsigned		id;
			unsigned		use;
			struct CapsuleT    *definition;
			struct LibCapsuleT *lib_definition;
			struct NameEntryT  *list_next;
		} direct;
		struct NameEntryT      *indirect;
    } u;
} NameEntryT, *NameEntryP;

/*--------------------------------------------------------------------------*/

extern NameEntryP		name_entry_create_direct(NameKeyP, struct ShapeEntryT *);
extern NameEntryP		name_entry_create_indirect(NameKeyP, NameEntryP);
extern NameEntryP		name_entry_create_place(NameKeyP);
extern void			name_entry_make_direct(NameEntryP, struct ShapeEntryT *);
extern void			name_entry_make_indirect(NameEntryP, NameEntryP);
extern NameEntryP		name_entry_resolve_renames(NameEntryP, NStringP, BoolT);
extern NameKeyP			name_entry_key(NameEntryP);
extern NameEntryP		name_entry_next(NameEntryP);
extern NameEntryP	       *name_entry_next_ref(NameEntryP);
extern BoolT			name_entry_is_direct(NameEntryP);
extern BoolT			name_entry_is_indirect(NameEntryP);
extern BoolT			name_entry_is_place(NameEntryP);
extern unsigned			name_entry_id(NameEntryP);
extern void			name_entry_merge_use(NameEntryP, unsigned);
extern unsigned			name_entry_get_use(NameEntryP);
extern void			name_entry_hide(NameEntryP);
extern void			name_entry_unhide(NameEntryP);
extern BoolT			name_entry_is_hidden(NameEntryP);
extern void			name_entry_set_definition(NameEntryP, struct CapsuleT *);
extern struct CapsuleT	       *name_entry_get_definition(NameEntryP);
extern void			name_entry_set_lib_definition(NameEntryP, struct LibCapsuleT *);
extern struct LibCapsuleT      *name_entry_get_lib_definition(NameEntryP);
extern NameEntryP		name_entry_list_next(NameEntryP);
extern NameEntryP	       *name_entry_list_next_ref(NameEntryP);
extern NameEntryP		name_entry_get_indirect(NameEntryP);
extern NameEntryP		name_entry_deallocate(NameEntryP);

extern void			name_entry_do_count(NameEntryP, GenericP);
extern void			name_entry_write_name(NameEntryP, GenericP);
extern void			name_entry_compute_tld_size(NameEntryP, GenericP);
extern void			name_entry_write_tld(NameEntryP, GenericP);
extern void			name_entry_check_multi_defs(NameEntryP, GenericP);
extern void			name_entry_do_lib_count(NameEntryP, GenericP);
extern void			name_entry_do_lib_write(NameEntryP, GenericP);
extern void			name_entry_suppress(NameEntryP, GenericP);
extern void			name_entry_builder_suppress(NameEntryP, GenericP);
extern BoolT			name_entry_resolve_undefined(NameEntryP, struct NameTableT *, struct UnitTableT *,
													 struct ShapeTableT *, NStringP);
extern void			name_entry_hide_defd(NameEntryP, GenericP);
extern void			name_entry_keep(NameEntryP, GenericP);
extern void			name_entry_suppress_mult(NameEntryP, GenericP);
extern void			name_entry_lib_suppress_mult(NameEntryP, GenericP);
extern void			name_entry_show_content(NameEntryP, GenericP);

#endif /* !defined (H_NAME_ENTRY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
 **/
