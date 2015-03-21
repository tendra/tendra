/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef READER_CODE_H
#define READER_CODE_H

typedef int flpt;

typedef struct {
	/* the definition of the internal representation of the sort nat */
	union {
		int small_nat;
		flpt big_nat;
	} nat_val;
	char issmall; /* 1 if small_nat, 0 if big_nat */
} nat;

union signed_nat_u {
	int small_s_nat;
	flpt big_s_nat;
};

typedef struct {
	union signed_nat_u signed_nat_val;
	char issmall;  /* 1 if small_s_nat 0 big */
	char negative; /* 1 for neg, 0 for pos */
} signed_nat;

typedef struct {
	int present; /* 1 if val is present, 0 otherwise */
	nat val;
} nat_option;

/*
 * the definition of the internal representation of the sort tdfstring
 * and tdfident
 */
typedef struct {
	int size;	/* size of components in bits */
	int number;	/* number of components */

	/*
	 * the components are place in the array of the smallest
	 * possible size elements
	 */
	union {
		char  *chars;
		short *shorts;
		int   *longs;
	} ints;
} tdfstring;

/* the definition of the internal representation of the sort tdfbool */
typedef char tdfbool;

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

