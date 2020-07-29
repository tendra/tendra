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
struct frame;
struct trie;
struct ast;

/*
 * Type of Zones indicate if a zone return terminals or not.
 *
 * If a zone never return terminal then it is possible to output
 * a more efficient code.
 *
 * TODO: we can calculate can these on the fly, and remove zone types entirely
 */
enum zone_kind {
	ZONE_GENERAL, /* A zone that can return more than one terminal */
	ZONE_PSEUDO,  /* A zone that returns only one terminal on zone exit */
	ZONE_PURE     /* A zone that never returns a terminal */
};

struct zone {
	/* NULL for the global zone */
	char *name;

	enum zone_kind kind;

	/*
	 * Characters in the pre-pass mapping trie take their values from u.map,
	 * and characters in the main pass take their values from u.definition.
	 * That is, the pre-pass trie keys onto strings, and the main pass keys
	 * onto command lists. See trie.h for the definitions of those values.
	 */
	struct trie *pre;
	struct trie *main;

	struct keyword *keywords;
	struct group_name *groups;
	struct group_name *white;

	struct frame *local;
	struct frame *enter;
	struct frame *exit;

	struct zone *opt; 	/* sibling */
	struct zone *next;	/* child */
	struct zone *up; 	/* parent */

	struct ast *ast;
};

size_t zone_maxlength(struct zone *z, int in_prepass);
struct zone *new_zone(struct ast *ast);
struct zone *add_zone(struct zone *, char *, const char *, int);

/*
 * ADD A STRING TO A ZONE'S TRIE
 *
 * These are the main interfaces for adding new keys to the trie for either a
 * pre-pass mapping, or for a main pass token respectively.
 */
struct trie *add_mainpass(struct zone *, const char *, struct frame *);
struct trie *add_prepass(struct zone *, const char *, char *);

int zone_isglobal(struct zone *z);
const char *zone_name(struct zone *z);

#endif

