/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef UTILITY_COMPLEXITY_H
#define UTILITY_COMPLEXITY_H

/*
 * Find the complexity of an expression
 *
 * This routine examines the structure of e to see if its complexity
 * (roughly the number of nodes) is greater than count. As soon as the
 * complexity exceeds this value it stops. It returns the difference
 * between count and the calculated complexity.
 */
int
complexity(exp e, int count, int newdecs,
	int crit_decs, int crit_decsatapp, int apply_cost);

#endif

