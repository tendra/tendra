/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef VIRT_OPS_H_INCLUDED
#define VIRT_OPS_H_INCLUDED

/* Operations for union VIRTUAL */

#define TAG_virt(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for component func of union VIRTUAL */

#define virt_func(P)			(CHECK_NULL(P) + 1)


/* Operations for component no of union VIRTUAL */

#define virt_no(P)			(CHECK_NULL(P) + 2)


/* Operations for component base of union VIRTUAL */

#define virt_base(P)			(CHECK_NULL(P) + 3)


/* Operations for component next of union VIRTUAL */

#define virt_next(P)			(CHECK_NULL(P) + 4)


/* Operations for field table of union VIRTUAL */

#define virt_table_tag			((unsigned)0)
#define IS_virt_table(P)		(CHECK_NULL(P)->ag_tag == 0)

#define virt_table_off(P)		(CHECK_TAG((P), 0) + 5)
#define virt_table_entries(P)		(CHECK_TAG((P), 0) + 6)
#define virt_table_tok(P)		(CHECK_TAG((P), 0) + 7)
#define virt_table_tbl(P)		(CHECK_TAG((P), 0) + 8)
#define virt_table_rtti(P)		(CHECK_TAG((P), 0) + 9)
#define virt_table_rtti_used(P)		(CHECK_TAG((P), 0) + 10)

#define MAKE_virt_table(func_, no_, base_, off_, c_class_virt)\
    {\
	c_class *x205_ = GEN_c_class(11, TYPEID_virt);\
	x205_->ag_tag = 0;\
	COPY_id(x205_ + 1, (func_));\
	COPY_ulong(x205_ + 2, (no_));\
	COPY_graph(x205_ + 3, (base_));\
	COPY_virt(x205_ + 4, NULL_virt);\
	COPY_off(x205_ + 5, (off_));\
	COPY_list(x205_ + 6, NULL_list ( VIRTUAL ));\
	COPY_ulong(x205_ + 7, LINK_NONE);\
	COPY_ulong(x205_ + 8, LINK_NONE);\
	COPY_ulong(x205_ + 9, LINK_NONE);\
	COPY_int(x205_ + 10, 0);\
	(c_class_virt) = x205_;\
    }

#define DECONS_virt_table(func_, no_, base_, next_, off_, entries_, tok_, tbl_, rtti_, rtti_used_, c_class_virt)\
    {\
	c_class *x206_ = CHECK_TAG((c_class_virt), 0);\
	(func_) = DEREF_id(x206_ + 1);\
	(no_) = DEREF_ulong(x206_ + 2);\
	(base_) = DEREF_graph(x206_ + 3);\
	(next_) = DEREF_virt(x206_ + 4);\
	(off_) = DEREF_off(x206_ + 5);\
	(entries_) = DEREF_list(x206_ + 6);\
	(tok_) = DEREF_ulong(x206_ + 7);\
	(tbl_) = DEREF_ulong(x206_ + 8);\
	(rtti_) = DEREF_ulong(x206_ + 9);\
	(rtti_used_) = DEREF_int(x206_ + 10);\
    }

#define DESTROY_virt_table(destroyer_, func_, no_, base_, next_, off_, entries_, tok_, tbl_, rtti_, rtti_used_, c_class_virt)\
    {\
	c_class *x207_ = CHECK_TAG((c_class_virt), 0);\
	(func_) = DEREF_id(x207_ + 1);\
	(no_) = DEREF_ulong(x207_ + 2);\
	(base_) = DEREF_graph(x207_ + 3);\
	(next_) = DEREF_virt(x207_ + 4);\
	(off_) = DEREF_off(x207_ + 5);\
	(entries_) = DEREF_list(x207_ + 6);\
	(tok_) = DEREF_ulong(x207_ + 7);\
	(tbl_) = DEREF_ulong(x207_ + 8);\
	(rtti_) = DEREF_ulong(x207_ + 9);\
	(rtti_used_) = DEREF_int(x207_ + 10);\
	(destroyer_)(x207_, (unsigned)11);\
    }


/* Operations for field simple of union VIRTUAL */

#define virt_simple_tag			((unsigned)1)
#define IS_virt_simple(P)		(CHECK_NULL(P)->ag_tag == 1)


#define MAKE_virt_simple(func_, no_, base_, c_class_virt)\
    {\
	c_class *x208_ = GEN_c_class(5, TYPEID_virt);\
	x208_->ag_tag = 1;\
	COPY_id(x208_ + 1, (func_));\
	COPY_ulong(x208_ + 2, (no_));\
	COPY_graph(x208_ + 3, (base_));\
	COPY_virt(x208_ + 4, NULL_virt);\
	(c_class_virt) = x208_;\
    }

