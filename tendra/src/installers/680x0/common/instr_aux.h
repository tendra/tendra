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
 *    		 Crown Copyright (c) 1996
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
/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------
 *$Log$
 *Revision 1.2  2002/11/21 22:30:45  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
 *Revision 1.1.1.1  1997/10/13 12:42:54  ma
 *First version.
 *
 *Revision 1.2  1997/09/25 06:45:11  ma
 *All general_proc tests passed
 *
 *Revision 1.1.1.1  1997/03/14 07:50:13  ma
 *Imported from DRA
 
 * Revision 1.1.1.1  1996/09/20  10:56:54  john
 *
 * Revision 1.2  1996/07/05  14:21:24  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:13  john
 *
 * Revision 1.3  93/03/03  14:46:53  14:46:53  ra (Robert Andrews)
 * Regenerated file with overflow jumps.
 * 
 * Revision 1.2  93/02/23  15:43:50  15:43:50  ra (Robert Andrews)
 * Regenerated file (it is automatically generated), adding instructions
 * for binary coded decimal and extended arithmetic
 * 
 * Revision 1.1  93/02/23  15:42:30  15:42:30  ra (Robert Andrews)
 * Initial revision
 * 
 *--------------------------------------------------------------------------
 */


/*
 *    THIS FILE IS AUTOMATICALLY GENERATED
 */


#ifdef INSTR_SET_0

