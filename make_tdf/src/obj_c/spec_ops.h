/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef SPEC_OPS_H_INCLUDED
#define SPEC_OPS_H_INCLUDED

/* Operations for union SPECIFICATION */

#define TAG_spec(P)			((unsigned) 0)


/* Operations for component major of union SPECIFICATION */

#define spec_major(P)			(CHECK_NULL(P) + 0)


/* Operations for component minor of union SPECIFICATION */

#define spec_minor(P)			(CHECK_NULL(P) + 1)


/* Operations for component sorts of union SPECIFICATION */

#define spec_sorts(P)			(CHECK_NULL(P) + 2)


/* Operations for component vars of union SPECIFICATION */

#define spec_vars(P)			(CHECK_NULL(P) + 3)


/* Operations for component eqns of union SPECIFICATION */

#define spec_eqns(P)			(CHECK_NULL(P) + 4)


/* Operations for component foreign of union SPECIFICATION */

#define spec_foreign(P)			(CHECK_NULL(P) + 5)


/* Operations for field basic of union SPECIFICATION */

#define spec_basic_tag			((unsigned)0)
#define IS_spec_basic(P)		1


#define MAKE_spec_basic(major_, minor_, sorts_, vars_, eqns_, foreign_, tdf_spec)\
    {\
	tdf *x99_ = GEN_tdf(6, TYPEID_spec);\
	COPY_unsigned(x99_ + 0, (major_));\
	COPY_unsigned(x99_ + 1, (minor_));\
	COPY_list(x99_ + 2, (sorts_));\
	COPY_list(x99_ + 3, (vars_));\
	COPY_list(x99_ + 4, (eqns_));\
	COPY_list(x99_ + 5, (foreign_));\
	(tdf_spec) = x99_;\
    }

#define DECONS_spec_basic(major_, minor_, sorts_, vars_, eqns_, foreign_, tdf_spec)\
    {\
	tdf *x100_ = (tdf_spec);\
	(major_) = DEREF_unsigned(x100_ + 0);\
	(minor_) = DEREF_unsigned(x100_ + 1);\
	(sorts_) = DEREF_list(x100_ + 2);\
	(vars_) = DEREF_list(x100_ + 3);\
	(eqns_) = DEREF_list(x100_ + 4);\
	(foreign_) = DEREF_list(x100_ + 5);\
    }

#define DESTROY_spec_basic(destroyer_, major_, minor_, sorts_, vars_, eqns_, foreign_, tdf_spec)\
    {\
	tdf *x101_ = (tdf_spec);\
	(major_) = DEREF_unsigned(x101_ + 0);\
	(minor_) = DEREF_unsigned(x101_ + 1);\
	(sorts_) = DEREF_list(x101_ + 2);\
	(vars_) = DEREF_list(x101_ + 3);\
	(eqns_) = DEREF_list(x101_ + 4);\
	(foreign_) = DEREF_list(x101_ + 5);\
	(destroyer_)(x101_, (unsigned)6);\
    }


#endif
