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
 *Revision 1.2  2002/11/21 22:31:09  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.13  1996/07/16  15:59:47  currie
 * alloca alignment
 *
 *Revision 1.12  1996/06/17 12:38:31  currie
 *Bitsfield in eval
 *
 *Revision 1.11  1996/06/13 09:20:37  currie
 *Bitf compound starting at non-0 offset
 *
 *Revision 1.10  1996/06/04 15:42:05  currie
 *include general_proc_tag in make_compound

 * Revision 1.9  1996/01/09  12:00:36  currie
 * var callee par in reg
 *
 * Revision 1.8  1995/12/08  11:20:04  currie
 * Constant offsets + allocaerr_lab
 *
 * Revision 1.7  1995/10/25  13:48:19  currie
 * change to position of .glob
 *
 * Revision 1.6  1995/09/12  10:59:18  currie
 * gcc pedanttry
 *
 * Revision 1.5  1995/08/16  16:06:35  currie
 * Shortened some .h names
 *
 * Revision 1.4  1995/08/15  09:19:14  currie
 * Dynamic callees + trap_tag
 *
 * Revision 1.3  1995/08/09  10:53:36  currie
 * apply_general bug
 *
 * Revision 1.2  1995/06/28  12:15:19  currie
 * New make_stack_limit etc
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
 ***********************************************************************/
/*****************************************************************
 *		eval.c
 *
 *	The main procedure defined here is evaluated which ouputs
 *assembler for data. The parameters are an evaluated exp and an index
 *into the table of externals (or 0 meaning anonymous). XXX
 *****************************************************************/

#include "config.h"
#include "common_types.h"
#include "addrtypes.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"
#include "exptypes.h"
#include "maxminmacs.h"
#include "shapemacs.h"
#include "flpttypes.h"
#include "flpt.h"
#include "syms.h"
#include "out_ba.h"
#include "main.h"
#include "ibinasm.h"
#include "frames.h"
#include "procrectypes.h"
#include "f64.h"
#include "eval.h"
#include "basicread.h"

extern void globalise_name(dec*);
extern  procrec * procrecs;

long  G_number = 64;		/* to give choice of .sdata or data */

int   data_lab = 33;

int
next_data_lab()
{	/*  anonymous label in data space - $$n in assember o/p */
	return data_lab++;
}

int
next_dlab_sym()
{	/* as above - but also gives it a symno for .G output */
	symnofordata (data_lab);
	return data_lab++;
}


/* various pieces of info for outputting data depending on shape */
mm scmm = {
	127, -128, "\t.byte %ld :%ld\n"
};
mm uscmm = {
	255, 0, "\t.byte %ld :%ld\n"
};
mm shmm = {
	0x7fff, 0xffff8000, "\t.half %ld :%ld\n"
};
mm ushmm = {
	0xffff, 0, "\t.half %ld :%ld\n"
};
mm swmm = {
	0x7fffffff, 0x80000000, "\t.word %ld :%ld\n"
};
mm uswmm = {
	0xffffffff, 0, "\t.word %ld :%ld\n"
};

/*************************************************************
 *maxmin
 *
 *finds the data size from the range of an integer shape
 **************************************************************/
mm
maxmin(shape s)
{
	switch (name (s)) {
    case scharhd:
		return scmm;
    case ucharhd:
		return uscmm;
    case swordhd:
		return shmm;
    case uwordhd:
		return ushmm;
    case slonghd:
		return swmm;
    case ulonghd:
		return uswmm;
    default: {
		
		return uswmm;
	}
	}
	
}


/**************************************************************
 *outlab
 *
 *outputs the label parameter if non negative else interprets it
 *to be an index into the externals and outputs the identifier.
 **************************************************************/

void
outlab(int l)
{
	if (l >= 0) {
		fprintf (as_file, "$$%d", l);
	}
	else {
		char *extname = main_globals[-l - 1] -> dec_u.dec_val.dec_id;
		fprintf (as_file, "%s", extname);
	}
}





/***************************************************************
 *evalone
 *
 *This procedure outputs all non-pack expressions and puts in label
 *values for the pack exps (putting new label numbers into their number
 *fields) which it accumulates for later application in the ptr parameter
 *of evalone. This is done to cope with the fact that the exp to evaluated
 *may contain pack operations which are graph-like .
 ***************************************************************/
