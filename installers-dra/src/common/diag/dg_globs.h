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
$Log: dg_globs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/12/04  19:36:31  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.2  1997/10/23  09:21:09  pwe
 * ANDF-DE V1.7 and extra diags
 *
 * Revision 1.1  1997/08/23  13:26:53  pwe
 * initial ANDF-DE
 *
***********************************************************************/

#ifndef dg_glob_key
#define dg_glob_key

#include "config.h"

#include "dg_first.h"

#include "diaginfo.h"
#include "exptypes.h"
#include "installtypes.h"
#include "dg_types.h"		/* NEW DIAGS */
#include "diag_config.h"

extern dg_filename all_files;
extern dg_compilation all_comp_units;
extern int doing_inlining;
extern dg_info current_dg_info;
extern exp current_dg_exp;
extern short_sourcepos no_short_sourcepos;

#endif
