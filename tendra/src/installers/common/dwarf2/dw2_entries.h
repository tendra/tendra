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
 *Revision 1.2  2002/11/21 22:31:05  nonce
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
 * Revision 1.3  1998/03/11  11:03:41  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/02/18  11:22:19  pwe
 * test corrections
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.10  1998/01/09  09:31:25  pwe
 * prep restructure
 *
 * Revision 1.9  1997/12/04  19:41:21  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.8  1997/11/06  09:22:03  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.7  1997/10/23  09:27:32  pwe
 * ANDF-DE v1.7, extra diags
 *
 * Revision 1.6  1997/10/10  18:18:29  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.5  1997/08/23  13:36:36  pwe
 * initial ANDF-DE
 *
 * Revision 1.4  1997/04/17  11:50:20  pwe
 * Sparc and 80x86 support
 *
 * Revision 1.3  1997/04/01  17:19:38  pwe
 * diagnose pl_tests and locate -> platform specific
 *
 * Revision 1.2  1997/03/24  11:10:23  pwe
 * struct bitfields
 *
 * Revision 1.1  1997/03/20  16:09:08  pwe
 * first version
 *
 **********************************************************************/

#ifndef entries_tag
#define entries_tag 1


typedef struct 
{
	int		index;
	long *	attr;
	long		valid;
	long		special;
#if 1
	char *	aname;
#endif
} abbrev_entry;

extern abbrev_entry
dwe_comp_unit,
	dwe_cmac_unit,
	dwe_module,
	dwe_namespace,
	dwe_subunit,
	dwe_childunit,
	dwe_child_acc,
	dwe_import,
	dwe_import_p,
	dwe_entrypt,
	dwe_param,
	dwe_formal,
	dwe_opt_par,
	dwe_thrown_t,
	dwe_inl_call,
	dwe_inl_opnd,
	dwe_scope,
	dwe_fragment,
	dwe_label,
	dwe_with,
	dwe_try,
	dwe_catch,
	dwe_variable,
	dwe_constant,
	dwe_tmpl_type,
	dwe_tmpl_val,
	dwe_tmpl_proc,
	dwe_tmpl_mod,
	dwe_typedef,
	dwe_typecon,
	dwe_cnstraint,
	dwe_base_type,
	dwe_cnst_type,
	dwe_vol_type,
	dwe_clwd_type,
	dwe_als_type,
	dwe_lim_type,
	dwe_ptr_type,
	dwe_hpptr_t,
	dwe_ref_type,
	dwe_pack_type,
	dwe_arr_type,
	dwe_arr_dyn,
	dwe_subr_type,
	dwe_enum_type,
	dwe_enum_tor,
	dwe_enum_char,
	dwe_struct_t,
	dwe_member,
	dwe_varpart,
	dwe_varpart_t,
	dwe_variant_0,
	dwe_variant_1,
	dwe_variant_n,
	dwe_union_t,
	dwe_class_t,
	dwe_inheritce,
	dwe_friend,
	dwe_ptrmem_t,
	dwe_ind_mem,
	dwe_proc_type,
	dwe_procv_t,
	dwe_string_t,
	dwe_stringc_t,
	dwe_file_t,
	dwe_set_t,
	dwe_fixpt_t,
	dwe_fldg_t,
	dwe_modular_t,
	dwe_task_t,
	dwe_synch_t,
	dwe_entry,
	dwe_for_unit,
	dwe_for_lang,
	dwe_call,
	dwe_return,
	dwe_destruct,
	dwe_branch,
	dwe_branch_0,
	dwe_break,
	dwe_test,
	dwe_test_0,
	dwe_jump,
	dwe_jump_0,
	dwe_lj,
	dwe_lj_0,
	dwe_throw,
	dwe_barrier,
	dwe_select,
	dwe_accept,
	dwe_accept_c,
	dwe_rts,
	dwe_rts_en,
	dwe_sel_alt,
	dwe_sel_alt_c,
	dwe_sel_guard,
	dwe_asynchsel,
	dwe_trigger,
	dwe_trigger_c,
	dwe_abort_pt,
	dwe_abort_ptc,
	dwe_requeue,
	dwe_unknown_t,
	dwe_span,
	dwe_span_strt,
	dwe_span_end,
	dwe_absent,
	dwe_absent_r,
	dwe_absent_x,
	dwe_absent_xr,
	dwe_displaced,
	dwe_displ_x,
	dwe_moved,
	dwe_moved_r,
	dwe_moved_x,
	dwe_moved_xr,
	dwe_optim,
	dwe_proc;

extern void init_dw_entries(void);

extern long dw_entry(abbrev_entry en, long attr);



/* general attributes */

#define H_AO	0x1		/* inline abstract origin */
#define H_SP	0x2		/* ref specification */
#define H_DC	0x4		/* declaration only */
#define H_NM	0x8		/* has name */
#define H_XY	0x10		/* has source coordinates */
#define H_EX	0x20		/* flag for external */
#define H_AT	0x40		/* has artificiality */
#define H_AC	0x80		/* has accessibility */
#define H_TP	0x100		/* has type */
#define H_SS	0x200		/* has start scope */
#define H_RP	0x400		/* has repn clause */
#define H_GN	0x800		/* generic name */
#define H_EL	0x1000		/* has elaboration */
#define H_SE	0x2000		/* Ada is separate */

/* attributes for functions */

#define H_PC	0x10000		/* has code address */
#define H_CC	0x20000		/* has calling convention */
#define H_PT	0x40000		/* has prototype */
#define H_IL	0x80000		/* inlined */
#define H_VT	0x100000	/* has virtuality */
#define H_VL	0x200000	/* vtable elem location */
#define H_SL	0x400000	/* has static link */
#define H_LN	0x800000	/* has language call convention */

/* attributes for objects */

#define H_CV	0x10000		/* has const value */
#define H_LC	0x20000		/* has single location  */
#define H_LL	0x40000		/* has location list */
#define H_LE	0x80000		/* has extended loclist */
#define H_VP	0x100000	/* variable parameter */
#define H_DF	0x200000	/* default value */
#if 0
#define H_DX	0x400000	/* default existance */
#endif

/* attributes for lex_scopes */

/*	H_PC	0x10000	*/
#define H_BG	0x20000		/* has 'BEGIN' */

/* attributes for types */

#define H_SZ	0x10000		/* has byte size */
#define H_NW	0x20000		/* is new */
#define H_AD	0x40000		/* Ada derived */

/* attributes for bounds */

#define H_LB	0x40000		/* lower bound */
#define H_UB	0x80000		/* upper bound */
#define H_CN	0x100000	/* count */

/* attributes for members */

/*	H_LC	0x20000	*/
#define H_BF	0x10000		/* bitfield */
#define H_DS	0x40000		/* discriminant */
/*	H_DF	0x100000 */
/*	H_DX	0x200000 REMOVE	*/

/* attributes for class types */

/*	H_AD	0x40000 */
#define H_VS	0x100000	/* vtable static */
#define H_VD	0x200000	/* vtable dynamic */
#define H_RS	0x400000	/* rtti static */
#define H_RD	0x800000	/* rtti dynamic */

/* attributes for Ada tasks and Synchronised types */

#define H_CB	0x100000	/* control block */
#define H_ID	0x200000	/* task id */

/* attributes for constraints */

#define	H_RM	0x800000	/* ref member */
/*	H_TP	0x100 */
/*	H_CV	0x10000 */

/* attributes for fixed point type */

/*	H_DF	0x100000    delta */
/*	H_DS	0x40000     digits */



#define H_EXTN	0x80000000



#endif
