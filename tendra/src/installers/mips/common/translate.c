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
 *Revision 1.2  2002/11/21 22:31:10  nonce
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
 * Revision 1.2  1998/02/04  10:43:45  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:56:07  release
 * First version to be checked into rolling release.
 *
 * Revision 1.11  1996/04/24  08:55:54  currie
 * Case may require 3 regs
 *
 * Revision 1.10  1996/01/17  11:27:11  currie
 * proc with no diagnostics
 *
 * Revision 1.9  1996/01/12  10:06:14  currie
 * AVS - env_offset + main declared but not d3efined
 *
 * Revision 1.8  1995/10/25  13:48:29  currie
 * change to position of .glob
 *
 * Revision 1.7  1995/10/02  10:30:35  currie
 * env_offset + -g (PIC)
 *
 * Revision 1.6  1995/09/20  14:23:10  currie
 * callee-list blunder + fix for silliness in ultrix assembler
 *
 * Revision 1.4  1995/09/12  10:59:45  currie
 * gcc pedanttry
 *
 * Revision 1.3  1995/08/16  16:07:14  currie
 * Shortened some .h names
 *
 * Revision 1.2  1995/06/28  12:15:26  currie
 * New make_stack_limit etc
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
 ***********************************************************************/
#include "config.h"
#include "cross_config.h"

#ifndef CROSS_INCLUDE
#include <symconst.h>
#else
#include CROSS_INCLUDE/symconst.h>
#endif

#include "common_types.h"
#include "symtab.h"
#include "installglob.h"
#include "tags.h"
#include "exp.h"
#include "expmacs.h"
#include "optimise.h"
#include "flags.h"
#include "shapemacs.h"
#include "tempdecs.h"
#include "weights.h"
#include "procrectypes.h"
#include "regalloc.h"
#include "new_code.h"
#include "code_here.h"
#include "eval.h"
#include "bitsmacs.h"
#include "needs_scan.h"
#include "ibinasm.h"
#include "syms.h"
#include "out_ba.h"
#include "xalloc.h"
#include "new_symbol.h"
#include "mipsdiags.h"
#include "extern_adds.h"
#include "mips_ins.h"
#include "machine.h"
#include "main.h"
#include "frames.h"
#include "basicread.h"
#include "getregs.h"
#include "locate.h"
#include "me_fns.h"

extern long aritherr_lab;
extern long stackerr_lab;


extern exp find_named_tg(char*, shape);
extern shape f_top;
extern shape f_proc;

procrec * procrecs;
dec ** main_globals;
int main_globals_index;

extern long fscopefile;
extern bool do_extern_adds;

ash
ashof(shape s)
{
	ash a;
	a.ashsize = shape_size(s);
	a.ashalign = shape_align(s);
	return a;
}


bool
not_reserved(char *id)
{
	/* various identifier reserved by MIPS */
	if (!strcmp (id, "edata"))
		return (0);
	if (!strcmp (id, "etext"))
		return (0);
	if (!strcmp (id, "end"))
		return (0);
	if (!strcmp (id, "_ftext"))
		return (0);
	if (!strcmp (id, "_fdata"))
		return (0);
	if (!strcmp (id, "_fbss"))
		return (0);
	if (!strcmp (id, "_gp"))
		return (0);
	if (!strcmp (id, "_procedure_table"))
		return (0);
	if (!strcmp (id, "_procedure_string_table"))
		return (0);
	return (1);
}





char
varsize(shape sha)
{
	return (name(sha)==nofhd);
}

int current_symno;

void
globalise_name(dec * my_def)
{
	char *id = my_def -> dec_u.dec_val.dec_id;
	if (!my_def -> dec_u.dec_val.extnamed) return;
	if (as_file)
		fprintf (as_file, "\t.globl\t%s\n", id);
	out_common (symnos[my_def->dec_u.dec_val.sym_number], iglobal);
	
}

