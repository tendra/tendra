/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "config.h"
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

bool fold_tncsorts = 1;

static const char *
sort_string(sortname s)
{
	switch (s) {
	case SORT_access:           return "access";
	case SORT_al_tag:           return "al_tag";
	case SORT_alignment:        return "alignment";
	case SORT_bitfield_variety: return "bitfield_variety";
	case SORT_bool:             return "bool";
	case SORT_error_treatment:  return "error_treatment";
	case SORT_exp:              return "exp";
	case SORT_floating_variety: return "floating_variety";
/*
	case SORT_foreign_sort:     return "foreign_sort";
*/
	case SORT_label:            return "label";
	case SORT_nat:              return "nat";
	case SORT_ntest:            return "ntest";
	case SORT_procprops:        return "procprops";
	case SORT_rounding_mode:    return "rounding_mode";
	case SORT_shape:            return "shape";
	case SORT_signed_nat:       return "signed_nat";
	case SORT_string:           return "string";
	case SORT_tag:              return "tag";
	case SORT_transfer_mode:    return "transfer_mode";
	case SORT_token:            return "token";
	case SORT_variety:          return "variety";
	case SORT_foreign:          return "foreign";
	case SORT_callees:          return "callees";
	case SORT_error_code:       return "error_code";
/*
	case SORT_sortname:         return "sortname";
	case SORT_unknown:          return "unknown";
*/
	case SORT_repeat:           return "repeat";
	case SORT_option:           return "option";
	case SORT_completion:       return "completion";
	case SORT_small_tdfint:     return "small_tdfint";
	case SORT_bitstream:        return "bitstream";
	case SORT_bytestream:       return "bytestream";
	case SORT_tdfbool:          return "tdfbool";
	case SORT_tdfident:         return "tdfident";
	case SORT_tdfint:           return "tdfint";
	case SORT_tdfstring:        return "tdfstring";

	default:
		return "?";
	}
}

static void
escputc(int c, FILE *f)
{
	size_t i;

	struct {
		int in;
		const char *out;
	} esc[] = {
		{ '&',  "&amp;"  },
		{ '\"', "&quot;" },
		{ '<',  "&#x3C;" },
		{ '>',  "&#x3E;" },

		{ '\\', "\\\\"   },
		{ '\f', "\\f"    },
		{ '\n', "\\n"    },
		{ '\r', "\\r"    },
		{ '\t', "\\t"    },
		{ '\v', "\\v"    },

		{ '|',  "\\|"    },
		{ '{',  "\\{"    },
		{ '}',  "\\}"    }
	};

	assert(f != NULL);

	for (i = 0; i < sizeof esc / sizeof *esc; i++) {
		if (esc[i].in == c) {
			fputs(esc[i].out, f);
			return;
		}
	}

	if (!isprint(c)) {
		fprintf(f, "\\x%x", (unsigned char) c);
		return;
	}

	putc(c, f);
}

static void
escputs(const char *s, FILE *f)
{
	const char *p;

	for (p = s; *p != '\0'; p++) {
		escputc(*p, f);
	}
}

static unsigned
node_argcount(const node *p)
{
	const node *q;
	unsigned i;

	if (p == NULL) {
		return 0;
	}

	i = 0;

	for (q = p; q != NULL; q = q->bro) {
		i++;
	}

	return i + 1;
}