long
evalexp(exp e)
{
	switch (name(e)) {
    case  val_tag: case null_tag: case top_tag:{
		if (name(sh(e)) == offsethd && al2(sh(e)) >= 8) {
			return (no(e)>>3);
		}
        return (no (e));
    }
    case bitf_to_int_tag:
	{
		return evalexp (son (e));
	}
    case int_to_bitf_tag:
	{
		ash a;
		long  w = evalexp (son (e));
		a = ashof (sh (e));
		if (a.ashalign != 1) {
			failer ("should be align 1");
		}
		if (a.ashsize != 32) {
			w &= ((1 << a.ashsize) - 1);
		}
		return w;
	}
    case not_tag:
	{
		return (~evalexp (son (e)));
	}
    case and_tag:
	{
		return (evalexp (son (e)) & evalexp (bro (son (e))));
	}
    case or_tag:
	{
		return (evalexp (son (e)) | evalexp (bro (son (e))));
	}
    case xor_tag:
	{
		return (evalexp (son (e)) ^ evalexp (bro (son (e))));
	}
	
    case shr_tag:
	{
		return (evalexp (son (e)) >> evalexp (bro (son (e))));
	}
	
    case shl_tag:
	{
		return (evalexp (son (e)) << evalexp (bro (son (e))));
	}
	
    case concatnof_tag:
	{
		ash a;
		long  wd = evalexp (son (e));
		a = ashof (sh (son (e)));
		return (wd | (evalexp (bro (son (e))) << a.ashsize));
	}
	
    case clear_tag:
	{
		ash a;
		a = ashof (sh (e));
		if (a.ashsize > 32)
			failer ("clearshape");
		return 0;
	}
	case env_offset_tag:
	case general_env_offset_tag: {
		return frame_offset(son(e));
	}
	case env_size_tag: {
		exp tg = son(son(e));
		procrec * pr = &procrecs[no(son(tg))];
		return ((pr->frame_size+pr->callee_size) >> 3);
	}
	case offset_add_tag:{
    	return (evalexp(son(e))+evalexp(bro(son(e))));
	}
	case offset_max_tag:{
    	return (max(evalexp(son(e)),evalexp(bro(son(e)))));
	}
	case offset_pad_tag:{
		return (rounder(evalexp(son(e)), shape_align(sh(e))));
	}
	case offset_mult_tag:{
    	return (evalexp(son(e))*evalexp(bro(son(e))));
	}
	case offset_div_tag:case offset_div_by_int_tag:{
    	return (evalexp(son(e))/evalexp(bro(son(e))));
	}
	case offset_subtract_tag:{
    	return (evalexp(son(e))-evalexp(bro(son(e))));
	}
	case offset_negate_tag: {
		return (- evalexp(son(e)));
	}
    default:
		failer ("tag not in evalexp");
	}
	return 0;
}

void
set_align(int al)
{
	if (al<16) return;
	if (as_file)
		fprintf (as_file, "\t.align%s\n",
				 (al == 16) ? " 1" :
				 ((al == 32) ? " 2" :
				  ((al == 64) ? " 3" : " 0")));
	out_value (0, ialign, (al == 16) ? 1 :
			   ((al == 32) ? 2 :
				((al == 64) ? 3 : 0)), 0);
	
}

int
eval_al(shape s)
{
	if (shape_align(s)!=1) return shape_align(s);
	if (shape_size(s) <=8) return 8;
	if (shape_size(s) <=16) return 16;
	return 32;
}

void
oneval(int val, int al, int rep)
{
	char *as = (al <= 8) ? "\t.byte %ld :%ld\n"
		:     ((al <= 16) ? "\t.half %ld :%ld\n"
			   :     "\t.word %ld :%ld\n");
	set_align(al);
	if (as_file)
		fprintf (as_file, as, val, rep);
	out_value (0, (al <= 8) ? ibyte : ((al <= 16) ? ihalf : iword), val, rep);
}