NULL,
    NULL,
    NULL,
    "\tlalign 4",
    "\tset ",
    "\tbyte ",
    "\tshort ",
    "\tlong ",
    "\tfloat ",
    "\tdouble ",
    "\tspace ",
    "\tglobal ",
    "\tcomm ",
    "\tcomm ",
    "\ttext",
    "\tdata",
    "\tbss",
    "\tabcd\t  ",
    "\tadd.b\t  ",
    "\tadd.w\t  ",
    "\tadd.l\t  ",
    "\taddq.b\t  ",
    "\taddq.w\t  ",
    "\taddq.l\t  ",
    "\taddx.b\t  ",
    "\taddx.w\t  ",
    "\taddx.l\t  ",
    "\tand.b\t  ",
    "\tand.w\t  ",
    "\tand.l\t  ",
    "\tasl.b\t  ",
    "\tasl.w\t  ",
    "\tasl.l\t  ",
    "\tasr.b\t  ",
    "\tasr.w\t  ",
    "\tasr.l\t  ",
    "\tbclr\t  ",
    "\tbfexts\t  ",
    "\tbfextu\t  ",
    "\tbfins\t  ",
    "\tbset\t  ",
    "\tbtst.b\t  ",
    "\tbtst\t  ",
    "\tbtst.l\t  ",
    "\tjsr\t  ",
    "\tclr.b\t  ",
    "\tclr.w\t  ",
    "\tclr.l\t  ",
    "\tcmp.b\t  ",
    "\tcmp.w\t  ",
    "\tcmp.l\t  ",
    "\tcmpm.b\t  ",
    "\tcmpm.w\t  ",
    "\tcmpm.l\t  ",
    "\tdbf\t  ",
    "\tdivs.l\t  ",
    "\tdivsl.l\t  ",
    "\tdivu.l\t  ",
    "\tdivul.l\t  ",
    "\tdont_know ",
    "\teor.b\t  ",
    "\teor.w\t  ",
    "\teor.l\t  ",
    "\text.w\t  ",
    "\text.l\t  ",
    "\textb.l\t  ",
    "\tfabs.s\t  ",
    "\tfabs.d\t  ",
    "\tfabs.x\t  ",
    "\tfadd.s\t  ",
    "\tfadd.d\t  ",
    "\tfadd.x\t  ",
    "\tfcmp.s\t  ",
    "\tfcmp.d\t  ",
    "\tfcmp.x\t  ",
    "\tfdiv.s\t  ",
    "\tfdiv.d\t  ",
    "\tfdiv.x\t  ",
    "\tfint.s\t  ",
    "\tfint.d\t  ",
    "\tfint.x\t  ",
    "\tfintrz.s  ",
    "\tfintrz.d  ",
    "\tfintrz.x  ",
    "\tfmov.l\t  ",
    "\tfmov.s\t  ",
    "\tfmov.d\t  ",
    "\tfmov.x\t  ",
    "\tfmovem.x  ",
    "\tfmul.s\t  ",
    "\tfmul.d\t  ",
    "\tfmul.x\t  ",
    "\tfneg.x\t  ",
    "\tfsub.s\t  ",
    "\tfsub.d\t  ",
    "\tfsub.x\t  ",
    "\tftest.x\t  ",
    "\tjmp\t  ",
    "\tlea\t  ",
    "\tlink.w\t  ",
    "\tlink.l\t  ",
    "\tlsl.b\t  ",
    "\tlsl.w\t  ",
    "\tlsl.l\t  ",
    "\tlsr.b\t  ",
    "\tlsr.w\t  ",
    "\tlsr.l\t  ",
    "\tmov.b\t  ",
    "\tmov.w\t  ",
    "\tmov.l\t  ",
    "\tmovm.l\t  ",
    "\tmovq\t  ",
    "\tmuls.w\t  ",
    "\tmuls.l\t  ",
    "\tmulu.w\t  ",
    "\tmulu.l\t  ",
    "\tnbcd\t  ",
    "\tneg.b\t  ",
    "\tneg.w\t  ",
    "\tneg.l\t  ",
    "\tnegx.b\t  ",
    "\tnegx.w\t  ",
    "\tnegx.l\t  ",
    "\tnop\t  ",
    "\tnot.b\t  ",
    "\tnot.w\t  ",
    "\tnot.l\t  ",
    "\tor.b\t  ",
    "\tor.w\t  ",
    "\tor.l\t  ",
    "\tpack\t  ",
    "\tpea\t  ",
    "\trol.b\t  ",
    "\trol.w\t  ",
    "\trol.l\t  ",
    "\tror.b\t  ",
    "\tror.w\t  ",
    "\tror.l\t  ",
    "\troxl.b\t  ",
    "\troxl.w\t  ",
    "\troxl.l\t  ",
    "\troxr.b\t  ",
    "\troxr.w\t  ",
    "\troxr.l\t  ",
    "\trts",
    "\tsbcd\t  ",
    "\tsub.b\t  ",
    "\tsub.w\t  ",
    "\tsub.l\t  ",
    "\tsubq.b\t  ",
    "\tsubq.w\t  ",
    "\tsubq.l\t  ",
    "\tsubx.b\t  ",
    "\tsubx.w\t  ",
    "\tsubx.l\t  ",
    "\ttst.b\t  ",
    "\ttst.w\t  ",
    "\ttst.l\t  ",
    "\tunlk\t  ",
    "\tunpk\t  ",
    "\tsltnormal\t",
    "\tsltspecial\t",
    "\tsltexit\t\t",
    "\tdntt",
    "\tvt",
    "\tlntt",
    "\tgntt",
    "\tvtbytes ",
    "\tlalign 1",
    "\tdnt_array\t",
    "\tdnt_begin\t",
    "\tdnt_const\t",
    "\tdnt_dvar\t",
    "\tdnt_end\t\t",
    "\tdnt_entry\t",
    "\tdnt_enum\t",
    "\tdnt_field\t",
    "\tdnt_file\t",
    "\tdnt_fparam\t",
    "\tdnt_function\t",
    "\tdnt_functype\t",
    "\tdnt_import\t",
    "\tdnt_label\t",
    "\tdnt_memenum\t",
    "\tdnt_module\t",
    "\tdnt_pointer\t",
    "\tdnt_set\t\t",
    "\tdnt_srcfile\t",
    "\tdnt_struct\t",
    "\tdnt_subrange\t",
    "\tdnt_svar\t",
    "\tdnt_tagdef\t",
    "\tdnt_typedef\t",
    "\tdnt_union\t",
    "\tdnt_variant\t",
    "\tstabs ",
    "\tstabd ",
    "\tstabn ",
    "\tbcc\t  ",
    "\tbcs\t  ",
    "\tbeq\t  ",
    "\tbge\t  ",
    "\tbgt\t  ",
    "\tbhi\t  ",
    "\tble\t  ",
    "\tbls\t  ",
    "\tblt\t  ",
    "\tbne\t  ",
    "\tbra\t  ",
    "\tbvc\t  ",
    "\tbvs\t  ",
    "\tfbeq\t  ",
    "\tfbge\t  ",
    "\tfbgt\t  ",
    "\tfble\t  ",
    "\tfblt\t  ",
    "\tfbne\t  ",
    "\tfbnge\t  ",
    "\tfbngt\t  ",
    "\tfbnle\t  ",
    "\tfbnlt\t  ",
    "\tbcc.b\t  ",
    "\tbcs.b\t  ",
    "\tbeq.b\t  ",
    "\tbge.b\t  ",
    "\tbgt.b\t  ",
    "\tbhi.b\t  ",
    "\tble.b\t  ",
    "\tbls.b\t  ",
    "\tblt.b\t  ",
    "\tbne.b\t  ",
    "\tbra.b\t  ",
    "\tbvc.b\t  ",
    "\tbvs.b\t  ",
    "\tfbeq.w\t  ",
    "\tfbge.w\t  ",
    "\tfbgt.w\t  ",
    "\tfble.w\t  ",
    "\tfblt.w\t  ",
    "\tfbne.w\t  ",
    "\tfbnge.w\t  ",
    "\tfbngt.w\t  ",
    "\tfbnle.w\t  ",
    "\tfbnlt.w\t  ",
    "\tbcc.w\t  ",
    "\tbcs.w\t  ",
    "\tbeq.w\t  ",
    "\tbge.w\t  ",
    "\tbgt.w\t  ",
    "\tbhi.w\t  ",
    "\tble.w\t  ",
    "\tbls.w\t  ",
    "\tblt.w\t  ",
    "\tbne.w\t  ",
    "\tbra.w\t  ",
    "\tbvc.w\t  ",
    "\tbvs.w\t  ",
    "\tfbeq.w\t  ",
    "\tfbge.w\t  ",
    "\tfbgt.w\t  ",
    "\tfble.w\t  ",
    "\tfblt.w\t  ",
    "\tfbne.w\t  ",
    "\tfbnge.w\t  ",
    "\tfbngt.w\t  ",
    "\tfbnle.w\t  ",
    "\tfbnlt.w\t  ",
    "\tbcc.l\t  ",
    "\tbcs.l\t  ",
    "\tbeq.l\t  ",
    "\tbge.l\t  ",
    "\tbgt.l\t  ",
    "\tbhi.l\t  ",
    "\tble.l\t  ",
    "\tbls.l\t  ",
    "\tblt.l\t  ",
    "\tbne.l\t  ",
    "\tbra.l\t  ",
    "\tbvc.l\t  ",
    "\tbvs.l\t  ",
    "\tfbeq.l\t  ",
    "\tfbge.l\t  ",
    "\tfbgt.l\t  ",
    "\tfble.l\t  ",
    "\tfblt.l\t  ",
    "\tfbne.l\t  ",
    "\tfbnge.l\t  ",
    "\tfbngt.l\t  ",
    "\tfbnle.l\t  ",
    "\tfbnlt.l\t  ",
    "\ttrap\t  ",
    "\ttrapcc\t  ",
    "\ttrapcs\t  ",
    "\ttrapeq\t  ",
    "\ttrapge\t  ",
    "\ttrapgt\t  ",
    "\ttraphi\t  ",
    "\ttraple\t  ",
    "\ttrapls\t  ",
    "\ttraplt\t  ",
    "\ttrapne\t  ",
    "\ttrapt\t  ",
    "\ttrapvc\t  ",
    "\ttrapvs\t  ",
    "\ttrapv\t  ",
    NULL
	
