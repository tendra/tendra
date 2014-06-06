/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef diag_fns_key
#define diag_fns_key 1

#include <reader/exp.h>

#include "dg_first.h"

#include <reader/token.h>


extern void out_diagnose_prelude(void);
extern void out_diagnose_postlude(void);

extern void start_make_diagdef_unit(int toks, int tags, int als, int ndiags);
extern void f_make_diagdef_unit(void);

extern void init_capsule_diagtags(void);
extern void start_make_diagtype_unit(int toks, int tags, int als,
				     int ndiagtype);
extern linkextern f_make_diagtagextern(tdfint i, external e);
extern void init_unit_diagtags(int n);

extern exp read_exp_to_source(exp body);
extern exp read_diag_id_scope(exp body);
extern exp read_diag_type_scope(exp body);

extern int unit_no_of_diagtags;
extern diag_tagdef **unit_ind_diagtags;

extern void f_make_diagtaglink(tdfint i, tdfint ext);

#ifdef NEWDIAGS
extern exp diag_locate(exp e);
#endif

#endif
