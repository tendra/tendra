/*
 * Copyright 2011-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCAL_TAG_H
#define LOCAL_TAG_H

enum {
	special_tag = 98,
	andcomp_tag = 99, /* for and with complement */
	dump_tag    = 100
};

/* these are name tags fabricated by scan or tokens */
enum {
	locptr_tag   = 249,
	maxlike_tag  = 250,
	minlike_tag  = 251,
	abslike_tag  = 252,
	refmap_tag   = 253
};

#endif

