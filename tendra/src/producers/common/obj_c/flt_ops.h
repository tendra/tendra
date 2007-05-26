/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
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
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef FLT_OPS_H_INCLUDED
#define FLT_OPS_H_INCLUDED

/* Operations for union FLOAT */

#define TAG_flt(P)			((unsigned) 0)


/* Operations for component tok of union FLOAT */

#define flt_tok(P)			(CHECK_NULL(P) + 0)


/* Operations for field simple of union FLOAT */

#define flt_simple_tag			((unsigned)0)
#define IS_flt_simple(P)		1

#define flt_simple_int_part(P)		((P) + 1)
#define flt_simple_frac_part(P)		((P) + 2)
#define flt_simple_exponent(P)		((P) + 3)

#define MAKE_flt_simple(int_part_, frac_part_, exponent_, c_class_flt)\
    {\
	c_class *x480_ = GEN_c_class(4, TYPEID_flt);\
	COPY_ulong(x480_ + 0, LINK_NONE);\
	COPY_string(x480_ + 1, (int_part_));\
	COPY_string(x480_ + 2, (frac_part_));\
	COPY_nat(x480_ + 3, (exponent_));\
	(c_class_flt) = x480_;\
    }

#define DECONS_flt_simple(tok_, int_part_, frac_part_, exponent_, c_class_flt)\
    {\
	c_class *x481_ = (c_class_flt);\
	(tok_) = DEREF_ulong(x481_ + 0);\
	(int_part_) = DEREF_string(x481_ + 1);\
	(frac_part_) = DEREF_string(x481_ + 2);\
	(exponent_) = DEREF_nat(x481_ + 3);\
    }

#define DESTROY_flt_simple(destroyer_, tok_, int_part_, frac_part_, exponent_, c_class_flt)\
    {\
	c_class *x482_ = (c_class_flt);\
	(tok_) = DEREF_ulong(x482_ + 0);\
	(int_part_) = DEREF_string(x482_ + 1);\
	(frac_part_) = DEREF_string(x482_ + 2);\
	(exponent_) = DEREF_nat(x482_ + 3);\
	(destroyer_)(x482_, (unsigned)4);\
    }


#endif
