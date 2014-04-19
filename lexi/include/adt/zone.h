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

struct keyword;
struct lexer_parse_tree;

/*
 * Type of Zones indicate if a zone return terminals or not.
 *
 * If a zone never return terminal then it is possible to output
 * a more efficient code.
 *
 * TODO: we can calculate can these on the fly, and remove zone types entirely
 */
enum zone_type {
	typezone_general_zone,	/* A zone that can return more than one terminal */
	typezone_pseudo_token,	/* A zone that returns only one terminal on zone exit */
	typezone_pure_function	/* A zone that never returns a terminal */ 
};

struct zone {
	/* NULL for the global zone */
	char* zone_name;

	enum zone_type type;

	/*
	 * Characters in the pre-pass mapping trie take their values from u.map,
	 * and characters in the main pass take their values from u.definition.
	 * That is, the pre-pass trie keys onto strings, and the main pass keys
	 * onto instruction lists. See char.h for the definitions of those values.
	 */
	struct character *zone_pre_pass;
	struct character *zone_main_pass;

	struct keyword *keywords;
	struct char_group_name *groups;
	struct char_group_name *white_space;

	struct instructions_list *default_instructions;
	struct instructions_list *entering_instructions;
	struct instructions_list *leaving_instructions;

	struct zone *opt; 	/* sibling */
	struct zone *next;	/* child */
	struct zone *up; 	/* parent */

	struct lexer_parse_tree *top_level;
};

size_t zone_maxlength(struct zone *z, int in_prepass);
struct zone *new_zone(struct lexer_parse_tree *top_level);
struct zone *add_zone(struct zone *, char *, const char *, int);

/*
 * ADD A STRING TO A ZONE'S TRIE
 *
 * These are the main interfaces for adding new keys to the trie for either a
 * pre-pass mapping, or for a main pass token respectively.
 */
struct character *add_mainpass(struct zone *, const char *, struct instructions_list *);
struct character *add_prepass(struct zone *, const char *, char *);

int zone_isglobal(struct zone *z);
const char *zone_name(struct zone *z);

#endif

