/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef installtypes_key
#define installtypes_key 1

#include <shared/bool.h>

#include <reader/exp.h>

#include <reader/code.h>

#ifdef TDF_DIAG4
#include <diag4/dg_first.h>
#else
#include <diag3/dg_first.h>
#include <diag3/diaginfo.h>
#endif

typedef exp otagexp;

typedef struct otagexp_list_t {
	exp start;
	exp end;
	exp id;
	int number;
} otagexp_list;

typedef int procprops;

typedef int procprops_option;
typedef exp callees;
typedef int error_code;
typedef int error_code_list;

typedef tdfstring string;

typedef struct exp_option_t {
	int present;	/* 1 if val is present, 0 otherwise */
	exp val;
} exp_option;


/* dummy definitions */
typedef int access;
typedef int access_option;

typedef int transfer_mode;


struct bfvar_t {
	int bits;	/* number of bits in bitfield */
	int has_sign;	/* 1 if signed */
};
typedef struct bfvar_t bitfield_variety;

typedef exp shape;

typedef exp *label;

struct caselim_t {
	label lab;	/* label to jump if control between low and high */
	signed_nat low;
	signed_nat high;
};	/* caselim during reading */

typedef struct caselim_t caselim;

typedef struct error_treatment_t {
	int err_code;	/* code for treatment */
	label jmp_dest;
} error_treatment;	/* error treatment during reading */


typedef struct dec_t *tag;

typedef int floating_variety;
typedef unsigned char ntest;
typedef unsigned char rounding_mode;

typedef struct shape_list_t {
	shape *elems;
	int number;
} shape_list;	/* number shapes */

typedef shape variety;


typedef exp caselim_list;


typedef struct version_t {
	int major_version;
	int minor_version;
} version;

typedef int version_props;
typedef int version_list;

#endif /* installtypes_key */
