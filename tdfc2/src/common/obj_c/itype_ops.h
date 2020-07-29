/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef ITYPE_OPS_H_INCLUDED
#define ITYPE_OPS_H_INCLUDED

/* Operations for union INT_TYPE */

#define TAG_itype(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for component prom of union INT_TYPE */

#define itype_prom(P)			(CHECK_NULL(P) + 1)


/* Operations for component cases of union INT_TYPE */

#define itype_cases(P)			(CHECK_NULL(P) + 2)


/* Operations for component unprom of union INT_TYPE */

#define itype_unprom(P)			(CHECK_NULL(P) + 3)


/* Operations for component itok of union INT_TYPE */

#define itype_itok(P)			(CHECK_NULL(P) + 4)


/* Operations for component ntok of union INT_TYPE */

#define itype_ntok(P)			(CHECK_NULL(P) + 5)


/* Operations for component diag of union INT_TYPE */

#define itype_diag(P)			(CHECK_NULL(P) + 6)


/* Operations for field basic of union INT_TYPE */

#define itype_basic_tag			((unsigned)0)
#define IS_itype_basic(P)		(CHECK_NULL(P)->ag_tag == 0)

#define itype_basic_rep(P)		(CHECK_TAG((P), 0) + 7)
#define itype_basic_no(P)		(CHECK_TAG((P), 0) + 8)

#define MAKE_itype_basic(prom_, cases_, rep_, no_, c_class_itype)\
    {\
	c_class *x169_ = GEN_c_class(9, TYPEID_itype);\
	x169_->ag_tag = 0;\
	COPY_type(x169_ + 1, (prom_));\
	COPY_list(x169_ + 2, (cases_));\
	COPY_ntype(x169_ + 3, ntype_none);\
	COPY_ulong(x169_ + 4, LINK_NONE);\
	COPY_ulong(x169_ + 5, LINK_NONE);\
	COPY_ulong(x169_ + 6, LINK_NONE);\
	COPY_btype(x169_ + 7, (rep_));\
	COPY_ntype(x169_ + 8, (no_));\
	(c_class_itype) = x169_;\
    }

#define DECONS_itype_basic(prom_, cases_, unprom_, itok_, ntok_, diag_, rep_, no_, c_class_itype)\
    {\
	c_class *x170_ = CHECK_TAG((c_class_itype), 0);\
	(prom_) = DEREF_type(x170_ + 1);\
	(cases_) = DEREF_list(x170_ + 2);\
	(unprom_) = DEREF_ntype(x170_ + 3);\
	(itok_) = DEREF_ulong(x170_ + 4);\
	(ntok_) = DEREF_ulong(x170_ + 5);\
	(diag_) = DEREF_ulong(x170_ + 6);\
	(rep_) = DEREF_btype(x170_ + 7);\
	(no_) = DEREF_ntype(x170_ + 8);\
    }

#define DESTROY_itype_basic(destroyer_, prom_, cases_, unprom_, itok_, ntok_, diag_, rep_, no_, c_class_itype)\
    {\
	c_class *x171_ = CHECK_TAG((c_class_itype), 0);\
	(prom_) = DEREF_type(x171_ + 1);\
	(cases_) = DEREF_list(x171_ + 2);\
	(unprom_) = DEREF_ntype(x171_ + 3);\
	(itok_) = DEREF_ulong(x171_ + 4);\
	(ntok_) = DEREF_ulong(x171_ + 5);\
	(diag_) = DEREF_ulong(x171_ + 6);\
	(rep_) = DEREF_btype(x171_ + 7);\
	(no_) = DEREF_ntype(x171_ + 8);\
	(destroyer_)(x171_, (unsigned)9);\
    }


/* Operations for field bitfield of union INT_TYPE */

#define itype_bitfield_tag		((unsigned)1)
#define IS_itype_bitfield(P)		(CHECK_NULL(P)->ag_tag == 1)

#define itype_bitfield_sub(P)		(CHECK_TAG((P), 1) + 7)
#define itype_bitfield_rep(P)		(CHECK_TAG((P), 1) + 8)
#define itype_bitfield_size(P)		(CHECK_TAG((P), 1) + 9)
#define itype_bitfield_info(P)		(CHECK_TAG((P), 1) + 10)

