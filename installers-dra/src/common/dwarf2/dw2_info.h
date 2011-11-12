/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: pwe $
$Date: 1998/03/11 11:03:45 $
$Revision: 1.3 $
$Log: dw2_info.h,v $
 * Revision 1.3  1998/03/11  11:03:45  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/02/18  11:22:22  pwe
 * test corrections
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.9  1997/12/04  19:41:37  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.8  1997/11/06  09:22:18  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.7  1997/10/28  10:14:26  pwe
 * local location corrections
 *
 * Revision 1.6  1997/10/23  09:27:45  pwe
 * ANDF-DE v1.7, extra diags
 *
 * Revision 1.5  1997/10/10  18:18:42  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.4  1997/08/23  13:36:48  pwe
 * initial ANDF-DE
 *
 * Revision 1.3  1997/04/17  11:50:29  pwe
 * Sparc and 80x86 support
 *
 * Revision 1.2  1997/04/01  17:19:43  pwe
 * diagnose pl_tests and locate -> platform specific
 *
 * Revision 1.1  1997/03/20  16:09:21  pwe
 * first version
 *
**********************************************************************/

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
