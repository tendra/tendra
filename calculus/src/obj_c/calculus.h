/*
    AUTOMATICALLY GENERATED FROM ALGEBRA calculus (VERSION 1.2)
    BY calculus (VERSION 1.3)
*/

#ifndef CALCULUS_H_INCLUDED
#define CALCULUS_H_INCLUDED

#ifndef calculus_NAME
#define calculus_NAME			"calculus"
#define calculus_VERSION		"1.2"
#define calculus_SPECIFICATION		0
#define calculus_IMPLEMENTATION		1
#endif


/* Prototype macros */



/* Primitive types */

typedef unsigned long number;
typedef char * string;


/* Basic types */

typedef union calculus_tag {
    unsigned ag_tag;
    union calculus_tag *ag_ptr;
    unsigned ag_enum;
    unsigned long ag_long_enum;
    int ag_prim_int;
    number ag_prim_number;
    string ag_prim_string;
} calculus;

typedef calculus *calculus_PTR;

#ifndef calculus_DESTR_DEFINED
#define calculus_DESTR_DEFINED
typedef void (*DESTROYER)(calculus *, unsigned);
#endif

#define PTR(A)	calculus_PTR
#define LIST(A)	calculus_PTR
#define STACK(A)	calculus_PTR
#define SIZE(A)	int


/* Assertion macros */

#ifndef NDEBUG
extern calculus *check_null_calculus(calculus *, char *, int);
extern calculus *check_tag_calculus(calculus *, unsigned, char *, int);
extern calculus *check_tag_etc_calculus(calculus *, unsigned, unsigned, char *, int);
#define CHECK_NULL(P)\
    (check_null_calculus((P), __FILE__, __LINE__))
#define CHECK_TAG(P, N)\
    (check_tag_calculus((P), (unsigned)(N), __FILE__, __LINE__))
#define CHECK_TAG_ETC(P, L, U)\
    (check_tag_etc_calculus((P), (unsigned)(L), (unsigned)(U), __FILE__, __LINE__))
#else
#define CHECK_NULL(P)			(P)
#define CHECK_TAG(P, N)			(P)
#define CHECK_TAG_ETC(P, L, U)		(P)
#endif


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

#define STEP_ptr(A, B)			(CHECK_NULL(A) + B)
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

#define COPY_ptr(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_ptr(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_ptr(A, B, C)\
    {\
	calculus *x0_ = GEN_calculus(2, TYPEID_list);\
	x0_[1].ag_ptr = (A);\
	x0_->ag_ptr = (B);\
	(C) = x0_;\
    }

#define UN_CONS_ptr(A, B, C)\
    {\
	calculus *x1_ = CHECK_NULL(C);\
	(A) = x1_[1].ag_ptr;\
	(B) = x1_->ag_ptr;\
    }

#define DESTROY_CONS_ptr(D, A, B, C)\
    {\
	calculus *x2_ = CHECK_NULL(C);\
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
	calculus *x4_ = CHECK_NULL(*r4_);\
	(A) = x4_[1].ag_ptr;\
	*r4_ = x4_->ag_ptr;\
	destroy_calculus(x4_, (unsigned)2);\
    }


/* Definitions for lists */

#define HEAD_list(A)			(CHECK_NULL(A) + 1)
#define PTR_TAIL_list(A)		(CHECK_NULL(A))
#define TAIL_list(A)			(CHECK_NULL(A)->ag_ptr)
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

#define COPY_list(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_list(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_list(A, B, C)\
    {\
	calculus *x5_ = GEN_calculus(2, TYPEID_list);\
	x5_[1].ag_ptr = (A);\
	x5_->ag_ptr = (B);\
	(C) = x5_;\
    }

#define UN_CONS_list(A, B, C)\
    {\
	calculus *x6_ = CHECK_NULL(C);\
	(A) = x6_[1].ag_ptr;\
	(B) = x6_->ag_ptr;\
    }

