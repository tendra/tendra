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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: installglob.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/08/23  13:24:24  pwe
 * no invert order, and NEWDIAGS inlining
 *
 * Revision 1.3  1996/10/29  10:10:50  currie
 * 512 bit alignment for hppa
 *
 * Revision 1.2  1995/09/19  16:06:49  currie
 * isAlpha!!
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/



#include "config.h"
#include "common_types.h"

#include "installglob.h"

/* All variables initialised */

exp crt_repeat;
exp repeat_list;
exp global_case;
dec * top_def;
dec ** deflist_end = &top_def;
aldef * top_aldef;	/* init in start_make_capsule */

int has_alloca;
int has_lv;
int proc_is_recursive;
int uses_crt_env;
int must_use_bp;
int has_setjmp;
int uses_loc_address;
int proc_struct_res;
int proc_label_count;
float default_freq;
int proc_externs;
int flpt_always_comparable = 1;
int report_versions = 0;
int do_unroll = 1;

int indirect_jumps = 1;

exp proc_struct_result;

version global_version;

char * dynamic_init_proc = (char*)0;

proc_props * old_proc_props = (proc_props *)0;
		/* initial value for pushing */
int in_proc_def = 0;
		/* initial value for pushing */

int flpt_const_overflow_fail = 1;
		/* flag can be cleared */

aldef const_aldefs[6];
int doing_aldefs; /* cleared in start_make_capsule */

alignment const_al1 = &const_aldefs[0];
alignment const_al8 = &const_aldefs[1];
alignment const_al16 = &const_aldefs[2];
alignment const_al32 = &const_aldefs[3];
alignment const_al64 = &const_aldefs[4];
alignment const_al512 = &const_aldefs[5];

int ptr_null = 0;
int proc_null = 0;
int lv_null = 0;

int no_bss = 0;



