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





#include "config.h"
#include "common_types.h"
#include "flpttypes.h"
#include "messages_c.h"
#include "flpt.h"
#include "basicread.h"
#include "expmacs.h"
#include "exp.h"

#include "f64.h"



/* PROCEDURES */

flt64
flt_to_f64(flpt fp, int sg, int * ov)
{
	flt * f = &flptnos[fp];
	flt64 res;
	int i = f->exp;
	*ov = 0;
	
	if (f->sign == 0 || i<0) {
		res.big = 0;
		res.small = 0;
	}
	else {
		res.big = 0;
		res.small = f->mant[i];
		if (i>0)
			res.small += (unsigned int)(f->mant[i-1] << 16);
		if (i>1)
			res.big = (int)f->mant[i-2];
		if (i>2)
			res.big += (int)(f->mant[i-3] << 16);
		if (i>3 || (sg && res.big < 0))
			*ov = 1;
	}
	
	if (f->sign == -1)  {
		res.small = ~res.small;
		res.big = ~res.big;
		if (res.small == 0xffffffff) {
			++res.big;
		}
		++res.small;
	}
	
	return res;
}

flpt
f64_to_flt(flt64 a, int sg)
{
	flpt r = new_flpt();
	flt * res = &flptnos[r];
	flt_zero(res);
	
	if (a.big == 0 && a.small == 0)  {
		return r;
	}
	
	if (sg && a.big < 0) {
		a.small = ~a.small;
		a.big = ~a.big;
		if (a.small == 0xffffffff) {
			++a.big;
		}
		++a.small;
		res->sign = -1;
	}
	else
		res->sign = 1;
	
	if (a.big == 0) {
		if ((a.small & 0xffff0000) == 0) {
			res->exp = 0;
			res->mant[0] = (unsigned short)(a.small & 0xffff);
		}
		else {
			res->exp = 1;
			res->mant[0] = (unsigned short)((a.small & 0xffff0000) >> 16);
			res->mant[1] = (unsigned short)(a.small & 0xffff);
		}
	}
	else {
		if ((a.big & (int)0xffff0000) == 0) {
			res->exp = 2;
			res->mant[0] = (unsigned short)(a.big & 0xffff);
			res->mant[1] = (unsigned short)((a.small & 0xffff0000) >> 16);
			res->mant[2] = (unsigned short)(a.small & 0xffff);
		}
		else {
			res->exp = 3;
			res->mant[0] = (unsigned short)(((unsigned int)a.big >> 16) & 0xffff);
			res->mant[1] = (unsigned short)(a.big & 0xffff);
			res->mant[2] = (unsigned short)((a.small & 0xffff0000) >> 16);
			res->mant[3] = (unsigned short)(a.small & 0xffff);
		}
	}
	
	return r;
}

int
f64_to_flpt(flt64 a, int sg, int * pr, int sz)
{
	int t = (int)a.small;
	*pr = 0;
	
	if (sg && (t >> 31) == a.big)
		return t;
	
	if (!sg && a.big == 0 && ((a.small & 0x80000000) == 0 || sz <= 32))
		return t;
	
	*pr = 1;
	return  f64_to_flt(a, sg);
}


flt64
int_to_f64(int i, int sg)
{
	flt64 res;
	res.small = (unsigned int)i;
	if (sg && i < 0)
		res.big = -1;
	else
		res.big = 0;
	return res;
}

flt64
exp_to_f64(exp e)
{
	int ov;
	if (isbigval(e))
		return flt_to_f64(no(e), is_signed(sh(e)), &ov);
	return int_to_f64(no(e), is_signed(sh(e)));
}


