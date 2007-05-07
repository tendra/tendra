/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
					 Crown Copyright (c) 1997

	This TenDRA(r) Computer Program is subject to Copyright
	owned by the United Kingdom Secretary of State for Defence
	acting through the Defence Evaluation and Research Agency
	(DERA).  It is made available to Recipients with a
	royalty-free licence for its use, reproduction, transfer
	to other parties and amendment for any purpose not excluding
	product development provided that any such use et cetera
	shall be deemed to be acceptance of the following conditions:-

		(1) Its Recipients shall ensure that this Notice is
		reproduced upon any copies or amended versions of it;

		(2) Any amended version of it shall be clearly marked to
		show both the nature of and the organisation responsible
		for the relevant amendment or amendments;

		(3) Its onward transfer from a recipient to another
		party shall be deemed to be that party's acceptance of
		these conditions;

		(4) DERA gives no warranty or assurance as to its
		quality or suitability for any purpose and DERA accepts
		no liability whatsoever in relation to any use to which
		it may be put.
*/

#include <stdio.h>

#include "char.h"
#include "shared/error.h"
#include "lex.h"
#include "output.h"


/*
	OUTPUT FILE

	This variable gives the main output file.  out is used within this file
	as a shorthand for lex_output.
*/

FILE *lex_output;


/*
	OUTPUT INDENTATION

	This routine outputs an indentation of d.
*/

static void
output_indent(int d)
{
	int n = 4 * d;
	for (; n >= 8; n -= 8)
		fputc('\t', lex_output);
	for (; n; n--)
		fputc(' ', lex_output);
	return;
}


/*
	FIND A CHARACTER LITERAL

	This routine finds the character literal corresponding to c.
*/

static char *
char_lit(letter c)
{
	static char buff [10];
	switch (c) {
		case '\n': return("'\\n'");
		case '\t': return("'\\t'");
		case '\v': return("'\\v'");
		case '\f': return("'\\f'");
		case '\\': return("'\\\\'");
		case '\'': return("'\\''");
	}
	if (c == EOF_LETTER) return("LEX_EOF");
	if (c > 127) return("'?'");
	sprintf(buff, "'%c'", (char)c);
	return(buff);
}


/*
	OUTPUT OPTIONS

	The flag in_pre_pass is used to indicate the preliminary pass to
	output_pass.  read_name gives the name of the character reading
	function used in the output routines.
*/

static int in_pre_pass = 0;
static char *read_name = "read_char";


/*
	OUTPUT PASS INFORMATION

	This routine outputs code for the lexical pass indicated by p.  n
	gives the depth of recursion and d gives the indentation.
*/

