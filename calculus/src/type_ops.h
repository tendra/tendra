/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA calculus (VERSION 1.2)
    BY calculus (VERSION 1.2)
*/

#ifndef TYPE_OPS_H_INCLUDED
#define TYPE_OPS_H_INCLUDED

/* Operations for union TYPE */

#define TAG_type(P)			((P)->ag_tag)


/* Operations for component size of union TYPE */

#define type_size(P)			((P) + 1)


/* Operations for field primitive of union TYPE */

#define type_primitive_tag		((unsigned)0)
#define IS_type_primitive(P)		((P)->ag_tag == 0)

#define type_primitive_prim(P)		((P) + 2)

#define MAKE_type_primitive(size_, prim_, calculus_type)\
    {\
	calculus *x153_ = GEN_calculus(4, TYPEID_type);\
	x153_->ag_tag = 0;\
	COPY_int(x153_ + 1, (size_));\
	COPY_ptr(x153_ + 2, (prim_));\
	x153_[3].ag_tag = 0;\
	(calculus_type) = x153_;\
    }

#define DECONS_type_primitive(size_, prim_, calculus_type)\
    {\
	calculus *x154_ = (calculus_type);\
	(size_) = DEREF_int(x154_ + 1);\
	(prim_) = DEREF_ptr(x154_ + 2);\
    }

