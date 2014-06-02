/* $Id$ */

/*
 * Copyright 2011-2014, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef READER_EXPTYPES_H
#define READER_EXPTYPES_H


#include <reader/codetypes.h>

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#else
#include <diag/dg_first.h>
#include <diag/diaginfo.h>
#endif

struct dec_t;
struct aldef_t;


/*
 * STRUCTURE REPRESENTING EXPRESSION PROPERTIES
 *
 * This is a bitfield, with different bits representing different properties.
 * The lower bits are used by common code, and the upper bits are used
 * for each architecture to specify its own architecture-specific properties.
 *
 * See expmacs.h for details.
 */
typedef unsigned short prop;


/*
 * UNION REPRESENTING A EXPRESSION CONSTITUENT
 *
 * An expression constituent can be another expression, a string, a
 * numerical value, a floating-point value or an external declaration.
 */
typedef union {
	struct exp_t *e;
	char *str;
#if defined(TRANS_680x0) && !defined(tdf3)
	long l;
	unsigned long ui;
#else
	int l;
	unsigned int ui;
#endif
	float f;
	struct dec_t *glob;

#ifndef NEWDIAGS
	diag_info *d;
#endif

	struct aldef_t *ald;
} expno;


/*
 * STRUCTURE REPRESENTING EXPRESSIONS
 *
 * An expression has a number of constituents given by the sonf, brof,
 * ptrf and numf fields, a shape (which is another expression),
 * a name representing the expression type and a properties field.
 *
 * .lastf serves as an end marker.
 */
struct exp_t {
	/* TODO: rename all fields sans-f */

	expno sonf;
	expno brof;
	expno ptf;
	expno numf;

	struct exp_t *shf;

	prop propsf;

	unsigned char namef;

	unsigned int lastf:1;
	unsigned int park :1;

#ifdef TRANS_HPPA
	unsigned int commuted:1;
#endif

#ifdef TRANS_ALPHA
	char *dfile; /* source .c file (for debugging only) */
#endif

#ifdef NEWDIAGS
	diag_info *diagf;
#endif
};


/*
 * THE EXPRESSION TYPE
 *
 * The type exp is a pointer to the structure given above.  Access to the
 * fields of the structure is by means of the macros given in expmacs.h.
 * XXX: don't typedef pointers
 */
typedef struct exp_t *exp;


#endif

