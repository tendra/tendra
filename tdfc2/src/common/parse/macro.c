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

#include "config.h"
#include "version.h"

#include "system.h"
#include "c_types.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "nspace_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "buffer.h"
#include "char.h"
#include "dump.h"
#include "file.h"
#include "hash.h"
#include "lex.h"
#include "literal.h"
#include "macro.h"
#include "namespace.h"
#include "predict.h"
#include "preproc.h"
#include "print.h"
#include "symbols.h"
#include "syntax.h"
#include "ustring.h"
#include "xalloc.h"


/*
    All the free lexical tokens are formed into a list.
*/

PPTOKEN *free_tokens = NULL;
static LIST(PPTOKEN_P)alloc_tokens = NULL_list(PPTOKEN_P);


/*
    This routine allocates a new token from the list free_tokens.
*/

PPTOKEN *
new_pptok(void)
{
	PPTOKEN *p = free_tokens;
	if (p == NULL) {
		PPTOKEN *q;
		int i, n = 2000;
		p = xmalloc_nof(PPTOKEN, n);
		CONS_pptok(p, alloc_tokens, alloc_tokens);
		q = p;
		for (i = 1; i < n; i++) {
			q->next = q + 1;
			q++;
		}
		q->next = NULL;
	}
	free_tokens = p->next;
	p->pp_opts = real_opts;
	return p;
}


/*
    This macro frees the single token P by adding it to the list of all
    free tokens.
*/

#define free_pptok(P)			\
    {					\
	(P)->next = free_tokens;	\
	free_tokens = (P);		\
    }


/*
    This routine adds the list of tokens p to the list of all free tokens.
*/

void
free_tok_list(PPTOKEN *p)
{
	PPTOKEN *q = p;
	if (q == NULL) {
		return;
	}
	while (q->next) {
		q = q->next;
	}
	q->next = free_tokens;
	free_tokens = p;
	return;
}


/*
    This routine frees all the space allocated for preprocessing tokens.
    It should only be called after the input has been completely processed.
*/

void
term_macros(void)
{
	LIST(PPTOKEN_P)p = alloc_tokens;
	while (!IS_NULL_list(p)) {
		PPTOKEN *q;
		DESTROY_CONS_pptok(destroy, q, p, p);
		xfree_nof(q);
	}
	alloc_tokens = p;
	free_tokens = NULL;
	return;
}


/*
    This macro copies the contents of the token with token value T and data
    Q into P.
*/

#define copy_pptok(P, T, Q)		\
    {					\
	(P)->tok = (T);			\
	(P)->pp_data = (Q)->pp_data;	\
	(P)->pp_opts = (Q)->pp_opts;	\
	(P)->pp_space = (Q)->pp_space;	\
    }


/*
    This routine assigns the token components for the token t, which has
    just been read from the input file (or faked on occasions - these are
    indicated) into p.  It is only necessary to call this routine is T is
    less than or equal to LAST_COMPLEX_TOKEN (defined in symbols.h).  If any
    cases are added to this routine then it may be necessary to change the
    value of this macro.
*/

void
token_parts(int t, PPTOKEN *p)
{
	switch (t) {
	case lex_identifier: {
		/* Identifiers */
		HASHID nm = token_hashid;
		IDENTIFIER id = DEREF_id(hashid_id(nm));
		p->pp_data.id.hash = nm;
		p->pp_data.id.use = id;
		break;
	}
	case lex_char_Hlit:
	case lex_string_Hlit:
	case lex_wchar_Hlit:
	case lex_wstring_Hlit: {
		/* String and character literals */
		string s1 = token_buff.start;
		gen_size n = (gen_size)(token_buff.posn - s1);
		string s2;
		if (n < 2) {
			/* Optimise for small strings */
			s2 = xustrcpy(s1);
		} else {
			s2 = xustr(n + 1);
			xumemcpy(s2, s1, n);
			s2[n] = 0;
		}
		p->pp_data.str.start = s2;
		p->pp_data.str.end = s2 + n;
		break;
	}
	case lex_integer_Hlit:
		/* Integer and floating-point literals */
		p->pp_data.text = xustrcpy(token_buff.start);
		break;
	case lex_hash_Hif:
	case lex_hash_Helif:
		/* Target dependent conditionals */
		p->pp_data.exp = crt_hash_if_exp;
		break;
	case lex_unknown: {
		/* Unknown characters */
		int i;
		string s1 = token_buff.start;
		string s2 = p->pp_data.buff;
		assert(MULTI_WIDTH <= sizeof(p->pp_data.buff));
		for (i = 0; i < MULTI_WIDTH; i++)s2[i] = s1[i];
		break;
	}
	}
	return;
}


/*
    This routine removes any ignored tokens from the list tok, returning
    the result.
*/

PPTOKEN *
clean_tok_list(PPTOKEN *toks)
{
	unsigned long sp = 0;
	PPTOKEN p0, *p = &p0;
	PPTOKEN *q;
	p->next = toks;
	while (q = p->next, q != NULL) {
		if (q->tok == lex_ignore_token) {
			sp |= q->pp_space;
			p->next = q->next;
			free_pptok(q);
			q = p->next;
			if (q == NULL) {
				break;
			}
		} else {
			if (sp) {
				q->pp_space |= sp;
				sp = 0;
			}
		}
		p = q;
	}
	return p0.next;
}


