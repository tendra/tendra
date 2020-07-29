/*
    AUTOMATICALLY GENERATED FROM ALGEBRA calculus (VERSION 1.2)
    BY calculus (VERSION 1.3)
*/

#ifndef CALCULUS_H_TOK_INCLUDED
#define CALCULUS_H_TOK_INCLUDED

#ifndef calculus_NAME
#define calculus_NAME			"calculus"
#define calculus_VERSION		"1.2"
#define calculus_SPECIFICATION		1
#define calculus_IMPLEMENTATION		0
#endif


/* Prototype macros */



/* Primitive types */

typedef unsigned long number;
typedef char * string;


/* Basic types */

#ifndef calculus_DESTR_DEFINED
#define calculus_DESTR_DEFINED
typedef void (*DESTROYER)();
#endif

#pragma token PROC(TYPE) TYPE PTR #
#pragma token PROC(TYPE) TYPE LIST #
#pragma token PROC(TYPE) TYPE STACK #
#pragma token PROC(TYPE) TYPE SIZE #

#pragma interface PTR LIST STACK SIZE


/* Enumeration type definitions */



/* Union type definitions */

#pragma token TYPE TYPE #
#pragma interface TYPE
#pragma token TYPE COMMAND #
#pragma interface COMMAND


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

extern void destroy_calculus();
extern void dummy_destroy_calculus();
#ifdef calculus_IO_ROUTINES
extern unsigned crt_calculus_alias;
extern void clear_calculus_alias(void);
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

#ifdef calculus_IO_ROUTINES
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

#ifdef calculus_IO_ROUTINES
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


/* Definitions for primitive number */

#pragma token EXP const : SIZE(number) : SIZE_number #

#pragma token PROC(\
	EXP : PTR(number) :,\
	EXP : number :\
    ) EXP : void : COPY_number #

#pragma token PROC(\
	EXP : PTR(number) :\
    ) EXP : number : DEREF_number #

#pragma token PROC(\
	EXP : number :,\
	EXP : LIST(number) :,\
	EXP lvalue : LIST(number) :\
    ) STATEMENT CONS_number #

#pragma token PROC(\
	EXP lvalue : number :,\
	EXP lvalue : LIST(number) :,\
	EXP : LIST(number) :\
    ) STATEMENT UN_CONS_number #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : number :,\
	EXP lvalue : LIST(number) :,\
	EXP : LIST(number) :\
    ) STATEMENT DESTROY_CONS_number #

#pragma token PROC(\
	EXP : number :,\
	EXP lvalue : STACK(number) :\
    ) STATEMENT PUSH_number #

#pragma token PROC(\
	EXP lvalue : number :,\
	EXP lvalue : STACK(number) :\
    ) STATEMENT POP_number #

#pragma interface SIZE_number COPY_number DEREF_number
#pragma interface CONS_number UN_CONS_number DESTROY_CONS_number
#pragma interface PUSH_number POP_number


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


/* Definitions for structure ALGEBRA_DEFN */

#pragma token PROC(EXP : PTR(ALGEBRA_DEFN) :) EXP : PTR(string) : alg_name #
#pragma interface alg_name

#pragma token PROC(EXP : PTR(ALGEBRA_DEFN) :) EXP : PTR(int) : alg_major_no #
#pragma interface alg_major_no

#pragma token PROC(EXP : PTR(ALGEBRA_DEFN) :) EXP : PTR(int) : alg_minor_no #
#pragma interface alg_minor_no

#pragma token PROC(EXP : PTR(ALGEBRA_DEFN) :) EXP : PTR(LIST(PRIMITIVE_P)) : alg_primitives #
#pragma interface alg_primitives

#pragma token PROC(EXP : PTR(ALGEBRA_DEFN) :) EXP : PTR(LIST(IDENTITY_P)) : alg_identities #
#pragma interface alg_identities

#pragma token PROC(EXP : PTR(ALGEBRA_DEFN) :) EXP : PTR(LIST(ENUM_P)) : alg_enumerations #
#pragma interface alg_enumerations

#pragma token PROC(EXP : PTR(ALGEBRA_DEFN) :) EXP : PTR(LIST(STRUCTURE_P)) : alg_structures #
#pragma interface alg_structures

#pragma token PROC(EXP : PTR(ALGEBRA_DEFN) :) EXP : PTR(LIST(UNION_P)) : alg_unions #
#pragma interface alg_unions