#define DECONS_virt_simple(func_, no_, base_, next_, c_class_virt)\
    {\
	c_class *x209_ = CHECK_TAG((c_class_virt), 1);\
	(func_) = DEREF_id(x209_ + 1);\
	(no_) = DEREF_ulong(x209_ + 2);\
	(base_) = DEREF_graph(x209_ + 3);\
	(next_) = DEREF_virt(x209_ + 4);\
    }

#define DESTROY_virt_simple(destroyer_, func_, no_, base_, next_, c_class_virt)\
    {\
	c_class *x210_ = CHECK_TAG((c_class_virt), 1);\
	(func_) = DEREF_id(x210_ + 1);\
	(no_) = DEREF_ulong(x210_ + 2);\
	(base_) = DEREF_graph(x210_ + 3);\
	(next_) = DEREF_virt(x210_ + 4);\
	(destroyer_)(x210_, (unsigned)5);\
    }


/* Operations for field override of union VIRTUAL */

#define virt_override_tag		((unsigned)2)
#define IS_virt_override(P)		(CHECK_NULL(P)->ag_tag == 2)

#define virt_override_ret(P)		(CHECK_TAG((P), 2) + 5)
#define virt_override_orig(P)		(CHECK_TAG((P), 2) + 6)
#define virt_override_src(P)		(CHECK_TAG((P), 2) + 7)

#define MAKE_virt_override(func_, no_, base_, ret_, orig_, src_, c_class_virt)\
    {\
	c_class *x211_ = GEN_c_class(8, TYPEID_virt);\
	x211_->ag_tag = 2;\
	COPY_id(x211_ + 1, (func_));\
	COPY_ulong(x211_ + 2, (no_));\
	COPY_graph(x211_ + 3, (base_));\
	COPY_virt(x211_ + 4, NULL_virt);\
	COPY_graph(x211_ + 5, (ret_));\
	COPY_id(x211_ + 6, (orig_));\
	COPY_graph(x211_ + 7, (src_));\
	(c_class_virt) = x211_;\
    }

#define DECONS_virt_override(func_, no_, base_, next_, ret_, orig_, src_, c_class_virt)\
    {\
	c_class *x212_ = CHECK_TAG((c_class_virt), 2);\
	(func_) = DEREF_id(x212_ + 1);\
	(no_) = DEREF_ulong(x212_ + 2);\
	(base_) = DEREF_graph(x212_ + 3);\
	(next_) = DEREF_virt(x212_ + 4);\
	(ret_) = DEREF_graph(x212_ + 5);\
	(orig_) = DEREF_id(x212_ + 6);\
	(src_) = DEREF_graph(x212_ + 7);\
    }

#define DESTROY_virt_override(destroyer_, func_, no_, base_, next_, ret_, orig_, src_, c_class_virt)\
    {\
	c_class *x213_ = CHECK_TAG((c_class_virt), 2);\
	(func_) = DEREF_id(x213_ + 1);\
	(no_) = DEREF_ulong(x213_ + 2);\
	(base_) = DEREF_graph(x213_ + 3);\
	(next_) = DEREF_virt(x213_ + 4);\
	(ret_) = DEREF_graph(x213_ + 5);\
	(orig_) = DEREF_id(x213_ + 6);\
	(src_) = DEREF_graph(x213_ + 7);\
	(destroyer_)(x213_, (unsigned)8);\
    }


/* Operations for field inherit of union VIRTUAL */

#define virt_inherit_tag		((unsigned)3)
#define IS_virt_inherit(P)		(CHECK_NULL(P)->ag_tag == 3)


#define MAKE_virt_inherit(func_, no_, base_, c_class_virt)\
    {\
	c_class *x214_ = GEN_c_class(5, TYPEID_virt);\
	x214_->ag_tag = 3;\
	COPY_id(x214_ + 1, (func_));\
	COPY_ulong(x214_ + 2, (no_));\
	COPY_graph(x214_ + 3, (base_));\
	COPY_virt(x214_ + 4, NULL_virt);\
	(c_class_virt) = x214_;\
    }

#define DECONS_virt_inherit(func_, no_, base_, next_, c_class_virt)\
    {\
	c_class *x215_ = CHECK_TAG((c_class_virt), 3);\
	(func_) = DEREF_id(x215_ + 1);\
	(no_) = DEREF_ulong(x215_ + 2);\
	(base_) = DEREF_graph(x215_ + 3);\
	(next_) = DEREF_virt(x215_ + 4);\
    }

