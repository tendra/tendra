/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include "config.h"
#include <ctype.h>
#include "types.h"
#include "file.h"
#include "high.h"
#include "names.h"
#include "node.h"
#include "shape.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"
#include "write.h"


/*
    FLAGS CONTROLLING OUTPUT OF TOKENS ETC

    The output is in the fully expanded form if verbose is true.  The
    shape of each expression is printed if print_shapes is true.  The
    flag func_output controls whether the output should be lisp-like
    (default) or c-like.
*/

boolean verbose = 0;
boolean print_shapes = 0;
boolean func_output = 0;


/*
    PRINT A NUMBER OF SPACES

    An indentation of d spaces is printed to the output file.
*/

static void
print_spaces(int d)
{
	d *= 2;
	while (d--)
		(void) fputc(' ', output);
}


/*
    PRINT A NODE

    The node p is printed to the output file with an indentation of
    d spaces.
*/

static boolean
print_node(node *p, int d)
{
	boolean negate = 0;
	boolean newline = 0;

	while (p) {
		construct *q = p->cons;
		sortname s = q->sortnum;
		long m = q->encoding;

		newline = 0;
		switch (s) {
		case SORT_tdfbool:
			/* Set neg for subsequent number */
			negate = (boolean)(m ? 1 : 0);
			break;
		case SORT_bytestream:
			/* Print a bytestream */
			newline = print_node(p->son, d);
			break;
		case SORT_completion:
			/* Print a completion */
			newline = print_node(p->son, d);
			break;
		case SORT_small_tdfint:
				/* Print a small number */
			{
				long n = q->encoding;

				print_spaces(d);

				if (negate)
					n = -n;

				(void) fprintf(output, "%ld", n);
				negate = 0;
				newline = 1;
			}
			break;
		case SORT_tdfint:
			/* Print a number */
			{
				char *num = q->name;

				print_spaces(d);

				if (fits_ulong(num, 0)) {
					unsigned long n = octal_to_ulong(num);

					if (negate && n)
						(void) fputc('-', output);

					(void) fprintf(output, "%lu", n);
				} else {
					if (negate)
						(void) fputc('-', output);

					(void) fprintf(output, "0%s", num);
				}

				negate = 0;
				newline = 1;
			}
			break;
		case SORT_option:
			/* Print an optional argument */
			{
				if (p->son)
					newline = print_node(p->son, d);
				else {
					print_spaces(d);
					(void) fputc('-', output);
					newline = 1;
				}
			}
			break;
		case SORT_repeat:
			/* Print a repeated argument */
			{
				if (m == 0) {
					print_spaces(d);
					(void) fputc('|', output);
					newline = 1;
				} else {
					newline = print_node(p->son, d);

					if (func_output)
						(void) fputc(',', output);

					(void) fputs(" |", output);
				}
			}
			break;
		case SORT_tdfstring:
			/* Print a string */
			{
				int i, n = (int)m;

				print_spaces(d);

				if (n == -1) {
					char *f = (func_output ? "%s (\n" : "( %s\n");

					(void) fprintf(output, f, MAKE_STRING);
					newline = print_node(p->son, d + 1);
					(void) fputs(" )", output);
				} else {
					(void) fputc('"', output);

					for (i = 0; i < n; i++) {
						int c = ((q->name[i]) & 0xff);

						if (isprint(c)) {
							if (c == '\\' || c == '"') {
								(void) fputc('\\', output);
							}

							(void) fputc(c, output);
						} else {
							if (c == '\n') {
								(void) fputs("\\n", output);
							} else if (c == '\t') {
								(void) fputs("\\t", output);
							} else {
								unsigned co = (unsigned)c;
								(void) fprintf(output, "\\%03o", co);
							}
						}
					}

					(void) fputc('"', output);
					newline = 1;
				}
			}
			break;
		case SORT_nat:
			/* Print a nat */
			if (m != ENC_make_nat)
				goto default_label;

			newline = print_node(p->son, d);
			break;
		case SORT_signed_nat:
			/* Print a signed_nat */
			if (m != ENC_make_signed_nat)
				goto default_label;
			newline = print_node(p->son, d);
			break;
		case SORT_string:
			/* Print a string */
			if (m != ENC_make_string)
				goto default_label;

			newline = print_node(p->son, d);
			break;
		case SORT_al_tag:
			/* Print an alignment tag */
			if (verbose || m != ENC_make_al_tag || p->son == NULL)
				goto default_label;

			newline = print_node(p->son, d);
			break;
		case SORT_label:
			/* Print a label */
			if (verbose || m != ENC_make_label || p->son == NULL)
				goto default_label;

			newline = print_node(p->son, d);
			break;
		case SORT_tag:
			/* Print a tag */
			if (verbose || m != ENC_make_tag || p->son == NULL)
				goto default_label;

			newline = print_node(p->son, d);
			break;
		case SORT_exp:
			{
				static node special_node;

				/* Change exp to show shape */
				if (print_shapes && p->shape != &special_node) {
					node *z = new_node();

					z->cons = &exp_shape;
					z->bro = p->bro;
					z->son = p;

					if (p->shape) {
						z->son->bro = copy_node(p->shape);
					} else {
						z->son->bro = new_node();
						z->son->bro->cons = &unknown_cons;
					}

					p->shape = &special_node;
					p = z;
					q = p->cons;
					m = q->encoding;
				}

				goto default_label;
			}
		default:
default_label:
			/* Print a simple sort */
			if (!verbose && m == sort_tokens[s] && p->son &&
			    p->son->cons->sortnum == SORT_token) {
				newline = print_node(p->son, d);
			} else {
				print_spaces(d);

				if (p->son) {
					char *f = (func_output ? "%s (\n" : "( %s\n");
					(void) fprintf(output, f, q->name);
					newline = print_node(p->son, d + 1);
					(void) fputs(" )", output);
				} else {
					(void) fprintf(output, "%s", q->name);
					newline = 1;
				}
			}
			break;
		}

		p = p->bro;
		if (newline && p) {
			if (func_output)
				(void) fputc(',', output);

			(void) fputc('\n', output);
			newline = 0;
		}
	}

	return newline;
}


