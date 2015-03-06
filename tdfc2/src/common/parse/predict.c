/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <syntax/syntax.h>

#include <parse/parse.h>
#include <parse/predict.h>

#include <construct/namespace.h>

#include "id_ops.h"
#include "type_ops.h"


/*
    The parser for this compiler is generated using the sid tool.
    Basically sid can generate a parser for any grammar it can transform
    into an LL(1) grammar.  Unfortunately, C++ is not a LL(1) language,
    so that no such grammar for C++ can be written.  In fact, C++ is a
    LL(k) language since a potentially unlimited look-ahead is necessary
    to distinguish declarations from expressions.  However the points
    at which C++ is not LL(1) are relatively few, so we have used sid's
    predicate mechanism to enable the look-ahead in these places to be
    done by hand, leaving sid to deal with the rest.  This file contains
    the implementation of these predicates.  A number of the routines
    contain conditional compilation to handle the differences between
    the C++ and C grammars.  Note that if the grammars are changed it
    may also be necessary to modify these routines.

    The look-ahead itself is implemented using next_token to read and store
    the next token.  Provided crt_token is reset afterwards, this will be
    invisible to the main parser.
*/


/*
    This table gives a simple look-up for lexical tokens to predict which
    kind of construct is likely to start with this token.  The values
    themselves are built into symbols.h.
*/

#define TOK_NONE			0
#define TOK_DECLARATION			1
#define TOK_DECL_SPEC			2
#define TOK_EXTERN			3
#define TOK_EXP				4
#define TOK_NESTED_NAME			5
#define TOK_FULL_NAME			6
#define TOK_SIMPLE_TYPE			7
#define TOK_STATEMENT			8
#define TOK_TYPE			9
#define TOK_TYPE_KEY			10
#define TOK_TYPE_SPEC			11

#if LANGUAGE_CPP
#define TOK_ASM				TOK_DECLARATION
#else
#define TOK_ASM				TOK_STATEMENT
#endif

#define lookup_token(T)			((int)tokens[(T)])

static unsigned char tokens[] = {
#define LEX_TOKEN(A, B, C)		(C),
#include <parse/symbols.h>
#undef LEX_TOKEN
	TOK_NONE
};


/*
    These flags are used to indicate various parser states.  The flag
    have_type_specifier is set during reading a sequence of declaration-
    specifiers or type-specifiers to indicate that a type-specifier (other
    than a cv-qualifier) has been read.  Similarly have_type_declaration
    is set to indicate an elaborated-type-specifier.  in_function_defn
    is used to count nested function definitions.
*/

int have_type_specifier = 0;
int have_type_declaration = TYPE_DECL_NONE;
int have_func_declarator = 0;
int in_function_defn = 0;
int in_class_defn = 0;
int in_declaration = 0;
int in_default_arg = 0;
int in_weak_param = 0;
int in_ptr_mem_selector = 0;
int in_token_decl = 0;
int in_template_decl = 0;
int really_in_function_defn = 0;
int really_in_class_defn = 0;
int is_function_next = 0;
int is_constructor_next = 0;


/*
    These variables are used to keep count of various items of interest
    in the parser, such as the number of expressions which have side
    effects and the number of type definitions.
*/

int no_side_effects = 0;
int no_type_defns = 0;
int have_destructor = 0;
unsigned long no_declarations = 0;
unsigned long no_token_defns = 0;


/*
    These flags are set to indicate that certain features, which require
    the program to perform extra checks, have been used.
*/

int used_extern_volatile = 0;
int used_register = 0;


/*
    The following look-ahead functions need to be declared in advance.
*/

#if LANGUAGE_CPP
static int predict_declarator(int, int, int);
#endif


/*
    This routine is called after reading an open bracket to skip to the
    corresponding close bracket.  It returns the number of tokens skipped.
*/

#if LANGUAGE_CPP

static int
skip_brackets(void)
{
	int n = 0;
	int brackets = 1;
	for (;;) {
		int t = next_token();
		n++;
		switch (t) {
		case lex_open_Hround:
		case lex_open_Hsquare_H1:
		case lex_open_Hbrace_H1:
			/* Open bracket */
			brackets++;
			break;
		case lex_close_Hround:
		case lex_close_Hsquare_H1:
		case lex_close_Hbrace_H1:
			/* Close bracket */
			if (--brackets == 0) {
				return n;
			}
			break;
		case lex_eof:
			/* Premature end of file */
			return n;
		}
	}

	UNREACHED;
}

#endif


/*
    This routine is called after 'operator' has been read to return the
    token immediately following.  It has to deal with both overloaded
    operator function names and conversion function names.  Note that
    class and enumeration definitions are allowed in a conversion function
    name by the syntax, but are weeded out later.  Skipping over them
    here would therefore seem to be a lot of effort for something which
    is going to prove illegal however it is interpreted.
*/

