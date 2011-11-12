/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: misc_c.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef misc_c_key
#define misc_c_key 1

#include "config.h"
#include "exptypes.h"

extern int invariant_to_apply(exp e);
extern int take_out_of_line(exp first, exp alt, int in_repeat, double scale);
extern int take_out_by_prob(exp first, exp alt);
extern int is_maxop(exp x, exp *t);
extern int is_minop(exp x, exp *t);
extern int is_tester(exp e, int eq);

#if condassign_implemented
extern int is_condassign(exp e, exp *to_test, exp *to_ass);
#endif

#endif
