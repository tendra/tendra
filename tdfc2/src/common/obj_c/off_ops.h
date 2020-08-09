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

#ifndef OFF_OPS_H_INCLUDED
#define OFF_OPS_H_INCLUDED

/* Operations for union OFFSET */

#define TAG_off(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for field zero of union OFFSET */

#define off_zero_tag			((unsigned)0)
#define IS_off_zero(P)			(CHECK_NULL(P)->ag_tag == 0)

#define off_zero_type(P)		(CHECK_TAG((P), 0) + 1)

#define MAKE_off_zero(type_, c_class_off)\
    {\
	c_class *x778_ = GEN_c_class(2, TYPEID_off);\
	x778_->ag_tag = 0;\
	COPY_type(x778_ + 1, (type_));\
	(c_class_off) = x778_;\
    }

#define DECONS_off_zero(type_, c_class_off)\
    {\
	c_class *x779_ = CHECK_TAG((c_class_off), 0);\
	(type_) = DEREF_type(x779_ + 1);\
    }

#define DESTROY_off_zero(destroyer_, type_, c_class_off)\
    {\
	c_class *x780_ = CHECK_TAG((c_class_off), 0);\
	(type_) = DEREF_type(x780_ + 1);\
	(destroyer_)(x780_, (unsigned)2);\
    }


/* Operations for field type of union OFFSET */

#define off_type_tag			((unsigned)1)
#define IS_off_type(P)			(CHECK_NULL(P)->ag_tag == 1)

#define off_type_type(P)		(CHECK_TAG((P), 1) + 1)

#define MAKE_off_type(type_, c_class_off)\
    {\
	c_class *x781_ = GEN_c_class(2, TYPEID_off);\
	x781_->ag_tag = 1;\
	COPY_type(x781_ + 1, (type_));\
	(c_class_off) = x781_;\
    }

#define DECONS_off_type(type_, c_class_off)\
    {\
	c_class *x782_ = CHECK_TAG((c_class_off), 1);\
	(type_) = DEREF_type(x782_ + 1);\
    }

#define DESTROY_off_type(destroyer_, type_, c_class_off)\
    {\
	c_class *x783_ = CHECK_TAG((c_class_off), 1);\
	(type_) = DEREF_type(x783_ + 1);\
	(destroyer_)(x783_, (unsigned)2);\
    }


/* Operations for field array of union OFFSET */

#define off_array_tag			((unsigned)2)
#define IS_off_array(P)			(CHECK_NULL(P)->ag_tag == 2)

#define off_array_type(P)		(CHECK_TAG((P), 2) + 1)
#define off_array_arg(P)		(CHECK_TAG((P), 2) + 2)

#define MAKE_off_array(type_, arg_, c_class_off)\
    {\
	c_class *x784_ = GEN_c_class(3, TYPEID_off);\
	x784_->ag_tag = 2;\
	COPY_type(x784_ + 1, (type_));\
	COPY_unsigned(x784_ + 2, (arg_));\
	(c_class_off) = x784_;\
    }

#define DECONS_off_array(type_, arg_, c_class_off)\
    {\
	c_class *x785_ = CHECK_TAG((c_class_off), 2);\
	(type_) = DEREF_type(x785_ + 1);\
	(arg_) = DEREF_unsigned(x785_ + 2);\
    }

#define DESTROY_off_array(destroyer_, type_, arg_, c_class_off)\
    {\
	c_class *x786_ = CHECK_TAG((c_class_off), 2);\
	(type_) = DEREF_type(x786_ + 1);\
	(arg_) = DEREF_unsigned(x786_ + 2);\
	(destroyer_)(x786_, (unsigned)3);\
    }


/* Operations for field extra of union OFFSET */

#define off_extra_tag			((unsigned)3)
#define IS_off_extra(P)			(CHECK_NULL(P)->ag_tag == 3)

#define off_extra_type(P)		(CHECK_TAG((P), 3) + 1)
#define off_extra_scale(P)		(CHECK_TAG((P), 3) + 2)

