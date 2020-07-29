/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef HASHID_OPS_H_INCLUDED
#define HASHID_OPS_H_INCLUDED

/* Operations for union HASHID */

#define TAG_hashid(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for component id of union HASHID */

#define hashid_id(P)			(CHECK_NULL(P) + 1)


/* Operations for component cache of union HASHID */

#define hashid_cache(P)			(CHECK_NULL(P) + 2)


/* Operations for component next of union HASHID */

#define hashid_next(P)			(CHECK_NULL(P) + 3)


/* Operations for component hash of union HASHID */

#define hashid_hash(P)			(CHECK_NULL(P) + 4)


/* Operations for field set name_etc of union HASHID */

#define hashid_name_etc_tag		((unsigned)2)
#define IS_hashid_name_etc(P)		((unsigned)(CHECK_NULL(P)->ag_tag - 0) < (unsigned)2)

#define hashid_name_etc_text(P)		(CHECK_TAG_ETC((P), 0, 2) + 5)

#define MAKE_hashid_name_etc(tag, next_, hash_, text_, c_class_hashid)\
    {\
	c_class *x288_ = GEN_c_class(6, TYPEID_hashid);\
	x288_->ag_tag = (tag);\
	COPY_id(x288_ + 1, NULL_id);\
	COPY_id(x288_ + 2, NULL_id);\
	COPY_hashid(x288_ + 3, (next_));\
	COPY_ulong(x288_ + 4, (hash_));\
	COPY_string(x288_ + 5, (text_));\
	(c_class_hashid) = CHECK_TAG_ETC(x288_, 0, 2);\
    }

#define MODIFY_hashid_name_etc(tag, c_class_hashid)\
    {\
	c_class *x289_ = CHECK_TAG_ETC ((c_class_hashid), 0, 2);\
	x289_->ag_tag = (tag);\
	(void) CHECK_TAG_ETC (x289_, 0, 2);\
    }

#define DECONS_hashid_name_etc(id_, cache_, next_, hash_, text_, c_class_hashid)\
    {\
	c_class *x290_ = CHECK_TAG_ETC((c_class_hashid), 0, 2);\
	(id_) = DEREF_id(x290_ + 1);\
	(cache_) = DEREF_id(x290_ + 2);\
	(next_) = DEREF_hashid(x290_ + 3);\
	(hash_) = DEREF_ulong(x290_ + 4);\
	(text_) = DEREF_string(x290_ + 5);\
    }

#define DESTROY_hashid_name_etc(destroyer_, id_, cache_, next_, hash_, text_, c_class_hashid)\
    {\
	c_class *x291_ = CHECK_TAG_ETC((c_class_hashid), 0, 2);\
	(id_) = DEREF_id(x291_ + 1);\
	(cache_) = DEREF_id(x291_ + 2);\
	(next_) = DEREF_hashid(x291_ + 3);\
	(hash_) = DEREF_ulong(x291_ + 4);\
	(text_) = DEREF_string(x291_ + 5);\
	(destroyer_)(x291_, (unsigned)6);\
    }


/* Operations for field name of union HASHID */

#define hashid_name_tag			((unsigned)0)
#define IS_hashid_name(P)		(CHECK_NULL(P)->ag_tag == 0)

#define hashid_name_text(P)		(CHECK_TAG((P), 0) + 5)

#define MAKE_hashid_name(next_, hash_, text_, c_class_hashid)\
    {\
	c_class *x292_ = GEN_c_class(6, TYPEID_hashid);\
	x292_->ag_tag = 0;\
	COPY_id(x292_ + 1, NULL_id);\
	COPY_id(x292_ + 2, NULL_id);\
	COPY_hashid(x292_ + 3, (next_));\
	COPY_ulong(x292_ + 4, (hash_));\
	COPY_string(x292_ + 5, (text_));\
	(c_class_hashid) = x292_;\
    }

#define DECONS_hashid_name(id_, cache_, next_, hash_, text_, c_class_hashid)\
    {\
	c_class *x293_ = CHECK_TAG((c_class_hashid), 0);\
	(id_) = DEREF_id(x293_ + 1);\
	(cache_) = DEREF_id(x293_ + 2);\
	(next_) = DEREF_hashid(x293_ + 3);\
	(hash_) = DEREF_ulong(x293_ + 4);\
	(text_) = DEREF_string(x293_ + 5);\
    }

#define DESTROY_hashid_name(destroyer_, id_, cache_, next_, hash_, text_, c_class_hashid)\
    {\
	c_class *x294_ = CHECK_TAG((c_class_hashid), 0);\
	(id_) = DEREF_id(x294_ + 1);\
	(cache_) = DEREF_id(x294_ + 2);\
	(next_) = DEREF_hashid(x294_ + 3);\
	(hash_) = DEREF_ulong(x294_ + 4);\
	(text_) = DEREF_string(x294_ + 5);\
	(destroyer_)(x294_, (unsigned)6);\
    }


