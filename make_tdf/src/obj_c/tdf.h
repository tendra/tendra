/* $Id$ */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef TDF_H_INCLUDED
#define TDF_H_INCLUDED

#ifndef tdf_NAME
#define tdf_NAME			"tdf"
#define tdf_VERSION			"1.0"
#define tdf_SPECIFICATION		0
#define tdf_IMPLEMENTATION		1
#endif


/* Prototype macros */



/* Primitive types */

typedef char * string;


/* Basic types */

typedef union tdf_tag {
    unsigned ag_tag;
    union tdf_tag *ag_ptr;
    unsigned ag_enum;
    unsigned long ag_long_enum;
    int ag_prim_int;
    unsigned ag_prim_unsigned;
    string ag_prim_string;
} tdf;

typedef tdf *tdf_PTR;

#ifndef tdf_DESTR_DEFINED
#define tdf_DESTR_DEFINED
typedef void (*DESTROYER)(tdf *, unsigned);
#endif

#define PTR(A)	tdf_PTR
#define LIST(A)	tdf_PTR
#define STACK(A)	tdf_PTR
#define SIZE(A)	int


/* Assertion macros */

#ifndef NDEBUG
extern tdf *check_null_tdf(tdf *, char *, int);
extern tdf *check_tag_tdf(tdf *, unsigned, char *, int);
extern tdf *check_tag_etc_tdf(tdf *, unsigned, unsigned, char *, int);
#define CHECK_NULL(P)\
    (check_null_tdf((P), __FILE__, __LINE__))
#define CHECK_TAG(P, N)\
    (check_tag_tdf((P), (unsigned)(N), __FILE__, __LINE__))
#define CHECK_TAG_ETC(P, L, U)\
    (check_tag_etc_tdf((P), (unsigned)(L), (unsigned)(U), __FILE__, __LINE__))
#else
#define CHECK_NULL(P)			(P)
#define CHECK_TAG(P, N)			(P)
#define CHECK_TAG_ETC(P, L, U)		(P)
#endif


/* Enumeration definitions */



/* Union type definitions */

typedef tdf *PARAMETER;
typedef tdf *CONSTRUCT;
typedef tdf *SORT_INFO;
typedef tdf *SORT;
typedef tdf *LINKAGE;
typedef tdf *SPECIFICATION;
typedef tdf *COMMAND;


/* Structure declarations */



/* Identity type definitions */



/* Structure definitions */

#ifndef tdf_STRUCT_DEFINED
#define tdf_STRUCT_DEFINED

#endif /* tdf_STRUCT_DEFINED */


/* Function declarations */

extern tdf *gen_tdf(unsigned);
extern void destroy_tdf(tdf *, unsigned);
extern void dummy_destroy_tdf (tdf *, unsigned);
extern void destroy_tdf_list (tdf *, unsigned);
extern tdf *append_tdf_list(tdf *, tdf *);
extern tdf *end_tdf_list(tdf *);
extern unsigned length_tdf_list(tdf *);
extern tdf *reverse_tdf_list(tdf *);
#ifdef tdf_IO_ROUTINES
extern unsigned crt_tdf_alias;
extern void set_tdf_alias(tdf *, unsigned);
extern tdf *find_tdf_alias(unsigned);
extern void clear_tdf_alias(void);
#endif


/* Run-time type information */

#ifndef GEN_tdf
#define GEN_tdf(A, B)			gen_tdf((unsigned)(A))
#endif
#define TYPEID_ptr			((unsigned)0)
#define TYPEID_list			((unsigned)1)
#define TYPEID_stack			((unsigned)2)
#define TYPEID_par			((unsigned)3)
#define TYPEID_cons			((unsigned)4)
#define TYPEID_info			((unsigned)5)
#define TYPEID_sort			((unsigned)6)
#define TYPEID_link			((unsigned)7)
#define TYPEID_spec			((unsigned)8)
#define TYPEID_cmd			((unsigned)9)


