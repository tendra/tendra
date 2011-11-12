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
$Log: flags.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/10/23  09:24:21  pwe
 * extra diags
 *
 * Revision 1.3  1997/10/10  18:15:28  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.2  1997/02/18  12:56:24  currie
 * NEW DIAG STRUCTURE
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef flags_key
#define flags_key

extern int do_inlining;
extern int do_special_fns;
extern int do_loopconsts;
extern int do_foralls;
extern int redo_structfns;
extern int redo_structparams;
extern int diagnose;
extern int do_profile;
extern int do_alloca;
extern int double_align;
extern int stack_align;
extern int param_align;
extern int extra_checks;
extern int separate_units;
extern int writable_strings;
extern int PIC_code;
extern int all_variables_visible;
extern int round_after_flop;
extern int strict_fl_div;
extern int do_prom;

#ifdef NEWDIAGS
extern int diag_visible;
extern int extra_diags;
#endif

#endif /* flags_key */
