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


/* 80x86/expmacs.h */

/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:02  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.15  1997/10/23  09:37:00  pwe
 * extra_diags
 *
 * Revision 1.14  1997/10/10  18:25:07  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.13  1997/04/23  16:24:42  pwe
 * added constovf
 *
 * Revision 1.12  1996/12/13  14:39:24  pwe
 * prep NEWDIAGS
 *
 * Revision 1.11  1996/12/10  15:11:34  pwe
 * prep NEWDIAGS
 *
 * Revision 1.10  1996/02/22  10:03:36  pwe
 * sco diag recursive struct (& clearinlined)
 *
 * Revision 1.9  1995/09/22  16:29:18  pwe
 * setoutpar introduced
 *
 * Revision 1.8  1995/09/05  16:24:48  pwe
 * specials and exception changes
 *
 * Revision 1.7  1995/09/01  17:30:01  pwe
 * traps and Build scripts
 *
 * Revision 1.6  1995/08/30  16:06:30  pwe
 * prepare exception trapping
 *
 * Revision 1.5  1995/08/14  13:53:33  pwe
 * several corrections, tail calls and error jumps
 *
 * Revision 1.4  1995/08/04  08:29:18  pwe
 * 4.0 general procs implemented
 *
 * Revision 1.3  1995/07/07  15:22:16  pwe
 * prepare for 4.0, and correct PIC switch
 *
 * Revision 1.2  1995/01/30  12:56:10  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:31:17  jmf
 * Initial revision
 *
 **********************************************************************/

#ifndef expmacs_key
#define expmacs_key 1


#define nilexp (exp)0

/* main components of exp */

#define son(x) ((x)->sonf.e)
#define bro(x) ((x)->brof.e)
#define last(x) (int)((x)->lastf)
#define name(x) (x)->namef
#define sh(x) (x)->shf
#define pt(x) ((x)->ptf.e)
#define props(x) (x)->propsf
#define no(x) ((x)->numf.l)
#define parked(x) ((x)->park)
#ifdef NEWDIAGS
#define dgf(x) ((x)->diagf)
#endif

/* alternative components of exp */

#define brog(x) ((x)->brof.glob)
#define nostr(x) ((x)->numf.str)
#define ptno(x) ((x) ->ptf.l)
#define sonno(x) ((x) ->sonf.l)
#define fno(x) ((x) -> numf.f)
#ifndef NEWDIAGS
#define dno(x) ((x) -> numf.d)
#endif
#define uno(x) ((x) -> numf.ui)

/* ntests */
#define test_number(x) (ntest)((x)->propsf & 0x1f)
#define settest_number(x, t) (x)->propsf= (prop)(((x)->propsf & 0xe0) | (int)(t))

/* rounding */
#define round_number(x) ((x)->propsf >> 3)
#define setround_number(x,r) (x)->propsf=(prop)(((x)->propsf & 0x7) | (r << 3))

/* error handling macros */
#define errhandle(x) ((x)->propsf & 0x7)
#define optop(x) ((int)errhandle(x) <= 2) 
#define seterrhandle(x,e) (x)->propsf= (prop)(((x)->propsf & 0xf8) | (e))

/* properties of constructions with EXCEPTIONS */
#define setjmp_dest(r,d) {(r)->ptf.e = (d); ++no(son(d));}
#define isov(x) (errhandle(x) == 0x4)
#define istrap(x) (((x)->propsf & 0x3) == 0x3)

/* setting macros for components of exp */

#define setbro(x,b) (x)->brof.e = (b)
#define setsh(x,b) (x)->shf = (b)
#define setson(x,b) (x)->sonf.e = (b)
#define setpt(x,b) (x)->ptf.e = (b)
#define setlast(x) (x)->lastf = 1
#define clearlast(x) (x)->lastf = 0
#define setname(x,n) (x)->namef = (n)
#define setfather(f,s) (s)->brof.e = (f); (s)->lastf = 1

/* components of shapes */
#define shape_size(x) ((x)->numf.l)
#define shape_align(x) ((x)->brof.ald->al.al_val.al)
#define align_of(x) ((x)->brof.ald)
#define al1(x) ((x)->sonf.ald->al.al_val.al)
#define al1_of(x) ((x)->sonf.ald)
#define al2(x) ((x)->ptf.ald->al.al_val.al)
#define al2_of(x) ((x)->ptf.ald)
#define is_signed(x) (int)((x)->lastf)

#define frame_al_of_ptr(x) (x)->sonf.ald->al.al_val.al_frame
#define frame_al1_of_offset(x) (x)->sonf.ald->al.al_val.al_frame
#define al_includes_vcallees 16
#define al_includes_caller_args 6


/* properties of IDENT_TAG */


