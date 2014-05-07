/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "addresstypes.h"
#include "instypes.h"

#include <local/exptypes.h>

extern int  comm_op(exp,space,where,instruction);
extern int  non_comm_op(exp,space,where,instruction);
extern int  monop(exp,space,where,instruction);
extern int  fop(exp,space,where,instruction);
extern int  fmop(exp,space,where,instruction);
extern void tidyshort(int,shape);
