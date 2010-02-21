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

#ifndef ERR_OPS_H_INCLUDED
#define ERR_OPS_H_INCLUDED

/* Operations for union ERROR */

#define TAG_err(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for component severity of union ERROR */

#define err_severity(P)			(CHECK_NULL(P) + 1)


/* Operations for field simple of union ERROR */

#define err_simple_tag			((unsigned)0)
#define IS_err_simple(P)		(CHECK_NULL(P)->ag_tag == 0)

#define err_simple_number(P)		(CHECK_TAG((P), 0) + 2)
#define err_simple_size(P)		(CHECK_TAG((P), 0) + 3)

#define MAKE_err_simple(severity_, number_, c_class_err)\
    {\
	c_class *x857_ = GEN_c_class(4, TYPEID_err);\
	x857_->ag_tag = 0;\
	COPY_int(x857_ + 1, (severity_));\
	COPY_int(x857_ + 2, (number_));\
	COPY_unsigned(x857_ + 3, 0);\
	(c_class_err) = x857_;\
    }

#define DECONS_err_simple(severity_, number_, size_, c_class_err)\
    {\
	c_class *x858_ = CHECK_TAG((c_class_err), 0);\
	(severity_) = DEREF_int(x858_ + 1);\
	(number_) = DEREF_int(x858_ + 2);\
	(size_) = DEREF_unsigned(x858_ + 3);\
    }

#define DESTROY_err_simple(destroyer_, severity_, number_, size_, c_class_err)\
    {\
	c_class *x859_ = CHECK_TAG((c_class_err), 0);\
	(severity_) = DEREF_int(x859_ + 1);\
	(number_) = DEREF_int(x859_ + 2);\
	(size_) = DEREF_unsigned(x859_ + 3);\
	(destroyer_)(x859_, (unsigned)4);\
    }


/* Operations for field compound of union ERROR */

#define err_compound_tag		((unsigned)1)
#define IS_err_compound(P)		(CHECK_NULL(P)->ag_tag == 1)

#define err_compound_head(P)		(CHECK_TAG((P), 1) + 2)
#define err_compound_tail(P)		(CHECK_TAG((P), 1) + 3)

#define MAKE_err_compound(severity_, head_, tail_, c_class_err)\
    {\
	c_class *x860_ = GEN_c_class(4, TYPEID_err);\
	x860_->ag_tag = 1;\
	COPY_int(x860_ + 1, (severity_));\
	COPY_err(x860_ + 2, (head_));\
	COPY_err(x860_ + 3, (tail_));\
	(c_class_err) = x860_;\
    }

#define DECONS_err_compound(severity_, head_, tail_, c_class_err)\
    {\
	c_class *x861_ = CHECK_TAG((c_class_err), 1);\
	(severity_) = DEREF_int(x861_ + 1);\
	(head_) = DEREF_err(x861_ + 2);\
	(tail_) = DEREF_err(x861_ + 3);\
    }

#define DESTROY_err_compound(destroyer_, severity_, head_, tail_, c_class_err)\
    {\
	c_class *x862_ = CHECK_TAG((c_class_err), 1);\
	(severity_) = DEREF_int(x862_ + 1);\
	(head_) = DEREF_err(x862_ + 2);\
	(tail_) = DEREF_err(x862_ + 3);\
	(destroyer_)(x862_, (unsigned)4);\
    }


#endif
