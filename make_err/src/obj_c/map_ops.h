/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef MAP_OPS_H_INCLUDED
#define MAP_OPS_H_INCLUDED

/* Operations for union MAP */

#define TAG_map(P)			((unsigned) 0)


/* Operations for component key of union MAP */

#define map_key(P)			(CHECK_NULL(P) + 0)


/* Operations for component msg of union MAP */

#define map_msg(P)			(CHECK_NULL(P) + 1)


/* Operations for component alt_msg of union MAP */

#define map_alt_msg(P)			(CHECK_NULL(P) + 2)


/* Operations for field basic of union MAP */

#define map_basic_tag			((unsigned)0)
#define IS_map_basic(P)			1


#define MAKE_map_basic(key_, msg_, alt_msg_, errors_map)\
    {\
	errors *x59_ = GEN_errors(3, TYPEID_map);\
	COPY_name(x59_ + 0, (key_));\
	COPY_list(x59_ + 1, (msg_));\
	COPY_list(x59_ + 2, (alt_msg_));\
	(errors_map) = x59_;\
    }

#define DECONS_map_basic(key_, msg_, alt_msg_, errors_map)\
    {\
	errors *x60_ = (errors_map);\
	(key_) = DEREF_name(x60_ + 0);\
	(msg_) = DEREF_list(x60_ + 1);\
	(alt_msg_) = DEREF_list(x60_ + 2);\
    }

#define DESTROY_map_basic(destroyer_, key_, msg_, alt_msg_, errors_map)\
    {\
	errors *x61_ = (errors_map);\
	(key_) = DEREF_name(x61_ + 0);\
	(msg_) = DEREF_list(x61_ + 1);\
	(alt_msg_) = DEREF_list(x61_ + 2);\
	(destroyer_)(x61_, (unsigned)3);\
    }


#endif
