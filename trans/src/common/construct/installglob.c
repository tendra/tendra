/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>

#include <construct/installglob.h>

/* All variables initialised */

exp crt_repeat;
exp repeat_list;
exp global_case;
dec *top_def;
dec **deflist_end = &top_def;
aldef *top_aldef;	/* init in start_make_capsule */

/* TODO: share with guts of proc_props perhaps */
bool has_alloca;
bool has_lv;
bool proc_is_recursive;
bool uses_crt_env;
bool must_use_bp;
bool has_setjmp;
bool uses_loc_address;
bool proc_struct_res;
int proc_label_count;
float default_freq;
bool proc_externs;
bool flpt_always_comparable = true;
bool report_versions        = false;

exp proc_struct_result;

version global_version;

char *dynamic_init_proc = NULL;

bool in_proc_def = false;				/* initial value for pushing */

static aldef const_aldefs[6];
bool doing_aldefs;	/* cleared in start_make_capsule */

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

bool no_bss = false;
