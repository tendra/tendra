/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <tdf/bitstream.h>

#include <utility/config.h>
#include "c_types.h"
#include <utility/option.h>

#include <parse/preproc.h>

#include <utility/ustring.h>
#include <utility/system.h>
#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/buffer.h>
#include <utility/print.h>
#include <utility/xalloc.h>

#include <syntax/syntax.h>

#include <parse/char.h>
#include <parse/constant.h>
#include <parse/file.h>
#include <parse/hash.h>
#include <parse/lex.h>
#include <parse/literal.h>
#include <parse/macro.h>
#include <parse/parse.h>
#include <parse/pragma.h>
#include <parse/predict.h>
#include <parse/preproc.h>
#include <parse/symbols.h>

#include <construct/convert.h>
#include <construct/identifier.h>
#include <construct/namespace.h>
#include <construct/statement.h>
#include <construct/tokdef.h>
#include <construct/token.h>
#include <construct/link.h>

#include <output/compile.h>
#include <output/dump.h>

#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "loc_ext.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "str_ops.h"
#include "tok_ops.h"
#include "type_ops.h"


/*
    The following functions, which are concerned with processing assertions,
    are used in read_if_exp before they are defined.
*/

static int eq_pptok(PPTOKEN *, PPTOKEN *);
static PPTOKEN *skip_predicate(PPTOKEN **, int);
static int check_assert(HASHID, PPTOKEN *, int);


/*
    The flag in_preproc_dir is set to true in a preprocessing directive.
    The flag preproc_only causes only the preprocessor to be run.  Finally
    preproc_loc records the position of the start of each preprocessing
    directive.
*/

int in_preproc_dir = 0;
int no_preproc_dir = 0;
int in_pragma_dir = 0;
int in_hash_if_exp = 0;
int pragma_number = 0;
int preproc_only = 0;
int preproc_space = 0;
LOCATION preproc_loc = NULL_loc;


/*
    This routine negates the conditional cond.  Note that skipped and
    unresolved conditions negate to themselves.
*/

static unsigned
negate_cond(unsigned cond)
{
	if (cond == PP_TRUE) {
		return PP_FALSE;
	}
	if (cond == PP_FALSE) {
		return PP_TRUE;
	}
	if (cond == PP_PAST) {
		return PP_FALSE;
	}
	return cond;
}


/*
    The stack preproc_stack gives all the active conditional compilation
    states.  In addition loc_stack records the corresponding file locations.
    preproc_depth gives the depth of conditional compilation within the
    current file.
*/

static STACK(unsigned)preproc_stack = NULL_stack(unsigned);
static STACK(LOCATION)loc_stack = NULL_stack(LOCATION);
static unsigned preproc_depth = 0;


/*
    This routine sets up the conditional compilation stack at the start
    of a source file by pushing an end marker.
*/

void
start_preproc_if(void)
{
	PUSH_unsigned(preproc_depth, preproc_stack);
	PUSH_unsigned(PP_END, preproc_stack);
	PUSH_loc(crt_loc, loc_stack);
	preproc_depth = 0;
	return;
}


/*
    This routine is called at the end of each source file to check for
    any unmatched '#if', '#elif' or '#else' directives.  It clears the
    conditional compilation stack down as far as the end marker set up
    by the previous routine.  It is possible for the routine to be
    called more than once for the main source file, hence the necessity
    to check that the stack is not empty.  The routine returns true if
    no unmatched directives are found.
*/

int
clear_preproc_if(void)
{
	int ok = 1;
	while (!IS_NULL_stack(preproc_stack)) {
		int dir;
		LOCATION loc;
		unsigned cond;
		POP_unsigned(cond, preproc_stack);
		POP_loc(loc, loc_stack);
		if (cond == PP_END) {
			/* Restore stored preprocessing depth */
			POP_unsigned(preproc_depth, preproc_stack);
			break;
		}
		if (cond & PP_HAVE_ELSE) {
			dir = lex_else;
		} else if (cond & PP_HAVE_ELIF) {
			dir = lex_elif;
		} else {
			dir = lex_if;
		}
		report(loc, ERR_cpp_cond_if_match(dir, lex_endif));
		decr_value(OPT_VAL_hash_if_depth);
		preproc_depth--;
		ok = 0;
	}
	return ok;
}


/*
    If check_macro finds a macro-like token then the corresponding identifier
    is stored in this variable.
*/

IDENTIFIER token_macro = NULL_id;


/*
    This routine checks whether the hash table entry macro represents a
    valid macro.  It returns PP_TRUE if macro is already defined and
    PP_FALSE otherwise.  It also reports on ISO keywords and other invalid
    macro identifiers.  If used is true then the macro is marked as having
    been used.
*/

unsigned
check_macro(HASHID macro, int used)
{
	/* Check for simple macros */
	DECL_SPEC ds;
	IDENTIFIER id;
	if (IS_NULL_hashid(macro)) {
		/* Special case for protection macros */
		return PP_TRUE;
	}
	id = DEREF_id(hashid_id(macro));
	switch (TAG_id(id)) {
	case id_obj_macro_tag:
	case id_func_macro_tag:
		if (used) {
			ds = DEREF_dspec(id_storage(id));
			ds |= dspec_used;
			COPY_dspec(id_storage(id), ds);
			if (do_macro && do_usage) {
				dump_use(id, &preproc_loc, 1);
			}
		}
		return PP_TRUE;
	case id_iso_keyword_tag:
		if (used) {
			report(preproc_loc, ERR_lex_key_iso(macro));
		}
		break;
	}

	/* Check for tokenised values */
	if (preproc_only) {
		id = underlying_id(id);
		ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_token) {
			/* May be a token */
			token_macro = id;
			return PP_TOKEN | PP_UNRESOLVED;
		}

	} else {
		id = find_id(macro);
		while (!IS_NULL_id(id)) {
			IDENTIFIER tid = find_token(id);
			if (IS_id_token(tid)) {
				IDENTIFIER sid = DEREF_id(id_token_alt(tid));
				ds = DEREF_dspec(id_storage(sid));
				if ((ds & dspec_token) &&
				    !(ds & dspec_template)) {
					TOKEN tok =
					    DEREF_tok(id_token_sort(tid));
					switch (TAG_tok(tok)) {
					case tok_exp_tag:
					case tok_stmt_tag:
					case tok_nat_tag:
					case tok_snat_tag:
					case tok_func_tag:
					case tok_proc_tag:
						/* These are in the macro
						 * namespace */
						if (used) {
							use_id(id, 0);
						}
						token_macro = id;
						ds = DEREF_dspec(id_storage(tid));
						if (ds & (dspec_pure |
							  dspec_defn)) {
							return PP_TOKEN | PP_TRUE;
						}
						return PP_TOKEN | PP_FALSE;
					}
				}
			}
			if (!IS_id_function_etc(id)) {
				break;
			}
			id = DEREF_id(id_function_etc_over(id));
		}
	}
	return PP_FALSE;
}


/*
    Any target dependent conditional compilation expressions encountered
    are stored in this variable.
*/

EXP crt_hash_if_exp = NULL_exp;


/*
    This routine is used to patch the preprocessing directive given by
    the preprocessing tokens p into the main preprocessor output.  It is
    used to preserve target dependent conditionals and other directives
    which need to be passed through to the output.
*/

void
patch_preproc_dir(PPTOKEN *p)
{
	if (p) {
		PPTOKEN *q = p;
		while (q->next && q->next->tok != lex_newline) {
			q = q->next;
		}
		free_tok_list(q->next);
		q->next = crt_token->next;
		crt_token->next = p;
		p->pp_space = WHITE_SPACE;
	}
	return;
}


/*
    This routine reads the constant expression following a '#if' or '#elif'
    preprocessing directive.  It returns a value indicating whether the
    expression is zero or nonzero.  The argument act is false to indicate
    that the directive is being skipped.  The expression consists of all
    the preprocessing tokens in the rest of the directive with any
    defined operations suitably expanded.  This is then macro expanded
    and finally has any remaining identifiers replaced by 0.  All the
    parsing is done using this list of tokens - no other tokens are read
    from the input file (the newline appended by read_line ensures that
    the parser doesn't spill off the end).
*/

