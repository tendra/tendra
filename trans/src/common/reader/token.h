/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef READER_TOKEN_H
#define READER_TOKEN_H

#ifdef TDF_DIAG4
#include <diag4/dg_first.h>
#else
#include <diag3/dg_first.h>
#include <diag3/diaginfo.h>
#endif

#include <tdf/nat.h>

#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/aldefs.h>
#include <construct/dec.h>

#ifdef TDF_DIAG4
#include <diag4/dg_types.h>  /* TDF_DIAG4 */
#include <diag4/diagtypes.h> /* TDF_DIAG3 */
#else
#include <diag3/dg_types.h>  /* TDF_DIAG4 */
#include <diag3/diagtypes.h> /* TDF_DIAG3 */
#endif


/* definitions of types used in read_fns.c */
typedef struct {
	int flag;     /* false if reading from stream, true if reading from pl_mem */
	char *pl_mem; /* pointer to the characters */
	int bits_on;  /* bit_index displacement of the start */
} place;

typedef place bitstream;
typedef place bytestream;

struct sortname_t {
	int code;   /* code number for the sort - see sortmacs.h */
	int result; /* if code is TOKEN this is the code for the result */

	/*
	 * pars.elems is an array of pars.number
	 * parameter sorts if the code is TOKEN
	 */
	struct sortname_list_t {
		struct sortname_t *elems;
		int number;
	} pars;
};

typedef struct sortname_t sortname;

typedef struct sortname_list_t sortname_list;

/* dummy definition types */
typedef int token_defn;
typedef int capsule;
typedef int tokextern_list;
typedef int tagextern_list;
typedef int tokdef_list;
typedef int tagdec_list;
typedef int tagdef_list;
typedef int al_tagdef_list;
typedef int unit;
typedef int info;
typedef int info_list;
typedef int linkunit;
typedef int linkunit_list;
typedef int toklink_list;
typedef int taglink_list;
typedef int allink_list;
typedef int tokdec_list;
typedef int tokdec_unit;
typedef int tokdef_unit;
typedef int tagdec_unit;
typedef int tagdef_unit;
typedef int aldef_unit;
typedef int tokdec_unit_list;
typedef int tokdef_unit_list;
typedef int tagdec_unit_list;
typedef int tagdef_unit_list;
typedef int linkinfo_props;

typedef char usage;


/*
 * the union of the representations of all sorts:
 * used in table_fns for token application
 */

typedef union {
	alignment            tk_alignment;
	al_tag               tk_al_tag;
	bitfield_variety     tk_bitfield_variety;
	bool                 tk_bool;
	error_treatment      tk_error_treatment;
	exp                  tk_exp;
	floating_variety     tk_floating_variety;
	label                tk_label;
	nat                  tk_nat;
	ntest                tk_ntest;
	rounding_mode        tk_rounding_mode;
	shape                tk_shape;
	signed_nat           tk_signed_nat;
	tag                  tk_tag;
	struct tok_define_t *tk_token;
	transfer_mode        tk_transfer_mode;
	variety              tk_variety;
	diag_type            tk_diag_type;   /* TDF_DIAG3 */
	filename             tk_filename;    /* TDF_DIAG3 */
	access               tk_access;
	procprops            tk_procprops;
	string               tk_string;

	dg                   tk_dg;          /* TDF_DIAG4 */
	dg_dim               tk_dg_dim;      /* TDF_DIAG4 */
	dg_filename          tk_dg_filename; /* TDF_DIAG4 */
	dg_idname            tk_dg_idname;   /* TDF_DIAG4 */
	dg_name              tk_dg_name;     /* TDF_DIAG4 */
	dg_type              tk_dg_type;     /* TDF_DIAG4 */
} tokval;


#define LOCAL_TOKS 4

typedef struct tag_con_t {
	dec *namet;
	exp e;
	struct tag_con_t *rest;
} tag_con;

typedef struct lab_con_t {
	label namel;
	exp e;
	struct lab_con_t *rest;
} lab_con;


