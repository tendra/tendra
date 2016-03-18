/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef expdecs_key
#define expdecs_key 1

#include <reader/exp.h>

#include <tdf/nat.h>

#include <construct/installtypes.h>
#include <construct/tagdata.h>
#include <construct/aldefs.h>

typedef struct exp_list_t {
	exp start;  /* the first element of a list chained through bro */
	exp end;    /* the last element of a list chained through bro */
	int number; /* the number of elements in the list */
} exp_list;

extern exp getexp (shape s, exp b, int l, exp sn, exp p, prop pr, int n,
		   unsigned char tag);
extern exp getshape (int l, alignment sn, alignment p, alignment pr, int n,
		     unsigned char tag);
extern shape lub_shape(shape a, shape b);
extern int next_lab(void);
extern int eq_shape(shape a, shape b);
extern char * intchars(int i);
extern void case_item(exp e);
extern void kill_exp(exp e, exp scope);
extern void altered(exp e, exp scope);
extern void replace(exp old, exp e, exp scope);
extern int internal_to(exp whole, exp part);
extern exp next_exp(void);
extern exp copy(exp e);
extern exp copy_res(exp e, exp var, exp lab);
extern exp copyexp(exp e);
extern exp father(exp e);
extern exp *refto(exp f, exp e);
extern void retcell(exp e);
extern bool is_comm(exp e);
extern void set_large_alloc(void);

extern int first_alloc_size;
extern exp freelist;
extern int exps_left;
extern int crt_labno;

extern exp clean_labelled(exp starter, label_list placelabs_intro);

#endif
