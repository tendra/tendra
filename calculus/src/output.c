/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#include <shared/error.h>

#include "calculus.h"
#include "common.h"
#include "lex.h"
#include "output.h"
#include "suffix.h"
#include "type_ops.h"

/*
 * FIND BINARY LOG OF A NUMBER
 *
 * This routine calculates the binary log of n (i.e. the smallest number
 * r such that n <= 2**r).
 */
number
ilog2(number n)
{
	number r;
	number m;

	for (r = 0, m = 1; n > m && m; r++, m *= 2)
		;

	return r;
}

/*
 * LOOP VARIABLES
 *
 * These are the counter variables used in the LOOP macros defined in
 * output.h.
 */
LIST(ECONST_P)crt_ec = NULL_list(ECONST_P);
LIST(ENUM_P)crt_en = NULL_list(ENUM_P);
LIST(IDENTITY_P)crt_id = NULL_list(IDENTITY_P);
LIST(PRIMITIVE_P)crt_prim = NULL_list(PRIMITIVE_P);
LIST(STRUCTURE_P)crt_str = NULL_list(STRUCTURE_P);
LIST(UNION_P)crt_union = NULL_list(UNION_P);
LIST(COMPONENT_P)crt_cmp = NULL_list(COMPONENT_P);
LIST(FIELD_P)crt_fld = NULL_list(FIELD_P);
LIST(MAP_P)crt_map = NULL_list(MAP_P);
LIST(ARGUMENT_P)crt_arg = NULL_list(ARGUMENT_P);
LIST(TYPE_P)crt_type = NULL_list(TYPE_P);
int unique = 0;

/*
 * CURRENT OUTPUT FILE
 *
 * This gives the file which is currently being used for output.
 */
FILE *output_file = NULL;
static int output_posn = 0;
static char output_buff[256];
static FILE *output_file_old = NULL;
static int column = 0;
int verbose_output = 1;
int const_tokens = 1;
int have_varargs = 1;

/*
 * PRINT A CHARACTER
 *
 * This routine prints the single character c.
 */
static void
output_char(int c)
{
	int i = output_posn;
	output_buff[i] = (char)c;
	if (++i >= 250 || c == '\n') {
		output_buff[i] = 0;
		fputs(output_buff, output_file);
		i = 0;
	}

	if (c == '\n') {
		column = 0;
	} else if (c == '\t') {
		column = column + (8 - column % 8);
	} else {
		column++;
	}

	output_posn = i;
}

/*
 * PRINT A STRING
 *
 * This routine prints the string s.
 */
static void
output_string(const char *s)
{
	for (; *s; s++) {
		output_char(*s);
	}
}

/*
 * FLUSH OUTPUT FILE
 *
 * This routine flushes the output file buffer by printing a newline
 * character.
 */
void
flush_output(void)
{
	if (output_posn) {
		output_char('\n');
	}
}

/*
 * PRINT A TYPE
 *
 * This routine prints the type t.
 */
void
output_type(TYPE_P t)
{
	TYPE t0 = DEREF_type(t);

	switch (TAG_type(t0)) {
	case type_vec_tag: {
		TYPE_P_P s = type_vec_sub(t0);
		output_string("VEC(");
		output_type(DEREF_ptr(s));
		output_string(")");
		break;
	}

	case type_ptr_tag: {
		TYPE_P_P s = type_ptr_sub(t0);
		output_string("PTR(");
		output_type(DEREF_ptr(s));
		output_string(")");
		break;
	}

	case type_list_tag: {
		TYPE_P_P s = type_list_sub(t0);
		output_string("LIST(");
		output_type(DEREF_ptr(s));
		output_string(")");
		break;
	}

	case type_stack_tag: {
		TYPE_P_P s = type_stack_sub(t0);
		output_string("STACK(");
		output_type(DEREF_ptr(s));
		output_string(")");
		break;
	}

	case type_vec_ptr_tag: {
		TYPE_P_P s = type_vec_ptr_sub(t0);
		output_string("VEC_PTR(");
		output_type(DEREF_ptr(s));
		output_string(")");
		break;
	}

	default:
		output_string(name_type(t));
		break;
	}
}

/*
 * PRINT A TYPE IDENTIFIER
 *
 * This routine prints an identifier derived from the type t.  depth
 * determines the depth to which identities are to be expanded.
 */