#undef INSTR_SET_0
#endif
	
#ifdef REGISTER_SET_0
	
    "%d0", "%d1", "%d2", "%d3", "%d4", "%d5", "%d6", "%d7",
    "%a0", "%a1", "%a2", "%a3", "%a4", "%a5", "%a6", "%sp",
    "%fp0", "%fp1", "%fp2", "%fp3", "%fp4", "%fp5", "%fp6", "%fp7",
    "%pc", "%ccr", "%fpcr", "%fpsr", "%fpiar", "%za0"
	
#define NO_OF_REGS 30
	
#undef REGISTER_SET_0
#endif
	
#ifdef INSTR_SET_1
	
    NULL,
    NULL,
    NULL,
    "\t.align 4",
    "\t.set ",
    "\t.byte ",
    "\t.short ",
    "\t.long ",
    "\t.single ",
    "\t.double ",
    "\t.skip ",
    "\t.globl ",
    "\t.comm ",
    "\t.lcomm ",
    "\t.text",
    "\t.data",
    "\t.data",
    "\tabcd\t  ",
    "\taddb\t  ",
    "\taddw\t  ",
    "\taddl\t  ",
    "\taddqb\t  ",
    "\taddqw\t  ",
    "\taddql\t  ",
    "\taddxb\t  ",
    "\taddxw\t  ",
    "\taddxl\t  ",
    "\tandb\t  ",
    "\tandw\t  ",
    "\tandl\t  ",
    "\taslb\t  ",
    "\taslw\t  ",
    "\tasll\t  ",
    "\tasrb\t  ",
    "\tasrw\t  ",
    "\tasrl\t  ",
    "\tbclr\t  ",
    "\tbfexts\t  ",
    "\tbfextu\t  ",
    "\tbfins\t  ",
    "\tbset\t  ",
    "\tbtstb\t  ",
    "\tbtst\t  ",
    "\tbtstl\t  ",
    "\tjbsr\t  ",
    "\tclrb\t  ",
    "\tclrw\t  ",
    "\tclrl\t  ",
    "\tcmpb\t  ",
    "\tcmpw\t  ",
    "\tcmpl\t  ",
    "\tcmpmb\t  ",
    "\tcmpmw\t  ",
    "\tcmpml\t  ",
    "\tdbf\t  ",
    "\tdivsl\t  ",
    "\tdivsll\t  ",
    "\tdivul\t  ",
    "\tdivull\t  ",
    "\tdont_know ",
    "\teorb\t  ",
    "\teorw\t  ",
    "\teorl\t  ",
    "\textw\t  ",
    "\textl\t  ",
    "\textbl\t  ",
    "\tfabss\t  ",
    "\tfabsd\t  ",
    "\tfabsx\t  ",
    "\tfadds\t  ",
    "\tfaddd\t  ",
    "\tfaddx\t  ",
    "\tfcmps\t  ",
    "\tfcmpd\t  ",
    "\tfcmpx\t  ",
    "\tfdivs\t  ",
    "\tfdivd\t  ",
    "\tfdivx\t  ",
    "\tfints\t  ",
    "\tfintd\t  ",
    "\tfintx\t  ",
    "\tfintrzs\t  ",
    "\tfintrzd\t  ",
    "\tfintrzx\t  ",
    "\tfmovel\t  ",
    "\tfmoves\t  ",
    "\tfmoved\t  ",
    "\tfmovex\t  ",
    "\tfmovemx\t  ",
    "\tfmuls\t  ",
    "\tfmuld\t  ",
    "\tfmulx\t  ",
    "\tfnegx\t  ",
    "\tfsubs\t  ",
    "\tfsubd\t  ",
    "\tfsubx\t  ",
    "\tftstx\t  ",
    "\tjmp\t  ",
    "\tlea\t  ",
    "\tlinkw\t  ",
    "\tlinkl\t  ",
    "\tlslb\t  ",
    "\tlslw\t  ",
    "\tlsll\t  ",
    "\tlsrb\t  ",
    "\tlsrw\t  ",
    "\tlsrl\t  ",
    "\tmoveb\t  ",
    "\tmovew\t  ",
    "\tmovel\t  ",
    "\tmoveml\t  ",
    "\tmoveq\t  ",
    "\tmulsw\t  ",
    "\tmulsl\t  ",
    "\tmuluw\t  ",
    "\tmulul\t  ",
    "\tnbcd\t  ",
    "\tnegb\t  ",
    "\tnegw\t  ",
    "\tnegl\t  ",
    "\tnegxb\t  ",
    "\tnegxw\t  ",
    "\tnegxl\t  ",
    "\tnop\t  ",
    "\tnotb\t  ",
    "\tnotw\t  ",
    "\tnotl\t  ",
    "\torb\t  ",
    "\torw\t  ",
    "\torl\t  ",
    "\tpack\t  ",
    "\tpea\t  ",
    "\trolb\t  ",
    "\trolw\t  ",
    "\troll\t  ",
    "\trorb\t  ",
    "\trorw\t  ",
    "\trorl\t  ",
    "\troxlb\t  ",
    "\troxlw\t  ",
    "\troxll\t  ",
    "\troxrb\t  ",
    "\troxrw\t  ",
    "\troxrl\t  ",
    "\trts",
    "\tsbcd\t  ",
    "\tsubb\t  ",
    "\tsubw\t  ",
    "\tsubl\t  ",
    "\tsubqb\t  ",
    "\tsubqw\t  ",
    "\tsubql\t  ",
    "\tsubxb\t  ",
    "\tsubxw\t  ",
    "\tsubxl\t  ",
    "\ttstb\t  ",
    "\ttstw\t  ",
    "\ttstl\t  ",
    "\tunlk\t  ",
    "\tunpk\t  ",
    "\t.sltnormal\t",
    "\t.sltspecial\t",
    "\t.sltexit\t",
    "\t.dntt",
    "\t.vt",
    "\t.lntt",
    "\t.gntt",
    "\t.vtbytes ",
    "\t.lalign 1",
    "\t.dnt_array\t",
    "\t.dnt_begin\t",
    "\t.dnt_const\t",
    "\t.dnt_dvar\t",
    "\t.dnt_end\t",
    "\t.dnt_entry\t",
    "\t.dnt_enum\t",
    "\t.dnt_field\t",
    "\t.dnt_file\t",
    "\t.dnt_fparam\t",
    "\t.dnt_function\t",
    "\t.dnt_functype\t",
    "\t.dnt_import\t",
    "\t.dnt_label\t",
    "\t.dnt_memenum\t",
    "\t.dnt_module\t",
    "\t.dnt_pointer\t",
    "\t.dnt_set\t",
    "\t.dnt_srcfile\t",
    "\t.dnt_struct\t",
    "\t.dnt_subrange\t",
    "\t.dnt_svar\t",
    "\t.dnt_tagdef\t",
    "\t.dnt_typedef\t",
    "\t.dnt_union\t",
    "\t.dnt_variant\t",
    "\t.stabs ",
    "\t.stabd ",
    "\t.stabn ",
    "\tjcc\t  ",
    "\tjcs\t  ",
    "\tjeq\t  ",
    "\tjge\t  ",
    "\tjgt\t  ",
    "\tjhi\t  ",
    "\tjle\t  ",
    "\tjls\t  ",
    "\tjlt\t  ",
    "\tjne\t  ",
    "\tjra\t  ",
    "\tjvc\t  ",
    "\tjvs\t  ",
    "\tfjeq\t  ",
    "\tfjge\t  ",
    "\tfjgt\t  ",
    "\tfjle\t  ",
    "\tfjlt\t  ",
    "\tfjne\t  ",
    "\tfjnge\t  ",
    "\tfjngt\t  ",
    "\tfjnle\t  ",
    "\tfjnlt\t  ",
    "\tbccb\t  ",
    "\tbcsb\t  ",
    "\tbeqb\t  ",
    "\tbgeb\t  ",
    "\tbgtb\t  ",
    "\tbhib\t  ",
    "\tbleb\t  ",
    "\tblsb\t  ",
    "\tbltb\t  ",
    "\tbneb\t  ",
    "\tbrab\t  ",
    "\tbvcb\t  ",
    "\tbvsb\t  ",
    "\tfbeqw\t  ",
    "\tfbgew\t  ",
    "\tfbgtw\t  ",
    "\tfblew\t  ",
    "\tfbltw\t  ",
    "\tfbnew\t  ",
    "\tfbngew\t  ",
    "\tfbngtw\t  ",
    "\tfbnlew\t  ",
    "\tfbnltw\t  ",
    "\tbccw\t  ",
    "\tbcsw\t  ",
    "\tbeqw\t  ",
    "\tbgew\t  ",
    "\tbgtw\t  ",
    "\tbhiw\t  ",
    "\tblew\t  ",
    "\tblsw\t  ",
    "\tbltw\t  ",
    "\tbnew\t  ",
    "\tbraw\t  ",
    "\tbvcw\t  ",
    "\tbvsw\t  ",
    "\tfbeqw\t  ",
    "\tfbgew\t  ",
    "\tfbgtw\t  ",
    "\tfblew\t  ",
    "\tfbltw\t  ",
    "\tfbnew\t  ",
    "\tfbngew\t  ",
    "\tfbngtw\t  ",
    "\tfbnlew\t  ",
    "\tfbnltw\t  ",
    "\tbccl\t  ",
    "\tbcsl\t  ",
    "\tbeql\t  ",
    "\tbgel\t  ",
    "\tbgtl\t  ",
    "\tbhil\t  ",
    "\tblel\t  ",
    "\tblsl\t  ",
    "\tbltl\t  ",
    "\tbnel\t  ",
    "\tbral\t  ",
    "\tbvcl\t  ",
    "\tbvsl\t  ",
    "\tfbeql\t  ",
    "\tfbgel\t  ",
    "\tfbgtl\t  ",
    "\tfblel\t  ",
    "\tfbltl\t  ",
    "\tfbnel\t  ",
    "\tfbngel\t  ",
    "\tfbngtl\t  ",
    "\tfbnlel\t  ",
    "\tfbnltl\t  ",
    "\ttrap\t  ",
    "\ttrapcc\t  ",
    "\ttrapcs\t  ",
    "\ttrapeq\t  ",
    "\ttrapge\t  ",
    "\ttrapgt\t  ",
    "\ttraphi\t  ",
    "\ttraple\t  ",
    "\ttrapls\t  ",
    "\ttraplt\t  ",
    "\ttrapne\t  ",
    "\ttrapt\t  ",
    "\ttrapvc\t  ",
    "\ttrapvs\t  ",
    "\ttrapv\t  ",
    NULL
	
