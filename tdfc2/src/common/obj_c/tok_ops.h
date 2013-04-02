/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef TOK_OPS_H_INCLUDED
#define TOK_OPS_H_INCLUDED

/* Operations for union TOKEN */

#define TAG_tok(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for field exp of union TOKEN */

#define tok_exp_tag			((unsigned)0)
#define IS_tok_exp(P)			(CHECK_NULL(P)->ag_tag == 0)

#define tok_exp_type(P)			(CHECK_TAG((P), 0) + 1)
#define tok_exp_constant(P)		(CHECK_TAG((P), 0) + 2)
#define tok_exp_value(P)		(CHECK_TAG((P), 0) + 3)

#define MAKE_tok_exp(type_, constant_, value_, c_class_tok)\
    {\
	c_class *x817_ = GEN_c_class(4, TYPEID_tok);\
	x817_->ag_tag = 0;\
	COPY_type(x817_ + 1, (type_));\
	COPY_int(x817_ + 2, (constant_));\
	COPY_exp(x817_ + 3, (value_));\
	(c_class_tok) = x817_;\
    }

#define DECONS_tok_exp(type_, constant_, value_, c_class_tok)\
    {\
	c_class *x818_ = CHECK_TAG((c_class_tok), 0);\
	(type_) = DEREF_type(x818_ + 1);\
	(constant_) = DEREF_int(x818_ + 2);\
	(value_) = DEREF_exp(x818_ + 3);\
    }

#define DESTROY_tok_exp(destroyer_, type_, constant_, value_, c_class_tok)\
    {\
	c_class *x819_ = CHECK_TAG((c_class_tok), 0);\
	(type_) = DEREF_type(x819_ + 1);\
	(constant_) = DEREF_int(x819_ + 2);\
	(value_) = DEREF_exp(x819_ + 3);\
	(destroyer_)(x819_, (unsigned)4);\
    }


/* Operations for field stmt of union TOKEN */

#define tok_stmt_tag			((unsigned)1)
#define IS_tok_stmt(P)			(CHECK_NULL(P)->ag_tag == 1)

#define tok_stmt_value(P)		(CHECK_TAG((P), 1) + 1)

#define MAKE_tok_stmt(value_, c_class_tok)\
    {\
	c_class *x820_ = GEN_c_class(2, TYPEID_tok);\
	x820_->ag_tag = 1;\
	COPY_exp(x820_ + 1, (value_));\
	(c_class_tok) = x820_;\
    }

#define DECONS_tok_stmt(value_, c_class_tok)\
    {\
	c_class *x821_ = CHECK_TAG((c_class_tok), 1);\
	(value_) = DEREF_exp(x821_ + 1);\
    }

#define DESTROY_tok_stmt(destroyer_, value_, c_class_tok)\
    {\
	c_class *x822_ = CHECK_TAG((c_class_tok), 1);\
	(value_) = DEREF_exp(x822_ + 1);\
	(destroyer_)(x822_, (unsigned)2);\
    }


/* Operations for field set nat_etc of union TOKEN */

#define tok_nat_etc_tag			((unsigned)4)
#define IS_tok_nat_etc(P)		((unsigned)(CHECK_NULL(P)->ag_tag - 2) < (unsigned)2)

#define tok_nat_etc_value(P)		(CHECK_TAG_ETC((P), 2, 4) + 1)

#define MAKE_tok_nat_etc(tag, value_, c_class_tok)\
    {\
	c_class *x823_ = GEN_c_class(2, TYPEID_tok);\
	x823_->ag_tag = (tag);\
	COPY_nat(x823_ + 1, (value_));\
	(c_class_tok) = CHECK_TAG_ETC(x823_, 2, 4);\
    }

#define MODIFY_tok_nat_etc(tag, c_class_tok)\
    {\
	c_class *x824_ = CHECK_TAG_ETC ((c_class_tok), 2, 4);\
	x824_->ag_tag = (tag);\
	(void) CHECK_TAG_ETC (x824_, 2, 4);\
    }

#define DECONS_tok_nat_etc(value_, c_class_tok)\
    {\
	c_class *x825_ = CHECK_TAG_ETC((c_class_tok), 2, 4);\
	(value_) = DEREF_nat(x825_ + 1);\
    }

#define DESTROY_tok_nat_etc(destroyer_, value_, c_class_tok)\
    {\
	c_class *x826_ = CHECK_TAG_ETC((c_class_tok), 2, 4);\
	(value_) = DEREF_nat(x826_ + 1);\
	(destroyer_)(x826_, (unsigned)2);\
    }


