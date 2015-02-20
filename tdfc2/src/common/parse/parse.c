/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>

#include <parse/char.h>
#include <parse/file.h>
#include <parse/hash.h>
#include <parse/lex.h>
#include <parse/literal.h>
#include <parse/macro.h>
#include <parse/parse.h>
#include <parse/predict.h>
#include <parse/preproc.h>
#include <parse/symbols.h>

#include "ctype_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "access.h"
#include "class.h"
#include "derive.h"
#include "identifier.h"
#include "namespace.h"
#include "redeclare.h"
#include "syntax.h"
#include "template.h"
#include "tokdef.h"


/*
    These variables are used by the parser to hold the current and former
    lexical token numbers.
*/

int crt_lex_token = lex_unknown;
int last_lex_token = lex_unknown;
int saved_lex_token = lex_unknown;
static int have_template = 0;
int have_syntax_error = 0;


/*
    The currently active lexical tokens are formed into a list starting
    with first_token.  The position of the current token within this list
    is given by crt_token.  The main routine for building up this list
    is expand_token which either advances crt_token one step along the
    list, or, if crt_token points to the end of the list, reads and macro
    expands the next token from the input file, appending the resulting
    tokens to the end of the list.  The list is periodically garbage
    collected by setting first_token to crt_token and freeing all the
    tokens from the old first_token.
*/

PPTOKEN *crt_token = NULL;
static PPTOKEN *first_token = NULL;
NAMESPACE crt_lookup = NULL_nspace;
static unsigned long crt_lookup_depth = 0;
static OPTIONS *prev_opts = NULL;
static STACK(int)token_stack = NULL_stack(int);
static STACK(PPTOKEN_P)parser_stack = NULL_stack(PPTOKEN_P);
static STACK(NAMESPACE)lookup_stack = NULL_stack(NAMESPACE);


/*
    This routine initialises a new list of active lexical tokens with the
    value toks by pushing the old values of first_token and crt_token onto
    the stack parser_stack and setting them to point to a new dummy token
    whose next field is toks.
*/

void
init_parser(PPTOKEN *toks)
{
	PPTOKEN *q;
	PUSH_int(crt_lex_token, token_stack);
	PUSH_int(last_lex_token, token_stack);
	PUSH_int(saved_lex_token, token_stack);
	PUSH_nspace(crt_lookup, lookup_stack);
	PUSH_pptok(first_token, parser_stack);
	PUSH_pptok(crt_token, parser_stack);
	q = new_pptok();
	q->tok = lex_ignore_token;
	q->pp_space = 0;
	q->next = toks;
	first_token = q;
	crt_token = q;
	crt_lookup = NULL_nspace;
	crt_lookup_depth = 0;
	crt_lex_token = lex_unknown;
	last_lex_token = lex_unknown;
	saved_lex_token = lex_unknown;
	return;
}


/*
    This routine restores the previous list of active lexical tokens by
    popping the values of first_token and crt_token from the stack.  The
    previous list is returned.
*/

PPTOKEN *
restore_parser(void)
{
	PPTOKEN *p = first_token;
	POP_pptok(crt_token, parser_stack);
	POP_pptok(first_token, parser_stack);
	POP_nspace(crt_lookup, lookup_stack);
	POP_int(last_lex_token, token_stack);
	POP_int(saved_lex_token, token_stack);
	POP_int(crt_lex_token, token_stack);
	crt_lookup_depth = 0;
	assert(first_token != NULL);
	return p;
}


/*
    This routine removes the tokens from p to q inclusive from the current
    list.  crt_token must not be included within this range.
*/

void
snip_tokens(PPTOKEN *p, PPTOKEN *q)
{
	PPTOKEN *r = first_token;
	if (r == p) {
		first_token = q->next;
	} else {
		while (r->next != p) {
			r = r->next;
		}
		r->next = q->next;
	}
	r = new_pptok();
	r->tok = lex_eof;
	q->next = r;
	r->next = NULL;
	return;
}


/*
    This routine patches n tokens into the current list immediately after
    crt_token, returning the first token.  This is used by the preprocessor
    to pass more than one token to the parser.
*/

PPTOKEN *
patch_tokens(int n)
{
	while (n) {
		PPTOKEN *p = new_pptok();
		p->tok = lex_ignore_token;
		p->next = crt_token->next;
		p->pp_space = WHITE_SPACE;
		crt_token->next = p;
		n--;
	}
	return crt_token->next;
}


/*
    This variable is used to record the current depth of saved parser
    states.
*/

int crt_state_depth = 0;


/*
    This routine saves the current parser state into s, it also clears the
    syntax error flag.  col is true if column numbers are to be considered
    during the parsing.
*/