static void
node_label(const node *p, const char *fmt, ...)
{
	va_list ap;
	sortname s;
	unsigned argcount;

	assert(p != NULL);

	s = p->cons->sortnum;

	argcount = node_argcount(p->son);

	IGNORE fprintf(output, "\t\t\t\"%p\" [ shape = Mrecord, ", (void *) p);

	if (s < 0) {
		/* tnc-manifested sorts */
		IGNORE fprintf(output, "style = filled, fillcolor = \"#EEEEEE\", ");
	}

	IGNORE fprintf(output, "label = \"");

	/* TODO: rankdir=TB only */
	IGNORE fprintf(output, "{");

	{
		IGNORE fprintf(output, "{");

		IGNORE fprintf(output, "%s", sort_string(s));

		if (fmt != NULL) {
			IGNORE fprintf(output, "|");

			va_start(ap, fmt);
			vfprintf(output, fmt, ap);
			va_end(ap);
		}

		IGNORE fprintf(output, "}");
	}

	if (argcount != 0) {
		unsigned int i;
		node *arg;

		IGNORE fprintf(output, "|{args:|");

		for (i = 0, arg = p->son; i < argcount - 1; i++, arg = arg->bro) {
			assert(arg != NULL);

			IGNORE fprintf(output, "<%u> ", i);

			/* fold in tnc-manifested sorts suitable for writing inline */
			if (fold_tncsorts) {
				switch (arg->cons->sortnum) {
				case SORT_option:
					fprintf(output, "%s", arg->son == NULL ? "-" : "opt");
					break;

				case SORT_tdfbool: {
					long m = arg->cons->encoding;
					fprintf(output, "%s", m ? "true" : "false");
					break;
				}

				case SORT_small_tdfint: {
					long n = arg->cons->encoding;
					fprintf(output, "%ld", n);
					break;
				}

				case SORT_tdfstring: {
					int i, n = (int) arg->cons->encoding;
					if (n == -1) {
						IGNORE fprintf(output, "%s", MAKE_STRING);
					} else {
						(void) escputc('"', output);

						for (i = 0; i < n; i++) {
							int c = ((arg->cons->name[i]) & 0xff);

							if (isprint(c)) {
								if (c == '\\' || c == '"') {
									(void) escputc('\\', output);
								}

								(void) escputc(c, output);
							} else {
								if (c == '\n') {
									(void) escputs("\\n", output);
								} else if (c == '\t') {
									(void) escputs("\\t", output);
								} else {
									unsigned co = (unsigned)c;
									(void) escputc('\\', output);
									IGNORE fprintf(output, "%03o", co);
								}
							}
						}

						(void) escputc('"', output);
					}
					break;
				}

				default:
					;
				}
			}

			if (i + 1 < argcount - 1) {
				IGNORE fprintf(output, "|");
			}
		}

		IGNORE fprintf(output, "}");
	}

	/* TODO: rankdir=TB only */
	IGNORE fprintf(output, "}");

	IGNORE fprintf(output, "\" ];\n");
}

static void
print_node(const char *prefix, void *root, const char *port, node *p)
{
	unsigned arg;

	for (arg = 0; p != NULL; p = p->bro, arg++) {
		construct *q = p->cons;
		sortname s = q->sortnum;
		long m = q->encoding;

		if (fold_tncsorts) {
			switch (s) {
			case SORT_tdfbool:
			case SORT_small_tdfint:
			case SORT_tdfstring:
				continue;

			case SORT_option:
				if (p->son == NULL) {
					continue;
				}
				break;

			default:
				break;
			}
		}

		if (port != NULL) {
			IGNORE fprintf(output, "\t\t\t\"%s%p\":%s",
				prefix, root, port);
		} else {
			IGNORE fprintf(output, "\t\t\t\"%s%p\":%u",
				prefix, root, arg);
		}

		IGNORE fprintf(output, " -> \"%p\" [ dir = none ];\n",
			(void *) p);

		switch (s) {
		case SORT_tdfbool:
			node_label(p, "%s", m ? "true" : "false");
			break;

		case SORT_bytestream:
			/* Print a bytestream */
			node_label(p, NULL);
			print_node("", p, NULL, p->son);
			break;

		case SORT_completion:
			/* Print a completion */
			node_label(p, NULL);
			print_node("", p, NULL, p->son);
			break;

		case SORT_small_tdfint:
			/* Print a small number */
			{
				long n = q->encoding;

				node_label(p, "%ld", n);
			}
			break;

		case SORT_tdfint:
			/* Print a number */
			{
				char *num = q->name;

				if (fits_ulong(num, 0)) {
					unsigned long n = octal_to_ulong(num);

					node_label(p, "%ld", n);
				} else {
					node_label(p, "0%s", num);
				}
			}
			break;

		case SORT_option:
			/* Print an optional argument */
			if (fold_tncsorts) {
				/* TODO */
			}
			{
				node_label(p, NULL);
				print_node("", p, NULL, p->son);
			}
			break;

		case SORT_repeat:
			/* Print a repeated argument */
			{
				node_label(p, "%ld", m);
				if (m != 0) {
					print_node("", p, NULL, p->son);
				}
			}
			break;

		case SORT_tdfstring:
			/* Print a string */
			{
				int n = (int) m;
				if (n == -1) {
					node_label(p, "%s", MAKE_STRING);
					print_node("", p, NULL, p->son);
				} else {
					node_label(p, "%s", "TODO");
/* TODO:
					IGNORE fprintf(output, "\t\t\"%p\" [ shape = Mrecord, label = \"{%s|",
						(void *) p, sort_string(s));

					(void) escputc('"', output);

					for (i = 0; i < n; i++) {
						int c = ((q->name[i]) & 0xff);

						if (isprint(c)) {
							if (c == '\\' || c == '"') {
								(void) escputc('\\', output);
							}

							(void) escputc(c, output);
						} else {
							if (c == '\n') {
								(void) escputs("\\n", output);
							} else if (c == '\t') {
								(void) escputs("\\t", output);
							} else {
								unsigned co = (unsigned)c;
								(void) escputc('\\', output);
								IGNORE fprintf(output, "%03o", co);
							}
						}
					}

					(void) escputc('"', output);
					IGNORE fprintf(output, "}\" ];\n");
*/
				}
			}
			break;

		case SORT_nat:
			/* Print a nat */
			if (m != ENC_make_nat) {
				goto default_label;
			}
			node_label(p, NULL);
			print_node("", p, NULL, p->son);
			break;

		case SORT_signed_nat:
			/* Print a signed_nat */
			if (m != ENC_make_signed_nat) {
				goto default_label;
			}
			node_label(p, NULL);
			print_node("", p, NULL, p->son);
			break;

		case SORT_string:
			/* Print a string */
			if (m != ENC_make_string) {
				goto default_label;
			}

			node_label(p, NULL);
			print_node("", p, NULL, p->son);
			break;

		case SORT_al_tag:
			/* Print an alignment tag */
			if (verbose || m != ENC_make_al_tag || p->son == NULL) {
				goto default_label;
			}

			node_label(p, NULL);
			print_node("", p, NULL, p->son);
			break;

		case SORT_label:
			/* Print a label */
			if (verbose || m != ENC_make_label || p->son == NULL) {
				goto default_label;
			}

			node_label(p, NULL);
			print_node("", p, NULL, p->son);
			break;

		case SORT_tag:
			/* Print a tag */
			if (verbose || m != ENC_make_tag || p->son == NULL) {
				goto default_label;
			}

			node_label(p, NULL);
			print_node("", p, NULL, p->son);
			break;

		case SORT_exp:
			{
				static node special_node;

				node_label(p, NULL);

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
				node_label(p, NULL);
				print_node("", p, NULL, p->son);
			} else {
				if (p->son) {
					node_label(p, NULL);
					print_node("", p, NULL, p->son);
				} else {
					node_label(p, "%s", q->name);
/* XXX:
					escputs(q->name, output);
*/
				}
			}
			break;
		}
	}
}

