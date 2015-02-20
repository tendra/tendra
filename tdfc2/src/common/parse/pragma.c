/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdio.h>

#include <shared/check.h>

#include "config.h"
#include "c_types.h"

#include "hashid_ops.h"
#include "id_ops.h"
#include "tok_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "char.h"
#include "declare.h"
#include "dump.h"
#include "file.h"
#include "lex.h"
#include "hash.h"
#include "macro.h"
#include "parse.h"
#include "pragma.h"
#include "predict.h"
#include "preproc.h"
#include "psyntax.h"
#include "redeclare.h"
#include "statement.h"
#include "symbols.h"
#include "tok.h"
#include "token.h"
#include "ustring.h"
#include "variable.h"


/*
    By including both psyntax.h and syntax.h, the compiler will check
    that the lex_* macros defined in each are consistent.  Note that
    because the #pragma syntax is the same for both C and C++, this
    also checks the consistency of the C and C++ syntaxes.  This is only
    done in development mode.
*/

#ifndef NDEBUG
#include "syntax.h"
#endif


/*
    This routine reads the next preprocessing token from the input file.
*/

static PPTOKEN *
get_token(void)
{
	PPTOKEN *p = new_pptok();
	int t = read_token();
	update_column();
	p->tok = t;
	p->pp_space = WHITE_SPACE;
	p->next = NULL;
	if (t <= LAST_COMPLEX_TOKEN) {
		token_parts(t, p);
	}
	return p;
}


/*
    This routine finds the lexical token corresponding to the identifier id.
    If id does not represent an underlying keyword then an error is reported
    and lex_identifier is returned.
*/

int
find_keyword(IDENTIFIER id)
{
	HASHID nm = DEREF_hashid(id_name(id));
	int t = find_hashid(nm);
	if (t == lex_identifier) {
		report(preproc_loc, ERR_pragma_keyword_bad(nm));
	}
	return t;
}


/*
    This routine defines id to be a keyword with lexical token number t.
    Certain language extensions are implemented by tokens disguised as
    keywords.
*/

void
define_keyword(IDENTIFIER id, int t)
{
	switch (t) {
	case lex_identifier: {
		break;
	}
	case lex_representation: {
		TOKEN tok = make_sort("ZZZ", 1);
		id = make_token_decl(tok, 0, id, id);
		token_interface(id, lex_no_Hdef);
		COPY_int(tok_proc_key(tok), t);
		break;
	}
	case lex_typeof: {
		TOKEN tok = make_sort("SE", 1);
		id = make_token_decl(tok, 0, id, id);
		token_interface(id, lex_no_Hdef);
		COPY_int(tok_proc_key(tok), t);
		break;
	}
	default: {
		HASHID nm = DEREF_hashid(id_name(id));
		IGNORE make_keyword(nm, t, NULL_id);
		break;
	}
	}
	return;
}


/*
    This routine undefines the keyword id.
*/

void
undef_keyword(IDENTIFIER id)
{
	unsigned tag;
	HASHID nm = DEREF_hashid(id_name(id));
	PTR(IDENTIFIER)ptr = hashid_id(nm);
	do {
		IDENTIFIER pid = DEREF_id(ptr);
		tag = TAG_id(pid);
		switch (tag) {
		case id_keyword_tag:
		case id_iso_keyword_tag:
		case id_reserved_tag:
			/* Undefine a keyword */
			if (do_keyword) {
				dump_undefine(pid, &preproc_loc, 1);
			}
			pid = DEREF_id(id_alias(pid));
			COPY_id(ptr, pid);
			COPY_id(hashid_cache(nm), NULL_id);
			return;
		}
		ptr = id_alias(pid);
	} while (tag != id_dummy_tag);
	return;
}


/*
    The routine read_tendra replaces all identifier tokens within a '#pragma'
    command by their corresponding underlying keywords.  This routine restores
    these keywords, except that given by s, to identifiers.
*/

void
rescan_pragma(int s)
{
	PPTOKEN *p;
	for (p = crt_token; p != NULL; p = p->next) {
		int t = p->tok;
		if (t >= FIRST_KEYWORD && t <= LAST_KEYWORD && t != s) {
			p->tok = lex_identifier;
		}
	}
	return;
}


/*
    This routine sets the preprocessing token p to the keyword corresponding
    to the lexical token number t.
*/

