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

#ifndef CALCULUS_H_INCLUDED
#define CALCULUS_H_INCLUDED

#ifndef calculus_NAME
#define calculus_NAME			"calculus"
#define calculus_VERSION		"1.2"
#define calculus_SPECIFICATION		0
#define calculus_IMPLEMENTATION		1
#endif


/* Primitive types */

typedef unsigned long number;
typedef char * string;


/* Basic types */

typedef unsigned calculus_dim;

typedef union calculus_tag {
    unsigned ag_tag;
    union calculus_tag *ag_ptr;
    calculus_dim ag_dim;
    unsigned ag_enum;
    unsigned long ag_long_enum;
    int ag_prim_int;
    number ag_prim_number;
    string ag_prim_string;
} calculus;

typedef calculus *calculus_PTR;

typedef struct {
    calculus *vec;
    calculus *ptr;
} calculus_VEC_PTR;

typedef struct {
    calculus_dim dim;
    calculus_VEC_PTR elems;
} calculus_VEC;

#ifndef calculus_DESTR_DEFINED
#define calculus_DESTR_DEFINED
typedef void (*DESTROYER)(calculus *, unsigned);
#endif

#define PTR(A)	calculus_PTR
#define LIST(A)	calculus_PTR
#define STACK(A)	calculus_PTR
#define VEC(A)	calculus_VEC
#define VEC_PTR(A)	calculus_VEC_PTR
#define SIZE(A)	int


/* Enumeration definitions */



/* Union type definitions */

typedef calculus *TYPE;
typedef calculus *COMMAND;


/* Structure declarations */

typedef struct alg_tag ALGEBRA_DEFN;
typedef struct cid_tag CLASS_ID;
typedef struct prim_tag PRIMITIVE;
typedef struct ec_tag ECONST;
typedef struct en_tag ENUM;
typedef struct ident_tag IDENTITY;
typedef struct cmp_tag COMPONENT;
typedef struct str_tag STRUCTURE;
typedef struct fld_tag FIELD;
typedef struct arg_tag ARGUMENT;
typedef struct map_tag MAP;
typedef struct un_tag UNION;


/* Identity type definitions */

typedef string name_string;
typedef int zero_int;
typedef PTR(int) int_P;
typedef PTR(number) number_P;
typedef PTR(string) string_P;
typedef PTR(ARGUMENT) ARGUMENT_P;
typedef PTR(CLASS_ID) CLASS_ID_P;
typedef PTR(CLASS_ID_P) CLASS_ID_P_P;
typedef PTR(COMPONENT) COMPONENT_P;
typedef PTR(ECONST) ECONST_P;
typedef PTR(ENUM) ENUM_P;
typedef PTR(FIELD) FIELD_P;
typedef PTR(IDENTITY) IDENTITY_P;
typedef PTR(MAP) MAP_P;
typedef PTR(PRIMITIVE) PRIMITIVE_P;
typedef PTR(STRUCTURE) STRUCTURE_P;
typedef PTR(TYPE) TYPE_P;
typedef PTR(TYPE_P) TYPE_P_P;
typedef PTR(UNION) UNION_P;


/* Structure definitions */

#ifndef calculus_STRUCT_DEFINED
#define calculus_STRUCT_DEFINED

struct alg_tag {
    string name;
    int major_no;
    int minor_no;
    LIST(PRIMITIVE_P) primitives;
    LIST(IDENTITY_P) identities;
    LIST(ENUM_P) enumerations;
    LIST(STRUCTURE_P) structures;
    LIST(UNION_P) unions;
    LIST(TYPE_P) types;
};

struct cid_tag {
    string name;
    string name_aux;
    int flag;
    name_string file;
    int line;
};

struct prim_tag {
    CLASS_ID_P id;
    string defn;
};

struct ec_tag {
    string name;
    number value;
};

struct en_tag {
    CLASS_ID_P id;
    LIST(ECONST_P) consts;
    number order;
    int lists;
};

struct ident_tag {
    CLASS_ID_P id;
    TYPE_P defn;
};

struct cmp_tag {
    string name;
    TYPE_P type;
    string value;
};

struct str_tag {
    CLASS_ID_P id;
    STRUCTURE_P base;
    LIST(COMPONENT_P) defn;
    zero_int output;
};

struct fld_tag {
    string name;
    int tag;
    int flag;
    int set;
    FIELD_P base;
    LIST(COMPONENT_P) defn;
};

struct arg_tag {
    string name;
    TYPE_P type;
};

struct map_tag {
    string name;
    int flag;
    TYPE_P ret_type;
    LIST(ARGUMENT_P) args;
};

struct un_tag {
    CLASS_ID_P id;
    UNION_P base;
    LIST(COMPONENT_P) s_defn;
    LIST(FIELD_P) u_defn;
    LIST(MAP_P) map;
    int no_fields;
};

#endif /* calculus_STRUCT_DEFINED */


/* Function declarations */

extern calculus *gen_calculus(unsigned);
extern void destroy_calculus(calculus *, unsigned);
extern void dummy_destroy_calculus (calculus *, unsigned);
extern void destroy_calculus_list (calculus *, unsigned);
extern calculus *append_calculus_list(calculus *, calculus *);
extern calculus *end_calculus_list(calculus *);
extern unsigned length_calculus_list(calculus *);
extern calculus *reverse_calculus_list(calculus *);
extern calculus_VEC empty_calculus_vec;
#ifdef calculus_IO_ROUTINES
extern unsigned crt_calculus_alias;
extern void set_calculus_alias(calculus *, unsigned);
extern calculus *find_calculus_alias(unsigned);
extern void clear_calculus_alias(void);
#endif


/* Run-time type information */

#ifndef GEN_calculus
#define GEN_calculus(A, B)		gen_calculus((unsigned)(A))
#endif
#define TYPEID_ptr			((unsigned)0)
#define TYPEID_list			((unsigned)1)
#define TYPEID_stack			((unsigned)2)
#define TYPEID_type			((unsigned)3)
#define TYPEID_cmd			((unsigned)4)


/* Definitions for pointers */

#define STEP_ptr(A, B)			((A) + B)
#define SIZE_ptr(A)			1
#define NULL_ptr(A)			((calculus *)0)
#define IS_NULL_ptr(A)			((A) == 0)
#define EQ_ptr(A, B)			((A) == (B))
#define MAKE_ptr(A)			GEN_calculus((A), TYPEID_ptr)
#define DESTROY_ptr(A, B)		destroy_calculus((A), (unsigned)(B))
#define UNIQ_ptr(A)			GEN_calculus(1, TYPEID_ptr)
#define DESTROY_UNIQ_ptr(A)		destroy_calculus((A), (unsigned)1)
#ifdef calculus_IO_ROUTINES
#define VOIDSTAR_ptr(A)			((void *)(A))
#endif

#define COPY_ptr(A, B)			((A)->ag_ptr = (B))
#define DEREF_ptr(A)			((A)->ag_ptr)
#define CONS_ptr(A, B, C)\
    {\
	calculus *x0_ = GEN_calculus(2, TYPEID_list);\
	x0_[1].ag_ptr = (A);\
	x0_->ag_ptr = (B);\
	(C) = x0_;\
    }

#define UN_CONS_ptr(A, B, C)\
    {\
	calculus *x1_ = (C);\
	(A) = x1_[1].ag_ptr;\
	(B) = x1_->ag_ptr;\
    }

#define DESTROY_CONS_ptr(D, A, B, C)\
    {\
	calculus *x2_ = (C);\
	(A) = x2_[1].ag_ptr;\
	(B) = x2_->ag_ptr;\
	(D)(x2_, (unsigned)2);\
    }

