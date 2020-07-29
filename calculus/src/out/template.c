/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdio.h>

#include <shared/error.h>
#include <shared/xalloc.h>
#include <shared/string.h>

#include "calculus.h"
#include "cmd_ops.h"
#include "common.h"
#include "output.h"

#include <out/template.h>

/*
 * GET A COMMAND FROM A STRING
 *
 * This routine returns the address of the first non-white space character
 * from the string ps.  It returns the null pointer if the end of the line
 * is reached.
 */
static char *
get_command(char **ps)
{
	char *t = *ps;
	char *s = t;

	if (s) {
		char c;

		while (c = *s, (c == ' ' || c == '\t' || c == '\r')) {
			*s = 0;
			s++;
		}

		if (c == '#' || c == '\n' || c == 0) {
			*s = 0;
			*ps = NULL;
			return NULL;
		}

		t = s;
		while (c = *s, !(c == ' ' || c == '\t' || c == '\r' ||
		                 c == '\n' || c == 0)) {
			s++;
		}

		*ps = s;
	}

	return t;
}

/*
 * READ A TEMPLATE FILE
 *
 * This routine reads a template file from the file f.
 */
static COMMAND
read_template(FILE *f, COMMAND p)
{
	int go = 1;
	char buff[1000];
	int ln1 = crt_line_no;
	LIST(COMMAND)q = NULL_list(COMMAND);

	do {
		COMMAND r = NULL_cmd;
		int ln2 = crt_line_no;
		char *s = fgets(buff, 1000, f);

		if (s == NULL) {
			/* End of file */
			if (IS_cmd_cond(p)) {
				error(ERR_SERIOUS, "End of '@if' expected");
			} else if (IS_cmd_loop(p)) {
				error(ERR_SERIOUS, "End of '@loop' expected");
			}
			break;
		}

		s = xstrdup(s);
		if (s[0] == '@') {
			/* Complex command */
			char *s1, *s2, *s3;
			s++;
			s1 = get_command(&s);
			if (s1 == NULL) {
				s1 = "<empty>";
			}
			s2 = get_command(&s);
			s3 = get_command(&s);
			if (streq(s1, "if")) {
				if (s2 == NULL) {
					error(ERR_SERIOUS, "Incomplete '@%s' command", s1);
					s2 = "true";
				}
				MAKE_cmd_cond(ln2, s2, NULL_cmd, NULL_cmd, r);
			} else if (streq(s1, "else")) {
				if (IS_cmd_cond(p)) {
					COMMAND v = DEREF_cmd(cmd_cond_true_code(p));
					if (!IS_NULL_cmd(v)) {
						error(ERR_SERIOUS, "Duplicate '@%s' command", s1);
					}
					q = REVERSE_list(q);
					MAKE_cmd_compound(ln1, q, v);
					COPY_cmd(cmd_cond_true_code(p), v);
					q = NULL_list(COMMAND);
					ln1 = ln2;
				} else {
					error(ERR_SERIOUS, "Misplaced '@%s' command", s1);
				}
				s3 = s2;
			} else if (streq(s1, "endif")) {
				if (IS_cmd_cond(p)) {
					go = 0;
				} else {
					error(ERR_SERIOUS, "Misplaced '@%s' command", s1);
				}
				s3 = s2;
			} else if (streq(s1, "loop")) {
				if (s2 == NULL) {
					error(ERR_SERIOUS, "Incomplete '@%s' command", s1);
					s2 = "false";
				}
				MAKE_cmd_loop(ln2, s2, NULL_cmd, r);
			} else if (streq(s1, "end")) {
				if (IS_cmd_loop(p)) {
					go = 0;
				} else {
					error(ERR_SERIOUS, "Misplaced '@%s' command", s1);
				}
				s3 = s2;
			} else if (streq(s1, "comment")) {
				s3 = NULL;
			} else {
				error(ERR_SERIOUS, "Unknown command, '@%s'", s1);
				s3 = NULL;
			}

			if (s3) {
				error(ERR_SERIOUS, "End of '@%s' expected", s1);
			}

			crt_line_no = ln2 + 1;
			if (!IS_NULL_cmd(r)) {
				/* Read body of command */
				COMMAND u = read_template(f, r);
				if (IS_cmd_cond(r)) {
					COMMAND v = DEREF_cmd(cmd_cond_true_code(r));
					if (IS_NULL_cmd(v)) {
						COPY_cmd(cmd_cond_true_code(r), u);
					} else {
						COPY_cmd(cmd_cond_false_code(r), u);
					}
				} else if (IS_cmd_loop(r)) {
					COPY_cmd(cmd_loop_body(r), u);
				}
				CONS_cmd(r, q, q);
			}
		} else {
			/* Simple command */
			MAKE_cmd_simple(ln2, s, r);
			CONS_cmd(r, q, q);
			crt_line_no = ln2 + 1;
		}
	} while (go);

	q = REVERSE_list(q);
	MAKE_cmd_compound(ln1, q, p);

	return p;
}

/*
 * TOKEN CONDITION
 *
 * This variable gives the value of the token condition.
 */
int token_cond = 0;

