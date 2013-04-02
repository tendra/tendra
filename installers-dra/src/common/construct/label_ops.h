/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef label_ops_key
#define label_ops_key 1

#include "exptypes.h"

extern int label_is_next(exp lab, exp e);
extern exp short_next_jump(exp e);
extern exp jump_dest(exp lab);
extern exp final_dest(exp lab);
extern exp final_dest_test(exp lab, exp e);

#endif
