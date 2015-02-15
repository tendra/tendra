/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CONFIG_H
#define CONFIG_H


#define streq(X, Y)	(strcmp((X), (Y)) == 0)
#define strneq(X, Y, Z)	(strncmp((X), (Y), (size_t)(Z)) == 0)
#define MAX_LINE	1024


#endif /* CONFIG_H */
