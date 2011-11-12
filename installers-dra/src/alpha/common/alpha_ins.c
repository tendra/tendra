/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef lint
static char vcid[] = "$Id: alpha_ins.c,v 1.1.1.1 1998/01/17 15:55:58 release Exp $";
#endif /* lint */

/*
  alpha_ins.c

  Defines the Alpha instruction set as C strings.
  PAL code is not included (see OSF1/palcode.c).
*/
#define INS_DEFINE
#include "config.h"
#include "alpha_ins.h"
#undef INS_DEFINE