#pragma token PROC(EXP : PTR(ALGEBRA_DEFN) :) EXP : PTR(LIST(TYPE_P)) : alg_types #
#pragma interface alg_types

#pragma token PROC(\
	EXP : string :,\
	EXP : int :,\
	EXP : int :,\
	EXP : LIST(PRIMITIVE_P) :,\
	EXP : LIST(IDENTITY_P) :,\
	EXP : LIST(ENUM_P) :,\
	EXP : LIST(STRUCTURE_P) :,\
	EXP : LIST(UNION_P) :,\
	EXP : LIST(TYPE_P) :,\
	EXP : PTR(ALGEBRA_DEFN) :\
    ) STATEMENT MAKE_alg #
#pragma interface MAKE_alg

#pragma token EXP const : SIZE(ALGEBRA_DEFN) : SIZE_alg #

#pragma token PROC(\
	EXP : PTR(ALGEBRA_DEFN) :,\
	EXP : ALGEBRA_DEFN :\
    ) STATEMENT COPY_alg #

#pragma token PROC(\
	EXP : PTR(ALGEBRA_DEFN) :,\
	EXP lvalue : ALGEBRA_DEFN :\
    ) STATEMENT DEREF_alg #

#pragma token PROC(\
	EXP : ALGEBRA_DEFN :,\
	EXP : LIST(ALGEBRA_DEFN) :,\
	EXP lvalue : LIST(ALGEBRA_DEFN) :\
    ) STATEMENT CONS_alg #

#pragma token PROC(\
	EXP lvalue : ALGEBRA_DEFN :,\
	EXP lvalue : LIST(ALGEBRA_DEFN) :,\
	EXP : LIST(ALGEBRA_DEFN) :\
    ) STATEMENT UN_CONS_alg #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : ALGEBRA_DEFN :,\
	EXP lvalue : LIST(ALGEBRA_DEFN) :,\
	EXP : LIST(ALGEBRA_DEFN) :\
    ) STATEMENT DESTROY_CONS_alg #

#pragma token PROC(\
	EXP : ALGEBRA_DEFN :,\
	EXP lvalue : STACK(ALGEBRA_DEFN) :\
    ) STATEMENT PUSH_alg #

#pragma token PROC(\
	EXP lvalue : ALGEBRA_DEFN :,\
	EXP lvalue : STACK(ALGEBRA_DEFN) :\
    ) STATEMENT POP_alg #

#pragma interface SIZE_alg COPY_alg DEREF_alg
#pragma interface CONS_alg UN_CONS_alg DESTROY_CONS_alg
#pragma interface PUSH_alg POP_alg


/* Definitions for structure CLASS_ID */

#pragma token PROC(EXP : PTR(CLASS_ID) :) EXP : PTR(string) : cid_name #
#pragma interface cid_name

#pragma token PROC(EXP : PTR(CLASS_ID) :) EXP : PTR(string) : cid_name_aux #
#pragma interface cid_name_aux

#pragma token PROC(EXP : PTR(CLASS_ID) :) EXP : PTR(int) : cid_flag #
#pragma interface cid_flag

#pragma token PROC(EXP : PTR(CLASS_ID) :) EXP : PTR(name_string) : cid_file #
#pragma interface cid_file

#pragma token PROC(EXP : PTR(CLASS_ID) :) EXP : PTR(int) : cid_line #
#pragma interface cid_line

#pragma token PROC(\
	EXP : string :,\
	EXP : string :,\
	EXP : int :,\
	EXP : name_string :,\
	EXP : int :,\
	EXP : PTR(CLASS_ID) :\
    ) STATEMENT MAKE_cid #
#pragma interface MAKE_cid

#pragma token EXP const : SIZE(CLASS_ID) : SIZE_cid #

#pragma token PROC(\
	EXP : PTR(CLASS_ID) :,\
	EXP : CLASS_ID :\
    ) STATEMENT COPY_cid #

#pragma token PROC(\
	EXP : PTR(CLASS_ID) :,\
	EXP lvalue : CLASS_ID :\
    ) STATEMENT DEREF_cid #

#pragma token PROC(\
	EXP : CLASS_ID :,\
	EXP : LIST(CLASS_ID) :,\
	EXP lvalue : LIST(CLASS_ID) :\
    ) STATEMENT CONS_cid #