static void
set_token(PPTOKEN *p, int t)
{
	HASHID nm = KEYWORD(t);
	p->tok = t;
	p->pp_data.id.hash = nm;
	p->pp_data.id.use = DEREF_id(hashid_id(nm));
	return;
}


/*
    This routine is used by the preprocessor to preserve a '#pragma'
    statement.  The arguments are as in parse_pragma.
*/

static void
patch_pragma(PPTOKEN *p, int tendra)
{
	p = clean_tok_list(p);
	switch (p->tok) {
	case lex_interface: {
		int t = crt_interface;
		if (t == lex_ignore && tendra) {
			t = lex_reject;
		}
		set_token(p, t);
		break;
	}
	case lex_member:
		if (!tendra) {
			if (p->next->tok == lex_definition) {
				set_token(p, lex_define_Hcap);
				set_token(p->next, lex_member_Hcap);
			}
		}
		break;
	case lex_promoted:
		if (!tendra) {
			set_token(p, lex_promote);
		}
		break;
	case lex_reject:
		if (!tendra) {
			set_token(p, lex_ignore);
		}
		break;
	}
	patch_preproc_dir(p);
	if (tendra) {
		p = patch_tokens(tendra);
		set_token(p, lex_tendra);
		if (tendra == 2)p->next->tok = lex_plus_Hplus;
	}
	return;
}


/*
    This routine parses the '#pragma' statement given by the preprocessing
    tokens p.  tendra is 1 for '#pragma TenDRA' statements, 2 for '#pragma
    TenDRA++' statements, and 0 otherwise.
*/

static int
parse_pragma(PPTOKEN *p, int tendra)
{
	int nt;
	PPTOKEN *pt;
	PARSE_STATE s;
	int pp = preproc_only;
	int tok = lex_ignore_token;

	/* Parsing action */
	new_linkage = crt_linkage;
	save_state(&s, 0);
	init_parser(p);
	crt_loc = preproc_loc;
	crt_line_changed = 1;
	ADVANCE_LEXER;
	if (pp) {
		/* try to parse the pragma, but ignore errors. typedefs are not
		 * handled during preprocessing, and pragmas may refer to them.
		 * pragmas should be parsed when possible though because they can
		 * affect how #if expressions are evaluated */
		int et = error_threshold;
		error_threshold = ERR_SERIOUS;
		parse_tendra(&tok);
		error_threshold = et;
	} else {
		parse_tendra(&tok);
	}
	nt = crt_lex_token;
	pt = crt_token;
	p = restore_parser();

	/* Check for end of input */
	switch (tok) {
	case lex_set:
	case lex_unused: {
		/* Patch inset pragma statements */
		PPTOKEN *q = clean_tok_list(p);
		PPTOKEN *r = new_pptok();
		p = q;
		p->tok = tok;
		while (q->tok != lex_newline) {
			q = q->next;
		}
		q->tok = lex_inset_Hend;
		r->tok = lex_newline;
		r->next = q->next;
		q->next = r;
		patch_preproc_dir(p);
		tok = lex_inset_Hstart;
		p = NULL;
		break;
	}
	default:
		/* Should have reached the end of the line */
		if (nt != lex_newline && !have_syntax_error) {
			ERROR err = ERR_lex_parse(pt);
			err = concat_error(err, ERR_cpp_end(lex_pragma));
			report(preproc_loc, err);
		}
		break;
	}

	/* Preprocessing action */
	if (pp) {
		patch_pragma(p, tendra);
		tok = lex_hash_Hpragma;
	} else {
		free_tok_list(p);
	}
	restore_state(&s);
	crt_linkage = new_linkage;
	return tok;
}


/*
    This routine scans along the list of preprocessing tokens p until it
    finds the first colon.  It then returns the following token.  The null
    token is returned if there is no colon in p.
*/

static PPTOKEN *
skip_to_colon(PPTOKEN *p)
{
	while (p) {
		PPTOKEN *q = p->next;
		if (p->tok == lex_colon) {
			return q;
		}
		p = q;
	}
	return NULL;
}


/*
    This routine marks the TDF token parameter given by the preprocessing
    tokens p.  This consists of an optional 'TAG' followed by an identifier,
    which is optional if n is false.  Macro expansion of this identifier
    is inhibited.  Macro is true if the identifier is declared in the
    token namespace.
*/

