/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef toktypes_key
#define toktypes_key 1

typedef tdf_pos bitstream;
typedef tdf_pos bytestream;

typedef struct sortname_t
{int code;	/* code number for the sort - see sortmacs.h */
	int result;	/* if code is TOKEN this is the code for the result */
	struct sortname_list_t {struct sortname_t * elems;
		int number;
	} pars;
	/* pars.elems is an array of pars.number parameter sorts 
	 *	   if the code is TOKEN */
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

struct tok_define_t;

#include "sort_union.h"

#define LOCAL_TOKS 4

typedef struct t_tag_con {
	dec * namet;
	exp e;
	struct t_tag_con * rest;
} tag_con;

typedef struct t_lab_con {
	label namel;
	exp e;
	struct t_lab_con * rest;
} lab_con;


typedef union tokval_u tokval;

struct tok_define_t {
	dec * * my_tagtab;		/* the tagtab current at the definition */
	aldef * * my_altab;	/* the altab current at the definition */
	exp * my_labtab;		/* the labtab current at the definition */
	struct tok_define_t * * my_toktab;
	/* the toktab current at the definition */
	diag_tagdef * * my_diagtab;	/* OLD DIAGS */
	/* the diagtab current at the definition */
	dgtag_struct * * my_dgtab;		/* NEW DIAGS */
	/* the dgtab current at the definition */
	char * tok_name;	/* the identifier (if any) for the token */
	struct tokformals_list_t	/* description of formal parameters */
	{
        sortname * par_sorts;	/* sorts of parameters */
        int * par_names;	/* token index for parameters */
        int number;		/* total number of parameters */
	} params;
	sortname tdsort;		/* sort of token result */
	tdf_pos tdplace;		/* place to read definition from */
	int unit_number;		/* number of unit in which defined */
	union tokval_u tdvalue;	/* preserved value if valpresent */
	int tok_index;		/* index number of this token */
	int   tdtoken;		/* the token */
	struct t_context * tok_context;     /* the context at the token definition */
	char * signature; 
	unsigned int re_evaluate :1;	/* needs to be reevaluated */
	unsigned int defined : 1;
	/* for diagnostic purposes, remove later */
	unsigned int is_capsule_token :1;	/* it is a capsule level token */
	unsigned int recursive :1;	/* used to check against recursion */
	unsigned int valpresent :1;/* the value is constant and has been
								*				   computed already */
	unsigned int tok_special :1; /* locally defined token */
};


/* struct holding a token definition */
typedef struct tok_define_t  tok_define;

typedef tok_define * token;

typedef struct t_context{
	tok_define loctoks[LOCAL_TOKS];    
	tok_define * othertoks; /* most tokens have <=LOCAL_TOKS parameters and
							 *				are not recursive so use of local space in
							 *				apply_tok for 'tok_context' to avoid lots of
							 *				mallocs ....*/ 
	short no_toks;
	short recursive;
	tag_con * tags;	   /* ... don't know how many tag & labs defined in token
						*			      so have to keep list; NB used only if recursive */
	lab_con * labs;
	struct t_context * outer;
} context;

extern context * crt_context;

/* dummy definitions */
typedef int taglink;
typedef int allink;
typedef int toklink;


typedef int tokextern;

typedef int tagextern;
typedef int alextern;

typedef int tokdec;

typedef struct tokformals_t
{sortname sn;
	int tk;
} tokformals;	/* formal parameter during reading */

typedef struct tokformals_list_t  tokformals_list;

typedef int tokdef;

typedef struct tagdec_t
{tag tg;		/* identifying tag */
	shape sha;		/* the shape of the tag */
	access_option acc;	/* its access_options */
	bool is_variable;	/* 1 for variable, 0 for identity */
	bool is_common;	/* 1 for common_tagdec */
} tagdec;

typedef struct tagdef_t
{
	tag tg;		/* identifying tag */
	exp def;		/* the associated exp definition */
	bool var;		/* 1 for variable, 0 for identity */
	bool is_common;	/* 1 for common_tagdef */
} tagdef;

typedef int al_tagdef;


typedef struct tdfstring_list_t
{int number;
	tdfstring * elems;
} tdfstring_list;	/* number tdfstrings */

typedef tdfstring tdfident;

typedef tdfstring_list tdfident_list;

typedef tdfident_list unique;

union external_u {unique u; tdfstring id;};

typedef struct external_t {union external_u ex; bool isstring;} external;

typedef struct capsule_link_t
{
    char * id;	/* name */
    tdfint n;	/* index */
} capsule_link;

typedef struct capsule_link_list_t 
{
    int number;
    capsule_link * members;
    
} capsule_link_list;	/* number capsule_links */

typedef struct tdfint_list_t 
{
    int number;
    tdfint * members;
    
} tdfint_list;	/* number tdfints */

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

typedef struct capsule_frees_t
{void * ptr;
	struct capsule_frees_t * next;
} capsule_frees;


#endif