void
code_it(dec * my_def)
{
	exp tg = my_def -> dec_u.dec_val.dec_exp;
	char *id = my_def -> dec_u.dec_val.dec_id;
	long symdef = my_def ->dec_u.dec_val.sym_number;
	bool extnamed =  my_def -> dec_u.dec_val.extnamed;
	
	static  space tempspace = {
		0, 0
    };
	if (symnos[symdef] <0) goto end; /* ? unused symbols */
	
	if (son (tg) != nilexp && (!extnamed || !is_comm(son(tg)))) {
		if (name (son (tg)) == proc_tag
			|| name(son(tg)) == general_proc_tag) {
			diag_descriptor * dd =  my_def -> dec_u.dec_val.diag_info;
			/* compile code for proc */
			if (as_file) {
				fprintf (as_file,"\t.text\n\t.align 3\n");
			}
			
			
			out_common (0, itext);
			out_value (0, ialign, 3, 0);
			if (diagnose) {
				if (dd != (diag_descriptor*)0) {
					sourcemark *sm = &dd -> data.id.whence;
					stabd(fscopefile = find_file(sm->file->file.ints.chars),
						  sm->line_no.nat_val.small_nat);
				}
				else { stabd(0,1); /*no diagnostics for this proc */ }
			}
			
			globalise_name(my_def);
			
			if (as_file) fprintf(as_file, "\t.ent\t%s\n%s:\n", id, id);
			
			out_ent (current_symno = symnos[symdef], ient, 2);/* why 2? */
			out_common (symnos[symdef], ilabel);
			if (as_file) {
				fprintf (as_file,
						 (diagnose) ? "\t.option O1\n" : "\t.option O2\n");
			}
			
			out_option (1, (diagnose) ? 1 : 2);
			
			symnoforstart (symdef, currentfile);
			settempregs (son(tg));
			code_here (son (tg), tempspace, nowhere);
			if (diagnose && dd != (diag_descriptor*)0) {
				stabd(fscopefile, currentlno+1);
			}
			if (as_file)
				fprintf (as_file, "\t.end\t%s\n", id);
			out_common (symnoforend (my_def, currentfile), iend);
		}
		else {			/* global values */
			
			exp c = son (tg);
			IGNORE evaluated (c, (isvar (tg)) ? (-symdef - 1) : symdef + 1, my_def);
			
			
		};
	}
	else {	/* global declarations but no definitions or is_comm */
		long  size;
		shape s = (son(tg)==nilexp)?my_def -> dec_u.dec_val.dec_shape :
			sh(son(tg));
		size = (shape_size(s) + 7) >> 3;
		
		if ((isvar(tg) || name(s) != prokhd) && not_reserved (id)) {
			if ((son(tg) != nilexp && is_comm(son(tg)))
				|| (son(tg)==nilexp && varsize(sh(tg)))) {
				if (size !=0) { /* ? ? ! ? */
					globalise_name(my_def);
					if (as_file)
						fprintf (as_file, "\t.comm\t%s %ld\n", id, size);
					out_value (symnos[symdef], icomm, size, 1);
				}
			}
			else {
				if (as_file)
					fprintf (as_file, "\t.extern\t%s %ld\n", id,
							 size);
				out_value (symnos[symdef], iextern, size, 1);
			}
		}
		else
			if (son (tg) == nilexp && !extnamed) {
				if (size !=0) { /* ? ? ! ? */
					if (as_file)
						fprintf (as_file, "\t.lcomm\t%s %ld\n", id, size);
					out_value (symnos[symdef], ilcomm, size, 1);
				}
			}
		
	}
	
	
  end:
	my_def -> dec_u.dec_val.processed = 1;
	return;
}

void
mark_unaliased(exp e)
{
	exp p = pt (e);
	bool ca = 1;
	while (p != nilexp && ca) {
		if (bro(p)==nilexp ||
			(!(last (p) && name (bro (p)) == cont_tag) &&
			 !(!last (p) && last (bro (p)) && name (bro (bro (p))) == ass_tag)))
			ca = 0;
		p = pt (p);
	};
	if (ca)
		setcaonly (e);
	return;
}

void
remove_unused()
{ dec ** sdef = &top_def;
 while (*sdef != (dec *) 0) {
	 exp crt_exp = (*sdef) -> dec_u.dec_val.dec_exp;
	 bool extnamed = (*sdef) -> dec_u.dec_val.extnamed;
	 if (no(crt_exp) == 0 && !extnamed) {
		 *sdef = (*sdef)->def_next;
	 }
	 else sdef = &((*sdef)->def_next);
 }
}



