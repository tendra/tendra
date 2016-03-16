/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef diagglob_key
#define diagglob_key

extern diag_descriptor_list unit_diagvar_tab;

extern int unit_no_of_diagtags;

extern diag_tagdef **unit_ind_diagtags;
extern diag_tagdef *unit_diag_tagdeftab;

extern dg_filename all_files;
extern dg_compilation all_comp_units;
extern short_sourcepos no_short_sourcepos;

#endif
