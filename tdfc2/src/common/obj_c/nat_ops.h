/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef NAT_OPS_H_INCLUDED
#define NAT_OPS_H_INCLUDED

/* Operations for union NAT */

#define TAG_nat(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for field small of union NAT */

#define nat_small_tag			((unsigned)0)
#define IS_nat_small(P)			(CHECK_NULL(P)->ag_tag == 0)

#define nat_small_value(P)		(CHECK_TAG((P), 0) + 1)

#define MAKE_nat_small(value_, c_class_nat)\
    {\
	c_class *x465_ = GEN_c_class(2, TYPEID_nat);\
	x465_->ag_tag = 0;\
	COPY_unsigned(x465_ + 1, (value_));\
	(c_class_nat) = x465_;\
    }

#define DECONS_nat_small(value_, c_class_nat)\
    {\
	c_class *x466_ = CHECK_TAG((c_class_nat), 0);\
	(value_) = DEREF_unsigned(x466_ + 1);\
    }

#define DESTROY_nat_small(destroyer_, value_, c_class_nat)\
    {\
	c_class *x467_ = CHECK_TAG((c_class_nat), 0);\
	(value_) = DEREF_unsigned(x467_ + 1);\
	(destroyer_)(x467_, (unsigned)2);\
    }


/* Operations for field large of union NAT */

#define nat_large_tag			((unsigned)1)
#define IS_nat_large(P)			(CHECK_NULL(P)->ag_tag == 1)

#define nat_large_values(P)		(CHECK_TAG((P), 1) + 1)

#define MAKE_nat_large(values_, c_class_nat)\
    {\
	c_class *x468_ = GEN_c_class(2, TYPEID_nat);\
	x468_->ag_tag = 1;\
	COPY_list(x468_ + 1, (values_));\
	(c_class_nat) = x468_;\
    }

#define DECONS_nat_large(values_, c_class_nat)\
    {\
	c_class *x469_ = CHECK_TAG((c_class_nat), 1);\
	(values_) = DEREF_list(x469_ + 1);\
    }

#define DESTROY_nat_large(destroyer_, values_, c_class_nat)\
    {\
	c_class *x470_ = CHECK_TAG((c_class_nat), 1);\
	(values_) = DEREF_list(x470_ + 1);\
	(destroyer_)(x470_, (unsigned)2);\
    }


/* Operations for field calc of union NAT */

#define nat_calc_tag			((unsigned)2)
#define IS_nat_calc(P)			(CHECK_NULL(P)->ag_tag == 2)

#define nat_calc_value(P)		(CHECK_TAG((P), 2) + 1)
#define nat_calc_tok(P)			(CHECK_TAG((P), 2) + 2)

#define MAKE_nat_calc(value_, c_class_nat)\
    {\
	c_class *x471_ = GEN_c_class(3, TYPEID_nat);\
	x471_->ag_tag = 2;\
	COPY_exp(x471_ + 1, (value_));\
	COPY_ulong(x471_ + 2, LINK_NONE);\
	(c_class_nat) = x471_;\
    }

#define DECONS_nat_calc(value_, tok_, c_class_nat)\
    {\
	c_class *x472_ = CHECK_TAG((c_class_nat), 2);\
	(value_) = DEREF_exp(x472_ + 1);\
	(tok_) = DEREF_ulong(x472_ + 2);\
    }

#define DESTROY_nat_calc(destroyer_, value_, tok_, c_class_nat)\
    {\
	c_class *x473_ = CHECK_TAG((c_class_nat), 2);\
	(value_) = DEREF_exp(x473_ + 1);\
	(tok_) = DEREF_ulong(x473_ + 2);\
	(destroyer_)(x473_, (unsigned)3);\
    }


/* Operations for field neg of union NAT */

#define nat_neg_tag			((unsigned)3)
#define IS_nat_neg(P)			(CHECK_NULL(P)->ag_tag == 3)

#define nat_neg_arg(P)			(CHECK_TAG((P), 3) + 1)

#define MAKE_nat_neg(arg_, c_class_nat)\
    {\
	c_class *x474_ = GEN_c_class(2, TYPEID_nat);\
	x474_->ag_tag = 3;\
	COPY_nat(x474_ + 1, (arg_));\
	(c_class_nat) = x474_;\
    }

#define DECONS_nat_neg(arg_, c_class_nat)\
    {\
	c_class *x475_ = CHECK_TAG((c_class_nat), 3);\
	(arg_) = DEREF_nat(x475_ + 1);\
    }

#define DESTROY_nat_neg(destroyer_, arg_, c_class_nat)\
    {\
	c_class *x476_ = CHECK_TAG((c_class_nat), 3);\
	(arg_) = DEREF_nat(x476_ + 1);\
	(destroyer_)(x476_, (unsigned)2);\
    }


/* Operations for field token of union NAT */

#define nat_token_tag			((unsigned)4)
#define IS_nat_token(P)			(CHECK_NULL(P)->ag_tag == 4)

#define nat_token_tok(P)		(CHECK_TAG((P), 4) + 1)
#define nat_token_args(P)		(CHECK_TAG((P), 4) + 2)

#define MAKE_nat_token(tok_, args_, c_class_nat)\
    {\
	c_class *x477_ = GEN_c_class(3, TYPEID_nat);\
	x477_->ag_tag = 4;\
	COPY_id(x477_ + 1, (tok_));\
	COPY_list(x477_ + 2, (args_));\
	(c_class_nat) = x477_;\
    }

#define DECONS_nat_token(tok_, args_, c_class_nat)\
    {\
	c_class *x478_ = CHECK_TAG((c_class_nat), 4);\
	(tok_) = DEREF_id(x478_ + 1);\
	(args_) = DEREF_list(x478_ + 2);\
    }

#define DESTROY_nat_token(destroyer_, tok_, args_, c_class_nat)\
    {\
	c_class *x479_ = CHECK_TAG((c_class_nat), 4);\
	(tok_) = DEREF_id(x479_ + 1);\
	(args_) = DEREF_list(x479_ + 2);\
	(destroyer_)(x479_, (unsigned)3);\
    }


#endif
