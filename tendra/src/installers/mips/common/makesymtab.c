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
 * Revision 1.2  1998/02/04  10:43:42  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/11/23  13:17:22  currie
 * Cache real consts + get text file name right in diags
 *
 * Revision 1.2  1995/09/12  10:59:32  currie
 * gcc pedanttry
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

#include "symtab.h"
#include "common_types.h"
#include "flags.h"
#include "makesymtab.h"
#include "xalloc.h"

extern bool BIGEND;
int MAJOR_VERSION_as = 3;
int MINOR_VERSION_as = 12;

long
count_syms(LSYMS* symlist)
{
	long symindex = symlist->noofsyms;
	while (symlist->nextsyms!=0)
	{  symlist=symlist->nextsyms;
	symindex+=symlist->noofsyms;
	}
	return symindex;
}


long
count_strings(STRINGS* list)
{
	long stringind=list->usage;
	while (list->overspill!=0)
	{  list=list->overspill;
	stringind+=list->usage;
	}
	return stringind;
}


long
count_aux(AUXTAB* auxdata)
{
	long auxcount=auxdata->num;
	while (auxdata->moreaux!=0)
	{	auxdata=auxdata->moreaux;
	auxcount+=auxdata->num;
	}
	return auxcount;
}



/* Function to make a symbol table from various components.
 *   Sets up a .T file for use by as1 (this function is called from
 *   new_symbol.c using output_symtab(name of .T file).)
 *   by R.R.R  3/12/90  */


