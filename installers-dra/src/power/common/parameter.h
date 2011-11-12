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
$Date: 1998/02/04 15:49:03 $
$Revision: 1.2 $
$Log: parameter.h,v $
 * Revision 1.2  1998/02/04  15:49:03  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:03:22  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef PARAMETER_H
#define PARAMETER_H

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"

extern void output_parameters(exp);
extern bool suspected_varargs;
extern int saved_varargs_register;
extern int saved_varargs_offset;
#endif
