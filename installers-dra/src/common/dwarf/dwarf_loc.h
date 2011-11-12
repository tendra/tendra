/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: dwarf_loc.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/09/28  12:39:45  pwe
 * dwarf.h via import, and type changes for tcc checks
 *
 * Revision 1.1.1.1  1995/08/14  14:30:22  pwe
 * transferred from DJCH
 *
**********************************************************************/

extern void out_dwarf_member_loc_attr(exp e);
extern void out_dwarf_bit_member_loc_attr(int u);
extern int  out_dwarf_loc_attr(exp t, int proc_no);
extern void out_dwarf_const4(exp x);
extern void out_dwarf_const_by8(exp x);
