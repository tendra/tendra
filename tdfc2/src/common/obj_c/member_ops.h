/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef MEMBER_OPS_H_INCLUDED
#define MEMBER_OPS_H_INCLUDED

/* Operations for union MEMBER */

#define TAG_member(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for component id of union MEMBER */

#define member_id(P)			(CHECK_NULL(P) + 1)


/* Operations for component alt of union MEMBER */

#define member_alt(P)			(CHECK_NULL(P) + 2)


/* Operations for component next of union MEMBER */

#define member_next(P)			(CHECK_NULL(P) + 3)


/* Operations for field small of union MEMBER */

#define member_small_tag		((unsigned)0)
#define IS_member_small(P)		(CHECK_NULL(P)->ag_tag == 0)


#define MAKE_member_small(next_, c_class_member)\
    {\
	c_class *x424_ = GEN_c_class(4, TYPEID_member);\
	x424_->ag_tag = 0;\
	COPY_id(x424_ + 1, NULL_id);\
	COPY_id(x424_ + 2, NULL_id);\
	COPY_member(x424_ + 3, (next_));\
	(c_class_member) = x424_;\
    }

#define DECONS_member_small(id_, alt_, next_, c_class_member)\
    {\
	c_class *x425_ = CHECK_TAG((c_class_member), 0);\
	(id_) = DEREF_id(x425_ + 1);\
	(alt_) = DEREF_id(x425_ + 2);\
	(next_) = DEREF_member(x425_ + 3);\
    }

#define DESTROY_member_small(destroyer_, id_, alt_, next_, c_class_member)\
    {\
	c_class *x426_ = CHECK_TAG((c_class_member), 0);\
	(id_) = DEREF_id(x426_ + 1);\
	(alt_) = DEREF_id(x426_ + 2);\
	(next_) = DEREF_member(x426_ + 3);\
	(destroyer_)(x426_, (unsigned)4);\
    }


/* Operations for field large of union MEMBER */

#define member_large_tag		((unsigned)1)
#define IS_member_large(P)		(CHECK_NULL(P)->ag_tag == 1)

#define member_large_tnext(P)		(CHECK_TAG((P), 1) + 4)

#define MAKE_member_large(next_, tnext_, c_class_member)\
    {\
	c_class *x427_ = GEN_c_class(5, TYPEID_member);\
	x427_->ag_tag = 1;\
	COPY_id(x427_ + 1, NULL_id);\
	COPY_id(x427_ + 2, NULL_id);\
	COPY_member(x427_ + 3, (next_));\
	COPY_member(x427_ + 4, (tnext_));\
	(c_class_member) = x427_;\
    }

#define DECONS_member_large(id_, alt_, next_, tnext_, c_class_member)\
    {\
	c_class *x428_ = CHECK_TAG((c_class_member), 1);\
	(id_) = DEREF_id(x428_ + 1);\
	(alt_) = DEREF_id(x428_ + 2);\
	(next_) = DEREF_member(x428_ + 3);\
	(tnext_) = DEREF_member(x428_ + 4);\
    }

#define DESTROY_member_large(destroyer_, id_, alt_, next_, tnext_, c_class_member)\
    {\
	c_class *x429_ = CHECK_TAG((c_class_member), 1);\
	(id_) = DEREF_id(x429_ + 1);\
	(alt_) = DEREF_id(x429_ + 2);\
	(next_) = DEREF_member(x429_ + 3);\
	(tnext_) = DEREF_member(x429_ + 4);\
	(destroyer_)(x429_, (unsigned)5);\
    }


#endif
