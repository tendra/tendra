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
 *    Copyright (c) 1993 Open Software Foundation, Inc.
 *
 *
 *    All Rights Reserved
 *
 *
 *    Permission to use, copy, modify, and distribute this software
 *    and its documentation for any purpose and without fee is hereby
 *    granted, provided that the above copyright notice appears in all
 *    copies and that both the copyright notice and this permission
 *    notice appear in supporting documentation.
 *
 *
 *    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
 *    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *    PARTICULAR PURPOSE.
 *
 *
 *    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 *    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 *    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $TenDRA$
 */

/*
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
 */



/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:12  nonce
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
 * Revision 1.2  1998/02/04  15:48:45  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/08/04  11:56:29  pwe
 * add constovf
 *
 * Revision 1.2  1996/10/04  16:00:38  pwe
 * add banners and mod for PWE ownership
 *
 **********************************************************************/


#ifndef expmacs_key
#define expmacs_key 1
#include "bitsmacs.h"
#include "shapemacs.h"

#define nilexp (exp)0

/* main components of exp */

#define son(x) ((x)->sonf.e)
#define bro(x) ((x)->brof.e)
#define last(x) (x)->lastf
#define name(x) (x)->namef
#define sh(x) (x)->shf
#define pt(x) ((x)->ptf.e)
#define props(x) (x)->propsf
#define no(x) ((x)->numf.l)
#define parked(x) ((x)->park)

/* alternative components of exp */

#define brog(x) ((x)->brof.glob)
#define nostr(x) ((x)->numf.str)
#define ptno(x) ((x) ->ptf.l)
#define sonno(x) ((x) ->sonf.l)
#define fno(x) ((x) -> numf.f)
#define dno(x) ((x) -> numf.d)
#define uno(x) ((x) -> numf.ui)

/* ntests */
#define test_number(x) (props(x) & 0xf)
#define settest_number(x, t) props(x) = ((props(x) & ~0xf)|(t))

/* rounding */
#define round_number(x) ((x)->propsf >> 3)
#define setround_number(x,r) (x)->propsf=(((x)->propsf & 0x7) | (r << 3))

/* error handling macros */
#define errhandle(x) ((x)->propsf & 0x7)
#define optop(x) ((int)errhandle(x) <= 2) 
#define seterrhandle(x,e) (x)->propsf= ((x)->propsf & 0xf8) | (e)

/* properties of constructions with EXCEPTIONS */
#define setjmp_dest(r,d) {(r)->ptf.e = (d); ++no(son(d));}
#define isov(x) (errhandle(x) == 0x4)

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
#define shape_size(x)                   ((x)->numf.l)
#define shape_align(x)                  ((unsigned long)((x)->brof.ald->al.al_val.al))
#define align_of(x)                     ((x)->brof.ald)
#define al1(x)                          ((unsigned long)((x)->sonf.ald->al.al_val.al))
#define al1_of(x)                       ((x)->sonf.ald)
#define al2(x)                          ((unsigned long)((x)->ptf.ald->al.al_val.al))
#define al2_of(x)                       ((x)->ptf.ald)
#define is_signed(x)                  last(x)

/* 
 * MACROS FOR MANIPULATING PROPERTIES
 */
#define pset(x, m)	                props (x) = (prop) (props (x) | (m))
#define pclr(x, m)	                props (x) = (prop) (props (x) & ~(m))
#define ptst(x, m)	                ((props (x) & (m)) != 0)

/* 
 * PROPERTIES OF IDENT 
 */

#define setvar(x)                     pset(x , 0x01)
#define clearvar(x)                   pclr(x , 0x01)
#define isvar(x)                      ptst(x , 0x01)
#define setid(x)                      clearvar(x)

#define setvis(x)                     pset(x , 0x02)
#define clearvis(x)                   pclr(x , 0x02)
#define isvis(x)                      ptst(x , 0x02)

#define setenvoff(x)                  pset(x , 0x04)
#define clearenvoff(x)                pclr(x , 0x04)
#define isenvoff(x)                   ptst(x , 0x04)

#define setcaonly(x)                  pset(x , 0x08)
#define clearcaonly(x)                pclr(x , 0x08)
#define iscaonly(x)                   ptst(x , 0x08)

