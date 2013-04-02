/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/******************************************************************
                             constmacs.h

  This file contains macros used in repeat_list

 *****************************************************************/

/* "no_alias" flag - set in consts.c and used by foralls.c */
#define set_noalias(x)	props(x) = (prop)(props(x) | 0x01)
#define clr_noalias(x)	props(x) &= 0xfe
#define is_noalias(x)	(props(x) & 0x01)

/* "dist" flag
   when x is an element of the repeat_list,
   if is_dist(x), then no(x) is maximum distance from a leaf repeat
   otherwise it is the count of repeats in the next level down
   (as set in dexp.c)
*/
#define set_dist(x)	(props(x) = (prop)(props(x) | 0x02))
#define is_dist(x)	(props(x) & 0x02)

#define max_loop_depth 6
