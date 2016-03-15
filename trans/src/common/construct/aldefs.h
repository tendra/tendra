/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONSTRUCT_ALDEFS_H
#define CONSTRUCT_ALDEFS_H

/* code describing the state */
/* that is, which fields of the union constitute the value */
enum aldef_state {
	ALDEF_NONE,
	ALDEF_VALAL,  /* defined in u.al */
	ALDEF_JOINAB, /* the join of u.al_join.a and b */
	ALDEF_JOINA   /* in u.al_join.a */
};

typedef struct alignment_t {
	enum aldef_state state;
	int sh_hd;
	int frame;
	union {
		int al;
		struct join_t {
			struct aldef_t *a;
			struct aldef_t *b;
		} al_join;
	} u;
} alignment_cell;

typedef struct aldef_t {
	struct aldef_t *next; /* keeps a list of all aldefs */
	alignment_cell al;
} aldef;

typedef aldef *alignment;
typedef aldef *al_tag;

extern void process_aldefs(void);

#endif

