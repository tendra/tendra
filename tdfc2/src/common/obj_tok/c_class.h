/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef C_CLASS_H_TOK_INCLUDED
#define C_CLASS_H_TOK_INCLUDED

#ifndef c_class_NAME
#define c_class_NAME			"c_class"
#define c_class_VERSION			"1.1"
#define c_class_SPECIFICATION		1
#define c_class_IMPLEMENTATION		0
#endif


/* Prototype macros */



/* Primitive types */

typedef character * string;
typedef unsigned long ulong_type;
typedef struct bits_tag * BITSTREAM_P;
typedef struct pptok_tag * PPTOKEN_P;


/* Basic types */

#ifndef c_class_DESTR_DEFINED
#define c_class_DESTR_DEFINED
typedef void (*DESTROYER)();
#endif

#pragma token PROC(TYPE) TYPE PTR #
#pragma token PROC(TYPE) TYPE LIST #
#pragma token PROC(TYPE) TYPE STACK #
#pragma token PROC(TYPE) TYPE SIZE #

#pragma interface PTR LIST STACK SIZE


/* Enumeration type definitions */

#pragma token VARIETY CV_SPEC #
#pragma interface CV_SPEC
#pragma token VARIETY BUILTIN_TYPE #
#pragma interface BUILTIN_TYPE
#pragma token VARIETY BASE_TYPE #
#pragma interface BASE_TYPE
#pragma token VARIETY CLASS_INFO #
#pragma interface CLASS_INFO
#pragma token VARIETY CLASS_USAGE #
#pragma interface CLASS_USAGE
#pragma token VARIETY DECL_SPEC #
#pragma interface DECL_SPEC
#pragma token VARIETY QUALIFIER #
#pragma interface QUALIFIER
#pragma token VARIETY NTEST #
#pragma interface NTEST
#pragma token VARIETY RMODE #
#pragma interface RMODE


/* Union type definitions */

#pragma token TYPE INT_TYPE #
#pragma interface INT_TYPE
#pragma token TYPE FLOAT_TYPE #
#pragma interface FLOAT_TYPE
#pragma token TYPE CLASS_TYPE #
#pragma interface CLASS_TYPE
#pragma token TYPE GRAPH #
#pragma interface GRAPH
#pragma token TYPE VIRTUAL #
#pragma interface VIRTUAL
#pragma token TYPE ENUM_TYPE #
#pragma interface ENUM_TYPE
#pragma token TYPE TYPE #
#pragma interface TYPE
#pragma token TYPE HASHID #
#pragma interface HASHID
#pragma token TYPE IDENTIFIER #
#pragma interface IDENTIFIER
#pragma token TYPE MEMBER #
#pragma interface MEMBER
#pragma token TYPE NAMESPACE #
#pragma interface NAMESPACE
#pragma token TYPE NAT #
#pragma interface NAT
#pragma token TYPE FLOAT #
#pragma interface FLOAT
#pragma token TYPE STRING #
#pragma interface STRING
#pragma token TYPE EXP #
#pragma interface EXP
#pragma token TYPE OFFSET #
#pragma interface OFFSET
#pragma token TYPE TOKEN #
#pragma interface TOKEN
#pragma token TYPE INSTANCE #
#pragma interface INSTANCE
#pragma token TYPE ERROR #
#pragma interface ERROR


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

extern void destroy_c_class();
extern void dummy_destroy_c_class();
#ifdef c_class_IO_ROUTINES
extern unsigned crt_c_class_alias;
extern void clear_c_class_alias(void);
#endif


/* Pointer token specifications */

#pragma token PROC {\
	TYPE t, EXP : PTR(t) : e1, EXP : SIZE(t) : e2 |\
	EXP e1, EXP e2\
    } EXP : PTR(t) : STEP_ptr #

#pragma token PROC(\
	TYPE t\
    ) EXP const : PTR(t) : NULL_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR(t) : e |\
	EXP e\
    } EXP : int : IS_NULL_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR(t) : e1, EXP : PTR(t) : e2 |\
	EXP e1, EXP e2\
    } EXP : int : EQ_ptr #

#pragma token PROC {\
	TYPE t, EXP : SIZE(t) : e |\
	EXP e\
    } EXP : PTR(t) : MAKE_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR(t) : e1, EXP : SIZE(t) : e2 |\
	EXP e1, EXP e2\
    } EXP : void : DESTROY_ptr #

#pragma token PROC(\
	TYPE t\
    ) EXP : PTR(t) : UNIQ_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR(t) : e |\
	EXP e\
    } EXP : void : DESTROY_UNIQ_ptr #

#pragma interface STEP_ptr NULL_ptr IS_NULL_ptr EQ_ptr
#pragma interface MAKE_ptr DESTROY_ptr

#ifdef c_class_IO_ROUTINES
#pragma token PROC {\
	TYPE t, EXP : PTR(t) : e |\
	EXP e\
    } EXP : void * : VOIDSTAR_ptr #
#pragma interface VOIDSTAR_ptr
#endif

#pragma token PROC(\
	TYPE t\
    ) EXP const : SIZE(PTR(t)) : SIZE_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR(PTR(t)) : e1,\
	EXP : PTR(t) : e2 |\
	EXP e1, EXP e2\
    } EXP : void : COPY_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR(PTR(t)) : e |\
	EXP e\
    } EXP : PTR(t) : DEREF_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR(t) : e2,\
	EXP : LIST(PTR(t)) : e3,\
	EXP lvalue : LIST(PTR(t)) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT CONS_ptr #

#pragma token PROC {\
	TYPE t, EXP lvalue : PTR(t) : e2,\
	EXP lvalue : LIST(PTR(t)) : e3,\
	EXP : LIST(PTR(t)) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT UN_CONS_ptr #

#pragma token PROC {\
	TYPE t, EXP : DESTROYER : e1,\
	EXP lvalue : PTR(t) : e2,\
	EXP lvalue : LIST(PTR(t)) : e3,\
	EXP : LIST(PTR(t)) : e4 |\
	EXP e1, EXP e2, EXP e3, EXP e4\
    } STATEMENT DESTROY_CONS_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR(t) : e2,\
	EXP lvalue : STACK(PTR(t)) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT PUSH_ptr #

#pragma token PROC {\
	TYPE t, EXP lvalue : PTR(t) : e2,\
	EXP lvalue : STACK(PTR(t)) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT POP_ptr #

#pragma interface SIZE_ptr COPY_ptr DEREF_ptr
#pragma interface CONS_ptr UN_CONS_ptr DESTROY_CONS_ptr
#pragma interface PUSH_ptr POP_ptr


/* List token specifications */

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e |\
	EXP e\
    } EXP : PTR(t) : HEAD_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e |\
	EXP e\
    } EXP : PTR(LIST(t)) : PTR_TAIL_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e |\
	EXP e\
    } EXP : LIST(t) : TAIL_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e1 |\
	EXP e1\
    } EXP : unsigned : LENGTH_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e1 |\
	EXP e1\
    } EXP : LIST(t) : END_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e1 |\
	EXP e1\
    } EXP : LIST(t) : REVERSE_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e1, EXP : LIST(t) : e2 |\
	EXP e1, EXP e2\
    } EXP : LIST(t) : APPEND_list #

#pragma token PROC(\
	TYPE t\
    ) EXP const : LIST(t) : NULL_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e |\
	EXP e\
    } EXP : int : IS_NULL_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e1, EXP : LIST(t) : e2 |\
	EXP e1, EXP e2\
    } EXP : int : EQ_list #

#pragma token PROC(\
	TYPE t\
    ) EXP : LIST(t) : UNIQ_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e |\
	EXP e\
    } EXP : void : DESTROY_UNIQ_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e1, EXP : SIZE(t) : e2 |\
	EXP e1, EXP e2\
    } STATEMENT DESTROY_list #

#pragma interface HEAD_list PTR_TAIL_list TAIL_list
#pragma interface LENGTH_list END_list REVERSE_list APPEND_list
#pragma interface NULL_list IS_NULL_list EQ_list
#pragma interface UNIQ_list DESTROY_UNIQ_list DESTROY_list

#ifdef c_class_IO_ROUTINES
#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e |\
	EXP e\
    } EXP : void * : VOIDSTAR_list #
#pragma interface VOIDSTAR_list
#endif

#pragma token PROC(\
	TYPE t\
    ) EXP const : SIZE(LIST(t)) : SIZE_list #

#pragma token PROC {\
	TYPE t, EXP : PTR(LIST(t)) : e1,\
	EXP : LIST(t) : e2 |\
	EXP e1, EXP e2\
    } EXP : void : COPY_list #

