/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/buffer.h>

#include <syntax/syntax.h>

#include <parse/file.h>
#include <parse/preproc.h>
#include <parse/macro.h>
#include <parse/parse.h>
#include <parse/predict.h>

#include <construct/access.h>
#include <construct/basetype.h>
#include <construct/class.h>
#include <construct/declare.h>
#include <construct/function.h>
#include <construct/initialise.h>
#include <construct/namespace.h>
#include <construct/rewrite.h>
#include <construct/statement.h>

#include "ctype_ops.h"
#include "exp_ops.h"
#include "id_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"


/*
    This value is used to keep track of the number of functions skipped
    and subsequently compiled.
*/

static int functions_pending = 0;


/*
    This routine skips the function definition for the function id given by
    the current sequence of lexical tokens.  Note that last_lex_token is
    set to lex_func_Hop to indicate that a function definition has been
    skipped.
*/

void
skip_function(IDENTIFIER id)
{
	EXP e;
	LOCATION loc;
	int t = crt_lex_token;
	PPTOKEN *p = crt_token;
	PPTOKEN *q = p;
	int brackets = 0;
	int try_block = 0;

	/* Check for previous definition */
	if (!IS_NULL_id(id)) {
		PTR(LOCATION)ploc = id_loc(id);
		COPY_loc(ploc, decl_loc);
		e = DEREF_exp(id_function_etc_defn(id));
		if (!IS_NULL_exp(e)) {
			/* Function already defined */
			report(crt_loc, ERR_basic_odr_def_func(id, ploc));
		}
	}

	/* Skip definition */
	loc = crt_loc;
	if (t == lex_try) {
		try_block = 1;
	}
	for (;;) {
		if (t == lex_open_Hbrace_H1 || t == lex_open_Hbrace_H2) {
			/* Start of block */
			brackets++;
		} else if (t == lex_close_Hbrace_H1 ||
			   t == lex_close_Hbrace_H2) {
			/* End of block */
			brackets--;
			if (brackets <= 0) {
				q = crt_token;
				t = expand_preproc(EXPAND_AHEAD);
				if (t != lex_catch || !try_block) {
					/* End of function */
					break;
				}
			}
		} else if (t == lex_semicolon && brackets == 0) {
			/* Premature end of function */
			break;
		} else if (t == lex_eof) {
			/* Premature end of file */
			report(loc, ERR_class_mfct_eof(id));
			crt_lex_token = t;
			return;
		}
		q = crt_token;
		t = expand_preproc(EXPAND_AHEAD);
	}
	last_lex_token = lex_func_Hop;
	crt_lex_token = t;
	snip_tokens(p, q);

	/* Create the definition */
	MAKE_exp_uncompiled(type_void, loc, p, e);
	if (!IS_NULL_id(id)) {
		COPY_exp(id_function_etc_defn(id), e);
		functions_pending++;
	}
	return;
}


/*
    This routine skips the default argument value for the function parameter
    id given by the current sequence of lexical tokens.  It returns an
    expression giving the skipped value which is associated with id by
    init_param.
*/

EXP
skip_default_arg(IDENTIFIER id)
{
	EXP e;
	LOCATION loc;
	int brackets = 0;
	int t = crt_lex_token;
	PPTOKEN *p = crt_token;
	PPTOKEN *q = p;

	/* Skip definition */
	loc = crt_loc;
	for (;;) {
		if (t == lex_open_Hround || t == lex_open_Htemplate) {
			brackets++;
		} else if (t == lex_close_Hround || t == lex_close_Htemplate) {
			if (brackets == 0) {
				break;
			}
			brackets--;
		} else if (t == lex_comma) {
			if (brackets == 0) {
				break;
			}
		} else if (t == lex_eof) {
			/* Premature end of file */
			report(loc, ERR_class_mfct_eof(id));
			crt_lex_token = t;
			return NULL_exp;
		}
		q = crt_token;
		t = expand_preproc(EXPAND_AHEAD);
	}
	crt_lex_token = t;
	snip_tokens(p, q);

	/* Create the definition */
	MAKE_exp_uncompiled(type_error, loc, p, e);
	functions_pending++;
	return e;
}


/*
    When rescanning a template member function it is necessary to bring
    the template parameters back into scope.  This routine performs this
    operation for the template type t.  It returns the non-template
    component of t.
*/

TYPE
begin_templ_scope(TYPE t)
{
	if (!IS_NULL_type(t) && IS_type_templ(t)) {
		TYPE s = DEREF_type(type_templ_defn(t));
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		NAMESPACE ns = DEREF_nspace(tok_templ_pars(sort));
		if (!IS_NULL_nspace(ns)) {
			record_location++;
			in_template_decl++;
			add_namespace(ns);
		}
		t = begin_templ_scope(s);
	}
	return t;
}


/*
    This routine removes any template parameters brought into scope by
    begin_templ_scope.
*/

void
end_templ_scope(TYPE t)
{
	if (!IS_NULL_type(t) && IS_type_templ(t)) {
		TYPE s = DEREF_type(type_templ_defn(t));
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		NAMESPACE ns = DEREF_nspace(tok_templ_pars(sort));
		end_templ_scope(s);
		if (!IS_NULL_nspace(ns)) {
			remove_namespace();
			in_template_decl--;
			record_location--;
		}
	}
	return;
}