/*
    This routine reads the sequence of preprocessing tokens comprising a
    preprocessing directive (for example, a macro definition).  If t1 is
    not lex_ignore_token then it is taken to be the first token in the
    definition, similarly tn gives the last token.
*/

PPTOKEN *
read_line(int t1, int tn)
{
	int t = t1;
	unsigned long sp = 0;
	PPTOKEN dummy_tok, *this_tok = &dummy_tok;
	if (t == lex_ignore_token) {
		t = read_token();
		update_column();
		if (in_preproc_dir) {
			preproc_loc = crt_loc;
		}
	}
	while (t != lex_newline && t != lex_eof) {
		this_tok->next = new_pptok();
		this_tok = this_tok->next;
		this_tok->tok = t;
		if (t <= LAST_COMPLEX_TOKEN) {
			token_parts(t, this_tok);
		}
		this_tok->pp_space = (sp & WHITE_MASK);
		sp = skip_white(0);
		t = read_token();
		update_column();
		if (in_preproc_dir) {
			preproc_loc = crt_loc;
		}
	}
	if (tn != lex_ignore_token) {
		this_tok->next = new_pptok();
		this_tok = this_tok->next;
		this_tok->tok = tn;
		token_parts(tn, this_tok);
		this_tok->pp_space = (sp & WHITE_MASK);
	}
	this_tok->next = NULL;
	if (in_preproc_dir) {
		IGNORE skip_to_end();
	}
	return dummy_tok.next;
}


/*
    This routine copies the list of tokens toks, excluding any ignored
    tokens.
*/

static PPTOKEN *
copy_tok_list(PPTOKEN *toks)
{
	PPTOKEN *ptr_tok;
	PPTOKEN dummy_tok, *this_tok = &dummy_tok;
	for (ptr_tok = toks; ptr_tok != NULL; ptr_tok = ptr_tok->next) {
		int t = ptr_tok->tok;
		if (t != lex_ignore_token) {
			this_tok->next = new_pptok();
			this_tok = this_tok->next;
			copy_pptok(this_tok, t, ptr_tok);
		}
	}
	this_tok->next = NULL;
	return dummy_tok.next;
}


/*
    This routine turns the list of tokens toks into a string.  The result
    is built up in token_buff.  If esc is true then any '"' (or whatever
    the value of quote is) and '\' characters in string and character
    literals (including the initial and terminating quotes) are preceded
    by a '\'.  This routine is used in the implementation of the # operator,
    in macro #include directives and a couple of other preprocessing
    directives.  It returns 1 to indicate a valid string.
*/

int
quote_tok_list(PPTOKEN *toks, int esc, int quote)
{
	int res = 1;
	string st, se;
	int started = 0;
	int escaped = 0;
	PPTOKEN *ptr_tok;
	character qo = (character)quote;
	BUFFER *bf = clear_buffer(&token_buff, NIL(FILE));

	/* Scan through tokens */
	for (ptr_tok = toks; ptr_tok != NULL; ptr_tok = ptr_tok->next) {
		character p, q;
		int t = ptr_tok->tok;
		if (t == lex_ignore_token) {
			continue;
		}

		/* Print initial space if necessary */
		if (ptr_tok->pp_space && started) {
			bfputc(bf, char_space);
		}

		/* Find the token name */
		switch (t) {
		case lex_identifier: {
			/* Identifiers */
			HASHID nm = ptr_tok->pp_data.id.hash;
			st = DEREF_string(hashid_name_etc_text(nm));
			bfputs(bf, st);
			break;
		}
		case lex_integer_Hlit:
			/* Integer and floating-point literals */
			st = ptr_tok->pp_data.text;
			bfputs(bf, st);
			break;
		case lex_char_Hlit:
			/* Character literals */
			p = 0;
			q = char_single_quote;
string_label:
			st = ptr_tok->pp_data.str.start;
			se = ptr_tok->pp_data.str.end;

			/* Prefix and opening quote */
			if (p) {
				bfputc(bf, (int)p);
			}
			if (esc && q == qo) {
				bfputc(bf, char_backslash);
			}
			bfputc(bf, (int)q);

			/* Copy string */
			while (st != se) {
				character c = *(st++);
				if (c == qo || c == char_backslash) {
					/* Escaped characters */
					if (esc) {
						bfputc(bf, char_backslash);
					}
				}
				bfputc(bf, (int)c);
			}

			/* Closing quote */
			if (esc && q == qo) {
				bfputc(bf, char_backslash);
			}
			bfputc(bf, (int)q);
			break;
		case lex_wchar_Hlit:
			/* Wide character literals */
			p = char_L;
			q = char_single_quote;
			goto string_label;
		case lex_string_Hlit:
			/* String literals */
			p = 0;
			q = char_quote;
			goto string_label;
		case lex_wstring_Hlit:
			/* Wide string literals */
			p = char_L;
			q = char_quote;
			goto string_label;
		case lex_unknown: {
			/* Unknown characters */
			unsigned long u;
			int ch = CHAR_SIMPLE;
			u = get_multi_char(ptr_tok->pp_data.buff, &ch);
			if (ch == CHAR_SIMPLE) {
				bfputc(bf, (int)u);
			} else {
				print_char(u, ch, 0, bf);
			}
			break;
		}
		case lex_macro_Harg: {
			/* Macro parameters */
			HASHID nm = ptr_tok->pp_data.par.hash;
			st = DEREF_string(hashid_name_etc_text(nm));
			bfputs(bf, st);
			break;
		}
		default:
			/* Symbols */
			st = token_name(t);
			bfputs(bf, st);
			break;
		}
		started = 1;
	}

	/* End of string */
	bfputc(bf, 0);
	bf->posn--;

	/* Check for legal strings */
	st = bf->start;
	se = bf->posn;
	while (st != se) {
		if (escaped) {
			escaped = 0;
		} else {
			character c = *st;
			if (c == qo) {
				res = 0;
			}
			if (c == char_backslash) {
				escaped = 1;
			}
		}
		st++;
	}
	if (escaped) {
		res = 0;
	}
	return res;
}


