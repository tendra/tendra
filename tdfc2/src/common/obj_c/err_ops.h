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