#pragma token PROC(\
	EXP lvalue : CLASS_ID :,\
	EXP lvalue : LIST(CLASS_ID) :,\
	EXP : LIST(CLASS_ID) :\
    ) STATEMENT UN_CONS_cid #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CLASS_ID :,\
	EXP lvalue : LIST(CLASS_ID) :,\
	EXP : LIST(CLASS_ID) :\
    ) STATEMENT DESTROY_CONS_cid #

#pragma token PROC(\
	EXP : CLASS_ID :,\
	EXP lvalue : STACK(CLASS_ID) :\
    ) STATEMENT PUSH_cid #

#pragma token PROC(\
	EXP lvalue : CLASS_ID :,\
	EXP lvalue : STACK(CLASS_ID) :\
    ) STATEMENT POP_cid #

#pragma interface SIZE_cid COPY_cid DEREF_cid
#pragma interface CONS_cid UN_CONS_cid DESTROY_CONS_cid
#pragma interface PUSH_cid POP_cid


/* Definitions for structure PRIMITIVE */

#pragma token PROC(EXP : PTR(PRIMITIVE) :) EXP : PTR(CLASS_ID_P) : prim_id #
#pragma interface prim_id

#pragma token PROC(EXP : PTR(PRIMITIVE) :) EXP : PTR(string) : prim_defn #
#pragma interface prim_defn

#pragma token PROC(\
	EXP : CLASS_ID_P :,\
	EXP : string :,\
	EXP : PTR(PRIMITIVE) :\
    ) STATEMENT MAKE_prim #
#pragma interface MAKE_prim

#pragma token EXP const : SIZE(PRIMITIVE) : SIZE_prim #

#pragma token PROC(\
	EXP : PTR(PRIMITIVE) :,\
	EXP : PRIMITIVE :\
    ) STATEMENT COPY_prim #

#pragma token PROC(\
	EXP : PTR(PRIMITIVE) :,\
	EXP lvalue : PRIMITIVE :\
    ) STATEMENT DEREF_prim #

#pragma token PROC(\
	EXP : PRIMITIVE :,\
	EXP : LIST(PRIMITIVE) :,\
	EXP lvalue : LIST(PRIMITIVE) :\
    ) STATEMENT CONS_prim #

#pragma token PROC(\
	EXP lvalue : PRIMITIVE :,\
	EXP lvalue : LIST(PRIMITIVE) :,\
	EXP : LIST(PRIMITIVE) :\
    ) STATEMENT UN_CONS_prim #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : PRIMITIVE :,\
	EXP lvalue : LIST(PRIMITIVE) :,\
	EXP : LIST(PRIMITIVE) :\
    ) STATEMENT DESTROY_CONS_prim #

#pragma token PROC(\
	EXP : PRIMITIVE :,\
	EXP lvalue : STACK(PRIMITIVE) :\
    ) STATEMENT PUSH_prim #

#pragma token PROC(\
	EXP lvalue : PRIMITIVE :,\
	EXP lvalue : STACK(PRIMITIVE) :\
    ) STATEMENT POP_prim #

#pragma interface SIZE_prim COPY_prim DEREF_prim
#pragma interface CONS_prim UN_CONS_prim DESTROY_CONS_prim
#pragma interface PUSH_prim POP_prim


/* Definitions for structure ECONST */

#pragma token PROC(EXP : PTR(ECONST) :) EXP : PTR(string) : ec_name #
#pragma interface ec_name

#pragma token PROC(EXP : PTR(ECONST) :) EXP : PTR(number) : ec_value #
#pragma interface ec_value

#pragma token PROC(\
	EXP : string :,\
	EXP : number :,\
	EXP : PTR(ECONST) :\
    ) STATEMENT MAKE_ec #
#pragma interface MAKE_ec

#pragma token EXP const : SIZE(ECONST) : SIZE_ec #

#pragma token PROC(\
	EXP : PTR(ECONST) :,\
	EXP : ECONST :\
    ) STATEMENT COPY_ec #

#pragma token PROC(\
	EXP : PTR(ECONST) :,\
	EXP lvalue : ECONST :\
    ) STATEMENT DEREF_ec #

#pragma token PROC(\
	EXP : ECONST :,\
	EXP : LIST(ECONST) :,\
	EXP lvalue : LIST(ECONST) :\
    ) STATEMENT CONS_ec #

#pragma token PROC(\
	EXP lvalue : ECONST :,\
	EXP lvalue : LIST(ECONST) :,\
	EXP : LIST(ECONST) :\
    ) STATEMENT UN_CONS_ec #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : ECONST :,\
	EXP lvalue : LIST(ECONST) :,\
	EXP : LIST(ECONST) :\
    ) STATEMENT DESTROY_CONS_ec #