#define PUSH_ptr(A, B)\
    {\
	calculus **r3_ = &(B);\
	calculus *x3_ = GEN_calculus(2, TYPEID_stack);\
	x3_[1].ag_ptr = (A);\
	x3_->ag_ptr = *r3_;\
	*r3_ = x3_;\
    }

#define POP_ptr(A, B)\
    {\
	calculus **r4_ = &(B);\
	calculus *x4_ = (*r4_);\
	(A) = x4_[1].ag_ptr;\
	*r4_ = x4_->ag_ptr;\
	destroy_calculus(x4_, (unsigned)2);\
    }


/* Definitions for lists */

#define HEAD_list(A)			((A) + 1)
#define PTR_TAIL_list(A)		((A))
#define TAIL_list(A)			((A)->ag_ptr)
#define LENGTH_list(A)			length_calculus_list((A))
#define END_list(A)			end_calculus_list((A))
#define REVERSE_list(A)			reverse_calculus_list((A))
#define APPEND_list(A, B)		append_calculus_list((A), (B))

#define SIZE_list(A)			1
#define NULL_list(A)			((calculus *) 0)
#define IS_NULL_list(A)			((A) == 0)
#define EQ_list(A, B)			((A) == (B))
#define UNIQ_list(A)			GEN_calculus(1, TYPEID_list)
#define DESTROY_UNIQ_list(A)		destroy_calculus((A), (unsigned)1)
#ifdef calculus_IO_ROUTINES
#define VOIDSTAR_list(A)		((void *)(A))
#endif

#define DESTROY_list(A, B)\
    {\
	destroy_calculus_list((A), (unsigned)(B));\
    }

#define COPY_list(A, B)			((A)->ag_ptr = (B))
#define DEREF_list(A)			((A)->ag_ptr)
#define CONS_list(A, B, C)\
    {\
	calculus *x5_ = GEN_calculus(2, TYPEID_list);\
	x5_[1].ag_ptr = (A);\
	x5_->ag_ptr = (B);\
	(C) = x5_;\
    }

#define UN_CONS_list(A, B, C)\
    {\
	calculus *x6_ = (C);\
	(A) = x6_[1].ag_ptr;\
	(B) = x6_->ag_ptr;\
    }

#define DESTROY_CONS_list(D, A, B, C)\
    {\
	calculus *x7_ = (C);\
	(A) = x7_[1].ag_ptr;\
	(B) = x7_->ag_ptr;\
	(D)(x7_, (unsigned)2);\
    }

#define PUSH_list(A, B)\
    {\
	calculus **r8_ = &(B);\
	calculus *x8_ = GEN_calculus(2, TYPEID_stack);\
	x8_[1].ag_ptr = (A);\
	x8_->ag_ptr = *r8_;\
	*r8_ = x8_;\
    }

#define POP_list(A, B)\
    {\
	calculus **r9_ = &(B);\
	calculus *x9_ = (*r9_);\
	(A) = x9_[1].ag_ptr;\
	*r9_ = x9_->ag_ptr;\
	destroy_calculus(x9_, (unsigned)2);\
    }


/* Definitions for stacks */

#define SIZE_stack(A)			1
#define NULL_stack(A)			((calculus *) 0)
#define IS_NULL_stack(A)		((A) == 0)
#define STACK_list(A)			(A)
#define LIST_stack(A)			(A)

#define COPY_stack(A, B)		((A)->ag_ptr = (B))
#define DEREF_stack(A)			((A)->ag_ptr)
#define CONS_stack(A, B, C)\
    {\
	calculus *x10_ = GEN_calculus(2, TYPEID_list);\
	x10_[1].ag_ptr = (A);\
	x10_->ag_ptr = (B);\
	(C) = x10_;\
    }

#define UN_CONS_stack(A, B, C)\
    {\
	calculus *x11_ = (C);\
	(A) = x11_[1].ag_ptr;\
	(B) = x11_->ag_ptr;\
    }

#define DESTROY_CONS_stack(D, A, B, C)\
    {\
	calculus *x12_ = (C);\
	(A) = x12_[1].ag_ptr;\
	(B) = x12_->ag_ptr;\
	(D)(x12_, (unsigned)2);\
    }

#define PUSH_stack(A, B)\
    {\
	calculus **r13_ = &(B);\
	calculus *x13_ = GEN_calculus(2, TYPEID_stack);\
	x13_[1].ag_ptr = (A);\
	x13_->ag_ptr = *r13_;\
	*r13_ = x13_;\
    }

#define POP_stack(A, B)\
    {\
	calculus **r14_ = &(B);\
	calculus *x14_ = (*r14_);\
	(A) = x14_[1].ag_ptr;\
	*r14_ = x14_->ag_ptr;\
	destroy_calculus(x14_, (unsigned)2);\
    }


/* Definitions for vectors */

#define DIM_vec(A)			((A).dim)
#define PTR_ptr_vec(A)			((A)[2].ag_ptr)
#define DIM_ptr_vec(A)			((A)->ag_dim)
#define SIZE_vec(A)			3
#define NULL_vec(A)			empty_calculus_vec

#define MAKE_vec(SZ, U, RES)\
    {\
	calculus_VEC x15_;\
	calculus_dim u15_ = (U);\
	x15_.dim = u15_;\
	if (u15_ == 0) u15_ = 1;\
	x15_.elems.ptr = GEN_calculus((SZ)*u15_, TYPEID_ptr);\
	x15_.elems.vec = x15_.elems.ptr;\
	(RES) = x15_;\
    }

#define DESTROY_vec(V, SZ)\
    {\
	calculus_VEC x16_;\
	x16_ = (V);\
	destroy_calculus (x16_.elems.ptr, (unsigned)((SZ)*x16_.dim));\
    }

#define TRIM_vec(V, SZ, L, U, RES)\
    {\
	calculus_VEC x17_;\
	int l17_ = (L);\
	x17_ = (V);\
	x17_.elems.ptr += ((SZ)*l17_);\
	x17_.dim = (unsigned)((U) - l17_);\
	(RES) = x17_;\
    }

#define COPY_vec(A, B)\
    {\
	calculus *x18_ = (A);\
	calculus_VEC y18_;\
	y18_ = (B);\
	x18_[0].ag_dim = y18_.dim;\
	x18_[1].ag_ptr = y18_.elems.vec;\
	x18_[2].ag_ptr = y18_.elems.ptr;\
    }

#define DEREF_vec(A, B)\
    {\
	calculus *x19_ = (A);\
	calculus_VEC *y19_ = &(B);\
	y19_->dim = x19_[0].ag_dim;\
	y19_->elems.vec = x19_[1].ag_ptr;\
	y19_->elems.ptr = x19_[2].ag_ptr;\
    }

#define CONS_vec(A, B, C)\
    {\
	calculus *x20_ = GEN_calculus(4, TYPEID_list);\
	calculus_VEC y20_;\
	y20_ = (A);\
	x20_[1].ag_dim = y20_.dim;\
	x20_[2].ag_ptr = y20_.elems.vec;\
	x20_[3].ag_ptr = y20_.elems.ptr;\
	x20_->ag_ptr = (B);\
	(C) = x20_;\
    }

#define UN_CONS_vec(A, B, C)\
    {\
	calculus *x21_ = (C);\
	calculus_VEC *y21_ = &(A);\
	y21_->dim = x21_[1].ag_dim;\
	y21_->elems.vec = x21_[2].ag_ptr;\
	y21_->elems.ptr = x21_[3].ag_ptr;\
	(B) = x21_->ag_ptr;\
    }

