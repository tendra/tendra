/*
 * Copyright (c) 2004, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  		 Crown Copyright (c) 1997
 *
 *  This TenDRA(r) Computer Program is subject to Copyright
 *  owned by the United Kingdom Secretary of State for Defence
 *  acting through the Defence Evaluation and Research Agency
 *  (DERA).  It is made available to Recipients with a
 *  royalty-free licence for its use, reproduction, transfer
 *  to other parties and amendment for any purpose not excluding
 *  product development provided that any such use et cetera
 *  shall be deemed to be acceptance of the following conditions:-
 *
 *      (1) Its Recipients shall ensure that this Notice is
 *      reproduced upon any copies or amended versions of it;
 *
 *      (2) Any amended version of it shall be clearly marked to
 *      show both the nature of and the organisation responsible
 *      for the relevant amendment or amendments;
 *
 *      (3) Its onward transfer from a recipient to another
 *      party shall be deemed to be that party's acceptance of
 *      these conditions;
 *
 *      (4) DERA gives no warranty or assurance as to its
 *      quality or suitability for any purpose and DERA accepts
 *      no liability whatsoever in relation to any use to which
 *      it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "calculus.h"
#include "code.h"
#include "common.h"
#include "lex.h"
#include "msgcat.h"
#include "output.h"
#include "suffix.h"
#include "type_ops.h"


/*
 *    OUTPUT FLAGS
 *
 *    The flag extra_asserts, if set to true, will cause the C implementation
 *    of the output to include assertions for run-time checks.  check_null is
 *    a string used in the assertions output.  extra_headers and map_proto
 *    are used for backwards compatibility on extra headers and union map
 *    prototypes.
 */

BoolT extra_asserts = FALSE;
BoolT extra_headers = FALSE;
BoolT map_proto = TRUE;
static char *check_null;


/*
 *    PRINT AN ASSIGNMENT COMPONENT
 *
 *    This routine prints the series of assignment operations to assign the
 *    value of type t given by nm to an offset p from the variable x%u_.  It
 *    returns the offset from x%u_ at the end of these assignments.
 */

static int
assign_component(TYPE_P t, int p, char *nm, int depth)
{
	TYPE t0 = DEREF_type (t);
	if (depth > MAX_TYPE_DEPTH) {
		MSG_cyclic_type_definition(name_type (t));
		return (p);
	}

	if (IS_type_ident (t0)) {
		/* Use identity definition */
		IDENTITY_P id = DEREF_ptr (type_ident_id (t0));
		TYPE_P s = DEREF_ptr (ident_defn (id));
		return (assign_component (s, p, nm, depth + 1));

	} else if (IS_type_structure (t0)) {
		/* Deal with structures componentwise */
		char buff [500];
		STRUCTURE_P str;
		LIST (COMPONENT_P) c;
		str = DEREF_ptr (type_structure_struc (t0));
		c = DEREF_list (str_defn (str));
		while (!IS_NULL_list (c)) {
			COMPONENT_P cmp = DEREF_ptr (HEAD_list (c));
			char *c_nm = DEREF_string (cmp_name (cmp));
			TYPE_P c_type = DEREF_ptr (cmp_type (cmp));
			int n = (int) strlen (nm) + (int) strlen (c_nm) + 8;
			if (n > (int) sizeof (buff)) {
				MSG_too_many_field_selectors (name_type (t));
				break;
			}
			(void)sprintf (buff, "%s.%s", nm, c_nm);
			p = assign_component (c_type, p, buff, depth + 1);
			c = TAIL_list (c);
		}
		return (p);
	}

	/* Other types are simple */
	output ("\t\tCOPY_%TM (x%u_ + %d, %e);\\\n", t, p, nm);
	return (p + size_type (t, 0));
}


/*
 *    PRINT A DEREFERENCE COMPONENT
 *
 *    This routine prints the series of dereference operations to assign the
 *    value of type t given by an offset p from the variable x%u_ into nm.  It
 *    returns the offset from x%u_ at the end of these dereferences.  depth is
 *    used to catch cyclic type definitions.
 */

static int
deref_component(TYPE_P t, int p, char *nm, int depth)
{
	TYPE t0 = DEREF_type (t);
	if (depth > MAX_TYPE_DEPTH) {
		MSG_cyclic_type_definition(name_type (t));
		return (p);
	}

	if (IS_type_ident (t0)) {
		/* Use identity definition */
		IDENTITY_P id = DEREF_ptr (type_ident_id (t0));
		TYPE_P s = DEREF_ptr (ident_defn (id));
		return (deref_component (s, p, nm, depth + 1));

	} else if (IS_type_structure (t0)) {
		/* Deal with structures componentwise */
		char buff [500];
		STRUCTURE_P str;
		LIST (COMPONENT_P) c;
		str = DEREF_ptr (type_structure_struc (t0));
		c = DEREF_list (str_defn (str));
		while (!IS_NULL_list (c)) {
			COMPONENT_P cmp = DEREF_ptr (HEAD_list (c));
			char *c_nm = DEREF_string (cmp_name (cmp));
			TYPE_P c_type = DEREF_ptr (cmp_type (cmp));
			int n = (int) strlen (nm) + (int) strlen (c_nm) + 8;
			if (n > (int) sizeof (buff)) {
				MSG_too_many_field_selectors (name_type (t));
				break;
			}
			(void)sprintf (buff, "%s.%s", nm, c_nm);
			p = deref_component (c_type, p, buff, depth + 1);
			c = TAIL_list (c);
		}
		return (p);
	}

	/* Other types are simple */
	if (is_complex_type (t)) {
		output ("\t\tDEREF_%TM (x%u_ + %d, %e);\\\n", t, p, nm);
	} else {
		output ("\t\t%e = DEREF_%TM (x%u_ + %d);\\\n", nm, t, p);
	}
	return (p + size_type (t, 0));
}


/*
 *    PRINT A DEREFERENCE INSTRUCTION
 *
 *    This routine prints code to dereference an object of type t from a
 *    into b.
 */

void
print_deref(TYPE_P t, char *a, char *b)
{
	if (is_complex_type (t)) {
		output ("DEREF_%TM (%e, %e);\n", t, a, b);
	} else {
		output ("%e = DEREF_%TM (%e);\n", b, t, a);
	}
	return;
}


/*
 *    PRINT FILE INCLUSIONS
 *
 *    This routine prints file inclusions for all the major output files.
 */

void
print_include(void)
{
	output ("#include \"%s%s\"\n", MAIN_PREFIX, MAIN_SUFFIX);
	LOOP_UNION output ("#include \"%UM%s\"\n", OPS_SUFFIX);
	output ("\n");
	return;
}


/*
 *    PRINT RUNTIME ASSERTION MACROS
 *
 *    These macros are used, if the extra_asserts variable is set, to make the
 *    output code a little more readable.  Moreover, if the checks need to
 *    be turned off, then ASSERTS may be undefined.
 */

static void
print_assert_decs(void)
{
	output ("#ifdef ASSERTS\n");
	output ("extern %X *check_null_%X ");
	output ("(%X *, const char *, int);\n");
	output ("extern %X *check_tag_%X ");
	output ("(%X *, unsigned, const char *, int);\n");
	output ("extern %X *check_tag_etc_%X ");
	output ("(%X *, unsigned, unsigned, const char *, int);\n");
	if (allow_vec) {
		output ("extern int check_int_size ");
		output ("(int, int, const char *, int);\n");
	}
	output ("#define\tCHECK_NULL(P)\\\n");
	output ("\t(check_null_%X ((P), __FILE__, __LINE__))\n");
	output ("#define\tCHECK_TAG(P, N)\\\n");
	output ("\t(check_tag_%X ((P), (unsigned)(N), ");
	output ("__FILE__, __LINE__))\n");
	output ("#define\tCHECK_TAG_ETC(P, L, U)\\\n");
	output ("\t(check_tag_etc_%X ((P), (unsigned)(L), ");
	output ("(unsigned)(U), __FILE__, __LINE__))\n");
	if (allow_vec) {
		output ("#define\tCHECK_INT(N, M)\\\n");
		output ("\t(check_int_size ((N), (M), ");
		output ("__FILE__, __LINE__))\n");
	}
	output ("#else\n");
	output ("#define\tCHECK_NULL(P)%t40(P)\n");
	output ("#define\tCHECK_TAG(P, N)%t40(P)\n");
	output ("#define\tCHECK_TAG_ETC(P, L, U)%t40(P)\n");
	if (allow_vec) output ("#define\tCHECK_INT(N, M)%t40(N)\n");
	output ("#endif\n\n\n");
	return;
}


/*
 *    PRINT RUN-TIME CHECK FUNCTIONS
 *
 *    If the assertion variable is set then these functions will be printed,
 *    they are to be used to perform run-time checks on the calculus.
 *    These functions are delivered to a special file.
 */

