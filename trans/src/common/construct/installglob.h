/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef installglob_key
#define installglob_key 1

#include <reader/exptypes.h>

#include <reader/toktypes.h>

extern exp crt_repeat;
extern exp repeat_list;
extern exp global_case;
extern dec *top_def;
extern dec **deflist_end;
extern aldef *top_aldef;

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

/*
 * Prints on stderr the versions of all the capsules
 * from which this capsule was made.
 */
extern int report_versions;

extern exp proc_struct_result;
extern char *dynamic_init_proc;
extern proc_props *old_proc_props;

extern version global_version;

extern int in_proc_def;

extern aldef const_aldefs[6];
extern int doing_aldefs;
extern alignment const_al1;
extern alignment const_al8;
extern alignment const_al16;
extern alignment const_al32;
extern alignment const_al64;
extern alignment const_al512;

extern int value_of_null;
extern int ptr_null;
extern int proc_null;
extern int lv_null;

extern int no_bss;

#define MAJOR_VERSION 4
#define MINOR_VERSION 1

#endif
