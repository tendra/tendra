/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/buffer.h>
#include <utility/print.h>
#include <utility/ustring.h>
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
#include <parse/preproc.h>

#include <output/dump.h>

#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "str_ops.h"


/*
    These flags control the behaviour of the parser and determine whether
    such features as trigraphs and digraphs are allowed.
*/

int allow_trigraphs = 1;
int allow_digraphs = 1;
int allow_unicodes = LANGUAGE_CPP;
int allow_multibyte = 1;
int allow_cpp_comments = LANGUAGE_CPP;
int allow_dos_newline = 0;
int allow_extra_symbols = 0;
int allow_iso_keywords = LANGUAGE_CPP;
int allow_newline_strings = 0;
int analyse_comments = 1;
unsigned long max_id_length = 1024;


/*
    This table gives the mapping between lexical token numbers and the
    corresponding symbols and keywords.  It is derived from the list of
    tokens in symbols.h.
*/

const char *token_names[] = {
#define LEX_TOKEN(A, B, C)		(B),
#include <parse/symbols.h>
#undef LEX_TOKEN
	NULL
};


/*
    This routine translates the alternative ISO keywords and digraphs
    into their primary form.
*/

int
primary_form(int t)
{
	int u = t;
	switch (u) {
	case lex_and_H2:           u = lex_and_H1;           break;
	case lex_and_Heq_H2:       u = lex_and_Heq_H1;       break;
	case lex_close_Hbrace_H2:  u = lex_close_Hbrace_H1;  break;
	case lex_close_Hsquare_H2: u = lex_close_Hsquare_H1; break;
	case lex_compl_H2:         u = lex_compl_H1;         break;
	case lex_hash_H2:          u = lex_hash_H1;          break;
	case lex_hash_Hhash_H2:    u = lex_hash_Hhash_H1;    break;
	case lex_logical_Hand_H2:  u = lex_logical_Hand_H1;  break;
	case lex_logical_Hor_H2:   u = lex_logical_Hor_H1;   break;
	case lex_not_H2:           u = lex_not_H1;           break;
	case lex_not_Heq_H2:       u = lex_not_Heq_H1;       break;
	case lex_open_Hbrace_H2:   u = lex_open_Hbrace_H1;   break;
	case lex_open_Hsquare_H2:  u = lex_open_Hsquare_H1;  break;
	case lex_or_H2:            u = lex_or_H1;            break;
	case lex_or_Heq_H2:        u = lex_or_Heq_H1;        break;
	case lex_xor_H2:           u = lex_xor_H1;           break;
	case lex_xor_Heq_H2:       u = lex_xor_Heq_H1;       break;
	}
	return u;
}


/*
    This routine reports the digraph t, returning the primary form of t.
*/

int
get_digraph(int t)
{
	int u = primary_form(t);
	if (u != t) {
		update_column();
		report(crt_loc, ERR_lex_digraph_replace(t, u));
	}
	return u;
}


/*
    This routine creates a keyword identifier with name nm and lexical
    token number key.  The special case when key is lex_unknown is used
    to indicate a reserved identifier.
*/

IDENTIFIER
make_keyword(HASHID nm, int key, IDENTIFIER id)
{
	PTR(IDENTIFIER)ptr = hashid_id(nm);
	if (IS_NULL_id(id)) {
		/* Find keyword type */
		unsigned tag = id_keyword_tag;
		if (key >= FIRST_ISO_KEYWORD && key <= LAST_ISO_KEYWORD) {
			tag = id_iso_keyword_tag;
		} else if (key >= FIRST_SYMBOL && key <= LAST_SYMBOL) {
			tag = id_iso_keyword_tag;
		} else if (key == lex_unknown) {
			tag = id_reserved_tag;
		}

		/* Create keyword identifier */
		MAKE_id_keyword_etc(tag, nm, dspec_none, NULL_nspace, crt_loc,
				    id);
		COPY_ulong(id_no(id), (unsigned long)key);
	}
	COPY_id(hashid_cache(nm), NULL_id);
	if (do_keyword) {
		dump_declare(id, &crt_loc, 1);
	}

	/* Add keyword to identifier meanings */
	for (;;) {
		IDENTIFIER pid = DEREF_id(ptr);
		switch (TAG_id(pid)) {
		case id_dummy_tag:
		case id_keyword_tag:
		case id_iso_keyword_tag:
		case id_reserved_tag:
			COPY_id(id_alias(id), pid);
			COPY_id(ptr, id);
			return id;
		}
		ptr = id_alias(pid);
	}
	/* NOTREACHED */
}


/*
    This routine initialises the hash table entries for the keywords.
*/

void
init_keywords(void)
{
	int key;

	/* Set up keyword entries */
	for (key = FIRST_KEYWORD; key <= LAST_KEYWORD; key++) {
		int ext = 0;
		string keyword = token_name(key);
		unsigned long h = hash(keyword);
		if (keyword[0] == char_less) {
			ext = 1;
		}
		KEYWORD(key) = lookup_name(keyword, h, ext, key);
	}

	/* Bring the C keywords into scope */
	for (key = FIRST_C_KEYWORD; key <= LAST_C_KEYWORD; key++) {
		HASHID nm = KEYWORD(key);
		IGNORE make_keyword(nm, key, NULL_id);
	}

	/* Bring the C++ keywords into scope */
	for (key = FIRST_CPP_KEYWORD; key <= LAST_CPP_KEYWORD; key++) {
		HASHID nm = KEYWORD(key);
#if LANGUAGE_CPP
		IGNORE make_keyword(nm, key, NULL_id);
#else
		if (key != lex_wchar_Ht) {
			IGNORE make_keyword(nm, lex_unknown, NULL_id);
		}
#endif
	}

	/* Bring the ISO alternative keywords into scope */
	for (key = FIRST_ISO_KEYWORD; key <= LAST_ISO_KEYWORD; key++) {
		HASHID nm = KEYWORD(key);
		if (allow_iso_keywords) {
			IGNORE make_keyword(nm, key, NULL_id);
		} else {
			IGNORE make_keyword(nm, lex_unknown, NULL_id);
		}
	}

	/* Find underlying dummy identifier for 'operator' */
	underlying_op = DEREF_id(hashid_id(KEYWORD(lex_operator)));
	underlying_op = underlying_id(underlying_op);
	return;
}