#define MAKE_off_extra(type_, scale_, c_class_off)\
    {\
	c_class *x787_ = GEN_c_class(3, TYPEID_off);\
	x787_->ag_tag = 3;\
	COPY_type(x787_ + 1, (type_));\
	COPY_int(x787_ + 2, (scale_));\
	(c_class_off) = x787_;\
    }

#define DECONS_off_extra(type_, scale_, c_class_off)\
    {\
	c_class *x788_ = CHECK_TAG((c_class_off), 3);\
	(type_) = DEREF_type(x788_ + 1);\
	(scale_) = DEREF_int(x788_ + 2);\
    }

#define DESTROY_off_extra(destroyer_, type_, scale_, c_class_off)\
    {\
	c_class *x789_ = CHECK_TAG((c_class_off), 3);\
	(type_) = DEREF_type(x789_ + 1);\
	(scale_) = DEREF_int(x789_ + 2);\
	(destroyer_)(x789_, (unsigned)3);\
    }


/* Operations for field base of union OFFSET */

#define off_base_tag			((unsigned)4)
#define IS_off_base(P)			(CHECK_NULL(P)->ag_tag == 4)

#define off_base_graph(P)		(CHECK_TAG((P), 4) + 1)

#define MAKE_off_base(graph_, c_class_off)\
    {\
	c_class *x790_ = GEN_c_class(2, TYPEID_off);\
	x790_->ag_tag = 4;\
	COPY_graph(x790_ + 1, (graph_));\
	(c_class_off) = x790_;\
    }

#define DECONS_off_base(graph_, c_class_off)\
    {\
	c_class *x791_ = CHECK_TAG((c_class_off), 4);\
	(graph_) = DEREF_graph(x791_ + 1);\
    }

#define DESTROY_off_base(destroyer_, graph_, c_class_off)\
    {\
	c_class *x792_ = CHECK_TAG((c_class_off), 4);\
	(graph_) = DEREF_graph(x792_ + 1);\
	(destroyer_)(x792_, (unsigned)2);\
    }


/* Operations for field deriv of union OFFSET */

#define off_deriv_tag			((unsigned)5)
#define IS_off_deriv(P)			(CHECK_NULL(P)->ag_tag == 5)

#define off_deriv_graph(P)		(CHECK_TAG((P), 5) + 1)
#define off_deriv_direct(P)		(CHECK_TAG((P), 5) + 2)
#define off_deriv_indirect(P)		(CHECK_TAG((P), 5) + 3)

#define MAKE_off_deriv(graph_, direct_, indirect_, c_class_off)\
    {\
	c_class *x793_ = GEN_c_class(4, TYPEID_off);\
	x793_->ag_tag = 5;\
	COPY_graph(x793_ + 1, (graph_));\
	COPY_off(x793_ + 2, (direct_));\
	COPY_off(x793_ + 3, (indirect_));\
	(c_class_off) = x793_;\
    }

#define DECONS_off_deriv(graph_, direct_, indirect_, c_class_off)\
    {\
	c_class *x794_ = CHECK_TAG((c_class_off), 5);\
	(graph_) = DEREF_graph(x794_ + 1);\
	(direct_) = DEREF_off(x794_ + 2);\
	(indirect_) = DEREF_off(x794_ + 3);\
    }

#define DESTROY_off_deriv(destroyer_, graph_, direct_, indirect_, c_class_off)\
    {\
	c_class *x795_ = CHECK_TAG((c_class_off), 5);\
	(graph_) = DEREF_graph(x795_ + 1);\
	(direct_) = DEREF_off(x795_ + 2);\
	(indirect_) = DEREF_off(x795_ + 3);\
	(destroyer_)(x795_, (unsigned)4);\
    }


/* Operations for field member of union OFFSET */

#define off_member_tag			((unsigned)6)
#define IS_off_member(P)		(CHECK_NULL(P)->ag_tag == 6)

#define off_member_id(P)		(CHECK_TAG((P), 6) + 1)

#define MAKE_off_member(id_, c_class_off)\
    {\
	c_class *x796_ = GEN_c_class(2, TYPEID_off);\
	x796_->ag_tag = 6;\
	COPY_id(x796_ + 1, (id_));\
	(c_class_off) = x796_;\
    }

