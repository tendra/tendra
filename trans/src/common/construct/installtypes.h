/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef installtypes_key
#define installtypes_key 1

#include <reader/exptypes.h>

#include <reader/codetypes.h>

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#else
#include <diag/dg_first.h>
#include <diag/diaginfo.h>
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


typedef struct alignment_t {
	int al_n;	/* code describing the state
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
	struct aldef_t *next_aldef;	/* keeps a list of all aldefs */
	alignment_cell al;
} aldef;

typedef aldef *alignment;


struct bfvar_t {
	int bits;	/* number of bits in bitfield */
	int has_sign;	/* 1 if signed */
};
typedef struct bfvar_t bitfield_variety;

typedef char bool;

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

 /* structure which describes a declaration */
struct dec_t {
	struct dec_t *def_next;
	/* if this is a global declaration this field holds next global
	   declaration which needs processing. If there is none, it is NULL */
	union ut {
		struct dec_v {
			char *dec_id;
			/* identifier to be used */
			shape dec_shape;
			/* shape of the value */
			exp dec_exp;
			/* definition or NULL */
			int unit_number;
			diag_global *diag_info;
			access acc;
			int index;
			/* used in inl_norm to hold procedure index number */

#if TRANS_MIPS || TRANS_SPARC || TRANS_POWER || TRANS_ALPHA || TRANS_HPPA
			int sym_number;
#endif

			/* bitfields only after this */
			unsigned int extnamed :1;
			/* external */
			unsigned int dec_var :1;
			/* this is a variable */
			unsigned int dec_outermost :1;
			/* this is global */
			unsigned int have_def :1;
			/* we have a definition */
			unsigned int processed :1;
			/* this exp has been output */
			unsigned int isweak :1;
			/* definition is weak */
			unsigned int is_common :1;
			/* declaration is common */
			unsigned int has_signature : 1;
			/* declaration has signature */
		} dec_val;
	} dec_u;
};

typedef struct dec_t dec;

typedef dec *tag;
typedef aldef *al_tag;

typedef int floating_variety;
typedef unsigned char ntest;
typedef unsigned char rounding_mode;

typedef struct shape_list_t {
	shape *elems;
	int number;
} shape_list;	/* number shapes */

typedef shape variety;

typedef struct tag_option_t {
	bool present;
	/* 1 if val is present, 0 otherwise */
	tag val;
} tag_option;

typedef struct string_option_t {
	bool present;
	string val;
} string_option;

typedef struct tagsh_t {
	shape sha;
	access visible;
	tag tg;
} tagshacc;

typedef struct tagsh_list_t {
	exp id;
	exp last_def;
	exp last_id;
	exp proc_def;
	int size;
	int number;
} tagshacc_list;

typedef struct tagacc_t {
	tag tg;
	access visible;
} tagacc;

typedef struct tagacc_option_t {
	bool present;	/* 1 if val is present, 0 otherwise */
	tagacc val;
} tagacc_option;

typedef  struct labtag_t {
	label place_label;
} labtag;


typedef struct exp_list_t {
	exp start;	/* the first element of a list chained through bro */
	exp end;	/* the last element of a list chained through bro */
	int number;	/* the number of elements in the list */
} exp_list;

typedef exp caselim_list;


struct labtag_list_t {
	label *elems;
	int number;	/* number labels */
};
typedef struct labtag_list_t label_list;

typedef struct tagshacc_option_t {
	int present;	/* 1 if val is present, 0 otherwise */
	tagshacc val;
} tagshacc_option;

typedef struct proc_props_t {
	struct proc_props_t *pushed;
	exp proc_struct_result;
	int proc_label_count;
	float default_freq;
	alignment frame_alignment;
	int has_alloca;
	int proc_is_recursive;
	int uses_crt_env;
	int has_setjmp;
	int uses_loc_address;
	int proc_struct_res;
	int proc_externs;
	int in_proc_def;
	int rep_make_proc;
	int in_initial_value;
} proc_props;
/* holds properties of a procedure while an internally defined procedure is
 * being read */

typedef struct version_t {
	int major_version;
	int minor_version;
} version;

typedef int version_props;
typedef int version_list;

#endif /* installtypes_key */
