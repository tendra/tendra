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
$Log: read_sort.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/12/04  19:50:03  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.2  1997/08/23  13:30:52  pwe
 * no invert order, and initial ANDF-DE
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/



/* defines read_sort, which calls the decoder routine for the sort
   given by sn and delivers the result inserted into the union tokval */


#include "config.h"
#include "common_types.h"
#include "readglob.h"
#include "basicread.h"
#include "sortmacs.h"
#include "exp.h"
#include "expmacs.h"
#include "main_reads.h"
#include "externs.h"
#include "messages_r.h"

#include "read_sort.h"

tokval read_sort
    PROTO_N ( (sn) )
    PROTO_T ( int sn )
{
  tokval v;
   switch (sn)
    {
      case ALIGNMENT_SORT:
        v.tk_alignment = d_alignment();
        break;
      case AL_TAG:
        v.tk_al_tag = d_al_tag();
        break;
      case BITFIELD_VARIETY:
        v.tk_bitfield_variety = d_bitfield_variety();
        break;
      case BOOL:
        v.tk_bool = d_bool();
        break;
      case ERROR_TREATMENT:
        v.tk_error_treatment = d_error_treatment();
        break;
      case EXP_S:
        v.tk_exp = d_exp();
        break;
      case FLOATING_VARIETY:
        v.tk_floating_variety = d_floating_variety();
        break;
      case LABEL:
        v.tk_label = d_label();
        break;
      case NAT:
        v.tk_nat = d_nat();
        break;
      case NTEST:
        v.tk_ntest = d_ntest();
        break;
      case ROUNDING_MODE:
        v.tk_rounding_mode = d_rounding_mode();
        break;
      case SHAPE:
        v.tk_shape = d_shape();
        break;
      case SIGNED_NAT:
        v.tk_signed_nat = d_signed_nat();
        break;
      case TAG:
        v.tk_tag = d_tag();
        break;
      case VARIETY:
        v.tk_variety = d_variety();
        break;
      case TOKEN:
        v.tk_token = d_token();
        break;
      case DIAG_TYPE_SORT:	/* OLD DIAGS */
	v.tk_diag_type = d_diag_type();
	break;
      case DIAG_FILENAME:	/* OLD DIAGS */
	v.tk_filename =  d_filename();
	break;
      case ACCESS_SORT:
        v.tk_access =  d_access();
        break;
       case TRANSFER_MODE_SORT:
        v.tk_transfer_mode =  d_transfer_mode();
        break;
       case PROCPROPS:
	v.tk_procprops = d_procprops();
	break;
       case STRING:
	v.tk_string = d_string();
	break;
       case DG_SORT:		/* NEW DIAGS */
	v.tk_dg = d_dg();
	break;
       case DG_DIM_SORT:	/* NEW DIAGS */
	v.tk_dg_dim = d_dg_dim();
	break;
       case DG_FILENAME_SORT:	/* NEW DIAGS */
	v.tk_dg_filename = d_dg_filename();
	break;
       case DG_IDNAME_SORT:	/* NEW DIAGS */
	v.tk_dg_idname = d_dg_idname();
	break;
       case DG_NAME_SORT:	/* NEW DIAGS */
	v.tk_dg_name = d_dg_name();
	break;
       case DG_TYPE_SORT:	/* NEW DIAGS */
	v.tk_dg_type = d_dg_type();
	break;
     default:{SET(v);  failer(SORT_NAME);};
    };
  return v;
}