static unsigned
read_if_exp(int act, int dir)
{
	EXP e = NULL_exp;
	unsigned cond = PP_SKIP;
	if (act) {
		/* Read the rest of the line */
		PARSE_STATE ps;
		HASHID def = KEYWORD(lex_defined);
		PPTOKEN *p = read_line(lex_ignore_token, lex_newline);
		PPTOKEN *q = p;

		/* Scan line for defined operations and assertions */
		while (q != NULL) {
			int t = q->tok;

			if (t == lex_identifier &&
			    EQ_hashid(q->pp_data.id.hash, def)) {
				/* Deal with 'defined' */
				PPTOKEN *r = q->next;
				/* Because of final newline don't need to check
				 * r != NULL */
				t = r->tok;
				if (t == lex_identifier) {
					/* Operation of the form 'defined id' */
					HASHID macro = r->pp_data.id.hash;
					unsigned c = check_macro(macro, 1);
					c &= PP_COND_MASK;
					if (c == PP_UNRESOLVED) {
						q->tok = lex_defined;
						cond = PP_UNRESOLVED;
					} else {
						q->tok = lex_integer_Hlit;
						q->pp_data.text =
						    ustrlit(c ? "1" : "0");
						q->next = r->next;
						r->next = NULL;
						free_tok_list(r);
					}

				} else if (t == lex_open_Hround &&
					   r->next->tok == lex_identifier &&
					   r->next->next->tok ==
					   lex_close_Hround) {
					/* Operation of the form
					 * 'defined(id)' */
					HASHID macro = r->next->pp_data.id.hash;
					unsigned c = check_macro(macro, 1);
					c &= PP_COND_MASK;
					if (c == PP_UNRESOLVED) {
						q->tok = lex_defined;
						cond = PP_UNRESOLVED;
					} else {
						q->tok = lex_integer_Hlit;
						q->pp_data.text =
						    ustrlit(c ? "1" : "0");
						q->next = r->next->next->next;
						r->next->next->next = NULL;
						free_tok_list(r);
					}

				} else {
					/* Badly formed 'defined' operation */
					report(preproc_loc,
					       ERR_cpp_cond_def_id());
				}

			} else if ((t == lex_hash_H1 || t == lex_hash_H2) &&
				   q->next->tok == lex_identifier) {
				/* Deal with '#predicate' */
				const char *c = "0";
				PPTOKEN *r = q->next;
				HASHID pred = r->pp_data.id.hash;
				if (t == lex_hash_H2) {
					IGNORE get_digraph(t);
				}
				if (r->next->tok == lex_open_Hround) {
					/* Check for a particular predicate */
					PPTOKEN *s = r->next->next;
					q->next = skip_predicate(&s, dir);
					if (check_assert(pred, s, 0)) {
						c = "1";
					}
				} else {
					/* Check for any predicate */
					if (check_assert(pred, r, 1)) {
						c = "1";
					}
					q->next = r->next;
					r->next = NULL;
				}
				free_tok_list(r);
				q->tok = lex_integer_Hlit;
				q->pp_data.text = ustrlit(c);
			}
			q = q->next;
		}

		/* Macro expand the line */
		q = expand_tok_list(p);
		free_tok_list(p);
		p = q;

		/* Check for any remaining identifiers */
		while (q != NULL) {
			if (q->tok == lex_identifier) {
				HASHID nm = q->pp_data.id.hash;
				IDENTIFIER id = DEREF_id(hashid_id(nm));
				unsigned tag = TAG_id(id);
				if (tag == id_obj_macro_tag ||
				    tag == id_func_macro_tag) {
					/* Allow for unexpanded macros */
					id = DEREF_id(id_alias(id));
					tag = TAG_id(id);
				}
				if (tag == id_keyword_tag) {
					int u = (int)DEREF_ulong(id_no(id));
					if (u == lex_true || u == lex_false) {
						/* Preserve boolean literals */
						tag = id_iso_keyword_tag;
					}
				}
				if (tag == id_iso_keyword_tag) {
					/* Allow for ISO keywords */
					int u = (int)DEREF_ulong(id_no(id));
					int v = primary_form(u);
					if (v != u) {
						ERROR err =
						    ERR_lex_digraph_iso(nm, v);
						report(preproc_loc, err);
					}
					q->tok = v;
				} else {
					unsigned c = check_macro(nm, 0);
					if (c & PP_TOKEN) {
						/* Preserve token identifiers */
						c &= PP_COND_MASK;
						if (c == PP_UNRESOLVED) {
							cond = PP_UNRESOLVED;
						}
					} else {
						/* Replace other identifiers by
						 * 0 */
						ERROR err;
						if (EQ_hashid(nm, def)) {
							/* Shouldn't have
							 * defined */
							err = ERR_cpp_cond_def_replace();
							if (!IS_NULL_err(err)) {
								report(preproc_loc, err);
							}
						}
						/* QUERY: what about true and false? */
						err = ERR_cpp_cond_zero(nm);
						if (!IS_NULL_err(err)) {
							report(preproc_loc,
							       err);
						}
						q->tok = lex_integer_Hlit;
						q->pp_data.text = ustrlit("0");
					}
				}
			}
			q = q->next;
		}

		/* Parse the line for a constant expression */
		save_state(&ps, 0);
		init_parser(p);
		in_hash_if_exp++;
		crt_loc = preproc_loc;
		crt_line_changed = 1;
		ADVANCE_LEXER;
		if (cond == PP_UNRESOLVED) {
			/* Unresolved tokens when preprocessing */
			assert(preproc_only);
			/* EMPTY */
		} else {
			/* Parse condition */
			cond = PP_FALSE;
			parse_nat(&e);
			if (crt_lex_token != lex_newline &&
			    !have_syntax_error) {
				/* Should have reached the end of the line */
				ERROR err = ERR_lex_parse(crt_token);
				err = concat_error(err, ERR_cpp_end(dir));
				report(preproc_loc, err);
			}
		}
		restore_state(&ps);

		/* Check the result expression */
		if (!IS_NULL_exp(e)) {
			/* Evaluate the expression */
			ERROR err = NULL_err;
			IGNORE make_nat_exp(e, &err);
			e = convert_boolean(e, exp_paren_tag, &err);
			if (!IS_NULL_err(err)) {
				err = concat_error(err,
						   ERR_cpp_cond_if_const(dir));
				report(preproc_loc, err);
				cond = PP_FALSE;
			} else {
				unsigned b = eval_const_cond(e);
				if (b == BOOL_TRUE) {
					cond = PP_TRUE;
				} else if (b == BOOL_FALSE) {
					cond = PP_FALSE;
				} else {
					cond = PP_UNRESOLVED;
				}
			}
		}

		/* Restore the parser */
		p = restore_parser();
		if (cond == PP_UNRESOLVED) {
			/* Save target dependent conditions */
			if (preproc_only) {
				/* Patch crt_token with tokens comprising
				 * condition */
				p = clean_tok_list(p);
				patch_preproc_dir(p);
				p = NULL;
			} else {
				/* Store condition in crt_hash_if_exp */
				report(preproc_loc, ERR_cpp_cond_if_ti(dir));
				crt_hash_if_exp = e;
			}
		}
		free_tok_list(p);
		in_hash_if_exp--;
	}
	if (in_preproc_dir) {
		IGNORE skip_to_end();
	}
	return cond;
}


/*
    This routine reads the macro identifier following a '#ifdef' or
    '#ifndef' preprocessing directive.  It returns a value indicating
    whether the macro is defined or not.  The argument act is false to
    indicate that the directive is being skipped, prev is as in
    read_preproc_dir.
*/

static unsigned
read_if_def(int act, int dir, int prev)
{
	unsigned cond;
	if (act) {
		int t = read_token();
		update_column();
		if (in_preproc_dir) {
			preproc_loc = crt_loc;
		}
		if (t == lex_identifier) {
			HASHID macro = token_hashid;
			cond = check_macro(macro, 1);
			cond &= PP_COND_MASK;
			if (prev == lex_included) {
				/* Protection macro begins '#ifndef macro' */
				protection_macro(macro, prev, dir);
			}
			if (in_preproc_dir && skip_to_end()) {
				report(preproc_loc, ERR_cpp_end(dir));
			}
		} else {
			report(preproc_loc, ERR_cpp_cond_ifdef_id(dir));
			cond = PP_FALSE;
		}
	} else {
		cond = PP_SKIP;
	}
	if (in_preproc_dir) {
		IGNORE skip_to_end();
	}
	return cond;
}


/*
    This routine deals with the various conditional compilation preprocessing
    directives.  dir gives the directive identifier and c indicates the
    associated condition.  The skipping of unused code is incorporated into
    this routine.  The routine returns lex_ignore_token for simple '#if' and
    '#elif' directives, lex_end_condition for simple '#else' and '#endif'
    directives, and one of the values lex_hash_Hif, lex_hash_Helif,
    lex_hash_Helse and lex_hash_Hendif for target dependent conditions.
*/

