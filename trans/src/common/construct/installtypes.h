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

union signed_nat_u {
	int small_s_nat;
	flpt big_s_nat;
};

struct signed_nat_t {
	union signed_nat_u signed_nat_val;
	char issmall;		/* 1 if small_s_nat 0 big */
	char negative;};	/* 1 for neg, 0 for pos */
typedef struct signed_nat_t signed_nat;

typedef struct nat_option_t {
	int present;	/* 1 if val is present, 0 otherwise */
	nat val;
} nat_option;

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
