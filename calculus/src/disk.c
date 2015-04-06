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
#include "disk.h"
#include "output.h"
#include "suffix.h"
#include "type_ops.h"

/*
 * OUTPUT ENUMERATION READING ROUTINE
 *
 * This routine outputs code for reading an enumeration type from disk.
 * This is done in two sections for long enumeration types.
 */
static void
disk_read_enum(void)
{
	number n;

	n = log2(DEREF_number(en_order(CRT_ENUM)));
	if (n <= 16) {
		output("    x_ = (%EN)READ_BITS(%n);\n", n);
	} else {
		n -= 16;
		output("    x_ = (%EN)READ_BITS(16);\n");
		output("    x_ += (((%EN)READ_BITS(%n)) << 16);\n", n);
	}
}

/*
 * OUTPUT STRUCTURE READING ROUTINE
 *
 * This routine outputs code for reading a structure type from disk.
 */
static void
disk_read_struct(void)
{
	LOOP_STRUCTURE_COMPONENT {
		TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
		output("    x_.%CN = READ_%TI();\n", t);
	}
}

/*
 * OUTPUT UNION READING ROUTINE
 *
 * This routine outputs code for reading a union type from disk.
 */
static void
disk_read_union(void)
{
	output("    x_ = NULL_%UM;\n");
	output("    if (READ_BITS(1) == 1) {\n");
	LOOP_UNION_COMPONENT output("\t%CT %CN;\n");
	output("\tunsigned tag_ = READ_BITS(%UO2);\n");
	output("\tswitch (tag_) {\n");

	LOOP_UNION_FIELD {
		int al = DEREF_int(fld_flag(CRT_FIELD));
		output("\t    case %UM_%FN_tag: {\n");
		LOOP_FIELD_COMPONENT output("\t\t%CT %CN;\n");

		/* Deal with aliasing */
		if (al) {
			output("\t\tunsigned alias_ = READ_ALIAS();\n");
			output("\t\tif (READ_BITS(1) == 0) {\n");
			output("\t\t    x_ = FIND_ALIAS_%UM_%FN(alias_);\n");
			output("\t\t    break;\n");
			output("\t\t}\n");
			if (al == 2) {
				output("\t\tUNALIAS_%UM_%FN(x_);\n");
				output("\t\tSET_ALIAS_%UM_%FN(x_, alias_);\n");
			} else {
				output("\t\tNEW_ALIAS_%UM_%FN(x_, alias_);\n");
			}
		}

		/* Read the components */
		LOOP_UNION_COMPONENT {
			TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
			output("\t\t%CN = READ_%TI();\n", t);
		}
		LOOP_FIELD_COMPONENT {
			TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
			output("\t\t%CN = READ_%TI();\n", t);
		}

		/* Assign components into x_ */
		if (al == 2) {
			output("\t\tUNIFY_%UM_%FN(");
			LOOP_UNION_COMPONENT output("%CN, ");
			LOOP_FIELD_COMPONENT output("%CN, ");
			output("x_);\n");
			output("\t\tSET_ALIAS_%UM_%FN(x_, alias_);\n");
		} else if (al) {
			LOOP_UNION_COMPONENT {
				TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
				output("\t\tCOPY_%TM(%UM_%CN(x_), %CN);\n", t);
			}
			LOOP_FIELD_COMPONENT {
				TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
				output("\t\tCOPY_%TM(%UM_%FN_%CN(x_), %CN);\n", t);
			}
		} else {
			int def = 0;
			output("\t\tMAKE_%UM_%FN(");
			LOOP_UNION_COMPONENT {
				string v = DEREF_string(cmp_value(CRT_COMPONENT));
				if (v == NULL) {
					output("%CN, ");
				} else {
					def = 1;
				}
			}
			LOOP_FIELD_COMPONENT {
				string v = DEREF_string(cmp_value(CRT_COMPONENT));
				if (v == NULL) {
					output("%CN, ");
				} else {
					def = 1;
				}
			}
			output("x_ );\n");
			if (def) {
				/* Override default values */
				LOOP_UNION_COMPONENT {
					string v = DEREF_string(cmp_value(CRT_COMPONENT));
					if (v) {
						TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
						output("\t\tCOPY_%TM ", t);
						output("(%UM_%CN(x_), %CN);\n");
					}
				}
				LOOP_FIELD_COMPONENT {
					string v = DEREF_string(cmp_value(CRT_COMPONENT));
					if (v) {
						TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
						output("\t\tCOPY_%TM ", t);
						output("(%UM_%FN_%CN(x_), %CN);\n");
					}
				}
			}
		}
		output("\t\tbreak;\n");
		output("\t    }\n");
	}

	output("\t}\n");
	output("    }\n");
}