#undef INSTR_SET_1
#endif
	
#ifdef REGISTER_SET_1
	
    "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7",
    "a0", "a1", "a2", "a3", "a4", "a5", "a6", "sp",
    "fp0", "fp1", "fp2", "fp3", "fp4", "fp5", "fp6", "fp7",
    "pc", "ccr", "fpcr", "fpsr", "fpiar", "za0"
	
#define NO_OF_REGS 30
	
#undef REGISTER_SET_1
#endif
	
#ifdef INSTR_SIZES
	
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2,
    4, 1, 2, 4, 1, 2, 4, 1, 2, 4, 1, 2, 4, 1, 2, 4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 2, 4, 1, 2, 4, 1, 2, 4, 0, 0, 0, 0, 0, 0,
    1, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 4, 1, 2, 4, 1, 2, 4, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4,
    1, 2, 4, 0, 1, 2, 4, 1, 2, 4, 0, 0, 1, 2, 4, 1, 2, 4, 1, 2,
    4, 1, 2, 4, 0, 0, 1, 2, 4, 1, 2, 4, 1, 2, 4, 1, 2, 4, 0, 0,
    0
	
#undef INSTR_SIZES
#endif
	
#ifdef OPPOSITE_JUMPS
	
	static int oppo_jump_table [] = {
		m_bcs,
		m_bcc,
		m_bne,
		m_blt,
		m_ble,
		m_bls,
		m_bgt,
		m_bhi,
		m_bge,
		m_beq,
		m_dont_know,
		m_bvs,
		m_bvc,
		m_fbne,
		m_fbnge,
		m_fbngt,
		m_fbnle,
		m_fbnlt,
		m_fbeq,
		m_fbge,
		m_fbgt,
		m_fble,
		m_fblt,
		m_dont_know
	};

#define  oppo_jump(X)		(oppo_jump_table [ (X) - m_bcc ])

#undef OPPOSITE_JUMPS
#endif

#ifdef REGISTER_SIZES
#define NO_OF_REGS 30
#undef REGISTER_SIZES
#endif