#define DESTROY_CONS_vec(D, A, B, C)\
    {\
	calculus *x22_ = (C);\
	calculus_VEC *y22_ = &(A);\
	y22_->dim = x22_[1].ag_dim;\
	y22_->elems.vec = x22_[2].ag_ptr;\
	y22_->elems.ptr = x22_[3].ag_ptr;\
	(B) = x22_->ag_ptr;\
	(D)(x22_, (unsigned)4);\
    }

#define PUSH_vec(A, B)\
    {\
	calculus **r23_ = &(B);\
	calculus *x23_ = GEN_calculus(4, TYPEID_stack);\
	calculus_VEC y23_;\
	y23_ = (A);\
	x23_[1].ag_dim = y23_.dim;\
	x23_[2].ag_ptr = y23_.elems.vec;\
	x23_[3].ag_ptr = y23_.elems.ptr;\
	x23_->ag_ptr = *r23_;\
	*r23_ = x23_;\
    }

#define POP_vec(A, B)\
    {\
	calculus **r24_ = &(B);\
	calculus *x24_ = (*r24_);\
	calculus_VEC *y24_ = &(A);\
	y24_->dim = x24_[1].ag_dim;\
	y24_->elems.vec = x24_[2].ag_ptr;\
	y24_->elems.ptr = x24_[3].ag_ptr;\
	*r24_ = x24_->ag_ptr;\
	destroy_calculus(x24_, (unsigned)4);\
    }


/* Definitions for vector pointers */

#define VEC_PTR_vec(A)			((A).elems)
#define PTR_vec_ptr(A)			((A).ptr)
#define SIZE_vec_ptr(A)			2

#define COPY_vec_ptr(A, B)\
    {\
	calculus *x25_ = (A);\
	calculus_VEC_PTR y25_;\
	y25_ = (B);\
	x25_->ag_ptr = y25_.vec;\
	x25_[1].ag_ptr = y25_.ptr;\
    }

#define DEREF_vec_ptr(A, B)\
    {\
	calculus *x26_ = (A);\
	calculus_VEC_PTR *y26_ = &(B);\
	y26_->vec = x26_->ag_ptr;\
	y26_->ptr = x26_[1].ag_ptr;\
    }

#define CONS_vec_ptr(A, B, C)\
    {\
	calculus *x27_ = GEN_calculus(3, TYPEID_list);\
	calculus_VEC_PTR y27_;\
	y27_ = (A);\
	x27_[1].ag_ptr = y27_.vec;\
	x27_[2].ag_ptr = y27_.ptr;\
	x27_->ag_ptr = (B);\
	(C) = x27_;\
    }

#define UN_CONS_vec_ptr(A, B, C)\
    {\
	calculus *x28_ = (C);\
	calculus_VEC_PTR *y28_ = &(A);\
	y28_->vec = x28_[1].ag_ptr;\
	y28_->ptr = x28_[2].ag_ptr;\
	(B) = x28_->ag_ptr;\
    }

#define DESTROY_CONS_vec_ptr(D, A, B, C)\
    {\
	calculus *x29_ = (C);\
	calculus_VEC_PTR *y29_ = &(A);\
	y29_->vec = x29_[1].ag_ptr;\
	y29_->ptr = x29_[2].ag_ptr;\
	(B) = x29_->ag_ptr;\
	(D)(x29_, (unsigned)3);\
    }

#define PUSH_vec_ptr(A, B)\
    {\
	calculus **r30_ = &(B);\
	calculus *x30_ = GEN_calculus(3, TYPEID_stack);\
	calculus_VEC_PTR y30_;\
	y30_ = (A);\
	x30_[1].ag_ptr = y30_.vec;\
	x30_[2].ag_ptr = y30_.ptr;\
	x30_->ag_ptr = *r30_;\
	*r30_ = x30_;\
    }

#define POP_vec_ptr(A, B)\
    {\
	calculus **r31_ = &(B);\
	calculus *x31_ = (*r31_);\
	calculus_VEC *y31_ = &(A);\
	y31_->vec = x31_[1].ag_ptr;\
	y31_->ptr = x31_[2].ag_ptr;\
	*r31_ = x31_->ag_ptr;\
	destroy_calculus(x31_, (unsigned)3);\
    }


/* Definitions for sizes */

#define SCALE(A, B)			((A)*(int)(B))


/* Definitions for primitive int */

#define SIZE_int			1

#define COPY_int(A, B)			((A)->ag_prim_int = (B))
#define DEREF_int(A)			((A)->ag_prim_int)
#define CONS_int(A, B, C)\
    {\
	calculus *x32_ = GEN_calculus(2, TYPEID_list);\
	COPY_int(x32_ + 1, (A));\
	x32_->ag_ptr = (B);\
	(C) = x32_;\
    }

#define UN_CONS_int(A, B, C)\
    {\
	calculus *x33_ = (C);\
	(A) = DEREF_int(x33_ + 1);\
	(B) = x33_->ag_ptr;\
    }

#define DESTROY_CONS_int(D, A, B, C)\
    {\
	calculus *x34_ = (C);\
	(A) = DEREF_int(x34_ + 1);\
	(B) = x34_->ag_ptr;\
	(D)(x34_, (unsigned)2);\
    }

#define PUSH_int(A, B)\
    {\
	calculus **r35_ = &(B);\
	calculus *x35_ = GEN_calculus(2, TYPEID_stack);\
	COPY_int(x35_ + 1, (A));\
	x35_->ag_ptr = *r35_;\
	*r35_ = x35_;\
    }

#define POP_int(A, B)\
    {\
	calculus **r36_ = &(B);\
	calculus *x36_ = (*r36_);\
	(A) = DEREF_int(x36_ + 1);\
	*r36_ = x36_->ag_ptr;\
	destroy_calculus(x36_, (unsigned)2);\
    }


/* Definitions for primitive number */

#define SIZE_number			1

#define COPY_number(A, B)		((A)->ag_prim_number = (B))
#define DEREF_number(A)			((A)->ag_prim_number)
#define CONS_number(A, B, C)\
    {\
	calculus *x37_ = GEN_calculus(2, TYPEID_list);\
	COPY_number(x37_ + 1, (A));\
	x37_->ag_ptr = (B);\
	(C) = x37_;\
    }

#define UN_CONS_number(A, B, C)\
    {\
	calculus *x38_ = (C);\
	(A) = DEREF_number(x38_ + 1);\
	(B) = x38_->ag_ptr;\
    }

#define DESTROY_CONS_number(D, A, B, C)\
    {\
	calculus *x39_ = (C);\
	(A) = DEREF_number(x39_ + 1);\
	(B) = x39_->ag_ptr;\
	(D)(x39_, (unsigned)2);\
    }

#define PUSH_number(A, B)\
    {\
	calculus **r40_ = &(B);\
	calculus *x40_ = GEN_calculus(2, TYPEID_stack);\
	COPY_number(x40_ + 1, (A));\
	x40_->ag_ptr = *r40_;\
	*r40_ = x40_;\
    }

#define POP_number(A, B)\
    {\
	calculus **r41_ = &(B);\
	calculus *x41_ = (*r41_);\
	(A) = DEREF_number(x41_ + 1);\
	*r41_ = x41_->ag_ptr;\
	destroy_calculus(x41_, (unsigned)2);\
    }


/* Definitions for primitive string */

#define SIZE_string			1

