/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/68k_globals.c,v 1.1.1.1 1998/01/17 15:55:48 release Exp $
--------------------------------------------------------------------------
$Log: 68k_globals.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:03  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:42:46  ma
First version.

Revision 1.1  1997/10/13 09:54:22  ma
First version.


--------------------------------------------------------------------------
*/

#include "config.h"
#include "common_types.h"
#include "68k_globals.h"

int not_in_params = 1;
int not_in_postlude = 1;
int need_preserve_stack = 0;
dec* cur_proc_dec = 0;
int cur_proc_has_tail_call = 0;
int cur_proc_use_same_callees = 0;
int cur_proc_has_vcallees = 0;
long cur_proc_callees_size = 0;
long cur_proc_callers_size = 0;
long cur_proc_env_size = 0;
int apply_tag_flag = 0;
