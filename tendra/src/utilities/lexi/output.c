/*
 * Copyright (c) 2002, 2003, The Tendra Project <http://www.ten15.org/>
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
#include "char.h"
#include "msgcat.h"
#include "lex.h"
#include "output.h"
#include "tenapp.h"


/*
 *    OUTPUT FILE
 *
 *    This variable gives the main output file.  out is used within this file
 *    as a shorthand for lex_output.
 */

OStreamP lex_output;
#define out lex_output


/*
 *    OUTPUT INDENTATION
 *
 *    This routine outputs an indentation of d.
 */

static void
output_indent(int d)
{
    int n = 4 * d;
    for (; n >= 8 ; n -= 8) write_tab(out);
    for (; n ; n--) write_char(out, ' ');
    return;
}


/*
 *    FIND A CHARACTER LITERAL
 *
 *    This routine finds the character literal corresponding to c.
 */

static char*
char_lit(letter c)
{
    static char buff [10];
    switch (c) {
	case '\n':
		return ("'\\n'");
	case '\r':
		return ("'\\r'");
	case '\t':
		return ("'\\t'");
	case '\v':
		return ("'\\v'");
	case '\f':
		return ("'\\f'");
	case '\\':
		return ("'\\\\'");
	case '\'':
		return ("'\\''");
    }
    if (c == EOF_LETTER) return ("LEX_EOF");
    if (c > 127) return ("'?'");
    (void)sprintf(buff, "'%c'", (char) c);
    return (buff);
}


/*
 *    OUTPUT OPTIONS
 *
 *    The flag in_pre_pass is used to indicate the preliminary pass to
 *    output_pass.  read_name gives the name of the character reading
 *    function used in the output routines.
 */

static int in_pre_pass = 0;
static char *read_name = "read_char";


/*
 *    OUTPUT PASS INFORMATION
 *
 *    This routine outputs code for the lexical pass indicated by p.  n
 *    gives the depth of recursion and d gives the indentation.
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
    for (q = p->next ; q != NULL ; q = q->opt) {
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
		if (classes || w1) {
			output_indent (d);
			write_fmt(out, "lookup_type t%d;\n", n);
		}
		output_indent (d);
		write_fmt(out, "int c%d = %s ();\n", n, read_name);
		if (w1) {
			output_indent (d);
			write_cstring(out, "t0 = lookup_char (c0);\n");
			output_indent (d);
			write_cstring(out, "if (is_white (t0)) goto start;\n");
		}
		if (w2) {
			output_indent (d);
			write_cstring(out, "restart : {\n");
			d++;
		}

		if (cases > 4) {
			/* Small number of cases */
			output_indent (d);
			write_fmt(out, "switch (c%d) {\n", n);
			for (q = p->next ; q != NULL ; q = q->opt) {
				letter c = q->ch;
				if (c != LAST_LETTER && c <= SIMPLE_LETTER) {
					output_indent (d + 1);
					write_fmt(out, "case %s : {\n", char_lit (c));
					if (output_pass (q, n + 1, d + 2) == 0) {
						output_indent (d + 2);
						write_cstring(out, "break;\n");
					}
					output_indent (d + 1);
					write_cstring(out, "}\n");
				}
			}
			output_indent (d);
			write_cstring(out, "}\n");
		} else {
			/* Large number of cases */
			int started = 0;
			for (q = p->next ; q != NULL ; q = q->opt) {
				letter c = q->ch;
				if (c != LAST_LETTER && c <= SIMPLE_LETTER) {
					output_indent (d);
					if (started) write_cstring(out, "} else ");
					write_fmt(out, "if (c%d == %s) {\n",
							   n, char_lit (c));
					IGNORE output_pass (q, n + 1, d + 1);
					started = 1;
				}
			}
			if (started) {
				output_indent (d);
				write_cstring(out, "}\n");
			}
		}

		if (classes) {
			/* Complex cases */
			int started = 0;
			if (!w1) {
				output_indent (d);
				write_fmt(out, "t%d = lookup_char (c%d);\n", n, n);
			}
			for (q = p->next ; q != NULL ; q = q->opt) {
				letter c = q->ch;
				if (c != LAST_LETTER && c > SIMPLE_LETTER) {
					char *gnm;
					if (c == WHITE_LETTER) {
						gnm = "white";
					} else {
						int g = (int) (c - GROUP_LETTER);
						gnm = groups [g].name;
					}
					output_indent (d);
					if (started) write_cstring(out, "} else ");
					write_fmt(out, "if (is_%s (t%d)) {\n", gnm, n);
					IGNORE output_pass (q, n + 1, d + 1);
					started = 1;
				}
			}
			output_indent (d);
			write_cstring(out, "}\n");
		}
		if (w2) {
			d--;
			output_indent (d);
			write_cstring(out, "}\n");
		}
		if (n) {
			output_indent (d);
			write_fmt(out, "unread_char (c%d);\n", n);
		}
    }

    /* Deal with return */
    if (ret) {
		if (in_pre_pass) {
			int m = *ret;
			if (m) {
				char *str;
				if (m == '\\') {
					str = char_lit (find_escape (ret [1]));
					m = ret [2];
				} else {
					str = char_lit ((letter) m);
					m = ret [1];
				}
				if (m) {
					MSG_bad_mapping_string(ret);
				}
				if (cond) {
					output_indent (d);
					write_fmt(out, "if (%s) {\n", cond);
					output_indent (d + 1);
					write_fmt(out, "c0 = %s;\n", str);
					output_indent (d + 1);
					write_cstring(out, "goto restart;\n");
					output_indent (d);
					write_cstring(out, "}\n");
				} else {
					output_indent (d);
					write_fmt(out, "c0 = %s;\n", str);
					output_indent (d);
					write_cstring(out, "goto restart;\n");
				}
			} else {
				output_indent (d);
				if (cond) write_fmt(out, "if (%s) ", cond);
				write_cstring(out, "goto start;\n");
			}
		} else {
			output_indent (d);
			if (cond) write_fmt(out, "if (%s) ", cond);
			write_fmt(out, "return (%s", ret);
			if (args) {
				int i;
				write_cstring(out, " (c0");
				for (i = 1 ; i < n ; i++) write_fmt(out, ", c%d", i);
				write_cstring(out, ")");
			}
			write_cstring(out, ");\n");
		}
    }
    return ((ret && (cond == NULL)) ? 1 : 0);
}