#define COPY_string(A, B)		((A)->ag_prim_string = (B))
#define DEREF_string(A)			((A)->ag_prim_string)
#define CONS_string(A, B, C)\
    {\
	calculus *x42_ = GEN_calculus(2, TYPEID_list);\
	COPY_string(x42_ + 1, (A));\
	x42_->ag_ptr = (B);\
	(C) = x42_;\
    }

#define UN_CONS_string(A, B, C)\
    {\
	calculus *x43_ = (C);\
	(A) = DEREF_string(x43_ + 1);\
	(B) = x43_->ag_ptr;\
    }

#define DESTROY_CONS_string(D, A, B, C)\
    {\
	calculus *x44_ = (C);\
	(A) = DEREF_string(x44_ + 1);\
	(B) = x44_->ag_ptr;\
	(D)(x44_, (unsigned)2);\
    }

#define PUSH_string(A, B)\
    {\
	calculus **r45_ = &(B);\
	calculus *x45_ = GEN_calculus(2, TYPEID_stack);\
	COPY_string(x45_ + 1, (A));\
	x45_->ag_ptr = *r45_;\
	*r45_ = x45_;\
    }

#define POP_string(A, B)\
    {\
	calculus **r46_ = &(B);\
	calculus *x46_ = (*r46_);\
	(A) = DEREF_string(x46_ + 1);\
	*r46_ = x46_->ag_ptr;\
	destroy_calculus(x46_, (unsigned)2);\
    }


/* Definitions for structure ALGEBRA_DEFN */

#define alg_name(P)			((P) + 0)
#define alg_major_no(P)			((P) + 1)
#define alg_minor_no(P)			((P) + 2)
#define alg_primitives(P)		((P) + 3)
#define alg_identities(P)		((P) + 4)
#define alg_enumerations(P)		((P) + 5)
#define alg_structures(P)		((P) + 6)
#define alg_unions(P)			((P) + 7)
#define alg_types(P)			((P) + 8)
#define SIZE_alg			9

#define COPY_alg(A, B)\
    {\
	calculus *x47_ = (A);\
	ALGEBRA_DEFN y47_;\
	y47_ = (B);\
	COPY_string(x47_ + 0, y47_.name);\
	COPY_int(x47_ + 1, y47_.major_no);\
	COPY_int(x47_ + 2, y47_.minor_no);\
	COPY_list(x47_ + 3, y47_.primitives);\
	COPY_list(x47_ + 4, y47_.identities);\
	COPY_list(x47_ + 5, y47_.enumerations);\
	COPY_list(x47_ + 6, y47_.structures);\
	COPY_list(x47_ + 7, y47_.unions);\
	COPY_list(x47_ + 8, y47_.types);\
    }

#define DEREF_alg(A, B)\
    {\
	calculus *x48_ = (A);\
	ALGEBRA_DEFN *y48_ = &(B);\
	y48_->name = DEREF_string(x48_ + 0);\
	y48_->major_no = DEREF_int(x48_ + 1);\
	y48_->minor_no = DEREF_int(x48_ + 2);\
	y48_->primitives = DEREF_list(x48_ + 3);\
	y48_->identities = DEREF_list(x48_ + 4);\
	y48_->enumerations = DEREF_list(x48_ + 5);\
	y48_->structures = DEREF_list(x48_ + 6);\
	y48_->unions = DEREF_list(x48_ + 7);\
	y48_->types = DEREF_list(x48_ + 8);\
    }

#define MAKE_alg(name_, major_no_, minor_no_, primitives_, identities_, enumerations_, structures_, unions_, types_, alg_)\
    {\
	calculus *x49_ = (alg_);\
	COPY_string(x49_ + 0, (name_));\
	COPY_int(x49_ + 1, (major_no_));\
	COPY_int(x49_ + 2, (minor_no_));\
	COPY_list(x49_ + 3, (primitives_));\
	COPY_list(x49_ + 4, (identities_));\
	COPY_list(x49_ + 5, (enumerations_));\
	COPY_list(x49_ + 6, (structures_));\
	COPY_list(x49_ + 7, (unions_));\
	COPY_list(x49_ + 8, (types_));\
    }

#define CONS_alg(A, B, C)\
    {\
	calculus *x50_ = GEN_calculus(10, TYPEID_list);\
	COPY_alg(x50_ + 1, (A));\
	x50_->ag_ptr = (B);\
	(C) = x50_;\
    }

#define UN_CONS_alg(A, B, C)\
    {\
	calculus *x51_ = (C);\
	DEREF_alg(x51_ + 1, (A));\
	(B) = x51_->ag_ptr;\
    }

#define DESTROY_CONS_alg(D, A, B, C)\
    {\
	calculus *x52_ = (C);\
	DEREF_alg(x52_ + 1, (A));\
	(B) = x52_->ag_ptr;\
	(D)(x52_, (unsigned)10);\
    }

#define PUSH_alg(A, B)\
    {\
	calculus **r53_ = &(B);\
	calculus *x53_ = GEN_calculus(10, TYPEID_stack);\
	COPY_alg(x53_ + 1, (A));\
	x53_->ag_ptr = *r53_;\
	*r53_ = x53_;\
    }

#define POP_alg(A, B)\
    {\
	calculus **r54_ = &(B);\
	calculus *x54_ = (*r54_);\
	DEREF_alg(x54_ + 1, (A));\
	*r54_ = x54_->ag_ptr;\
	destroy_calculus(x54_, (unsigned)10);\
    }


/* Definitions for structure CLASS_ID */

#define cid_name(P)			((P) + 0)
#define cid_name_aux(P)			((P) + 1)
#define cid_flag(P)			((P) + 2)
#define cid_file(P)			((P) + 3)
#define cid_line(P)			((P) + 4)
#define SIZE_cid			5

#define COPY_cid(A, B)\
    {\
	calculus *x55_ = (A);\
	CLASS_ID y55_;\
	y55_ = (B);\
	COPY_string(x55_ + 0, y55_.name);\
	COPY_string(x55_ + 1, y55_.name_aux);\
	COPY_int(x55_ + 2, y55_.flag);\
	COPY_string(x55_ + 3, y55_.file);\
	COPY_int(x55_ + 4, y55_.line);\
    }

#define DEREF_cid(A, B)\
    {\
	calculus *x56_ = (A);\
	CLASS_ID *y56_ = &(B);\
	y56_->name = DEREF_string(x56_ + 0);\
	y56_->name_aux = DEREF_string(x56_ + 1);\
	y56_->flag = DEREF_int(x56_ + 2);\
	y56_->file = DEREF_string(x56_ + 3);\
	y56_->line = DEREF_int(x56_ + 4);\
    }

#define MAKE_cid(name_, name_aux_, flag_, file_, line_, cid_)\
    {\
	calculus *x57_ = (cid_);\
	COPY_string(x57_ + 0, (name_));\
	COPY_string(x57_ + 1, (name_aux_));\
	COPY_int(x57_ + 2, (flag_));\
	COPY_string(x57_ + 3, (file_));\
	COPY_int(x57_ + 4, (line_));\
    }

#define CONS_cid(A, B, C)\
    {\
	calculus *x58_ = GEN_calculus(6, TYPEID_list);\
	COPY_cid(x58_ + 1, (A));\
	x58_->ag_ptr = (B);\
	(C) = x58_;\
    }

#define UN_CONS_cid(A, B, C)\
    {\
	calculus *x59_ = (C);\
	DEREF_cid(x59_ + 1, (A));\
	(B) = x59_->ag_ptr;\
    }

#define DESTROY_CONS_cid(D, A, B, C)\
    {\
	calculus *x60_ = (C);\
	DEREF_cid(x60_ + 1, (A));\
	(B) = x60_->ag_ptr;\
	(D)(x60_, (unsigned)6);\
    }