static void
print_title(char *title, construct *p, int dec)
{
	UNUSED(dec);

	if (p->ename == NULL) {
		IGNORE fprintf(output, "%s ", LOCAL_DECL);
	}

	IGNORE fprintf(output, "%s", title);
}

static void
print_name(char *title, construct *p, int dec)
{
	UNUSED(title);

	if (p->ename && p->ename->cons->encoding && dec) {
		char *f = "\n  %s (\n";
		if (p->ename->son->cons->sortnum == SORT_tdfstring) {
			if (p->ename->son->bro == NULL) {
				IGNORE fprintf(output, f, MAKE_STRING_EXTERN);
			} else {
				IGNORE fprintf(output, f, MAKE_CHAIN_EXTERN);
			}
		} else {
			IGNORE fprintf(output, f, MAKE_UNIQUE_EXTERN);
		}

		print_node("", NULL, NULL, p->ename->son);

		(void) fputs(" ),\n  ", output);

	} else {
		(void) fputc(' ', output);
	}

	IGNORE fprintf(output, "%s", p->name);
}


static void
print_aldec(construct *p)
{
	if (p->encoding == -1) {
		return;
	}

	IGNORE fprintf(output, "\t\t\"aldec_%p\" [ label=<", (void *) p);
	IGNORE fprintf(output, "<table cellborder=\"1\" cellspacing=\"0\" border=\"0\">");

	(void) fputs("<tr>", output);

	(void) fputs("<td bgcolor=\"#EEEEEE\">", output);
	print_title(MAKE_ALDEC, p, 1);
	(void) fputs("</td>", output);

	(void) fputs("<td>", output);
	print_name(MAKE_ALDEC, p, 1);
	(void) fputs("</td>", output);

	(void) fputs("</tr>", output);

	(void) fputs("</table>> ];\n", output);
}