/* Operations for field ename of union HASHID */

#define hashid_ename_tag		((unsigned)1)
#define IS_hashid_ename(P)		(CHECK_NULL(P)->ag_tag == 1)

#define hashid_ename_text(P)		(CHECK_TAG((P), 1) + 5)

#define MAKE_hashid_ename(next_, hash_, text_, c_class_hashid)\
    {\
	c_class *x295_ = GEN_c_class(6, TYPEID_hashid);\
	x295_->ag_tag = 1;\
	COPY_id(x295_ + 1, NULL_id);\
	COPY_id(x295_ + 2, NULL_id);\
	COPY_hashid(x295_ + 3, (next_));\
	COPY_ulong(x295_ + 4, (hash_));\
	COPY_string(x295_ + 5, (text_));\
	(c_class_hashid) = x295_;\
    }

#define DECONS_hashid_ename(id_, cache_, next_, hash_, text_, c_class_hashid)\
    {\
	c_class *x296_ = CHECK_TAG((c_class_hashid), 1);\
	(id_) = DEREF_id(x296_ + 1);\
	(cache_) = DEREF_id(x296_ + 2);\
	(next_) = DEREF_hashid(x296_ + 3);\
	(hash_) = DEREF_ulong(x296_ + 4);\
	(text_) = DEREF_string(x296_ + 5);\
    }

#define DESTROY_hashid_ename(destroyer_, id_, cache_, next_, hash_, text_, c_class_hashid)\
    {\
	c_class *x297_ = CHECK_TAG((c_class_hashid), 1);\
	(id_) = DEREF_id(x297_ + 1);\
	(cache_) = DEREF_id(x297_ + 2);\
	(next_) = DEREF_hashid(x297_ + 3);\
	(hash_) = DEREF_ulong(x297_ + 4);\
	(text_) = DEREF_string(x297_ + 5);\
	(destroyer_)(x297_, (unsigned)6);\
    }


/* Operations for field set constr_etc of union HASHID */

#define hashid_constr_etc_tag		((unsigned)5)
#define IS_hashid_constr_etc(P)		((unsigned)(CHECK_NULL(P)->ag_tag - 2) < (unsigned)3)

#define hashid_constr_etc_type(P)	(CHECK_TAG_ETC((P), 2, 5) + 5)
#define hashid_constr_etc_tid(P)	(CHECK_TAG_ETC((P), 2, 5) + 6)

#define MAKE_hashid_constr_etc(tag, next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x298_ = GEN_c_class(7, TYPEID_hashid);\
	x298_->ag_tag = (tag);\
	COPY_id(x298_ + 1, NULL_id);\
	COPY_id(x298_ + 2, NULL_id);\
	COPY_hashid(x298_ + 3, (next_));\
	COPY_ulong(x298_ + 4, (hash_));\
	COPY_type(x298_ + 5, (type_));\
	COPY_id(x298_ + 6, (tid_));\
	(c_class_hashid) = CHECK_TAG_ETC(x298_, 2, 5);\
    }

#define MODIFY_hashid_constr_etc(tag, c_class_hashid)\
    {\
	c_class *x299_ = CHECK_TAG_ETC ((c_class_hashid), 2, 5);\
	x299_->ag_tag = (tag);\
	(void) CHECK_TAG_ETC (x299_, 2, 5);\
    }

#define DECONS_hashid_constr_etc(id_, cache_, next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x300_ = CHECK_TAG_ETC((c_class_hashid), 2, 5);\
	(id_) = DEREF_id(x300_ + 1);\
	(cache_) = DEREF_id(x300_ + 2);\
	(next_) = DEREF_hashid(x300_ + 3);\
	(hash_) = DEREF_ulong(x300_ + 4);\
	(type_) = DEREF_type(x300_ + 5);\
	(tid_) = DEREF_id(x300_ + 6);\
    }

#define DESTROY_hashid_constr_etc(destroyer_, id_, cache_, next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x301_ = CHECK_TAG_ETC((c_class_hashid), 2, 5);\
	(id_) = DEREF_id(x301_ + 1);\
	(cache_) = DEREF_id(x301_ + 2);\
	(next_) = DEREF_hashid(x301_ + 3);\
	(hash_) = DEREF_ulong(x301_ + 4);\
	(type_) = DEREF_type(x301_ + 5);\
	(tid_) = DEREF_id(x301_ + 6);\
	(destroyer_)(x301_, (unsigned)7);\
    }


/* Operations for field constr of union HASHID */

#define hashid_constr_tag		((unsigned)2)
#define IS_hashid_constr(P)		(CHECK_NULL(P)->ag_tag == 2)