/*
    This routine is called after a question mark has been read from the
    input file to allow for trigraphs.  It returns the trigraph replacement
    character or '?' if the following characters do not form a trigraph.
*/

static int
adjust_trigraph(void)
{
	if (allow_trigraphs) {
		int c = next_char();
		if (c == char_end) {
			c = refill_char();
		}
		if (c == char_question) {
			int d;
			c = next_char();
			if (c == char_end) {
				c = refill_char();
			}
			switch (c) {
			case char_close_round:  d = char_close_square; break; /* Map '\?\?)' to ']' */
			case char_equal:        d = char_hash;         break; /* Map '\?\?=' to '#' */
			case char_exclaim:      d = char_bar;          break; /* Map '\?\?!' to '|' */
			case char_greater:      d = char_close_brace;  break; /* Map '\?\?>' to '}' */
			case char_less:         d = char_open_brace;   break; /* Map '\?\?<' to '{' */
			case char_minus:        d = char_tilde;        break; /* Map '\?\?-' to '~' */
			case char_open_round:   d = char_open_square;  break; /* Map '\?\?(' to '[' */
			case char_single_quote: d = char_circum;       break; /* Map '\?\?\'' to '^' */
			case char_slash:        d = char_backslash;    break; /* Map '\?\?/' to '\\' */

			default:
				/* Not a trigraph */
				unread_char(c);
				unread_char(char_question);
				return char_question;
			}
			update_column();
			report(crt_loc, ERR_lex_trigraph_replace(c, d));
			return d;
		} else {
			/* Not a trigraph */
			unread_char(c);
		}
	}
	return char_question;
}


/*
    This routine is called after each carriage return character, checking
    for a following newline character.
*/

static int
read_newline(void)
{
	if (allow_dos_newline) {
		int c = next_char();
		if (c == char_end) {
			c = refill_char();
		}
		if (c == char_newline) {
			return c;
		}
		unread_char(c);
	}
	return char_return;
}


/*
    This routine is called after each terminate character, checking for
    a following end of file character.
*/

static int
read_eof(void)
{
	if (allow_dos_newline) {
		int c = next_char();
		if (c == char_end) {
			c = refill_char();
		}
		if (c == char_eof) {
			return c;
		}
		unread_char(c);
	}
	return char_sub;
}


/*
    This routine reads the next character from the input file, adjusting
    it as necessary for trigraphs and escaped newlines.  This routine
    corresponds to phases 1 and 2 of the phases of translation.
*/

static int
read_char(void)
{
	for (;;) {
		int c = next_char();
		if (c == char_end) {
			c = refill_char();
		}
		if (c == char_question) {
			c = adjust_trigraph();
		}
		if (c != char_backslash) {
			/* Not an escaped newline */
			return c;
		}
		c = next_char();
		if (c == char_end) {
			c = refill_char();
		}
		if (c == char_return) {
			c = read_newline();
		}
		if (c != char_newline) {
			/* Not an escaped newline */
			unread_char(c);
			return char_backslash;
		}
		crt_loc.line++;
		crt_loc.column = 0;
		input_crt = input_posn;
	}
	/* NOTREACHED */
}


/*
    This look-up table gives the various character types.  Note that the
    default look-up table is for ASCII, for other codesets the table
    needs to be rewritten.  The only really interesting points in the
    table itself are that newline has not been classified as a white-space
    and that character char_eof (-1) represents end of file.
*/

#define SPACE_M			0x01
#define ALPHA_M			0x02
#define DIGIT_M			0x04
#define ALNUM_M			0x08
#define PPDIG_M			0x10
#define SYMBL_M			0x20
#define NLINE_M			0x40
#define LEGAL_M			0x80

#define ILLEG			0x00
#define LEGAL			LEGAL_M
#define SPACE			(SPACE_M | LEGAL_M)
#define ALPHA			(ALPHA_M | ALNUM_M | PPDIG_M | LEGAL_M)
#define DIGIT			(DIGIT_M | ALNUM_M | PPDIG_M | LEGAL_M)
#define SYMBL			(SYMBL_M | LEGAL_M)
#define POINT			(PPDIG_M | SYMBL_M | LEGAL_M)
#define NLINE			(NLINE_M | LEGAL_M)

#define main_characters		(characters + 1)
#define lookup_char(C)		((int)main_characters[C])
#define is_white(T)		((T) & SPACE_M)
#define is_alpha(T)		((T) & ALPHA_M)
#define is_digit(T)		((T) & DIGIT_M)
#define is_alphanum(T)		((T) & ALNUM_M)
#define is_ppdigit(T)		((T) & PPDIG_M)
#define is_symbol(T)		((T) & SYMBL_M)
#define is_newline(T)		((T) & NLINE_M)
#define is_legal(T)		((T) & LEGAL_M)

static unsigned char characters[NO_CHAR + 2] = {
	LEGAL,			/* EOF */
#define CHAR_DATA(A, B, C, D)	(A),
#include <parse/char.h>
#undef CHAR_DATA
	ILLEG			/* dummy */
};

static unsigned char *copy_characters = main_characters;


/*
    This routine sets the look-up value for character a to be equal to
    the underlying value for character b.  As a special case, setting
    the look-up for a carriage return to that for newline enables
    DOS-like rules on newline and end of file characters.
*/

void
set_char_lookup(int a, int b)
{
	if (a >= 0 && a < NO_CHAR && b >= 0 && b < NO_CHAR) {
		unsigned char t = copy_characters[b];
		if (a == char_return) {
			if (b == char_newline) {
				/* Set DOS-like newline rules */
				allow_dos_newline = 1;
				return;
			}
			if (b == char_return) {
				/* Unset DOS-like newline rules */
				allow_dos_newline = 0;
			}
		}
		main_characters[a] = t;
	}
	return;
}


/*
    This routine sets the character look-ups for all the elements of the
    string or character literal expression a to be equal to that for the
    character literal expression b.  If b is the null expression then
    the look-up is set to be an illegal character.
*/

