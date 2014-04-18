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

struct zone_tag;
struct instructions_list_tag;

typedef enum letter_translation_type_tag {
	group_letter, char_letter
} letter_translation_type;

union char_value {
	/* for char_letter: character or EOF */
	int c;

	/* for group_letter */
	struct {
		unsigned int not:1;	/* boolean */
		struct char_group_name_tag *grp;
	} g;
};

/*
 * TYPE REPRESENTING A CHARACTER
 *
 * A character consists of a single letter (which may have associated
 * data) plus pointers to the next character and to a list of alternative
 * characters.
 */
typedef struct character_tag character;
struct character_tag {
	letter_translation_type type;

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
		struct instructions_list_tag *definition;
		char *map;
	} u;

	/* siblings */
	/* TODO: consider splitting this per char_value type */
	character *opt;

	/* children */
	character *next;
};

character *add_string(struct zone_tag *, character **, const char *);
size_t char_maxlength(character *);
int find_escape(char c);

#endif