#define hashid_constr_type(P)		(CHECK_TAG((P), 2) + 5)
#define hashid_constr_tid(P)		(CHECK_TAG((P), 2) + 6)

#define MAKE_hashid_constr(next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x302_ = GEN_c_class(7, TYPEID_hashid);\
	x302_->ag_tag = 2;\
	COPY_id(x302_ + 1, NULL_id);\
	COPY_id(x302_ + 2, NULL_id);\
	COPY_hashid(x302_ + 3, (next_));\
	COPY_ulong(x302_ + 4, (hash_));\
	COPY_type(x302_ + 5, (type_));\
	COPY_id(x302_ + 6, (tid_));\
	(c_class_hashid) = x302_;\
    }

#define DECONS_hashid_constr(id_, cache_, next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x303_ = CHECK_TAG((c_class_hashid), 2);\
	(id_) = DEREF_id(x303_ + 1);\
	(cache_) = DEREF_id(x303_ + 2);\
	(next_) = DEREF_hashid(x303_ + 3);\
	(hash_) = DEREF_ulong(x303_ + 4);\
	(type_) = DEREF_type(x303_ + 5);\
	(tid_) = DEREF_id(x303_ + 6);\
    }

#define DESTROY_hashid_constr(destroyer_, id_, cache_, next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x304_ = CHECK_TAG((c_class_hashid), 2);\
	(id_) = DEREF_id(x304_ + 1);\
	(cache_) = DEREF_id(x304_ + 2);\
	(next_) = DEREF_hashid(x304_ + 3);\
	(hash_) = DEREF_ulong(x304_ + 4);\
	(type_) = DEREF_type(x304_ + 5);\
	(tid_) = DEREF_id(x304_ + 6);\
	(destroyer_)(x304_, (unsigned)7);\
    }


/* Operations for field destr of union HASHID */

#define hashid_destr_tag		((unsigned)3)
#define IS_hashid_destr(P)		(CHECK_NULL(P)->ag_tag == 3)

#define hashid_destr_type(P)		(CHECK_TAG((P), 3) + 5)
#define hashid_destr_tid(P)		(CHECK_TAG((P), 3) + 6)

#define MAKE_hashid_destr(next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x305_ = GEN_c_class(7, TYPEID_hashid);\
	x305_->ag_tag = 3;\
	COPY_id(x305_ + 1, NULL_id);\
	COPY_id(x305_ + 2, NULL_id);\
	COPY_hashid(x305_ + 3, (next_));\
	COPY_ulong(x305_ + 4, (hash_));\
	COPY_type(x305_ + 5, (type_));\
	COPY_id(x305_ + 6, (tid_));\
	(c_class_hashid) = x305_;\
    }

#define DECONS_hashid_destr(id_, cache_, next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x306_ = CHECK_TAG((c_class_hashid), 3);\
	(id_) = DEREF_id(x306_ + 1);\
	(cache_) = DEREF_id(x306_ + 2);\
	(next_) = DEREF_hashid(x306_ + 3);\
	(hash_) = DEREF_ulong(x306_ + 4);\
	(type_) = DEREF_type(x306_ + 5);\
	(tid_) = DEREF_id(x306_ + 6);\
    }

#define DESTROY_hashid_destr(destroyer_, id_, cache_, next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x307_ = CHECK_TAG((c_class_hashid), 3);\
	(id_) = DEREF_id(x307_ + 1);\
	(cache_) = DEREF_id(x307_ + 2);\
	(next_) = DEREF_hashid(x307_ + 3);\
	(hash_) = DEREF_ulong(x307_ + 4);\
	(type_) = DEREF_type(x307_ + 5);\
	(tid_) = DEREF_id(x307_ + 6);\
	(destroyer_)(x307_, (unsigned)7);\
    }


/* Operations for field conv of union HASHID */

#define hashid_conv_tag			((unsigned)4)
#define IS_hashid_conv(P)		(CHECK_NULL(P)->ag_tag == 4)

#define hashid_conv_type(P)		(CHECK_TAG((P), 4) + 5)
#define hashid_conv_tid(P)		(CHECK_TAG((P), 4) + 6)

#define MAKE_hashid_conv(next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x308_ = GEN_c_class(7, TYPEID_hashid);\
	x308_->ag_tag = 4;\
	COPY_id(x308_ + 1, NULL_id);\
	COPY_id(x308_ + 2, NULL_id);\
	COPY_hashid(x308_ + 3, (next_));\
	COPY_ulong(x308_ + 4, (hash_));\
	COPY_type(x308_ + 5, (type_));\
	COPY_id(x308_ + 6, (tid_));\
	(c_class_hashid) = x308_;\
    }