/*
    This routine concatenates the two tokens p and q into a single token.
    This is used to implement the ## operator.  If the result is a valid
    preprocessing token then p is overwritten by the result and 1 is
    returned.  Otherwise p and q are unchanged and 0 is returned.
*/

static int
concat_pptoks(PPTOKEN *p, PPTOKEN *q)
{
	int a = p->tok;
	int b = q->tok;
	unsigned long sa = p->pp_space;
	unsigned long sb = q->pp_space;
	p->pp_space = (sa | sb);
	q->pp_space = 0;
	if (a >= FIRST_SYMBOL && a <= LAST_SYMBOL) {
		if (b >= FIRST_SYMBOL && b <= LAST_SYMBOL) {
			/* Two symbols may combine to give another symbol */
			int c;
			string s = token_buff.start;
			ustrcpy_v(s, token_name(a));
			ustrcpy_v(s + ustrlen(s), token_name(b));
			for (c = FIRST_SYMBOL; c <= LAST_SYMBOL; c++) {
				if (ustreq(s, token_name(c))) {
					/* Token found - check options */
					p->tok = c;
					if (c >= FIRST_C_SYMBOL &&
					    c <= LAST_C_SYMBOL) {
						return 1;
					}
#if LANGUAGE_CPP
					if (c >= FIRST_CPP_SYMBOL &&
					    c <= LAST_CPP_SYMBOL) {
						return 1;
					}
#endif
					if (c >= FIRST_EXTRA_SYMBOL &&
					    c <= LAST_EXTRA_SYMBOL) {
						if (allow_extra_symbols) {
							return 1;
						}
					}
					if (c >= FIRST_DIGRAPH &&
					    c <= LAST_DIGRAPH) {
						if (allow_digraphs) {
							return 1;
						}
					}
					p->tok = a;
				}
			}
			return 0;

		} else if (a == lex_dot && b == lex_integer_Hlit) {
			/* A dot may start a number */
			string s = q->pp_data.text;
			if (s[0] == char_dot) {
				return 0;
			}
			p->tok = lex_integer_Hlit;
			p->pp_data.text = xustrcat(token_name(a), s);
			return 1;

		} else if (a == lex_backslash && b == lex_identifier) {
			/* A backslash may start a universal character */
			/* NOT YET IMPLEMENTED */
			/* EMPTY */
		}

	} else if (a == lex_identifier) {
		HASHID nm = p->pp_data.id.hash;
		string s = DEREF_string(hashid_name_etc_text(nm));
		if (b == lex_identifier) {
			/* Two identifiers give another identifier */
			HASHID nm2 = q->pp_data.id.hash;
			string s2 = DEREF_string(hashid_name_etc_text(nm2));
			s = xustrcat(s, s2);
			nm = lookup_name(s, hash(s), 2, lex_identifier);
			p->pp_data.id.hash = nm;
			p->pp_data.id.use = DEREF_id(hashid_id(nm));
			return 1;

		} else if (b == lex_integer_Hlit) {
			/* An identifier and a number may give an identifier */
			character c;
			string n = q->pp_data.text;
			while (c = *(n++), c != 0) {
				if (c == char_dot || c == char_plus ||
				    c == char_minus) {
					/* The number must be entirely
					 * alphanumeric */
					return 0;
				}
			}
			s = xustrcat(s, q->pp_data.text);
			nm = lookup_name(s, hash(s), 2, lex_identifier);
			p->pp_data.id.hash = nm;
			p->pp_data.id.use = DEREF_id(hashid_id(nm));
			return 1;

		} else if (s[0] == char_L && s[1] == 0) {
			/* An L may start a wide character or string */
			if (b == lex_char_Hlit) {
				p->tok = lex_wchar_Hlit;
				p->pp_data.str.start = q->pp_data.str.start;
				p->pp_data.str.end = q->pp_data.str.end;
				return 1;
			} else if (b == lex_string_Hlit) {
				p->tok = lex_wstring_Hlit;
				p->pp_data.str.start = q->pp_data.str.start;
				p->pp_data.str.end = q->pp_data.str.end;
				return 1;
			}
		}

	} else if (a == lex_integer_Hlit) {
		string s = p->pp_data.text;
		if (b == lex_identifier) {
			/* A number followed by an identifier is a number */
			HASHID nm = q->pp_data.id.hash;
			string s2 = DEREF_string(hashid_name_etc_text(nm));
			p->pp_data.text = xustrcat(s, s2);
			return 1;

		} else if (b == lex_integer_Hlit) {
			/* Two numbers form another number */
			string s2 = q->pp_data.text;
			p->pp_data.text = xustrcat(s, s2);
			return 1;

		} else if (b == lex_dot || b == lex_ellipsis) {
			/* A number followed by a sequence of dots is a
			 * number */
			p->pp_data.text = xustrcat(s, token_name(b));
			return 1;

		} else if (b == lex_plus || b == lex_minus) {
			/* A sign may terminate a number after e or E */
			unsigned n = (unsigned)ustrlen(s) - 1;
			if (s[n] == char_e || s[n] == char_E) {
				p->pp_data.text = xustrcat(s, token_name(b));
				return 1;
			}
		}
	}
	return 0;
}


