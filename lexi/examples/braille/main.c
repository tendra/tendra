/*
 * This program reads ASCII british english text from standard input and
 * outputs formatted BRF to standard output. It is intended as an example
 * for lexi; see the braille.lxi file for details.
 *
 * In addition to ASCII, curly quotes in UTF-8 are also supported.
 *
 * $Id$
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

int curr;

int unread_char(int c);
int read_char(void);
int get_word(int c);
int get_number(int c);
int unknown_token(int c);

bool grade2;
bool capital;

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
#define cond_initial (true)
#define cond_notinitial (true)
#define cond_final (true)

#include "braille.c"

char word[256];

int unread_char(int c) {
	return ungetc(c, stdin);
}

int read_char(void) {
	int prev;

	prev = curr;
	curr = fgetc(stdin);

	/* TODO maybe set capital here and convert to lowercase so mappings work for starts of words */
	capital = is_upper(lookup_char(curr));
//	curr = tolower(curr);

	return curr;
}

/* scan word */
int get_word(int c) {
	int i;

	/* the -1 here allows for composition characters */
	for(i = 0; i < sizeof(word) - 1; i++) {
		int n;

		if(!i) {
			n = c;
		} else {
			n = read_char_aux();
		}

		if(!isspace(n)) {
			if(capital) {
				word[i++] = ',';
			}

			word[i] = toupper(n);
			continue;
		}

		/* the word is done */
		unread_char(n);
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
	for(i = 2; i < sizeof(word); i++) {
		int c;

		c = read_char_aux();
		if(is_digit(lookup_char(c)) || c == '.') {
			word[i] = c;
			continue;
		}

		/* the number is done */
		unread_char(c);
		word[i] = '\0';
		return lex_number;
	}

	fprintf(stderr, "word overflow\n");

	return lex_number;
}

int unknown_token(int c) {
	if(c == EOF) {
		return LEX_EOF;
	}

	return lex_unknown;

//	fprintf(stderr, "unknown token for character \"%c\"\n", c);

//	return get_word(c);
}

void emit(char *word, unsigned int *col) {
	size_t len;

	if(!strcmp(word, "\n")) {
		printf("\n");
		col = 0;
		return;
	}

	len = strlen(word);
	if(*col + len > 40) {
		/* The line is full. Knuth would be proud */
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

	/* TODO and for -o to output */
	while((c = getopt(argc, argv, "hc")) != -1) {
		switch(c) {
		case 'c':
			grade2 = true;
			break;

		case 'h':
		default:
			fprintf(stderr, "usage: brf\n");
			return 1;
		}
	}

	col = 0;
	while((t = read_token()) != LEX_EOF) {
		switch(t) {
		case lex_word:
		case lex_number:
			if(col) {
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

