/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef C_CLASS_H_INCLUDED
#define C_CLASS_H_INCLUDED

#ifndef c_class_NAME
#define c_class_NAME			"c_class"
#define c_class_VERSION			"1.1"
#define c_class_SPECIFICATION		0
#define c_class_IMPLEMENTATION		1
#endif


/* Prototype macros */



/* Primitive types */

typedef character * string;
typedef unsigned long ulong_type;
typedef struct bits_tag * BITSTREAM_P;
typedef struct pptok_tag * PPTOKEN_P;


/* Basic types */

typedef union c_class_tag {
    unsigned ag_tag;
    union c_class_tag *ag_ptr;
    unsigned ag_enum;
    unsigned long ag_long_enum;
    int ag_prim_int;
    unsigned ag_prim_unsigned;
    string ag_prim_string;
    ulong_type ag_prim_ulong;
    BITSTREAM_P ag_prim_bits;
    PPTOKEN_P ag_prim_pptok;
} c_class;

typedef c_class *c_class_PTR;

#ifndef c_class_DESTR_DEFINED
#define c_class_DESTR_DEFINED
typedef void (*DESTROYER)(c_class *, unsigned);
#endif

#define PTR(A)	c_class_PTR
#define LIST(A)	c_class_PTR
#define STACK(A)	c_class_PTR
#define SIZE(A)	int


/* Assertion macros */

#ifndef NDEBUG
extern c_class *check_null_c_class(c_class *, char *, int);
extern c_class *check_tag_c_class(c_class *, unsigned, char *, int);
extern c_class *check_tag_etc_c_class(c_class *, unsigned, unsigned, char *, int);
#define CHECK_NULL(P)\
    (check_null_c_class((P), __FILE__, __LINE__))
#define CHECK_TAG(P, N)\
    (check_tag_c_class((P), (unsigned)(N), __FILE__, __LINE__))
#define CHECK_TAG_ETC(P, L, U)\
    (check_tag_etc_c_class((P), (unsigned)(L), (unsigned)(U), __FILE__, __LINE__))
#else
#define CHECK_NULL(P)			(P)
#define CHECK_TAG(P, N)			(P)
#define CHECK_TAG_ETC(P, L, U)		(P)
#endif


/* Enumeration definitions */

typedef unsigned CV_SPEC;
typedef unsigned BUILTIN_TYPE;
typedef unsigned long BASE_TYPE;
typedef unsigned long CLASS_INFO;
typedef unsigned CLASS_USAGE;
typedef unsigned long DECL_SPEC;
typedef unsigned QUALIFIER;
typedef unsigned NTEST;
typedef unsigned RMODE;


/* Union type definitions */

typedef c_class *INT_TYPE;
typedef c_class *FLOAT_TYPE;
typedef c_class *CLASS_TYPE;
typedef c_class *GRAPH;
typedef c_class *VIRTUAL;
typedef c_class *ENUM_TYPE;
typedef c_class *TYPE;
typedef c_class *HASHID;
typedef c_class *IDENTIFIER;
typedef c_class *MEMBER;
typedef c_class *NAMESPACE;
typedef c_class *NAT;
typedef c_class *FLOAT;
typedef c_class *STRING;
typedef c_class *EXP;
typedef c_class *OFFSET;
typedef c_class *TOKEN;
typedef c_class *INSTANCE;
typedef c_class *ERROR;


/* Structure declarations */

typedef struct var_tag VARIABLE;
typedef struct loc_tag LOCATION;
typedef struct posn_tag POSITION;


/* Identity type definitions */



/* Structure definitions */

#ifndef c_class_STRUCT_DEFINED
#define c_class_STRUCT_DEFINED

struct var_tag {
    IDENTIFIER id;
    DECL_SPEC info;
};

struct loc_tag {
    ulong_type line;
    ulong_type column;
    PTR(POSITION) posn;
};

struct posn_tag {
    string file;
    string input;
    string base;
    string dir;
    ulong_type offset;
    PTR(LOCATION) from;
    ulong_type datestamp;
    ulong_type tok;
};

#endif /* c_class_STRUCT_DEFINED */


/* Function declarations */

extern c_class *gen_c_class(unsigned);
extern void destroy_c_class(c_class *, unsigned);
extern void dummy_destroy_c_class (c_class *, unsigned);
extern void destroy_c_class_list (c_class *, unsigned);
extern c_class *append_c_class_list(c_class *, c_class *);
extern c_class *end_c_class_list(c_class *);
extern unsigned length_c_class_list(c_class *);
extern c_class *reverse_c_class_list(c_class *);
#ifdef c_class_IO_ROUTINES
extern unsigned crt_c_class_alias;
extern void set_c_class_alias(c_class *, unsigned);
extern c_class *find_c_class_alias(unsigned);
extern void clear_c_class_alias(void);
#endif


/* Run-time type information */

#ifndef GEN_c_class
#define GEN_c_class(A, B)		gen_c_class((unsigned)(A))
#endif
#define TYPEID_ptr			((unsigned)0)
#define TYPEID_list			((unsigned)1)
#define TYPEID_stack			((unsigned)2)
#define TYPEID_itype			((unsigned)3)
#define TYPEID_ftype			((unsigned)4)
#define TYPEID_ctype			((unsigned)5)
#define TYPEID_graph			((unsigned)6)
#define TYPEID_virt			((unsigned)7)
#define TYPEID_etype			((unsigned)8)
#define TYPEID_type			((unsigned)9)
#define TYPEID_hashid			((unsigned)10)
#define TYPEID_id			((unsigned)11)
#define TYPEID_member			((unsigned)12)
#define TYPEID_nspace			((unsigned)13)
#define TYPEID_nat			((unsigned)14)
#define TYPEID_flt			((unsigned)15)
#define TYPEID_str			((unsigned)16)
#define TYPEID_exp			((unsigned)17)
#define TYPEID_off			((unsigned)18)
#define TYPEID_tok			((unsigned)19)
#define TYPEID_inst			((unsigned)20)
#define TYPEID_err			((unsigned)21)


/* Definitions for pointers */

#define STEP_ptr(A, B)			(CHECK_NULL(A) + B)
#define SIZE_ptr(A)			1
#define NULL_ptr(A)			((c_class *)0)
#define IS_NULL_ptr(A)			((A) == 0)
#define EQ_ptr(A, B)			((A) == (B))
#define MAKE_ptr(A)			GEN_c_class((A), TYPEID_ptr)
#define DESTROY_ptr(A, B)		destroy_c_class((A), (unsigned)(B))
#define UNIQ_ptr(A)			GEN_c_class(1, TYPEID_ptr)
#define DESTROY_UNIQ_ptr(A)		destroy_c_class((A), (unsigned)1)
#ifdef c_class_IO_ROUTINES
#define VOIDSTAR_ptr(A)			((void *)(A))
#endif

#define COPY_ptr(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_ptr(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_ptr(A, B, C)\
    {\
	c_class *x0_ = GEN_c_class(2, TYPEID_list);\
	x0_[1].ag_ptr = (A);\
	x0_->ag_ptr = (B);\
	(C) = x0_;\
    }

#define UN_CONS_ptr(A, B, C)\
    {\
	c_class *x1_ = CHECK_NULL(C);\
	(A) = x1_[1].ag_ptr;\
	(B) = x1_->ag_ptr;\
    }

#define DESTROY_CONS_ptr(D, A, B, C)\
    {\
	c_class *x2_ = CHECK_NULL(C);\
	(A) = x2_[1].ag_ptr;\
	(B) = x2_->ag_ptr;\
	(D)(x2_, (unsigned)2);\
    }

#define PUSH_ptr(A, B)\
    {\
	c_class **r3_ = &(B);\
	c_class *x3_ = GEN_c_class(2, TYPEID_stack);\
	x3_[1].ag_ptr = (A);\
	x3_->ag_ptr = *r3_;\
	*r3_ = x3_;\
    }

#define POP_ptr(A, B)\
    {\
	c_class **r4_ = &(B);\
	c_class *x4_ = CHECK_NULL(*r4_);\
	(A) = x4_[1].ag_ptr;\
	*r4_ = x4_->ag_ptr;\
	destroy_c_class(x4_, (unsigned)2);\
    }


/* Definitions for lists */

#define HEAD_list(A)			(CHECK_NULL(A) + 1)
#define PTR_TAIL_list(A)		(CHECK_NULL(A))
#define TAIL_list(A)			(CHECK_NULL(A)->ag_ptr)
#define LENGTH_list(A)			length_c_class_list((A))
#define END_list(A)			end_c_class_list((A))
#define REVERSE_list(A)			reverse_c_class_list((A))
#define APPEND_list(A, B)		append_c_class_list((A), (B))

#define SIZE_list(A)			1
#define NULL_list(A)			((c_class *) 0)
#define IS_NULL_list(A)			((A) == 0)
#define EQ_list(A, B)			((A) == (B))
#define UNIQ_list(A)			GEN_c_class(1, TYPEID_list)
#define DESTROY_UNIQ_list(A)		destroy_c_class((A), (unsigned)1)
#ifdef c_class_IO_ROUTINES
#define VOIDSTAR_list(A)		((void *)(A))
#endif

#define DESTROY_list(A, B)\
    {\
	destroy_c_class_list((A), (unsigned)(B));\
    }

#define COPY_list(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_list(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_list(A, B, C)\
    {\
	c_class *x5_ = GEN_c_class(2, TYPEID_list);\
	x5_[1].ag_ptr = (A);\
	x5_->ag_ptr = (B);\
	(C) = x5_;\
    }

#define UN_CONS_list(A, B, C)\
    {\
	c_class *x6_ = CHECK_NULL(C);\
	(A) = x6_[1].ag_ptr;\
	(B) = x6_->ag_ptr;\
    }

#define DESTROY_CONS_list(D, A, B, C)\
    {\
	c_class *x7_ = CHECK_NULL(C);\
	(A) = x7_[1].ag_ptr;\
	(B) = x7_->ag_ptr;\
	(D)(x7_, (unsigned)2);\
    }

#define PUSH_list(A, B)\
    {\
	c_class **r8_ = &(B);\
	c_class *x8_ = GEN_c_class(2, TYPEID_stack);\
	x8_[1].ag_ptr = (A);\
	x8_->ag_ptr = *r8_;\
	*r8_ = x8_;\
    }

#define POP_list(A, B)\
    {\
	c_class **r9_ = &(B);\
	c_class *x9_ = CHECK_NULL(*r9_);\
	(A) = x9_[1].ag_ptr;\
	*r9_ = x9_->ag_ptr;\
	destroy_c_class(x9_, (unsigned)2);\
    }


/* Definitions for stacks */

#define SIZE_stack(A)			1
#define NULL_stack(A)			((c_class *) 0)
#define IS_NULL_stack(A)		((A) == 0)
#define STACK_list(A)			(A)
#define LIST_stack(A)			(A)