/* Definitions for pointers */

#define STEP_ptr(A, B)			(CHECK_NULL(A) + B)
#define SIZE_ptr(A)			1
#define NULL_ptr(A)			((tdf *)0)
#define IS_NULL_ptr(A)			((A) == 0)
#define EQ_ptr(A, B)			((A) == (B))
#define MAKE_ptr(A)			GEN_tdf((A), TYPEID_ptr)
#define DESTROY_ptr(A, B)		destroy_tdf((A), (unsigned)(B))
#define UNIQ_ptr(A)			GEN_tdf(1, TYPEID_ptr)
#define DESTROY_UNIQ_ptr(A)		destroy_tdf((A), (unsigned)1)
#ifdef tdf_IO_ROUTINES
#define VOIDSTAR_ptr(A)			((void *)(A))
#endif

#define COPY_ptr(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_ptr(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_ptr(A, B, C)\
    {\
	tdf *x0_ = GEN_tdf(2, TYPEID_list);\
	x0_[1].ag_ptr = (A);\
	x0_->ag_ptr = (B);\
	(C) = x0_;\
    }

#define UN_CONS_ptr(A, B, C)\
    {\
	tdf *x1_ = CHECK_NULL(C);\
	(A) = x1_[1].ag_ptr;\
	(B) = x1_->ag_ptr;\
    }

#define DESTROY_CONS_ptr(D, A, B, C)\
    {\
	tdf *x2_ = CHECK_NULL(C);\
	(A) = x2_[1].ag_ptr;\
	(B) = x2_->ag_ptr;\
	(D)(x2_, (unsigned)2);\
    }

#define PUSH_ptr(A, B)\
    {\
	tdf **r3_ = &(B);\
	tdf *x3_ = GEN_tdf(2, TYPEID_stack);\
	x3_[1].ag_ptr = (A);\
	x3_->ag_ptr = *r3_;\
	*r3_ = x3_;\
    }

#define POP_ptr(A, B)\
    {\
	tdf **r4_ = &(B);\
	tdf *x4_ = CHECK_NULL(*r4_);\
	(A) = x4_[1].ag_ptr;\
	*r4_ = x4_->ag_ptr;\
	destroy_tdf(x4_, (unsigned)2);\
    }


/* Definitions for lists */

#define HEAD_list(A)			(CHECK_NULL(A) + 1)
#define PTR_TAIL_list(A)		(CHECK_NULL(A))
#define TAIL_list(A)			(CHECK_NULL(A)->ag_ptr)
#define LENGTH_list(A)			length_tdf_list((A))
#define END_list(A)			end_tdf_list((A))
#define REVERSE_list(A)			reverse_tdf_list((A))
#define APPEND_list(A, B)		append_tdf_list((A), (B))

#define SIZE_list(A)			1
#define NULL_list(A)			((tdf *) 0)
#define IS_NULL_list(A)			((A) == 0)
#define EQ_list(A, B)			((A) == (B))
#define UNIQ_list(A)			GEN_tdf(1, TYPEID_list)
#define DESTROY_UNIQ_list(A)		destroy_tdf((A), (unsigned)1)
#ifdef tdf_IO_ROUTINES
#define VOIDSTAR_list(A)		((void *)(A))
#endif

#define DESTROY_list(A, B)\
    {\
	destroy_tdf_list((A), (unsigned)(B));\
    }

#define COPY_list(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_list(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_list(A, B, C)\
    {\
	tdf *x5_ = GEN_tdf(2, TYPEID_list);\
	x5_[1].ag_ptr = (A);\
	x5_->ag_ptr = (B);\
	(C) = x5_;\
    }

#define UN_CONS_list(A, B, C)\
    {\
	tdf *x6_ = CHECK_NULL(C);\
	(A) = x6_[1].ag_ptr;\
	(B) = x6_->ag_ptr;\
    }

