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
$Log: dwarf_gbl.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/08/14  14:30:20  pwe
 * transferred from DJCH
 *
**********************************************************************/

/* 14/2/94 djch new_dwarf_global was declared as diag_global *, but should
   be dwarf_global *. Note that diag_global is typedefed to be
   dwarf_global in diag_config.h */

				/* this is on its own to break cycles */
extern void out_dwarf_global_list(void);
extern void out_dwarf_diag_tags(void);
extern dwarf_global *new_dwarf_global(diag_descriptor *d);
extern void dwarf_inspect_filename(filename f);
