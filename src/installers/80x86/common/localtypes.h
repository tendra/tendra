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


/* 80x86/localtypes.h */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: localtypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/04/17  11:55:55  pwe
 * dwarf2 improvements
 *
 * Revision 1.2  1995/01/30  12:56:33  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:36:49  jmf
 * Initial revision
 *
**********************************************************************/

#ifndef localtypes_key
#define localtypes_key 1


struct asht {			/* structure definition for ash  */
  int  ashsize;	/*  the minimum size in bits of a shape  
				*/
  int  ashalign;	/* the required alignment in bit units of
				   the start of a shape */
};

typedef struct asht ash;

struct wht {
  exp where_exp;
  int  where_off;
};

typedef struct wht  where;

struct regut {
  int can_do;
  int  ru_regs;
  int  ru_reg_free;
};

typedef struct regut  regu;

struct dclt {
  int  dcl_pl;
  int  dcl_n;
  ash  dcl_place;
  int dcl_new;
};

typedef struct dclt dcl;

struct frrt {
  int  fr_no;
  int  regno;
};
typedef struct frrt frr;

struct specit {
  int is_special;
  exp special_exp;
};
typedef struct specit speci;



struct regcell_t {int regcell_key;
			/* 0 - indetermined
			   1 - has first_dest, not second
			   2 - has second_dest, not first
			   3 - has first_dest and second_dest
			   4 - overdetermined
			*/
                  exp first_dest;
                  int first_size;
                  exp second_dest;
                  int second_size;
                 };

typedef struct regcell_t regcell;

typedef regcell reg_record[7];

typedef struct outofline_t {
	struct outofline_t * next;
	where dest;
	ash stack;
	exp body;
	int regsinuse;
	exp jr;
	int fstack_pos;
	int labno;
	int cond1_set;
	int cond2_set;
	where cond1;
	where cond2a;
	where cond2b;
	int repeat_level;
	float scale;
#ifdef NEWDWARF
	long dw2_hi;
	long dw2_slave;
#endif
} outofline;



#endif
