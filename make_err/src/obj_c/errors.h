/* $Id$ */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#ifndef errors_NAME
#define errors_NAME			"errors"
#define errors_VERSION			"1.0"
#define errors_SPECIFICATION		0
#define errors_IMPLEMENTATION		1
#endif


/* Prototype macros */



/* Primitive types */

typedef char * string;


/* Basic types */

typedef union errors_tag {
    unsigned ag_tag;
    union errors_tag *ag_ptr;
    unsigned ag_enum;
    unsigned long ag_long_enum;
    int ag_prim_int;
    string ag_prim_string;
} errors;

typedef errors *errors_PTR;

#ifndef errors_DESTR_DEFINED
#define errors_DESTR_DEFINED
typedef void (*DESTROYER)(errors *, unsigned);
#endif

#define PTR(A)	errors_PTR
#define LIST(A)	errors_PTR
#define STACK(A)	errors_PTR
#define SIZE(A)	int


/* Assertion macros */

#ifndef NDEBUG
extern errors *check_null_errors(errors *, char *, int);
extern errors *check_tag_errors(errors *, unsigned, char *, int);
extern errors *check_tag_etc_errors(errors *, unsigned, unsigned, char *, int);
#define CHECK_NULL(P)\
    (check_null_errors((P), __FILE__, __LINE__))
#define CHECK_TAG(P, N)\
    (check_tag_errors((P), (unsigned)(N), __FILE__, __LINE__))
#define CHECK_TAG_ETC(P, L, U)\
    (check_tag_etc_errors((P), (unsigned)(L), (unsigned)(U), __FILE__, __LINE__))
#else
#define CHECK_NULL(P)			(P)
#define CHECK_TAG(P, N)			(P)
#define CHECK_TAG_ETC(P, L, U)		(P)
#endif


/* Enumeration definitions */



/* Union type definitions */

typedef errors *NAME;
typedef errors *MESSAGE;
typedef errors *MAP;
typedef errors *PARAM;
typedef errors *ENTRY;


/* Structure declarations */



/* Identity type definitions */

typedef NAME KEY;
typedef NAME PROPERTY;
typedef NAME TYPE;
typedef NAME USAGE;


/* Structure definitions */

#ifndef errors_STRUCT_DEFINED
#define errors_STRUCT_DEFINED

#endif /* errors_STRUCT_DEFINED */


/* Function declarations */

extern errors *gen_errors(unsigned);
extern void destroy_errors(errors *, unsigned);
extern void dummy_destroy_errors (errors *, unsigned);
extern void destroy_errors_list (errors *, unsigned);
extern errors *append_errors_list(errors *, errors *);
extern errors *end_errors_list(errors *);
extern unsigned length_errors_list(errors *);
extern errors *reverse_errors_list(errors *);
#ifdef errors_IO_ROUTINES
extern unsigned crt_errors_alias;
extern void set_errors_alias(errors *, unsigned);
extern errors *find_errors_alias(unsigned);
extern void clear_errors_alias(void);
#endif


/* Run-time type information */

#ifndef GEN_errors
#define GEN_errors(A, B)		gen_errors((unsigned)(A))
#endif
#define TYPEID_ptr			((unsigned)0)
#define TYPEID_list			((unsigned)1)
#define TYPEID_stack			((unsigned)2)
#define TYPEID_name			((unsigned)3)
#define TYPEID_msg			((unsigned)4)
#define TYPEID_map			((unsigned)5)
#define TYPEID_param			((unsigned)6)
#define TYPEID_entry			((unsigned)7)


/* Definitions for pointers */

#define STEP_ptr(A, B)			(CHECK_NULL(A) + B)
#define SIZE_ptr(A)			1
#define NULL_ptr(A)			((errors *)0)
#define IS_NULL_ptr(A)			((A) == 0)
#define EQ_ptr(A, B)			((A) == (B))
#define MAKE_ptr(A)			GEN_errors((A), TYPEID_ptr)
#define DESTROY_ptr(A, B)		destroy_errors((A), (unsigned)(B))
#define UNIQ_ptr(A)			GEN_errors(1, TYPEID_ptr)
#define DESTROY_UNIQ_ptr(A)		destroy_errors((A), (unsigned)1)
#ifdef errors_IO_ROUTINES
#define VOIDSTAR_ptr(A)			((void *)(A))
#endif

