/* $Id$ */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA calculus (VERSION 1.2)
    BY calculus (VERSION 1.3)
*/

#ifndef PRINT_DEF_H_INCLUDED
#define PRINT_DEF_H_INCLUDED

#include "calculus.h"
#include "type_ops.h"
#include "cmd_ops.h"

/* Printing function declarations */

#ifndef PRINT_list_cmd
static void PRINT_list_cmd (FILE *, LIST(COMMAND), char *, int);
#endif

#ifndef PRINT_cmd
static void PRINT_cmd (FILE *, COMMAND, char *, int);
#endif

#ifndef PRINT_list_ptr_map
static void PRINT_list_ptr_map (FILE *, LIST(PTR(MAP)), char *, int);
#endif

#ifndef PRINT_list_MAP_P
#define PRINT_list_MAP_P(A, B, C, D)PRINT_list_ptr_map((A), (B), (C), (D))
#endif

#ifndef PRINT_list_ptr_fld
static void PRINT_list_ptr_fld (FILE *, LIST(PTR(FIELD)), char *, int);
#endif

#ifndef PRINT_list_FIELD_P
#define PRINT_list_FIELD_P(A, B, C, D)PRINT_list_ptr_fld((A), (B), (C), (D))
#endif

#ifndef PRINT_list_ptr_arg
static void PRINT_list_ptr_arg (FILE *, LIST(PTR(ARGUMENT)), char *, int);
#endif

#ifndef PRINT_list_ARGUMENT_P
#define PRINT_list_ARGUMENT_P(A, B, C, D)PRINT_list_ptr_arg((A), (B), (C), (D))
#endif

#ifndef PRINT_list_ptr_cmp
static void PRINT_list_ptr_cmp (FILE *, LIST(PTR(COMPONENT)), char *, int);
#endif

#ifndef PRINT_list_COMPONENT_P
#define PRINT_list_COMPONENT_P(A, B, C, D)PRINT_list_ptr_cmp((A), (B), (C), (D))
#endif

#ifndef PRINT_list_ptr_ec
static void PRINT_list_ptr_ec (FILE *, LIST(PTR(ECONST)), char *, int);
#endif

#ifndef PRINT_list_ECONST_P
#define PRINT_list_ECONST_P(A, B, C, D)PRINT_list_ptr_ec((A), (B), (C), (D))
#endif

#ifndef PRINT_alg
static void PRINT_alg (FILE *, ALGEBRA_DEFN, char *, int);
#endif

#ifndef PRINT_list_ptr_type
static void PRINT_list_ptr_type (FILE *, LIST(PTR(TYPE)), char *, int);
#endif

#ifndef PRINT_list_TYPE_P
#define PRINT_list_TYPE_P(A, B, C, D)PRINT_list_ptr_type((A), (B), (C), (D))
#endif

#ifndef PRINT_list_ptr_un
static void PRINT_list_ptr_un (FILE *, LIST(PTR(UNION)), char *, int);
#endif

#ifndef PRINT_list_UNION_P
#define PRINT_list_UNION_P(A, B, C, D)PRINT_list_ptr_un((A), (B), (C), (D))
#endif

#ifndef PRINT_list_ptr_str
static void PRINT_list_ptr_str (FILE *, LIST(PTR(STRUCTURE)), char *, int);
#endif

#ifndef PRINT_list_STRUCTURE_P
#define PRINT_list_STRUCTURE_P(A, B, C, D)PRINT_list_ptr_str((A), (B), (C), (D))
#endif

#ifndef PRINT_list_ptr_en
static void PRINT_list_ptr_en (FILE *, LIST(PTR(ENUM)), char *, int);
#endif

#ifndef PRINT_list_ENUM_P
#define PRINT_list_ENUM_P(A, B, C, D)PRINT_list_ptr_en((A), (B), (C), (D))
#endif

#ifndef PRINT_list_ptr_ident
static void PRINT_list_ptr_ident (FILE *, LIST(PTR(IDENTITY)), char *, int);
#endif

#ifndef PRINT_list_IDENTITY_P
#define PRINT_list_IDENTITY_P(A, B, C, D)PRINT_list_ptr_ident((A), (B), (C), (D))
#endif

#ifndef PRINT_list_ptr_prim
static void PRINT_list_ptr_prim (FILE *, LIST(PTR(PRIMITIVE)), char *, int);
#endif

#ifndef PRINT_list_PRIMITIVE_P
#define PRINT_list_PRIMITIVE_P(A, B, C, D)PRINT_list_ptr_prim((A), (B), (C), (D))
#endif

#ifndef PRINT_UNION_P
#define PRINT_UNION_P(A, B, C, D)PRINT_ptr_un((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_un
static void PRINT_ptr_un (FILE *, PTR(UNION), char *, int);
#endif

#ifndef PRINT_un
static void PRINT_un (FILE *, UNION, char *, int);
#endif

#ifndef PRINT_TYPE_P_P
#define PRINT_TYPE_P_P(A, B, C, D)PRINT_ptr_TYPE_P((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_ptr_type
static void PRINT_ptr_ptr_type (FILE *, PTR(PTR(TYPE)), char *, int);
#endif

#ifndef PRINT_ptr_TYPE_P
#define PRINT_ptr_TYPE_P(A, B, C, D)PRINT_ptr_ptr_type((A), (B), (C), (D))
#endif

#ifndef PRINT_TYPE_P
#define PRINT_TYPE_P(A, B, C, D)PRINT_ptr_type((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_type
static void PRINT_ptr_type (FILE *, PTR(TYPE), char *, int);
#endif