static int
output_pass(character *p, int n, int d)
{
	character *q;
	int cases = 0;
	int classes = 0;
	char *ret = NULL;
	char *args = NULL;
	char *cond = NULL;

	/* First pass */
	for (q = p->next; q != NULL; q = q->opt) {
		letter c = q->ch;
		if (c == LAST_LETTER) {
			ret = q->defn;
			args = q->args;
			cond = q->cond;
		} else if (c <= SIMPLE_LETTER) {
			cases++;
		} else {
			classes++;
		}
	}

	/* Deal with cases */
	if (cases || classes) {
		int w1 = (n == 0 && !in_pre_pass);
		int w2 = (n == 0 && in_pre_pass);
		output_indent(d);
		fprintf(lex_output, "int c%d = %s()", n, read_name);
		if (classes || w1)
			fprintf(lex_output, ", t%d", n);
		fputs(";\n", lex_output);
		if (w1) {
			output_indent(d);
			fputs("t0 = lookup_char(c0);\n", lex_output);
			output_indent(d);
			fputs("if (is_white(t0)) goto start;\n", lex_output);
		}
		if (w2) {
			output_indent(d);
			fputs("restart: {\n", lex_output);
			d++;
		}

		if (cases > 4) {
			/* Small number of cases */
			output_indent(d);
			fprintf(lex_output, "switch (c%d) {\n", n);
			for (q = p->next; q != NULL; q = q->opt) {
				letter c = q->ch;
				if (c != LAST_LETTER && c <= SIMPLE_LETTER) {
					output_indent(d + 1);
					fprintf(lex_output, "case %s: {\n", char_lit(c));
					if (output_pass(q, n + 1, d + 2) == 0) {
						output_indent(d + 2);
						fputs("break;\n", lex_output);
					}
					output_indent(d + 1);
					fputs("}\n", lex_output);
				}
			}
			output_indent(d);
			fputs("}\n", lex_output);
		} else {
			/* Large number of cases */
			int started = 0;
			for (q = p->next; q != NULL; q = q->opt) {
				letter c = q->ch;
				if (c != LAST_LETTER && c <= SIMPLE_LETTER) {
					output_indent(d);
					if (started)
						fputs("} else ", lex_output);
					fprintf(lex_output, "if (c%d == %s) {\n",
								n, char_lit(c));
					output_pass(q, n + 1, d + 1);
					started = 1;
				}
			}
			if (started) {
				output_indent(d);
				fputs("}\n", lex_output);
			}
		}

		if (classes) {
			/* Complex cases */
			int started = 0;
			if (!w1) {
				output_indent(d);
				fprintf(lex_output, "t%d = lookup_char(c%d);\n", n, n);
			}
			for (q = p->next; q != NULL; q = q->opt) {
				letter c = q->ch;
				if (c != LAST_LETTER && c > SIMPLE_LETTER) {
					char *gnm;
					if (c == WHITE_LETTER) {
						gnm = "white";
					} else {
						int g = (int)(c - GROUP_LETTER);
						gnm = groups [g].name;
					}
					output_indent(d);
					if (started)
						fputs("} else ", lex_output);
					fprintf(lex_output, "if (is_%s(t%d)) {\n", gnm, n);
					output_pass(q, n + 1, d + 1);
					started = 1;
				}
			}
			output_indent(d);
			fputs("}\n", lex_output);
		}
		if (w2) {
			d--;
			output_indent(d);
			fputs("}\n", lex_output);
		}
		if (n) {
			output_indent(d);
			fprintf(lex_output, "unread_char(c%d);\n", n);
		}
	}

	/* Deal with return */
	if (ret) {
		if (in_pre_pass) {
			int m = *ret;
			if (m) {
				char *str;
				if (m == '\\') {
					str = char_lit(find_escape(ret [1]));
					m = ret [2];
				} else {
					str = char_lit((letter)m);
					m = ret [1];
				}
				if (m) {
					error(ERROR_SERIOUS, "Bad mapping string, '%s'", ret);
				}
				if (cond) {
					output_indent(d);
					fprintf(lex_output, "if (%s) {\n", cond);
					output_indent(d + 1);
					fprintf(lex_output, "c0 = %s;\n", str);
					output_indent(d + 1);
					fputs("goto restart;\n", lex_output);
					output_indent(d);
					fputs("}\n", lex_output);
				} else {
					output_indent(d);
					fprintf(lex_output, "c0 = %s;\n", str);
					output_indent(d);
					fputs("goto restart;\n", lex_output);
				}
			} else {
				output_indent(d);
				if (cond)
					fprintf(lex_output, "if (%s) ", cond);
				fputs("goto start;\n", lex_output);
			}
		} else {
			output_indent(d);
			if (cond)
				fprintf(lex_output, "if (%s) ", cond);
			fprintf(lex_output, "return(%s", ret);
			if (args) {
				int i;
				fputs("(c0", lex_output);
				for (i = 1; i < n; i++)
					fprintf(lex_output, ", c%d", i);
				fputs(")", lex_output);
			}
			fputs(");\n", lex_output);
		}
	}
	return((ret && (cond == NULL))? 1 : 0);
}


/*
	OUTPUT INITIAL COMMENT

	This routine outputs a comment stating that the file is automatically
	generated.
*/

static void
output_comment(void)
{
	if (first_comment) {
		/* Print copyright comment, if present */
		fprintf(lex_output, "%s\n\n", first_comment);
	}
	fputs("/*\n *  AUTOMATICALLY GENERATED", lex_output);
	fprintf(lex_output, " BY %s VERSION %s", progname, progvers);
	fputs("\n */\n\n\n", lex_output);
	return;
}


/*
	MAIN OUTPUT ROUTINE

	This routine is the entry point for the main output routine.
*/

