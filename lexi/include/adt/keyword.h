/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_KEYWORD_H
#define LEXI_KEYWORD_H

struct cmd;
struct zone;

struct keyword {
	const char *name;
	struct cmd *cmd;

	struct keyword *next;
};

void add_keyword(struct zone *, const char *, struct cmd *);
void keywords_iterate(struct keyword *,
	void (*f)(struct keyword *, void *), void *);

#endif

