/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
			    VERSION INFORMATION
			    ===================
--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/codex.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: codex.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:10  ma
Replaced use_alloca with has_alloca.
Revision 1.1.1.1  1997/10/13 12:42:49  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:11  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:25  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:53  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:10  john
 *
 * Revision 1.2  94/02/21  15:57:12  15:57:12  ra (Robert Andrews)
 * Declare functions with no arguments using ( void ).
 *
 * Revision 1.1  93/02/22  17:15:26  17:15:26  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef CODEX_INCLUDED
#define CODEX_INCLUDED

#include "config.h"

#include "installtypes.h"

extern int ins(long, int, int, int);
extern int insf(long, int, int, int);
extern void libcall(char *);
extern bool reserved(char *);

extern bitpattern regsinuse;
extern bitpattern regsinproc;
extern bitpattern reuseables;
extern bitpattern regsindec;
extern bitpattern bigregs;
extern long crt_ret_lab;

extern bool used_stack;
extern bool used_ldisp;
extern long max_stack;
extern long extra_stack;
extern long stack_dec;
extern long stack_size;
extern long ldisp;
extern int no_calls;

extern long stack_change;
extern int stack_direction;
extern void add_to_reg(int, long);
extern void dec_stack(long);
extern void update_stack(void);

extern void area(int);
#define  ptext		0
#define  pdata		1
#define  pbss		2
#define  plast		3

extern void profile_hack(void);
extern void cproc(exp, char *, long, int, int, diag_global *);

#endif