void
save_state(PARSE_STATE *s, int col)
{
	/* Save current location */
	s->loc = crt_loc;

	/* Save current namespace */
	s->nspace[0] = crt_namespace;
	s->nspace[1] = templ_namespace;
	s->nstack[0] = namespace_stack;
	s->nstack[1] = crt_nspace_stack;
	s->nstack[2] = local_nspace_stack;

	/* Save flag values */
	s->flag[0] = in_class_defn;
	s->flag[1] = in_function_defn;
	s->flag[2] = really_in_class_defn;
	s->flag[3] = really_in_function_defn;
	s->flag[4] = in_declaration;
	s->flag[5] = in_template_decl;
	s->flag[6] = have_syntax_error;
	s->flag[7] = cache_lookup;
	s->flag[8] = crt_col_changed;
	have_syntax_error = 0;
	cache_lookup = old_cache_lookup;
	crt_col_changed = col;

	/* Save declaration specifiers */
	s->dspec[0] = crt_access;
	s->dspec[1] = crt_linkage;
	crt_access = dspec_public;
	crt_state_depth++;
	bad_crt_loc++;
	return;
}


/*
    This routine restores the parser state from the value stored in s.
    Note that there is some attempt at recovering the state following
    some intervening error, particularly with regard to resetting the
    current namespace.
*/

void
restore_state(PARSE_STATE *s)
{
	/* Restore current namespace */
	NAMESPACE ns = s->nspace[0];
	NAMESPACE cns = crt_namespace;
	LIST(NAMESPACE)pns = LIST_stack(s->nstack[0]);
	cache_lookup = old_cache_lookup;
	while (!EQ_list(pns, LIST_stack(namespace_stack))) {
		/* Reset name look-up stack */
		remove_namespace();
	}
	crt_namespace = ns;
	crt_nspace_stack = s->nstack[1];
	local_nspace_stack = s->nstack[2];
	if (!EQ_nspace(ns, cns)) {
		/* Recalculate namespaces if necessary */
		update_namespace();
	}
	templ_namespace = s->nspace[1];

	/* Restore current location */
	crt_loc = s->loc;
	crt_line_changed = 1;
	crt_file_changed = 1;

	/* Restore flag values */
	in_class_defn = s->flag[0];
	in_function_defn = s->flag[1];
	really_in_class_defn = s->flag[2];
	really_in_function_defn = s->flag[3];
	in_declaration = s->flag[4];
	in_template_decl = s->flag[5];
	have_syntax_error = s->flag[6];
	cache_lookup = s->flag[7];
	crt_col_changed = s->flag[8];

	/* Restore declaration specifiers */
	crt_access = s->dspec[0];
	crt_linkage = s->dspec[1];
	crt_state_depth--;
	bad_crt_loc--;
	return;
}


/*
    This routine sets up preprocessing tokens recording the current file
    position immediately following p.
*/

static void
make_loc_tokens(PPTOKEN *p)
{
	PPTOKEN *q = new_pptok();
	if (crt_file_changed) {
		q->tok = lex_builtin_Hfile;
		crt_file_changed = 0;
	} else {
		q->tok = lex_builtin_Hline;
	}
	crt_line_changed = 0;
	q->pp_space = crt_loc.column;
	q->pp_data.loc.line = crt_loc.line;
	q->pp_data.loc.posn = crt_loc.posn;
	q->next = p->next;
	p->next = q;
	return;
}


/*
    This routine adjusts the current line number according to the
    preprocessing tokens p.
*/

PPTOKEN *
read_loc_tokens(PPTOKEN *p)
{
	if (p) {
		int t = p->tok;
		if (t == lex_builtin_Hline) {
			/* Set line number */
			crt_loc.column = p->pp_space;
			crt_loc.line = p->pp_data.loc.line;
			crt_loc.posn = p->pp_data.loc.posn;
			crt_line_changed = 1;
			p = p->next;
		} else if (t == lex_builtin_Hfile) {
			/* Set file name */
			crt_loc.column = p->pp_space;
			crt_loc.line = p->pp_data.loc.line;
			crt_loc.posn = p->pp_data.loc.posn;
			crt_line_changed = 1;
			crt_file_changed = 1;
			p = p->next;
		} else if (crt_col_changed) {
			unsigned long sp = p->pp_space;
			if (sp)crt_loc.column = sp;
		}
	}
	return p;
}


/*
    This routine returns the destructor name for the class name cid or the
    null identifier if cid is not a class name.
*/

#if LANGUAGE_CPP

