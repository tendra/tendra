/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ANALYSER_H
#define ANALYSER_H


#define INPUT_OPEN		0
#define INPUT_CLOSE		1
#define INPUT_EOF		2
#define INPUT_WORD		3
#define INPUT_NUMBER		4
#define INPUT_STRING		5
#define INPUT_BLANK		6
#define INPUT_BLANK_FIRST	7
#define INPUT_BAR		8
#define INPUT_BAR_FIRST		9
#define INPUT_COMMA		10
#define INPUT_SEMICOLON		11
#define INPUT_ARROW		12


extern char *word;
extern int word_type;
extern long word_length;
extern bool looked_ahead;
extern long line_no;
extern bool func_input;


void read_word(void);
void store_position(position *);
void set_position(position *);
long skip_words(void);


#endif /* ANALYSER_H */