#define setusereg(x)                  pset(x , 0x10)
#define clearusereg(x)                pclr(x , 0x10)
#define isusereg(x)                   ptst(x , 0x10)

#define setparam(x)                   pset(x , 0x20)
#define clearparam(x)                 pclr(x , 0x20)
#define isparam(x)                    ptst(x , 0x20)

#define setglob(x)                    pset(x , 0x40)
#define clearglob(x)                  pclr(x , 0x40)
#define isglob(x)                     ptst(x , 0x40)

#define setcopy(x)                    pset(x , 0x80)
#define clearcopy(x)                  pclr(x , 0x80)
#define copying(x)                    ptst(x , 0x80)

#define setvarargparam(x)              pset(x, vararg_bit)
#define isvarargparam(x)               ptst(x ,vararg_bit)
#define clearvarargparam(x)            pclr(x ,vararg_bit)


#define setinlined(x)                 pset(x , inlined) /* inlined defined in bitsmacs.h */
#define clearinlined(x)               pclr(x , inlined)
#define isinlined(x)                  ptst(x , inlined)

#define setoutpar(x)                  pset(x , 0x8000)
#define isoutpar(x)                   ptst(x , 0x8000)
#define clearoutpar(x)                pclr(x , 0x8000)
/* 
 * PROPERTIES OF MAKE_PROC CONSTRUCTION
 */

#define set_struct_res(x)             pset(x , 0x01)
#define has_struct_res(x)             ptst(x , 0x01)

#define set_loc_address(x)            pset(x , 0x02)
#define loc_address(x)                ptst(x , 0x02)

#define set_proc_has_setjmp(x)        pset(x , 0x04)
#define proc_has_setjmp(x)            ptst(x , 0x04)

#define set_proc_has_alloca(x)        pset(x , 0x08)
#define proc_has_alloca(x)            ptst(x , 0x08)

#define set_proc_has_lv(x)            pset(x , 0x10)
#define proc_has_lv(x)                ptst(x , 0x10)


#define setrecursive(x)               pset(x , 0x20)
#define isrecursive(x)                ptst(x , 0x20)

#define set_proc_uses_crt_env(x)      pset(x , 0x40)
#define proc_uses_crt_env(x)          ptst(x , 0x40)

#define set_proc_uses_external(x)     pset(x , 0x80)
#define proc_uses_external(x)         ptst(x , 0x80)

/*
 * PROPERTIES OF SOLVE CONSTRUCT
 */

#define setcrtsolve(x)                props(x) = 0x01
#define set_copying_solve(x)          pset(x , 0x01)
#define clear_copying_solve(x)        pclr(x , 0x01)
#define is_copying_solve(x)           ptst(x , 0x01)

/*
 * PROPERTIES OF MOVE SOME CONSTRUCT 
 */

#define setnooverlap(x)               pset(x , 0x01)
#define isnooverlap(x)                ptst(x , 0x01)

/*
 * PROPERTIES OF CONT CONSTRUCT
 */

#define set_propagate(x)              pset(x , 0x01)
#define clear_propagate(x)		pclr(x , 0x01)
#define to_propagate(x)		ptst(x , 0x01)

/* 
 * PROPERTIES OF LABST CONSTRUCTION
 */

#define set_loaded_lv(x)		pset(x , 0x10)
#define is_loaded_lv(x)		ptst(x , 0x10)
#define setunroll(x) 			pset(x , 0x04)
#define clearunroll(x)  		pclr(x , 0x04)
#define isunroll(x) 			ptst(x , 0x04)


/*
 * PROPERTIES OF NAME CONSTRUCT
 */

#define setlastuse(x)                 pset(x , 0x01)
#define islastuse(x)                  ptst(x , 0x01)

#define setloadparam(x)               pset(x , 0x02)
#define isloadparam(x)                ptst(x , 0x02)

#define setreallyass(x)               pset(x , 0x04)
#define isreallyass(x)                ptst(x , 0x04)

/* 
 * PROPERTIES OF STRING CONSTRUCT
 */

#define string_char_size(x)           props(x)

/*
 * PROPERTIES OF VAL CONSTRUCT
 */