static PPTOKEN *
mark_tdf_param(PPTOKEN *p, int n, int macro)
{
	if (p && p->tok == lex_identifier) {
		int t = find_hashid(p->pp_data.id.hash);
		if (t == lex_tag_Hcap) {
			if (p->next && p->next->tok == lex_identifier) {
				/* Have 'TAG id' */
				p->tok = t;
				p = p->next;
				p->pp_data.id.use = NULL_id;
			} else {
				/* Have 'TAG' */
				if (n == 0) {
					/* Interpret as 'TAG' */
					p->tok = t;
				} else {
					/* Interpret as 'id' where id = TAG */
					p->pp_data.id.use = NULL_id;
				}
			}
		} else {
			/* Have 'id' */
			if (macro && preproc_only) {
				/* Mark macro names when preprocessing */
				HASHID nm = p->pp_data.id.hash;
				unsigned c = check_macro(nm, 0);
				IDENTIFIER id =
				    underlying_id(p->pp_data.id.use);
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				ds |= dspec_token;
				COPY_dspec(id_storage(id), ds);
				if (c == PP_TRUE) {
					/* Token previously defined as macro */
					PPTOKEN *q;
					token_macro = DEREF_id(hashid_id(nm));
					IGNORE patch_cond(lex_hash_Hop,
							  lex_define);
					q = patch_tokens(2);
					q->tok = lex_builtin_Hfile;
					q->next->tok = lex_hash_Hop;
				}
			}
			p->pp_data.id.use = NULL_id;
		}
		return p->next;
	}
	if (n) {
		return NULL;
	}
	return p;
}


/*
    This routine marks the TDF token program parameter given by the
    preprocessing tokens p.
*/

static PPTOKEN *
mark_prog_param(PPTOKEN *p)
{
	if (p && p->tok == lex_identifier) {
		int t = find_hashid(p->pp_data.id.hash);
		switch (t) {
		case lex_exp_Hcap:
		case lex_nat_Hcap:
		case lex_int_Hcap:
		case lex_stmt_Hcap:
		case lex_proc_Hcap:
			/* Have the form 'EXP id' etc */
			p->tok = t;
			p = p->next;
			if (p) {
				p = p->next;
			}
			return p;
		case lex_type_Hcap: {
			/* Have the form 'TYPE t' */
			int depth = 0;
			p->tok = t;
			while (p) {
				/* Step over type */
				switch (p->tok) {
				case lex_open_Hround:
				case lex_open_Hsquare_H1:
				case lex_open_Hsquare_H2:
					depth++;
					break;
				case lex_close_Hround:
				case lex_close_Hsquare_H1:
				case lex_close_Hsquare_H2:
					if (depth > 0) {
						depth--;
					}
					break;
				case lex_comma:
					if (depth == 0) {
						return p;
					}
					break;
				case lex_close_Hbrace_H1:
				case lex_close_Hbrace_H2:
					return p;
				}
				p = p->next;
			}
			break;
		}
		case lex_member_Hcap:
			/* Have the form 'MEMBER t : id' */
			p->tok = t;
			p = skip_to_colon(p->next);
			if (p) {
				p = p->next;
			}
			return p;
		}
	}
	return NULL;
}


/*
    The macro expansion of '#pragma token' statements is rather complex.
    The token syntax skeleton is not subject to macro expansion, while
    any types etc. involved in the specification are.  This routine marks
    the skeleton keywords in the list of preprocessing tokens p, returning
    the token immediately following the token specification.  It also sets
    macro to true if the declared token lies in the macro namespace.
*/

