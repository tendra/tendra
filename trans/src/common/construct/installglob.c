/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <construct/installglob.h>

/* All variables initialised */

exp crt_repeat;
exp repeat_list;
exp global_case;
dec *top_def;
dec **deflist_end = &top_def;
aldef *top_aldef;	/* init in start_make_capsule */

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

exp proc_struct_result;

version global_version;

char *dynamic_init_proc = NULL;

proc_props *old_proc_props = NULL;	/* initial value for pushing */
int in_proc_def = 0;				/* initial value for pushing */

static aldef const_aldefs[6];
int doing_aldefs;	/* cleared in start_make_capsule */

alignment const_al1 = &const_aldefs[0];
alignment const_al8 = &const_aldefs[1];
alignment const_al16 = &const_aldefs[2];
alignment const_al32 = &const_aldefs[3];
alignment const_al64 = &const_aldefs[4];
alignment const_al512 = &const_aldefs[5];

int value_of_null = 0;
int ptr_null = 0;
int proc_null = 0;
int lv_null = 0;

int no_bss = 0;
