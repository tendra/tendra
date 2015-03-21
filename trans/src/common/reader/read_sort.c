/* $Id$ */

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

#include <shared/check.h>
#include <shared/error.h>

#include <tdf/nat.h>

#include <reader/readglob.h>
#include <reader/basicread.h>
#include <reader/sort.h>
#include <reader/main_reads.h>
#include <reader/externs.h>
#include <reader/messages_r.h>
#include <reader/read_sort.h>

#include <construct/exp.h>

tokval
read_sort(int sn)
{
	tokval v;

	switch (sn) {
	case ALIGNMENT_SORT:     v.tk_alignment        = d_alignment();        break;
	case AL_TAG:             v.tk_al_tag           = d_al_tag();           break;
	case BITFIELD_VARIETY:   v.tk_bitfield_variety = d_bitfield_variety(); break;
	case BOOL:               v.tk_bool             = d_bool();             break;
	case ERROR_TREATMENT:    v.tk_error_treatment  = d_error_treatment();  break;
	case EXP_S:              v.tk_exp              = d_exp();              break;
	case FLOATING_VARIETY:   v.tk_floating_variety = d_floating_variety(); break;
	case LABEL:              v.tk_label            = d_label();            break;
	case NAT:                v.tk_nat              = d_nat();              break;
	case NTEST:              v.tk_ntest            = d_ntest();            break;
	case ROUNDING_MODE:      v.tk_rounding_mode    = d_rounding_mode();    break;
	case SHAPE:              v.tk_shape            = d_shape();            break;
	case SIGNED_NAT:         v.tk_signed_nat       = d_signed_nat();       break;
	case TAG:                v.tk_tag              = d_tag();              break;
	case VARIETY:            v.tk_variety          = d_variety();          break;
	case TOKEN:              v.tk_token            = d_token();            break;
	case DIAG_TYPE_SORT:     v.tk_diag_type        = d_diag_type();        break; /* TDF_DIAG3 */
	case DIAG_FILENAME:      v.tk_filename         = d_filename();         break; /* TDF_DIAG3 */
	case ACCESS_SORT:        v.tk_access           = d_access();           break;
	case TRANSFER_MODE_SORT: v.tk_transfer_mode    = d_transfer_mode();    break;
	case PROCPROPS:          v.tk_procprops        = d_procprops();        break;
	case STRING:             v.tk_string           = d_string();           break;
	case DG_SORT:            v.tk_dg               = d_dg();               break; /* TDF_DIAG4 */
	case DG_DIM_SORT:        v.tk_dg_dim           = d_dg_dim();           break; /* TDF_DIAG4 */
	case DG_FILENAME_SORT:   v.tk_dg_filename      = d_dg_filename();      break; /* TDF_DIAG4 */
	case DG_IDNAME_SORT:     v.tk_dg_idname        = d_dg_idname();        break; /* TDF_DIAG4 */
	case DG_NAME_SORT:       v.tk_dg_name          = d_dg_name();          break; /* TDF_DIAG4 */
	case DG_TYPE_SORT:       v.tk_dg_type          = d_dg_type();          break; /* TDF_DIAG4 */

	default:
		SET(v);
		error(ERR_INTERNAL, SORT_NAME);
	}

	return v;
}