#if LANGUAGE_CPP

static int
skip_operator(void)
{
	int t, c;
	int go = 1;
	int have_type = 0;

	/* Check for conversion function names */
	do {
		t = next_token();
		c = lookup_token(t);
		switch (c) {
		case TOK_SIMPLE_TYPE:
		case TOK_TYPE_SPEC:
		case TOK_TYPE:
			/* These are type-specifiers */
			have_type = 1;
			break;
		case TOK_NESTED_NAME:
		case TOK_FULL_NAME: {
			/* Look for nested type names */
			PPTOKEN *p = crt_token;
			NAMESPACE np = crt_lookup;
			int t2 = next_token();
			c = lookup_token(t2);
			if (c != TOK_TYPE) {
				crt_lookup = np;
				crt_token = p;
				return t;
			}
			have_type = 1;
			break;
		}
		case TOK_TYPE_KEY:
			/* These are elaborated-type-specifiers */
			t = next_token();
			switch (t) {
			case lex_identifier:
			case lex_type_Hname:
			case lex_namespace_Hname:
			case lex_statement_Hname:
			case lex_template_Htype:
				/* Name present */
				t = next_token();
				break;
			case lex_full_Hname:
			case lex_nested_Hname:
			case lex_colon_Hcolon:
				/* Allow for nested names */
				t = next_token();
				switch (t) {
				case lex_identifier:
				case lex_type_Hname:
				case lex_namespace_Hname:
				case lex_statement_Hname:
				case lex_template_Htype:
					break;
				default:
					return t;
				}
				break;
			default:
				/* Other characters */
				return t;
			}
			have_type = 1;
			break;
		default:
			/* Other characters */
			go = 0;
			break;
		}
	} while (go);

	/* Step over any conversion function declarators */
	if (have_type) {
		go = 1;
		do {
			switch (t) {
			case lex_and_H1:
			case lex_full_Hname_Hstar:
			case lex_nested_Hname_Hstar:
			case lex_star:
			case lex_const:
			case lex_volatile:
				/* Pointer operators */
				t = next_token();
				break;
			default:
				/* Other characters */
				go = 0;
				break;
			}
		} while (go);
		return t;
	}

	/* Check for overloaded operator function names */
	switch (t) {
	case lex_open_Hround:
		/* Check for 'operator ()' */
		t = next_token();
		if (t == lex_close_Hround) {
			t = next_token();
		}
		break;
	case lex_open_Hsquare_H1:
		/* Check for 'operator []' */
		t = next_token();
		if (t == lex_close_Hsquare_H1) {
			t = next_token();
		}
		break;
	case lex_question:
		/* Check for 'operator ?:' */
		t = next_token();
		if (t == lex_colon) {
			t = next_token();
		}
		break;
	case lex_new:
	case lex_delete:
		/* Check for 'operator new []' and 'operator delete []' */
		t = next_token();
		if (t == lex_open_Hsquare_H1) {
			PPTOKEN *p = crt_token;
			NAMESPACE np = crt_lookup;
			int t2 = next_token();
			if (t2 == lex_close_Hsquare_H1) {
				t = next_token();
			} else {
				crt_token = p;
				crt_lookup = np;
			}
		}
		break;
	}
	return t;
}

#endif


/*
    This routine is used to distinguish lists of function parameters from
    lists of expressions (such as function arguments or function style
    initialisers.  It is called after an initial open bracket has been
    read.  It returns 1 if the following list definitely consists of
    function parameters, 0 if it definitely consists of expressions,
    and 2 if it could be either.
*/

#if LANGUAGE_CPP

static int
predict_func_params(int t, int empty, int depth)
{
	int c = lookup_token(t);
	switch (c) {
	case TOK_DECLARATION:
	case TOK_DECL_SPEC:
	case TOK_EXTERN:
	case TOK_TYPE_KEY:
	case TOK_TYPE_SPEC:
		/* These are all obviously parameter declarations */
		return 1;
	case TOK_SIMPLE_TYPE:
	case TOK_TYPE:
		/* These are simple-type-specifiers */
		t = next_token();
		if (t == lex_open_Hround) {
			t = next_token();
			return predict_func_params(t, 1, 1);
		}
		return 1;
	case TOK_NESTED_NAME:
	case TOK_FULL_NAME:
		/* Look for nested type-names */
		t = next_token();
		c = lookup_token(t);
		if (c == TOK_TYPE) {
			t = next_token();
			if (t == lex_open_Hround) {
				t = next_token();
				return predict_func_params(t, 1, 1);
			}
			return 1;
		}
		return 0;
	}
	if (t == lex_ellipsis) {
		return 1;
	}
	if (t == lex_ellipsis_Hexp) {
		return 1;
	}
	if (t == lex_close_Hround) {
		/* Empty pair of brackets */
		return empty;
	}
	if (depth) {
		int d = predict_declarator(t, 2, 1);
		if (d == 0) {
			return 0;
		}
		if (d == 2) {
			/* Comma - check next parameter */
			t = next_token();
			return predict_func_params(t, 1, 0);
		}
		if (d == 3) {
			return 2;
		}
		return 1;
	}
	return 0;
}

