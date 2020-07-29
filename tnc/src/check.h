/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CHECK_H
#define CHECK_H


/*
    BASIC SHAPE CHECKING ROUTINES
*/

void check_exp_fn(node *);
void check_nat_fn(node *);
void check_shape_fn(node *);
void check_snat_fn(node *);
void check_access_fn(node *);
void check_tagdef(construct *);

extern bool do_check;
extern char *checking;

#define check_exp(X)		check_exp_fn((X))
#define check_nat(X)		check_nat_fn((X))
#define check_shape(X)		check_shape_fn((X))
#define check_signed_nat(X)	check_snat_fn((X))
#define check_access(X)		check_access_fn((X))


#endif /* CHECK_H */