static void
output_type_id(TYPE_P t, int depth)
{
	TYPE t0 = DEREF_type(t);

	switch (TAG_type(t0)) {
	case type_vec_tag: {
		TYPE_P_P s = type_vec_sub(t0);
		output_string("vec_");
		output_type_id(DEREF_ptr(s), depth);
		break;
	}

	case type_ptr_tag: {
		TYPE_P_P s = type_ptr_sub(t0);
		output_string("ptr_");
		output_type_id(DEREF_ptr(s), depth);
		break;
	}

	case type_list_tag: {
		TYPE_P_P s = type_list_sub(t0);
		output_string("list_");
		output_type_id(DEREF_ptr(s), depth);
		break;
	}

	case type_stack_tag: {
		TYPE_P_P s = type_stack_sub(t0);
		output_string("stack_");
		output_type_id(DEREF_ptr(s), depth);
		break;
	}

	case type_vec_ptr_tag: {
		TYPE_P_P s = type_vec_ptr_sub(t0);
		output_string("vptr_");
		output_type_id(DEREF_ptr(s), depth);
		break;
	}

	case type_ident_tag: {
		IDENTITY_P id = DEREF_ptr(type_ident_id(t0));
		if (depth) {
			TYPE_P_P s = ident_defn(id);
			output_type_id(DEREF_ptr(s), depth - 1);
		} else {
			CLASS_ID_P nm = DEREF_ptr(ident_id(id));
			output_string(DEREF_string(cid_name(nm)));
		}
		break;
	}

	default:
		output_string(name_aux_type(t));
		break;
	}
}

/*
 * PRINT A TYPE SIZE
 *
 * This routine print the size of the type t.
 */
static void
output_type_size(TYPE_P t)
{
	TYPE t0 = DEREF_type(t);

	switch (TAG_type(t0)) {
	case type_vec_tag: {
		TYPE_P_P s = type_vec_sub(t0);
		output("SIZE_vec(%TT)", DEREF_ptr(s));
		break;
	}

	case type_ptr_tag: {
		TYPE_P_P s = type_ptr_sub(t0);
		output("SIZE_ptr(%TT)", DEREF_ptr(s));
		break;
	}

	case type_list_tag: {
		TYPE_P_P s = type_list_sub(t0);
		output("SIZE_list(%TT)", DEREF_ptr(s));
		break;
	}

	case type_stack_tag: {
		TYPE_P_P s = type_stack_sub(t0);
		output("SIZE_stack(%TT)", DEREF_ptr(s));
		break;
	}

	case type_vec_ptr_tag: {
		TYPE_P_P s = type_vec_ptr_sub(t0);
		output("SIZE_vec_ptr(%TT)", DEREF_ptr(s));
		break;
	}

	case type_ident_tag: {
		IDENTITY_P id = DEREF_ptr(type_ident_id(t0));
		output_type_size(DEREF_ptr(ident_defn(id)));
		break;
	}

	default:
		output_string("SIZE_");
		output_string(name_aux_type(t));
		break;
	}
}

/*
 * PRINT A FORMAT STRING
 *
 * This routine prints the string s, taking any formatting characters
 * into account.  These formatting characters have the form %X or %XY
 * for characters X and Y.  Each is commented within the body of the
 * procedure in the form "%XY -> ....".
 */