static PPTOKEN *
mark_tdf_token(PPTOKEN *p, int *macro)
{
	if (p == NULL) {
		return NULL;
	}
	if (p->tok == lex_identifier) {
		int t = find_hashid(p->pp_data.id.hash);
		switch (t) {
		case lex_exp_Hcap:
			/* Expression token specifiers */
			*macro = 1;
			p->tok = t;
			p = p->next;
			if (p->tok == lex_identifier) {
				/* Check for lvalue or rvalue qualifier */
				t = find_hashid(p->pp_data.id.hash);
				if (t == lex_lvalue || t == lex_rvalue ||
				    t == lex_const) {
					p->tok = t;
				}
				p = p->next;
			}
			if (p->tok == lex_colon) {
				/* Step over type name */
				p = skip_to_colon(p->next);
			}
			return p;

		case lex_func_Hcap:
			/* Function token specifiers */
			*macro = 1;
			p->tok = t;
			p = skip_to_colon(p->next);
			return p;

		case lex_member_Hcap:
			/* Member token specifiers */
			p->tok = t;
			p = p->next;
			if (p->tok == lex_identifier) {
				/* Check for access specifier */
				t = find_hashid(p->pp_data.id.hash);
				if (t == lex_public || t == lex_protected ||
				    t == lex_private) {
					p->tok = t;
					p = p->next;
				}
			}
			p = skip_to_colon(p);
			p = skip_to_colon(p);
			return p;

		case lex_proc_Hcap:
			/* Procedure token specifiers */
			*macro = 1;
			p->tok = t;
			p = p->next;
			if (p == NULL) {
				return NULL;
			}
			t = p->tok;
			if (t == lex_open_Hbrace_H1 ||
			    t == lex_open_Hbrace_H2) {
				/* General procedure parameters */
				p = p->next;
				for (;;) {
					if (p == NULL) {
						break;
					}
					t = p->tok;
					if (t == lex_or_H1) {
						p = p->next;
						break;
					}
					p = mark_tdf_token(p, macro);
					p = mark_tdf_param(p, 1, 0);
					if (p == NULL) {
						break;
					}
					if (p->tok == lex_comma)p = p->next;
				}
				for (;;) {
					if (p == NULL) {
						break;
					}
					t = p->tok;
					if (t == lex_close_Hbrace_H1 ||
					    t == lex_close_Hbrace_H2) {
						p = p->next;
						break;
					}
					p = mark_prog_param(p);
					if (p == NULL) {
						break;
					}
					if (p->tok == lex_comma)p = p->next;
				}
			} else if (t == lex_open_Hround) {
				/* Simple procedure parameters */
				p = p->next;
				for (;;) {
					if (p == NULL) {
						break;
					}
					t = p->tok;
					if (t == lex_close_Hround) {
						p = p->next;
						break;
					}
					p = mark_tdf_token(p, macro);
					p = mark_tdf_param(p, 0, 0);
					if (p == NULL) {
						break;
					}
					if (p->tok == lex_comma) {
						p = p->next;
					}
				}
			}
			p = mark_tdf_token(p, macro);
			return p;

		case lex_variety_Hcap:
			/* Integral type token specifiers */
			p->tok = t;
			p = p->next;
			if (p->tok == lex_identifier) {
				/* Check for signed or unsigned qualifier */
				t = find_hashid(p->pp_data.id.hash);
				if (t == lex_signed || t == lex_unsigned) {
					p->tok = t;
					p = p->next;
				}
			}
			return p;

		case lex_nat_Hcap:
		case lex_int_Hcap:
		case lex_stmt_Hcap:
			/* Simple token specifiers */
			*macro = 1;
			p->tok = t;
			return p->next;

		case lex_arith_Hcap:
		case lex_class_Hcap:
		case lex_float_Hcap:
		case lex_scalar_Hcap:
		case lex_struct_Hcap:
		case lex_type_Hcap:
		case lex_union_Hcap:
			/* Type token specifiers */
			p->tok = t;
			return p->next;
		}
	}
	return p->next;
}


/*
    This routine processes an external token name.  This consists of a
    hash symbol, pointed to by p, followed a list of preprocessing
    tokens.  Note that the result is an extended identifier, unless it
    is a simple identifier.
*/

static PPTOKEN *
quote_token_name(PPTOKEN *p)
{
	PPTOKEN *q = p->next;
	if (q != NULL) {
		/* All following tokens are quoted */
		string s;
		unsigned long sp = q->pp_space;
		IGNORE quote_tok_list(q, 0, char_quote);
		free_tok_list(q);
		q = new_pptok();
		q->pp_space = sp;
		q->next = NULL;
		s = token_buff.start;
		if (ustrseq(s, "-")) {
			/* Special form '-' */
			q->tok = lex_minus;
		} else {
			/* Create an identifier */
			unsigned long h = hash(s);
			token_hashid = lookup_name(s, h, 1, lex_unknown);
			q->tok = lex_identifier;
			token_parts(lex_identifier, q);
		}
		p->next = q;
		p = q;
	}
	return p;
}


