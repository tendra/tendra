/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_KEYWORD_H
#define LEXI_KEYWORD_H

struct instruction_tag;
struct zone_tag;
struct keyword_tag;

/*
 * TYPE REPRESENTING A KEYWORD
 *
 * A keyword consists of a name plus some associated data.
 */
typedef struct keyword_tag keyword;

void add_keyword(struct zone_tag *, const char*, struct instruction_tag *);
void keywords_iterate(struct keyword_tag *,
	void (*f)(struct keyword_tag *, void *), void *);
struct instruction_tag *keyword_instruction(struct keyword_tag *);
const char *keyword_name(struct keyword_tag *);

#endif