void
print_assert_fns(void)
{
	/* Assertion printing */
	output ("#ifndef assert_%X\n");
	output ("static void\nassert_%X");
	output ("(const char *s, const char *fn, int ln)\n");
	output ("{\n");
	output ("\t(void)fprintf(stderr, \"Assertion %%s failed, ");
	output ("%%s, line %%d.\\n\", s, fn, ln);\n");
	output ("\tabort();\n");
	output ("}\n");
	output ("#endif\n\n");

	/* Null pointer check */
	output ("%X *\ncheck_null_%X");
	output ("(%X *p, const char *fn, int ln)\n");
	output ("{\n");
	output ("\tif (p == NULL) ");
	output ("assert_%X (\"Null pointer\", fn, ln);\n");
	output ("\treturn (p);\n");
	output ("}\n\n");

	/* Union tag check */
	output ("%X *\ncheck_tag_%X");
	output ("(%X *p, unsigned t, const char *fn, int ln)\n");
	output ("{\n");
	output ("\tp = check_null_%X(p, fn, ln);\n");
	output ("\tif (p->ag_tag != t) ");
	output ("assert_%X(\"Union tag\", fn, ln);\n");
	output ("\treturn (p);\n");
	output ("}\n\n");

	/* Union tag range check */
	output ("%X *\ncheck_tag_etc_%X");
	output ("(%X *p, unsigned tl, unsigned tb ");
	output (", const char *fn, int ln)\n");
	output ("{\n");
	output ("\tp = check_null_%X (p, fn, ln);\n");
	output ("\tif (p->ag_tag < tl || p->ag_tag >= tb) {\n");
	output ("\t\tassert_%X(\"Union tag\", fn, ln);\n");
	output ("\t}\n");
	output ("\treturn (p);\n");
	output ("}\n\n");

	/* Vector trim range check */
	if (!allow_vec) return;
	output ("int\ncheck_int_size");
	output ("(int n, int m, const char *fn, int ln)\n");
	output ("{\n");
	output ("\tif (n > m) assert_%X(\"Vector bound\", fn, ln);\n");
	output ("\treturn (n);\n");
	output ("}\n\n");
	return;
}


/*
 *    MAXIMUM ALLOCATION CHUNK
 *
 *    This variable is used to keep track of the largest block used in
 *    the memory allocation routine.
 */

static int gen_max = 0;


/*
 *    FIND A MEMORY ALLOCATION INSTRUCTION
 *
 *    This routine returns the instruction for allocating a block of n
 *    objects.  gen_max is also kept up to date.
 */

static char *
gen(int n, char *nm)
{
	static char gbuff [100];
	(void)sprintf (gbuff, "GEN_%%X ( %d, TYPEID_%s )", n, nm);
	if (n > gen_max) gen_max = n;
	return (gbuff);
}


/*
 *    PRINT SIMPLE LIST CONSTRUCTORS
 *
 *    This routine prints the list construction and deconstruction routines
 *    for the type named nm of size sz.  d is true for simply dereferenced
 *    types.
 */

static void
print_simple_cons(char *nm, int sz, int d)
{
	/* CONS routine */
	char *g;
	output ("#define\tCONS_%e(A, B, C)\\\n", nm);
	output ("\t{\\\n");
	g = gen (sz + 1, "list");
	output ("\t\t%X *x%u_ = %e;\\\n", g);
	output ("\t\tCOPY_%e (x%u_ + 1, (A));\\\n", nm);
	output ("\t\tx%u_->ag_ptr = (B);\\\n");
	output ("\t\t(C) = x%u_;\\\n");
	output ("\t}\n\n");
	unique++;

	/* UN_CONS routine */
	output ("#define\tUN_CONS_%e(A, B, C)\\\n", nm);
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	if (d) {
		output ("\t\t(A) = DEREF_%e (x%u_ + 1);\\\n", nm);
	} else {
		output ("\t\tDEREF_%e (x%u_ + 1, (A));\\\n", nm);
	}
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t}\n\n");
	unique++;

	/* DESTROY_CONS routine */
	output ("#define\tDESTROY_CONS_%e(D, A, B, C)\\\n", nm);
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	if (d) {
		output ("\t\t(A) = DEREF_%e (x%u_ + 1);\\\n", nm);
	} else {
		output ("\t\tDEREF_%e (x%u_ + 1, (A));\\\n", nm);
	}
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t\t(D) (x%u_, %du);\\\n", sz + 1);
	output ("\t}\n\n");
	unique++;

	if (allow_stack) {
		/* PUSH routine */
		output ("#define\tPUSH_%e(A, B)\\\n", nm);
		output ("\t{\\\n");
		output ("\t\t%X **r%u_ = &(B);\\\n");
		g = gen (sz + 1, "stack");
		output ("\t\t%X *x%u_ = %e;\\\n", g);
		output ("\t\tCOPY_%e (x%u_ + 1, (A));\\\n", nm);
		output ("\t\tx%u_->ag_ptr = *r%u_;\\\n");
		output ("\t\t*r%u_ = x%u_;\\\n");
		output ("\t}\n\n");
		unique++;

		/* POP routine */
		output ("#define\tPOP_%e(A, B)\\\n", nm);
		output ("\t{\\\n");
		output ("\t\t%X **r%u_ = &(B);\\\n");
		output ("\t\t%X *x%u_ = %s(*r%u_);\\\n", check_null);
		if (d) {
			output ("\t\t(A) = DEREF_%e (x%u_ + 1);\\\n", nm);
		} else {
			output ("\t\tDEREF_%e (x%u_ + 1, (A));\\\n", nm);
		}
		output ("\t\t*r%u_ = x%u_->ag_ptr;\\\n");
		output ("\t\tdestroy_%X (x%u_, %du);\\\n", sz + 1);
		output ("\t}\n\n");
		unique++;
	}

	/* End of routine */
	output ("\n");
	return;
}


/*
 *    PRINT STRUCTURE DEFINITIONS
 *
 *    This routine prints all the structure declarations and definitions
 *    and all identity declarations.  Some care needs to be taken with the
 *    ordering of the structure definitions.  Cyclic structures will have
 *    already been detected, so there is no need to worry about them.
 */

void
print_struct_defn(void)
{
	int ok;
	comment ("Structure declarations");
	LOOP_STRUCTURE {
		output ("typedef struct %SM_tag %SN;\n");
		COPY_int (str_output (CRT_STRUCTURE), 0);
	}
	output ("\n\n");

	comment ("Identity type definitions");
	LOOP_IDENTITY output ("typedef %IT %IN;\n");
	output ("\n\n");

	comment ("Structure definitions");
	output ("#ifndef %X_STRUCT_DEFINED\n");
	output ("#define\t%X_STRUCT_DEFINED\n\n");
	do {
		ok = 1;
		LOOP_STRUCTURE {
			int pr = DEREF_int (str_output (CRT_STRUCTURE));
			if (pr == 0) {
				/* Check if all components have been printed */
				pr = 1;
				LOOP_STRUCTURE_COMPONENT {
					TYPE t0;
					TYPE_P t = DEREF_ptr (cmp_type (CRT_COMPONENT));
					t0 = DEREF_type (t);
					while (IS_type_ident (t0)) {
						IDENTITY_P id;
						id = DEREF_ptr (type_ident_id (t0));
						t = DEREF_ptr (ident_defn (id));
						t0 = DEREF_type (t);
					}
					if (IS_type_structure (t0)) {
						STRUCTURE_P str;
						str = DEREF_ptr (type_structure_struc (t0));
						pr = DEREF_int (str_output (str));
						if (pr == 0) break;
					}
				}
				if (pr) {
					/* Print structure definition */
					output ("struct %SM_tag {\n");
					LOOP_STRUCTURE_COMPONENT output ("\t%CT %CN;\n");
					output ("};\n\n");
					COPY_int (str_output (CRT_STRUCTURE), 1);
				} else {
					/* Structure definition postponed */
					output ("/* struct %SM_tag later */\n\n");
					ok = 0;
				}
			}
		}
	} while (!ok);
	output ("#endif /* %X_STRUCT_DEFINED */\n\n\n");
	return;
}


/*
 *    PRINT BASIC TYPES (C VERSION)
 *
 *    This routine prints the C versions of the basic type definitions.
 */