void
evalone(exp e, long rep)
{
	/* outputs constant expression e, rep
	 *				   times;  */
	ash a;
	a = ashof (sh (e));
	switch (name (e)) {
		
    case string_tag:
	{
        long char_size = props(e);
		long  strsize = shape_size(sh(e))/char_size;
		char *st = nostr(e);
		long  strs = shape_size(sh(e))>>3;
		int   i,j;
		if (rep != 1 && as_file)
			fprintf (as_file, "\t.repeat %ld\n", rep);
		set_align(char_size);
		if (as_file) {
			for (j=0; j< strsize;) {
				switch (char_size) {
				case 8: fprintf (as_file, "\t.byte "); break;
				case 16: fprintf (as_file, "\t.half "); break;
				case 32: fprintf (as_file, "\t.word "); break;
				}
				for (i = j; i < strsize && i-j < 8; i++) {
					switch (char_size) {
					case 8:fprintf (as_file, "0x%x ", st[i]); break;
					case 16:fprintf (as_file, "0x%x ", ((short *)st)[i]); break;
					case 32:fprintf (as_file, "0x%lx ", ((long *)st)[i]); break;
					}
				}
				j =i;
				fprintf (as_file, "\n");
			}
		}
		if (rep != 1 && as_file)
			fprintf (as_file, "\t.endr\n");
		out_chars (0, iascii, strs, rep);
		out_data (st, strs);
		return;
	}
    case real_tag:
	{
		r2l   n;
		int i;
		n = real2longs_IEEE(&flptnos[no (e)], (a.ashsize>32)?1:0);
		set_align(a.ashalign);
		for (i=0; i<rep; i++) {
			if (BIGEND) {
				if (a.ashsize>32)  oneval(n.i2, 32, 1);
				oneval(n.i1, 32, 1);
			}
			else {
				oneval(n.i1, 32, 1);
          		if (a.ashsize>32) oneval(n.i2, 32, 1);
			}
        }
		return;
	}
    case null_tag: case top_tag:
		no (e) = 0;
    case val_tag:
	{
		if (shape_size(sh(e)) > 32) {
			flt64 temp;
			int ov;
			int i;
			if (isbigval(e)) {
				temp = flt_to_f64(no(e), 0, &ov);
			}
			else {
				temp.big = (is_signed(sh(e)) && no(e)<0)?-1:0;
				temp.small = no(e);
			}
			for (i=0; i<rep; i++) {
				oneval(temp.small, 32, 1);
				oneval(temp.big, 32, 1);
			}
			return;
		}
		
		oneval(evalexp(e), eval_al(sh(e)), rep);
		return;
	}
	
    case name_tag:
	{
		exp dc = son(e);
		dec * globdec= brog(dc);/* must be global name */
		char *nm = globdec -> dec_u.dec_val.dec_id;
		long symdef = globdec ->dec_u.dec_val.sym_number;
		if (!isvar(dc) && son(dc) != nilexp
			&& name(son(dc)) != proc_tag && name(son(dc)) != general_proc_tag
			&& no(e)==0
			&& shape_size(sh(e)) == shape_size(sh(son(dc))) ) {
			evalone(son(dc), rep);
			return;
		}
		set_align(32);
		if (as_file) {
			if (no (e) == 0) {
				fprintf (as_file, "\t.word %s : %ld\n", nm, rep);
			}
			else {
				fprintf (as_file, "\t.word %s + %d :%ld\n", nm, no (e) / 8, rep);
			}
		}
		out_value (symnos[symdef], iword, no (e) / 8, rep);
		return;
	}
    case compound_tag:  {
		exp tup = son (e);
		unsigned long val;
		bool first_bits=1;
		long bits_start =0;
		long offs =0;
		
		if (rep != 1)
			failer ("CAN'T REP TUPLES");
		set_align(a.ashalign);
		
		
		for (;;) {
			ash ae;
			ae = ashof(sh(bro(tup)));
			offs = no(tup);
			if (ae.ashalign == 1) {
				unsigned long vb = evalexp(bro(tup));
				if (ae.ashsize != 32) {
					vb = vb & ((1<<ae.ashsize)-1);
				}
                if (first_bits) {
					val = 0;
					first_bits=0;
                }
				
                if (offs - bits_start +ae.ashsize > 32) {
					if (BIGEND) {
						for (;;) {
							oneval(val>>24, 8, 1);
							val <<=8;
							bits_start+=8;
							if (offs-bits_start < 8) break;
						}
					}
					else {
						for (;;) {
							oneval(val &255, 8,1);
							val >>= 8;
							bits_start += 8;
							if (offs - bits_start  < 8)
								break;
						}
					}
                }
				
                if (offs - bits_start +ae.ashsize <= 32) {
					if (BIGEND) {
						val |= (vb << (32 -offs+bits_start-ae.ashsize));
					}
					else {
                     	val |= (vb <<(offs-bits_start));
					}
                }
                else {
					failer("Constant bitfield does not fit into 32 bits");
                }
			}
			else {
				if (!first_bits) {
					first_bits=1;
					if (BIGEND) {
						for (;;) {
							oneval(val>>24, 8, 1);
							val <<=8;
							bits_start+=8;
							if (offs-bits_start <= 0) break;
						}
					}
					else {
						for (;;) {
							oneval(val &255, 8,1);
							val >>=8;
							bits_start += 8;
							if (offs - bits_start  <=0)
								break;
						}
					}
				}
				while (bits_start < offs) {
					oneval(0, 0, 1);
					bits_start+=8;
				}
				evalone(bro(tup),1);
				bits_start += shape_size(sh(bro(tup)));
			}
			
			if (last(bro(tup))) {
				offs += ae.ashsize;
				offs = (offs+7)&~7;
				for (;!first_bits;) {
					if (BIGEND) {
						oneval(val>>24, 8, 1);
						val <<=8;
						bits_start+=8;
						if (offs-bits_start<= 0) break;
					}
					else {
						oneval(val &255, 8,1);
						val >>= 8;
						bits_start +=8;
						if (offs - bits_start <=0)
							break;
					}
				}
				Assert(a.ashsize >= offs);
				while (a.ashsize > offs) { /* pad out unions etc */
					oneval(0,8,1);
					offs+=8;
				}
				return;
			}
			tup = bro(bro(tup));
		}
		
	}
		
	case nof_tag: {
		exp s = son(e);
		if (s==nilexp) return;
		if (rep != 1)
			failer ("CAN'T REP TUPLES");
		set_align(a.ashalign);
		for (;;) {
			evalone(s,1);
			if (last(s)) return;
			s = bro(s);
		}
	}
		
		
    case ncopies_tag:
	{
        if (name(son(e)) == compound_tag || name(son(e)) == concatnof_tag ||
			name(son(e)) == nof_tag) {
			int n;
			for (n = rep*no(e); n > 0; n--) {
             	evalone(son(e), 1);
			}
        }
		else evalone (son (e), rep * no (e));
		return;
	}
	
    case concatnof_tag:
	{
		if (a.ashalign == 1) {
			long  ee = evalexp (e);
			exp dad = father(e);
			ash abits;
			abits = ashof(sh(dad));
			oneval(ee, abits.ashalign, rep);
		}
		else {
			if (rep != 1)
				failer ("CAN'T REP concat");
			evalone (son (e), 1);
			evalone (bro (son (e)), 1);
		}
		return;
	}
	
    case clear_tag:
	{
		int s = eval_al(sh(e));
		if (as_file)
			fprintf (as_file, "\t.space %ld\n", (s>>3) * rep);
		out_value (0, ispace, (s>>3) * rep, 1);
		return;
	}
	
	
	
    case not_tag:
    case and_tag:
    case or_tag:
    case shl_tag:
    case shr_tag:
    case bitf_to_int_tag:
    case int_to_bitf_tag:
    case env_offset_tag:
    case general_env_offset_tag:
	case env_size_tag: case offset_add_tag: case offset_max_tag:
	case offset_pad_tag: case offset_mult_tag: case offset_div_tag:
	case offset_div_by_int_tag: case offset_subtract_tag: case offset_negate_tag:
	{
		long  ee = evalexp (e);
		oneval(ee, eval_al(sh(e)) , rep);
		return;
	}
	case seq_tag:
	{
		if (name(son(son(e))) == prof_tag && last(son(son(e))))
		{ evalone(bro(son(e)),rep); return;}
	}		/* otherwise drop through to failure */
	
	
    default:
		failer ("tag not in evaluated");
		
	}				/* end switch */
}


