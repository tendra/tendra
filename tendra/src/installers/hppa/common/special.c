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
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1996/11/25  13:43:27  wfs
 *    Fixed the comm_op register tracking bug in "oprators.c" and removed a
 * few superfluous "#if 0"s.
 *
 * Revision 1.3  1996/04/18  11:09:17  wfs
 * Fixed a bug in "needscan.c" where "locptr_tag" was being wrapped around
 * the wrong exps.
 *
 * Revision 1.2  1995/12/18  13:12:34  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.1  1995/10/20  14:12:03  wfs
 * gcc compilation changes.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  10:32:18  wfs
 * Register synonyms changed. Minor change to "extj_special_ins"
 * required for tail_call's
 *
 * Revision 3.4  1995/08/25  10:32:18  wfs
 * Register synonyms changed. Minor change to "extj_special_ins"
 * required for tail_call's
 *
 * Revision 3.1  95/04/10  16:28:11  16:28:11  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:18:59  11:18:59  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:28:49  15:28:49  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.2  95/01/17  17:30:49  17:30:49  wfs (William Simmonds)
 * Changed name of an included header file.
 * 
 * Revision 1.1  95/01/11  13:18:45  13:18:45  wfs (William Simmonds)
 * Initial revision
 * 
 */


#define HPPATRANS_CODE
#include "config.h"
#include "common_types.h"
#include "exptypes.h"
#include "expmacs.h"
#include "codetypes.h"
#include "const.h"
#include "installtypes.h"
#include "exp.h"
#include "translat.h"
#include "addrtypes.h"
#include "shapemacs.h"
#include "move.h"
#include "regmacs.h"
#include "getregs.h"
#include "guard.h"
#include "codehere.h"
#include "inst_fmt.h"
#include "hppains.h"
#include "labels.h"
#include "tags.h"
#include "proctypes.h"
#include "bitsmacs.h"
#include "comment.h"
#include "machine.h"
#include "proc.h"
#include "myassert.h"
#include "out.h"
#include "frames.h"
#include "regexps.h"
#include "flags.h"
#include "special.h"

speci
special_fn(exp a1, exp a2, shape s)
{				/* look for special functions */
	speci spr;
	
	/* +++ implement special fns handling */
	spr.is_special = 0;
	spr.special_exp = nilexp;
	
	return spr;
}

/* these are the procs I could do something about */
static int
specno(char * n)
{
	
	/*
	 * specno: >0 special, handle inline in specialmake 0 not special <0
	 * special, rewrite TDF in specialneeds, no call to specialmake
	 */
	
	FULLCOMMENT1("specno(%s)", (long) n);
	
	if (strcmp(n, "___builtin_strcpy") == 0 || strcmp(n, "___TDF_builtin_strcpy") == 0)
		return -1;
	
	if (strcmp(n, "___builtin_asm") == 0 || strcmp(n, "___TDF_builtin_asm") == 0)
		return 4;
	
	if (strcmp(n, "___builtin_alloca") == 0 || strcmp(n, "___TDF_builtin_alloca") == 0)
		return 5;
	
#if 0
	/* +++ use special maybe */
	if (strcmp(n, "strlen") == 0)
		return 2;
	if (strcmp(n, "strcmp") == 0)
		return -3;
#endif
	
	return 0;
}


/* what name to use with call instruction for specials */
char
*special_call_name(int i)
{
	switch (i)
	{
    case -1:
    case 1:
		return ("_strcpy");
		
	case 5:
		return ("_alloca");
		
	default:
		fail("attempting external call to builtin");
		return "";
	}
	/* NOTREACHED */
}



static needs zeroneeds = {0, 0, 0, 0};	/* has no needs */
#if 0
static CONST needs onefixneeds = {1, 0, 0, 0};	/* one fix reg needs */
static CONST needs twofixneeds = {2, 0, 0, 0};	/* two fix reg needs */
#endif


/* these are the needs for their expansion */
needs
specialneeds(int i, exp application, exp pars)
{
	FULLCOMMENT1("specialneeds(%d,...)", i);
	
	switch (i)
	{
/* +++ implement special fuinction handling */
		
	case 4:
	{   return zeroneeds;		/* asm(string) */ }
	
	case 5:
		return zeroneeds;		/* alloca(n) */
		
	default:
		comment1("specialneeds: unimplemented builtin %d", i);
		fail("unimplemented builtin");
		return zeroneeds;
	}
	/* NOTREACHED */
}


/* could I treat this function load specially ? */
int
specialfn(exp fn)
{
	if (name(fn) == name_tag && name(son(fn)) == ident_tag &&
		isglob(son(fn)) && son(son(fn)) == nilexp)
	{
		char *extname = brog(son(fn))->dec_u.dec_val.dec_id;
		
		return specno(extname);
	}
	return 0;
}