static void
print_types_c(void)
{
	int n;
	comment ("Primitive types");
	LOOP_PRIMITIVE {
		CLASS_ID_P c = DEREF_ptr (prim_id (CRT_PRIMITIVE));
		char *pn = DEREF_string (cid_name (c));
		char *pd = DEREF_string (prim_defn (CRT_PRIMITIVE));
		if (!streq (pn, pd)) output ("typedef %PD %PN;\n");
	}
	output ("\n\n");

	comment ("Basic types");
	if (allow_vec) output ("typedef unsigned %X_dim;\n\n");
	output ("typedef union %X_tag {\n");
	output ("\tunsigned ag_tag;\n");
	output ("\tunion %X_tag *ag_ptr;\n");
	if (allow_vec) output ("\t%X_dim ag_dim;\n");
	output ("\tunsigned ag_enum;\n");
	output ("\tunsigned long ag_long_enum;\n");
	LOOP_PRIMITIVE output ("\t%PN ag_prim_%PM;\n");
	output ("} %X;\n\n");
	output ("typedef %X *%X_PTR;\n\n");

	if (allow_vec) {
		output ("typedef struct {\n");
		output ("\t%X *vec;\n");
		output ("\t%X *ptr;\n");
		output ("} %X_VEC_PTR;\n\n");

		output ("typedef struct {\n");
		output ("\t%X_dim dim;\n");
		output ("\t%X_VEC_PTR elems;\n");
		output ("} %X_VEC;\n\n");
	}

	output ("#ifndef %X_DESTR_DEFINED\n");
	output ("#define\t%X_DESTR_DEFINED\n");
	output ("typedef void (*DESTROYER) ");
	output ("(%X *, unsigned);\n");
	output ("#endif\n\n");

	output ("#define\tPTR(A)\t%X_PTR\n");
	output ("#define\tLIST(A)\t%X_PTR\n");
	if (allow_stack) {
		output ("#define\tSTACK(A)\t%X_PTR\n");
	}
	if (allow_vec) {
		output ("#define\tVEC(A)\t%X_VEC\n");
		output ("#define\tVEC_PTR(A)\t%X_VEC_PTR\n");
	}
	output ("#define\tSIZE(A)\tint\n\n\n");

	if (extra_asserts) {
		comment ("Assertion macros");
		print_assert_decs ();
	}

	comment ("Enumeration definitions");
	LOOP_ENUM {
		number m = DEREF_number (en_order (CRT_ENUM));
		if (m > (number) 0x10000) {
			output ("typedef unsigned long %EN;\n");
		} else {
			output ("typedef unsigned %EN;\n");
		}
	}
	output ("\n\n");

	comment ("Union type definitions");
	LOOP_UNION output ("typedef %X *%UN;\n");
	output ("\n\n");

	print_struct_defn ();

	comment ("Function declarations");
	output ("extern %X *gen_%X (unsigned);\n");
	output ("extern void destroy_%X (%X *, unsigned);\n");
	output ("extern void dummy_destroy_%X ");
	output ("(%X *, unsigned);\n");
	output ("extern void destroy_%X_list ");
	output ("(%X *, unsigned);\n");
	output ("extern %X *append_%X_list (%X *,%X *);\n");
	output ("extern %X *end_%X_list (%X *);\n");
	output ("extern unsigned length_%X_list (%X *);\n");
	output ("extern %X *reverse_%X_list (%X *);\n");
	if (allow_vec) output ("extern %X_VEC empty_%X_vec;\n");
	output ("#ifdef %X_IO_ROUTINES\n");
	output ("extern unsigned crt_%X_alias;\n");
	output ("extern void set_%X_alias (%X *, unsigned);\n");
	output ("extern %X *find_%X_alias (unsigned);\n");
	output ("extern void clear_%X_alias (void);\n");
	output ("#endif\n");
	output ("\n\n");
	comment ("Run-time type information");
	output ("#ifndef GEN_%X\n");
	output ("#define\tGEN_%X(A, B)%t40gen_%X ((unsigned)(A))\n");
	output ("#endif\n");
	output ("#define\tTYPEID_ptr%t40%du\n", 0);
	output ("#define\tTYPEID_list%t40%du\n", 1);
	output ("#define\tTYPEID_stack%t40%du\n", 2);
	n = 3;
	LOOP_UNION {
		output ("#define\tTYPEID_%UM%t40%du\n", n);
		n++;
	}
	output ("\n\n");
	return;
}


/*
 *    PRINT POINTER CONSTRUCTS (C VERSION)
 *
 *    This routine prints the C versions of the pointer constructs.
 */

