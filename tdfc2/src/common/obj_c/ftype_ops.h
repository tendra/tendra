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

#ifndef FTYPE_OPS_H_INCLUDED
#define FTYPE_OPS_H_INCLUDED

/* Operations for union FLOAT_TYPE */

#define TAG_ftype(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for component arg_prom of union FLOAT_TYPE */

#define ftype_arg_prom(P)		(CHECK_NULL(P) + 1)


/* Operations for component ftok of union FLOAT_TYPE */

#define ftype_ftok(P)			(CHECK_NULL(P) + 2)


/* Operations for component ntok of union FLOAT_TYPE */

#define ftype_ntok(P)			(CHECK_NULL(P) + 3)


/* Operations for component diag of union FLOAT_TYPE */

#define ftype_diag(P)			(CHECK_NULL(P) + 4)


/* Operations for component small of union FLOAT_TYPE */

#define ftype_small(P)			(CHECK_NULL(P) + 5)


/* Operations for field basic of union FLOAT_TYPE */

#define ftype_basic_tag			((unsigned)0)
#define IS_ftype_basic(P)		(CHECK_NULL(P)->ag_tag == 0)

#define ftype_basic_rep(P)		(CHECK_TAG((P), 0) + 6)
#define ftype_basic_no(P)		(CHECK_TAG((P), 0) + 7)

#define MAKE_ftype_basic(arg_prom_, rep_, no_, c_class_ftype)\
    {\
	c_class *x187_ = GEN_c_class(8, TYPEID_ftype);\
	x187_->ag_tag = 0;\
	COPY_type(x187_ + 1, (arg_prom_));\
	COPY_ulong(x187_ + 2, LINK_NONE);\
	COPY_ulong(x187_ + 3, LINK_NONE);\
	COPY_ulong(x187_ + 4, LINK_NONE);\
	COPY_list(x187_ + 5, NULL_list ( FLOAT ));\
	COPY_btype(x187_ + 6, (rep_));\
	COPY_ntype(x187_ + 7, (no_));\
	(c_class_ftype) = x187_;\
    }

#define DECONS_ftype_basic(arg_prom_, ftok_, ntok_, diag_, small_, rep_, no_, c_class_ftype)\
    {\
	c_class *x188_ = CHECK_TAG((c_class_ftype), 0);\
	(arg_prom_) = DEREF_type(x188_ + 1);\
	(ftok_) = DEREF_ulong(x188_ + 2);\
	(ntok_) = DEREF_ulong(x188_ + 3);\
	(diag_) = DEREF_ulong(x188_ + 4);\
	(small_) = DEREF_list(x188_ + 5);\
	(rep_) = DEREF_btype(x188_ + 6);\
	(no_) = DEREF_ntype(x188_ + 7);\
    }

#define DESTROY_ftype_basic(destroyer_, arg_prom_, ftok_, ntok_, diag_, small_, rep_, no_, c_class_ftype)\
    {\
	c_class *x189_ = CHECK_TAG((c_class_ftype), 0);\
	(arg_prom_) = DEREF_type(x189_ + 1);\
	(ftok_) = DEREF_ulong(x189_ + 2);\
	(ntok_) = DEREF_ulong(x189_ + 3);\
	(diag_) = DEREF_ulong(x189_ + 4);\
	(small_) = DEREF_list(x189_ + 5);\
	(rep_) = DEREF_btype(x189_ + 6);\
	(no_) = DEREF_ntype(x189_ + 7);\
	(destroyer_)(x189_, (unsigned)8);\
    }


/* Operations for field arg_promote of union FLOAT_TYPE */

#define ftype_arg_promote_tag		((unsigned)1)
#define IS_ftype_arg_promote(P)		(CHECK_NULL(P)->ag_tag == 1)

#define ftype_arg_promote_arg(P)	(CHECK_TAG((P), 1) + 6)

#define MAKE_ftype_arg_promote(arg_prom_, arg_, c_class_ftype)\
    {\
	c_class *x190_ = GEN_c_class(7, TYPEID_ftype);\
	x190_->ag_tag = 1;\
	COPY_type(x190_ + 1, (arg_prom_));\
	COPY_ulong(x190_ + 2, LINK_NONE);\
	COPY_ulong(x190_ + 3, LINK_NONE);\
	COPY_ulong(x190_ + 4, LINK_NONE);\
	COPY_list(x190_ + 5, NULL_list ( FLOAT ));\
	COPY_ftype(x190_ + 6, (arg_));\
	(c_class_ftype) = x190_;\
    }

#define DECONS_ftype_arg_promote(arg_prom_, ftok_, ntok_, diag_, small_, arg_, c_class_ftype)\
    {\
	c_class *x191_ = CHECK_TAG((c_class_ftype), 1);\
	(arg_prom_) = DEREF_type(x191_ + 1);\
	(ftok_) = DEREF_ulong(x191_ + 2);\
	(ntok_) = DEREF_ulong(x191_ + 3);\
	(diag_) = DEREF_ulong(x191_ + 4);\
	(small_) = DEREF_list(x191_ + 5);\
	(arg_) = DEREF_ftype(x191_ + 6);\
    }

#define DESTROY_ftype_arg_promote(destroyer_, arg_prom_, ftok_, ntok_, diag_, small_, arg_, c_class_ftype)\
    {\
	c_class *x192_ = CHECK_TAG((c_class_ftype), 1);\
	(arg_prom_) = DEREF_type(x192_ + 1);\
	(ftok_) = DEREF_ulong(x192_ + 2);\
	(ntok_) = DEREF_ulong(x192_ + 3);\
	(diag_) = DEREF_ulong(x192_ + 4);\
	(small_) = DEREF_list(x192_ + 5);\
	(arg_) = DEREF_ftype(x192_ + 6);\
	(destroyer_)(x192_, (unsigned)7);\
    }