#define COPY_stack(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_stack(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_stack(A, B, C)\
    {\
	c_class *x10_ = GEN_c_class(2, TYPEID_list);\
	x10_[1].ag_ptr = (A);\
	x10_->ag_ptr = (B);\
	(C) = x10_;\
    }

#define UN_CONS_stack(A, B, C)\
    {\
	c_class *x11_ = CHECK_NULL(C);\
	(A) = x11_[1].ag_ptr;\
	(B) = x11_->ag_ptr;\
    }

#define DESTROY_CONS_stack(D, A, B, C)\
    {\
	c_class *x12_ = CHECK_NULL(C);\
	(A) = x12_[1].ag_ptr;\
	(B) = x12_->ag_ptr;\
	(D)(x12_, (unsigned)2);\
    }

#define PUSH_stack(A, B)\
    {\
	c_class **r13_ = &(B);\
	c_class *x13_ = GEN_c_class(2, TYPEID_stack);\
	x13_[1].ag_ptr = (A);\
	x13_->ag_ptr = *r13_;\
	*r13_ = x13_;\
    }

#define POP_stack(A, B)\
    {\
	c_class **r14_ = &(B);\
	c_class *x14_ = CHECK_NULL(*r14_);\
	(A) = x14_[1].ag_ptr;\
	*r14_ = x14_->ag_ptr;\
	destroy_c_class(x14_, (unsigned)2);\
    }


/* Definitions for sizes */

#define SCALE(A, B)			((A)*(int)(B))


/* Definitions for primitive int */

#define SIZE_int			1

#define COPY_int(A, B)			(CHECK_NULL(A)->ag_prim_int = (B))
#define DEREF_int(A)			(CHECK_NULL(A)->ag_prim_int)
#define CONS_int(A, B, C)\
    {\
	c_class *x15_ = GEN_c_class(2, TYPEID_list);\
	COPY_int(x15_ + 1, (A));\
	x15_->ag_ptr = (B);\
	(C) = x15_;\
    }

#define UN_CONS_int(A, B, C)\
    {\
	c_class *x16_ = CHECK_NULL(C);\
	(A) = DEREF_int(x16_ + 1);\
	(B) = x16_->ag_ptr;\
    }

#define DESTROY_CONS_int(D, A, B, C)\
    {\
	c_class *x17_ = CHECK_NULL(C);\
	(A) = DEREF_int(x17_ + 1);\
	(B) = x17_->ag_ptr;\
	(D)(x17_, (unsigned)2);\
    }

#define PUSH_int(A, B)\
    {\
	c_class **r18_ = &(B);\
	c_class *x18_ = GEN_c_class(2, TYPEID_stack);\
	COPY_int(x18_ + 1, (A));\
	x18_->ag_ptr = *r18_;\
	*r18_ = x18_;\
    }

#define POP_int(A, B)\
    {\
	c_class **r19_ = &(B);\
	c_class *x19_ = CHECK_NULL(*r19_);\
	(A) = DEREF_int(x19_ + 1);\
	*r19_ = x19_->ag_ptr;\
	destroy_c_class(x19_, (unsigned)2);\
    }


/* Definitions for primitive unsigned */

#define SIZE_unsigned			1

#define COPY_unsigned(A, B)		(CHECK_NULL(A)->ag_prim_unsigned = (B))
#define DEREF_unsigned(A)		(CHECK_NULL(A)->ag_prim_unsigned)
#define CONS_unsigned(A, B, C)\
    {\
	c_class *x20_ = GEN_c_class(2, TYPEID_list);\
	COPY_unsigned(x20_ + 1, (A));\
	x20_->ag_ptr = (B);\
	(C) = x20_;\
    }

#define UN_CONS_unsigned(A, B, C)\
    {\
	c_class *x21_ = CHECK_NULL(C);\
	(A) = DEREF_unsigned(x21_ + 1);\
	(B) = x21_->ag_ptr;\
    }

#define DESTROY_CONS_unsigned(D, A, B, C)\
    {\
	c_class *x22_ = CHECK_NULL(C);\
	(A) = DEREF_unsigned(x22_ + 1);\
	(B) = x22_->ag_ptr;\
	(D)(x22_, (unsigned)2);\
    }

#define PUSH_unsigned(A, B)\
    {\
	c_class **r23_ = &(B);\
	c_class *x23_ = GEN_c_class(2, TYPEID_stack);\
	COPY_unsigned(x23_ + 1, (A));\
	x23_->ag_ptr = *r23_;\
	*r23_ = x23_;\
    }

#define POP_unsigned(A, B)\
    {\
	c_class **r24_ = &(B);\
	c_class *x24_ = CHECK_NULL(*r24_);\
	(A) = DEREF_unsigned(x24_ + 1);\
	*r24_ = x24_->ag_ptr;\
	destroy_c_class(x24_, (unsigned)2);\
    }


/* Definitions for primitive string */

#define SIZE_string			1

#define COPY_string(A, B)		(CHECK_NULL(A)->ag_prim_string = (B))
#define DEREF_string(A)			(CHECK_NULL(A)->ag_prim_string)
#define CONS_string(A, B, C)\
    {\
	c_class *x25_ = GEN_c_class(2, TYPEID_list);\
	COPY_string(x25_ + 1, (A));\
	x25_->ag_ptr = (B);\
	(C) = x25_;\
    }

#define UN_CONS_string(A, B, C)\
    {\
	c_class *x26_ = CHECK_NULL(C);\
	(A) = DEREF_string(x26_ + 1);\
	(B) = x26_->ag_ptr;\
    }

#define DESTROY_CONS_string(D, A, B, C)\
    {\
	c_class *x27_ = CHECK_NULL(C);\
	(A) = DEREF_string(x27_ + 1);\
	(B) = x27_->ag_ptr;\
	(D)(x27_, (unsigned)2);\
    }

#define PUSH_string(A, B)\
    {\
	c_class **r28_ = &(B);\
	c_class *x28_ = GEN_c_class(2, TYPEID_stack);\
	COPY_string(x28_ + 1, (A));\
	x28_->ag_ptr = *r28_;\
	*r28_ = x28_;\
    }

#define POP_string(A, B)\
    {\
	c_class **r29_ = &(B);\
	c_class *x29_ = CHECK_NULL(*r29_);\
	(A) = DEREF_string(x29_ + 1);\
	*r29_ = x29_->ag_ptr;\
	destroy_c_class(x29_, (unsigned)2);\
    }


/* Definitions for primitive ulong_type */

#define SIZE_ulong			1

#define COPY_ulong(A, B)		(CHECK_NULL(A)->ag_prim_ulong = (B))
#define DEREF_ulong(A)			(CHECK_NULL(A)->ag_prim_ulong)
#define CONS_ulong(A, B, C)\
    {\
	c_class *x30_ = GEN_c_class(2, TYPEID_list);\
	COPY_ulong(x30_ + 1, (A));\
	x30_->ag_ptr = (B);\
	(C) = x30_;\
    }

#define UN_CONS_ulong(A, B, C)\
    {\
	c_class *x31_ = CHECK_NULL(C);\
	(A) = DEREF_ulong(x31_ + 1);\
	(B) = x31_->ag_ptr;\
    }

#define DESTROY_CONS_ulong(D, A, B, C)\
    {\
	c_class *x32_ = CHECK_NULL(C);\
	(A) = DEREF_ulong(x32_ + 1);\
	(B) = x32_->ag_ptr;\
	(D)(x32_, (unsigned)2);\
    }

#define PUSH_ulong(A, B)\
    {\
	c_class **r33_ = &(B);\
	c_class *x33_ = GEN_c_class(2, TYPEID_stack);\
	COPY_ulong(x33_ + 1, (A));\
	x33_->ag_ptr = *r33_;\
	*r33_ = x33_;\
    }

#define POP_ulong(A, B)\
    {\
	c_class **r34_ = &(B);\
	c_class *x34_ = CHECK_NULL(*r34_);\
	(A) = DEREF_ulong(x34_ + 1);\
	*r34_ = x34_->ag_ptr;\
	destroy_c_class(x34_, (unsigned)2);\
    }


/* Definitions for primitive BITSTREAM_P */

#define SIZE_bits			1

#define COPY_bits(A, B)			(CHECK_NULL(A)->ag_prim_bits = (B))
#define DEREF_bits(A)			(CHECK_NULL(A)->ag_prim_bits)
#define CONS_bits(A, B, C)\
    {\
	c_class *x35_ = GEN_c_class(2, TYPEID_list);\
	COPY_bits(x35_ + 1, (A));\
	x35_->ag_ptr = (B);\
	(C) = x35_;\
    }

#define UN_CONS_bits(A, B, C)\
    {\
	c_class *x36_ = CHECK_NULL(C);\
	(A) = DEREF_bits(x36_ + 1);\
	(B) = x36_->ag_ptr;\
    }

#define DESTROY_CONS_bits(D, A, B, C)\
    {\
	c_class *x37_ = CHECK_NULL(C);\
	(A) = DEREF_bits(x37_ + 1);\
	(B) = x37_->ag_ptr;\
	(D)(x37_, (unsigned)2);\
    }

#define PUSH_bits(A, B)\
    {\
	c_class **r38_ = &(B);\
	c_class *x38_ = GEN_c_class(2, TYPEID_stack);\
	COPY_bits(x38_ + 1, (A));\
	x38_->ag_ptr = *r38_;\
	*r38_ = x38_;\
    }

#define POP_bits(A, B)\
    {\
	c_class **r39_ = &(B);\
	c_class *x39_ = CHECK_NULL(*r39_);\
	(A) = DEREF_bits(x39_ + 1);\
	*r39_ = x39_->ag_ptr;\
	destroy_c_class(x39_, (unsigned)2);\
    }


/* Definitions for primitive PPTOKEN_P */

#define SIZE_pptok			1

#define COPY_pptok(A, B)		(CHECK_NULL(A)->ag_prim_pptok = (B))
#define DEREF_pptok(A)			(CHECK_NULL(A)->ag_prim_pptok)
#define CONS_pptok(A, B, C)\
    {\
	c_class *x40_ = GEN_c_class(2, TYPEID_list);\
	COPY_pptok(x40_ + 1, (A));\
	x40_->ag_ptr = (B);\
	(C) = x40_;\
    }

#define UN_CONS_pptok(A, B, C)\
    {\
	c_class *x41_ = CHECK_NULL(C);\
	(A) = DEREF_pptok(x41_ + 1);\
	(B) = x41_->ag_ptr;\
    }

#define DESTROY_CONS_pptok(D, A, B, C)\
    {\
	c_class *x42_ = CHECK_NULL(C);\
	(A) = DEREF_pptok(x42_ + 1);\
	(B) = x42_->ag_ptr;\
	(D)(x42_, (unsigned)2);\
    }

#define PUSH_pptok(A, B)\
    {\
	c_class **r43_ = &(B);\
	c_class *x43_ = GEN_c_class(2, TYPEID_stack);\
	COPY_pptok(x43_ + 1, (A));\
	x43_->ag_ptr = *r43_;\
	*r43_ = x43_;\
    }

