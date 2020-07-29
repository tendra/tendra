/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dg_fns_key
#define dg_fns_key 1

extern int unit_no_of_dgtags;
extern dgtag_struct **unit_ind_dgtags;
extern dgtag_struct *unit_dgtagtab;

extern void init_capsule_dgtags(void);
extern void init_unit_dgtags(int n);
extern void start_make_dg_comp_unit(int toks, int tags, int als, int dgnames);
extern void f_make_dg_comp_unit(void);
extern void f_make_dglink(tdfint i, tdfint ext);
extern linkextern f_make_dgtagextern(tdfint internal, external ext);

extern exp f_dg_exp(exp body, dg diagnostic);
extern exp read_dg_exp(exp body);


#endif
