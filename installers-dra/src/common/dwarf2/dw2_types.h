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
$Log: dw2_types.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/12/04  19:41:47  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.3  1997/10/10  18:18:49  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.2  1997/08/23  13:36:59  pwe
 * initial ANDF-DE
 *
 * Revision 1.1  1997/03/20  16:09:33  pwe
 * first version
 *
**********************************************************************/

#ifndef dw2_type_key
#define dw2_type_key 1

extern void dw2_set_diagtags(void);
extern ext_lab dw2_find_type_label(dg_type t);
extern void dw2_out_all_types(void);
extern void dw_out_type(dg_type t);
extern void dw_out_dim(dg_dim d);

#endif