#define DESTROY_CONS_list(D, A, B, C)\
    {\
	tdf *x7_ = CHECK_NULL(C);\
	(A) = x7_[1].ag_ptr;\
	(B) = x7_->ag_ptr;\
	(D)(x7_, (unsigned)2);\
    }

#define PUSH_list(A, B)\
    {\
	tdf **r8_ = &(B);\
	tdf *x8_ = GEN_tdf(2, TYPEID_stack);\
	x8_[1].ag_ptr = (A);\
	x8_->ag_ptr = *r8_;\
	*r8_ = x8_;\
    }

#define POP_list(A, B)\
    {\
	tdf **r9_ = &(B);\
	tdf *x9_ = CHECK_NULL(*r9_);\
	(A) = x9_[1].ag_ptr;\
	*r9_ = x9_->ag_ptr;\
	destroy_tdf(x9_, (unsigned)2);\
    }


/* Definitions for stacks */

#define SIZE_stack(A)			1
#define NULL_stack(A)			((tdf *) 0)
#define IS_NULL_stack(A)		((A) == 0)
#define STACK_list(A)			(A)
#define LIST_stack(A)			(A)

#define COPY_stack(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_stack(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_stack(A, B, C)\
    {\
	tdf *x10_ = GEN_tdf(2, TYPEID_list);\
	x10_[1].ag_ptr = (A);\
	x10_->ag_ptr = (B);\
	(C) = x10_;\
    }

#define UN_CONS_stack(A, B, C)\
    {\
	tdf *x11_ = CHECK_NULL(C);\
	(A) = x11_[1].ag_ptr;\
	(B) = x11_->ag_ptr;\
    }

#define DESTROY_CONS_stack(D, A, B, C)\
    {\
	tdf *x12_ = CHECK_NULL(C);\
	(A) = x12_[1].ag_ptr;\
	(B) = x12_->ag_ptr;\
	(D)(x12_, (unsigned)2);\
    }

#define PUSH_stack(A, B)\
    {\
	tdf **r13_ = &(B);\
	tdf *x13_ = GEN_tdf(2, TYPEID_stack);\
	x13_[1].ag_ptr = (A);\
	x13_->ag_ptr = *r13_;\
	*r13_ = x13_;\
    }

#define POP_stack(A, B)\
    {\
	tdf **r14_ = &(B);\
	tdf *x14_ = CHECK_NULL(*r14_);\
	(A) = x14_[1].ag_ptr;\
	*r14_ = x14_->ag_ptr;\
	destroy_tdf(x14_, (unsigned)2);\
    }


/* Definitions for sizes */

#define SCALE(A, B)			((A)*(int)(B))


/* Definitions for primitive int */

#define SIZE_int			1

#define COPY_int(A, B)			(CHECK_NULL(A)->ag_prim_int = (B))
#define DEREF_int(A)			(CHECK_NULL(A)->ag_prim_int)
#define CONS_int(A, B, C)\
    {\
	tdf *x15_ = GEN_tdf(2, TYPEID_list);\
	COPY_int(x15_ + 1, (A));\
	x15_->ag_ptr = (B);\
	(C) = x15_;\
    }

#define UN_CONS_int(A, B, C)\
    {\
	tdf *x16_ = CHECK_NULL(C);\
	(A) = DEREF_int(x16_ + 1);\
	(B) = x16_->ag_ptr;\
    }

#define DESTROY_CONS_int(D, A, B, C)\
    {\
	tdf *x17_ = CHECK_NULL(C);\
	(A) = DEREF_int(x17_ + 1);\
	(B) = x17_->ag_ptr;\
	(D)(x17_, (unsigned)2);\
    }

#define PUSH_int(A, B)\
    {\
	tdf **r18_ = &(B);\
	tdf *x18_ = GEN_tdf(2, TYPEID_stack);\
	COPY_int(x18_ + 1, (A));\
	x18_->ag_ptr = *r18_;\
	*r18_ = x18_;\
    }