static IDENTIFIER
find_destr_id(IDENTIFIER cid)
{
	CLASS_TYPE ct = NULL_ctype;
	if (IS_id_class_name_etc(cid)) {
		TYPE t = DEREF_type(id_class_name_etc_defn(cid));
		unsigned tag = TAG_type(t);
		while (tag == type_templ_tag) {
			t = DEREF_type(type_templ_defn(t));
			tag = TAG_type(t);
		}
		if (tag == type_compound_tag) {
			ct = DEREF_ctype(type_compound_defn(t));
		}
	} else {
		ct = find_class(cid);
	}
	if (!IS_NULL_ctype(ct)) {
		/* Find destructor name */
		IDENTIFIER tid = DEREF_id(ctype_destr(ct));
		HASHID nm = DEREF_hashid(id_name(tid));
		tid = DEREF_id(hashid_id(nm));
		set_hashid_loc(tid, cid);
		return tid;
	}
	return NULL_id;
}

#endif


/*
    This routine checks whether the destructor name cid specified using
    nm is legal.  For example, nm might be a typedef-name for the class
    rather than the class itself.  d is the result of the previous call
    to predict_destr.
*/

#if LANGUAGE_CPP

static void
check_destr_id(IDENTIFIER cid, HASHID nm, int d)
{
	if (d <= 2) {
		HASHID cnm = DEREF_hashid(id_name(cid));
		IDENTIFIER tid = DEREF_id(hashid_destr_tid(cnm));
		HASHID tnm = DEREF_hashid(id_name(tid));
		if (!EQ_hashid(tnm, nm)) {
			/* Destructor names don't match */
			IDENTIFIER id = DEREF_id(hashid_id(nm));
			report(crt_loc, ERR_dcl_typedef_destr(id, cnm));
		}
	}
	return;
}

#endif


/*
    This routine reads the next token from the list of all active tokens,
    first_token (see above).  This consists either of advancing crt_token
    along this list, or reading and expanding a new token from the input
    file, appending the result to the list.  The argument store gives the
    context for the token.  The usual cases are EXPAND_NORMAL, indicating
    that the token is to be used and then discarded (allowing first_token
    to be garbage collected up to crt_token), and EXPAND_AHEAD, indicating
    that the token is to be stored for use later.  The value EXPAND_RESCAN
    can be used to force the current token to be rescanned.  Other values
    are used internally.  Note that crt_token is set to the token currently
    being defined during all calls to read_token.  The routine can be
    considerably simplified for C, and because of the performance critical
    nature of the routine this has been done by conditional compilation.

    There is a problem with the look-ahead method in that certain tokens
    are context dependent, and thus may not mean the same in the initial
    scan using expand_token ( EXPAND_AHEAD ) as they do when the same
    tokens are re-analysed using expand_token ( EXPAND_NORMAL ).  This
    is solved by storing all the tokens in these cases and reinterpreting
    them later.  This means in particular than a context dependent
    interpretation such as an identifier being a type name is not set
    in stone by being recorded in the token's tok field.  Instead this
    interpretation is returned, but the identifier is only marked as
    an identifier.

    Note also that SID is always one token ahead of itself.  For example
    in:

		void f ()
		{
		    {
			extern void g ( int ) ;
			g ( 0 ) ;
		    }
		    g ( 1 ) ;
		}

    g goes out of scope after the first close brace, by which time SID has
    already read the following token and resolved it as g.  Thus in these
    cases it is necessary to insert an explicit rescan of the current token
    (with a store value of EXPAND_RESCAN) after the close brace so that
    g is seen not to be in scope.  This problem only ever occurs one
    token ahead of the current token.
*/