/*
 * PRINT THE DISK READING DEFINITIONS
 *
 * This routine prints all the routines for reading the various types
 * from disk.
 */
static void
disk_read_def(char *dir)
{
	open_file(dir, READ_PREFIX, DEF_SUFFIX);
	print_include();

	comment("Disk reading function declarations");
	LOOP_TYPE {
		TYPE_P t = CRT_TYPE;
		TYPE t0 = DEREF_type(t);
		unsigned tag = TAG_type(t0);
		if (is_identity_type(t)) {
			output("#ifndef READ_%TI\n", t);
			output("#define READ_%TI() READ_%TJ()\n", t, t);
			output("#endif\n\n");
		} else if (tag != type_primitive_tag) {
			output("#ifndef READ_%TI\n", t);
			output("static %TT READ_%TI(void);\n", t, t);
			output("#endif\n\n");
		}
	}
	output("\n");

	/* Function definitions */
	LOOP_TYPE {
		TYPE_P t = CRT_TYPE;
		TYPE t0 = DEREF_type(t);
		unsigned tag = TAG_type(t0);
		if (!is_identity_type(t) && tag != type_primitive_tag) {
			/* Function header */
			output("/* Disk reading routine for %TT */\n\n", t);
			output("#ifndef READ_%TI\n\n", t);
			output("static %TT READ_%TI\n", t, t);
			output("(void)\n");
			output("{\n");
			output("    %TT x_;\n", t);

			/* Function body */
			switch (tag) {

			case type_enumeration_tag: {
				ENUM_P p = DEREF_ptr(type_enumeration_en(t0));
				LOOP_ENUM {
					if (EQ_ptr(CRT_ENUM, p)) {
						disk_read_enum();
						break;
					}
				}
				break;
			}

			case type_structure_tag: {
				STRUCTURE_P p = DEREF_ptr(type_structure_struc(t0));
				LOOP_STRUCTURE {
					if (EQ_ptr(CRT_STRUCTURE, p)) {
						disk_read_struct();
						break;
					}
				}
				break;
			}

			case type_onion_tag: {
				UNION_P p = DEREF_ptr(type_onion_un(t0));
				LOOP_UNION {
					if (EQ_ptr(CRT_UNION, p)) {
						disk_read_union();
						break;
					}
				}
				break;
			}

			case type_ptr_tag: {
				TYPE_P s = DEREF_ptr(type_ptr_sub(t0));
				output("    if (READ_BITS(1) == 0) {\n");
				output("\tx_ = NULL_ptr(%TT);\n", s);
				output("    } else {\n");
				output("\tx_ = MAKE_ptr(%TS);\n", s);
				output("\tCOPY_%TM(x_, READ_%TI());\n", s, s);
				output("    }\n");
				break;
			}

			case type_list_tag: {
				TYPE_P s = DEREF_ptr(type_list_sub(t0));
				output("    x_ = NULL_list(%TT);\n", s);
				output("    while (READ_BITS(1)) {\n");
				output("\t%TT y_;\n", s);
				output("\t%TT z_;\n", t);
				output("\ty_ = READ_%TI();\n", s);
				output("\tCONS_%TM(y_, NULL_list(%TT), z_);\n",
				       s, s);
				output("\tx_ = APPEND_list(x_, z_);\n");
				output("    }\n");
				break;
			}

			case type_stack_tag: {
				TYPE_P s = DEREF_ptr(type_stack_sub(t0));
				output("    LIST(%TT) w_;\n", s);
				output("    w_ = NULL_list(%TT);\n", s);
				output("    while (READ_BITS(1)) {\n");
				output("\t%TT y_;\n", s);
				output("\t%TT z_;\n", t);
				output("\ty_ = READ_%TI();\n", s);
				output("\tCONS_%TM(y_, NULL_list(%TT), z_);\n",
				       s, s);
				output("\tw_ = APPEND_list(w_, z_);\n");
				output("    }\n");
				output("    x_ = STACK_list(w_);\n");
				break;
			}

			case type_vec_tag: {
				TYPE_P s = DEREF_ptr(type_vec_sub(t0));
				output("    PTR(%TT)y_;\n", s);
				output("    %X_dim n_ = (%X_dim)READ_DIM();\n");
				output("    MAKE_vec(%TS, n_, x_);\n", s);
				output("    y_ = PTR_vec_ptr(");
				output("VEC_PTR_vec(x_));\n");
				output("    while (n_--) {\n");
				output("\tCOPY_%TM(y_, READ_%TI());\n", s, s);
				output("\ty_ = STEP_ptr(y_, %TS);\n", s);
				output("    }\n");
				break;
			}

			case type_vec_ptr_tag: {
				TYPE_P s = DEREF_ptr(type_vec_ptr_sub(t0));
				output("    VEC(%TT)y_;\n", s);
				output("    PTR(%TT)z_;\n", s);
				output("    MAKE_vec(%TS, (%X_dim)1, y_);\n", s);
				output("    x_ = VEC_PTR_vec(y_);\n");
				output("    z_ = PTR_vec_ptr(x_);\n");
				output("    COPY_%TM(z_, READ_%TI());\n", s, s);
				break;
			}
			}

			/* Function trailer */
			output("    return x_;\n");
			output("}\n\n");
			output("#endif\n\n\n", t);
		}
	}

	close_file();
}