#endif


/*
    This routine is used to distinguish declarators from other constructs,
    including expressions.  The argument depth indicates the number of
    open brackets which have been read before the routine is entered.
    The argument loc is 0 to indicate normal declarators, 1 to indicate
    abstract declarators and 2 to indicate parameter declarators.  The
    return value is 0 if this is definitely not a declarator, and 1 if it
    definitely is.  The return values 2 and 3 are used to indicate possible
    declarators in the parameter case, with 2 indicating a following comma
    and 3 a close bracket.
*/

#if LANGUAGE_CPP

static int
predict_declarator(int t, int loc, int depth)
{
	int go = 1;
	int res = -1;
	int have_init = 0;
	NAMESPACE ns = NULL_nspace;

	/* Step over open brackets and pointer operations */
	while (go) {
		switch (t) {
		case lex_and_H1:
		case lex_star:
			/* Can be a pointer or reference or a unary operator */
			t = next_token();
			if (t == lex_const || t == lex_volatile) {
				/* This is definitely a pointer operation */
				return 1;
			}
			break;
		case lex_full_Hname_Hstar:
		case lex_nested_Hname_Hstar:
			/* Definitely a pointer to member */
			return 1;
		case lex_open_Hround:
			/* Nested declarator brackets */
			depth++;
			t = next_token();
			break;
		default:
			/* Other tokens */
			go = 0;
			break;
		}
	}

	/* Check for declarator-id */
	if (loc != 1) {
		switch (t) {
		case lex_nested_Hname:
		case lex_full_Hname:
		case lex_colon_Hcolon:
			/* Allow for qualified identifiers */
			ns = crt_lookup;
			t = next_token();
			break;
		}
		switch (t) {
		case lex_identifier:
		case lex_type_Hname:
		case lex_namespace_Hname:
		case lex_statement_Hname:
		case lex_destructor_Hname:
		case lex_template_Hid:
		case lex_template_Htype:
			/* Identifiers and destructors */
			t = next_token();
			break;
		case lex_operator:
			/* Operator function identifiers */
			t = skip_operator();
			break;
		default:
			/* Anything else isn't a declarator-id */
			if (loc == 0 || !IS_NULL_nspace(ns)) {
				return 0;
			}
			break;
		}
	}

	/* Check for declarator tail and initialiser */
	if (!IS_NULL_nspace(ns)) {
		IGNORE add_nested_nspace(ns);
	}
	for (;;) {
		switch (t) {

		case lex_open_Hround: {
			/* Function parameters, function call or initialiser */
			int d;
			PPTOKEN *p = crt_token;
			NAMESPACE np = crt_lookup;
			t = next_token();
			d = predict_func_params(t, 1, 0);
			if (d == 1) {
				/* Definitely function parameters */
				res = 1;
			} else if (d == 0) {
				/* Definitely expression list */
				if (depth > 0 || have_init) {
					/* Can't be an initialiser in these
					 * cases */
					res = 0;
				} else {
					crt_lookup = np;
					crt_token = p;
					IGNORE skip_brackets();
					have_init = 1;
				}
			}
			break;
		}

		case lex_open_Hsquare_H1: {
			/* Array dimension or index expression */
			int d = skip_brackets();
			if (d == 1) {
				/* Only array dimensions can be empty */
				res = 1;
			}
			break;
		}

		case lex_assign: {
			/* Initialiser or assignment expression */
			int brackets = 0;
			if (loc == 1 || depth > 0) {
				/* Can't have initialiser in these cases */
				res = 0;
				break;
			}
			t = next_token();
			if (t == lex_open_Hbrace_H1) {
				/* Can only have aggregates in initialisers */
				if (loc == 0) {
					res = 1;
					break;
				}
			}
			/* Scan to end of expression */
			go = 1;
			while (go) {
				switch (t) {
				case lex_open_Hround:
				case lex_open_Hsquare_H1:
				case lex_open_Hbrace_H1:
					/* Open bracket */
					brackets++;
					break;
				case lex_close_Hround:
				case lex_close_Hsquare_H1:
				case lex_close_Hbrace_H1:
					/* Close bracket */
					brackets--;
					if (brackets < 0 && loc == 2) {
						res = 3;
					}
					break;
				case lex_semicolon:
					/* End of declaration */
					if (brackets <= 0) {
						res = 3;
					}
					break;
				case lex_comma: {
					/* Comma */
					if (brackets <= 0) {
						/* Check rest of declaration */
						if (loc == 1) {
							res = 0;
						} else if (loc == 2) {
							res = 2;
						} else {
							t = next_token();
							res = predict_declarator(t, 0, 0);
						}
					}
					break;
				}
				case lex_ellipsis:
				case lex_ellipsis_Hexp:
					/* Ellipsis */
					if (loc == 2 && brackets <= 0) {
						res = 1;
					}
					break;
				case lex_eof:
					/* Premature end of file */
					res = 1;
					break;
				}
				if (res != -1) {
					break;
				}
				t = next_token();
			}
			break;
		}

		case lex_semicolon:
		case lex_close_Htemplate:
			/* End of declaration (don't worry about depth) */
			res = 3;
			break;

		case lex_comma:
			/* Comma */
			if (depth <= 0) {
				/* Check rest of declaration */
				if (loc == 1) {
					res = 1;
				} else if (loc == 2) {
					res = 2;
				} else {
					t = next_token();
					res = predict_declarator(t, 0, 0);
				}
			} else {
				res = 0;
			}
			break;

		case lex_ellipsis:
		case lex_ellipsis_Hexp:
			/* Ellipsis */
			if (depth <= 0 && loc == 2) {
				res = 1;
			} else {
				res = 0;
			}
			break;

		case lex_close_Hround: {
			/* Declarator close bracket */
			depth--;
			if (depth < 0) {
				if (loc == 1) {
					res = 1;
				} else if (loc == 2) {
					res = 3;
				}
			}
			break;
		}

		default:
			/* Nothing else can appear in a declaration */
			res = 0;
			break;
		}
		if (res != -1) {
			break;
		}
		t = next_token();
	}
	if (!IS_NULL_nspace(ns)) {
		IGNORE remove_nested_nspace(ns);
	}
	return res;
}

