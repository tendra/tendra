/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/error.h>
#include <shared/string.h>

#include "calculus.h"
#include "code.h"
#include "common.h"
#include "lex.h"
#include "output.h"
#include "suffix.h"
#include "type_ops.h"

#include <out/token.h>

/*
 * PRINT SIMPLE TOKENS
 *
 * This routine prints the simple tokens for a type named nm with short
 * name ns.  e is true for simply dereferenced types.
 */
static void
print_simple_tok(char *nm, char *ns, int e, int lst)
{
	/* SIZE token */
	output("%pt %xc : SIZE(%e) : SIZE_%e #\n\n", nm, ns);

	/* Assign token */
	output("%pt PROC(\\\n");
	output("\t%xr : PTR(%e) :,\\\n\t%xr : %e :\\\n    ) ", nm, nm);
	output(e ? "%xr : void :" : "STATEMENT");
	output(" COPY_%e #\n\n", ns);

	/* Dereference token */
	output("%pt PROC(\\\n");
	output("\t%xr : PTR(%e) :", nm);
	if (e) {
		output("\\\n    ) %xr : %e :", nm);
	} else {
		output(",\\\n\t%xl : %e :\\\n    ) STATEMENT", nm);
	}
	output(" DEREF_%e #\n\n", ns);

	if (lst) {
		/* CONS token */
		output("%pt PROC(\\\n");
		output("\t%xr : %e :,\\\n\t%xr : LIST(%e) :,\\\n", nm, nm);
		output("\t%xl : LIST(%e) :\\\n", nm);
		output("    ) STATEMENT CONS_%e #\n\n", ns);

		/* UN_CONS token */
		output("%pt PROC(\\\n");
		output("\t%xl : %e :,\\\n", nm);
		output("\t%xl : LIST(%e) :,\\\n", nm);
		output("\t%xr : LIST(%e) :\\\n", nm);
		output("    ) STATEMENT UN_CONS_%e #\n\n", ns);

		/* DESTROY_CONS token */
		output("%pt PROC(\\\n");
		output("\t%xr : DESTROYER :,\\\n\t%xl : %e :,\\\n", nm);
		output("\t%xl : LIST(%e) :,\\\n", nm);
		output("\t%xr : LIST(%e) :\\\n", nm);
		output("    ) STATEMENT DESTROY_CONS_%e #\n\n", ns);

		if (allow_stack) {
			/* PUSH token */
			output("%pt PROC(\\\n");
			output("\t%xr : %e :,\\\n", nm);
			output("\t%xl : STACK(%e) :\\\n", nm);
			output("    ) STATEMENT PUSH_%e #\n\n", ns);

			/* POP token */
			output("%pt PROC(\\\n");
			output("\t%xl : %e :,\\\n", nm);
			output("\t%xl : STACK(%e) :\\\n", nm);
			output("    ) STATEMENT POP_%e #\n\n", ns);
		}
	}

	/* Interface commands */
	output("%pi SIZE_%e COPY_%e DEREF_%e\n", ns, ns, ns);
	if (lst) {
		output("%pi CONS_%e UN_CONS_%e DESTROY_CONS_%e\n", ns, ns, ns);
		if (allow_stack) {
			output("%pi PUSH_%e POP_%e\n", ns, ns);
		}
	}

	output("\n\n");
}

/*
 * PRINT SIMPLE TOKENS FOR TYPE OPERATIONS
 *
 * This routine prints the simple tokens for the type operation op.
 * The tokens are named using nm.  e is true for simply dereferenced types.
 */
