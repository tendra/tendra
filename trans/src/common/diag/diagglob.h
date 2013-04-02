/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef diagglob_key
#define diagglob_key

#ifndef EXTERN_DIAG
#define EXTERN_DIAG extern
#endif

EXTERN_DIAG diag_descriptor_list  unit_diagvar_tab;

EXTERN_DIAG int 	unit_no_of_diagtags;

EXTERN_DIAG diag_tagdef **unit_ind_diagtags;
EXTERN_DIAG diag_tagdef *unit_diag_tagdeftab;
#endif
