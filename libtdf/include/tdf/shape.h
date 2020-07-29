/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TDF_SHAPE_H
#define TDF_SHAPE_H

enum {
	bothd           = 1,
	tophd           = 2,
	scharhd         = 3,
	ucharhd         = 4,
	swordhd         = 5,
	uwordhd         = 6,
	slonghd         = 7,
	ulonghd         = 8,
	s64hd           = 9,
	u64hd           = 10,

	shcomplexhd     = 17,
	complexhd       = 18,
	complexdoublehd = 19,
	shrealhd        = 20,
	realhd          = 21,
	doublehd        = 22,
	bitfhd          = 23,
	prokhd          = 24,
	ptrhd           = 25,
	offsethd        = 26,
	sizehd          = 27,
	cpdhd           = 28,

	nofhd           = 29,
	tokhd           = 30
};

enum {
	shrealfv        = 0,
	realfv          = 1,
	doublefv        = 2,
	shcomplexfv     = 3,
	complexfv       = 4,
	complexdoublefv = 5
};

#define is_floating(x)	((x) >= shrealhd && (x) <= doublehd)

#endif

