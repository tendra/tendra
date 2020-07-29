/*
 * Copyright 2007-2013, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCAL_CPU_H
#define LOCAL_CPU_H

/* This is a set of feature-selection bits, which may be masked together */
enum cpu {
	CPU_80386 = 1 << 0,
	CPU_80486 = 1 << 1,
	CPU_80586 = 1 << 2
};

extern enum cpu cpu;

#endif