#pragma token PROC(\
	EXP : ECONST :,\
	EXP lvalue : STACK(ECONST) :\
    ) STATEMENT PUSH_ec #

#pragma token PROC(\
	EXP lvalue : ECONST :,\
	EXP lvalue : STACK(ECONST) :\
    ) STATEMENT POP_ec #

#pragma interface SIZE_ec COPY_ec DEREF_ec
#pragma interface CONS_ec UN_CONS_ec DESTROY_CONS_ec
#pragma interface PUSH_ec POP_ec


/* Definitions for structure ENUM */

#pragma token PROC(EXP : PTR(ENUM) :) EXP : PTR(CLASS_ID_P) : en_id #
#pragma interface en_id

#pragma token PROC(EXP : PTR(ENUM) :) EXP : PTR(LIST(ECONST_P)) : en_consts #
#pragma interface en_consts

#pragma token PROC(EXP : PTR(ENUM) :) EXP : PTR(number) : en_order #
#pragma interface en_order

#pragma token PROC(EXP : PTR(ENUM) :) EXP : PTR(int) : en_lists #
#pragma interface en_lists

#pragma token PROC(\
	EXP : CLASS_ID_P :,\
	EXP : LIST(ECONST_P) :,\
	EXP : number :,\
	EXP : int :,\
	EXP : PTR(ENUM) :\
    ) STATEMENT MAKE_en #
#pragma interface MAKE_en

#pragma token EXP const : SIZE(ENUM) : SIZE_en #

#pragma token PROC(\
	EXP : PTR(ENUM) :,\
	EXP : ENUM :\
    ) STATEMENT COPY_en #

#pragma token PROC(\
	EXP : PTR(ENUM) :,\
	EXP lvalue : ENUM :\
    ) STATEMENT DEREF_en #

#pragma token PROC(\
	EXP : ENUM :,\
	EXP : LIST(ENUM) :,\
	EXP lvalue : LIST(ENUM) :\
    ) STATEMENT CONS_en #

#pragma token PROC(\
	EXP lvalue : ENUM :,\
	EXP lvalue : LIST(ENUM) :,\
	EXP : LIST(ENUM) :\
    ) STATEMENT UN_CONS_en #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : ENUM :,\
	EXP lvalue : LIST(ENUM) :,\
	EXP : LIST(ENUM) :\
    ) STATEMENT DESTROY_CONS_en #

#pragma token PROC(\
	EXP : ENUM :,\
	EXP lvalue : STACK(ENUM) :\
    ) STATEMENT PUSH_en #

#pragma token PROC(\
	EXP lvalue : ENUM :,\
	EXP lvalue : STACK(ENUM) :\
    ) STATEMENT POP_en #

#pragma interface SIZE_en COPY_en DEREF_en
#pragma interface CONS_en UN_CONS_en DESTROY_CONS_en
#pragma interface PUSH_en POP_en


/* Definitions for structure IDENTITY */

#pragma token PROC(EXP : PTR(IDENTITY) :) EXP : PTR(CLASS_ID_P) : ident_id #
#pragma interface ident_id

#pragma token PROC(EXP : PTR(IDENTITY) :) EXP : PTR(TYPE_P) : ident_defn #
#pragma interface ident_defn

#pragma token PROC(\
	EXP : CLASS_ID_P :,\
	EXP : TYPE_P :,\
	EXP : PTR(IDENTITY) :\
    ) STATEMENT MAKE_ident #
#pragma interface MAKE_ident

#pragma token EXP const : SIZE(IDENTITY) : SIZE_ident #

#pragma token PROC(\
	EXP : PTR(IDENTITY) :,\
	EXP : IDENTITY :\
    ) STATEMENT COPY_ident #

#pragma token PROC(\
	EXP : PTR(IDENTITY) :,\
	EXP lvalue : IDENTITY :\
    ) STATEMENT DEREF_ident #

#pragma token PROC(\
	EXP : IDENTITY :,\
	EXP : LIST(IDENTITY) :,\
	EXP lvalue : LIST(IDENTITY) :\
    ) STATEMENT CONS_ident #

#pragma token PROC(\
	EXP lvalue : IDENTITY :,\
	EXP lvalue : LIST(IDENTITY) :,\
	EXP : LIST(IDENTITY) :\
    ) STATEMENT UN_CONS_ident #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTITY :,\
	EXP lvalue : LIST(IDENTITY) :,\
	EXP : LIST(IDENTITY) :\
    ) STATEMENT DESTROY_CONS_ident #

