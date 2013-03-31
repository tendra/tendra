/* $Id$ */

/*
 * Copyright 2011-2013, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef FORALLS_H
#define FORALLS_H

#define remove_unused_counters	1
#define remove_unused_index_counters 0
#define good_index_factor(f) 0
#if 0
#define good_pointer_factor(f) ( (f) != 1 && (f) != 2 && (f) != 4 && (f) != 8 )
#else
#define good_pointer_factor(f) 1
#endif

#endif