static void
print_ptr_c(void)
{
	/* Pointers */
	char *g;
	comment ("Definitions for pointers");
	output ("#define\tSTEP_ptr(A, B)%t40");
	output ("(%s(A) + B)\n", check_null);
	output ("#define\tSIZE_ptr(A)%t40%d\n", SIZE_PTR);
	output ("#define\tNULL_ptr(A)%t40((%X *)0)\n");
	output ("#define\tIS_NULL_ptr(A)%t40((A) == 0)\n");
	output ("#define\tEQ_ptr(A, B)%t40((A) == (B))\n");
	output ("#define\tMAKE_ptr(A)%t40GEN_%X ((A), TYPEID_ptr)\n");
	output ("#define\tDESTROY_ptr(A, B)%t40");
	output ("destroy_%X ((A), (unsigned)(B))\n");
	g = gen (1, "ptr");
	output ("#define\tUNIQ_ptr(A)%t40%e\n", g);
	output ("#define\tDESTROY_UNIQ_ptr(A)%t40");
	output ("destroy_%X ((A), 1u)\n");
	output ("#ifdef %X_IO_ROUTINES\n");
	output ("#define\tVOIDSTAR_ptr(A)%t40((void *)(A))\n");
	output ("#endif\n\n");

	/* Assignment and dereference of pointers */
	output ("#define\tCOPY_ptr(A, B)%t40");
	output ("(%s(A)->ag_ptr = (B))\n", check_null);
	output ("#define\tDEREF_ptr(A)%t40");
	output ("(%s(A)->ag_ptr)\n", check_null);

	/* Pointer list constructor */
	output ("#define\tCONS_ptr(A, B, C)\\\n");
	output ("\t{\\\n");
	g = gen (SIZE_PTR + 1, "list");
	output ("\t\t%X *x%u_ = %e;\\\n", g);
	output ("\t\tx%u_[1].ag_ptr = (A);\\\n");
	output ("\t\tx%u_->ag_ptr = (B);\\\n");
	output ("\t\t(C) = x%u_;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Pointer list deconstructor */
	output ("#define\tUN_CONS_ptr(A, B, C)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	output ("\t\t(A) = x%u_[1].ag_ptr;\\\n");
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Pointer list destructor */
	output ("#define\tDESTROY_CONS_ptr(D, A, B, C)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	output ("\t\t(A) = x%u_[1].ag_ptr;\\\n");
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t\t(D) (x%u_, 2u);\\\n");
	output ("\t}\n\n");
	unique++;

	if (allow_stack) {
		/* Pointer stack constructor */
		output ("#define\tPUSH_ptr(A, B)\\\n");
		output ("\t{\\\n");
		output ("\t\t%X **r%u_ = &(B);\\\n");
		g = gen (SIZE_PTR + 1, "stack");
		output ("\t\t%X *x%u_ = %e;\\\n", g);
		output ("\t\tx%u_[1].ag_ptr = (A);\\\n");
		output ("\t\tx%u_->ag_ptr = *r%u_;\\\n");
		output ("\t\t*r%u_ = x%u_;\\\n");
		output ("\t}\n\n");
		unique++;

		/* Pointer stack destructor */
		output ("#define\tPOP_ptr(A, B)\\\n");
		output ("\t{\\\n");
		output ("\t\t%X **r%u_ = &(B);\\\n");
		output ("\t\t%X *x%u_ = %s(*r%u_);\\\n", check_null);
		output ("\t\t(A) = x%u_[1].ag_ptr;\\\n");
		output ("\t\t*r%u_ = x%u_->ag_ptr;\\\n");
		output ("\t\tdestroy_%X (x%u_, 2u);\\\n");
		output ("\t}\n\n");
		unique++;
	}

	output ("\n");
	return;
}


/*
 *    PRINT LIST CONSTRUCTS (C VERSION)
 *
 *    This routine prints the C versions of the list constructs.
 */

static void
print_list_c(void)
{
	/* Lists */
	char *g;
	comment ("Definitions for lists");
	output ("#define\tHEAD_list(A)%t40");
	output ("(%s(A) + 1)\n", check_null);
	output ("#define\tPTR_TAIL_list(A)%t40");
	output ("(%s(A))\n", check_null);
	output ("#define\tTAIL_list(A)%t40");
	output ("(%s(A)->ag_ptr)\n", check_null);

	output ("#define\tLENGTH_list(A)%t40length_%X_list ((A))\n");
	output ("#define\tEND_list(A)%t40end_%X_list ((A))\n");
	output ("#define\tREVERSE_list(A)%t40reverse_%X_list ((A))\n");
	output ("#define\tAPPEND_list(A, B)%t40");
	output ("append_%X_list ((A), (B))\n\n");
	output ("#define\tSIZE_list(A)%t40%d\n", SIZE_LIST);
	output ("#define\tNULL_list(A)%t40((%X *) 0)\n");
	output ("#define\tIS_NULL_list(A)%t40((A) == 0)\n");
	output ("#define\tEQ_list(A, B)%t40((A) == (B))\n");
	g = gen (1, "list");
	output ("#define\tUNIQ_list(A)%t40%e\n", g);
	output ("#define\tDESTROY_UNIQ_list(A)%t40");
	output ("destroy_%X ((A), 1u)\n");
	output ("#ifdef %X_IO_ROUTINES\n");
	output ("#define\tVOIDSTAR_list(A)%t40((void *) (A))\n");
	output ("#endif\n\n");

	/* Destruction of lists */
	output ("#define\tDESTROY_list(A, B)\\\n");
	output ("\t{\\\n");
	output ("\t\tdestroy_%X_list ((A), (unsigned) (B));\\\n");
	output ("\t}\n\n");

	/* Assignment and dereference of lists */
	output ("#define\tCOPY_list(A, B)%t40");
	output ("(%s(A)->ag_ptr = (B))\n", check_null);
	output ("#define\tDEREF_list(A)%t40");
	output ("(%s(A)->ag_ptr)\n", check_null);

	/* List list constructor */
	output ("#define\tCONS_list(A, B, C)\\\n");
	output ("\t{\\\n");
	g = gen (SIZE_LIST + 1, "list");
	output ("\t\t%X *x%u_ = %e;\\\n", g);
	output ("\t\tx%u_[1].ag_ptr = (A);\\\n");
	output ("\t\tx%u_->ag_ptr = (B);\\\n");
	output ("\t\t(C) = x%u_;\\\n");
	output ("\t}\n\n");
	unique++;

	/* List list deconstructor */
	output ("#define\tUN_CONS_list(A, B, C)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	output ("\t\t(A) = x%u_[1].ag_ptr;\\\n");
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t}\n\n");
	unique++;

	/* List list destructor */
	output ("#define\tDESTROY_CONS_list(D, A, B, C)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	output ("\t\t(A) = x%u_[1].ag_ptr;\\\n");
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t\t(D) (x%u_, 2u);\\\n");
	output ("\t}\n\n");
	unique++;

	if (allow_stack) {
		/* List stack constructor */
		output ("#define\tPUSH_list(A, B)\\\n");
		output ("\t{\\\n");
		output ("\t%X **r%u_ = &(B);\\\n");
		g = gen (SIZE_LIST + 1, "stack");
		output ("\t\t%X *x%u_ = %e;\\\n", g);
		output ("\t\tx%u_[1].ag_ptr = (A);\\\n");
		output ("\t\tx%u_->ag_ptr = *r%u_;\\\n");
		output ("\t\t*r%u_ = x%u_;\\\n");
		output ("\t}\n\n");
		unique++;

		/* List stack destructor */
		output ("#define\tPOP_list(A, B)\\\n");
		output ("\t{\\\n");
		output ("\t\t%X **r%u_ = &(B);\\\n");
		output ("\t\t%X *x%u_ = %s(*r%u_);\\\n", check_null);
		output ("\t\t(A) = x%u_[1].ag_ptr;\\\n");
		output ("\t\t*r%u_ = x%u_->ag_ptr;\\\n");
		output ("\t\tdestroy_%X (x%u_, 2u);\\\n");
		output ("\t}\n\n");
		unique++;
	}

	output ("\n");
	return;
}


/*
 *    PRINT STACK CONSTRUCTS (C VERSION)
 *
 *    This routine prints the C versions of the stack constructs.
 */

static void
print_stack_c(void)
{
	/* Stacks */
	char *g;
	comment ("Definitions for stacks");
	output ("#define\tSIZE_stack(A)%t40%d\n", SIZE_STACK);
	output ("#define\tNULL_stack(A)%t40((%X *) 0)\n");
	output ("#define\tIS_NULL_stack(A)%t40((A) == 0)\n");
	output ("#define\tSTACK_list(A)%t40(A)\n");
	output ("#define\tLIST_stack(A)%t40(A)\n\n");

	/* Assignment and dereference of stacks */
	output ("#define\tCOPY_stack(A, B)%t40");
	output ("(%s(A)->ag_ptr = (B))\n", check_null);
	output ("#define\tDEREF_stack(A)%t40");
	output ("(%s(A)->ag_ptr)\n", check_null);

	/* Stack list constructor */
	output ("#define\tCONS_stack(A, B, C)\\\n");
	output ("\t{\\\n");
	g = gen (SIZE_STACK + 1, "list");
	output ("\t\t%X *x%u_ = %e;\\\n", g);
	output ("\t\tx%u_[1].ag_ptr = (A);\\\n");
	output ("\t\tx%u_->ag_ptr = (B);\\\n");
	output ("\t\t(C) = x%u_;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Stack list deconstructor */
	output ("#define\tUN_CONS_stack(A, B, C)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	output ("\t\t(A) = x%u_[1].ag_ptr;\\\n");
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Stack list destructor */
	output ("#define\tDESTROY_CONS_stack(D, A, B, C)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	output ("\t\t(A) = x%u_[1].ag_ptr;\\\n");
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t\t(D) (x%u_, 2u);\\\n");
	output ("\t}\n\n");
	unique++;

	if (allow_stack) {
		/* Stack stack constructor */
		output ("#define\tPUSH_stack(A, B)\\\n");
		output ("\t{\\\n");
		output ("\t%X **r%u_ = &(B);\\\n");
		g = gen (SIZE_STACK + 1, "stack");
		output ("\t\t%X *x%u_ = %e;\\\n", g);
		output ("\t\tx%u_[1].ag_ptr = (A);\\\n");
		output ("\t\tx%u_->ag_ptr = *r%u_;\\\n");
		output ("\t\t*r%u_ = x%u_;\\\n");
		output ("\t}\n\n");
		unique++;

		/* Stack stack destructor */
		output ("#define\tPOP_stack(A, B)\\\n");
		output ("\t{\\\n");
		output ("\t\t%X **r%u_ = &(B);\\\n");
		output ("\t\t%X *x%u_ = %s(*r%u_);\\\n", check_null);
		output ("\t\t(A) = x%u_[1].ag_ptr;\\\n");
		output ("\t\t*r%u_ = x%u_->ag_ptr;\\\n");
		output ("\t\tdestroy_%X (x%u_, 2u);\\\n");
		output ("\t}\n\n");
		unique++;
	}

	output ("\n");
	return;
}


/*
 *    PRINT VECTOR CONSTRUCTS (C VERSION)
 *
 *    This routine prints the C versions of the vector constructs.
 */

static void
print_vec_c(void)
{
	/* Vectors */
	char *g;
	comment ("Definitions for vectors");
	output ("#define\tDIM_vec(A)%t40((A).dim)\n");
	output ("#define\tPTR_ptr_vec(A)%t40");
	output ("(%s(A)[2].ag_ptr)\n", check_null);
	output ("#define\tDIM_ptr_vec(A)%t40((A)->ag_dim)\n");
	output ("#define\tSIZE_vec(A)%t40%d\n", SIZE_VEC);
	output ("#define\tNULL_vec(A)%t40empty_%X_vec\n\n");

	/* Vector creation */
	output ("#define\tMAKE_vec(SZ, U, RES)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X_VEC x%u_;\\\n");
	output ("\t\t%X_dim u%u_ = (U);\\\n");
	output ("\t\tx%u_.dim = u%u_;\\\n");
	output ("\t\tif (u%u_ == 0) u%u_ = 1;\\\n");
	output ("\t\tx%u_.elems.ptr = ");
	output ("GEN_%X ((SZ) * u%u_, TYPEID_ptr);\\\n");
	output ("\t\tx%u_.elems.vec = x%u_.elems.ptr;\\\n");
	output ("\t\t(RES) = x%u_;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Vector destroyer */
	output ("#define\tDESTROY_vec(V, SZ)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X_VEC x%u_;\\\n");
	output ("\t\tx%u_ = (V);\\\n");
	output ("\t\tdestroy_%X (x%u_.elems.ptr, ");
	output ("(unsigned) ((SZ) * x%u_.dim));\\\n");
	output ("\t}\n\n");
	unique++;

	/* Vector trimmer */
	output ("#define\tTRIM_vec(V, SZ, L, U, RES)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X_VEC x%u_;\\\n");
	if (extra_asserts) {
		output ("\t\tint u%u_, l%u_;\\\n");
		output ("\t\tx%u_ = (V);\\\n");
		output ("\t\tu%u_ = CHECK_INT ((U), DIM_vec (x%u_));\\\n");
		output ("\t\tl%u_ = CHECK_INT ((L), u%u_);\\\n");
		output ("\t\tx%u_.elems.ptr += ((SZ) * l%u_);\\\n");
		output ("\t\tx%u_.dim = (unsigned) (u%u_ - l%u_);\\\n");
	} else {
		output ("\t\tint l%u_ = (L);\\\n");
		output ("\t\tx%u_ = (V);\\\n");
		output ("\t\tx%u_.elems.ptr += ((SZ) * l%u_);\\\n");
		output ("\t\tx%u_.dim = (unsigned) ((U) - l%u_);\\\n");
	}
	output ("\t\t(RES) = x%u_;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Vector assignment */
	output ("#define\tCOPY_vec(A, B)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(A);\\\n", check_null);
	output ("\t\t%X_VEC y%u_;\\\n");
	output ("\t\ty%u_ = (B);\\\n");
	output ("\t\tx%u_[0].ag_dim = y%u_.dim;\\\n");
	output ("\t\tx%u_[1].ag_ptr = y%u_.elems.vec;\\\n");
	output ("\t\tx%u_[2].ag_ptr = y%u_.elems.ptr;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Vector dereference */
	output ("#define\tDEREF_vec(A, B)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(A);\\\n", check_null);
	output ("\t\t%X_VEC *y%u_ = &(B);\\\n");
	output ("\t\ty%u_->dim = x%u_[0].ag_dim;\\\n");
	output ("\t\ty%u_->elems.vec = x%u_[1].ag_ptr;\\\n");
	output ("\t\ty%u_->elems.ptr = x%u_[2].ag_ptr;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Vector list constructor */
	output ("#define\tCONS_vec(A, B, C)\\\n");
	output ("\t{\\\n");
	g = gen (SIZE_VEC + 1, "list");
	output ("\t\t%X *x%u_ = %e;\\\n", g);
	output ("\t\t%X_VEC y%u_;\\\n");
	output ("\t\ty%u_ = (A);\\\n");
	output ("\t\tx%u_[1].ag_dim = y%u_.dim;\\\n");
	output ("\t\tx%u_[2].ag_ptr = y%u_.elems.vec;\\\n");
	output ("\t\tx%u_[3].ag_ptr = y%u_.elems.ptr;\\\n");
	output ("\t\tx%u_->ag_ptr = (B);\\\n");
	output ("\t\t(C) = x%u_;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Vector list deconstructor */
	output ("#define\tUN_CONS_vec(A, B, C)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	output ("\t\t%X_VEC *y%u_ = &(A);\\\n");
	output ("\t\ty%u_->dim = x%u_[1].ag_dim;\\\n");
	output ("\t\ty%u_->elems.vec = x%u_[2].ag_ptr;\\\n");
	output ("\t\ty%u_->elems.ptr = x%u_[3].ag_ptr;\\\n");
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Vector list destructor */
	output ("#define\tDESTROY_CONS_vec(D, A, B, C)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	output ("\t\t%X_VEC *y%u_ = &(A);\\\n");
	output ("\t\ty%u_->dim = x%u_[1].ag_dim;\\\n");
	output ("\t\ty%u_->elems.vec = x%u_[2].ag_ptr;\\\n");
	output ("\t\ty%u_->elems.ptr = x%u_[3].ag_ptr;\\\n");
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t\t(D) (x%u_, 4u);\\\n");
	output ("\t}\n\n");
	unique++;

	if (allow_stack) {
		/* Vector stack constructor */
		output ("#define\tPUSH_vec(A, B)\\\n");
		output ("\t{\\\n");
		output ("\t\t%X **r%u_ = &(B);\\\n");
		g = gen (SIZE_VEC + 1, "stack");
		output ("\t\t%X *x%u_ = %e;\\\n", g);
		output ("\t\t%X_VEC y%u_;\\\n");
		output ("\t\ty%u_ = (A);\\\n");
		output ("\t\tx%u_[1].ag_dim = y%u_.dim;\\\n");
		output ("\t\tx%u_[2].ag_ptr = y%u_.elems.vec;\\\n");
		output ("\t\tx%u_[3].ag_ptr = y%u_.elems.ptr;\\\n");
		output ("\t\tx%u_->ag_ptr = *r%u_;\\\n");
		output ("\t\t*r%u_ = x%u_;\\\n");
		output ("\t}\n\n");
		unique++;

		/* Vector stack destructor */
		output ("#define\tPOP_vec(A, B)\\\n");
		output ("\t{\\\n");
		output ("\t\t%X **r%u_ = &(B);\\\n");
		output ("\t\t%X *x%u_ = %s(*r%u_);\\\n", check_null);
		output ("\t\t%X_VEC *y%u_ = &(A);\\\n");
		output ("\t\ty%u_->dim = x%u_[1].ag_dim;\\\n");
		output ("\t\ty%u_->elems.vec = x%u_[2].ag_ptr;\\\n");
		output ("\t\ty%u_->elems.ptr = x%u_[3].ag_ptr;\\\n");
		output ("\t\t*r%u_ = x%u_->ag_ptr;\\\n");
		output ("\t\tdestroy_%X (x%u_, 4u);\\\n");
		output ("\t}\n\n");
		unique++;
	}

	output ("\n");
	return;
}


/*
 *    PRINT VECTOR POINTER CONSTRUCTS (C VERSION)
 *
 *    This routine prints the C versions of the vector pointer constructs.
 */

static void
print_vec_ptr_c(void)
{
	/* Vector pointers */
	char *g;
	comment ("Definitions for vector pointers");
	output ("#define\tVEC_PTR_vec(A)%t40((A).elems)\n");
	output ("#define\tPTR_vec_ptr(A)%t40((A).ptr)\n");
	output ("#define\tSIZE_vec_ptr(A)%t40%d\n\n", SIZE_VEC_PTR);

	/* Vector pointer assignment */
	output ("#define\tCOPY_vec_ptr(A, B)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(A);\\\n", check_null);
	output ("\t\t%X_VEC_PTR y%u_;\\\n");
	output ("\t\ty%u_ = (B);\\\n");
	output ("\t\tx%u_->ag_ptr = y%u_.vec;\\\n");
	output ("\t\tx%u_[1].ag_ptr = y%u_.ptr;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Vector pointer dereference */
	output ("#define\tDEREF_vec_ptr(A, B)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(A);\\\n", check_null);
	output ("\t\t%X_VEC_PTR *y%u_ = &(B);\\\n");
	output ("\t\ty%u_->vec = x%u_->ag_ptr;\\\n");
	output ("\t\ty%u_->ptr = x%u_[1].ag_ptr;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Vector pointer list constructor */
	output ("#define\tCONS_vec_ptr(A, B, C)\\\n");
	output ("\t{\\\n");
	g = gen (SIZE_VEC_PTR + 1, "list");
	output ("\t\t%X *x%u_ = %e;\\\n", g);
	output ("\t\t%X_VEC_PTR y%u_;\\\n");
	output ("\t\ty%u_ = (A);\\\n");
	output ("\t\tx%u_[1].ag_ptr = y%u_.vec;\\\n");
	output ("\t\tx%u_[2].ag_ptr = y%u_.ptr;\\\n");
	output ("\t\tx%u_->ag_ptr = (B);\\\n");
	output ("\t\t(C) = x%u_;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Vector pointer list deconstructor */
	output ("#define\tUN_CONS_vec_ptr(A, B, C)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	output ("\t\t%X_VEC_PTR *y%u_ = &(A);\\\n");
	output ("\t\ty%u_->vec = x%u_[1].ag_ptr;\\\n");
	output ("\t\ty%u_->ptr = x%u_[2].ag_ptr;\\\n");
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t}\n\n");
	unique++;

	/* Vector pointer list destructor */
	output ("#define\tDESTROY_CONS_vec_ptr(D, A, B, C)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(C);\\\n", check_null);
	output ("\t\t%X_VEC_PTR *y%u_ = &(A);\\\n");
	output ("\t\ty%u_->vec = x%u_[1].ag_ptr;\\\n");
	output ("\t\ty%u_->ptr = x%u_[2].ag_ptr;\\\n");
	output ("\t\t(B) = x%u_->ag_ptr;\\\n");
	output ("\t\t(D) (x%u_, 3u);\\\n");
	output ("\t}\n\n");
	unique++;

	if (allow_stack) {
		/* Vector stack constructor */
		output ("#define\tPUSH_vec_ptr(A, B)\\\n");
		output ("\t{\\\n");
		output ("\t\t%X **r%u_ = &(B);\\\n");
		g = gen (SIZE_VEC_PTR + 1, "stack");
		output ("\t\t%X *x%u_ = %e;\\\n", g);
		output ("\t\t%X_VEC_PTR y%u_;\\\n");
		output ("\t\ty%u_ = (A);\\\n");
		output ("\t\tx%u_[1].ag_ptr = y%u_.vec;\\\n");
		output ("\t\tx%u_[2].ag_ptr = y%u_.ptr;\\\n");
		output ("\t\tx%u_->ag_ptr = *r%u_;\\\n");
		output ("\t\t*r%u_ = x%u_;\\\n");
		output ("\t}\n\n");
		unique++;

		/* Vector stack destructor */
		output ("#define\tPOP_vec_ptr(A, B)\\\n");
		output ("\t{\\\n");
		output ("\t\t%X **r%u_ = &(B);\\\n");
		output ("\t\t%X *x%u_ = %s(*r%u_);\\\n", check_null);
		output ("\t\t%X_VEC *y%u_ = &(A);\\\n");
		output ("\t\ty%u_->vec = x%u_[1].ag_ptr;\\\n");
		output ("\t\ty%u_->ptr = x%u_[2].ag_ptr;\\\n");
		output ("\t\t*r%u_ = x%u_->ag_ptr;\\\n");
		output ("\t\tdestroy_%X (x%u_, 3u);\\\n");
		output ("\t}\n\n");
		unique++;
	}

	output ("\n");
	return;
}


/*
 *    PRINT SIZE CONSTRUCTS (C VERSION)
 *
 *    This routine prints the C versions of the size constructs.
 */

static void
print_size_c(void)
{
	comment ("Definitions for sizes");
	output ("#define\tSCALE(A, B)%t40((A) * (int) (B))\n\n\n");
	return;
}


/*
 *    PRINT PRIMITIVE CONSTRUCTS (C VERSION)
 *
 *    This routine prints the C versions of the primitive constructs.
 */

static void
print_prim_c(void)
{
	comment ("Definitions for primitive %PN");
	output ("#define\tSIZE_%PM%t40%d\n\n", SIZE_PRIM);
	output ("#define\tCOPY_%PM(A, B)%t40");
	output ("(%s(A)->ag_prim_%PM = (B))\n", check_null);
	output ("#define\tDEREF_%PM(A)%t40");
	output ("(%s(A)->ag_prim_%PM)\n", check_null);
	print_simple_cons ("%PM", SIZE_PRIM, 1);
	return;
}


/*
 *    PRINT ENUMERATION CONSTANTS
 *
 *    This routine prints the definitions of the enumeration constants.
 */

void
print_enum_consts(void)
{
	number n = DEREF_number (en_order (CRT_ENUM));
	if (n > (number) 0x10000) {
		output ("#ifdef __STDC__\n");
		LOOP_ENUM_CONST output ("#define\t%EM_%ES%t40((%EN) %EVUL)\n");
		output ("#define\tORDER_%EM%t40(%EOUL)\n");
		output ("#else\n");
	}
	LOOP_ENUM_CONST output ("#define\t%EM_%ES%t40((%EN) %EV)\n");
	output ("#define\tORDER_%EM%t40((unsigned long) %EO)\n");
	if (n > (number) 0x10000) {
		output ("#endif\n");
	}
	return;
}


/*
 *    PRINT ENUMERATION CONSTRUCTS (C VERSION)
 *
 *    This routine prints the C versions of the enumeration constructs.
 */

static void
print_enum_c(void)
{
	char *fld = "ag_enum";
	number n = DEREF_number (en_order (CRT_ENUM));
	if (n > (number) 0x10000) fld = "ag_long_enum";
	comment ("Definitions for enumeration %EN");
	print_enum_consts ();
	output ("#define\tSIZE_%EM%t40%d\n\n", SIZE_ENUM);
	output ("#define\tCOPY_%EM(A, B)%t40");
	output ("(%s(A)->%s = (B))\n", check_null, fld);
	output ("#define\tDEREF_%EM(A)%t40");
	output ("(%s(A)->%s)\n", check_null, fld);
	if (DEREF_int (en_lists (CRT_ENUM))) {
		print_simple_cons ("%EM", SIZE_ENUM, 1);
	} else {
		output ("\n\n");
	}
	return;
}


/*
 *    PRINT STRUCTURE CONSTRUCTS (C VERSION)
 *
 *    This routine prints the C versions of the structure constructs.
 */

static void
print_struct_c(void)
{
	/* Structure constructors etc. */
	int posn;
	int sz = 0;
	STRUCTURE_P base = DEREF_ptr (str_base (CRT_STRUCTURE));

	comment ("Definitions for structure %SN");
	LOOP_STRUCTURE_COMPONENT {
		TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
		output ("#define\t%SM_%CN(P)%t40");
		output ("((P) + %d)\n", sz);
		sz += size_type (ct, 0);
	}
	output ("#define\tSIZE_%SM%t40%d\n\n", sz);

	output ("#define\tCOPY_%SM(A, B)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(A);\\\n", check_null);
	output ("\t\t%SN y%u_;\\\n");
	output ("\t\ty%u_ = (B);\\\n");
	posn = 0;
	LOOP_STRUCTURE_COMPONENT {
		TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
		posn = assign_component (ct, posn, "y%u_.%CN", 0);
	}
	output ("\t}\n\n");
	unique++;

	output ("#define\tDEREF_%SM(A, B)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(A);\\\n", check_null);
	output ("\t\t%SN *y%u_ = &(B);\\\n");
	posn = 0;
	LOOP_STRUCTURE_COMPONENT {
		TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
		posn = deref_component (ct, posn, "y%u_->%CN", 0);
	}
	output ("\t}\n\n");
	unique++;

	output ("#define\tMAKE_%SM(");
	LOOP_STRUCTURE_COMPONENT {
		string v = DEREF_string (cmp_value (CRT_COMPONENT));
		if (v == NULL) output ("%CN_, ");
	}
	output ("%SM_)\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = %s(%SM_);\\\n", check_null);
	posn = 0;
	LOOP_STRUCTURE_COMPONENT {
		TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
		string v = DEREF_string (cmp_value (CRT_COMPONENT));
		if (v == NULL) v = "(%CN_)";
		posn = assign_component (ct, posn, v, 0);
	}
	output ("\t}\n\n");
	unique++;

	if (!IS_NULL_ptr (base)) {
		CLASS_ID_P id = DEREF_ptr (str_id (base));
		char *nm = DEREF_string (cid_name_aux (id));
		output ("#define\tCONVERT_%SM_%s(P)%t40(P)\n\n", nm);
	}

	print_simple_cons ("%SM", sz, 0);
	return;
}


/*
 *    PRINT UNION CONSTRUCTS (C VERSION)
 *
 *    This routine prints the C versions of the union constructs.
 */

static void
print_union_c(void)
{
	UNION_P base = DEREF_ptr (un_base (CRT_UNION));

	comment ("Definitions for union %UN");
	output ("#define\tORDER_%UM%t40%UOu\n");
	output ("#define\tSIZE_%UM%t40%d\n", SIZE_UNION);
	output ("#define\tNULL_%UM%t40((%UN) 0)\n");
	output ("#define\tIS_NULL_%UM(A)%t40((A) == 0)\n");
	output ("#define\tEQ_%UM(A, B)%t40((A) == (B))\n\n");
	output ("#define\tCOPY_%UM(A, B)%t40");
	output ("(%s(A)->ag_ptr = (B))\n", check_null);
	output ("#define\tDEREF_%UM(A)%t40");
	output ("(%s(A)->ag_ptr)\n\n", check_null);

	if (!IS_NULL_ptr (base)) {
		CLASS_ID_P id = DEREF_ptr (un_id (base));
		char *nm = DEREF_string (cid_name_aux (id));
		output ("#define\tCONVERT_%UM_%s(P)%t40(P)\n\n", nm);
	}

	print_simple_cons ("%UM", SIZE_UNION, 1);
	return;
}


/*
 *    PRINT THE MAIN OUTPUT FILE
 *
 *    This routine prints the main output file, describing the implementation
 *    of the various types described in the calculus.
 */

static void
print_main_c(void)
{
	if (extra_headers) {
		output ("#include \"%s_bscs.h\"\n\n", MAIN_PREFIX);
	}
	output ("#ifndef %X_NAME\n");
	output ("#define\t%X_NAME%t40\"%X\"\n");
	output ("#define\t%X_VERSION%t40\"%V\"\n");
	output ("#define\t%X_SPECIFICATION%t40%d\n", 0);
	output ("#define\t%X_IMPLEMENTATION%t40%d\n", 1);
	output ("#endif\n\n\n");

	print_types_c ();
	print_ptr_c ();
	print_list_c ();
	if (allow_stack) {
		print_stack_c ();
	}
	if (allow_vec) {
		print_vec_c ();
		print_vec_ptr_c ();
	}
	print_size_c ();

	LOOP_PRIMITIVE print_prim_c ();
	LOOP_ENUM print_enum_c ();
	LOOP_STRUCTURE print_struct_c ();
	LOOP_UNION print_union_c ();

	if (extra_headers) {
		output ("#include \"%s_term.h\"\n\n", MAIN_PREFIX);
	}
	return;
}


/*
 *    PRINT ARGUMENTS FOR A UNION CONSTRUCTOR
 *
 *    This routine prints the list of arguments for a union constructor and
 *    similar functions.
 */

static void
print_cons_args(int d, char *suff)
{
	LOOP_UNION_COMPONENT {
		string v = DEREF_string (cmp_value (CRT_COMPONENT));
		if (v == NULL || d == 0) output ("%CN%s, ", suff);
	}
	LOOP_FIELD_COMPONENT {
		string v = DEREF_string (cmp_value (CRT_COMPONENT));
		if (v == NULL || d == 0) output ("%CN%s, ", suff);
	}
	output ("%X_%UM");
	return;
}


/*
 *    DOES THE CURRENT FIELD HAVE ANY COMPONENTS?
 *
 *    This routine returns 1 if the current field of the current union has
 *    a component, and 0 otherwise.
 */

int
field_not_empty(void)
{
	LIST (COMPONENT_P) c;
	c = DEREF_list (un_s_defn (CRT_UNION));
	if (!IS_NULL_list (c)) return (1);
	c = DEREF_list (fld_defn (CRT_FIELD));
	if (!IS_NULL_list (c)) return (1);
	return (0);
}


/*
 *    PRINT FIELD SELECTOR OPERATIONS
 *
 *    This routine prints the operations on field selectors (C version).
 *    sz gives the size of the common union components.  tag is the field
 *    tag number (or -1 for untagged unions).  rng gives the number of
 *    elements in the field set (if appropriate).  al is true if the
 *    field is aliased.
 */

static void
print_field_c(int sz, int tag, int rng, int al)
{
	char *g;
	int posn = 0;
	char *f = (rng ? "%FN_etc" : "%FN");

	LOOP_FIELD_COMPONENT {
		TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
		output ("#define\t%UM_%e_%CN(P)%t40", f);
		if (extra_asserts && tag != -1) {
			if (rng) {
				output ("(CHECK_TAG_ETC ((P), %d, %d) + %d)\n",
				  tag, tag + rng, sz);
			} else {
				output ("(CHECK_TAG ((P), %d) + %d)\n", tag, sz);
			}
		} else {
			output ("((P) + %d)\n", sz);
		}
		sz += size_type (ct, 0);
	}

	/* Component constructor */
	output ("\n#define MAKE_%UM_%e(", f);
	if (rng) output ("tag, ");
	print_cons_args (1, "_");
	output (")\\\n");
	output ("\t{\\\n");
	g = gen (sz + al, "%UM");
	output ("\t\t%X *x%u_ = %e;\\\n", g);
	if (tag != -1) {
		if (rng) {
			output ("\t\tx%u_->ag_tag = (tag);\\\n");
		} else {
			output ("\t\tx%u_->ag_tag = %d;\\\n", tag);
		}
		posn = 1;
	}
	LOOP_UNION_COMPONENT {
		TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
		string v = DEREF_string (cmp_value (CRT_COMPONENT));
		if (v == NULL) v = "(%CN_)";
		posn = assign_component (ct, posn, v, 0);
	}
	LOOP_FIELD_COMPONENT {
		TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
		string v = DEREF_string (cmp_value (CRT_COMPONENT));
		if (v == NULL) v = "(%CN_)";
		posn = assign_component (ct, posn, v, 0);
	}
	if (al) output ("\t\tx%u_[%d].ag_tag = 0;\\\n", sz);
	if (rng && extra_asserts) {
		output ("\t\t(%X_%UM) = CHECK_TAG_ETC (x%u_, %d, %d);\\\n",
		  tag, tag + rng);
	} else {
		output ("\t\t(%X_%UM) = x%u_;\\\n");
	}
	output ("\t}\n\n");
	unique++;

	/* Tag modifier */
	if (rng) {
		output ("#define\tMODIFY_%UM_%e(tag, %X_%UM)\\\n", f);
		output ("\t{\\\n");
		if (extra_asserts) {
			output ("\t\t%X *x%u_ = CHECK_TAG_ETC");
			output (" ((%X_%UM), %d, %d);\\\n", tag, tag + rng);
			output ("\t\tx%u_->ag_tag = (tag);\\\n");
			output ("\t\t(void) CHECK_TAG_ETC");
			output (" (x%u_, %d, %d);\\\n", tag, tag + rng);
		} else {
			output ("\t\t(%X_%UM)->ag_tag = (tag);\\\n");
		}
		output ("\t}\n\n");
		unique++;
	}

	/* Component deconstructor */
	if (field_not_empty ()) {
		output ("#define\tDECONS_%UM_%e(", f);
		print_cons_args (0, "_");
		output (")\\\n");
		output ("\t{\\\n");
		output ("\t\t%X *x%u_ = ");
		if (tag != -1) {
			if (extra_asserts) {
				if (rng) {
					output ("CHECK_TAG_ETC ((%X_%UM), %d, %d);\\\n",
					  tag, tag + rng);
				} else {
					output ("CHECK_TAG ((%X_%UM), %d);\\\n", tag);
				}
			} else {
				output ("(%X_%UM);\\\n");
			}
			posn = 1;
		} else {
			output ("(%X_%UM);\\\n");
			posn = 0;
		}
		LOOP_UNION_COMPONENT {
			TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
			posn = deref_component (ct, posn, "(%CN_)", 0);
		}
		LOOP_FIELD_COMPONENT {
			TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
			posn = deref_component (ct, posn, "(%CN_)", 0);
		}
		output ("\t}\n\n");
		unique++;
	}

	/* Component destructor */
	output ("#define\tDESTROY_%UM_%e(destroyer_, ", f);
	print_cons_args (0, "_");
	output (")\\\n");
	output ("\t{\\\n");
	output ("\t\t%X *x%u_ = ");
	if (tag != -1) {
		if (extra_asserts) {
			if (rng) {
				output ("CHECK_TAG_ETC ((%X_%UM), %d, %d);\\\n",
				  tag, tag + rng);
			} else {
				output ("CHECK_TAG ((%X_%UM), %d);\\\n", tag);
			}
		} else {
			output ("(%X_%UM);\\\n");
		}
		posn = 1;
	} else {
		output ("(%X_%UM);\\\n");
		posn = 0;
	}
	LOOP_UNION_COMPONENT {
		TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
		posn = deref_component (ct, posn, "(%CN_)", 0);
	}
	LOOP_FIELD_COMPONENT {
		TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
		posn = deref_component (ct, posn, "(%CN_)", 0);
	}
	output ("\t\t(destroyer_) (x%u_, %du);\\\n", sz + al);
	output ("\t}\n\n");
	unique++;

	/* Aliasing commands */
	if (al && !rng) {
		output ("#ifdef %X_IO_ROUTINES\n\n");
		output ("#define\tNEW_ALIAS_%UM_%FN(P, N)\\\n");
		output ("\t{\\\n");
		g = gen (sz + al, "list");
		output ("\t\t%X *x%u_ = %e;\\\n", g);
		output ("\t\tunsigned a%u_ = (N);\\\n");
		if (tag != -1) output ("\tx%u_->ag_tag = %d;\\\n", tag);
		output ("\t\tx%u_[%d].ag_tag = a%u_;\\\n", sz);
		output ("\t\tset_%X_alias (x%u_ + %d, a%u_);\\\n", sz);
		output ("\t\t(P) = x%u_;\\\n");
		output ("\t}\n\n");
		unique++;

		output ("#define\tGET_ALIAS_%UM_%FN(P)%t40");
		output ("((%s(P) + %d)->ag_tag)\n", check_null, sz);
		output ("#define\tSET_ALIAS_%UM_%FN(P, N)%t40");
		output ("set_%X_alias (%s(P) + %d, (N))\n", check_null, sz);
		output ("#define\tFIND_ALIAS_%UM_%FN(N)%t40");
		output ("(find_%X_alias (N) - %d)\n\n", sz);
		output ("#endif\n\n");
	}
	output ("\n");
	return;
}


/*
 *    PRINT DECLARATION FOR A UNION MAP TABLE
 *
 *    This routine prints the type of the current map table.
 */

static void
print_map_table(int d)
{
	output ("%MR (*%MN_%UM_table[ORDER_%UM])");
	if (map_proto) {
		output ("\n\t(%UN");
		if (d) output (", DESTROYER");
		LOOP_MAP_ARGUMENT output (", %AT");
		output (")");
	} else {
		output (" ()");
	}
	return;
}


/*
 *    PRINT ARGUMENTS FOR A UNION MAP
 *
 *    This routine prints the list of arguments for the current map.  The
 *    argument d, if present, gives the destructor argument.
 */

void
print_map_args(char *d)
{
	output ("(%X_%UM");
	if (d) output (", %e", d);
	LOOP_MAP_ARGUMENT output (", %AN");
	output (")");
	return;
}


/*
 *    PRINT THE UNION OPERATIONS OUTPUT FILE
 *
 *    For each union in the calculus there is an operations file.
 */

void
print_union_ops_c(char *dir, char *un)
{
	int sz = 1;
	int tag = 0;
	int is_tagged = 1;
	open_file (dir, un, OPS_SUFFIX);
	if (extra_headers) {
		output ("#include \"%s%s\"\n", MAIN_PREFIX, MAIN_SUFFIX);
		output ("#include <%s_ops.h>\n\n", MAIN_PREFIX);
	}

	/* Check for unions with one field */
	LOOP_UNION_FIELD tag++;
	if (tag < 2) {
		sz = 0;
		is_tagged = 0;
	}

	comment ("Operations for union %UN");
	output ("#define\tTAG_%UM(P)%t40", check_null);
	if (is_tagged) {
		output ("(%s(P)->ag_tag)\n\n\n", check_null);
	} else {
		output ("0u\n\n\n");
	}

	/* Operations on common components */
	LOOP_UNION_COMPONENT {
		TYPE_P ct = DEREF_ptr (cmp_type (CRT_COMPONENT));
		comment ("Operations for component %CN of union %UN");
		output ("#define\t%UM_%CN(P)%t40");
		output ("(%s(P) + %d)\n\n\n", check_null, sz);
		sz += size_type (ct, 0);
	}

	/* Operations on field components */
	tag = 0;
	LOOP_UNION_FIELD {
		int rng = DEREF_int (fld_set (CRT_FIELD));
		int hash = DEREF_int (fld_flag (CRT_FIELD));
		int al = (hash ? 1 : 0);

		if (rng) {
			comment ("Operations for field set %FN_etc of union %UN");
			output ("#define\t%UM_%FN_etc_tag%t40%du\n", tag + rng);
			output ("#define\tIS_%UM_%FN_etc(P)%t40");
			output ("((unsigned) (%s(P)->ag_tag - %d)",
			  check_null, tag);
			output (" < %du)\n\n", rng);
			print_field_c (sz, tag, rng, al);
		}

		comment ("Operations for field %FN of union %UN");
		output ("#define\t%UM_%FN_tag%t40%du\n", tag);
		output ("#define\tIS_%UM_%FN(P)%t40");
		if (is_tagged) {
			output ("(%s(P)->ag_tag == %d)\n\n", check_null, tag);
			print_field_c (sz, tag, 0, al);
		} else {
			output ("1\n\n");
			print_field_c (sz, -1, 0, al);
		}
		ASSERT (DEREF_int (fld_tag (CRT_FIELD)) == tag);
		tag++;
	}

	/* Map tables */
	LOOP_UNION_MAP {
		int hash = DEREF_int (map_flag (CRT_MAP));
		char *dest = (hash ? "destroyer" : NULL);
		comment ("Map %MN on union %UN");
		output ("extern ");
		print_map_table (hash);
		output (";\n\n#define %MN_%UM");
		print_map_args (dest);
		output ("\\\n    ((%MN_%UM_table[");
		if (is_tagged) {
			if (extra_asserts) {
				output ("CHECK_TAG_ETC ((%X_%UM), 0, ORDER_%UM)");
			} else {
				output ("(%X_%UM)");
			}
			output ("->ag_tag]) ");
		} else {
			output ("0]) ");
		}
		print_map_args (dest);
		output (")\n\n\n");
	}

	/* End of file */
	close_file ();
	return;
}


/*
 *    PRINT A UNION MAPPING TABLE
 *
 *    This routine prints a single union mapping table.
 */

static void
print_func_tab(int i)
{
	int hash = DEREF_int (map_flag (CRT_MAP));
	comment ("Function table for map %MN on union %UN");
	if (i) output ("#ifndef IGNORE_%MN_%UM\n\n");
	print_map_table (hash);
	output (" = {\n");
	LOOP_UNION_FIELD output ("\t%MN_%UM_%FN%F,\n");
	output ("};\n\n");
	if (i) output ("#endif\n\n");
	output ("\n");
	return;
}


/*
 *    PRINT A FUNCTION HEADER
 *
 *    This routine prints the function headers required in print_union_hdr_c.
 *    The argument d is true if this is the destructor version.  The argument
 *    e is true if this is the header for a field set.
 */

static void
print_func_hdr(int d, int e)
{
	int hash = DEREF_int (map_flag (CRT_MAP));
	char *dest = (d ? "_d_" : "_");
	char *etc = (e ? "_etc" : "");
	output ("#define\tHDR_%MN%s%UM_%FN%s\\\n", dest, etc);

	/* Function header */
	output ("\t%MR %MN_%UM_%FN\\\n");
	output ("\t(");
	print_map_args (hash ? "destroyer" : NULL);
	output (")\\\n");

	/* Function argument declarations */
	output ("\t(%UN %X_%UM");
	if (hash) output (", DESTROYER destroyer");
	LOOP_MAP_ARGUMENT output (", %AT %AN");
	output (")\\\n\t{");

	/* Field component declarations */
	LOOP_UNION_COMPONENT output ("\\\n\t%CT %CN;");
	LOOP_FIELD_COMPONENT output ("\\\n\t%CT %CN;");

	/* Assignment of field components */
	if (d) {
		output ("\\\n\tDESTROY_%UM_%FN%s (", etc);
		output (hash ? "destroyer, " : "destroy_%X, ");
		print_cons_args (0, "");
		output (");");
	} else {
		if (field_not_empty ()) {
			output ("\\\n\tDECONS_%UM_%FN%s (", etc);
			print_cons_args (0, "");
			output (");");
		}
	}
	output ("\n\n");
	return;
}


/*
 *    PRINT A UNION MAP OUTPUT FILE
 *
 *    For each union with maps in the calculus a file is printed giving the
 *    tables which give the actions of each map on each union component.
 */

void
print_union_map_c(char *dir, char *un)
{
	open_file (dir, un, MAP_SUFFIX);
	LOOP_UNION_MAP print_func_tab (1);
	close_file ();
	return;
}


/*
 *    PRINT THE UNION MAPPING HEADERS OUTPUT FILE
 *
 *    For each union with maps in the calculus a file is printed giving the
 *    function headers for the actions in the previous file.  Note that two
 *    versions of the header are given - a deconstructor and a destructor
 *    version.  Also versions are given for any field sets.
 */

void
print_union_hdr_c(char *dir, char *un)
{
	open_file (dir, un, HDR_SUFFIX);
	LOOP_UNION_MAP {
		comment ("Function headers for map %MN on union %UN");
		output ("#ifndef IGNORE_%MN_%UM\n\n");
		LOOP_UNION_FIELD {
			print_func_hdr (0, 0);
			print_func_hdr (1, 0);
			if (DEREF_int (fld_set (CRT_FIELD))) {
				print_func_hdr (0, 1);
				print_func_hdr (1, 1);
			}
		}
		output ("#endif\n\n\n");
	}
	close_file ();
	return;
}


/*
 *    MAIN ACTION (C VERSION)
 *
 *    This routine prints all the output files for the calculus (C version).
 */

void
main_action_c(char *dir)
{
	int ign = 0;
	gen_max = 0;
	output_c_code = 1;
	check_null = (extra_asserts ? "CHECK_NULL " : "");

	open_file (dir, MAIN_PREFIX, MAIN_SUFFIX);
	print_main_c ();

	LOOP_UNION {
		LIST (MAP_P) maps;
		CLASS_ID_P cid = DEREF_ptr (un_id (CRT_UNION));
		char *un = DEREF_string (cid_name_aux (cid));
		print_union_ops_c (dir, un);
		maps = DEREF_list (un_map (CRT_UNION));
		if (!IS_NULL_list (maps)) {
			print_union_map_c (dir, un);
			print_union_hdr_c (dir, un);
			ign = 1;
		}
	}

	comment ("Maximum allocation size");
	output ("#define\t%X_GEN_MAX%t40%d\n\n", gen_max + 1);
	close_file ();

	if (ign) {
		open_file (dir, IGNORE_PREFIX, DEF_SUFFIX);
		comment ("Map ignore macros");
		LOOP_UNION {
			LOOP_UNION_MAP output ("#define\tIGNORE_%MN_%UM%t40%d\n", 1);
		}
		output ("\n");
		close_file ();
	}

	if (extra_asserts) {
		open_file (dir, ASSERT_PREFIX, DEF_SUFFIX);
		comment ("Assertion function definitions");
		print_assert_fns ();
		close_file ();
	}
	return;
}
