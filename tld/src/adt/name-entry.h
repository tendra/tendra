/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * name-entry.h - Name table entry ADT.
 *
 * See the file "name-entry.c" for more information.
 */

#ifndef H_NAME_ENTRY
#define H_NAME_ENTRY

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include "name-key.h"

struct ShapeTableT;
struct ShapeEntryT;
struct CapsuleT;
struct LibCapsuleT;
struct NameTableT;
struct UnitTableT;

typedef enum {
    NT_INDIRECT,
    NT_INDIRECT_CYCLING,
    NT_INDIRECT_DONE,
    NT_DIRECT,
    NT_PLACEHOLDER
} NameEntryTypeT;

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
} NameEntryT;

extern NameEntryT *	name_entry_create_direct
(NameKeyT *, struct ShapeEntryT *);
extern NameEntryT *	name_entry_create_indirect
(NameKeyT *, NameEntryT *);
extern NameEntryT *	name_entry_create_place
(NameKeyT *);
extern void			name_entry_make_direct
(NameEntryT *, struct ShapeEntryT *);
extern void			name_entry_make_indirect
(NameEntryT *, NameEntryT *);
extern NameEntryT *	name_entry_resolve_renames
(NameEntryT *, NStringT *, bool);
extern NameKeyT *		name_entry_key
(NameEntryT *);
extern NameEntryT *	name_entry_next
(NameEntryT *);
extern NameEntryT *       *name_entry_next_ref
(NameEntryT *);
extern bool			name_entry_is_direct
(NameEntryT *);
extern bool			name_entry_is_indirect
(NameEntryT *);
extern bool			name_entry_is_place
(NameEntryT *);
extern unsigned			name_entry_id
(NameEntryT *);
extern void			name_entry_merge_use
(NameEntryT *, unsigned);
extern unsigned			name_entry_get_use
(NameEntryT *);
extern void			name_entry_hide
(NameEntryT *);
extern void			name_entry_unhide
(NameEntryT *);
extern bool			name_entry_is_hidden
(NameEntryT *);
extern void			name_entry_set_definition
(NameEntryT *, struct CapsuleT *);
extern struct CapsuleT	       *name_entry_get_definition
(NameEntryT *);
extern void			name_entry_set_lib_definition
(NameEntryT *, struct LibCapsuleT *);
extern struct LibCapsuleT      *name_entry_get_lib_definition
(NameEntryT *);
extern NameEntryT *	name_entry_list_next
(NameEntryT *);
extern NameEntryT *       *name_entry_list_next_ref
(NameEntryT *);
extern NameEntryT *	name_entry_get_indirect
(NameEntryT *);
extern NameEntryT *	name_entry_deallocate
(NameEntryT *);

extern void			name_entry_do_count
(NameEntryT *, void *);
extern void			name_entry_write_name
(NameEntryT *, void *);
extern void			name_entry_compute_tld_size
(NameEntryT *, void *);
extern void			name_entry_write_tld
(NameEntryT *, void *);
extern void			name_entry_check_multi_defs
(NameEntryT *, void *);
extern void			name_entry_do_lib_count
(NameEntryT *, void *);
extern void			name_entry_do_lib_write
(NameEntryT *, void *);
extern void			name_entry_suppress
(NameEntryT *, void *);
extern void			name_entry_builder_suppress
(NameEntryT *, void *);
extern bool			name_entry_resolve_undefined
	(NameEntryT *, struct NameTableT *, struct UnitTableT *,
	       struct ShapeTableT *, NStringT *, bool);
extern void			name_entry_hide_defd
(NameEntryT *, void *);
extern void			name_entry_keep
(NameEntryT *, void *);
extern void			name_entry_suppress_mult
(NameEntryT *, void *);
extern void			name_entry_lib_suppress_mult
(NameEntryT *, void *);
extern void			name_entry_show_content
(NameEntryT *, void *);

#endif /* !defined (H_NAME_ENTRY) */
