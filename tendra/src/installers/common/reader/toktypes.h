/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:06  nonce
 *Remove ossg prototypes.  This commit is largely whitespace changes,
 *but is nonetheless important.  Here's why.
 *
 *I.  Background
 *=========================
 *
 *    The current TenDRA-4.1.2 source tree uses "ossg" prototype
 *conventions, based on the Open Systems Software Group publication "C
 *Coding Standards", DRA/CIS(SE2)/WI/94/57/2.0 (OSSG internal document).
 *The goal behind ossg prototypes remains admirable: TenDRA should
 *support platforms that lack ANSI compliant compilers.  The explicit
 *nature of ossg's prototypes makes macro substition easy.
 *
 *    Here's an example of one function:
 *
 *    static void uop
 *	PROTO_N ( ( op, sha, a, dest, stack ) )
 *	PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where ) ) X
 *		  shape sha X exp a X where dest X ash stack )
 *    {
 *
 *tendra/src/installers/680x0/common/codec.c
 *
 *  The reasons for removing ossg are several, including:
 *
 *  0) Variables called 'X' present a problem (besides being a poor
 *variable name).
 *
 *  1) Few platforms lack ANSI-compliant compilers.  ISO-compliant
 *prototypes are easily handled by most every compiler these days.
 *
 *  2) Although TenDRA emphasizes portability, standards compliance is
 *the primary goal of the current project.  We should expect no less
 *from the compiler source code.
 *
 *  3) The benefits of complex prototypes are few, given parameter
 *promotion rules.  (Additionally, packing more types into int-sized
 *spaces tends to diminish type safety, and greatly complicates
 *debugging and testing.)
 *
 *  4) It would prove impractical to use an OSSG internal style document
 *in an open source project.
 *
 *  5) Quite frankly, ossg prototypes are difficult to read, but that's
 *certainly a matter of taste and conditioning.
 *
 *II.  Changes
 *=========================
 *
 *   This commit touches most every .h and .c file in the tendra source
 *tree.  An emacs lisp script (http://www.tendra.org/~nonce/tendra/rmossg.el)
 *was used to automate the following changes:
 *
 *   A.  Prototype Conversions.
 *   --------------------------------------------------
 *
 *   The PROTO_S, PROTO_Z, PROTO_N, PROTO_T, and PROTO_V macros were
 *rewritten to ISO-compliant form.  Not every file was touched.  The
 *files named ossg.h, ossg_api.h, code.c, coder.c and ossg_std.h were
 *left for hand editing.  These files provide header generation, or have
 *non-ossg compliant headers to start with.  Scripting around these
 *would take too much time; a separate hand edit will fix them.
 *
 *   B.  Statement Spacing
 *   --------------------------------------------------
 *
 *   Most of the code in the TenDRA-4.1.2 used extra spaces to separate
 *parenthetical lexemes.  (See the quoted example above.)  A simple
 *text substitution was made for:
 *
 *     Before            After
 *===================================
 *
 *   if ( x )            if (x)
 *   if(x)               if (x)
 *   x = 5 ;             x = 5;
 *   ... x) )            ... x))
 *
 *All of these changes are suggested by style(9).  Additional, statement
 *spacing considerations were made for all of the style(9) keywords:
 *"if" "while" "for" "return" "switch".
 *
 *A few files seem to have too few spaces around operators, e.g.:
 *
 *      arg1*arg2
 *
 *instead of
 *
 *      arg1 * arg2
 *
 *These were left for hand edits and later commits, since few files
 *needed these changes.  (At present, the rmossg.el script takes 1 hour
 *to run on a 2GHz P4, using a ramdisk.  Screening for the 1% that
 *needed change would take too much time.)
 *
 *   C.  License Information
 *   --------------------------------------------------
 *
 *After useful discussion on IRC, the following license changes were
 *made:
 *
 *   1) Absent support for $License::BSD$ in the repository, license
 *and copyright information was added to each file.
 *
 *   2) Each file begins with:
 *
 *   Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 *   All rights reserved.
 *
 *   Usually, copyright stays with the author of the code; however, I
 *feel very strongly that this is a group effort, and so the tendra
 *project should claim any new (c) interest.
 *
 *   3) The comment field then shows the bsd license and warranty
 *
 *   4) The comment field then shows the Crown Copyright, since our
 *changes are not yet extensive enough to claim any different.
 *
 *   5) The comment field then closes with the $TenDRA$ tag.
 *
 *   D.  Comment Formatting
 *   --------------------------------------------------
 *
 *The TenDRA-4.1.2 code base tended to use comment in this form:
 *
 *    /*
 *       Statement statement
 *       statement
 *     */
 *
 *while style(9) suggests:
 *
 *    /*
 *     * Statement statement
 *     * statement
 *     */
 *
 *Not every comment in -4.1.2 needed changing.  A parser was written to
 *identify non-compliant comments.  Note that a few comments do not
 *follow either the TenDRA-4.1.2 style or style(9), or any style I can
 *recognize.  These need hand fixing.
 *
 *   E.  Indentation
 *   --------------------------------------------------
 *
 *   A elisp tendra-c-mode was created to define how code should be
 *indented.  The structure follows style(9) in the following regards:
 *
 *  (c-set-offset 'substatement-open 0)
 *  (setq c-indent-tabs-mode t
 *	c-indent-level 4
 *	c-argdecl-indent t
 *	c-tab-always-indent t
 *	backward-delete-function nil
 *	c-basic-offset 4
 *	tab-width 4))
 *
 *This means that substatement opening are not indented.  E.g.:
 *
 *   if (condition)
 *   {
 *
 *instead of
 *
 *   if (condition)
 *     {
 *
 *or even
 *
 *   if (condition) {
 *
 *Each statement is indented by a tab instead of a spaces.  Set your tab
 *stop to comply with style(9); see the vim resources in the tendra
 *tree.  I'll add the emacs mode support shortly.
 *
 *No doubt, a function or two escaped change because of unusual
 *circumstances.  These must be hand fixed as well.
 *
 *III.  Things Not Changed
 *=========================
 *
 *    A large number of style(9) deficiencies remain.  These will
 *require a separate effort.  I decided to stop with the changes noted
 *above because:
 *
 *   0)  The script currently takes hours to run to completion even on
 *high-end consumer machines.
 *
 *   1)  We need to move on and fix other substantive problems.
 *
 *   2) The goal of this commit was *just* ossg removal; I took the
 *opportunity to get other major white-space issues out of the way.
 *
 *    I'll also note that despite this commit, a few ossg issues remain.
 *These include:
 *
 *   0) The ossg headers remain.  They contain useful flags needed by
 *other operations.  Additionally, the BUILD_ERRORS perl script still
 *generates ossg-compliant headers.  (This is being removed as we change
 *the build process.)
 *
 *   1) A few patches of code check for ossg flags: "if (ossg) etc."
 *These can be hand removed as well.
 *
 *   2) No doubt, a few ossg headers escaped the elisp script.  We can
 *address these seriatim.
 *
 *IV.  Testing
 *=========================
 *
 *    Without a complete build or test suite, it's difficult to
 *determine if these changes have introduced any bugs.  I've identified
 *several situations where removal of ossg caused bugs in sid and
 *calculus operations.  The elisp script avoids these situations; we
 *will hand edit a few files.
 *
 *    As is, the changes should behave properly; the source base builds
 *the same before and after the rmossg.el script is run.  Nonetheless,
 *please note that this commit changes over 23,000 PROTO declarations,
 *and countless line changes.  I'll work closely with any developers
 *affected by this change.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/08/23  13:31:10  pwe
 * no invert order, and initial ANDF-DE
 *
 * Revision 1.2  1995/06/22  09:21:11  currie
 * Signatures on tokens
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
 ***********************************************************************/
#ifndef toktypes_key
#define toktypes_key 1



/* definitions of types used in read_fns.c */

struct place_t {
	int  flag;  /* false if reading from stream, true if reading from pl_mem */
	char *pl_mem;	/* pointer to the characters */
	int  bits_on; /* bit_index displacement of the start */
};

typedef struct place_t  place;
typedef place bitstream;
typedef place bytestream;

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
	place tdplace;		/* place to read definition from */
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
