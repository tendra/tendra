/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <time.h>
#include <ctype.h>
#include <string.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <out/index.h>
#include <out/print.h>

#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "utility.h"

/*
 * FLAGS
 *
 * These flags are used to indicate various output states indicated by
 * preprocessing directives.  A value of 1 is the default (which
 * actually means that the condition is false), 2 means that the given
 * statement is true, and 0 means that its negation is true.
 */
static int building_libs = 1;
static int commented_out = 1;

/*
 * FIELD SEPARATOR
 *
 * The field separator for the machine processable index.  This
 * separator can be changed, but no command line option is provided to
 * do this as '$' seems ideal.
 */
#define FIELD_SEP '$'

/*
 * PRINT FIELD SEPARATOR
 *
 * Routine to print field separator of the machine processable index.
 */
#define print_field_sep() IGNORE putchar(FIELD_SEP)

/*
 * PRINT FIELD
 *
 * Routine to print field and separator of the machine processable index.
 */
static void
print_field(char *s)
{
	IGNORE printf("%s%c", s, FIELD_SEP);
}

/*
 * PRINT ESCAPED FIELD
 *
 * Routine to print field without separator of the machine processable
 * index, escaping characters that could confuse output processing tools.
 */
static void
print_escape(char *s)
{
	int c;

	while (c = *s++, c != '\0') {
		switch (c) {
		case FIELD_SEP: IGNORE printf("\\F");  break;
		case '\n':	  IGNORE printf("\\n");  break;
		case '\\':	  IGNORE printf("\\\\"); break;
		default:		IGNORE putchar(c);	 break;
		}
	}
}

/*
 * PRINT VALUE FIELD
 *
 * Routine to print the final value field of the machine processable index.
 */
static void
print_value(char *s)
{
	print_field_sep();
	print_escape(s);
	IGNORE putchar('\n');
}

/*
 * PRINT EMPTY VALUE FIELD
 *
 * Routine to print the final empty value field of the machine processable
 * index.
 */
static void
print_no_value(void)
{
	IGNORE printf("%c\n", FIELD_SEP);
}

/*
 * PRINT SORT, INFO AND TYPE FIELDS
 *
 * Routine to print sort, info and type fields of the machine processable
 * index.
 */
static void
print_sit_v(char *s, char *i, type *t, char *nm)
{
	IGNORE printf("%s%c%s%c", s, FIELD_SEP, i, FIELD_SEP);
	IGNORE print_type(stdout, t, nm, 0);
}

/*
 * PRINT SORT AND TYPE FIELDS
 *
 * Routine to print sort, empty info, and type fields of the machine
 * processable index.
 */
static void
print_st_v(char *s, type *t, char *nm)
{
	print_sit_v(s, "", t, nm);
}

/*
 * PRINT SORT AND INFO FIELDS
 *
 * Routine to print sort, info, and empty type fields of the machine
 * processable index.
 */
static void
print_si_v(char *s, char *i)
{
	IGNORE printf("%s%c%s%c", s, FIELD_SEP, i, FIELD_SEP);
}

/*
 * PRINT SORT FIELD
 *
 * Routine to print sort, empty info, and empty type fields of the
 * machine processable index.
 */
static void
print_s_v(char *s)
{
	IGNORE printf("%s%c%c", s, FIELD_SEP, FIELD_SEP);
}

/*
 * PRINT SORT, INFO, TYPE AND EMPTY VALUE FIELDS
 *
 * Routine to print sort, info, type and empty value fields of the
 * machine processable index.
 */
static void
print_sit(char *s, char *i, type *t, char *nm)
{
	print_sit_v(s, i, t, nm);
	print_no_value();
}

/*
 * PRINT SORT, TYPE AND EMPTY VALUE FIELDS
 *
 * Routine to print sort, empty info, type and empty value fields of the
 * machine processable index.
 */
static void
print_st(char *s, type *t, char *nm)
{
	print_st_v(s, t, nm);
	print_no_value();
}

/*
 * PRINT SORT, INFO AND EMPTY VALUE FIELDS
 *
 * Routine to print sort, info, empty type and empty value fields of the
 * machine processable index.
 */
static void
print_si(char *s, char *i)
{
	print_si_v(s, i);
	print_no_value();
}

/*
 * PRINT SORT AND EMPTY VALUE FIELDS
 *
 * Routine to print sort, empty info, empty type and empty value fields
 * of the machine processable index.
 */
static void
print_s(char *s)
{
	print_s_v(s);
	print_no_value();
}

/*
 * IF STACK STATE
 *
 * This stack is used to keep track of the current +IF conditions.
 */