#endif


/*
    A look-ahead is needed in declaration-statement to distinguish
    declarations from other statements including, in particular, expression
    statements.  The disambiguation rule is that anything which looks like
    a declaration is a declaration.  Note that the empty statement is
    classified as an expression-statement.  Actually the real answer to
    questions like is 'int ( a ) ;' a declaration or an expression is,
    are flying pigs kosher?
*/

int
predict_decl(void)
{
	int t = crt_lex_token;
	int c = lookup_token(t);
	switch (c) {
	case TOK_DECLARATION:
	case TOK_DECL_SPEC:
	case TOK_EXTERN:
	case TOK_TYPE_KEY:
	case TOK_TYPE_SPEC:
		/* These are all obviously declarations */
		return 1;
	case TOK_SIMPLE_TYPE:
	case TOK_TYPE: {
		/* These are simple-type-specifiers */
		int d = 1;
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		t = next_token();
#if LANGUAGE_CPP
		if (t == lex_open_Hround) {
			/* This is the tricky case, 'T ( ...' */
			t = next_token();
			d = predict_declarator(t, 0, 1);
		} else /* continued ... */
#endif
			if (t == lex_colon) {
				/* Check for labels */
				if (c == TOK_TYPE) {
					d = 0;
				}
			}
		crt_lookup = np;
		crt_token = p;
		return d;
	}
#if LANGUAGE_CPP
	case TOK_NESTED_NAME:
	case TOK_FULL_NAME: {
		/* Look for nested type-names */
		int d = 0;
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		t = next_token();
		c = lookup_token(t);
		if (c == TOK_TYPE) {
			d = 1;
			t = next_token();
			if (t == lex_open_Hround) {
				/* This is the tricky case, 'N::T ( ...' */
				t = next_token();
				d = predict_declarator(t, 0, 1);
			}
		}
		crt_lookup = np;
		crt_token = p;
		return d;
	}
#endif
	}
	/* Nothing else is a declaration */
	return 0;
}


/*
    This look-ahead is used to handle syntax errors following undeclared
    types.  The context is in a sequence of declaration specifiers in
    which no type specifier has been encountered.  t gives the token read.
*/

