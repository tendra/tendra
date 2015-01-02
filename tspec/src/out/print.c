/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <time.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include <out/print.h>

#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "utility.h"

#define SUBSET_TO_SUBSET ".."
#define INCLUDE_TO_SUBSET "../../subset"

/*
 * OUTPUT MACROS
 *
 * These macros are used as convenient shorthands for various print
 * routines.
 */
#define OUT        IGNORE fprintf
#define OUTC(X, Y) IGNORE fputc(Y, X)
#define OUTS(X, Y) IGNORE fputs(Y, X)

/*
 * OUTPUT TRICKS
 *
 * A number of minor tricks are required in the headers, mostly due to
 * library building problems.
 */
static bool weak_proto = 0;
#define enum_hack "__enum_"
#define is_hidden(X) (strncmp(X, HIDDEN_NAME, HIDDEN_LEN) == 0)

/*
 * OUTPUT FILE
 *
 * These variables hold information about the current output file.
 */
static info *crt_info = NULL;
static int column = 0;

/*
 * DOES A TYPE HAVE A TAIL COMPONENT?
 *
 * This routine checks whether the type t has an array, bitfield or
 * function component.
 */
static int
is_tailed_type(type *t)
{
	if (t == NULL) {
		return 0;
	}

	switch (t->id) {
	case TYPE_ARRAY:
	case TYPE_BITFIELD:
	case TYPE_PROC:
		return 1;

	default:
		return 0;
	}
}

/*
 * PRINT THE HEAD OF A TYPE
 *
 * This routine prints the head of the type t, that is to say the base type
 * and the pointer components, to the file output.
 */
static int
print_head(FILE *output, type *t, int sp, int tok)
{
	if (t == NULL) {
		return sp;
	}

	switch (t->id) {
	case TYPE_VOID:
	case TYPE_INT:
	case TYPE_SIGNED:
	case TYPE_UNSIGNED:
	case TYPE_FLOAT:
	case TYPE_ARITH:
	case TYPE_SCALAR:
	case TYPE_STRUCT:
	case TYPE_UNION:
	case TYPE_ENUM:
	case TYPE_GENERIC:
	case TYPE_DEFINED:
	case TYPE_PROMOTE:
		OUTS(output, t->u.obj->name);
		sp = 1;
		break;

	case TYPE_STRUCT_TAG:
		OUT(output, "struct %s", t->u.obj->name);
		sp = 1;
		break;

	case TYPE_UNION_TAG:
		OUT(output, "union %s", t->u.obj->name);
		sp = 1;
		break;

	case TYPE_ENUM_TAG:
		if (tok) {
			OUT(output, "%s%s", enum_hack, t->u.obj->name);
		} else {
			OUT(output, "enum %s", t->u.obj->name);
		}
		sp = 1;
		break;

	case TYPE_LVALUE:
		OUTS(output, "lvalue ");
		if (tok) {
			OUTS(output, ": ");
		}
		sp = print_head(output, t->u.subtype, 0, tok);
		break;

	case TYPE_QUALIFIER:
		OUT(output, "%s ", t->v.str);
		sp = print_head(output, t->u.subtype, 0, tok);
		break;

	case TYPE_RVALUE:
		if (tok) {
			OUTS(output, "rvalue : ");
		}
		sp = print_head(output, t->u.subtype, 0, tok);
		break;

	case TYPE_PTR: {
		type *s = t->u.subtype;
		char *q = t->v.str;

		sp = print_head(output, s, sp, tok);
		if (sp) {
			OUTC(output, ' ');
		}

		if (is_tailed_type(s)) {
			OUTS(output, "( *");
		} else {
			OUTS(output, "*");
		}

		sp = 0;
		if (q != NULL) {
			OUT(output, " %s", q);
			sp = 1;
		}
		break;
	}

	case TYPE_ARRAY:
	case TYPE_BITFIELD:
	case TYPE_PROC:
		sp = print_head(output, t->u.subtype, sp, tok);
		break;

	default:
		/* Unknown types */
		error(ERROR_INTERNAL, "Unknown type identifier, '%d'", t->id);
		break;
	}

	return sp;
}

/*
 * PRINT THE TAIL OF A TYPE
 *
 * This routine prints the tail of the type t, that is to say the array,
 * bitfield and function components, to the file output.
 */