#define DESTROY_type_primitive(destroyer_, size_, prim_, calculus_type)\
    {\
	calculus *x155_ = (calculus_type);\
	(size_) = DEREF_int(x155_ + 1);\
	(prim_) = DEREF_ptr(x155_ + 2);\
	(destroyer_)(x155_, (unsigned)4);\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_primitive(P, N)\
    {\
	calculus *x156_ = GEN_calculus(4, TYPEID_list);\
	unsigned a156_ = (N);\
	x156_->ag_tag = 0;\
	x156_[3].ag_tag = a156_;\
	set_calculus_alias(x156_ + 3, a156_);\
	(P) = x156_;\
    }

#define GET_ALIAS_type_primitive(P)	(((P) + 3)->ag_tag)
#define SET_ALIAS_type_primitive(P, N)	set_calculus_alias((P) + 3, (N))
#define FIND_ALIAS_type_primitive(N)	(find_calculus_alias(N) - 3)

#endif


/* Operations for field ident of union TYPE */

#define type_ident_tag			((unsigned)1)
#define IS_type_ident(P)		((P)->ag_tag == 1)

#define type_ident_id(P)		((P) + 2)

#define MAKE_type_ident(size_, id_, calculus_type)\
    {\
	calculus *x157_ = GEN_calculus(4, TYPEID_type);\
	x157_->ag_tag = 1;\
	COPY_int(x157_ + 1, (size_));\
	COPY_ptr(x157_ + 2, (id_));\
	x157_[3].ag_tag = 0;\
	(calculus_type) = x157_;\
    }

#define DECONS_type_ident(size_, id_, calculus_type)\
    {\
	calculus *x158_ = (calculus_type);\
	(size_) = DEREF_int(x158_ + 1);\
	(id_) = DEREF_ptr(x158_ + 2);\
    }

#define DESTROY_type_ident(destroyer_, size_, id_, calculus_type)\
    {\
	calculus *x159_ = (calculus_type);\
	(size_) = DEREF_int(x159_ + 1);\
	(id_) = DEREF_ptr(x159_ + 2);\
	(destroyer_)(x159_, (unsigned)4);\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_ident(P, N)\
    {\
	calculus *x160_ = GEN_calculus(4, TYPEID_list);\
	unsigned a160_ = (N);\
	x160_->ag_tag = 1;\
	x160_[3].ag_tag = a160_;\
	set_calculus_alias(x160_ + 3, a160_);\
	(P) = x160_;\
    }

#define GET_ALIAS_type_ident(P)		(((P) + 3)->ag_tag)
#define SET_ALIAS_type_ident(P, N)	set_calculus_alias((P) + 3, (N))
#define FIND_ALIAS_type_ident(N)	(find_calculus_alias(N) - 3)

#endif


/* Operations for field enumeration of union TYPE */

#define type_enumeration_tag		((unsigned)2)
#define IS_type_enumeration(P)		((P)->ag_tag == 2)

#define type_enumeration_en(P)		((P) + 2)

#define MAKE_type_enumeration(size_, en_, calculus_type)\
    {\
	calculus *x161_ = GEN_calculus(4, TYPEID_type);\
	x161_->ag_tag = 2;\
	COPY_int(x161_ + 1, (size_));\
	COPY_ptr(x161_ + 2, (en_));\
	x161_[3].ag_tag = 0;\
	(calculus_type) = x161_;\
    }

#define DECONS_type_enumeration(size_, en_, calculus_type)\
    {\
	calculus *x162_ = (calculus_type);\
	(size_) = DEREF_int(x162_ + 1);\
	(en_) = DEREF_ptr(x162_ + 2);\
    }

#define DESTROY_type_enumeration(destroyer_, size_, en_, calculus_type)\
    {\
	calculus *x163_ = (calculus_type);\
	(size_) = DEREF_int(x163_ + 1);\
	(en_) = DEREF_ptr(x163_ + 2);\
	(destroyer_)(x163_, (unsigned)4);\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_enumeration(P, N)\
    {\
	calculus *x164_ = GEN_calculus(4, TYPEID_list);\
	unsigned a164_ = (N);\
	x164_->ag_tag = 2;\
	x164_[3].ag_tag = a164_;\
	set_calculus_alias(x164_ + 3, a164_);\
	(P) = x164_;\
    }

#define GET_ALIAS_type_enumeration(P)	(((P) + 3)->ag_tag)
#define SET_ALIAS_type_enumeration(P, N)set_calculus_alias((P) + 3, (N))
#define FIND_ALIAS_type_enumeration(N)	(find_calculus_alias(N) - 3)

#endif


/* Operations for field structure of union TYPE */

#define type_structure_tag		((unsigned)3)
#define IS_type_structure(P)		((P)->ag_tag == 3)

#define type_structure_struc(P)		((P) + 2)

#define MAKE_type_structure(size_, struc_, calculus_type)\
    {\
	calculus *x165_ = GEN_calculus(4, TYPEID_type);\
	x165_->ag_tag = 3;\
	COPY_int(x165_ + 1, (size_));\
	COPY_ptr(x165_ + 2, (struc_));\
	x165_[3].ag_tag = 0;\
	(calculus_type) = x165_;\
    }

#define DECONS_type_structure(size_, struc_, calculus_type)\
    {\
	calculus *x166_ = (calculus_type);\
	(size_) = DEREF_int(x166_ + 1);\
	(struc_) = DEREF_ptr(x166_ + 2);\
    }

#define DESTROY_type_structure(destroyer_, size_, struc_, calculus_type)\
    {\
	calculus *x167_ = (calculus_type);\
	(size_) = DEREF_int(x167_ + 1);\
	(struc_) = DEREF_ptr(x167_ + 2);\
	(destroyer_)(x167_, (unsigned)4);\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_structure(P, N)\
    {\
	calculus *x168_ = GEN_calculus(4, TYPEID_list);\
	unsigned a168_ = (N);\
	x168_->ag_tag = 3;\
	x168_[3].ag_tag = a168_;\
	set_calculus_alias(x168_ + 3, a168_);\
	(P) = x168_;\
    }

#define GET_ALIAS_type_structure(P)	(((P) + 3)->ag_tag)
#define SET_ALIAS_type_structure(P, N)	set_calculus_alias((P) + 3, (N))
#define FIND_ALIAS_type_structure(N)	(find_calculus_alias(N) - 3)

#endif


/* Operations for field onion of union TYPE */

#define type_onion_tag			((unsigned)4)
#define IS_type_onion(P)		((P)->ag_tag == 4)

#define type_onion_un(P)		((P) + 2)

#define MAKE_type_onion(size_, un_, calculus_type)\
    {\
	calculus *x169_ = GEN_calculus(4, TYPEID_type);\
	x169_->ag_tag = 4;\
	COPY_int(x169_ + 1, (size_));\
	COPY_ptr(x169_ + 2, (un_));\
	x169_[3].ag_tag = 0;\
	(calculus_type) = x169_;\
    }

#define DECONS_type_onion(size_, un_, calculus_type)\
    {\
	calculus *x170_ = (calculus_type);\
	(size_) = DEREF_int(x170_ + 1);\
	(un_) = DEREF_ptr(x170_ + 2);\
    }

#define DESTROY_type_onion(destroyer_, size_, un_, calculus_type)\
    {\
	calculus *x171_ = (calculus_type);\
	(size_) = DEREF_int(x171_ + 1);\
	(un_) = DEREF_ptr(x171_ + 2);\
	(destroyer_)(x171_, (unsigned)4);\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_onion(P, N)\
    {\
	calculus *x172_ = GEN_calculus(4, TYPEID_list);\
	unsigned a172_ = (N);\
	x172_->ag_tag = 4;\
	x172_[3].ag_tag = a172_;\
	set_calculus_alias(x172_ + 3, a172_);\
	(P) = x172_;\
    }

#define GET_ALIAS_type_onion(P)		(((P) + 3)->ag_tag)
#define SET_ALIAS_type_onion(P, N)	set_calculus_alias((P) + 3, (N))
#define FIND_ALIAS_type_onion(N)	(find_calculus_alias(N) - 3)

#endif


/* Operations for field set ptr_etc of union TYPE */

#define type_ptr_etc_tag		((unsigned)10)
#define IS_type_ptr_etc(P)		((unsigned)((P)->ag_tag - 5) < (unsigned)5)

#define type_ptr_etc_sub(P)		((P) + 2)

#define MAKE_type_ptr_etc(tag, size_, sub_, calculus_type)\
    {\
	calculus *x173_ = GEN_calculus(4, TYPEID_type);\
	x173_->ag_tag = (tag);\
	COPY_int(x173_ + 1, (size_));\
	COPY_ptr(x173_ + 2, (sub_));\
	x173_[3].ag_tag = 0;\
	(calculus_type) = x173_;\
    }

#define MODIFY_type_ptr_etc(tag, calculus_type)\
    {\
	(calculus_type)->ag_tag = (tag);\
    }

#define DECONS_type_ptr_etc(size_, sub_, calculus_type)\
    {\
	calculus *x175_ = (calculus_type);\
	(size_) = DEREF_int(x175_ + 1);\
	(sub_) = DEREF_ptr(x175_ + 2);\
    }

#define DESTROY_type_ptr_etc(destroyer_, size_, sub_, calculus_type)\
    {\
	calculus *x176_ = (calculus_type);\
	(size_) = DEREF_int(x176_ + 1);\
	(sub_) = DEREF_ptr(x176_ + 2);\
	(destroyer_)(x176_, (unsigned)4);\
    }


/* Operations for field ptr of union TYPE */

#define type_ptr_tag			((unsigned)5)
#define IS_type_ptr(P)			((P)->ag_tag == 5)

#define type_ptr_sub(P)			((P) + 2)

#define MAKE_type_ptr(size_, sub_, calculus_type)\
    {\
	calculus *x177_ = GEN_calculus(4, TYPEID_type);\
	x177_->ag_tag = 5;\
	COPY_int(x177_ + 1, (size_));\
	COPY_ptr(x177_ + 2, (sub_));\
	x177_[3].ag_tag = 0;\
	(calculus_type) = x177_;\
    }

#define DECONS_type_ptr(size_, sub_, calculus_type)\
    {\
	calculus *x178_ = (calculus_type);\
	(size_) = DEREF_int(x178_ + 1);\
	(sub_) = DEREF_ptr(x178_ + 2);\
    }

#define DESTROY_type_ptr(destroyer_, size_, sub_, calculus_type)\
    {\
	calculus *x179_ = (calculus_type);\
	(size_) = DEREF_int(x179_ + 1);\
	(sub_) = DEREF_ptr(x179_ + 2);\
	(destroyer_)(x179_, (unsigned)4);\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_ptr(P, N)\
    {\
	calculus *x180_ = GEN_calculus(4, TYPEID_list);\
	unsigned a180_ = (N);\
	x180_->ag_tag = 5;\
	x180_[3].ag_tag = a180_;\
	set_calculus_alias(x180_ + 3, a180_);\
	(P) = x180_;\
    }

#define GET_ALIAS_type_ptr(P)		(((P) + 3)->ag_tag)
#define SET_ALIAS_type_ptr(P, N)	set_calculus_alias((P) + 3, (N))
#define FIND_ALIAS_type_ptr(N)		(find_calculus_alias(N) - 3)

#endif


/* Operations for field list of union TYPE */

#define type_list_tag			((unsigned)6)
#define IS_type_list(P)			((P)->ag_tag == 6)

#define type_list_sub(P)		((P) + 2)

#define MAKE_type_list(size_, sub_, calculus_type)\
    {\
	calculus *x181_ = GEN_calculus(4, TYPEID_type);\
	x181_->ag_tag = 6;\
	COPY_int(x181_ + 1, (size_));\
	COPY_ptr(x181_ + 2, (sub_));\
	x181_[3].ag_tag = 0;\
	(calculus_type) = x181_;\
    }

#define DECONS_type_list(size_, sub_, calculus_type)\
    {\
	calculus *x182_ = (calculus_type);\
	(size_) = DEREF_int(x182_ + 1);\
	(sub_) = DEREF_ptr(x182_ + 2);\
    }

#define DESTROY_type_list(destroyer_, size_, sub_, calculus_type)\
    {\
	calculus *x183_ = (calculus_type);\
	(size_) = DEREF_int(x183_ + 1);\
	(sub_) = DEREF_ptr(x183_ + 2);\
	(destroyer_)(x183_, (unsigned)4);\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_list(P, N)\
    {\
	calculus *x184_ = GEN_calculus(4, TYPEID_list);\
	unsigned a184_ = (N);\
	x184_->ag_tag = 6;\
	x184_[3].ag_tag = a184_;\
	set_calculus_alias(x184_ + 3, a184_);\
	(P) = x184_;\
    }

#define GET_ALIAS_type_list(P)		(((P) + 3)->ag_tag)
#define SET_ALIAS_type_list(P, N)	set_calculus_alias((P) + 3, (N))
#define FIND_ALIAS_type_list(N)		(find_calculus_alias(N) - 3)

#endif


/* Operations for field stack of union TYPE */

#define type_stack_tag			((unsigned)7)
#define IS_type_stack(P)		((P)->ag_tag == 7)

#define type_stack_sub(P)		((P) + 2)

#define MAKE_type_stack(size_, sub_, calculus_type)\
    {\
	calculus *x185_ = GEN_calculus(4, TYPEID_type);\
	x185_->ag_tag = 7;\
	COPY_int(x185_ + 1, (size_));\
	COPY_ptr(x185_ + 2, (sub_));\
	x185_[3].ag_tag = 0;\
	(calculus_type) = x185_;\
    }

#define DECONS_type_stack(size_, sub_, calculus_type)\
    {\
	calculus *x186_ = (calculus_type);\
	(size_) = DEREF_int(x186_ + 1);\
	(sub_) = DEREF_ptr(x186_ + 2);\
    }

#define DESTROY_type_stack(destroyer_, size_, sub_, calculus_type)\
    {\
	calculus *x187_ = (calculus_type);\
	(size_) = DEREF_int(x187_ + 1);\
	(sub_) = DEREF_ptr(x187_ + 2);\
	(destroyer_)(x187_, (unsigned)4);\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_stack(P, N)\
    {\
	calculus *x188_ = GEN_calculus(4, TYPEID_list);\
	unsigned a188_ = (N);\
	x188_->ag_tag = 7;\
	x188_[3].ag_tag = a188_;\
	set_calculus_alias(x188_ + 3, a188_);\
	(P) = x188_;\
    }

#define GET_ALIAS_type_stack(P)		(((P) + 3)->ag_tag)
#define SET_ALIAS_type_stack(P, N)	set_calculus_alias((P) + 3, (N))
#define FIND_ALIAS_type_stack(N)	(find_calculus_alias(N) - 3)

#endif


/* Operations for field vec of union TYPE */

#define type_vec_tag			((unsigned)8)
#define IS_type_vec(P)			((P)->ag_tag == 8)

#define type_vec_sub(P)			((P) + 2)

#define MAKE_type_vec(size_, sub_, calculus_type)\
    {\
	calculus *x189_ = GEN_calculus(4, TYPEID_type);\
	x189_->ag_tag = 8;\
	COPY_int(x189_ + 1, (size_));\
	COPY_ptr(x189_ + 2, (sub_));\
	x189_[3].ag_tag = 0;\
	(calculus_type) = x189_;\
    }

#define DECONS_type_vec(size_, sub_, calculus_type)\
    {\
	calculus *x190_ = (calculus_type);\
	(size_) = DEREF_int(x190_ + 1);\
	(sub_) = DEREF_ptr(x190_ + 2);\
    }

#define DESTROY_type_vec(destroyer_, size_, sub_, calculus_type)\
    {\
	calculus *x191_ = (calculus_type);\
	(size_) = DEREF_int(x191_ + 1);\
	(sub_) = DEREF_ptr(x191_ + 2);\
	(destroyer_)(x191_, (unsigned)4);\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_vec(P, N)\
    {\
	calculus *x192_ = GEN_calculus(4, TYPEID_list);\
	unsigned a192_ = (N);\
	x192_->ag_tag = 8;\
	x192_[3].ag_tag = a192_;\
	set_calculus_alias(x192_ + 3, a192_);\
	(P) = x192_;\
    }

#define GET_ALIAS_type_vec(P)		(((P) + 3)->ag_tag)
#define SET_ALIAS_type_vec(P, N)	set_calculus_alias((P) + 3, (N))
#define FIND_ALIAS_type_vec(N)		(find_calculus_alias(N) - 3)

#endif


/* Operations for field vec_ptr of union TYPE */

#define type_vec_ptr_tag		((unsigned)9)
#define IS_type_vec_ptr(P)		((P)->ag_tag == 9)

#define type_vec_ptr_sub(P)		((P) + 2)

#define MAKE_type_vec_ptr(size_, sub_, calculus_type)\
    {\
	calculus *x193_ = GEN_calculus(4, TYPEID_type);\
	x193_->ag_tag = 9;\
	COPY_int(x193_ + 1, (size_));\
	COPY_ptr(x193_ + 2, (sub_));\
	x193_[3].ag_tag = 0;\
	(calculus_type) = x193_;\
    }

#define DECONS_type_vec_ptr(size_, sub_, calculus_type)\
    {\
	calculus *x194_ = (calculus_type);\
	(size_) = DEREF_int(x194_ + 1);\
	(sub_) = DEREF_ptr(x194_ + 2);\
    }

#define DESTROY_type_vec_ptr(destroyer_, size_, sub_, calculus_type)\
    {\
	calculus *x195_ = (calculus_type);\
	(size_) = DEREF_int(x195_ + 1);\
	(sub_) = DEREF_ptr(x195_ + 2);\
	(destroyer_)(x195_, (unsigned)4);\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_vec_ptr(P, N)\
    {\
	calculus *x196_ = GEN_calculus(4, TYPEID_list);\
	unsigned a196_ = (N);\
	x196_->ag_tag = 9;\
	x196_[3].ag_tag = a196_;\
	set_calculus_alias(x196_ + 3, a196_);\
	(P) = x196_;\
    }

#define GET_ALIAS_type_vec_ptr(P)	(((P) + 3)->ag_tag)
#define SET_ALIAS_type_vec_ptr(P, N)	set_calculus_alias((P) + 3, (N))
#define FIND_ALIAS_type_vec_ptr(N)	(find_calculus_alias(N) - 3)

#endif


/* Operations for field quote of union TYPE */

#define type_quote_tag			((unsigned)10)
#define IS_type_quote(P)		((P)->ag_tag == 10)

#define type_quote_defn(P)		((P) + 2)

#define MAKE_type_quote(size_, defn_, calculus_type)\
    {\
	calculus *x197_ = GEN_calculus(3, TYPEID_type);\
	x197_->ag_tag = 10;\
	COPY_int(x197_ + 1, (size_));\
	COPY_string(x197_ + 2, (defn_));\
	(calculus_type) = x197_;\
    }

#define DECONS_type_quote(size_, defn_, calculus_type)\
    {\
	calculus *x198_ = (calculus_type);\
	(size_) = DEREF_int(x198_ + 1);\
	(defn_) = DEREF_string(x198_ + 2);\
    }

#define DESTROY_type_quote(destroyer_, size_, defn_, calculus_type)\
    {\
	calculus *x199_ = (calculus_type);\
	(size_) = DEREF_int(x199_ + 1);\
	(defn_) = DEREF_string(x199_ + 2);\
	(destroyer_)(x199_, (unsigned)3);\
    }


/* Operations for field undef of union TYPE */

#define type_undef_tag			((unsigned)11)
#define IS_type_undef(P)		((P)->ag_tag == 11)

#define type_undef_name(P)		((P) + 2)

#define MAKE_type_undef(size_, name_, calculus_type)\
    {\
	calculus *x200_ = GEN_calculus(3, TYPEID_type);\
	x200_->ag_tag = 11;\
	COPY_int(x200_ + 1, (size_));\
	COPY_string(x200_ + 2, (name_));\
	(calculus_type) = x200_;\
    }

#define DECONS_type_undef(size_, name_, calculus_type)\
    {\
	calculus *x201_ = (calculus_type);\
	(size_) = DEREF_int(x201_ + 1);\
	(name_) = DEREF_string(x201_ + 2);\
    }

#define DESTROY_type_undef(destroyer_, size_, name_, calculus_type)\
    {\
	calculus *x202_ = (calculus_type);\
	(size_) = DEREF_int(x202_ + 1);\
	(name_) = DEREF_string(x202_ + 2);\
	(destroyer_)(x202_, (unsigned)3);\
    }


#endif
