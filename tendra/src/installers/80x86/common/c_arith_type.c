/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/* 80x86/c_arith_type.c */

/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/



#include "config.h"
#include "common_types.h"
#include "install_fns.h"
#include "arith_codes.h"

/* PROCEDURES */

int
arith_type(int a, int b)
{
	if (a==(t_long|t_unsigned)) return a;
	if (b==(t_long|t_unsigned)) return b;
	if (a==(t_long|t_signed)){
		if (b==(t_int|t_unsigned)) return (t_long|t_unsigned);
		return a;
	}
	if (b==(t_long|t_signed)){
		if (a==(t_int|t_unsigned)) return (t_long|t_unsigned);
		return b;
	}
	if (a==(t_int|t_unsigned)) return a;
	if (b==(t_int|t_unsigned)) return b;
	return (t_int|t_signed);
}

int
promote(int a)
{
	if ((a&variety_filter)<t_int) return (t_int|t_signed);
	return a;
}

int
sign_promote(int a)
{
	if ((a&variety_filter)<t_int)a=((a&~variety_filter)|t_int);
	return a;
}

variety
convert(unsigned a)
{
	switch (a) {
	case (t_char|t_none): return scharsh;
	case (t_char|t_signed): return scharsh;
	case (t_char|t_unsigned): return ucharsh;
	case (t_short|t_signed): return swordsh;
	case (t_short|t_unsigned): return uwordsh;
		
	case (t_int|t_signed): return slongsh;
	case (t_int|t_unsigned): return ulongsh;
	case (t_long|t_signed): return slongsh;
	case (t_long|t_unsigned): return ulongsh;
	}
	return slongsh;
}