/*
    PRINT AN EXTERNAL NAME

    The start of a statement with name title concerning the construct
    p is output.  dec is true if this is the first statement concerning p.
*/

static void
print_name(char *title, construct *p, int dec)
{
	if (!func_output)
		(void) fputs("( ", output);

	if (p->ename == NULL)
		(void) fprintf(output, "%s ", LOCAL_DECL);

	(void) fprintf(output, "%s", title);

	if (func_output)
		(void) fputs(" (", output);

	if (p->ename && p->ename->cons->encoding && dec) {
		char *f = (func_output ? "\n  %s (\n" : "\n  ( %s\n");
		if (p->ename->son->cons->sortnum == SORT_tdfstring) {
			if (p->ename->son->bro == NULL)
				(void) fprintf(output, f, MAKE_STRING_EXTERN);
			else
				(void) fprintf(output, f, MAKE_CHAIN_EXTERN);

		} else
			(void) fprintf(output, f, MAKE_UNIQUE_EXTERN);

		(void) print_node(p->ename->son, 2);

		if (func_output)
			(void) fputs(" ),\n  ", output);
		else
			(void) fputs(" )\n  ", output);

	} else
		(void) fputc(' ', output);

	(void) fprintf(output, "%s", p->name);
}


/*
    ALIGNMENT TAG DECLARATION AUXILIARY PRINTING ROUTINE

    Print the declaration of the alignment tag p.
*/

static void
print_aldec(construct *p)
{
	if (p->encoding == -1)
		return;

	print_name(MAKE_ALDEC, p, 1);
	(void) fputs((func_output ? " ) ;\n\n" : " )\n\n"), output);
}


/*
    ALIGNMENT TAG DEFINITION AUXILIARY PRINTING ROUTINE

    Print the definition of the alignment tag p.
*/

