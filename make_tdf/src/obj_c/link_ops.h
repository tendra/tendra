/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef LINK_OPS_H_INCLUDED
#define LINK_OPS_H_INCLUDED

/* Operations for union LINKAGE */

#define TAG_link(P)			((unsigned) 0)


/* Operations for component name of union LINKAGE */

#define link_name(P)			(CHECK_NULL(P) + 0)


/* Operations for component type of union LINKAGE */

#define link_type(P)			(CHECK_NULL(P) + 1)


/* Operations for field basic of union LINKAGE */

#define link_basic_tag			((unsigned)0)
#define IS_link_basic(P)		1


#define MAKE_link_basic(name_, type_, tdf_link)\
    {\
	tdf *x96_ = GEN_tdf(2, TYPEID_link);\
	COPY_string(x96_ + 0, (name_));\
	COPY_sort(x96_ + 1, (type_));\
	(tdf_link) = x96_;\
    }

#define DECONS_link_basic(name_, type_, tdf_link)\
    {\
	tdf *x97_ = (tdf_link);\
	(name_) = DEREF_string(x97_ + 0);\
	(type_) = DEREF_sort(x97_ + 1);\
    }

#define DESTROY_link_basic(destroyer_, name_, type_, tdf_link)\
    {\
	tdf *x98_ = (tdf_link);\
	(name_) = DEREF_string(x98_ + 0);\
	(type_) = DEREF_sort(x98_ + 1);\
	(destroyer_)(x98_, (unsigned)2);\
    }


#endif