void
set_character(EXP a, EXP b)
{
	int c = get_char_value(b);
	if (IS_exp_string_lit(a)) {
		STRING s = DEREF_str(exp_string_lit_str(a));
		unsigned long n = DEREF_ulong(str_simple_len(s));
		string t = DEREF_string(str_simple_text(s));
		unsigned kind = DEREF_unsigned(str_simple_kind(s));
		if (kind & STRING_MULTI) {
			while (n) {
				int ch = CHAR_SIMPLE;
				unsigned long d = get_multi_char(t, &ch);
				if (d < (unsigned long)NO_CHAR) {
					set_char_lookup((int)d, c);
				}
				t += MULTI_WIDTH;
				n--;
			}
		} else {
			while (n) {
				int d = (int)*t;
				set_char_lookup(d, c);
				t++;
				n--;
			}
		}
	} else {
		int d = get_char_value(a);
		if (d != char_illegal) {
			set_char_lookup(d, c);
		}
	}
	return;
}


/*
    This routine checks whether the character a represents a white space.
    The newline character constitutes a special case.
*/

int
is_white_char(unsigned long a)
{
	int t;
	if (a >= NO_CHAR) {
		return 0;
	}
	t = lookup_char(a);
	return is_white(t) || is_newline(t);
}


/*
    This routine checks whether the character a represents an alphabetic
    character.
*/

int
is_alpha_char(unsigned long a)
{
	if (a >= NO_CHAR) {
		return 0;
	}
	return is_alpha(lookup_char(a));
}


/*
    This routine checks whether the character a represents a legal character.
*/

int
is_legal_char(unsigned long a)
{
	if (a >= NO_CHAR) {
		return 0;
	}
	return is_legal(lookup_char(a));
}


/*
    This routine tests whether the next character is a (which will not be
    newline).  If so the current character is advanced one, otherwise it
    is left unchanged.  legal is set to false if the next character is
    not legal.
*/

int
peek_char(int a, int *legal)
{
	int c = read_char();
	assert(a != char_newline);
	if (c == a) {
		return 1;
	}
	*legal = is_legal_char((unsigned long)c);
	unread_char(c);
	return 0;
}


/*
    This buffer is used by read_token to hold the values of identifiers,
    numbers and strings.
*/

BUFFER token_buff = NULL_buff;


/*
    These macros are used to identify the start or end of certain tokens
    such as comments and strings.
*/

#define START_COMMENT(A)	((A) == char_asterix)
#define END_COMMENT(A, B)	((A) == char_asterix && (B) == char_slash)
#define START_CPP_COMMENT(A)	((A) == char_slash && allow_cpp_comments)
#define END_CPP_COMMENT(A)	((A) == char_newline)
#define START_STRING(A)		((A) == char_quote || (A) == char_single_quote)
#define END_STRING(A, Q)	((A) == (Q))


/*
    Each source file should end in a newline character, which is not
    preceded by a backspace.  This flag is used to indicate whether the
    end of the present file has the correct form.
*/

static int good_eof = 0;


/*
    This routine skips a string or character literal.  It is entered after
    the initial quote, q, has been read.  Escape sequences are always
    allowed.  The routine returns lex_string_Hlit if the string terminates
    correctly and lex_eof otherwise.
*/

static int
skip_string(int q)
{
	int e = q;
	LOCATION loc;
	unsigned nl = 0;
	int escaped = 0;
	int have_char = 0;
	int allow_nl = allow_newline_strings;
	if (e == char_single_quote || in_preproc_dir == 1) {
		allow_nl = 0;
	}
	update_column();
	loc = crt_loc;

	/* Scan to end of string */
	for (;;) {
		int c = read_char();
		if (END_STRING(c, e) && !escaped) {
			if (e == char_single_quote && !have_char) {
				update_column();
				report(crt_loc, ERR_lex_ccon_empty());
			}
			if (nl) {
				report(loc, ERR_lex_string_nl(nl, nl));
			}
			return lex_string_Hlit;
		}
		if (c == char_newline) {
			if (allow_nl) {
				/* Report newlines but continue */
				crt_loc.line++;
				crt_loc.column = 0;
				input_crt = input_posn;
				nl++;
			} else {
				unread_char(c);
				update_column();
				report(crt_loc, ERR_lex_string_pp_nl());
				break;
			}
		} else if (c == char_eof) {
			report(loc, ERR_lex_phases_str_eof());
			good_eof = 1;
			nl = 0;
			break;
		}
		if (escaped) {
			escaped = 0;
		} else {
			if (c == char_backslash) {
				escaped = 1;
			}
		}
		if (!escaped) {
			have_char = 1;
		}
	}
	if (nl) {
		/* Report newlines in string */
		report(loc, ERR_lex_string_nl(nl, nl));
	} else {
		/* Don't bother with error recovery */
		/* EMPTY */
	}
	return lex_eof;
}


/*
    This routine reads the body of a string or character literal or of a
    header name.  It is entered after the initial quote has been read.
    The corresponding close quote is passed in as q.  The esc argument
    indicates whether escape sequences are allowed (they are not in
    header names for example).  The string itself is built up in
    token_buff.  The routine returns lex_string_Hlit if the string
    terminates correctly and lex_eof otherwise.  It also sets
    token_buff.posn to point to the end of the string.
*/

int
read_string(int q, int esc)
{
	int c;
	int e = q;
	LOCATION loc;
	long posn = -1;
	int escaped = 0;
	unsigned nl = 0;
	int have_char = 0;
	string s = token_buff.start;
	string se = token_buff.end;
	int allow_nl = allow_newline_strings;
	update_column();
	if (e == char_single_quote) {
		posn = tell_buffer(crt_buff_no);
		allow_nl = 0;
	} else if (in_preproc_dir == 1) {
		allow_nl = 0;
	}
	loc = crt_loc;

	/* Scan the string */
	for (;;) {
		c = read_char();
		if (END_STRING(c, e) && !escaped) {
			if (e == char_single_quote && !have_char) {
				update_column();
				report(crt_loc, ERR_lex_ccon_empty());
			}
			if (nl) {
				report(loc, ERR_lex_string_nl(nl, nl));
			}
			token_buff.posn = s;
			*s = 0;
			return lex_string_Hlit;
		}
		if (c == char_newline) {
			if (allow_nl) {
				/* Report newlines but continue */
				crt_loc.line++;
				crt_loc.column = 0;
				input_crt = input_posn;
				nl++;
			} else {
				unread_char(c);
				update_column();
				if (e == char_greater) {
					/* Header name */
					report(crt_loc,
					       ERR_cpp_include_incompl());
				} else {
					report(crt_loc, ERR_lex_string_pp_nl());
				}
				break;
			}
		} else if (c == char_eof) {
			report(loc, ERR_lex_phases_str_eof());
			good_eof = 1;
			nl = 0;
			break;
		}
		*s = (character)c;
		if (++s == se) {
			s = extend_buffer(&token_buff, s);
			se = token_buff.end;
		}
		if (escaped) {
			escaped = 0;
		} else {
			if (c == char_backslash) {
				escaped = esc;
			}
		}
		if (!escaped)have_char = 1;
	}
	if (nl) {
		/* Report newlines in string */
		report(loc, ERR_lex_string_nl(nl, nl));
	} else {
		/* Error recovery */
		if (e == char_single_quote && have_char) {
			seek_buffer(crt_buff_no, posn, 1);
			crt_loc = loc;
			s = token_buff.start;
			c = read_char();
			*(s++) = (character)c;
			if (c == char_backslash && esc) {
				c = read_char();
				*(s++) = (character)c;
			}
		}
	}
	token_buff.posn = s;
	*s = 0;
	return lex_eof;
}