#define POP_int(A, B)\
    {\
	tdf **r19_ = &(B);\
	tdf *x19_ = CHECK_NULL(*r19_);\
	(A) = DEREF_int(x19_ + 1);\
	*r19_ = x19_->ag_ptr;\
	destroy_tdf(x19_, (unsigned)2);\
    }


/* Definitions for primitive unsigned */

#define SIZE_unsigned			1

#define COPY_unsigned(A, B)		(CHECK_NULL(A)->ag_prim_unsigned = (B))
#define DEREF_unsigned(A)		(CHECK_NULL(A)->ag_prim_unsigned)
#define CONS_unsigned(A, B, C)\
    {\
	tdf *x20_ = GEN_tdf(2, TYPEID_list);\
	COPY_unsigned(x20_ + 1, (A));\
	x20_->ag_ptr = (B);\
	(C) = x20_;\
    }

#define UN_CONS_unsigned(A, B, C)\
    {\
	tdf *x21_ = CHECK_NULL(C);\
	(A) = DEREF_unsigned(x21_ + 1);\
	(B) = x21_->ag_ptr;\
    }

#define DESTROY_CONS_unsigned(D, A, B, C)\
    {\
	tdf *x22_ = CHECK_NULL(C);\
	(A) = DEREF_unsigned(x22_ + 1);\
	(B) = x22_->ag_ptr;\
	(D)(x22_, (unsigned)2);\
    }

#define PUSH_unsigned(A, B)\
    {\
	tdf **r23_ = &(B);\
	tdf *x23_ = GEN_tdf(2, TYPEID_stack);\
	COPY_unsigned(x23_ + 1, (A));\
	x23_->ag_ptr = *r23_;\
	*r23_ = x23_;\
    }

#define POP_unsigned(A, B)\
    {\
	tdf **r24_ = &(B);\
	tdf *x24_ = CHECK_NULL(*r24_);\
	(A) = DEREF_unsigned(x24_ + 1);\
	*r24_ = x24_->ag_ptr;\
	destroy_tdf(x24_, (unsigned)2);\
    }


/* Definitions for primitive string */

#define SIZE_string			1

#define COPY_string(A, B)		(CHECK_NULL(A)->ag_prim_string = (B))
#define DEREF_string(A)			(CHECK_NULL(A)->ag_prim_string)
#define CONS_string(A, B, C)\
    {\
	tdf *x25_ = GEN_tdf(2, TYPEID_list);\
	COPY_string(x25_ + 1, (A));\
	x25_->ag_ptr = (B);\
	(C) = x25_;\
    }

#define UN_CONS_string(A, B, C)\
    {\
	tdf *x26_ = CHECK_NULL(C);\
	(A) = DEREF_string(x26_ + 1);\
	(B) = x26_->ag_ptr;\
    }

#define DESTROY_CONS_string(D, A, B, C)\
    {\
	tdf *x27_ = CHECK_NULL(C);\
	(A) = DEREF_string(x27_ + 1);\
	(B) = x27_->ag_ptr;\
	(D)(x27_, (unsigned)2);\
    }

#define PUSH_string(A, B)\
    {\
	tdf **r28_ = &(B);\
	tdf *x28_ = GEN_tdf(2, TYPEID_stack);\
	COPY_string(x28_ + 1, (A));\
	x28_->ag_ptr = *r28_;\
	*r28_ = x28_;\
    }

#define POP_string(A, B)\
    {\
	tdf **r29_ = &(B);\
	tdf *x29_ = CHECK_NULL(*r29_);\
	(A) = DEREF_string(x29_ + 1);\
	*r29_ = x29_->ag_ptr;\
	destroy_tdf(x29_, (unsigned)2);\
    }


/* Definitions for union PARAMETER */

#define ORDER_par			((unsigned) 1)
#define SIZE_par			1
#define NULL_par			((PARAMETER) 0)
#define IS_NULL_par(A)			((A) == 0)
#define EQ_par(A, B)			((A) == (B))