static void
print_tail(FILE *output, type *t, int tok)
{
	if (t == NULL) {
		return;
	}

	switch (t->id) {
	case TYPE_LVALUE:
	case TYPE_RVALUE:
	case TYPE_QUALIFIER:
		print_tail(output, t->u.subtype, tok);
		break;

	case TYPE_PTR: {
		type *s = t->u.subtype;

		if (is_tailed_type(s)) {
			OUTS(output, " )");
		}
		print_tail(output, s, tok);
		break;
	}

	case TYPE_ARRAY:
		OUT(output, " [%s]", t->v.str);
		print_tail(output, t->u.subtype, tok);
		break;

	case TYPE_BITFIELD:
		if (tok) {
			OUT(output, " %% %s", t->v.str);
		} else {
			OUT(output, " : %s", t->v.str);
		}
		print_tail(output, t->u.subtype, tok);
		break;

	case TYPE_PROC: {
		type *s = t->v.next;

		if (s != NULL) {
			OUTS(output, " ( ");
			while (s != NULL) {
				print_type(output, s->u.subtype, NULL, tok);
				s = s->v.next;
				if (s != NULL) {
					OUTS(output, ", ");
				}
			}
			OUTS(output, " )");
		} else {
			OUTS(output, " ()");
		}

		print_tail(output, t->u.subtype, tok);
		break;
	}
	}
}

/*
 * PRINT A TYPE
 *
 * This routine prints the object nm of type t to the file output.
 */
void
print_type(FILE *output, type *t, char *nm, int tok)
{
	int sp;

	if (t == NULL) {
		return;
	}

	sp = print_head(output, t, 0, tok);
	if (nm != NULL) {
		if (sp) {
			OUTC(output, ' ');
		}
		OUTS(output, nm);
	}
	print_tail(output, t, tok);
}

/*
 * PRINT A STRUCT OR UNION DEFINITION
 *
 * This routine prints the specification for a structure or union type,
 * t, with internal name nm and external name tnm, to output.
 */
static void
print_struct_defn(FILE *output, type *t, char *nm, char *tnm, int d)
{
	char *tok = NULL, *tag = NULL;
	object *q = t->v.obj2;

	bool show_token  = 1, show_interface = 1;
	bool show_ignore = 1, show_defn = 1;

	/* Find the token type */
	switch (t->id) EXHAUSTIVE {
	case TYPE_STRUCT:     tok = "STRUCT"; tag = "";     break;
	case TYPE_STRUCT_TAG: tok = "STRUCT"; tag = "TAG "; break;
	case TYPE_UNION:      tok = "UNION";  tag = "";     break;
	case TYPE_UNION_TAG:  tok = "UNION";  tag = "TAG "; break;
	}

	/* Deal with undefined tokens immediately */
	if (q == NULL) {
		OUT(output, "#pragma token %s %s%s # %s\n", tok, tag, nm, tnm);
		return;
	}

	/* Deal with the various definition cases */
	switch (t->state) {
	case TYPE_IMMEDIATE:
		/* Definition is immediate */
		if (is_hidden(nm)) {
			show_token     = 0;
			show_interface = 0;
			show_ignore    = 0;
		}
		break;

	case TYPE_ELSEWHERE:
		/* Definition is elsewhere */
		show_interface = 0;
		show_ignore    = 0;
		show_defn      = 0;

		t->state = TYPE_EARLIER;
		break;

	case TYPE_EARLIER:
		/* Declaration was earlier in file */
		show_token = 0;
		t->state   = TYPE_IMMEDIATE;
		break;

	case TYPE_ANOTHER:
		/* Declaration was in another file */
		if (d) {
			show_token     = 0;
			show_interface = 0;

			t->state = TYPE_ELSEWHERE;
		} else {
			show_interface = 0;
			show_ignore    = 0;
			show_defn      = 0;

			t->state = TYPE_EARLIER;
		}
		break;
	}

	/* Print the token if necessary */
	if (show_token) {
		OUT(output, "#pragma token %s %s%s # %s\n", tok, tag, nm, tnm);
	}

	/* Print the interface statement */
	if (show_interface) {
		char *b = BUILDING_MACRO;
		OUT(output, "#ifdef %s\n", b);
		OUT(output, "#pragma interface %s%s\n", tag, nm);
		OUT ( output, "#else /* %s */\n", b ) ;
	}

	/* Print the ignore statement */
	if (show_ignore) {
		if (!show_interface) {
			char *b = BUILDING_MACRO;
			OUT(output, "#ifndef %s\n", b);
		}
		OUT(output, "#pragma ignore %s%s\n", tag, nm);
	}

	/* Print the type definition */
	if (show_defn) {
		tok = (tok [0] == 'S' ? "struct" : "union");
		if (*tag) {
			OUT(output, "%s %s {\n", tok, nm);
		} else {
			OUT(output, "typedef %s {\n", tok);
		}

		while (q) {
			field *f = q->u.u_obj->u.u_field;
			OUTS(output, "	");
			print_type(output, f->ftype, f->fname, 0);
			OUTS(output, " ;\n");
			q = q->next;
		}

		if (*tag) {
			OUTS(output, "} ;\n");
		} else {
			OUT(output, "} %s ;\n", nm);
		}
	}

	/* Print the final #endif */
	if (show_interface || show_ignore) {
		char *b = BUILDING_MACRO;
		OUT ( output, "#endif /* %s */\n", b ) ;
	}
}

/*
 * PRINT A TOKENISED TYPE
 *
 * This routine is the special case of print_token which deals with
 * tokenised types.
 */