#define POP_pptok(A, B)\
    {\
	c_class **r44_ = &(B);\
	c_class *x44_ = CHECK_NULL(*r44_);\
	(A) = DEREF_pptok(x44_ + 1);\
	*r44_ = x44_->ag_ptr;\
	destroy_c_class(x44_, (unsigned)2);\
    }


/* Definitions for enumeration CV_SPEC */

#define cv_none				((CV_SPEC) 0)
#define cv_const			((CV_SPEC) 1)
#define cv_volatile			((CV_SPEC) 2)
#define cv_lvalue			((CV_SPEC) 4)
#define cv_c				((CV_SPEC) 8)
#define cv_cpp				((CV_SPEC) 16)
#define cv_qual				((CV_SPEC) 3)
#define cv_mask				((CV_SPEC) 7)
#define cv_language			((CV_SPEC) 24)
#define ORDER_cv			((unsigned long) 25)
#define SIZE_cv				1

#define COPY_cv(A, B)			(CHECK_NULL(A)->ag_enum = (B))
#define DEREF_cv(A)			(CHECK_NULL(A)->ag_enum)


/* Definitions for enumeration BUILTIN_TYPE */

#define ntype_none			((BUILTIN_TYPE) 0)
#define ntype_char			((BUILTIN_TYPE) 1)
#define ntype_schar			((BUILTIN_TYPE) 2)
#define ntype_uchar			((BUILTIN_TYPE) 3)
#define ntype_sshort			((BUILTIN_TYPE) 4)
#define ntype_ushort			((BUILTIN_TYPE) 5)
#define ntype_sint			((BUILTIN_TYPE) 6)
#define ntype_uint			((BUILTIN_TYPE) 7)
#define ntype_slong			((BUILTIN_TYPE) 8)
#define ntype_ulong			((BUILTIN_TYPE) 9)
#define ntype_sllong			((BUILTIN_TYPE) 10)
#define ntype_ullong			((BUILTIN_TYPE) 11)
#define ntype_float			((BUILTIN_TYPE) 12)
#define ntype_double			((BUILTIN_TYPE) 13)
#define ntype_ldouble			((BUILTIN_TYPE) 14)
#define ntype_void			((BUILTIN_TYPE) 15)
#define ntype_bottom			((BUILTIN_TYPE) 16)
#define ntype_bool			((BUILTIN_TYPE) 17)
#define ntype_ptrdiff_t			((BUILTIN_TYPE) 18)
#define ntype_size_t			((BUILTIN_TYPE) 19)
#define ntype_wchar_t			((BUILTIN_TYPE) 20)
#define ntype_ellipsis			((BUILTIN_TYPE) 21)
#define ORDER_ntype			((unsigned long) 22)
#define SIZE_ntype			1

#define COPY_ntype(A, B)		(CHECK_NULL(A)->ag_enum = (B))
#define DEREF_ntype(A)			(CHECK_NULL(A)->ag_enum)


/* Definitions for enumeration BASE_TYPE */

#ifdef __STDC__
#define btype_none			((BASE_TYPE) 0UL)
#define btype_class			((BASE_TYPE) 1UL)
#define btype_struct_			((BASE_TYPE) 2UL)
#define btype_union_			((BASE_TYPE) 3UL)
#define btype_enum_			((BASE_TYPE) 4UL)
#define btype_alias			((BASE_TYPE) 5UL)
#define btype_any			((BASE_TYPE) 6UL)
#define btype_named			((BASE_TYPE) 7UL)
#define btype_signed			((BASE_TYPE) 8UL)
#define btype_unsigned			((BASE_TYPE) 16UL)
#define btype_char			((BASE_TYPE) 32UL)
#define btype_short			((BASE_TYPE) 64UL)
#define btype_int			((BASE_TYPE) 128UL)
#define btype_long			((BASE_TYPE) 256UL)
#define btype_long2			((BASE_TYPE) 512UL)
#define btype_float			((BASE_TYPE) 1024UL)
#define btype_double			((BASE_TYPE) 2048UL)
#define btype_void			((BASE_TYPE) 4096UL)
#define btype_bottom			((BASE_TYPE) 8192UL)
#define btype_bool			((BASE_TYPE) 16384UL)
#define btype_ptrdiff_t			((BASE_TYPE) 32768UL)
#define btype_size_t			((BASE_TYPE) 65536UL)
#define btype_wchar_t			((BASE_TYPE) 131072UL)
#define btype_schar			((BASE_TYPE) 40UL)
#define btype_uchar			((BASE_TYPE) 48UL)
#define btype_sshort			((BASE_TYPE) 200UL)
#define btype_ushort			((BASE_TYPE) 208UL)
#define btype_sint			((BASE_TYPE) 136UL)
#define btype_uint			((BASE_TYPE) 144UL)
#define btype_slong			((BASE_TYPE) 392UL)
#define btype_ulong			((BASE_TYPE) 400UL)
#define btype_llong			((BASE_TYPE) 768UL)
#define btype_sllong			((BASE_TYPE) 904UL)
#define btype_ullong			((BASE_TYPE) 912UL)
#define btype_ldouble			((BASE_TYPE) 2304UL)
#define btype_ellipsis			((BASE_TYPE) 262144UL)
#define btype_star			((BASE_TYPE) 524288UL)
#define btype_template			((BASE_TYPE) 1048576UL)
#define btype_typename			((BASE_TYPE) 2097152UL)
#define btype_args			((BASE_TYPE) 4194304UL)
#define btype_keyword			((BASE_TYPE) 154624UL)
#define btype_other			((BASE_TYPE) 261120UL)
#define btype_arith			((BASE_TYPE) 1152UL)
#define btype_scalar			((BASE_TYPE) 525440UL)
#define ORDER_btype			(4194305UL)
#else
#define btype_none			((BASE_TYPE) 0)
#define btype_class			((BASE_TYPE) 1)
#define btype_struct_			((BASE_TYPE) 2)
#define btype_union_			((BASE_TYPE) 3)
#define btype_enum_			((BASE_TYPE) 4)
#define btype_alias			((BASE_TYPE) 5)
#define btype_any			((BASE_TYPE) 6)
#define btype_named			((BASE_TYPE) 7)
#define btype_signed			((BASE_TYPE) 8)
#define btype_unsigned			((BASE_TYPE) 16)
#define btype_char			((BASE_TYPE) 32)
#define btype_short			((BASE_TYPE) 64)
#define btype_int			((BASE_TYPE) 128)
#define btype_long			((BASE_TYPE) 256)
#define btype_long2			((BASE_TYPE) 512)
#define btype_float			((BASE_TYPE) 1024)
#define btype_double			((BASE_TYPE) 2048)
#define btype_void			((BASE_TYPE) 4096)
#define btype_bottom			((BASE_TYPE) 8192)
#define btype_bool			((BASE_TYPE) 16384)
#define btype_ptrdiff_t			((BASE_TYPE) 32768)
#define btype_size_t			((BASE_TYPE) 65536)
#define btype_wchar_t			((BASE_TYPE) 131072)
#define btype_schar			((BASE_TYPE) 40)
#define btype_uchar			((BASE_TYPE) 48)
#define btype_sshort			((BASE_TYPE) 200)
#define btype_ushort			((BASE_TYPE) 208)
#define btype_sint			((BASE_TYPE) 136)
#define btype_uint			((BASE_TYPE) 144)
#define btype_slong			((BASE_TYPE) 392)
#define btype_ulong			((BASE_TYPE) 400)
#define btype_llong			((BASE_TYPE) 768)
#define btype_sllong			((BASE_TYPE) 904)
#define btype_ullong			((BASE_TYPE) 912)
#define btype_ldouble			((BASE_TYPE) 2304)
#define btype_ellipsis			((BASE_TYPE) 262144)
#define btype_star			((BASE_TYPE) 524288)
#define btype_template			((BASE_TYPE) 1048576)
#define btype_typename			((BASE_TYPE) 2097152)
#define btype_args			((BASE_TYPE) 4194304)
#define btype_keyword			((BASE_TYPE) 154624)
#define btype_other			((BASE_TYPE) 261120)
#define btype_arith			((BASE_TYPE) 1152)
#define btype_scalar			((BASE_TYPE) 525440)
#define ORDER_btype			((unsigned long) 4194305)
#endif
#define SIZE_btype			1

#define COPY_btype(A, B)		(CHECK_NULL(A)->ag_long_enum = (B))
#define DEREF_btype(A)			(CHECK_NULL(A)->ag_long_enum)


/* Definitions for enumeration CLASS_INFO */

