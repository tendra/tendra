/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef INFO_OPS_H_INCLUDED
#define INFO_OPS_H_INCLUDED

/* Operations for union SORT_INFO */

#define TAG_info(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for component name of union SORT_INFO */

#define info_name(P)			(CHECK_NULL(P) + 1)


/* Operations for field builtin of union SORT_INFO */

#define info_builtin_tag		((unsigned)0)
#define IS_info_builtin(P)		(CHECK_NULL(P)->ag_tag == 0)


#define MAKE_info_builtin(name_, tdf_info)\
    {\
	tdf *x71_ = GEN_tdf(2, TYPEID_info);\
	x71_->ag_tag = 0;\
	COPY_string(x71_ + 1, (name_));\
	(tdf_info) = x71_;\
    }

#define DECONS_info_builtin(name_, tdf_info)\
    {\
	tdf *x72_ = CHECK_TAG((tdf_info), 0);\
	(name_) = DEREF_string(x72_ + 1);\
    }

#define DESTROY_info_builtin(destroyer_, name_, tdf_info)\
    {\
	tdf *x73_ = CHECK_TAG((tdf_info), 0);\
	(name_) = DEREF_string(x73_ + 1);\
	(destroyer_)(x73_, (unsigned)2);\
    }


/* Operations for field basic of union SORT_INFO */

#define info_basic_tag			((unsigned)1)
#define IS_info_basic(P)		(CHECK_NULL(P)->ag_tag == 1)

#define info_basic_bits(P)		(CHECK_TAG((P), 1) + 2)
#define info_basic_extend(P)		(CHECK_TAG((P), 1) + 3)
#define info_basic_max(P)		(CHECK_TAG((P), 1) + 4)
#define info_basic_cons(P)		(CHECK_TAG((P), 1) + 5)
#define info_basic_sortname(P)		(CHECK_TAG((P), 1) + 6)

#define MAKE_info_basic(name_, bits_, extend_, max_, cons_, sortname_, tdf_info)\
    {\
	tdf *x74_ = GEN_tdf(7, TYPEID_info);\
	x74_->ag_tag = 1;\
	COPY_string(x74_ + 1, (name_));\
	COPY_unsigned(x74_ + 2, (bits_));\
	COPY_unsigned(x74_ + 3, (extend_));\
	COPY_unsigned(x74_ + 4, (max_));\
	COPY_list(x74_ + 5, (cons_));\
	COPY_cons(x74_ + 6, (sortname_));\
	(tdf_info) = x74_;\
    }

#define DECONS_info_basic(name_, bits_, extend_, max_, cons_, sortname_, tdf_info)\
    {\
	tdf *x75_ = CHECK_TAG((tdf_info), 1);\
	(name_) = DEREF_string(x75_ + 1);\
	(bits_) = DEREF_unsigned(x75_ + 2);\
	(extend_) = DEREF_unsigned(x75_ + 3);\
	(max_) = DEREF_unsigned(x75_ + 4);\
	(cons_) = DEREF_list(x75_ + 5);\
	(sortname_) = DEREF_cons(x75_ + 6);\
    }

#define DESTROY_info_basic(destroyer_, name_, bits_, extend_, max_, cons_, sortname_, tdf_info)\
    {\
	tdf *x76_ = CHECK_TAG((tdf_info), 1);\
	(name_) = DEREF_string(x76_ + 1);\
	(bits_) = DEREF_unsigned(x76_ + 2);\
	(extend_) = DEREF_unsigned(x76_ + 3);\
	(max_) = DEREF_unsigned(x76_ + 4);\
	(cons_) = DEREF_list(x76_ + 5);\
	(sortname_) = DEREF_cons(x76_ + 6);\
	(destroyer_)(x76_, (unsigned)7);\
    }


/* Operations for field dummy of union SORT_INFO */

#define info_dummy_tag			((unsigned)2)
#define IS_info_dummy(P)		(CHECK_NULL(P)->ag_tag == 2)

#define info_dummy_cons(P)		(CHECK_TAG((P), 2) + 2)

#define MAKE_info_dummy(name_, cons_, tdf_info)\
    {\
	tdf *x77_ = GEN_tdf(3, TYPEID_info);\
	x77_->ag_tag = 2;\
	COPY_string(x77_ + 1, (name_));\
	COPY_cons(x77_ + 2, (cons_));\
	(tdf_info) = x77_;\
    }

#define DECONS_info_dummy(name_, cons_, tdf_info)\
    {\
	tdf *x78_ = CHECK_TAG((tdf_info), 2);\
	(name_) = DEREF_string(x78_ + 1);\
	(cons_) = DEREF_cons(x78_ + 2);\
    }

#define DESTROY_info_dummy(destroyer_, name_, cons_, tdf_info)\
    {\
	tdf *x79_ = CHECK_TAG((tdf_info), 2);\
	(name_) = DEREF_string(x79_ + 1);\
	(cons_) = DEREF_cons(x79_ + 2);\
	(destroyer_)(x79_, (unsigned)3);\
    }


/* Operations for field set clist_etc of union SORT_INFO */

#define info_clist_etc_tag		((unsigned)6)
#define IS_info_clist_etc(P)		((unsigned)(CHECK_NULL(P)->ag_tag - 3) < (unsigned)3)

