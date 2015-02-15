/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include "calculus.h"
#include "code.h"
#include "common.h"
#include "output.h"
#include "print.h"
#include "suffix.h"
#include "type_ops.h"


/*
 * PRINT A PRIMITIVE PRINTING ROUTINE
 *
 * This routine prints the body of the printing routine for the current
 * primitive.
 */

static void
printer_prim(void)
{
    output("    print_indent(f_, d_);\n");
    output("    (void)fprintf(f_, \"%%s = \", nm_);\n");
    output("    OUTPUT_%PM(f_, x_);\n");
    output("    (void)fprintf(f_, \" ;\\n\");\n");
    return;
}


/*
 * PRINT AN ENUMERATION PRINTING ROUTINE
 *
 * This routine prints the body of the printing routine for the current
 * enumeration.
 */

static void
printer_enum(void)
{
    output("    print_indent(f_, d_);\n");
    output("    (void)fprintf(f_, \"%%s = \", nm_);\n");
    output("    switch (x_) {\n");
    LOOP_ENUM_CONST {
	output("\tcase %EM_%ES: {\n");
	output("\t    (void)fprintf(f_, \"%ES ;\\n\");\n");
	output("\t    break;\n");
	output("\t}\n");
    }
    output("\tdefault: {\n");
    output("\t    (void)fprintf(f_, \"%%lu ;\\n\",");
    output(" (unsigned long)x_);\n");
    output("\t    break;\n");
    output("\t}\n");
    output("    }\n");
    return;
}


/*
 * PRINT A STRUCTURE PRINTING ROUTINE
 *
 * This routine prints the body of the printing routine for the current
 * structure.
 */

static void
printer_struct(void)
{
    output("    print_indent(f_, d_);\n");
    output("    (void)fprintf(f_, \"%%s = {\\n\", nm_);\n");
    LOOP_STRUCTURE_COMPONENT {
	TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
	output("    PRINT_%TI(f_, x_.%CN, \"%CN\", d_ + 1);\n", t);
    }
    output("    print_indent(f_, d_);\n");
    output("    (void)fprintf(f_, \"}\\n\");\n");
    return;
}


/*
 * PRINT A UNION COMPONENT PRINTING ROUTINE
 *
 * This routine prints the code for printing a component of a union.
 * The argument d gives the token for accessing the component.
 */

static void
printer_component(char *d)
{
    TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
    output("\t\t{\n");
    output("\t\t    %TT z_;\n", t);
    output("\t\t    ");
    print_deref(t, d, "z_");
    output("\t\t    PRINT_%TI(f_, z_, \"%CN\", d_ + 1);\n", t);
    output("\t\t}\n");
    return;
}


/*
 * PRINT A UNION PRINTING ROUTINE
 *
 * This routine prints the body of the printing routine for the current
 * primitive.
 */

static void
printer_union(void)
{
    output("    print_indent(f_, d_);\n");
    output("    if (IS_NULL_%UM(x_)) {\n");
    output("\t(void)fprintf(f_, \"%%s = NULL_%UM ;\\n\", nm_);\n");
    output("    } else {\n");
    output("\tswitch (TAG_%UM(x_)) {\n");
    LOOP_UNION_FIELD {
	int al = DEREF_int(fld_flag(CRT_FIELD));
	output("\t    case %UM_%FN_tag: {\n");
	if (al) {
	    output("\t\tunsigned alias_ = GET_ALIAS_%UM_%FN(x_);\n");
	    output("\t\tif (alias_) {\n");
	    output("\t\t    (void)fprintf(f_, \"%%s = ");
	    output("[%%u] ;\\n\", nm_, alias_);\n");
	    output("\t\t    break;\n");
	    output("\t\t}\n");
	    output("\t\talias_ = ++crt_%X_alias ;\n");
	    output("\t\tSET_ALIAS_%UM_%FN(x_, alias_);\n");
	    output("\t\t(void)fprintf(f_, \"%%s = [%%u] = {\\n\", ");
	    output("nm_, alias_);\n");
	} else {
	    output("\t\t(void)fprintf(f_, \"%%s = {\\n\", nm_);\n");
	}
	output("\t\tprint_indent(f_, d_ + 1);\n");
	output("\t\t(void)fprintf(f_, \"(tag) = %FN ;\\n\");\n");
	LOOP_UNION_COMPONENT printer_component("%UM_%CN(x_)");
	LOOP_FIELD_COMPONENT printer_component("%UM_%FN_%CN(x_)");
	output("\t\tprint_indent(f_, d_);\n");
	output("\t\t(void)fprintf(f_, \"}\\n\");\n");
	output("\t\tbreak;\n");
	output("\t    }\n");
    }
    output("\t    default : {\n");
    output("\t\t(void)fprintf(f_, \"%%s = ERROR!\\n\", nm_);\n");
    output("\t\tbreak;\n");
    output("\t    }\n");
    output("\t}\n");
    output("    }\n");
    return;
}


