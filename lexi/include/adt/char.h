/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LEXI_CHAR_H
#define LEXI_CHAR_H

#include <stddef.h>

struct zone;
struct cmd_list;

enum char_kind {
	CHAR_GROUP,
	CHAR_LETTER
};

union char_value {
	/* CHAR_LETTER: character or EOF */
	int c;

	/* CHAR_GROUP */
	struct {
		unsigned int not:1;	/* boolean */
		struct group_name *gn;
	} g;
};

/*
 * TYPE REPRESENTING A CHARACTER
 *
 * A character consists of a single letter (which may have associated
 * data) plus pointers to the next character and to a list of alternative
 * characters.
 */
struct character {
	enum char_kind kind;

	union char_value v;

	/*
	 * Which of these used depends if the trie is a pre-pass mapping or
	 * is the main pass for a zone. Both tries are stored separately; see
	 * zone.h for details.
	 *
	 * TODO: if map can point to limited content, this may be simplified.
	 * TODO: store mapping unescaped
	 */
	union {
		struct cmd_list *cmds;
		char *map;
	} u;

	/* siblings */
	/* TODO: consider splitting this per char_value type */
	struct character *opt;

	/* children */
	struct character *next;
};

struct character *add_string(struct zone *, struct character **, const char *);
size_t char_maxlength(struct character *);
int find_escape(char c);

#endif