static void
print_token_type(FILE *output, object *p, char *tnm)
{
	char *tok = "TYPE";
	char *nm = p->name;
	type *t = p->u.u_type;
	int i = t->id;

	switch (i) {
	case TYPE_DEFINED: {
		char *tm, *sp;
		type *s = t->v.next;
		char *b = BUILDING_MACRO;

		/* Defined types */
		if (s == type_bottom) {
			sp = "bottom";
		} else if (s == type_printf) {
			sp = "... printf";
		} else if (s == type_scanf) {
			sp = "... scanf";
		} else {
			OUTS(output, "typedef ");
			print_type(output, s, nm, 0);
			OUTS(output, " ;\n");
			break;
		}

		/* Allow for special types */
		tm = "__TenDRA__";
		OUT(output, "#ifndef %s\n", b);
		OUT(output, "#ifdef %s\n", tm);
		OUT(output, "#pragma TenDRA type %s for %s\n", nm, sp);
		OUT(output, "#else /* %s */\n", tm ) ;
		OUT(output, "typedef %s %s ;\n", s->u.obj->name, nm);
		OUT(output, "#endif /* %s */\n", tm ) ;
		OUT(output, "#else /* %s */\n", b ) ;
		OUT(output, "typedef %s %s ;\n", s->u.obj->name, nm);
		OUT(output, "#endif /* %s */\n", b ) ;

		break;
	}

	case TYPE_INT:      tok = "VARIETY";          goto generic_lab;
	case TYPE_SIGNED:   tok = "VARIETY signed";   goto generic_lab;
	case TYPE_UNSIGNED: tok = "VARIETY unsigned"; goto generic_lab;
	case TYPE_FLOAT:    tok = "FLOAT";            goto generic_lab;
	case TYPE_ARITH:    tok = "ARITHMETIC";       goto generic_lab;
	case TYPE_SCALAR:   tok = "SCALAR";           goto generic_lab;

	case TYPE_GENERIC:
generic_lab:
		/* Generic types */
		OUT(output, "#pragma token %s %s # %s\n", tok, nm, tnm);
		break;

	case TYPE_PROMOTE: {
		/* Promotion types */
		char *pt = t->v.next->u.obj->name;
		OUT(output, "#pragma token VARIETY %s # %s\n", nm, tnm);
		OUT(output, "#pragma promote %s : %s\n", pt, nm);
		break;
	}

	case TYPE_STRUCT:
	case TYPE_STRUCT_TAG:
	case TYPE_UNION:
	case TYPE_UNION_TAG:
		/* Structure or union types */
		print_struct_defn(output, t, nm, tnm, 0);
		break;

	case TYPE_ENUM:
	case TYPE_ENUM_TAG: {
		/* Enumeration types are a complete hack */
		char *b = BUILDING_MACRO;
		bool tagged = i == TYPE_ENUM ? 0 : 1;
		object *q;

		OUT(output, "#ifndef %s\n", b);

		/* Print the enumeration type */
		if (tagged) {
			OUT(output, "typedef enum %s {", nm);
		} else {
			OUTS(output, "typedef enum {");
		}

		/* Print the enumeration elements */
		for (q = t->v.obj2; q != NULL; q = q->next) {
			object *r = q->u.u_obj;
			char *v   = r->u.u_str;

			if (v && v [0]) {
				OUT(output, "\n	%s = %s", r->name, v);
			} else {
				OUT(output, "\n	%s", r->name);
			}

			if (q->next != NULL) {
				OUTC(output, ',');
			}
		}

		/* Print the end of the enumeration type */
		if (tagged) {
			IGNORE sprintf(buffer, "%s%s", enum_hack, nm);
			OUT(output, "\n} %s ;\n", buffer);
		} else {
			OUT(output, "\n} %s ;\n", nm);
		}

		/* Print the hacked library building version */
		OUT(output, "#else /* %s */\n", b );
		if (tagged) {
			OUT(output, "typedef int %s ;\n", buffer);
		} else {
			OUT(output, "#pragma token VARIETY %s # %s\n", nm, tnm);
			OUT(output, "#pragma promote %s : %s\n", nm, nm);
			OUT(output, "#pragma interface %s\n", nm);
		}

		OUT(output, "#endif /* %s */\n", b);

		break;
	}

	default:
		/* Other types */
		error(ERROR_INTERNAL, "Unknown type identifier, '%d'", i);
		break;
	}
}

/*
 * PRINT A TOKEN
 *
 * This routine prints the object p, representing the token tnm, to the
 * file output.
 */