#define DECONS_off_member(id_, c_class_off)\
    {\
	c_class *x797_ = CHECK_TAG((c_class_off), 6);\
	(id_) = DEREF_id(x797_ + 1);\
    }

#define DESTROY_off_member(destroyer_, id_, c_class_off)\
    {\
	c_class *x798_ = CHECK_TAG((c_class_off), 6);\
	(id_) = DEREF_id(x798_ + 1);\
	(destroyer_)(x798_, (unsigned)2);\
    }


/* Operations for field ptr_mem of union OFFSET */

#define off_ptr_mem_tag			((unsigned)7)
#define IS_off_ptr_mem(P)		(CHECK_NULL(P)->ag_tag == 7)

#define off_ptr_mem_arg(P)		(CHECK_TAG((P), 7) + 1)

#define MAKE_off_ptr_mem(arg_, c_class_off)\
    {\
	c_class *x799_ = GEN_c_class(2, TYPEID_off);\
	x799_->ag_tag = 7;\
	COPY_exp(x799_ + 1, (arg_));\
	(c_class_off) = x799_;\
    }

#define DECONS_off_ptr_mem(arg_, c_class_off)\
    {\
	c_class *x800_ = CHECK_TAG((c_class_off), 7);\
	(arg_) = DEREF_exp(x800_ + 1);\
    }

#define DESTROY_off_ptr_mem(destroyer_, arg_, c_class_off)\
    {\
	c_class *x801_ = CHECK_TAG((c_class_off), 7);\
	(arg_) = DEREF_exp(x801_ + 1);\
	(destroyer_)(x801_, (unsigned)2);\
    }


/* Operations for field negate of union OFFSET */

#define off_negate_tag			((unsigned)8)
#define IS_off_negate(P)		(CHECK_NULL(P)->ag_tag == 8)

#define off_negate_arg(P)		(CHECK_TAG((P), 8) + 1)

#define MAKE_off_negate(arg_, c_class_off)\
    {\
	c_class *x802_ = GEN_c_class(2, TYPEID_off);\
	x802_->ag_tag = 8;\
	COPY_off(x802_ + 1, (arg_));\
	(c_class_off) = x802_;\
    }

#define DECONS_off_negate(arg_, c_class_off)\
    {\
	c_class *x803_ = CHECK_TAG((c_class_off), 8);\
	(arg_) = DEREF_off(x803_ + 1);\
    }

#define DESTROY_off_negate(destroyer_, arg_, c_class_off)\
    {\
	c_class *x804_ = CHECK_TAG((c_class_off), 8);\
	(arg_) = DEREF_off(x804_ + 1);\
	(destroyer_)(x804_, (unsigned)2);\
    }


/* Operations for field plus of union OFFSET */

#define off_plus_tag			((unsigned)9)
#define IS_off_plus(P)			(CHECK_NULL(P)->ag_tag == 9)

#define off_plus_arg1(P)		(CHECK_TAG((P), 9) + 1)
#define off_plus_arg2(P)		(CHECK_TAG((P), 9) + 2)

#define MAKE_off_plus(arg1_, arg2_, c_class_off)\
    {\
	c_class *x805_ = GEN_c_class(3, TYPEID_off);\
	x805_->ag_tag = 9;\
	COPY_off(x805_ + 1, (arg1_));\
	COPY_off(x805_ + 2, (arg2_));\
	(c_class_off) = x805_;\
    }

#define DECONS_off_plus(arg1_, arg2_, c_class_off)\
    {\
	c_class *x806_ = CHECK_TAG((c_class_off), 9);\
	(arg1_) = DEREF_off(x806_ + 1);\
	(arg2_) = DEREF_off(x806_ + 2);\
    }

#define DESTROY_off_plus(destroyer_, arg1_, arg2_, c_class_off)\
    {\
	c_class *x807_ = CHECK_TAG((c_class_off), 9);\
	(arg1_) = DEREF_off(x807_ + 1);\
	(arg2_) = DEREF_off(x807_ + 2);\
	(destroyer_)(x807_, (unsigned)3);\
    }


/* Operations for field mult of union OFFSET */