#define COPY_ptr(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_ptr(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_ptr(A, B, C)\
    {\
	errors *x0_ = GEN_errors(2, TYPEID_list);\
	x0_[1].ag_ptr = (A);\
	x0_->ag_ptr = (B);\
	(C) = x0_;\
    }

#define UN_CONS_ptr(A, B, C)\
    {\
	errors *x1_ = CHECK_NULL(C);\
	(A) = x1_[1].ag_ptr;\
	(B) = x1_->ag_ptr;\
    }

#define DESTROY_CONS_ptr(D, A, B, C)\
    {\
	errors *x2_ = CHECK_NULL(C);\
	(A) = x2_[1].ag_ptr;\
	(B) = x2_->ag_ptr;\
	(D)(x2_, (unsigned)2);\
    }

#define PUSH_ptr(A, B)\
    {\
	errors **r3_ = &(B);\
	errors *x3_ = GEN_errors(2, TYPEID_stack);\
	x3_[1].ag_ptr = (A);\
	x3_->ag_ptr = *r3_;\
	*r3_ = x3_;\
    }

#define POP_ptr(A, B)\
    {\
	errors **r4_ = &(B);\
	errors *x4_ = CHECK_NULL(*r4_);\
	(A) = x4_[1].ag_ptr;\
	*r4_ = x4_->ag_ptr;\
	destroy_errors(x4_, (unsigned)2);\
    }


/* Definitions for lists */

#define HEAD_list(A)			(CHECK_NULL(A) + 1)
#define PTR_TAIL_list(A)		(CHECK_NULL(A))
#define TAIL_list(A)			(CHECK_NULL(A)->ag_ptr)
#define LENGTH_list(A)			length_errors_list((A))
#define END_list(A)			end_errors_list((A))
#define REVERSE_list(A)			reverse_errors_list((A))
#define APPEND_list(A, B)		append_errors_list((A), (B))

#define SIZE_list(A)			1
#define NULL_list(A)			((errors *) 0)
#define IS_NULL_list(A)			((A) == 0)
#define EQ_list(A, B)			((A) == (B))
#define UNIQ_list(A)			GEN_errors(1, TYPEID_list)
#define DESTROY_UNIQ_list(A)		destroy_errors((A), (unsigned)1)
#ifdef errors_IO_ROUTINES
#define VOIDSTAR_list(A)		((void *)(A))
#endif

#define DESTROY_list(A, B)\
    {\
	destroy_errors_list((A), (unsigned)(B));\
    }

#define COPY_list(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_list(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_list(A, B, C)\
    {\
	errors *x5_ = GEN_errors(2, TYPEID_list);\
	x5_[1].ag_ptr = (A);\
	x5_->ag_ptr = (B);\
	(C) = x5_;\
    }

#define UN_CONS_list(A, B, C)\
    {\
	errors *x6_ = CHECK_NULL(C);\
	(A) = x6_[1].ag_ptr;\
	(B) = x6_->ag_ptr;\
    }

#define DESTROY_CONS_list(D, A, B, C)\
    {\
	errors *x7_ = CHECK_NULL(C);\
	(A) = x7_[1].ag_ptr;\
	(B) = x7_->ag_ptr;\
	(D)(x7_, (unsigned)2);\
    }

#define PUSH_list(A, B)\
    {\
	errors **r8_ = &(B);\
	errors *x8_ = GEN_errors(2, TYPEID_stack);\
	x8_[1].ag_ptr = (A);\
	x8_->ag_ptr = *r8_;\
	*r8_ = x8_;\
    }

#define POP_list(A, B)\
    {\
	errors **r9_ = &(B);\
	errors *x9_ = CHECK_NULL(*r9_);\
	(A) = x9_[1].ag_ptr;\
	*r9_ = x9_->ag_ptr;\
	destroy_errors(x9_, (unsigned)2);\
    }


/* Definitions for stacks */

#define SIZE_stack(A)			1
#define NULL_stack(A)			((errors *) 0)
#define IS_NULL_stack(A)		((A) == 0)
#define STACK_list(A)			(A)
#define LIST_stack(A)			(A)

#define COPY_stack(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_stack(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_stack(A, B, C)\
    {\
	errors *x10_ = GEN_errors(2, TYPEID_list);\
	x10_[1].ag_ptr = (A);\
	x10_->ag_ptr = (B);\
	(C) = x10_;\
    }