#define info_clist_etc_arg(P)		(CHECK_TAG_ETC((P), 3, 6) + 2)

#define MAKE_info_clist_etc(tag, name_, arg_, tdf_info)\
    {\
	tdf *x80_ = GEN_tdf(3, TYPEID_info);\
	x80_->ag_tag = (tag);\
	COPY_string(x80_ + 1, (name_));\
	COPY_sort(x80_ + 2, (arg_));\
	(tdf_info) = CHECK_TAG_ETC(x80_, 3, 6);\
    }

#define MODIFY_info_clist_etc(tag, tdf_info)\
    {\
	tdf *x81_ = CHECK_TAG_ETC ((tdf_info), 3, 6);\
	x81_->ag_tag = (tag);\
	(void) CHECK_TAG_ETC (x81_, 3, 6);\
    }

#define DECONS_info_clist_etc(name_, arg_, tdf_info)\
    {\
	tdf *x82_ = CHECK_TAG_ETC((tdf_info), 3, 6);\
	(name_) = DEREF_string(x82_ + 1);\
	(arg_) = DEREF_sort(x82_ + 2);\
    }

#define DESTROY_info_clist_etc(destroyer_, name_, arg_, tdf_info)\
    {\
	tdf *x83_ = CHECK_TAG_ETC((tdf_info), 3, 6);\
	(name_) = DEREF_string(x83_ + 1);\
	(arg_) = DEREF_sort(x83_ + 2);\
	(destroyer_)(x83_, (unsigned)3);\
    }


/* Operations for field clist of union SORT_INFO */

#define info_clist_tag			((unsigned)3)
#define IS_info_clist(P)		(CHECK_NULL(P)->ag_tag == 3)

#define info_clist_arg(P)		(CHECK_TAG((P), 3) + 2)

#define MAKE_info_clist(name_, arg_, tdf_info)\
    {\
	tdf *x84_ = GEN_tdf(3, TYPEID_info);\
	x84_->ag_tag = 3;\
	COPY_string(x84_ + 1, (name_));\
	COPY_sort(x84_ + 2, (arg_));\
	(tdf_info) = x84_;\
    }

#define DECONS_info_clist(name_, arg_, tdf_info)\
    {\
	tdf *x85_ = CHECK_TAG((tdf_info), 3);\
	(name_) = DEREF_string(x85_ + 1);\
	(arg_) = DEREF_sort(x85_ + 2);\
    }

#define DESTROY_info_clist(destroyer_, name_, arg_, tdf_info)\
    {\
	tdf *x86_ = CHECK_TAG((tdf_info), 3);\
	(name_) = DEREF_string(x86_ + 1);\
	(arg_) = DEREF_sort(x86_ + 2);\
	(destroyer_)(x86_, (unsigned)3);\
    }


/* Operations for field slist of union SORT_INFO */

#define info_slist_tag			((unsigned)4)
#define IS_info_slist(P)		(CHECK_NULL(P)->ag_tag == 4)

#define info_slist_arg(P)		(CHECK_TAG((P), 4) + 2)

#define MAKE_info_slist(name_, arg_, tdf_info)\
    {\
	tdf *x87_ = GEN_tdf(3, TYPEID_info);\
	x87_->ag_tag = 4;\
	COPY_string(x87_ + 1, (name_));\
	COPY_sort(x87_ + 2, (arg_));\
	(tdf_info) = x87_;\
    }

#define DECONS_info_slist(name_, arg_, tdf_info)\
    {\
	tdf *x88_ = CHECK_TAG((tdf_info), 4);\
	(name_) = DEREF_string(x88_ + 1);\
	(arg_) = DEREF_sort(x88_ + 2);\
    }

#define DESTROY_info_slist(destroyer_, name_, arg_, tdf_info)\
    {\
	tdf *x89_ = CHECK_TAG((tdf_info), 4);\
	(name_) = DEREF_string(x89_ + 1);\
	(arg_) = DEREF_sort(x89_ + 2);\
	(destroyer_)(x89_, (unsigned)3);\
    }


/* Operations for field option of union SORT_INFO */

#define info_option_tag			((unsigned)5)
#define IS_info_option(P)		(CHECK_NULL(P)->ag_tag == 5)

#define info_option_arg(P)		(CHECK_TAG((P), 5) + 2)

#define MAKE_info_option(name_, arg_, tdf_info)\
    {\
	tdf *x90_ = GEN_tdf(3, TYPEID_info);\
	x90_->ag_tag = 5;\
	COPY_string(x90_ + 1, (name_));\
	COPY_sort(x90_ + 2, (arg_));\
	(tdf_info) = x90_;\
    }

#define DECONS_info_option(name_, arg_, tdf_info)\
    {\
	tdf *x91_ = CHECK_TAG((tdf_info), 5);\
	(name_) = DEREF_string(x91_ + 1);\
	(arg_) = DEREF_sort(x91_ + 2);\
    }

#define DESTROY_info_option(destroyer_, name_, arg_, tdf_info)\
    {\
	tdf *x92_ = CHECK_TAG((tdf_info), 5);\
	(name_) = DEREF_string(x92_ + 1);\
	(arg_) = DEREF_sort(x92_ + 2);\
	(destroyer_)(x92_, (unsigned)3);\
    }


#endif