/*
    This routine skips a C style comment, returning lex_ignore_token if
    the comment is terminated correctly and lex_eof otherwise.  It is
    entered after the first two characters comprising the comment start
    have been read.  If keep is true then the comment text is built up
    in token_buff, otherwise it is discarded.
*/

static int
skip_comment(int keep)
{
	int c = 0;
	int lastc;
	string s, se;
	LOCATION loc;
	update_column();
	loc = crt_loc;
	if (keep) {
		s = token_buff.start;
		se = token_buff.end;
	} else {
		s = NULL;
		se = NULL;
	}
	do {
		lastc = c;
read_label:
		/* Inlined version of read_char */
		c = next_char();
		if (c == char_end) {
			c = refill_char();
		}
		if (c == char_question) {
			c = adjust_trigraph();
		}
		if (c == char_backslash) {
			c = next_char();
			if (c == char_end) {
				c = refill_char();
			}
			if (c == char_return) {
				c = read_newline();
			}
			if (c == char_newline) {
				/* Allow for escaped newlines */
				crt_loc.line++;
				crt_loc.column = 0;
				input_crt = input_posn;
				goto read_label;
			}
			unread_char(c);
			c = char_backslash;
		} else if (c == char_newline) {
			/* New line characters */
			crt_loc.line++;
			crt_loc.column = 0;
			input_crt = input_posn;
			crt_line_changed = 1;
			crt_spaces = 0;
		} else if (c == char_eof) {
			/* End of file characters */
			report(loc, ERR_lex_phases_comm_eof());
			good_eof = 1;
			if (s) {
				token_buff.posn = s;
				*s = 0;
			}
			return lex_eof;
		} else if (c == char_asterix && lastc == char_slash) {
			/* Nested comments */
			update_column();
			report(crt_loc, ERR_lex_comment_nest());
		}
		if (s) {
			*s = (character)c;
			if (++s == se) {
				s = extend_buffer(&token_buff, s);
				se = token_buff.end;
			}
		}
	} while (!END_COMMENT(lastc, c));
	if (s) {
		s -= 2;
		token_buff.posn = s;
		*s = 0;
	}
	crt_spaces++;
	return lex_ignore_token;
}


/*
    This routine skips a C++ style comment, returning lex_ignore_token
    if the comment terminates correctly and lex_eof otherwise.  It is
    entered after the first two characters comprising the comment start
    have been read.  The next token read after the comment will be the
    terminating newline.  If keep is true then the comment text is built
    up in token_buff, otherwise it is discarded.
*/

static int
skip_cpp_comment(int keep)
{
	int c;
	string s, se;
	if (keep) {
		s = token_buff.start;
		se = token_buff.end;
	} else {
		s = NULL;
		se = NULL;
	}
	do {
read_label:
		/* Inlined version of read_char */
		c = next_char();
		if (c == char_end) {
			c = refill_char();
		}
		if (c == char_question) {
			c = adjust_trigraph();
		}
		if (c == char_backslash) {
			c = next_char();
			if (c == char_end) {
				c = refill_char();
			}
			if (c == char_return) {
				c = read_newline();
			}
			if (c == char_newline) {
				/* Allow for escaped newlines */
				crt_loc.line++;
				crt_loc.column = 0;
				input_crt = input_posn;
				goto read_label;
			}
			unread_char(c);
			c = char_backslash;
		} else if (c == char_eof) {
			/* End of file characters */
			update_column();
			report(crt_loc, ERR_lex_phases_comm_eof());
			good_eof = 1;
			if (s) {
				token_buff.posn = s;
				*s = 0;
			}
			return lex_eof;
		}
		if (s) {
			*s = (character)c;
			if (++s == se) {
				s = extend_buffer(&token_buff, s);
				se = token_buff.end;
			}
		}
	} while (!END_CPP_COMMENT(c));
	unread_char(c);
	if (s) {
		s -= 1;
		token_buff.posn = s;
		*s = 0;
	}
	crt_line_changed = 1;
	crt_spaces = 0;
	return lex_ignore_token;
}


/*
    This routine skips any white-space characters (including comments).
    Newline characters are treated as white-space only if nl is true.
    The result is a bitpattern formed from the components:

	WHITE_SPACE		for white-space characters;
	WHITE_NEWLINE		for newline characters;
	WHITE_ESC_NEWLINE	for escaped newlines;

    the result being reset to WHITE_NEWLINE after each newline.  Note that
    trigraphs and escaped newlines are treated by hand.  The effect of this
    routine is that all non-empty sequences of white-space characters other
    than newlines are treated as if they were a single space (the C/C++
    specification says that this is implementation-defined).
*/

