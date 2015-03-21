/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SORT_UNION_H
#define SORT_UNION_H

#include <tdf/nat.h>

#include <construct/installtypes.h>
#include <construct/aldefs.h>

#ifdef TDF_DIAG4
#include <diag4/dg_first.h>
#include <diag4/dg_types.h>
#else
#include <diag3/dg_first.h>
#include <diag3/dg_types.h>
#endif


/*
 * the union of the representations of all sorts:
 * used in table_fns for token application
 */

union tokval_u {
	alignment		tk_alignment;
	al_tag			tk_al_tag;
	bitfield_variety	tk_bitfield_variety;
	bool			tk_bool;
	error_treatment		tk_error_treatment;
	exp			tk_exp;
	floating_variety	tk_floating_variety;
	label			tk_label;
	nat			tk_nat;
	ntest			tk_ntest;
	rounding_mode		tk_rounding_mode;
	shape			tk_shape;
	signed_nat		tk_signed_nat;
	tag			tk_tag;
	struct tok_define_t	*tk_token;
	transfer_mode		tk_transfer_mode;
	variety			tk_variety;
	diag_type		tk_diag_type;	/* TDF_DIAG3 */
	filename		tk_filename;	/* TDF_DIAG3 */
	access			tk_access;
	procprops		tk_procprops;
	string			tk_string;
	dg			tk_dg;		/* TDF_DIAG4 */
	dg_dim			tk_dg_dim;	/* TDF_DIAG4 */
	dg_filename		tk_dg_filename;	/* TDF_DIAG4 */
	dg_idname		tk_dg_idname;	/* TDF_DIAG4 */
	dg_name			tk_dg_name;	/* TDF_DIAG4 */
	dg_type			tk_dg_type;	/* TDF_DIAG4 */
};

#endif /* SORT_UNION_H */
