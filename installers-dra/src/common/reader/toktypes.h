/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TOKTYPES_H
#define TOKTYPES_H

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#else
#include <diag/dg_first.h>
#include <diag/diaginfo.h>
#endif

#include "exptypes.h"
#include <construct/installtypes.h>

#ifdef NEWDIAGS
#include <newdiag/dg_types.h>  /* new diags */
#include <newdiag/diagtypes.h> /* old diags */
#else
#include <diag/dg_types.h>  /* new diags */
#include <diag/diagtypes.h> /* old diags */
#endif



/* definitions of types used in read_fns.c */

struct place_t {
	/*
	 * false if reading from stream,
	 * true if reading from pl_mem
	 */
	int flag;
	char *pl_mem;	/* pointer to the characters */
	int bits_on;	/* bit_index displacement of the start */
};

typedef struct place_t place;
typedef place bitstream;
typedef place bytestream;

typedef struct sortname_t {
	int code;	/* code number for the sort - see sortmacs.h */
	int result;	/* if code is TOKEN this is the code for the result */
	/*
	 * pars.elems is an array of pars.number
	 * parameter sorts if the code is TOKEN
	 */
	struct sortname_list_t {
		struct sortname_t *elems;
		int number;
	} pars;
} sortname;

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

#include <reader/sort_union.h>

#define LOCAL_TOKS 4

struct tag_con_t {
	dec *namet;
	exp e;
	struct tag_con_t *rest;
};
typedef struct tag_con_t tag_con;

struct lab_con_t {
	label namel;
	exp e;
	struct lab_con_t *rest;
};
typedef struct lab_con_t lab_con;


typedef union tokval_u tokval;

/* struct holding a token definition */
struct tok_define_t {
	dec			**my_tagtab;		/* the tagtab current at the definition */
	aldef			**my_altab;		/* the altab current at the definition */
	exp			*my_labtab;		/* the labtab current at the definition */
	struct tok_define_t	**my_toktab;		/* the toktab current at the definition */
	diag_tagdef		**my_diagtab;		/* OLD DIAGS */	/* the diagtab current at the definition */
	dgtag_struct		**my_dgtab;		/* NEW DIAGS */ /* the dgtab current at the definition */
	char			*tok_name;		/* the identifier (if any) for the token */

	struct tokformals_list_t {
		sortname *par_sorts;			/* sorts of parameters */
		int *par_names;				/* token index for parameters */
		int number;				/* total number of parameters */
	} params;					/* description of formal parameters */

	sortname		tdsort;			/* sort of token result */
	place			tdplace;		/* place to read definition from */
	int			unit_number;		/* number of unit in which defined */
	union tokval_u		tdvalue;		/* preserved value if valpresent */
	int			tok_index;		/* index number of this token */
	int			tdtoken;		/* the token */
	struct context_t	*tok_context;		/* context at the token definition */
	char			*signature;
	unsigned int		re_evaluate:1;		/* needs to be reevaluated */
	unsigned int		defined:1;		/* for diagnostic purposes, remove later */
	unsigned int		is_capsule_token:1;	/* it is a capsule level token */
	unsigned int		recursive:1;		/* used to check against recursion */
	unsigned int		valpresent:1;		/* the value is constant and has been computed already */
	unsigned int		tok_special:1;		/* locally defined token */
};
typedef struct tok_define_t tok_define;

typedef tok_define *token;

struct context_t {
        tok_define loctoks[LOCAL_TOKS];
	/*
	 * most tokens have <=LOCAL_TOKS parameters and
	 * are not recursive so use of local space in
	 * apply_tok for 'tok_context' to avoid lots of
	 * mallocs ....
	 */
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

typedef struct tokformals_t {
	sortname sn;
	int tk;
} tokformals;		/* formal parameter during reading */

typedef struct tokformals_list_t tokformals_list;

typedef int tokdef;

typedef struct tagdec_t {
	tag tg;			/* identifying tag */
	shape sha;		/* the shape of the tag */
	access_option acc;	/* its access_options */
	bool is_variable;	/* 1 for variable, 0 for identity */
	bool is_common;		/* 1 for common_tagdec */
} tagdec;

typedef struct tagdef_t {
	tag tg;			/* identifying tag */
	exp def;		/* the associated exp definition */
	bool var;		/* 1 for variable, 0 for identity */
	bool is_common;		/* 1 for common_tagdef */
} tagdef;

typedef int al_tagdef;

typedef struct tdfstring_list_t {
	int number;
	tdfstring *elems;
} tdfstring_list;	/* number tdfstrings */

typedef tdfstring tdfident;

typedef tdfstring_list tdfident_list;

typedef tdfident_list unique;

union external_u {
	unique u;
	tdfstring id;
};

typedef struct external_t {
	union external_u ex;
	bool isstring;
} external;

typedef struct capsule_link_t {
	char *id;	/* name */
	tdfint n;	/* index */
} capsule_link;

typedef struct capsule_link_list_t {
	int number;
	capsule_link *members;
} capsule_link_list;	/* number capsule_links */

typedef struct tdfint_list_t {
	int number;
	tdfint *members;
} tdfint_list;		/* number tdfints */

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

#endif /* TOKTYPES_H */