static void
print_token(FILE *output, object *p, char *tnm)
{
	char *nm = p->name;
	switch (p->objtype) {
	case OBJ_CONST:
	case OBJ_EXP: {
		/* Constants and expressions */
		type *t = p->u.u_type;

		OUTS(output, "#pragma token EXP ");
		if (p->objtype == OBJ_CONST && t->id == TYPE_RVALUE) {
			OUTS(output, "const : ");
			t = t->u.subtype;
		}

		print_type(output, t, NULL, 1);
		OUT(output, " : %s # %s\n", nm, tnm);
		break;
	}

	case OBJ_EXTERN: {
		/* External expressions */
		type *t = p->u.u_type;

		if (t->id == TYPE_LVALUE) {
			t = t->u.subtype;
		}

		OUTS(output, "extern ");
		print_type(output, t, nm, 0);
		OUTS(output, " ;\n");

		break;
	}

	case OBJ_WEAK: {
		/* Weak prototype declarations */
		int sp;
		char *w = WEAK_PROTO;
		type *t = p->u.u_type;

		if (!weak_proto) {
			char *b = BUILDING_MACRO;
			OUT(output, "#ifndef %s\n", w);
			OUT(output, "#ifndef %s\n", b);
			OUT(output, "#pragma TenDRA keyword %s_KEY for weak\n", w);
			OUT(output, "#define %s( A )\t%s_KEY A\n", w, w);
			OUT ( output, "#else /* %s */\n", b ) ;
			OUT(output, "#define %s( A )\t()\n", w);
			OUT ( output, "#endif /* %s */\n", b ) ;
			OUT ( output, "#endif /* %s */\n\n", w ) ;
			weak_proto = 1;
		}

		OUTS(output, "extern ");
		sp = print_head(output, t, 0, 0);
		if (sp) {
			OUTC(output, ' ');
		}
		OUT(output, "%s %s (", nm, w);
		print_tail(output, t, 0);
		OUTS(output, " ) ;\n");

		break;
	}

	case OBJ_DEFINE: {
		/* Macro definitions */
		char *s = p->u.u_str;

		OUT(output, "#define %s%s\n", nm, s);
		break;
	}

	case OBJ_DEFMIN: {
		/* Macro definitions */
		char *s = p->u.u_str;

		OUT(output, "#if defined(%s) && %s < %s\n", nm, nm, s);
		OUT(output, "/* Should probably be an #error */\n");
		OUT(output, "#define %s%s\n", nm, s);
		OUT(output, "#elif !defined(%s)\n", nm);
		OUT(output, "#define %s%s\n", nm, s);
		OUT(output, "#endif\n");
		break;
	}

	case OBJ_FIELD: {
		/* Field selectors */
		field *f = p->u.u_field;

		OUTS(output, "#pragma token MEMBER ");
		print_type(output, f->ftype, NULL, 1);
		OUTS(output, " : ");
		print_type(output, f->stype, NULL, 1);
		OUT(output, " : %s # %s\n", f->fname, tnm);
		break;
	}

	case OBJ_FUNC: {
		/* Functions */
		type *t = p->u.u_type;

		OUTS(output, "#pragma token FUNC ");
		print_type(output, t, NULL, 1);
		OUT(output, " : %s # %s\n", nm, tnm);
		break;
	}

	case OBJ_MACRO: {
		/* Macros */
		type *t = p->u.u_type;
		type *s = t->v.next;

		OUTS(output, "#pragma token PROC ( ");

		/* Print the macro arguments */
		while (s && s != type_none ) {
			OUTS(output, "EXP ");
			print_type(output, s->u.subtype, NULL, 1);
			s = s->v.next;
			OUTS(output,(s ? " : , " : " : "));
		}

		/* Print the macro result */
		OUTS(output, ") EXP ");
		print_type(output, t->u.subtype, NULL, 1);
		OUT(output, " : %s # %s\n", nm, tnm);

		break;
	}

	case OBJ_NAT:
		/* Nats */
		OUT(output, "#pragma token NAT %s # %s\n", nm, tnm);
		break;

	case OBJ_STATEMENT: {
		/* Statements */
		type *t = p->u.u_type;

		if (t != NULL) {
			/* Statements with arguments */
			type *s;

			OUTS(output, "#pragma token PROC ( ");

			for (s = t->v.next; s != NULL && s != type_none; s = s->v.next) {
				OUTS(output, "EXP ");
				print_type(output, s->u.subtype, NULL, 1);
				OUTS(output, (s->v.next ? " : , " : " : "));
			}

			OUT(output, ") STATEMENT %s # %s\n", nm, tnm);
		} else {
			/* Statements with no arguments */
			OUT(output, "#pragma token STATEMENT %s # %s\n", nm, tnm);
		}
		break;
	}

	case OBJ_TOKEN: {
		/* Tokens */
		char *s = p->u.u_str;

		OUT(output, "#pragma token %s %s # %s\n", s, nm, tnm);
		break;
	}

	case OBJ_TYPE:
		/* Types */
		print_token_type(output, p, tnm);
		break;

	default:
		/* Unknown objects */
		error(ERROR_INTERNAL, "Unknown object type, '%d'", p->objtype);
		break;
	}
}