#pragma token PROC {\
	TYPE t, EXP : PTR(LIST(t)) : e |\
	EXP e\
    } EXP : LIST(t) : DEREF_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e2,\
	EXP : LIST(LIST(t)) : e3,\
	EXP lvalue : LIST(LIST(t)) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT CONS_list #

#pragma token PROC {\
	TYPE t, EXP lvalue : LIST(t) : e2,\
	EXP lvalue : LIST(LIST(t)) : e3,\
	EXP : LIST(LIST(t)) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT UN_CONS_list #

#pragma token PROC {\
	TYPE t, EXP : DESTROYER : e1,\
	EXP lvalue : LIST(t) : e2,\
	EXP lvalue : LIST(LIST(t)) : e3,\
	EXP : LIST(LIST(t)) : e4 |\
	EXP e1, EXP e2, EXP e3, EXP e4\
    } STATEMENT DESTROY_CONS_list #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e2,\
	EXP lvalue : STACK(LIST(t)) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT PUSH_list #

#pragma token PROC {\
	TYPE t, EXP lvalue : LIST(t) : e2,\
	EXP lvalue : STACK(LIST(t)) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT POP_list #

#pragma interface SIZE_list COPY_list DEREF_list
#pragma interface CONS_list UN_CONS_list DESTROY_CONS_list
#pragma interface PUSH_list POP_list


/* Stack token specifications */

#pragma token PROC(\
	TYPE t\
    ) EXP const : STACK(t) : NULL_stack #

#pragma token PROC {\
	TYPE t, EXP : STACK(t) : e |\
	EXP e\
    } EXP : int : IS_NULL_stack #

#pragma token PROC {\
	TYPE t, EXP : STACK(t) : e1 |\
	EXP e1\
    } EXP : LIST(t) : LIST_stack #

#pragma token PROC {\
	TYPE t, EXP : LIST(t) : e1 |\
	EXP e1\
    } EXP : STACK(t) : STACK_list #

#pragma interface NULL_stack IS_NULL_stack LIST_stack STACK_list

#pragma token PROC(\
	TYPE t\
    ) EXP const : SIZE(STACK(t)) : SIZE_stack #

#pragma token PROC {\
	TYPE t, EXP : PTR(STACK(t)) : e1,\
	EXP : STACK(t) : e2 |\
	EXP e1, EXP e2\
    } EXP : void : COPY_stack #

#pragma token PROC {\
	TYPE t, EXP : PTR(STACK(t)) : e |\
	EXP e\
    } EXP : STACK(t) : DEREF_stack #

#pragma token PROC {\
	TYPE t, EXP : STACK(t) : e2,\
	EXP : LIST(STACK(t)) : e3,\
	EXP lvalue : LIST(STACK(t)) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT CONS_stack #

#pragma token PROC {\
	TYPE t, EXP lvalue : STACK(t) : e2,\
	EXP lvalue : LIST(STACK(t)) : e3,\
	EXP : LIST(STACK(t)) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT UN_CONS_stack #

#pragma token PROC {\
	TYPE t, EXP : DESTROYER : e1,\
	EXP lvalue : STACK(t) : e2,\
	EXP lvalue : LIST(STACK(t)) : e3,\
	EXP : LIST(STACK(t)) : e4 |\
	EXP e1, EXP e2, EXP e3, EXP e4\
    } STATEMENT DESTROY_CONS_stack #

#pragma token PROC {\
	TYPE t, EXP : STACK(t) : e2,\
	EXP lvalue : STACK(STACK(t)) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT PUSH_stack #

#pragma token PROC {\
	TYPE t, EXP lvalue : STACK(t) : e2,\
	EXP lvalue : STACK(STACK(t)) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT POP_stack #

#pragma interface SIZE_stack COPY_stack DEREF_stack
#pragma interface CONS_stack UN_CONS_stack DESTROY_CONS_stack
#pragma interface PUSH_stack POP_stack


/* Size token specifications */

#pragma token PROC {\
	TYPE t, VARIETY v,\
	EXP : SIZE(t) : e1, EXP : v : e2 |\
	EXP e1, EXP e2\
    } EXP : SIZE(t) : SCALE #

#pragma interface SCALE


/* Definitions for primitive int */

#pragma token EXP const : SIZE(int) : SIZE_int #

#pragma token PROC(\
	EXP : PTR(int) :,\
	EXP : int :\
    ) EXP : void : COPY_int #

#pragma token PROC(\
	EXP : PTR(int) :\
    ) EXP : int : DEREF_int #

#pragma token PROC(\
	EXP : int :,\
	EXP : LIST(int) :,\
	EXP lvalue : LIST(int) :\
    ) STATEMENT CONS_int #

#pragma token PROC(\
	EXP lvalue : int :,\
	EXP lvalue : LIST(int) :,\
	EXP : LIST(int) :\
    ) STATEMENT UN_CONS_int #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : LIST(int) :,\
	EXP : LIST(int) :\
    ) STATEMENT DESTROY_CONS_int #

#pragma token PROC(\
	EXP : int :,\
	EXP lvalue : STACK(int) :\
    ) STATEMENT PUSH_int #

#pragma token PROC(\
	EXP lvalue : int :,\
	EXP lvalue : STACK(int) :\
    ) STATEMENT POP_int #

#pragma interface SIZE_int COPY_int DEREF_int
#pragma interface CONS_int UN_CONS_int DESTROY_CONS_int
#pragma interface PUSH_int POP_int


/* Definitions for primitive unsigned */

#pragma token EXP const : SIZE(unsigned) : SIZE_unsigned #

#pragma token PROC(\
	EXP : PTR(unsigned) :,\
	EXP : unsigned :\
    ) EXP : void : COPY_unsigned #

#pragma token PROC(\
	EXP : PTR(unsigned) :\
    ) EXP : unsigned : DEREF_unsigned #

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : LIST(unsigned) :,\
	EXP lvalue : LIST(unsigned) :\
    ) STATEMENT CONS_unsigned #

#pragma token PROC(\
	EXP lvalue : unsigned :,\
	EXP lvalue : LIST(unsigned) :,\
	EXP : LIST(unsigned) :\
    ) STATEMENT UN_CONS_unsigned #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : LIST(unsigned) :,\
	EXP : LIST(unsigned) :\
    ) STATEMENT DESTROY_CONS_unsigned #

#pragma token PROC(\
	EXP : unsigned :,\
	EXP lvalue : STACK(unsigned) :\
    ) STATEMENT PUSH_unsigned #

#pragma token PROC(\
	EXP lvalue : unsigned :,\
	EXP lvalue : STACK(unsigned) :\
    ) STATEMENT POP_unsigned #

#pragma interface SIZE_unsigned COPY_unsigned DEREF_unsigned
#pragma interface CONS_unsigned UN_CONS_unsigned DESTROY_CONS_unsigned
#pragma interface PUSH_unsigned POP_unsigned


/* Definitions for primitive string */

#pragma token EXP const : SIZE(string) : SIZE_string #

#pragma token PROC(\
	EXP : PTR(string) :,\
	EXP : string :\
    ) EXP : void : COPY_string #

#pragma token PROC(\
	EXP : PTR(string) :\
    ) EXP : string : DEREF_string #

#pragma token PROC(\
	EXP : string :,\
	EXP : LIST(string) :,\
	EXP lvalue : LIST(string) :\
    ) STATEMENT CONS_string #

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : LIST(string) :,\
	EXP : LIST(string) :\
    ) STATEMENT UN_CONS_string #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : LIST(string) :,\
	EXP : LIST(string) :\
    ) STATEMENT DESTROY_CONS_string #

#pragma token PROC(\
	EXP : string :,\
	EXP lvalue : STACK(string) :\
    ) STATEMENT PUSH_string #

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : STACK(string) :\
    ) STATEMENT POP_string #

#pragma interface SIZE_string COPY_string DEREF_string
#pragma interface CONS_string UN_CONS_string DESTROY_CONS_string
#pragma interface PUSH_string POP_string


/* Definitions for primitive ulong_type */

#pragma token EXP const : SIZE(ulong_type) : SIZE_ulong #

#pragma token PROC(\
	EXP : PTR(ulong_type) :,\
	EXP : ulong_type :\
    ) EXP : void : COPY_ulong #

#pragma token PROC(\
	EXP : PTR(ulong_type) :\
    ) EXP : ulong_type : DEREF_ulong #

#pragma token PROC(\
	EXP : ulong_type :,\
	EXP : LIST(ulong_type) :,\
	EXP lvalue : LIST(ulong_type) :\
    ) STATEMENT CONS_ulong #

#pragma token PROC(\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST(ulong_type) :,\
	EXP : LIST(ulong_type) :\
    ) STATEMENT UN_CONS_ulong #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST(ulong_type) :,\
	EXP : LIST(ulong_type) :\
    ) STATEMENT DESTROY_CONS_ulong #