static int
read_if(int dir, unsigned c, int prev)
{
	unsigned cond = c;
	int ret = lex_ignore_token;

	if (dir == lex_if || dir == lex_ifdef || dir == lex_ifndef) {
		/* Deal with '#if', '#ifdef' and '#ifndef' */
		if (cond == PP_UNRESOLVED) {
			ret = lex_hash_Hif;
		}
		if (prev != lex_included && preproc_depth == 0) {
			/* Can't have second '#if' in protection macro */
			protection_macro(NULL_hashid, lex_ignore_token, dir);
		}
		PUSH_unsigned(cond, preproc_stack);
		PUSH_loc(preproc_loc, loc_stack);
		IGNORE incr_value(OPT_VAL_hash_if_depth);
		preproc_depth++;

	} else {
		/* Get current condition for other directives */
		LOCATION loc;
		unsigned crt_cond;
		POP_unsigned(cond, preproc_stack);
		decr_value(OPT_VAL_hash_if_depth);
		preproc_depth--;
		/* Don't pop location yet */
		if (cond == PP_END) {
			/* No matching '#if' */
			ERROR err = ERR_cpp_cond_if_match(dir, lex_if);
			report(preproc_loc, err);
			PUSH_unsigned(cond, preproc_stack);
			PUSH_loc(preproc_loc, loc_stack);
			IGNORE incr_value(OPT_VAL_hash_if_depth);
			preproc_depth++;
			cond = c;
		}
		crt_cond = (cond & PP_COND_MASK);
		ret = lex_end_condition;

		if (dir == lex_endif) {
			/* Deal with '#endif' */
			if (crt_cond == PP_UNRESOLVED) {
				ret = lex_hash_Hendif;
				cond = PP_TRUE;
			} else if (crt_cond == PP_SKIP) {
				cond = PP_SKIP;
			} else {
				cond = PP_TRUE;
			}
			POP_loc(loc, loc_stack);
			UNUSED(loc);

		} else if (dir == lex_else) {
			/* Deal with '#else' */
			PTR(LOCATION)ploc;
			ploc = HEAD_list(LIST_stack(loc_stack));
			if (cond & PP_HAVE_ELSE) {
				/* Duplicate '#else' directives */
				ERROR err = ERR_cpp_cond_else_dup(dir, dir,
								  ploc);
				report(preproc_loc, err);
			}
			if (crt_cond == PP_UNRESOLVED)ret = lex_hash_Helse;
			cond = (negate_cond(crt_cond) | PP_HAVE_ELSE);
			PUSH_unsigned(cond, preproc_stack);
			COPY_loc(ploc, preproc_loc);
			if (preproc_depth == 0) {
				/* Can't have '#else' in protection macro */
				protection_macro(NULL_hashid, lex_ignore_token,
						 dir);
			}
			IGNORE incr_value(OPT_VAL_hash_if_depth);
			preproc_depth++;

		} else {
			/* Deal with '#elif' (fairly tricky) */
			unsigned new_cond;
			PTR(LOCATION)ploc;
			ploc = HEAD_list(LIST_stack(loc_stack));
			if (cond & PP_HAVE_ELSE) {
				/* '#elif' after '#else' */
				ERROR err = ERR_cpp_cond_else_dup(dir, lex_else,
								  ploc);
				report(preproc_loc, err);
			}
			if (crt_cond == PP_TRUE || crt_cond == PP_PAST) {
				/* A previous '#if' or '#elif' was true */
				ret = lex_ignore_token;
				IGNORE read_if_exp(0, dir);
				c = PP_PAST;
				new_cond = (c | PP_HAVE_ELIF);
			} else if (crt_cond == PP_FALSE) {
				/* All previous '#if's and '#elif's were
				 * false */
				c = read_if_exp(1, dir);
				if (c == PP_UNRESOLVED) {
					ret = lex_hash_Hif;
				}
				new_cond = (c | PP_HAVE_ELIF);
			} else if (crt_cond == PP_UNRESOLVED) {
				/* Unresolved existing condition */
				c = read_if_exp(1, dir);
				if (c == PP_FALSE) {
					/* Overall condition is still
					 * unresolved */
					ret = lex_ignore_token;
					new_cond = (crt_cond | PP_HAVE_ELIF);
				} else if (c == PP_TRUE) {
					/* This terminates the conditional */
					ret = lex_hash_Hendif;
					new_cond = (c | PP_HAVE_ELIF);
				} else {
					/* A second unresolved condition */
					ret = lex_hash_Helif;
					new_cond = (c | PP_HAVE_ELIF);
				}
			} else {
				/* Skip this directive */
				ret = lex_ignore_token;
				c = read_if_exp(0, dir);
				new_cond = (c | PP_HAVE_ELIF);
			}
			PUSH_unsigned(new_cond, preproc_stack);
			COPY_loc(ploc, preproc_loc);
			if (preproc_depth == 0) {
				/* Can't have '#elif' in protection macro */
				protection_macro(NULL_hashid, lex_ignore_token,
						 dir);
			}
			IGNORE incr_value(OPT_VAL_hash_if_depth);
			preproc_depth++;
			cond = c;
		}
	}
	assert(!in_preproc_dir);

	/* Step over any unused code */
	cond &= PP_COND_MASK;
	if (cond == PP_FALSE || cond == PP_PAST || cond == PP_SKIP) {
		for (;;) {
			int t;
			unsigned long sp = skip_white(1);
			in_preproc_dir = 1;
			t = read_token();
			update_column();
			if (in_preproc_dir) {
				preproc_loc = crt_loc;
			}
			if (t == lex_hash_H2) {
				t = get_digraph(t);
			}
			if (t == lex_hash_H1) {
				/* Scan any nested preprocessing directives */
				int p;
				unsigned long sp2 = skip_white(0);
				update_column();
				p = read_preproc_dir(0, lex_ignore_token);
				switch (p) {
				case lex_hash_Hif:
				case lex_hash_Helif:
				case lex_hash_Helse:
				case lex_hash_Hendif:
				case lex_end_condition: {
					/* These terminate the current
					 * condition */
					if (sp & (WHITE_SPACE |
						  WHITE_ESC_NEWLINE)) {
						report(preproc_loc,
						       ERR_cpp_indent());
					}
					if (sp2 & (WHITE_SPACE |
						   WHITE_ESC_NEWLINE)) {
						report(preproc_loc,
						       ERR_cpp_indent_dir());
					}
					in_preproc_dir = 0;
					return p;
				}
				}
			} else if (t == lex_eof) {
				if (sp & (WHITE_SPACE | WHITE_ESC_NEWLINE)) {
					report(crt_loc, ERR_lex_phases_eof());
				}
				break;
			} else {
				if (in_preproc_dir)IGNORE skip_to_end();
			}
		}
	}
	in_preproc_dir = 0;
	return ret;
}


/*
    Any list of statements in a target dependent conditional are treated
    as if they comprised a compound statement.  In particular any variables
    declared within the conditional are only in scope inside that condition.
    The neatest way to do this is for the preprocessor to patch the necessary
    open and close braces into the parser input.  This is the purpose of
    this routine.
*/

int
patch_cond(int t, int dir)
{
	HASHID nm;
	PPTOKEN *p;
	IDENTIFIER id;

	/* Compilation action */
	if (!preproc_only) {
		switch (t) {
		case lex_hash_Hif:
			/* Create '#if {' */
			p = patch_tokens(1);
			p->tok = lex_open_Hbrace_H1;
			break;
		case lex_hash_Helif:
		case lex_hash_Helse:
			/* Create '} #elif {' and '} #else {' */
			p = patch_tokens(2);
			p->tok = t;
			token_parts(t, p);
			p->next->tok = lex_open_Hbrace_H1;
			t = lex_close_Hbrace_H1;
			break;
		case lex_hash_Hendif:
			/* Create '} #endif' */
			p = patch_tokens(1);
			p->tok = t;
			t = lex_close_Hbrace_H1;
			break;
		}
		return t;
	}

	/* Preprocessing action */
	id = token_macro;
	if (IS_NULL_id(id)) {
		return t;
	}
	nm = DEREF_hashid(id_name(id));
	switch (t) {

	case lex_hash_Hif:
		if (dir == lex_ifdef) {
			/* Create '#if defined x' */
			p = patch_tokens(2);
			p->tok = lex_identifier,
			    p->pp_data.id.hash = KEYWORD(lex_defined);
			p->next->tok = lex_identifier,
			    p->next->pp_data.id.hash = nm;
			p->next->pp_data.id.use = id;
		} else if (dir == lex_ifndef) {
			/* Create '#if !defined x' */
			p = patch_tokens(3);
			p->tok = lex_not_H1;
			p->next->tok = lex_identifier,
			    p->next->pp_data.id.hash = KEYWORD(lex_defined);
			p->next->pp_space = 0;
			p->next->next->tok = lex_identifier,
			    p->next->next->pp_data.id.hash = nm;
			p->next->next->pp_data.id.use = id;
		}
		break;

	case lex_hash_Hop:
		/* Create '#define x ...' or '#undef x' */
		if (dir == lex_define) {
			/* Patch in macro definition */
			PPTOKEN *q = NULL;
			unsigned tag = TAG_id(id);
			if (tag == id_obj_macro_tag) {
				q = DEREF_pptok(id_obj_macro_defn(id));
			} else if (tag == id_func_macro_tag) {
				q = DEREF_pptok(id_func_macro_defn(id));
			}
			q = expand_tok_list(q);
			q = clean_tok_list(q);
			patch_preproc_dir(q);
			if (tag == id_func_macro_tag) {
				unsigned n;
				LIST(HASHID)pars;
				pars = DEREF_list(id_func_macro_params(id));
				n = DEREF_unsigned(id_func_macro_no_params(id));
				p = patch_tokens((int)(2 * n + 2));
				p->tok = lex_open_Hround;
				p->pp_space = 0;
				p->next->tok = lex_close_Hround;
				p->next->pp_space = 0;
				while (!IS_NULL_list(pars)) {
					HASHID par =
					    DEREF_hashid(HEAD_list(pars));
					pars = TAIL_list(pars);
					p = p->next;
					p->tok = lex_identifier;
					p->pp_data.id.hash = par;
					p->pp_space = WHITE_SPACE;
					p = p->next;
					if (IS_NULL_list(pars)) {
						p->tok = lex_close_Hround;
						p->pp_space = WHITE_SPACE;
					} else {
						p->tok = lex_comma;
						p->pp_space = 0;
					}
				}
			}
		}
		p = patch_tokens(2);
		p->tok = lex_identifier;
		p->pp_data.id.hash = KEYWORD(dir);
		p->pp_space = 0;
		p->next->tok = lex_identifier,
		    p->next->pp_data.id.hash = nm;
		p->next->pp_data.id.use = id;
		break;
	}
	return t;
}


/*
    This routine processes a '#include' or similar directive.  This consists
    of just a header name or a sequence of tokens which expand to a header
    name.  If act is true then the actual inclusion is initialised.
    The name of the preprocessing directive, dir, is passed in for the
    purposes of error reporting.  The routine returns lex_included to
    indicate that control has passed to the new file.
*/