#ifndef PRINT_type
static void PRINT_type (FILE *, TYPE, char *, int);
#endif

#ifndef PRINT_STRUCTURE_P
#define PRINT_STRUCTURE_P(A, B, C, D)PRINT_ptr_str((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_str
static void PRINT_ptr_str (FILE *, PTR(STRUCTURE), char *, int);
#endif

#ifndef PRINT_str
static void PRINT_str (FILE *, STRUCTURE, char *, int);
#endif

#ifndef PRINT_PRIMITIVE_P
#define PRINT_PRIMITIVE_P(A, B, C, D)PRINT_ptr_prim((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_prim
static void PRINT_ptr_prim (FILE *, PTR(PRIMITIVE), char *, int);
#endif

#ifndef PRINT_prim
static void PRINT_prim (FILE *, PRIMITIVE, char *, int);
#endif

#ifndef PRINT_MAP_P
#define PRINT_MAP_P(A, B, C, D)PRINT_ptr_map((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_map
static void PRINT_ptr_map (FILE *, PTR(MAP), char *, int);
#endif

#ifndef PRINT_map
static void PRINT_map (FILE *, MAP, char *, int);
#endif

#ifndef PRINT_IDENTITY_P
#define PRINT_IDENTITY_P(A, B, C, D)PRINT_ptr_ident((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_ident
static void PRINT_ptr_ident (FILE *, PTR(IDENTITY), char *, int);
#endif

#ifndef PRINT_ident
static void PRINT_ident (FILE *, IDENTITY, char *, int);
#endif

#ifndef PRINT_FIELD_P
#define PRINT_FIELD_P(A, B, C, D)PRINT_ptr_fld((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_fld
static void PRINT_ptr_fld (FILE *, PTR(FIELD), char *, int);
#endif

#ifndef PRINT_fld
static void PRINT_fld (FILE *, FIELD, char *, int);
#endif

#ifndef PRINT_ENUM_P
#define PRINT_ENUM_P(A, B, C, D)PRINT_ptr_en((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_en
static void PRINT_ptr_en (FILE *, PTR(ENUM), char *, int);
#endif

#ifndef PRINT_en
static void PRINT_en (FILE *, ENUM, char *, int);
#endif

#ifndef PRINT_ECONST_P
#define PRINT_ECONST_P(A, B, C, D)PRINT_ptr_ec((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_ec
static void PRINT_ptr_ec (FILE *, PTR(ECONST), char *, int);
#endif

#ifndef PRINT_ec
static void PRINT_ec (FILE *, ECONST, char *, int);
#endif

#ifndef PRINT_COMPONENT_P
#define PRINT_COMPONENT_P(A, B, C, D)PRINT_ptr_cmp((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_cmp
static void PRINT_ptr_cmp (FILE *, PTR(COMPONENT), char *, int);
#endif

#ifndef PRINT_cmp
static void PRINT_cmp (FILE *, COMPONENT, char *, int);
#endif

#ifndef PRINT_CLASS_ID_P_P
#define PRINT_CLASS_ID_P_P(A, B, C, D)PRINT_ptr_CLASS_ID_P((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_ptr_cid
static void PRINT_ptr_ptr_cid (FILE *, PTR(PTR(CLASS_ID)), char *, int);
#endif

#ifndef PRINT_ptr_CLASS_ID_P
#define PRINT_ptr_CLASS_ID_P(A, B, C, D)PRINT_ptr_ptr_cid((A), (B), (C), (D))
#endif

#ifndef PRINT_CLASS_ID_P
#define PRINT_CLASS_ID_P(A, B, C, D)PRINT_ptr_cid((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_cid
static void PRINT_ptr_cid (FILE *, PTR(CLASS_ID), char *, int);
#endif

#ifndef PRINT_cid
static void PRINT_cid (FILE *, CLASS_ID, char *, int);
#endif

#ifndef PRINT_ARGUMENT_P
#define PRINT_ARGUMENT_P(A, B, C, D)PRINT_ptr_arg((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_arg
static void PRINT_ptr_arg (FILE *, PTR(ARGUMENT), char *, int);
#endif

#ifndef PRINT_arg
static void PRINT_arg (FILE *, ARGUMENT, char *, int);
#endif

#ifndef PRINT_string_P
#define PRINT_string_P(A, B, C, D)PRINT_ptr_string((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_string
static void PRINT_ptr_string (FILE *, PTR(string), char *, int);
#endif

#ifndef PRINT_number_P
#define PRINT_number_P(A, B, C, D)PRINT_ptr_number((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_number
static void PRINT_ptr_number (FILE *, PTR(number), char *, int);
#endif

#ifndef PRINT_int_P
#define PRINT_int_P(A, B, C, D)PRINT_ptr_int((A), (B), (C), (D))
#endif

#ifndef PRINT_ptr_int
static void PRINT_ptr_int (FILE *, PTR(int), char *, int);
#endif

#ifndef PRINT_zero_int
#define PRINT_zero_int(A, B, C, D)PRINT_int((A), (B), (C), (D))
#endif

#ifndef PRINT_name_string
#define PRINT_name_string(A, B, C, D)PRINT_string((A), (B), (C), (D))
#endif

#ifndef PRINT_string
static void PRINT_string (FILE *, string, char *, int);
#endif

#ifndef PRINT_number
static void PRINT_number (FILE *, number, char *, int);
#endif