/*
 * OUTPUT ENUMERATION WRITING ROUTINE
 *
 * This routine outputs code for writing an enumeration type to disk.
 * This is done in two sections for long enumeration types.
 */
static void
disk_write_enum(void)
{
	number n = log2(DEREF_number(en_order(CRT_ENUM)));
	if (n <= 16) {
		output("    WRITE_BITS(%n, (unsigned)x_);\n", n);
	} else {
		n -= 16;
		output("    WRITE_BITS(16, (unsigned)(x_ & 0xffff));\n");
		output("    WRITE_BITS(%n, (unsigned)(x_ >> 16));\n", n);
	}
}

/*
 * OUTPUT STRUCTURE WRITING ROUTINE
 *
 * This routine outputs code for writing a structure type to disk.
 */
static void
disk_write_struct(void)
{
	LOOP_STRUCTURE_COMPONENT {
		TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
		output("    WRITE_%TI(x_.%CN);\n", t);
	}
}

/*
 * OUTPUT UNION WRITING ROUTINE
 *
 * This routine outputs code for writing a union type to disk.
 */
static void
disk_write_union(void)
{
	int have_ucmp = 0;
	output("    if (IS_NULL_%UM(x_)) {\n");
	output("\tWRITE_BITS(1, (unsigned)0);\n");
	output("    } else {\n");
	LOOP_UNION_COMPONENT {
		output("\t%CT %CN;\n");
		have_ucmp = 1;
	}
	output("\tunsigned tag_ = TAG_%UM(x_);\n");
	output("\tWRITE_BITS(1, (unsigned)1);\n");
	output("\tWRITE_BITS(%UO2, tag_);\n");
	output("\tswitch (tag_) {\n");
	LOOP_UNION_FIELD {
		int have_cmp = have_ucmp;
		int al = DEREF_int(fld_flag(CRT_FIELD));
		output("\t    case %UM_%FN_tag: {\n");
		LOOP_FIELD_COMPONENT {
			output("\t\t%CT %CN;\n");
			have_cmp = 1;
		}

		/* Deal with aliasing */
		if (al) {
			output("\t\tunsigned alias_ = GET_ALIAS_%UM_%FN(x_);\n");
			output("\t\tif (alias_) {\n");
			output("\t\t    WRITE_ALIAS(alias_);\n");
			output("\t\t    WRITE_BITS(1, (unsigned)0);\n");
			output("\t\t    break;\n");
			output("\t\t}\n");
			output("\t\talias_ = ++crt_%X_alias;\n");
			output("\t\tSET_ALIAS_%UM_%FN(x_, alias_);\n");
			output("\t\tWRITE_ALIAS(alias_);\n");
			output("\t\tWRITE_BITS(1, (unsigned)1);\n");
		}

		/* Deconstruct union */
		if (have_cmp) {
			output("\t\tDECONS_%UM_%FN(");
			LOOP_UNION_COMPONENT output("%CN, ");
			LOOP_FIELD_COMPONENT output("%CN, ");
			output(" x_);\n");
		}

		/* Process further if necessary */
		if (al == 2) {
			output("\t\tALIAS_%UM_%FN(");
			LOOP_UNION_COMPONENT output("%CN, ");
			LOOP_FIELD_COMPONENT output("%CN, ");
			output(" x_);\n");
		}

		/* Write out components */
		LOOP_UNION_COMPONENT {
			TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
			output("\t\tWRITE_%TI(%CN);\n", t);
		}
		LOOP_FIELD_COMPONENT {
			TYPE_P t = DEREF_ptr(cmp_type(CRT_COMPONENT));
			output("\t\tWRITE_%TI(%CN);\n", t);
		}
		output("\t\tbreak;\n");
		output("\t    }\n");
	}
	output("\t}\n");
	output("    }\n");
}

