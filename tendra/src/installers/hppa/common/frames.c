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
 *	(1) Its Recipients shall ensure that this Notice is
 *	reproduced upon any copies or amended versions of it;
 *
 *	(2) Any amended version of it shall be clearly marked to
 *	show both the nature of and the organisation responsible
 *	for the relevant amendment or amendments;
 *
 *	(3) Its onward transfer from a recipient to another
 *	party shall be deemed to be that party's acceptance of
 *	these conditions;
 *
 *	(4) DERA gives no warranty or assurance as to its
 *	quality or suitability for any purpose and DERA accepts
 *	no liability whatsoever in relation to any use to which
 *	it may be put.
 *
 * $TenDRA$
 */


/*
 *$Log$
 *Revision 1.2  2002/11/21 22:31:07  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1996/11/14  15:22:13  wfs
 *    Fixed a bug in regexps.c which was common to most of the installers and
 * has only just come to light due to PWE's work on powertrans. (There was
 * previously only a patch.) Cosmetic changes to other files.
 *
 * Revision 1.5  1996/10/24  15:51:14  wfs
 * Added "~alloc_size" special token. Minor change to alloca_tag - only need
 * one word for storage of pointer. Major change to round_tag (rounding to
 * unsigned chars) in the fix of avs bug.
 *
 * Revision 1.4  1996/09/06  10:38:19  wfs
 * bug fixes to "offset.pl" and cosmetic changes to the dynamic initialization
 * code.
 *
 * Revision 1.3  1996/09/05  11:05:08  wfs
 * "dynamic_init" boolean variable removed - must always be considered true.
 *
 * Revision 1.2  1995/12/18  13:11:19  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.5  1995/10/11  15:52:57  wfs
 * "Has_no_vcallers" was defined incorrectly.
 *
 * Revision 5.4  1995/10/09  13:04:27  wfs
 * Cosmetic changes.
 *
 * Revision 5.3  1995/09/15  14:47:07  wfs
 * Removed "#include "extra_expmacs.h"".
 *
 * Revision 5.2  1995/09/15  12:20:09  wfs
 * "extra_expmacs.h" included + minor variable name changes and
 * initializations.
 *
 * Revision 5.1  1995/09/07  15:41:49  wfs
 * Removed "extra_expmacs.h" include.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  09:20:13  wfs
 * All the stuff (formerly in "proc.c") which set up the variables
 * for stack frames has been moved to frames.c. Substantial comments
 * have been added.
 *
 * Revision 3.4  1995/08/25  09:20:13  wfs
 * All the stuff (formerly in "proc.c") which set up the variables
 * for stack frames has been moved to frames.c. Substantial comments
 * have been added.
 *
 * Revision 3.1  95/04/10  16:26:26  16:26:26  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:17:06  11:17:06  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:26:53  15:26:53  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.1  95/01/11  13:06:47  13:06:47  wfs (William Simmonds)
 * Initial revision
 *
 */


#include "config.h"
#include "bitsmacs.h"
#include "common_types.h"
#include "expmacs.h"
#include "procrec.h"
#include "tags.h"
#include "addrtypes.h"
#include "hppains.h"
#include "regmacs.h"
#include "flags.h"
#include "frames.h"

extern char *proc_name;
extern int bitsin(long);
extern exp father(exp);
extern int diagnose;
extern int gdb;

bool Has_fp = 0;
bool Has_vsp = 0;
bool Has_tos = 0;
bool No_S = 0;
bool Has_ll = 0;
bool Has_checkalloc = 0;
bool Has_callees = 0;
bool Has_vcallees = 0;
bool Has_no_vcallers = 0;
bool Uses_crt_env = 0;
bool is_PIC_and_calls = 0;
bool plusZ;
int fixdump = 0;
long callee_sz;
long callees_offset;
long locals_offset;
long max_args;
long params_offset;
long locals_space;
long frame_sz;
long stackerr_lab;
long aritherr_lab;

baseoff MEM_TEMP_BOFF;
baseoff LONG_RESULT_BOFF;
baseoff SP_BOFF;
baseoff FP_BOFF;