#pragma token PROC(\
	EXP : ulong_type :,\
	EXP lvalue : STACK(ulong_type) :\
    ) STATEMENT PUSH_ulong #

#pragma token PROC(\
	EXP lvalue : ulong_type :,\
	EXP lvalue : STACK(ulong_type) :\
    ) STATEMENT POP_ulong #

#pragma interface SIZE_ulong COPY_ulong DEREF_ulong
#pragma interface CONS_ulong UN_CONS_ulong DESTROY_CONS_ulong
#pragma interface PUSH_ulong POP_ulong


/* Definitions for primitive BITSTREAM_P */

#pragma token EXP const : SIZE(BITSTREAM_P) : SIZE_bits #

#pragma token PROC(\
	EXP : PTR(BITSTREAM_P) :,\
	EXP : BITSTREAM_P :\
    ) EXP : void : COPY_bits #

#pragma token PROC(\
	EXP : PTR(BITSTREAM_P) :\
    ) EXP : BITSTREAM_P : DEREF_bits #

#pragma token PROC(\
	EXP : BITSTREAM_P :,\
	EXP : LIST(BITSTREAM_P) :,\
	EXP lvalue : LIST(BITSTREAM_P) :\
    ) STATEMENT CONS_bits #

#pragma token PROC(\
	EXP lvalue : BITSTREAM_P :,\
	EXP lvalue : LIST(BITSTREAM_P) :,\
	EXP : LIST(BITSTREAM_P) :\
    ) STATEMENT UN_CONS_bits #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : BITSTREAM_P :,\
	EXP lvalue : LIST(BITSTREAM_P) :,\
	EXP : LIST(BITSTREAM_P) :\
    ) STATEMENT DESTROY_CONS_bits #

#pragma token PROC(\
	EXP : BITSTREAM_P :,\
	EXP lvalue : STACK(BITSTREAM_P) :\
    ) STATEMENT PUSH_bits #

#pragma token PROC(\
	EXP lvalue : BITSTREAM_P :,\
	EXP lvalue : STACK(BITSTREAM_P) :\
    ) STATEMENT POP_bits #

#pragma interface SIZE_bits COPY_bits DEREF_bits
#pragma interface CONS_bits UN_CONS_bits DESTROY_CONS_bits
#pragma interface PUSH_bits POP_bits


/* Definitions for primitive PPTOKEN_P */

#pragma token EXP const : SIZE(PPTOKEN_P) : SIZE_pptok #

#pragma token PROC(\
	EXP : PTR(PPTOKEN_P) :,\
	EXP : PPTOKEN_P :\
    ) EXP : void : COPY_pptok #

#pragma token PROC(\
	EXP : PTR(PPTOKEN_P) :\
    ) EXP : PPTOKEN_P : DEREF_pptok #

#pragma token PROC(\
	EXP : PPTOKEN_P :,\
	EXP : LIST(PPTOKEN_P) :,\
	EXP lvalue : LIST(PPTOKEN_P) :\
    ) STATEMENT CONS_pptok #

#pragma token PROC(\
	EXP lvalue : PPTOKEN_P :,\
	EXP lvalue : LIST(PPTOKEN_P) :,\
	EXP : LIST(PPTOKEN_P) :\
    ) STATEMENT UN_CONS_pptok #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : PPTOKEN_P :,\
	EXP lvalue : LIST(PPTOKEN_P) :,\
	EXP : LIST(PPTOKEN_P) :\
    ) STATEMENT DESTROY_CONS_pptok #

#pragma token PROC(\
	EXP : PPTOKEN_P :,\
	EXP lvalue : STACK(PPTOKEN_P) :\
    ) STATEMENT PUSH_pptok #

#pragma token PROC(\
	EXP lvalue : PPTOKEN_P :,\
	EXP lvalue : STACK(PPTOKEN_P) :\
    ) STATEMENT POP_pptok #

#pragma interface SIZE_pptok COPY_pptok DEREF_pptok
#pragma interface CONS_pptok UN_CONS_pptok DESTROY_CONS_pptok
#pragma interface PUSH_pptok POP_pptok


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
#pragma token EXP const : SIZE(CV_SPEC) : SIZE_cv #

#pragma token PROC(\
	EXP : PTR(CV_SPEC) :,\
	EXP : CV_SPEC :\
    ) EXP : void : COPY_cv #

#pragma token PROC(\
	EXP : PTR(CV_SPEC) :\
    ) EXP : CV_SPEC : DEREF_cv #

#pragma interface SIZE_cv COPY_cv DEREF_cv


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
#pragma token EXP const : SIZE(BUILTIN_TYPE) : SIZE_ntype #

#pragma token PROC(\
	EXP : PTR(BUILTIN_TYPE) :,\
	EXP : BUILTIN_TYPE :\
    ) EXP : void : COPY_ntype #

#pragma token PROC(\
	EXP : PTR(BUILTIN_TYPE) :\
    ) EXP : BUILTIN_TYPE : DEREF_ntype #

#pragma interface SIZE_ntype COPY_ntype DEREF_ntype


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
#pragma token EXP const : SIZE(BASE_TYPE) : SIZE_btype #

#pragma token PROC(\
	EXP : PTR(BASE_TYPE) :,\
	EXP : BASE_TYPE :\
    ) EXP : void : COPY_btype #

#pragma token PROC(\
	EXP : PTR(BASE_TYPE) :\
    ) EXP : BASE_TYPE : DEREF_btype #

#pragma interface SIZE_btype COPY_btype DEREF_btype


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
#pragma token EXP const : SIZE(CLASS_INFO) : SIZE_cinfo #

#pragma token PROC(\
	EXP : PTR(CLASS_INFO) :,\
	EXP : CLASS_INFO :\
    ) EXP : void : COPY_cinfo #

#pragma token PROC(\
	EXP : PTR(CLASS_INFO) :\
    ) EXP : CLASS_INFO : DEREF_cinfo #

#pragma interface SIZE_cinfo COPY_cinfo DEREF_cinfo


/* Definitions for enumeration CLASS_USAGE */

#define cusage_none			((CLASS_USAGE) 0)
#define cusage_address			((CLASS_USAGE) 1)
#define cusage_destr			((CLASS_USAGE) 2)
#define cusage_delete			((CLASS_USAGE) 4)
#define cusage_delete_array		((CLASS_USAGE) 8)
#define ORDER_cusage			((unsigned long) 9)
#pragma token EXP const : SIZE(CLASS_USAGE) : SIZE_cusage #

#pragma token PROC(\
	EXP : PTR(CLASS_USAGE) :,\
	EXP : CLASS_USAGE :\
    ) EXP : void : COPY_cusage #

#pragma token PROC(\
	EXP : PTR(CLASS_USAGE) :\
    ) EXP : CLASS_USAGE : DEREF_cusage #

#pragma interface SIZE_cusage COPY_cusage DEREF_cusage


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
#pragma token EXP const : SIZE(DECL_SPEC) : SIZE_dspec #

#pragma token PROC(\
	EXP : PTR(DECL_SPEC) :,\
	EXP : DECL_SPEC :\
    ) EXP : void : COPY_dspec #

#pragma token PROC(\
	EXP : PTR(DECL_SPEC) :\
    ) EXP : DECL_SPEC : DEREF_dspec #

#pragma token PROC(\
	EXP : DECL_SPEC :,\
	EXP : LIST(DECL_SPEC) :,\
	EXP lvalue : LIST(DECL_SPEC) :\
    ) STATEMENT CONS_dspec #

#pragma token PROC(\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : LIST(DECL_SPEC) :,\
	EXP : LIST(DECL_SPEC) :\
    ) STATEMENT UN_CONS_dspec #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : LIST(DECL_SPEC) :,\
	EXP : LIST(DECL_SPEC) :\
    ) STATEMENT DESTROY_CONS_dspec #

#pragma token PROC(\
	EXP : DECL_SPEC :,\
	EXP lvalue : STACK(DECL_SPEC) :\
    ) STATEMENT PUSH_dspec #

#pragma token PROC(\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : STACK(DECL_SPEC) :\
    ) STATEMENT POP_dspec #

#pragma interface SIZE_dspec COPY_dspec DEREF_dspec
#pragma interface CONS_dspec UN_CONS_dspec DESTROY_CONS_dspec
#pragma interface PUSH_dspec POP_dspec


/* Definitions for enumeration QUALIFIER */

#define qual_none			((QUALIFIER) 0)
#define qual_nested			((QUALIFIER) 1)
#define qual_full			((QUALIFIER) 2)
#define qual_top			((QUALIFIER) 3)
#define qual_mark			((QUALIFIER) 4)
#define qual_explicit			((QUALIFIER) 3)
#define ORDER_qual			((unsigned long) 5)
#pragma token EXP const : SIZE(QUALIFIER) : SIZE_qual #