static int
predict_undecl_type(int t, int force)
{
	switch (t) {
	case lex_identifier:
	case lex_type_Hname:
	case lex_namespace_Hname:
	case lex_statement_Hname: {
		int d = force;
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		if (!d) {
			t = next_token();
			switch (t) {
#if LANGUAGE_CPP
			case lex_and_H1:
			case lex_full_Hname_Hstar:
			case lex_nested_Hname_Hstar:
#endif
			case lex_star:
				/* These are ptr-operators */
				d = 1;
				break;
			case lex_open_Hround:
				/* This is stretching the bounds of
				 * possibility */
				break;
			case lex_identifier:
			case lex_type_Hname:
			case lex_namespace_Hname:
			case lex_statement_Hname:
			case lex_template_Htype:
			case lex_template_Hid:
			case lex_full_Hname:
			case lex_nested_Hname:
				/* The identifier can't be a declarator */
				d = 1;
				break;
			default: {
				/* Check for further declaration specifiers */
				int c = lookup_token(t);
				switch (c) {
				case TOK_DECL_SPEC:
				case TOK_SIMPLE_TYPE:
				case TOK_TYPE_KEY:
				case TOK_TYPE_SPEC:
				case TOK_EXTERN:
				case TOK_TYPE: {
					d = 1;
					break;
				}
				}
				break;
			}
			}
		}
		if (d) {
			p->tok = lex_type_Hname;
		}
		crt_lookup = np;
		crt_token = p;
		return d;
	}
	}
	return 0;
}


/*
    A look-ahead is needed to distinguish decl-specifiers from following
    declarators or other constructs.  Note that linkage-specifications are
    spotted at this stage.  In addition type names are not always what
    they seem.  For example in:

		typedef int t ;
		typedef int t ;

    the second t is a type-name, but needs to be recognised as a declarator-id
    rather than a decl-specifier.  Similarly in:

		class c {
		    c () ;
		} ;

    the second c is a class-name, but is actually a constructor name rather
    than a decl-specifier.
*/

int
predict_dspec(int force)
{
	int d = 0;
	int t = crt_lex_token;
	int c = lookup_token(t);
#if LANGUAGE_CPP
	is_constructor_next = 0;
#endif
	switch (c) {
	case TOK_DECL_SPEC:
	case TOK_SIMPLE_TYPE:
	case TOK_TYPE_KEY:
	case TOK_TYPE_SPEC:
		/* These are declaration-specifiers */
		d = 1;
		break;
	case TOK_EXTERN: {
#if LANGUAGE_CPP
		/* Explicitly check for linkage-specifications */
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		t = next_token();
		if (t != lex_string_Hexp && t != lex_wstring_Hexp)d = 1;
		crt_lookup = np;
		crt_token = p;
#else
		d = 1;
#endif
		break;
	}
	case TOK_TYPE:
		/* Only the first type name is counted */
		if (t == lex_type_Hname || t == lex_template_Htype) {
			if (!have_type_specifier) {
#if LANGUAGE_CPP
				PPTOKEN *p = crt_token;
				NAMESPACE np = crt_lookup;
				d = 1;
				t = next_token();
				if (t == lex_open_Hround) {
					/* Allow for constructors */
					t = next_token();
					if (predict_func_params(t, 1, 0)) {
						is_constructor_next = 1;
						d = 0;
					}
				}
				crt_lookup = np;
				crt_token = p;
#else
				d = 1;
#endif
			}
		} else {
			d = 1;
		}
		break;
#if LANGUAGE_CPP
	case TOK_NESTED_NAME:
	case TOK_FULL_NAME:
		/* Look for nested type names */
		if (!have_type_specifier) {
			PPTOKEN *p = crt_token;
			NAMESPACE np = crt_lookup;
			t = next_token();
			c = lookup_token(t);
			if (c == TOK_TYPE) {
				/* These are simple-type-specifiers */
				d = 1;
				t = next_token();
				if (t == lex_open_Hround) {
					/* Allow for constructors */
					IGNORE add_nested_nspace(np);
					t = next_token();
					if (predict_func_params(t, 1, 0)) {
						is_constructor_next = 1;
						d = 0;
					}
					IGNORE remove_nested_nspace(np);
				}
			} else {
				d = predict_undecl_type(t, force);
			}
			crt_lookup = np;
			crt_token = p;
		}
		break;
#endif
	default:
		/* Check for undefined types */
		if (!have_type_specifier) {
			d = predict_undecl_type(t, force);
			if (d)crt_lex_token = lex_type_Hname;
		}
		break;
	}
	return d;
}


/*
    A look-ahead is needed to distinguish type-specifiers from following
    declarators or other constructs.
*/

int
predict_tspec(int force)
{
	int d = 0;
	int t = crt_lex_token;
	int c = lookup_token(t);
	switch (c) {
	case TOK_SIMPLE_TYPE:
	case TOK_TYPE_KEY:
	case TOK_TYPE_SPEC:
	case TOK_TYPE:
		/* These are type-specifiers */
		d = 1;
		break;
#if LANGUAGE_CPP
	case TOK_NESTED_NAME:
	case TOK_FULL_NAME: {
		/* Look for nested type names */
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		t = next_token();
		c = lookup_token(t);
		if (c == TOK_TYPE) {
			d = 1;
		} else {
			if (!have_type_specifier) {
				d = predict_undecl_type(t, force);
			}
		}
		crt_lookup = np;
		crt_token = p;
		break;
	}
#endif
	default:
		/* Check for undefined types */
		if (!have_type_specifier) {
			d = predict_undecl_type(t, force);
			if (d)crt_lex_token = lex_type_Hname;
		}
		break;
	}
	return d;
}


