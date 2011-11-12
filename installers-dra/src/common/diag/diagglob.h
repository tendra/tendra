/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:46 $
$Revision: 1.1.1.1 $
$Log: diagglob.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1997/08/23  13:27:11  pwe
 * initial ANDF-DE
 *
 * Revision 1.1  1995/04/06  10:42:55  currie
 * Initial revision
 *
***********************************************************************/
#ifndef diagglob_key
#define diagglob_key



#ifndef EXTERN_DIAG
#define EXTERN_DIAG extern
#endif

#ifndef NEWDIAGS
EXTERN_DIAG diag_descriptor_list  unit_diagvar_tab;
#endif

EXTERN_DIAG int 	unit_no_of_diagtags;

EXTERN_DIAG diag_tagdef **unit_ind_diagtags;
EXTERN_DIAG diag_tagdef *unit_diag_tagdeftab;
#endif