#ifdef __STDC__
#define cinfo_none			((CLASS_INFO) 0UL)
#define cinfo_complete			((CLASS_INFO) 1UL)
#define cinfo_defined			((CLASS_INFO) 2UL)
#define cinfo_struct_			((CLASS_INFO) 4UL)
#define cinfo_union_			((CLASS_INFO) 8UL)
#define cinfo_template			((CLASS_INFO) 16UL)
#define cinfo_token			((CLASS_INFO) 32UL)
#define cinfo_pod			((CLASS_INFO) 64UL)
#define cinfo_nested			((CLASS_INFO) 128UL)
#define cinfo_rescan			((CLASS_INFO) 256UL)
#define cinfo_recursive			((CLASS_INFO) 512UL)
#define cinfo_incomplete		((CLASS_INFO) 1024UL)
#define cinfo_base			((CLASS_INFO) 2048UL)
#define cinfo_multiple_base		((CLASS_INFO) 4096UL)
#define cinfo_virtual_base		((CLASS_INFO) 8192UL)
#define cinfo_templ_base		((CLASS_INFO) 16384UL)
#define cinfo_ambiguous			((CLASS_INFO) 32768UL)
#define cinfo_empty			((CLASS_INFO) 65536UL)
#define cinfo_private			((CLASS_INFO) 131072UL)
#define cinfo_const			((CLASS_INFO) 262144UL)
#define cinfo_static			((CLASS_INFO) 524288UL)
#define cinfo_function			((CLASS_INFO) 1048576UL)
#define cinfo_params			((CLASS_INFO) 2097152UL)
#define cinfo_polymorphic		((CLASS_INFO) 4194304UL)
#define cinfo_poly_base			((CLASS_INFO) 8388608UL)
#define cinfo_abstract			((CLASS_INFO) 16777216UL)
#define cinfo_trivial_constr		((CLASS_INFO) 33554432UL)
#define cinfo_trivial_destr		((CLASS_INFO) 67108864UL)
#define cinfo_trivial_copy		((CLASS_INFO) 134217728UL)
#define cinfo_trivial_assign		((CLASS_INFO) 268435456UL)
#define cinfo_const_copy		((CLASS_INFO) 536870912UL)
#define cinfo_const_assign		((CLASS_INFO) 1073741824UL)
#define cinfo_usr_constr		((CLASS_INFO) 2147483648UL)
#define cinfo_key			((CLASS_INFO) 12UL)
#define cinfo_non_aggregate		((CLASS_INFO) 2151811104UL)
#define cinfo_force_copy		((CLASS_INFO) 3670016UL)
#define cinfo_trivial_make		((CLASS_INFO) 436207616UL)
#define cinfo_trivial			((CLASS_INFO) 503316480UL)
#define cinfo_implicit			((CLASS_INFO) 2113929216UL)
#define cinfo_default			((CLASS_INFO) 2113994816UL)
#define ORDER_cinfo			(2151811105UL)
#else
#define cinfo_none			((CLASS_INFO) 0)
#define cinfo_complete			((CLASS_INFO) 1)
#define cinfo_defined			((CLASS_INFO) 2)
#define cinfo_struct_			((CLASS_INFO) 4)
#define cinfo_union_			((CLASS_INFO) 8)
#define cinfo_template			((CLASS_INFO) 16)
#define cinfo_token			((CLASS_INFO) 32)
#define cinfo_pod			((CLASS_INFO) 64)
#define cinfo_nested			((CLASS_INFO) 128)
#define cinfo_rescan			((CLASS_INFO) 256)
#define cinfo_recursive			((CLASS_INFO) 512)
#define cinfo_incomplete		((CLASS_INFO) 1024)
#define cinfo_base			((CLASS_INFO) 2048)
#define cinfo_multiple_base		((CLASS_INFO) 4096)
#define cinfo_virtual_base		((CLASS_INFO) 8192)
#define cinfo_templ_base		((CLASS_INFO) 16384)
#define cinfo_ambiguous			((CLASS_INFO) 32768)
#define cinfo_empty			((CLASS_INFO) 65536)
#define cinfo_private			((CLASS_INFO) 131072)
#define cinfo_const			((CLASS_INFO) 262144)
#define cinfo_static			((CLASS_INFO) 524288)
#define cinfo_function			((CLASS_INFO) 1048576)
#define cinfo_params			((CLASS_INFO) 2097152)
#define cinfo_polymorphic		((CLASS_INFO) 4194304)
#define cinfo_poly_base			((CLASS_INFO) 8388608)
#define cinfo_abstract			((CLASS_INFO) 16777216)
#define cinfo_trivial_constr		((CLASS_INFO) 33554432)
#define cinfo_trivial_destr		((CLASS_INFO) 67108864)
#define cinfo_trivial_copy		((CLASS_INFO) 134217728)
#define cinfo_trivial_assign		((CLASS_INFO) 268435456)
#define cinfo_const_copy		((CLASS_INFO) 536870912)
#define cinfo_const_assign		((CLASS_INFO) 1073741824)
#define cinfo_usr_constr		((CLASS_INFO) 2147483648)
#define cinfo_key			((CLASS_INFO) 12)
#define cinfo_non_aggregate		((CLASS_INFO) 2151811104)
#define cinfo_force_copy		((CLASS_INFO) 3670016)
#define cinfo_trivial_make		((CLASS_INFO) 436207616)
#define cinfo_trivial			((CLASS_INFO) 503316480)
#define cinfo_implicit			((CLASS_INFO) 2113929216)
#define cinfo_default			((CLASS_INFO) 2113994816)
#define ORDER_cinfo			((unsigned long) 2151811105)
#endif
#define SIZE_cinfo			1

#define COPY_cinfo(A, B)		(CHECK_NULL(A)->ag_long_enum = (B))
#define DEREF_cinfo(A)			(CHECK_NULL(A)->ag_long_enum)


/* Definitions for enumeration CLASS_USAGE */

#define cusage_none			((CLASS_USAGE) 0)
#define cusage_address			((CLASS_USAGE) 1)
#define cusage_destr			((CLASS_USAGE) 2)
#define cusage_delete			((CLASS_USAGE) 4)
#define cusage_delete_array		((CLASS_USAGE) 8)
#define ORDER_cusage			((unsigned long) 9)
#define SIZE_cusage			1

#define COPY_cusage(A, B)		(CHECK_NULL(A)->ag_enum = (B))
#define DEREF_cusage(A)			(CHECK_NULL(A)->ag_enum)


/* Definitions for enumeration DECL_SPEC */

#ifdef __STDC__
#define dspec_none			((DECL_SPEC) 0UL)
#define dspec_used			((DECL_SPEC) 1UL)
#define dspec_called			((DECL_SPEC) 2UL)
#define dspec_defn			((DECL_SPEC) 4UL)
#define dspec_inherit			((DECL_SPEC) 8UL)
#define dspec_alias			((DECL_SPEC) 16UL)
#define dspec_done			((DECL_SPEC) 32UL)
#define dspec_static			((DECL_SPEC) 64UL)
#define dspec_extern			((DECL_SPEC) 128UL)
#define dspec_auto			((DECL_SPEC) 256UL)
#define dspec_register			((DECL_SPEC) 512UL)
#define dspec_mutable			((DECL_SPEC) 1024UL)
#define dspec_inline			((DECL_SPEC) 2048UL)
#define dspec_virtual			((DECL_SPEC) 4096UL)
#define dspec_explicit			((DECL_SPEC) 8192UL)
#define dspec_friend			((DECL_SPEC) 16384UL)
#define dspec_typedef			((DECL_SPEC) 32768UL)
#define dspec_public			((DECL_SPEC) 65536UL)
#define dspec_protected			((DECL_SPEC) 131072UL)
#define dspec_private			((DECL_SPEC) 196608UL)
#define dspec_public2			((DECL_SPEC) 262144UL)
#define dspec_protected2		((DECL_SPEC) 524288UL)
#define dspec_private2			((DECL_SPEC) 786432UL)
#define dspec_c				((DECL_SPEC) 1048576UL)
#define dspec_cpp			((DECL_SPEC) 2097152UL)
#define dspec_ignore			((DECL_SPEC) 4194304UL)
#define dspec_implicit			((DECL_SPEC) 8388608UL)
#define dspec_instance			((DECL_SPEC) 16777216UL)
#define dspec_main			((DECL_SPEC) 33554432UL)
#define dspec_pure			((DECL_SPEC) 67108864UL)
#define dspec_reserve			((DECL_SPEC) 134217728UL)
#define dspec_temp			((DECL_SPEC) 268435456UL)
#define dspec_template			((DECL_SPEC) 536870912UL)
#define dspec_token			((DECL_SPEC) 1073741824UL)
#define dspec_trivial			((DECL_SPEC) 2147483648UL)
#define dspec_linkage			((DECL_SPEC) 192UL)
#define dspec_storage			((DECL_SPEC) 1984UL)
#define dspec_function			((DECL_SPEC) 14336UL)
#define dspec_keyword			((DECL_SPEC) 65472UL)
#define dspec_duplicate			((DECL_SPEC) 65472UL)
#define dspec_access			((DECL_SPEC) 196608UL)
#define dspec_access2			((DECL_SPEC) 786432UL)
#define dspec_language			((DECL_SPEC) 3145728UL)
#define dspec_other			((DECL_SPEC) 4290772992UL)
#define ORDER_dspec			(4290772993UL)
#else
#define dspec_none			((DECL_SPEC) 0)
#define dspec_used			((DECL_SPEC) 1)
#define dspec_called			((DECL_SPEC) 2)
#define dspec_defn			((DECL_SPEC) 4)
#define dspec_inherit			((DECL_SPEC) 8)
#define dspec_alias			((DECL_SPEC) 16)
#define dspec_done			((DECL_SPEC) 32)
#define dspec_static			((DECL_SPEC) 64)
#define dspec_extern			((DECL_SPEC) 128)
#define dspec_auto			((DECL_SPEC) 256)
#define dspec_register			((DECL_SPEC) 512)
#define dspec_mutable			((DECL_SPEC) 1024)
#define dspec_inline			((DECL_SPEC) 2048)
#define dspec_virtual			((DECL_SPEC) 4096)
#define dspec_explicit			((DECL_SPEC) 8192)
#define dspec_friend			((DECL_SPEC) 16384)
#define dspec_typedef			((DECL_SPEC) 32768)
#define dspec_public			((DECL_SPEC) 65536)
#define dspec_protected			((DECL_SPEC) 131072)
#define dspec_private			((DECL_SPEC) 196608)
#define dspec_public2			((DECL_SPEC) 262144)
#define dspec_protected2		((DECL_SPEC) 524288)
#define dspec_private2			((DECL_SPEC) 786432)
#define dspec_c				((DECL_SPEC) 1048576)
#define dspec_cpp			((DECL_SPEC) 2097152)
#define dspec_ignore			((DECL_SPEC) 4194304)
#define dspec_implicit			((DECL_SPEC) 8388608)
#define dspec_instance			((DECL_SPEC) 16777216)
#define dspec_main			((DECL_SPEC) 33554432)
#define dspec_pure			((DECL_SPEC) 67108864)
#define dspec_reserve			((DECL_SPEC) 134217728)
#define dspec_temp			((DECL_SPEC) 268435456)
#define dspec_template			((DECL_SPEC) 536870912)
#define dspec_token			((DECL_SPEC) 1073741824)
#define dspec_trivial			((DECL_SPEC) 2147483648)
#define dspec_linkage			((DECL_SPEC) 192)
#define dspec_storage			((DECL_SPEC) 1984)
#define dspec_function			((DECL_SPEC) 14336)
#define dspec_keyword			((DECL_SPEC) 65472)
#define dspec_duplicate			((DECL_SPEC) 65472)
#define dspec_access			((DECL_SPEC) 196608)
#define dspec_access2			((DECL_SPEC) 786432)
#define dspec_language			((DECL_SPEC) 3145728)
#define dspec_other			((DECL_SPEC) 4290772992)
#define ORDER_dspec			((unsigned long) 4290772993)
#endif
#define SIZE_dspec			1

#define COPY_dspec(A, B)		(CHECK_NULL(A)->ag_long_enum = (B))
#define DEREF_dspec(A)			(CHECK_NULL(A)->ag_long_enum)
#define CONS_dspec(A, B, C)\
    {\
	c_class *x45_ = GEN_c_class(2, TYPEID_list);\
	COPY_dspec(x45_ + 1, (A));\
	x45_->ag_ptr = (B);\
	(C) = x45_;\
    }

#define UN_CONS_dspec(A, B, C)\
    {\
	c_class *x46_ = CHECK_NULL(C);\
	(A) = DEREF_dspec(x46_ + 1);\
	(B) = x46_->ag_ptr;\
    }

#define DESTROY_CONS_dspec(D, A, B, C)\
    {\
	c_class *x47_ = CHECK_NULL(C);\
	(A) = DEREF_dspec(x47_ + 1);\
	(B) = x47_->ag_ptr;\
	(D)(x47_, (unsigned)2);\
    }

