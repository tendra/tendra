/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
