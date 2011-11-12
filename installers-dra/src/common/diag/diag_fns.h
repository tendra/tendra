/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:46 $
$Revision: 1.1.1.1 $
$Log: diag_fns.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1998/01/09  09:30:00  pwe
 * prep restructure
 *
 * Revision 1.6  1997/11/06  09:17:53  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.5  1997/10/23  09:21:19  pwe
 * ANDF-DE V1.7 and extra diags
 *
 * Revision 1.4  1997/08/23  13:27:03  pwe
 * initial ANDF-DE
 *
 * Revision 1.3  1997/03/20  17:04:51  currie
 * Dwarf2 diags
 *
Revision 1.2  1997/02/18 12:55:51  currie
NEW DIAG STRUCTURE

 * Revision 1.1  1995/04/06  10:42:55  currie
 * Initial revision
 *
***********************************************************************/
#ifndef diag_fns_key
#define diag_fns_key 1


#include "config.h"

#include "exptypes.h"
#include "dg_first.h"
#include "diaginfo.h"
#include "toktypes.h"


extern void out_diagnose_prelude(void);
extern void out_diagnose_postlude(void);

extern void start_make_diagdef_unit(int toks, int tags, int als, int ndiags);
extern void f_make_diagdef_unit(void);


extern void init_capsule_diagtags(void);
extern void start_make_diagtype_unit(int toks, int tags, int als,
				     int ndiagtype);
extern linkextern f_make_diagtagextern(tdfint i, external e);
extern void init_unit_diagtags(int n);


#ifdef NEWDIAGS

extern exp read_exp_to_source(exp body);
extern exp read_diag_id_scope(exp body);
extern exp read_diag_type_scope(exp body);
extern exp read_diag_tag_scope(exp body);

#else

extern diag_info *read_exp_to_source(void);
extern diag_info *read_diag_id_scope(void);
extern diag_info *read_diag_type_scope(void);
extern diag_info *read_diag_tag_scope(void);

#endif


#ifndef NEWDIAGS

extern void output_diag(diag_info *d, int proc_no, exp e);
extern void output_end_scope(diag_info *d, exp e);

extern void diag_proc_begin(diag_global *d, int global, int cname, char *pname);
extern void diag_proc_end(diag_global *d);

extern void diag_val_begin(diag_global *d, int global, int cname, char *pname);
extern void diag_val_end(diag_global *d);

#endif


extern int unit_no_of_diagtags;
extern diag_tagdef **unit_ind_diagtags;

extern void f_make_diagtaglink(tdfint i, tdfint ext);

#ifdef NEWDIAGS
extern exp diag_locate(exp e);
#endif

#endif
