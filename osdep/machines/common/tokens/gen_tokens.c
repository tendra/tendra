/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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


/************************************************************************/
/*									*/
/*		gen_tokens.c	Version 2.0				*/
/*									*/
/*  This program produces some of the target dependency tokens		*/
/*  in 'PL TDF' or 'tnc' format for the target system it is		*/
/*  compiled and run on.						*/
/*									*/
/*  Results are not guaranteed - they should be checked.		*/
/*									*/
/*  Each token value may be pre-set by externally defining a macro	*/
/*  with the appropriate local name and value.				*/
/*									*/
/*  Output format is PL TDF by default, 'tnc' if the macro TNC_SRC	*/
/*  is defined.								*/
/*									*/
/************************************************************************/


#include <stdio.h>
#include <stddef.h>
#include <limits.h>


static void
out_nat(char *name, int value)
{
#ifdef TNC_SRC
	(void)printf("( make_tokdef .~%s nat %d )\n\n", name, value);
#else	/* PL TDF source */
	(void)printf("Tokdef .~%s = [] NAT %d;\n\n", name, value);
#endif
	return;
}


static void
out_bool(char *name, int value)
{
	char *str = (value ? "true" : "false");
#ifdef TNC_SRC
	(void)printf("( make_tokdef .~%s bool %s )\n\n", name, str);
#else	/* PL TDF source */
	(void)printf("Tokdef .~%s = [] BOOL %s;\n\n", name, str);
#endif
	return;
}


static int
calc_width(unsigned long s_max)
{
	int i;
	for (i=1;;i++) {
		if ((((unsigned long)1) <<i) > s_max) return i+1;
	}
	/* UNREACHED */
}

#define width(c)	calc_width((unsigned long)(c))


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
	sz_width = sizeof(size_t)* c_width;
#endif
	out_nat("size_t_width", sz_width);

#ifdef ptr_width
	p_width = ptr_width;
#else
	p_width = sizeof(char*)* c_width;
#endif
	out_nat("ptr_width", p_width);

#ifdef min_struct_rep
	al_width = min_struct_rep;
	str_ch_width = min_struct_rep;
#else
	{
		struct t { char c; struct { char c; } s; };
		struct c { char c; };
		al_width = offsetof(struct t,s)* c_width;
		str_ch_width = sizeof(struct c)* c_width;
	}
#endif
	if (al_width == str_ch_width) {
		out_nat("min_struct_rep", al_width);
	}

#ifdef char_is_signed
	c_sgn = char_is_signed;
#else
	c_sgn = (CHAR_MIN<0)? 1 : 0;
#endif
	out_nat("char_is_signed", c_sgn);

#ifdef bitfield_is_signed
	bf_sgn = bitfield_is_signed;
#else
	{
		struct { int ibits : 2; } s;
		s.ibits = -1;
		bf_sgn = (s.ibits<0)? 1 : 0;
	}
#endif
	out_nat("bitfield_is_signed", bf_sgn);

#ifdef best_div
	bdiv = best_div;
#else
	bdiv = (4%(-6) >0) +1;
#endif
	out_nat("best_div", bdiv);

#ifdef little_endian
	l_end = little_endian;
#else
	{
		unsigned u;
		u = ('a' << 24) | ('b' << 16) | ('c' << 8) | ('d' << 0);
		l_end = -1;
		if (sizeof(u) ==4 && *(char *) &u == 'd')l_end = 1;
		if (sizeof(u) ==4 && *(char *) &u == 'a')l_end = 0;
	}
#endif
	if (l_end >= 0 && l_end <= 1) {
		out_bool("little_endian", l_end);
	}

	return 0;
}