#ifndef PRINT_int
static void PRINT_int (FILE *, int, char *, int);
#endif



/* Printing variables */

static int print_indent_step = 4;
static int print_ptr_depth = 1;
static int print_list_expand = 0;


/* Printing indentation routine */

static void print_indent

(FILE *f, int d)
{
    int i = print_indent_step * d;
    while (i--) (void)fputc(' ', f);
    return;
}


/* Printing routines for LIST(COMMAND) */

#ifndef PRINT_list_cmd

static void
PRINT_list_cmd(FILE *f_, LIST(COMMAND) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	COMMAND z_;
	UN_CONS_cmd(z_, x_, x_);
	PRINT_cmd(f_, z_, "(cmd)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_cmd(LIST(COMMAND) x_)
{
    PRINT_list_cmd(stdout, x_, "list_cmd", 0);
    return;
}

#endif

#endif


/* Printing routines for COMMAND */

#ifndef PRINT_cmd

static void
PRINT_cmd(FILE *f_, COMMAND x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_cmd(x_)) {
	(void)fprintf(f_, "%s = NULL_cmd ;\n", nm_);
    } else {
	switch (TAG_cmd(x_)) {
	    case cmd_simple_tag: {
		(void)fprintf(f_, "%s = {\n", nm_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = simple ;\n");
		{
		    int z_;
		    z_ = DEREF_int(cmd_line(x_));
		    PRINT_int(f_, z_, "line", d_ + 1);
		}
		{
		    string z_;
		    z_ = DEREF_string(cmd_simple_text(x_));
		    PRINT_string(f_, z_, "text", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case cmd_compound_tag: {
		(void)fprintf(f_, "%s = {\n", nm_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = compound ;\n");
		{
		    int z_;
		    z_ = DEREF_int(cmd_line(x_));
		    PRINT_int(f_, z_, "line", d_ + 1);
		}
		{
		    LIST(COMMAND) z_;
		    z_ = DEREF_list(cmd_compound_seq(x_));
		    PRINT_list_cmd(f_, z_, "seq", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case cmd_loop_tag: {
		(void)fprintf(f_, "%s = {\n", nm_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = loop ;\n");
		{
		    int z_;
		    z_ = DEREF_int(cmd_line(x_));
		    PRINT_int(f_, z_, "line", d_ + 1);
		}
		{
		    string z_;
		    z_ = DEREF_string(cmd_loop_control(x_));
		    PRINT_string(f_, z_, "control", d_ + 1);
		}
		{
		    COMMAND z_;
		    z_ = DEREF_cmd(cmd_loop_body(x_));
		    PRINT_cmd(f_, z_, "body", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case cmd_cond_tag: {
		(void)fprintf(f_, "%s = {\n", nm_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = cond ;\n");
		{
		    int z_;
		    z_ = DEREF_int(cmd_line(x_));
		    PRINT_int(f_, z_, "line", d_ + 1);
		}
		{
		    string z_;
		    z_ = DEREF_string(cmd_cond_control(x_));
		    PRINT_string(f_, z_, "control", d_ + 1);
		}
		{
		    COMMAND z_;
		    z_ = DEREF_cmd(cmd_cond_true_code(x_));
		    PRINT_cmd(f_, z_, "true_code", d_ + 1);
		}
		{
		    COMMAND z_;
		    z_ = DEREF_cmd(cmd_cond_false_code(x_));
		    PRINT_cmd(f_, z_, "false_code", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    default : {
		(void)fprintf(f_, "%s = ERROR!\n", nm_);
		break;
	    }
	}
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_cmd(COMMAND x_)
{
    PRINT_cmd(stdout, x_, "cmd", 0);
    return;
}

#endif

#endif


/* Printing routines for LIST(PTR(MAP)) */

#ifndef PRINT_list_ptr_map

static void
PRINT_list_ptr_map(FILE *f_, LIST(PTR(MAP)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	PTR(MAP) z_;
	UN_CONS_ptr(z_, x_, x_);
	PRINT_ptr_map(f_, z_, "(ptr_map)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_ptr_map(LIST(PTR(MAP)) x_)
{
    PRINT_list_ptr_map(stdout, x_, "list_ptr_map", 0);
    return;
}

#endif

#endif


/* Printing routines for LIST(PTR(FIELD)) */

#ifndef PRINT_list_ptr_fld

static void
PRINT_list_ptr_fld(FILE *f_, LIST(PTR(FIELD)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	PTR(FIELD) z_;
	UN_CONS_ptr(z_, x_, x_);
	PRINT_ptr_fld(f_, z_, "(ptr_fld)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_ptr_fld(LIST(PTR(FIELD)) x_)
{
    PRINT_list_ptr_fld(stdout, x_, "list_ptr_fld", 0);
    return;
}

#endif

#endif


/* Printing routines for LIST(PTR(ARGUMENT)) */

#ifndef PRINT_list_ptr_arg

static void
PRINT_list_ptr_arg(FILE *f_, LIST(PTR(ARGUMENT)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	PTR(ARGUMENT) z_;
	UN_CONS_ptr(z_, x_, x_);
	PRINT_ptr_arg(f_, z_, "(ptr_arg)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_ptr_arg(LIST(PTR(ARGUMENT)) x_)
{
    PRINT_list_ptr_arg(stdout, x_, "list_ptr_arg", 0);
    return;
}

#endif

#endif


/* Printing routines for LIST(PTR(COMPONENT)) */

#ifndef PRINT_list_ptr_cmp

static void
PRINT_list_ptr_cmp(FILE *f_, LIST(PTR(COMPONENT)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	PTR(COMPONENT) z_;
	UN_CONS_ptr(z_, x_, x_);
	PRINT_ptr_cmp(f_, z_, "(ptr_cmp)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_ptr_cmp(LIST(PTR(COMPONENT)) x_)
{
    PRINT_list_ptr_cmp(stdout, x_, "list_ptr_cmp", 0);
    return;
}

#endif

#endif


/* Printing routines for LIST(PTR(ECONST)) */

#ifndef PRINT_list_ptr_ec

static void
PRINT_list_ptr_ec(FILE *f_, LIST(PTR(ECONST)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	PTR(ECONST) z_;
	UN_CONS_ptr(z_, x_, x_);
	PRINT_ptr_ec(f_, z_, "(ptr_ec)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_ptr_ec(LIST(PTR(ECONST)) x_)
{
    PRINT_list_ptr_ec(stdout, x_, "list_ptr_ec", 0);
    return;
}

#endif

#endif


/* Printing routines for ALGEBRA_DEFN */

#ifndef PRINT_alg

static void
PRINT_alg(FILE *f_, ALGEBRA_DEFN x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_string(f_, x_.name, "name", d_ + 1);
    PRINT_int(f_, x_.major_no, "major_no", d_ + 1);
    PRINT_int(f_, x_.minor_no, "minor_no", d_ + 1);
    PRINT_list_PRIMITIVE_P(f_, x_.primitives, "primitives", d_ + 1);
    PRINT_list_IDENTITY_P(f_, x_.identities, "identities", d_ + 1);
    PRINT_list_ENUM_P(f_, x_.enumerations, "enumerations", d_ + 1);
    PRINT_list_STRUCTURE_P(f_, x_.structures, "structures", d_ + 1);
    PRINT_list_UNION_P(f_, x_.unions, "unions", d_ + 1);
    PRINT_list_TYPE_P(f_, x_.types, "types", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_alg(ALGEBRA_DEFN *x_)
{
    if (x_)PRINT_alg(stdout, *x_, "alg", 0);
    return;
}

#endif

#endif


/* Printing routines for LIST(PTR(TYPE)) */

#ifndef PRINT_list_ptr_type

static void
PRINT_list_ptr_type(FILE *f_, LIST(PTR(TYPE)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	PTR(TYPE) z_;
	UN_CONS_ptr(z_, x_, x_);
	PRINT_ptr_type(f_, z_, "(ptr_type)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_ptr_type(LIST(PTR(TYPE)) x_)
{
    PRINT_list_ptr_type(stdout, x_, "list_ptr_type", 0);
    return;
}

#endif

#endif


/* Printing routines for LIST(PTR(UNION)) */

#ifndef PRINT_list_ptr_un

static void
PRINT_list_ptr_un(FILE *f_, LIST(PTR(UNION)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	PTR(UNION) z_;
	UN_CONS_ptr(z_, x_, x_);
	PRINT_ptr_un(f_, z_, "(ptr_un)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_ptr_un(LIST(PTR(UNION)) x_)
{
    PRINT_list_ptr_un(stdout, x_, "list_ptr_un", 0);
    return;
}

#endif

#endif


/* Printing routines for LIST(PTR(STRUCTURE)) */

#ifndef PRINT_list_ptr_str

static void
PRINT_list_ptr_str(FILE *f_, LIST(PTR(STRUCTURE)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	PTR(STRUCTURE) z_;
	UN_CONS_ptr(z_, x_, x_);
	PRINT_ptr_str(f_, z_, "(ptr_str)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_ptr_str(LIST(PTR(STRUCTURE)) x_)
{
    PRINT_list_ptr_str(stdout, x_, "list_ptr_str", 0);
    return;
}

#endif

#endif


/* Printing routines for LIST(PTR(ENUM)) */

#ifndef PRINT_list_ptr_en

static void
PRINT_list_ptr_en(FILE *f_, LIST(PTR(ENUM)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	PTR(ENUM) z_;
	UN_CONS_ptr(z_, x_, x_);
	PRINT_ptr_en(f_, z_, "(ptr_en)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_ptr_en(LIST(PTR(ENUM)) x_)
{
    PRINT_list_ptr_en(stdout, x_, "list_ptr_en", 0);
    return;
}

#endif

#endif


/* Printing routines for LIST(PTR(IDENTITY)) */

#ifndef PRINT_list_ptr_ident

static void
PRINT_list_ptr_ident(FILE *f_, LIST(PTR(IDENTITY)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	PTR(IDENTITY) z_;
	UN_CONS_ptr(z_, x_, x_);
	PRINT_ptr_ident(f_, z_, "(ptr_ident)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_ptr_ident(LIST(PTR(IDENTITY)) x_)
{
    PRINT_list_ptr_ident(stdout, x_, "list_ptr_ident", 0);
    return;
}

#endif

#endif


/* Printing routines for LIST(PTR(PRIMITIVE)) */

#ifndef PRINT_list_ptr_prim

static void
PRINT_list_ptr_prim(FILE *f_, LIST(PTR(PRIMITIVE)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = LIST {\n", nm_);
    while (!IS_NULL_list(x_)) {
	PTR(PRIMITIVE) z_;
	UN_CONS_ptr(z_, x_, x_);
	PRINT_ptr_prim(f_, z_, "(ptr_prim)", d_ + 1);
	if (!print_list_expand && !IS_NULL_list(x_)) {
	    print_indent(f_, d_ + 1);
	    (void)fprintf(f_, "(tail) = 0x%p ;\n", VOIDSTAR_list(x_));
	    break;
	}
    }
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_list_ptr_prim(LIST(PTR(PRIMITIVE)) x_)
{
    PRINT_list_ptr_prim(stdout, x_, "list_ptr_prim", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(UNION) */

#ifndef PRINT_ptr_un

static void
PRINT_ptr_un(FILE *f_, PTR(UNION) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	UNION z_;
	DEREF_un(x_, z_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_un(f_, z_, "(un)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_un(PTR(UNION) x_)
{
    PRINT_ptr_un(stdout, x_, "ptr_un", 0);
    return;
}

#endif

#endif


/* Printing routines for UNION */

#ifndef PRINT_un

static void
PRINT_un(FILE *f_, UNION x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_CLASS_ID_P(f_, x_.id, "id", d_ + 1);
    PRINT_UNION_P(f_, x_.base, "base", d_ + 1);
    PRINT_list_COMPONENT_P(f_, x_.s_defn, "s_defn", d_ + 1);
    PRINT_list_FIELD_P(f_, x_.u_defn, "u_defn", d_ + 1);
    PRINT_list_MAP_P(f_, x_.map, "map", d_ + 1);
    PRINT_int(f_, x_.no_fields, "no_fields", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_un(UNION *x_)
{
    if (x_)PRINT_un(stdout, *x_, "un", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(PTR(TYPE)) */

#ifndef PRINT_ptr_ptr_type

static void
PRINT_ptr_ptr_type(FILE *f_, PTR(PTR(TYPE)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	PTR(TYPE) z_;
	z_ = DEREF_ptr(x_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_ptr_type(f_, z_, "(ptr_type)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_ptr_type(PTR(PTR(TYPE)) x_)
{
    PRINT_ptr_ptr_type(stdout, x_, "ptr_ptr_type", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(TYPE) */

#ifndef PRINT_ptr_type

static void
PRINT_ptr_type(FILE *f_, PTR(TYPE) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	TYPE z_;
	z_ = DEREF_type(x_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_type(f_, z_, "(type)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_type(PTR(TYPE) x_)
{
    PRINT_ptr_type(stdout, x_, "ptr_type", 0);
    return;
}

#endif

#endif


/* Printing routines for TYPE */

#ifndef PRINT_type

static void
PRINT_type(FILE *f_, TYPE x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_type(x_)) {
	(void)fprintf(f_, "%s = NULL_type ;\n", nm_);
    } else {
	switch (TAG_type(x_)) {
	    case type_primitive_tag: {
		unsigned alias_ = GET_ALIAS_type_primitive(x_);
		if (alias_) {
		    (void)fprintf(f_, "%s = [%u] ;\n", nm_, alias_);
		    break;
		}
		alias_ = ++crt_calculus_alias ;
		SET_ALIAS_type_primitive(x_, alias_);
		(void)fprintf(f_, "%s = [%u] = {\n", nm_, alias_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = primitive ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    PRIMITIVE_P z_;
		    z_ = DEREF_ptr(type_primitive_prim(x_));
		    PRINT_PRIMITIVE_P(f_, z_, "prim", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case type_ident_tag: {
		unsigned alias_ = GET_ALIAS_type_ident(x_);
		if (alias_) {
		    (void)fprintf(f_, "%s = [%u] ;\n", nm_, alias_);
		    break;
		}
		alias_ = ++crt_calculus_alias ;
		SET_ALIAS_type_ident(x_, alias_);
		(void)fprintf(f_, "%s = [%u] = {\n", nm_, alias_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = ident ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    IDENTITY_P z_;
		    z_ = DEREF_ptr(type_ident_id(x_));
		    PRINT_IDENTITY_P(f_, z_, "id", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case type_enumeration_tag: {
		unsigned alias_ = GET_ALIAS_type_enumeration(x_);
		if (alias_) {
		    (void)fprintf(f_, "%s = [%u] ;\n", nm_, alias_);
		    break;
		}
		alias_ = ++crt_calculus_alias ;
		SET_ALIAS_type_enumeration(x_, alias_);
		(void)fprintf(f_, "%s = [%u] = {\n", nm_, alias_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = enumeration ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    ENUM_P z_;
		    z_ = DEREF_ptr(type_enumeration_en(x_));
		    PRINT_ENUM_P(f_, z_, "en", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case type_structure_tag: {
		unsigned alias_ = GET_ALIAS_type_structure(x_);
		if (alias_) {
		    (void)fprintf(f_, "%s = [%u] ;\n", nm_, alias_);
		    break;
		}
		alias_ = ++crt_calculus_alias ;
		SET_ALIAS_type_structure(x_, alias_);
		(void)fprintf(f_, "%s = [%u] = {\n", nm_, alias_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = structure ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    STRUCTURE_P z_;
		    z_ = DEREF_ptr(type_structure_struc(x_));
		    PRINT_STRUCTURE_P(f_, z_, "struc", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case type_onion_tag: {
		unsigned alias_ = GET_ALIAS_type_onion(x_);
		if (alias_) {
		    (void)fprintf(f_, "%s = [%u] ;\n", nm_, alias_);
		    break;
		}
		alias_ = ++crt_calculus_alias ;
		SET_ALIAS_type_onion(x_, alias_);
		(void)fprintf(f_, "%s = [%u] = {\n", nm_, alias_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = onion ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    UNION_P z_;
		    z_ = DEREF_ptr(type_onion_un(x_));
		    PRINT_UNION_P(f_, z_, "un", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case type_ptr_tag: {
		unsigned alias_ = GET_ALIAS_type_ptr(x_);
		if (alias_) {
		    (void)fprintf(f_, "%s = [%u] ;\n", nm_, alias_);
		    break;
		}
		alias_ = ++crt_calculus_alias ;
		SET_ALIAS_type_ptr(x_, alias_);
		(void)fprintf(f_, "%s = [%u] = {\n", nm_, alias_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = ptr ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    TYPE_P z_;
		    z_ = DEREF_ptr(type_ptr_sub(x_));
		    PRINT_TYPE_P(f_, z_, "sub", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case type_list_tag: {
		unsigned alias_ = GET_ALIAS_type_list(x_);
		if (alias_) {
		    (void)fprintf(f_, "%s = [%u] ;\n", nm_, alias_);
		    break;
		}
		alias_ = ++crt_calculus_alias ;
		SET_ALIAS_type_list(x_, alias_);
		(void)fprintf(f_, "%s = [%u] = {\n", nm_, alias_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = list ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    TYPE_P z_;
		    z_ = DEREF_ptr(type_list_sub(x_));
		    PRINT_TYPE_P(f_, z_, "sub", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case type_stack_tag: {
		unsigned alias_ = GET_ALIAS_type_stack(x_);
		if (alias_) {
		    (void)fprintf(f_, "%s = [%u] ;\n", nm_, alias_);
		    break;
		}
		alias_ = ++crt_calculus_alias ;
		SET_ALIAS_type_stack(x_, alias_);
		(void)fprintf(f_, "%s = [%u] = {\n", nm_, alias_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = stack ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    TYPE_P z_;
		    z_ = DEREF_ptr(type_stack_sub(x_));
		    PRINT_TYPE_P(f_, z_, "sub", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case type_vec_tag: {
		unsigned alias_ = GET_ALIAS_type_vec(x_);
		if (alias_) {
		    (void)fprintf(f_, "%s = [%u] ;\n", nm_, alias_);
		    break;
		}
		alias_ = ++crt_calculus_alias ;
		SET_ALIAS_type_vec(x_, alias_);
		(void)fprintf(f_, "%s = [%u] = {\n", nm_, alias_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = vec ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    TYPE_P z_;
		    z_ = DEREF_ptr(type_vec_sub(x_));
		    PRINT_TYPE_P(f_, z_, "sub", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case type_vec_ptr_tag: {
		unsigned alias_ = GET_ALIAS_type_vec_ptr(x_);
		if (alias_) {
		    (void)fprintf(f_, "%s = [%u] ;\n", nm_, alias_);
		    break;
		}
		alias_ = ++crt_calculus_alias ;
		SET_ALIAS_type_vec_ptr(x_, alias_);
		(void)fprintf(f_, "%s = [%u] = {\n", nm_, alias_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = vec_ptr ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    TYPE_P z_;
		    z_ = DEREF_ptr(type_vec_ptr_sub(x_));
		    PRINT_TYPE_P(f_, z_, "sub", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case type_quote_tag: {
		(void)fprintf(f_, "%s = {\n", nm_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = quote ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    string z_;
		    z_ = DEREF_string(type_quote_defn(x_));
		    PRINT_string(f_, z_, "defn", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    case type_undef_tag: {
		(void)fprintf(f_, "%s = {\n", nm_);
		print_indent(f_, d_ + 1);
		(void)fprintf(f_, "(tag) = undef ;\n");
		{
		    zero_int z_;
		    z_ = DEREF_int(type_size(x_));
		    PRINT_zero_int(f_, z_, "size", d_ + 1);
		}
		{
		    string z_;
		    z_ = DEREF_string(type_undef_name(x_));
		    PRINT_string(f_, z_, "name", d_ + 1);
		}
		print_indent(f_, d_);
		(void)fprintf(f_, "}\n");
		break;
	    }
	    default : {
		(void)fprintf(f_, "%s = ERROR!\n", nm_);
		break;
	    }
	}
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_type(TYPE x_)
{
    PRINT_type(stdout, x_, "type", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(STRUCTURE) */

#ifndef PRINT_ptr_str

static void
PRINT_ptr_str(FILE *f_, PTR(STRUCTURE) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	STRUCTURE z_;
	DEREF_str(x_, z_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_str(f_, z_, "(str)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_str(PTR(STRUCTURE) x_)
{
    PRINT_ptr_str(stdout, x_, "ptr_str", 0);
    return;
}

#endif

#endif


/* Printing routines for STRUCTURE */

#ifndef PRINT_str

static void
PRINT_str(FILE *f_, STRUCTURE x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_CLASS_ID_P(f_, x_.id, "id", d_ + 1);
    PRINT_STRUCTURE_P(f_, x_.base, "base", d_ + 1);
    PRINT_list_COMPONENT_P(f_, x_.defn, "defn", d_ + 1);
    PRINT_zero_int(f_, x_.output, "output", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_str(STRUCTURE *x_)
{
    if (x_)PRINT_str(stdout, *x_, "str", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(PRIMITIVE) */

#ifndef PRINT_ptr_prim

static void
PRINT_ptr_prim(FILE *f_, PTR(PRIMITIVE) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	PRIMITIVE z_;
	DEREF_prim(x_, z_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_prim(f_, z_, "(prim)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_prim(PTR(PRIMITIVE) x_)
{
    PRINT_ptr_prim(stdout, x_, "ptr_prim", 0);
    return;
}

#endif

#endif


/* Printing routines for PRIMITIVE */

#ifndef PRINT_prim

static void
PRINT_prim(FILE *f_, PRIMITIVE x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_CLASS_ID_P(f_, x_.id, "id", d_ + 1);
    PRINT_string(f_, x_.defn, "defn", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_prim(PRIMITIVE *x_)
{
    if (x_)PRINT_prim(stdout, *x_, "prim", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(MAP) */

#ifndef PRINT_ptr_map

static void
PRINT_ptr_map(FILE *f_, PTR(MAP) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	MAP z_;
	DEREF_map(x_, z_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_map(f_, z_, "(map)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_map(PTR(MAP) x_)
{
    PRINT_ptr_map(stdout, x_, "ptr_map", 0);
    return;
}

#endif

#endif


/* Printing routines for MAP */

#ifndef PRINT_map

static void
PRINT_map(FILE *f_, MAP x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_string(f_, x_.name, "name", d_ + 1);
    PRINT_int(f_, x_.flag, "flag", d_ + 1);
    PRINT_TYPE_P(f_, x_.ret_type, "ret_type", d_ + 1);
    PRINT_list_ARGUMENT_P(f_, x_.args, "args", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_map(MAP *x_)
{
    if (x_)PRINT_map(stdout, *x_, "map", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(IDENTITY) */

#ifndef PRINT_ptr_ident

static void
PRINT_ptr_ident(FILE *f_, PTR(IDENTITY) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	IDENTITY z_;
	DEREF_ident(x_, z_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_ident(f_, z_, "(ident)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_ident(PTR(IDENTITY) x_)
{
    PRINT_ptr_ident(stdout, x_, "ptr_ident", 0);
    return;
}

#endif

#endif


/* Printing routines for IDENTITY */

#ifndef PRINT_ident

static void
PRINT_ident(FILE *f_, IDENTITY x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_CLASS_ID_P(f_, x_.id, "id", d_ + 1);
    PRINT_TYPE_P(f_, x_.defn, "defn", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_ident(IDENTITY *x_)
{
    if (x_)PRINT_ident(stdout, *x_, "ident", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(FIELD) */

#ifndef PRINT_ptr_fld

static void
PRINT_ptr_fld(FILE *f_, PTR(FIELD) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	FIELD z_;
	DEREF_fld(x_, z_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_fld(f_, z_, "(fld)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_fld(PTR(FIELD) x_)
{
    PRINT_ptr_fld(stdout, x_, "ptr_fld", 0);
    return;
}

#endif

#endif


/* Printing routines for FIELD */

#ifndef PRINT_fld

static void
PRINT_fld(FILE *f_, FIELD x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_string(f_, x_.name, "name", d_ + 1);
    PRINT_int(f_, x_.tag, "tag", d_ + 1);
    PRINT_int(f_, x_.flag, "flag", d_ + 1);
    PRINT_int(f_, x_.set, "set", d_ + 1);
    PRINT_FIELD_P(f_, x_.base, "base", d_ + 1);
    PRINT_list_COMPONENT_P(f_, x_.defn, "defn", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_fld(FIELD *x_)
{
    if (x_)PRINT_fld(stdout, *x_, "fld", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(ENUM) */

#ifndef PRINT_ptr_en

static void
PRINT_ptr_en(FILE *f_, PTR(ENUM) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	ENUM z_;
	DEREF_en(x_, z_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_en(f_, z_, "(en)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_en(PTR(ENUM) x_)
{
    PRINT_ptr_en(stdout, x_, "ptr_en", 0);
    return;
}

#endif

#endif


/* Printing routines for ENUM */

#ifndef PRINT_en

static void
PRINT_en(FILE *f_, ENUM x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_CLASS_ID_P(f_, x_.id, "id", d_ + 1);
    PRINT_list_ECONST_P(f_, x_.consts, "consts", d_ + 1);
    PRINT_number(f_, x_.order, "order", d_ + 1);
    PRINT_int(f_, x_.lists, "lists", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_en(ENUM *x_)
{
    if (x_)PRINT_en(stdout, *x_, "en", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(ECONST) */

#ifndef PRINT_ptr_ec

static void
PRINT_ptr_ec(FILE *f_, PTR(ECONST) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	ECONST z_;
	DEREF_ec(x_, z_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_ec(f_, z_, "(ec)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_ec(PTR(ECONST) x_)
{
    PRINT_ptr_ec(stdout, x_, "ptr_ec", 0);
    return;
}

#endif

#endif


/* Printing routines for ECONST */

#ifndef PRINT_ec

static void
PRINT_ec(FILE *f_, ECONST x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_string(f_, x_.name, "name", d_ + 1);
    PRINT_number(f_, x_.value, "value", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_ec(ECONST *x_)
{
    if (x_)PRINT_ec(stdout, *x_, "ec", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(COMPONENT) */

#ifndef PRINT_ptr_cmp

static void
PRINT_ptr_cmp(FILE *f_, PTR(COMPONENT) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	COMPONENT z_;
	DEREF_cmp(x_, z_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_cmp(f_, z_, "(cmp)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_cmp(PTR(COMPONENT) x_)
{
    PRINT_ptr_cmp(stdout, x_, "ptr_cmp", 0);
    return;
}

#endif

#endif


/* Printing routines for COMPONENT */

#ifndef PRINT_cmp

static void
PRINT_cmp(FILE *f_, COMPONENT x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_string(f_, x_.name, "name", d_ + 1);
    PRINT_TYPE_P(f_, x_.type, "type", d_ + 1);
    PRINT_string(f_, x_.value, "value", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_cmp(COMPONENT *x_)
{
    if (x_)PRINT_cmp(stdout, *x_, "cmp", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(PTR(CLASS_ID)) */

#ifndef PRINT_ptr_ptr_cid

static void
PRINT_ptr_ptr_cid(FILE *f_, PTR(PTR(CLASS_ID)) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	PTR(CLASS_ID) z_;
	z_ = DEREF_ptr(x_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_ptr_cid(f_, z_, "(ptr_cid)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_ptr_cid(PTR(PTR(CLASS_ID)) x_)
{
    PRINT_ptr_ptr_cid(stdout, x_, "ptr_ptr_cid", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(CLASS_ID) */

#ifndef PRINT_ptr_cid

static void
PRINT_ptr_cid(FILE *f_, PTR(CLASS_ID) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	CLASS_ID z_;
	DEREF_cid(x_, z_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_cid(f_, z_, "(cid)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_cid(PTR(CLASS_ID) x_)
{
    PRINT_ptr_cid(stdout, x_, "ptr_cid", 0);
    return;
}

#endif

#endif


/* Printing routines for CLASS_ID */

#ifndef PRINT_cid

static void
PRINT_cid(FILE *f_, CLASS_ID x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_string(f_, x_.name, "name", d_ + 1);
    PRINT_string(f_, x_.name_aux, "name_aux", d_ + 1);
    PRINT_int(f_, x_.flag, "flag", d_ + 1);
    PRINT_name_string(f_, x_.file, "file", d_ + 1);
    PRINT_int(f_, x_.line, "line", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_cid(CLASS_ID *x_)
{
    if (x_)PRINT_cid(stdout, *x_, "cid", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(ARGUMENT) */

#ifndef PRINT_ptr_arg

static void
PRINT_ptr_arg(FILE *f_, PTR(ARGUMENT) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	ARGUMENT z_;
	DEREF_arg(x_, z_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_arg(f_, z_, "(arg)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_arg(PTR(ARGUMENT) x_)
{
    PRINT_ptr_arg(stdout, x_, "ptr_arg", 0);
    return;
}

#endif

#endif


/* Printing routines for ARGUMENT */

#ifndef PRINT_arg

static void
PRINT_arg(FILE *f_, ARGUMENT x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = {\n", nm_);
    PRINT_string(f_, x_.name, "name", d_ + 1);
    PRINT_TYPE_P(f_, x_.type, "type", d_ + 1);
    print_indent(f_, d_);
    (void)fprintf(f_, "}\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_arg(ARGUMENT *x_)
{
    if (x_)PRINT_arg(stdout, *x_, "arg", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(string) */

#ifndef PRINT_ptr_string

static void
PRINT_ptr_string(FILE *f_, PTR(string) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	string z_;
	z_ = DEREF_string(x_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_string(f_, z_, "(string)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_string(PTR(string) x_)
{
    PRINT_ptr_string(stdout, x_, "ptr_string", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(number) */

#ifndef PRINT_ptr_number

static void
PRINT_ptr_number(FILE *f_, PTR(number) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	number z_;
	z_ = DEREF_number(x_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_number(f_, z_, "(number)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_number(PTR(number) x_)
{
    PRINT_ptr_number(stdout, x_, "ptr_number", 0);
    return;
}

#endif

#endif


/* Printing routines for PTR(int) */

#ifndef PRINT_ptr_int

static void
PRINT_ptr_int(FILE *f_, PTR(int) x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    if (IS_NULL_ptr(x_)) {
	(void)fprintf(f_, "%s = NULL_ptr;\n", nm_);
    } else if (d_ < print_ptr_depth) {
	int z_;
	z_ = DEREF_int(x_);
	(void)fprintf(f_, "%s = PTR {\n", nm_);
	PRINT_int(f_, z_, "(int)", d_ + 1);
	print_indent(f_, d_);
	(void)fprintf(f_, "}\n");
    } else {
	(void)fprintf(f_, "%s = 0x%p ;\n", nm_, VOIDSTAR_ptr(x_));
    }
    return;
}

#ifndef NDEBUG

void
DEBUG_ptr_int(PTR(int) x_)
{
    PRINT_ptr_int(stdout, x_, "ptr_int", 0);
    return;
}

#endif

#endif


/* Printing routines for string */

#ifndef PRINT_string

static void
PRINT_string(FILE *f_, string x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = ", nm_);
    OUTPUT_string(f_, x_);
    (void)fprintf(f_, " ;\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_string(string x_)
{
    PRINT_string(stdout, x_, "string", 0);
    return;
}

#endif

#endif


/* Printing routines for number */

#ifndef PRINT_number

static void
PRINT_number(FILE *f_, number x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = ", nm_);
    OUTPUT_number(f_, x_);
    (void)fprintf(f_, " ;\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_number(number x_)
{
    PRINT_number(stdout, x_, "number", 0);
    return;
}

#endif

#endif


/* Printing routines for int */

#ifndef PRINT_int

static void
PRINT_int(FILE *f_, int x_, char *nm_, int d_)
{
    print_indent(f_, d_);
    (void)fprintf(f_, "%s = ", nm_);
    OUTPUT_int(f_, x_);
    (void)fprintf(f_, " ;\n");
    return;
}

#ifndef NDEBUG

void
DEBUG_int(int x_)
{
    PRINT_int(stdout, x_, "int", 0);
    return;
}

#endif

#endif


#endif