static object **if_stack = 0;
static int if_stack_sz = 0;
static int if_stack_index = 0;

/*
 * STACK AN IF COMMAND OBJECT
 *
 * Routine to stack an object representing +IFxxx or +ELSE.
 */
static void
stack_if(object *p)
{
	if (if_stack_index == if_stack_sz) {
		if_stack_sz += 16;
		if_stack = xrealloc_nof(if_stack, object *, if_stack_sz);
	}

	if_stack[if_stack_index] = p;
	if_stack_index++;
}

/*
 * UNSTACK AN IF COMMAND OBJECT
 *
 * Routine to unstack an object representing +IFxxx or +ELSE.
 */
static object *
unstack_if(void)
{
	return if_stack[--if_stack_index];
}

/*
 * PRINT IF NESTING
 *
 * Routine to print the currently stacked +IFxxx and +ELSE nesting.
 */
static void
print_if_nest(void)
{
	int i;

	for (i = 0; i < if_stack_index; i++) {
		char code;
		object *p;
		char *c;

		code = ' ';
		p = if_stack[i];
		c = p->name;

		if (i > 0) {
			print_escape(";");
		}

		if (i + 1 < if_stack_index && if_stack[i + 1]->u.u_iftype == CMD_ELSE) {
			IGNORE printf("e");
			i++;
		}

		switch (p->u.u_iftype) EXHAUSTIVE {
		case CMD_IF:     code = 'i'; break;
		case CMD_IFDEF:  code = 'd'; break;
		case CMD_IFNDEF: code = 'n'; break;
		default:                     break;
		}

		IGNORE printf("%c", code);
		print_escape(":");
		print_escape(c);
	}
}

/*
 * PRINT A MACHINE PROCESSABLE ITEM INDEX
 *
 * This routine prints the index item indicated by the token object p.
 * u gives the token status, a the current file name, and e is used in
 * enumeration items.  The output is in fields suitable for machine
 * processing by tools such as 'awk'.
 */