/*
    This dummy location represents tokens read directly from the input file.
    If present, it will always be the last element of a list of token
    locations.
*/

static PPTOKEN *dummy_loc_toks = NULL;
static TOKEN_LOC dummy_loc = { &dummy_loc_toks, NULL };
TOKEN_LOC *file_loc = &dummy_loc;


/*
    The functions expand_macro, expand_toks and expand_tok_list are defined
    recursively.  This gives the necessary forward declarations.
*/

static PPTOKEN *expand_toks(PPTOKEN *, TOKEN_LOC *, int);


/*
    This routine handles the old style stringising for the definition defn
    for the given macro.  Argument replacement has already been performed
    on defn.  If this facility is enabled then in macro definitions of the
    form:

		#define f( X )	"X"

    quotes are classified as unknown characters rather than string
    terminators.  This means that the X is recognised as a macro parameter
    and is replaced during argument replacement.  The job of this routine
    is to spot these unrecognised quotes and turn them into proper strings.
*/

PPTOKEN *
recognise_strings(PPTOKEN *defn, HASHID macro, int act)
{
	PPTOKEN *this_tok = defn;
	PPTOKEN *last_tok = defn;
	while (this_tok != NULL) {
		if (this_tok->tok == lex_unknown) {
			unsigned long u;
			int ch = CHAR_SIMPLE;
			character qo = char_question;
			u = get_multi_char(this_tok->pp_data.buff, &ch);
			if (ch == CHAR_SIMPLE) {
				qo = (character)u;
			}
			if (qo == char_quote || qo == char_single_quote) {
				/* Start of string */
				int t;
				int escaped = 0;
				PPTOKEN *next_tok = this_tok->next;
				PPTOKEN *ptr_tok = next_tok;
				while (ptr_tok != NULL) {
					t = ptr_tok->tok;
					if (t == lex_macro_Harg) {
						HASHID nm =
						    ptr_tok->pp_data.par.hash;
						ERROR err =
						    ERR_cpp_stringize_old(nm,
									 macro);
						report(preproc_loc, err);
					}
					if (escaped) {
						escaped = 0;
					} else if (t == lex_unknown) {
						character qc = char_question;
						u = get_multi_char(ptr_tok->pp_data.buff, &ch);
						if (ch == CHAR_SIMPLE) {
							qc = (character)u;
						}
						if (qc == qo) {
							break;
						}
						if (qc == char_backslash) {
							escaped = 1;
						}
					}
					ptr_tok = ptr_tok->next;
				}
				if (act) {
					if (ptr_tok == NULL) {
						/* No closing quote */
						report(crt_loc,
						  ERR_cpp_stringize_bad(macro));
						this_tok->next = NULL;
					} else {
						ptr_tok->tok = lex_ignore_token;
						this_tok->next = ptr_tok->next;
						ptr_tok->next = NULL;
					}

					/* Form the string */
					if (!quote_tok_list(next_tok, 0,
							    (int)qo)) {
						report(crt_loc,
						  ERR_cpp_stringize_bad(macro));
					}
					t = (qo == char_quote ?
					     lex_string_Hlit : lex_char_Hlit);
					this_tok->tok = t;
					token_parts(t, this_tok);
					free_tok_list(next_tok);

					/* Check for wide strings */
					if (last_tok->tok == lex_identifier) {
						string s;
						HASHID nm =
						    last_tok->pp_data.id.hash;
						s = DEREF_string(hashid_name_etc_text(nm));
						if (s[0] == char_L &&
						    s[1] == 0) {
							if (t ==
							    lex_string_Hlit) {
								t = lex_wstring_Hlit;
							} else {
								t = lex_wchar_Hlit;
							}
							copy_pptok(last_tok, t,
								   this_tok);
							last_tok->next =
							    this_tok->next;
							free_pptok(this_tok);
							this_tok = last_tok;
						}
					}
				}
			}
		}
		last_tok = this_tok;
		this_tok = this_tok->next;
	}
	return defn;
}


/*
    This routine handles any ## operators in the definition defn of the
    given macro.  Note that any initial or terminal ## operators have
    already been reported.
*/