/*
 *    OUTPUT INITIAL COMMENT
 *
 *    This routine outputs a comment stating that the file is automatically
 *    generated.
 */

static void
output_comment(void)
{
    if (first_comment) {
		/* Print copyright comment, if present */
		write_fmt(out, "%s\n\n", first_comment);
    }
    write_cstring(out, "/*\n *    AUTOMATICALLY GENERATED");
    write_fmt(out, " BY %s VERSION %s", progname, progvers);
    write_cstring(out, "\n */\n\n\n");
    return;
}


/*
 *    MAIN OUTPUT ROUTINE
 *
 *    This routine is the entry point for the main output routine.
 */

static void
output_main(unsigned opts)
{
    int c, n;
    int no;

    CONST char *hex;
    CONST char *type;

    /* Character look-up table */
    if (no_groups >= 16) {
		type = "unsigned long";
		hex = "0x%08lxUL";
		no = 2;
    } else if (no_groups >= 8) {
		type = "unsigned short";
		hex = "ox%04lx";
		no = 4;
    } else {
		type = "unsigned char";
		hex = "0x%02lx";
		no = 8;
    }
    if (opts & OUTPUT_MACROS) {
		write_cstring(out, "/* LOOKUP TABLE */\n\n");
		write_fmt(out, "typedef %s lookup_type;\n", type);
		if (opts & OUTPUT_TABLE) {
			write_fmt(out, "\nstatic ");
		} else {
			write_fmt(out, "extern lookup_type lookup_tab [];\n\n");
		}
    }
    if (opts & OUTPUT_TABLE) {
		write_fmt(out, "lookup_type lookup_tab [257] = {\n");
		for (c = 0 ; c <= 256 ; c++) {
			unsigned long m = 0;
			letter a = (c == 256 ? EOF_LETTER : (letter) c);
			if (in_group (white_space, a)) m = 1;
			for (n = 0 ; n < no_groups ; n++) {
				if (in_group (groups [n].defn, a)) {
            	    m |= (unsigned long) (1 << (n + 1));
				}
			}
			if ((c % no) == 0) write_cstring(out, "    ");
			write_fmt(out, hex, m);
			if (c != 256) {
				if ((c % no) == no - 1) {
					write_cstring(out, ",\n");
				} else {
					write_cstring(out, ", ");
				}
			}
		}
		write_cstring(out, "\n};\n\n");
    }

    /* Macros for accessing table */
    if (opts & OUTPUT_MACROS) {
		write_cstring(out, "#ifndef LEX_EOF\n");
		write_cstring(out, "#define LEX_EOF\t\t\t256\n");
		write_cstring(out, "#endif\n\n");
		write_cstring(out, "#define lookup_char(C)\t");
		write_cstring(out, "(lookup_tab [ (C) ])\n");
		for (n = 0 ; n <= no_groups ; n++) {
			CONST char *gnm = "white";
			unsigned long m = (unsigned long) (1 << n);
			if (n > 0) gnm = groups [ n - 1].name;
			write_fmt(out, "#define is_%s(T)\t", gnm);
			if ((int) strlen (gnm) < 8) write_tab(out);
			write_cstring(out, "((T) & ");
			write_fmt(out, hex, m);
			write_cstring(out, ")\n");
		}
		write_cstring(out, "\n\n\n");
    }

    /* Lexical pre-pass */
    if (opts & OUTPUT_FUNCTIONS) {
		if (pre_pass->next) {
			in_pre_pass = 1;
			write_cstring(out, "/* PRE-PASS ANALYSER */\n\n");
			write_cstring(out, "static int\nread_char_aux(void)\n");
			write_cstring(out, "{\n");
			write_cstring(out, "    start : {\n");
			IGNORE output_pass (pre_pass, 0, 2);
			write_cstring(out, "\treturn (c0);\n");
			write_cstring(out, "    }\n");
			write_cstring(out, "}\n\n\n");
			read_name = "read_char_aux";
		}
    }

    /* Main pass */
    if (opts & OUTPUT_FUNCTIONS) {
		in_pre_pass = 0;
		write_cstring(out, "/* MAIN PASS ANALYSER */\n\n");
		write_cstring(out, "int\nread_token(void)\n");
		write_cstring(out, "{\n");
		write_cstring(out, "    start : {\n");
		IGNORE output_pass (main_pass, 0, 2);
		write_cstring(out, "\treturn (unknown_token (c0));\n");
		write_cstring(out, "    }\n");
		write_cstring(out, "}\n");
    }
    return;
}