#pragma token PROC(\
	EXP : PTR(QUALIFIER) :,\
	EXP : QUALIFIER :\
    ) EXP : void : COPY_qual #

#pragma token PROC(\
	EXP : PTR(QUALIFIER) :\
    ) EXP : QUALIFIER : DEREF_qual #

#pragma interface SIZE_qual COPY_qual DEREF_qual


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
#pragma token EXP const : SIZE(NTEST) : SIZE_ntest #

#pragma token PROC(\
	EXP : PTR(NTEST) :,\
	EXP : NTEST :\
    ) EXP : void : COPY_ntest #

#pragma token PROC(\
	EXP : PTR(NTEST) :\
    ) EXP : NTEST : DEREF_ntest #

#pragma interface SIZE_ntest COPY_ntest DEREF_ntest


/* Definitions for enumeration RMODE */

#define rmode_as_state			((RMODE) 0)
#define rmode_to_nearest		((RMODE) 1)
#define rmode_to_larger			((RMODE) 2)
#define rmode_to_smaller		((RMODE) 3)
#define rmode_to_zero			((RMODE) 4)
#define ORDER_rmode			((unsigned long) 5)
#pragma token EXP const : SIZE(RMODE) : SIZE_rmode #

#pragma token PROC(\
	EXP : PTR(RMODE) :,\
	EXP : RMODE :\
    ) EXP : void : COPY_rmode #

#pragma token PROC(\
	EXP : PTR(RMODE) :\
    ) EXP : RMODE : DEREF_rmode #

#pragma interface SIZE_rmode COPY_rmode DEREF_rmode


/* Definitions for structure VARIABLE */

#pragma token PROC(EXP : PTR(VARIABLE) :) EXP : PTR(IDENTIFIER) : var_id #
#pragma interface var_id

#pragma token PROC(EXP : PTR(VARIABLE) :) EXP : PTR(DECL_SPEC) : var_info #
#pragma interface var_info

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : DECL_SPEC :,\
	EXP : PTR(VARIABLE) :\
    ) STATEMENT MAKE_var #
#pragma interface MAKE_var

#pragma token EXP const : SIZE(VARIABLE) : SIZE_var #

#pragma token PROC(\
	EXP : PTR(VARIABLE) :,\
	EXP : VARIABLE :\
    ) STATEMENT COPY_var #

#pragma token PROC(\
	EXP : PTR(VARIABLE) :,\
	EXP lvalue : VARIABLE :\
    ) STATEMENT DEREF_var #

#pragma token PROC(\
	EXP : VARIABLE :,\
	EXP : LIST(VARIABLE) :,\
	EXP lvalue : LIST(VARIABLE) :\
    ) STATEMENT CONS_var #

#pragma token PROC(\
	EXP lvalue : VARIABLE :,\
	EXP lvalue : LIST(VARIABLE) :,\
	EXP : LIST(VARIABLE) :\
    ) STATEMENT UN_CONS_var #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : VARIABLE :,\
	EXP lvalue : LIST(VARIABLE) :,\
	EXP : LIST(VARIABLE) :\
    ) STATEMENT DESTROY_CONS_var #

#pragma token PROC(\
	EXP : VARIABLE :,\
	EXP lvalue : STACK(VARIABLE) :\
    ) STATEMENT PUSH_var #

#pragma token PROC(\
	EXP lvalue : VARIABLE :,\
	EXP lvalue : STACK(VARIABLE) :\
    ) STATEMENT POP_var #

#pragma interface SIZE_var COPY_var DEREF_var
#pragma interface CONS_var UN_CONS_var DESTROY_CONS_var
#pragma interface PUSH_var POP_var


/* Definitions for structure LOCATION */

#pragma token PROC(EXP : PTR(LOCATION) :) EXP : PTR(ulong_type) : loc_line #
#pragma interface loc_line

#pragma token PROC(EXP : PTR(LOCATION) :) EXP : PTR(ulong_type) : loc_column #
#pragma interface loc_column

#pragma token PROC(EXP : PTR(LOCATION) :) EXP : PTR(PTR(POSITION)) : loc_posn #
#pragma interface loc_posn

#pragma token PROC(\
	EXP : ulong_type :,\
	EXP : ulong_type :,\
	EXP : PTR(POSITION) :,\
	EXP : PTR(LOCATION) :\
    ) STATEMENT MAKE_loc #
#pragma interface MAKE_loc

#pragma token EXP const : SIZE(LOCATION) : SIZE_loc #

#pragma token PROC(\
	EXP : PTR(LOCATION) :,\
	EXP : LOCATION :\
    ) STATEMENT COPY_loc #

#pragma token PROC(\
	EXP : PTR(LOCATION) :,\
	EXP lvalue : LOCATION :\
    ) STATEMENT DEREF_loc #

#pragma token PROC(\
	EXP : LOCATION :,\
	EXP : LIST(LOCATION) :,\
	EXP lvalue : LIST(LOCATION) :\
    ) STATEMENT CONS_loc #

#pragma token PROC(\
	EXP lvalue : LOCATION :,\
	EXP lvalue : LIST(LOCATION) :,\
	EXP : LIST(LOCATION) :\
    ) STATEMENT UN_CONS_loc #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : LIST(LOCATION) :,\
	EXP : LIST(LOCATION) :\
    ) STATEMENT DESTROY_CONS_loc #

#pragma token PROC(\
	EXP : LOCATION :,\
	EXP lvalue : STACK(LOCATION) :\
    ) STATEMENT PUSH_loc #

#pragma token PROC(\
	EXP lvalue : LOCATION :,\
	EXP lvalue : STACK(LOCATION) :\
    ) STATEMENT POP_loc #

#pragma interface SIZE_loc COPY_loc DEREF_loc
#pragma interface CONS_loc UN_CONS_loc DESTROY_CONS_loc
#pragma interface PUSH_loc POP_loc


/* Definitions for structure POSITION */

#pragma token PROC(EXP : PTR(POSITION) :) EXP : PTR(string) : posn_file #
#pragma interface posn_file

#pragma token PROC(EXP : PTR(POSITION) :) EXP : PTR(string) : posn_input #
#pragma interface posn_input

#pragma token PROC(EXP : PTR(POSITION) :) EXP : PTR(string) : posn_base #
#pragma interface posn_base

#pragma token PROC(EXP : PTR(POSITION) :) EXP : PTR(string) : posn_dir #
#pragma interface posn_dir

#pragma token PROC(EXP : PTR(POSITION) :) EXP : PTR(ulong_type) : posn_offset #
#pragma interface posn_offset

#pragma token PROC(EXP : PTR(POSITION) :) EXP : PTR(PTR(LOCATION)) : posn_from #
#pragma interface posn_from

#pragma token PROC(EXP : PTR(POSITION) :) EXP : PTR(ulong_type) : posn_datestamp #
#pragma interface posn_datestamp

#pragma token PROC(EXP : PTR(POSITION) :) EXP : PTR(ulong_type) : posn_tok #
#pragma interface posn_tok

#pragma token PROC(\
	EXP : string :,\
	EXP : string :,\
	EXP : string :,\
	EXP : string :,\
	EXP : ulong_type :,\
	EXP : PTR(LOCATION) :,\
	EXP : ulong_type :,\
	EXP : PTR(POSITION) :\
    ) STATEMENT MAKE_posn #
#pragma interface MAKE_posn

#pragma token EXP const : SIZE(POSITION) : SIZE_posn #

#pragma token PROC(\
	EXP : PTR(POSITION) :,\
	EXP : POSITION :\
    ) STATEMENT COPY_posn #

#pragma token PROC(\
	EXP : PTR(POSITION) :,\
	EXP lvalue : POSITION :\
    ) STATEMENT DEREF_posn #

#pragma token PROC(\
	EXP : POSITION :,\
	EXP : LIST(POSITION) :,\
	EXP lvalue : LIST(POSITION) :\
    ) STATEMENT CONS_posn #

#pragma token PROC(\
	EXP lvalue : POSITION :,\
	EXP lvalue : LIST(POSITION) :,\
	EXP : LIST(POSITION) :\
    ) STATEMENT UN_CONS_posn #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : POSITION :,\
	EXP lvalue : LIST(POSITION) :,\
	EXP : LIST(POSITION) :\
    ) STATEMENT DESTROY_CONS_posn #

#pragma token PROC(\
	EXP : POSITION :,\
	EXP lvalue : STACK(POSITION) :\
    ) STATEMENT PUSH_posn #

