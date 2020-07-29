/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef PARAM_OPS_H_INCLUDED
#define PARAM_OPS_H_INCLUDED

/* Operations for union PARAM */

#define TAG_param(P)			((unsigned) 0)


/* Operations for component type of union PARAM */

#define param_type(P)			(CHECK_NULL(P) + 0)


/* Operations for component name of union PARAM */

#define param_name(P)			(CHECK_NULL(P) + 1)


/* Operations for component number of union PARAM */

#define param_number(P)			(CHECK_NULL(P) + 2)


/* Operations for field basic of union PARAM */

#define param_basic_tag			((unsigned)0)
#define IS_param_basic(P)		1


#define MAKE_param_basic(type_, name_, number_, errors_param)\
    {\
	errors *x62_ = GEN_errors(3, TYPEID_param);\
	COPY_name(x62_ + 0, (type_));\
	COPY_string(x62_ + 1, (name_));\
	COPY_int(x62_ + 2, (number_));\
	(errors_param) = x62_;\
    }

#define DECONS_param_basic(type_, name_, number_, errors_param)\
    {\
	errors *x63_ = (errors_param);\
	(type_) = DEREF_name(x63_ + 0);\
	(name_) = DEREF_string(x63_ + 1);\
	(number_) = DEREF_int(x63_ + 2);\
    }

#define DESTROY_param_basic(destroyer_, type_, name_, number_, errors_param)\
    {\
	errors *x64_ = (errors_param);\
	(type_) = DEREF_name(x64_ + 0);\
	(name_) = DEREF_string(x64_ + 1);\
	(number_) = DEREF_int(x64_ + 2);\
	(destroyer_)(x64_, (unsigned)3);\
    }


#endif