#define PUSH_cid(A, B)\
    {\
	calculus **r61_ = &(B);\
	calculus *x61_ = GEN_calculus(6, TYPEID_stack);\
	COPY_cid(x61_ + 1, (A));\
	x61_->ag_ptr = *r61_;\
	*r61_ = x61_;\
    }

#define POP_cid(A, B)\
    {\
	calculus **r62_ = &(B);\
	calculus *x62_ = (*r62_);\
	DEREF_cid(x62_ + 1, (A));\
	*r62_ = x62_->ag_ptr;\
	destroy_calculus(x62_, (unsigned)6);\
    }


/* Definitions for structure PRIMITIVE */

#define prim_id(P)			((P) + 0)
#define prim_defn(P)			((P) + 1)
#define SIZE_prim			2

#define COPY_prim(A, B)\
    {\
	calculus *x63_ = (A);\
	PRIMITIVE y63_;\
	y63_ = (B);\
	COPY_ptr(x63_ + 0, y63_.id);\
	COPY_string(x63_ + 1, y63_.defn);\
    }

#define DEREF_prim(A, B)\
    {\
	calculus *x64_ = (A);\
	PRIMITIVE *y64_ = &(B);\
	y64_->id = DEREF_ptr(x64_ + 0);\
	y64_->defn = DEREF_string(x64_ + 1);\
    }

#define MAKE_prim(id_, defn_, prim_)\
    {\
	calculus *x65_ = (prim_);\
	COPY_ptr(x65_ + 0, (id_));\
	COPY_string(x65_ + 1, (defn_));\
    }

#define CONS_prim(A, B, C)\
    {\
	calculus *x66_ = GEN_calculus(3, TYPEID_list);\
	COPY_prim(x66_ + 1, (A));\
	x66_->ag_ptr = (B);\
	(C) = x66_;\
    }

#define UN_CONS_prim(A, B, C)\
    {\
	calculus *x67_ = (C);\
	DEREF_prim(x67_ + 1, (A));\
	(B) = x67_->ag_ptr;\
    }

#define DESTROY_CONS_prim(D, A, B, C)\
    {\
	calculus *x68_ = (C);\
	DEREF_prim(x68_ + 1, (A));\
	(B) = x68_->ag_ptr;\
	(D)(x68_, (unsigned)3);\
    }

#define PUSH_prim(A, B)\
    {\
	calculus **r69_ = &(B);\
	calculus *x69_ = GEN_calculus(3, TYPEID_stack);\
	COPY_prim(x69_ + 1, (A));\
	x69_->ag_ptr = *r69_;\
	*r69_ = x69_;\
    }

#define POP_prim(A, B)\
    {\
	calculus **r70_ = &(B);\
	calculus *x70_ = (*r70_);\
	DEREF_prim(x70_ + 1, (A));\
	*r70_ = x70_->ag_ptr;\
	destroy_calculus(x70_, (unsigned)3);\
    }


/* Definitions for structure ECONST */

#define ec_name(P)			((P) + 0)
#define ec_value(P)			((P) + 1)
#define SIZE_ec				2

#define COPY_ec(A, B)\
    {\
	calculus *x71_ = (A);\
	ECONST y71_;\
	y71_ = (B);\
	COPY_string(x71_ + 0, y71_.name);\
	COPY_number(x71_ + 1, y71_.value);\
    }

#define DEREF_ec(A, B)\
    {\
	calculus *x72_ = (A);\
	ECONST *y72_ = &(B);\
	y72_->name = DEREF_string(x72_ + 0);\
	y72_->value = DEREF_number(x72_ + 1);\
    }

#define MAKE_ec(name_, value_, ec_)\
    {\
	calculus *x73_ = (ec_);\
	COPY_string(x73_ + 0, (name_));\
	COPY_number(x73_ + 1, (value_));\
    }

#define CONS_ec(A, B, C)\
    {\
	calculus *x74_ = GEN_calculus(3, TYPEID_list);\
	COPY_ec(x74_ + 1, (A));\
	x74_->ag_ptr = (B);\
	(C) = x74_;\
    }

#define UN_CONS_ec(A, B, C)\
    {\
	calculus *x75_ = (C);\
	DEREF_ec(x75_ + 1, (A));\
	(B) = x75_->ag_ptr;\
    }

#define DESTROY_CONS_ec(D, A, B, C)\
    {\
	calculus *x76_ = (C);\
	DEREF_ec(x76_ + 1, (A));\
	(B) = x76_->ag_ptr;\
	(D)(x76_, (unsigned)3);\
    }

#define PUSH_ec(A, B)\
    {\
	calculus **r77_ = &(B);\
	calculus *x77_ = GEN_calculus(3, TYPEID_stack);\
	COPY_ec(x77_ + 1, (A));\
	x77_->ag_ptr = *r77_;\
	*r77_ = x77_;\
    }

#define POP_ec(A, B)\
    {\
	calculus **r78_ = &(B);\
	calculus *x78_ = (*r78_);\
	DEREF_ec(x78_ + 1, (A));\
	*r78_ = x78_->ag_ptr;\
	destroy_calculus(x78_, (unsigned)3);\
    }


/* Definitions for structure ENUM */

#define en_id(P)			((P) + 0)
#define en_consts(P)			((P) + 1)
#define en_order(P)			((P) + 2)
#define en_lists(P)			((P) + 3)
#define SIZE_en				4

#define COPY_en(A, B)\
    {\
	calculus *x79_ = (A);\
	ENUM y79_;\
	y79_ = (B);\
	COPY_ptr(x79_ + 0, y79_.id);\
	COPY_list(x79_ + 1, y79_.consts);\
	COPY_number(x79_ + 2, y79_.order);\
	COPY_int(x79_ + 3, y79_.lists);\
    }

#define DEREF_en(A, B)\
    {\
	calculus *x80_ = (A);\
	ENUM *y80_ = &(B);\
	y80_->id = DEREF_ptr(x80_ + 0);\
	y80_->consts = DEREF_list(x80_ + 1);\
	y80_->order = DEREF_number(x80_ + 2);\
	y80_->lists = DEREF_int(x80_ + 3);\
    }

#define MAKE_en(id_, consts_, order_, lists_, en_)\
    {\
	calculus *x81_ = (en_);\
	COPY_ptr(x81_ + 0, (id_));\
	COPY_list(x81_ + 1, (consts_));\
	COPY_number(x81_ + 2, (order_));\
	COPY_int(x81_ + 3, (lists_));\
    }

#define CONS_en(A, B, C)\
    {\
	calculus *x82_ = GEN_calculus(5, TYPEID_list);\
	COPY_en(x82_ + 1, (A));\
	x82_->ag_ptr = (B);\
	(C) = x82_;\
    }

#define UN_CONS_en(A, B, C)\
    {\
	calculus *x83_ = (C);\
	DEREF_en(x83_ + 1, (A));\
	(B) = x83_->ag_ptr;\
    }

#define DESTROY_CONS_en(D, A, B, C)\
    {\
	calculus *x84_ = (C);\
	DEREF_en(x84_ + 1, (A));\
	(B) = x84_->ag_ptr;\
	(D)(x84_, (unsigned)5);\
    }

#define PUSH_en(A, B)\
    {\
	calculus **r85_ = &(B);\
	calculus *x85_ = GEN_calculus(5, TYPEID_stack);\
	COPY_en(x85_ + 1, (A));\
	x85_->ag_ptr = *r85_;\
	*r85_ = x85_;\
    }

