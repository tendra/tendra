/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dw2_info_key
#define dw2_info_key

typedef enum {
	GLOBAL_NAME,
	LOCAL_NAME,
	DEAD_NAME,
	PARAM_NAME,
	INL_PARAM_NAME,
	EXCEPT_NAME,
	MEMBER_NAME
} dg_nm_contex;

extern void dw2_out_name(dg_name di, dg_nm_contex contex);
extern void dw2_out_generic(dg_name_list p);
extern void dw_out_const(exp e);
extern void dw_out_default(dg_default *d);
extern void complete_defaults(void);
extern void dw2_proc_start(exp p, dg_name d);
extern void dw2_return_pos(long over);
extern void dw2_proc_end(exp p);
extern void dw2_code_info(dg_info d, void(*mcode)(void *), void *args);
extern dg_where find_diag_res(void *args);

extern long dw2_scope_start;
extern int dw_doing_branch_tests;

#endif