#define UN_CONS_stack(A, B, C)\
    {\
	errors *x11_ = CHECK_NULL(C);\
	(A) = x11_[1].ag_ptr;\
	(B) = x11_->ag_ptr;\
    }

#define DESTROY_CONS_stack(D, A, B, C)\
    {\
	errors *x12_ = CHECK_NULL(C);\
	(A) = x12_[1].ag_ptr;\
	(B) = x12_->ag_ptr;\
	(D)(x12_, (unsigned)2);\
    }

#define PUSH_stack(A, B)\
    {\
	errors **r13_ = &(B);\
	errors *x13_ = GEN_errors(2, TYPEID_stack);\
	x13_[1].ag_ptr = (A);\
	x13_->ag_ptr = *r13_;\
	*r13_ = x13_;\
    }

#define POP_stack(A, B)\
    {\
	errors **r14_ = &(B);\
	errors *x14_ = CHECK_NULL(*r14_);\
	(A) = x14_[1].ag_ptr;\
	*r14_ = x14_->ag_ptr;\
	destroy_errors(x14_, (unsigned)2);\
    }


/* Definitions for sizes */

#define SCALE(A, B)			((A)*(int)(B))


/* Definitions for primitive int */

#define SIZE_int			1

#define COPY_int(A, B)			(CHECK_NULL(A)->ag_prim_int = (B))
#define DEREF_int(A)			(CHECK_NULL(A)->ag_prim_int)
#define CONS_int(A, B, C)\
    {\
	errors *x15_ = GEN_errors(2, TYPEID_list);\
	COPY_int(x15_ + 1, (A));\
	x15_->ag_ptr = (B);\
	(C) = x15_;\
    }

#define UN_CONS_int(A, B, C)\
    {\
	errors *x16_ = CHECK_NULL(C);\
	(A) = DEREF_int(x16_ + 1);\
	(B) = x16_->ag_ptr;\
    }

#define DESTROY_CONS_int(D, A, B, C)\
    {\
	errors *x17_ = CHECK_NULL(C);\
	(A) = DEREF_int(x17_ + 1);\
	(B) = x17_->ag_ptr;\
	(D)(x17_, (unsigned)2);\
    }

#define PUSH_int(A, B)\
    {\
	errors **r18_ = &(B);\
	errors *x18_ = GEN_errors(2, TYPEID_stack);\
	COPY_int(x18_ + 1, (A));\
	x18_->ag_ptr = *r18_;\
	*r18_ = x18_;\
    }

#define POP_int(A, B)\
    {\
	errors **r19_ = &(B);\
	errors *x19_ = CHECK_NULL(*r19_);\
	(A) = DEREF_int(x19_ + 1);\
	*r19_ = x19_->ag_ptr;\
	destroy_errors(x19_, (unsigned)2);\
    }


/* Definitions for primitive string */

#define SIZE_string			1

#define COPY_string(A, B)		(CHECK_NULL(A)->ag_prim_string = (B))
#define DEREF_string(A)			(CHECK_NULL(A)->ag_prim_string)
#define CONS_string(A, B, C)\
    {\
	errors *x20_ = GEN_errors(2, TYPEID_list);\
	COPY_string(x20_ + 1, (A));\
	x20_->ag_ptr = (B);\
	(C) = x20_;\
    }

#define UN_CONS_string(A, B, C)\
    {\
	errors *x21_ = CHECK_NULL(C);\
	(A) = DEREF_string(x21_ + 1);\
	(B) = x21_->ag_ptr;\
    }

#define DESTROY_CONS_string(D, A, B, C)\
    {\
	errors *x22_ = CHECK_NULL(C);\
	(A) = DEREF_string(x22_ + 1);\
	(B) = x22_->ag_ptr;\
	(D)(x22_, (unsigned)2);\
    }

#define PUSH_string(A, B)\
    {\
	errors **r23_ = &(B);\
	errors *x23_ = GEN_errors(2, TYPEID_stack);\
	COPY_string(x23_ + 1, (A));\
	x23_->ag_ptr = *r23_;\
	*r23_ = x23_;\
    }