#define COPY_par(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_par(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_par(A, B, C)\
    {\
	tdf *x30_ = GEN_tdf(2, TYPEID_list);\
	COPY_par(x30_ + 1, (A));\
	x30_->ag_ptr = (B);\
	(C) = x30_;\
    }

#define UN_CONS_par(A, B, C)\
    {\
	tdf *x31_ = CHECK_NULL(C);\
	(A) = DEREF_par(x31_ + 1);\
	(B) = x31_->ag_ptr;\
    }

#define DESTROY_CONS_par(D, A, B, C)\
    {\
	tdf *x32_ = CHECK_NULL(C);\
	(A) = DEREF_par(x32_ + 1);\
	(B) = x32_->ag_ptr;\
	(D)(x32_, (unsigned)2);\
    }

#define PUSH_par(A, B)\
    {\
	tdf **r33_ = &(B);\
	tdf *x33_ = GEN_tdf(2, TYPEID_stack);\
	COPY_par(x33_ + 1, (A));\
	x33_->ag_ptr = *r33_;\
	*r33_ = x33_;\
    }

#define POP_par(A, B)\
    {\
	tdf **r34_ = &(B);\
	tdf *x34_ = CHECK_NULL(*r34_);\
	(A) = DEREF_par(x34_ + 1);\
	*r34_ = x34_->ag_ptr;\
	destroy_tdf(x34_, (unsigned)2);\
    }


/* Definitions for union CONSTRUCT */

#define ORDER_cons			((unsigned) 1)
#define SIZE_cons			1
#define NULL_cons			((CONSTRUCT) 0)
#define IS_NULL_cons(A)			((A) == 0)
#define EQ_cons(A, B)			((A) == (B))

#define COPY_cons(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_cons(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_cons(A, B, C)\
    {\
	tdf *x35_ = GEN_tdf(2, TYPEID_list);\
	COPY_cons(x35_ + 1, (A));\
	x35_->ag_ptr = (B);\
	(C) = x35_;\
    }

#define UN_CONS_cons(A, B, C)\
    {\
	tdf *x36_ = CHECK_NULL(C);\
	(A) = DEREF_cons(x36_ + 1);\
	(B) = x36_->ag_ptr;\
    }

#define DESTROY_CONS_cons(D, A, B, C)\
    {\
	tdf *x37_ = CHECK_NULL(C);\
	(A) = DEREF_cons(x37_ + 1);\
	(B) = x37_->ag_ptr;\
	(D)(x37_, (unsigned)2);\
    }

#define PUSH_cons(A, B)\
    {\
	tdf **r38_ = &(B);\
	tdf *x38_ = GEN_tdf(2, TYPEID_stack);\
	COPY_cons(x38_ + 1, (A));\
	x38_->ag_ptr = *r38_;\
	*r38_ = x38_;\
    }

#define POP_cons(A, B)\
    {\
	tdf **r39_ = &(B);\
	tdf *x39_ = CHECK_NULL(*r39_);\
	(A) = DEREF_cons(x39_ + 1);\
	*r39_ = x39_->ag_ptr;\
	destroy_tdf(x39_, (unsigned)2);\
    }


/* Definitions for union SORT_INFO */

#define ORDER_info			((unsigned) 6)
#define SIZE_info			1
#define NULL_info			((SORT_INFO) 0)
#define IS_NULL_info(A)			((A) == 0)
#define EQ_info(A, B)			((A) == (B))

#define COPY_info(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_info(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_info(A, B, C)\
    {\
	tdf *x40_ = GEN_tdf(2, TYPEID_list);\
	COPY_info(x40_ + 1, (A));\
	x40_->ag_ptr = (B);\
	(C) = x40_;\
    }

#define UN_CONS_info(A, B, C)\
    {\
	tdf *x41_ = CHECK_NULL(C);\
	(A) = DEREF_info(x41_ + 1);\
	(B) = x41_->ag_ptr;\
    }