#define MAKE_itype_bitfield(prom_, cases_, sub_, rep_, size_, info_, c_class_itype)\
    {\
	c_class *x172_ = GEN_c_class(11, TYPEID_itype);\
	x172_->ag_tag = 1;\
	COPY_type(x172_ + 1, (prom_));\
	COPY_list(x172_ + 2, (cases_));\
	COPY_ntype(x172_ + 3, ntype_none);\
	COPY_ulong(x172_ + 4, LINK_NONE);\
	COPY_ulong(x172_ + 5, LINK_NONE);\
	COPY_ulong(x172_ + 6, LINK_NONE);\
	COPY_type(x172_ + 7, (sub_));\
	COPY_btype(x172_ + 8, (rep_));\
	COPY_nat(x172_ + 9, (size_));\
	COPY_dspec(x172_ + 10, (info_));\
	(c_class_itype) = x172_;\
    }

#define DECONS_itype_bitfield(prom_, cases_, unprom_, itok_, ntok_, diag_, sub_, rep_, size_, info_, c_class_itype)\
    {\
	c_class *x173_ = CHECK_TAG((c_class_itype), 1);\
	(prom_) = DEREF_type(x173_ + 1);\
	(cases_) = DEREF_list(x173_ + 2);\
	(unprom_) = DEREF_ntype(x173_ + 3);\
	(itok_) = DEREF_ulong(x173_ + 4);\
	(ntok_) = DEREF_ulong(x173_ + 5);\
	(diag_) = DEREF_ulong(x173_ + 6);\
	(sub_) = DEREF_type(x173_ + 7);\
	(rep_) = DEREF_btype(x173_ + 8);\
	(size_) = DEREF_nat(x173_ + 9);\
	(info_) = DEREF_dspec(x173_ + 10);\
    }

#define DESTROY_itype_bitfield(destroyer_, prom_, cases_, unprom_, itok_, ntok_, diag_, sub_, rep_, size_, info_, c_class_itype)\
    {\
	c_class *x174_ = CHECK_TAG((c_class_itype), 1);\
	(prom_) = DEREF_type(x174_ + 1);\
	(cases_) = DEREF_list(x174_ + 2);\
	(unprom_) = DEREF_ntype(x174_ + 3);\
	(itok_) = DEREF_ulong(x174_ + 4);\
	(ntok_) = DEREF_ulong(x174_ + 5);\
	(diag_) = DEREF_ulong(x174_ + 6);\
	(sub_) = DEREF_type(x174_ + 7);\
	(rep_) = DEREF_btype(x174_ + 8);\
	(size_) = DEREF_nat(x174_ + 9);\
	(info_) = DEREF_dspec(x174_ + 10);\
	(destroyer_)(x174_, (unsigned)11);\
    }


/* Operations for field promote of union INT_TYPE */

#define itype_promote_tag		((unsigned)2)
#define IS_itype_promote(P)		(CHECK_NULL(P)->ag_tag == 2)

#define itype_promote_arg(P)		(CHECK_TAG((P), 2) + 7)

#define MAKE_itype_promote(prom_, cases_, arg_, c_class_itype)\
    {\
	c_class *x175_ = GEN_c_class(8, TYPEID_itype);\
	x175_->ag_tag = 2;\
	COPY_type(x175_ + 1, (prom_));\
	COPY_list(x175_ + 2, (cases_));\
	COPY_ntype(x175_ + 3, ntype_none);\
	COPY_ulong(x175_ + 4, LINK_NONE);\
	COPY_ulong(x175_ + 5, LINK_NONE);\
	COPY_ulong(x175_ + 6, LINK_NONE);\
	COPY_itype(x175_ + 7, (arg_));\
	(c_class_itype) = x175_;\
    }

#define DECONS_itype_promote(prom_, cases_, unprom_, itok_, ntok_, diag_, arg_, c_class_itype)\
    {\
	c_class *x176_ = CHECK_TAG((c_class_itype), 2);\
	(prom_) = DEREF_type(x176_ + 1);\
	(cases_) = DEREF_list(x176_ + 2);\
	(unprom_) = DEREF_ntype(x176_ + 3);\
	(itok_) = DEREF_ulong(x176_ + 4);\
	(ntok_) = DEREF_ulong(x176_ + 5);\
	(diag_) = DEREF_ulong(x176_ + 6);\
	(arg_) = DEREF_itype(x176_ + 7);\
    }

#define DESTROY_itype_promote(destroyer_, prom_, cases_, unprom_, itok_, ntok_, diag_, arg_, c_class_itype)\
    {\
	c_class *x177_ = CHECK_TAG((c_class_itype), 2);\
	(prom_) = DEREF_type(x177_ + 1);\
	(cases_) = DEREF_list(x177_ + 2);\
	(unprom_) = DEREF_ntype(x177_ + 3);\
	(itok_) = DEREF_ulong(x177_ + 4);\
	(ntok_) = DEREF_ulong(x177_ + 5);\
	(diag_) = DEREF_ulong(x177_ + 6);\
	(arg_) = DEREF_itype(x177_ + 7);\
	(destroyer_)(x177_, (unsigned)8);\
    }