int
read_include(int act, int dir)
{
	int ret = lex_ignore_token;
	if (act) {
		string s;
		character c;
		int end = 0;
		int next = 0;
		int legal = 1;
		int import = 0;
		character quote = 0;

		/* Look ahead for start of header name */
		if (dir == lex_import) {
			import = 1;
		}
		if (dir == lex_include_Hnext) {
			next = 1;
		}
		IGNORE skip_white(0);
		if (peek_char(char_less, &legal)) {
			quote = char_greater;
		} else if (peek_char(char_quote, &legal)) {
			quote = char_quote;
		} else if (dir == lex_pragma) {
			if (peek_char(char_open_square, &legal)) {
				quote = char_close_square;
				next = 1;
			}
		}
		update_column();

		if (quote) {
			/* Read simple header name */
			int e = read_string((int)quote, 0);
			if (e != lex_eof) {
				if (in_preproc_dir) {
					end = skip_to_end();
				}
			}
			s = token_buff.start;
		} else {
			/* Expand complex header name */
			PPTOKEN *p = read_line(lex_ignore_token,
					       lex_ignore_token);
			PPTOKEN *q = expand_tok_list(p);
			IGNORE quote_tok_list(q, 0, char_quote);
			s = token_buff.start;

			/* Check first character */
			c = s[0];
			if (c == char_less) {
				quote = char_greater;
			} else if (c == char_quote) {
				quote = char_quote;
			} else if (dir == lex_pragma && c == char_open_square) {
				quote = char_close_square;
				next = 1;
			} else {
				report(preproc_loc, ERR_cpp_include_bad());
				act = 0;
			}

			/* Scan header name */
			if (quote) {
				string t = ++s;
				for (;;) {
					if (*t == quote) {
						*t = 0;
						if (t + 1 != token_buff.posn) {
							end = 1;
						}
						break;
					}
					if (t == token_buff.posn) {
						/* End of buffer reached */
						report(preproc_loc,
						       ERR_cpp_include_incompl());
						break;
					}
					t++;
				}
			}
			free_tok_list(p);
			free_tok_list(q);
		}
		if (end) {
			report(preproc_loc, ERR_cpp_end(dir));
		}
		in_preproc_dir = 0;
		if (act) {
			/* Check header name */
			string t = s;
			while (c = *(t++), c != 0) {
				if (c == char_quote ||
				    c == char_single_quote ||
				    c == char_backslash ||
				    (c == char_slash && *t == char_asterix) ||
				    (c == char_slash && *t == char_slash)) {
					report(preproc_loc,
					       ERR_cpp_include_undef(s));
					break;
				}
			}
			if (start_include(s, (int)quote, import, next)) {
				/* Control passed to new file */
				ret = lex_included;
			}
		}
	} else {
		/* Ignore rest of line */
		if (in_preproc_dir)IGNORE skip_to_end();
	}
	return ret;
}


/*
    This routine checks whether the lists of preprocessing tokens p and q
    are identical.  It returns 2 if they are equal including preceeding
    white spaces, 1 if they are otherwise equal, and 0 otherwise.
*/

static int
eq_pptok(PPTOKEN *p, PPTOKEN *q)
{
	int eq = 2;
	while (p && q) {
		int t1 = p->tok;
		int t2 = q->tok;
		if (t1 != t2) {
			return 0;
		}
		if (p->pp_space != q->pp_space) {
			eq = 1;
		}
		switch (t1) {
		case lex_identifier: {
			/* Check identifiers */
			HASHID n1 = p->pp_data.id.hash;
			HASHID n2 = q->pp_data.id.hash;
			if (!EQ_hashid(n1, n2)) {
				return 0;
			}
			break;
		}
		case lex_integer_Hlit: {
			/* Check integer and floating-point literals */
			string s1 = p->pp_data.text;
			string s2 = q->pp_data.text;
			if (!ustreq(s1, s2)) {
				return 0;
			}
			break;
		}
		case lex_char_Hlit:
		case lex_string_Hlit:
		case lex_wchar_Hlit:
		case lex_wstring_Hlit: {
			/* Check string and characters literals */
			string s1 = p->pp_data.str.start;
			string s2 = q->pp_data.str.start;
			size_t n1 = p->pp_data.str.end - s1;
			size_t n2 = q->pp_data.str.end - s2;
			if (n1 != n2) {
				return 0;
			}
			if (memcmp(s1, s2, n1) != 0) {
				return 0;
			}
			break;
		}
		case lex_unknown: {
			/* Check unknown characters */
			string s1 = p->pp_data.buff;
			string s2 = q->pp_data.buff;
			size_t n1 = MULTI_WIDTH;
			if (memcmp(s1, s2, n1) != 0) {
				return 0;
			}
			break;
		}
		case lex_macro_Harg: {
			/* Check macro parameter applications */
			unsigned long m1 = p->pp_data.par.no;
			unsigned long m2 = q->pp_data.par.no;
			if (m1 != m2) {
				return 0;
			}
			break;
		}
		}
		p = p->next;
		q = q->next;
	}
	if (p || q) {
		return 0;
	}
	return eq;
}


/*
    This routine checks that a definition of the macro given by id_new is
    consistent with the previous definition, id_old.  It returns an error
    message reporting on the level of consistency.
*/

static ERROR
check_macro_redef(IDENTIFIER id_new, IDENTIFIER id_old)
{
	int defn_ok;
	int pars_ok = 1;
	ERROR err = NULL_err;
	PTR(LOCATION)loc_old;
	PPTOKEN *defn_new, *defn_old;
	unsigned tag_new = TAG_id(id_new);
	unsigned tag_old = TAG_id(id_old);
	DECL_SPEC ds_old = DEREF_dspec(id_storage(id_old));

	/* Check on old macro definition */
	loc_old = id_loc(id_old);
	if ((ds_old & dspec_builtin) && crt_file_type == 0) {
		/* Built-in macro redefined */
		err = ERR_cpp_predef_redef(id_old);
	}

	/* Macro types must agree */
	if (tag_new != tag_old) {
		ERROR e = ERR_cpp_replace_redef_bad(id_old, loc_old);
		err = concat_error(err, e);
		return err;
	}

	if (tag_new == id_obj_macro_tag) {
		/* Find the definitions for object-like macros */
		defn_new = DEREF_pptok(id_obj_macro_defn(id_new));
		defn_old = DEREF_pptok(id_obj_macro_defn(id_old));

	} else {
		/* Check parameter lists for function-like macros */
		unsigned no_pars_new, no_pars_old;
		LIST(HASHID)pars_new, pars_old;
		pars_new = DEREF_list(id_func_macro_params(id_new));
		pars_old = DEREF_list(id_func_macro_params(id_old));
		no_pars_new = DEREF_unsigned(id_func_macro_no_params(id_new));
		no_pars_old = DEREF_unsigned(id_func_macro_no_params(id_old));

		if (no_pars_new != no_pars_old) {
			/* Number of parameters must match */
			ERROR e = ERR_cpp_replace_redef_bad(id_old, loc_old);
			err = concat_error(err, e);
			return err;
		}

		while (!IS_NULL_list(pars_new)) {
			/* Check that parameter names match */
			HASHID p_new = DEREF_hashid(HEAD_list(pars_new));
			HASHID p_old = DEREF_hashid(HEAD_list(pars_old));
			if (!EQ_hashid(p_new, p_old)) {
				/* Just clear pars_ok if they don't */
				pars_ok = 0;
				break;
			}
			pars_new = TAIL_list(pars_new);
			pars_old = TAIL_list(pars_old);
		}

		/* Find the definitions for function-like macros */
		defn_new = DEREF_pptok(id_func_macro_defn(id_new));
		defn_old = DEREF_pptok(id_func_macro_defn(id_old));
	}

	/* Check that the definitions match */
	defn_ok = eq_pptok(defn_new, defn_old);
	if (defn_ok == 0) {
		/* Inconsistent redefinition */
		ERROR e = ERR_cpp_replace_redef_bad(id_old, loc_old);
		err = concat_error(err, e);
		return err;
	} else if (defn_ok == 1) {
		/* Consistent redefinition up to white space */
		ERROR e = ERR_cpp_replace_redef_space(id_old, loc_old);
		e = set_severity(e, OPT_macro_redef, -1);
		err = concat_error(err, e);
	}

	/* Prepare final error */
	if (pars_ok) {
		/* Consistent macro redefinition */
		if (IS_NULL_err(err)) {
			err = ERR_cpp_replace_redef_ok(id_old, loc_old);
		}
	} else {
		/* Consistent redefinition up to parameter names */
		ERROR e = ERR_cpp_replace_redef_weak(id_old, loc_old);
		e = set_severity(e, OPT_macro_redef, -1);
		err = concat_error(err, e);
	}
	return err;
}


/*
    This routine frees the macro definition given by the identifier id.
    It returns the previous definition of id.
*/

static IDENTIFIER
free_macro_defn(IDENTIFIER id)
{
	PPTOKEN *defn;
	IDENTIFIER prev = DEREF_id(id_alias(id));
	if (IS_id_obj_macro(id)) {
		defn = DEREF_pptok(id_obj_macro_defn(id));
		COPY_pptok(id_obj_macro_defn(id), NULL);
	} else {
		defn = DEREF_pptok(id_func_macro_defn(id));
		COPY_pptok(id_func_macro_defn(id), NULL);
	}
	free_tok_list(defn);
	return prev;
}


/*
    This routine processes a '#define' directive.  This consists of a macro
    identifier, and optional list of macro parameters, and a list of token
    comprising the macro definition.  Note that the list of parameters is
    built up in the reverse order to that in which they appear in the file
    (also see read_macro_args).  The routine returns true if the directive
    is a macro definition.
*/

