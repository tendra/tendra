/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_ZONE_H
#define LEXI_ZONE_H

#include <stddef.h>

#include "group.h"

struct keyword_tag;
struct lexer_parse_tree_tag;

/*
 * Type of Zones indicate if a zone return terminals or not.
 *
 * If a zone never return terminal then it is possible to output
 * a more efficient code.
 *
 * TODO: we can calculate can these on the fly, and remove zone types entirely
 */
typedef enum zone_type_tag {
	typezone_general_zone,	/* A zone that can return more than one terminal */
	typezone_pseudo_token,	/* A zone that returns only one terminal on zone exit */
	typezone_pure_function	/* A zone that never returns a terminal */ 
} zone_type;

typedef struct zone_tag zone;
struct zone_tag {
	/* NULL for the global zone */
	char* zone_name;

	zone_type type;

	/*
	 * Characters in the pre-pass mapping trie take their values from u.map,
	 * and characters in the main pass take their values from u.definition.
	 * That is, the pre-pass trie keys onto strings, and the main pass keys
	 * onto instruction lists. See char.h for the definitions of those values.
	 */
	struct character_tag *zone_pre_pass;
	struct character_tag *zone_main_pass;

	struct keyword_tag *keywords;
	char_group_name *groups;
	char_group_name *white_space;

	struct instructions_list_tag *default_instructions;
	struct instructions_list_tag *entering_instructions;
	struct instructions_list_tag *leaving_instructions;

	zone *opt; 	/* sibling */
	zone *next;	/* child */
	zone *up; 	/* parent */

	struct lexer_parse_tree_tag *top_level;
};

size_t zone_maxlength(zone *z, int in_prepass);
zone *new_zone(struct lexer_parse_tree_tag *top_level);
zone *add_zone(zone *, char *, const char *, int);

/*
 * ADD A STRING TO A ZONE'S TRIE
 *
 * These are the main interfaces for adding new keys to the trie for either a
 * pre-pass mapping, or for a main pass token respectively.
 */
struct character_tag *add_mainpass(zone *, const char *, struct instructions_list_tag *);
struct character_tag *add_prepass(zone *, const char *, char *);

int zone_isglobal(zone *z);
const char *zone_name(zone *z);

#endif