/*
    A further look-ahead is required when distinguishing type-ids from
    expressions after 'T ()' has been read for some type.  If the next
    token is '+' for example it is an expression, if it is 'const' it
    is a declaration.  t gives the next token and e gives the default
    value.
*/

#if LANGUAGE_CPP

static int
predict_qual(int t, int e)
{
	switch (t) {
	case lex_const:
	case lex_volatile:
	case lex_throw:
		/* Function qualifiers */
		e = 1;
		break;
	case lex_and_H1:
	case lex_and_Heq_H1:
	case lex_arrow:
	case lex_arrow_Hstar:
	case lex_assign:
	case lex_div:
	case lex_div_Heq:
	case lex_dot:
	case lex_dot_Hstar:
	case lex_eq:
	case lex_greater:
	case lex_greater_Heq:
	case lex_less:
	case lex_less_Heq:
	case lex_logical_Hand_H1:
	case lex_logical_Hor_H1:
	case lex_lshift:
	case lex_lshift_Heq:
	case lex_minus:
	case lex_minus_Heq:
	case lex_minus_Hminus:
	case lex_not_Heq_H1:
	case lex_or_H1:
	case lex_or_Heq_H1:
	case lex_plus:
	case lex_plus_Heq:
	case lex_plus_Hplus:
	case lex_question:
	case lex_rem:
	case lex_rem_Heq:
	case lex_rshift:
	case lex_rshift_Heq:
	case lex_star:
	case lex_star_Heq:
	case lex_xor_H1:
	case lex_xor_Heq_H1:
	case lex_abs:
	case lex_max:
	case lex_min:
		/* Binary expression operators */
		e = 0;
		break;
	case lex_comma:
		/* Comma operators */
		if (e == 1) {
			e = 0;
		}
		break;
	}
	return e;
}

#endif


/*
    A look-ahead is needed to distinguish type-ids from expressions in,
    for example, sizeof expressions.  A type-id consists of a sequence
    of type-specifiers followed by an optional abstract-declarator,
    whereas the only tricky expressions are those consisting of a
    simple-type-specifier followed by a bracketed list of expressions.
    e gives the value to be returned if the result could be either.
*/

int
predict_typeid(int e)
{
	int t = crt_lex_token;
	int c = lookup_token(t);
	switch (c) {
	case TOK_TYPE_KEY:
	case TOK_TYPE_SPEC:
		/* These are type-specifiers */
		return 1;
	case TOK_SIMPLE_TYPE:
	case TOK_TYPE: {
		/* These are simple-type-specifiers */
		int d = 1;
#if LANGUAGE_CPP
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		t = next_token();
		if (t == lex_open_Hround) {
			/* This is the tricky case 'T ( ...' */
			PPTOKEN *q;
			NAMESPACE nq;
			t = next_token();
			q = crt_token;
			nq = crt_lookup;
			d = predict_func_params(t, 2, 0);
			if (d != 1) {
				if (t == lex_close_Hround) {
					t = next_token();
					d = predict_qual(t, e);
				} else {
					crt_lookup = nq;
					crt_token = q;
					d = predict_declarator(t, 1, 1);
				}
			}
		}
		crt_lookup = np;
		crt_token = p;
#else
		UNUSED(e);
#endif
		return d;
	}
#if LANGUAGE_CPP
	case TOK_NESTED_NAME:
	case TOK_FULL_NAME: {
		/* Look for nested type-names */
		int d = 0;
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		t = next_token();
		c = lookup_token(t);
		if (c == TOK_TYPE) {
			d = 1;
			t = next_token();
			if (t == lex_open_Hround) {
				/* This is the tricky case 'N::T ( ...' */
				PPTOKEN *q;
				NAMESPACE nq;
				t = next_token();
				q = crt_token;
				nq = crt_lookup;
				d = predict_func_params(t, 2, 0);
				if (d != 1) {
					if (t == lex_close_Hround) {
						t = next_token();
						d = predict_qual(t, e);
					} else {
						crt_lookup = nq;
						crt_token = q;
						d = predict_declarator(t, 1, 1);
					}
				}
			}
		}
		crt_lookup = np;
		crt_token = p;
		return d;
	}
#endif
	}
	return 0;
}


/*
    A look-ahead is needed to distinguish template type names from other
    types when parsing template arguments.
*/