#define DESTROY_CONS_info(D, A, B, C)\
    {\
	tdf *x42_ = CHECK_NULL(C);\
	(A) = DEREF_info(x42_ + 1);\
	(B) = x42_->ag_ptr;\
	(D)(x42_, (unsigned)2);\
    }

#define PUSH_info(A, B)\
    {\
	tdf **r43_ = &(B);\
	tdf *x43_ = GEN_tdf(2, TYPEID_stack);\
	COPY_info(x43_ + 1, (A));\
	x43_->ag_ptr = *r43_;\
	*r43_ = x43_;\
    }

#define POP_info(A, B)\
    {\
	tdf **r44_ = &(B);\
	tdf *x44_ = CHECK_NULL(*r44_);\
	(A) = DEREF_info(x44_ + 1);\
	*r44_ = x44_->ag_ptr;\
	destroy_tdf(x44_, (unsigned)2);\
    }


/* Definitions for union SORT */

#define ORDER_sort			((unsigned) 1)
#define SIZE_sort			1
#define NULL_sort			((SORT) 0)
#define IS_NULL_sort(A)			((A) == 0)
#define EQ_sort(A, B)			((A) == (B))

#define COPY_sort(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_sort(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_sort(A, B, C)\
    {\
	tdf *x45_ = GEN_tdf(2, TYPEID_list);\
	COPY_sort(x45_ + 1, (A));\
	x45_->ag_ptr = (B);\
	(C) = x45_;\
    }

#define UN_CONS_sort(A, B, C)\
    {\
	tdf *x46_ = CHECK_NULL(C);\
	(A) = DEREF_sort(x46_ + 1);\
	(B) = x46_->ag_ptr;\
    }

#define DESTROY_CONS_sort(D, A, B, C)\
    {\
	tdf *x47_ = CHECK_NULL(C);\
	(A) = DEREF_sort(x47_ + 1);\
	(B) = x47_->ag_ptr;\
	(D)(x47_, (unsigned)2);\
    }

#define PUSH_sort(A, B)\
    {\
	tdf **r48_ = &(B);\
	tdf *x48_ = GEN_tdf(2, TYPEID_stack);\
	COPY_sort(x48_ + 1, (A));\
	x48_->ag_ptr = *r48_;\
	*r48_ = x48_;\
    }

#define POP_sort(A, B)\
    {\
	tdf **r49_ = &(B);\
	tdf *x49_ = CHECK_NULL(*r49_);\
	(A) = DEREF_sort(x49_ + 1);\
	*r49_ = x49_->ag_ptr;\
	destroy_tdf(x49_, (unsigned)2);\
    }


/* Definitions for union LINKAGE */

#define ORDER_link			((unsigned) 1)
#define SIZE_link			1
#define NULL_link			((LINKAGE) 0)
#define IS_NULL_link(A)			((A) == 0)
#define EQ_link(A, B)			((A) == (B))

#define COPY_link(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_link(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_link(A, B, C)\
    {\
	tdf *x50_ = GEN_tdf(2, TYPEID_list);\
	COPY_link(x50_ + 1, (A));\
	x50_->ag_ptr = (B);\
	(C) = x50_;\
    }

#define UN_CONS_link(A, B, C)\
    {\
	tdf *x51_ = CHECK_NULL(C);\
	(A) = DEREF_link(x51_ + 1);\
	(B) = x51_->ag_ptr;\
    }

#define DESTROY_CONS_link(D, A, B, C)\
    {\
	tdf *x52_ = CHECK_NULL(C);\
	(A) = DEREF_link(x52_ + 1);\
	(B) = x52_->ag_ptr;\
	(D)(x52_, (unsigned)2);\
    }

#define PUSH_link(A, B)\
    {\
	tdf **r53_ = &(B);\
	tdf *x53_ = GEN_tdf(2, TYPEID_stack);\
	COPY_link(x53_ + 1, (A));\
	x53_->ag_ptr = *r53_;\
	*r53_ = x53_;\
    }

