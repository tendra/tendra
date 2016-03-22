/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Types for usable addressing modes are defined here:
 * baseoff, instore, freg, ans, where
 */

#ifndef ADDR_H
#define ADDR_H

#include <local/ash.h>

#include <reader/exp.h>

#include <construct/installtypes.h>

#include <utility/int64.h>

typedef struct {
	int lab;
	int regmove;
} makeans;

#define NOREG 100

typedef struct {
	int base;    /* base register for addressing */
	long offset; /* offset in words */
} baseoff;

typedef struct {
	bool reg;
	int value;
} source;

typedef struct {
	baseoff b;
	bool adval;	/* if true then b is itself an address value i.e not a pointer to a value */
} instore;

typedef enum {
	VAX_single,
	VAX_double,
	IEEE_single,
	IEEE_double
} float_reg_contents;

typedef struct {
	int fr;
	float_reg_contents type;
} freg;

typedef struct {
	int *fr;
	float_reg_contents type;
} somefreg;

typedef struct {
	int  *r;
} somereg;

/*
 * this type used as union of a fixpnt reg,
 * a float reg and an instore value
 */
typedef struct {
	/* use to discriminate the .val union type */
	enum {
		inreg,
		infreg,
		notinreg,
		insomereg,
		insomefreg
	} discrim;

	union {
		int regans; /* register number */
		freg fregans;
		instore instoreans;
		somefreg somefregans;
		somereg someregans;
	} val;
} ans;

typedef struct {
	ans answhere; /* reg or store position */
	ash ashwhere; /* size and alignment, see ashtypes.h */
} where;

typedef struct {
	INT64 maxi;
	INT64 mini;
	char *fmt;
} mm;

/* Macros for ease of use of unions, allow 'hiding' of discriminator. */
#define regalt(x)            (x).val.regans
#define fregalt(x)           (x).val.fregans
#define insalt(x)            (x).val.instoreans
#define someregalt(x)        (x).val.someregans.r;
#define somefregalt(x)       (x).val.somefregans;

/* Assign to field of union, discriminator set as appropriate */
#define setregalt(x, y)      (x).val.regans       = (y); (x).discrim = inreg
#define setfregalt(x, y)     (x).val.fregans      = (y); (x).discrim = infreg
#define setinsalt(x, y)      (x).val.instoreans   = (y); (x).discrim = notinreg
#define setsomeregalt(x, y)  (x).val.someregans.r = (y); (x).discrim = insomereg
#define setsomefregalt(x, y) (x).val.somefregans  = (y); (x).discrim = insomefreg

#endif

