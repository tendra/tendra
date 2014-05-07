/* $Id$ */

/*
 * Copyright 2008-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCALTYPES_H
#define LOCALTYPES_H

#include <local/exptypes.h>

/* structure definition for ash  */
struct asht {
	int ashsize;	/* the minimum size in bits of a shape */
	int ashalign;	/* the required alignment in bit units of
			   the start of a shape */
};

typedef struct asht ash;


struct wht {
	exp where_exp;
	int where_off;
};

typedef struct wht where;


struct regut {
	int can_do;
	int ru_regs;
	int ru_reg_free;
};

typedef struct regut regu;


struct dclt {
	int dcl_pl;
	int dcl_n;
	ash dcl_place;
	int dcl_new;
};

typedef struct dclt dcl;


struct frrt {
	int fr_no;
	int regno;
};

typedef struct frrt frr;


struct specit {
	int is_special;
	exp special_exp;
};

typedef struct specit speci;


struct regcell_t {
	/*
	 * 0 - indetermined
	 * 1 - has first_dest, not second
	 * 2 - has second_dest, not first
	 * 3 - has first_dest and second_dest
	 * 4 - overdetermined
	 */
	int regcell_key;
	exp first_dest;
	int first_size;
	exp second_dest;
	int second_size;
};

typedef struct regcell_t regcell;

typedef regcell reg_record[7];


typedef struct outofline_t {
	struct outofline_t *next;
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

#endif /* LOCALTYPES_H */