/* struct holding a token definition */
struct tok_define_t {
	dec                 **my_tagtab;  /* the tagtab current at the definition */
	aldef               **my_altab;   /* the altab current at the definition */
	exp                  *my_labtab;  /* the labtab current at the definition */
	struct tok_define_t **my_toktab;  /* the toktab current at the definition */
	diag_tagdef         **my_diagtab; /* TDF_DIAG3 */ /* the diagtab current at the definition */
	dgtag_struct        **my_dgtab;   /* TDF_DIAG4 */ /* the dgtab current at the definition */

	char *tok_name; /* the identifier (if any) for the token */

	struct tokformals_list_t {
		sortname *par_sorts; /* sorts of parameters */
		int *par_names;      /* token index for parameters */
		int number;          /* total number of parameters */
	} params;                /* description of formal parameters */

	sortname tdsort; /* sort of token result */
	place tdplace;   /* place to read definition from */
	int unit_number; /* number of unit in which defined */
	tokval tdvalue;  /* preserved value if valpresent */
	int tok_index;   /* index number of this token */
	int tdtoken;     /* the token */

	struct context_t *tok_context; /* context at the token definition */
	char *signature;

	bool re_evaluate      :1; /* needs to be reevaluated */
	bool defined          :1; /* for diagnostic purposes, remove later */
	bool is_capsule_token :1; /* it is a capsule level token */
	bool recursive        :1; /* used to check against recursion */
	bool valpresent       :1; /* the value is constant and has been computed already */
	bool tok_special      :1; /* locally defined token */
};

typedef struct tok_define_t tok_define;

typedef tok_define *token;

struct context_t {
	/*
	 * most tokens have <= LOCAL_TOKS parameters and
	 * are not recursive so use of local space in
	 * apply_tok for 'tok_context' to avoid lots of
	 * mallocs ....
	 */
	tok_define loctoks[LOCAL_TOKS];
	tok_define *othertoks;

	short no_toks;
	short recursive;

	/*
	 * don't know how many tag & labs defined in token
	 * so have to keep list; NB used only if recursive
	 */
	tag_con *tags;
	lab_con *labs;

	struct context_t *outer;
};

typedef struct context_t context;

extern context *crt_context;

/* dummy definitions */
typedef int taglink;
typedef int allink;
typedef int toklink;

typedef int tokextern;
typedef int tagextern;
typedef int alextern;

typedef int tokdec;

/* formal parameter during reading */
typedef struct {
	sortname sn;
	int tk;
} tokformals;

typedef struct tokformals_list_t tokformals_list;

typedef int tokdef;

typedef struct tagdec_t {
	tag tg;            /* identifying tag */
	shape sha;         /* the shape of the tag */
	access_option acc; /* its access_options */
	bool is_variable;  /* 1 for variable, 0 for identity */
	bool is_common;    /* 1 for common_tagdec */
} tagdec;

typedef struct {
	tag tg;         /* identifying tag */
	exp def;        /* the associated exp definition */
	bool var;       /* 1 for variable, 0 for identity */
	bool is_common; /* 1 for common_tagdef */
} tagdef;

typedef int al_tagdef;

/* number tdfstrings */
typedef struct {
	int number;
	tdfstring *elems;
} tdfstring_list;

typedef tdfstring tdfident;

typedef tdfstring_list tdfident_list;

typedef tdfident_list unique;

typedef struct {
	union {
		unique u;
		tdfstring id;
	} ex;
	bool isstring;
} external;

typedef struct {
	char *id; /* name */
	tdfint n; /* index */
} capsule_link;

/* number capsule_links */
typedef struct {
	int number;
	capsule_link *members;
} capsule_link_list;

/* number tdfints */
typedef struct {
	int number;
	tdfint *members;
} tdfint_list;

/* dummy definitions */
typedef int group_list;
typedef int extern_link_list;
typedef int linkextern_list;
typedef int extern_link;
typedef int group;
typedef int unit_list;
typedef int link;
typedef int linkextern;
typedef int links;
typedef int link_list;
typedef int tokdec_props;
typedef int tokdef_props;
typedef int tagdec_props;
typedef int tagdef_props;
typedef int al_tagdef_props;
typedef int tokdef_bd;
typedef int links_list;

typedef struct capsule_frees_t {
	void *ptr;
	struct capsule_frees_t *next;
} capsule_frees;

#endif