#pragma token PROC(\
	EXP : IDENTITY :,\
	EXP lvalue : STACK(IDENTITY) :\
    ) STATEMENT PUSH_ident #

#pragma token PROC(\
	EXP lvalue : IDENTITY :,\
	EXP lvalue : STACK(IDENTITY) :\
    ) STATEMENT POP_ident #

#pragma interface SIZE_ident COPY_ident DEREF_ident
#pragma interface CONS_ident UN_CONS_ident DESTROY_CONS_ident
#pragma interface PUSH_ident POP_ident


/* Definitions for structure COMPONENT */

#pragma token PROC(EXP : PTR(COMPONENT) :) EXP : PTR(string) : cmp_name #
#pragma interface cmp_name

#pragma token PROC(EXP : PTR(COMPONENT) :) EXP : PTR(TYPE_P) : cmp_type #
#pragma interface cmp_type

#pragma token PROC(EXP : PTR(COMPONENT) :) EXP : PTR(string) : cmp_value #
#pragma interface cmp_value

#pragma token PROC(\
	EXP : string :,\
	EXP : TYPE_P :,\
	EXP : string :,\
	EXP : PTR(COMPONENT) :\
    ) STATEMENT MAKE_cmp #
#pragma interface MAKE_cmp

#pragma token EXP const : SIZE(COMPONENT) : SIZE_cmp #

#pragma token PROC(\
	EXP : PTR(COMPONENT) :,\
	EXP : COMPONENT :\
    ) STATEMENT COPY_cmp #

#pragma token PROC(\
	EXP : PTR(COMPONENT) :,\
	EXP lvalue : COMPONENT :\
    ) STATEMENT DEREF_cmp #

#pragma token PROC(\
	EXP : COMPONENT :,\
	EXP : LIST(COMPONENT) :,\
	EXP lvalue : LIST(COMPONENT) :\
    ) STATEMENT CONS_cmp #

#pragma token PROC(\
	EXP lvalue : COMPONENT :,\
	EXP lvalue : LIST(COMPONENT) :,\
	EXP : LIST(COMPONENT) :\
    ) STATEMENT UN_CONS_cmp #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : COMPONENT :,\
	EXP lvalue : LIST(COMPONENT) :,\
	EXP : LIST(COMPONENT) :\
    ) STATEMENT DESTROY_CONS_cmp #

#pragma token PROC(\
	EXP : COMPONENT :,\
	EXP lvalue : STACK(COMPONENT) :\
    ) STATEMENT PUSH_cmp #

#pragma token PROC(\
	EXP lvalue : COMPONENT :,\
	EXP lvalue : STACK(COMPONENT) :\
    ) STATEMENT POP_cmp #

#pragma interface SIZE_cmp COPY_cmp DEREF_cmp
#pragma interface CONS_cmp UN_CONS_cmp DESTROY_CONS_cmp
#pragma interface PUSH_cmp POP_cmp


/* Definitions for structure STRUCTURE */

#pragma token PROC(EXP : PTR(STRUCTURE) :) EXP : PTR(CLASS_ID_P) : str_id #
#pragma interface str_id

#pragma token PROC(EXP : PTR(STRUCTURE) :) EXP : PTR(STRUCTURE_P) : str_base #
#pragma interface str_base

#pragma token PROC(EXP : PTR(STRUCTURE) :) EXP : PTR(LIST(COMPONENT_P)) : str_defn #
#pragma interface str_defn

#pragma token PROC(EXP : PTR(STRUCTURE) :) EXP : PTR(zero_int) : str_output #
#pragma interface str_output

#pragma token PROC(\
	EXP : CLASS_ID_P :,\
	EXP : STRUCTURE_P :,\
	EXP : LIST(COMPONENT_P) :,\
	EXP : zero_int :,\
	EXP : PTR(STRUCTURE) :\
    ) STATEMENT MAKE_str #
#pragma interface MAKE_str

#pragma token EXP const : SIZE(STRUCTURE) : SIZE_str #

#pragma token PROC(\
	EXP : PTR(STRUCTURE) :,\
	EXP : STRUCTURE :\
    ) STATEMENT COPY_str #

#pragma token PROC(\
	EXP : PTR(STRUCTURE) :,\
	EXP lvalue : STRUCTURE :\
    ) STATEMENT DEREF_str #