#define POP_en(A, B)\
    {\
	calculus **r86_ = &(B);\
	calculus *x86_ = (*r86_);\
	DEREF_en(x86_ + 1, (A));\
	*r86_ = x86_->ag_ptr;\
	destroy_calculus(x86_, (unsigned)5);\
    }


/* Definitions for structure IDENTITY */

#define ident_id(P)			((P) + 0)
#define ident_defn(P)			((P) + 1)
#define SIZE_ident			2

#define COPY_ident(A, B)\
    {\
	calculus *x87_ = (A);\
	IDENTITY y87_;\
	y87_ = (B);\
	COPY_ptr(x87_ + 0, y87_.id);\
	COPY_ptr(x87_ + 1, y87_.defn);\
    }

#define DEREF_ident(A, B)\
    {\
	calculus *x88_ = (A);\
	IDENTITY *y88_ = &(B);\
	y88_->id = DEREF_ptr(x88_ + 0);\
	y88_->defn = DEREF_ptr(x88_ + 1);\
    }

#define MAKE_ident(id_, defn_, ident_)\
    {\
	calculus *x89_ = (ident_);\
	COPY_ptr(x89_ + 0, (id_));\
	COPY_ptr(x89_ + 1, (defn_));\
    }

#define CONS_ident(A, B, C)\
    {\
	calculus *x90_ = GEN_calculus(3, TYPEID_list);\
	COPY_ident(x90_ + 1, (A));\
	x90_->ag_ptr = (B);\
	(C) = x90_;\
    }

#define UN_CONS_ident(A, B, C)\
    {\
	calculus *x91_ = (C);\
	DEREF_ident(x91_ + 1, (A));\
	(B) = x91_->ag_ptr;\
    }

#define DESTROY_CONS_ident(D, A, B, C)\
    {\
	calculus *x92_ = (C);\
	DEREF_ident(x92_ + 1, (A));\
	(B) = x92_->ag_ptr;\
	(D)(x92_, (unsigned)3);\
    }

#define PUSH_ident(A, B)\
    {\
	calculus **r93_ = &(B);\
	calculus *x93_ = GEN_calculus(3, TYPEID_stack);\
	COPY_ident(x93_ + 1, (A));\
	x93_->ag_ptr = *r93_;\
	*r93_ = x93_;\
    }

#define POP_ident(A, B)\
    {\
	calculus **r94_ = &(B);\
	calculus *x94_ = (*r94_);\
	DEREF_ident(x94_ + 1, (A));\
	*r94_ = x94_->ag_ptr;\
	destroy_calculus(x94_, (unsigned)3);\
    }


/* Definitions for structure COMPONENT */

#define cmp_name(P)			((P) + 0)
#define cmp_type(P)			((P) + 1)
#define cmp_value(P)			((P) + 2)
#define SIZE_cmp			3

#define COPY_cmp(A, B)\
    {\
	calculus *x95_ = (A);\
	COMPONENT y95_;\
	y95_ = (B);\
	COPY_string(x95_ + 0, y95_.name);\
	COPY_ptr(x95_ + 1, y95_.type);\
	COPY_string(x95_ + 2, y95_.value);\
    }

#define DEREF_cmp(A, B)\
    {\
	calculus *x96_ = (A);\
	COMPONENT *y96_ = &(B);\
	y96_->name = DEREF_string(x96_ + 0);\
	y96_->type = DEREF_ptr(x96_ + 1);\
	y96_->value = DEREF_string(x96_ + 2);\
    }

#define MAKE_cmp(name_, type_, value_, cmp_)\
    {\
	calculus *x97_ = (cmp_);\
	COPY_string(x97_ + 0, (name_));\
	COPY_ptr(x97_ + 1, (type_));\
	COPY_string(x97_ + 2, (value_));\
    }

#define CONS_cmp(A, B, C)\
    {\
	calculus *x98_ = GEN_calculus(4, TYPEID_list);\
	COPY_cmp(x98_ + 1, (A));\
	x98_->ag_ptr = (B);\
	(C) = x98_;\
    }

#define UN_CONS_cmp(A, B, C)\
    {\
	calculus *x99_ = (C);\
	DEREF_cmp(x99_ + 1, (A));\
	(B) = x99_->ag_ptr;\
    }

#define DESTROY_CONS_cmp(D, A, B, C)\
    {\
	calculus *x100_ = (C);\
	DEREF_cmp(x100_ + 1, (A));\
	(B) = x100_->ag_ptr;\
	(D)(x100_, (unsigned)4);\
    }

#define PUSH_cmp(A, B)\
    {\
	calculus **r101_ = &(B);\
	calculus *x101_ = GEN_calculus(4, TYPEID_stack);\
	COPY_cmp(x101_ + 1, (A));\
	x101_->ag_ptr = *r101_;\
	*r101_ = x101_;\
    }

#define POP_cmp(A, B)\
    {\
	calculus **r102_ = &(B);\
	calculus *x102_ = (*r102_);\
	DEREF_cmp(x102_ + 1, (A));\
	*r102_ = x102_->ag_ptr;\
	destroy_calculus(x102_, (unsigned)4);\
    }


/* Definitions for structure STRUCTURE */

#define str_id(P)			((P) + 0)
#define str_base(P)			((P) + 1)
#define str_defn(P)			((P) + 2)
#define str_output(P)			((P) + 3)
#define SIZE_str			4

#define COPY_str(A, B)\
    {\
	calculus *x103_ = (A);\
	STRUCTURE y103_;\
	y103_ = (B);\
	COPY_ptr(x103_ + 0, y103_.id);\
	COPY_ptr(x103_ + 1, y103_.base);\
	COPY_list(x103_ + 2, y103_.defn);\
	COPY_int(x103_ + 3, y103_.output);\
    }

#define DEREF_str(A, B)\
    {\
	calculus *x104_ = (A);\
	STRUCTURE *y104_ = &(B);\
	y104_->id = DEREF_ptr(x104_ + 0);\
	y104_->base = DEREF_ptr(x104_ + 1);\
	y104_->defn = DEREF_list(x104_ + 2);\
	y104_->output = DEREF_int(x104_ + 3);\
    }

#define MAKE_str(id_, base_, defn_, output_, str_)\
    {\
	calculus *x105_ = (str_);\
	COPY_ptr(x105_ + 0, (id_));\
	COPY_ptr(x105_ + 1, (base_));\
	COPY_list(x105_ + 2, (defn_));\
	COPY_int(x105_ + 3, (output_));\
    }

#define CONS_str(A, B, C)\
    {\
	calculus *x106_ = GEN_calculus(5, TYPEID_list);\
	COPY_str(x106_ + 1, (A));\
	x106_->ag_ptr = (B);\
	(C) = x106_;\
    }

#define UN_CONS_str(A, B, C)\
    {\
	calculus *x107_ = (C);\
	DEREF_str(x107_ + 1, (A));\
	(B) = x107_->ag_ptr;\
    }

#define DESTROY_CONS_str(D, A, B, C)\
    {\
	calculus *x108_ = (C);\
	DEREF_str(x108_ + 1, (A));\
	(B) = x108_->ag_ptr;\
	(D)(x108_, (unsigned)5);\
    }

#define PUSH_str(A, B)\
    {\
	calculus **r109_ = &(B);\
	calculus *x109_ = GEN_calculus(5, TYPEID_stack);\
	COPY_str(x109_ + 1, (A));\
	x109_->ag_ptr = *r109_;\
	*r109_ = x109_;\
    }