/* Operations for field nat of union TOKEN */

#define tok_nat_tag			((unsigned)2)
#define IS_tok_nat(P)			(CHECK_NULL(P)->ag_tag == 2)

#define tok_nat_value(P)		(CHECK_TAG((P), 2) + 1)

#define MAKE_tok_nat(value_, c_class_tok)\
    {\
	c_class *x827_ = GEN_c_class(2, TYPEID_tok);\
	x827_->ag_tag = 2;\
	COPY_nat(x827_ + 1, (value_));\
	(c_class_tok) = x827_;\
    }

#define DECONS_tok_nat(value_, c_class_tok)\
    {\
	c_class *x828_ = CHECK_TAG((c_class_tok), 2);\
	(value_) = DEREF_nat(x828_ + 1);\
    }

#define DESTROY_tok_nat(destroyer_, value_, c_class_tok)\
    {\
	c_class *x829_ = CHECK_TAG((c_class_tok), 2);\
	(value_) = DEREF_nat(x829_ + 1);\
	(destroyer_)(x829_, (unsigned)2);\
    }


/* Operations for field snat of union TOKEN */

#define tok_snat_tag			((unsigned)3)
#define IS_tok_snat(P)			(CHECK_NULL(P)->ag_tag == 3)

#define tok_snat_value(P)		(CHECK_TAG((P), 3) + 1)

#define MAKE_tok_snat(value_, c_class_tok)\
    {\
	c_class *x830_ = GEN_c_class(2, TYPEID_tok);\
	x830_->ag_tag = 3;\
	COPY_nat(x830_ + 1, (value_));\
	(c_class_tok) = x830_;\
    }

#define DECONS_tok_snat(value_, c_class_tok)\
    {\
	c_class *x831_ = CHECK_TAG((c_class_tok), 3);\
	(value_) = DEREF_nat(x831_ + 1);\
    }

#define DESTROY_tok_snat(destroyer_, value_, c_class_tok)\
    {\
	c_class *x832_ = CHECK_TAG((c_class_tok), 3);\
	(value_) = DEREF_nat(x832_ + 1);\
	(destroyer_)(x832_, (unsigned)2);\
    }


/* Operations for field type of union TOKEN */

#define tok_type_tag			((unsigned)4)
#define IS_tok_type(P)			(CHECK_NULL(P)->ag_tag == 4)

#define tok_type_kind(P)		(CHECK_TAG((P), 4) + 1)
#define tok_type_value(P)		(CHECK_TAG((P), 4) + 2)
#define tok_type_alt(P)			(CHECK_TAG((P), 4) + 3)

#define MAKE_tok_type(kind_, value_, c_class_tok)\
    {\
	c_class *x833_ = GEN_c_class(4, TYPEID_tok);\
	x833_->ag_tag = 4;\
	COPY_btype(x833_ + 1, (kind_));\
	COPY_type(x833_ + 2, (value_));\
	COPY_type(x833_ + 3, NULL_type);\
	(c_class_tok) = x833_;\
    }

#define DECONS_tok_type(kind_, value_, alt_, c_class_tok)\
    {\
	c_class *x834_ = CHECK_TAG((c_class_tok), 4);\
	(kind_) = DEREF_btype(x834_ + 1);\
	(value_) = DEREF_type(x834_ + 2);\
	(alt_) = DEREF_type(x834_ + 3);\
    }

#define DESTROY_tok_type(destroyer_, kind_, value_, alt_, c_class_tok)\
    {\
	c_class *x835_ = CHECK_TAG((c_class_tok), 4);\
	(kind_) = DEREF_btype(x835_ + 1);\
	(value_) = DEREF_type(x835_ + 2);\
	(alt_) = DEREF_type(x835_ + 3);\
	(destroyer_)(x835_, (unsigned)4);\
    }


/* Operations for field func of union TOKEN */

#define tok_func_tag			((unsigned)5)
#define IS_tok_func(P)			(CHECK_NULL(P)->ag_tag == 5)

#define tok_func_type(P)		(CHECK_TAG((P), 5) + 1)
#define tok_func_defn(P)		(CHECK_TAG((P), 5) + 2)
#define tok_func_proc(P)		(CHECK_TAG((P), 5) + 3)

#define MAKE_tok_func(type_, c_class_tok)\
    {\
	c_class *x836_ = GEN_c_class(4, TYPEID_tok);\
	x836_->ag_tag = 5;\
	COPY_type(x836_ + 1, (type_));\
	COPY_id(x836_ + 2, NULL_id);\
	COPY_tok(x836_ + 3, NULL_tok);\
	(c_class_tok) = x836_;\
    }