#define setvar(e) props(e) = (prop)(props(e) | 0x01)
/* sets the property of a declaration to isvar (is a variable)*/
#define clearvar(e) props(e) = (prop)(props(e) & ~0x01)
/* sets the property of a declaration to !isvar */
#define setid(e) props(e) = (prop)(props(e) & ~0x01)
/* sets the property of a declaration to !isvar */
#define isvar(e) (props(e)&0x01)
/* tests the property of a declaration as above */

#define setvis(e) props(e) = (prop)(props(e) | 0x02)
/* sets the property of a declaration to in memory */
#define isvis(e) (props(e)&0x02)
/* tests if a declaration is to be in memory */

#define setenvoff(e) props(e) = (prop)(props(e) | 0x04)
/* sets the property of a declaration to visible */
#define isenvoff(e) (props(e)&0x04)
/* tests if a declaration is to be visible */

#define setcaonly(e) props(e) = (prop)(props(e) | 0x08)
/* sets the property of a variable declaration to show that it is only
 *     operated on by contents and assign operations */
#define clearcaonly(e) props(e) = (prop)(props(e) & ~0x08)
#define iscaonly(e) (props(e)&0x08)
/* tests the above property */

#define setusereg(e) props(e) = (prop)(props(e) | 0x10)
/* sets the property of a declaration to recommend the use of
 *     a register */
#define isusereg(e) (props(e)&0x10)
/* tests a declaration for a register recommendation */
#define clearusereg(e) props(e) = (prop)(props(e) & ~0x10)

#define setparam(x) props(x) = (prop)(props(x) | 0x20)
#define clearparam(x) props(x) = (prop)(props(x) & ~0x20)
#define isparam(x) (props(x) & 0x20)

#define setglob(e) props(e) = (prop)(props(e) | 0x40)
/* sets property of declaration to be global, in this case
 *     bro(e) will be the index of the declaration */
#define clearglob(e) props(e) &= ~0x40
#define isglob(e) (props(e)&0x40)
/* tests the above property */

#define setcopy(e) props(e) = (prop)(props(e) | 0x80)
/* set a flag used during copy : also used for LABST_TAG */
#define clearcopy(e) props(e) = (prop)(props(e) & ~0x80)
/* clear a flag used during copy */
#define copying(e) (props(e)&0x80)
/* test the flag used during copying */

/* Set in weights and used in coder. At this time no copying */
#define set_intnl_call(x) props(x) = (prop)(props(x) | 0x80)
#define has_intnl_call(x) (props(x) & 0x80)

/* variable has had the no-sign-extension opt. (80x86 only) */
#define setse_opt(x) props(x) = (prop)(props(x) | 0x400)
#define isse_opt(x) (props(x) & 0x400)

#define setinlined(x) props(x) = (prop)(props(x) | 0x200)
#define isinlined(x) (props(x) & 0x200)
#define clearinlined(x) props(x) &= ~0x200

/* variable is used both as byte and long (80x86 only) */
#define setbyteuse(x) props(x) = (prop)(props(x) | 0x800)
#define isbyteuse(x) (props(x) & 0x800)

/* parameter used for output (needs only to be in memory for 80x86) */
#define setoutpar(x) setvis(x)
#define isoutpar(x) isvis(x)
#define clearoutpar(x) 

/* properties of PROC_TAG construction */

#define set_struct_res(x) props(x) = (prop)(props(x) | 0x1)
#define has_struct_res(x) (props(x) & 0x1)

#define set_loc_address(x) props(x) = (prop)(props(x) | 0x2)
#define loc_address(x) (props(x) & 0x2)

#define set_proc_has_setjmp(x) props(x) = (prop)(props(x) | 0x4)
#define proc_has_setjmp(x) (props(x) & 0x4)

#define set_proc_has_alloca(x) props(x) = (prop)(props(x) | 0x8)
#define proc_has_alloca(x) (props(x) & 0x8)

#define set_proc_has_lv(x) props(x) = (prop)(props(x) | 0x10)
#define proc_has_lv(x) (props(x) & 0x10)

#define isrecursive(x) (props(x) & 0x20)
#define setrecursive(x) props(x) = (prop)(props(x) | 0x20)

#define set_proc_uses_crt_env(x) props(x) = (prop)(props(x) | 0x40)
#define proc_uses_crt_env(x) (props(x) & 0x40)

#define set_proc_uses_external(x) props(x) = (prop)(props(x) | 0x80)
#define proc_uses_external(x) (props(x) & 0x80)

/* used for diags, after code production */
#define set_proc_has_fp(x) props(x) = (prop)(props(x) | 0x100)
#define clear_proc_has_fp(x) props(x) &= ~0x100
#define proc_has_fp(x) (props(x) & 0x100)


/*set property of SOLVE_TAG construction */
#define setcrtsolve(x) props(x)=1