#define POP_string(A, B)\
    {\
	errors **r24_ = &(B);\
	errors *x24_ = CHECK_NULL(*r24_);\
	(A) = DEREF_string(x24_ + 1);\
	*r24_ = x24_->ag_ptr;\
	destroy_errors(x24_, (unsigned)2);\
    }


/* Definitions for union NAME */

#define ORDER_name			((unsigned) 1)
#define SIZE_name			1
#define NULL_name			((NAME) 0)
#define IS_NULL_name(A)			((A) == 0)
#define EQ_name(A, B)			((A) == (B))

#define COPY_name(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_name(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_name(A, B, C)\
    {\
	errors *x25_ = GEN_errors(2, TYPEID_list);\
	COPY_name(x25_ + 1, (A));\
	x25_->ag_ptr = (B);\
	(C) = x25_;\
    }

#define UN_CONS_name(A, B, C)\
    {\
	errors *x26_ = CHECK_NULL(C);\
	(A) = DEREF_name(x26_ + 1);\
	(B) = x26_->ag_ptr;\
    }

#define DESTROY_CONS_name(D, A, B, C)\
    {\
	errors *x27_ = CHECK_NULL(C);\
	(A) = DEREF_name(x27_ + 1);\
	(B) = x27_->ag_ptr;\
	(D)(x27_, (unsigned)2);\
    }

#define PUSH_name(A, B)\
    {\
	errors **r28_ = &(B);\
	errors *x28_ = GEN_errors(2, TYPEID_stack);\
	COPY_name(x28_ + 1, (A));\
	x28_->ag_ptr = *r28_;\
	*r28_ = x28_;\
    }

#define POP_name(A, B)\
    {\
	errors **r29_ = &(B);\
	errors *x29_ = CHECK_NULL(*r29_);\
	(A) = DEREF_name(x29_ + 1);\
	*r29_ = x29_->ag_ptr;\
	destroy_errors(x29_, (unsigned)2);\
    }


/* Definitions for union MESSAGE */

#define ORDER_msg			((unsigned) 2)
#define SIZE_msg			1
#define NULL_msg			((MESSAGE) 0)
#define IS_NULL_msg(A)			((A) == 0)
#define EQ_msg(A, B)			((A) == (B))

#define COPY_msg(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_msg(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_msg(A, B, C)\
    {\
	errors *x30_ = GEN_errors(2, TYPEID_list);\
	COPY_msg(x30_ + 1, (A));\
	x30_->ag_ptr = (B);\
	(C) = x30_;\
    }

#define UN_CONS_msg(A, B, C)\
    {\
	errors *x31_ = CHECK_NULL(C);\
	(A) = DEREF_msg(x31_ + 1);\
	(B) = x31_->ag_ptr;\
    }

#define DESTROY_CONS_msg(D, A, B, C)\
    {\
	errors *x32_ = CHECK_NULL(C);\
	(A) = DEREF_msg(x32_ + 1);\
	(B) = x32_->ag_ptr;\
	(D)(x32_, (unsigned)2);\
    }

#define PUSH_msg(A, B)\
    {\
	errors **r33_ = &(B);\
	errors *x33_ = GEN_errors(2, TYPEID_stack);\
	COPY_msg(x33_ + 1, (A));\
	x33_->ag_ptr = *r33_;\
	*r33_ = x33_;\
    }

#define POP_msg(A, B)\
    {\
	errors **r34_ = &(B);\
	errors *x34_ = CHECK_NULL(*r34_);\
	(A) = DEREF_msg(x34_ + 1);\
	*r34_ = x34_->ag_ptr;\
	destroy_errors(x34_, (unsigned)2);\
    }


/* Definitions for union MAP */

#define ORDER_map			((unsigned) 1)
#define SIZE_map			1
#define NULL_map			((MAP) 0)
#define IS_NULL_map(A)			((A) == 0)
#define EQ_map(A, B)			((A) == (B))

#define COPY_map(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_map(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_map(A, B, C)\
    {\
	errors *x35_ = GEN_errors(2, TYPEID_list);\
	COPY_map(x35_ + 1, (A));\
	x35_->ag_ptr = (B);\
	(C) = x35_;\
    }

#define UN_CONS_map(A, B, C)\
    {\
	errors *x36_ = CHECK_NULL(C);\
	(A) = DEREF_map(x36_ + 1);\
	(B) = x36_->ag_ptr;\
    }