void
makesymtab(STRINGS* extstrings, ESYMS* extsymbols,
		   DENSETAB* densenos, pSYMFDR filedescs,
		   long numfiles, char* symtabname,
		   long noextsyms, long nosyms, long extstringsize,
		   long stringsize, long noaux, long densind,
		   PROCSYM* procinds, long noprocs)
{
	
/* function to produce a symbol table (.T file), from information supplied
 *   by the translator, including TDF diagnostics. The output file and the
 *   binary assembler file (.G , made by as0 on a *.s file) can then be
 *   passed to as1 */
	
	
	LSYMS * symlist;
	
	HDRR symhdrout;				/* symbolic header */
	int i,j;
	FDR fdrtab;
	long stroff=0;
	long symoff=0;
	long procoff=0;
	long auxoff=0;
	PDR* pdr_ptr;
	STRINGS* tempstrings;
	AUXTAB* auxdata;
	pSYMFDR tempfileptr;
	FILE* sym_tab_file = fopen(symtabname,"w");
	
	
/******************  set up new symbolic header  **********************/
	
	
	symhdrout.magic = magicSym;	/* defined in symconst.h */
	symhdrout.vstamp = MAJOR_VERSION_as*256+MINOR_VERSION_as;
	symhdrout.ilineMax = 0;
	symhdrout.cbLine = 0;
	symhdrout.cbLineOffset = 0;
	symhdrout.ipdMax = noprocs;
	symhdrout.cbPdOffset = sizeof(HDRR);
	symhdrout.isymMax = nosyms;
	symhdrout.cbSymOffset = symhdrout.cbPdOffset + noprocs*sizeof(PDR);
	symhdrout.ioptMax = 0;
	symhdrout.cbOptOffset = 0;
	symhdrout.iauxMax = noaux;
	symhdrout.cbAuxOffset = symhdrout.cbSymOffset + nosyms*sizeof(SYMR);
	symhdrout.issMax = stringsize;
	symhdrout.cbSsOffset = symhdrout.cbAuxOffset + noaux*sizeof(AUXU);
	symhdrout.issExtMax = extstringsize;
	symhdrout.cbSsExtOffset = symhdrout.cbSsOffset + stringsize;
	symhdrout.ifdMax = numfiles;
	symhdrout.cbFdOffset = symhdrout.cbSsExtOffset + extstringsize;
	symhdrout.crfd = 0;
	symhdrout.cbRfdOffset = 0;	/* something may need to be done here */
	symhdrout.iextMax = noextsyms;
	symhdrout.cbExtOffset = symhdrout.cbFdOffset + symhdrout.ifdMax*sizeof(FDR);
	
/* Dense numbers */
	
	symhdrout.idnMax = densind;
	symhdrout.cbDnOffset = symhdrout.cbExtOffset + symhdrout.iextMax*sizeof(EXTR);
	
/* write header to output file */
	
	fwrite(&symhdrout,sizeof(HDRR),1,sym_tab_file);
	
/********************  header completed  *************************/
	
	
	
/**************** write the tables to the file  ******************/
	
	
	tempfileptr=filedescs;
	
/* initialise proc info */
	pdr_ptr=(PDR*)xcalloc(1,sizeof(PDR));
	for (j=0;j<numfiles;j++)
	{PROCSYM* procindptr=procinds;
	for (i=1;i<=noprocs;i++,procindptr++)
	{if (procindptr->fnum==j)
	{
		pdr_ptr->isym=procindptr->procsymindex;
		fwrite(pdr_ptr,sizeof(PDR),1,sym_tab_file);
	}
	}
	}
	
/* write local symbols */
	
    for (i=1;i<=numfiles;i++,tempfileptr++)
	{symlist=tempfileptr->symbols;
	while (symlist)
	{
		fwrite(symlist->symlist,sizeof(SYMR), symlist->noofsyms, sym_tab_file);
		symlist=symlist->nextsyms;
	}
	}
	
/* write auxillary symbol entries */
	
	tempfileptr=filedescs;
    for (i=1;i<=numfiles;i++,tempfileptr++)
	{auxdata=tempfileptr->auxtabs;
	while (auxdata)
	{	fwrite(auxdata->auxinfo,sizeof(AUXU),auxdata->num,
			   sym_tab_file);
	auxdata=auxdata->moreaux;
	}
	}
	
/* write local strings */
	
	tempfileptr=filedescs;
    for (i=1;i<=numfiles;i++,tempfileptr++)
	{
		tempstrings = tempfileptr->filestr;
		while (tempstrings)
		{
			fwrite(tempstrings->str, sizeof(char), tempstrings->usage,sym_tab_file);
			tempstrings=tempstrings->overspill;
		}
	}
	
	
/* write external strings */
	
	tempstrings=extstrings;
	while (tempstrings)
	{
		fwrite(tempstrings->str, sizeof(char), tempstrings->usage,sym_tab_file);
		tempstrings=tempstrings->overspill;
	}
	
	
/* write file descriptors */
	
	tempfileptr=filedescs;
	for (i=1;i<=numfiles;i++,tempfileptr++)
		
	{long count;
	fdrtab.adr=0;
	fdrtab.rss=1;		/* source file name at start of lsymbols */
	fdrtab.issBase = stroff;
	count= count_strings(tempfileptr->filestr);
	stroff+=count;
	fdrtab.cbSs=count;
	count=count_syms(tempfileptr->symbols);
	fdrtab.isymBase = symoff;
	symoff+=count;
	fdrtab.csym=count;
	fdrtab.ilineBase=0;
	fdrtab.cline=0;
	fdrtab.ioptBase=0;
	fdrtab.copt=0;
	fdrtab.ipdFirst=procoff;
	procoff+=tempfileptr->proc_count;
	fdrtab.cpd = tempfileptr->proc_count;
	fdrtab.iauxBase = auxoff;
	count=count_aux(tempfileptr->auxtabs);
	auxoff+=count;
	fdrtab.caux=count;
	fdrtab.rfdBase=0;
	fdrtab.crfd=0;
	fdrtab.lang=langC;	/* C ,see symconst.h  */
	fdrtab.fMerge=0;	/* 1 for .h files I think */
	fdrtab.fReadin=0;
	fdrtab.fBigendian=BIGEND;
	fdrtab.glevel= diagnose?GLEVEL_2:GLEVEL_0;
	fdrtab.reserved=0;	/* what else ! */
	fdrtab.cbLineOffset=0;	/* ??? */
	fdrtab.cbLine=0;	/* ??? */
	
	fwrite(&fdrtab,sizeof(FDR),1,sym_tab_file);
	}
	
/*appears to write the right stuff so is it the right place?? */
/* write external symbols */
	
	while (extsymbols)
	{
		fwrite(extsymbols->symlist, sizeof(EXTR), extsymbols->noofsyms, sym_tab_file);
		extsymbols=extsymbols->nextsyms;
	}
	
/* write dense nos */
	
	while (densenos)
	{
		fwrite(densenos->densenolist,sizeof(DNR),densenos->num,sym_tab_file);
		densenos=densenos->moredensenos;
	}
	
	fclose(sym_tab_file);
	return;
}