/*
 * EVALUATE A CONDITION
 *
 * This routine evaluates the condition s.
 */
static int
eval_cond(char *s)
{
	if (s[0] == '!') {
		/* Negate condition */
		return !eval_cond(s + 1);
	}

	if (streq(s, "comp.complex")) {
		/* Complex component type */
		if (HAVE_COMPONENT) {
			TYPE_P_P pt = cmp_type(CRT_COMPONENT);
			TYPE_P t = DEREF_ptr(pt);
			return is_complex_type(t);
		}
		return 0;
	}

	if (streq(s, "comp.default")) {
		/* Component default value */
		if (HAVE_COMPONENT) {
			string_P pv = cmp_name(CRT_COMPONENT);
			string v = DEREF_string(pv);
			if (v) {
				return 1;
			}
		}
		return 0;
	}

	if (streq(s, "token")) {
		return token_cond;
	}

	if (streq(s, "true")) {
		return 1;
	}

	if (streq(s, "false")) {
		return 0;
	}

	error(ERR_SERIOUS, "Unknown condition, '%s'", s);
	return 0;
}

/*
 * WRITE A TEMPLATE FILE
 *
 * This routine writes the template file given by the commands cmd.
 */
static void
write_template(COMMAND cmd)
{
	if (IS_NULL_cmd(cmd)) {
		return;
	}

	crt_line_no = DEREF_int(cmd_line(cmd));
	switch (TAG_cmd(cmd)) {
	case cmd_simple_tag: {
		string s = DEREF_string(cmd_simple_text(cmd));
		output(s);
		break;
	}

	case cmd_compound_tag: {
		LIST(COMMAND)p;
		p = DEREF_list(cmd_compound_seq(cmd));
		while (!IS_NULL_list(p)) {
			COMMAND a = DEREF_cmd(HEAD_list(p));
			write_template(a);
			p = TAIL_list(p);
		}
		break;
	}

	case cmd_loop_tag: {
		string s = DEREF_string(cmd_loop_control(cmd));
		COMMAND a = DEREF_cmd(cmd_loop_body(cmd));
		if (streq(s, "enum")) {
			LOOP_ENUM write_template(a);
		} else if (streq(s, "enum.const")) {
			if (HAVE_ENUM) {
				LOOP_ENUM_CONST write_template(a);
			}
		} else if (streq(s, "identity")) {
			LOOP_IDENTITY write_template(a);
		} else if (streq(s, "primitive")) {
			LOOP_PRIMITIVE write_template(a);
		} else if (streq(s, "struct")) {
			LOOP_STRUCTURE write_template(a);
		} else if (streq(s, "struct.comp")) {
			if (HAVE_STRUCTURE) {
				LOOP_STRUCTURE_COMPONENT write_template(a);
			}
		} else if (streq(s, "union")) {
			LOOP_UNION write_template(a);
		} else if (streq(s, "union.comp")) {
			if (HAVE_UNION) {
				LOOP_UNION_COMPONENT write_template(a);
			}
		} else if (streq(s, "union.field")) {
			if (HAVE_UNION) {
				LOOP_UNION_FIELD write_template(a);
			}
		} else if (streq(s, "union.field.comp")) {
			if (HAVE_UNION && HAVE_FIELD) {
				LOOP_FIELD_COMPONENT write_template(a);
			}
		} else if (streq(s, "union.map")) {
			if (HAVE_UNION) {
				LOOP_UNION_MAP write_template(a);
			}
		} else if (streq(s, "union.map.arg")) {
			if (HAVE_UNION && HAVE_MAP) {
				LOOP_MAP_ARGUMENT write_template(a);
			}
		} else {
			error(ERR_SERIOUS, "Unknown control, '%s'", s);
		}
		break;
	}

	case cmd_cond_tag: {
		string s = DEREF_string(cmd_cond_control(cmd));
		COMMAND a = DEREF_cmd(cmd_cond_true_code(cmd));
		COMMAND b = DEREF_cmd(cmd_cond_false_code(cmd));
		if (eval_cond(s)) {
			write_template(a);
		} else {
			write_template(b);
		}
		break;
	}
	}
}

/*
 * PROCESS A TEMPLATE FILE
 *
 * This routine processes the template file in to the output file out.
 */
void
template_file(char *in, char *out)
{
	COMMAND cmd;
	FILE *input_file;
	crt_line_no = 1;
	crt_file_name = in;
	input_file = fopen(in, "r");

	if (input_file == NULL) {
		error(ERR_SERIOUS, "Can't open template file, '%s'", in);
		return;
	}

	MAKE_cmd_simple(1, "<dummy>", cmd);
	cmd = read_template(input_file, cmd);
	fclose(input_file);

	if (streq(out, ".")) {
		output_file = stdout;
	} else {
		output_file = fopen(out, "w");
		if (output_file == NULL) {
			error(ERR_SERIOUS, "Can't open output file, '%s'", out);
			return;
		}
	}

	have_varargs = 0;
	write_template(cmd);
	have_varargs = 1;
	flush_output();
	if (output_file != stdout) {
		fclose(output_file);
	}
}