/*
    This routine compiles any previously skipped definition for the
    function id.
*/

static void
rescan_function(IDENTIFIER id)
{
	EXP e = DEREF_exp(id_function_etc_defn(id));
	if (!IS_NULL_exp(e) && IS_exp_uncompiled(e)) {
		PPTOKEN *p;
		PARSE_STATE s;
		TYPE fn = DEREF_type(id_function_etc_type(id));

		/* Mark function as inline */
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		ds |= dspec_inline;
		COPY_dspec(id_storage(id), ds);

		/* Save current compiler state */
		save_state(&s, 1);

		/* Set parser to stored definition */
		DEREF_loc(exp_uncompiled_start(e), crt_loc);
		crt_line_changed = 1;
		crt_file_changed = 1;
		p = DEREF_pptok(exp_uncompiled_defn(e));
		init_parser(p);

		/* Start function definition */
		in_class_defn = 0;
		in_function_defn++;
		really_in_function_defn++;
		COPY_exp(id_function_etc_defn(id), NULL_exp);
		DEREF_loc(id_loc(id), decl_loc);
		IGNORE begin_templ_scope(fn);
		begin_function(id);

		/* Parse the stored function definition */
		ADVANCE_LEXER;
		parse_func(&e);
		if (crt_lex_token != lex_eof && !have_syntax_error) {
			ERROR err = ERR_lex_parse(crt_token);
			report(crt_loc, err);
			unreached_code = 1;
		}

		/* End the function definition */
		IGNORE end_function(id, e);
		end_templ_scope(fn);

		/* Reset the parser */
		restore_state(&s);
		p = restore_parser();
		free_tok_list(p);
		functions_pending--;
	}
	return;
}


/*
    This routine compiles any previously skipped default argument value
    for the parameter id.
*/

void
rescan_param(IDENTIFIER id, int rescan)
{
	EXP e = DEREF_exp(id_parameter_init(id));
	if (!IS_NULL_exp(e) && IS_exp_uncompiled(e)) {
		PPTOKEN *p;
		PARSE_STATE s;
		TYPE fn = NULL_type;
		NAMESPACE ns = DEREF_nspace(id_parent(id));
		IDENTIFIER pid = DEREF_id(nspace_name(ns));
		if (!IS_NULL_id(pid) && IS_id_function_etc(pid)) {
			fn = DEREF_type(id_function_etc_type(pid));
		} else {
			CLASS_TYPE ct = crt_class;
			if (!IS_NULL_ctype(ct)) {
				pid = DEREF_id(ctype_name(ct));
			} else {
				pid = NULL_id;
			}
		}

		/* Save current compiler state */
		save_state(&s, 1);

		/* Set parser to stored definition */
		DEREF_loc(exp_uncompiled_start(e), crt_loc);
		crt_line_changed = 1;
		crt_file_changed = 1;
		p = DEREF_pptok(exp_uncompiled_defn(e));
		init_parser(p);

		/* Start dafault argument value */
		in_class_defn = 0;
		COPY_exp(id_parameter_init(id), NULL_exp);
		if (rescan) {
			IGNORE begin_templ_scope(fn);
			push_namespace(ns);
		}

		/* Parse the stored expression */
		ADVANCE_LEXER;
		in_default_arg++;
		parse_exp(&e);
		in_default_arg--;
		if (crt_lex_token != lex_eof && !have_syntax_error) {
			ERROR err = ERR_lex_parse(crt_token);
			report(crt_loc, err);
		}

		/* End the default argument value */
		init_param(id, e);
		if (rescan) {
			IGNORE pop_namespace();
			end_templ_scope(fn);
		}

		/* Reset the parser */
		if (crt_access_list.pending) {
			IGNORE report_access(pid);
		}
		restore_state(&s);
		p = restore_parser();
		free_tok_list(p);
		functions_pending--;
	}
	return;
}


/*
    This routine scans through the current class and any nested classes
    compiling any function definitions which remain uncompiled.
*/

void
rescan_functions(void)
{
	CLASS_TYPE ct = crt_class;
	LIST(IDENTIFIER) ft = DEREF_list(ctype_nest(ct));
	while (!IS_NULL_list(ft)) {
		IDENTIFIER id = DEREF_id(HEAD_list(ft));
		switch (TAG_id(id)) {
		case id_class_name_tag: {
			/* Deal with nested classes */
			CLASS_TYPE cs;
			CLASS_INFO ci;
			NAMESPACE cns;
			TYPE t = DEREF_type(id_class_name_defn(id));
			TYPE s = begin_templ_scope(t);
			cs = DEREF_ctype(type_compound_defn(s));
			ci = DEREF_cinfo(ctype_info(cs));
			if (ci & cinfo_complete) {
				cns = DEREF_nspace(ctype_member(cs));
				push_class(cs);
				push_namespace(cns);
				rescan_functions();
				IGNORE pop_namespace();
				pop_class();
			}
			end_templ_scope(t);
			break;
		}
		case id_function_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag:
			/* Deal with inline functions (including friends) */
			rescan_function(id);
			break;
		case id_parameter_tag:
			/* Deal with default arguments */
			rescan_param(id, 1);
			break;
		}
		ft = TAIL_list(ft);
	}
	return;
}
