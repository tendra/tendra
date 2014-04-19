/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_KEYWORD_H
#define LEXI_KEYWORD_H

struct instruction;
struct zone;
struct keyword;

void add_keyword(struct zone *, const char*, struct instruction *);
void keywords_iterate(struct keyword *,
	void (*f)(struct keyword *, void *), void *);
struct instruction *keyword_instruction(struct keyword *);
const char *keyword_name(struct keyword *);

#endif