/* Is a call to this function reason to prohibit optmisation of caller? */
int
specialopt(exp fn)
{
	if (name(fn) == name_tag && name(son(fn)) == ident_tag &&
		isglob(son(fn)) && son(son(fn)) == nilexp)
	{
		char *extname = brog(son(fn))->dec_u.dec_val.dec_id;
		
		if (extname == 0)
			return 0;
		
		extname += strlen(name_prefix); /* Normalise "_foo" -> "foo" */
		
		FULLCOMMENT1("specialopt: %s", (int)extname);
		
		if ((strcmp(extname, "vfork") == 0) ||
			(strcmp(extname, "setjmp") == 0) ||
			(strcmp(extname, "_setjmp") == 0) ||
			(strcmp(extname, "sigsetjmp") == 0)
			)
		{
			FULLCOMMENT("specialopt: return 1");
			return 1;
		}
	}
	return 0;
}


int
specialmake(int i, exp par, space sp, where dest,
			int exitlab)
{
	switch (i)
	{
	case 4:
    {
		/* asm(s) - simply output s */
		exp e;
		char *s;
		
		/* "par" is (eval_tag (pack_tag (string_tag no=string-table-index))) */
		e = son(son(par));
		if (name(e) != string_tag)
		{
			fail("asm argument not string");
			return 0;
		}
		s = nostr(e);
		
		/* asm is dangerous; as the least precaution, zap register tracking. */
		clear_all();
		fprintf(outf,"!  asm:\n");
		fprintf(outf,s);
		fputc('\n',outf);
		break;
    }
	
	case 5:
    {
		
		/* alloca(n) - grow stack frame by n bytes and then grab 
		 *	  grab n bytes */
		
		int maxargbytes = max_args>>3;
		int dreg;
		ans aa;
		
		dreg = ((discrim(dest.answhere)==inreg) ? regalt(dest.answhere) : getreg(sp.fixed));
		
		if (name(par) == val_tag)
		{
			/* n is a constant */
			int n = no(par);
			
			/* adjust n to be multiple of 64 so stack stays 64 byte aligned */
			n = (n+63) & ~(63);
			
			if (n != 0)
			{
				/* alloca(n) = %sp - maxargbytes */
				if (SIMM14(-maxargbytes))
					ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,-maxargbytes,SP,dreg);
				else
				{
					ir_ins(i_addil,fs_L,empty_ltrl,-maxargbytes,SP);
					ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,-maxargbytes,GR1,dreg);
				}
				/* grow stack frame, i.e. %sp -> %sp + n */             
				if (SIMM14(n))
					ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,n,SP,SP);
				else
				{
					/* grow stack frame by more than 8192 bytes */
					ir_ins(i_addil,fs_L,empty_ltrl,n,SP);
					ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,n,GR1,SP);
				}
			}
		}
		else
		{
			int nreg = reg_operand(par, sp);
			
			/* adjust nreg so that stack stays 64 byte aligned */
			ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,63,nreg,GR1);
			riir_ins(i_dep,c_,0,31,6,GR1);
			
			/* alloca(n) = %sp - maxargbytes */
			if (SIMM14(-maxargbytes))
				ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,-maxargbytes,SP,dreg);
			else
			{
				ir_ins(i_addil,fs_L,empty_ltrl,-maxargbytes,SP);
				ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,-maxargbytes,GR1,dreg);
			}
			/* %sp -> %sp + nreg */
			rrr_ins(i_add,c_,SP,GR1,SP);
		}
		
		setregalt(aa, dreg);
		move(aa, dest, guardreg(dreg, sp).fixed, 0);
		break;
    }
	
	default:
		comment1("specialmake: unimplemented builtin %d", i);
		fail("unimplemented builtin");
		return 0;
	}
	
	return exitlab;		/* for most cases */
}


/*
 *    TDF LIBRARY KEY
 *
 *    A value of 0 means that the library is not present, 1 that it is, and
 *    2 that it should be generated.
 */

int library_key = 0;


/*
 *    SPECIAL ROUTINES
 */

#define sz_millicode_lib 7

static struct {
	CONST char *proc_name;
	bool called;
	bool in_library;
} millicode_lib [ sz_millicode_lib ] =
{
	{ milli_mulU, 0, 1 },	        /* $$mulU    */
	{ milli_mulI, 0, 1 },	        /* $$mulI    */
	{ milli_divU, 0, 1 },	        /* $$mulU    */
	{ milli_divI, 0, 1 },    	/* $$divI    */
	{ milli_remU, 0, 1 },	        /* $$remU    */
	{ milli_remI, 0, 1 },  	/* $$remI    */
	{ milli_dyncall, 0, 1 },	/* $$dyncall */
};


/*
 *    OUTPUT A MILLICODE LIBRARY CALL
 */

void
call_millicode(int n, int r, char *stub, bool restore_linkage_ptr_reg)
{
    CONST char *nm = millicode_lib[n].proc_name;
    millicode_lib[n].called = 1;
    extj_special_ins (nm, r, stub, 0);
    if (PIC_code && restore_linkage_ptr_reg)
		rr_ins(i_copy,GR5,GR19);
    return;
	
}

void
import_millicode()
{
	int n;
	for (n=0; n<sz_millicode_lib; n++)
		if (millicode_lib[n].called)
			fprintf(outf,"\t.IMPORT\t%s,MILLICODE\n",millicode_lib[n].proc_name);
}