/*
    This routine processes a '#pragma token' statement.  p gives the first
    preprocessing token (i.e. 'token').  tendra is as in parse_pragma.
*/

static int
read_tdf_token(PPTOKEN *p, int tendra)
{
	/* Read and macro expand the rest of the line */
	int t;
	PPTOKEN *q = p;
	while (q->next)q = q->next;
	if (q->tok != lex_newline) {
		int macro = 0;
		PPTOKEN *r = read_line(lex_ignore_token, lex_ignore_token);
		if (r) {
			r->pp_space = WHITE_SPACE;
		}
		q->next = r;
		r = mark_tdf_token(r, &macro);
		r = mark_tdf_param(r, 1, macro);
		while (r) {
			/* Find token name */
			t = r->tok;
			if (t == lex_hash_H1 || t == lex_hash_H2) {
				q = quote_token_name(r);
				break;
			}
			q = r;
			r = r->next;
		}

		/* Add newline token */
		while (q->next) {
			q = q->next;
		}
		q->next = new_pptok();
		q->next->tok = lex_newline;
		q->next->next = NULL;
	}
	q = expand_tok_list(p);
	free_tok_list(p);

	/* Parse the line */
	in_token_decl = 1;
	decl_loc = preproc_loc;
	t = parse_pragma(q, tendra);
	in_token_decl = 0;
	return t;
}


/*
    This routine processes a '#pragma TenDRA' statement, returning the
    corresponding lexical token.  One or two tokens from the line will
    have already been read into p.  tendra is as in parse_pragma.
*/

static int
read_tendra(PPTOKEN *p, int tendra)
{
	/* Read and macro expand the rest of the line */
	PPTOKEN *q = p;
	while (q->next) {
		q = q->next;
	}
	if (q->tok != lex_newline) {
		PPTOKEN *r = read_line(lex_ignore_token, lex_newline);
		if (r) {
			r->pp_space = WHITE_SPACE;
		}
		q->next = r;
	}
	q = expand_tok_list(p);
	free_tok_list(p);
	p = q;

	/* Replace any identifiers by keywords */
	for (q = p; q != NULL; q = q->next) {
		int t = q->tok;
		if (t == lex_identifier) {
			t = find_hashid(q->pp_data.id.hash);
			q->tok = t;
		}
	}

	/* Parse the line */
	return parse_pragma(p, tendra);
}


/*
    This routine processes a '#pragma interface' statement, returning the
    corresponding lexical token.  One or two tokens from the line will
    have already been read into p.  tendra is as in parse_pragma.
*/

static int
read_interface(PPTOKEN *p, int tendra)
{
	/* Read and macro expand the rest of the line */
	int tok;
	int nl = 0;
	PPTOKEN *q = p;
	PPTOKEN *r = p;
	while (q->next)q = q->next;
	if (q->tok != lex_newline) {
		PPTOKEN *s = read_line(lex_ignore_token, lex_ignore_token);
		if (s) {
			s->pp_space = WHITE_SPACE;
		}
		q->next = s;
		nl = 1;
	}
	for (q = p; q != NULL; q = q->next) {
		/* Suppress expansion of 'TAG' */
		int t = q->tok;
		if (t == lex_identifier) {
			t = find_hashid(q->pp_data.id.hash);
			if (t == lex_tag_Hcap) {
				q->tok = t;
			}
		} else if (t == lex_hash_H1 || t == lex_hash_H2) {
			r = quote_token_name(q);
			break;
		}
		r = q;
	}

	/* Add newline token */
	if (nl) {
		while (r->next)r = r->next;
		r->next = new_pptok();
		r->next->tok = lex_newline;
		r->next->next = NULL;
	}

	/* Parse the line */
	tok = parse_pragma(p, tendra);
	return tok;
}


/*
    This routine processes a '#pragma' statement in which there is no
    TenDRA keyword, or such a keyword is optional.  The argument p gives
    the first preprocessing token of the statement, while tendra is as
    in parse_pragma.  The corresponding lexical token value is returned
    if the statement is recognised, otherwise lex_unknown is returned.
    The non-TenDRA and TenDRA forms may differ as follows:

	token				TenDRA token
	extend interface		TenDRA extend
	implement interface		TenDRA implement
	define				TenDRA define
	no_def				TenDRA no_def
	ignore				TenDRA reject
	interface			TenDRA interface
	promote				TenDRA promoted
	compute promote			TenDRA compute promote (?)
	integer literal			TenDRA integer literal
	external volatile		TenDRA external volatile
	DEFINE MEMBER			TenDRA member definition
*/

