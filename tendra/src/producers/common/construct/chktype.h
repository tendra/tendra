/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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


#ifndef CHKTYPE_INCLUDED
#define CHKTYPE_INCLUDED


/*
 *    TYPE CHECKING DECLARATIONS
 *
 *    The routines in this module are concerned with type checking and type
 *    consistency.
 */

extern ERROR check_object(TYPE) ;
extern ERROR check_abstract(TYPE);
extern ERROR check_complete(TYPE);
extern ERROR check_incomplete(TYPE);
extern ERROR check_modifiable(TYPE, EXP);
extern TYPE check_pointer(TYPE, ERROR *);
extern TYPE check_compatible(TYPE, TYPE, int, ERROR *, int);
extern TYPE type_composite(TYPE, TYPE, int, int, ERROR *, int);
extern int is_global_type(TYPE);
extern int unify_type(TYPE, TYPE, CV_SPEC, int);
extern unsigned type_category(TYPE *);
extern unsigned type_tag(TYPE);

extern int eq_func_type(TYPE, TYPE, int, int);
extern int eq_type_qual(TYPE, TYPE, int);
extern int eq_type_offset(TYPE, TYPE);
extern int eq_itype(INT_TYPE, INT_TYPE);
extern int eq_ftype(FLOAT_TYPE, FLOAT_TYPE);
extern int eq_ctype(CLASS_TYPE, CLASS_TYPE);
extern int eq_etype(ENUM_TYPE, ENUM_TYPE);
extern CV_SPEC cv_compare(TYPE, TYPE);
extern CV_SPEC find_cv_qual(TYPE);

#define eq_type(A, B)			eq_type_qual ((A), (B), 0)
#define eq_type_unqual(A, B)		eq_type_qual ((A), (B), 1)


/*
 *    TYPE CATEGORIES
 *
 *    These macros are used to describe the various categories of types.  The
 *    class value associated with a type can be found using type_category.
 *    There are categories for each of the basic kinds of type - integral
 *    types, pointer types etc. plus a category for lvalues.  Other categories
 *    are unions of existing categories, for example:
 *
 *	    INT = INTEGER u BITF u ENUM;
 *	    ARITH = INTEGER u FLOAT u BITF u ENUM;
 *	    OVERLOAD = CLASS u ENUM;
 */

#define CTYPE_NONE			((unsigned) 0x0000)
#define CTYPE_INTEGER			((unsigned) 0x0001)
#define CTYPE_FLOAT			((unsigned) 0x0002)
#define CTYPE_PTR			((unsigned) 0x0004)
#define CTYPE_PTR_MEM			((unsigned) 0x0008)
#define CTYPE_BITF			((unsigned) 0x0010)
#define CTYPE_CLASS			((unsigned) 0x0020)
#define CTYPE_ENUM			((unsigned) 0x0040)
#define CTYPE_VOID			((unsigned) 0x0080)
#define CTYPE_ERROR			((unsigned) 0x0100)
#define CTYPE_TOKEN			((unsigned) 0x0200)
#define CTYPE_TEMPL			((unsigned) 0x0400)
#define CTYPE_LVALUE			((unsigned) 0x0800)

#define CTYPE_INT			((unsigned) 0x0051)
#define CTYPE_ARITH			((unsigned) 0x0053)
#define CTYPE_SCALAR			((unsigned) 0x0057)
#define CTYPE_OVERLOAD			((unsigned) 0x0460)
#define CTYPE_ADDRESS			((unsigned) 0x082c)

#define IS_TYPE_INTEGER(C)		((C) & CTYPE_INTEGER)
#define IS_TYPE_FLOAT(C)		((C) & CTYPE_FLOAT)
#define IS_TYPE_PTR(C)		((C) & CTYPE_PTR)
#define IS_TYPE_PTR_MEM(C)		((C) & CTYPE_PTR_MEM)
#define IS_TYPE_BITF(C)		((C) & CTYPE_BITF)
#define IS_TYPE_CLASS(C)		((C) & CTYPE_CLASS)
#define IS_TYPE_ENUM(C)		((C) & CTYPE_ENUM)
#define IS_TYPE_VOID(C)		((C) & CTYPE_VOID)
#define IS_TYPE_ERROR(C)		((C) & CTYPE_ERROR)
#define IS_TYPE_TOKEN(C)		((C) & CTYPE_TOKEN)
#define IS_TYPE_TEMPL(C)		((C) & CTYPE_TEMPL)
#define IS_TYPE_LVALUE(C)		((C) & CTYPE_LVALUE)

#define IS_TYPE_INT(C)		((C) & CTYPE_INT)
#define IS_TYPE_ARITH(C)		((C) & CTYPE_ARITH)
#define IS_TYPE_SCALAR(C)		((C) & CTYPE_SCALAR)
#define IS_TYPE_OVERLOAD(C)		((C) & CTYPE_OVERLOAD)
#define IS_TYPE_ADDRESS(C)		((C) & CTYPE_ADDRESS)


#endif