/*
 * PRINT A POINTER PRINTING ROUTINE
 *
 * This routine prints the body of the printing routine for a pointer
 * to s.
 */

static void
printer_ptr(TYPE_P s, char *ptr, char *nm, char *i)
{
    output("%s    print_indent(f_, d_);\n", i);
    output("%s    if (IS_NULL_ptr(%s)) {\n", i, nm);
    output("%s\t(void)fprintf(f_, ", i);
    output("\"%%s = NULL_ptr;\\n\", nm_);\n");
    output("%s    } else if (d_ < print_ptr_depth) {\n", i);
    output("%s\t%TT z_;\n", i, s);
    output("%s\t", i);
    print_deref(s, nm, "z_");
    output("%s\t(void)fprintf(f_, ", i);
    output("\"%%s = %s {\\n\", nm_);\n", ptr);
    output("%s\tPRINT_%TI(f_, z_, \"(%TI)\", d_ + 1);\n", i, s, s);
    output("%s\tprint_indent(f_, d_);\n", i);
    output("%s\t(void)fprintf(f_, \"}\\n\");\n", i);
    output("%s    } else {\n", i);
    output("%s\t(void)fprintf(f_, \"%%s = ", i);
    output("0x%%p ;\\n\", nm_, VOIDSTAR_ptr(%s));\n", nm);
    output("%s    }\n", i);
    return;
}


/*
 * PRINT A LIST PRINTING ROUTINE
 *
 * This routine prints the body of the printing routine for a list
 * of s named nm.
 */

static void
printer_list(TYPE_P s, char *nm)
{
    output("    print_indent(f_, d_);\n");
    output("    (void)fprintf(f_, \"%%s = LIST {\\n\", nm_);\n");
    output("    while (!IS_NULL_list(%s)) {\n", nm);
    output("\t%TT z_;\n", s);
    output("\tUN_CONS_%TM(z_, %s, %s);\n", s, nm, nm);
    output("\tPRINT_%TI(f_, z_, \"(%TI)\", d_ + 1);\n", s, s);
    output("\tif (!print_list_expand && !IS_NULL_list(%s)) {\n", nm);
    output("\t    print_indent(f_, d_ + 1);\n");
    output("\t    (void)fprintf(f_, \"(tail) = ");
    output("0x%%p ;\\n\", VOIDSTAR_list(%s));\n", nm);
    output("\t    break;\n");
    output("\t}\n");
    output("    }\n");
    output("    print_indent(f_, d_);\n");
    output("    (void)fprintf(f_, \"}\\n\");\n");
    return;
}


/*
 * PRINT A VECTOR PRINTING ROUTINE
 *
 * This routine prints the body of the printing routine for a vector
 * of s.
 */

static void
printer_vec(TYPE_P s)
{
    output("    print_indent(f_, d_);\n");
    output("    {\n");
    output("\t%X_dim n = DIM_vec(x_);\n");
    output("\tPTR(%TT) y_ = PTR_vec_ptr(VEC_PTR_vec(x_));\n", s);
    output("\t(void)fprintf(f_, \"%%s = {\\n\", nm_);\n");
    output("\twhile (n--) {\n");
    printer_ptr(s, "VEC", "y_", "\t");
    output("\t    y_ = STEP_ptr(y_, SIZE_%TM);\n", s);
    output("\t}\n");
    output("\tprint_indent(f_, d_);\n");
    output("\t(void)fprintf(f_, \"}\\n\");\n");
    output("    }\n");
    return;
}


/*
 * PRINT A VECTOR POINTER PRINTING ROUTINE
 *
 * This routine prints the body of the printing routine for a vector
 * pointer to s.
 */

static void
printer_vec_ptr(TYPE_P s)
{
    output("    PTR(%TT) y_ = PTR_vec_ptr(x_);\n", s);
    printer_ptr(s, "VEC_PTR", "y_", "");
    return;
}


/*
 * PRINT ALL PRINTING ROUTINES
 *
 * This routine prints all the printing routines.
 */