#define DESTROY_CONS_map(D, A, B, C)\
    {\
	errors *x37_ = CHECK_NULL(C);\
	(A) = DEREF_map(x37_ + 1);\
	(B) = x37_->ag_ptr;\
	(D)(x37_, (unsigned)2);\
    }

#define PUSH_map(A, B)\
    {\
	errors **r38_ = &(B);\
	errors *x38_ = GEN_errors(2, TYPEID_stack);\
	COPY_map(x38_ + 1, (A));\
	x38_->ag_ptr = *r38_;\
	*r38_ = x38_;\
    }

#define POP_map(A, B)\
    {\
	errors **r39_ = &(B);\
	errors *x39_ = CHECK_NULL(*r39_);\
	(A) = DEREF_map(x39_ + 1);\
	*r39_ = x39_->ag_ptr;\
	destroy_errors(x39_, (unsigned)2);\
    }


/* Definitions for union PARAM */

#define ORDER_param			((unsigned) 1)
#define SIZE_param			1
#define NULL_param			((PARAM) 0)
#define IS_NULL_param(A)		((A) == 0)
#define EQ_param(A, B)			((A) == (B))

#define COPY_param(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_param(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_param(A, B, C)\
    {\
	errors *x40_ = GEN_errors(2, TYPEID_list);\
	COPY_param(x40_ + 1, (A));\
	x40_->ag_ptr = (B);\
	(C) = x40_;\
    }

#define UN_CONS_param(A, B, C)\
    {\
	errors *x41_ = CHECK_NULL(C);\
	(A) = DEREF_param(x41_ + 1);\
	(B) = x41_->ag_ptr;\
    }

#define DESTROY_CONS_param(D, A, B, C)\
    {\
	errors *x42_ = CHECK_NULL(C);\
	(A) = DEREF_param(x42_ + 1);\
	(B) = x42_->ag_ptr;\
	(D)(x42_, (unsigned)2);\
    }

#define PUSH_param(A, B)\
    {\
	errors **r43_ = &(B);\
	errors *x43_ = GEN_errors(2, TYPEID_stack);\
	COPY_param(x43_ + 1, (A));\
	x43_->ag_ptr = *r43_;\
	*r43_ = x43_;\
    }

#define POP_param(A, B)\
    {\
	errors **r44_ = &(B);\
	errors *x44_ = CHECK_NULL(*r44_);\
	(A) = DEREF_param(x44_ + 1);\
	*r44_ = x44_->ag_ptr;\
	destroy_errors(x44_, (unsigned)2);\
    }


/* Definitions for union ENTRY */

#define ORDER_entry			((unsigned) 1)
#define SIZE_entry			1
#define NULL_entry			((ENTRY) 0)
#define IS_NULL_entry(A)		((A) == 0)
#define EQ_entry(A, B)			((A) == (B))

#define COPY_entry(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_entry(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_entry(A, B, C)\
    {\
	errors *x45_ = GEN_errors(2, TYPEID_list);\
	COPY_entry(x45_ + 1, (A));\
	x45_->ag_ptr = (B);\
	(C) = x45_;\
    }

#define UN_CONS_entry(A, B, C)\
    {\
	errors *x46_ = CHECK_NULL(C);\
	(A) = DEREF_entry(x46_ + 1);\
	(B) = x46_->ag_ptr;\
    }

#define DESTROY_CONS_entry(D, A, B, C)\
    {\
	errors *x47_ = CHECK_NULL(C);\
	(A) = DEREF_entry(x47_ + 1);\
	(B) = x47_->ag_ptr;\
	(D)(x47_, (unsigned)2);\
    }

#define PUSH_entry(A, B)\
    {\
	errors **r48_ = &(B);\
	errors *x48_ = GEN_errors(2, TYPEID_stack);\
	COPY_entry(x48_ + 1, (A));\
	x48_->ag_ptr = *r48_;\
	*r48_ = x48_;\
    }

#define POP_entry(A, B)\
    {\
	errors **r49_ = &(B);\
	errors *x49_ = CHECK_NULL(*r49_);\
	(A) = DEREF_entry(x49_ + 1);\
	*r49_ = x49_->ag_ptr;\
	destroy_errors(x49_, (unsigned)2);\
    }


/* Maximum allocation size */

#define errors_GEN_MAX			8

#endif