#pragma token PROC(\
	EXP lvalue : POSITION :,\
	EXP lvalue : STACK(POSITION) :\
    ) STATEMENT POP_posn #

#pragma interface SIZE_posn COPY_posn DEREF_posn
#pragma interface CONS_posn UN_CONS_posn DESTROY_CONS_posn
#pragma interface PUSH_posn POP_posn


/* Definitions for union INT_TYPE */

#define ORDER_itype ((unsigned)6)
#pragma token EXP const : INT_TYPE : NULL_itype #
#pragma token PROC(EXP : INT_TYPE :) EXP : int : IS_NULL_itype #
#pragma token PROC(EXP : INT_TYPE :, EXP : INT_TYPE :) EXP : int : EQ_itype #
#pragma interface NULL_itype IS_NULL_itype EQ_itype

#pragma token EXP const : SIZE(INT_TYPE) : SIZE_itype #

#pragma token PROC(\
	EXP : PTR(INT_TYPE) :,\
	EXP : INT_TYPE :\
    ) EXP : void : COPY_itype #

#pragma token PROC(\
	EXP : PTR(INT_TYPE) :\
    ) EXP : INT_TYPE : DEREF_itype #

#pragma token PROC(\
	EXP : INT_TYPE :,\
	EXP : LIST(INT_TYPE) :,\
	EXP lvalue : LIST(INT_TYPE) :\
    ) STATEMENT CONS_itype #

#pragma token PROC(\
	EXP lvalue : INT_TYPE :,\
	EXP lvalue : LIST(INT_TYPE) :,\
	EXP : LIST(INT_TYPE) :\
    ) STATEMENT UN_CONS_itype #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : INT_TYPE :,\
	EXP lvalue : LIST(INT_TYPE) :,\
	EXP : LIST(INT_TYPE) :\
    ) STATEMENT DESTROY_CONS_itype #

#pragma token PROC(\
	EXP : INT_TYPE :,\
	EXP lvalue : STACK(INT_TYPE) :\
    ) STATEMENT PUSH_itype #

#pragma token PROC(\
	EXP lvalue : INT_TYPE :,\
	EXP lvalue : STACK(INT_TYPE) :\
    ) STATEMENT POP_itype #

#pragma interface SIZE_itype COPY_itype DEREF_itype
#pragma interface CONS_itype UN_CONS_itype DESTROY_CONS_itype
#pragma interface PUSH_itype POP_itype


/* Definitions for union FLOAT_TYPE */

#define ORDER_ftype ((unsigned)4)
#pragma token EXP const : FLOAT_TYPE : NULL_ftype #
#pragma token PROC(EXP : FLOAT_TYPE :) EXP : int : IS_NULL_ftype #
#pragma token PROC(EXP : FLOAT_TYPE :, EXP : FLOAT_TYPE :) EXP : int : EQ_ftype #
#pragma interface NULL_ftype IS_NULL_ftype EQ_ftype

#pragma token EXP const : SIZE(FLOAT_TYPE) : SIZE_ftype #

#pragma token PROC(\
	EXP : PTR(FLOAT_TYPE) :,\
	EXP : FLOAT_TYPE :\
    ) EXP : void : COPY_ftype #

#pragma token PROC(\
	EXP : PTR(FLOAT_TYPE) :\
    ) EXP : FLOAT_TYPE : DEREF_ftype #

#pragma token PROC(\
	EXP : FLOAT_TYPE :,\
	EXP : LIST(FLOAT_TYPE) :,\
	EXP lvalue : LIST(FLOAT_TYPE) :\
    ) STATEMENT CONS_ftype #

#pragma token PROC(\
	EXP lvalue : FLOAT_TYPE :,\
	EXP lvalue : LIST(FLOAT_TYPE) :,\
	EXP : LIST(FLOAT_TYPE) :\
    ) STATEMENT UN_CONS_ftype #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : FLOAT_TYPE :,\
	EXP lvalue : LIST(FLOAT_TYPE) :,\
	EXP : LIST(FLOAT_TYPE) :\
    ) STATEMENT DESTROY_CONS_ftype #

#pragma token PROC(\
	EXP : FLOAT_TYPE :,\
	EXP lvalue : STACK(FLOAT_TYPE) :\
    ) STATEMENT PUSH_ftype #

#pragma token PROC(\
	EXP lvalue : FLOAT_TYPE :,\
	EXP lvalue : STACK(FLOAT_TYPE) :\
    ) STATEMENT POP_ftype #

#pragma interface SIZE_ftype COPY_ftype DEREF_ftype
#pragma interface CONS_ftype UN_CONS_ftype DESTROY_CONS_ftype
#pragma interface PUSH_ftype POP_ftype


/* Definitions for union CLASS_TYPE */

#define ORDER_ctype ((unsigned)1)
#pragma token EXP const : CLASS_TYPE : NULL_ctype #
#pragma token PROC(EXP : CLASS_TYPE :) EXP : int : IS_NULL_ctype #
#pragma token PROC(EXP : CLASS_TYPE :, EXP : CLASS_TYPE :) EXP : int : EQ_ctype #
#pragma interface NULL_ctype IS_NULL_ctype EQ_ctype

#pragma token EXP const : SIZE(CLASS_TYPE) : SIZE_ctype #

#pragma token PROC(\
	EXP : PTR(CLASS_TYPE) :,\
	EXP : CLASS_TYPE :\
    ) EXP : void : COPY_ctype #

#pragma token PROC(\
	EXP : PTR(CLASS_TYPE) :\
    ) EXP : CLASS_TYPE : DEREF_ctype #

#pragma token PROC(\
	EXP : CLASS_TYPE :,\
	EXP : LIST(CLASS_TYPE) :,\
	EXP lvalue : LIST(CLASS_TYPE) :\
    ) STATEMENT CONS_ctype #

#pragma token PROC(\
	EXP lvalue : CLASS_TYPE :,\
	EXP lvalue : LIST(CLASS_TYPE) :,\
	EXP : LIST(CLASS_TYPE) :\
    ) STATEMENT UN_CONS_ctype #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CLASS_TYPE :,\
	EXP lvalue : LIST(CLASS_TYPE) :,\
	EXP : LIST(CLASS_TYPE) :\
    ) STATEMENT DESTROY_CONS_ctype #

#pragma token PROC(\
	EXP : CLASS_TYPE :,\
	EXP lvalue : STACK(CLASS_TYPE) :\
    ) STATEMENT PUSH_ctype #

#pragma token PROC(\
	EXP lvalue : CLASS_TYPE :,\
	EXP lvalue : STACK(CLASS_TYPE) :\
    ) STATEMENT POP_ctype #

#pragma interface SIZE_ctype COPY_ctype DEREF_ctype
#pragma interface CONS_ctype UN_CONS_ctype DESTROY_CONS_ctype
#pragma interface PUSH_ctype POP_ctype


/* Definitions for union GRAPH */

#define ORDER_graph ((unsigned)1)
#pragma token EXP const : GRAPH : NULL_graph #
#pragma token PROC(EXP : GRAPH :) EXP : int : IS_NULL_graph #
#pragma token PROC(EXP : GRAPH :, EXP : GRAPH :) EXP : int : EQ_graph #
#pragma interface NULL_graph IS_NULL_graph EQ_graph

#pragma token EXP const : SIZE(GRAPH) : SIZE_graph #

#pragma token PROC(\
	EXP : PTR(GRAPH) :,\
	EXP : GRAPH :\
    ) EXP : void : COPY_graph #

#pragma token PROC(\
	EXP : PTR(GRAPH) :\
    ) EXP : GRAPH : DEREF_graph #

#pragma token PROC(\
	EXP : GRAPH :,\
	EXP : LIST(GRAPH) :,\
	EXP lvalue : LIST(GRAPH) :\
    ) STATEMENT CONS_graph #

#pragma token PROC(\
	EXP lvalue : GRAPH :,\
	EXP lvalue : LIST(GRAPH) :,\
	EXP : LIST(GRAPH) :\
    ) STATEMENT UN_CONS_graph #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : LIST(GRAPH) :,\
	EXP : LIST(GRAPH) :\
    ) STATEMENT DESTROY_CONS_graph #

#pragma token PROC(\
	EXP : GRAPH :,\
	EXP lvalue : STACK(GRAPH) :\
    ) STATEMENT PUSH_graph #

#pragma token PROC(\
	EXP lvalue : GRAPH :,\
	EXP lvalue : STACK(GRAPH) :\
    ) STATEMENT POP_graph #

#pragma interface SIZE_graph COPY_graph DEREF_graph
#pragma interface CONS_graph UN_CONS_graph DESTROY_CONS_graph
#pragma interface PUSH_graph POP_graph


/* Definitions for union VIRTUAL */

