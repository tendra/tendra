/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SPECIAL_TOK_H
#define SPECIAL_TOK_H

struct special_tok {
	const char *name;
	int mask;
	bool (*f)(tokval *tkv, token td, bitstream pars);
};

/*
 * Intercepts specially defined functions tokens
 */
bool
special_token(const struct special_tok a[], size_t count,
	tokval *tkv, token td, bitstream pars, int sortcode);

extern const struct special_tok special_toks[];
extern size_t special_toks_count;

extern const struct special_tok special_allocs[];
extern size_t special_allocs_count;

extern const struct special_tok special_diags[];
extern size_t special_diags_count;

#endif

