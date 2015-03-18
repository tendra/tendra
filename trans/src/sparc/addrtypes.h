/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef ADDRTYPES_H
#define ADDRTYPES_H

#include <shared/check.h>

#include <local/ash.h>

#include <construct/installtypes.h>

#define NOREG 100

typedef int reg_num; /* so we can distinguish regs */

/*
 * TYPES REPRESENTING ADDRESSING MODES
 *
 * Each of these types represent a different way of representing data.
 * The type ans is a discriminated union of these types.
 */

typedef struct {
	int lab;
	reg_num regmove;
} makeans;

typedef struct {
	reg_num base;
	long offset; /* in BYTES (bits / 8) */
} baseoff;

typedef struct {
	baseoff b;
	bool adval;
} instore;

typedef struct {
	reg_num base;
	long offset_bits; /* in BITS */
} baseoff_bits;

typedef struct {
	baseoff_bits b;
	bool adval;
} instore_bits;

typedef struct {
	reg_num fr;
	bool dble;
} freg;

typedef struct {
	reg_num *fr;
	bool dble;
} somefreg;

typedef struct {
	reg_num *r;
} somereg;

typedef struct {
	enum ansdiscrim {
		inreg,
		infreg,
		notinreg,
		insomereg,
		insomefreg
	} d;

	union {
		reg_num regans;
		freg fregans;
		instore instoreans;
		somereg someregans;
		somefreg somefregans;
	} val;
} ans;

#define  CREATE_instore_bits(a, x) \
    instore_bits a;                \
    a.b.base        = (x).b.base;  \
    a.b.offset_bits = -1;          \
    a.adval         = (x).adval

#define BITS2BYTES(x) ((x) >> 3)
#define BYTES2BITS(x) ((x) << 3)

/*
 * bottom 6 bits are used for reg number,
 * offset is aligned 32 bits, and doubled, so that bottom6 are clear
 */
#define REG_PART(x) ((x) & 0x3f)

/*
 * value (bits) was doubled, so shift by 4,
 * and ensure bottom two are clear (because the old code did this...)
 */
#define BYTE_OFFSET_PART(x) (((x) >> 4) & ~0x3)

/*
 * globals and locals use the part above REG_PART
 */
#define ADDR_PART(x) ((x) >> 6)

/*
 * TYPE REPRESENTING A STORED VALUE
 */
typedef struct {
	ans answhere;
	ash ashwhere;
} where;

/*
 * TYPE REPRESENTING A DATA STORAGE TYPE
 */
typedef struct {
	long maxi;
	long mini;
	char *fmt;
} mm;


#define discrim(x)        	 (x).d
#define regalt(x)        	 (x).val.regans
#define fregalt(x)        	 (x).val.fregans
#define insalt(x)        	 (x).val.instoreans
#define someregalt(x)        (x).val.someregans.r
#define somefregalt(x)       (x).val.somefregans

#define setregalt(x, y)      (x).val.regans       = (y); (x).d = inreg
#define setfregalt(x, y)     (x).val.fregans      = (y); (x).d = infreg
#define setinsalt(x, y)      (x).val.instoreans   = (y); (x).d = notinreg
#define setsomeregalt(x, y)  (x).val.someregans.r = (y); (x).d = insomereg
#define setsomefregalt(x, y) (x).val.somefregans  = (y); (x).d = insomefreg

#endif

