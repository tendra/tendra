/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

extern void out_dwarf_member_loc_attr(exp e);
extern void out_dwarf_bit_member_loc_attr(int u);
extern int  out_dwarf_loc_attr(exp t, int proc_no);
extern void out_dwarf_const4(exp x);
extern void out_dwarf_const_by8(exp x);