#define DECONS_tok_func(type_, defn_, proc_, c_class_tok)\
    {\
	c_class *x837_ = CHECK_TAG((c_class_tok), 5);\
	(type_) = DEREF_type(x837_ + 1);\
	(defn_) = DEREF_id(x837_ + 2);\
	(proc_) = DEREF_tok(x837_ + 3);\
    }

#define DESTROY_tok_func(destroyer_, type_, defn_, proc_, c_class_tok)\
    {\
	c_class *x838_ = CHECK_TAG((c_class_tok), 5);\
	(type_) = DEREF_type(x838_ + 1);\
	(defn_) = DEREF_id(x838_ + 2);\
	(proc_) = DEREF_tok(x838_ + 3);\
	(destroyer_)(x838_, (unsigned)4);\
    }


/* Operations for field member of union TOKEN */

#define tok_member_tag			((unsigned)6)
#define IS_tok_member(P)		(CHECK_NULL(P)->ag_tag == 6)

#define tok_member_of(P)		(CHECK_TAG((P), 6) + 1)
#define tok_member_type(P)		(CHECK_TAG((P), 6) + 2)
#define tok_member_value(P)		(CHECK_TAG((P), 6) + 3)

#define MAKE_tok_member(of_, type_, value_, c_class_tok)\
    {\
	c_class *x839_ = GEN_c_class(4, TYPEID_tok);\
	x839_->ag_tag = 6;\
	COPY_type(x839_ + 1, (of_));\
	COPY_type(x839_ + 2, (type_));\
	COPY_off(x839_ + 3, (value_));\
	(c_class_tok) = x839_;\
    }

#define DECONS_tok_member(of_, type_, value_, c_class_tok)\
    {\
	c_class *x840_ = CHECK_TAG((c_class_tok), 6);\
	(of_) = DEREF_type(x840_ + 1);\
	(type_) = DEREF_type(x840_ + 2);\
	(value_) = DEREF_off(x840_ + 3);\
    }

#define DESTROY_tok_member(destroyer_, of_, type_, value_, c_class_tok)\
    {\
	c_class *x841_ = CHECK_TAG((c_class_tok), 6);\
	(of_) = DEREF_type(x841_ + 1);\
	(type_) = DEREF_type(x841_ + 2);\
	(value_) = DEREF_off(x841_ + 3);\
	(destroyer_)(x841_, (unsigned)4);\
    }


/* Operations for field class of union TOKEN */

#define tok_class_tag			((unsigned)7)
#define IS_tok_class(P)			(CHECK_NULL(P)->ag_tag == 7)

#define tok_class_type(P)		(CHECK_TAG((P), 7) + 1)
#define tok_class_value(P)		(CHECK_TAG((P), 7) + 2)
#define tok_class_alt(P)		(CHECK_TAG((P), 7) + 3)

#define MAKE_tok_class(type_, value_, c_class_tok)\
    {\
	c_class *x842_ = GEN_c_class(4, TYPEID_tok);\
	x842_->ag_tag = 7;\
	COPY_type(x842_ + 1, (type_));\
	COPY_id(x842_ + 2, (value_));\
	COPY_type(x842_ + 3, NULL_type);\
	(c_class_tok) = x842_;\
    }

#define DECONS_tok_class(type_, value_, alt_, c_class_tok)\
    {\
	c_class *x843_ = CHECK_TAG((c_class_tok), 7);\
	(type_) = DEREF_type(x843_ + 1);\
	(value_) = DEREF_id(x843_ + 2);\
	(alt_) = DEREF_type(x843_ + 3);\
    }

#define DESTROY_tok_class(destroyer_, type_, value_, alt_, c_class_tok)\
    {\
	c_class *x844_ = CHECK_TAG((c_class_tok), 7);\
	(type_) = DEREF_type(x844_ + 1);\
	(value_) = DEREF_id(x844_ + 2);\
	(alt_) = DEREF_type(x844_ + 3);\
	(destroyer_)(x844_, (unsigned)4);\
    }


/* Operations for field proc of union TOKEN */

#define tok_proc_tag			((unsigned)8)
#define IS_tok_proc(P)			(CHECK_NULL(P)->ag_tag == 8)