static void
print_item_m(object *p, char *u, char *a, type *e)
{
	char *nm;
	char *ap;
	char *tnm;
	object *q;

	tnm = p->name;
	q = p->u.u_obj;

	if (q->objtype == OBJ_FIELD) {
		nm = q->u.u_field->fname;
	} else {
		nm = q->name;
	}

	/* Field 1: C_SYMBOL */
	print_field(nm);

	/* Field 2: TOKEN */
	print_field(tnm);

	/* Field 3: STATUS */
	IGNORE printf("%c%c", u[0], FIELD_SEP);

	/* Field 4: IF_NESTING */
	print_if_nest();
	print_field_sep();

	/* Field 5: API_LOCATION */
	for (ap = a; *ap && *ap != ':'; ap++) {
		IGNORE putchar(*ap);
	}
	print_field_sep();

	/* Field 6: FILE_LOCATION */
	if (*ap != '\0') {
		ap++;
	}
	for ( ; *ap && *ap != ':'; ap++) {
		IGNORE putchar(*ap);
	}
	print_field_sep();

	/* Field 7: LINE_LOCATION */
	IGNORE printf("%d%c", q->line_no, FIELD_SEP);

	/* Field 8: SUBSET_NESTING */
	if (*ap != '\0') {
		IGNORE printf("%s", ap + 1);
	}
	print_field_sep();

	/* Fields 9-12: SORT, INFO, TYPE, VALUE */
	switch (q->objtype) {
	case OBJ_CONST: {
		print_st("const", q->u.u_type, NULL);
		break;
	}

	case OBJ_ENUMVAL: {
		print_field("enum_member");
		print_type(stdout, e, NULL, 0);
		print_field_sep();
		if (q->u.u_str) {
			print_value(q->u.u_str);
		} else {
			print_no_value();
		}
		break;
	}

	case OBJ_EXP: {
		type *t = q->u.u_type;
		char *s = t->id == TYPE_LVALUE ? "lvalue" : "rvalue";
		print_st(s, t, NULL);
		break;
	}

	case OBJ_EXTERN: {
		type *t = q->u.u_type;

		if (t->id == TYPE_LVALUE) {
			t = t->u.subtype;
		}

		if (t->id == TYPE_PROC) {
			print_sit("func", "extern", t, nm);
		} else {
			print_st("extern", t, NULL);
		}
		break;
	}

	case OBJ_WEAK: {
		type *t = q->u.u_type;
		print_sit("func", "weak", t, nm);
		break;
	}

	case OBJ_DEFINE: {
		char *s = q->u.u_str;

		if (*s == '(') {
			print_field("define");
			print_field("param");

			for (; *s && *s != ')'; s++) {
				IGNORE putchar(*s);
			}

			if (*s == ')') {
				s++;
			}

			IGNORE printf(")");
		} else {
			print_s_v("define");
		}

		while (*s == ' ') {
			s++;
		}
		print_value(s);
		break;
	}

	case OBJ_DEFMIN: {
		char *s = q->u.u_str;

		if (*s == '(') {
			print_field("defmin");
			print_field("param");

			for (; *s && *s != ')'; s++) {
				IGNORE putchar(*s);
			}

			if (*s == ')') {
				s++;
			}

			IGNORE printf(")");
		} else {
			print_s_v("defmin");
		}

		while (*s == ' ') {
			s++;
		}
		print_value(s);
		break;
	}

	case OBJ_FIELD: {
		field *f = q->u.u_field;

		print_field("member");
		print_type(stdout, f->stype, NULL, 0);
		print_field_sep();
		print_type(stdout, f->ftype, NULL, 0);
		print_no_value();
		break;
	}

	case OBJ_FUNC:
		print_st("func", q->u.u_type, nm);
		break;

	case OBJ_MACRO:
		print_st("macro", q->u.u_type, nm);
		break;

	case OBJ_NAT:
		print_s("nat");
		break;

	case OBJ_STATEMENT: {
		type *t = q->u.u_type;
		if (t != NULL) {
			print_sit("statement", "param", t, NULL);
		} else {
			print_s("statement");
		}
		break;
	}

	case OBJ_TOKEN:
		print_s_v("token");
		print_value(q->u.u_str);
		break;

	case OBJ_TYPE: {
		type *t = q->u.u_type;
		int i = t->id;

		switch (i) {
		case TYPE_DEFINED:
			print_st("typedef", t->v.next, NULL);
			break;

		case TYPE_GENERIC:
			print_s("opaque");
			break;

		case TYPE_INT:
			print_s("integral");
			break;

		case TYPE_SIGNED:
			print_s("signed_integral");
			break;

		case TYPE_UNSIGNED:
			print_s("unsigned_integral");
			break;

		case TYPE_PROMOTE:
			print_field("promotion");
			print_type(stdout, t->v.next, NULL, 0);
			print_field_sep();
			print_no_value();
			break;

		case TYPE_FLOAT:
			print_s("floating");
			break;

		case TYPE_ARITH:
			print_s("arithmetic");
			break;

		case TYPE_SCALAR:
			print_s("scalar");
			break;

		case TYPE_STRUCT:
		case TYPE_STRUCT_TAG:
		case TYPE_UNION:
		case TYPE_UNION_TAG:
		case TYPE_ENUM:
		case TYPE_ENUM_TAG: {
			char *s = NULL;
			type *en = NULL;
			object *r = t->v.obj2;
			char *inf = (r ? "exact" : "");
			switch (i)EXHAUSTIVE {
			case TYPE_STRUCT: s = "struct"; break;
			case TYPE_STRUCT_TAG: s = "struct_tag"; break;
			case TYPE_UNION: s = "union"; break;
			case TYPE_UNION_TAG: s = "union_tag"; break;
			case TYPE_ENUM: s = "enum"; en = t; break;
			case TYPE_ENUM_TAG: s = "enum_tag"; en = t; break;
			}
			print_si(s, inf);
			while (r) {
			print_item_m(r, u, a, en);
			r = r->next;
			}
			break;
		}

		default :
			error(ERR_INTERNAL, "Unknown type identifier, '%d'", i);
			break;
		}
		break;
	}

	default :
		error(ERR_INTERNAL, "Unknown object type, '%d'", q->objtype);
		break;
	}
}

/*
 * PRINT AN INDEX ITEM
 *
 * This routine prints the index item indicated by the token object p.
 * u gives the token status, a the current file name, and e is used in
 * enumeration items.  The output is in a humun readable format.
 */