#define setbigval(x)                  pset(x , 0x01)
#define clearbigval(x)                pclr(x , 0x01)
#define isbigval(x)                   ptst(x , 0x01)

#define setconstovf(x)		pset (x, 0x02)
#define constovf(x)			ptst (x, 0x02)

/*
 * PROPERTIES OF REP CONSTRUCT
 */

#define setunrolled(x)                pset(x , 0x01)
#define isunrolled(x)                 ptst(x , 0x01)
#define setinnermost(x)               pset(x , 0x10)
#define isinnermost(x)                ptst(x , 0x10)
#define clearinnermost(x)             pclr(x , 0x10)

/*
 * PROPERTIES OF TEST CONSTRUCT
 */
#define set_use_count_register(x)     pset(x , 0x100)
#define is_use_count_register(x)      ptst(x , 0x100)
#define clear_use_count_register(x)   pclr(x , 0x100)
/*
 * PROPERTIES OF APPLY CONSTRUCT
 */

#define settoinline(x)                pset(x , 0x01)
#define istoinline(x)                 ptst(x , 0x01)
/* 
 * PROPERTIES OF ALLOCA CONSTRUCT
 */
#define set_checkalloc(x) props(x) |= 1;
#define checkalloc(x) (props(x) & 1)


/* 
 * PROPERTIES OF JUMP RECORD
 */
#define fstack_pos_of(x)              props(x)
/* PROPERTIES OF CALLER TAGS */
#define set_coded_caller(x)           pset(x , 0x01)
#define is_coded_caller(x)            ptst(x , 0x01)
#define clear_coded_caller(x)         pclr(x , 0x01)


/* PROPERTIES FOR THINGS WHICH CAN HAVE RECORD BIT SET */
#define setrecordbit(x)               pset(x , 0x8000)
#define clearrecordbit(x)             pclr(x , 0x8000)
#define isrecordbit(x)                ptst(x , 0x8000)

/* 
 * ROUNDING FOR ALIGNMENT
 */

#define rounder(n , a)                (((n) + (a) - 1) / (a)) * (a)

/*
 * USEFUL CONSTANTS
 */

#define align32                         ((unsigned long) 32)
#define align16                         ((unsigned long) 16)
#define align8                          ((unsigned long) 8)
#define align1                          ((unsigned long) 1)

#define size64                          ((long) 64)
#define size32                          ((long) 32)
#define size16                          ((long) 16)
#define size8                           ((long) 8)
#define Z                               (long) 0



/*
 * A few new macros for powertrans
 */
#define is_single_precision(x)        (name(x) == shrealhd)
#define is_double_precision(x)        (name(x) != shrealhd)


#define IS_A_PROC(x)         (name(x)==proc_tag || name(x)==general_proc_tag)
/* These are used in TDF 3.1 for general_env_offset */
#define frame_al_of_ptr(x) (x)->sonf.ald->al.al_val.al_frame
#define frame_al1_of_offset(x) (x)->sonf.ald->al.al_val.al_frame
#define includes_vcallees(x) (((x) & 16) != 0)
#define l_or_cees(x) (((x) &25) !=0)
#define i_reckon_its_a_general_proc(x) (((x)&24)!=0)
/* extra tags needed */
#define locptr_tag 249
#define TEST_LE 1
#define TEST_LT 2
#define TEST_GE 3
#define TEST_GT 4
#define TEST_NE 5
#define TEST_EQ 6

/* extra_expmacs.h */
#define set_callee(id)  setname(son(id), formal_callee_tag)
#define set_make_procprops(e, p) props(e) |= ((p)<<8)
#define proc_has_vcallees(e) ((props(e) & 0x200)!=0)
#define postlude_has_call(e) (props(e) & 1)
#define call_has_vcallees(e) ((props(e) & 2) != 0)
#define proc_has_checkstack(e) ((props(e) & 0x800)!=0)
#define proc_has_vcallers(e) ((props(e) & 0x100) != 0)
#define proc_has_nolongj(e) ((props(e) & 0x1000) !=0)

#define call_is_untidy(e) ((props(e) & 4) != 0)
#define IS_AGGREGATE(s)  (name(s)==nofhd||name(s)==cpdhd||name(s)==s64hd||name(s)==u64hd)

#endif