#define POP_link(A, B)\
    {\
	tdf **r54_ = &(B);\
	tdf *x54_ = CHECK_NULL(*r54_);\
	(A) = DEREF_link(x54_ + 1);\
	*r54_ = x54_->ag_ptr;\
	destroy_tdf(x54_, (unsigned)2);\
    }


/* Definitions for union SPECIFICATION */

#define ORDER_spec			((unsigned) 1)
#define SIZE_spec			1
#define NULL_spec			((SPECIFICATION) 0)
#define IS_NULL_spec(A)			((A) == 0)
#define EQ_spec(A, B)			((A) == (B))

#define COPY_spec(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_spec(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_spec(A, B, C)\
    {\
	tdf *x55_ = GEN_tdf(2, TYPEID_list);\
	COPY_spec(x55_ + 1, (A));\
	x55_->ag_ptr = (B);\
	(C) = x55_;\
    }

#define UN_CONS_spec(A, B, C)\
    {\
	tdf *x56_ = CHECK_NULL(C);\
	(A) = DEREF_spec(x56_ + 1);\
	(B) = x56_->ag_ptr;\
    }

#define DESTROY_CONS_spec(D, A, B, C)\
    {\
	tdf *x57_ = CHECK_NULL(C);\
	(A) = DEREF_spec(x57_ + 1);\
	(B) = x57_->ag_ptr;\
	(D)(x57_, (unsigned)2);\
    }

#define PUSH_spec(A, B)\
    {\
	tdf **r58_ = &(B);\
	tdf *x58_ = GEN_tdf(2, TYPEID_stack);\
	COPY_spec(x58_ + 1, (A));\
	x58_->ag_ptr = *r58_;\
	*r58_ = x58_;\
    }

#define POP_spec(A, B)\
    {\
	tdf **r59_ = &(B);\
	tdf *x59_ = CHECK_NULL(*r59_);\
	(A) = DEREF_spec(x59_ + 1);\
	*r59_ = x59_->ag_ptr;\
	destroy_tdf(x59_, (unsigned)2);\
    }


/* Definitions for union COMMAND */

#define ORDER_cmd			((unsigned) 6)
#define SIZE_cmd			1
#define NULL_cmd			((COMMAND) 0)
#define IS_NULL_cmd(A)			((A) == 0)
#define EQ_cmd(A, B)			((A) == (B))

#define COPY_cmd(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_cmd(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_cmd(A, B, C)\
    {\
	tdf *x60_ = GEN_tdf(2, TYPEID_list);\
	COPY_cmd(x60_ + 1, (A));\
	x60_->ag_ptr = (B);\
	(C) = x60_;\
    }

#define UN_CONS_cmd(A, B, C)\
    {\
	tdf *x61_ = CHECK_NULL(C);\
	(A) = DEREF_cmd(x61_ + 1);\
	(B) = x61_->ag_ptr;\
    }

#define DESTROY_CONS_cmd(D, A, B, C)\
    {\
	tdf *x62_ = CHECK_NULL(C);\
	(A) = DEREF_cmd(x62_ + 1);\
	(B) = x62_->ag_ptr;\
	(D)(x62_, (unsigned)2);\
    }

#define PUSH_cmd(A, B)\
    {\
	tdf **r63_ = &(B);\
	tdf *x63_ = GEN_tdf(2, TYPEID_stack);\
	COPY_cmd(x63_ + 1, (A));\
	x63_->ag_ptr = *r63_;\
	*r63_ = x63_;\
    }

#define POP_cmd(A, B)\
    {\
	tdf **r64_ = &(B);\
	tdf *x64_ = CHECK_NULL(*r64_);\
	(A) = DEREF_cmd(x64_ + 1);\
	*r64_ = x64_->ag_ptr;\
	destroy_tdf(x64_, (unsigned)2);\
    }


/* Maximum allocation size */

#define tdf_GEN_MAX			10

#endif