static int
read_define(void)
{
	HASHID macro;
	PPTOKEN *defn;
	int legal = 1;
	IDENTIFIER id;
	IDENTIFIER tok;
	IDENTIFIER prev;
	unsigned prev_def;
	unsigned npars = 0;
	int object_like = 0;
	int ret = lex_ignore_token;
	int first_tok = lex_ignore_token;
	LIST(HASHID)pars = NULL_list(HASHID);
	OPTION preproc_strings = option(OPT_preproc_old);

	/* Read the macro identifier */
	int t = read_token();
	update_column();
	if (in_preproc_dir) {
		preproc_loc = crt_loc;
	}
	if (t != lex_identifier) {
		report(preproc_loc, ERR_cpp_replace_id(lex_define));
		return ret;
	}
	macro = token_hashid;
	if (EQ_KEYWORD(macro, lex_defined)) {
		/* Cannot define defined as a macro */
		report(preproc_loc, ERR_cpp_predef_bad(macro, lex_define));
	} else {
		id = DEREF_id(hashid_id(macro));
		if (IS_id_keyword(id) && !preproc_only) {
			/* Warn about redefining keywords */
			report(preproc_loc, ERR_cpp_predef_keyword(macro));
		}
	}
	prev_def = check_macro(macro, 0);
	tok = token_macro;

	/* Check for macro parameters */
	if (peek_char(char_open_round, &legal)) {
		PPTOKEN *p;
		int err = 0;
		int par_next = 2;
		LIST(HASHID)lp;
		unsigned long par_no = 1;

		/* Scan through definition looking for parameters */
		update_column();
		if (in_preproc_dir) {
			preproc_loc = crt_loc;
		}
		while (t = read_token(), t != lex_close_Hround) {
			update_column();
			if (in_preproc_dir) {
				preproc_loc = crt_loc;
			}
			if (t == lex_identifier) {
				/* Identifiers are parameter names */
				unsigned long mark;
				HASHID par = token_hashid;
				IGNORE check_macro(par, 0);
				CONS_hashid(par, pars, pars);

				/* Mark name with parameter number */
				mark = DEREF_ulong(hashid_hash(par));
				if (mark >= HASH_SIZE) {
					/* Parameter already marked */
					ERROR e =
					    ERR_cpp_replace_par_dup(par, macro);
					report(preproc_loc, e);
					mark %= HASH_SIZE;
				}
				mark += HASH_SIZE * par_no;
				COPY_ulong(hashid_hash(par), mark);
				if (!par_next) {
					err = 1;
				}
				par_next = 0;
				par_no++;
			} else if (t == lex_comma) {
				/* Commas separate parameters */
				if (par_next) {
					err = 1;
				}
				par_next = 1;
			} else {
				/* Anything else is an error */
				first_tok = t;
				err = 1;
				break;
			}
		}
		update_column();
		if (in_preproc_dir) {
			preproc_loc = crt_loc;
		}
		if (err || par_next == 1) {
			/* Report any errors */
			report(preproc_loc, ERR_cpp_replace_par_bad(macro));
		}

		/* Allow for parameter expansion in strings */
		if (preproc_strings) {
			/* This causes strings not to be recognised */
			set_char_lookup(char_quote, char_illegal);
			set_char_lookup(char_single_quote, char_illegal);
		}

		/* Read the macro definition for function-like macros */
		defn = read_line(first_tok, lex_ignore_token);
		if (defn)defn->pp_space = WHITE_SPACE;

		/* Restore string terminators */
		if (preproc_strings) {
			set_char_lookup(char_quote, char_quote);
			set_char_lookup(char_single_quote, char_single_quote);
		}

		/* Mark the macro parameters in the definition */
		for (p = defn; p != NULL; p = p->next) {
			int tk = p->tok;
			if (tk == lex_identifier) {
				HASHID par = p->pp_data.id.hash;
				unsigned long mark =
				    DEREF_ulong(hashid_hash(par));
				if (mark >= HASH_SIZE) {
					/* Parameters are identified by the
					 * parameter number */
					p->tok = lex_macro_Harg;
					p->pp_data.par.hash = par;
					p->pp_data.par.no = (mark / HASH_SIZE);
				}
			}
		}

		/* Check for quoted parameters */
		if (preproc_strings) {
			defn = recognise_strings(defn, macro, 0);
		}

		/* Check for '#' operators */
		for (p = defn; p != NULL; p = p->next) {
			int tk = p->tok;
			if (tk == lex_hash_H2) {
				tk = get_digraph(tk);
			}
			if (tk == lex_hash_H1) {
				/* '#' should be followed by a parameter */
				if (p->next == NULL ||
				    p->next->tok != lex_macro_Harg) {
					report(preproc_loc,
					       ERR_cpp_stringize_par(macro));
				} else {
					p->tok = lex_hash_Hop;
				}
			}
		}

		/* Clear the parameter marks */
		for (lp = pars; !IS_NULL_list(lp); lp = TAIL_list(lp)) {
			HASHID par = DEREF_hashid(HEAD_list(lp));
			unsigned long mark = DEREF_ulong(hashid_hash(par));
			mark %= HASH_SIZE;
			COPY_ulong(hashid_hash(par), mark);
			npars++;
		}
		pars = REVERSE_list(pars);

	} else {
		/* Read the macro definition for object-like macros */
		if (!legal) {
			report(preproc_loc, ERR_cpp_space_replace());
		}
		defn = read_line(first_tok, lex_ignore_token);
		object_like = 1;
	}

	/* Check for '##' operators */
	if (defn) {
		PPTOKEN *p;
		int tk = defn->tok;
		if (tk == lex_hash_Hhash_H2) {
			tk = get_digraph(tk);
		}
		if (tk == lex_hash_Hhash_H1) {
			/* Definition can't start with '##' */
			report(preproc_loc, ERR_cpp_concat_place(macro));
		}
		for (p = defn->next; p != NULL; p = p->next) {
			tk = p->tok;
			if (tk == lex_hash_Hhash_H2) {
				tk = get_digraph(tk);
			}
			if (tk == lex_hash_Hhash_H1) {
				if (p->next == NULL) {
					/* Definition can't end with '##' */
					report(preproc_loc,
					       ERR_cpp_concat_place(macro));
				} else {
					p->tok = lex_hash_Hhash_Hop;
				}
			}
		}
	}

	/* Define the macro */
	if (!IS_NULL_exp(crt_hash_cond)) {
		report(preproc_loc, ERR_cpp_cond_if_macro(macro));
	}
	prev = DEREF_id(hashid_id(macro));
	if (object_like) {
		MAKE_id_obj_macro(macro, dspec_defn, NULL_nspace, preproc_loc,
				  defn, id);
	} else {
		IGNORE check_value(OPT_VAL_macro_pars, (ulong)npars);
		MAKE_id_func_macro(macro, dspec_defn, NULL_nspace, preproc_loc,
				   defn, pars, npars, id);
	}
	COPY_id(id_alias(id), prev);
	if (prev_def & PP_TOKEN) {
		/* Allow for token definitions */
		prev_def &= PP_COND_MASK;
		if (prev_def == PP_UNRESOLVED) {
			/* Can only happen when preprocessing */
			token_macro = id;
			ret = lex_hash_Hop;
		} else {
			int tokdef;
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			COPY_dspec(id_storage(id), (ds | dspec_temp));
			tokdef = define_token_macro(tok, id);
			COPY_dspec(id_storage(id), ds);
			if (tokdef) {
				IGNORE free_macro_defn(id);
				no_declarations++;
				return ret;
			}
			prev_def = PP_FALSE;
		}
	}
	COPY_id(hashid_id(macro), id);
	if (do_macro) {
		/* Dump macro definition using current namespace */
		COPY_nspace(id_parent(id), crt_namespace);
		dump_declare(id, &preproc_loc, 1);
		COPY_nspace(id_parent(id), NULL_nspace);
	}

	/* Check consistency of previous definition */
	if (prev_def == PP_TRUE) {
		ERROR err;
		if (option(OPT_macro_nest) == OPTION_DISALLOW) {
			err = check_macro_redef(id, prev);
			prev = free_macro_defn(prev);
		} else {
			PTR(LOCATION)loc = id_loc(prev);
			err = ERR_cpp_replace_redef_nest(prev, loc);
		}
		if (!IS_NULL_err(err)) {
			report(preproc_loc, err);
		}
		COPY_id(id_alias(id), prev);
	} else {
		IGNORE incr_value(OPT_VAL_macro_ids);
	}
	return ret;
}


/*
    This routine processes a '#undef' directive.  This just consists of a
    macro identifier.  The routine returns true if the macro represents
    a token.
*/