#define tok_proc_res(P)			(CHECK_TAG((P), 8) + 1)
#define tok_proc_pars(P)		(CHECK_TAG((P), 8) + 2)
#define tok_proc_key(P)			(CHECK_TAG((P), 8) + 3)
#define tok_proc_apps(P)		(CHECK_TAG((P), 8) + 4)
#define tok_proc_bids(P)		(CHECK_TAG((P), 8) + 5)
#define tok_proc_pids(P)		(CHECK_TAG((P), 8) + 6)

#define MAKE_tok_proc(res_, pars_, key_, c_class_tok)\
    {\
	c_class *x845_ = GEN_c_class(7, TYPEID_tok);\
	x845_->ag_tag = 8;\
	COPY_tok(x845_ + 1, (res_));\
	COPY_nspace(x845_ + 2, (pars_));\
	COPY_int(x845_ + 3, (key_));\
	COPY_inst(x845_ + 4, NULL_inst);\
	COPY_list(x845_ + 5, NULL_list ( IDENTIFIER ));\
	COPY_list(x845_ + 6, NULL_list ( IDENTIFIER ));\
	(c_class_tok) = x845_;\
    }

#define DECONS_tok_proc(res_, pars_, key_, apps_, bids_, pids_, c_class_tok)\
    {\
	c_class *x846_ = CHECK_TAG((c_class_tok), 8);\
	(res_) = DEREF_tok(x846_ + 1);\
	(pars_) = DEREF_nspace(x846_ + 2);\
	(key_) = DEREF_int(x846_ + 3);\
	(apps_) = DEREF_inst(x846_ + 4);\
	(bids_) = DEREF_list(x846_ + 5);\
	(pids_) = DEREF_list(x846_ + 6);\
    }

#define DESTROY_tok_proc(destroyer_, res_, pars_, key_, apps_, bids_, pids_, c_class_tok)\
    {\
	c_class *x847_ = CHECK_TAG((c_class_tok), 8);\
	(res_) = DEREF_tok(x847_ + 1);\
	(pars_) = DEREF_nspace(x847_ + 2);\
	(key_) = DEREF_int(x847_ + 3);\
	(apps_) = DEREF_inst(x847_ + 4);\
	(bids_) = DEREF_list(x847_ + 5);\
	(pids_) = DEREF_list(x847_ + 6);\
	(destroyer_)(x847_, (unsigned)7);\
    }


/* Operations for field templ of union TOKEN */

#define tok_templ_tag			((unsigned)9)
#define IS_tok_templ(P)			(CHECK_NULL(P)->ag_tag == 9)

#define tok_templ_usage(P)		(CHECK_TAG((P), 9) + 1)
#define tok_templ_pars(P)		(CHECK_TAG((P), 9) + 2)
#define tok_templ_apps(P)		(CHECK_TAG((P), 9) + 3)
#define tok_templ_pids(P)		(CHECK_TAG((P), 9) + 4)
#define tok_templ_dargs(P)		(CHECK_TAG((P), 9) + 5)

#define MAKE_tok_templ(usage_, pars_, c_class_tok)\
    {\
	c_class *x848_ = GEN_c_class(6, TYPEID_tok);\
	x848_->ag_tag = 9;\
	COPY_dspec(x848_ + 1, (usage_));\
	COPY_nspace(x848_ + 2, (pars_));\
	COPY_inst(x848_ + 3, NULL_inst);\
	COPY_list(x848_ + 4, NULL_list ( IDENTIFIER ));\
	COPY_list(x848_ + 5, NULL_list ( TOKEN ));\
	(c_class_tok) = x848_;\
    }

#define DECONS_tok_templ(usage_, pars_, apps_, pids_, dargs_, c_class_tok)\
    {\
	c_class *x849_ = CHECK_TAG((c_class_tok), 9);\
	(usage_) = DEREF_dspec(x849_ + 1);\
	(pars_) = DEREF_nspace(x849_ + 2);\
	(apps_) = DEREF_inst(x849_ + 3);\
	(pids_) = DEREF_list(x849_ + 4);\
	(dargs_) = DEREF_list(x849_ + 5);\
    }

#define DESTROY_tok_templ(destroyer_, usage_, pars_, apps_, pids_, dargs_, c_class_tok)\
    {\
	c_class *x850_ = CHECK_TAG((c_class_tok), 9);\
	(usage_) = DEREF_dspec(x850_ + 1);\
	(pars_) = DEREF_nspace(x850_ + 2);\
	(apps_) = DEREF_inst(x850_ + 3);\
	(pids_) = DEREF_list(x850_ + 4);\
	(dargs_) = DEREF_list(x850_ + 5);\
	(destroyer_)(x850_, (unsigned)6);\
    }


#endif