static void
print_item_h(object *p, char *u, char *a, type *e)
{
	char *tnm = p->name;
	object *q = p->u.u_obj;
	char *nm = q->name;

	IGNORE printf("TOKEN: %s\n", tnm);
	IGNORE printf("STATUS: %s", u);

	if (building_libs == 0) {
		IGNORE printf(" (not library building)");
	}

	if (building_libs == 2) {
		IGNORE printf(" (library building only)");
	}

	IGNORE printf("\nDEFINED: %s, line %d\n", a, q->line_no);
	IGNORE printf("INFO: ");

	if (commented_out == 2) {
		IGNORE printf("(commented out) ");
	}

	switch (q->objtype) {
	case OBJ_CONST:
		IGNORE printf("%s is a constant expression of type ", nm);
		print_type(stdout, q->u.u_type, NULL, 0);
		IGNORE printf("\n\n");
		break;

	case OBJ_ENUMVAL:
		IGNORE printf("%s is a member of the enumeration type ", nm);
		print_type(stdout, e, NULL, 0);
		IGNORE printf("\n\n");
		break;

	case OBJ_EXP:
		IGNORE printf("%s is an expression of type ", nm);
		print_type(stdout, q->u.u_type, NULL, 0);
		IGNORE printf("\n\n");
		break;

	case OBJ_EXTERN: {
		type *t = q->u.u_type;

		if (t->id == TYPE_LVALUE) {
			t = t->u.subtype;
		}

		IGNORE printf("%s is an external ", nm);
		if (t->id == TYPE_PROC) {
			IGNORE printf("function with prototype ");
			print_type(stdout, t, nm, 0);
		} else {
			IGNORE printf("expression with type ");
			print_type(stdout, t, NULL, 0);
		}
		IGNORE printf("\n\n");
		break;
	}

	case OBJ_WEAK: {
		type *t = q->u.u_type;
		IGNORE printf("%s is an external ", nm);
		IGNORE printf("function with weak prototype ");
		print_type(stdout, t, nm, 0);
		IGNORE printf("\n\n");
		break;
	}

	case OBJ_DEFINE: {
		char *s = q->u.u_str;
		IGNORE printf("%s is a macro ", nm);

		if (*s == '(') {
			IGNORE printf("with arguments ");
			for (; *s && *s != ')'; s++) {
				IGNORE putchar(*s);
			}
			if (*s == ')') {
				s++;
			}
			IGNORE printf(") ");
		}

		while (*s == ' ') {
			s++;
		}

		IGNORE printf("defined to be %s\n\n", s);
		break;
	}

	case OBJ_DEFMIN: {
		char *s = q->u.u_str;

		IGNORE printf("%s is a macro ", nm);
		if (*s == '(') {
			IGNORE printf("with arguments ");
			for (; *s && *s != ')'; s++) {
				IGNORE putchar(*s);
			}
			if (*s == ')') {
				s++;
			}
			IGNORE printf(") ");
		}

		while (*s == ' ') {
			s++;
		}

		IGNORE printf("defined to be minimum %s\n\n", s);
		break;
	}

	case OBJ_FIELD: {
		field *f = q->u.u_field;
		IGNORE printf("%s is a field selector of ", f->fname);
		print_type(stdout, f->stype, NULL, 0);
		IGNORE printf(" of type ");
		print_type(stdout, f->ftype, NULL, 0);
		IGNORE printf("\n\n");
		break;
	}

	case OBJ_FUNC:
		IGNORE printf("%s is a function with prototype ", nm);
		print_type(stdout, q->u.u_type, nm, 0);
		IGNORE printf("\n\n");
		break;

	case OBJ_MACRO:
		IGNORE printf("%s is a macro with prototype ", nm);
		print_type(stdout, q->u.u_type, nm, 0);
		IGNORE printf("\n\n");
		break;

	case OBJ_NAT:
		IGNORE printf("%s is a constant integer\n\n", nm);
		break;

	case OBJ_STATEMENT: {
		type *t = q->u.u_type;
		IGNORE printf("%s is a statement", nm);
		if (t != NULL) {
			IGNORE printf(" with arguments");
			print_type(stdout, t, NULL, 0);
		}
		IGNORE printf("\n\n");
		break;
	}

	case OBJ_TOKEN:
		IGNORE printf("%s is a complex token\n\n", nm);
		break;

	case OBJ_TYPE: {
		type *t = q->u.u_type;
		int i = t->id;

		print_type(stdout, t, NULL, 0);

		switch (i) {
		case TYPE_DEFINED:
			IGNORE printf(" is a type defined to be ");
			print_type(stdout, t->v.next, NULL, 0);
			IGNORE printf("\n\n");
			break;

		case TYPE_GENERIC:
			IGNORE printf(" is a type\n\n");
			break;

		case TYPE_INT:
			IGNORE printf(" is an integral type\n\n");
			break;

		case TYPE_SIGNED:
			IGNORE printf(" is a signed integral type\n\n");
			break;

		case TYPE_UNSIGNED:
			IGNORE printf(" is an unsigned integral type\n\n");
			break;

		case TYPE_PROMOTE:
			IGNORE printf(" is the integral promotion of ");
			print_type(stdout, t->v.next, NULL, 0);
			IGNORE printf("\n\n");
			break;

		case TYPE_FLOAT:
			IGNORE printf(" is a floating type\n\n");
			break;

		case TYPE_ARITH:
			IGNORE printf(" is an arithmetic type\n\n");
			break;

		case TYPE_SCALAR:
			IGNORE printf(" is a scalar type\n\n");
			break;

		case TYPE_STRUCT:
		case TYPE_STRUCT_TAG:
		case TYPE_UNION:
		case TYPE_UNION_TAG: {
			char *n = NULL;
			object *r = t->v.obj2;
			switch (i)EXHAUSTIVE {
			case TYPE_STRUCT: n = "structure"; break;
			case TYPE_STRUCT_TAG: n = "structure"; break;
			case TYPE_UNION: n = "union"; break;
			case TYPE_UNION_TAG: n = "union"; break;
			}
			if (r == NULL) {
			IGNORE printf(" is an inexact %s type\n\n", n);
			} else {
			IGNORE printf(" is an exact %s type\n\n", n);
			while (r) {
				print_item_h(r, u, a,(type *)NULL);
				r = r->next;
			}
			}
			break;
		}

		case TYPE_ENUM:
		case TYPE_ENUM_TAG: {
			object *r = t->v.obj2;
			IGNORE printf(" is an enumeration type\n\n");
			while (r) {
			print_item_h(r, u, a, t);
			r = r->next;
			}
			break;
		}

		default:
			IGNORE printf(" is a type\n\n");
			error(ERR_INTERNAL, "Unknown type identifier, '%d'", i);
			break;
		}
		break;
	}

	default :
		error(ERR_INTERNAL, "Unknown object type, '%d'", q->objtype);
		break;
	}
}