static int
read_non_tendra(PPTOKEN *p, int tendra)
{
	if (p->tok == lex_identifier) {
		int t = find_hashid(p->pp_data.id.hash);
		switch (t) {

		case lex_token:
			/* Token syntax */
			p->tok = t;
			return read_tdf_token(p, tendra);

		case lex_extend:
		case lex_implement: {
			/* Interface inclusion */
			int pp;
			if (!tendra) {
				/* Need 'interface' for non-TenDRA form */
				PPTOKEN *q = get_token();
				p->next = q;
				if (q->tok == lex_identifier) {
					int s = find_hashid(q->pp_data.id.hash);
					if (s != lex_interface) {
						break;
					}
				}
			}
			pp = read_include(1, lex_pragma);
			if (pp == lex_included) {
				/* Update current interface flag */
				if (t == lex_implement) {
					crt_interface = lex_define;
				} else {
					if (crt_interface != lex_no_Hdef) {
						crt_interface = lex_ignore;
					}
				}
			}
			return pp;
		}

		case lex_define:
		case lex_no_Hdef:
		case lex_interface:
			/* Interface listing */
			p->tok = t;
			return read_interface(p, tendra);

		case lex_reject:
			/* Interface listing (TenDRA form) */
			if (tendra) {
				p->tok = t;
				return read_interface(p, tendra);
			}
			break;

		case lex_ignore:
			/* Interface listing (non-TenDRA form) */
			if (!tendra) {
				p->tok = lex_reject;
				return read_interface(p, tendra);
			}
			break;

		case lex_undef: {
			/* Token undefining */
			PPTOKEN *q = get_token();
			p->next = q;
			if (q->tok == lex_identifier) {
				int s = find_hashid(q->pp_data.id.hash);
				if (s == lex_token) {
					p->tok = t;
					q->tok = s;
					return read_interface(p, tendra);
				}
			}
			break;
		}

		case lex_promote:
			/* Promotion specification (non-TenDRA form) */
			if (!tendra) {
				set_token(p, lex_promoted);
				return read_tendra(p, tendra);
			}
			break;

		case lex_promoted:
			/* Promotion specification (TenDRA form) */
			if (tendra) {
				set_token(p, lex_promoted);
				return read_tendra(p, tendra);
			}
			break;

		case lex_compute: {
			/* Computed promotion specification */
			PPTOKEN *q = get_token();
			p->next = q;
			if (q->tok == lex_identifier) {
				int s = find_hashid(q->pp_data.id.hash);
				if (s == lex_promote) {
					set_token(p, t);
					set_token(q, s);
					return read_tendra(p, tendra);
				}
			}
			break;
		}

		case lex_integer: {
			/* Integer literal specification */
			PPTOKEN *q = get_token();
			p->next = q;
			if (q->tok == lex_identifier) {
				int s = find_hashid(q->pp_data.id.hash);
				if (s == lex_lit) {
					set_token(p, t);
					set_token(q, s);
					return read_tendra(p, tendra);
				}
			}
			break;
		}

		case lex_define_Hcap:
			/* Member definition (non-TenDRA form) */
			if (!tendra) {
				PPTOKEN *q = get_token();
				p->next = q;
				if (q->tok == lex_identifier) {
					int s = find_hashid(q->pp_data.id.hash);
					if (s == lex_member_Hcap) {
						set_token(p, lex_member);
						set_token(q, lex_definition);
						return read_tendra(p, tendra);
					}
				}
			}
			break;

		case lex_member:
			/* Member definition (TenDRA form) */
			if (tendra) {
				PPTOKEN *q = get_token();
				p->next = q;
				if (q->tok == lex_identifier) {
					int s = find_hashid(q->pp_data.id.hash);
					if (s == lex_definition) {
						set_token(p, lex_member);
						set_token(q, lex_definition);
						return read_tendra(p, tendra);
					}
				}
			}
			break;

		case lex_accept:
			/* Conversion tokens (non-TenDRA form) */
			if (!tendra) {
				PPTOKEN *q = get_token();
				p->next = q;
				if (q->tok == lex_ellipsis) {
					return read_tendra(p, tendra);
				}
				if (q->tok == lex_identifier) {
					int s = find_hashid(q->pp_data.id.hash);
					if (s == lex_conversion) {
						return read_tendra(p, tendra);
					}
				}
			}
			break;

		case lex_external:
			/* External volatility (non-TenDRA form) */
			if (!tendra) {
				PPTOKEN *q = get_token();
				p->next = q;
				if (q->tok == lex_identifier) {
					int s = find_hashid(q->pp_data.id.hash);
					if (s == lex_volatile) {
						return read_tendra(p, tendra);
					}
				}
			}
			break;

		case lex_preserve:
			/* Preserve statics (non-TenDRA form) */
			return read_tendra(p, tendra);
		}
	}
	return lex_unknown;
}