void
print_action(char *dir)
{
    open_file(dir, PRINT_PREFIX, DEF_SUFFIX);
    print_include();

    comment("Printing function declarations");
    LOOP_TYPE {
	TYPE_P t = CRT_TYPE;
	if (is_identity_type(t)) {
	    output("#ifndef PRINT_%TI\n", t);
	    output("#define PRINT_%TI(A, B, C, D)", t);
	    output("PRINT_%TJ((A), (B), (C), (D))\n", t);
	    output("#endif\n\n");
	} else {
	    output("#ifndef PRINT_%TI\n", t);
	    output("static void PRINT_%TI ", t);
	    output("(FILE *, %TT, char *, int);\n", t);
	    output("#endif\n\n");
	}
    }
    output("\n\n");

    comment("Printing variables");
    output("static int print_indent_step = 4;\n");
    output("static int print_ptr_depth = 1;\n");
    output("static int print_list_expand = 0;\n\n\n");

    comment("Printing indentation routine");
    output("static void print_indent\n");
    output("\n");
    output("(FILE *f, int d)\n");
    output("{\n");
    output("    int i = print_indent_step * d;\n");
    output("    while (i--) (void)fputc(' ', f);\n");
    output("    return;\n");
    output("}\n\n\n");

    /* Function definitions */
    LOOP_TYPE {
	TYPE_P t = CRT_TYPE;
	TYPE t0 = DEREF_type(t);
	unsigned tag = TAG_type(t0);
	if (!is_identity_type(t)) {
	    /* Function header */
	    int is_struct = 0;
	    output("/* Printing routines for %TT */\n\n", t);
	    output("#ifndef PRINT_%TI\n\n", t);
	    output("static void\n");
	    output("PRINT_%TI(FILE *f_, %TT x_, char *nm_, int d_)\n", t, t);
	    output("{\n");

	    /* Function body */
	    switch (tag) {
		case type_primitive_tag: {
		    PRIMITIVE_P p = DEREF_ptr(type_primitive_prim(t0));
		    LOOP_PRIMITIVE {
			if (EQ_ptr(CRT_PRIMITIVE, p)) {
			    printer_prim();
			    break;
			}
		    }
		    break;
		}
		case type_enumeration_tag: {
		    ENUM_P p = DEREF_ptr(type_enumeration_en(t0));
		    LOOP_ENUM {
			if (EQ_ptr(CRT_ENUM, p)) {
			    printer_enum();
			    break;
			}
		    }
		    break;
		}
		case type_structure_tag: {
		    STRUCTURE_P p = DEREF_ptr(type_structure_struc(t0));
		    LOOP_STRUCTURE {
			if (EQ_ptr(CRT_STRUCTURE, p)) {
			    printer_struct();
			    break;
			}
		    }
		    is_struct = 1;
		    break;
		}
		case type_onion_tag: {
		    UNION_P p = DEREF_ptr(type_onion_un(t0));
		    LOOP_UNION {
			if (EQ_ptr(CRT_UNION, p)) {
			    printer_union();
			    break;
			}
		    }
		    break;
		}
		case type_ptr_tag: {
		    TYPE_P s = DEREF_ptr(type_ptr_sub(t0));
		    printer_ptr(s, "PTR", "x_", "");
		    break;
		}
		case type_list_tag: {
		    TYPE_P s = DEREF_ptr(type_list_sub(t0));
		    printer_list(s, "x_");
		    break;
		}
		case type_stack_tag: {
		    TYPE_P s = DEREF_ptr(type_stack_sub(t0));
		    output("    LIST(%TT) y_ = LIST_stack(x_);\n", s);
		    printer_list(s, "y_");
		    break;
		}
		case type_vec_tag: {
		    TYPE_P s = DEREF_ptr(type_vec_sub(t0));
		    printer_vec(s);
		    is_struct = 1;
		    break;
		}
		case type_vec_ptr_tag: {
		    TYPE_P s = DEREF_ptr(type_vec_ptr_sub(t0));
		    printer_vec_ptr(s);
		    is_struct = 1;
		    break;
		}
	    }

	    /* Function trailer */
	    output("    return;\n");
	    output("}\n\n");

	    /* Debugging routine */
	    if (extra_asserts) {
		char *star = (is_struct ? "*" : "");
		output("#ifndef NDEBUG\n\n");
		output("void\n");
		output("DEBUG_%TI(%TT %sx_)\n", t, t, star);
		output("{\n    ");
		if (is_struct) {
			output("if (x_)");
		}
		output("PRINT_%TI(stdout, %sx_, ", t, star);
		output("\"%TI\", 0);\n", t);
		output("    return;\n");
		output("}\n\n");
		output("#endif\n\n");
	    }
	    output("#endif\n\n\n");
	}
    }

    close_file();
    return;
}