void
output(char *s, ...)
{
	char c;
	va_list args;
	char nbuff[100];

	va_start(args, s);

	while (c = *(s++), c != 0) {
		char *s0;

		if (c != '%') {
			output_char(c);
			continue;
		}

		s0 = s;
		c = *(s++);

		switch (c) {
		case 'A':
			/* Arguments */
			c = *(s++);
			if (c == 'N') {
				/* %AN -> argument name */
				if (HAVE_ARGUMENT) {
					string_P ps = arg_name(CRT_ARGUMENT);
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'T') {
				/* %AT -> argument type */
				if (HAVE_ARGUMENT) {
					TYPE_P_P pt = arg_type(CRT_ARGUMENT);
					output_type(DEREF_ptr(pt));
				} else {
					goto misplaced_arg;
				}
			} else {
				goto bad_format;
			}
			break;

		case 'C':
			/* Components */
			c = *(s++);
			if (c == 'N') {
				/* %CN -> component name */
				if (HAVE_COMPONENT) {
					string_P ps = cmp_name(CRT_COMPONENT);
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'T') {
				/* %CT -> component type */
				if (HAVE_COMPONENT) {
					TYPE_P_P pt = cmp_type(CRT_COMPONENT);
					output_type(DEREF_ptr(pt));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'U') {
				/* %CU -> short component type */
				if (HAVE_COMPONENT) {
					TYPE_P_P pt = cmp_type(CRT_COMPONENT);
					TYPE_P ta = DEREF_ptr(pt);
					char *tn = name_aux_type(ta);
					output_string(tn);
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'V') {
				/* %CV -> component default value */
				if (HAVE_COMPONENT) {
					string_P ps = cmp_name(CRT_COMPONENT);
					string s1 = DEREF_string(ps);
					if (s1) {
						output_string(s1);
					}
				} else {
					goto misplaced_arg;
				}
			} else {
				goto bad_format;
			}
			break;

		case 'E':
			/* Enumerations */
			c = *(s++);
			if (c == 'N') {
				/* %EN -> enumeration name */
				if (HAVE_ENUM) {
					CLASS_ID_P_P pi = en_id(CRT_ENUM);
					string_P ps = cid_name(DEREF_ptr(pi));
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'M') {
				/* %EM -> short enumeration name */
				if (HAVE_ENUM) {
					CLASS_ID_P_P pi = en_id(CRT_ENUM);
					string_P ps = cid_name_aux(DEREF_ptr(pi));
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'O') {
				/* %EO -> enumeration order */
				if (HAVE_ENUM) {
					number_P pn = en_order(CRT_ENUM);
					number n = DEREF_number(pn);
					if (*s == '2') {
						n = ilog2(n);
						s++;
					}
					sprintf(nbuff, "%lu", n);
					output_string(nbuff);
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'S') {
				/* %ES -> enumerator name */
				if (HAVE_ECONST) {
					string_P ps = ec_name(CRT_ECONST);
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'V') {
				/* %EV -> enumerator value */
				if (HAVE_ECONST) {
					number_P pn = ec_value(CRT_ECONST);
					number n = DEREF_number(pn);
					sprintf(nbuff, "%lu", n);
					output_string(nbuff);
				} else {
					goto misplaced_arg;
				}
			} else {
				goto bad_format;
			}
			break;

		case 'F':
			/* Fields */
			c = *(s++);
			if (c == 'N') {
				/* %FN -> field name */
				if (HAVE_FIELD) {
					string_P ps = fld_name(CRT_FIELD);
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == ',') {
				/* %F, -> ',' (if not the last field) */
				if (HAVE_FIELD) {
					LIST(FIELD_P)nf = TAIL_list(crt_fld);
					if (!IS_NULL_list(nf)) {
						output_string(",");
					}
				} else {
					goto misplaced_arg;
				}
			} else {
				goto bad_format;
			}
			break;

		case 'I':
			/* Identities */
			c = *(s++);
			if (c == 'N') {
				/* %IN -> identity name */
				if (HAVE_IDENTITY) {
					CLASS_ID_P_P pi = ident_id(CRT_IDENTITY);
					string_P ps = cid_name(DEREF_ptr(pi));
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'M') {
				/* %IM -> short identity name */
				if (HAVE_IDENTITY) {
					CLASS_ID_P_P pi = ident_id(CRT_IDENTITY);
					string_P ps = cid_name_aux(DEREF_ptr(pi));
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'T') {
				/* %IT -> identity type definition */
				if (HAVE_IDENTITY) {
					TYPE_P_P pt = ident_defn(CRT_IDENTITY);
					output_type(DEREF_ptr(pt));
				} else {
					goto misplaced_arg;
				}
			} else {
				goto bad_format;
			}
			break;

		case 'M':
			/* Maps */
			c = *(s++);
			if (c == 'N') {
				/* %MN -> map name */
				if (HAVE_MAP) {
					string_P ps = map_name(CRT_MAP);
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'R') {
				/* %MR -> map return type */
				if (HAVE_MAP) {
					TYPE_P_P pt = map_ret_type(CRT_MAP);
					output_type(DEREF_ptr(pt));
				} else {
					goto misplaced_arg;
				}
			} else {
				goto bad_format;
			}
			break;

		case 'P':
			/* Primitives */
			c = *(s++);
			if (c == 'N') {
				/* %PN -> primitive name */
				if (HAVE_PRIMITIVE) {
					CLASS_ID_P_P pi = prim_id(CRT_PRIMITIVE);
					string_P ps = cid_name(DEREF_ptr(pi));
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'M') {
				/* %PM -> short primitive name */
				if (HAVE_PRIMITIVE) {
					CLASS_ID_P_P pi = prim_id(CRT_PRIMITIVE);
					string_P ps = cid_name_aux(DEREF_ptr(pi));
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'D') {
				/* %PD -> primitive definition */
				if (HAVE_PRIMITIVE) {
					string_P ps = prim_defn(CRT_PRIMITIVE);
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else {
				goto bad_format;
			}
			break;

		case 'S':
			/* Structures */
			c = *(s++);
			if (c == 'N') {
				/* %SN -> structure name */
				if (HAVE_STRUCTURE) {
					CLASS_ID_P_P pi = str_id(CRT_STRUCTURE);
					string_P ps = cid_name(DEREF_ptr(pi));
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'M') {
				/* %SM -> short structure name */
				if (HAVE_STRUCTURE) {
					CLASS_ID_P_P pi = str_id(CRT_STRUCTURE);
					string_P ps = cid_name_aux(DEREF_ptr(pi));
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else {
				goto bad_format;
			}
			break;

		case 'T':
			/* Types */
			c = *(s++);
			if (have_varargs) {
				TYPE_P ta = va_arg(args, TYPE_P);
				if (c == 'N') {
					/* %TN -> type name */
					char *tn = name_type(ta);
					output_string(tn);
				} else if (c == 'M') {
					/* %TM -> short type name */
					char *tn = name_aux_type(ta);
					output_string(tn);
				} else if (c == 'I') {
					/* %TI -> type identifier */
					output_type_id(ta, 0);
				} else if (c == 'J') {
					/* %TJ -> type identifier */
					output_type_id(ta, 1);
				} else if (c == 'S') {
					/* %TS -> type size */
					output_type_size(ta);
				} else if (c == 'T') {
					/* %TT -> type definition */
					output_type(ta);
				} else {
					goto bad_format;
				}
				break;
			}
			goto bad_format;

		case 'U':
			/* Unions */
			c = *(s++);
			if (c == 'N') {
				/* %UN -> union name */
				if (HAVE_UNION) {
					CLASS_ID_P_P pi = un_id(CRT_UNION);
					string_P ps = cid_name(DEREF_ptr(pi));
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'M') {
				/* %UM -> short union name */
				if (HAVE_UNION) {
					CLASS_ID_P_P pi = un_id(CRT_UNION);
					string_P ps = cid_name_aux(DEREF_ptr(pi));
					output_string(DEREF_string(ps));
				} else {
					goto misplaced_arg;
				}
			} else if (c == 'O') {
				/* %UO -> union order */
				if (HAVE_UNION) {
					int_P pi = un_no_fields(CRT_UNION);
					number n = (number)DEREF_int(pi);
					c = *s;
					if (c == '2') {
						n = ilog2(n);
						s++;
					} else if (c == '3') {
						n = ilog2(n + 1);
						s++;
					}
					sprintf(nbuff, "%lu", n);
					output_string(nbuff);
				} else {
					goto misplaced_arg;
				}
			} else {
				goto bad_format;
			}
			break;

		case 'V': {
			/* %V -> overall version */
			int v1 = algebra->major_no;
			int v2 = algebra->minor_no;
			sprintf(nbuff, "%d.%d", v1, v2);
			output_string(nbuff);
			break;
		}

		case 'X':
			/* %X -> overall name */
			output_string(algebra->name);
			break;

		case 'Z':
			c = *(s++);
			if (c == 'V') {
				/* %ZV -> program version */
				output_string(progvers);
			} else if (c == 'X') {
				/* %ZX -> program name */
				output_string(progname);
			} else {
				goto bad_format;
			}
			break;

		case 'b':
			/* %b -> backspace */
			if (output_posn) {
				output_posn--;
			}
			break;

		case 'd':
			/* %d -> integer (extra argument) */
			if (have_varargs) {
				int da = va_arg(args, int);
				sprintf(nbuff, "%d", da);
				output_string(nbuff);
				break;
			}
			goto bad_format;

		case 'e':
			/* %e -> evaluated string (extra argument) */
			if (have_varargs) {
				char *ea = va_arg(args, char *);
				if (ea) {
					output(ea);
				}
				break;
			}
			goto bad_format;

		case 'n':
			/* %n -> number (extra argument) */
			if (have_varargs) {
				number na = va_arg(args, number);
				sprintf(nbuff, "%lu", na);
				output_string(nbuff);
				break;
			}
			goto bad_format;

		case 'p':
			/* Pragmas */
			c = *(s++);
			if (c == 't') {
				/* %pt -> '#pragma token' */
				output_string("#pragma token");
			} else if (c == 'i') {
				/* %pi -> '#pragma interface' */
				output_string("#pragma interface");
			} else {
				goto bad_format;
			}
			break;

		case 's':
			/* %s -> string (extra argument) */
			if (have_varargs) {
				char *sa = va_arg(args, char *);
				if (sa) {
					output_string(sa);
				}
				break;
			}
			goto bad_format;

		case 't': {
			/* %t[0-9]* -> tab */
			int t = 0;
			while (c = *s, (c >= '0' && c <= '9')) {
				t = 10 * t + (c - '0');
				s++;
			}
			while (column < t) {
				output_char('\t');
			}
			break;
		}

		case 'u':
			/* %u -> unique */
			sprintf(nbuff, "%d", unique);
			output_string(nbuff);
			break;

		case 'x':
			/* Expression tokens */
			c = *(s++);
			if (c == 'r') {
				/* %xr -> 'EXP rvalue' */
				output_string("EXP");
			} else if (c == 'l') {
				/* %xl -> 'EXP lvalue' */
				output_string("EXP lvalue");
			} else if (c == 'c') {
				/* %xc -> 'EXP const' */
				output_string("EXP");
				if (const_tokens) {
					output_string(" const");
				}
			} else {
				goto bad_format;
			}
			break;

		case '0':
			/* %0 -> x<unique>_ */
			sprintf(nbuff, "x%d_", unique);
			output_string(nbuff);
			break;

		case '%':
			/* %% -> '%' */
			output_string("%");
			break;

		case '@':
			/* %@ -> '@' */
			output_string("@");
			break;

		case '\n':
			/* %\n -> ignored newline */
			break;

misplaced_arg:
			error(ERR_SERIOUS, "Misplaced formatting string '%%%.2s'", s0);
			break;

		default:
bad_format:
			error(ERR_SERIOUS, "Unknown formatting string '%%%.2s'", s0);
			s = s0;
			break;
		}
	}

	va_end(args);
}

/*
 * PRINT INITIAL COMMENT
 *
 * This comment is printed at the start of each output file to indicate
 * that it is automatically generated.
 */
static void
print_comment(void)
{
	if (first_comment) {
		/* Print copyright comment, if present */
		output("%s\n\n", first_comment);
	}

	output("/*\n");
	output("    AUTOMATICALLY GENERATED FROM ALGEBRA %X (VERSION %V)\n");
	output("    BY %ZX (VERSION %ZV)\n");
	output("*/\n\n");
}

/*
 * C CODE FLAG
 *
 * This flag is true if C code is being output.
 */
int output_c_code = 1;

/*
 * OPEN AN OUTPUT FILE
 *
 * This routine opens the output file formed by concatenating nm and suff.
 * Two files can be open at once.
 */
void
open_file(char *dir, char *nm, char *suff)
{
	char *p;
	char buff[1000];
	flush_output();
	sprintf(buff, "%s/%s%s", dir, nm, suff);
	output_file_old = output_file;
	output_file = fopen(buff, "w");
	if (output_file == NULL) {
		error(ERR_FATAL, "Can't open output file, %s", buff);
	}
	if (verbose_output) {
		printf("Creating %s ...\n", buff);
	}
	column = 0;

	if (output_c_code) {
		/* Set up protection macro */
		char *tok = "";
		if (output_c_code == 2) {
			tok = "_TOK";
		}

		sprintf(buff, "%s%s%s_INCLUDED", nm, suff, tok);
		for (p = buff; *p; p++) {
			char c = *p;
			if (isalpha(c)) {
				if (islower(c)) {
					c = (char)toupper(c);
				}
			} else if (!isdigit(c)) {
				c = '_';
			}
			*p = c;
		}

		/* Print file header */
		print_comment();
		output("#ifndef %s\n", buff);
		output("#define %s\n\n", buff);
	}
}

/*
 * CLOSE AN OUTPUT FILE
 *
 * This routine closes the current output file.
 */
void
close_file(void)
{
	if (output_c_code) {
		output("#endif\n");
	}

	flush_output();
	fclose(output_file);
	output_file = output_file_old;
	output_file_old = NULL;
	output_c_code = 1;
}

