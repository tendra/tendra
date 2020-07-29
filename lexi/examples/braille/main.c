/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This program reads ASCII british english text from standard input and
 * outputs formatted BRF (AKA ASCII Braille, Digital Braille) to standard
 * output. It is intended as an example for Lexi; see the braille.lxi file
 * for details.
 *
 * Grade 2 Contracted Braille is supported with -c.
 *
 * For details of BRF, see:
 *  http://www.duxburysystems.com/braille.asp
 *  http://en.wikipedia.org/wiki/Braille_ASCII
 *  http://www.brailleauthority.org/def.html
 *  http://www.bauk.org.uk/docs/bbchanf.htm
 *  http://www.iceb.org/ICEVI2006_UEB_Paper_Jolley.htm
 *
 * In addition to ASCII, curly quotes in UTF-8 are also supported.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int curr;

int read_char(void);
int get_word(int c);
int get_number(int c);
int unknown_token(int c);

int grade2;
int capital;

/* lexemes */
enum {
	lex_dash,
	lex_elipsis,
	lex_squote__open,
	lex_squote__close,
	lex_dquote__open,
	lex_dquote__close,
	lex_word,
	lex_number,
	lex_unknown,
	lex_space,
	lex_newline
};

/* conditionals */
/* TODO */
#define cond_initial    (1)
#define cond_notinitial (1)
#define cond_final      (1)

#include "braille.c"

char word[256];

int read_char(void) {
	int prev;

	prev = curr;
	curr = fgetc(stdin);

	/* TODO: maybe set capital here and convert to lowercase so mappings work for starts of words */
	capital = is_upper(lookup_char(curr));

	return curr;
}

/* scan word */
int get_word(int c) {
	int i;

	/* the -1 here allows for composition characters */
	for (i = 0; i < sizeof(word) - 1; i++) {
		int n;

		if (!i) {
			n = c;
		} else {
			n = read_char_aux();
		}

		if (!isspace(n)) {
			if (capital) {
				word[i++] = ',';
			}

			word[i] = toupper(n);
			continue;
		}

		/* the word is done */
		ungetc(n, stdin);
		word[i] = '\0';
		return lex_word;
	}

	fprintf(stderr, "word overflow\n");

	return lex_word;
}

/* scan numbers */
int get_number(int c) {
	int i;

	word[0] = '#';
	word[1] = c;
	for (i = 2; i < sizeof(word); i++) {
		int c;

		c = read_char_aux();
		if (is_digit(lookup_char(c)) || c == '.') {
			word[i] = c;
			continue;
		}

		/* the number is done */
		ungetc(c, stdin);
		word[i] = '\0';
		return lex_number;
	}

	fprintf(stderr, "word overflow\n");

	return lex_number;
}

int unknown_token(int c) {
	if (c == EOF) {
		return LEX_EOF;
	}

	return lex_unknown;
}

void emit(char *word, unsigned int *col) {
	size_t len;

	if (0 == strcmp(word, "\n")) {
		printf("\n");
		col = 0;
		return;
	}

	/*
	 * BRF specifies that the line width is 40 columns in order to
	 * support 40-column braille devices. BRF is not hyphenated, and
	 * so overhanging words are simply moved to the following line.
	 */
	len = strlen(word);
	if (*col + len > 40) {
		*col = 0;
		printf("\n");
	}

	printf("%s", word);
	*col += len;
}

int main(int argc, char *argv[]) {
	int t;
	unsigned int col;
	int c;

	/* TODO: and for -o to output */
	while (c = getopt(argc, argv, "hc"), c != -1) {
		switch(c) {
		case 'c':
			grade2 = 1;
			break;

		case 'h':
		default:
			fprintf(stderr, "usage: brf [-c]\n");
			return 1;
		}
	}

	col = 0;
	while (t = read_token(), t != LEX_EOF) {
		switch(t) {
		case lex_word:
		case lex_number:
			if (col) {
				printf(" ");
			}
			emit(word, &col);
			continue;

		case lex_unknown:
			printf("%c", curr);
			continue;

		case lex_dash:
			/* 3,6 3,6 */
			emit("--", &col);
			continue;

		case lex_elipsis:
			/* 3 3 3 */
			emit("\'", &col);
			continue;

		case lex_newline:
			emit("\n", &col);
			continue;

		default:
			fprintf(stderr, "token %d\n", t);
		}
	}

	printf("\n");

	return 0;
}

