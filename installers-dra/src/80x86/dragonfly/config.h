/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* dragonfly/config.h */

#ifndef config_key
#define config_key 1

#define DWARF 0
#define use_long_double 1


/* Parameters for foralls optimisations */

#define remove_unused_counters 0
#define remove_unused_index_counters 0
#define good_index_factor(f) 0
#define good_pointer_factor(f) ((f) != 1 && (f) != 2 && (f) != 4 && (f) != 8)

#endif