int
expand_token(int store)
{
	int t;
	int expand;
#if LANGUAGE_CPP
	NAMESPACE ns = crt_lookup;
#endif
	PPTOKEN *prev_tok = crt_token;
	PPTOKEN *this_tok = prev_tok->next;

	/* A store value of EXPAND_RESCAN means rescan this token */
	if (store == EXPAND_RESCAN) {
		this_tok = prev_tok;
#if LANGUAGE_CPP
		ns = NULL_nspace;
#endif
	}

	/* Get the next token */
start_label:
	if (this_tok == NULL) {
		/* Read the token from the file */
		this_tok = new_pptok();
		this_tok->next = NULL;
		prev_tok->next = this_tok;
		crt_token = this_tok;
		t = read_token();
		update_column();
		this_tok->tok = t;
		if (t <= LAST_COMPLEX_TOKEN) {
			token_parts(t, this_tok);
		}
		/* Don't bother with the space field */

		if (store == EXPAND_NORMAL) {
			/* Garbage collect stored tokens */
			prev_tok->next = free_tokens;
			free_tokens = first_token;
			first_token = this_tok;
		}
		expand = 1;

	} else {
		/* Use a previously stored token */
		t = this_tok->tok;
		if (t == lex_ignore_token) {
			/* Step over any ignored tokens */
			prev_tok = this_tok;
			this_tok = this_tok->next;
			goto start_label;
		} else if (t == lex_builtin_Hline || t == lex_builtin_Hfile) {
			/* Set line number */
			prev_tok = this_tok;
			this_tok = read_loc_tokens(this_tok);
			goto start_label;
		} else if (crt_col_changed) {
			unsigned long sp = this_tok->pp_space;
			if (sp) {
				crt_loc.column = sp;
			}
		}
		crt_token = this_tok;
		expand = 0;
	}
	crt_lookup = NULL_nspace;

	/* Deal with context switch */
	if (store == EXPAND_NORMAL) {
		OPTIONS *opts = prev_opts;
		if (opts != crt_opts) {
			set_mode(opts);
		}
		prev_opts = this_tok->pp_opts;
	}

	/* Analyse the token */
	switch (t) {

	case lex_identifier: {
		/* Deal with identifiers */
		unsigned tag;
		int tt = lex_identifier;

		/* Check for macro expansion */
		HASHID nm = this_tok->pp_data.id.hash;
		IDENTIFIER id = DEREF_id(hashid_id(nm));
expand_label:
		tag = TAG_id(id);
		switch (tag) {

		case id_obj_macro_tag:
		case id_func_macro_tag:
			/* Check for expansion of macros */
			if (expand) {
				PPTOKEN *toks;
				toks = expand_macro(nm, file_loc, 1);
				this_tok->tok = lex_ignore_token;
				this_tok->next = toks;
				prev_tok = this_tok;
				this_tok = toks;
				goto start_label;
			}
			id = DEREF_id(id_alias(id));
			goto expand_label;

		case id_keyword_tag:
			/* Check on keywords */
			this_tok->pp_data.id.use = id;
			t = (int)DEREF_ulong(id_no(id));
			this_tok->tok = t;
			return t;

		case id_iso_keyword_tag:
			/* Check on ISO keywords */
			this_tok->pp_data.id.use = id;
			if (!in_pragma_dir) {
				ERROR err;
				t = (int)DEREF_ulong(id_no(id));
				t = primary_form(t);
				err = ERR_lex_digraph_iso(nm, t);
				if (!IS_NULL_err(err)) {
					report(crt_loc, err);
				}
				this_tok->tok = t;
#if LANGUAGE_CPP
				if (t == lex_compl_H1)goto compl_label;
#endif
				return t;
			}
			break;

		case id_reserved_tag:
			/* Report reserved identifiers */
			if (store == EXPAND_NORMAL && !in_pragma_dir) {
				ERROR err = ERR_lex_key_reserve(nm);
				report(crt_loc, err);
			}
			break;
		}

		/* Perform name look-up */
#if LANGUAGE_CPP
		if (IS_NULL_nspace(ns)) {
			id = find_id(nm);
		} else {
			IDENTIFIER mid = find_qual_id(ns, nm, 0, 0);
			if (!IS_NULL_id(mid))id = mid;
		}
#else
		id = find_op_id(nm);
#endif
		tag = TAG_id(id);

#if LANGUAGE_CPP
		/* Look ahead for following '::' (C++ only) */
		t = expand_token(EXPAND_CHECK_COLON);
		crt_token = this_tok;
#endif

		/* Allow for tokens and templates */
		if (tag == id_token_tag) {
			TOKEN sort = DEREF_tok(id_token_sort(id));
			if (IS_tok_proc(sort)) {
				/* Procedure token application */
#if LANGUAGE_CPP
				/* Following token already read */
#else
				/* Check for following '(' */
				t = expand_token(EXPAND_CHECK_COLON);
				crt_token = this_tok;
#endif
				if (t == lex_open_Hround) {
					PPTOKEN *args = skip_token_args(id);
					id = DEREF_id(id_token_alt(id));
					this_tok->pp_data.tok.id = id;
					this_tok->pp_data.tok.args = args;
					sort = DEREF_tok(tok_proc_res(sort));
					switch (TAG_tok(sort)) {
					case tok_exp_tag:
					case tok_nat_tag:
					case tok_snat_tag: {
						tt = lex_complex_Hexp;
						break;
					}
					case tok_stmt_tag: {
						tt = lex_complex_Hstmt;
						break;
					}
					case tok_member_tag: {
						/* NOT YET IMPLEMENTED */
						tt = lex_complex_Hexp;
						break;
					}
					default : {
						tt = lex_complex_Htype;
#if LANGUAGE_CPP
						/* Check again for following
						 * '::' */
						t = expand_token(EXPAND_CHECK_COLON);
						crt_token = this_tok;
#endif
						break;
					}
					}
				} else {
					tt = DEREF_int(tok_proc_key(sort));
					if (store == EXPAND_NORMAL) {
						if (tt != lex_identifier &&
						    !in_pragma_dir) {
							ERROR err = ERR_cpp_replace_arg_none(nm);
							report(crt_loc, err);
						}
					}
				}
			}

#if LANGUAGE_CPP
		} else if (t == lex_less) {
			/* Check for templates (C++ only) */
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_template) {
				/* Template application */
				PPTOKEN *args;
				if (ds & dspec_implicit) {
					/* Allow for injected template names */
					IDENTIFIER tid = find_template(id, 0);
					if (!IS_NULL_id(tid)) {
						id = tid;
						tag = TAG_id(id);
					}
				}
				args = skip_template_args(id, 0);
				if (store == EXPAND_TEMPLATE) {
					have_template = 1;
				}
				switch (tag) {
				case id_class_name_tag:
					tt = lex_template_Htype;
					goto class_template_lab;
				case id_class_alias_tag:
					tt = lex_complex_Htype;
					goto class_template_lab;
				case id_type_alias_tag: {
					CLASS_TYPE ct = find_class(id);
					tt = lex_complex_Htype;
					if (!IS_NULL_ctype(ct)) {
						goto class_template_lab;
					}
					break;
				}
class_template_lab:	{
				t = expand_token(EXPAND_CHECK_COLON);
				crt_token = this_tok;
				if (t == lex_colon_Hcolon) {
					/* Expand the template class now */
					id = parse_type_template(id, args, 1);
					tt = lex_identifier;
				}
				break;
			}
				case id_enum_name_tag:
				case id_enum_alias_tag:
			tt = lex_complex_Htype;
			break;
				default:
			/* Function template */
			tt = lex_template_Hid;
			break;
				}
				if (tt != lex_identifier) {
					this_tok->pp_data.tok.id = id;
					this_tok->pp_data.tok.args = args;
				}
			} else if (store == EXPAND_TEMPLATE) {
				/* Have 'template id < ... >' */
				PPTOKEN *args = skip_template_args(id, 0);
				this_tok->pp_data.tok.id = id;
				this_tok->pp_data.tok.args = args;
				tt = lex_template_Hid;
				have_template = 1;
			}
#endif
		}

#if LANGUAGE_CPP
		/* Allow for destructors (C++ only) */
		if (store == EXPAND_DESTRUCTOR && t != lex_colon_Hcolon) {
			int level = 2;
			IDENTIFIER cid = id;
			do {
				switch (TAG_id(cid)) {
				case id_class_name_tag:
				case id_class_alias_tag:
				case id_token_tag: {
					IDENTIFIER tid;
					if (tt == lex_template_Htype) {
						this_tok->tok = tt;
						t = lex_destructor_Hname;
						return t;
					}
					tid = find_destr_id(cid);
					if (!IS_NULL_id(tid)) {
						this_tok->pp_data.id.use = tid;
						t = lex_destructor_Hname;
						return t;
					}
					level = 0;
					break;
				}
				default:
					if (level == 2 && !IS_NULL_nspace(ns)) {
						cid = find_id(nm);
						level = 1;
					} else {
						level = 0;
					}
					break;
				}
			} while (level);
		}
#endif

#if LANGUAGE_CPP
		/* Look ahead for further qualifiers (C++ only) */
		if (t == lex_colon_Hcolon) {
			/* Following token is '::' */
			int level = 2;
			IDENTIFIER cid = id;
			do {
				switch (TAG_id(cid)) {
				case id_class_name_tag:
				case id_class_alias_tag:
				case id_nspace_name_tag:
				case id_nspace_alias_tag: {
					/* Have namespace or class name */
					ns = find_namespace(cid);
					if (!IS_NULL_nspace(ns)) {
						crt_lookup = ns;
						t = expand_token(EXPAND_IDENTIFIER);
						switch (t) {
						case lex_full_Hname:
						case lex_colon_Hcolon:
							t = lex_nested_Hname;
							this_tok->tok =
							    lex_ignore_token;
							crt_token->tok = t;
							return t;
						case lex_full_Hname_Hstar:
							t = lex_nested_Hname_Hstar;
							this_tok->tok =
							    lex_ignore_token;
							crt_token->tok = t;
							return t;
						}
						crt_token = this_tok;
					}
					level = 0;
					break;
				}

				default: {
					/* Look up namespace or class name */
					if (level == 2) {
						CLASS_TYPE ct = find_class(cid);
						if (!IS_NULL_ctype(ct)) {
							cid = DEREF_id(ctype_name(ct));
						} else {
							if (IS_NULL_nspace(ns)) {
								cid = find_type_id(nm, 3);
							} else {
								cid = find_qual_id(ns, nm, 0, 3);
							}
						}
						if (IS_NULL_id(cid)) {
							level = 0;
						} else {
							level = 1;
						}
					} else {
						level = 0;
					}
					break;
				}
				}
			} while (level);
		}
#endif

		/* Deal with context dependent identifiers */
		switch (tag) {

#if LANGUAGE_CPP
		case id_class_name_tag:
		case id_enum_name_tag:
			/* Type names (C++ only) */
			t = lex_type_Hname;
			break;
#endif
		case id_class_alias_tag:
		case id_enum_alias_tag:
		case id_type_alias_tag:
			/* Type aliases */
			t = lex_type_Hname;
			break;
#if LANGUAGE_CPP
		case id_nspace_name_tag:
		case id_nspace_alias_tag:
			/* Namespace names (C++ only) */
			t = lex_namespace_Hname;
			break;
#endif
		case id_token_tag: {
			/* Token names */
			TOKEN sort = DEREF_tok(id_token_sort(id));
			if (IS_tok_stmt(sort)) {
				t = lex_statement_Hname;
			} else {
				t = lex_identifier;
			}
			break;
		}

		default:
			/* Other names */
			t = lex_identifier;
			break;
		}
		if (tt == lex_identifier) {
			this_tok->pp_data.id.use = id;
		} else {
			this_tok->tok = tt;
			t = tt;
		}
		break;
	}

#if LANGUAGE_CPP
	case lex_colon_Hcolon: {
		/* Deal with qualified names (C++ only) */
		int nt;
		unsigned long depth;
		if (store == EXPAND_CHECK_COLON) {
			/* Look ahead for '::' */
			return t;
		} else if (IS_NULL_nspace(ns)) {
			/* Initial '::' */
			ns = global_namespace;
			depth = 0;
		} else if (store == EXPAND_IDENTIFIER) {
			/* Following a namespace identifier */
			depth = crt_lookup_depth + 1;
		} else {
			/* Badly placed '::' */
			return t;
		}

		/* Look ahead to further tokens */
		crt_lookup = ns;
		crt_lookup_depth = depth;
		nt = expand_token(EXPAND_COLON_COLON);
		crt_lookup_depth = 0;
		if (nt == lex_nested_Hname) {
			nt = lex_full_Hname;
			this_tok->tok = lex_ignore_token;
			crt_token->tok = nt;
			return nt;
		}
		if (nt == lex_nested_Hname_Hstar) {
			if (crt_token == this_tok->next) {
				IGNORE check_value(OPT_VAL_scope_qualifiers,
						   depth);
			}
			nt = lex_full_Hname_Hstar;
			this_tok->tok = lex_ignore_token;
			crt_token->tok = nt;
			return nt;
		}
		IGNORE check_value(OPT_VAL_scope_qualifiers, depth);
		this_tok->pp_data.ns = ns;
		crt_lookup = ns;
		crt_token = this_tok;
		break;
	}
#endif

#if LANGUAGE_CPP
	case lex_full_Hname:
	case lex_nested_Hname: {
		/* Deal with stored nested names (C++ only) */
		int nt;
		ns = this_tok->pp_data.ns;
		crt_lookup = ns;
		crt_lookup_depth++;
		nt = expand_token(EXPAND_COLON_COLON);
		crt_lookup_depth = 0;
		if (nt == lex_nested_Hname) {
			this_tok->tok = lex_ignore_token;
			crt_token->tok = t;
			return nt;
		}
		if (nt == lex_nested_Hname_Hstar) {
			if (t == lex_full_Hname)nt = lex_full_Hname_Hstar;
			this_tok->tok = lex_ignore_token;
			crt_token->tok = nt;
			return nt;
		}
		crt_lookup = ns;
		crt_token = this_tok;
		break;
	}
#endif

#if LANGUAGE_CPP
	case lex_star:
		/* Deal with pointer to members (C++ only) */
		if (store == EXPAND_COLON_COLON && crt_lookup_depth) {
			IDENTIFIER cid = DEREF_id(nspace_name(ns));
			t = lex_nested_Hname_Hstar;
			this_tok->tok = t;
			this_tok->pp_data.id.use = cid;
		}
		break;
#endif

#if LANGUAGE_CPP
	case lex_compl_H1:
compl_label:
		/* Deal with destructors (C++ only) */
		if (store != EXPAND_COLON_COLON) {
			int nt;
			crt_lookup = ns;
			nt = expand_token(EXPAND_DESTRUCTOR);
			if (nt == lex_destructor_Hname) {
				int d = predict_destr(ns);
				if (d) {
					this_tok->tok = lex_ignore_token;
					this_tok = crt_token;
					t = this_tok->tok;
					if (t == lex_template_Htype) {
						/* Template class destructors */
						IDENTIFIER id =
						    this_tok->pp_data.tok.id;
						PPTOKEN *args =
						    this_tok->pp_data.tok.args;
						HASHID nm =
						    DEREF_hashid(id_name(id));
						id = parse_type_template(id,
									 args,
									 1);
						id = find_destr_id(id);
						this_tok->pp_data.id.hash = nm;
						this_tok->pp_data.id.use = id;
					} else {
						/* Simple destructors */
						IDENTIFIER id =
						    this_tok->pp_data.id.use;
						HASHID nm =
						    this_tok->pp_data.id.hash;
						check_destr_id(id, nm, d);
					}
					this_tok->tok = nt;
					return nt;
				}
			}
			crt_token = this_tok;
		}
		break;
#endif

	case lex_integer_Hlit: {
		/* Deal with integer and floating point literals */
		int nt;
		int pn = pragma_number;
		OPTIONS *opts = crt_opts;
		OPTIONS *nopts = this_tok->pp_opts;
		string n = this_tok->pp_data.text;
		if (opts != nopts)set_mode(nopts);
		this_tok->pp_data.exp = make_literal_exp(n, &nt, pn);
		this_tok->tok = nt;
		if (opts != nopts)set_mode(opts);
		t = nt;
		break;
	}

	case lex_char_Hlit:
	case lex_wchar_Hlit: {
		/* Deal with character literals */
		STRING s;
		OPTIONS *opts = crt_opts;
		OPTIONS *nopts = this_tok->pp_opts;
		string sb = this_tok->pp_data.str.start;
		string se = this_tok->pp_data.str.end;
		if (opts != nopts)set_mode(nopts);
		s = new_string_lit(sb, se, t);
		if (t == lex_char_Hlit) {
			t = lex_char_Hexp;
		} else {
			t = lex_wchar_Hexp;
		}
		this_tok->pp_data.exp = make_string_exp(s);
		this_tok->tok = t;
		if (opts != nopts)set_mode(opts);
		break;
	}

	case lex_string_Hlit:
	case lex_wstring_Hlit: {
		/* Deal with string literals */
		int nt;
		STRING s;
		OPTIONS *opts = crt_opts;
		OPTIONS *nopts = this_tok->pp_opts;
		string sb = this_tok->pp_data.str.start;
		string se = this_tok->pp_data.str.end;
		if (opts != nopts) {
			set_mode(nopts);
		}
		s = new_string_lit(sb, se, t);

		/* Concatenate adjacent strings */
		nt = expand_token(EXPAND_STRING);
		if (nt == lex_string_Hlit || nt == lex_wstring_Hlit) {
			/* Combine the following string with this one */
			if (nt != t) {
				/* String types don't match */
				report(crt_loc, ERR_lex_string_concat());
				t = lex_wstring_Hlit;
			}
			s = concat_string_lit(s, crt_token->pp_data.strlit);
			crt_token->tok = lex_ignore_token;
		}
		crt_token = this_tok;
		if (store == EXPAND_STRING) {
			/* Continue concatenation */
			this_tok->pp_data.strlit = s;
		} else {
			/* Transform string literal into expression */
			if (t == lex_string_Hlit) {
				t = lex_string_Hexp;
			} else {
				t = lex_wstring_Hexp;
			}
			this_tok->pp_data.exp = make_string_exp(s);
			this_tok->tok = t;
		}
		if (opts != nopts) {
			set_mode(opts);
		}
		break;
	}

	case lex_ellipsis:
		/* Ellipses */
		if (store == EXPAND_NORMAL) {
			OPTION opt = option(OPT_ellipsis_ident);
			NAMESPACE cns = crt_namespace;
			if (opt != OPTION_DISALLOW && IS_nspace_block(cns)) {
				t = lex_ellipsis_Hexp;
				this_tok->tok = t;
			}
		}
		break;

	case lex_hash_H2:
	case lex_hash_Hhash_H2:
	case lex_open_Hbrace_H2:
	case lex_open_Hsquare_H2:
	case lex_close_Hbrace_H2:
	case lex_close_Hsquare_H2:
		/* Digraphs */
		t = get_digraph(t);
		this_tok->tok = t;
		break;

	case lex_and_H2:
	case lex_and_Heq_H2:
	case lex_compl_H2:
	case lex_logical_Hand_H2:
	case lex_logical_Hor_H2:
	case lex_not_H2:
	case lex_not_Heq_H2:
	case lex_or_H2:
	case lex_or_Heq_H2:
	case lex_xor_H2:
	case lex_xor_Heq_H2: {
		/* ISO keywords */
		int tt;
		IDENTIFIER id = this_tok->pp_data.id.use;
		t = (int)DEREF_ulong(id_no(id));
		tt = primary_form(t);
		if (tt != t) {
			HASHID nm;
			if (in_pragma_dir) {
				break;
			}
			nm = this_tok->pp_data.id.hash;
			report(crt_loc, ERR_lex_digraph_iso(nm, tt));
			t = tt;
		}
		this_tok->tok = t;
#if LANGUAGE_CPP
		if (t == lex_compl_H1) {
			goto compl_label;
		}
#endif
		break;
	}

	case lex_unknown: {
		/* Unknown characters */
		unsigned long u;
		int ch = CHAR_SIMPLE;
		u = get_multi_char(this_tok->pp_data.buff, &ch);
		if (ch == CHAR_SIMPLE) {
			if (is_legal_char(u)) {
				if (!is_white_char(u)) {
					break;
				}
			} else {
				int c = (int)u;
				report(crt_loc, ERR_lex_pptoken_unknown(c));
			}
		} else {
			report(crt_loc, ERR_lex_pptoken_unicode(u));
		}
		this_tok->tok = lex_ignore_token;
		t = expand_token(store);
		break;
	}
	}
	return t;
}


