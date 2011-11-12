/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef codetypes_key
#define codetypes_key 1



typedef int flpt;

 /* the definition of the internal representation of the sort nat */
union nat_u {int small_nat;
             flpt big_nat;};
struct nat_t {union nat_u nat_val;
	      char issmall;	/* 1 if small_nat, 0 if big_nat */
	     };
typedef struct nat_t nat;



 /* the definition of the internal representation of the sort tdfstring
    and tdfident */
typedef struct tdfstring_t
  {int size;	/* size of components in bits */
   int number;	/* number of components */
   union tdfs_u {char * chars; short * shorts; int * longs;} ints;
	/* the components are place in the array of the smallest
	   possible size elements */
  } tdfstring;

 /* the definition of the internal representation of the sort tdfbool */
typedef char tdfbool;

 /* the definition of the internal representation of the sort tdfint */
typedef nat tdfint;

#endif