#define PUSH_dspec(A, B)\
    {\
	c_class **r48_ = &(B);\
	c_class *x48_ = GEN_c_class(2, TYPEID_stack);\
	COPY_dspec(x48_ + 1, (A));\
	x48_->ag_ptr = *r48_;\
	*r48_ = x48_;\
    }

#define POP_dspec(A, B)\
    {\
	c_class **r49_ = &(B);\
	c_class *x49_ = CHECK_NULL(*r49_);\
	(A) = DEREF_dspec(x49_ + 1);\
	*r49_ = x49_->ag_ptr;\
	destroy_c_class(x49_, (unsigned)2);\
    }


/* Definitions for enumeration QUALIFIER */

#define qual_none			((QUALIFIER) 0)
#define qual_nested			((QUALIFIER) 1)
#define qual_full			((QUALIFIER) 2)
#define qual_top			((QUALIFIER) 3)
#define qual_mark			((QUALIFIER) 4)
#define qual_explicit			((QUALIFIER) 3)
#define ORDER_qual			((unsigned long) 5)
#define SIZE_qual			1

#define COPY_qual(A, B)			(CHECK_NULL(A)->ag_enum = (B))
#define DEREF_qual(A)			(CHECK_NULL(A)->ag_enum)


/* Definitions for enumeration NTEST */

#define ntest_eq			((NTEST) 0)
#define ntest_greater			((NTEST) 1)
#define ntest_greater_eq		((NTEST) 2)
#define ntest_less			((NTEST) 3)
#define ntest_less_eq			((NTEST) 4)
#define ntest_not_eq			((NTEST) 5)
#define ntest_not_greater		((NTEST) 6)
#define ntest_not_greater_eq		((NTEST) 7)
#define ntest_not_less			((NTEST) 8)
#define ntest_not_less_eq		((NTEST) 9)
#define ntest_not_not_eq		((NTEST) 10)
#define ntest_none			((NTEST) 11)
#define ntest_negate			((NTEST) 5)
#define ntest_not			((NTEST) 5)
#define ntest_not_not			((NTEST) 10)
#define ORDER_ntest			((unsigned long) 12)
#define SIZE_ntest			1

#define COPY_ntest(A, B)		(CHECK_NULL(A)->ag_enum = (B))
#define DEREF_ntest(A)			(CHECK_NULL(A)->ag_enum)


/* Definitions for enumeration RMODE */

#define rmode_as_state			((RMODE) 0)
#define rmode_to_nearest		((RMODE) 1)
#define rmode_to_larger			((RMODE) 2)
#define rmode_to_smaller		((RMODE) 3)
#define rmode_to_zero			((RMODE) 4)
#define ORDER_rmode			((unsigned long) 5)
#define SIZE_rmode			1

#define COPY_rmode(A, B)		(CHECK_NULL(A)->ag_enum = (B))
#define DEREF_rmode(A)			(CHECK_NULL(A)->ag_enum)


/* Definitions for structure VARIABLE */

#define var_id(P)			((P) + 0)
#define var_info(P)			((P) + 1)
#define SIZE_var			2

#define COPY_var(A, B)\
    {\
	c_class *x50_ = CHECK_NULL(A);\
	VARIABLE y50_;\
	y50_ = (B);\
	COPY_id(x50_ + 0, y50_.id);\
	COPY_dspec(x50_ + 1, y50_.info);\
    }

#define DEREF_var(A, B)\
    {\
	c_class *x51_ = CHECK_NULL(A);\
	VARIABLE *y51_ = &(B);\
	y51_->id = DEREF_id(x51_ + 0);\
	y51_->info = DEREF_dspec(x51_ + 1);\
    }

#define MAKE_var(id_, info_, var_)\
    {\
	c_class *x52_ = CHECK_NULL(var_);\
	COPY_id(x52_ + 0, (id_));\
	COPY_dspec(x52_ + 1, (info_));\
    }

#define CONS_var(A, B, C)\
    {\
	c_class *x53_ = GEN_c_class(3, TYPEID_list);\
	COPY_var(x53_ + 1, (A));\
	x53_->ag_ptr = (B);\
	(C) = x53_;\
    }

#define UN_CONS_var(A, B, C)\
    {\
	c_class *x54_ = CHECK_NULL(C);\
	DEREF_var(x54_ + 1, (A));\
	(B) = x54_->ag_ptr;\
    }

#define DESTROY_CONS_var(D, A, B, C)\
    {\
	c_class *x55_ = CHECK_NULL(C);\
	DEREF_var(x55_ + 1, (A));\
	(B) = x55_->ag_ptr;\
	(D)(x55_, (unsigned)3);\
    }

#define PUSH_var(A, B)\
    {\
	c_class **r56_ = &(B);\
	c_class *x56_ = GEN_c_class(3, TYPEID_stack);\
	COPY_var(x56_ + 1, (A));\
	x56_->ag_ptr = *r56_;\
	*r56_ = x56_;\
    }

#define POP_var(A, B)\
    {\
	c_class **r57_ = &(B);\
	c_class *x57_ = CHECK_NULL(*r57_);\
	DEREF_var(x57_ + 1, (A));\
	*r57_ = x57_->ag_ptr;\
	destroy_c_class(x57_, (unsigned)3);\
    }


/* Definitions for structure LOCATION */

#define loc_line(P)			((P) + 0)
#define loc_column(P)			((P) + 1)
#define loc_posn(P)			((P) + 2)
#define SIZE_loc			3

#define COPY_loc(A, B)\
    {\
	c_class *x58_ = CHECK_NULL(A);\
	LOCATION y58_;\
	y58_ = (B);\
	COPY_ulong(x58_ + 0, y58_.line);\
	COPY_ulong(x58_ + 1, y58_.column);\
	COPY_ptr(x58_ + 2, y58_.posn);\
    }

#define DEREF_loc(A, B)\
    {\
	c_class *x59_ = CHECK_NULL(A);\
	LOCATION *y59_ = &(B);\
	y59_->line = DEREF_ulong(x59_ + 0);\
	y59_->column = DEREF_ulong(x59_ + 1);\
	y59_->posn = DEREF_ptr(x59_ + 2);\
    }

#define MAKE_loc(line_, column_, posn_, loc_)\
    {\
	c_class *x60_ = CHECK_NULL(loc_);\
	COPY_ulong(x60_ + 0, (line_));\
	COPY_ulong(x60_ + 1, (column_));\
	COPY_ptr(x60_ + 2, (posn_));\
    }

#define CONS_loc(A, B, C)\
    {\
	c_class *x61_ = GEN_c_class(4, TYPEID_list);\
	COPY_loc(x61_ + 1, (A));\
	x61_->ag_ptr = (B);\
	(C) = x61_;\
    }

#define UN_CONS_loc(A, B, C)\
    {\
	c_class *x62_ = CHECK_NULL(C);\
	DEREF_loc(x62_ + 1, (A));\
	(B) = x62_->ag_ptr;\
    }

#define DESTROY_CONS_loc(D, A, B, C)\
    {\
	c_class *x63_ = CHECK_NULL(C);\
	DEREF_loc(x63_ + 1, (A));\
	(B) = x63_->ag_ptr;\
	(D)(x63_, (unsigned)4);\
    }

#define PUSH_loc(A, B)\
    {\
	c_class **r64_ = &(B);\
	c_class *x64_ = GEN_c_class(4, TYPEID_stack);\
	COPY_loc(x64_ + 1, (A));\
	x64_->ag_ptr = *r64_;\
	*r64_ = x64_;\
    }

#define POP_loc(A, B)\
    {\
	c_class **r65_ = &(B);\
	c_class *x65_ = CHECK_NULL(*r65_);\
	DEREF_loc(x65_ + 1, (A));\
	*r65_ = x65_->ag_ptr;\
	destroy_c_class(x65_, (unsigned)4);\
    }


/* Definitions for structure POSITION */

#define posn_file(P)			((P) + 0)
#define posn_input(P)			((P) + 1)
#define posn_base(P)			((P) + 2)
#define posn_dir(P)			((P) + 3)
#define posn_offset(P)			((P) + 4)
#define posn_from(P)			((P) + 5)
#define posn_datestamp(P)		((P) + 6)
#define posn_tok(P)			((P) + 7)
#define SIZE_posn			8

#define COPY_posn(A, B)\
    {\
	c_class *x66_ = CHECK_NULL(A);\
	POSITION y66_;\
	y66_ = (B);\
	COPY_string(x66_ + 0, y66_.file);\
	COPY_string(x66_ + 1, y66_.input);\
	COPY_string(x66_ + 2, y66_.base);\
	COPY_string(x66_ + 3, y66_.dir);\
	COPY_ulong(x66_ + 4, y66_.offset);\
	COPY_ptr(x66_ + 5, y66_.from);\
	COPY_ulong(x66_ + 6, y66_.datestamp);\
	COPY_ulong(x66_ + 7, y66_.tok);\
    }

#define DEREF_posn(A, B)\
    {\
	c_class *x67_ = CHECK_NULL(A);\
	POSITION *y67_ = &(B);\
	y67_->file = DEREF_string(x67_ + 0);\
	y67_->input = DEREF_string(x67_ + 1);\
	y67_->base = DEREF_string(x67_ + 2);\
	y67_->dir = DEREF_string(x67_ + 3);\
	y67_->offset = DEREF_ulong(x67_ + 4);\
	y67_->from = DEREF_ptr(x67_ + 5);\
	y67_->datestamp = DEREF_ulong(x67_ + 6);\
	y67_->tok = DEREF_ulong(x67_ + 7);\
    }

#define MAKE_posn(file_, input_, base_, dir_, offset_, from_, datestamp_, posn_)\
    {\
	c_class *x68_ = CHECK_NULL(posn_);\
	COPY_string(x68_ + 0, (file_));\
	COPY_string(x68_ + 1, (input_));\
	COPY_string(x68_ + 2, (base_));\
	COPY_string(x68_ + 3, (dir_));\
	COPY_ulong(x68_ + 4, (offset_));\
	COPY_ptr(x68_ + 5, (from_));\
	COPY_ulong(x68_ + 6, (datestamp_));\
	COPY_ulong(x68_ + 7, LINK_NONE);\
    }

#define CONS_posn(A, B, C)\
    {\
	c_class *x69_ = GEN_c_class(9, TYPEID_list);\
	COPY_posn(x69_ + 1, (A));\
	x69_->ag_ptr = (B);\
	(C) = x69_;\
    }

#define UN_CONS_posn(A, B, C)\
    {\
	c_class *x70_ = CHECK_NULL(C);\
	DEREF_posn(x70_ + 1, (A));\
	(B) = x70_->ag_ptr;\
    }

#define DESTROY_CONS_posn(D, A, B, C)\
    {\
	c_class *x71_ = CHECK_NULL(C);\
	DEREF_posn(x71_ + 1, (A));\
	(B) = x71_->ag_ptr;\
	(D)(x71_, (unsigned)9);\
    }