/* Operations for field arith of union FLOAT_TYPE */

#define ftype_arith_tag			((unsigned)2)
#define IS_ftype_arith(P)		(CHECK_NULL(P)->ag_tag == 2)

#define ftype_arith_arg1(P)		(CHECK_TAG((P), 2) + 6)
#define ftype_arith_arg2(P)		(CHECK_TAG((P), 2) + 7)

#define MAKE_ftype_arith(arg_prom_, arg1_, arg2_, c_class_ftype)\
    {\
	c_class *x193_ = GEN_c_class(8, TYPEID_ftype);\
	x193_->ag_tag = 2;\
	COPY_type(x193_ + 1, (arg_prom_));\
	COPY_ulong(x193_ + 2, LINK_NONE);\
	COPY_ulong(x193_ + 3, LINK_NONE);\
	COPY_ulong(x193_ + 4, LINK_NONE);\
	COPY_list(x193_ + 5, NULL_list ( FLOAT ));\
	COPY_ftype(x193_ + 6, (arg1_));\
	COPY_ftype(x193_ + 7, (arg2_));\
	(c_class_ftype) = x193_;\
    }

#define DECONS_ftype_arith(arg_prom_, ftok_, ntok_, diag_, small_, arg1_, arg2_, c_class_ftype)\
    {\
	c_class *x194_ = CHECK_TAG((c_class_ftype), 2);\
	(arg_prom_) = DEREF_type(x194_ + 1);\
	(ftok_) = DEREF_ulong(x194_ + 2);\
	(ntok_) = DEREF_ulong(x194_ + 3);\
	(diag_) = DEREF_ulong(x194_ + 4);\
	(small_) = DEREF_list(x194_ + 5);\
	(arg1_) = DEREF_ftype(x194_ + 6);\
	(arg2_) = DEREF_ftype(x194_ + 7);\
    }

#define DESTROY_ftype_arith(destroyer_, arg_prom_, ftok_, ntok_, diag_, small_, arg1_, arg2_, c_class_ftype)\
    {\
	c_class *x195_ = CHECK_TAG((c_class_ftype), 2);\
	(arg_prom_) = DEREF_type(x195_ + 1);\
	(ftok_) = DEREF_ulong(x195_ + 2);\
	(ntok_) = DEREF_ulong(x195_ + 3);\
	(diag_) = DEREF_ulong(x195_ + 4);\
	(small_) = DEREF_list(x195_ + 5);\
	(arg1_) = DEREF_ftype(x195_ + 6);\
	(arg2_) = DEREF_ftype(x195_ + 7);\
	(destroyer_)(x195_, (unsigned)8);\
    }


/* Operations for field token of union FLOAT_TYPE */

#define ftype_token_tag			((unsigned)3)
#define IS_ftype_token(P)		(CHECK_NULL(P)->ag_tag == 3)

#define ftype_token_tok(P)		(CHECK_TAG((P), 3) + 6)
#define ftype_token_args(P)		(CHECK_TAG((P), 3) + 7)

#define MAKE_ftype_token(arg_prom_, tok_, args_, c_class_ftype)\
    {\
	c_class *x196_ = GEN_c_class(8, TYPEID_ftype);\
	x196_->ag_tag = 3;\
	COPY_type(x196_ + 1, (arg_prom_));\
	COPY_ulong(x196_ + 2, LINK_NONE);\
	COPY_ulong(x196_ + 3, LINK_NONE);\
	COPY_ulong(x196_ + 4, LINK_NONE);\
	COPY_list(x196_ + 5, NULL_list ( FLOAT ));\
	COPY_id(x196_ + 6, (tok_));\
	COPY_list(x196_ + 7, (args_));\
	(c_class_ftype) = x196_;\
    }

#define DECONS_ftype_token(arg_prom_, ftok_, ntok_, diag_, small_, tok_, args_, c_class_ftype)\
    {\
	c_class *x197_ = CHECK_TAG((c_class_ftype), 3);\
	(arg_prom_) = DEREF_type(x197_ + 1);\
	(ftok_) = DEREF_ulong(x197_ + 2);\
	(ntok_) = DEREF_ulong(x197_ + 3);\
	(diag_) = DEREF_ulong(x197_ + 4);\
	(small_) = DEREF_list(x197_ + 5);\
	(tok_) = DEREF_id(x197_ + 6);\
	(args_) = DEREF_list(x197_ + 7);\
    }

#define DESTROY_ftype_token(destroyer_, arg_prom_, ftok_, ntok_, diag_, small_, tok_, args_, c_class_ftype)\
    {\
	c_class *x198_ = CHECK_TAG((c_class_ftype), 3);\
	(arg_prom_) = DEREF_type(x198_ + 1);\
	(ftok_) = DEREF_ulong(x198_ + 2);\
	(ntok_) = DEREF_ulong(x198_ + 3);\
	(diag_) = DEREF_ulong(x198_ + 4);\
	(small_) = DEREF_list(x198_ + 5);\
	(tok_) = DEREF_id(x198_ + 6);\
	(args_) = DEREF_list(x198_ + 7);\
	(destroyer_)(x198_, (unsigned)8);\
    }


#endif
