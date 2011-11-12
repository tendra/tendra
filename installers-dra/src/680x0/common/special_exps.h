/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
			    VERSION INFORMATION
			    ===================
--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/special_exps.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log:
--------------------------------------------------------------------------
*/

#ifndef __SPECIAL_EXPS__
#define __SPECIAL_EXPS__

extern exp make_extn(char* n, shape s, int v);
extern exp get_stack_limit(void);
extern exp get_error_handler(void);
extern exp get_dummy_double_dest(void);
extern exp get_env_size(dec*);

#endif