static PPTOKEN *
process_concat(PPTOKEN *defn, HASHID macro)
{
	PPTOKEN *this_tok;
	while (defn && defn->tok == lex_hash_Hhash_Hop) {
		/* Check for initial ## */
		this_tok = defn;
		defn = defn->next;
		free_pptok(this_tok);
	}
	this_tok = defn;
	while (this_tok != NULL) {
		PPTOKEN *next_tok = this_tok->next;
		if (next_tok == NULL) {
			break;
		}
		if (next_tok->tok == lex_hash_Hhash_Hop) {
			/* Delete the ## */
			this_tok->next = next_tok->next;
			free_pptok(next_tok);

			/* Check for terminal ## */
			if (this_tok->next == NULL) {
				break;
			}

			/* Do the token concatenation */
			if (concat_pptoks(this_tok, this_tok->next)) {
				/* Delete the second argument if successful */
				next_tok = this_tok->next;
				this_tok->next = next_tok->next;
				free_pptok(next_tok);
			} else {
				report(crt_loc, ERR_cpp_concat_bad(macro));
			}
			/* Now reprocess this_tok */
		} else {
			this_tok = next_tok;
		}
	}
	return defn;
}


/*
    This macro defines the maximum number of macro parameters which
    expand_macro can handle without having to allocate temporary space
    to hold them.  With allocation the number of parameters is unlimited.
*/

#define MAX_MACRO_PARAMS	256


/*
    This routine expands the macro given by the hash table entry macro.
    The argument locs gives a list of locations where macro arguments can
    be read from.  locs will never be NULL.  The argument complete is true
    to indicate that this is a complete macro expansion, and that any
    argument errors should be reported.  If locs contains file_loc then
    complete will always be true.  When reading from file_loc we always
    set in_preproc_dir to 2 to make read_token return lex_eof at the end
    of each file, rather than automatically reverting to the including
    file, and to cause it to ignore any preprocessing directives.

    Note that the entry for the macro in the hash table is marked during
    expansion to prevent recursive expansions.  Several points concerning
    macro expansion are undefined; in this implementation:

	1.  Firstly, # operators are evaluated from left to right;
	2.  Secondly, ## operators are evaluated from left to right;
	3.  If a ## b is not a valid preprocessing token then it is
	    resolved to a b;
	4.  A # operator in a function-like macro which is not followed
	    by a macro argument is ignored (it is left as # in object-like
	    macros of course);
	5.  A ## operator at the start or end of a macro is ignored;
	6.  Any preprocessing directives in the macro arguments are treated
	    as normal sequences of preprocessing tokens.

    A further undefined area concerns the ban on recursive macro expansions.
    This is extended from the macro definition itself to any extra tokens
    which are read during the expansion of the macro definition.  For
    example, in:

		    #define f( a )	a * g
		    #define g( a )	f ( a )
		    f ( 2 ) ( 9 )

    the result is '2 * f ( 9 )', rather than '2 * 9 * g'.
*/

