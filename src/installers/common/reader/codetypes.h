/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:45 $
$Revision: 1.1.1.1 $
$Log: codetypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/
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