/*****************************************************************
 *evaluated
 *
 *This outputs data from the evaluated exp into either .sdata or .data
 *depending on size and labels this data either with either id in main_globals
 *or an anonymous label derived from l. The result is the instore "address"
 *of the constant. A negative l implies that this is the initialisation of a global
 *variable.

*****************************************************************/

instore
evaluated(exp e, long l, dec * dc)
{
	
	int   lab = (l == 0) ? next_dlab_sym ()
		: (l< 0)? l: -l;
	int   lab0 = lab;
	ash a;
	instore isa;
	exp z = e;
	
	isa.adval = 0;
	isa.b.offset = 0;
	isa.b.base = lab0;
	
	
	if (name (e) == clear_tag) {/* uninitialised global */
		int   size = (ashof (sh (e)).ashsize + 7) >> 3;
		bool temp = (l == 0 ||
					 (main_globals[-lab - 1] -> dec_u.dec_val.dec_id)[0] == '$');
		if (dc != (dec*)0) globalise_name(dc);
		if (as_file) {
			fprintf (as_file, (temp) ? "\t.lcomm\t" : "\t.comm\t");
			outlab (lab);
			fprintf (as_file, " %d\n", size);
		}
		out_value ((lab >= 0) ? tempsnos[lab - 32] : symnos[-lab - 1],
				   (temp) ? ilcomm : icomm, size, 1);
		
		return isa;
	}
	
	
    a = ashof (sh (z));
    if (a.ashsize <= G_number) {
		if (as_file)
			fprintf (as_file, "\t.sdata\n");
		out_common (0, isdata);
    }
    else {
		if (as_file)
			fprintf (as_file, "\t.data\n");
		out_common (0, idata);
    }
    set_align(a.ashalign);   /* I think this is unnecessary ? bug in as */
    if (dc != (dec*)0) globalise_name(dc);
    if (as_file) {
		outlab (lab);
		fprintf (as_file, ":\n");
    }
    out_common ((lab > 0) ? tempsnos[lab - 32] : symnos[-lab - 1], ilabel);
    evalone (z, 1);
	
	return isa;
}
