/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * shape-entry.h - Shape table entry ADT.
 *
 * See the file "shape-entry.c" for more information.
 */

#ifndef H_SHAPE_ENTRY
#define H_SHAPE_ENTRY

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "map-table.h"
#include "name-entry.h"
#include "name-table.h"
#include "tdf-write.h"

struct ShapeTableT;
struct UnitTableT;

typedef struct ShapeEntryT {
    struct ShapeEntryT  *next;
    NStringT            key;      /* shape name */
    NameTableT *        names;    /* external names for the shape. */
    unsigned            id_count; /* next available capsule scope
                                     identifier for the shape. */

   /* `non_empty' is set to true during the capsule output routines if
      the shape is to be output (if it has either unit scope
      identifiers or capsule scope identifiers). */
    bool                non_empty; 

    /* `num_lib_names' is used to cache the number of identifiers of
       the shape that are going to be written out to the library
       index. */
    unsigned            num_lib_names;

    /* `head' and `tail' store a list of name entries as they are
       added to the name table "names".  As new names are added to the
       the name table, they are also added to this list.  When trying
       to resolve undefined external names, the names are removed from
       the front of this list, and definitions are looked up in the
       libraries.  When all such lists are empty, then all possible
       name resolution has been done. */  
    NameEntryT *        head;
    NameEntryT *        *tail;
} ShapeEntryT;

typedef struct ShapeClosureT {
    MapTableT *		table;
    TDFWriterT *		writer;
} ShapeClosureT;

typedef struct ShapeLibClosureT {
    bool			did_define;
    struct ShapeTableT	       *lib_shapes;
    struct UnitTableT	       *units;
    struct ShapeTableT	       *shapes;
    bool			missing_definitions;
} ShapeLibClosureT;

extern ShapeEntryT *	shape_entry_create
(NStringT *);
extern ShapeEntryT *	shape_entry_next
(ShapeEntryT *);
extern ShapeEntryT *       *shape_entry_next_ref
(ShapeEntryT *);
extern NStringT *		shape_entry_key
(ShapeEntryT *);
extern NameTableT *	shape_entry_name_table
(ShapeEntryT *);
extern unsigned			shape_entry_next_id
(ShapeEntryT *);
extern void			shape_entry_set_non_empty
(ShapeEntryT *);
extern bool			shape_entry_get_non_empty
(ShapeEntryT *);
extern void			shape_entry_add_to_list
(ShapeEntryT *, NameEntryT *);
extern NameEntryT *	shape_entry_get_from_list
(ShapeEntryT *);
extern ShapeEntryT *	shape_entry_deallocate
(ShapeEntryT *);

extern void			shape_entry_do_count
(ShapeEntryT *, void *);
extern void			shape_entry_write_shape
(ShapeEntryT *, void *);
extern void			shape_entry_write_externs
(ShapeEntryT *, void *);
extern void			shape_entry_compute_tld_size
(ShapeEntryT *, void *);
extern void			shape_entry_write_tld
(ShapeEntryT *, void *);
extern void			shape_entry_write_count
(ShapeEntryT *, void *);
extern void			shape_entry_write_links
(ShapeEntryT *, void *);
extern void			shape_entry_check_multi_defs
(ShapeEntryT *, void *);
extern void			shape_entry_do_lib_count
(ShapeEntryT *, void *);
extern void			shape_entry_do_lib_write
(ShapeEntryT *, void *);
extern void			shape_entry_resolve_undefined
(ShapeEntryT *, void *);
extern void			shape_entry_hide_all_defd
(ShapeEntryT *, void *);
extern void			shape_entry_suppress_mult
(ShapeEntryT *, void *);
extern void			shape_entry_lib_suppress_mult
(ShapeEntryT *, void *);
extern void			shape_entry_show_content
(ShapeEntryT *, void *);

#endif /* !defined (H_SHAPE_ENTRY) */
