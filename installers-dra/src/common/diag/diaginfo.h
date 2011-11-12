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
$Log: diaginfo.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1997/08/23  13:27:14  pwe
 * initial ANDF-DE
 *
 * Revision 1.4  1997/03/20  17:12:33  currie
 * small blunder
 *
Revision 1.3  1997/03/20 17:04:53  currie
Dwarf2 diags

Revision 1.2  1997/02/18 12:55:52  currie
NEW DIAG STRUCTURE

 * Revision 1.1  1995/04/06  10:42:55  currie
 * Initial revision
 *
***********************************************************************/

#ifndef NEWDIAGS

#ifndef diaginfo_key
#define diaginfo_key 1


#include "config.h"

typedef struct diag_info_t diag_info; /* let's break a type cycle */

#include "diagtypes1.h"	/* gets diag_descriptor */

#include "diag_config.h"

#else				/* been included at least once */

#ifdef diagtypes_key

#ifndef diaginfo_done_phase2
#define diaginfo_done_phase2
				/* phase 2  */
typedef enum {
	DIAG_INFO_UNINIT,
	DIAG_INFO_SOURCE,
	DIAG_INFO_ID,
	DIAG_INFO_TYPE,
	DIAG_INFO_TAG
} diag_info_key;

struct diag_info_t {
	diag_info_key key;
	union {
		struct {
			sourcemark beg;
			sourcemark end;
		} source;
		struct {
			tdfstring nme;
			exp access;
			diag_type typ;
		} id_scope;
		struct {
			tdfstring nme;
			diag_type typ;
		} type_scope;
		struct {
			tdfstring nme;
			diag_type typ;
		} tag_scope;
	} data;
};

				/* end phase 2 */
#endif				/* done phase 2 */
#endif				/* diagtypes defined */
#endif

#endif