static void
print_aldef(construct *p)
{
	al_tag_info *info = get_al_tag_info(p);

	if (p->encoding == -1) {
		return;
	}

	if (info->def == NULL) {
		return;
	}

	IGNORE fprintf(output, "\t\t\"aldef_%p\" [ label=<", (void *) p);
	IGNORE fprintf(output, "<table cellborder=\"1\" cellspacing=\"0\" border=\"0\">");

	(void) fputs("<tr>", output);

	(void) fputs("<td bgcolor=\"#EEEEEE\">", output);
	print_title(MAKE_ALDEF, p, !show_aldecs);
	(void) fputs("</td>", output);

	(void) fputs("<td>", output);
	print_name(MAKE_ALDEF, p, !show_aldecs);
	(void) fputs("</td>", output);

	(void) fputs("</tr>", output);

	(void) fputs("<tr>", output);
	(void) fputs("<td>def</td>", output);
	(void) fputs("<td port=\"def\"></td>", output);
	(void) fputs("</tr>", output);

	(void) fputs("</table>> ];\n", output);

	if (info->def != NULL) {
		fprintf(output, "\n");
		fprintf(output, "\t\tsubgraph {\n");

		print_node("aldef_", p, "def", info->def);

		fprintf(output, "\t\t}\n");
	}

}


static void
print_tagdec(construct *p)
{
	tag_info *info = get_tag_info(p);

	if (p->encoding == -1 || info->dec == NULL) {
		return;
	}

	IGNORE fprintf(output, "\t\t\"%p\" [ label=<", (void *) p);
	IGNORE fprintf(output, "<table cellborder=\"1\" cellspacing=\"0\" border=\"0\">");

	(void) fputs("<tr>", output);
	(void) fputs("<td bgcolor=\"#EEEEEE\">", output);

	switch (info->var) {
	case 0: print_title(MAKE_ID_TAGDEC,  p, 1); break;
	case 1: print_title(MAKE_VAR_TAGDEC, p, 1); break;
	case 2: print_title(COMMON_TAGDEC,   p, 1); break;
	}

	(void) fputs("</td>", output);
	(void) fputs("<td bgcolor=\"#EEEEEE\">", output);

	switch (info->var) {
	case 0: print_name(MAKE_ID_TAGDEC,  p, 1); break;
	case 1: print_name(MAKE_VAR_TAGDEC, p, 1); break;
	case 2: print_name(COMMON_TAGDEC,   p, 1); break;
	}

	(void) fputs("</td>", output);
	(void) fputs("</tr>", output);

	(void) fputs("<tr>", output);

	(void) fputs("<td>dec</td>", output);
	(void) fputs("<td port=\"dec\"></td>", output);

	(void) fputs("</tr>", output);

	(void) fputs("</table>> ];\n", output);

	if (info->dec != NULL) {
		fprintf(output, "\n");
		fprintf(output, "\t\tsubgraph {\n");

		print_node("", p, "dec", info->dec);

		fprintf(output, "\t\t}\n");
	}
}


static void
print_tagdef(construct *p)
{
	char *instr = NULL;
	tag_info *info = get_tag_info(p);
	node *d;

	if (p->encoding == -1) {
		return;
	}

	IGNORE fprintf(output, "\t\t\"tagdef_%p\" [ label=<", (void *) p);
	IGNORE fprintf(output, "<table cellborder=\"1\" cellspacing=\"0\" border=\"0\">");

	switch (info->var) {
	case 0: instr = MAKE_ID_TAGDEF;  break;
	case 1: instr = MAKE_VAR_TAGDEF; break;
	case 2: instr = COMMON_TAGDEF;   break;
	}

	/* Can have multiple definitions */
	for (d = info->def; d != NULL; d = d->bro) {
		(void) fputs("<tr>", output);
		(void) fputs("<td bgcolor=\"#EEEEEE\">", output);

		print_title(instr, p, !show_tagdecs);

		(void) fputs("</td>", output);
		(void) fputs("<td bgcolor=\"#EEEEEE\">", output);

		print_name(instr, p, !show_tagdecs);

		(void) fputs("</td>", output);
		(void) fputs("</tr>", output);

		(void) fputs("<tr>", output);

		(void) fputs("<td>def</td>", output);
		IGNORE fprintf(output, "<td port=\"def_%p\"></td>", (void *) d);

		(void) fputs("</tr>", output);
	}

	(void) fputs("</table>> ];\n", output);

	for (d = info->def; d != NULL; d = d->bro) {
		if (d->son != NULL) {
			fprintf(output, "\n");
			fprintf(output, "\t\tsubgraph {\n");

			print_node("tagdef_", p, "def", d->son);

			fprintf(output, "\t\t}\n");
		}
	}
}


