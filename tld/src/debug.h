/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * debug.h - Debugging routines.
 *
 * See the file "debug.c" for more information.
 */

#ifndef H_DEBUG
#define H_DEBUG

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/cstring.h>
#include <exds/dstring.h>
#include "adt/name-key.h"
#include <exds/ostream.h>

extern void			debug_set_file
(OStreamT *);

extern void			debug_info_u_name
(NStringT *);

extern void			debug_info_r_start_capsule
(char *);
extern void			debug_info_r_versions
(unsigned, unsigned);
extern void			debug_info_r_start_unit_decs
(unsigned);
extern void			debug_info_r_unit_dec
(NStringT *);
extern void			debug_info_r_start_shapes
(unsigned);
extern void			debug_info_r_shape
(NStringT *, unsigned);
extern void			debug_info_r_start_names
(unsigned);
extern void			debug_info_r_start_shape_names
(NStringT *, unsigned);
extern void			debug_info_r_name
(NameKeyT *, unsigned, unsigned, NameKeyT *);
extern void			debug_info_r_start_unit_sets
(unsigned);
extern void			debug_info_r_start_units
(NStringT *, unsigned);
extern void			debug_info_r_start_unit
(NStringT *, unsigned, unsigned);
extern void			debug_info_r_start_counts
(unsigned);
extern void			debug_info_r_count
(unsigned, NStringT *);
extern void			debug_info_r_start_maps
(unsigned);
extern void			debug_info_r_start_shape_maps
(NStringT *, unsigned);
extern void			debug_info_r_map
(unsigned, unsigned, unsigned);
extern void			debug_info_r_unit_body
(size_t);
extern void			debug_info_r_tld_version
(unsigned);
extern void			debug_info_r_start_usages
(NStringT *, unsigned);
extern void			debug_info_r_usage
(unsigned, unsigned, NameKeyT *);
extern void			debug_info_r_end_capsule
(void);
extern void			debug_info_r_abort_capsule
(void);

extern void			debug_info_w_start_capsule
(char *);
extern void			debug_info_w_versions
(unsigned, unsigned);
extern void			debug_info_w_start_unit_decs
(unsigned);
extern void			debug_info_w_unit_dec
(NStringT *);
extern void			debug_info_w_start_shapes
(unsigned);
extern void			debug_info_w_shape
(NStringT *, unsigned);
extern void			debug_info_w_start_names
(unsigned);
extern void			debug_info_w_start_shape_names
(NStringT *, unsigned);
extern void			debug_info_w_name
(NameKeyT *, unsigned);
extern void			debug_info_w_start_unit_sets
(unsigned);
extern void			debug_info_w_start_units
(NStringT *, unsigned);
extern void			debug_info_w_start_unit
(NStringT *, unsigned, unsigned);
extern void			debug_info_w_start_counts
(unsigned);
extern void			debug_info_w_count
(unsigned, NStringT *);
extern void			debug_info_w_start_maps
(unsigned);
extern void			debug_info_w_start_shape_maps
(NStringT *, unsigned);
extern void			debug_info_w_map
(unsigned, unsigned);
extern void			debug_info_w_unit_body
(size_t);
extern void			debug_info_w_tld_version
(unsigned);
extern void			debug_info_w_start_usages
(NStringT *);
extern void			debug_info_w_usage
(unsigned, NameKeyT *);
extern void			debug_info_w_end_capsule
(void);

extern void			debug_info_r_start_library
(const char *);
extern void			debug_info_r_lib_versions
(unsigned, unsigned);
extern void			debug_info_r_library_version
(unsigned);
extern void			debug_info_r_start_capsules
(unsigned);
extern void			debug_info_r_capsule
(NStringT *, size_t);
extern void			debug_info_r_start_index
(unsigned);
extern void			debug_info_r_start_shape_index
(NStringT *, unsigned);
extern void			debug_info_r_index_entry
(NameKeyT *, unsigned, unsigned, NameKeyT *, char *);
extern void			debug_info_r_end_library
(void);
extern void			debug_info_r_abort_library
(void);

extern void			debug_info_w_start_library
(const char *);
extern void			debug_info_w_lib_versions
(unsigned, unsigned);
extern void			debug_info_w_library_version
(unsigned);
extern void			debug_info_w_start_capsules
(unsigned);
extern void			debug_info_w_capsule
(char *, size_t);
extern void			debug_info_w_start_index
(unsigned);
extern void			debug_info_w_start_shape_index
(NStringT *, unsigned);
extern void			debug_info_w_index_entry
(NameKeyT *, unsigned, char *, unsigned);
extern void			debug_info_w_end_library
(void);

extern void			debug_info_l_not_needed
(NameKeyT *, NStringT *, unsigned);
extern void			debug_info_l_not_found
(NameKeyT *, NStringT *, unsigned);
extern void			debug_info_l_found
(NameKeyT *, NStringT *, unsigned, char *);
extern void			debug_info_l_hide
(NStringT *, NameKeyT *);
extern void			debug_info_l_keep
(NStringT *, NameKeyT *);
extern void			debug_info_l_suppress
(NStringT *, NameKeyT *);
extern void			debug_info_l_rename
(NStringT *, NameKeyT *, NameKeyT *);

#endif /* !defined (H_DEBUG) */