#pragma token PROC(\
	EXP : STRUCTURE :,\
	EXP : LIST(STRUCTURE) :,\
	EXP lvalue : LIST(STRUCTURE) :\
    ) STATEMENT CONS_str #

#pragma token PROC(\
	EXP lvalue : STRUCTURE :,\
	EXP lvalue : LIST(STRUCTURE) :,\
	EXP : LIST(STRUCTURE) :\
    ) STATEMENT UN_CONS_str #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : STRUCTURE :,\
	EXP lvalue : LIST(STRUCTURE) :,\
	EXP : LIST(STRUCTURE) :\
    ) STATEMENT DESTROY_CONS_str #

#pragma token PROC(\
	EXP : STRUCTURE :,\
	EXP lvalue : STACK(STRUCTURE) :\
    ) STATEMENT PUSH_str #

#pragma token PROC(\
	EXP lvalue : STRUCTURE :,\
	EXP lvalue : STACK(STRUCTURE) :\
    ) STATEMENT POP_str #

#pragma interface SIZE_str COPY_str DEREF_str
#pragma interface CONS_str UN_CONS_str DESTROY_CONS_str
#pragma interface PUSH_str POP_str


/* Definitions for structure FIELD */

#pragma token PROC(EXP : PTR(FIELD) :) EXP : PTR(string) : fld_name #
#pragma interface fld_name

#pragma token PROC(EXP : PTR(FIELD) :) EXP : PTR(int) : fld_tag #
#pragma interface fld_tag

#pragma token PROC(EXP : PTR(FIELD) :) EXP : PTR(int) : fld_flag #
#pragma interface fld_flag

#pragma token PROC(EXP : PTR(FIELD) :) EXP : PTR(int) : fld_set #
#pragma interface fld_set

#pragma token PROC(EXP : PTR(FIELD) :) EXP : PTR(FIELD_P) : fld_base #
#pragma interface fld_base

#pragma token PROC(EXP : PTR(FIELD) :) EXP : PTR(LIST(COMPONENT_P)) : fld_defn #
#pragma interface fld_defn

#pragma token PROC(\
	EXP : string :,\
	EXP : int :,\
	EXP : int :,\
	EXP : int :,\
	EXP : FIELD_P :,\
	EXP : LIST(COMPONENT_P) :,\
	EXP : PTR(FIELD) :\
    ) STATEMENT MAKE_fld #
#pragma interface MAKE_fld

#pragma token EXP const : SIZE(FIELD) : SIZE_fld #

#pragma token PROC(\
	EXP : PTR(FIELD) :,\
	EXP : FIELD :\
    ) STATEMENT COPY_fld #

#pragma token PROC(\
	EXP : PTR(FIELD) :,\
	EXP lvalue : FIELD :\
    ) STATEMENT DEREF_fld #

#pragma token PROC(\
	EXP : FIELD :,\
	EXP : LIST(FIELD) :,\
	EXP lvalue : LIST(FIELD) :\
    ) STATEMENT CONS_fld #

#pragma token PROC(\
	EXP lvalue : FIELD :,\
	EXP lvalue : LIST(FIELD) :,\
	EXP : LIST(FIELD) :\
    ) STATEMENT UN_CONS_fld #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : FIELD :,\
	EXP lvalue : LIST(FIELD) :,\
	EXP : LIST(FIELD) :\
    ) STATEMENT DESTROY_CONS_fld #

#pragma token PROC(\
	EXP : FIELD :,\
	EXP lvalue : STACK(FIELD) :\
    ) STATEMENT PUSH_fld #

#pragma token PROC(\
	EXP lvalue : FIELD :,\
	EXP lvalue : STACK(FIELD) :\
    ) STATEMENT POP_fld #

#pragma interface SIZE_fld COPY_fld DEREF_fld
#pragma interface CONS_fld UN_CONS_fld DESTROY_CONS_fld
#pragma interface PUSH_fld POP_fld


/* Definitions for structure ARGUMENT */

#pragma token PROC(EXP : PTR(ARGUMENT) :) EXP : PTR(string) : arg_name #
#pragma interface arg_name

#pragma token PROC(EXP : PTR(ARGUMENT) :) EXP : PTR(TYPE_P) : arg_type #
#pragma interface arg_type

#pragma token PROC(\
	EXP : string :,\
	EXP : TYPE_P :,\
	EXP : PTR(ARGUMENT) :\
    ) STATEMENT MAKE_arg #