/*
 *	The purpose of this file (the 5th revision) is to collect together
 *     all the code which maintains the stack frame. Below is an illustration
 *     of the >>most general<< stack frame.
 *
 *
 *
 *	|                                       |
 *	|---------------------------------------|<--SP
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|         8 word "frame marker"         |
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|---------------------------------------|
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|        4 word "parameter dump"        |
 *	|                                       |
 *	|                                       |
 *	|                                       |
 *	|---------------------------------------|
 *	|                                       |
 *	:                                       :
 *	:          remaining arguments          :
 *	:                                       :
 *	|                                       |
 *	|---------------------------------------|
 *	|                                       |
 *	:                                       :
 *	:      dynamically allocated space      :
 *	:                                       :
 *	|                                       |
 *	|---------------------------------------|
 *	|                                       |
 *	|       2 words of temporary mem        |
 *	|                                       |
 *	|---------------------------------------|
 *	|                                       |
 *	|       2 words for long result         |
 *	|                                       |
 *	|---------------------------------------|
 *	|     1 word to keep track of SP        |
 *	|---------------------------------------|
 *	|                                       |
 *	:                                       :
 *	:                                       :
 *	:                                       :
 *	:            locals space               :
 *	:                                       :
 *	:                                       :
 *	:                                       :
 *	|                                       |
 *	|---------------------------------------|
 *	|                                       |
 *	:                                       :
 *	:                                       :
 *	:                                       :
 *	:            callees space              :
 *	:                                       :
 *	:                                       :
 *	:                                       :
 *	|                                       |
 *	|---------------------------------------|
 *	|        2 words for callee_sz          |
 *	|---------------------------------------|
 *	|                                       |
 *	:                                       :
 *	:  s reg save space (16 words maximum)  :
 *	:                                       :
 *	|                                       |
 *	|---------------------------------------|<--FP (=OLD SP)
 *	|                                       |
 *
 *
 *
 *
 *	   EP ("enviroment" pointer) is a copy of the SP before (if ever) SP
 *	is incremented to create dynamically allocated space.
 *	   The locals, the temporary memory, the long result words, and the
 *	stack copies of SP and FP (both reset at possible long jump
 *	targets) are all offset relative to EP. If Has_fp==0, then the
 *	parameters and the callees are also offset relative to EP,
 *	otherwise they are offset relative to FP. The callee_sz is stored
 *	on the stack only when Has_vcallees==1, and therefore Has_fp==1,
 *	and is offset relative to FP.
 
*/


void
setframe_flags(exp e, bool leaf)
{
	/* e is a proc_tag */
	unsigned char ne = name(e);
	Uses_crt_env = proc_uses_crt_env(e);
	No_S = (!leaf && Uses_crt_env && proc_has_lv(e)
			&& (ne!=general_proc_tag || !proc_has_nolongj(e)));
	Has_ll = procrecs[no(e)].Has_ll;
	Has_checkalloc = procrecs[no(e)].Has_checkalloc;
	Has_vsp = (proc_has_alloca(e) || No_S || ne==general_proc_tag );
	Has_tos = (No_S && proc_has_alloca(e));
	Has_callees = (ne==general_proc_tag);
	Has_vcallees = (ne==general_proc_tag && proc_has_vcallees(e));
	Has_no_vcallers = (ne==proc_tag || !proc_has_vcallers(e));
	Has_fp = (Has_vcallees || gdb);
	/*  n.b. gdb, apparently, tracks all locals and parameters via +ve
	 *       offsets relative to a frame pointer = %r3. We comply by putting
	 *       Has_fp=1  */
	is_PIC_and_calls = (PIC_code && !leaf);
	
#ifdef Try_No_S
	No_S = 1;
#endif
#ifdef Try_Has_fp
	Has_fp = !leaf;
#endif
#ifdef Try_Has_tos
	Has_tos = 1;
#endif
}


