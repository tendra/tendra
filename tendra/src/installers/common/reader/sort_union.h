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
$Date: 1998/01/17 15:55:45 $
$Revision: 1.1.1.1 $
$Log: sort_union.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/12/04  19:50:07  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.2  1997/08/23  13:31:02  pwe
 * no invert order, and initial ANDF-DE
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/



/* the union of the representations of all sorts: used in table_fns
   for token application */

union tokval_u
 {
   alignment tk_alignment;
   al_tag tk_al_tag;
   bitfield_variety tk_bitfield_variety;
   bool tk_bool;
   error_treatment tk_error_treatment;
   exp tk_exp;
   floating_variety tk_floating_variety;
   label tk_label;
   nat tk_nat;
   ntest tk_ntest;
   rounding_mode tk_rounding_mode;
   shape tk_shape;
   signed_nat tk_signed_nat;
   tag tk_tag;
   struct tok_define_t  * tk_token;
   transfer_mode tk_transfer_mode;
   variety tk_variety;
   diag_type	tk_diag_type;	/* OLD DIAGS */
   filename 	tk_filename;	/* OLD DIAGS */
   access	tk_access;
   procprops	tk_procprops;
   string 	tk_string;
   dg		tk_dg;		/* NEW DIAGS */
   dg_dim	tk_dg_dim;	/* NEW DIAGS */
   dg_filename	tk_dg_filename;	/* NEW DIAGS */
   dg_idname	tk_dg_idname;	/* NEW DIAGS */
   dg_name	tk_dg_name;	/* NEW DIAGS */
   dg_type	tk_dg_type;	/* NEW DIAGS */
 };
