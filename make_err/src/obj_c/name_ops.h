/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef NAME_OPS_H_INCLUDED
#define NAME_OPS_H_INCLUDED

/* Operations for union NAME */

#define TAG_name(P)			((unsigned) 0)


/* Operations for component id of union NAME */

#define name_id(P)			(CHECK_NULL(P) + 0)


/* Operations for component number of union NAME */

#define name_number(P)			(CHECK_NULL(P) + 1)


/* Operations for field basic of union NAME */

#define name_basic_tag			((unsigned)0)
#define IS_name_basic(P)		1


#define MAKE_name_basic(id_, number_, errors_name)\
    {\
	errors *x50_ = GEN_errors(2, TYPEID_name);\
	COPY_string(x50_ + 0, (id_));\
	COPY_int(x50_ + 1, (number_));\
	(errors_name) = x50_;\
    }

#define DECONS_name_basic(id_, number_, errors_name)\
    {\
	errors *x51_ = (errors_name);\
	(id_) = DEREF_string(x51_ + 0);\
	(number_) = DEREF_int(x51_ + 1);\
    }

#define DESTROY_name_basic(destroyer_, id_, number_, errors_name)\
    {\
	errors *x52_ = (errors_name);\
	(id_) = DEREF_string(x52_ + 0);\
	(number_) = DEREF_int(x52_ + 1);\
	(destroyer_)(x52_, (unsigned)2);\
    }


#endif