#define PUSH_posn(A, B)\
    {\
	c_class **r72_ = &(B);\
	c_class *x72_ = GEN_c_class(9, TYPEID_stack);\
	COPY_posn(x72_ + 1, (A));\
	x72_->ag_ptr = *r72_;\
	*r72_ = x72_;\
    }

#define POP_posn(A, B)\
    {\
	c_class **r73_ = &(B);\
	c_class *x73_ = CHECK_NULL(*r73_);\
	DEREF_posn(x73_ + 1, (A));\
	*r73_ = x73_->ag_ptr;\
	destroy_c_class(x73_, (unsigned)9);\
    }


/* Definitions for union INT_TYPE */

#define ORDER_itype			((unsigned) 6)
#define SIZE_itype			1
#define NULL_itype			((INT_TYPE) 0)
#define IS_NULL_itype(A)		((A) == 0)
#define EQ_itype(A, B)			((A) == (B))

#define COPY_itype(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_itype(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_itype(A, B, C)\
    {\
	c_class *x74_ = GEN_c_class(2, TYPEID_list);\
	COPY_itype(x74_ + 1, (A));\
	x74_->ag_ptr = (B);\
	(C) = x74_;\
    }

#define UN_CONS_itype(A, B, C)\
    {\
	c_class *x75_ = CHECK_NULL(C);\
	(A) = DEREF_itype(x75_ + 1);\
	(B) = x75_->ag_ptr;\
    }

#define DESTROY_CONS_itype(D, A, B, C)\
    {\
	c_class *x76_ = CHECK_NULL(C);\
	(A) = DEREF_itype(x76_ + 1);\
	(B) = x76_->ag_ptr;\
	(D)(x76_, (unsigned)2);\
    }

#define PUSH_itype(A, B)\
    {\
	c_class **r77_ = &(B);\
	c_class *x77_ = GEN_c_class(2, TYPEID_stack);\
	COPY_itype(x77_ + 1, (A));\
	x77_->ag_ptr = *r77_;\
	*r77_ = x77_;\
    }

#define POP_itype(A, B)\
    {\
	c_class **r78_ = &(B);\
	c_class *x78_ = CHECK_NULL(*r78_);\
	(A) = DEREF_itype(x78_ + 1);\
	*r78_ = x78_->ag_ptr;\
	destroy_c_class(x78_, (unsigned)2);\
    }


/* Definitions for union FLOAT_TYPE */

#define ORDER_ftype			((unsigned) 4)
#define SIZE_ftype			1
#define NULL_ftype			((FLOAT_TYPE) 0)
#define IS_NULL_ftype(A)		((A) == 0)
#define EQ_ftype(A, B)			((A) == (B))

#define COPY_ftype(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_ftype(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_ftype(A, B, C)\
    {\
	c_class *x79_ = GEN_c_class(2, TYPEID_list);\
	COPY_ftype(x79_ + 1, (A));\
	x79_->ag_ptr = (B);\
	(C) = x79_;\
    }

#define UN_CONS_ftype(A, B, C)\
    {\
	c_class *x80_ = CHECK_NULL(C);\
	(A) = DEREF_ftype(x80_ + 1);\
	(B) = x80_->ag_ptr;\
    }

#define DESTROY_CONS_ftype(D, A, B, C)\
    {\
	c_class *x81_ = CHECK_NULL(C);\
	(A) = DEREF_ftype(x81_ + 1);\
	(B) = x81_->ag_ptr;\
	(D)(x81_, (unsigned)2);\
    }

#define PUSH_ftype(A, B)\
    {\
	c_class **r82_ = &(B);\
	c_class *x82_ = GEN_c_class(2, TYPEID_stack);\
	COPY_ftype(x82_ + 1, (A));\
	x82_->ag_ptr = *r82_;\
	*r82_ = x82_;\
    }

#define POP_ftype(A, B)\
    {\
	c_class **r83_ = &(B);\
	c_class *x83_ = CHECK_NULL(*r83_);\
	(A) = DEREF_ftype(x83_ + 1);\
	*r83_ = x83_->ag_ptr;\
	destroy_c_class(x83_, (unsigned)2);\
    }


/* Definitions for union CLASS_TYPE */

#define ORDER_ctype			((unsigned) 1)
#define SIZE_ctype			1
#define NULL_ctype			((CLASS_TYPE) 0)
#define IS_NULL_ctype(A)		((A) == 0)
#define EQ_ctype(A, B)			((A) == (B))

#define COPY_ctype(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_ctype(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_ctype(A, B, C)\
    {\
	c_class *x84_ = GEN_c_class(2, TYPEID_list);\
	COPY_ctype(x84_ + 1, (A));\
	x84_->ag_ptr = (B);\
	(C) = x84_;\
    }

#define UN_CONS_ctype(A, B, C)\
    {\
	c_class *x85_ = CHECK_NULL(C);\
	(A) = DEREF_ctype(x85_ + 1);\
	(B) = x85_->ag_ptr;\
    }

#define DESTROY_CONS_ctype(D, A, B, C)\
    {\
	c_class *x86_ = CHECK_NULL(C);\
	(A) = DEREF_ctype(x86_ + 1);\
	(B) = x86_->ag_ptr;\
	(D)(x86_, (unsigned)2);\
    }

#define PUSH_ctype(A, B)\
    {\
	c_class **r87_ = &(B);\
	c_class *x87_ = GEN_c_class(2, TYPEID_stack);\
	COPY_ctype(x87_ + 1, (A));\
	x87_->ag_ptr = *r87_;\
	*r87_ = x87_;\
    }

#define POP_ctype(A, B)\
    {\
	c_class **r88_ = &(B);\
	c_class *x88_ = CHECK_NULL(*r88_);\
	(A) = DEREF_ctype(x88_ + 1);\
	*r88_ = x88_->ag_ptr;\
	destroy_c_class(x88_, (unsigned)2);\
    }


/* Definitions for union GRAPH */

#define ORDER_graph			((unsigned) 1)
#define SIZE_graph			1
#define NULL_graph			((GRAPH) 0)
#define IS_NULL_graph(A)		((A) == 0)
#define EQ_graph(A, B)			((A) == (B))

#define COPY_graph(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_graph(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_graph(A, B, C)\
    {\
	c_class *x89_ = GEN_c_class(2, TYPEID_list);\
	COPY_graph(x89_ + 1, (A));\
	x89_->ag_ptr = (B);\
	(C) = x89_;\
    }

#define UN_CONS_graph(A, B, C)\
    {\
	c_class *x90_ = CHECK_NULL(C);\
	(A) = DEREF_graph(x90_ + 1);\
	(B) = x90_->ag_ptr;\
    }

#define DESTROY_CONS_graph(D, A, B, C)\
    {\
	c_class *x91_ = CHECK_NULL(C);\
	(A) = DEREF_graph(x91_ + 1);\
	(B) = x91_->ag_ptr;\
	(D)(x91_, (unsigned)2);\
    }

#define PUSH_graph(A, B)\
    {\
	c_class **r92_ = &(B);\
	c_class *x92_ = GEN_c_class(2, TYPEID_stack);\
	COPY_graph(x92_ + 1, (A));\
	x92_->ag_ptr = *r92_;\
	*r92_ = x92_;\
    }

#define POP_graph(A, B)\
    {\
	c_class **r93_ = &(B);\
	c_class *x93_ = CHECK_NULL(*r93_);\
	(A) = DEREF_graph(x93_ + 1);\
	*r93_ = x93_->ag_ptr;\
	destroy_c_class(x93_, (unsigned)2);\
    }


/* Definitions for union VIRTUAL */

#define ORDER_virt			((unsigned) 6)
#define SIZE_virt			1
#define NULL_virt			((VIRTUAL) 0)
#define IS_NULL_virt(A)			((A) == 0)
#define EQ_virt(A, B)			((A) == (B))

#define COPY_virt(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_virt(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_virt(A, B, C)\
    {\
	c_class *x94_ = GEN_c_class(2, TYPEID_list);\
	COPY_virt(x94_ + 1, (A));\
	x94_->ag_ptr = (B);\
	(C) = x94_;\
    }

#define UN_CONS_virt(A, B, C)\
    {\
	c_class *x95_ = CHECK_NULL(C);\
	(A) = DEREF_virt(x95_ + 1);\
	(B) = x95_->ag_ptr;\
    }

#define DESTROY_CONS_virt(D, A, B, C)\
    {\
	c_class *x96_ = CHECK_NULL(C);\
	(A) = DEREF_virt(x96_ + 1);\
	(B) = x96_->ag_ptr;\
	(D)(x96_, (unsigned)2);\
    }

#define PUSH_virt(A, B)\
    {\
	c_class **r97_ = &(B);\
	c_class *x97_ = GEN_c_class(2, TYPEID_stack);\
	COPY_virt(x97_ + 1, (A));\
	x97_->ag_ptr = *r97_;\
	*r97_ = x97_;\
    }

#define POP_virt(A, B)\
    {\
	c_class **r98_ = &(B);\
	c_class *x98_ = CHECK_NULL(*r98_);\
	(A) = DEREF_virt(x98_ + 1);\
	*r98_ = x98_->ag_ptr;\
	destroy_c_class(x98_, (unsigned)2);\
    }


/* Definitions for union ENUM_TYPE */

#define ORDER_etype			((unsigned) 1)
#define SIZE_etype			1
#define NULL_etype			((ENUM_TYPE) 0)
#define IS_NULL_etype(A)		((A) == 0)
#define EQ_etype(A, B)			((A) == (B))

#define COPY_etype(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_etype(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_etype(A, B, C)\
    {\
	c_class *x99_ = GEN_c_class(2, TYPEID_list);\
	COPY_etype(x99_ + 1, (A));\
	x99_->ag_ptr = (B);\
	(C) = x99_;\
    }

#define UN_CONS_etype(A, B, C)\
    {\
	c_class *x100_ = CHECK_NULL(C);\
	(A) = DEREF_etype(x100_ + 1);\
	(B) = x100_->ag_ptr;\
    }

#define DESTROY_CONS_etype(D, A, B, C)\
    {\
	c_class *x101_ = CHECK_NULL(C);\
	(A) = DEREF_etype(x101_ + 1);\
	(B) = x101_->ag_ptr;\
	(D)(x101_, (unsigned)2);\
    }

#define PUSH_etype(A, B)\
    {\
	c_class **r102_ = &(B);\
	c_class *x102_ = GEN_c_class(2, TYPEID_stack);\
	COPY_etype(x102_ + 1, (A));\
	x102_->ag_ptr = *r102_;\
	*r102_ = x102_;\
    }

#define POP_etype(A, B)\
    {\
	c_class **r103_ = &(B);\
	c_class *x103_ = CHECK_NULL(*r103_);\
	(A) = DEREF_etype(x103_ + 1);\
	*r103_ = x103_->ag_ptr;\
	destroy_c_class(x103_, (unsigned)2);\
    }


/* Definitions for union TYPE */