/*
 * TYPE REPRESENTING AN IF STATEMENT
 *
 * All if, else and endif statements are stored and simplified prior to
 * output.  The ifcmd structure is used to represent the commands, with
 * the dir field giving the command type and the nm field the associated
 * expression.
*/

typedef struct {
	enum obj_iftype dir;
	char *nm;
} ifcmd;

/*
 * PRINT A NUMBER OF IF STATEMENTS
 *
 * This routine outputs the list of if statements, ifs, to the file
 * output.
 */
static void
print_ifs(FILE *output, ifcmd *ifs)
{
	ifcmd *p;
	bool changed;

	/* Simplify the list of statements */
	do {
		ifcmd *q = NULL;

		changed = 0;
		for (p = ifs; p->dir != CMD_END; p++) {
			int d = p->dir;
			int e;

			if (d == CMD_NONE) {
				continue;
			}

			if (q == NULL || q->dir == CMD_NONE) {
				q = p;
				continue;
			}

			e = q->dir;

			if (d == CMD_ENDIF) {
				if (e == CMD_ELSE) {
					/* else + endif -> endif */
					q->dir = CMD_NONE;
					changed = 1;
				} else if (e != CMD_ENDIF) {
					/* if + endif -> nothing */
					p->dir = CMD_NONE;
					q->dir = CMD_NONE;
					changed = 1;
				}
			}

			if (d == CMD_ELSE) {
				if (e == CMD_IFDEF) {
					/* ifdef + else -> ifndef */
					p->dir = CMD_IFNDEF;
					q->dir = CMD_NONE;
					changed = 1;
				} else if (e == CMD_IFDEF) {
					/* ifndef + else -> ifdef */
					p->dir = CMD_IFDEF;
					q->dir = CMD_NONE;
					changed = 1;
				}
			}

			q = p;
		}
	} while (changed);

	/* Print the result */
	if (column) {
		OUTC(output, '\n');
	}

	for (p = ifs; p->dir != CMD_END; p++) {
		switch (p->dir) {
		case CMD_IF:     OUT(output, "#if %s\n", p->nm);          break;
		case CMD_IFDEF:  OUT(output, "#ifdef %s\n", p->nm);       break;
		case CMD_IFNDEF: OUT(output, "#ifndef %s\n", p->nm);      break;
		case CMD_ELSE:   OUT(output, "#else /* %s */\n", p->nm);  break;
		case CMD_ENDIF:  OUT(output, "#endif /* %s */\n", p->nm); break;

		default:
			break;
		}
	}

	column = 0;
	ifs [0].dir = CMD_END;
}

/*
 * PRINT AN INTERFACE ITEM
 *
 * This routine prints an interface statement for the object p to the
 * file output.
 */
static void
print_interface(FILE *output, object *p, ifcmd *ifs)
{
	char *nm = p->name;
	int n;

	switch (p->objtype) {
	case OBJ_CONST:
	case OBJ_EXP:
	case OBJ_MACRO:
	case OBJ_NAT:
	case OBJ_STATEMENT:
	case OBJ_TOKEN:
		/* Simple tokens are easy */
		break;

	case OBJ_EXTERN:
	case OBJ_WEAK:
		/* Deal with externals */
		nm = NULL;
		break;

	case OBJ_FIELD: {
		/* Deal with fields */
		field *f = p->u.u_field;

		switch (f->stype->id) {
		case TYPE_STRUCT_TAG:
		case TYPE_UNION_TAG:
			/* Tagged types require some attention */
			IGNORE sprintf(buffer, "TAG %s", nm);
			nm = buffer;
			break;
		}

		break;
	}

	case OBJ_FUNC: {
		/* Functions containing ... are not actually tokens */
		type *t;

		for (t = p->u.u_type->v.next; t != NULL; t = t->v.next) {
			if (t->u.subtype == type_ellipsis) {
				nm = NULL;
				break;
			}
		}

		break;
	}

	case OBJ_DEFINE:
		/* Macro definitions are not tokens */
		nm = NULL;
		break;

	case OBJ_DEFMIN:
		/* Macro definitions are not tokens */
		nm = NULL;
		break;

	case OBJ_TYPE: {
		/* Deal with types */
		type *t = p->u.u_type;

		switch (t->id) {
		case TYPE_STRUCT_TAG:
		case TYPE_UNION_TAG:
			/* Tagged types require some attention */
			IGNORE sprintf(buffer, "TAG %s", nm);
			nm = buffer;
			goto type_struct_lab;

		case TYPE_STRUCT:
		case TYPE_UNION:
type_struct_lab:
			/* Some structures and unions are not tokens */
			if (t->v.obj2) {
				if (t->state == TYPE_EARLIER) {
					t->state = TYPE_ANOTHER;
				} else {
					nm = NULL;
				}
			}
			break;

		case TYPE_DEFINED:
			/* Type definitions are not tokens */
			nm = NULL;
			break;

		case TYPE_ENUM:
		case TYPE_ENUM_TAG:
			/* Enumeration types are not tokens */
			nm = NULL;
			break;
		}
		break;
	}

	default:
		/* Unknown objects */
		error(ERROR_INTERNAL, "Unknown object type, '%d'", p->objtype);
		nm = NULL;
		break;
	}

	/* Print the interface statement */
	if (nm == NULL) {
		return;
	}

	n = (int) strlen(nm) + 1;

	if (ifs [0].dir != CMD_END) {
		print_ifs(output, ifs);
	}

	if (column + n >= 60) {
		OUTC(output, '\n');
		column = 0;
	}

	if (column == 0) {
		OUTS(output, "#pragma interface");
	}

	OUTC(output, ' ');
	OUTS(output, nm);

	column += n;
}

