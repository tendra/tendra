/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:49:04 $
$Revision: 1.2 $
$Log: proc.h,v $
 * Revision 1.2  1998/02/04  15:49:04  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:03:34  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef PROCDECS_H
#define PROCDECS_H


#include "config.h"

#include "installtypes.h"
#include "addresstypes.h"
#include "procrectypes.h"
#include "exptypes.h"



/*
 * The following is the global state for compiling a procedure.
 * It needs to be saved and restored if nested procedures allowed.
 */
extern bool last_caller_param(exp);
extern baseoff mem_temp(int);

extern void make_proc_tag_code(exp, space);
extern makeans make_ident_tag_code(exp, space, where, int);
extern void make_res_tag_code(exp, space);
extern makeans make_apply_tag_code(exp, space, where, int);
extern makeans make_apply_general_tag_code(exp,space,where,int);
extern void make_callee_list_tag_code(exp,space);
extern void make_dynamic_callee_tag_code(exp,space);
extern void make_tail_call_tag_code(exp,space);
extern void make_untidy_return_tag_code(exp,space);
extern void make_same_callees_tag_code(exp,space);
extern void make_return_to_label_tag_code(exp,space);
extern void byte_memory_copy(int,int);
extern void word_memory_copy(int,int);
extern long aritherr_lab;
extern long stackerr_lab;

#endif
