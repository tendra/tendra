/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef PAR_OPS_H_INCLUDED
#define PAR_OPS_H_INCLUDED

/* Operations for union PARAMETER */

#define TAG_par(P)			((unsigned) 0)


/* Operations for component name of union PARAMETER */

#define par_name(P)			(CHECK_NULL(P) + 0)


/* Operations for component type of union PARAMETER */

#define par_type(P)			(CHECK_NULL(P) + 1)


/* Operations for component brk of union PARAMETER */

#define par_brk(P)			(CHECK_NULL(P) + 2)


/* Operations for component align of union PARAMETER */

#define par_align(P)			(CHECK_NULL(P) + 3)


/* Operations for component intro of union PARAMETER */

#define par_intro(P)			(CHECK_NULL(P) + 4)


/* Operations for field basic of union PARAMETER */

#define par_basic_tag			((unsigned)0)
#define IS_par_basic(P)			1


#define MAKE_par_basic(name_, type_, brk_, align_, intro_, tdf_par)\
    {\
	tdf *x65_ = GEN_tdf(5, TYPEID_par);\
	COPY_string(x65_ + 0, (name_));\
	COPY_sort(x65_ + 1, (type_));\
	COPY_int(x65_ + 2, (brk_));\
	COPY_int(x65_ + 3, (align_));\
	COPY_int(x65_ + 4, (intro_));\
	(tdf_par) = x65_;\
    }

#define DECONS_par_basic(name_, type_, brk_, align_, intro_, tdf_par)\
    {\
	tdf *x66_ = (tdf_par);\
	(name_) = DEREF_string(x66_ + 0);\
	(type_) = DEREF_sort(x66_ + 1);\
	(brk_) = DEREF_int(x66_ + 2);\
	(align_) = DEREF_int(x66_ + 3);\
	(intro_) = DEREF_int(x66_ + 4);\
    }

#define DESTROY_par_basic(destroyer_, name_, type_, brk_, align_, intro_, tdf_par)\
    {\
	tdf *x67_ = (tdf_par);\
	(name_) = DEREF_string(x67_ + 0);\
	(type_) = DEREF_sort(x67_ + 1);\
	(brk_) = DEREF_int(x67_ + 2);\
	(align_) = DEREF_int(x67_ + 3);\
	(intro_) = DEREF_int(x67_ + 4);\
	(destroyer_)(x67_, (unsigned)5);\
    }


#endif