/*
 * PRINT AN INCLUDED FILE
 */
static void
print_include(FILE *output, char *nm, int on)
{
	object *p;

	if (nm == NULL) {
		return;
	}

	IGNORE sprintf(buffer, "%s[%s]", crt_info->src, nm);
	if (search_hash(files, buffer, no_version)) {
		return;
	}

	p = make_object(xstrdup(buffer), OBJ_FILE);
	p->u.u_file = NULL;
	IGNORE add_hash(files, p, no_version);

	if (on) {
		OUT(output, "#include <%s>\n", nm);
	}
}

/*
 * PRINT AN OBJECT
 *
 * This routine prints the list of objects input to the file output, the
 * form of the information to be printed being indicated by pass.
 */
static void
print_object(FILE *output, object *input, int pass)
{
	ifcmd ifs [100];
	object *p;

	ifs[0].dir = CMD_END;

	for (p = input; p != NULL; p = p->next) {
		char *nm = p->name;

		switch (p->objtype) {
		case OBJ_IF: {
			int i;

			/* If statements etc. */
			if (pass == 1) {
				break;
			}

			for (i = 0; ifs[i].dir != CMD_END; i++)
				;

			ifs[i].dir = p->u.u_num;
			ifs[i].nm  = p->name;
			ifs[i + 1].dir = CMD_END;

			if (i >= 90) {
				print_ifs(output, ifs);
			}

			break;
		}

		case OBJ_IMPLEMENT:
		case OBJ_USE: {
			/* Inclusion statements */
			object *q;
			info *i;
			char *b;
			char *f;
			char *m;
			size_t n;

			if (nm[pass] != '1') {
				break;
			}

			q = p->u.u_obj;
			i = q->u.u_info;
			b = BUILDING_MACRO;

			if (0 == strcmp(i->api, LOCAL_API)) {
				break;
			}

			if (ifs [0].dir != CMD_END) {
				print_ifs(output, ifs);
			}

			if (pass != 0) {
				print_include(output, strip_extension(i->file), 1);
				break;
			}

			m = i->protect;

			if (nm[2] == 'G') {
				char *dir;
				OUT(output, "#ifndef %s\n", b);
				dir = "#pragma extend interface [%s]\n";
				OUT(output, dir, strip_extension(i->file));
				OUT(output, "#else /* %s */\n", b);
				m = "";
			}

			if (*m) {
				OUT(output, "#ifndef %s\n", m);
			}

			n = strlen(output_dir) + 1;

			if (i->incl != NULL) {
				f = i->incl + n;
			} else {
				f = crt_info->incl + n;
			}

			OUT(output, "#pragma extend interface \"%s/%s\"\n", "../..", f);
			if (*m) {
				OUT(output, "#endif /* %s */\n", m);
			}

			if (nm[2] == 'G') {
				OUT(output, "#endif /* %s */\n", b);
			}

			break;
		}

		case OBJ_SET: {
			/* Subsets */
			object *q = p->u.u_obj;
			info *i = q->u.u_info;

			if (strcmp(i->api, LOCAL_API) == 0) {
				if (ifs[0].dir != CMD_END) {
					print_ifs(output, ifs);
				}
				print_object(output, i->elements, pass);
			} else {
				if (ifs[0].dir != CMD_END) {
					print_ifs(output, ifs);
				}
				print_set(p, pass);
			}
			break;
		}

		case OBJ_TEXT_INCL:
			/* Include file quoted text */
			if (pass != 0) {
				break;
			}

			if (ifs[0].dir != CMD_END) {
				print_ifs(output, ifs);
			}

			OUTS(output, nm);
			OUTC(output, '\n');
			break;

		case OBJ_TEXT_SRC:
			/* Source file quoted text */
			if (pass != 1) {
				break;
			}

			if (ifs[0].dir != CMD_END) {
				print_ifs(output, ifs);
			}

			OUTS(output, nm);
			OUTC(output, '\n');
			break;

		case OBJ_TOKEN:
			/* Tokenised objects */
			if (pass == 0) {
				if (ifs[0].dir != CMD_END) {
					print_ifs(output, ifs);
				}
				print_token(output, p->u.u_obj, nm);
			}
			break;

		case OBJ_TYPE:
			/* Definition of previously declared type */
			if (pass == 0) {
				type *t = p->u.u_type;
				char *tnm = t->u.obj->name;
				print_struct_defn(output, t, tnm, tnm, 1);
			}
			break;

		default:
			/* Unknown objects */
			error(ERROR_INTERNAL, "Unknown object type, '%d'", p->objtype);
			break;
		}
	}

	if (ifs[0].dir != CMD_END) {
		print_ifs(output, ifs);
	}
}

