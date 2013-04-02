/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

				/* this is on its own to break cycles */
extern void out_dwarf_global_list(void);
extern void out_dwarf_diag_tags(void);
extern dwarf_global *new_dwarf_global(diag_descriptor *d);
extern void dwarf_inspect_filename(filename f);
