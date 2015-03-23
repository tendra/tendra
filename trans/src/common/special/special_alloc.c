/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <tdf/nat.h>

#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/messages_r.h>
#include <reader/main_reads.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>
#include <construct/aldefs.h>

#include <local/szs_als.h>

#include <special/special_tok.h>

#include <main/flags.h>

#include <refactor/refactor.h>

static bool
special_alloc_size(tokval *tkv, token t, bitstream pars)
{
	exp off,off1,arg1;
	place old_place;

	old_place = keep_place();
	set_place(pars);

	arg1 = hold_refactor(d_exp());
	set_place(old_place);

	off1 = hold_refactor(f_offset_pad(SLONG_ALIGN, arg1));
	off  = hold_refactor(me_b3(f_offset(al1_of(sh(off1)), SLONG_ALIGN),
							  off1, f_shape_offset(slongsh), offset_add_tag));

	tkv->tk_exp = hold_refactor(f_offset_pad(const_al512, off));

	return true;
}

static bool
special_alloca(tokval *tkv, token t, bitstream pars)
{
	exp arg1;
	place old_place;

	old_place = keep_place();
	set_place(pars);

	arg1 = hold_refactor(d_exp());
	set_place(old_place);
	tkv->tk_exp = hold_refactor(me_u3(f_pointer(long_to_al(8)), arg1, alloca_tag));
	has_alloca = 1;

	return true;
}

const struct special_tok special_allocs[] = {
	{ "~alloc_size", BUILTIN_ALLOCA, special_alloc_size },
	{ "~alloca",     BUILTIN_ALLOCA, special_alloca     }
};

size_t special_allocs_count = sizeof special_allocs / sizeof *special_allocs;