static int
read_undef(void)
{
	/* Read the macro identifier */
	unsigned def;
	HASHID macro;
	int ret = lex_ignore_token;
	int t = read_token();
	update_column();
	if (in_preproc_dir) {
		preproc_loc = crt_loc;
	}
	if (t != lex_identifier) {
		report(preproc_loc, ERR_cpp_scope_id(lex_undef));
		return ret;
	}
	macro = token_hashid;
	if (EQ_KEYWORD(macro, lex_defined)) {
		/* Cannot undefine defined */
		report(preproc_loc, ERR_cpp_predef_bad(macro, lex_undef));
	}

	/* Undefine the macro if necessary */
	def = check_macro(macro, 0);
	if (def == PP_TRUE) {
		/* Previously defined as macro */
		IDENTIFIER prev = DEREF_id(hashid_id(macro));
		DECL_SPEC ds = DEREF_dspec(id_storage(prev));
		if ((ds & dspec_builtin) && crt_file_type == 0) {
			report(preproc_loc, ERR_cpp_predef_undef(prev));
		}
		if (do_macro) {
			dump_undefine(prev, &preproc_loc, 1);
		}
		prev = free_macro_defn(prev);
		COPY_id(hashid_id(macro), prev);
		decr_value(OPT_VAL_macro_ids);

	} else if (def & PP_TOKEN) {
		/* Previously defined as token */
		IDENTIFIER prev = token_macro;
		def &= PP_COND_MASK;
		if (def == PP_UNRESOLVED) {
			/* Can only happen when preprocessing */
			ret = lex_hash_Hop;
		} else {
			if (IS_id_function_etc(prev)) {
				do {
					DECL_SPEC ds =
					    DEREF_dspec(id_storage(prev));
					TYPE f = DEREF_type(id_function_etc_form(prev));
					if (!IS_NULL_type(f) &&
					    IS_type_token(f)) {
						IDENTIFIER ext =
						    DEREF_id(type_token_tok(f));
						if (!IS_NULL_id(ext) &&
						    IS_id_token(ext)) {
							if (do_dump) {
								dump_undefine(prev, &preproc_loc, 1);
							}
							f = NULL_type;
							COPY_type(id_function_etc_form(prev), f);
						}
					}
					ds &= ~dspec_token;
					COPY_dspec(id_storage(prev), ds);
					prev = DEREF_id(id_function_etc_over(prev));
				} while (!IS_NULL_id(prev));
			} else {
				if (do_dump) {
					dump_undefine(prev, &preproc_loc, 1);
				}
				remove_id(prev);
			}
		}
	} else {
		/* Not previously declared */
		report(preproc_loc, ERR_cpp_scope_undef(macro));
	}

	/* Check the rest of the directive */
	if (in_preproc_dir && skip_to_end()) {
		report(preproc_loc, ERR_cpp_end(lex_undef));
	}
	return ret;
}


/*
    This routine processes a '#line' or '#file' directive (as indicated
    by dir).
*/

static void
read_location(int dir)
{
	/* Read the line */
	PPTOKEN *p = read_line(lex_ignore_token, lex_ignore_token);
	unsigned long ln = crt_loc.line;
	string fn = DEREF_string(posn_file(crt_loc.posn));
	unsigned long ln_old = ln;
	string fn_old = fn;

	/* Macro expand the line */
	PPTOKEN *q = expand_tok_list(p);
	q = clean_tok_list(q);
	if (q && q->tok == lex_integer_Hlit && dir == lex_line) {
		/* Process '#line number string-opt' */
		unsigned err = 0;
		PPTOKEN *r = q->next;
		ln = eval_line_digits(q->pp_data.text, &err);
		if (ln != ln_old) {
			crt_line_changed = 1;
		}
		if (err & 2) {
			report(preproc_loc, ERR_cpp_line_float(dir));
		}
		if ((err & 1) || (ln == 0)) {
			report(preproc_loc, ERR_cpp_line_range(dir));
		}
		if (r && r->tok == lex_string_Hlit) {
			fn = r->pp_data.str.start;
			if (!ustreq(fn, fn_old)) {
				crt_file_changed = 1;
				crt_line_changed = 1;
			}
			r = r->next;
		}
		if (r) {
			report(preproc_loc, ERR_cpp_end(dir));
		}
	} else if (q && q->tok == lex_string_Hlit && dir == lex_file) {
		/* Process '#file string' */
		PPTOKEN *r = q->next;
		fn = q->pp_data.str.start;
		if (!ustreq(fn, fn_old)) {
			crt_file_changed = 1;
			crt_line_changed = 1;
		}
		if (r) {
			report(preproc_loc, ERR_cpp_end(dir));
		}
	} else {
		report(preproc_loc, ERR_cpp_line_bad(dir));
	}
	free_tok_list(p);
	free_tok_list(q);
	if (crt_line_changed) {
		PTR(POSITION)posn = crt_loc.posn;
		string d = DEREF_string(posn_dir(posn));
		string input = DEREF_string(posn_input(posn));
		unsigned long off = DEREF_ulong(posn_offset(posn));
		unsigned long date = DEREF_ulong(posn_datestamp(posn));
		PTR(LOCATION)from = DEREF_ptr(posn_from(posn));
		off += (ln - ln_old);
		posn = MAKE_ptr(SIZE_posn);
		MAKE_posn(fn, input, fn, d, off, from, date, posn);
		crt_loc.posn = posn;
	}
	crt_loc.line = ln;
	crt_loc.column = 0;
	return;
}


/*
    This routine processes a '#error' or '#warning' directive (as indicated
    by the error severity level sev).
*/

static void
read_error(int opt)
{
	ERROR err;
	PPTOKEN *p = read_line(lex_ignore_token, lex_ignore_token);
	IGNORE quote_tok_list(p, 0, char_quote);
	err = ERR_cpp_error_msg(token_buff.start);
	if (!IS_NULL_err(err)) {
		err = set_severity(err, opt, 0);
		report(preproc_loc, err);
	}
	free_tok_list(p);
	return;
}


/*
    This routine processes a '#ident' directive.
*/

void
read_ident(int dir)
{
	int t = read_token();
	update_column();
	if (in_preproc_dir) {
		preproc_loc = crt_loc;
	}
	if (t == lex_string_Hlit) {
		string s = token_buff.start;
		unsigned long n = (unsigned long)(token_buff.posn - s);
		compile_comment(s, n);
		if (in_preproc_dir && skip_to_end()) {
			report(preproc_loc, ERR_cpp_end(dir));
		}
	} else {
		report(preproc_loc, ERR_pragma_cpp_ident(dir));
	}
	return;
}


/*
    This routine looks up the assertion named pred, creating it if it does
    not already exist.
*/

IDENTIFIER
make_assert(HASHID pred, int key)
{
	NAMESPACE ns = assert_namespace;
	MEMBER mem = search_member(ns, pred, 1);
	IDENTIFIER id = DEREF_id(member_id(mem));
	if (IS_NULL_id(id)) {
		/* Define assertion if not already defined */
		MAKE_id_predicate(pred, dspec_none, ns, preproc_loc, id);
		COPY_ulong(id_no(id), (unsigned long)key);
		COPY_id(member_id(mem), id);
	}
	return id;
}


/*
    This routine skips a predicate given by the list of preprocessing
    tokens p.  It is entered after the initial open bracket and returns
    the token after the matching close bracket.
*/

static PPTOKEN *
skip_predicate(PPTOKEN **p, int dir)
{
	PPTOKEN *q = *p;
	PPTOKEN *r = NULL;
	int bracket = 1;
	if (q) {
		q->pp_space = 0;
	}
	while (q) {
		int t = q->tok;
		if (t == lex_open_Hround) {
			/* Increase bracket count */
			bracket++;
		} else if (t == lex_close_Hround) {
			/* Decrease bracket count */
			if (--bracket == 0) {
				if (r) {
					r->next = NULL;
				} else if (dir == lex_define ||
					   dir == lex_undef) {
					*p = NULL;
				} else {
					report(preproc_loc,
					       ERR_pragma_assert_empty(dir));
					*p = NULL;
				}
				r = q->next;
				q->next = free_tokens;
				free_tokens = q;
				return r;
			}
		} else if (t == lex_newline) {
			/* Terminate if a newline is reached */
			report(preproc_loc, ERR_pragma_assert_paren(dir));
			if (r) {
				r->next = NULL;
			} else {
				report(preproc_loc,
				       ERR_pragma_assert_empty(dir));
				*p = NULL;
			}
			return q;
		}
		r = q;
		q = q->next;
	}
	report(preproc_loc, ERR_pragma_assert_paren(dir));
	return NULL;
}


/*
    This routine checks whether the value p, or any value if def is true,
    has been defined in the predicate pred.
*/

static int
check_assert(HASHID pred, PPTOKEN *p, int def)
{
	IDENTIFIER id = make_assert(pred, lex_unknown);
	int key = (int)DEREF_ulong(id_no(id));
	LIST(PPTOKEN_P)s = DEREF_list(id_predicate_values(id));
	report(preproc_loc, ERR_pragma_assert_pred(pred));
	if (def) {
		/* Check for any predicate */
		if (!IS_NULL_list(s)) {
			return 1;
		}
	} else {
		while (!IS_NULL_list(s)) {
			PPTOKEN *q = DEREF_pptok(HEAD_list(s));
			if (eq_pptok(p, q) == 2) {
				return 1;
			}
			s = TAIL_list(s);
		}
	}
	if (key == lex_include) {
		/* '#include' checks for included files */
		if (def) {
			return 1;
		}
		IGNORE quote_tok_list(p, 0, char_quote);
		return start_include(token_buff.start, char_quote, 4, 0);
	}
	if (key == lex_keyword) {
		/* '#keyword' checks for keywords */
		if (def) {
			return 1;
		}
		if (p && p->next == NULL) {
			if (p->tok == lex_identifier) {
				IDENTIFIER pid = p->pp_data.id.use;
				if (IS_id_keyword(pid)) {
					return 1;
				}
				if (IS_id_iso_keyword(pid)) {
					return 1;
				}
			}
		}
	}
	if (key == lex_option) {
		/* '#option' checks for options */
		int n;
		ulong sn;
		string sb;
		static STRING str = NULL_str;
		if (def) {
			return 1;
		}
		IGNORE quote_tok_list(p, 0, char_quote);
		sb = token_buff.start;
		sn = (ulong)(token_buff.posn - sb);
		if (IS_NULL_str(str)) {
			MAKE_str_simple(sn, sb, STRING_NONE, str);
		} else {
			COPY_string(str_simple_text(str), sb);
			COPY_ulong(str_simple_len(str), sn);
		}
		n = find_option_no(str, 0);
		if (n != -1 && option(n)) {
			return 1;
		}
	}
	return 0;
}


