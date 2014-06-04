/* $Id$ */

/*
 * Copyright 2008-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCAL_TYPES_H
#define LOCAL_TYPES_H

#include <local/ash.h>

#include <reader/exptypes.h>

typedef struct {
	exp where_exp;
	int where_off;
} where;

typedef struct {
	int can_do;
	int ru_regs;
	int ru_reg_free;
} regu;

typedef struct {
	int dcl_pl;
	int dcl_n;
	ash dcl_place;
	int dcl_new;
} dcl;

typedef struct {
	int fr_no;
	int regno;
} frr;

typedef struct {
	/*
	 * 0 - indetermined
	 * 1 - has first_dest, not second
	 * 2 - has second_dest, not first
	 * 3 - has first_dest and second_dest
	 * 4 - overdetermined
	 * TODO: enum?
	 */
	int regcell_key;
	exp first_dest;
	int first_size;
	exp second_dest;
	int second_size;
} regcell;

typedef regcell reg_record[7];

typedef struct {
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

#endif