#define ORDER_virt ((unsigned)6)
#pragma token EXP const : VIRTUAL : NULL_virt #
#pragma token PROC(EXP : VIRTUAL :) EXP : int : IS_NULL_virt #
#pragma token PROC(EXP : VIRTUAL :, EXP : VIRTUAL :) EXP : int : EQ_virt #
#pragma interface NULL_virt IS_NULL_virt EQ_virt

#pragma token EXP const : SIZE(VIRTUAL) : SIZE_virt #

#pragma token PROC(\
	EXP : PTR(VIRTUAL) :,\
	EXP : VIRTUAL :\
    ) EXP : void : COPY_virt #

#pragma token PROC(\
	EXP : PTR(VIRTUAL) :\
    ) EXP : VIRTUAL : DEREF_virt #

#pragma token PROC(\
	EXP : VIRTUAL :,\
	EXP : LIST(VIRTUAL) :,\
	EXP lvalue : LIST(VIRTUAL) :\
    ) STATEMENT CONS_virt #

#pragma token PROC(\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : LIST(VIRTUAL) :,\
	EXP : LIST(VIRTUAL) :\
    ) STATEMENT UN_CONS_virt #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : LIST(VIRTUAL) :,\
	EXP : LIST(VIRTUAL) :\
    ) STATEMENT DESTROY_CONS_virt #

#pragma token PROC(\
	EXP : VIRTUAL :,\
	EXP lvalue : STACK(VIRTUAL) :\
    ) STATEMENT PUSH_virt #

#pragma token PROC(\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : STACK(VIRTUAL) :\
    ) STATEMENT POP_virt #

#pragma interface SIZE_virt COPY_virt DEREF_virt
#pragma interface CONS_virt UN_CONS_virt DESTROY_CONS_virt
#pragma interface PUSH_virt POP_virt


/* Definitions for union ENUM_TYPE */

#define ORDER_etype ((unsigned)1)
#pragma token EXP const : ENUM_TYPE : NULL_etype #
#pragma token PROC(EXP : ENUM_TYPE :) EXP : int : IS_NULL_etype #
#pragma token PROC(EXP : ENUM_TYPE :, EXP : ENUM_TYPE :) EXP : int : EQ_etype #
#pragma interface NULL_etype IS_NULL_etype EQ_etype

#pragma token EXP const : SIZE(ENUM_TYPE) : SIZE_etype #

#pragma token PROC(\
	EXP : PTR(ENUM_TYPE) :,\
	EXP : ENUM_TYPE :\
    ) EXP : void : COPY_etype #

#pragma token PROC(\
	EXP : PTR(ENUM_TYPE) :\
    ) EXP : ENUM_TYPE : DEREF_etype #

#pragma token PROC(\
	EXP : ENUM_TYPE :,\
	EXP : LIST(ENUM_TYPE) :,\
	EXP lvalue : LIST(ENUM_TYPE) :\
    ) STATEMENT CONS_etype #

#pragma token PROC(\
	EXP lvalue : ENUM_TYPE :,\
	EXP lvalue : LIST(ENUM_TYPE) :,\
	EXP : LIST(ENUM_TYPE) :\
    ) STATEMENT UN_CONS_etype #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : ENUM_TYPE :,\
	EXP lvalue : LIST(ENUM_TYPE) :,\
	EXP : LIST(ENUM_TYPE) :\
    ) STATEMENT DESTROY_CONS_etype #

#pragma token PROC(\
	EXP : ENUM_TYPE :,\
	EXP lvalue : STACK(ENUM_TYPE) :\
    ) STATEMENT PUSH_etype #

#pragma token PROC(\
	EXP lvalue : ENUM_TYPE :,\
	EXP lvalue : STACK(ENUM_TYPE) :\
    ) STATEMENT POP_etype #

#pragma interface SIZE_etype COPY_etype DEREF_etype
#pragma interface CONS_etype UN_CONS_etype DESTROY_CONS_etype
#pragma interface PUSH_etype POP_etype


/* Definitions for union TYPE */

#define ORDER_type ((unsigned)18)
#pragma token EXP const : TYPE : NULL_type #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_NULL_type #
#pragma token PROC(EXP : TYPE :, EXP : TYPE :) EXP : int : EQ_type #
#pragma interface NULL_type IS_NULL_type EQ_type

#pragma token EXP const : SIZE(TYPE) : SIZE_type #

#pragma token PROC(\
	EXP : PTR(TYPE) :,\
	EXP : TYPE :\
    ) EXP : void : COPY_type #

#pragma token PROC(\
	EXP : PTR(TYPE) :\
    ) EXP : TYPE : DEREF_type #

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LIST(TYPE) :,\
	EXP lvalue : LIST(TYPE) :\
    ) STATEMENT CONS_type #

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP : LIST(TYPE) :\
    ) STATEMENT UN_CONS_type #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP : LIST(TYPE) :\
    ) STATEMENT DESTROY_CONS_type #

#pragma token PROC(\
	EXP : TYPE :,\
	EXP lvalue : STACK(TYPE) :\
    ) STATEMENT PUSH_type #

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : STACK(TYPE) :\
    ) STATEMENT POP_type #

#pragma interface SIZE_type COPY_type DEREF_type
#pragma interface CONS_type UN_CONS_type DESTROY_CONS_type
#pragma interface PUSH_type POP_type


/* Definitions for union HASHID */

#define ORDER_hashid ((unsigned)7)
#pragma token EXP const : HASHID : NULL_hashid #
#pragma token PROC(EXP : HASHID :) EXP : int : IS_NULL_hashid #
#pragma token PROC(EXP : HASHID :, EXP : HASHID :) EXP : int : EQ_hashid #
#pragma interface NULL_hashid IS_NULL_hashid EQ_hashid

#pragma token EXP const : SIZE(HASHID) : SIZE_hashid #

#pragma token PROC(\
	EXP : PTR(HASHID) :,\
	EXP : HASHID :\
    ) EXP : void : COPY_hashid #

#pragma token PROC(\
	EXP : PTR(HASHID) :\
    ) EXP : HASHID : DEREF_hashid #

#pragma token PROC(\
	EXP : HASHID :,\
	EXP : LIST(HASHID) :,\
	EXP lvalue : LIST(HASHID) :\
    ) STATEMENT CONS_hashid #

#pragma token PROC(\
	EXP lvalue : HASHID :,\
	EXP lvalue : LIST(HASHID) :,\
	EXP : LIST(HASHID) :\
    ) STATEMENT UN_CONS_hashid #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : LIST(HASHID) :,\
	EXP : LIST(HASHID) :\
    ) STATEMENT DESTROY_CONS_hashid #

#pragma token PROC(\
	EXP : HASHID :,\
	EXP lvalue : STACK(HASHID) :\
    ) STATEMENT PUSH_hashid #

#pragma token PROC(\
	EXP lvalue : HASHID :,\
	EXP lvalue : STACK(HASHID) :\
    ) STATEMENT POP_hashid #

#pragma interface SIZE_hashid COPY_hashid DEREF_hashid
#pragma interface CONS_hashid UN_CONS_hashid DESTROY_CONS_hashid
#pragma interface PUSH_hashid POP_hashid


/* Definitions for union IDENTIFIER */

#define ORDER_id ((unsigned)29)
#pragma token EXP const : IDENTIFIER : NULL_id #
#pragma token PROC(EXP : IDENTIFIER :) EXP : int : IS_NULL_id #
#pragma token PROC(EXP : IDENTIFIER :, EXP : IDENTIFIER :) EXP : int : EQ_id #
#pragma interface NULL_id IS_NULL_id EQ_id

#pragma token EXP const : SIZE(IDENTIFIER) : SIZE_id #

#pragma token PROC(\
	EXP : PTR(IDENTIFIER) :,\
	EXP : IDENTIFIER :\
    ) EXP : void : COPY_id #

#pragma token PROC(\
	EXP : PTR(IDENTIFIER) :\
    ) EXP : IDENTIFIER : DEREF_id #

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(IDENTIFIER) :\
    ) STATEMENT CONS_id #

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP : LIST(IDENTIFIER) :\
    ) STATEMENT UN_CONS_id #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP : LIST(IDENTIFIER) :\
    ) STATEMENT DESTROY_CONS_id #

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP lvalue : STACK(IDENTIFIER) :\
    ) STATEMENT PUSH_id #

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : STACK(IDENTIFIER) :\
    ) STATEMENT POP_id #

#pragma interface SIZE_id COPY_id DEREF_id
#pragma interface CONS_id UN_CONS_id DESTROY_CONS_id
#pragma interface PUSH_id POP_id


/* Definitions for union MEMBER */

