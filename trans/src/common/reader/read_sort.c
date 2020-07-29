/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Defines read_sort, which calls the decoder routine for the sort
 * given by sn and delivers the result inserted into the union tokval
 */

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <tdf/nat.h>
#include <tdf/sort.h>

#include <reader/readglob.h>
#include <reader/basicread.h>
#include <reader/main_reads.h>
#include <reader/externs.h>
#include <reader/read_sort.h>

#include <construct/exp.h>

tokval
read_sort(int sn)
{
	tokval v;

	switch (sn) {
	case SORT_ALIGNMENT:          v.tk_alignment        = d_alignment();        break;
	case SORT_AL_TAG:             v.tk_al_tag           = d_al_tag();           break;
	case SORT_BITFIELD_VARIETY:   v.tk_bitfield_variety = d_bitfield_variety(); break;
	case SORT_BOOL:               v.tk_bool             = d_bool();             break;
	case SORT_ERROR_TREATMENT:    v.tk_error_treatment  = d_error_treatment();  break;
	case SORT_EXP:                v.tk_exp              = d_exp();              break;
	case SORT_FLOATING_VARIETY:   v.tk_floating_variety = d_floating_variety(); break;
	case SORT_LABEL:              v.tk_label            = d_label();            break;
	case SORT_NAT:                v.tk_nat              = d_nat();              break;
	case SORT_NTEST:              v.tk_ntest            = d_ntest();            break;
	case SORT_ROUNDING_MODE:      v.tk_rounding_mode    = d_rounding_mode();    break;
	case SORT_SHAPE:              v.tk_shape            = d_shape();            break;
	case SORT_SIGNED_NAT:         v.tk_signed_nat       = d_signed_nat();       break;
	case SORT_TAG:                v.tk_tag              = d_tag();              break;
	case SORT_VARIETY:            v.tk_variety          = d_variety();          break;
	case SORT_TOKEN:              v.tk_token            = d_token();            break;
	case SORT_DIAG_TYPE:          v.tk_diag_type        = d_diag_type();        break; /* TDF_DIAG3 */
	case SORT_FILENAME:           v.tk_filename         = d_filename();         break; /* TDF_DIAG3 */
	case SORT_ACCESS:             v.tk_access           = d_access();           break;
	case SORT_TRANSFER_MODE:      v.tk_transfer_mode    = d_transfer_mode();    break;
	case SORT_PROCPROPS:          v.tk_procprops        = d_procprops();        break;
	case SORT_STRING:             v.tk_string           = d_string();           break;
	case SORT_DG:                 v.tk_dg               = d_dg();               break; /* TDF_DIAG4 */
	case SORT_DG_DIM:             v.tk_dg_dim           = d_dg_dim();           break; /* TDF_DIAG4 */
	case SORT_DG_FILENAME:        v.tk_dg_filename      = d_dg_filename();      break; /* TDF_DIAG4 */
	case SORT_DG_IDNAME:          v.tk_dg_idname        = d_dg_idname();        break; /* TDF_DIAG4 */
	case SORT_DG_NAME:            v.tk_dg_name          = d_dg_name();          break; /* TDF_DIAG4 */
	case SORT_DG_TYPE:            v.tk_dg_type          = d_dg_type();          break; /* TDF_DIAG4 */

	default:
		SET(v);
		error(ERR_INTERNAL, "illegal sort name");
	}

	return v;
}