/*
 *    OUTPUT CODE FOR A SINGLE KEYWORD
 *
 *    This routine outputs code for the keyword p.
 */

static void
output_word(keyword *p)
{
    write_fmt(out, "MAKE_KEYWORD (\"%s\", %s", p->name, p->defn);
    if (p->args) write_cstring(out, " ()");
    write_cstring(out, ");\n");
    p->done = 1;
    return;
}


/*
 *    KEYWORD OUTPUT ROUTINE
 *
 *    This routine outputs code to generate all keywords.
 */

static void
output_keyword(void)
{
    keyword *p, *q;
    write_cstring(out, "/* KEYWORDS */\n\n");
    for (p = keywords ; p != NULL ; p = p->next) {
		if (p->done == 0) {
			char *cond = p->cond;
			if (cond) {
				write_fmt(out, "if (%s) {\n    ", cond);
				output_word (p);
				for (q = p->next ; q != NULL ; q = q->next) {
					if (q->cond && streq (q->cond, cond)) {
						write_cstring(out, "    ");
						output_word (q);
					}
				}
				write_cstring(out, "}\n");
			} else {
				output_word (p);
				for (q = p->next ; q != NULL ; q = q->next) {
					if (q->cond == NULL) output_word (q);
				}
			}
		}
    }
    return;
}


/*
 *    MAIN OUTPUT ROUTINE
 *
 *    This routine is the entry point for the main output routine.
 */

void
output_all(unsigned opts)
{
    output_comment ();
    if (opts & OUTPUT_KEYWORDS) {
		output_keyword ();
    } else {
		output_main (opts);
    }
    return;
}
