/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CHKTYPE_INCLUDED
#define CHKTYPE_INCLUDED


/*
    TYPE CHECKING DECLARATIONS

    The routines in this module are concerned with type checking and type
    consistency.
*/

extern ERROR check_object(TYPE);
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

#define eq_type(A, B)			eq_type_qual((A), (B), 0)
#define eq_type_unqual(A, B)		eq_type_qual((A), (B), 1)


/*
    TYPE CATEGORIES

    These macros are used to describe the various categories of types.  The
    class value associated with a type can be found using type_category.
    There are categories for each of the basic kinds of type - integral
    types, pointer types etc. plus a category for lvalues.  Other categories
    are unions of existing categories, for example:

	    INT = INTEGER u BITF u ENUM ;
	    ARITH = INTEGER u FLOAT u BITF u ENUM ;
	    OVERLOAD = CLASS u ENUM ;
*/

#define CTYPE_NONE			((unsigned)0x0000)
#define CTYPE_INTEGER			((unsigned)0x0001)
#define CTYPE_FLOAT			((unsigned)0x0002)
#define CTYPE_PTR			((unsigned)0x0004)
#define CTYPE_PTR_MEM			((unsigned)0x0008)
#define CTYPE_BITF			((unsigned)0x0010)
#define CTYPE_CLASS			((unsigned)0x0020)
#define CTYPE_ENUM			((unsigned)0x0040)
#define CTYPE_VOID			((unsigned)0x0080)
#define CTYPE_ERROR			((unsigned)0x0100)
#define CTYPE_TOKEN			((unsigned)0x0200)
#define CTYPE_TEMPL			((unsigned)0x0400)
#define CTYPE_LVALUE			((unsigned)0x0800)

#define CTYPE_INT			((unsigned)0x0051)
#define CTYPE_ARITH			((unsigned)0x0053)
#define CTYPE_SCALAR			((unsigned)0x0057)
#define CTYPE_OVERLOAD			((unsigned)0x0460)
#define CTYPE_ADDRESS			((unsigned)0x082c)

#define IS_TYPE_INTEGER(C)		((C) & CTYPE_INTEGER)
#define IS_TYPE_FLOAT(C)		((C) & CTYPE_FLOAT)
#define IS_TYPE_PTR(C)			((C) & CTYPE_PTR)
#define IS_TYPE_PTR_MEM(C)		((C) & CTYPE_PTR_MEM)
#define IS_TYPE_BITF(C)			((C) & CTYPE_BITF)
#define IS_TYPE_CLASS(C)		((C) & CTYPE_CLASS)
#define IS_TYPE_ENUM(C)			((C) & CTYPE_ENUM)
#define IS_TYPE_VOID(C)			((C) & CTYPE_VOID)
#define IS_TYPE_ERROR(C)		((C) & CTYPE_ERROR)
#define IS_TYPE_TOKEN(C)		((C) & CTYPE_TOKEN)
#define IS_TYPE_TEMPL(C)		((C) & CTYPE_TEMPL)
#define IS_TYPE_LVALUE(C)		((C) & CTYPE_LVALUE)

#define IS_TYPE_INT(C)			((C) & CTYPE_INT)
#define IS_TYPE_ARITH(C)		((C) & CTYPE_ARITH)
#define IS_TYPE_SCALAR(C)		((C) & CTYPE_SCALAR)
#define IS_TYPE_OVERLOAD(C)		((C) & CTYPE_OVERLOAD)
#define IS_TYPE_ADDRESS(C)		((C) & CTYPE_ADDRESS)


#endif
