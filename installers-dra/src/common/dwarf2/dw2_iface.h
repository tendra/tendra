/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:48 $
$Revision: 1.1.1.1 $
$Log: dw2_iface.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/11/06  09:22:11  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.3  1997/10/10  18:18:35  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.2  1997/08/23  13:36:42  pwe
 * initial ANDF-DE
 *
 * Revision 1.1  1997/03/20  16:09:15  pwe
 * first version
 *
**********************************************************************/

#ifndef dw2_iface_key
#define dw2_iface_key 1

extern int dwarf2;
extern long dw_info_start;
extern long dw_text_start;

extern void dw_out_path(dg_filename f, int w);
extern void init_dwarf2(void);
extern void dwarf2_prelude(void);
extern void dwarf2_postlude(void);
extern void end_dwarf2(void);

#endif