int
predict_typename(void)
{
	int d = 0;
	int t = crt_lex_token;
	if (t == lex_type_Hname) {
		/* Unqualified type names */
		IDENTIFIER id = crt_token->pp_data.id.use;
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_template) {
			d = 1;
		}
	}
#if LANGUAGE_CPP
	if (t == lex_full_Hname || t == lex_nested_Hname ||
	    t == lex_colon_Hcolon) {
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		t = next_token();
		if (t == lex_type_Hname) {
			/* Qualified type names */
			IDENTIFIER id = crt_token->pp_data.id.use;
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_template) {
				d = 1;
			}
		}
		crt_lookup = np;
		crt_token = p;
	}
#endif
	return d;
}


/*
    A look-ahead is needed to distinguish function-style initialisers in
    init-declarator from function declarators.  This predicate is called
    immediately after an open bracket.  Note that anything which could
    possibly be a function declarator is.  If the result is an initialiser
    beginning with '(' then this first token is replaced by a dummy to
    prevent further calls to predict_init.
*/

int
predict_init(void)
{
#if LANGUAGE_CPP
	PPTOKEN *p = crt_token;
	NAMESPACE np = crt_lookup;
	int t = crt_lex_token;
	int d = predict_func_params(t, 1, 0);
	crt_lookup = np;
	crt_token = p;
	if (d == 0) {
		/* Definitely doesn't look like a function declarator */
		if (t == lex_open_Hround) {
			t = lex_open_Hinit;
			crt_lex_token = t;
			p->tok = t;
		}
		return 1;
	}
	if (t == lex_ellipsis_Hexp) {
		t = lex_ellipsis;
		crt_lex_token = t;
		p->tok = t;
	}
#endif
	return 0;
}


/*
    A look-ahead is required to distinguish a destructor-name from a
    complement operator followed by a class-name.  The latter is only the
    case if it is followed by a bracketed list of expressions.  The
    really difficult case is when this list is empty.  The return value
    is 2 following '::', 3 following '->' or '.', and 1 for other
    destructors.
*/

int
predict_destr(NAMESPACE ns)
{
#if LANGUAGE_CPP
	int d = 1;
	int t = last_lex_token;
	if (!IS_NULL_nspace(ns)) {
		if (EQ_nspace(ns, global_namespace)) {
			t = lex_colon_Hcolon;
		} else {
			t = lex_nested_Hname;
		}
	}
	switch (t) {
	case lex_nested_Hname:
	case lex_full_Hname:
		/* Always have destructor names after these */
		if (cache_lookup) {
			d = 2;
		} else {
			/* Can only happen after '.' or '->' */
			d = 3;
		}
		break;
	case lex_colon_Hcolon:
		/* Never have destructor name after this */
		d = 0;
		break;
	case lex_arrow:
	case lex_dot:
		/* Always have destructor names after these */
		d = 3;
		break;
	default: {
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		t = next_token();
		if (t == lex_open_Hround) {
			t = next_token();
			if (t == lex_close_Hround) {
				/* This is the commonest case */
				if (in_function_defn)d = 0;
			} else {
				d = predict_func_params(t, 1, 0);
				if (d)d = 1;
			}
		}
		crt_lookup = np;
		crt_token = p;
		break;
	}
	}
	return d;
#else
	UNUSED(ns);
	return 0;
#endif
}


/*
    A look-ahead is needed to distinguish a declarator-id representing a
    function parameter from a type-specifier.  The only difficult case is
    a type-name immediately after an open bracket.
*/

int
predict_param(void)
{
	int t = crt_lex_token;
	switch (t) {
	case lex_identifier:
	case lex_namespace_Hname:
	case lex_statement_Hname:
	case lex_destructor_Hname:
	case lex_template_Hid:
	case lex_operator:
		/* These are all unqualified-ids */
		return 1;
	case lex_type_Hname:
	case lex_template_Htype:
		/* Check for type names */
		if (last_lex_token != lex_open_Hround) {
			return 1;
		}
		break;
#if LANGUAGE_CPP
	case lex_full_Hname:
	case lex_nested_Hname:
	case lex_colon_Hcolon: {
		/* Check token after a nested name */
		int d;
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		crt_lex_token = next_token();
		d = predict_param();
		crt_lex_token = t;
		crt_lookup = np;
		crt_token = p;
		return d;
	}
#endif
	}
	return 0;
}


/*
    A look-ahead of one token is needed in type-specifier to distinguish a
    class-specifier or an enum-specifier from an elaborated-type-specifier.
    This predicate is called after a class-key to check for a class-specifier
    or an enum-specifier.  This is recognised by an optional qualified
    identifier followed by an open brace (for the class body) or a colon
    (for a base-clause, if col is true).
*/

