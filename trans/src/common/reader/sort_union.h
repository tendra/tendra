/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SORT_UNION_H
#define SORT_UNION_H

#include <reader/codetypes.h>
#include <construct/installtypes.h>

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#include <newdiag/dg_types.h>
#else
#include <diag/dg_first.h>
#include <diag/dg_types.h>
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
	diag_type		tk_diag_type;	/* OLD DIAGS */
	filename		tk_filename;	/* OLD DIAGS */
	access			tk_access;
	procprops		tk_procprops;
	string			tk_string;
	dg			tk_dg;		/* NEW DIAGS */
	dg_dim			tk_dg_dim;	/* NEW DIAGS */
	dg_filename		tk_dg_filename;	/* NEW DIAGS */
	dg_idname		tk_dg_idname;	/* NEW DIAGS */
	dg_name			tk_dg_name;	/* NEW DIAGS */
	dg_type			tk_dg_type;	/* NEW DIAGS */
};

#endif /* SORT_UNION_H */