static void
print_tokdec(construct *p)
{
	tok_info *info = get_tok_info(p);

	if (p->encoding == -1) {
		return;
	}

	if (!info->dec) {
		return;
	}

	IGNORE fprintf(output, "\t\t\"tokdec_%p\" [ label=<", (void *) p);
	IGNORE fprintf(output, "<table cellborder=\"1\" cellspacing=\"0\" border=\"0\">");

	(void) fputs("<tr>", output);
	(void) fputs("<td bgcolor=\"#EEEEEE\">", output);
	print_title(MAKE_TOKDEC, p, 1);
	(void) fputs("</td>", output);
	(void) fputs("<td bgcolor=\"#EEEEEE\">", output);
	print_name(MAKE_TOKDEC, p, 1);
	(void) fputs("</td>", output);
	(void) fputs("</tr>", output);

	(void) fputs("<tr>", output);
	(void) fputs("<td>sig</td>", output);
	IGNORE fprintf(output, "<td port=\"sig\">%s</td>", info->sig ? "" : "-");
	(void) fputs("</tr>", output);

	(void) fputs("<tr>", output);

	{
		char *q = info->args;
		unsigned count;

		if (q == NULL) {
			count = 1;
		} else {
			count = 0;

			while (*q) {
				sortname s;

				q = find_sortname(q, &s);
				q++;

				count++;
			}
		}

		IGNORE fprintf(output, "<td rowspan=\"%u\" valign=\"middle\">args</td>", count);

	}

	if (info->args == NULL) {
		(void) fputs("<td>-</td>", output);
	} else {
		char *q = info->args;

		while (*q) {
			sortname s;

			q = find_sortname(q, &s);
			q++;

			IGNORE fprintf(output, "<td>%s</td>", sort_name(s));

			if (*q) {
				(void) fputs("</tr>", output);
				(void) fputs("<tr>", output);
			}
		}
	}

	(void) fputs("</tr>", output);

	(void) fputs("<tr>", output);
	(void) fputs("<td>-&gt;</td>", output);
	(void) fputs("<td>", output);
	(void) fputs(sort_name(info->res), output);
	(void) fputs("</td>", output);
	(void) fputs("</tr>", output);

	(void) fputs("</table>> ];\n", output);

	if (info->sig != NULL) {
		fprintf(output, "\n");
		fprintf(output, "\t\tsubgraph {\n");

		print_node("tokdec_", p, "sig", info->sig);

		fprintf(output, "\t\t}\n");
	}
}


static void
print_tokdef(construct *p)
{
	tok_info *info = get_tok_info(p);

	if (p->encoding == -1) {
		return;
	}

	if (!info->dec) {
		return;
	}

	if (info->def == NULL) {
		return;
	}

	IGNORE fprintf(output, "\t\t\"tokdef_%p\" [ label=<", (void *) p);
	IGNORE fprintf(output, "<table cellborder=\"1\" cellspacing=\"0\" border=\"0\">");

	(void) fputs("<tr>", output);
	(void) fputs("<td bgcolor=\"#EEEEEE\">", output);
	print_title(MAKE_TOKDEF, p, !show_tagdefs);
	(void) fputs("</td>", output);
	(void) fputs("<td colspan=\"2\" bgcolor=\"#EEEEEE\">", output);
	print_name(MAKE_TOKDEF, p, !show_tagdefs);
	(void) fputs("</td>", output);
	(void) fputs("</tr>", output);

	(void) fputs("<tr>", output);
	(void) fputs("<td>sig</td>", output);
	IGNORE fprintf(output, "<td colspan=\"2\" port=\"sig\">%s</td>", info->sig ? "" : "-");
	(void) fputs("</tr>", output);

	(void) fputs("<tr>", output);

	if (info->pars) {
		construct **q = info->pars;
		unsigned count;

		if (*q == NULL) {
			count = 1;
		} else {
			for (count = 0; *q; count++)
				q++;
		}

		IGNORE fprintf(output, "<td rowspan=\"%u\" valign=\"middle\">pars</td>", count);
	} else {
		IGNORE fprintf(output, "<td rowspan=\"%u\" valign=\"middle\">pars</td>", 1);
	}

	if (info->pars == NULL) {
		(void) fputs("<td colspan=\"2\">-</td>", output);
	} else {
		construct **q = info->pars;

		while (*q) {
			tok_info *qinfo = get_tok_info(*q);

			IGNORE fprintf(output, "<td>%s</td><td>%s</td>",
				sort_name(qinfo->res), (*q)->name);
			q++;

			if (*q) {
				(void) fputs("</tr>", output);
				(void) fputs("<tr>", output);
			}
		}
	}

	(void) fputs("</tr>", output);

	(void) fputs("<tr>", output);
	(void) fputs("<td>-&gt;</td>", output);
	(void) fputs("<td colspan=\"2\">", output);
	(void) fputs(sort_name(info->res), output);
	(void) fputs("</td>", output);
	(void) fputs("</tr>", output);

	(void) fputs("<tr>", output);
	(void) fputs("<td>def</td>", output);
	(void) fputs("<td colspan=\"2\" port=\"def\"></td>", output);
	(void) fputs("</tr>", output);

	(void) fputs("</table>> ];\n", output);

	if (info->sig != NULL) {
		fprintf(output, "\n");
		fprintf(output, "\t\tsubgraph {\n");

		print_node("tokdef_", p, "sig", info->sig);

		fprintf(output, "\t\t}\n");
	}

	if (info->def != NULL) {
		fprintf(output, "\n");
		fprintf(output, "\t\tsubgraph {\n");

		print_node("tokdef_", p, "def", info->def);

		fprintf(output, "\t\t}\n");
	}
}