#define ORDER_type			((unsigned) 18)
#define SIZE_type			1
#define NULL_type			((TYPE) 0)
#define IS_NULL_type(A)			((A) == 0)
#define EQ_type(A, B)			((A) == (B))

#define COPY_type(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_type(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_type(A, B, C)\
    {\
	c_class *x104_ = GEN_c_class(2, TYPEID_list);\
	COPY_type(x104_ + 1, (A));\
	x104_->ag_ptr = (B);\
	(C) = x104_;\
    }

#define UN_CONS_type(A, B, C)\
    {\
	c_class *x105_ = CHECK_NULL(C);\
	(A) = DEREF_type(x105_ + 1);\
	(B) = x105_->ag_ptr;\
    }

#define DESTROY_CONS_type(D, A, B, C)\
    {\
	c_class *x106_ = CHECK_NULL(C);\
	(A) = DEREF_type(x106_ + 1);\
	(B) = x106_->ag_ptr;\
	(D)(x106_, (unsigned)2);\
    }

#define PUSH_type(A, B)\
    {\
	c_class **r107_ = &(B);\
	c_class *x107_ = GEN_c_class(2, TYPEID_stack);\
	COPY_type(x107_ + 1, (A));\
	x107_->ag_ptr = *r107_;\
	*r107_ = x107_;\
    }

#define POP_type(A, B)\
    {\
	c_class **r108_ = &(B);\
	c_class *x108_ = CHECK_NULL(*r108_);\
	(A) = DEREF_type(x108_ + 1);\
	*r108_ = x108_->ag_ptr;\
	destroy_c_class(x108_, (unsigned)2);\
    }


/* Definitions for union HASHID */

#define ORDER_hashid			((unsigned) 7)
#define SIZE_hashid			1
#define NULL_hashid			((HASHID) 0)
#define IS_NULL_hashid(A)		((A) == 0)
#define EQ_hashid(A, B)			((A) == (B))

#define COPY_hashid(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_hashid(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_hashid(A, B, C)\
    {\
	c_class *x109_ = GEN_c_class(2, TYPEID_list);\
	COPY_hashid(x109_ + 1, (A));\
	x109_->ag_ptr = (B);\
	(C) = x109_;\
    }

#define UN_CONS_hashid(A, B, C)\
    {\
	c_class *x110_ = CHECK_NULL(C);\
	(A) = DEREF_hashid(x110_ + 1);\
	(B) = x110_->ag_ptr;\
    }

#define DESTROY_CONS_hashid(D, A, B, C)\
    {\
	c_class *x111_ = CHECK_NULL(C);\
	(A) = DEREF_hashid(x111_ + 1);\
	(B) = x111_->ag_ptr;\
	(D)(x111_, (unsigned)2);\
    }

#define PUSH_hashid(A, B)\
    {\
	c_class **r112_ = &(B);\
	c_class *x112_ = GEN_c_class(2, TYPEID_stack);\
	COPY_hashid(x112_ + 1, (A));\
	x112_->ag_ptr = *r112_;\
	*r112_ = x112_;\
    }

#define POP_hashid(A, B)\
    {\
	c_class **r113_ = &(B);\
	c_class *x113_ = CHECK_NULL(*r113_);\
	(A) = DEREF_hashid(x113_ + 1);\
	*r113_ = x113_->ag_ptr;\
	destroy_c_class(x113_, (unsigned)2);\
    }


/* Definitions for union IDENTIFIER */

#define ORDER_id			((unsigned) 29)
#define SIZE_id				1
#define NULL_id				((IDENTIFIER) 0)
#define IS_NULL_id(A)			((A) == 0)
#define EQ_id(A, B)			((A) == (B))

#define COPY_id(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_id(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_id(A, B, C)\
    {\
	c_class *x114_ = GEN_c_class(2, TYPEID_list);\
	COPY_id(x114_ + 1, (A));\
	x114_->ag_ptr = (B);\
	(C) = x114_;\
    }

#define UN_CONS_id(A, B, C)\
    {\
	c_class *x115_ = CHECK_NULL(C);\
	(A) = DEREF_id(x115_ + 1);\
	(B) = x115_->ag_ptr;\
    }

#define DESTROY_CONS_id(D, A, B, C)\
    {\
	c_class *x116_ = CHECK_NULL(C);\
	(A) = DEREF_id(x116_ + 1);\
	(B) = x116_->ag_ptr;\
	(D)(x116_, (unsigned)2);\
    }

#define PUSH_id(A, B)\
    {\
	c_class **r117_ = &(B);\
	c_class *x117_ = GEN_c_class(2, TYPEID_stack);\
	COPY_id(x117_ + 1, (A));\
	x117_->ag_ptr = *r117_;\
	*r117_ = x117_;\
    }

#define POP_id(A, B)\
    {\
	c_class **r118_ = &(B);\
	c_class *x118_ = CHECK_NULL(*r118_);\
	(A) = DEREF_id(x118_ + 1);\
	*r118_ = x118_->ag_ptr;\
	destroy_c_class(x118_, (unsigned)2);\
    }


/* Definitions for union MEMBER */

#define ORDER_member			((unsigned) 2)
#define SIZE_member			1
#define NULL_member			((MEMBER) 0)
#define IS_NULL_member(A)		((A) == 0)
#define EQ_member(A, B)			((A) == (B))

#define COPY_member(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_member(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_member(A, B, C)\
    {\
	c_class *x119_ = GEN_c_class(2, TYPEID_list);\
	COPY_member(x119_ + 1, (A));\
	x119_->ag_ptr = (B);\
	(C) = x119_;\
    }

#define UN_CONS_member(A, B, C)\
    {\
	c_class *x120_ = CHECK_NULL(C);\
	(A) = DEREF_member(x120_ + 1);\
	(B) = x120_->ag_ptr;\
    }

#define DESTROY_CONS_member(D, A, B, C)\
    {\
	c_class *x121_ = CHECK_NULL(C);\
	(A) = DEREF_member(x121_ + 1);\
	(B) = x121_->ag_ptr;\
	(D)(x121_, (unsigned)2);\
    }

#define PUSH_member(A, B)\
    {\
	c_class **r122_ = &(B);\
	c_class *x122_ = GEN_c_class(2, TYPEID_stack);\
	COPY_member(x122_ + 1, (A));\
	x122_->ag_ptr = *r122_;\
	*r122_ = x122_;\
    }

#define POP_member(A, B)\
    {\
	c_class **r123_ = &(B);\
	c_class *x123_ = CHECK_NULL(*r123_);\
	(A) = DEREF_member(x123_ + 1);\
	*r123_ = x123_->ag_ptr;\
	destroy_c_class(x123_, (unsigned)2);\
    }


/* Definitions for union NAMESPACE */

#define ORDER_nspace			((unsigned) 9)
#define SIZE_nspace			1
#define NULL_nspace			((NAMESPACE) 0)
#define IS_NULL_nspace(A)		((A) == 0)
#define EQ_nspace(A, B)			((A) == (B))

#define COPY_nspace(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_nspace(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_nspace(A, B, C)\
    {\
	c_class *x124_ = GEN_c_class(2, TYPEID_list);\
	COPY_nspace(x124_ + 1, (A));\
	x124_->ag_ptr = (B);\
	(C) = x124_;\
    }

#define UN_CONS_nspace(A, B, C)\
    {\
	c_class *x125_ = CHECK_NULL(C);\
	(A) = DEREF_nspace(x125_ + 1);\
	(B) = x125_->ag_ptr;\
    }

#define DESTROY_CONS_nspace(D, A, B, C)\
    {\
	c_class *x126_ = CHECK_NULL(C);\
	(A) = DEREF_nspace(x126_ + 1);\
	(B) = x126_->ag_ptr;\
	(D)(x126_, (unsigned)2);\
    }

#define PUSH_nspace(A, B)\
    {\
	c_class **r127_ = &(B);\
	c_class *x127_ = GEN_c_class(2, TYPEID_stack);\
	COPY_nspace(x127_ + 1, (A));\
	x127_->ag_ptr = *r127_;\
	*r127_ = x127_;\
    }

#define POP_nspace(A, B)\
    {\
	c_class **r128_ = &(B);\
	c_class *x128_ = CHECK_NULL(*r128_);\
	(A) = DEREF_nspace(x128_ + 1);\
	*r128_ = x128_->ag_ptr;\
	destroy_c_class(x128_, (unsigned)2);\
    }


/* Definitions for union NAT */

#define ORDER_nat			((unsigned) 5)
#define SIZE_nat			1
#define NULL_nat			((NAT) 0)
#define IS_NULL_nat(A)			((A) == 0)
#define EQ_nat(A, B)			((A) == (B))

#define COPY_nat(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_nat(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_nat(A, B, C)\
    {\
	c_class *x129_ = GEN_c_class(2, TYPEID_list);\
	COPY_nat(x129_ + 1, (A));\
	x129_->ag_ptr = (B);\
	(C) = x129_;\
    }

#define UN_CONS_nat(A, B, C)\
    {\
	c_class *x130_ = CHECK_NULL(C);\
	(A) = DEREF_nat(x130_ + 1);\
	(B) = x130_->ag_ptr;\
    }

#define DESTROY_CONS_nat(D, A, B, C)\
    {\
	c_class *x131_ = CHECK_NULL(C);\
	(A) = DEREF_nat(x131_ + 1);\
	(B) = x131_->ag_ptr;\
	(D)(x131_, (unsigned)2);\
    }

#define PUSH_nat(A, B)\
    {\
	c_class **r132_ = &(B);\
	c_class *x132_ = GEN_c_class(2, TYPEID_stack);\
	COPY_nat(x132_ + 1, (A));\
	x132_->ag_ptr = *r132_;\
	*r132_ = x132_;\
    }

#define POP_nat(A, B)\
    {\
	c_class **r133_ = &(B);\
	c_class *x133_ = CHECK_NULL(*r133_);\
	(A) = DEREF_nat(x133_ + 1);\
	*r133_ = x133_->ag_ptr;\
	destroy_c_class(x133_, (unsigned)2);\
    }


/* Definitions for union FLOAT */

#define ORDER_flt			((unsigned) 1)
#define SIZE_flt			1
#define NULL_flt			((FLOAT) 0)
#define IS_NULL_flt(A)			((A) == 0)
#define EQ_flt(A, B)			((A) == (B))

#define COPY_flt(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_flt(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_flt(A, B, C)\
    {\
	c_class *x134_ = GEN_c_class(2, TYPEID_list);\
	COPY_flt(x134_ + 1, (A));\
	x134_->ag_ptr = (B);\
	(C) = x134_;\
    }

#define UN_CONS_flt(A, B, C)\
    {\
	c_class *x135_ = CHECK_NULL(C);\
	(A) = DEREF_flt(x135_ + 1);\
	(B) = x135_->ag_ptr;\
    }