int
predict_class(int col)
{
	int t = crt_lex_token;

	/* Examine the name */
	switch (t) {
	case lex_identifier:
	case lex_type_Hname:
	case lex_namespace_Hname:
	case lex_statement_Hname:
	case lex_template_Htype: {
		/* Name present */
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		t = next_token();
		crt_lookup = np;
		crt_token = p;
		break;
	}
#if LANGUAGE_CPP
	case lex_full_Hname:
	case lex_nested_Hname:
	case lex_colon_Hcolon: {
		/* Allow for nested names */
		PPTOKEN *p = crt_token;
		NAMESPACE np = crt_lookup;
		t = next_token();
		switch (t) {
		case lex_identifier:
		case lex_type_Hname:
		case lex_namespace_Hname:
		case lex_statement_Hname:
		case lex_template_Htype:
			/* Nested name present */
			t = next_token();
			crt_lookup = np;
			crt_token = p;
			break;
		default:
			/* Invalid name */
			crt_lookup = np;
			crt_token = p;
			return 0;
		}
		break;
	}
#endif
	}

	/* Examine the token following the name */
	if (t == lex_open_Hbrace_H1) {
		return 1;
	}
	if (t == lex_colon && !in_token_decl) {
		return col;
	}
	return 0;
}


/*
    A predicate is needed to distinguish function definitions from function
    declarations. A function definition is recognised by means of a '{'
    (starting a function-body), a ':' (starting a ctor-initialiser), or
    a 'try' (starting a function-try-block).  It has already been checked
    whether the type of the current declarator is a function.
*/

int
predict_func_defn(void)
{
	int t = crt_lex_token;
	if (t == lex_open_Hbrace_H1) {
		return 1;
	}
#if LANGUAGE_CPP
	if (t == lex_try) {
		return 1;
	}
	if (t == lex_colon && !in_token_decl) {
		return 1;
	}
#endif
	return 0;
}


/*
    A predicate is needed to determine whether an object declaration
    is followed by an initialising expression.  Note this is not the
    same as the object being defined.
*/

int
predict_obj_defn(void)
{
	int t = crt_lex_token;
	if (t == lex_assign) {
		return 1;
	}
#if LANGUAGE_CPP
	if (t == lex_open_Hround) {
		return 1;
	}
#endif
	return 0;
}


/*
    A look-ahead is needed following a conversion-function-id for possible
    ptr-operators.  This is because, for instance 'operator int *' needs
    to be resolved as the conversion function for 'int *' rather than as
    the conversion function for 'int' times something.  The argument ref
    indicates whether '&' is a valid pointer operator.
*/

int
predict_ptr(int ref)
{
	int t = crt_lex_token;
	if (t == lex_star) {
		return 1;
	}
#if LANGUAGE_CPP
	if (t == lex_full_Hname_Hstar || t == lex_nested_Hname_Hstar) {
		return 1;
	}
	if (t == lex_and_H1) {
		return ref;
	}
#else
	UNUSED(ref);
#endif
	return 0;
}


/*
    A look-ahead is needed in the token syntax for overloaded operator
    and conversion function names.
*/

int
predict_operator(void)
{
#if LANGUAGE_CPP
	int t = crt_lex_token;
	if (t == lex_operator) {
		return 1;
	}
#endif
	return 0;
}


/*
    A look-ahead of one token is needed following 'operator new' and
    'operator delete'.  A following '[' might be the start of an array index,
    or it may introduce 'operator new []' or 'operator delete []'.  This
    routine returns true in the latter case.
*/

int
predict_array(void)
{
	PPTOKEN *p;
	NAMESPACE np;
	int t = crt_lex_token;
	if (t != lex_open_Hsquare_H1) {
		return 0;
	}
	p = crt_token;
	np = crt_lookup;
	t = next_token();
	crt_lookup = np;
	crt_token = p;
	if (t != lex_close_Hsquare_H1) {
		return 0;
	}
	return 1;
}


/*
    A look-ahead is required to distinguish type template parameters from
    non-type template parameters.
*/

int
predict_template(void)
{
	int d = 0;
	int t = crt_lex_token;
	if (t == lex_class || t == lex_typename) {
		int have_id = 0;
		PPTOKEN *p = crt_token;
		int s = next_token();
		switch (s) {
		case lex_identifier:
		case lex_type_Hname:
		case lex_namespace_Hname:
		case lex_statement_Hname:
			s = next_token();
			have_id = 1;
			break;
		}
		if (s == lex_comma || s == lex_close_Htemplate) {
			d = 1;
		} else if (s == lex_assign) {
			if (have_id) {
				s = next_token();
				crt_lex_token = s;
				d = predict_typeid(2);
			} else {
				d = 1;
			}
		}
		crt_lex_token = t;
		crt_token = p;
	} else if (t == lex_template) {
		d = 1;
	}
	return d;
}
