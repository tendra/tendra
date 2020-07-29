/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef diag_fns_key
#define diag_fns_key 1

extern void start_make_diagdef_unit(int toks, int tags, int als, int ndiags);
extern void f_make_diagdef_unit(void);

extern void init_capsule_diagtags(void);
extern void start_make_diagtype_unit(int toks, int tags, int als,
				     int ndiagtype);
extern linkextern f_make_diagtagextern(tdfint i, external e);
extern void init_unit_diagtags(int n);

extern int unit_no_of_diagtags;
extern diag_tagdef **unit_ind_diagtags;

extern void f_make_diagtaglink(tdfint i, tdfint ext);

#endif
