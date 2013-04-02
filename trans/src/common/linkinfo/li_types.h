/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef li_types_key
#define li_types_key 1

typedef int linkinfo;
typedef int linkinfo_list;

typedef struct weak_cell_t {
	char *weak_id;
	char *val_id;
	struct weak_cell_t *next;
} weak_cell;

#endif