unsigned long
skip_white(int nl)
{
	int c;
	unsigned long sp = 0;
	for (;;) {
		c = next_char();
		if (c == char_end) {
			c = refill_char();
		}
		if (c == char_return) {
			c = read_newline();
		}
		if (c == char_sub) {
			c = read_eof();
		}
		if (c == char_newline) {
			/* Deal with newline characters */
			if (!nl) {
				break;
			}
			sp = WHITE_NEWLINE;
			crt_loc.line++;
			crt_loc.column = 0;
			input_crt = input_posn;
			crt_line_changed = 1;
			crt_spaces = 0;
		} else if (c == char_space) {
			/* Deal with simple spaces */
			sp |= WHITE_SPACE;
			crt_spaces++;
		} else if (c == char_tab) {
			/* Deal with tab characters */
			unsigned long tab = tab_width;
			sp |= WHITE_SPACE;
			crt_spaces = tab *(crt_spaces / tab + 1);
		} else if (c == char_eof) {
			/* End of file */
			if (sp == WHITE_NEWLINE) {
				good_eof = 1;
			}
			break;
		} else {
			int t;
			if (is_extended(c)) {
				break;
			}
			t = lookup_char(c);
			if (is_white(t)) {
				/* Deal with other white space characters */
				sp |= WHITE_SPACE;
				crt_spaces++;
			} else {
				if (c == char_question)c = adjust_trigraph();
				if (c == char_slash) {
					/* Deal with comments */
					int b = read_char();
					if (START_COMMENT(b)) {
						sp |= WHITE_SPACE;
						b = skip_comment(0);
						if (b == lex_eof)  {
							return sp;
						}
					} else if (START_CPP_COMMENT(b)) {
						sp |= WHITE_SPACE;
						b = skip_cpp_comment(0);
						if (b == lex_eof) {
							return sp;
						}
						if (!nl) {
							return sp;
						}
					} else {
						unread_char(b);
						break;
					}
				} else if (c == char_backslash) {
					/* Deal with escaped newlines */
					int b = next_char();
					if (b == char_end) {
						b = refill_char();
					}
					if (b == char_return) {
						b = read_newline();
					}
					if (b == char_newline) {
						crt_loc.line++;
						crt_loc.column = 0;
						input_crt = input_posn;
					} else {
						unread_char(b);
						break;
					}
					sp |= WHITE_ESC_NEWLINE;
				} else {
					break;
				}
			}
		}
	}
	unread_char(c);
	return sp;
}


/*
    Calling skip_white ( 1 ) can mess up the parser as regards spotting
    preprocessing directives and valid end of file markers.  This routine
    may be called with the return value of skip_white as an argument to
    patch up the buffer in order to get the parser back into the right
    state.
*/

void
patch_white(unsigned long sp)
{
	if (sp & WHITE_NEWLINE) {
		if (sp & WHITE_SPACE) {
			/* Patch in a space after a newline */
			unsigned long n;
			update_column();
			n = crt_loc.column;
			while (n) {
				unread_char(char_space);
				if (input_posn <= input_start) {
					break;
				}
				n--;
			}
		} else if (sp & WHITE_ESC_NEWLINE) {
			/* Patch in an escaped newline after a newline */
			unread_char(char_backslash);
			unread_char(char_newline);
			crt_loc.line--;
		}
		/* Patch in a newline */
		unread_char(char_newline);
		crt_loc.line--;
		crt_loc.column = 0;
		crt_spaces = 0;
	}
	return;
}


/*
    This routine skips to the end of the current line.  It returns 0 if
    only white-space characters are encountered.  It uses skip_white to
    jump over white-space (including comments).
*/

int
skip_to_end(void)
{
	int c;
	int res = 0;
	in_preproc_dir = 0;
	for (;;) {
		IGNORE skip_white(0);
read_label:
		/* Inlined version of read_char */
		c = next_char();
		if (c == char_end) {
			c = refill_char();
		}
		if (c == char_question) {
			c = adjust_trigraph();
		}
		if (c == char_backslash) {
			c = next_char();
			if (c == char_end) {
				c = refill_char();
			}
			if (c == char_return) {
				c = read_newline();
			}
			if (c == char_newline) {
				/* Allow for escaped newlines */
				crt_loc.line++;
				crt_loc.column = 0;
				input_crt = input_posn;
				goto read_label;
			}
			unread_char(c);
		} else if (c == char_newline) {
			/* New line characters */
			crt_loc.line++;
			crt_loc.column = 0;
			input_crt = input_posn;
			crt_line_changed = 1;
			crt_spaces = 0;
			return res;
		} else if (START_STRING(c)) {
			/* String literals */
			res = 1;
			c = skip_string(c);
			if (c == lex_eof) {
				return res;
			}
		} else if (c == char_eof) {
			/* End of file characters */
			break;
		} else {
			res = 1;
		}
	}
	update_column();
	report(crt_loc, ERR_lex_phases_eof());
	good_eof = 1;
	return res;
}


/*
    This routine reads a unicode character.  It is entered after the
    initial backslash and the following character, c, have been read.
    It assigns the character type to pc and returns the character code.
*/

static unsigned long
read_unicode(int c, int *pc)
{
	unsigned i, n;
	unsigned long u;
	character s[10];
	ERROR err = NULL_err;
	string p = s;
	if (c == char_u && allow_unicodes) {
		/* Read '\uxxxx' */
		*pc = CHAR_UNI4;
		n = 4;
	} else if (c == char_U && allow_unicodes) {
		/* Read '\Uxxxxxxxx' */
		*pc = CHAR_UNI8;
		n = 8;
	} else {
		unread_char(c);
		*pc = CHAR_NONE;
		return 0;
	}
	for (i = 0; i < n; i++) {
		int t;
		int d = read_char();
		if (d == char_eof) {
			break;
		}
		if (is_extended(d)) {
			unread_char(d);
			break;
		}
		t = lookup_char(d);
		if (!is_alphanum(t)) {
			unread_char(d);
			break;
		}
		s[i] = (character)d;
	}
	s[i] = 0;
	u = eval_unicode(c, n, pc, &p, &err);
	if (!IS_NULL_err(err)) {
		update_column();
		report(crt_loc, err);
	}
	return u;
}


/*
    This routine reads an extended identifier name (one including a unicode
    character).  It is entered after reading the simple characters in the
    token buffer plus the unicode character given by u and ch.
*/

static HASHID
read_extended_id(unsigned long u, int ch)
{
	string s;
	int c, t;
	HASHID nm;
	unsigned long h;
	BUFFER *bf = &token_buff;
	do {
		if (!unicode_alpha(u)) {
			/* Report illegal identifiers */
			update_column();
			report(crt_loc, ERR_lex_name_extendid(u));
		}
		print_char(u, ch, 0, bf);
		for (;;) {
			c = read_char();
			if (is_extended(c)) {
				break;
			}
			t = lookup_char(c);
			if (!is_alphanum(t)) {
				break;
			}
			bfputc(bf, c);
		}
		ch = CHAR_NONE;
		if (c == char_backslash) {
			int nextc = read_char();
			u = read_unicode(nextc, &ch);
		}
	} while (ch != CHAR_NONE);
	unread_char(c);
	bfputc(bf, 0);
	s = bf->start;
	h = hash(s);
	nm = lookup_name(s, h, 1, lex_unknown);
	return nm;
}