/*
 * PRINT AN OBJECT, PASS 2
 */
static void
print_object2(FILE *output, object *input)
{
	ifcmd ifs [100];
	object *p;

	ifs[0].dir = CMD_END;

	for (p = input; p != NULL; p = p->next) {
		switch (p->objtype) {
		case OBJ_IF: {
			int i;

			/* If statements etc. */

			for (i = 0; ifs[i].dir != CMD_END; i++)
				;

			ifs[i].dir = p->u.u_num;
			ifs[i].nm  = p->name;
			ifs[i + 1].dir = CMD_END;

			if (i >= 90) {
				print_ifs(output, ifs);
			}

			break;
		}

		case OBJ_IMPLEMENT:
		case OBJ_USE:
			/* Inclusion statements */
			break;

		case OBJ_SET: {
			/* Subsets */
			object *q = p->u.u_obj;
			info *i = q->u.u_info;

			if (strcmp(i->api, LOCAL_API) == 0) {
				if (ifs[0].dir != CMD_END) {
					print_ifs(output, ifs);
				}
				print_object2(output, i->elements);
			}
			break;
		}

		case OBJ_TEXT_INCL:
			/* Include file quoted text */
			break;

		case OBJ_TEXT_SRC:
			/* Source file quoted text */
			break;

		case OBJ_TOKEN:
			/* Tokenised objects */
			print_interface(output, p->u.u_obj, ifs);
			break;

		case OBJ_TYPE:
			/* Definition of previously declared type */
			break;

		default:
			/* Unknown objects */
			error(ERROR_INTERNAL, "Unknown object type, '%d'", p->objtype);
			break;
		}
	}

	if (ifs[0].dir != CMD_END) {
		print_ifs(output, ifs);
	}
}

/*
 * SCAN AN OBJECT
 *
 * This routine scans the object input, calling print_set on any subsets.
 */
static void
scan_object1(object *input)
{
	object *p;

	for (p = input; p != NULL; p = p->next) {
		object *q;
		info *i;

		if (p->objtype != OBJ_SET) {
			continue;
		}

		q = p->u.u_obj;
		i = q->u.u_info;

		if (0 == strcmp(i->api, LOCAL_API)) {
			scan_object1(i->elements);
		} else {
			print_set(p, 1);
		}
	}
}

/*
 * PRINT A SET
 *
 * This routine prints the set of objects given by input.  The form of the
 * output is indicated by pass.
 */