/*
    This routine sets the assertion value of the preprocessing tokens p
    in the predicate id to be def.
*/

static void
set_assert(IDENTIFIER id, PPTOKEN *p, int def)
{
	LIST(PPTOKEN_P)s;
	PTR(LIST(PPTOKEN_P))ps = id_predicate_values(id);
	LIST(PPTOKEN_P)r = DEREF_list(ps);
	while (s = DEREF_list(ps), !IS_NULL_list(s)) {
		PPTOKEN *q = DEREF_pptok(HEAD_list(s));
		if (eq_pptok(p, q) == 2) {
			/* Already asserted */
			if (!def) {
				DESTROY_CONS_pptok(destroy, q, s, s);
				COPY_list(ps, s);
				free_tok_list(q);
			}
			free_tok_list(p);
			return;
		}
		ps = PTR_TAIL_list(s);
	}
	if (def) {
		/* Create assertion */
		CONS_pptok(p, r, r);
		COPY_list(id_predicate_values(id), r);
	} else {
		free_tok_list(p);
	}
	return;
}


/*
    This routine processes a '#assert' directive.
*/

static void
read_assert(int dir)
{
	/* Read the predicate name */
	int def = 1;
	IDENTIFIER id;
	PPTOKEN *p, *q;
	int t = read_token();
	update_column();
	if (in_preproc_dir) {
		preproc_loc = crt_loc;
	}
	if (t != lex_identifier) {
		report(preproc_loc, ERR_pragma_assert_id(dir));
		return;
	}
	id = make_assert(token_hashid, lex_unknown);

	/* Read the predicate token sequence */
	t = read_token();
	update_column();
	if (in_preproc_dir) {
		preproc_loc = crt_loc;
	}
	if (t != lex_open_Hround) {
		report(preproc_loc, ERR_pragma_assert_open(dir));
		return;
	}
	p = read_line(lex_ignore_token, lex_ignore_token);
	q = skip_predicate(&p, dir);
	if (q) {
		report(preproc_loc, ERR_cpp_end(dir));
		free_tok_list(q);
	}

	/* Create the assertion */
	if (p) {
		set_assert(id, p, def);
	}
	return;
}


/*
    This routine processes a '#unassert' directive.
*/

static void
read_unassert(int dir)
{
	/* Read the predicate name */
	IDENTIFIER id;
	PPTOKEN *p, *q;
	int t = read_token();
	update_column();
	if (in_preproc_dir) {
		preproc_loc = crt_loc;
	}
	if (t != lex_identifier) {
		report(preproc_loc, ERR_pragma_assert_id(dir));
		return;
	}
	id = make_assert(token_hashid, lex_unknown);

	/* Check for simple identifier */
	t = read_token();
	update_column();
	if (in_preproc_dir) {
		preproc_loc = crt_loc;
	}
	if (t == lex_newline) {
		p = NULL;
	} else {
		/* Read the predicate token sequence */
		if (t != lex_open_Hround) {
			report(preproc_loc, ERR_pragma_assert_open(dir));
			return;
		}
		p = read_line(lex_ignore_token, lex_ignore_token);
		q = skip_predicate(&p, dir);
		if (q) {
			report(preproc_loc, ERR_cpp_end(dir));
			free_tok_list(q);
		}
	}

	if (p == NULL) {
		/* Unassert all values */
		LIST(PPTOKEN_P)r;
		r = DEREF_list(id_predicate_values(id));
		while (!IS_NULL_list(r)) {
			DESTROY_CONS_pptok(destroy, q, r, r);
			free_tok_list(q);
		}
		COPY_list(id_predicate_values(id), r);
		COPY_ulong(id_no(id), lex_unknown);
	} else {
		/* Destroy the assertion */
		set_assert(id, p, 0);
	}
	return;
}


/*
    This routine looks up the identifier named nm used in a '#pragma
    weak' directive.  The result should be an external variable or
    function.  The null identifier is returned to indicate an error.
*/

static IDENTIFIER
find_weak_id(HASHID nm)
{
	if (!IS_NULL_hashid(nm)) {
		ERROR err;
		IDENTIFIER id = find_id(nm);
		switch (TAG_id(id)) {
		case id_variable_tag: {
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (!(ds & dspec_auto)) {
				ds |= dspec_used;
				COPY_dspec(id_storage(id), ds);
				return id;
			}
			break;
		}
		case id_function_tag: {
			TYPE t = DEREF_type(id_function_type(id));
			IDENTIFIER over = DEREF_id(id_function_over(id));
			if (IS_NULL_id(over) && IS_type_func(t)) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				ds |= dspec_used;
				COPY_dspec(id_storage(id), ds);
				return id;
			}
			break;
		}
		}
		err = ERR_pragma_preserve_undecl(lex_weak, id);
		report(preproc_loc, err);
	}
	return NULL_id;
}


/*
    This routine processes a '#pragma weak' directive.
*/

void
read_weak(int dir)
{
	IDENTIFIER id = NULL_id;
	IDENTIFIER aid = NULL_id;
	int t = read_token();
	update_column();
	if (in_preproc_dir) {
		preproc_loc = crt_loc;
	}
	if (t == lex_identifier) {
		id = find_weak_id(token_hashid);
		t = read_token();
		update_column();
		if (in_preproc_dir) {
			preproc_loc = crt_loc;
		}
		if (t == lex_assign) {
			t = read_token();
			update_column();
			if (in_preproc_dir) {
				preproc_loc = crt_loc;
			}
			if (t == lex_identifier) {
				aid = find_weak_id(token_hashid);
				t = read_token();
				update_column();
				if (in_preproc_dir)preproc_loc = crt_loc;
			}
		}
	} else {
		t = lex_unknown;
	}
	if (!IS_NULL_id(aid)) {
		static LIST(IDENTIFIER)weak_ids = NULL_list(IDENTIFIER);
		LIST(IDENTIFIER)p = weak_ids;
		while (!IS_NULL_list(p)) {
			IDENTIFIER pid = DEREF_id(HEAD_list(p));
			if (EQ_id(id, pid)) {
				report(preproc_loc, ERR_pragma_weak_redef(id));
				id = NULL_id;
				break;
			}
			p = TAIL_list(p);
		}
		if (!IS_NULL_id(id)) {
			CONS_id(id, weak_ids, weak_ids);
		}
	}
	compile_weak(id, aid);
	if (t != lex_newline) {
		report(preproc_loc, ERR_cpp_end(dir));
	}
	if (in_preproc_dir) {
		IGNORE skip_to_end();
	}
	return;
}


/*
    This routine processes a preprocessing directive up to and including
    the terminating newline character.  The act argument indicates
    whether the directive is active or is being skipped in a conditional
    compilation.  prev gives the previous preprocessing directive value.
    The routine returns a lexical token value which is used to
    communicate the effect of the directive on the main processor.  Most
    directives are only visible to the preprocessor, and return one of
    the values lex_ignore_token, lex_end_condition or lex_included (note
    that these are all less than zero).  Other directives (for example,
    target dependent conditionals) do communicate with the main
    processor by returning a valid lexical token value.
*/