/*
    The hash value for identifiers is built up as the identifier is read.
    It is then stored in this variable.  The algorithm for calculuating
    the hash value needs to be kept in step with the routine hash (it
    is checked by an assertion in lookup_name, so any errors should be
    caught quickly if in debug mode).
*/

HASHID token_hashid = NULL_hashid;


/*
    This routine reads the next preprocessing token from the input file.
    It is designed for speed rather than elegance, hence the rather
    indiscriminate use of labels.  Trigraphs and escaped newlines
    involving the first character are processed by hand.  This routine
    corresponds to phase 3 of the phases of translation.  The position
    within the line is tracked by column - this is zero at the start of
    a line, positive if only white space has been read and negative
    otherwise.  preproc keeps track of the last preprocessing directive.
*/

int
read_token(void)
{
	int c, t;
	int column = -1;
	int preproc = lex_ignore_token;

	/* Read the next character */
start_label:
	c = next_char();
	if (c == char_end)c = refill_char();
restart_label:
	if (is_extended(c)) {
		goto unknown_label;
	}
	t = lookup_char(c);
	if (is_white(t)) {
		crt_spaces++;
		goto start_label;
	}
process_label:
	/* Process the next character */

	/* Check symbols and punctuation */
	if (is_symbol(t)) {
		switch (c) {

		case char_question: {
			/* Deal with '?' and trigraphs */
			c = adjust_trigraph();
			if (c == char_question) return lex_question;
			goto restart_label;
		}

		case char_backslash: {
			/* Deal with escaped newlines */
			unsigned long u;
			int ch = CHAR_NONE;
			int nextc = next_char();
			if (nextc == char_end)nextc = refill_char();
			if (nextc == char_return)nextc = read_newline();
			if (nextc == char_newline) {
				crt_loc.line++;
				crt_loc.column = 0;
				input_crt = input_posn;
				if (column == 0)column = 1;
				goto start_label;
			}

			/* Check for unicode characters */
			u = read_unicode(nextc, &ch);
			if (ch != CHAR_NONE) {
				token_buff.posn = token_buff.start;
				token_hashid = read_extended_id(u, ch);
				return lex_identifier;
			}
			return lex_backslash;
		}

		case char_hash:
			/* Deal with '#' and '##' */
			c = read_char();
			if (c == char_hash) {
				return lex_hash_Hhash_H1;
			}
			unread_char(c);

			/* Return with '#' if not at start of line */
			if (column < 0 || no_preproc_dir) {
				return lex_hash_H1;
			}

			/* Deal with preprocessing directives */
preproc_label:	{
			unsigned long sp = skip_white(0);
			update_column();
			if (column) {
				report(crt_loc, ERR_cpp_indent());
			}
			if (sp & (WHITE_SPACE | WHITE_ESC_NEWLINE)) {
				report(preproc_loc, ERR_cpp_indent_dir());
			}
			preproc = read_preproc_dir(1, preproc);
			if (preproc < 0) {
				goto start_line_label;
			}
			unread_char(char_newline);
			crt_loc.line--;
			crt_loc.column = 0;
			return preproc;
		}

		case char_percent:
			/* Deal with '%', '%=', '%>', '%:' and '%:%:' */
			c = read_char();
			if (c == char_equal) {
				return lex_rem_Heq;
			}
			if (c == char_greater && allow_digraphs) {
				return lex_close_Hbrace_H2;
			}
			if (c == char_colon && allow_digraphs) {
				/* Check for '%:' and '%:%:' */
				c = read_char();
				if (c == char_percent) {
					int nextc = read_char();
					if (nextc == char_colon) {
						return lex_hash_Hhash_H2;
					}
					unread_char(nextc);
				}
				unread_char(c);

				/* Return with '%:' if not at start of line */
				if (column < 0 || no_preproc_dir) {
					return lex_hash_H2;
				}

				/* Otherwise this is a preprocessing
				 * directive */
				IGNORE get_digraph(lex_hash_H2);
				goto preproc_label;
			}
			unread_char(c);
			return lex_rem;

		case char_quote:
			/* Deal with string literals */
			IGNORE read_string(c, 1);
			return lex_string_Hlit;

		case char_single_quote:
			/* Deal with character literals */
			IGNORE read_string(c, 1);
			return lex_char_Hlit;

		case char_exclaim:
			/* Deal with '!' and '!=' */
			c = read_char();
			if (c == char_equal) {
				return lex_not_Heq_H1;
			}
			unread_char(c);
			return lex_not_H1;

		case char_ampersand:
			/* Deal with '&', '&&' and '&=' */
			c = read_char();
			if (c == char_ampersand) {
				return lex_logical_Hand_H1;
			}
			if (c == char_equal) {
				return lex_and_Heq_H1;
			}
			unread_char(c);
			return lex_and_H1;

		case char_asterix:
			/* Deal with '*' and '*=' */
			c = read_char();
			if (c == char_equal) {
				return lex_star_Heq;
			}
			unread_char(c);
			return lex_star;

		case char_plus:
			/* Deal with '+', '++' and '+=' */
			c = read_char();
			if (c == char_plus) {
				return lex_plus_Hplus;
			}
			if (c == char_equal) {
				return lex_plus_Heq;
			}
			if (c == char_question && allow_extra_symbols) {
				return lex_abs;
			}
			unread_char(c);
			return lex_plus;

		case char_minus:
			/* Deal with '-', '--', '-=', '->' and '->*' */
			c = read_char();
			if (c == char_minus) {
				return lex_minus_Hminus;
			}
			if (c == char_equal) {
				return lex_minus_Heq;
			}
			if (c == char_greater) {
#if LANGUAGE_CPP
				/* '->*' is only allowed in C++ */
				c = read_char();
				if (c == char_asterix) {
					return lex_arrow_Hstar;
				}
				unread_char(c);
#endif
				return lex_arrow;
			}
			unread_char(c);
			return lex_minus;

		case char_dot:
			/* Deal with '.', '...', '.*' and numbers */
			c = read_char();
			if (c == char_dot) {
				c = read_char();
				if (c == char_dot) {
					return lex_ellipsis;
				}
				unread_char(c);
				unread_char(char_dot);
				return lex_dot;
			}
#if LANGUAGE_CPP
			/* '.*' is only allowed in C++ */
			if (c == char_asterix) {
				return lex_dot_Hstar;
			}
#endif
			if (is_extended(c)) {
				unread_char(c);
				return lex_dot;
			}
			t = lookup_char(c);
			if (is_digit(t)) {
				/* Indicate a number with first digit '.' */
				t = POINT;
				goto number_label;
			}
			unread_char(c);
			return lex_dot;

		case char_slash:
			/* Deal with '/', '/=' and comments */
			c = read_char();
			if (START_COMMENT(c)) {
				int a = analyse_comments;
				c = skip_comment(a);
				if (c == lex_eof) {
					goto eof_label;
				}
				if (a) {
					c = lint_comment();
					if (c >= 0) return c;
				}
				if (column == 0) {
					column = 1;
				}
				goto start_label;
			}
			if (START_CPP_COMMENT(c)) {
				int a = analyse_comments;
				c = skip_cpp_comment(a);
				if (c == lex_eof) {
					goto eof_label;
				}
				if (a) {
					c = lint_comment();
					if (c >= 0) {
						return c;
					}
				}
				IGNORE read_char();
				goto newline_label;
			}
			if (c == char_equal) {
				return lex_div_Heq;
			}
			unread_char(c);
			return lex_div;

		case char_colon:
			/* Deal with ':', '::' and ':>' */
			c = read_char();
#if LANGUAGE_CPP
			/* '::' is only allowed in C++ */
			if (c == char_colon) {
				return lex_colon_Hcolon;
			}
#endif
			if (c == char_greater && allow_digraphs) {
				return lex_close_Hsquare_H2;
			}
			unread_char(c);
			return lex_colon;

		case char_less:
			/* Deal with '<', '<=', '<<', '<<=', '<%', '<:' */
			c = read_char();
			if (c == char_equal) {
				return lex_less_Heq;
			}
			if (c == char_less) {
				c = read_char();
				if (c == char_equal) {
					return lex_lshift_Heq;
				}
				unread_char(c);
				return lex_lshift;
			}
			if (c == char_percent && allow_digraphs) {
				return lex_open_Hbrace_H2;
			}
			if (c == char_colon && allow_digraphs) {
				return lex_open_Hsquare_H2;
			}
			if (c == char_question && allow_extra_symbols) {
				return lex_min;
			}
			unread_char(c);
			return lex_less;

		case char_equal:
			/* Deal with '=' and '==' */
			c = read_char();
			switch (c) {
			case char_equal:
				return lex_eq;
			case char_ampersand:
			case char_asterix:
			case char_minus:
			case char_plus:
				update_column();
				report(crt_loc, ERR_lex_op_old_assign(c, c));
				break;
			}
			unread_char(c);
			return lex_assign;

		case char_greater:
			/* Deal with '>', '>=', '>>' and '>>=' */
			c = read_char();
			if (c == char_equal) {
				return lex_greater_Heq;
			}
			if (c == char_greater) {
				c = read_char();
				if (c == char_equal) {
					return lex_rshift_Heq;
				}
				unread_char(c);
				return lex_rshift;
			}
			if (c == char_question && allow_extra_symbols) {
				return lex_max;
			}
			unread_char(c);
			return lex_greater;

		case char_circum:
			/* Deal with '^' and '^=' */
			c = read_char();
			if (c == char_equal) {
				return lex_xor_Heq_H1;
			}
			unread_char(c);
			return lex_xor_H1;

		case char_bar:
			/* Deal with '|', '||' and '|=' */
			c = read_char();
			if (c == char_bar) {
				return lex_logical_Hor_H1;
			}
			if (c == char_equal) {
				return lex_or_Heq_H1;
			}
			unread_char(c);
			return lex_or_H1;

		case char_open_round:   return lex_open_Hround;      /* Deal with '(' */
		case char_close_round:  return lex_close_Hround;     /* Deal with ')' */
		case char_comma:        return lex_comma;            /* Deal with ',' */
		case char_semicolon:    return lex_semicolon;        /* Deal with ';' */
		case char_open_square:  return lex_open_Hsquare_H1;  /* Deal with '[' */
		case char_close_square: return lex_close_Hsquare_H1; /* Deal with ']' */
		case char_open_brace:   return lex_open_Hbrace_H1;   /* Deal with '{' */
		case char_close_brace:  return lex_close_Hbrace_H1;  /* Deal with '}' */
		case char_tilde:        return lex_compl_H1;         /* Deal with '~' */

		default:
			/* Anything else is an unknown character */
			goto unknown_label;
		}
	}

	/* Read an identifier (calculating hash value on fly) */
	if (is_alpha(t)) {
		HASHID nm;
		LOCATION loc;
		BUFFER *bf = &token_buff;
		string s = bf->start;
		string se = bf->end;
		unsigned long h = (unsigned long)c;
		*(s++) = (character)c;

		/* Get the second character */
		update_column();
		loc = crt_loc;
		c = read_char();
		t = (is_extended(c)? ILLEG : lookup_char(c));
		if (is_alphanum(t)) {
			/* Scan the third and subsequent characters */
			do {
				h = HASH_POWER * h + (unsigned long)c;
				*s = (character)c;
				if (++s == se) {
					s = extend_buffer(bf, s);
					se = bf->end;
				}
				c = read_char();
				if (is_extended(c)) {
					break;
				}
				t = lookup_char(c);
			} while (is_alphanum(t));
		} else {
			/* Allow for wide strings and characters */
			if (h == char_L && is_symbol(t)) {
				if (c == char_quote) {
					IGNORE read_string(c, 1);
					return lex_wstring_Hlit;
				}
				if (c == char_single_quote) {
					IGNORE read_string(c, 1);
					return lex_wchar_Hlit;
				}
			}
			/* Identifier of length one */
		}
		if (c == char_backslash) {
			/* Allow for extended identifiers */
			int ch = CHAR_NONE;
			int nextc = read_char();
			unsigned long u = read_unicode(nextc, &ch);
			if (ch != CHAR_NONE) {
				bf->posn = s;
				nm = read_extended_id(u, ch);
				goto identifier_label;
			}
		}
		unread_char(c);
		se = s;
		*se = 0;

		/* Look up the symbol in the hash table */
		h %= HASH_SIZE;
		s = bf->start;
		nm = lookup_name(s, h, 0, lex_unknown);
identifier_label:
		{
			IDENTIFIER id = DEREF_id(hashid_id(nm));
			while (!IS_id_dummy(id)) {
				/* Scan to last hidden value */
				id = DEREF_id(id_alias(id));
			}
			COPY_loc(id_loc(id), loc);
		}
		token_hashid = nm;
		return lex_identifier;
	}

	/* Read the first token in a line */
	if (c == char_return) {
		c = read_newline();
	}
	if (c == char_newline) {
newline_label:
		/* Re-entry point after C++ style comments */
		crt_loc.line++;
		crt_loc.column = 0;
		input_crt = input_posn;
		crt_line_changed = 1;
		crt_spaces = 0;
		if (in_preproc_dir == 1) {
			in_preproc_dir = 0;
			return lex_newline;
		}
start_line_label:
		/* Re-entry point after preprocessing directives */
		column = 0;
		for (;;) {
			/* Step over any obvious spaces */
			c = next_char();
			if (c == char_end) {
				c = refill_char();
			}
			if (c == char_return) {
				c = read_newline();
			}
			if (c == char_sub) {
				c = read_eof();
			}
			if (c == char_newline) {
				crt_loc.line++;
				crt_loc.column = 0;
				input_crt = input_posn;
				crt_line_changed = 1;
				crt_spaces = 0;
				column = 0;
			} else if (c == char_eof) {
				/* Check for end of file (should start line) */
				if (column == 0) {
					good_eof = 1;
				}
				goto eof_label;
			} else if (c == char_space) {
				crt_spaces++;
				column = 1;
			} else if (c == char_tab) {
				unsigned long tab = tab_width;
				crt_spaces = tab *(crt_spaces / tab + 1);
				column = 1;
			} else {
				if (is_extended(c)) {
					t = ILLEG;
					break;
				}
				t = lookup_char(c);
				if (is_white(t)) {
					if (!is_newline(t)) {
						crt_spaces++;
						column = 1;
					}
				} else {
					break;
				}
			}
		}
		/* c and t now hold the next character */
		goto process_label;
	}

	/* Read a pp-number */
	if (is_digit(t)) {
number_label:	{
			int lastc;
			BUFFER *bf = &token_buff;
			string s = bf->start;
			string se = bf->end;
			if (t == POINT) {
				/* t is set to POINT to indicate an initial
				 * '.' */
				*(s++) = char_dot;
			}
digit_label:
			/* Step over alphanumeric characters and '.' */
			do {
				*s = (character)c;
				if (++s == se) {
					s = extend_buffer(bf, s);
					se = bf->end;
				}
next_digit_label:
				lastc = c;
				c = read_char();
				if (is_extended(c)) {
					break;
				}
				t = lookup_char(c);
			} while (is_ppdigit(t));
			if (c == char_plus || c == char_minus) {
				/* Allow for [Ee][+-] */
				if (lastc == char_e || lastc == char_E) {
					goto digit_label;
				}
			}
			if (c == char_backslash) {
				/* Allow for unicode characters */
				int ch = CHAR_NONE;
				int nextc = read_char();
				unsigned long u = read_unicode(nextc, &ch);
				if (ch != CHAR_NONE) {
					bf->posn = s;
					print_char(u, ch, 0, bf);
					s = bf->posn;
					se = bf->end;
					goto next_digit_label;
				}
			}
			*s = 0;
			unread_char(c);
		}
		return lex_integer_Hlit;
	}

	/* End of file marker */
	if (c == char_sub) {
		c = read_eof();
	}
	if (c == char_eof) {
eof_label:
		if (in_preproc_dir != 0) {
			return lex_eof;
		}
		if (!good_eof) {
			update_column();
			report(crt_loc, ERR_lex_phases_eof());
			good_eof = 1;
		}
		if (end_include(preproc)) {
			/* Revert to previous file */
			good_eof = 0;
			preproc = lex_ignore_token;
			goto start_line_label;
		}
		/* End of main file */
		return lex_eof;
	}

	/* Unknown characters */
unknown_label:
	{
		string s = token_buff.start;
		add_multi_char(s, (unsigned long)c, CHAR_SIMPLE);
		return lex_unknown;
	}
}


