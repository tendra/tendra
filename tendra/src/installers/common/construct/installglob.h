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
$Log: installglob.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1997/08/23  13:24:27  pwe
 * no invert order, and NEWDIAGS inlining
 *
 * Revision 1.4  1996/10/29  10:10:51  currie
 * 512 bit alignment for hppa
 *
 * Revision 1.3  1995/09/19  16:06:51  currie
 * isAlpha!!
 *
 * Revision 1.2  1995/07/06  09:14:01  currie
 * rem & VERSION
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef installglob_key
#define installglob_key 1



extern exp crt_repeat;
extern exp repeat_list;
extern exp global_case;
extern dec * top_def;
extern dec ** deflist_end;
extern aldef * top_aldef;

extern int has_alloca;
extern int has_lv;
extern int proc_is_recursive;
extern int uses_crt_env;
extern int must_use_bp;
extern int has_setjmp;
extern int uses_loc_address;
extern int proc_struct_res;
extern int proc_label_count;
extern float default_freq;
extern int proc_externs;
extern int flpt_always_comparable;
extern int report_versions;
extern int indirect_jumps;
extern int do_unroll;

extern exp proc_struct_result;
extern char * dynamic_init_proc;
extern proc_props * old_proc_props;

extern version global_version;

extern int in_proc_def;
extern int flpt_const_overflow_fail;

extern aldef const_aldefs[6];
extern int doing_aldefs;
extern alignment const_al1;
extern alignment const_al8;
extern alignment const_al16;
extern alignment const_al32;
extern alignment const_al64;
extern alignment const_al512;

extern int ptr_null;
extern int proc_null;
extern int lv_null;

extern int no_bss;

#define MAJOR_VERSION 4
#define MINOR_VERSION 1

#endif