/* properties of pt of REP_TAG and SOLVE_TAG during copy */
#define set_copying_solve(x) props(x) = (prop)(props(x) | 1)
#define clear_copying_solve(x) props(x) = (prop)(props(x) & ~0x01)

/* properties of MOVECONT_TAG construction */
#define setnooverlap(x) props(x) = (prop)(props(x) | 0x01)
#define isnooverlap(x) (props(x) & 0x01)

/* properties of CONT_TAG construction */
#define set_propagate(x) props(x) = (prop)(props(x) | 0x1)
#define to_propagate(x) (props(x) & 0x1)
#define clear_propagate(x) props(x) = (prop)(props(x) & ~0x01)

/* various properties of LABST_TAG construction are used in exp.c */
#define set_loaded_lv(x) props(x) = (prop)(props(x) | 0x10)
#define is_loaded_lv(x) (props(x) & 0x10)
#define setunroll(x) props(x) = (prop)(props(x) | 0x04)
#define clearunroll(x)  props(x) = (prop)(props(x) & ~0x04)
#define isunroll(x) (props(x) & 0x04)
/* see also setcopy */
#define set_dg_labmark(x) props(x) = (prop)(props(x) | 0x800)
#define dg_labmark(x)(props(x) & 0x800)
#define clear_dg_labmark(x) props(x) = (prop)(props(x) & ~0x800)

/* properties of NAME_TAG construction */
#define setlastuse(x) props(x) = (prop)(props(x) | 0x01)
#define islastuse(x) (props(x) & 0x01)

#define setloadparam(x) props(x) = (prop)(props(x) | 0x02)
#define isloadparam(x) (props(x) & 0x02)

#define setreallyass(x) props(x) = (prop)(props(x) | 0x04)
#define isreallyass(x) (props(x) & 0x04)

#ifdef NEWDIAGS
#define setisdiaginfo(x) props(x) = (prop)(props(x) | 0x08)
#define isdiaginfo(x) (props(x) & 0x08)

#define setdiscarded(x) props(x) = (prop)(props(x) | 0x10)
#define isdiscarded(x) (props(x) & 0x10)
#endif

/* properties of STRING_TAG construction */
#define string_char_size(e) props(e)

/* properties of VAL_TAG construction */
#define setbigval(x)  props(x) = (prop)(props(x) | 0x01)
#define clearbigval(x) props(x) = (prop)(props(x) & ~0x01)
#define isbigval(x) (props(x) & 0x01)

#define setconstovf(x)  props(x) = (prop)(props(x) | 0x02)
#define constovf(x) (props(x) & 0x02)

/* properties of REP_TAG construction */
#define setunrolled(x)  props(x) = (prop)(props(x) | 0x01)
#define isunrolled(x) (props(x) & 0x01)

/* properties of APPLY_TAG construction */
#define settoinline(x)  props(x) = (prop)(props(x) | 0x01)
#define istoinline(x) (props(x) & 0x01)

#define setbuiltin(x)  props(x) = (prop)(props(x) | 0x8000)
#define builtinproc(x) (props(x) & 0x8000)	/* trans386 special */

/* properties of ASM construction */
#define asm_string(x) (props(x) & 0x01)
#define asm_in(x) (props(x) & 0x02)
#define asm_out(x) (props(x) & 0x04)
#define asm_ptr(x) (props(x) & 0x08)
#define asm_var(x) (props(x) & 0x0c)	/* out | ptr */

/* properties of alloca constructions */
#define set_checkalloc(x) props(x) |= 1;
#define checkalloc(x) (props(x) & 1)


/* properties of jump record */

#define fstack_pos_of(x) (x)->propsf


#define set_callee(id)	setname(son(id), formal_callee_tag)
#define set_make_procprops(e, p) props(e) |= ((p)<<8)
#define proc_has_vcallees(e) (props(e) & 0x200)
#define postlude_has_call(e) (props(e) & 1)
#define call_has_vcallees(e) (props(e) & 2)
#define proc_has_checkstack(e) (props(e) & 0x800)
#define proc_has_vcallers(e) (props(e) & 0x100)
#define proc_has_nolongj(e) (props(e) & 0x1000)

#define set_proc_needs_envsize(x) props(x) = (prop)(props(x) | 0x8000)
#define proc_needs_envsize(x) (props(x) & 0x8000)

#define call_is_untidy(e) (props(bro(son(e))) & 4)
#define call_has_checkstack(e) (props(bro(son(e))) & 8)


/* rounding for alignment */

#define rounder(n,a) (((n)+(a)-1)/(a))*(a)

#define align32 (32)
#define align16 (16)
#define align8 (8)
#define align1 (1)

#define size64 (64)
#define size32 (32)
#define size16 (16)
#define size8 (8)

#endif


