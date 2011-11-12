/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
			    VERSION INFORMATION
			    ===================
--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/spec_tok.c,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: spec_tok.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:58  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:18  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:58  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:17  john
 *
 * Revision 1.1  94/06/29  14:25:55  14:25:55  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "config.h"

#include "codetypes.h"
#include "basicread.h"
#include "tags.h"
#include "exp.h"
#include "expmacs.h"
#include "diag_fns.h"
#include "flags.h"
#include "check.h"
#include "me_fns.h"
#include "externs.h"
#include "installglob.h"
#include "messages_r.h"
#include "main_reads.h"
#include "install_fns.h"
#include "c_arith_type.h"
#include "natmacs.h"
#include "spec_tok.h"


/*
    INTERCEPT SPECIAL TOKENS
*/

tokval
special_token(token t, bitstream pars, int sortcode, int *done)
{
	tokval tkv;
	UNUSED(sortcode);

	if (t->tok_name == NULL) {
		/* call looks at done to see if result is meaningful */
		SET(tkv);
		return tkv;
	}

	/* alloca */
	if (!strcmp(t->tok_name, "~alloca")) {
		exp arg1;
		place old_place;
		old_place = keep_place();
		set_place(pars);
		arg1 = hold_check(d_exp());
		set_place(old_place);
		tkv.tk_exp = hold_check(me_u3(f_pointer(long_to_al(8)),
					      arg1, alloca_tag));
		*done = 1;
		has_alloca = 1;
		return tkv;
	}

	/* diagnostic tokens */
	if (!strcmp(t->tok_name, "~exp_to_source") ||
	    !strcmp(t->tok_name, "~diag_id_scope") ||
	    !strcmp(t->tok_name, "~diag_type_scope") ||
	    !strcmp(t->tok_name, "~diag_tag_scope")) {
		place old_place;
		old_place = keep_place();
		set_place(pars);
		tkv.tk_exp = hold_check(d_exp());
		*done = 1;
		if (!diagnose) {
			set_place(old_place);
			return tkv;
		}
		if (!strcmp(t->tok_name, "~exp_to_source")) {
			exp r;
			diag_info *di = read_exp_to_source();
			crt_lno = natint(di->data.source.end.line_no);
			crt_charno = natint(di->data.source.end.char_off);
			crt_flnm = di->data.source.beg.file->file.ints.chars;
			r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp,
				   nilexp, 1, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
			set_place(old_place);
			return tkv;
		}
		if (!strcmp(t->tok_name, "~diag_id_scope")) {
			exp r;
			diag_info *di = read_diag_id_scope();
			r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp,
				   nilexp, 2, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
			set_place(old_place);
			return tkv;
		}
		if (!strcmp(t->tok_name, "~diag_type_scope")) {
			exp r;
			diag_info *di = read_diag_type_scope();
			r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp,
				   nilexp, 3, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
			set_place(old_place);
			return tkv;
		}
		if (!strcmp(t->tok_name, "~diag_tag_scope")) {
			exp r;
			diag_info *di = read_diag_tag_scope();
			r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp,
				   nilexp, 4, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
			set_place(old_place);
			return tkv;
		}
	}

	/* call looks at done to see if result is meaningful */
	SET(tkv);
	return tkv;
}


/*
    CHECK FOR MACHINE DEPENDENT TOKENS
*/

int
machine_toks(char *s)
{
	return 0;
}
