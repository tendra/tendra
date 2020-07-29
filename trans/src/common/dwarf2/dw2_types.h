/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dw2_type_key
#define dw2_type_key 1

extern void dw2_set_diagtags(void);
extern ext_lab dw2_find_type_label(dg_type t);
extern void dw2_out_all_types(void);
extern void dw_out_type(dg_type t);
extern void dw_out_dim(dg_dim d);

#endif
