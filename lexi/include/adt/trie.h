/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LEXI_TRIE_H
#define LEXI_TRIE_H

#include <stddef.h>

struct zone;
struct cmd_list;

enum trie_kind {
	TRIE_CHAR, /* .c is literal character or EOF */
	TRIE_GROUP /* .g is group */
};

union trie_value {
	int c;

	struct {
		unsigned int not:1;	/* boolean */
		struct group_name *gn;
	} g;
};

/*
 * CHARACTER TRIE NODE
 *
 * A character consists of a single letter (which may have associated
 * data) plus pointers to the next character and to a list of alternative
 * characters.
 */
struct trie {
	enum trie_kind kind;

	union trie_value v;

	/*
	 * Which of these used depends if the trie is a pre-pass mapping or
	 * is the main pass for a zone. Both tries are stored separately; see
	 * zone.h for details.
	 *
	 * TODO: if map can point to limited content, this may be simplified.
	 * TODO: store mapping unescaped
	 */
	union {
		struct frame *frame;
		char *map;
	} u;

	/* siblings */
	/* TODO: consider splitting this per trie_value type */
	struct trie *opt;

	/* children */
	struct trie *next;
};

struct trie *add_string(struct zone *, struct trie **, const char *);
size_t trie_maxlength(struct trie *);
int find_escape(char c);

#endif

