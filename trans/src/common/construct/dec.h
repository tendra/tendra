/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONSTRUCT_DEC_H
#define CONSTRUCT_DEC_H

#ifdef TDF_DIAG4
#include <diag4/dg_first.h>
#else
#include <diag3/dg_first.h>
#include <diag3/diaginfo.h>
#endif


 /* structure which describes a declaration */
struct dec_t {
	struct dec_t *def_next;
	/* if this is a global declaration this field holds next global
	   declaration which needs processing. If there is none, it is NULL */
	char *dec_id;
	/* identifier to be used */
	shape dec_shape;
	/* shape of the value */
	exp dec_exp;
	/* definition or NULL */
	int unit_number;
#ifdef TDF_DIAG4
	struct dg_name_t *dg_name;
#else
	diag_descriptor *diag_info;
#endif
	access acc;
	int index;
	/* used in inl_norm to hold procedure index number */
	
#if TRANS_MIPS || TRANS_SPARC || TRANS_POWER || TRANS_ALPHA || TRANS_HPPA
	int sym_number;
#endif

	/* bitfields only after this */
	unsigned int extnamed :1;
	/* external */
	unsigned int dec_var :1;
	/* this is a variable */
	unsigned int dec_outermost :1;
	/* this is global */
	unsigned int have_def :1;
	/* we have a definition */
	unsigned int processed :1;
	/* this exp has been output */
	unsigned int isweak :1;
	/* definition is weak */
	unsigned int is_common :1;
	/* declaration is common */
	unsigned int has_signature : 1;
	/* declaration has signature */
};

typedef struct dec_t dec;


#endif