static void
print_aldef(construct *p)
{
	al_tag_info *info = get_al_tag_info(p);

	if (p->encoding == -1)
		return;

	if (info->def == NULL)
		return;

	print_name(MAKE_ALDEF, p, !show_aldecs);

	if (func_output)
		(void) fputc(',', output);

	(void) fputc('\n', output);
	(void) print_node(info->def, 1);
	(void) fputs((func_output ? " ) ;\n\n" : " )\n\n"), output);
}


/*
    TAG DECLARATION AUXILIARY PRINTING ROUTINE

    Print the declaration of the tag p.
*/

static void
print_tagdec(construct *p)
{
	tag_info *info = get_tag_info(p);

	if (p->encoding == -1 || info->dec == NULL)
		return;

	switch (info->var) {
	case 0: print_name(MAKE_ID_TAGDEC, p, 1); break;
	case 1: print_name(MAKE_VAR_TAGDEC, p, 1); break;
	case 2: print_name(COMMON_TAGDEC, p, 1); break;
	}

	if (func_output)
		(void) fputc(',', output);

	(void) fputc('\n', output);
	(void) print_node(info->dec, 1);
	(void) fputs((func_output ? " ) ;\n\n" : " )\n\n"), output);
}


/*
    TAG DEFINITION AUXILIARY PRINTING ROUTINE

    Print the definition of the tag p.
*/

static void
print_tagdef(construct *p)
{
	char *instr = NULL;
	tag_info *info = get_tag_info(p);
	node *d = info->def;

	if (p->encoding == -1 || d == NULL)
		return;

	switch (info->var) {
	case 0: instr = MAKE_ID_TAGDEF; break;
	case 1: instr = MAKE_VAR_TAGDEF; break;
	case 2: instr = COMMON_TAGDEF; break;
	}

	/* Can have multiple definitions */
	while (d) {
		print_name(instr, p, !show_tagdecs);

		if (func_output)
			(void) fputc(',', output);

		(void) fputc('\n', output);
		(void) print_node(d->son, 1);
		(void) fputs((func_output ? " ) ;\n\n" : " )\n\n"), output);
		d = d->bro;
	}
}


/*
    TOKEN DECLARATION AUXILIARY PRINTING ROUTINE

    Print the declaration of the token p.
*/

static void
print_tokdec(construct *p)
{
	tok_info *info = get_tok_info(p);

	if (p->encoding == -1)
		return;

	if (!info->dec)
		return;

	print_name(MAKE_TOKDEC, p, 1);

	if (func_output)
		(void) fputc(',', output);

	(void) fputc('\n', output);

	if (info->sig)
		(void) print_node(info->sig, 1);
	else {
		print_spaces(1);
		(void) fputc('-', output);
	}

	if (func_output)
		(void) fputc(',', output);

	(void) fputs("\n  ", output);

	if (info->args) {
		int n = 0;
		char *q = info->args;

		(void) fputs("( ", output);

		while (*q) {
			sortname s;

			q = find_sortname(q, &s);
			q++;

			if (n++ == 8) {
				(void) fputs("\n  ", output);
				n = 1;
			}

			(void) fputs(sort_name(s), output);

			if (func_output && *q)
				(void) fputc(',', output);

			(void) fputc(' ', output);
		}

		(void) fputs(") ", output);

		if (func_output)
			(void) fputs("-> ", output);
	}

	(void) fputs(sort_name(info->res), output);
	(void) fputs((func_output ? " ) ;\n\n" : " )\n\n"), output);
}


/*
    TOKEN DEFINITION AUXILIARY PRINTING ROUTINE

    Print the definition of the token p.
*/

