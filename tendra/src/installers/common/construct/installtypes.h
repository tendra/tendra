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
 *Revision 1.2  2002/11/21 22:31:03  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1996/11/12  10:42:24  currie
 * unsigned cases
 *
 * Revision 1.6  1996/01/08  11:49:26  currie
 * ishppa
 *
 * Revision 1.5  1995/10/06  14:42:00  currie
 * Env-offset alignments + new div with ET
 *
 * Revision 1.4  1995/09/19  16:06:52  currie
 * isAlpha!!
 *
 * Revision 1.3  1995/09/11  15:35:37  currie
 * caller params -ve
 *
 * Revision 1.2  1995/05/05  08:10:54  currie
 * initial_value + signtures
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
 ***********************************************************************/
#ifndef installtypes_key
#define installtypes_key 1


typedef exp otagexp;

typedef struct otagexp_list_t 
{ exp start;
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

union signed_nat_u {int small_s_nat;
	flpt big_s_nat;};

struct signed_nat_t {union signed_nat_u signed_nat_val;
	char issmall;	/* 1 if small_s_nat 0 big */
	char negative;};	/* 1 for neg, 0 for pos */
typedef struct signed_nat_t signed_nat;

typedef struct nat_option_t 
{int present;	/* 1 if val is present, 0 otherwise */
    nat val;} nat_option;

typedef struct exp_option_t 
{int present;	/* 1 if val is present, 0 otherwise */
    exp val;} exp_option;


/* dummy definitions */
typedef int access;
typedef int access_option;

typedef int transfer_mode;


typedef struct alignment_t {
	int al_n;	/* code describing the state
				 *			1 - defined in al_val.al
				 *			2 - the join of al_val.al_join.a and b
				 *			3 - in al_val.al_join.a
				 */
	int sh_hd;
	struct alignment_u
	{
		int al;
		int al_frame;
		struct join_t {struct aldef_t * a; struct aldef_t * b;}
		al_join;
	} al_val;
} alignment_cell;

typedef struct aldef_t {
	struct aldef_t * next_aldef;	/* keeps a list of all aldefs */
	alignment_cell al;
} aldef;

typedef aldef * alignment;


struct bfvar_t {int bits;	/* number of bits in bitfield */
	int has_sign;	/* 1 if signed */
};
typedef struct bfvar_t bitfield_variety;

typedef char bool;

typedef exp shape;

typedef exp * label;

struct caselim_t {label lab;	/* label to jump if control between
								 *				   low and high */
	signed_nat low;
	signed_nat high;
};	/* caselim during reading */

typedef struct caselim_t caselim;

typedef struct error_treatment_t
{int err_code;	/* code for treatment */
	label jmp_dest;
} error_treatment;	/* error treatment during reading */

/* structure which describes a declaration */
struct dec_t {
	struct dec_t *def_next;
	/* if this is a global declaration this field holds next global
	 *     declaration which needs processing. If there is none, it is nilexp */
	union ut {
		struct dec_v {
			char *dec_id;
			/* identifier to be used */
			shape dec_shape;
			/* shape of the value */
			exp dec_exp;
			/* definition or nilexp */
			int unit_number;
			diag_global * diag_info;
			access acc;
			int index;
			/* used in inl_norm to hold procedure index number */
			
#if ismips || issparc || ispower || isAlpha || ishppa
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
		}             dec_val;
	}             dec_u;
};

typedef struct dec_t  dec;

typedef dec * tag;
typedef aldef * al_tag;

typedef int floating_variety;
typedef unsigned char ntest;
typedef unsigned char rounding_mode;

typedef struct shape_list_t
{shape * elems;
	int number;} shape_list;	/* number shapes */

typedef shape variety;


typedef struct tag_option_t {bool present;
	/* 1 if val is present, 0 otherwise */
	tag val;
} tag_option;

typedef struct string_option_t {
	bool present;
	string val;
} string_option;

typedef struct tagsh_t {shape sha;
	access visible;
	tag tg;
} tagshacc;

typedef struct tagsh_list_t
{exp id;
	exp last_def;
	exp last_id;
	exp proc_def;
	int size;
	int number;} tagshacc_list;

typedef struct tagacc_t {
	tag tg;
	access visible;
} tagacc;

typedef struct tagacc_option_t {
	bool present;	/* 1 if val is present, 0 otherwise */
	tagacc val;
} tagacc_option;

typedef  struct labtag_t {label place_label;
} labtag;


typedef struct exp_list_t
{exp start;	/* the first element of a list chained through bro */
	exp end;	/* the last element of a list chained through bro */
	int number;	/* the number of elements in the list */
} exp_list;

typedef exp caselim_list;


struct labtag_list_t
{label * elems;
	int number;	/* number labels */
};
typedef struct labtag_list_t label_list;

typedef struct tagshacc_option_t 
{int present;	/* 1 if val is present, 0 otherwise */
    tagshacc val;} tagshacc_option;

typedef struct proc_props_t {
	struct proc_props_t * pushed;
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
/* holds properties of a procedure while an internally defined
 *	   procedure is being read */

typedef struct version_t {
	int major_version;
	int minor_version;
} version;

typedef int version_props;
typedef int version_list;




#endif
