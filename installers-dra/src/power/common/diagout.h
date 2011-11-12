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
$Date: 1998/02/04 15:48:42 $
$Revision: 1.2 $
$Log: diagout.h,v $
 * Revision 1.2  1998/02/04  15:48:42  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:00:15  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef DIAGOUT_H
#define DIAGOUT_H	1

#include "config.h"

#include "installtypes.h"
#include "config.h"
#include "exptypes.h"

extern void init_diag(void);
extern void fixup_name(exp , dec * , dec *);
extern void stab_bs(char *);
extern void stab_es(char *);
extern void stab_global(exp , char *, bool);
extern void stab_proc1(exp , char *, bool);
extern void stab_proc2(exp , char *, bool);
extern void stab_endproc(exp , char *, bool);
extern void stab_local(char *, diag_type , exp , int , int);
extern void output_diag_tags(void);
extern void stab_end_file(void);

#endif				/* DIAGOUT_H */