void
set_up_frame(exp e)
{
    procrec * pr = & procrecs[no(e)];
    needs * ndpr = & pr->needsproc;
    spacereq *sppr = & pr->spacereqproc;
    long pprops = (ndpr->propsneeds);
    bool leaf = (pprops & anyproccall) == 0;
    long ma = ndpr->maxargs;   /* maxargs of proc body in bits  */
    long st = sppr->stack;    /*  space for locals in bits     */
    bool simpleans = (pprops & long_result_bit) == 0;
    int cs = pr->callee_sz;
	
    setframe_flags(e,leaf);
	
    if (No_S)
    {
		fixdump = -65536; /* dump all sregs */
    }
    else
    {
		fixdump = sppr->fixdump;
    }
    if (Has_fp) /* Has frame pointer */
    {
		/* reserved GR3 for use as frame pointer...     */
		fixdump|=(1<<FP) ; /* ...dump and restore FP  */
    }
    if (Has_vsp) /* Has variable stack pointer */
    {
		/* reserved GR4 for use as "enviroment pointer"...   */
		EP = GR4;
		fixdump|=(1<<EP) ; /* ...dump and restore EP    */
    }
    else
    {
		EP = SP;
    }
    if (is_PIC_and_calls)
    {
		/* reserved GR5 as a copy of GR19...             */
		fixdump|=(1<<GR5) ; /* ...dump and restore GR5  */
    }
	
    st+=(2<<5);       /* 2 words of temporary memory */
    if (!simpleans)  /*  + 2 words in which to store address of long result */
    {
		st+=(2<<5);
    }
    if (Has_tos)
    {
		st+=(1<<5);  /*  + 1 word in which to store SP (reset at possible  */
    }              /*   long jump targets)                               */
	
    /*   HP PA reserved stack area. c.f. p 3-13 of HP PA reference manual */
    if (!leaf)
    {
		if (ma<(4<<5))
			ma = (4<<5);	 /* 4 words for parameter dump */
		ma+=(8<<5);  	/*  + 8 word frame marker     */
    }
	
    /* keep maxargs a multiple of 2 words to ease possible alloca inlining */
    ma = (ma+63) & ~63;
    /* keep st a multiple of 2 words */
    st = (st + 63) & ~63;
	
    pr->locals_offset = ma + st;  /* relative to EP */
	
    /*  Budget for sreg save area  */
    if (Has_callees)
    {
		st+=(18<<5); /* 2 words to keep a record of callee sz (2 words      */
		/*  are allocated to guarentee the callees are double  */
		/*   word aligned) + (maximum) 16 word register save   */
		/*    area (because callers must know where to put     */
		/*     callees).                                       */
    }
    else
    {
		/* Can we be more economical? */
		int nos;
		if (No_S)
		{
			nos = 16;
		}
		else
		{
			nos = bitsin(fixdump); /* = number of s regs used in body of proc */
		}
		st+=(nos<<5);
    }
	
    if (!Has_vcallees)
    {
		/* adjust st so that ma + st + cs is a multiple of 16 words
		 * according to convention */
		st = ((ma+st+cs+511) & (~511)) - ma -cs;
    }
	
    pr->locals_space = st;
    pr->frame_sz = ma + st + cs;
    if (Has_vcallees)
    {
		/* relative to FP */
		pr->params_offset = (8<<5);
		pr->callees_offset = -(18<<5);
    }
    else
    {
		/* relative to EP */
		pr->params_offset = pr->frame_sz + (8<<5);
		pr->callees_offset = pr->frame_sz - (18<<5);
    }
    pr->leaf = leaf;
    pr->max_args = ma;
	
    MEM_TEMP_BOFF.base = EP; MEM_TEMP_BOFF.offset = -(ma>>3)-(2<<2);
    LONG_RESULT_BOFF.base = EP; LONG_RESULT_BOFF.offset = -(ma>>3)-(4<<2);
    SP_BOFF.base = EP; SP_BOFF.offset = -(ma>>3)-(simpleans ? (3<<2) : (5<<2));
    FP_BOFF.base = EP; FP_BOFF.offset = -4;
	
    stackerr_lab=0;
    aritherr_lab=0;
}


long
frame_offset(exp e)
{
	exp p;
	procrec *pr;
	int eo,lo,po,co;
	for (p = father(e); (name(p)!=proc_tag && name(p)!=general_proc_tag);                              p = father(p));
	pr = &procrecs[no(p)];
	lo = pr->locals_offset>>3;
	po = pr->params_offset>>3;
	co = pr->callees_offset>>3;
	if (isparam(e))
	{
		int nse = no(son(e));
		if (name(son(e))==formal_callee_tag)
		{
			eo = -co+(nse>>3);
		}
		else
		{
			eo = -po-(nse>>3);
		}
	}
	else
	{
		int  n = no(e);
		int  b = n & 0x3f;
		eo = -lo+((n-b)>>4);
	}
	return eo;
}






