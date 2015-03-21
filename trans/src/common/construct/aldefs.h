/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONSTRUCT_ALDEFS_H
#define CONSTRUCT_ALDEFS_H

typedef struct alignment_t {
	int al_n;   /* code describing the state
			   1 - defined in al_val.al
			   2 - the join of al_val.al_join.a and b
			   3 - in al_val.al_join.a
			 */
	int sh_hd;
	struct alignment_u {
		int al;
		int al_frame;
		struct join_t {
			struct aldef_t *a;
			struct aldef_t *b;
		} al_join;
	} al_val;
} alignment_cell;

typedef struct aldef_t {
	struct aldef_t *next_aldef; /* keeps a list of all aldefs */
	alignment_cell al;
} aldef;

typedef aldef *alignment;
typedef aldef *al_tag;

extern void process_aldefs(void);

#endif

