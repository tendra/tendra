/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef XDB_OUTPUT_INCLUDED
#define XDB_OUTPUT_INCLUDED

#include <stdio.h>

#include "config.h"

#include "exptypes.h"
#include <construct/installtypes.h>


/*
    TYPE REPRENTING DIAGNOSTIC DIRECTIVES
*/

typedef struct {
    int instr;
    long old_size;
    long new_size;
} diag_directive;

extern diag_directive dd[];


/*
    INDEX TO ARRAY OF DIAGNOSTIC DIRECTIVES

    These macros correspond to the entries in the table above.
*/

#define  xdb_array		0
#define  xdb_begin		1
#define  xdb_const		2
#define  xdb_dvar		3
#define  xdb_end		4
#define  xdb_entry		5
#define  xdb_enum		6
#define  xdb_field		7
#define  xdb_file		8
#define  xdb_fparam		9
#define  xdb_function		10
#define  xdb_functype		11
#define  xdb_import		12
#define  xdb_label		13
#define  xdb_memenum		14
#define  xdb_module		15
#define  xdb_pointer		16
#define  xdb_set		17
#define  xdb_srcfile		18
#define  xdb_struct		19
#define  xdb_subrange		20
#define  xdb_svar		21
#define  xdb_tagdef		22
#define  xdb_typedef		23
#define  xdb_union		24
#define  xdb_variant		25


extern long crt_diag_proc_lab;

extern void init_diag(void);
extern void copy_diag(void);
extern void slt_exit(void);
extern void dnt_begin(void);
extern int dnt_end(void);
extern void diag_string(FILE *, char *);
extern void diag_source(char *, long, int);
extern void diag_source_file(char *, long);
extern void diag_globl_variable(diag_type, char *, int, char *, int);
extern void diag_local_variable(diag_type, char *, long);
extern void diag_type_defn(char *, diag_type);
extern void diag_proc_main(diag_type, exp, char *, int, char *);

#endif