#define ORDER_member ((unsigned)2)
#pragma token EXP const : MEMBER : NULL_member #
#pragma token PROC(EXP : MEMBER :) EXP : int : IS_NULL_member #
#pragma token PROC(EXP : MEMBER :, EXP : MEMBER :) EXP : int : EQ_member #
#pragma interface NULL_member IS_NULL_member EQ_member

#pragma token EXP const : SIZE(MEMBER) : SIZE_member #

#pragma token PROC(\
	EXP : PTR(MEMBER) :,\
	EXP : MEMBER :\
    ) EXP : void : COPY_member #

#pragma token PROC(\
	EXP : PTR(MEMBER) :\
    ) EXP : MEMBER : DEREF_member #

#pragma token PROC(\
	EXP : MEMBER :,\
	EXP : LIST(MEMBER) :,\
	EXP lvalue : LIST(MEMBER) :\
    ) STATEMENT CONS_member #

#pragma token PROC(\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(MEMBER) :,\
	EXP : LIST(MEMBER) :\
    ) STATEMENT UN_CONS_member #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(MEMBER) :,\
	EXP : LIST(MEMBER) :\
    ) STATEMENT DESTROY_CONS_member #

#pragma token PROC(\
	EXP : MEMBER :,\
	EXP lvalue : STACK(MEMBER) :\
    ) STATEMENT PUSH_member #

#pragma token PROC(\
	EXP lvalue : MEMBER :,\
	EXP lvalue : STACK(MEMBER) :\
    ) STATEMENT POP_member #

#pragma interface SIZE_member COPY_member DEREF_member
#pragma interface CONS_member UN_CONS_member DESTROY_CONS_member
#pragma interface PUSH_member POP_member


/* Definitions for union NAMESPACE */

#define ORDER_nspace ((unsigned)9)
#pragma token EXP const : NAMESPACE : NULL_nspace #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_NULL_nspace #
#pragma token PROC(EXP : NAMESPACE :, EXP : NAMESPACE :) EXP : int : EQ_nspace #
#pragma interface NULL_nspace IS_NULL_nspace EQ_nspace

#pragma token EXP const : SIZE(NAMESPACE) : SIZE_nspace #

#pragma token PROC(\
	EXP : PTR(NAMESPACE) :,\
	EXP : NAMESPACE :\
    ) EXP : void : COPY_nspace #

#pragma token PROC(\
	EXP : PTR(NAMESPACE) :\
    ) EXP : NAMESPACE : DEREF_nspace #

#pragma token PROC(\
	EXP : NAMESPACE :,\
	EXP : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :\
    ) STATEMENT CONS_nspace #

#pragma token PROC(\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP : LIST(NAMESPACE) :\
    ) STATEMENT UN_CONS_nspace #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP : LIST(NAMESPACE) :\
    ) STATEMENT DESTROY_CONS_nspace #

#pragma token PROC(\
	EXP : NAMESPACE :,\
	EXP lvalue : STACK(NAMESPACE) :\
    ) STATEMENT PUSH_nspace #

#pragma token PROC(\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : STACK(NAMESPACE) :\
    ) STATEMENT POP_nspace #

#pragma interface SIZE_nspace COPY_nspace DEREF_nspace
#pragma interface CONS_nspace UN_CONS_nspace DESTROY_CONS_nspace
#pragma interface PUSH_nspace POP_nspace


/* Definitions for union NAT */

#define ORDER_nat ((unsigned)5)
#pragma token EXP const : NAT : NULL_nat #
#pragma token PROC(EXP : NAT :) EXP : int : IS_NULL_nat #
#pragma token PROC(EXP : NAT :, EXP : NAT :) EXP : int : EQ_nat #
#pragma interface NULL_nat IS_NULL_nat EQ_nat

#pragma token EXP const : SIZE(NAT) : SIZE_nat #

#pragma token PROC(\
	EXP : PTR(NAT) :,\
	EXP : NAT :\
    ) EXP : void : COPY_nat #

#pragma token PROC(\
	EXP : PTR(NAT) :\
    ) EXP : NAT : DEREF_nat #

#pragma token PROC(\
	EXP : NAT :,\
	EXP : LIST(NAT) :,\
	EXP lvalue : LIST(NAT) :\
    ) STATEMENT CONS_nat #

#pragma token PROC(\
	EXP lvalue : NAT :,\
	EXP lvalue : LIST(NAT) :,\
	EXP : LIST(NAT) :\
    ) STATEMENT UN_CONS_nat #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : NAT :,\
	EXP lvalue : LIST(NAT) :,\
	EXP : LIST(NAT) :\
    ) STATEMENT DESTROY_CONS_nat #

#pragma token PROC(\
	EXP : NAT :,\
	EXP lvalue : STACK(NAT) :\
    ) STATEMENT PUSH_nat #

#pragma token PROC(\
	EXP lvalue : NAT :,\
	EXP lvalue : STACK(NAT) :\
    ) STATEMENT POP_nat #

#pragma interface SIZE_nat COPY_nat DEREF_nat
#pragma interface CONS_nat UN_CONS_nat DESTROY_CONS_nat
#pragma interface PUSH_nat POP_nat


/* Definitions for union FLOAT */

#define ORDER_flt ((unsigned)1)
#pragma token EXP const : FLOAT : NULL_flt #
#pragma token PROC(EXP : FLOAT :) EXP : int : IS_NULL_flt #
#pragma token PROC(EXP : FLOAT :, EXP : FLOAT :) EXP : int : EQ_flt #
#pragma interface NULL_flt IS_NULL_flt EQ_flt

#pragma token EXP const : SIZE(FLOAT) : SIZE_flt #

#pragma token PROC(\
	EXP : PTR(FLOAT) :,\
	EXP : FLOAT :\
    ) EXP : void : COPY_flt #

#pragma token PROC(\
	EXP : PTR(FLOAT) :\
    ) EXP : FLOAT : DEREF_flt #

#pragma token PROC(\
	EXP : FLOAT :,\
	EXP : LIST(FLOAT) :,\
	EXP lvalue : LIST(FLOAT) :\
    ) STATEMENT CONS_flt #

#pragma token PROC(\
	EXP lvalue : FLOAT :,\
	EXP lvalue : LIST(FLOAT) :,\
	EXP : LIST(FLOAT) :\
    ) STATEMENT UN_CONS_flt #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : FLOAT :,\
	EXP lvalue : LIST(FLOAT) :,\
	EXP : LIST(FLOAT) :\
    ) STATEMENT DESTROY_CONS_flt #

#pragma token PROC(\
	EXP : FLOAT :,\
	EXP lvalue : STACK(FLOAT) :\
    ) STATEMENT PUSH_flt #

#pragma token PROC(\
	EXP lvalue : FLOAT :,\
	EXP lvalue : STACK(FLOAT) :\
    ) STATEMENT POP_flt #

#pragma interface SIZE_flt COPY_flt DEREF_flt
#pragma interface CONS_flt UN_CONS_flt DESTROY_CONS_flt
#pragma interface PUSH_flt POP_flt


/* Definitions for union STRING */

#define ORDER_str ((unsigned)1)
#pragma token EXP const : STRING : NULL_str #
#pragma token PROC(EXP : STRING :) EXP : int : IS_NULL_str #
#pragma token PROC(EXP : STRING :, EXP : STRING :) EXP : int : EQ_str #
#pragma interface NULL_str IS_NULL_str EQ_str

#pragma token EXP const : SIZE(STRING) : SIZE_str #

#pragma token PROC(\
	EXP : PTR(STRING) :,\
	EXP : STRING :\
    ) EXP : void : COPY_str #

#pragma token PROC(\
	EXP : PTR(STRING) :\
    ) EXP : STRING : DEREF_str #

#pragma token PROC(\
	EXP : STRING :,\
	EXP : LIST(STRING) :,\
	EXP lvalue : LIST(STRING) :\
    ) STATEMENT CONS_str #

#pragma token PROC(\
	EXP lvalue : STRING :,\
	EXP lvalue : LIST(STRING) :,\
	EXP : LIST(STRING) :\
    ) STATEMENT UN_CONS_str #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : STRING :,\
	EXP lvalue : LIST(STRING) :,\
	EXP : LIST(STRING) :\
    ) STATEMENT DESTROY_CONS_str #

#pragma token PROC(\
	EXP : STRING :,\
	EXP lvalue : STACK(STRING) :\
    ) STATEMENT PUSH_str #

#pragma token PROC(\
	EXP lvalue : STRING :,\
	EXP lvalue : STACK(STRING) :\
    ) STATEMENT POP_str #

#pragma interface SIZE_str COPY_str DEREF_str
#pragma interface CONS_str UN_CONS_str DESTROY_CONS_str
#pragma interface PUSH_str POP_str