/*
    This routine initialises the tables of character look-ups and the token
    buffer.
*/

void
init_char(void)
{
	int i;
	unsigned char *p, *q;

	/* Set native locale for multibyte characters */
	if (allow_multibyte) {
		IGNORE setlocale(LC_CTYPE, "");
	}

	/* Allow for non-ASCII codesets */
	init_ascii();
	map_ascii(main_characters);
	map_ascii(digit_values);
	map_ascii(escape_sequences);

	/* Set up extra characters */
	p = xmalloc_nof(unsigned char, NO_CHAR);
	q = main_characters;
	copy_characters = p;
	for (i = 0; i < NO_CHAR; i++) {
		*(p++) = *(q++);
	}

	/* Initialise token buffer */
	token_buff.posn = extend_buffer(&token_buff, token_buff.posn);
	return;
}


/*
    This routine initialises the lexical analysis routines in preparation
    for parsing or preprocessing the current input file.
*/

void
init_lex(void)
{
	/* Initialise file variables */
	crt_buff_no = 0;
	IGNORE init_buffer(crt_buff_no);
	start_preproc_if ();
	preproc_loc = crt_loc;
	have_syntax_error = 0;
	if (do_header) {
		dump_start(&crt_loc, NIL(INCL_DIR));
	}

	/* Deal with first start-up file */
	open_startup();

	/* Force processing to start at the beginning of a line */
	unread_char(char_newline);
	crt_loc.line--;

	/* Initialise the parser */
	init_parser(NIL(PPTOKEN));
	return;
}


/*
    This routine is the main entry point for the parsing of the current
    input file.
*/

void
process_file(void)
{
	init_lex();
	ADVANCE_LEXER;
	parse_file(NULL_type, dspec_none);
	return;
}