#define off_mult_tag			((unsigned)10)
#define IS_off_mult(P)			(CHECK_NULL(P)->ag_tag == 10)

#define off_mult_arg1(P)		(CHECK_TAG((P), 10) + 1)
#define off_mult_arg2(P)		(CHECK_TAG((P), 10) + 2)

#define MAKE_off_mult(arg1_, arg2_, c_class_off)\
    {\
	c_class *x808_ = GEN_c_class(3, TYPEID_off);\
	x808_->ag_tag = 10;\
	COPY_off(x808_ + 1, (arg1_));\
	COPY_exp(x808_ + 2, (arg2_));\
	(c_class_off) = x808_;\
    }

#define DECONS_off_mult(arg1_, arg2_, c_class_off)\
    {\
	c_class *x809_ = CHECK_TAG((c_class_off), 10);\
	(arg1_) = DEREF_off(x809_ + 1);\
	(arg2_) = DEREF_exp(x809_ + 2);\
    }

#define DESTROY_off_mult(destroyer_, arg1_, arg2_, c_class_off)\
    {\
	c_class *x810_ = CHECK_TAG((c_class_off), 10);\
	(arg1_) = DEREF_off(x810_ + 1);\
	(arg2_) = DEREF_exp(x810_ + 2);\
	(destroyer_)(x810_, (unsigned)3);\
    }


/* Operations for field ptr_diff of union OFFSET */

#define off_ptr_diff_tag		((unsigned)11)
#define IS_off_ptr_diff(P)		(CHECK_NULL(P)->ag_tag == 11)

#define off_ptr_diff_ptr1(P)		(CHECK_TAG((P), 11) + 1)
#define off_ptr_diff_ptr2(P)		(CHECK_TAG((P), 11) + 2)

#define MAKE_off_ptr_diff(ptr1_, ptr2_, c_class_off)\
    {\
	c_class *x811_ = GEN_c_class(3, TYPEID_off);\
	x811_->ag_tag = 11;\
	COPY_exp(x811_ + 1, (ptr1_));\
	COPY_exp(x811_ + 2, (ptr2_));\
	(c_class_off) = x811_;\
    }

#define DECONS_off_ptr_diff(ptr1_, ptr2_, c_class_off)\
    {\
	c_class *x812_ = CHECK_TAG((c_class_off), 11);\
	(ptr1_) = DEREF_exp(x812_ + 1);\
	(ptr2_) = DEREF_exp(x812_ + 2);\
    }

#define DESTROY_off_ptr_diff(destroyer_, ptr1_, ptr2_, c_class_off)\
    {\
	c_class *x813_ = CHECK_TAG((c_class_off), 11);\
	(ptr1_) = DEREF_exp(x813_ + 1);\
	(ptr2_) = DEREF_exp(x813_ + 2);\
	(destroyer_)(x813_, (unsigned)3);\
    }


/* Operations for field token of union OFFSET */

#define off_token_tag			((unsigned)12)
#define IS_off_token(P)			(CHECK_NULL(P)->ag_tag == 12)

#define off_token_tok(P)		(CHECK_TAG((P), 12) + 1)
#define off_token_args(P)		(CHECK_TAG((P), 12) + 2)

#define MAKE_off_token(tok_, args_, c_class_off)\
    {\
	c_class *x814_ = GEN_c_class(3, TYPEID_off);\
	x814_->ag_tag = 12;\
	COPY_id(x814_ + 1, (tok_));\
	COPY_list(x814_ + 2, (args_));\
	(c_class_off) = x814_;\
    }

#define DECONS_off_token(tok_, args_, c_class_off)\
    {\
	c_class *x815_ = CHECK_TAG((c_class_off), 12);\
	(tok_) = DEREF_id(x815_ + 1);\
	(args_) = DEREF_list(x815_ + 2);\
    }

#define DESTROY_off_token(destroyer_, tok_, args_, c_class_off)\
    {\
	c_class *x816_ = CHECK_TAG((c_class_off), 12);\
	(tok_) = DEREF_id(x816_ + 1);\
	(args_) = DEREF_list(x816_ + 2);\
	(destroyer_)(x816_, (unsigned)3);\
    }


#endif