static void
print_high_sort(high_sort *h)
{
	int i, n;

	if (h->id == SORT_unknown) {
		return;
	}

	IGNORE fprintf(output, "%s ( %s, ", MAKE_SORT, h->name);

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

			if (i < n - 1) {
				(void) fputc(',', output);
			}

			(void) fputc(' ', output);
		}

		(void) fputs(") ", output);

		(void) fputs("-> ", output);
	}

	(void) fputs(sort_name(h->res), output);
	(void) fputs(" ) ;\n\n", output);
}

void
dot_capsule(void)
{
	(void) fputs("digraph G {\n", output);
	(void) fputs("\tnode [ shape = plaintext ];\n", output);

	if (high_sorts) {
		int i;

		(void) fputc('\n', output);
		(void) fputs("\tsubgraph cluster_highsorts {\n", output);
		(void) fputs("\t\tlabel = \"High-level SORTs\";\n", output);

		for (i = 0; i < crt_high_sort; i++)
			UNUSED(print_high_sort);
/* TODO:
			print_high_sort(high_sorts + i);
*/

		(void) fputs("\t}\n", output);
	}

	if (show_tokdecs) {
		(void) fputc('\n', output);
		(void) fputs("\tsubgraph cluster_tokdecs {\n", output);
		(void) fputs("\t\tlabel = \"Token Declarations\";\n", output);

		apply_to_all(print_tokdec, SORT_token);

		(void) fputs("\t}\n", output);
	}

	if (show_aldecs) {
		(void) fputc('\n', output);
		(void) fputs("\tsubgraph cluster_aldecs {\n", output);
		(void) fputs("\t\tlabel = \"Alignment Tag Declarations\";\n", output);

		apply_to_all(print_aldec, SORT_al_tag);

		(void) fputs("\t}\n", output);
	}

	if (show_tagdecs) {
		(void) fputc('\n', output);
		(void) fputs("\tsubgraph cluster_tagdecs {\n", output);
		(void) fputs("\t\tlabel = \"Tag Declarations\";\n", output);

		apply_to_all(print_tagdec, SORT_tag);

		(void) fputs("\t}\n", output);
	}

	if (show_tokdefs) {
		(void) fputc('\n', output);
		(void) fputs("\tsubgraph cluster_tokdefs {\n", output);
		(void) fputs("\t\tlabel = \"Token Definitions\";\n", output);

		apply_to_all(print_tokdef, SORT_token);

		(void) fputs("\t}\n", output);
	}

	if (show_aldefs) {
		(void) fputc('\n', output);
		(void) fputs("\tsubgraph cluster_aldefs {\n", output);
		(void) fputs("\t\tlabel = \"Alignment Tag Definitions\";\n", output);

		apply_to_all(print_aldef, SORT_al_tag);

		(void) fputs("\t}\n", output);
	}

	if (show_tagdefs) {
		(void) fputc('\n', output);
		(void) fputs("\tsubgraph cluster_tagdefs {\n", output);
		(void) fputs("\t\tlabel = \"Tag Definitions\";\n", output);

		apply_to_all(print_tagdef, SORT_tag);

		(void) fputs("\t}\n", output);
	}

	(void) fputs("}\n", output);
}