int
read_preproc_dir(int act, int prev)
{
	int t;
	ERROR err;
	HASHID dir;
	int pp = lex_ignore_token;
	in_preproc_dir = 1;
	preproc_loc = crt_loc;

	/* Read the token following the '#' */
	t = read_token();
	update_column();
	if (in_preproc_dir) {
		preproc_loc = crt_loc;
	}
	if (t != lex_identifier) {
		if (t == lex_newline || t == lex_eof) {
			/* Warn about empty directives */
			report(preproc_loc, ERR_cpp_null());
			goto end_label;
		}
		/* Give an error for other directives */
		report(preproc_loc, ERR_cpp_bad());
		goto end_label;
	}

	/* Analyse the '#identifier' directive */
	dir = token_hashid;
	t = find_hashid(dir);
	switch (t) {

	case lex_define:
		/* Deal with '#define' */
		if (act) {
			pp = read_define();
			if (pp >= 0) {
				pp = patch_cond(pp, t);
			}
		}
		goto end_label;

	case lex_else:
	case lex_endif:
		/* Deal with '#else' and '#endif' */
		if (in_preproc_dir && skip_to_end()) {
			/* Check end of directive */
			report(preproc_loc, ERR_cpp_cond_endif_end(t));
		}
		pp = read_if(t, PP_FALSE, lex_ignore_token);
		if (act && pp >= 0)pp = patch_cond(pp, t);
		return pp;

	case lex_elif:
		/* Deal with '#elif' (expression is read in read_if) */
		report(preproc_loc, ERR_cpp_old(t));
		pp = read_if(t, PP_FALSE, lex_ignore_token);
		if (act && pp >= 0) {
			pp = patch_cond(pp, t);
		}
		return pp;

	case lex_error:
		/* Deal with '#error' */
		report(preproc_loc, ERR_cpp_old(t));
		if (act) {
			read_error(OPT_error);
		}
		goto end_label;

	case lex_include:
		/* Deal with '#include' */
		pp = read_include(act, t);
		return pp;

	case lex_if: {
		/* Deal with '#if' */
		unsigned cond = read_if_exp(act, t);
		pp = read_if (t, cond, lex_ignore_token);
		if (act && pp >= 0)pp = patch_cond(pp, t);
		return pp;
	}

	case lex_ifdef: {
		/* Deal with '#ifdef' */
		unsigned cond = read_if_def(act, t, prev);
		pp = read_if (t, cond, prev);
		if (act && pp >= 0)pp = patch_cond(pp, t);
		return pp;
	}

	case lex_ifndef: {
		/* Deal with '#ifndef' */
		unsigned cond = read_if_def(act, t, prev);
		pp = read_if (t, negate_cond(cond), prev);
		if (act && pp >= 0)pp = patch_cond(pp, t);
		return pp;
	}

	case lex_line:
		/* Deal with '#line' */
		if (act) {
			read_location(t);
		}
		goto end_label;

	case lex_pragma:
		/* Deal with '#pragma' */
		if (act) {
			int ts = have_type_specifier;
			int td = have_type_declaration;
			int fd = have_func_declarator;
			QUALIFIER cq = crt_id_qualifier;
			in_pragma_dir = 1;
			pp = read_pragma();
			in_pragma_dir = 0;
			pragma_number = 0;
			crt_id_qualifier = cq;
			have_type_specifier = ts;
			have_type_declaration = td;
			have_func_declarator = fd;
		}
		goto end_label;

	case lex_undef:
		/* Deal with '#undef' */
		if (act) {
			pp = read_undef();
			if (pp >= 0)pp = patch_cond(pp, t);
		}
		goto end_label;

	case lex_assert: {
		/* Deal with '#assert' (extension) */
		OPTION opt = option(OPT_ppdir_assert);
		if (opt != OPTION_DISALLOW) {
			if (opt != OPTION_ALLOW) {
				err = ERR_pragma_cpp_known(t);
				err = set_severity(err, OPT_ppdir_assert, 0);
				report(preproc_loc, err);
			}
			if (act && !option(OPT_ppdir_assert_ignore)) {
				read_assert(t);
			}
			goto end_label;
		}
		break;
	}

	case lex_file: {
		/* Deal with '#file' (extension) */
		OPTION opt = option(OPT_ppdir_file);
		if (opt != OPTION_DISALLOW) {
			if (opt != OPTION_ALLOW) {
				err = ERR_pragma_cpp_known(t);
				err = set_severity(err, OPT_ppdir_file, 0);
				report(preproc_loc, err);
			}
			if (act && !option(OPT_ppdir_file_ignore)) {
				read_location(t);
			}
			goto end_label;
		}
		break;
	}

	case lex_ident: {
		/* Deal with '#ident' (extension) */
		OPTION opt = option(OPT_ppdir_ident);
		if (opt != OPTION_DISALLOW) {
			if (opt != OPTION_ALLOW) {
				err = ERR_pragma_cpp_known(t);
				err = set_severity(err, OPT_ppdir_ident, 0);
				report(preproc_loc, err);
			}
			if (act && !option(OPT_ppdir_ident_ignore)) {
				read_ident(t);
			}
			goto end_label;
		}
		break;
	}

	case lex_import:
	case lex_include_Hnext: {
		/* Deal with '#import' and '#include_next' (extension) */
		OPTION opt = option(OPT_ppdir_import);
		if (opt != OPTION_DISALLOW) {
			if (opt != OPTION_ALLOW) {
				err = ERR_pragma_cpp_known(t);
				err = set_severity(err, OPT_ppdir_import, 0);
				report(preproc_loc, err);
			}
			if (!option(OPT_ppdir_import_ignore)) {
				pp = read_include(act, t);
				return pp;
			}
			goto end_label;
		}
		break;
	}

	case lex_unassert: {
		/* Deal with '#unassert' (extension) */
		OPTION opt = option(OPT_ppdir_unassert);
		if (opt != OPTION_DISALLOW) {
			if (opt != OPTION_ALLOW) {
				err = ERR_pragma_cpp_known(t);
				err = set_severity(err, OPT_ppdir_unassert, 0);
				report(preproc_loc, err);
			}
			if (act && !option(OPT_ppdir_unassert_ignore)) {
				read_unassert(t);
			}
			goto end_label;
		}
		break;
	}

	case lex_warning: {
		/* Deal with '#warning' (extension) */
		OPTION opt = option(OPT_ppdir_warning);
		if (opt != OPTION_DISALLOW) {
			if (opt != OPTION_ALLOW) {
				err = ERR_pragma_cpp_known(t);
				err = set_severity(err, OPT_ppdir_warning, 0);
				report(preproc_loc, err);
			}
			if (act && !option(OPT_ppdir_warning_ignore)) {
				read_error(OPT_warning);
			}
			goto end_label;
		}
		break;
	}

	case lex_weak: {
		/* Deal with '#weak' (extension) */
		OPTION opt = option(OPT_ppdir_weak);
		if (opt != OPTION_DISALLOW) {
			if (opt != OPTION_ALLOW) {
				err = ERR_pragma_cpp_known(t);
				err = set_severity(err, OPT_ppdir_weak, 0);
				report(preproc_loc, err);
			}
			if (act && !option(OPT_ppdir_weak_ignore)) {
				read_weak(t);
			}
			goto end_label;
		}
		break;
	}
	}

	/* Unknown directives */
	report(preproc_loc, ERR_cpp_unknown(dir));
end_label:
	if (in_preproc_dir) {
		IGNORE skip_to_end();
	}
	return pp;
}


/*
 * Print a list of #line directives representing the #include stack
 * so that information on wrapper header files (which simply directly
 * include another header file) is not lost.
 */
static void
print_linedir(FILE *f, LOCATION loc)
{
	string fm = DEREF_string(posn_file(loc.posn));
	char *s = strlit(fm);

	PTR(LOCATION)from = DEREF_ptr(posn_from(loc.posn));
	if (!IS_NULL_ptr(from)) {
		LOCATION fromloc;
		DEREF_loc(from, fromloc);
		print_linedir(f, fromloc);
	}

	fprintf_v(f, "#line %lu \"%s\"\n",
		  loc.line, s);
}

/*
    This routine gives the preprocessor entry point for the compiler.  Each
    token is read, preprocessed, and printed.  The white space in the output
    does not necessarily bear any resemblance to that in the input.
*/

void
preprocess_file(void)
{
	int t;
	FILE *f;
	string fn;
	BUFFER *bf;
	unsigned long ws = 0;
	unsigned long ln = 0;
	int force_space = preproc_space;
	static BUFFER preproc_buff = { NULL, NULL, NULL, NULL };

	/* Initialise input file */
	init_lex();
	fn = DEREF_string(posn_file(preproc_loc.posn));

	/* Open output file */
	if (!open_output(OUTPUT_PREPROC, text_mode)) {
		string nm = output_name[OUTPUT_PREPROC];
		fail(ERR_fail_output(nm));
		term_error(0);
		return;
	}
	f = output_file[OUTPUT_PREPROC];
	bf = clear_buffer(&preproc_buff, f);
	crt_file_changed = 1;

	/* Scan through preprocessing tokens */
	while (t = expand_preproc(EXPAND_NORMAL), t != lex_eof) {
		/* Allow for skipped files */
		if (crt_file_type) {
			continue;
		}

		/* Replace keywords by underlying identifier */
		if (t >= FIRST_KEYWORD && t <= LAST_KEYWORD) {
			crt_token->tok = lex_identifier;
		}
		if (t == lex_builtin_Hfile) {
			fputc_v('\n', f);
			ln++;
			crt_line_changed = 1;
			crt_spaces = 0;
			continue;
		}

		/* Print any required '#line' directives */
		if (crt_line_changed) {
			int ch = crt_file_changed;
			unsigned long n = crt_loc.line;
			unsigned long sp = crt_spaces;
			unsigned long tab = tab_width;
			output_buffer(bf, 0);
			if (ch) {
				string fm =
				    DEREF_string(posn_file(crt_loc.posn));
				if (ch > 1 || !ustreq(fn, fm)) {
					fputs_v("\n\n", f);
					print_linedir(f, crt_loc);
					fn = fm;
					ln = n;
				}
				crt_file_changed = 0;
			}
			if (n != ln) {
				if (n > ln && n <= ln + 10) {
					for (; ln < n; ln++) {
						fputc_v('\n', f);
					}
				} else {
					/* Force '#line' for more than 10 blank
					 * lines */
					fprintf_v(f, "\n\n#line %lu\n", n);
				}
				ln = n;
			}
			crt_line_changed = 0;

			/* Print indentation */
			ws = sp;
			for (; sp >= tab; sp -= tab) {
				bfputc(bf, '\t');
			}
			for (; sp; sp--) {
				bfputc(bf, ' ');
			}

			/* Allow for hash symbols */
			if (t == lex_hash_H1) {
				crt_token->tok = lex_hash_Hhash_H1;
			}
			if (t == lex_hash_H2) {
				crt_token->tok = lex_hash_Hhash_H2;
			}

		} else {
			unsigned long sp = crt_spaces;
			if (sp != ws || force_space) {
				/* Print space */
				ws = sp;
				bfputc(bf, ' ');
			}
		}

		/* Print the token name */
		IGNORE print_pptok(crt_token, bf, 0);
	}
	bfputc(bf, '\n');
	output_buffer(bf, 0);
	close_output(OUTPUT_PREPROC);
	return;
}
