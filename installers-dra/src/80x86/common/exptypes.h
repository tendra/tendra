/* $Id$ */

/*
 * Copyright 2007-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EXPTYPES_H
#define EXPTYPES_H

#include <reader/codetypes.h>

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#else
#include <diag/dg_first.h>
#include <diag/diaginfo.h>
#endif

typedef short prop;

struct aldef_t;
struct exp_t;

union expno_u {
	struct exp_t *e;
	char *str;
	int l;
	unsigned int ui;
	float f;
	struct dec_t *glob;
#ifndef NEWDIAGS
	diag_info *d;
#endif
	struct aldef_t *ald;
};

struct exp_t {
	union expno_u brof;
	union expno_u numf;
	union expno_u ptf;
	union expno_u sonf;
	struct exp_t *shf;
	prop propsf;
	unsigned char namef;
	unsigned int lastf : 1;
	unsigned int park : 1;
#ifdef NEWDIAGS
	diag_info *diagf;
#endif
};

typedef struct exp_t *exp;
typedef union expno_u expno;

#endif /* EXPTYPES_H */