#define DECONS_hashid_conv(id_, cache_, next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x309_ = CHECK_TAG((c_class_hashid), 4);\
	(id_) = DEREF_id(x309_ + 1);\
	(cache_) = DEREF_id(x309_ + 2);\
	(next_) = DEREF_hashid(x309_ + 3);\
	(hash_) = DEREF_ulong(x309_ + 4);\
	(type_) = DEREF_type(x309_ + 5);\
	(tid_) = DEREF_id(x309_ + 6);\
    }

#define DESTROY_hashid_conv(destroyer_, id_, cache_, next_, hash_, type_, tid_, c_class_hashid)\
    {\
	c_class *x310_ = CHECK_TAG((c_class_hashid), 4);\
	(id_) = DEREF_id(x310_ + 1);\
	(cache_) = DEREF_id(x310_ + 2);\
	(next_) = DEREF_hashid(x310_ + 3);\
	(hash_) = DEREF_ulong(x310_ + 4);\
	(type_) = DEREF_type(x310_ + 5);\
	(tid_) = DEREF_id(x310_ + 6);\
	(destroyer_)(x310_, (unsigned)7);\
    }


/* Operations for field op of union HASHID */

#define hashid_op_tag			((unsigned)5)
#define IS_hashid_op(P)			(CHECK_NULL(P)->ag_tag == 5)

#define hashid_op_lex(P)		(CHECK_TAG((P), 5) + 5)

#define MAKE_hashid_op(next_, hash_, lex_, c_class_hashid)\
    {\
	c_class *x311_ = GEN_c_class(6, TYPEID_hashid);\
	x311_->ag_tag = 5;\
	COPY_id(x311_ + 1, NULL_id);\
	COPY_id(x311_ + 2, NULL_id);\
	COPY_hashid(x311_ + 3, (next_));\
	COPY_ulong(x311_ + 4, (hash_));\
	COPY_int(x311_ + 5, (lex_));\
	(c_class_hashid) = x311_;\
    }

#define DECONS_hashid_op(id_, cache_, next_, hash_, lex_, c_class_hashid)\
    {\
	c_class *x312_ = CHECK_TAG((c_class_hashid), 5);\
	(id_) = DEREF_id(x312_ + 1);\
	(cache_) = DEREF_id(x312_ + 2);\
	(next_) = DEREF_hashid(x312_ + 3);\
	(hash_) = DEREF_ulong(x312_ + 4);\
	(lex_) = DEREF_int(x312_ + 5);\
    }

#define DESTROY_hashid_op(destroyer_, id_, cache_, next_, hash_, lex_, c_class_hashid)\
    {\
	c_class *x313_ = CHECK_TAG((c_class_hashid), 5);\
	(id_) = DEREF_id(x313_ + 1);\
	(cache_) = DEREF_id(x313_ + 2);\
	(next_) = DEREF_hashid(x313_ + 3);\
	(hash_) = DEREF_ulong(x313_ + 4);\
	(lex_) = DEREF_int(x313_ + 5);\
	(destroyer_)(x313_, (unsigned)6);\
    }


/* Operations for field anon of union HASHID */

#define hashid_anon_tag			((unsigned)6)
#define IS_hashid_anon(P)		(CHECK_NULL(P)->ag_tag == 6)

#define hashid_anon_uniq(P)		(CHECK_TAG((P), 6) + 5)

#define MAKE_hashid_anon(next_, hash_, uniq_, c_class_hashid)\
    {\
	c_class *x314_ = GEN_c_class(6, TYPEID_hashid);\
	x314_->ag_tag = 6;\
	COPY_id(x314_ + 1, NULL_id);\
	COPY_id(x314_ + 2, NULL_id);\
	COPY_hashid(x314_ + 3, (next_));\
	COPY_ulong(x314_ + 4, (hash_));\
	COPY_ulong(x314_ + 5, (uniq_));\
	(c_class_hashid) = x314_;\
    }

#define DECONS_hashid_anon(id_, cache_, next_, hash_, uniq_, c_class_hashid)\
    {\
	c_class *x315_ = CHECK_TAG((c_class_hashid), 6);\
	(id_) = DEREF_id(x315_ + 1);\
	(cache_) = DEREF_id(x315_ + 2);\
	(next_) = DEREF_hashid(x315_ + 3);\
	(hash_) = DEREF_ulong(x315_ + 4);\
	(uniq_) = DEREF_ulong(x315_ + 5);\
    }

#define DESTROY_hashid_anon(destroyer_, id_, cache_, next_, hash_, uniq_, c_class_hashid)\
    {\
	c_class *x316_ = CHECK_TAG((c_class_hashid), 6);\
	(id_) = DEREF_id(x316_ + 1);\
	(cache_) = DEREF_id(x316_ + 2);\
	(next_) = DEREF_hashid(x316_ + 3);\
	(hash_) = DEREF_ulong(x316_ + 4);\
	(uniq_) = DEREF_ulong(x316_ + 5);\
	(destroyer_)(x316_, (unsigned)6);\
    }


#endif
