/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef NATMACS_H
#define NATMACS_H

#include <reader/codetypes.h>

#define natint(x)	((x).nat_val.small_nat)
#define natbig(x)	((x).nat_val.big_nat)
#define nat_issmall(x)	((x).issmall)
#define snatint(x)	((x).signed_nat_val.small_s_nat)
#define snatneg(x)	((x).negative)
#define snatbig(x)	((x).signed_nat_val.big_s_nat)
#define snat_issmall(x)	((x).issmall)

#endif /* NATMACS_H */