#define POP_str(A, B)\
    {\
	calculus **r110_ = &(B);\
	calculus *x110_ = (*r110_);\
	DEREF_str(x110_ + 1, (A));\
	*r110_ = x110_->ag_ptr;\
	destroy_calculus(x110_, (unsigned)5);\
    }


/* Definitions for structure FIELD */

#define fld_name(P)			((P) + 0)
#define fld_tag(P)			((P) + 1)
#define fld_flag(P)			((P) + 2)
#define fld_set(P)			((P) + 3)
#define fld_base(P)			((P) + 4)
#define fld_defn(P)			((P) + 5)
#define SIZE_fld			6

#define COPY_fld(A, B)\
    {\
	calculus *x111_ = (A);\
	FIELD y111_;\
	y111_ = (B);\
	COPY_string(x111_ + 0, y111_.name);\
	COPY_int(x111_ + 1, y111_.tag);\
	COPY_int(x111_ + 2, y111_.flag);\
	COPY_int(x111_ + 3, y111_.set);\
	COPY_ptr(x111_ + 4, y111_.base);\
	COPY_list(x111_ + 5, y111_.defn);\
    }

#define DEREF_fld(A, B)\
    {\
	calculus *x112_ = (A);\
	FIELD *y112_ = &(B);\
	y112_->name = DEREF_string(x112_ + 0);\
	y112_->tag = DEREF_int(x112_ + 1);\
	y112_->flag = DEREF_int(x112_ + 2);\
	y112_->set = DEREF_int(x112_ + 3);\
	y112_->base = DEREF_ptr(x112_ + 4);\
	y112_->defn = DEREF_list(x112_ + 5);\
    }

#define MAKE_fld(name_, tag_, flag_, set_, base_, defn_, fld_)\
    {\
	calculus *x113_ = (fld_);\
	COPY_string(x113_ + 0, (name_));\
	COPY_int(x113_ + 1, (tag_));\
	COPY_int(x113_ + 2, (flag_));\
	COPY_int(x113_ + 3, (set_));\
	COPY_ptr(x113_ + 4, (base_));\
	COPY_list(x113_ + 5, (defn_));\
    }

#define CONS_fld(A, B, C)\
    {\
	calculus *x114_ = GEN_calculus(7, TYPEID_list);\
	COPY_fld(x114_ + 1, (A));\
	x114_->ag_ptr = (B);\
	(C) = x114_;\
    }

#define UN_CONS_fld(A, B, C)\
    {\
	calculus *x115_ = (C);\
	DEREF_fld(x115_ + 1, (A));\
	(B) = x115_->ag_ptr;\
    }

#define DESTROY_CONS_fld(D, A, B, C)\
    {\
	calculus *x116_ = (C);\
	DEREF_fld(x116_ + 1, (A));\
	(B) = x116_->ag_ptr;\
	(D)(x116_, (unsigned)7);\
    }

#define PUSH_fld(A, B)\
    {\
	calculus **r117_ = &(B);\
	calculus *x117_ = GEN_calculus(7, TYPEID_stack);\
	COPY_fld(x117_ + 1, (A));\
	x117_->ag_ptr = *r117_;\
	*r117_ = x117_;\
    }

#define POP_fld(A, B)\
    {\
	calculus **r118_ = &(B);\
	calculus *x118_ = (*r118_);\
	DEREF_fld(x118_ + 1, (A));\
	*r118_ = x118_->ag_ptr;\
	destroy_calculus(x118_, (unsigned)7);\
    }


/* Definitions for structure ARGUMENT */

#define arg_name(P)			((P) + 0)
#define arg_type(P)			((P) + 1)
#define SIZE_arg			2

#define COPY_arg(A, B)\
    {\
	calculus *x119_ = (A);\
	ARGUMENT y119_;\
	y119_ = (B);\
	COPY_string(x119_ + 0, y119_.name);\
	COPY_ptr(x119_ + 1, y119_.type);\
    }

#define DEREF_arg(A, B)\
    {\
	calculus *x120_ = (A);\
	ARGUMENT *y120_ = &(B);\
	y120_->name = DEREF_string(x120_ + 0);\
	y120_->type = DEREF_ptr(x120_ + 1);\
    }

#define MAKE_arg(name_, type_, arg_)\
    {\
	calculus *x121_ = (arg_);\
	COPY_string(x121_ + 0, (name_));\
	COPY_ptr(x121_ + 1, (type_));\
    }

#define CONS_arg(A, B, C)\
    {\
	calculus *x122_ = GEN_calculus(3, TYPEID_list);\
	COPY_arg(x122_ + 1, (A));\
	x122_->ag_ptr = (B);\
	(C) = x122_;\
    }

#define UN_CONS_arg(A, B, C)\
    {\
	calculus *x123_ = (C);\
	DEREF_arg(x123_ + 1, (A));\
	(B) = x123_->ag_ptr;\
    }

#define DESTROY_CONS_arg(D, A, B, C)\
    {\
	calculus *x124_ = (C);\
	DEREF_arg(x124_ + 1, (A));\
	(B) = x124_->ag_ptr;\
	(D)(x124_, (unsigned)3);\
    }

#define PUSH_arg(A, B)\
    {\
	calculus **r125_ = &(B);\
	calculus *x125_ = GEN_calculus(3, TYPEID_stack);\
	COPY_arg(x125_ + 1, (A));\
	x125_->ag_ptr = *r125_;\
	*r125_ = x125_;\
    }

#define POP_arg(A, B)\
    {\
	calculus **r126_ = &(B);\
	calculus *x126_ = (*r126_);\
	DEREF_arg(x126_ + 1, (A));\
	*r126_ = x126_->ag_ptr;\
	destroy_calculus(x126_, (unsigned)3);\
    }


/* Definitions for structure MAP */

#define map_name(P)			((P) + 0)
#define map_flag(P)			((P) + 1)
#define map_ret_type(P)			((P) + 2)
#define map_args(P)			((P) + 3)
#define SIZE_map			4

#define COPY_map(A, B)\
    {\
	calculus *x127_ = (A);\
	MAP y127_;\
	y127_ = (B);\
	COPY_string(x127_ + 0, y127_.name);\
	COPY_int(x127_ + 1, y127_.flag);\
	COPY_ptr(x127_ + 2, y127_.ret_type);\
	COPY_list(x127_ + 3, y127_.args);\
    }

#define DEREF_map(A, B)\
    {\
	calculus *x128_ = (A);\
	MAP *y128_ = &(B);\
	y128_->name = DEREF_string(x128_ + 0);\
	y128_->flag = DEREF_int(x128_ + 1);\
	y128_->ret_type = DEREF_ptr(x128_ + 2);\
	y128_->args = DEREF_list(x128_ + 3);\
    }

#define MAKE_map(name_, flag_, ret_type_, args_, map_)\
    {\
	calculus *x129_ = (map_);\
	COPY_string(x129_ + 0, (name_));\
	COPY_int(x129_ + 1, (flag_));\
	COPY_ptr(x129_ + 2, (ret_type_));\
	COPY_list(x129_ + 3, (args_));\
    }

#define CONS_map(A, B, C)\
    {\
	calculus *x130_ = GEN_calculus(5, TYPEID_list);\
	COPY_map(x130_ + 1, (A));\
	x130_->ag_ptr = (B);\
	(C) = x130_;\
    }

#define UN_CONS_map(A, B, C)\
    {\
	calculus *x131_ = (C);\
	DEREF_map(x131_ + 1, (A));\
	(B) = x131_->ag_ptr;\
    }

