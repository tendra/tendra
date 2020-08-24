/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONSTRUCT_CONST_H
#define CONSTRUCT_CONST_H

/*
 * The type maxconst returns information about the expression under
 * consideration. The field self is true if the expression as a whole is
 * constant within the program fragment under consideration. If the
 * entire expression is not constant (self is false) then the field cont
 * is a list of the sub-expressions which are constant within the
 * specified region.
 *
 * If no sub-expressions are constant, cont has the value NULL.
 *
 * If cont is not empty, its child is a list of elements, each of which
 * has a child which is a constant within the specified program fragment.
 * The pointer of cont points to the last element of the list.
 */
typedef struct {
	bool self;
	exp cont;
} maxconst;


/*
 * This file contains macros used in repeat_list
 */

/* "no_alias" flag - set in consts.c and used by foralls.c */
#define set_noalias(x)	(x)->props = (prop) ((x)->props | 0x01)
#define clr_noalias(x)	(x)->props &= 0xfe
#define is_noalias(x)	((x)->props & 0x01)

/*
 * "dist" flag
 *
 * When x is an element of the repeat_list, if is_dist(x), then
 * no(x) is maximum distance from a leaf repeat. Otherwise it is
 * the count of repeats in the next level down (as set in dexp.c)
 */
#define set_dist(x)	((x)->props = (prop) ((x)->props | 0x02))
#define is_dist(x)	((x)->props & 0x02)

#define max_loop_depth 6


#endif

