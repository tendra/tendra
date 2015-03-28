/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/nat.h>
#include <tdf/tag.h>

#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/messages_r.h>
#include <reader/main_reads.h>

#include <construct/exp.h>
#include <construct/me_fns.h>
#include <construct/aldefs.h>
#include <construct/installtypes.h>
#include <construct/install_fns.h>

#include <special/special_tok.h>
#include <special/arith_codes.h>

#include <main/flags.h>

#include <refactor/refactor.h>

static int
arith_type(int a, int b)
{
	if (a == (t_long | t_unsigned)) {
		return a;
	}

	if (b == (t_long | t_unsigned)) {
		return b;
	}

	if (a == (t_long | t_signed)) {
		if (b == (t_int | t_unsigned)) {
			return t_long | t_unsigned;
		}

		return a;
	}

	if (b == (t_long | t_signed)) {
		if (a == (t_int | t_unsigned)) {
			return t_long | t_unsigned;
		}

		return b;
	}

	if (a == (t_int | t_unsigned)) {
		return a;
	}

	if (b == (t_int | t_unsigned)) {
		return b;
	}

	return t_int | t_signed;
}

static int
promote(int a)
{
	if ((a & variety_filter) < t_int) {
		return t_int | t_signed;
	}

	return a;
}

static int
sign_promote(int a)
{
	if ((a & variety_filter) < t_int) {
		a = ((a & ~variety_filter) | t_int);
	}

	return a;
}

static variety
convert(unsigned int a)
{
	switch (a) {
	case t_char  | t_none:     return scharsh;
	case t_char  | t_signed:   return scharsh;
	case t_char  | t_unsigned: return ucharsh;
	case t_short | t_signed:   return swordsh;
	case t_short | t_unsigned: return uwordsh;
	case t_int   | t_signed:   return slongsh;
	case t_int   | t_unsigned: return ulongsh;
	case t_long  | t_signed:   return slongsh;
	case t_long  | t_unsigned: return ulongsh;
	}

	return slongsh;
}

static bool
special_arith_type(tokval *tkv, token t, bitstream pars)
{
	int a, b;
	place old_place;
	signed_nat sn;

	old_place = keep_place();
	set_place(pars);

	sn = d_signed_nat(); a = snatint(sn);
	sn = d_signed_nat(); b = snatint(sn);

	set_place(old_place);
	snatint(sn) = arith_type(a, b);
	tkv->tk_signed_nat = sn;

	return true;
}

static bool
special_promote(tokval *tkv, token t, bitstream pars)
{
	int a;
	place old_place;
	signed_nat sn;

	old_place = keep_place();
	set_place(pars);

	sn = d_signed_nat();
	a = snatint(sn);

	set_place(old_place);
	snatint(sn) = promote(a);
	tkv->tk_signed_nat = sn;

	return true;
}

static bool
special_sign_promote(tokval *tkv, token t, bitstream pars)
{
	int a;
	place old_place;
	signed_nat sn;

	old_place = keep_place();
	set_place(pars);

	sn = d_signed_nat();
	a = snatint(sn);

	set_place(old_place);
	snatint(sn) = sign_promote(a);
	tkv->tk_signed_nat = sn;

	return true;
}

static bool
special_convert(tokval *tkv, token t, bitstream pars)
{
	int a;
	place old_place;
	signed_nat sn;

	old_place = keep_place();
	set_place(pars);

	sn = d_signed_nat();
	a = snatint(sn);

	set_place(old_place);
	tkv->tk_variety = convert((unsigned)a);

	return true;
}

const struct special_tok special_ariths[] = {
	{ "~arith_type",   BUILTIN_PROMOTE, special_arith_type   },
	{ "~promote",      BUILTIN_PROMOTE, special_promote      },
	{ "~sign_promote", BUILTIN_PROMOTE, special_sign_promote },
	{ "~convert",      BUILTIN_PROMOTE, special_convert      }
};

size_t special_ariths_count = sizeof special_ariths / sizeof *special_ariths;