PPTOKEN *
expand_macro(HASHID macro, TOKEN_LOC *locs, int complete)
{
	LOCATION loc;
	int state = 0;
	PPTOKEN *defn;
	unsigned long sp = 0;
	unsigned no_pars = 0;
	int have_unknown = 0;
	int have_hash_hash = 0;
	unsigned long ws = crt_spaces;
	PPTOKEN dummy_tok, *this_tok = &dummy_tok;
	PPTOKEN *arg_array_base[MAX_MACRO_PARAMS + 1];
	PPTOKEN **arg_array = arg_array_base;

	/* Get the macro identifier */
	IDENTIFIER id = DEREF_id(hashid_id(macro));
	unsigned tag = TAG_id(id);
	DECL_SPEC ds = DEREF_dspec(id_storage(id));

	/* Mark the macro as being used */
	loc = crt_loc;
	ds |= dspec_used;
	COPY_dspec(id_storage(id), ds);
	if (do_macro && do_usage)dump_use(id, &crt_loc, 1);

	/* Get macro definition and other data */
	if (tag == id_obj_macro_tag) {
		/* Object-like macros */
		defn = DEREF_pptok(id_obj_macro_defn(id));
		if (defn == NULL) {
			return NULL;
		}

		if (ds & dspec_builtin) {
			/* Check built-in macros */
			int t = defn->tok;
			if (t == lex_builtin_Hline) {
				/* Construct an integer literal for __LINE__ */
				BUFFER *bf = clear_buffer(&token_buff,
							  NIL(FILE));
				bfprintf(bf, "%lu", loc.line);
				bfputc(bf, 0);
				this_tok = new_pptok();
				this_tok->tok = lex_integer_Hlit;
				this_tok->next = NULL;
				this_tok->pp_opts = NULL;
				this_tok->pp_space = 0;
				token_parts(lex_integer_Hlit, this_tok);
				return this_tok;
			}

			if (t == lex_builtin_Hfile) {
				/* Construct a string literal for __FILE__ */
				character c;
				string fn =
				    DEREF_string(posn_file(crt_loc.posn));
				BUFFER *bf = clear_buffer(&token_buff,
							  NIL(FILE));
				while (c = *(fn++), c != 0) {
					if (c == char_quote ||
					    c == char_backslash) {
						/* Escape quotes and
						 * backslashes */
						bfputc(bf, char_backslash);
					}
					bfputc(bf, (int)c);
				}
				this_tok = new_pptok();
				this_tok->tok = lex_string_Hlit;
				this_tok->next = NULL;
				this_tok->pp_opts = NULL;
				this_tok->pp_space = 0;
				token_parts(lex_string_Hlit, this_tok);
				return this_tok;
			}
		}

	} else {
		/* Function-like macros */
		int t;
		unsigned n;
		TOKEN_LOC *lc;
		int brackets = 0;
		unsigned no_args = 0;
		PPTOKEN *ptr_tok = NULL;
		TOKEN_LOC *ptr_loc = locs;

		/* Check for following open bracket */
		for (;;) {
			if (ptr_loc == file_loc) {
				/* Read token from input location */
				int legal = 1;
				sp = skip_white(1);
				if (peek_char(char_open_round, &legal)) {
					/* Next token in file is '(' */
					update_column();
					t = lex_open_Hround;
				} else {
					/* Other cases */
					t = lex_unknown;
					if (sp)patch_white(sp);
				}
				break;
			} else if (ptr_loc == NULL) {
				/* No more locations */
				t = lex_eof;
				break;
			} else {
				/* Read token from current location */
				ptr_tok = (*(ptr_loc->toks))->next;
				while (ptr_tok && ptr_tok->tok ==
				       lex_ignore_token) {
					/* Step over any ignored tokens */
					ptr_tok = ptr_tok->next;
				}
				if (ptr_tok != NULL) {
					/* Return the next token */
					t = ptr_tok->tok;
					ptr_tok = ptr_tok->next;
					break;
				}
				/* Move on to next location */
				ptr_loc = ptr_loc->next;
			}
		}

		/* Next token is not an open bracket */
		if (t != lex_open_Hround) {
			if (complete) {
				report(loc, ERR_cpp_replace_arg_none(macro));
			}
incomplete_macro:
			/* Return macro identifier */
			this_tok = new_pptok();
			this_tok->tok = lex_identifier;
			this_tok->next = NULL;
			this_tok->pp_space = 0;
			this_tok->pp_data.id.hash = macro;
			this_tok->pp_data.id.use = id;
			return this_tok;
		}

		/* Check argument array size */
		no_pars = DEREF_unsigned(id_func_macro_no_params(id));
		if (no_pars > MAX_MACRO_PARAMS) {
			arg_array = xmalloc_nof(PPTOKEN *, no_pars + 1);
		}

		/* Scan macro arguments */
		for (;;) {
			/* Get the next token */
			int refill = 0;
			for (;;) {
				if (ptr_loc == file_loc) {
					/* Read token from file location */
					sp = skip_white(1);
					in_preproc_dir = 2;
					t = read_token();
					update_column();
					if (t == lex_hash_H1 ||
					    t == lex_hash_H2) {
						if (sp & WHITE_NEWLINE) {
							/* Looks like
							 * preprocessing
							 * directive */
							ERROR err = ERR_cpp_replace_arg_ppdir(macro);
							report(crt_loc, err);
						}
					}
					break;
				} else if (ptr_loc == NULL) {
					/* No more locations to read token
					 * from */
					t = lex_eof;
					break;
				} else {
					/* Read token from next location */
					if (refill)ptr_tok =
						(*(ptr_loc->toks))->next;
					if (ptr_tok != NULL) {
						t = ptr_tok->tok;
						break;
					}
					ptr_loc = ptr_loc->next;
					refill = 1;
				}
			}

			/* Examine this token */
			if (t == lex_open_Hround) {
				brackets++;
			} else if (t == lex_close_Hround) {
				/* Close brackets mark the end of the argument
				 * list */
				if (brackets == 0) {
					break;
				}
				brackets--;
			} else if (t == lex_comma) {
				/* Commas mark the end of an argument */
				if (brackets == 0) {
					this_tok->next = NULL;
					no_args++;
					if (dummy_tok.next) {
						dummy_tok.next->pp_space = 0;
					} else if (complete) {
						ERROR err;
						err = ERR_cpp_replace_arg_empty(no_args, macro);
						report(crt_loc, err);
					}
					if (no_args <= no_pars) {
						arg_array[no_args] = dummy_tok.next;
					} else {
						free_tok_list(dummy_tok.next);
					}
					if (ptr_tok) {
						ptr_tok = ptr_tok->next;
					}
					this_tok = &dummy_tok;
					continue;
				}
			} else if (t == lex_eof) {
				break;
			}

			/* Build up current argument */
			this_tok->next = new_pptok();
			this_tok = this_tok->next;
			if (ptr_tok) {
				copy_pptok(this_tok, t, ptr_tok);
				ptr_tok = ptr_tok->next;
			} else {
				this_tok->tok = t;
				if (t <= LAST_COMPLEX_TOKEN) {
					token_parts(t, this_tok);
				}
				this_tok->pp_space = (sp & WHITE_MASK);
			}
		}

		/* Create last argument */
		in_preproc_dir = 0;
		this_tok->next = NULL;
		if (no_args || dummy_tok.next) {
			no_args++;
			if (dummy_tok.next) {
				dummy_tok.next->pp_space = 0;
			} else if (complete) {
				ERROR err = ERR_cpp_replace_arg_empty(no_args,
								      macro);
				report(crt_loc, err);
			}
			if (no_args <= no_pars) {
				arg_array[no_args] = dummy_tok.next;
			} else {
				free_tok_list(dummy_tok.next);
			}
		}
		if (sp)patch_white(sp);
		this_tok = &dummy_tok;

		/* Check for incomplete argument lists */
		if (t == lex_eof) {
			if (complete) {
				/* Report error, but carry on */
				report(loc, ERR_cpp_replace_arg_eof(macro));
			} else {
				/* Free those arguments actually read */
				for (n = 1; n <= no_args && n <= no_pars; n++) {
					free_tok_list(arg_array[n]);
				}
				if (arg_array != arg_array_base) {
					xfree_nof(arg_array);
				}
				goto incomplete_macro;
			}
		}

		/* Update location pointers */
		if (ptr_loc) {
			*(ptr_loc)->toks = ptr_tok;
		}
		for (lc = locs; lc != ptr_loc; lc = lc->next) {
			*(lc)->toks = NULL;
		}

		/* Check that argument and parameter lists match */
		if (no_pars != no_args) {
			ERROR err;
			n = no_args;
			err = ERR_cpp_replace_arg_number(macro, n, n, no_pars);
			report(crt_loc, err);

			/* Add extra arguments if there are not enough */
			for (n = no_args + 1; n <= no_pars; n++) {
				arg_array[n] = NULL;
			}
		}
		IGNORE check_value(OPT_VAL_macro_args, (ulong)no_args);

		/* Get the macro definition */
		defn = DEREF_pptok(id_func_macro_defn(id));
	}
	crt_spaces = ws;

	/* Copy the definition, expanding macro arguments */
	while (defn != NULL) {
		int t = defn->tok;

		if (t == lex_macro_Harg) {
			/* Macro argument - identified by argument number */
			unsigned long n = defn->pp_data.par.no;
			PPTOKEN *arg = arg_array[n];

			if (state == 0) {
				if (defn->next &&
				    defn->next->tok == lex_hash_Hhash_Hop) {
					/* Preceding ##, just copy argument */
					this_tok->next = copy_tok_list(arg);
				} else {
					/* Normal argument expansion */
					TOKEN_LOC *arg_locs = NULL;
					this_tok->next =
					    expand_toks(arg, arg_locs, 0);
				}

			} else if (state == 1) {
				/* Following #, fake reading a string literal */
				this_tok->next = new_pptok();
				if (!quote_tok_list(arg, 1, char_quote)) {
					report(crt_loc,
					       ERR_cpp_stringize_bad(macro));
				}
				this_tok->next->tok = lex_string_Hlit;
				token_parts(lex_string_Hlit, this_tok->next);
				this_tok->next->next = NULL;
				this_tok->next->pp_space = 0;

			} else {
				/* Following ##, just copy argument */
				this_tok->next = copy_tok_list(arg);
			}

			sp = defn->pp_space;
			if (sp && this_tok->next) {
				this_tok->next->pp_space = sp;
				sp = 0;
			}
			while (this_tok->next) {
				this_tok = this_tok->next;
			}
			state = 0;

		} else if (t == lex_hash_Hop) {
			/* Check for # operator */
			state = 1;

		} else if (t != lex_ignore_token) {
			/* Copy other tokens */
			this_tok->next = new_pptok();
			this_tok = this_tok->next;
			copy_pptok(this_tok, t, defn);
			if (sp) {
				this_tok->pp_space = sp;
				sp = 0;
			}
			if (t == lex_hash_Hhash_Hop) {
				/* Check for ## operator */
				have_hash_hash = 1;
				state = 2;
			} else {
				if (t == lex_unknown) {
					have_unknown = 1;
				}
				state = 0;
			}
		}
		defn = defn->next;
	}
	this_tok->next = NULL;
	defn = dummy_tok.next;

	/* Allow for argument expansion in strings */
	if (have_unknown) {
		defn = recognise_strings(defn, macro, 1);
	}

	/* Rescan for ## directives */
	if (have_hash_hash) {
		defn = process_concat(defn, macro);
	}

	/* Rescan for further expansion (but not expanding macro) */
	COPY_dspec(id_storage(id), (ds | dspec_temp));
	this_tok = expand_toks(defn, locs, complete);
	free_tok_list(defn);
	defn = this_tok;
	COPY_dspec(id_storage(id), ds);

	/* Clean up after macro expansion */
	if (tag == id_func_macro_tag) {
		/* Free the macro arguments */
		unsigned n;
		for (n = 1; n <= no_pars; n++) {
			free_tok_list(arg_array[n]);
		}
		if (arg_array != arg_array_base) {
			xfree_nof(arg_array);
		}
	}

	/* Return the result */
	return defn;
}