void
print_set(object *input, int pass)
{
	char *nm;
	time_t t1, t2;
	FILE *output = NULL;
	object *ss = input->u.u_obj;
	info *i = ss->u.u_info;
	object *q;
	info *old_info;
	int old_column;
	bool old_weak_proto;

	column = 0;

	if (0 == strcmp(i->api, LOCAL_API)) {
		if (pass != 0) {
			return;
		}

		/* Local files go to the standard output */
		nm     = "stdout";
		output = stdout;

		t1 = (time_t) 0;
		t2 = (time_t) 0;
	} else {
		nm = (pass ? i->src : i->incl);

		if (nm == NULL || (restrict_use && i->implemented == 0)) {
			scan_object1(i->elements);
			return;
		}

		if (pass == 1 && i->tokens == 0) {
			if (verbose > 1) {
				IGNORE printf("%s is not required ...\n", nm);
			}

			scan_object1(i->elements);
			return;
		}

		t1 = i->age;
		if (progdate > t1) {
			t1 = progdate;
		}
		t2 = date_stamp(nm);
	}

	if ((t1 && t1 < t2) && !force_output) {
		/* Output file is up to date */
		object *q;

		if (verbose > 1) {
			IGNORE printf("%s is up to date ...\n", nm);
		}

		q = make_object(nm, OBJ_FILE);
		q->u.u_file = NULL;
		IGNORE add_hash(files, q, no_version);

		for (q = i->elements; q != NULL; q = q->next) {
			if (q->objtype == OBJ_SET) {
				print_set(q, pass);
			}
		}

		return;
	}

	/* Output file needs updating */
	q = NULL;
	old_info = crt_info;
	old_column = column;
	old_weak_proto = weak_proto;
	weak_proto = 0;

	/* Open output file */
	if (output == NULL) {
		create_dir(nm);
		if (verbose) {
			IGNORE printf("Creating %s ...\n", nm);
		}

		check_name(nm);
		q = make_object(nm, OBJ_FILE);
		q->u.u_file = NULL;
		IGNORE add_hash(files, q, no_version);
		output = fopen(nm, "w");
		q->u.u_file = output;

		if (output == NULL) {
			error(ERROR_SERIOUS, "Can't open output file, %s", nm);
			return;
		}
	}

	crt_info = i;
	if (pass == 0) {
		/* Include output file */
		char *m = i->protect;
		char *v = i->version;

		/* Find the version number */
		if (v == NULL && i->subset) {
			char *a = subset_name(i->api, i->file, NULL);
			object *ap = make_subset(a);
			v = ap->u.u_info->version;
		}
		if (v == NULL && i->file) {
			char *a = subset_name(i->api, NULL, NULL);
			object *ap = make_subset(a);
			v = ap->u.u_info->version;
		}

		/* Print the file header */
		OUTS(output, "/*\n\tAUTOMATICALLY GENERATED BY ");
		OUT(output, "%s %s\n", progname, progvers);
		OUT(output, "\tAPI SUBSET: %s", ss->name);
		if (v != NULL) {
			OUT(output, " (VERSION %s)", v);
		}
		OUTS (output, "\n\tCopyright terms for the input source also apply to this generated code.");
		OUTS (output, "\n*/\n\n");

		/* Print the file body */
		if (*m != '\0') {
			OUT(output, "#ifndef %s\n", m);
			OUT(output, "#define %s\n\n", m);
		}

		if (i->elements) {
			bool is_cpplus = 0;

			if (i->linkage) {
				if (strcmp(i->linkage, "C++") == 0) {
					OUT(output, "extern \"%s\" {\n\n", i->linkage);
					is_cpplus = 1;
				} else {
					OUT(output, "#ifdef __cplusplus\n");
					OUT(output, "extern \"%s\" {\n", i->linkage);
					OUT(output, "#endif\n\n");
				}
			}

			if (i->nspace) {
				if (is_cpplus) {
					OUT(output, "namespace %s {\n\n", i->nspace);
				} else {
					OUT(output, "#ifdef __cplusplus\n");
					OUT(output, "namespace %s {\n", i->nspace);
					OUT(output, "#endif\n\n");
				}
			}

			if (i->block) {
				char *dir;
				dir = "#pragma TenDRA declaration block %s begin\n\n";
				OUT(output, dir, i->block);
			}

			print_object(output, i->elements, 0);
			if (i->tokens) {
				OUTC(output, '\n');
			}

			print_object2(output, i->elements);
			if (column) {
				OUTC(output, '\n');
			}

			if (i->block) {
				char *dir;
				dir = "\n#pragma TenDRA declaration block end\n";
				OUT(output, "%s", dir);
			}

			if (i->nspace) {
				if (is_cpplus) {
					OUT(output, "\n}\n");
				} else {
					OUT(output, "\n#ifdef __cplusplus\n");
					OUT(output, "}\n");
					OUT(output, "#endif\n");
				}
			}

			if (i->linkage) {
				if (is_cpplus) {
					OUT(output, "\n}\n");
				} else {
					OUT(output, "\n#ifdef __cplusplus\n");
					OUT(output, "}\n");
					OUT(output, "#endif\n");
				}
			}
		}

		if (*m) {
			OUT(output, "\n#endif /* %s */\n", m);
		}
	} else {
		/* Source output file */
		if (i->method == NULL) {
			char *m, *s;
			char *w1, *w2;

			m = macro_name(DEFINE_PREFIX, i->api, i->file, i->subset);
			w1 = macro_name(WRONG_PREFIX, i->api, NULL, NULL);
			w2 = macro_name(WRONG_PREFIX, i->api, i->file, i->subset);

			s = i->incl + strlen(output_dir) + 1;

			OUTS(output, "/*\n");
			OUT(output, " * AUTOMATICALLY GENERATED BY %s %s\n", progname, progvers);
			OUTS(output, " * Copyright terms for the input source also apply to this generated code.\n");
			OUT(output, " */\n\n");
			OUT(output, "#ifndef %s\n", w1);
			OUT(output, "#ifndef %s\n", w2);
			OUT(output, "#if #include ( %s )\n", strip_extension(i->file));
			OUT(output, "#define %s\n", m);
			print_include(output, strip_extension(i->file), 0);
			print_object(output, i->elements, 1);
			OUT(output, "#include <%s>\n", strip_extension(i->file));
			OUT(output, "#endif\n");
			OUT(output, "#endif\n\n");
			OUT(output, "#ifndef %s\n", m);
			OUT(output, "#pragma TenDRA no token definition allow\n");
			OUT(output, "#endif\n");
			OUT(output, "#pragma implement interface \"%s/%s\"\n", "../..", s);
			OUT(output, "#endif\n");
		} else {
			print_object(output, i->elements, 1);
		}
	}

	/* End the output */
	IGNORE fclose(output);
	if (q != NULL) {
		q->u.u_file = NULL;
	}
	crt_info = old_info;
	column = old_column;
	weak_proto = old_weak_proto;
}

