/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CONFIG_H
#define CONFIG_H


#if __TenDRA__
#pragma TenDRA keyword SET for set
#pragma TenDRA keyword UNUSED for discard variable
#pragma TenDRA keyword IGNORE for discard value
#pragma TenDRA keyword EXHAUSTIVE for exhaustive
#pragma TenDRA keyword REACHED for set reachable
#pragma TenDRA keyword UNREACHED for set unreachable
#else
#define SET(name)
#define UNUSED(name)
#define IGNORE			(void)
#define EXHAUSTIVE
#define REACHED
#define UNREACHED
#endif /* __TenDRA__ */


/* Stuff that is currently required but really wants to die */
typedef int boolean;

#define streq(X, Y)	(strcmp((X), (Y)) == 0)
#define strneq(X, Y, Z)	(strncmp((X), (Y), (size_t)(Z)) == 0)
#define MAX_LINE	1024


#endif /* CONFIG_H */