/*
 * PRINT INDEX USING PRINT ITEM FUNCTION
 *
 * This routine prints an index of the set object input using fn.
 */

typedef void (*index_func)(object *, char *, char *, type *);

static void
print_index_with(object *input, index_func fn)
{
	object *p = input->u.u_obj;
	info *i = p->u.u_info;
	char *a = p->name;
	char *u = (i->implemented ? "implemented" : "used");

	for (p = i->elements; p != NULL; p = p->next) {
		switch (p->objtype) {
		case OBJ_IF: {
			/* Deal with preprocessing directives */
			char *c;

			c = p->name;
			if (fn == print_item_m) {
				switch (p->u.u_iftype) {
				case CMD_IF:
				case CMD_IFDEF:
				case CMD_IFNDEF:
				case CMD_ELSE:
					stack_if(p);
					break;

				case CMD_ENDIF:
					if (unstack_if()->u.u_iftype == CMD_ELSE) {
						IGNORE unstack_if();
					}
					break;

				default:
					break;
				}
			} else if (streq(c, BUILDING_MACRO)) {
				/* Check for the building_libs macro */
				switch (p->u.u_iftype) {
				case CMD_IF:
				case CMD_IFDEF:  building_libs = 2;                 break;
				case CMD_IFNDEF: building_libs = 0;                 break;
				case CMD_ELSE:   building_libs = 2 - building_libs; break;
				case CMD_ENDIF:  building_libs = 1;                 break;
				default: break;
				}
			} else {
				/* Check for integers */
				int n = 0;

				/* TODO: strtol? */
				while (*c == '-') {
					c++;
				}
				while (isdigit((int) *c)) {
					n = 10 * n + (*c - '0');
					c++;
				}

				if (*c == 0) {
					switch (p->u.u_iftype) {
					case CMD_IF:    commented_out = (n ? 0 : 2);       break;
					case CMD_ELSE:  commented_out = 2 - commented_out; break;
					case CMD_ENDIF: commented_out = 1;                 break;
					default:                                           break;
					}
				}
			}
			break;
		}

		case OBJ_SET:
			/* Deal with subsets */
			print_index_with(p, fn);
			break;

		case OBJ_TOKEN:
			/* Deal with tokens */
			if (i->implemented || !restrict_use) {
			   fn(p, u, a, (type *) NULL);
			}
			break;

		default:
			break;
		}
	}
}

/*
 * PRINT MACHINE PROCESSABLE INDEX
 *
 * This routine prints an index intended for machine processing of the
 * set object input.
 */
void
print_machine_index(object *input)
{
	print_index_with(input, print_item_m);
}

/*
 * PRINT INDEX
 *
 * This routine prints an index intended for human readers of the set
 * object input.
 */
void
print_index(object *input)
{
	print_index_with(input, print_item_h);
}

