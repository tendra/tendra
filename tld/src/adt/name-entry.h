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
	NameKeyT			key; /* name's name */
	NameEntryTypeT		type; /* see comment below this struct */
	union {
		struct {
		  /* This contains the capsule scope identifier that has been allocated
			 for this name.  It is only used if the entry is a direct entry (as
			 is the case for all other "u.direct.X" fields). */
			unsigned		id;

		  /* This contains the name's usage information (as read from
			 the linker information unit).  In addition, an otherwise
			 unused bit is used to indicate that the name is
			 hidden. */
			unsigned		use;

		  /* This contains a pointer to the capsule object that
			 defined the name.  It is used for reporting the original
			 definition for multiply defined names.  It is also used
			 to indicate that the name has a definition (it is set to
			 the nil pointer if the name has no definition, or if the
			 definition has been suppressed).  It is only used for
			 names not in a library index. */
			struct CapsuleT    *definition;

		  /* This contains a pointer to the library capsule object that defined
			 the name.  It is only used for names in a library index, to indicate
			 which capsule should be loaded to define the name.  It is set to
			 the nil pointer if the name has no library definition, or if the
			 definition has been suppressed. */
			struct LibCapsuleT *lib_definition;

		  /* This contains a pointer to the next name in the list of names of
			 this shape (the list that the "head" and "tail" fields in the shape
			 entry structure represent). */
			struct NameEntryT  *list_next;
		} direct;

		/* This contains a pointer to another entry that is to be used
		   in place of this entry.  It is only used if the entry is an
		   indirect entry of some form. */
		struct NameEntryT      *indirect; 
	} u;
} NameEntryT;

/* NameEntryT.type:

   This is the type of the name.  There are five types: "NT_INDIRECT",
   "NT_INDIRECT_CYCLING", "NT_INDIRECT_DONE", "NT_DIRECT" and
   "NT_PLACEHOLDER".  The first three types are all indirect names
   (used by the renaming); the last type is also used by the renaming.
   The direct name type is the real name type.

   When renaming information is read, it is entered into each name
   table of the appropriate shape.  Initially, a place holder name is
   created for the new name, and an indirect name is created for the
   old name.  The indirect name contains a pointer to the place holder
   name (actually, this may also be an indirect name if it has also
   been renamed).

   Once all of the renamed names have been added to the table, the
   renamings are checked for cycles, and the indirect entries are set
   so that they all point to a place holder entry (so that it will not
   be necessary to follow chains of indirect entries).  The other two
   indirect types are used by this process.  After the process has
   completed, all entries in the table will be of type
   "NT_INDIRECT_DONE" or "NT_PLACEHOLDER".  At this stage, there will
   be no direct entries.

   Direct entries are added when capsules and libraries are read.
   Place holder entries will automatically turn into direct entries
   when a direct entry of the same name is added.  Attempts to add an
   entry with the same name as an indirect entry will result in the
   entry it points to being used instead.

   The name table hides all of the renaming: the functions that get
   entries from the name table follow indirect entries, and ignore
   place holder entries; the iteration function only iterates across
   direct entries.  In this way, nothing outside of the name table
   structure needs to worry about renaming.
*/

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