/* Definitions for union EXP */

#define ORDER_exp ((unsigned)88)
#pragma token EXP const : EXP : NULL_exp #
#pragma token PROC(EXP : EXP :) EXP : int : IS_NULL_exp #
#pragma token PROC(EXP : EXP :, EXP : EXP :) EXP : int : EQ_exp #
#pragma interface NULL_exp IS_NULL_exp EQ_exp

#pragma token EXP const : SIZE(EXP) : SIZE_exp #

#pragma token PROC(\
	EXP : PTR(EXP) :,\
	EXP : EXP :\
    ) EXP : void : COPY_exp #

#pragma token PROC(\
	EXP : PTR(EXP) :\
    ) EXP : EXP : DEREF_exp #

#pragma token PROC(\
	EXP : EXP :,\
	EXP : LIST(EXP) :,\
	EXP lvalue : LIST(EXP) :\
    ) STATEMENT CONS_exp #

#pragma token PROC(\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(EXP) :,\
	EXP : LIST(EXP) :\
    ) STATEMENT UN_CONS_exp #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(EXP) :,\
	EXP : LIST(EXP) :\
    ) STATEMENT DESTROY_CONS_exp #

#pragma token PROC(\
	EXP : EXP :,\
	EXP lvalue : STACK(EXP) :\
    ) STATEMENT PUSH_exp #

#pragma token PROC(\
	EXP lvalue : EXP :,\
	EXP lvalue : STACK(EXP) :\
    ) STATEMENT POP_exp #

#pragma interface SIZE_exp COPY_exp DEREF_exp
#pragma interface CONS_exp UN_CONS_exp DESTROY_CONS_exp
#pragma interface PUSH_exp POP_exp


/* Definitions for union OFFSET */

#define ORDER_off ((unsigned)13)
#pragma token EXP const : OFFSET : NULL_off #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_NULL_off #
#pragma token PROC(EXP : OFFSET :, EXP : OFFSET :) EXP : int : EQ_off #
#pragma interface NULL_off IS_NULL_off EQ_off

#pragma token EXP const : SIZE(OFFSET) : SIZE_off #

#pragma token PROC(\
	EXP : PTR(OFFSET) :,\
	EXP : OFFSET :\
    ) EXP : void : COPY_off #

#pragma token PROC(\
	EXP : PTR(OFFSET) :\
    ) EXP : OFFSET : DEREF_off #

#pragma token PROC(\
	EXP : OFFSET :,\
	EXP : LIST(OFFSET) :,\
	EXP lvalue : LIST(OFFSET) :\
    ) STATEMENT CONS_off #

#pragma token PROC(\
	EXP lvalue : OFFSET :,\
	EXP lvalue : LIST(OFFSET) :,\
	EXP : LIST(OFFSET) :\
    ) STATEMENT UN_CONS_off #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : LIST(OFFSET) :,\
	EXP : LIST(OFFSET) :\
    ) STATEMENT DESTROY_CONS_off #

#pragma token PROC(\
	EXP : OFFSET :,\
	EXP lvalue : STACK(OFFSET) :\
    ) STATEMENT PUSH_off #

#pragma token PROC(\
	EXP lvalue : OFFSET :,\
	EXP lvalue : STACK(OFFSET) :\
    ) STATEMENT POP_off #

#pragma interface SIZE_off COPY_off DEREF_off
#pragma interface CONS_off UN_CONS_off DESTROY_CONS_off
#pragma interface PUSH_off POP_off


/* Definitions for union TOKEN */

#define ORDER_tok ((unsigned)10)
#pragma token EXP const : TOKEN : NULL_tok #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_NULL_tok #
#pragma token PROC(EXP : TOKEN :, EXP : TOKEN :) EXP : int : EQ_tok #
#pragma interface NULL_tok IS_NULL_tok EQ_tok

#pragma token EXP const : SIZE(TOKEN) : SIZE_tok #

#pragma token PROC(\
	EXP : PTR(TOKEN) :,\
	EXP : TOKEN :\
    ) EXP : void : COPY_tok #

#pragma token PROC(\
	EXP : PTR(TOKEN) :\
    ) EXP : TOKEN : DEREF_tok #

#pragma token PROC(\
	EXP : TOKEN :,\
	EXP : LIST(TOKEN) :,\
	EXP lvalue : LIST(TOKEN) :\
    ) STATEMENT CONS_tok #

#pragma token PROC(\
	EXP lvalue : TOKEN :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : LIST(TOKEN) :\
    ) STATEMENT UN_CONS_tok #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TOKEN :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : LIST(TOKEN) :\
    ) STATEMENT DESTROY_CONS_tok #

#pragma token PROC(\
	EXP : TOKEN :,\
	EXP lvalue : STACK(TOKEN) :\
    ) STATEMENT PUSH_tok #

#pragma token PROC(\
	EXP lvalue : TOKEN :,\
	EXP lvalue : STACK(TOKEN) :\
    ) STATEMENT POP_tok #

#pragma interface SIZE_tok COPY_tok DEREF_tok
#pragma interface CONS_tok UN_CONS_tok DESTROY_CONS_tok
#pragma interface PUSH_tok POP_tok


/* Definitions for union INSTANCE */

#define ORDER_inst ((unsigned)2)
#pragma token EXP const : INSTANCE : NULL_inst #
#pragma token PROC(EXP : INSTANCE :) EXP : int : IS_NULL_inst #
#pragma token PROC(EXP : INSTANCE :, EXP : INSTANCE :) EXP : int : EQ_inst #
#pragma interface NULL_inst IS_NULL_inst EQ_inst

#pragma token EXP const : SIZE(INSTANCE) : SIZE_inst #

#pragma token PROC(\
	EXP : PTR(INSTANCE) :,\
	EXP : INSTANCE :\
    ) EXP : void : COPY_inst #

#pragma token PROC(\
	EXP : PTR(INSTANCE) :\
    ) EXP : INSTANCE : DEREF_inst #

#pragma token PROC(\
	EXP : INSTANCE :,\
	EXP : LIST(INSTANCE) :,\
	EXP lvalue : LIST(INSTANCE) :\
    ) STATEMENT CONS_inst #

#pragma token PROC(\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : LIST(INSTANCE) :,\
	EXP : LIST(INSTANCE) :\
    ) STATEMENT UN_CONS_inst #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : LIST(INSTANCE) :,\
	EXP : LIST(INSTANCE) :\
    ) STATEMENT DESTROY_CONS_inst #

#pragma token PROC(\
	EXP : INSTANCE :,\
	EXP lvalue : STACK(INSTANCE) :\
    ) STATEMENT PUSH_inst #

#pragma token PROC(\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : STACK(INSTANCE) :\
    ) STATEMENT POP_inst #

#pragma interface SIZE_inst COPY_inst DEREF_inst
#pragma interface CONS_inst UN_CONS_inst DESTROY_CONS_inst
#pragma interface PUSH_inst POP_inst


/* Definitions for union ERROR */

#define ORDER_err ((unsigned)2)
#pragma token EXP const : ERROR : NULL_err #
#pragma token PROC(EXP : ERROR :) EXP : int : IS_NULL_err #
#pragma token PROC(EXP : ERROR :, EXP : ERROR :) EXP : int : EQ_err #
#pragma interface NULL_err IS_NULL_err EQ_err

#pragma token EXP const : SIZE(ERROR) : SIZE_err #

#pragma token PROC(\
	EXP : PTR(ERROR) :,\
	EXP : ERROR :\
    ) EXP : void : COPY_err #

#pragma token PROC(\
	EXP : PTR(ERROR) :\
    ) EXP : ERROR : DEREF_err #

#pragma token PROC(\
	EXP : ERROR :,\
	EXP : LIST(ERROR) :,\
	EXP lvalue : LIST(ERROR) :\
    ) STATEMENT CONS_err #

#pragma token PROC(\
	EXP lvalue : ERROR :,\
	EXP lvalue : LIST(ERROR) :,\
	EXP : LIST(ERROR) :\
    ) STATEMENT UN_CONS_err #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : ERROR :,\
	EXP lvalue : LIST(ERROR) :,\
	EXP : LIST(ERROR) :\
    ) STATEMENT DESTROY_CONS_err #

#pragma token PROC(\
	EXP : ERROR :,\
	EXP lvalue : STACK(ERROR) :\
    ) STATEMENT PUSH_err #

#pragma token PROC(\
	EXP lvalue : ERROR :,\
	EXP lvalue : STACK(ERROR) :\
    ) STATEMENT POP_err #

#pragma interface SIZE_err COPY_err DEREF_err
#pragma interface CONS_err UN_CONS_err DESTROY_CONS_err
#pragma interface PUSH_err POP_err


#endif