/*
 * PRINT THE DISK WRITING DEFINITIONS
 *
 * This routine outputs all the routines for writing the various types
 * to disk.
 */
static void
disk_write_def(char *dir)
{
	open_file(dir, WRITE_PREFIX, DEF_SUFFIX);
	print_include();

	comment("Disk writing function declarations");
	LOOP_TYPE {
		TYPE_P t = CRT_TYPE;
		TYPE t0 = DEREF_type(t);
		unsigned tag = TAG_type(t0);
		if (is_identity_type(t)) {
			output("#ifndef WRITE_%TI\n", t);
			output("#define WRITE_%TI(A) WRITE_%TJ(A)\n", t, t);
			output("#endif\n\n");
		} else if (tag != type_primitive_tag) {
			output("#ifndef WRITE_%TI\n", t);
			output("static void WRITE_%TI(%TT);\n", t, t);
			output("#endif\n\n");
		}
	}
	output("\n");

	/* Function definitions */
	LOOP_TYPE {
		TYPE_P t = CRT_TYPE;
		TYPE t0 = DEREF_type(t);
		unsigned tag = TAG_type(t0);
		if (!is_identity_type(t) && tag != type_primitive_tag) {
			/* Function header */
			output ("/* Disk writing routine for %TT */\n\n", t );
			output("#ifndef WRITE_%TI\n\n", t);
			output("static void WRITE_%TI\n", t);
			output("\n");
			output("(%TT x_)\n", t);
			output("{\n");

			/* Function body */
			switch (tag) {
			case type_enumeration_tag: {
				ENUM_P p = DEREF_ptr(type_enumeration_en(t0));
				LOOP_ENUM {
					if (EQ_ptr(CRT_ENUM, p)) {
						disk_write_enum();
						break;
					}
				}
				break;
			}

			case type_structure_tag: {
				STRUCTURE_P p = DEREF_ptr(type_structure_struc(t0));
				LOOP_STRUCTURE {
					if (EQ_ptr(CRT_STRUCTURE, p)) {
						disk_write_struct();
						break;
					}
				}
				break;
			}

			case type_onion_tag: {
				UNION_P p = DEREF_ptr(type_onion_un(t0));
				LOOP_UNION {
					if (EQ_ptr(CRT_UNION, p)) {
						disk_write_union();
						break;
					}
				}
				break;
			}

			case type_ptr_tag: {
				TYPE_P s = DEREF_ptr(type_ptr_sub(t0));
				output("    if (IS_NULL_ptr(x_)) {\n");
				output("\tWRITE_BITS(1, (unsigned)0);\n");
				output("    } else {\n");
				output("\t%TT y_;\n\t", s);
				print_deref(s, "x_", "y_");
				output("\tWRITE_BITS(1, (unsigned)1);\n");
				output("\tWRITE_%TI(y_);\n", s);
				output("    }\n");
				break;
			}

			case type_list_tag: {
				TYPE_P s = DEREF_ptr(type_list_sub(t0));
				output("    while (!IS_NULL_list(x_)) {\n");
				output("\t%TT y_;\n\t", s);
				print_deref(s, "HEAD_list(x_)", "y_");
				output("\tWRITE_BITS(1, (unsigned)1);\n");
				output("\tWRITE_%TI(y_);\n", s);
				output("\tx_ = TAIL_list(x_);\n");
				output("    }\n");
				output("    WRITE_BITS(1, (unsigned)0);\n");
				break;
			}

			case type_stack_tag: {
				TYPE_P s = DEREF_ptr(type_stack_sub(t0));
				output("    LIST(%TT) w_ = LIST_stack(x_);\n", s);
				output("    while (!IS_NULL_list(w_)) {\n");
				output("\t%TT y_;\n\t", s);
				print_deref(s, "HEAD_list(w_)", "y_");
				output("\tWRITE_BITS(1, (unsigned)1);\n");
				output("\tWRITE_%TI(y_);\n", s);
				output("\tw_ = TAIL_list(w_);\n");
				output("    }\n");
				output("    WRITE_BITS(1, (unsigned)0);\n");
				break;
			}

			case type_vec_tag: {
				TYPE_P s = DEREF_ptr(type_vec_sub(t0));
				output("    %X_dim n_ = DIM_vec(x_);\n");
				output("    PTR(%TT)y_ ", s);
				output(" = PTR_vec_ptr(VEC_PTR_vec(x_));\n");
				output("    WRITE_DIM((unsigned)n_);\n");
				output("    while (n_--) {\n");
				output("\t%TT z_;\n\t", s);
				print_deref(s, "y_", "z_");
				output("\tWRITE_%TI(z_);\n", s);
				output("\ty_ = STEP_ptr(y_, %TS);\n", s);
				output("    }\n");
				break;
			}

			case type_vec_ptr_tag: {
				TYPE_P s = DEREF_ptr(type_vec_ptr_sub(t0));
				output("    PTR(%TT)y_ = PTR_vec_ptr(x_);\n", s);
				output("    %TT z_;\n    ", s);
				print_deref(s, "y_", "z_");
				output("    WRITE_%TI(z_);\n", s);
				break;
			}
			}

			/* Function trailer */
			output("    return;\n");
			output("}\n\n");
			output("#endif\n\n\n");
		}
	}

	close_file();
}

/*
 * MAIN DISK ACTION
 *
 * This routine prints all the output files for reading and writing the
 * calculus to disk.
 */
void
disk_action(char *dir)
{
	disk_read_def(dir);
	disk_write_def(dir);
}