/*
    This is the main macro expansion routine.  It expands the list of macros
    tok, returning the result.  If toks ends in an unterminated function-like
    macro then further tokens may be read from the locations given in locs.
    The complete argument is as in expand_macro.
*/

static PPTOKEN *
expand_toks(PPTOKEN *toks, TOKEN_LOC *locs, int complete)
{
	PPTOKEN *ptr_tok;
	unsigned long sp = 0;
	PPTOKEN dummy_tok, *this_tok = &dummy_tok;

	/* Copy list of tokens */
	for (ptr_tok = toks; ptr_tok != NULL; ptr_tok = ptr_tok->next) {
		int t = ptr_tok->tok;
		if (t == lex_ignore_token) {
			sp |= ptr_tok->pp_space;
			continue;
		}
		this_tok->next = new_pptok();
		this_tok = this_tok->next;
		copy_pptok(this_tok, t, ptr_tok);
		if (sp) {
			this_tok->pp_space |= sp;
			sp = 0;
		}

		/* Check for macros */
		if (t == lex_identifier) {
			HASHID m = ptr_tok->pp_data.id.hash;
			IDENTIFIER id = DEREF_id(hashid_id(m));
			unsigned tag = TAG_id(id);
			switch (tag) {
			case id_obj_macro_tag:
			case id_func_macro_tag: {
				DECL_SPEC ds;
				TOKEN_LOC tloc;

				/* Check for non-expanding tokens */
				if (IS_NULL_id(this_tok->pp_data.id.use)) {
					break;
				}

				/* Check for recursive macro definitions */
				ds = DEREF_dspec(id_storage(id));
				if (ds & dspec_temp) {
					/* Mark this token as non-expanding */
					ERROR err = ERR_cpp_rescan_recursive(m);
					report(crt_loc, err);
					this_tok->pp_data.id.use = NULL_id;
					break;
				}

				/* Expand the macro using an extra location */
				tloc.toks = &ptr_tok;
				tloc.next = locs;
				this_tok->tok = lex_ignore_token;
				this_tok->next = expand_macro(m, &tloc,
							      complete);
				while (this_tok->next)this_tok = this_tok->next;
				break;
			}
			}
			if (ptr_tok == NULL) {
				break;
			}
		}
	}
	this_tok->next = NULL;
	return dummy_tok.next;
}