static void
print_type_ops_tok(char *op, char *nm, int e)
{
	/* Size token */
	output("%pt PROC(\\\n\tTYPE t\\\n");
	output("    ) %xc : SIZE(%s(t)) : SIZE_%s #\n\n", op, nm);

	/* Assign token */
	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : PTR(%s(t)) : e1,\\\n", op);
	output("\t%xr : %s(t) : e2 |\\\n", op);
	output("\tEXP e1, EXP e2\\\n    } ");
	output(e ? "%xr : void :" : "STATEMENT");
	output(" COPY_%s #\n\n", nm);

	/* Dereference token */
	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : PTR(%s(t)) : e", op);
	if (e) {
		output(" |\\\n\tEXP e\\\n");
		output("    } %xr : %s(t) : ", op);
	} else {
		output("1,\\\n\t%xl : %s(t) : e2 |\\\n", op);
		output("\tEXP e1, EXP e2\\\n");
		output("    } STATEMENT ");
	}
	output("DEREF_%s #\n\n", nm);

	/* CONS token */
	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : %s(t) : e2,\\\n", op);
	output("\t%xr : LIST(%s(t)) : e3,\\\n", op);
	output("\t%xl : LIST(%s(t)) : e4 |\\\n", op);
	output("\tEXP e2, EXP e3, EXP e4\\\n");
	output("    } STATEMENT CONS_%s #\n\n", nm);

	/* UN_CONS token */
	output("%pt PROC {\\\n");
	output("\tTYPE t, %xl : %s(t) : e2,\\\n", op);
	output("\t%xl : LIST(%s(t)) : e3,\\\n", op);
	output("\t%xr : LIST(%s(t)) : e4 |\\\n", op);
	output("\tEXP e2, EXP e3, EXP e4\\\n");
	output("    } STATEMENT UN_CONS_%s #\n\n", nm);

	/* DESTROY_CONS token */
	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : DESTROYER : e1,\\\n");
	output("\t%xl : %s(t) : e2,\\\n", op);
	output("\t%xl : LIST(%s(t)) : e3,\\\n", op);
	output("\t%xr : LIST(%s(t)) : e4 |\\\n", op);
	output("\tEXP e1, EXP e2, EXP e3, EXP e4\\\n");
	output("    } STATEMENT DESTROY_CONS_%s #\n\n", nm);

	if (allow_stack) {
		/* PUSH token */
		output("%pt PROC {\\\n");
		output("\tTYPE t, %xr : %s(t) : e2,\\\n", op);
		output("\t%xl : STACK(%s(t)) : e3 |\\\n", op);
		output("\tEXP e2, EXP e3\\\n");
		output("    } STATEMENT PUSH_%s #\n\n", nm);

		/* POP token */
		output("%pt PROC {\\\n");
		output("\tTYPE t, %xl : %s(t) : e2,\\\n", op);
		output("\t%xl : STACK(%s(t)) : e3 |\\\n", op);
		output("\tEXP e2, EXP e3\\\n");
		output("    } STATEMENT POP_%s #\n\n", nm);
	}

	/* Interface commands */
	output("%pi SIZE_%s COPY_%s DEREF_%s\n", nm, nm, nm);
	output("%pi CONS_%s UN_CONS_%s DESTROY_CONS_%s\n", nm, nm, nm);
	if (allow_stack) {
		output("%pi PUSH_%s POP_%s\n", nm, nm);
	}

	output("\n\n");
}

/*
 * PRINT BASIC TYPES (TOKEN VERSION)
 *
 * This routine prints the token versions of the basic type definitions.
 */
static void
print_types_tok(void)
{
	comment("Primitive types");
	LOOP_PRIMITIVE {
		CLASS_ID_P c = DEREF_ptr(prim_id(CRT_PRIMITIVE));
		char *pn = DEREF_string(cid_name(c));
		char *pd = DEREF_string(prim_defn(CRT_PRIMITIVE));
		if (!streq(pn, pd))
		{
			output("typedef %PD %PN;\n");
		}
	}
	output("\n\n");

	comment("Basic types");
	output("#ifndef %X_DESTR_DEFINED\n");
	output("#define %X_DESTR_DEFINED\n");
	output("typedef void (*DESTROYER)();\n");
	output("#endif\n\n");
	output("%pt PROC(TYPE) TYPE PTR #\n");
	output("%pt PROC(TYPE) TYPE LIST #\n");
	if (allow_stack) {
		output("%pt PROC(TYPE) TYPE STACK #\n");
	}
	if (allow_vec) {
		output("%pt VARIETY %X_dim #\n");
		output("%pt PROC(TYPE) TYPE VEC #\n");
		output("%pt PROC(TYPE) TYPE VEC_PTR #\n");
	}
	output("%pt PROC(TYPE) TYPE SIZE #\n\n");
	output("%pi PTR LIST ");
	if (allow_stack) {
		output("STACK ");
	}
	if (allow_vec) {
		output("%X_dim VEC VEC_PTR ");
	}
	output("SIZE\n\n\n");

	comment("Enumeration type definitions");
	LOOP_ENUM {
		output("%pt VARIETY %EN #\n");
		output("%pi %EN\n");
	}
	output("\n\n");

	comment("Union type definitions");
	LOOP_UNION {
		output("%pt TYPE %UN #\n");
		output("%pi %UN\n");
	}
	output("\n\n");

	print_struct_defn();

	comment("Function declarations");
	output("extern void destroy_%X();\n");
	output("extern void dummy_destroy_%X();\n");
	output("#ifdef %X_IO_ROUTINES\n");
	output("extern unsigned crt_%X_alias;\n");
	output("extern void clear_%X_alias(void);\n");
	output("#endif\n");
	output("\n\n");
}