/*
    This routine analyses a '#pragma' statement, returning the corresponding
    lexical token.  It is called from read_preproc_dir (q.v.) immediately
    after the '#pragma' directive has been identified.  It is not called for
    skipped '#pragma' directives.  The calling routine will skip to the end
    of the preprocessing directive if necessary.
*/

int
read_pragma(void)
{
	int t;
	PPTOKEN *p = get_token();
	if (p->tok == lex_identifier) {
		t = find_hashid(p->pp_data.id.hash);
		switch (t) {

		case lex_tendra: {
			/* Deal with '#pragma TenDRA' */
			int tendra = 1;
			p->next = free_tokens;
			free_tokens = p;
			p = get_token();
			if (p->tok == lex_plus_Hplus) {
				/* Allow for TenDRA++ */
#if LANGUAGE_CPP
				p->next = free_tokens;
				free_tokens = p;
				p = get_token();
				tendra = 2;
#else
				return lex_ignore_token;
#endif
			}

			/* Allow for optional TenDRA pragmas */
			t = read_non_tendra(p, tendra);
			if (t != lex_unknown) {
				return t;
			}

			/* Deal with TenDRA pragmas */
			t = read_tendra(p, tendra);
			return t;
		}

		case lex_ident:
			/* Deal with '#pragma ident' */
			if (!option(OPT_ppdir_ident_ignore)) {
				read_ident(lex_pragma);
			}
			return lex_ignore_token;

		case lex_weak:
			/* Deal with '#pragma weak' */
			if (!option(OPT_ppdir_weak_ignore)) {
				read_weak(lex_pragma);
			}
			return lex_ignore_token;
		}
	}

	/* Deal with non-TenDRA pragmas */
	t = read_non_tendra(p, 0);
	if (t != lex_unknown) {
		return t;
	}

	/* Report unknown pragmas */
	free_tok_list(p);
	report(preproc_loc, ERR_cpp_pragma_unknown(lex_pragma));
	return lex_ignore_token;
}


/*
    This routine analyses the comment built up in token_buff for lint
    format comments.  These are interpreted locally.  This can go slightly
    wrong with look-ahead, in which case the more structured keyword
    approach should be used.  Other fairly standard lint comments include
    VARARGS, LINTLIBRARY, CONSTANTCONDITION (CONSTCOND), EMPTY, LINTED,
    PROTOLIB, PRINTFLIKE and SCANFLIKE.
*/

int
lint_comment(void)
{
	string t;
	size_t sz;
	character c;
	string s = token_buff.start;
	while (c = *s, is_white_char((unsigned long)c)) {
		/* Step over initial white space */
		s++;
	}
	t = s;
	while (c = *s, is_alpha_char((unsigned long)c)) {
		/* Scan to end of identifier */
		s++;
	}

	/* Check identifier */
	sz = (size_t)(s - t);
	switch (sz) {
	case 8:
		if (strncmp(strlit(t), "ARGSUSED", sz) == 0) {
			/* Indicate unused variables */
			suppress_variable = 1;
		} else if (strncmp(strlit(t), "FALLTHRU", sz) == 0) {
			/* Suppress fall through errors */
			suppress_fall = 1;
		}
		break;
	case 10:
		if (strncmp(strlit(t), "NOTREACHED", sz) == 0) {
			/* Suppress unreached code errors */
			unreached_last = 1;
		}
		break;
	case 11:
		if (strncmp(strlit(t), "FALLTHROUGH", sz) == 0) {
			/* Suppress fall through errors */
			suppress_fall = 1;
		}
		break;
	}

	/* Rest of comment is ignored */
	return lex_ignore_token;
}
