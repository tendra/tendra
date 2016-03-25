/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * arg-data.h - Command line argument data ADT.
 *
 * See the file "arg-data.c" for more information.
 */

#ifndef H_ARG_DATA
#define H_ARG_DATA

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/cstring.h>
#include <exds/cstring-list.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "name-key.h"
#include <exds/ostream.h>

typedef struct ShapeControlEntryT {
    struct ShapeControlEntryT  *next;
    NStringT			shape;
    bool			all;
    NameKeyListT		names;
} ShapeControlEntryT;

typedef struct ShapeControlT {
    ShapeControlEntryT *	head;
} ShapeControlT;

typedef struct RenameControlEntryT {
    struct RenameControlEntryT *next;
    NStringT			shape;
    NameKeyPairListT		names;
} RenameControlEntryT;

typedef struct RenameControlT {
    RenameControlEntryT *	head;
} RenameControlT;

typedef struct ArgDataT {
    bool			all_hide_defined;
    bool			suppress_mult;
    ShapeControlT		hides;
    ShapeControlT		keeps;
    ShapeControlT		suppresses;
    RenameControlT		renames;
    bool			extract_all;
    bool			extract_basename;
    bool			extract_match_base;
    bool			content_index;
    bool			content_size;
    bool			content_version;
    bool			missing_definitions;
    OStreamT			debug_file;
    char *			default_output_file;
    char *			output_file;
    unsigned			num_library_files;
    unsigned			num_library_paths;
    union {
	struct {
	    CStringListT	file;
	    CStringListT	path;
	} list;
	struct {
	    const char *       *file;
	    const char *       *path;
	} vector;
    } library;
    char *			unit_file;
    unsigned			num_files;
    char *		       *files;
} ArgDataT;

extern void			shape_control_iter
	(ShapeControlT *, void(*)(NStringT *, bool, NameKeyListT *,
					   void *), void *);
extern void			rename_control_iter
	(RenameControlT *, void(*)(NStringT *, NameKeyPairListT *,
					    void *), void *);

extern void			arg_data_init
(ArgDataT *, char *);
extern void			arg_data_set_all_hide_defd
(ArgDataT *, bool);
extern bool			arg_data_get_all_hide_defd
(ArgDataT *);
extern void			arg_data_set_suppress_mult
(ArgDataT *, bool);
extern bool			arg_data_get_suppress_mult
(ArgDataT *);
extern void			arg_data_add_hide
(ArgDataT *, char *, char *);
extern void			arg_data_add_hide_defined
(ArgDataT *, char *);
extern ShapeControlT *	arg_data_get_hides
(ArgDataT *);
extern void			arg_data_add_keep
(ArgDataT *, char *, char *);
extern void			arg_data_add_keep_all
(ArgDataT *, char *);
extern ShapeControlT *	arg_data_get_keeps
(ArgDataT *);
extern void			arg_data_add_suppress
(ArgDataT *, char *, char *);
extern void			arg_data_add_suppress_all
(ArgDataT *, char *);
extern ShapeControlT *	arg_data_get_suppresses
(ArgDataT *);
extern void			arg_data_add_rename
(ArgDataT *, NStringT *, NameKeyT *, NameKeyT *);
extern void			arg_data_parse_rename
(ArgDataT *, char *, char *, char *);
extern RenameControlT *	arg_data_get_renames
(ArgDataT *);
extern void			arg_data_set_extract_all
(ArgDataT *, bool);
extern bool			arg_data_get_extract_all
(ArgDataT *);
extern void			arg_data_set_extract_basename
(ArgDataT *, bool);
extern bool			arg_data_get_extract_basename
(ArgDataT *);
extern void			arg_data_set_extract_match_base
(ArgDataT *, bool);
extern bool			arg_data_get_extract_match_base
(ArgDataT *);
extern void			arg_data_set_content_index
(ArgDataT *, bool);
extern bool			arg_data_get_content_index
(ArgDataT *);
extern void			arg_data_set_content_size
(ArgDataT *, bool);
extern bool			arg_data_get_content_size
(ArgDataT *);
extern void			arg_data_set_content_version
(ArgDataT *, bool);
extern bool			arg_data_get_content_version
(ArgDataT *);
extern void			arg_data_set_missing_definitions
(ArgDataT *, bool);
extern bool			arg_data_get_missing_definitions
(ArgDataT *);
extern void			arg_data_set_debug_file
(ArgDataT *, char *);
extern OStreamT *		arg_data_get_debug_file
(ArgDataT *);
extern void			arg_data_set_output_file
(ArgDataT *, char *);
extern char *			arg_data_get_output_file
(ArgDataT *);
extern void			arg_data_add_library_file
(ArgDataT *, char *);
extern void			arg_data_add_library_path
(ArgDataT *, char *);
extern void			arg_data_vector_libraries
(ArgDataT *);
extern unsigned			arg_data_num_library_files
(ArgDataT *);
extern unsigned			arg_data_num_library_paths
(ArgDataT *);
extern const char *	       *arg_data_library_files
(ArgDataT *);
extern const char *	       *arg_data_library_paths
(ArgDataT *);
extern void			arg_data_set_unit_file
(ArgDataT *, char *);
extern void			arg_data_set_files
(ArgDataT *, int, char * *);
extern unsigned			arg_data_get_num_files
(ArgDataT *);
extern char *		       *arg_data_get_files
(ArgDataT *);

#endif /* !defined (H_ARG_DATA) */