#define DESTROY_CONS_map(D, A, B, C)\
    {\
	calculus *x132_ = (C);\
	DEREF_map(x132_ + 1, (A));\
	(B) = x132_->ag_ptr;\
	(D)(x132_, (unsigned)5);\
    }

#define PUSH_map(A, B)\
    {\
	calculus **r133_ = &(B);\
	calculus *x133_ = GEN_calculus(5, TYPEID_stack);\
	COPY_map(x133_ + 1, (A));\
	x133_->ag_ptr = *r133_;\
	*r133_ = x133_;\
    }

#define POP_map(A, B)\
    {\
	calculus **r134_ = &(B);\
	calculus *x134_ = (*r134_);\
	DEREF_map(x134_ + 1, (A));\
	*r134_ = x134_->ag_ptr;\
	destroy_calculus(x134_, (unsigned)5);\
    }


/* Definitions for structure UNION */

#define un_id(P)			((P) + 0)
#define un_base(P)			((P) + 1)
#define un_s_defn(P)			((P) + 2)
#define un_u_defn(P)			((P) + 3)
#define un_map(P)			((P) + 4)
#define un_no_fields(P)			((P) + 5)
#define SIZE_un				6

#define COPY_un(A, B)\
    {\
	calculus *x135_ = (A);\
	UNION y135_;\
	y135_ = (B);\
	COPY_ptr(x135_ + 0, y135_.id);\
	COPY_ptr(x135_ + 1, y135_.base);\
	COPY_list(x135_ + 2, y135_.s_defn);\
	COPY_list(x135_ + 3, y135_.u_defn);\
	COPY_list(x135_ + 4, y135_.map);\
	COPY_int(x135_ + 5, y135_.no_fields);\
    }

#define DEREF_un(A, B)\
    {\
	calculus *x136_ = (A);\
	UNION *y136_ = &(B);\
	y136_->id = DEREF_ptr(x136_ + 0);\
	y136_->base = DEREF_ptr(x136_ + 1);\
	y136_->s_defn = DEREF_list(x136_ + 2);\
	y136_->u_defn = DEREF_list(x136_ + 3);\
	y136_->map = DEREF_list(x136_ + 4);\
	y136_->no_fields = DEREF_int(x136_ + 5);\
    }

#define MAKE_un(id_, base_, s_defn_, u_defn_, map_, no_fields_, un_)\
    {\
	calculus *x137_ = (un_);\
	COPY_ptr(x137_ + 0, (id_));\
	COPY_ptr(x137_ + 1, (base_));\
	COPY_list(x137_ + 2, (s_defn_));\
	COPY_list(x137_ + 3, (u_defn_));\
	COPY_list(x137_ + 4, (map_));\
	COPY_int(x137_ + 5, (no_fields_));\
    }

#define CONS_un(A, B, C)\
    {\
	calculus *x138_ = GEN_calculus(7, TYPEID_list);\
	COPY_un(x138_ + 1, (A));\
	x138_->ag_ptr = (B);\
	(C) = x138_;\
    }

#define UN_CONS_un(A, B, C)\
    {\
	calculus *x139_ = (C);\
	DEREF_un(x139_ + 1, (A));\
	(B) = x139_->ag_ptr;\
    }

#define DESTROY_CONS_un(D, A, B, C)\
    {\
	calculus *x140_ = (C);\
	DEREF_un(x140_ + 1, (A));\
	(B) = x140_->ag_ptr;\
	(D)(x140_, (unsigned)7);\
    }

#define PUSH_un(A, B)\
    {\
	calculus **r141_ = &(B);\
	calculus *x141_ = GEN_calculus(7, TYPEID_stack);\
	COPY_un(x141_ + 1, (A));\
	x141_->ag_ptr = *r141_;\
	*r141_ = x141_;\
    }

#define POP_un(A, B)\
    {\
	calculus **r142_ = &(B);\
	calculus *x142_ = (*r142_);\
	DEREF_un(x142_ + 1, (A));\
	*r142_ = x142_->ag_ptr;\
	destroy_calculus(x142_, (unsigned)7);\
    }


/* Definitions for union TYPE */

#define ORDER_type			((unsigned) 12)
#define SIZE_type			1
#define NULL_type			((TYPE) 0)
#define IS_NULL_type(A)			((A) == 0)
#define EQ_type(A, B)			((A) == (B))

#define COPY_type(A, B)			((A)->ag_ptr = (B))
#define DEREF_type(A)			((A)->ag_ptr)

#define CONS_type(A, B, C)\
    {\
	calculus *x143_ = GEN_calculus(2, TYPEID_list);\
	COPY_type(x143_ + 1, (A));\
	x143_->ag_ptr = (B);\
	(C) = x143_;\
    }

#define UN_CONS_type(A, B, C)\
    {\
	calculus *x144_ = (C);\
	(A) = DEREF_type(x144_ + 1);\
	(B) = x144_->ag_ptr;\
    }

#define DESTROY_CONS_type(D, A, B, C)\
    {\
	calculus *x145_ = (C);\
	(A) = DEREF_type(x145_ + 1);\
	(B) = x145_->ag_ptr;\
	(D)(x145_, (unsigned)2);\
    }

#define PUSH_type(A, B)\
    {\
	calculus **r146_ = &(B);\
	calculus *x146_ = GEN_calculus(2, TYPEID_stack);\
	COPY_type(x146_ + 1, (A));\
	x146_->ag_ptr = *r146_;\
	*r146_ = x146_;\
    }

#define POP_type(A, B)\
    {\
	calculus **r147_ = &(B);\
	calculus *x147_ = (*r147_);\
	(A) = DEREF_type(x147_ + 1);\
	*r147_ = x147_->ag_ptr;\
	destroy_calculus(x147_, (unsigned)2);\
    }


/* Definitions for union COMMAND */

#define ORDER_cmd			((unsigned) 4)
#define SIZE_cmd			1
#define NULL_cmd			((COMMAND) 0)
#define IS_NULL_cmd(A)			((A) == 0)
#define EQ_cmd(A, B)			((A) == (B))

#define COPY_cmd(A, B)			((A)->ag_ptr = (B))
#define DEREF_cmd(A)			((A)->ag_ptr)

#define CONS_cmd(A, B, C)\
    {\
	calculus *x148_ = GEN_calculus(2, TYPEID_list);\
	COPY_cmd(x148_ + 1, (A));\
	x148_->ag_ptr = (B);\
	(C) = x148_;\
    }

#define UN_CONS_cmd(A, B, C)\
    {\
	calculus *x149_ = (C);\
	(A) = DEREF_cmd(x149_ + 1);\
	(B) = x149_->ag_ptr;\
    }

#define DESTROY_CONS_cmd(D, A, B, C)\
    {\
	calculus *x150_ = (C);\
	(A) = DEREF_cmd(x150_ + 1);\
	(B) = x150_->ag_ptr;\
	(D)(x150_, (unsigned)2);\
    }

#define PUSH_cmd(A, B)\
    {\
	calculus **r151_ = &(B);\
	calculus *x151_ = GEN_calculus(2, TYPEID_stack);\
	COPY_cmd(x151_ + 1, (A));\
	x151_->ag_ptr = *r151_;\
	*r151_ = x151_;\
    }

#define POP_cmd(A, B)\
    {\
	calculus **r152_ = &(B);\
	calculus *x152_ = (*r152_);\
	(A) = DEREF_cmd(x152_ + 1);\
	*r152_ = x152_->ag_ptr;\
	destroy_calculus(x152_, (unsigned)2);\
    }


/* Maximum allocation size */

#define calculus_GEN_MAX		11

#endif
