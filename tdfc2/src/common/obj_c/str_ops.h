/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef STR_OPS_H_INCLUDED
#define STR_OPS_H_INCLUDED

/* Operations for union STRING */

#define TAG_str(P)			((unsigned) 0)


/* Operations for component next of union STRING */

#define str_next(P)			(CHECK_NULL(P) + 0)


/* Operations for field simple of union STRING */

#define str_simple_tag			((unsigned)0)
#define IS_str_simple(P)		1

#define str_simple_len(P)		((P) + 1)
#define str_simple_text(P)		((P) + 2)
#define str_simple_kind(P)		((P) + 3)
#define str_simple_tok(P)		((P) + 4)

#define MAKE_str_simple(len_, text_, kind_, c_class_str)\
    {\
	c_class *x483_ = GEN_c_class(5, TYPEID_str);\
	COPY_str(x483_ + 0, NULL_str);\
	COPY_ulong(x483_ + 1, (len_));\
	COPY_string(x483_ + 2, (text_));\
	COPY_unsigned(x483_ + 3, (kind_));\
	COPY_ulong(x483_ + 4, LINK_NONE);\
	(c_class_str) = x483_;\
    }

#define DECONS_str_simple(next_, len_, text_, kind_, tok_, c_class_str)\
    {\
	c_class *x484_ = (c_class_str);\
	(next_) = DEREF_str(x484_ + 0);\
	(len_) = DEREF_ulong(x484_ + 1);\
	(text_) = DEREF_string(x484_ + 2);\
	(kind_) = DEREF_unsigned(x484_ + 3);\
	(tok_) = DEREF_ulong(x484_ + 4);\
    }

#define DESTROY_str_simple(destroyer_, next_, len_, text_, kind_, tok_, c_class_str)\
    {\
	c_class *x485_ = (c_class_str);\
	(next_) = DEREF_str(x485_ + 0);\
	(len_) = DEREF_ulong(x485_ + 1);\
	(text_) = DEREF_string(x485_ + 2);\
	(kind_) = DEREF_unsigned(x485_ + 3);\
	(tok_) = DEREF_ulong(x485_ + 4);\
	(destroyer_)(x485_, (unsigned)5);\
    }


#endif
