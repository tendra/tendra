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


/*** name-entry.h --- Name table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "name-entry.c" for more information.
 *
 *** Change Log:
 * $Log: name-entry.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:19  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:46:37  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:35  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

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

extern NameEntryP		name_entry_create_direct
	PROTO_S ((NameKeyP, struct ShapeEntryT *));
extern NameEntryP		name_entry_create_indirect
	PROTO_S ((NameKeyP, NameEntryP));
extern NameEntryP		name_entry_create_place
	PROTO_S ((NameKeyP));
extern void			name_entry_make_direct
	PROTO_S ((NameEntryP, struct ShapeEntryT *));
extern void			name_entry_make_indirect
	PROTO_S ((NameEntryP, NameEntryP));
extern NameEntryP		name_entry_resolve_renames
	PROTO_S ((NameEntryP, NStringP, BoolT));
extern NameKeyP			name_entry_key
	PROTO_S ((NameEntryP));
extern NameEntryP		name_entry_next
	PROTO_S ((NameEntryP));
extern NameEntryP	       *name_entry_next_ref
	PROTO_S ((NameEntryP));
extern BoolT			name_entry_is_direct
	PROTO_S ((NameEntryP));
extern BoolT			name_entry_is_indirect
	PROTO_S ((NameEntryP));
extern BoolT			name_entry_is_place
	PROTO_S ((NameEntryP));
extern unsigned			name_entry_id
	PROTO_S ((NameEntryP));
extern void			name_entry_merge_use
	PROTO_S ((NameEntryP, unsigned));
extern unsigned			name_entry_get_use
	PROTO_S ((NameEntryP));
extern void			name_entry_hide
	PROTO_S ((NameEntryP));
extern void			name_entry_unhide
	PROTO_S ((NameEntryP));
extern BoolT			name_entry_is_hidden
	PROTO_S ((NameEntryP));
extern void			name_entry_set_definition
	PROTO_S ((NameEntryP, struct CapsuleT *));
extern struct CapsuleT	       *name_entry_get_definition
	PROTO_S ((NameEntryP));
extern void			name_entry_set_lib_definition
	PROTO_S ((NameEntryP, struct LibCapsuleT *));
extern struct LibCapsuleT      *name_entry_get_lib_definition
	PROTO_S ((NameEntryP));
extern NameEntryP		name_entry_list_next
	PROTO_S ((NameEntryP));
extern NameEntryP	       *name_entry_list_next_ref
	PROTO_S ((NameEntryP));
extern NameEntryP		name_entry_get_indirect
	PROTO_S ((NameEntryP));
extern NameEntryP		name_entry_deallocate
	PROTO_S ((NameEntryP));

extern void			name_entry_do_count
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_write_name
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_compute_tld_size
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_write_tld
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_check_multi_defs
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_do_lib_count
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_do_lib_write
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_suppress
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_builder_suppress
	PROTO_S ((NameEntryP, GenericP));
extern BoolT			name_entry_resolve_undefined
	PROTO_S ((NameEntryP, struct NameTableT *, struct UnitTableT *,
	       struct ShapeTableT *, NStringP));
extern void			name_entry_hide_defd
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_keep
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_suppress_mult
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_lib_suppress_mult
	PROTO_S ((NameEntryP, GenericP));
extern void			name_entry_show_content
	PROTO_S ((NameEntryP, GenericP));

#endif /* !defined (H_NAME_ENTRY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
