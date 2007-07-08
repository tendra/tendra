/*
 * Comment-stripping example for lexi. See comments.lxi for details.
 *
 * $Id$
 */

#include <stdio.h>

/*
 * Support functions for the generated lexer.
 */
int unread_char(int c);
int read_char(void);
int skip_single_comment(int c0, int c1);
int skip_block_comment(int c0, int c1);
int pass_string(int c);
int unknown_token(int c);

/* lexemes */
enum {
	lex_unknown
};

#include "comments.c"

char word[256];

int unknown_token(int c) {
	if(c == EOF) {
		return LEX_EOF;
	}

	putc(c, stdout);

	return c;
}

int unread_char(int c) {
	/*
	 * XXX This is slightly hacky; we should maintain our own
	 * buffer and not assume that POSIX can unget multiple characters.
	 */
	return ungetc(c, stdin);
}

int read_char(void) {
	int c;

	c = fgetc(stdin);

	return c;
}

/*
 * Skip through a single-line string, outputting its contents.
 *
 * This example illustrated two tokens coding for one function;
 * this function deals with escaping characters for both double-quoted
 * and single-quoted strings, depending on which delimiter is used.
 */
int pass_string(int delim) {
	int c;
	int inescape = 0;

	putc(delim, stdout);

	for(;;) {
		c = read_char();

		if(c == EOF) {
			return LEX_EOF;
		}

		putc(c, stdout);

		/*
		 * If we're in an escape sequence, this character takes us out of it.
		 * If we're not, then a \ takes us into one.
		 */
		if(inescape) {
			inescape = 0;
		} else if(c == '\\') {
			inescape = 1;
		}

		if(!inescape && c == delim) {
			return lex_unknown;
		}
	}
}

/*
 * Skip through a single-line comment, not outputting its contents.
 */
int skip_single_comment(int c0, int c1) {
	int c;

	for(;;) {
		c = read_char();

		if(c == EOF) {
			return LEX_EOF;
		}

		if(c == '\n') {
			unread_char(c);	/* to preserve the newline */
			return lex_unknown;
		}
	}
}

/*
 * Skip through a block comment, not outputting its contents.
 */
int skip_block_comment(int c0, int c1) {
	int c;

	for(;;) {
		c = read_char();

		if(c == EOF) {
			return LEX_EOF;
		}

		if(c == '*') {
			c = read_char();

			if(c == EOF) {
				return LEX_EOF;
			}

			if(c == '/') {
				return lex_unknown;
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int t;

	if(argc != 1) {
		fputs("usage: stripc\n", stderr);
		return 1;
	}

	do {
		t = read_token();
	} while(t != LEX_EOF);

	return 0;
}