void
output_all(FILE *output)
{
	int c, n;

		lex_output = output;

	/* Initial comment */
	output_comment();

	/* Character look-up table */
	fputs("/* LOOKUP TABLE */\n\n", lex_output);
	fprintf(lex_output, "static unsigned %s lookup_tab[257] = {\n",
				(no_groups >= 8 ? "short" : "char"));
	for (c = 0; c <= 256; c++) {
		unsigned int m = 0;
		letter a = (c == 256 ? EOF_LETTER : (letter)c);
		if (in_group(white_space, a))
			m = 1;
		for (n = 0; n < no_groups; n++) {
			if (in_group(groups [n].defn, a)) {
				m |= (unsigned int)(1 << (n + 1));
			}
		}
		if ((c % 8) == 0)
			fputs("\t", lex_output);
		fprintf(lex_output, "0x%04x", m);
		if (c != 256) {
			if ((c % 8) == 7) {
				fputs(",\n", lex_output);
			} else {
				fputs(", ", lex_output);
			}
		}
	}
	fputs("\n};\n\n", lex_output);

	/* Macros for accessing table */
	fputs("#ifndef LEX_EOF\n", lex_output);
	fputs("#define LEX_EOF\t\t256\n", lex_output);
	fputs("#endif\n\n", lex_output);
	fputs("#define lookup_char(C)\t", lex_output);
	fputs("((int)lookup_tab[(C)])\n", lex_output);
	fputs("#define is_white(T)\t((T) & 0x0001)\n", lex_output);
	for (n = 0; n < no_groups; n++) {
		char *gnm = groups [n].name;
		unsigned int m = (unsigned int)(1 << (n + 1));
		fprintf(lex_output, "#define is_%s(T)\t", gnm);
		/*if ((int)strlen(gnm) < 8)fputc('\t', lex_output);*/
		fprintf(lex_output, "((T) & 0x%04x)\n", m);
	}
	fputs("\n\n", lex_output);

	/* Lexical pre-pass */
	if (pre_pass->next) {
		in_pre_pass = 1;
		fputs( "/* PRE-PASS ANALYSER */\n\n", lex_output);
		fputs("static int read_char_aux(void)\n", lex_output);
		fputs("{\n", lex_output);
		fputs("\tstart: {\n", lex_output);
		output_pass(pre_pass, 0, 2);
		fputs("\treturn(c0);\n", lex_output);
		fputs("\t}\n", lex_output);
		fputs("}\n\n\n", lex_output);
		read_name = "read_char_aux";
	}

	/* Main pass */
	in_pre_pass = 0;
	fputs("/* MAIN PASS ANALYSER */\n\n", lex_output);
	fputs("int\nread_token(void)\n", lex_output);
	fputs("{\n", lex_output);
	fputs("\tstart: {\n", lex_output);
	output_pass(main_pass, 0, 2);
	fputs("\treturn(unknown_token(c0));\n", lex_output);
	fputs("\t}\n", lex_output);
	fputs("}\n", lex_output);
	return;
}


/*
	OUTPUT CODE FOR A SINGLE KEYWORD

	This routine outputs code for the keyword p.
*/

static void
output_word(keyword *p)
{
	fprintf(lex_output, "MAKE_KEYWORD(\"%s\", %s", p->name, p->defn);
	if (p->args)
		fputs("()", lex_output);
	fputs(");\n", lex_output);
	p->done = 1;
	return;
}


/*
	KEYWORD OUTPUT ROUTINE

	This routine outputs code to generate all keywords.
*/

void
output_keyword(FILE *output)
{
	keyword *p, *q;

		lex_output = output;

	output_comment();
	fputs("/* KEYWORDS */\n\n", lex_output);
	for (p = keywords; p != NULL; p = p->next) {
		if (p->done == 0) {
			char *cond = p->cond;
			if (cond) {
				fprintf(lex_output, "if (%s) {\n\t", cond);
				output_word(p);
				for (q = p->next; q != NULL; q = q->next) {
					if (q->cond && !strcmp(q->cond, cond)) {
						fputs("\t", lex_output);
						output_word(q);
					}
				}
				fputs("}\n", lex_output);
			} else {
				output_word(p);
				for (q = p->next; q != NULL; q = q->next) {
					if (q->cond == NULL)
						output_word(q);
				}
			}
		}
	}
	return;
}