#define DESTROY_CONS_list(D, A, B, C)\
    {\
	calculus *x7_ = CHECK_NULL(C);\
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
	calculus *x9_ = CHECK_NULL(*r9_);\
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

#define COPY_stack(A, B)		(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_stack(A)			(CHECK_NULL(A)->ag_ptr)
#define CONS_stack(A, B, C)\
    {\
	calculus *x10_ = GEN_calculus(2, TYPEID_list);\
	x10_[1].ag_ptr = (A);\
	x10_->ag_ptr = (B);\
	(C) = x10_;\
    }

#define UN_CONS_stack(A, B, C)\
    {\
	calculus *x11_ = CHECK_NULL(C);\
	(A) = x11_[1].ag_ptr;\
	(B) = x11_->ag_ptr;\
    }

#define DESTROY_CONS_stack(D, A, B, C)\
    {\
	calculus *x12_ = CHECK_NULL(C);\
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
	calculus *x14_ = CHECK_NULL(*r14_);\
	(A) = x14_[1].ag_ptr;\
	*r14_ = x14_->ag_ptr;\
	destroy_calculus(x14_, (unsigned)2);\
    }


/* Definitions for sizes */

#define SCALE(A, B)			((A)*(int)(B))


/* Definitions for primitive int */

#define SIZE_int			1

#define COPY_int(A, B)			(CHECK_NULL(A)->ag_prim_int = (B))
#define DEREF_int(A)			(CHECK_NULL(A)->ag_prim_int)
#define CONS_int(A, B, C)\
    {\
	calculus *x15_ = GEN_calculus(2, TYPEID_list);\
	COPY_int(x15_ + 1, (A));\
	x15_->ag_ptr = (B);\
	(C) = x15_;\
    }

#define UN_CONS_int(A, B, C)\
    {\
	calculus *x16_ = CHECK_NULL(C);\
	(A) = DEREF_int(x16_ + 1);\
	(B) = x16_->ag_ptr;\
    }

#define DESTROY_CONS_int(D, A, B, C)\
    {\
	calculus *x17_ = CHECK_NULL(C);\
	(A) = DEREF_int(x17_ + 1);\
	(B) = x17_->ag_ptr;\
	(D)(x17_, (unsigned)2);\
    }

#define PUSH_int(A, B)\
    {\
	calculus **r18_ = &(B);\
	calculus *x18_ = GEN_calculus(2, TYPEID_stack);\
	COPY_int(x18_ + 1, (A));\
	x18_->ag_ptr = *r18_;\
	*r18_ = x18_;\
    }

#define POP_int(A, B)\
    {\
	calculus **r19_ = &(B);\
	calculus *x19_ = CHECK_NULL(*r19_);\
	(A) = DEREF_int(x19_ + 1);\
	*r19_ = x19_->ag_ptr;\
	destroy_calculus(x19_, (unsigned)2);\
    }


/* Definitions for primitive number */

#define SIZE_number			1

#define COPY_number(A, B)		(CHECK_NULL(A)->ag_prim_number = (B))
#define DEREF_number(A)			(CHECK_NULL(A)->ag_prim_number)
#define CONS_number(A, B, C)\
    {\
	calculus *x20_ = GEN_calculus(2, TYPEID_list);\
	COPY_number(x20_ + 1, (A));\
	x20_->ag_ptr = (B);\
	(C) = x20_;\
    }

#define UN_CONS_number(A, B, C)\
    {\
	calculus *x21_ = CHECK_NULL(C);\
	(A) = DEREF_number(x21_ + 1);\
	(B) = x21_->ag_ptr;\
    }

#define DESTROY_CONS_number(D, A, B, C)\
    {\
	calculus *x22_ = CHECK_NULL(C);\
	(A) = DEREF_number(x22_ + 1);\
	(B) = x22_->ag_ptr;\
	(D)(x22_, (unsigned)2);\
    }

#define PUSH_number(A, B)\
    {\
	calculus **r23_ = &(B);\
	calculus *x23_ = GEN_calculus(2, TYPEID_stack);\
	COPY_number(x23_ + 1, (A));\
	x23_->ag_ptr = *r23_;\
	*r23_ = x23_;\
    }

#define POP_number(A, B)\
    {\
	calculus **r24_ = &(B);\
	calculus *x24_ = CHECK_NULL(*r24_);\
	(A) = DEREF_number(x24_ + 1);\
	*r24_ = x24_->ag_ptr;\
	destroy_calculus(x24_, (unsigned)2);\
    }


/* Definitions for primitive string */

#define SIZE_string			1

#define COPY_string(A, B)		(CHECK_NULL(A)->ag_prim_string = (B))
#define DEREF_string(A)			(CHECK_NULL(A)->ag_prim_string)
#define CONS_string(A, B, C)\
    {\
	calculus *x25_ = GEN_calculus(2, TYPEID_list);\
	COPY_string(x25_ + 1, (A));\
	x25_->ag_ptr = (B);\
	(C) = x25_;\
    }

#define UN_CONS_string(A, B, C)\
    {\
	calculus *x26_ = CHECK_NULL(C);\
	(A) = DEREF_string(x26_ + 1);\
	(B) = x26_->ag_ptr;\
    }

#define DESTROY_CONS_string(D, A, B, C)\
    {\
	calculus *x27_ = CHECK_NULL(C);\
	(A) = DEREF_string(x27_ + 1);\
	(B) = x27_->ag_ptr;\
	(D)(x27_, (unsigned)2);\
    }

#define PUSH_string(A, B)\
    {\
	calculus **r28_ = &(B);\
	calculus *x28_ = GEN_calculus(2, TYPEID_stack);\
	COPY_string(x28_ + 1, (A));\
	x28_->ag_ptr = *r28_;\
	*r28_ = x28_;\
    }

#define POP_string(A, B)\
    {\
	calculus **r29_ = &(B);\
	calculus *x29_ = CHECK_NULL(*r29_);\
	(A) = DEREF_string(x29_ + 1);\
	*r29_ = x29_->ag_ptr;\
	destroy_calculus(x29_, (unsigned)2);\
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
	calculus *x30_ = CHECK_NULL(A);\
	ALGEBRA_DEFN y30_;\
	y30_ = (B);\
	COPY_string(x30_ + 0, y30_.name);\
	COPY_int(x30_ + 1, y30_.major_no);\
	COPY_int(x30_ + 2, y30_.minor_no);\
	COPY_list(x30_ + 3, y30_.primitives);\
	COPY_list(x30_ + 4, y30_.identities);\
	COPY_list(x30_ + 5, y30_.enumerations);\
	COPY_list(x30_ + 6, y30_.structures);\
	COPY_list(x30_ + 7, y30_.unions);\
	COPY_list(x30_ + 8, y30_.types);\
    }

#define DEREF_alg(A, B)\
    {\
	calculus *x31_ = CHECK_NULL(A);\
	ALGEBRA_DEFN *y31_ = &(B);\
	y31_->name = DEREF_string(x31_ + 0);\
	y31_->major_no = DEREF_int(x31_ + 1);\
	y31_->minor_no = DEREF_int(x31_ + 2);\
	y31_->primitives = DEREF_list(x31_ + 3);\
	y31_->identities = DEREF_list(x31_ + 4);\
	y31_->enumerations = DEREF_list(x31_ + 5);\
	y31_->structures = DEREF_list(x31_ + 6);\
	y31_->unions = DEREF_list(x31_ + 7);\
	y31_->types = DEREF_list(x31_ + 8);\
    }

#define MAKE_alg(name_, major_no_, minor_no_, primitives_, identities_, enumerations_, structures_, unions_, types_, alg_)\
    {\
	calculus *x32_ = CHECK_NULL(alg_);\
	COPY_string(x32_ + 0, (name_));\
	COPY_int(x32_ + 1, (major_no_));\
	COPY_int(x32_ + 2, (minor_no_));\
	COPY_list(x32_ + 3, (primitives_));\
	COPY_list(x32_ + 4, (identities_));\
	COPY_list(x32_ + 5, (enumerations_));\
	COPY_list(x32_ + 6, (structures_));\
	COPY_list(x32_ + 7, (unions_));\
	COPY_list(x32_ + 8, (types_));\
    }

#define CONS_alg(A, B, C)\
    {\
	calculus *x33_ = GEN_calculus(10, TYPEID_list);\
	COPY_alg(x33_ + 1, (A));\
	x33_->ag_ptr = (B);\
	(C) = x33_;\
    }

#define UN_CONS_alg(A, B, C)\
    {\
	calculus *x34_ = CHECK_NULL(C);\
	DEREF_alg(x34_ + 1, (A));\
	(B) = x34_->ag_ptr;\
    }

#define DESTROY_CONS_alg(D, A, B, C)\
    {\
	calculus *x35_ = CHECK_NULL(C);\
	DEREF_alg(x35_ + 1, (A));\
	(B) = x35_->ag_ptr;\
	(D)(x35_, (unsigned)10);\
    }

#define PUSH_alg(A, B)\
    {\
	calculus **r36_ = &(B);\
	calculus *x36_ = GEN_calculus(10, TYPEID_stack);\
	COPY_alg(x36_ + 1, (A));\
	x36_->ag_ptr = *r36_;\
	*r36_ = x36_;\
    }

#define POP_alg(A, B)\
    {\
	calculus **r37_ = &(B);\
	calculus *x37_ = CHECK_NULL(*r37_);\
	DEREF_alg(x37_ + 1, (A));\
	*r37_ = x37_->ag_ptr;\
	destroy_calculus(x37_, (unsigned)10);\
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
	calculus *x38_ = CHECK_NULL(A);\
	CLASS_ID y38_;\
	y38_ = (B);\
	COPY_string(x38_ + 0, y38_.name);\
	COPY_string(x38_ + 1, y38_.name_aux);\
	COPY_int(x38_ + 2, y38_.flag);\
	COPY_string(x38_ + 3, y38_.file);\
	COPY_int(x38_ + 4, y38_.line);\
    }

#define DEREF_cid(A, B)\
    {\
	calculus *x39_ = CHECK_NULL(A);\
	CLASS_ID *y39_ = &(B);\
	y39_->name = DEREF_string(x39_ + 0);\
	y39_->name_aux = DEREF_string(x39_ + 1);\
	y39_->flag = DEREF_int(x39_ + 2);\
	y39_->file = DEREF_string(x39_ + 3);\
	y39_->line = DEREF_int(x39_ + 4);\
    }

#define MAKE_cid(name_, name_aux_, flag_, file_, line_, cid_)\
    {\
	calculus *x40_ = CHECK_NULL(cid_);\
	COPY_string(x40_ + 0, (name_));\
	COPY_string(x40_ + 1, (name_aux_));\
	COPY_int(x40_ + 2, (flag_));\
	COPY_string(x40_ + 3, (file_));\
	COPY_int(x40_ + 4, (line_));\
    }

#define CONS_cid(A, B, C)\
    {\
	calculus *x41_ = GEN_calculus(6, TYPEID_list);\
	COPY_cid(x41_ + 1, (A));\
	x41_->ag_ptr = (B);\
	(C) = x41_;\
    }

#define UN_CONS_cid(A, B, C)\
    {\
	calculus *x42_ = CHECK_NULL(C);\
	DEREF_cid(x42_ + 1, (A));\
	(B) = x42_->ag_ptr;\
    }

#define DESTROY_CONS_cid(D, A, B, C)\
    {\
	calculus *x43_ = CHECK_NULL(C);\
	DEREF_cid(x43_ + 1, (A));\
	(B) = x43_->ag_ptr;\
	(D)(x43_, (unsigned)6);\
    }

#define PUSH_cid(A, B)\
    {\
	calculus **r44_ = &(B);\
	calculus *x44_ = GEN_calculus(6, TYPEID_stack);\
	COPY_cid(x44_ + 1, (A));\
	x44_->ag_ptr = *r44_;\
	*r44_ = x44_;\
    }

#define POP_cid(A, B)\
    {\
	calculus **r45_ = &(B);\
	calculus *x45_ = CHECK_NULL(*r45_);\
	DEREF_cid(x45_ + 1, (A));\
	*r45_ = x45_->ag_ptr;\
	destroy_calculus(x45_, (unsigned)6);\
    }


/* Definitions for structure PRIMITIVE */

#define prim_id(P)			((P) + 0)
#define prim_defn(P)			((P) + 1)
#define SIZE_prim			2

#define COPY_prim(A, B)\
    {\
	calculus *x46_ = CHECK_NULL(A);\
	PRIMITIVE y46_;\
	y46_ = (B);\
	COPY_ptr(x46_ + 0, y46_.id);\
	COPY_string(x46_ + 1, y46_.defn);\
    }

#define DEREF_prim(A, B)\
    {\
	calculus *x47_ = CHECK_NULL(A);\
	PRIMITIVE *y47_ = &(B);\
	y47_->id = DEREF_ptr(x47_ + 0);\
	y47_->defn = DEREF_string(x47_ + 1);\
    }

#define MAKE_prim(id_, defn_, prim_)\
    {\
	calculus *x48_ = CHECK_NULL(prim_);\
	COPY_ptr(x48_ + 0, (id_));\
	COPY_string(x48_ + 1, (defn_));\
    }

#define CONS_prim(A, B, C)\
    {\
	calculus *x49_ = GEN_calculus(3, TYPEID_list);\
	COPY_prim(x49_ + 1, (A));\
	x49_->ag_ptr = (B);\
	(C) = x49_;\
    }

#define UN_CONS_prim(A, B, C)\
    {\
	calculus *x50_ = CHECK_NULL(C);\
	DEREF_prim(x50_ + 1, (A));\
	(B) = x50_->ag_ptr;\
    }

#define DESTROY_CONS_prim(D, A, B, C)\
    {\
	calculus *x51_ = CHECK_NULL(C);\
	DEREF_prim(x51_ + 1, (A));\
	(B) = x51_->ag_ptr;\
	(D)(x51_, (unsigned)3);\
    }

#define PUSH_prim(A, B)\
    {\
	calculus **r52_ = &(B);\
	calculus *x52_ = GEN_calculus(3, TYPEID_stack);\
	COPY_prim(x52_ + 1, (A));\
	x52_->ag_ptr = *r52_;\
	*r52_ = x52_;\
    }

#define POP_prim(A, B)\
    {\
	calculus **r53_ = &(B);\
	calculus *x53_ = CHECK_NULL(*r53_);\
	DEREF_prim(x53_ + 1, (A));\
	*r53_ = x53_->ag_ptr;\
	destroy_calculus(x53_, (unsigned)3);\
    }


/* Definitions for structure ECONST */

#define ec_name(P)			((P) + 0)
#define ec_value(P)			((P) + 1)
#define SIZE_ec				2

#define COPY_ec(A, B)\
    {\
	calculus *x54_ = CHECK_NULL(A);\
	ECONST y54_;\
	y54_ = (B);\
	COPY_string(x54_ + 0, y54_.name);\
	COPY_number(x54_ + 1, y54_.value);\
    }

#define DEREF_ec(A, B)\
    {\
	calculus *x55_ = CHECK_NULL(A);\
	ECONST *y55_ = &(B);\
	y55_->name = DEREF_string(x55_ + 0);\
	y55_->value = DEREF_number(x55_ + 1);\
    }

#define MAKE_ec(name_, value_, ec_)\
    {\
	calculus *x56_ = CHECK_NULL(ec_);\
	COPY_string(x56_ + 0, (name_));\
	COPY_number(x56_ + 1, (value_));\
    }

#define CONS_ec(A, B, C)\
    {\
	calculus *x57_ = GEN_calculus(3, TYPEID_list);\
	COPY_ec(x57_ + 1, (A));\
	x57_->ag_ptr = (B);\
	(C) = x57_;\
    }

#define UN_CONS_ec(A, B, C)\
    {\
	calculus *x58_ = CHECK_NULL(C);\
	DEREF_ec(x58_ + 1, (A));\
	(B) = x58_->ag_ptr;\
    }

#define DESTROY_CONS_ec(D, A, B, C)\
    {\
	calculus *x59_ = CHECK_NULL(C);\
	DEREF_ec(x59_ + 1, (A));\
	(B) = x59_->ag_ptr;\
	(D)(x59_, (unsigned)3);\
    }

#define PUSH_ec(A, B)\
    {\
	calculus **r60_ = &(B);\
	calculus *x60_ = GEN_calculus(3, TYPEID_stack);\
	COPY_ec(x60_ + 1, (A));\
	x60_->ag_ptr = *r60_;\
	*r60_ = x60_;\
    }

#define POP_ec(A, B)\
    {\
	calculus **r61_ = &(B);\
	calculus *x61_ = CHECK_NULL(*r61_);\
	DEREF_ec(x61_ + 1, (A));\
	*r61_ = x61_->ag_ptr;\
	destroy_calculus(x61_, (unsigned)3);\
    }


/* Definitions for structure ENUM */

#define en_id(P)			((P) + 0)
#define en_consts(P)			((P) + 1)
#define en_order(P)			((P) + 2)
#define en_lists(P)			((P) + 3)
#define SIZE_en				4

#define COPY_en(A, B)\
    {\
	calculus *x62_ = CHECK_NULL(A);\
	ENUM y62_;\
	y62_ = (B);\
	COPY_ptr(x62_ + 0, y62_.id);\
	COPY_list(x62_ + 1, y62_.consts);\
	COPY_number(x62_ + 2, y62_.order);\
	COPY_int(x62_ + 3, y62_.lists);\
    }

#define DEREF_en(A, B)\
    {\
	calculus *x63_ = CHECK_NULL(A);\
	ENUM *y63_ = &(B);\
	y63_->id = DEREF_ptr(x63_ + 0);\
	y63_->consts = DEREF_list(x63_ + 1);\
	y63_->order = DEREF_number(x63_ + 2);\
	y63_->lists = DEREF_int(x63_ + 3);\
    }

#define MAKE_en(id_, consts_, order_, lists_, en_)\
    {\
	calculus *x64_ = CHECK_NULL(en_);\
	COPY_ptr(x64_ + 0, (id_));\
	COPY_list(x64_ + 1, (consts_));\
	COPY_number(x64_ + 2, (order_));\
	COPY_int(x64_ + 3, (lists_));\
    }

#define CONS_en(A, B, C)\
    {\
	calculus *x65_ = GEN_calculus(5, TYPEID_list);\
	COPY_en(x65_ + 1, (A));\
	x65_->ag_ptr = (B);\
	(C) = x65_;\
    }

#define UN_CONS_en(A, B, C)\
    {\
	calculus *x66_ = CHECK_NULL(C);\
	DEREF_en(x66_ + 1, (A));\
	(B) = x66_->ag_ptr;\
    }

#define DESTROY_CONS_en(D, A, B, C)\
    {\
	calculus *x67_ = CHECK_NULL(C);\
	DEREF_en(x67_ + 1, (A));\
	(B) = x67_->ag_ptr;\
	(D)(x67_, (unsigned)5);\
    }

#define PUSH_en(A, B)\
    {\
	calculus **r68_ = &(B);\
	calculus *x68_ = GEN_calculus(5, TYPEID_stack);\
	COPY_en(x68_ + 1, (A));\
	x68_->ag_ptr = *r68_;\
	*r68_ = x68_;\
    }

#define POP_en(A, B)\
    {\
	calculus **r69_ = &(B);\
	calculus *x69_ = CHECK_NULL(*r69_);\
	DEREF_en(x69_ + 1, (A));\
	*r69_ = x69_->ag_ptr;\
	destroy_calculus(x69_, (unsigned)5);\
    }


/* Definitions for structure IDENTITY */

#define ident_id(P)			((P) + 0)
#define ident_defn(P)			((P) + 1)
#define SIZE_ident			2

#define COPY_ident(A, B)\
    {\
	calculus *x70_ = CHECK_NULL(A);\
	IDENTITY y70_;\
	y70_ = (B);\
	COPY_ptr(x70_ + 0, y70_.id);\
	COPY_ptr(x70_ + 1, y70_.defn);\
    }

#define DEREF_ident(A, B)\
    {\
	calculus *x71_ = CHECK_NULL(A);\
	IDENTITY *y71_ = &(B);\
	y71_->id = DEREF_ptr(x71_ + 0);\
	y71_->defn = DEREF_ptr(x71_ + 1);\
    }

#define MAKE_ident(id_, defn_, ident_)\
    {\
	calculus *x72_ = CHECK_NULL(ident_);\
	COPY_ptr(x72_ + 0, (id_));\
	COPY_ptr(x72_ + 1, (defn_));\
    }

#define CONS_ident(A, B, C)\
    {\
	calculus *x73_ = GEN_calculus(3, TYPEID_list);\
	COPY_ident(x73_ + 1, (A));\
	x73_->ag_ptr = (B);\
	(C) = x73_;\
    }

#define UN_CONS_ident(A, B, C)\
    {\
	calculus *x74_ = CHECK_NULL(C);\
	DEREF_ident(x74_ + 1, (A));\
	(B) = x74_->ag_ptr;\
    }

#define DESTROY_CONS_ident(D, A, B, C)\
    {\
	calculus *x75_ = CHECK_NULL(C);\
	DEREF_ident(x75_ + 1, (A));\
	(B) = x75_->ag_ptr;\
	(D)(x75_, (unsigned)3);\
    }

#define PUSH_ident(A, B)\
    {\
	calculus **r76_ = &(B);\
	calculus *x76_ = GEN_calculus(3, TYPEID_stack);\
	COPY_ident(x76_ + 1, (A));\
	x76_->ag_ptr = *r76_;\
	*r76_ = x76_;\
    }

#define POP_ident(A, B)\
    {\
	calculus **r77_ = &(B);\
	calculus *x77_ = CHECK_NULL(*r77_);\
	DEREF_ident(x77_ + 1, (A));\
	*r77_ = x77_->ag_ptr;\
	destroy_calculus(x77_, (unsigned)3);\
    }


/* Definitions for structure COMPONENT */

#define cmp_name(P)			((P) + 0)
#define cmp_type(P)			((P) + 1)
#define cmp_value(P)			((P) + 2)
#define SIZE_cmp			3

#define COPY_cmp(A, B)\
    {\
	calculus *x78_ = CHECK_NULL(A);\
	COMPONENT y78_;\
	y78_ = (B);\
	COPY_string(x78_ + 0, y78_.name);\
	COPY_ptr(x78_ + 1, y78_.type);\
	COPY_string(x78_ + 2, y78_.value);\
    }

#define DEREF_cmp(A, B)\
    {\
	calculus *x79_ = CHECK_NULL(A);\
	COMPONENT *y79_ = &(B);\
	y79_->name = DEREF_string(x79_ + 0);\
	y79_->type = DEREF_ptr(x79_ + 1);\
	y79_->value = DEREF_string(x79_ + 2);\
    }

#define MAKE_cmp(name_, type_, value_, cmp_)\
    {\
	calculus *x80_ = CHECK_NULL(cmp_);\
	COPY_string(x80_ + 0, (name_));\
	COPY_ptr(x80_ + 1, (type_));\
	COPY_string(x80_ + 2, (value_));\
    }

#define CONS_cmp(A, B, C)\
    {\
	calculus *x81_ = GEN_calculus(4, TYPEID_list);\
	COPY_cmp(x81_ + 1, (A));\
	x81_->ag_ptr = (B);\
	(C) = x81_;\
    }

#define UN_CONS_cmp(A, B, C)\
    {\
	calculus *x82_ = CHECK_NULL(C);\
	DEREF_cmp(x82_ + 1, (A));\
	(B) = x82_->ag_ptr;\
    }

#define DESTROY_CONS_cmp(D, A, B, C)\
    {\
	calculus *x83_ = CHECK_NULL(C);\
	DEREF_cmp(x83_ + 1, (A));\
	(B) = x83_->ag_ptr;\
	(D)(x83_, (unsigned)4);\
    }

#define PUSH_cmp(A, B)\
    {\
	calculus **r84_ = &(B);\
	calculus *x84_ = GEN_calculus(4, TYPEID_stack);\
	COPY_cmp(x84_ + 1, (A));\
	x84_->ag_ptr = *r84_;\
	*r84_ = x84_;\
    }

#define POP_cmp(A, B)\
    {\
	calculus **r85_ = &(B);\
	calculus *x85_ = CHECK_NULL(*r85_);\
	DEREF_cmp(x85_ + 1, (A));\
	*r85_ = x85_->ag_ptr;\
	destroy_calculus(x85_, (unsigned)4);\
    }


/* Definitions for structure STRUCTURE */

#define str_id(P)			((P) + 0)
#define str_base(P)			((P) + 1)
#define str_defn(P)			((P) + 2)
#define str_output(P)			((P) + 3)
#define SIZE_str			4

#define COPY_str(A, B)\
    {\
	calculus *x86_ = CHECK_NULL(A);\
	STRUCTURE y86_;\
	y86_ = (B);\
	COPY_ptr(x86_ + 0, y86_.id);\
	COPY_ptr(x86_ + 1, y86_.base);\
	COPY_list(x86_ + 2, y86_.defn);\
	COPY_int(x86_ + 3, y86_.output);\
    }

#define DEREF_str(A, B)\
    {\
	calculus *x87_ = CHECK_NULL(A);\
	STRUCTURE *y87_ = &(B);\
	y87_->id = DEREF_ptr(x87_ + 0);\
	y87_->base = DEREF_ptr(x87_ + 1);\
	y87_->defn = DEREF_list(x87_ + 2);\
	y87_->output = DEREF_int(x87_ + 3);\
    }

#define MAKE_str(id_, base_, defn_, output_, str_)\
    {\
	calculus *x88_ = CHECK_NULL(str_);\
	COPY_ptr(x88_ + 0, (id_));\
	COPY_ptr(x88_ + 1, (base_));\
	COPY_list(x88_ + 2, (defn_));\
	COPY_int(x88_ + 3, (output_));\
    }

#define CONS_str(A, B, C)\
    {\
	calculus *x89_ = GEN_calculus(5, TYPEID_list);\
	COPY_str(x89_ + 1, (A));\
	x89_->ag_ptr = (B);\
	(C) = x89_;\
    }

#define UN_CONS_str(A, B, C)\
    {\
	calculus *x90_ = CHECK_NULL(C);\
	DEREF_str(x90_ + 1, (A));\
	(B) = x90_->ag_ptr;\
    }

#define DESTROY_CONS_str(D, A, B, C)\
    {\
	calculus *x91_ = CHECK_NULL(C);\
	DEREF_str(x91_ + 1, (A));\
	(B) = x91_->ag_ptr;\
	(D)(x91_, (unsigned)5);\
    }

#define PUSH_str(A, B)\
    {\
	calculus **r92_ = &(B);\
	calculus *x92_ = GEN_calculus(5, TYPEID_stack);\
	COPY_str(x92_ + 1, (A));\
	x92_->ag_ptr = *r92_;\
	*r92_ = x92_;\
    }

#define POP_str(A, B)\
    {\
	calculus **r93_ = &(B);\
	calculus *x93_ = CHECK_NULL(*r93_);\
	DEREF_str(x93_ + 1, (A));\
	*r93_ = x93_->ag_ptr;\
	destroy_calculus(x93_, (unsigned)5);\
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
	calculus *x94_ = CHECK_NULL(A);\
	FIELD y94_;\
	y94_ = (B);\
	COPY_string(x94_ + 0, y94_.name);\
	COPY_int(x94_ + 1, y94_.tag);\
	COPY_int(x94_ + 2, y94_.flag);\
	COPY_int(x94_ + 3, y94_.set);\
	COPY_ptr(x94_ + 4, y94_.base);\
	COPY_list(x94_ + 5, y94_.defn);\
    }

#define DEREF_fld(A, B)\
    {\
	calculus *x95_ = CHECK_NULL(A);\
	FIELD *y95_ = &(B);\
	y95_->name = DEREF_string(x95_ + 0);\
	y95_->tag = DEREF_int(x95_ + 1);\
	y95_->flag = DEREF_int(x95_ + 2);\
	y95_->set = DEREF_int(x95_ + 3);\
	y95_->base = DEREF_ptr(x95_ + 4);\
	y95_->defn = DEREF_list(x95_ + 5);\
    }

#define MAKE_fld(name_, tag_, flag_, set_, base_, defn_, fld_)\
    {\
	calculus *x96_ = CHECK_NULL(fld_);\
	COPY_string(x96_ + 0, (name_));\
	COPY_int(x96_ + 1, (tag_));\
	COPY_int(x96_ + 2, (flag_));\
	COPY_int(x96_ + 3, (set_));\
	COPY_ptr(x96_ + 4, (base_));\
	COPY_list(x96_ + 5, (defn_));\
    }

#define CONS_fld(A, B, C)\
    {\
	calculus *x97_ = GEN_calculus(7, TYPEID_list);\
	COPY_fld(x97_ + 1, (A));\
	x97_->ag_ptr = (B);\
	(C) = x97_;\
    }

#define UN_CONS_fld(A, B, C)\
    {\
	calculus *x98_ = CHECK_NULL(C);\
	DEREF_fld(x98_ + 1, (A));\
	(B) = x98_->ag_ptr;\
    }

#define DESTROY_CONS_fld(D, A, B, C)\
    {\
	calculus *x99_ = CHECK_NULL(C);\
	DEREF_fld(x99_ + 1, (A));\
	(B) = x99_->ag_ptr;\
	(D)(x99_, (unsigned)7);\
    }

#define PUSH_fld(A, B)\
    {\
	calculus **r100_ = &(B);\
	calculus *x100_ = GEN_calculus(7, TYPEID_stack);\
	COPY_fld(x100_ + 1, (A));\
	x100_->ag_ptr = *r100_;\
	*r100_ = x100_;\
    }

#define POP_fld(A, B)\
    {\
	calculus **r101_ = &(B);\
	calculus *x101_ = CHECK_NULL(*r101_);\
	DEREF_fld(x101_ + 1, (A));\
	*r101_ = x101_->ag_ptr;\
	destroy_calculus(x101_, (unsigned)7);\
    }


/* Definitions for structure ARGUMENT */

#define arg_name(P)			((P) + 0)
#define arg_type(P)			((P) + 1)
#define SIZE_arg			2

#define COPY_arg(A, B)\
    {\
	calculus *x102_ = CHECK_NULL(A);\
	ARGUMENT y102_;\
	y102_ = (B);\
	COPY_string(x102_ + 0, y102_.name);\
	COPY_ptr(x102_ + 1, y102_.type);\
    }

#define DEREF_arg(A, B)\
    {\
	calculus *x103_ = CHECK_NULL(A);\
	ARGUMENT *y103_ = &(B);\
	y103_->name = DEREF_string(x103_ + 0);\
	y103_->type = DEREF_ptr(x103_ + 1);\
    }

#define MAKE_arg(name_, type_, arg_)\
    {\
	calculus *x104_ = CHECK_NULL(arg_);\
	COPY_string(x104_ + 0, (name_));\
	COPY_ptr(x104_ + 1, (type_));\
    }

#define CONS_arg(A, B, C)\
    {\
	calculus *x105_ = GEN_calculus(3, TYPEID_list);\
	COPY_arg(x105_ + 1, (A));\
	x105_->ag_ptr = (B);\
	(C) = x105_;\
    }

#define UN_CONS_arg(A, B, C)\
    {\
	calculus *x106_ = CHECK_NULL(C);\
	DEREF_arg(x106_ + 1, (A));\
	(B) = x106_->ag_ptr;\
    }

#define DESTROY_CONS_arg(D, A, B, C)\
    {\
	calculus *x107_ = CHECK_NULL(C);\
	DEREF_arg(x107_ + 1, (A));\
	(B) = x107_->ag_ptr;\
	(D)(x107_, (unsigned)3);\
    }

#define PUSH_arg(A, B)\
    {\
	calculus **r108_ = &(B);\
	calculus *x108_ = GEN_calculus(3, TYPEID_stack);\
	COPY_arg(x108_ + 1, (A));\
	x108_->ag_ptr = *r108_;\
	*r108_ = x108_;\
    }

#define POP_arg(A, B)\
    {\
	calculus **r109_ = &(B);\
	calculus *x109_ = CHECK_NULL(*r109_);\
	DEREF_arg(x109_ + 1, (A));\
	*r109_ = x109_->ag_ptr;\
	destroy_calculus(x109_, (unsigned)3);\
    }


/* Definitions for structure MAP */

#define map_name(P)			((P) + 0)
#define map_flag(P)			((P) + 1)
#define map_ret_type(P)			((P) + 2)
#define map_args(P)			((P) + 3)
#define SIZE_map			4

#define COPY_map(A, B)\
    {\
	calculus *x110_ = CHECK_NULL(A);\
	MAP y110_;\
	y110_ = (B);\
	COPY_string(x110_ + 0, y110_.name);\
	COPY_int(x110_ + 1, y110_.flag);\
	COPY_ptr(x110_ + 2, y110_.ret_type);\
	COPY_list(x110_ + 3, y110_.args);\
    }

#define DEREF_map(A, B)\
    {\
	calculus *x111_ = CHECK_NULL(A);\
	MAP *y111_ = &(B);\
	y111_->name = DEREF_string(x111_ + 0);\
	y111_->flag = DEREF_int(x111_ + 1);\
	y111_->ret_type = DEREF_ptr(x111_ + 2);\
	y111_->args = DEREF_list(x111_ + 3);\
    }

#define MAKE_map(name_, flag_, ret_type_, args_, map_)\
    {\
	calculus *x112_ = CHECK_NULL(map_);\
	COPY_string(x112_ + 0, (name_));\
	COPY_int(x112_ + 1, (flag_));\
	COPY_ptr(x112_ + 2, (ret_type_));\
	COPY_list(x112_ + 3, (args_));\
    }

#define CONS_map(A, B, C)\
    {\
	calculus *x113_ = GEN_calculus(5, TYPEID_list);\
	COPY_map(x113_ + 1, (A));\
	x113_->ag_ptr = (B);\
	(C) = x113_;\
    }

#define UN_CONS_map(A, B, C)\
    {\
	calculus *x114_ = CHECK_NULL(C);\
	DEREF_map(x114_ + 1, (A));\
	(B) = x114_->ag_ptr;\
    }

#define DESTROY_CONS_map(D, A, B, C)\
    {\
	calculus *x115_ = CHECK_NULL(C);\
	DEREF_map(x115_ + 1, (A));\
	(B) = x115_->ag_ptr;\
	(D)(x115_, (unsigned)5);\
    }

#define PUSH_map(A, B)\
    {\
	calculus **r116_ = &(B);\
	calculus *x116_ = GEN_calculus(5, TYPEID_stack);\
	COPY_map(x116_ + 1, (A));\
	x116_->ag_ptr = *r116_;\
	*r116_ = x116_;\
    }

#define POP_map(A, B)\
    {\
	calculus **r117_ = &(B);\
	calculus *x117_ = CHECK_NULL(*r117_);\
	DEREF_map(x117_ + 1, (A));\
	*r117_ = x117_->ag_ptr;\
	destroy_calculus(x117_, (unsigned)5);\
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
	calculus *x118_ = CHECK_NULL(A);\
	UNION y118_;\
	y118_ = (B);\
	COPY_ptr(x118_ + 0, y118_.id);\
	COPY_ptr(x118_ + 1, y118_.base);\
	COPY_list(x118_ + 2, y118_.s_defn);\
	COPY_list(x118_ + 3, y118_.u_defn);\
	COPY_list(x118_ + 4, y118_.map);\
	COPY_int(x118_ + 5, y118_.no_fields);\
    }

#define DEREF_un(A, B)\
    {\
	calculus *x119_ = CHECK_NULL(A);\
	UNION *y119_ = &(B);\
	y119_->id = DEREF_ptr(x119_ + 0);\
	y119_->base = DEREF_ptr(x119_ + 1);\
	y119_->s_defn = DEREF_list(x119_ + 2);\
	y119_->u_defn = DEREF_list(x119_ + 3);\
	y119_->map = DEREF_list(x119_ + 4);\
	y119_->no_fields = DEREF_int(x119_ + 5);\
    }

#define MAKE_un(id_, base_, s_defn_, u_defn_, map_, no_fields_, un_)\
    {\
	calculus *x120_ = CHECK_NULL(un_);\
	COPY_ptr(x120_ + 0, (id_));\
	COPY_ptr(x120_ + 1, (base_));\
	COPY_list(x120_ + 2, (s_defn_));\
	COPY_list(x120_ + 3, (u_defn_));\
	COPY_list(x120_ + 4, (map_));\
	COPY_int(x120_ + 5, (no_fields_));\
    }

#define CONS_un(A, B, C)\
    {\
	calculus *x121_ = GEN_calculus(7, TYPEID_list);\
	COPY_un(x121_ + 1, (A));\
	x121_->ag_ptr = (B);\
	(C) = x121_;\
    }

#define UN_CONS_un(A, B, C)\
    {\
	calculus *x122_ = CHECK_NULL(C);\
	DEREF_un(x122_ + 1, (A));\
	(B) = x122_->ag_ptr;\
    }

#define DESTROY_CONS_un(D, A, B, C)\
    {\
	calculus *x123_ = CHECK_NULL(C);\
	DEREF_un(x123_ + 1, (A));\
	(B) = x123_->ag_ptr;\
	(D)(x123_, (unsigned)7);\
    }

#define PUSH_un(A, B)\
    {\
	calculus **r124_ = &(B);\
	calculus *x124_ = GEN_calculus(7, TYPEID_stack);\
	COPY_un(x124_ + 1, (A));\
	x124_->ag_ptr = *r124_;\
	*r124_ = x124_;\
    }

#define POP_un(A, B)\
    {\
	calculus **r125_ = &(B);\
	calculus *x125_ = CHECK_NULL(*r125_);\
	DEREF_un(x125_ + 1, (A));\
	*r125_ = x125_->ag_ptr;\
	destroy_calculus(x125_, (unsigned)7);\
    }


/* Definitions for union TYPE */

#define ORDER_type			((unsigned) 12)
#define SIZE_type			1
#define NULL_type			((TYPE) 0)
#define IS_NULL_type(A)			((A) == 0)
#define EQ_type(A, B)			((A) == (B))

#define COPY_type(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_type(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_type(A, B, C)\
    {\
	calculus *x126_ = GEN_calculus(2, TYPEID_list);\
	COPY_type(x126_ + 1, (A));\
	x126_->ag_ptr = (B);\
	(C) = x126_;\
    }

#define UN_CONS_type(A, B, C)\
    {\
	calculus *x127_ = CHECK_NULL(C);\
	(A) = DEREF_type(x127_ + 1);\
	(B) = x127_->ag_ptr;\
    }

#define DESTROY_CONS_type(D, A, B, C)\
    {\
	calculus *x128_ = CHECK_NULL(C);\
	(A) = DEREF_type(x128_ + 1);\
	(B) = x128_->ag_ptr;\
	(D)(x128_, (unsigned)2);\
    }

#define PUSH_type(A, B)\
    {\
	calculus **r129_ = &(B);\
	calculus *x129_ = GEN_calculus(2, TYPEID_stack);\
	COPY_type(x129_ + 1, (A));\
	x129_->ag_ptr = *r129_;\
	*r129_ = x129_;\
    }

#define POP_type(A, B)\
    {\
	calculus **r130_ = &(B);\
	calculus *x130_ = CHECK_NULL(*r130_);\
	(A) = DEREF_type(x130_ + 1);\
	*r130_ = x130_->ag_ptr;\
	destroy_calculus(x130_, (unsigned)2);\
    }


/* Definitions for union COMMAND */

#define ORDER_cmd			((unsigned) 4)
#define SIZE_cmd			1
#define NULL_cmd			((COMMAND) 0)
#define IS_NULL_cmd(A)			((A) == 0)
#define EQ_cmd(A, B)			((A) == (B))

#define COPY_cmd(A, B)			(CHECK_NULL(A)->ag_ptr = (B))
#define DEREF_cmd(A)			(CHECK_NULL(A)->ag_ptr)

#define CONS_cmd(A, B, C)\
    {\
	calculus *x131_ = GEN_calculus(2, TYPEID_list);\
	COPY_cmd(x131_ + 1, (A));\
	x131_->ag_ptr = (B);\
	(C) = x131_;\
    }

#define UN_CONS_cmd(A, B, C)\
    {\
	calculus *x132_ = CHECK_NULL(C);\
	(A) = DEREF_cmd(x132_ + 1);\
	(B) = x132_->ag_ptr;\
    }

#define DESTROY_CONS_cmd(D, A, B, C)\
    {\
	calculus *x133_ = CHECK_NULL(C);\
	(A) = DEREF_cmd(x133_ + 1);\
	(B) = x133_->ag_ptr;\
	(D)(x133_, (unsigned)2);\
    }

#define PUSH_cmd(A, B)\
    {\
	calculus **r134_ = &(B);\
	calculus *x134_ = GEN_calculus(2, TYPEID_stack);\
	COPY_cmd(x134_ + 1, (A));\
	x134_->ag_ptr = *r134_;\
	*r134_ = x134_;\
    }

#define POP_cmd(A, B)\
    {\
	calculus **r135_ = &(B);\
	calculus *x135_ = CHECK_NULL(*r135_);\
	(A) = DEREF_cmd(x135_ + 1);\
	*r135_ = x135_->ag_ptr;\
	destroy_calculus(x135_, (unsigned)2);\
    }


/* Maximum allocation size */

#define calculus_GEN_MAX		11

#endif