#define DESTROY_virt_inherit(destroyer_, func_, no_, base_, next_, c_class_virt)\
    {\
	c_class *x216_ = CHECK_TAG((c_class_virt), 3);\
	(func_) = DEREF_id(x216_ + 1);\
	(no_) = DEREF_ulong(x216_ + 2);\
	(base_) = DEREF_graph(x216_ + 3);\
	(next_) = DEREF_virt(x216_ + 4);\
	(destroyer_)(x216_, (unsigned)5);\
    }


/* Operations for field complex of union VIRTUAL */

#define virt_complex_tag		((unsigned)4)
#define IS_virt_complex(P)		(CHECK_NULL(P)->ag_tag == 4)

#define virt_complex_ret(P)		(CHECK_TAG((P), 4) + 5)
#define virt_complex_orig(P)		(CHECK_TAG((P), 4) + 6)
#define virt_complex_src(P)		(CHECK_TAG((P), 4) + 7)

#define MAKE_virt_complex(func_, no_, base_, ret_, orig_, src_, c_class_virt)\
    {\
	c_class *x217_ = GEN_c_class(8, TYPEID_virt);\
	x217_->ag_tag = 4;\
	COPY_id(x217_ + 1, (func_));\
	COPY_ulong(x217_ + 2, (no_));\
	COPY_graph(x217_ + 3, (base_));\
	COPY_virt(x217_ + 4, NULL_virt);\
	COPY_graph(x217_ + 5, (ret_));\
	COPY_id(x217_ + 6, (orig_));\
	COPY_graph(x217_ + 7, (src_));\
	(c_class_virt) = x217_;\
    }

#define DECONS_virt_complex(func_, no_, base_, next_, ret_, orig_, src_, c_class_virt)\
    {\
	c_class *x218_ = CHECK_TAG((c_class_virt), 4);\
	(func_) = DEREF_id(x218_ + 1);\
	(no_) = DEREF_ulong(x218_ + 2);\
	(base_) = DEREF_graph(x218_ + 3);\
	(next_) = DEREF_virt(x218_ + 4);\
	(ret_) = DEREF_graph(x218_ + 5);\
	(orig_) = DEREF_id(x218_ + 6);\
	(src_) = DEREF_graph(x218_ + 7);\
    }

#define DESTROY_virt_complex(destroyer_, func_, no_, base_, next_, ret_, orig_, src_, c_class_virt)\
    {\
	c_class *x219_ = CHECK_TAG((c_class_virt), 4);\
	(func_) = DEREF_id(x219_ + 1);\
	(no_) = DEREF_ulong(x219_ + 2);\
	(base_) = DEREF_graph(x219_ + 3);\
	(next_) = DEREF_virt(x219_ + 4);\
	(ret_) = DEREF_graph(x219_ + 5);\
	(orig_) = DEREF_id(x219_ + 6);\
	(src_) = DEREF_graph(x219_ + 7);\
	(destroyer_)(x219_, (unsigned)8);\
    }


/* Operations for field link of union VIRTUAL */

#define virt_link_tag			((unsigned)5)
#define IS_virt_link(P)			(CHECK_NULL(P)->ag_tag == 5)

#define virt_link_to(P)			(CHECK_TAG((P), 5) + 5)

#define MAKE_virt_link(func_, no_, base_, to_, c_class_virt)\
    {\
	c_class *x220_ = GEN_c_class(6, TYPEID_virt);\
	x220_->ag_tag = 5;\
	COPY_id(x220_ + 1, (func_));\
	COPY_ulong(x220_ + 2, (no_));\
	COPY_graph(x220_ + 3, (base_));\
	COPY_virt(x220_ + 4, NULL_virt);\
	COPY_ptr(x220_ + 5, (to_));\
	(c_class_virt) = x220_;\
    }

#define DECONS_virt_link(func_, no_, base_, next_, to_, c_class_virt)\
    {\
	c_class *x221_ = CHECK_TAG((c_class_virt), 5);\
	(func_) = DEREF_id(x221_ + 1);\
	(no_) = DEREF_ulong(x221_ + 2);\
	(base_) = DEREF_graph(x221_ + 3);\
	(next_) = DEREF_virt(x221_ + 4);\
	(to_) = DEREF_ptr(x221_ + 5);\
    }

#define DESTROY_virt_link(destroyer_, func_, no_, base_, next_, to_, c_class_virt)\
    {\
	c_class *x222_ = CHECK_TAG((c_class_virt), 5);\
	(func_) = DEREF_id(x222_ + 1);\
	(no_) = DEREF_ulong(x222_ + 2);\
	(base_) = DEREF_graph(x222_ + 3);\
	(next_) = DEREF_virt(x222_ + 4);\
	(to_) = DEREF_ptr(x222_ + 5);\
	(destroyer_)(x222_, (unsigned)6);\
    }


#endif