/*
    This routine is a cut-down version of expand_token with only the macro
    expansion and keyword actions.  This is for use with the stand-alone
    preprocessor and in the rewriting rules.
*/

int
expand_preproc(int store)
{
	int t;
	int expand;
	PPTOKEN *prev_tok = crt_token;
	PPTOKEN *this_tok = prev_tok->next;

	/* Get the next token */
start_label:
	if (this_tok == NULL) {
		/* Read the token from the file */
		this_tok = new_pptok();
		this_tok->next = NULL;
		prev_tok->next = this_tok;
		crt_token = this_tok;
		t = read_token();
		update_column();
		this_tok->tok = t;
		if (t <= LAST_COMPLEX_TOKEN) {
			token_parts(t, this_tok);
		}

		if (store == EXPAND_NORMAL) {
			/* Garbage collect stored tokens */
			this_tok->pp_space = 0;
			prev_tok->next = free_tokens;
			free_tokens = first_token;
			first_token = this_tok;
		} else {
			this_tok->pp_space = crt_loc.column;
			if (crt_line_changed) {
				/* Record file position */
				make_loc_tokens(prev_tok);
			}
		}
		expand = 1;

	} else {
		/* Use a previously stored token */
		if (this_tok->pp_space) {
			/* Increase space count if necessary */
			if (!crt_line_changed) {
				crt_spaces++;
			}
			if (store == EXPAND_AHEAD) {
				this_tok->pp_space = 0;
			}
		}
		t = this_tok->tok;
		if (t == lex_ignore_token) {
			/* Step over any ignored tokens */
			prev_tok = this_tok;
			this_tok = this_tok->next;
			goto start_label;
		}
		crt_token = this_tok;
		expand = 0;
	}

	/* Deal with context switch */
	if (store == EXPAND_NORMAL) {
		OPTIONS *opts = prev_opts;
		if (opts != crt_opts) {
			set_mode(opts);
		}
		prev_opts = this_tok->pp_opts;
	}

	/* Deal with identifiers */
	if (t == lex_identifier) {
		HASHID nm = this_tok->pp_data.id.hash;
		IDENTIFIER id = DEREF_id(hashid_id(nm));
expand_label:
		switch (TAG_id(id)) {
		case id_obj_macro_tag:
		case id_func_macro_tag:
			if (expand) {
				PPTOKEN *toks = expand_macro(nm, file_loc, 1);
				if (!crt_line_changed)crt_spaces++;
				this_tok->tok = lex_ignore_token;
				this_tok->next = toks;
				prev_tok = this_tok;
				this_tok = toks;
				goto start_label;
			}
			id = DEREF_id(id_alias(id));
			goto expand_label;
		case id_keyword_tag:
			if (store == EXPAND_AHEAD) {
				t = (int)DEREF_ulong(id_no(id));
				this_tok->tok = t;
			}
			break;
		case id_iso_keyword_tag:
			if (store == EXPAND_AHEAD) {
				t = (int)DEREF_ulong(id_no(id));
				if (t >= FIRST_SYMBOL && t <= LAST_SYMBOL) {
					/* Will be reinterpreted later */
					t = lex_and_H2;
				}
				this_tok->tok = t;
			}
			break;
		}
		this_tok->pp_data.id.use = id;
	}
	return t;
}


/*
    This routine is called after the optional 'template' at the start of
    a qualified identifier or a field member selector.  It forces the
    following identifier to be treated as a template-id even if it doesn't
    seem to be one.
*/

void
rescan_template(NAMESPACE ns)
{
	PPTOKEN *p = crt_token;
	crt_lookup = ns;
	have_template = 0;
	IGNORE expand_token(EXPAND_TEMPLATE);
	if (!have_template) {
		/* Didn't read template-id */
		report(crt_loc, ERR_temp_names_bad());
	}
	crt_token = p;
	crt_lookup = ns;
	return;
}
