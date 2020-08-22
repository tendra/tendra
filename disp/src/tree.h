/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TREE_INCLUDED
#define TREE_INCLUDED


/*
 *  STRUCTURE DEFINITION: WORD
 *
 *  The structure word is used to record the layout of the pretty
 *  printed TDF tree.  It consists of a layout type (see below
 *  for details), a string of characters, together with the length
 *  of this string, and pointers to the "child" and "next" words.
 */
typedef struct s_word {
    char type;
    int length;
    char *text;
    struct s_word *child;
    struct s_word *next;
} word;


/*
 * WORD LAYOUT TYPES
 *
 * The available layout types are:
 *
 *   SIMPLE         - representing a simple word,
 *   HORIZ_NONE     - a word with a number of arguments listed horizontally,
 *   HORIZ_BRACKETS - a word with arguments listed horizontally in brackets,
 *   VERT_NONE      - a word with arguments listed vertically,
 *   VERT_BRACKETS  - a word with arguments listed vertically in brackets.
*/

#define SIMPLE			0
#define HORIZ_BRACKETS		1
#define VERT_BRACKETS		2
#define HORIZ_NONE		3
#define VERT_NONE		4


/*
 * TDF TREE MANIPULATION
 *
 * The layout of the pretty-printed TDF tree is recorded in the
 * structure word. The routine new_word allocates a new word of
 * a given type.  The macro end_word is used to indicate the end
 * of a complex word.  The routine format combines these with
 * decode to provide a convenient way of decoding a word with a
 * number of arguments of given sorts.
 */

#define blank_line()		(void)new_word(SIMPLE)
#define end_word(X)		word_ptr = (X); word_ptr->next = NULL

extern int length;
extern word word1;
extern word *word_ptr;

extern void initialize_tree(void);
extern word *new_word(int);
extern void out_char(int);
extern void out_string(char *);
extern void out(char *);
extern void out_int(long);
extern void out_signed(char *, int);
extern void out_unique(unique);
extern void format(int, char *, char *);


#endif
