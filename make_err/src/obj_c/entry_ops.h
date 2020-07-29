/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef ENTRY_OPS_H_INCLUDED
#define ENTRY_OPS_H_INCLUDED

/* Operations for union ENTRY */

#define TAG_entry(P)			((unsigned) 0)


/* Operations for component name of union ENTRY */

#define entry_name(P)			(CHECK_NULL(P) + 0)


/* Operations for component alt_name of union ENTRY */

#define entry_alt_name(P)		(CHECK_NULL(P) + 1)


/* Operations for component signature of union ENTRY */

#define entry_signature(P)		(CHECK_NULL(P) + 2)


/* Operations for component use of union ENTRY */

#define entry_use(P)			(CHECK_NULL(P) + 3)


/* Operations for component alt_use of union ENTRY */

#define entry_alt_use(P)		(CHECK_NULL(P) + 4)


/* Operations for component props of union ENTRY */

#define entry_props(P)			(CHECK_NULL(P) + 5)


/* Operations for component maps of union ENTRY */

#define entry_maps(P)			(CHECK_NULL(P) + 6)


/* Operations for field basic of union ENTRY */

#define entry_basic_tag			((unsigned)0)
#define IS_entry_basic(P)		1


#define MAKE_entry_basic(name_, alt_name_, signature_, use_, alt_use_, props_, maps_, errors_entry)\
    {\
	errors *x65_ = GEN_errors(7, TYPEID_entry);\
	COPY_string(x65_ + 0, (name_));\
	COPY_string(x65_ + 1, (alt_name_));\
	COPY_list(x65_ + 2, (signature_));\
	COPY_name(x65_ + 3, (use_));\
	COPY_name(x65_ + 4, (alt_use_));\
	COPY_list(x65_ + 5, (props_));\
	COPY_list(x65_ + 6, (maps_));\
	(errors_entry) = x65_;\
    }

#define DECONS_entry_basic(name_, alt_name_, signature_, use_, alt_use_, props_, maps_, errors_entry)\
    {\
	errors *x66_ = (errors_entry);\
	(name_) = DEREF_string(x66_ + 0);\
	(alt_name_) = DEREF_string(x66_ + 1);\
	(signature_) = DEREF_list(x66_ + 2);\
	(use_) = DEREF_name(x66_ + 3);\
	(alt_use_) = DEREF_name(x66_ + 4);\
	(props_) = DEREF_list(x66_ + 5);\
	(maps_) = DEREF_list(x66_ + 6);\
    }

#define DESTROY_entry_basic(destroyer_, name_, alt_name_, signature_, use_, alt_use_, props_, maps_, errors_entry)\
    {\
	errors *x67_ = (errors_entry);\
	(name_) = DEREF_string(x67_ + 0);\
	(alt_name_) = DEREF_string(x67_ + 1);\
	(signature_) = DEREF_list(x67_ + 2);\
	(use_) = DEREF_name(x67_ + 3);\
	(alt_use_) = DEREF_name(x67_ + 4);\
	(props_) = DEREF_list(x67_ + 5);\
	(maps_) = DEREF_list(x67_ + 6);\
	(destroyer_)(x67_, (unsigned)7);\
    }


#endif
