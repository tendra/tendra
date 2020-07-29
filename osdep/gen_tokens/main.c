/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This program produces some of the target dependency tokens
 * in 'PL TDF' or 'tnc' format for the target system it is
 * compiled and run on.
 *
 * Results are not guaranteed - they should be checked.
 *
 * Each token value may be pre-set by externally defining a macro
 * with the appropriate local name and value.
 *
 * Output format is PL TDF by default, 'tnc' if the macro TNC_SRC
 * is defined.
 */

#include <stdio.h>
#include <stddef.h>
#include <limits.h>

static void
out_nat(char *name, int value)
{
#ifdef TNC_SRC
	(void) printf("( make_tokdef .~%s nat %d )\n\n", name, value);
#else
	(void) printf("Tokdef .~%s = [] NAT %d;\n\n", name, value);
#endif
}

static void
out_bool(char *name, int value)
{
	char *str = (value ? "true" : "false");
#ifdef TNC_SRC
	(void) printf("( make_tokdef .~%s bool %s )\n\n", name, str);
#else
	(void) printf("Tokdef .~%s = [] BOOL %s;\n\n", name, str);
#endif
}

static int
calc_width(unsigned long s_max)
{
	int i;

	for (i = 1; ; i++) {
		if ((((unsigned long) 1) << i) > s_max) return i + 1;
	}

	/* UNREACHED */
}

#define width(c) calc_width((unsigned long) (c))

int
main(void)
{
	int c_width, s_width, i_width, l_width, sz_width;
	int p_width, al_width, str_ch_width;
	int c_sgn, bf_sgn, bdiv, l_end;

#ifdef char_width
	c_width = char_width;
#else
	c_width = width(SCHAR_MAX);
#endif
	out_nat("char_width", c_width);

#ifdef short_width
	s_width = short_width;
#else
	s_width = width(SHRT_MAX);
#endif
	out_nat("short_width", s_width);

#ifdef int_width
	i_width = int_width;
#else
	i_width = width(INT_MAX);
#endif
	out_nat("int_width", i_width);

#ifdef long_width
	l_width = long_width;
#else
	l_width = width(LONG_MAX);
#endif
	out_nat("long_width", l_width);

#ifdef size_t_width
	sz_width = size_t_width;
#else
	sz_width = sizeof (size_t) * c_width;
#endif
	out_nat("size_t_width", sz_width);

#ifdef ptr_width
	p_width = ptr_width;
#else
	p_width = sizeof (char*) * c_width;
#endif
	out_nat("ptr_width", p_width);

#ifdef min_struct_rep
	al_width = min_struct_rep;
	str_ch_width = min_struct_rep;
#else
	{
		struct t { char c; struct { char c; } s; };
		struct c { char c; };
		al_width = offsetof(struct t, s) * c_width;
		str_ch_width = sizeof (struct c) * c_width;
	}
#endif
	if (al_width == str_ch_width) {
		out_nat("min_struct_rep", al_width);
	}

#ifdef char_is_signed
	c_sgn = char_is_signed;
#else
	c_sgn = (CHAR_MIN < 0)? 1 : 0;
#endif
	out_nat("char_is_signed", c_sgn);

#ifdef bitfield_is_signed
	bf_sgn = bitfield_is_signed;
#else
	{
		struct { int ibits :2; } s;
		s.ibits = -1;
		bf_sgn = (s.ibits < 0)? 1 : 0;
	}
#endif
	out_nat("bitfield_is_signed", bf_sgn);

#ifdef best_div
	bdiv = best_div;
#else
	bdiv = (4 % (-6) > 0) +1;
#endif
	out_nat("best_div", bdiv);

#ifdef little_endian
	l_end = little_endian;
#else
	{
		unsigned u;
		u = ('a' << 24) | ('b' << 16) | ('c' << 8) | ('d' << 0);
		l_end = -1;
		if (sizeof u == 4 && * (char *) &u == 'd') l_end = 1;
		if (sizeof u == 4 && * (char *) &u == 'a') l_end = 0;
	}
#endif
	if (l_end >= 0 && l_end <= 1) {
		out_bool("little_endian", l_end);
	}

	return 0;
}