/*
 * PRINT POINTER CONSTRUCTS (TOKEN VERSION)
 *
 * This routine prints the token versions of the pointer constructs.
 */
static void
print_ptr_tok(void)
{
	comment("Pointer token specifications");
	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : PTR(t) : e1, %xr : SIZE(t) : e2 |\\\n");
	output("\tEXP e1, EXP e2\\\n");
	output("    } %xr : PTR(t) : STEP_ptr #\n\n");

	output("%pt PROC(\\\n\tTYPE t\\\n");
	output("    ) %xc : PTR(t) : NULL_ptr #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : PTR(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : int : IS_NULL_ptr #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : PTR(t) : e1, %xr : PTR(t) : e2 |\\\n");
	output("\tEXP e1, EXP e2\\\n");
	output("    } %xr : int : EQ_ptr #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : SIZE(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : PTR(t) : MAKE_ptr #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : PTR(t) : e1, %xr : SIZE(t) : e2 |\\\n");
	output("\tEXP e1, EXP e2\\\n");
	output("    } %xr : void : DESTROY_ptr #\n\n");

	output("%pt PROC(\\\n\tTYPE t\\\n");
	output("    ) %xr : PTR(t) : UNIQ_ptr #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : PTR(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : void : DESTROY_UNIQ_ptr #\n\n");

	output("%pi STEP_ptr NULL_ptr IS_NULL_ptr EQ_ptr\n");
	output("%pi MAKE_ptr DESTROY_ptr\n\n");

	output("#ifdef %X_IO_ROUTINES\n");
	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : PTR(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : void * : VOIDSTAR_ptr #\n");
	output("%pi VOIDSTAR_ptr\n");
	output("#endif\n\n");

	print_type_ops_tok("PTR", "ptr", 1);
}

/*
 * PRINT LIST CONSTRUCTS (TOKEN VERSION)
 *
 * This routine prints the token versions of the list constructs.
 */
static void
print_list_tok(void)
{
	comment("List token specifications");
	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : PTR(t) : HEAD_list #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : PTR(LIST(t)) : PTR_TAIL_list #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : LIST(t) : TAIL_list #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e1 |\\\n");
	output("\tEXP e1\\\n");
	output("    } %xr : unsigned : LENGTH_list #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e1 |\\\n");
	output("\tEXP e1\\\n");
	output("    } %xr : LIST(t) : END_list #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e1 |\\\n");
	output("\tEXP e1\\\n");
	output("    } %xr : LIST(t) : REVERSE_list #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e1, %xr : LIST(t) : e2 |\\\n");
	output("\tEXP e1, EXP e2\\\n");
	output("    } %xr : LIST(t) : APPEND_list #\n\n");

	output("%pt PROC(\\\n\tTYPE t\\\n");
	output("    ) %xc : LIST(t) : NULL_list #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : int : IS_NULL_list #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e1, %xr : LIST(t) : e2 |\\\n");
	output("\tEXP e1, EXP e2\\\n");
	output("    } %xr : int : EQ_list #\n\n");

	output("%pt PROC(\\\n\tTYPE t\\\n");
	output("    ) %xr : LIST(t) : UNIQ_list #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : void : DESTROY_UNIQ_list #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e1, %xr : SIZE(t) : e2 |\\\n");
	output("\tEXP e1, EXP e2\\\n");
	output("    } STATEMENT DESTROY_list #\n\n");

	output("%pi HEAD_list PTR_TAIL_list TAIL_list\n");
	output("%pi LENGTH_list END_list REVERSE_list APPEND_list\n");
	output("%pi NULL_list IS_NULL_list EQ_list\n");
	output("%pi UNIQ_list DESTROY_UNIQ_list DESTROY_list\n\n");

	output("#ifdef %X_IO_ROUTINES\n");
	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : void * : VOIDSTAR_list #\n");
	output("%pi VOIDSTAR_list\n");
	output("#endif\n\n");

	print_type_ops_tok("LIST", "list", 1);
}

/*
 * PRINT STACK CONSTRUCTS (TOKEN VERSION)
 *
 * This routine prints the token versions of the stack constructs.
 */
static void
print_stack_tok(void)
{
	comment("Stack token specifications");
	output("%pt PROC(\\\n\tTYPE t\\\n");
	output("    ) %xc : STACK(t) : NULL_stack #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : STACK(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : int : IS_NULL_stack #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : STACK(t) : e1 |\\\n");
	output("\tEXP e1\\\n");
	output("    } %xr : LIST(t) : LIST_stack #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : LIST(t) : e1 |\\\n");
	output("\tEXP e1\\\n");
	output("    } %xr : STACK(t) : STACK_list #\n\n");

	output("%pi NULL_stack IS_NULL_stack LIST_stack STACK_list\n\n");

	print_type_ops_tok("STACK", "stack", 1);
}

/*
 * PRINT VECTOR CONSTRUCTS (TOKEN VERSION)
 *
 * This routine prints the token versions of the vector constructs.
 */
static void
print_vec_tok(void)
{
	comment("Vector token specifications");
	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : VEC(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : %X_dim : DIM_vec #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : PTR(VEC(t)) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : PTR(t) : PTR_ptr_vec #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : PTR(VEC(t)) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : %X_dim : DIM_ptr_vec #\n\n");

	output("%pt PROC(\\\n\tTYPE t\\\n");
	output("    ) %xr : VEC(t) : NULL_vec #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : SIZE(t) : e1,\\\n");
	output("\t%xr : %X_dim : e2,\\\n");
	output("\t%xl : VEC(t) : e3 |\\\n");
	output("\tEXP e1, EXP e2, EXP e3\\\n");
	output("    } STATEMENT MAKE_vec #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : VEC(t) : e1, %xr : SIZE(t) : e2 |\\\n");
	output("\tEXP e1, EXP e2\\\n");
	output("    } STATEMENT DESTROY_vec #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : VEC(t) : e1,\\\n");
	output("\t%xr : SIZE(t) : e2, %xr : int : e3,\\\n");
	output("\t%xr : int : e4, %xl : VEC(t) : e5 |\\\n");
	output("\tEXP e1, EXP e2, EXP e3, EXP e4, EXP e5\\\n");
	output("    } STATEMENT TRIM_vec #\n\n");

	output("%pi DIM_vec PTR_ptr_vec DIM_ptr_vec\n");
	output("%pi NULL_vec MAKE_vec DESTROY_vec TRIM_vec\n\n");
	print_type_ops_tok("VEC", "vec", 0);
}

/*
 * PRINT VECTOR POINTER CONSTRUCTS (TOKEN VERSION)
 *
 * This routine prints the token versions of the vector pointer
 * constructs.
 */
static void
print_vec_ptr_tok(void)
{
	comment("Vector pointer token specifications");
	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : VEC(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : VEC_PTR(t) : VEC_PTR_vec #\n\n");

	output("%pt PROC {\\\n");
	output("\tTYPE t, %xr : VEC_PTR(t) : e |\\\n");
	output("\tEXP e\\\n");
	output("    } %xr : PTR(t) : PTR_vec_ptr #\n\n");

	output("%pi VEC_PTR_vec PTR_vec_ptr\n\n");
	print_type_ops_tok("VEC_PTR", "vec_ptr", 0);
}

/*
 * PRINT SIZE CONSTRUCTS (TOKEN VERSION)
 *
 * This routine prints the token versions of the size constructs.
 */
static void
print_size_tok(void)
{
	comment("Size token specifications");
	output("%pt PROC {\\\n");
	output("\tTYPE t, VARIETY v,\\\n");
	output("\t%xr : SIZE(t) : e1, %xr : v : e2 |\\\n");
	output("\tEXP e1, EXP e2\\\n");
	output("    } %xr : SIZE(t) : SCALE #\n\n");
	output("%pi SCALE\n\n\n");
}

/*
 * PRINT PRIMITIVE CONSTRUCTS (TOKEN VERSION)
 *
 * This routine prints the token versions of the primitive constructs.
 */
static void
print_prim_tok(void)
{
	comment("Definitions for primitive %PN");
	print_simple_tok("%PN", "%PM", 1, 1);
}

/*
 * PRINT ENUMERATION CONSTRUCTS (TOKEN VERSION)
 *
 * This routine prints the token versions of the enumeration constructs.
 */
static void
print_enum_tok(void)
{
	int lst = DEREF_int(en_lists(CRT_ENUM));
	comment("Definitions for enumeration %EN");
	print_enum_consts();
	print_simple_tok("%EN", "%EM", 1, lst);
}

/*
 * PRINT STRUCTURE CONSTRUCTS (TOKEN VERSION)
 *
 * This routine prints the token versions of the structure constructs.
 */
static void
print_struct_tok(void)
{
	STRUCTURE_P base = DEREF_ptr(str_base(CRT_STRUCTURE));

	comment("Definitions for structure %SN");
	LOOP_STRUCTURE_COMPONENT {
		output("%pt PROC(%xr : PTR(%SN) :) ");
		output("%xr : PTR(%CT) : %SM_%CN #\n");
		output("%pi %SM_%CN\n\n");
	}
	output("%pt PROC(\\\n");
	LOOP_STRUCTURE_COMPONENT {
		string v = DEREF_string(cmp_value(CRT_COMPONENT));
		if (v == NULL)
		{
			output("\t%xr : %CT :,\\\n");
		}
	}
	output("\t%xr : PTR(%SN) :\\\n");
	output("    ) STATEMENT MAKE_%SM #\n");
	output("%pi MAKE_%SM\n\n");

	if (!IS_NULL_ptr(base)) {
		CLASS_ID_P id = DEREF_ptr(str_id(base));
		char *nt = DEREF_string(cid_name(id));
		char *nm = DEREF_string(cid_name_aux(id));
		output("%pt PROC(\\\n");
		output("\t%xr : PTR(%SN) :\\\n");
		output("    ) %xr : PTR(%s) : CONVERT_%SM_%s #\n", nt, nm);
		output("%pi CONVERT_%SM_%s\n\n", nm);
	}

	print_simple_tok("%SN", "%SM", 0, 1);
}

/*
 * PRINT UNION CONSTRUCTS (TOKEN VERSION)
 *
 * This routine prints the token versions of the union constructs.
 */
static void
print_union_tok(void)
{
	UNION_P base = DEREF_ptr(un_base(CRT_UNION));

	comment("Definitions for union %UN");
	output("#define ORDER_%UM ((unsigned)%UO)\n");
	output("%pt %xc : %UN : NULL_%UM #\n");
	output("%pt PROC(%xr : %UN :) %xr : int : IS_NULL_%UM #\n");
	output("%pt PROC(%xr : %UN :, %xr : %UN :) ");
	output("%xr : int : EQ_%UM #\n");
	output("%pi NULL_%UM IS_NULL_%UM EQ_%UM\n\n");

	if (!IS_NULL_ptr(base)) {
		CLASS_ID_P id = DEREF_ptr(un_id(base));
		char *nt = DEREF_string(cid_name(id));
		char *nm = DEREF_string(cid_name_aux(id));
		output("%pt PROC(%xr : %UN :) %xr : %s : CONVERT_%UM_%s #\n",
		       nt, nm);
		output("%pi CONVERT_%UM_%s\n\n", nm);
	}

	print_simple_tok("%UN", "%UM", 1, 1);
	return;
}

/*
 * PRINT THE MAIN TOKEN OUTPUT FILE
 *
 * This routine prints the token specifications for the objects above.
 */
static void
print_main_tok(char *dir)
{
	open_file(dir, MAIN_PREFIX, MAIN_SUFFIX);
	if (extra_headers) {
		output("#include \"%s_bscs.h\"\n\n", MAIN_PREFIX);
	}

	output("#ifndef %X_NAME\n");
	output("#define %X_NAME%t40\"%X\"\n");
	output("#define %X_VERSION%t40\"%V\"\n");
	output("#define %X_SPECIFICATION%t40%d\n", 1);
	output("#define %X_IMPLEMENTATION%t40%d\n", 0);
	output("#endif\n\n\n");

	print_proto();
	print_types_tok();
	print_ptr_tok();
	print_list_tok();
	if (allow_stack) {
		print_stack_tok();
	}
	if (allow_vec) {
		print_vec_tok();
		print_vec_ptr_tok();
	}
	print_size_tok();

	LOOP_PRIMITIVE print_prim_tok();
	LOOP_ENUM print_enum_tok();
	LOOP_STRUCTURE print_struct_tok();
	LOOP_UNION print_union_tok();

	if (extra_headers) {
		output("#include \"%s_term.h\"\n\n", MAIN_PREFIX);
	}

	close_file();
}

/*
 * PRINT ARGUMENTS FOR A TOKENISED UNION CONSTRUCTOR
 *
 * This routine prints the list of arguments for a tokenised union
 * constructor and similar functions.  lv is true if all the arguments
 * are lvalues.
 */
static void
print_cons_tok_args(int lv, int d)
{
	char *a = "%xr";
	char *b = "%xl";

	if (lv) {
		char *c = a;
		a = b;
		b = c;
	}

	LOOP_UNION_COMPONENT {
		string v = DEREF_string(cmp_value(CRT_COMPONENT));
		if (v == NULL || d == 0)
		{
			output("\\\n\t%e : %CT :,", a);
		}
	}

	LOOP_FIELD_COMPONENT {
		string v = DEREF_string(cmp_value(CRT_COMPONENT));
		if (v == NULL || d == 0)
		{
			output("\\\n\t%e : %CT :,", a);
		}
	}

	output("\\\n\t%e : %UN :", b);
}

/*
 * PRINT FIELD SELECTOR OPERATIONS
 *
 * This routine prints the operations on field selectors (token version).
 * rng gives the number of elements in the field set (if appropriate).
 * al is true if the field is aliased.
 */
static void
print_field_tok(int rng, int al)
{
	char *f = (rng ? "%FN_etc" : "%FN");

	LOOP_FIELD_COMPONENT {
		output("%pt PROC(%xr : %UN :)\\\n");
		output("    %xr : PTR(%CT) : ");
		output("%UM_%e_%CN #\n", f);
		output("%pi %UM_%e_%CN\n\n", f);
	}

	/* Component constructor */
	output("%pt PROC(");
	if (rng) {
		output("\\\n\t%xr : unsigned :,");
	}
	print_cons_tok_args(0, 1);
	output("\\\n    ) STATEMENT MAKE_%UM_%e #\n", f);
	output("%pi MAKE_%UM_%e\n\n", f);

	/* Tag modifier */
	if (rng) {
		output("%pt PROC(");
		output("\\\n\t%xr : unsigned :,");
		output("\\\n\t%xr : %UN :");
		output("\\\n    ) STATEMENT MODIFY_%UM_%e #\n", f);
		output("%pi MODIFY_%UM_%e\n\n", f);
	}

	/* Component deconstructor */
	if (field_not_empty()) {
		output("%pt PROC(");
		print_cons_tok_args(1, 0);
		output("\\\n    ) STATEMENT DECONS_%UM_%e #\n", f);
		output("%pi DECONS_%UM_%e\n\n", f);
	}

	/* Component destructor */
	output("%pt PROC(");
	output("\\\n\t%xr : DESTROYER :,");
	print_cons_tok_args(1, 0);
	output("\\\n    ) STATEMENT DESTROY_%UM_%e #\n", f);
	output("%pi DESTROY_%UM_%e\n\n", f);

	/* Aliasing tokens */
	if (al && !rng) {
		output("#ifdef %X_IO_ROUTINES\n\n");
		output("%pt PROC(\\\n");
		output("\t%xl : %UN :,\\\n");
		output("\t%xr : unsigned :\\\n");
		output("    ) STATEMENT NEW_ALIAS_%UM_%FN #\n");
		output("%pi NEW_ALIAS_%UM_%FN\n\n");

		output("%pt PROC(%xr : %UN :)\\\n    ");
		output("%xr : unsigned : GET_ALIAS_%UM_%FN #\n");
		output("%pt PROC(%xr : %UN :, %xr : unsigned :)\\\n    ");
		output("%xr : void : SET_ALIAS_%UM_%FN #\n");
		output("%pt PROC(%xr : unsigned :)\\\n    ");
		output("%xr : %UN : FIND_ALIAS_%UM_%FN #\n\n");
		output("%pi GET_ALIAS_%UM_%FN SET_ALIAS_%UM_%FN ");
		output("FIND_ALIAS_%UM_%FN\n\n");
		output("#endif\n\n");
	}

	output("\n");
}

/*
 * PRINT THE UNION OPERATIONS OUTPUT FILE
 *
 * For each union in the calculus there is an operations file.
 */
static void
print_union_ops_tok(char *dir, char *un)
{
	open_file(dir, un, OPS_SUFFIX);
	if (extra_headers) {
		output("#include \"%s%s\"\n", MAIN_PREFIX, MAIN_SUFFIX);
		output("#include <%s_ops.h>\n\n", MAIN_PREFIX);
	}

	comment("Operations for union %UN");
	output("%pt PROC(%xr : %UN :) %xr : unsigned : TAG_%UM #\n");
	output("%pi TAG_%UM\n\n\n");

	/* Operations on common components */
	LOOP_UNION_COMPONENT {
		comment("Operations for component %CN of union %UN");
		output("%pt PROC(%xr : %UN :)\\\n");
		output("    %xr : PTR(%CT) : %UM_%CN #\n");
		output("%pi %UM_%CN\n\n");
	}

	/* Operations on field components */
	LOOP_UNION_FIELD {
		int rng = DEREF_int(fld_set(CRT_FIELD));
		int hash = DEREF_int(fld_flag(CRT_FIELD));
		int al = (hash ? 1 : 0);
		if (rng)
		{
			comment("Operations for field set %FN_etc of union %UN");
			output("%pt %xc : unsigned : %UM_%FN_etc_tag #\n");
			output("%pt PROC(%xr : %UN :) ");
			output("%xr : int : IS_%UM_%FN_etc #\n");
			output("%pi %UM_%FN_etc_tag IS_%UM_%FN_etc\n\n");
			print_field_tok(rng, al);
		}

		comment("Operations for field %FN of union %UN");
		output("%pt %xc : unsigned : %UM_%FN_tag #\n");
		output("%pt PROC(%xr : %UN :) %xr : int : IS_%UM_%FN #\n");
		output("%pi %UM_%FN_tag IS_%UM_%FN\n\n");
		print_field_tok(0, al);
	}

	/* Map tables */
	LOOP_UNION_MAP {
		int hash = DEREF_int(map_flag(CRT_MAP));
		comment("Map %MN on union %UN");
		output("%pt PROC(\\\n");
		output("\t%xr : %UN :");
		if (hash)
		{
			output(",\\\n\t%xr : DESTROYER :");
		}
		LOOP_MAP_ARGUMENT output(",\\\n\t%xr : %AT :");
		output("\\\n    ) %xr : %MR : %MN_%UM #\n ");
		output("%pi %MN_%UM\n\n\n");
	}

	/* End of file */
	close_file();
}

/*
 * MAIN ACTION (TOKEN VERSION)
 *
 * This routine prints all the output files for the calculus (token
 * version).
 */
void
main_action_tok(char *dir)
{
	int ign = 0;
	output_c_code = 2;
	print_main_tok(dir);

	LOOP_UNION {
		LIST(MAP_P)maps;
		CLASS_ID_P cid = DEREF_ptr(un_id(CRT_UNION));
		char *un = DEREF_string(cid_name_aux(cid));
		print_union_ops_tok(dir, un);
		maps = DEREF_list(un_map(CRT_UNION));
		if (!IS_NULL_list(maps))
		{
			print_union_map_c(dir, un);
			print_union_hdr_c(dir, un);
			ign = 1;
		}
	}

	if (ign) {
		open_file(dir, IGNORE_PREFIX, DEF_SUFFIX);
		comment("Map ignore macros");
		LOOP_UNION {
			LOOP_UNION_MAP output("#define IGNORE_%MN_%UM%t40%d\n", 1);
		}
		output("\n");
		close_file();
	}

	if (extra_asserts) {
		open_file(dir, ASSERT_PREFIX, DEF_SUFFIX);
		comment("Dummy assertion function definitions");
		close_file();
	}
}