void
translate_capsule()
{
	dec * my_def;
	int noprocs;
	int i;
	
	opt_all_exps ();
	remove_unused();
	
#ifdef INCLUDE_INITS
	my_def = top_def;
	while (my_def != (dec *) 0) {
        exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		char * id = my_def -> dec_u.dec_val.dec_id;
		if (strcmp(id, "main")==0 && son(crt_exp)!= nilexp &&
			name(son(crt_exp)) == proc_tag) {
			exp fn = me_obtain(find_named_tg("__DO_I_TDF", f_proc));
			exp cll = getexp(f_top, nilexp, 0, fn, nilexp, 0, 0, apply_tag);
			exp * dm = &son(son(crt_exp));
			exp hld, seq;
			bro(fn) = cll; setlast(fn);
			while (name(*dm)==ident_tag && isparam(*dm)) dm = &bro(son(*dm));
			/* dm is body of main after params */
			hld = getexp(f_top, *dm, 0, cll, nilexp, 0, 1, 0);
			seq = getexp(sh(*dm), bro(*dm), last(*dm), hld, nilexp, 0, 0, seq_tag);
			bro(*dm) = seq; setlast(*dm);
			bro(cll) = hld; setlast(cll);
			*dm = seq;
			break;
		}
        my_def = my_def -> def_next;
	}
#endif
	
    /* mark static unaliased */
	my_def = top_def;
	while (my_def != (dec *) 0) {
		exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		if (son (crt_exp) != nilexp &&
			!my_def -> dec_u.dec_val.extnamed &&
			isvar (crt_exp))
			mark_unaliased (crt_exp);
		my_def = my_def -> def_next;
	};
	
	noprocs = 0;
	my_def = top_def;
	while (my_def != (dec *) 0) {
		exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		if (son (crt_exp) != nilexp
			&& (name (son (crt_exp)) == proc_tag ||
				name(son(crt_exp)) == general_proc_tag)) {
			noprocs++;
		}
		my_def = my_def -> def_next;
	}
	/* count procs */
	
	procrecs = (procrec *) xcalloc (noprocs, sizeof (procrec));
	noprocs = 0;
	
	my_def = top_def;
	while (my_def != (dec *) 0) {
		exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		if (son (crt_exp) != nilexp &&
			(name (son (crt_exp)) == proc_tag || name(son(crt_exp)) == general_proc_tag)) {
			no (son (crt_exp)) = noprocs++;
			/* put index into procrecs in no(proc) */
		}
		my_def = my_def -> def_next;
	}
	
	if (do_extern_adds) {
		usages = (exp*)xcalloc(noprocs, sizeof(exp));
		my_def = top_def;
		while (my_def != (dec *) 0) {
			exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
			if (son(crt_exp) == nilexp && isvar(crt_exp)) {
				global_usages(crt_exp, noprocs);
				/* try to identify globals ptrs in procs */
			}
			my_def = my_def -> def_next;
		}
	}
	
	if (diagnose && nofds !=0) {
		init_table_space (nofds, noprocs);
		add_dense_no (0, 0);
		add_dense_no (0, 0);	/* dont know why!! */
		symnosforfiles ();
		stab_types();
	}
	else {
		init_table_space (1,noprocs);
		add_dense_no (0, 0);
		add_dense_no (0, 0);	/* dont know why!! */
		IGNORE new_lsym_d ("NOFILE.c", 0, stFile, scText, 0, 0);
	};
	
	/* scan to put everything in MIPS form */
	
	my_def = top_def;
	while (my_def != (dec *) 0) {
		exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		if (son (crt_exp) != nilexp
			&& (name (son (crt_exp)) == proc_tag ||
				name(son(crt_exp))== general_proc_tag)) {
			procrec * pr = &procrecs[no (son (crt_exp))];
			exp * st = &son(crt_exp);
			pr -> needsproc = scan (st, &st);
			pr->callee_size = (callee_size+63)&~63;
		}
		my_def = my_def -> def_next;
	}
	
	
	/* calculate the break points for register allocation and do it */
	my_def = top_def;
	while (my_def != (dec *) 0) {
		exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		if (son (crt_exp) != nilexp
			&& (name (son (crt_exp)) == proc_tag ||
				name(son(crt_exp))== general_proc_tag)) {
			procrec * pr = &procrecs[no (son (crt_exp))];
			needs * ndpr = & pr->needsproc;
			long pprops = (ndpr->propsneeds);
			bool leaf = (pprops & anyproccall) == 0;
			spacereq forrest;
			int   freefixed = 8;	/* NO OF S_REGISTERS */
			int   freefloat = 6;	/* NO OF S $f REGISTERS */
			
			setframe_flags(son(crt_exp), leaf);
			if (!Has_fp) freefixed++; /* can use $30 as normal caller save */
			
			if (Has_vcallees) { freefixed--; }
			
			if (!No_S) IGNORE weightsv (1.0, bro (son (son (crt_exp))));
			/* estimate usage of tags in body of proc */
			
			forrest = regalloc (bro (son (son (crt_exp))), freefixed, freefloat,
								(PIC_code && !leaf)?32:0);
			/* reg and stack allocation for tags */
			
			pr -> spacereqproc = forrest;
			
			setframe_info(son(crt_exp));
		}
		my_def = my_def -> def_next;
	}
	
	/* put defs in main globals and set up symnos*/
	my_def = top_def;
	main_globals_index = 0;
	while (my_def != (dec*) 0) {
		main_globals_index++;
		my_def = my_def -> def_next;
	}
	
	data_lab = (main_globals_index > 33)?main_globals_index:33;
	main_globals = (dec**)xcalloc(main_globals_index, sizeof(dec*));
	symnos = (int *) xcalloc (main_globals_index, sizeof (int));
	
	my_def = top_def;
	for (i=0; i < main_globals_index; i++) {
		main_globals[i] = my_def;
		my_def = my_def -> def_next;
	}
	
	
    /* ... and set in the position and "addresses" of the externals */
	for (i = 0; i < main_globals_index; i++) {
		exp tg = main_globals[i] -> dec_u.dec_val.dec_exp;
		char *id = main_globals[i] -> dec_u.dec_val.dec_id;
		bool extnamed = main_globals[i] -> dec_u.dec_val.extnamed;
		diag_descriptor * dinf = main_globals[i] -> dec_u.dec_val.diag_info;
		main_globals[i] ->dec_u.dec_val.sym_number = i;
		if (no (tg) != 0 || (extnamed && son(tg) != nilexp)
			|| strcmp(id,"__TDFhandler") == 0
			|| strcmp(id,"__TDFstacklim")==0
			) {
			if (no(tg)==1 && son(tg)==nilexp && dinf != (diag_descriptor *)0
				/* diagnostics only! */) {
				symnos[i]= -1;
			}
			else {
				no (tg) = (i + 1) * 64 + 32;
				symnos[i] = symnoforext (main_globals[i], mainfile);
			}
		}
		else
			symnos[i] = -1;
	};
	
	
	
	setregalt (nowhere.answhere, 0);
	nowhere.ashwhere.ashsize = 0;
	nowhere.ashwhere.ashsize = 0;
	
	if (as_file) {
		fprintf (as_file, "\t.verstamp %d %d\n", majorno, minorno);
		
		if (PIC_code) {
			fprintf (as_file, "\t.option pic2\n");
		}
		else {
			fprintf (as_file, (diagnose) ? "\t.option O1\n" : "\t.option O2\n");
		}
	}
	
	out_verstamp (majorno, minorno);
	/* this is the only? use of these nos, to
	 *				   satisfy as1 */
	if (PIC_code) {
		out_option(2, 2);
	}
	else
	{ out_option (1, (diagnose) ? 1 : 2); }
	
	if (diagnose && nofds!=0) {
		stab_file (0);
	}
	else
	{
		currentfile = 0;
	}
	
	
	/* compile procedures, evaluate constants, put in the .comm entries for
	 *     undefined objects */
	
	my_def = top_def;
	
/*
 *  while (my_def != (dec *) 0) {
 *    exp tg = my_def -> dec_u.dec_val.dec_exp;
 *    char *id = my_def -> dec_u.dec_val.dec_id;
 *    bool extnamed = my_def -> dec_u.dec_val.extnamed;
 *    if (son (tg) != nilexp && (extnamed || no (tg) != 0 || !strcmp (id, "main"))) {
 *      if (extnamed) {
 *	if (as_file)
 *	  fprintf (as_file, "\t.globl\t%s\n", id);
 *	out_common (symnos[my_def->dec_u.dec_val.sym_number], iglobal);
 *      }
 *    }
 *    my_def = my_def -> def_next;
 *  }
 */
	my_def = top_def;
	
	while (my_def != (dec *) 0) {
		if (!my_def -> dec_u.dec_val.processed)
			code_it (my_def);
		my_def = my_def -> def_next;
	};
	
	
	return;		/* return 1 for error, 0 for good */
	
	
}
void
translate_unit()
{
	if (separate_units)
	{
		dec * my_def;
		translate_capsule();
		my_def = top_def;
		while (my_def != (dec *) 0) {
			exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
			no(crt_exp) = 0;
			pt(crt_exp) = nilexp;
			my_def = my_def -> def_next;
		};
		crt_repeat = nilexp;
		repeat_list = nilexp;
	};
	return;
}


void
translate_tagdef()
{
	return;
}