/* Operations for field arith of union INT_TYPE */

#define itype_arith_tag			((unsigned)3)
#define IS_itype_arith(P)		(CHECK_NULL(P)->ag_tag == 3)

#define itype_arith_arg1(P)		(CHECK_TAG((P), 3) + 7)
#define itype_arith_arg2(P)		(CHECK_TAG((P), 3) + 8)

#define MAKE_itype_arith(prom_, cases_, arg1_, arg2_, c_class_itype)\
    {\
	c_class *x178_ = GEN_c_class(9, TYPEID_itype);\
	x178_->ag_tag = 3;\
	COPY_type(x178_ + 1, (prom_));\
	COPY_list(x178_ + 2, (cases_));\
	COPY_ntype(x178_ + 3, ntype_none);\
	COPY_ulong(x178_ + 4, LINK_NONE);\
	COPY_ulong(x178_ + 5, LINK_NONE);\
	COPY_ulong(x178_ + 6, LINK_NONE);\
	COPY_itype(x178_ + 7, (arg1_));\
	COPY_itype(x178_ + 8, (arg2_));\
	(c_class_itype) = x178_;\
    }

#define DECONS_itype_arith(prom_, cases_, unprom_, itok_, ntok_, diag_, arg1_, arg2_, c_class_itype)\
    {\
	c_class *x179_ = CHECK_TAG((c_class_itype), 3);\
	(prom_) = DEREF_type(x179_ + 1);\
	(cases_) = DEREF_list(x179_ + 2);\
	(unprom_) = DEREF_ntype(x179_ + 3);\
	(itok_) = DEREF_ulong(x179_ + 4);\
	(ntok_) = DEREF_ulong(x179_ + 5);\
	(diag_) = DEREF_ulong(x179_ + 6);\
	(arg1_) = DEREF_itype(x179_ + 7);\
	(arg2_) = DEREF_itype(x179_ + 8);\
    }

#define DESTROY_itype_arith(destroyer_, prom_, cases_, unprom_, itok_, ntok_, diag_, arg1_, arg2_, c_class_itype)\
    {\
	c_class *x180_ = CHECK_TAG((c_class_itype), 3);\
	(prom_) = DEREF_type(x180_ + 1);\
	(cases_) = DEREF_list(x180_ + 2);\
	(unprom_) = DEREF_ntype(x180_ + 3);\
	(itok_) = DEREF_ulong(x180_ + 4);\
	(ntok_) = DEREF_ulong(x180_ + 5);\
	(diag_) = DEREF_ulong(x180_ + 6);\
	(arg1_) = DEREF_itype(x180_ + 7);\
	(arg2_) = DEREF_itype(x180_ + 8);\
	(destroyer_)(x180_, (unsigned)9);\
    }


/* Operations for field literal of union INT_TYPE */

#define itype_literal_tag		((unsigned)4)
#define IS_itype_literal(P)		(CHECK_NULL(P)->ag_tag == 4)

#define itype_literal_nat(P)		(CHECK_TAG((P), 4) + 7)
#define itype_literal_spec(P)		(CHECK_TAG((P), 4) + 8)
#define itype_literal_form(P)		(CHECK_TAG((P), 4) + 9)
#define itype_literal_suff(P)		(CHECK_TAG((P), 4) + 10)
#define itype_literal_tok(P)		(CHECK_TAG((P), 4) + 11)

#define MAKE_itype_literal(prom_, cases_, nat_, spec_, form_, suff_, tok_, c_class_itype)\
    {\
	c_class *x181_ = GEN_c_class(12, TYPEID_itype);\
	x181_->ag_tag = 4;\
	COPY_type(x181_ + 1, (prom_));\
	COPY_list(x181_ + 2, (cases_));\
	COPY_ntype(x181_ + 3, ntype_none);\
	COPY_ulong(x181_ + 4, LINK_NONE);\
	COPY_ulong(x181_ + 5, LINK_NONE);\
	COPY_ulong(x181_ + 6, LINK_NONE);\
	COPY_nat(x181_ + 7, (nat_));\
	COPY_int(x181_ + 8, (spec_));\
	COPY_int(x181_ + 9, (form_));\
	COPY_int(x181_ + 10, (suff_));\
	COPY_id(x181_ + 11, (tok_));\
	(c_class_itype) = x181_;\
    }