/*
    This routine is the simplest form of expand_toks, where toks is a
    complete list, with no locations for reading further tokens.
*/

PPTOKEN *
expand_tok_list(PPTOKEN *toks)
{
	return expand_toks(toks, NIL(TOKEN_LOC), 1);
}


/*
    The assertions occupy a namespace distinct from all other namespaces,
    including the macro namespace.
*/

NAMESPACE assert_namespace;


/*
    This routine creates a built-in macro named nm defined by a single
    preprocessing token with token type t and associated data d.
*/

static void
builtin_macro(const char *nm, int t, const char *d)
{
	if (d) {
		IDENTIFIER id;
		string s = ustrlit(nm);
		unsigned long h = hash(s);
		HASHID macro = lookup_name(s, h, 0, lex_identifier);
		IDENTIFIER pid = DEREF_id(hashid_id(macro));
		DECL_SPEC ds = (dspec_defn | dspec_builtin);

		/* Set up the token definition */
		PPTOKEN *p = new_pptok();
		p->tok = t;
		p->pp_space = 0;
		p->pp_opts = NULL;
		p->next = NULL;
		if (t == lex_integer_Hlit) {
			/* Set up associated integer data */
			string c = xustrcpy(ustrlit(d));
			p->pp_data.text = c;
		} else if (t == lex_string_Hlit) {
			/* Set up associated string data */
			string c = xustrcpy(ustrlit(d));
			p->pp_data.str.start = c;
			p->pp_data.str.end = c + ustrlen(c);
		} else if (t == lex_builtin_Hline || t == lex_builtin_Hfile) {
			/* Set up associated location data */
			p->pp_space = crt_loc.column;
			p->pp_data.loc.line = crt_loc.line;
			p->pp_data.loc.posn = crt_loc.posn;
		}

		/* Define the macro */
		MAKE_id_obj_macro(macro, ds, NULL_nspace, crt_loc, p, id);
		COPY_id(id_alias(id), pid);
		COPY_id(hashid_id(macro), id);
		if (do_macro) {
			dump_declare(id, &crt_loc, 1);
		}
	}
	return;
}


/*
    This routine initialises the built-in macros, and sets up the assertion
    namespace.
*/

void
init_macros(int m, int a)
{
	const char *d = find_date("%s %2d %d");
	const char *t = find_time("%.2d:%.2d:%.2d");
	if (m) {
		/* Define built-in macros */
		builtin_macro("__LINE__", lex_builtin_Hline, "1");
		builtin_macro("__FILE__", lex_builtin_Hfile, "<unknown>");
		builtin_macro("__DATE__", lex_string_Hlit, d);
		builtin_macro("__TIME__", lex_string_Hlit, t);
		builtin_macro("__STDC__", lex_integer_Hlit, C_VERSION);
		builtin_macro("__STDC_VERSION__", lex_integer_Hlit,
			      ISOC_VERSION);
#if LANGUAGE_CPP
		builtin_macro("__cplusplus", lex_integer_Hlit, CPP_VERSION);
		builtin_macro("__tcpplus", lex_integer_Hlit, "1");
#else
		builtin_macro("__tcpplus", lex_integer_Hlit, "0");
#endif
	}
	assert_namespace = make_global_nspace("<assert>", 20);
	if (a) {
		/* Define built-in assertions */
		IGNORE make_assert(KEYWORD(lex_include), lex_include);
		IGNORE make_assert(KEYWORD(lex_keyword), lex_keyword);
		IGNORE make_assert(KEYWORD(lex_option), lex_option);
	}
	return;
}
