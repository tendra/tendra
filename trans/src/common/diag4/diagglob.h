/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef diagglob_key
#define diagglob_key

#include <construct/installtypes.h>

#include "dg_first.h"
#include "dg_types.h"		/* TDF_DIAG4 */

#include <reader/exp.h>

extern int unit_no_of_diagtags;

extern diag_tagdef **unit_ind_diagtags;
extern diag_tagdef *unit_diag_tagdeftab;

extern dg_filename all_files;
extern dg_compilation all_comp_units;
extern int doing_inlining;
extern dg_info current_dg_info;
extern exp current_dg_exp;
extern short_sourcepos no_short_sourcepos;

#endif
