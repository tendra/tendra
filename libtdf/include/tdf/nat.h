/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TDF_NAT_H
#define TDF_NAT_H

typedef int flpt;

/* the definition of the internal representation of the sort nat */
typedef struct {
	union {
		int small_nat;
		flpt big_nat;
	} nat_val;
	bool issmall; /* 1 if small_nat, 0 if big_nat */
} nat;

union signed_nat_u {
	int small_s_nat;
	flpt big_s_nat;
};

typedef struct {
	union signed_nat_u signed_nat_val;
	bool issmall;  /* 1 if small_s_nat 0 big */
	bool negative; /* 1 for neg, 0 for pos */
} signed_nat;

typedef struct {
	bool present; /* 1 if val is present, 0 otherwise */
	nat val;
} nat_option;

/* the definition of the internal representation of the sort tdfint */
typedef nat tdfint;

#define natint(x)       ((x).nat_val.small_nat)
#define natbig(x)       ((x).nat_val.big_nat)
#define nat_issmall(x)  ((x).issmall)
#define snatint(x)      ((x).signed_nat_val.small_s_nat)
#define snatneg(x)      ((x).negative)
#define snatbig(x)      ((x).signed_nat_val.big_s_nat)
#define snat_issmall(x) ((x).issmall)

#endif