#define DESTROY_CONS_flt(D, A, B, C)\
    {\
	c_class *x136_ = CHECK_NULL(C);\
	(A) = DEREF_flt(x136_ + 1);\
	(B) = x136_->ag_ptr;\
	(D)(x136_, (unsigned)2);\
    }

#define PUSH_flt(A, B)\
    {\
	c_class **r137_ = &(B);\
	c_class *x137_ = GEN_c_class(2, TYPEID_stack);\
	COPY_flt(x137_ + 1, (A));\
	x137_->ag_ptr = *r137_;\
	*r137_ = x137_;\
    }

#define POP_flt(A, B)\
    {\
	c_class **r138_ = &(B);\
	c_class *x138_ = CHECK_NULL(*r138_);\
	(A) = DEREF_flt(x138_ + 1);\
	*r138_ = x138_->ag_ptr;\
	destroy_c_class(x138_, (unsigned)2);\
    }


/* Definitions for union STRING */

#define ORDER_str			((unsigned) 1)
#define SIZE_str			1
#define NULL_str			((STRING) 0)
#define IS_NULL_str(A)			((A) == 0)
#define EQ_str(A, B)			((A) == (B))

#define COPY_str(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_str(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_str(A, B, C)\
    {\
	c_class *x139_ = GEN_c_class(2, TYPEID_list);\
	COPY_str(x139_ + 1, (A));\
	x139_->ag_ptr = (B);\
	(C) = x139_;\
    }

#define UN_CONS_str(A, B, C)\
    {\
	c_class *x140_ = CHECK_NULL(C);\
	(A) = DEREF_str(x140_ + 1);\
	(B) = x140_->ag_ptr;\
    }

#define DESTROY_CONS_str(D, A, B, C)\
    {\
	c_class *x141_ = CHECK_NULL(C);\
	(A) = DEREF_str(x141_ + 1);\
	(B) = x141_->ag_ptr;\
	(D)(x141_, (unsigned)2);\
    }

#define PUSH_str(A, B)\
    {\
	c_class **r142_ = &(B);\
	c_class *x142_ = GEN_c_class(2, TYPEID_stack);\
	COPY_str(x142_ + 1, (A));\
	x142_->ag_ptr = *r142_;\
	*r142_ = x142_;\
    }

#define POP_str(A, B)\
    {\
	c_class **r143_ = &(B);\
	c_class *x143_ = CHECK_NULL(*r143_);\
	(A) = DEREF_str(x143_ + 1);\
	*r143_ = x143_->ag_ptr;\
	destroy_c_class(x143_, (unsigned)2);\
    }


/* Definitions for union EXP */

#define ORDER_exp			((unsigned) 88)
#define SIZE_exp			1
#define NULL_exp			((EXP) 0)
#define IS_NULL_exp(A)			((A) == 0)
#define EQ_exp(A, B)			((A) == (B))

#define COPY_exp(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_exp(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_exp(A, B, C)\
    {\
	c_class *x144_ = GEN_c_class(2, TYPEID_list);\
	COPY_exp(x144_ + 1, (A));\
	x144_->ag_ptr = (B);\
	(C) = x144_;\
    }

#define UN_CONS_exp(A, B, C)\
    {\
	c_class *x145_ = CHECK_NULL(C);\
	(A) = DEREF_exp(x145_ + 1);\
	(B) = x145_->ag_ptr;\
    }

#define DESTROY_CONS_exp(D, A, B, C)\
    {\
	c_class *x146_ = CHECK_NULL(C);\
	(A) = DEREF_exp(x146_ + 1);\
	(B) = x146_->ag_ptr;\
	(D)(x146_, (unsigned)2);\
    }

#define PUSH_exp(A, B)\
    {\
	c_class **r147_ = &(B);\
	c_class *x147_ = GEN_c_class(2, TYPEID_stack);\
	COPY_exp(x147_ + 1, (A));\
	x147_->ag_ptr = *r147_;\
	*r147_ = x147_;\
    }

#define POP_exp(A, B)\
    {\
	c_class **r148_ = &(B);\
	c_class *x148_ = CHECK_NULL(*r148_);\
	(A) = DEREF_exp(x148_ + 1);\
	*r148_ = x148_->ag_ptr;\
	destroy_c_class(x148_, (unsigned)2);\
    }


/* Definitions for union OFFSET */

#define ORDER_off			((unsigned) 13)
#define SIZE_off			1
#define NULL_off			((OFFSET) 0)
#define IS_NULL_off(A)			((A) == 0)
#define EQ_off(A, B)			((A) == (B))

#define COPY_off(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_off(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_off(A, B, C)\
    {\
	c_class *x149_ = GEN_c_class(2, TYPEID_list);\
	COPY_off(x149_ + 1, (A));\
	x149_->ag_ptr = (B);\
	(C) = x149_;\
    }

#define UN_CONS_off(A, B, C)\
    {\
	c_class *x150_ = CHECK_NULL(C);\
	(A) = DEREF_off(x150_ + 1);\
	(B) = x150_->ag_ptr;\
    }

#define DESTROY_CONS_off(D, A, B, C)\
    {\
	c_class *x151_ = CHECK_NULL(C);\
	(A) = DEREF_off(x151_ + 1);\
	(B) = x151_->ag_ptr;\
	(D)(x151_, (unsigned)2);\
    }

#define PUSH_off(A, B)\
    {\
	c_class **r152_ = &(B);\
	c_class *x152_ = GEN_c_class(2, TYPEID_stack);\
	COPY_off(x152_ + 1, (A));\
	x152_->ag_ptr = *r152_;\
	*r152_ = x152_;\
    }

#define POP_off(A, B)\
    {\
	c_class **r153_ = &(B);\
	c_class *x153_ = CHECK_NULL(*r153_);\
	(A) = DEREF_off(x153_ + 1);\
	*r153_ = x153_->ag_ptr;\
	destroy_c_class(x153_, (unsigned)2);\
    }


/* Definitions for union TOKEN */

#define ORDER_tok			((unsigned) 10)
#define SIZE_tok			1
#define NULL_tok			((TOKEN) 0)
#define IS_NULL_tok(A)			((A) == 0)
#define EQ_tok(A, B)			((A) == (B))

#define COPY_tok(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_tok(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_tok(A, B, C)\
    {\
	c_class *x154_ = GEN_c_class(2, TYPEID_list);\
	COPY_tok(x154_ + 1, (A));\
	x154_->ag_ptr = (B);\
	(C) = x154_;\
    }

#define UN_CONS_tok(A, B, C)\
    {\
	c_class *x155_ = CHECK_NULL(C);\
	(A) = DEREF_tok(x155_ + 1);\
	(B) = x155_->ag_ptr;\
    }

#define DESTROY_CONS_tok(D, A, B, C)\
    {\
	c_class *x156_ = CHECK_NULL(C);\
	(A) = DEREF_tok(x156_ + 1);\
	(B) = x156_->ag_ptr;\
	(D)(x156_, (unsigned)2);\
    }

#define PUSH_tok(A, B)\
    {\
	c_class **r157_ = &(B);\
	c_class *x157_ = GEN_c_class(2, TYPEID_stack);\
	COPY_tok(x157_ + 1, (A));\
	x157_->ag_ptr = *r157_;\
	*r157_ = x157_;\
    }

#define POP_tok(A, B)\
    {\
	c_class **r158_ = &(B);\
	c_class *x158_ = CHECK_NULL(*r158_);\
	(A) = DEREF_tok(x158_ + 1);\
	*r158_ = x158_->ag_ptr;\
	destroy_c_class(x158_, (unsigned)2);\
    }


/* Definitions for union INSTANCE */

#define ORDER_inst			((unsigned) 2)
#define SIZE_inst			1
#define NULL_inst			((INSTANCE) 0)
#define IS_NULL_inst(A)			((A) == 0)
#define EQ_inst(A, B)			((A) == (B))

#define COPY_inst(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_inst(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_inst(A, B, C)\
    {\
	c_class *x159_ = GEN_c_class(2, TYPEID_list);\
	COPY_inst(x159_ + 1, (A));\
	x159_->ag_ptr = (B);\
	(C) = x159_;\
    }

#define UN_CONS_inst(A, B, C)\
    {\
	c_class *x160_ = CHECK_NULL(C);\
	(A) = DEREF_inst(x160_ + 1);\
	(B) = x160_->ag_ptr;\
    }

#define DESTROY_CONS_inst(D, A, B, C)\
    {\
	c_class *x161_ = CHECK_NULL(C);\
	(A) = DEREF_inst(x161_ + 1);\
	(B) = x161_->ag_ptr;\
	(D)(x161_, (unsigned)2);\
    }

#define PUSH_inst(A, B)\
    {\
	c_class **r162_ = &(B);\
	c_class *x162_ = GEN_c_class(2, TYPEID_stack);\
	COPY_inst(x162_ + 1, (A));\
	x162_->ag_ptr = *r162_;\
	*r162_ = x162_;\
    }

#define POP_inst(A, B)\
    {\
	c_class **r163_ = &(B);\
	c_class *x163_ = CHECK_NULL(*r163_);\
	(A) = DEREF_inst(x163_ + 1);\
	*r163_ = x163_->ag_ptr;\
	destroy_c_class(x163_, (unsigned)2);\
    }


/* Definitions for union ERROR */

#define ORDER_err			((unsigned) 2)
#define SIZE_err			1
#define NULL_err			((ERROR) 0)
#define IS_NULL_err(A)			((A) == 0)
#define EQ_err(A, B)			((A) == (B))

#define COPY_err(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_err(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_err(A, B, C)\
    {\
	c_class *x164_ = GEN_c_class(2, TYPEID_list);\
	COPY_err(x164_ + 1, (A));\
	x164_->ag_ptr = (B);\
	(C) = x164_;\
    }

#define UN_CONS_err(A, B, C)\
    {\
	c_class *x165_ = CHECK_NULL(C);\
	(A) = DEREF_err(x165_ + 1);\
	(B) = x165_->ag_ptr;\
    }

#define DESTROY_CONS_err(D, A, B, C)\
    {\
	c_class *x166_ = CHECK_NULL(C);\
	(A) = DEREF_err(x166_ + 1);\
	(B) = x166_->ag_ptr;\
	(D)(x166_, (unsigned)2);\
    }

#define PUSH_err(A, B)\
    {\
	c_class **r167_ = &(B);\
	c_class *x167_ = GEN_c_class(2, TYPEID_stack);\
	COPY_err(x167_ + 1, (A));\
	x167_->ag_ptr = *r167_;\
	*r167_ = x167_;\
    }

#define POP_err(A, B)\
    {\
	c_class **r168_ = &(B);\
	c_class *x168_ = CHECK_NULL(*r168_);\
	(A) = DEREF_err(x168_ + 1);\
	*r168_ = x168_->ag_ptr;\
	destroy_c_class(x168_, (unsigned)2);\
    }


/* Maximum allocation size */

#define c_class_GEN_MAX			19

#endif
