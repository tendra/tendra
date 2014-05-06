/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef diag_fns_key
#define diag_fns_key 1

#include <local/exptypes.h>

#include "dg_first.h"
#include "diaginfo.h"

#include <reader/toktypes.h>


extern void out_diagnose_prelude(void);
extern void out_diagnose_postlude(void);

extern void start_make_diagdef_unit(int toks, int tags, int als, int ndiags);
extern void f_make_diagdef_unit(void);


extern void init_capsule_diagtags(void);
extern void start_make_diagtype_unit(int toks, int tags, int als,
				     int ndiagtype);
extern linkextern f_make_diagtagextern(tdfint i, external e);
extern void init_unit_diagtags(int n);


extern diag_info *read_exp_to_source(void);
extern diag_info *read_diag_id_scope(void);
extern diag_info *read_diag_type_scope(void);
extern diag_info *read_diag_tag_scope(void);


extern void output_diag(diag_info *d, int proc_no, exp e);
extern void output_end_scope(diag_info *d, exp e);

extern void diag_proc_begin(diag_global *d, int global, int cname, char *pname);
extern void diag_proc_end(diag_global *d);

extern void diag_val_begin(diag_global *d, int global, int cname, char *pname);
extern void diag_val_end(diag_global *d);


extern int unit_no_of_diagtags;
extern diag_tagdef **unit_ind_diagtags;

extern void f_make_diagtaglink(tdfint i, tdfint ext);

#endif
