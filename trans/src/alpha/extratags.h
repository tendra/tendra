/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef EXTRATAGS
#define EXTRATAGS

/* these are name tags fabricated by scan or tokens */
enum {
	locptr_tag   = 249,
	maxlike_tag  = 250,
	minlike_tag  = 251,
	abslike_tag  = 252,
	last_env_tag = 253,
	refmap_tag   = 254
};

extern shape LISTsh;

#define isLIST(x) ((x) == LISTsh)

#endif

