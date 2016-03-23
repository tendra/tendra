/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef DIAG4_REFORM_H
#define DIAG4_REFORM_H

#include <diag4/dg_types.h>
#include <diag4/dg_aux.h>

struct diag4_driver {
	void (*out_diagnose_prelude)(void);
	void (*init_stab_aux)(void);
	void (*out_diagnose_postlude)(void);

	void (*stabd)(dg_filename f, long lno, int seg);
	void (*code_diag_info)(dg_info d, void(*mcode)(void *), void *args);
#ifdef TRANS_SPARC
	void (*stab_global)(dg_name di, exp global, char *name, int ext);
	void (*stab_proc)(dg_name di, exp proc, char *name, int ext);
#endif
#ifdef TRANS_X86
	void (*out_diag_global)(dg_name di, int global, int cname, char *pname);
	void (*diag_proc_begin)(dg_name di, int global, int cname, char *pname);
#endif
	void (*stab_proc_end)(void);
	void (*stab_types)(void);
};

extern const struct diag4_driver *diag4_driver;

#endif

