/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dw2_iface_key
#define dw2_iface_key 1

extern long dw_info_start;
extern long dw_text_start;

extern void dw_out_path(dg_filename f, int w);
extern void init_dwarf2(void);
extern void dwarf2_prelude(void);
extern void dwarf2_postlude(void);
extern void end_dwarf2(void);

#endif