static void
print_tokdef(construct *p)
{
	tok_info *info = get_tok_info(p);

	if (p->encoding == -1)
		return;

	if (!info->dec)
		return;

	if (info->def == NULL)
		return;

	print_name(MAKE_TOKDEF, p, !show_tagdefs);

	if (func_output)
		(void) fputc(',', output);

	(void) fputc('\n', output);

	if (info->sig) {
		(void) print_node(info->sig, 1);
	} else {
		print_spaces(1);
		(void) fputc('-', output);
	}

	if (func_output)
		(void) fputc(',', output);

	(void) fputs("\n  ", output);

	if (info->args) {
		int n = 0;
		construct **q = info->pars;

		(void) fputs("( ", output);

		while (*q) {
			tok_info *qinfo = get_tok_info(*q);

			if (n++ == 4) {
				(void) fputs("\n    ", output);
				n = 1;
			}

			(void) fprintf(output, "%s %s", sort_name(qinfo->res),
			    (*q) ->name);
			q++;

			if (func_output && *q)
				(void) fputc(',', output);

			(void) fputc(' ', output);
		}

		(void) fputs(") ", output);

		if (func_output)
			(void) fputs("-> ", output);
	}

	(void) fputs(sort_name(info->res), output);

	if (func_output)
		(void) fputc(',', output);

	(void) fputc('\n', output);
	(void) print_node(info->def, 1);
	(void) fputs((func_output ? " ) ;\n\n" : " )\n\n"), output);
}


/*
    PRINT A HIGH-LEVEL SORT

    This routine prints the high level sort h.
*/

static void
print_high_sort(high_sort *h)
{
	int i, n;

	if (h->id == SORT_unknown)
		return;

	if (func_output)
		(void) fprintf(output, "%s ( %s, ", MAKE_SORT, h->name);
	else
		(void) fprintf(output, "( %s %s ", MAKE_SORT, h->name);

	n = h->no_args;

	if (n) {
		int m = 0;

		(void) fputs("( ", output);

		for (i = 0; i < n; i++) {
			if (m++ == 8) {
				(void) fputs("\n  ", output);
				m = 1;
			}

			(void) fputs(sort_name(h->args[i]), output);

			if (func_output && i < n - 1)
				(void) fputc(',', output);

			(void) fputc(' ', output);
		}

		(void) fputs(") ", output);

		if (func_output)
			(void) fputs("-> ", output);
	}

	(void) fputs(sort_name(h->res), output);
	(void) fputs((func_output ? " ) ;\n\n" : " )\n\n"), output);
}


/*
    MAIN PRINTING ROUTINE

    This routine prints an entire capsule to the output file.
*/

void
print_capsule(void)
{
	if (high_sorts) {
		int i;

		(void) fputs("# HIGH-LEVEL SORTS\n\n", output);

		for (i = 0; i < crt_high_sort; i++)
			print_high_sort(high_sorts + i);

		(void) fputc('\n', output);
	}

	if (show_tokdecs) {
		(void) fputs("# TOKEN DECLARATIONS\n\n", output);
		apply_to_all(print_tokdec, SORT_token);
		(void) fputc('\n', output);
	}

	if (show_aldecs) {
		(void) fputs("# ALIGNMENT TAG DECLARATIONS\n\n", output);
		apply_to_all(print_aldec, SORT_al_tag);
		(void) fputc('\n', output);
	}

	if (show_tagdecs) {
		(void) fputs("# TAG DECLARATIONS\n\n", output);
		apply_to_all(print_tagdec, SORT_tag);
		(void) fputc('\n', output);
	}

	if (show_tokdefs) {
		(void) fputs("# TOKEN DEFINITIONS\n\n", output);
		apply_to_all(print_tokdef, SORT_token);
		(void) fputc('\n', output);
	}

	if (show_aldefs) {
		(void) fputs("# ALIGNMENT TAG DEFINITIONS\n\n", output);
		apply_to_all(print_aldef, SORT_al_tag);
		(void) fputc('\n', output);
	}

	if (show_tagdefs) {
		(void) fputs("# TAG DEFINITIONS\n\n", output);
		apply_to_all(print_tagdef, SORT_tag);
		(void) fputc('\n', output);
	}
}