#define DECONS_itype_literal(prom_, cases_, unprom_, itok_, ntok_, diag_, nat_, spec_, form_, suff_, tok_, c_class_itype)\
    {\
	c_class *x182_ = CHECK_TAG((c_class_itype), 4);\
	(prom_) = DEREF_type(x182_ + 1);\
	(cases_) = DEREF_list(x182_ + 2);\
	(unprom_) = DEREF_ntype(x182_ + 3);\
	(itok_) = DEREF_ulong(x182_ + 4);\
	(ntok_) = DEREF_ulong(x182_ + 5);\
	(diag_) = DEREF_ulong(x182_ + 6);\
	(nat_) = DEREF_nat(x182_ + 7);\
	(spec_) = DEREF_int(x182_ + 8);\
	(form_) = DEREF_int(x182_ + 9);\
	(suff_) = DEREF_int(x182_ + 10);\
	(tok_) = DEREF_id(x182_ + 11);\
    }

#define DESTROY_itype_literal(destroyer_, prom_, cases_, unprom_, itok_, ntok_, diag_, nat_, spec_, form_, suff_, tok_, c_class_itype)\
    {\
	c_class *x183_ = CHECK_TAG((c_class_itype), 4);\
	(prom_) = DEREF_type(x183_ + 1);\
	(cases_) = DEREF_list(x183_ + 2);\
	(unprom_) = DEREF_ntype(x183_ + 3);\
	(itok_) = DEREF_ulong(x183_ + 4);\
	(ntok_) = DEREF_ulong(x183_ + 5);\
	(diag_) = DEREF_ulong(x183_ + 6);\
	(nat_) = DEREF_nat(x183_ + 7);\
	(spec_) = DEREF_int(x183_ + 8);\
	(form_) = DEREF_int(x183_ + 9);\
	(suff_) = DEREF_int(x183_ + 10);\
	(tok_) = DEREF_id(x183_ + 11);\
	(destroyer_)(x183_, (unsigned)12);\
    }


/* Operations for field token of union INT_TYPE */

#define itype_token_tag			((unsigned)5)
#define IS_itype_token(P)		(CHECK_NULL(P)->ag_tag == 5)

#define itype_token_tok(P)		(CHECK_TAG((P), 5) + 7)
#define itype_token_args(P)		(CHECK_TAG((P), 5) + 8)

#define MAKE_itype_token(prom_, cases_, tok_, args_, c_class_itype)\
    {\
	c_class *x184_ = GEN_c_class(9, TYPEID_itype);\
	x184_->ag_tag = 5;\
	COPY_type(x184_ + 1, (prom_));\
	COPY_list(x184_ + 2, (cases_));\
	COPY_ntype(x184_ + 3, ntype_none);\
	COPY_ulong(x184_ + 4, LINK_NONE);\
	COPY_ulong(x184_ + 5, LINK_NONE);\
	COPY_ulong(x184_ + 6, LINK_NONE);\
	COPY_id(x184_ + 7, (tok_));\
	COPY_list(x184_ + 8, (args_));\
	(c_class_itype) = x184_;\
    }

#define DECONS_itype_token(prom_, cases_, unprom_, itok_, ntok_, diag_, tok_, args_, c_class_itype)\
    {\
	c_class *x185_ = CHECK_TAG((c_class_itype), 5);\
	(prom_) = DEREF_type(x185_ + 1);\
	(cases_) = DEREF_list(x185_ + 2);\
	(unprom_) = DEREF_ntype(x185_ + 3);\
	(itok_) = DEREF_ulong(x185_ + 4);\
	(ntok_) = DEREF_ulong(x185_ + 5);\
	(diag_) = DEREF_ulong(x185_ + 6);\
	(tok_) = DEREF_id(x185_ + 7);\
	(args_) = DEREF_list(x185_ + 8);\
    }

#define DESTROY_itype_token(destroyer_, prom_, cases_, unprom_, itok_, ntok_, diag_, tok_, args_, c_class_itype)\
    {\
	c_class *x186_ = CHECK_TAG((c_class_itype), 5);\
	(prom_) = DEREF_type(x186_ + 1);\
	(cases_) = DEREF_list(x186_ + 2);\
	(unprom_) = DEREF_ntype(x186_ + 3);\
	(itok_) = DEREF_ulong(x186_ + 4);\
	(ntok_) = DEREF_ulong(x186_ + 5);\
	(diag_) = DEREF_ulong(x186_ + 6);\
	(tok_) = DEREF_id(x186_ + 7);\
	(args_) = DEREF_list(x186_ + 8);\
	(destroyer_)(x186_, (unsigned)9);\
    }


#endif