#pragma interface MAKE_arg

#pragma token EXP const : SIZE(ARGUMENT) : SIZE_arg #

#pragma token PROC(\
	EXP : PTR(ARGUMENT) :,\
	EXP : ARGUMENT :\
    ) STATEMENT COPY_arg #

#pragma token PROC(\
	EXP : PTR(ARGUMENT) :,\
	EXP lvalue : ARGUMENT :\
    ) STATEMENT DEREF_arg #

#pragma token PROC(\
	EXP : ARGUMENT :,\
	EXP : LIST(ARGUMENT) :,\
	EXP lvalue : LIST(ARGUMENT) :\
    ) STATEMENT CONS_arg #

#pragma token PROC(\
	EXP lvalue : ARGUMENT :,\
	EXP lvalue : LIST(ARGUMENT) :,\
	EXP : LIST(ARGUMENT) :\
    ) STATEMENT UN_CONS_arg #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : ARGUMENT :,\
	EXP lvalue : LIST(ARGUMENT) :,\
	EXP : LIST(ARGUMENT) :\
    ) STATEMENT DESTROY_CONS_arg #

#pragma token PROC(\
	EXP : ARGUMENT :,\
	EXP lvalue : STACK(ARGUMENT) :\
    ) STATEMENT PUSH_arg #

#pragma token PROC(\
	EXP lvalue : ARGUMENT :,\
	EXP lvalue : STACK(ARGUMENT) :\
    ) STATEMENT POP_arg #

#pragma interface SIZE_arg COPY_arg DEREF_arg
#pragma interface CONS_arg UN_CONS_arg DESTROY_CONS_arg
#pragma interface PUSH_arg POP_arg


/* Definitions for structure MAP */

#pragma token PROC(EXP : PTR(MAP) :) EXP : PTR(string) : map_name #
#pragma interface map_name

#pragma token PROC(EXP : PTR(MAP) :) EXP : PTR(int) : map_flag #
#pragma interface map_flag

#pragma token PROC(EXP : PTR(MAP) :) EXP : PTR(TYPE_P) : map_ret_type #
#pragma interface map_ret_type

#pragma token PROC(EXP : PTR(MAP) :) EXP : PTR(LIST(ARGUMENT_P)) : map_args #
#pragma interface map_args

#pragma token PROC(\
	EXP : string :,\
	EXP : int :,\
	EXP : TYPE_P :,\
	EXP : LIST(ARGUMENT_P) :,\
	EXP : PTR(MAP) :\
    ) STATEMENT MAKE_map #
#pragma interface MAKE_map

#pragma token EXP const : SIZE(MAP) : SIZE_map #

#pragma token PROC(\
	EXP : PTR(MAP) :,\
	EXP : MAP :\
    ) STATEMENT COPY_map #

#pragma token PROC(\
	EXP : PTR(MAP) :,\
	EXP lvalue : MAP :\
    ) STATEMENT DEREF_map #

#pragma token PROC(\
	EXP : MAP :,\
	EXP : LIST(MAP) :,\
	EXP lvalue : LIST(MAP) :\
    ) STATEMENT CONS_map #

#pragma token PROC(\
	EXP lvalue : MAP :,\
	EXP lvalue : LIST(MAP) :,\
	EXP : LIST(MAP) :\
    ) STATEMENT UN_CONS_map #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : MAP :,\
	EXP lvalue : LIST(MAP) :,\
	EXP : LIST(MAP) :\
    ) STATEMENT DESTROY_CONS_map #

#pragma token PROC(\
	EXP : MAP :,\
	EXP lvalue : STACK(MAP) :\
    ) STATEMENT PUSH_map #

#pragma token PROC(\
	EXP lvalue : MAP :,\
	EXP lvalue : STACK(MAP) :\
    ) STATEMENT POP_map #

#pragma interface SIZE_map COPY_map DEREF_map
#pragma interface CONS_map UN_CONS_map DESTROY_CONS_map
#pragma interface PUSH_map POP_map


/* Definitions for structure UNION */

#pragma token PROC(EXP : PTR(UNION) :) EXP : PTR(CLASS_ID_P) : un_id #
#pragma interface un_id

#pragma token PROC(EXP : PTR(UNION) :) EXP : PTR(UNION_P) : un_base #
#pragma interface un_base

#pragma token PROC(EXP : PTR(UNION) :) EXP : PTR(LIST(COMPONENT_P)) : un_s_defn #
#pragma interface un_s_defn

