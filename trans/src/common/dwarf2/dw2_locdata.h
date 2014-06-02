/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dw2_loc_key
#define dw2_loc_key

#include <reader/exptypes.h>

typedef struct obl {
	dg_name		obj;
	int		islist;
	struct obl	*next;
} obj_list;

extern obj_list *local_objects;

extern void set_locdata(obj_list this_obl);
extern void close_locdata(obj_list this_obl);
extern void set_optim_objects(dg_info optim, int start);
extern void set_remval_object(dg_info rmv);
extern void set_obj_rets(retrec *rec);
extern int decide_ll_type(exp x);
extern void out_obj_loclist(long l1, long l2, exp x);
extern void out_obj_extloclist(long l1, long l2, exp x);
extern void out_obj_shared_set(dg_name dn);

extern void *dw_new_regshare(dg_name nm, int reg);
extern void dw_add_regshare(void *w, dg_name nm, long start, long end);
extern dg_name find_equiv_object(exp e, int isc);

extern void init_dw_locdata(void);
extern void complete_dw_locdata(void);


#endif