#pragma token PROC(EXP : PTR(UNION) :) EXP : PTR(LIST(FIELD_P)) : un_u_defn #
#pragma interface un_u_defn

#pragma token PROC(EXP : PTR(UNION) :) EXP : PTR(LIST(MAP_P)) : un_map #
#pragma interface un_map

#pragma token PROC(EXP : PTR(UNION) :) EXP : PTR(int) : un_no_fields #
#pragma interface un_no_fields

#pragma token PROC(\
	EXP : CLASS_ID_P :,\
	EXP : UNION_P :,\
	EXP : LIST(COMPONENT_P) :,\
	EXP : LIST(FIELD_P) :,\
	EXP : LIST(MAP_P) :,\
	EXP : int :,\
	EXP : PTR(UNION) :\
    ) STATEMENT MAKE_un #
#pragma interface MAKE_un

#pragma token EXP const : SIZE(UNION) : SIZE_un #

#pragma token PROC(\
	EXP : PTR(UNION) :,\
	EXP : UNION :\
    ) STATEMENT COPY_un #

#pragma token PROC(\
	EXP : PTR(UNION) :,\
	EXP lvalue : UNION :\
    ) STATEMENT DEREF_un #

#pragma token PROC(\
	EXP : UNION :,\
	EXP : LIST(UNION) :,\
	EXP lvalue : LIST(UNION) :\
    ) STATEMENT CONS_un #

#pragma token PROC(\
	EXP lvalue : UNION :,\
	EXP lvalue : LIST(UNION) :,\
	EXP : LIST(UNION) :\
    ) STATEMENT UN_CONS_un #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : UNION :,\
	EXP lvalue : LIST(UNION) :,\
	EXP : LIST(UNION) :\
    ) STATEMENT DESTROY_CONS_un #

#pragma token PROC(\
	EXP : UNION :,\
	EXP lvalue : STACK(UNION) :\
    ) STATEMENT PUSH_un #

#pragma token PROC(\
	EXP lvalue : UNION :,\
	EXP lvalue : STACK(UNION) :\
    ) STATEMENT POP_un #

#pragma interface SIZE_un COPY_un DEREF_un
#pragma interface CONS_un UN_CONS_un DESTROY_CONS_un
#pragma interface PUSH_un POP_un


/* Definitions for union TYPE */

#define ORDER_type ((unsigned)12)
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


/* Definitions for union COMMAND */

#define ORDER_cmd ((unsigned)4)
#pragma token EXP const : COMMAND : NULL_cmd #
#pragma token PROC(EXP : COMMAND :) EXP : int : IS_NULL_cmd #
#pragma token PROC(EXP : COMMAND :, EXP : COMMAND :) EXP : int : EQ_cmd #
#pragma interface NULL_cmd IS_NULL_cmd EQ_cmd

#pragma token EXP const : SIZE(COMMAND) : SIZE_cmd #

#pragma token PROC(\
	EXP : PTR(COMMAND) :,\
	EXP : COMMAND :\
    ) EXP : void : COPY_cmd #

#pragma token PROC(\
	EXP : PTR(COMMAND) :\
    ) EXP : COMMAND : DEREF_cmd #

#pragma token PROC(\
	EXP : COMMAND :,\
	EXP : LIST(COMMAND) :,\
	EXP lvalue : LIST(COMMAND) :\
    ) STATEMENT CONS_cmd #

#pragma token PROC(\
	EXP lvalue : COMMAND :,\
	EXP lvalue : LIST(COMMAND) :,\
	EXP : LIST(COMMAND) :\
    ) STATEMENT UN_CONS_cmd #

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : COMMAND :,\
	EXP lvalue : LIST(COMMAND) :,\
	EXP : LIST(COMMAND) :\
    ) STATEMENT DESTROY_CONS_cmd #

#pragma token PROC(\
	EXP : COMMAND :,\
	EXP lvalue : STACK(COMMAND) :\
    ) STATEMENT PUSH_cmd #

#pragma token PROC(\
	EXP lvalue : COMMAND :,\
	EXP lvalue : STACK(COMMAND) :\
    ) STATEMENT POP_cmd #

#pragma interface SIZE_cmd COPY_cmd DEREF_cmd
#pragma interface CONS_cmd UN_CONS_cmd DESTROY_CONS_cmd
#pragma interface PUSH_cmd POP_cmd


#endif
