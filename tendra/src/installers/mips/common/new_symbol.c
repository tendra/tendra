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
 * Revision 1.2  1998/02/04  10:43:43  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/10/25  13:48:26  currie
 * change to position of .glob
 *
 * Revision 1.3  1995/09/20  08:28:09  currie
 * Inits
 *
 * Revision 1.2  1995/08/16  16:07:02  currie
 * Shortened some .h names
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
#include "bstack.h"
#include "type_to_aux.h"
#include "makesymtab.h"
#include "xalloc.h"
#include "diagtypes.h"
#include "flags.h"
#include "new_symbol.h"

extern char * init_NAME;

/* Procedures to accumulate symbol table records for MIPS translator
 *
 *new_lsym
 *new_lsym_d
 *new_esym
 *new_esym_d
 *
 *and to output the table
 *
 *output_symtab(name)
 *
 *by R.R.R.  25/1/91	*/

long numfiles;
long numprocs;	/* provided by mipstrans in call to init */


DENSETAB *dense_numbers, *densenos;
STRINGS* extstrings, *external_strings;
ESYMS* esymlist, *external_symbols;

pSYMFDR fdrlist, file_desc_table;
LSYMS* local_symbols;
STRINGS* local_strings;
AUXTAB* aux_symbols;
BSTACK* blockstack;


long* file_inds;
long* aux_inds;
long* str_inds;
long* sym_inds;

PROCSYM* proc_isym_inds;

long nosyms = 0;
long stringsize = 0;
long nostrings=0;
long noaux = 0;
long densind = 0;
long esymindex = 0;
long extind=0;


void
init_table_space(long noofiles, long noprocs)
{
	int ind=0;
	AUXU nilaux;
	nilaux.isym=0;
	blockstack= (BSTACK*)xcalloc(noofiles,sizeof(BSTACK));
	
	densenos=(DENSETAB*)xcalloc(1,sizeof(DENSETAB));
	densenos->num = 0;
	densenos->densenolist = (pDNR)xcalloc(DENSETABSIZE,sizeof(DNR));
	densenos->moredensenos= (DENSETAB*)0;
	dense_numbers=densenos;
	
	extstrings=(STRINGS*)xcalloc(1,sizeof(STRINGS));
	extstrings->str=(char*)xcalloc(STRINGTABSIZE,sizeof(char));
	extstrings->usage=0;
	extstrings->overspill=(STRINGS*)0;
	external_strings=extstrings;
	
	
	esymlist=(ESYMS*)xcalloc(1,sizeof(ESYMS));
	esymlist->symlist=(pEXTR)xcalloc(SYMTABSIZE,sizeof(EXTR));
	esymlist->noofsyms=0;
	esymlist->nextsyms=(ESYMS*)0;
	external_symbols=esymlist;
	
	numfiles=noofiles;
	numprocs=noprocs;
	file_inds =(long*)xcalloc(noofiles,sizeof(long));
	aux_inds =(long*)xcalloc(noofiles,sizeof(long));
	str_inds =(long*)xcalloc(noofiles,sizeof(long));
	sym_inds =(long*)xcalloc(noofiles,sizeof(long));
	proc_isym_inds =(PROCSYM*)xcalloc(noprocs,sizeof(PROCSYM));
	
	fdrlist = (pSYMFDR)xcalloc(noofiles,sizeof(SYMFDR));
	file_desc_table = fdrlist;
	
	local_symbols = (LSYMS*)xcalloc(noofiles,sizeof(LSYMS));
	local_symbols->symlist = (pSYMR)xcalloc(noofiles*SYMTABSIZE,sizeof(SYMR));
	
	local_strings = (STRINGS*)xcalloc(noofiles,sizeof(STRINGS));
	local_strings->str = (char*)xcalloc(noofiles*STRINGTABSIZE,sizeof(char));
	
	aux_symbols=(AUXTAB*)xcalloc(noofiles,sizeof(AUXTAB));
	aux_symbols->auxinfo=(pAUXU)xcalloc(noofiles*AUXTABSIZE,sizeof(AUXU));
	
	for (ind=0; ind<noofiles;ind++,fdrlist++)
	{	fdrlist->symbols=local_symbols+ind;
	fdrlist->filestr=local_strings+ind;
	fdrlist->auxtabs=aux_symbols+ind;
	fdrlist->proc_count=0;
	(local_symbols+ind)->symlist=local_symbols->symlist+ind*SYMTABSIZE;
	(local_strings+ind)->str=local_strings->str+ind*STRINGTABSIZE;
	add_to_loc_strings("",ind);
	(aux_symbols+ind)->auxinfo=aux_symbols->auxinfo+ind*AUXTABSIZE;
	add_aux(nilaux,ind);	/* for each file add nilaux so no 0 */
	}
}


void
add_proc(long sympos, long filenum)
{
	static long symcount=0;
	pSYMFDR fdrlist=file_desc_table+filenum;
	fdrlist->proc_count+=1;
	(proc_isym_inds+symcount)->procsymindex=sympos;
	(proc_isym_inds+symcount)->fnum=filenum;
	symcount++;
}




/*********************  STRING procedures  ********************/


long
add_string(char* str, STRINGS* list)
{
	long stringind=list->usage;
	int length = strlen(str)+1;
	while (list->overspill!=0)
	{  list=list->overspill;
	stringind+=list->usage;
	}
	if ((list->usage+length)>STRINGTABSIZE)
	{  list->overspill = (STRINGS*)xcalloc(1,sizeof(STRINGS));
	list=list->overspill;
	list->str=(char*)xcalloc(STRINGTABSIZE,sizeof(char));
	list->usage=length;
	strcpy(list->str,str);
	}
	else 	{  strcpy(list->str+list->usage,str);
	list->usage+=length;
	}
	return (stringind);
}


long
add_to_loc_strings(char* locstr, int index)
{
	stringsize+=strlen(locstr)+1;
	nostrings++;
	return (add_string(locstr, local_strings+index));
}



long
add_to_ext_strings(char* extstr)
{
	long posind=extind;
	add_string(extstr, extstrings);
	extind+=strlen(extstr)+1;
	return (posind);
}


/******************  DENSE NUMBERS  ********************/



long
add_dense_no(long rfd, long index)
{
	DNR* curr_dense;
	DENSETAB* denseptr= densenos;
	while (denseptr->moredensenos)
	{  denseptr=denseptr->moredensenos;
	}
	if (denseptr->num==DENSETABSIZE)
	{
		denseptr->moredensenos = (DENSETAB*)xcalloc(1,sizeof(DENSETAB));
		denseptr=denseptr->moredensenos;
		denseptr->num = 0;
		denseptr->densenolist = (pDNR)xcalloc(DENSETABSIZE,sizeof(DNR));
		denseptr->moredensenos = (DENSETAB*)0;
	}
	curr_dense=(denseptr->densenolist)+denseptr->num;
	curr_dense->rfd = rfd;
	curr_dense->index = index;
	denseptr->num+=1;
	densind++;
	return (densind-1);
}

DNR*
get_dense_ptr(long densind)
{
	DENSETAB* denseptr = densenos;
	long densecount=denseptr->num;
	while (densecount<=densind)
	{denseptr=denseptr->moredensenos;
	densecount+=denseptr->num;
	}
	return (denseptr->densenolist+(denseptr->num-(densecount-densind)));
}


/********************  SYMBOL PROCEDURES  ********************/

long
get_sym_index(long ind)
{
	LSYMS* lsymlist=local_symbols+ind;
	long lsymindex = lsymlist->noofsyms;
	while (lsymlist->nextsyms!=0)
	{  lsymlist=lsymlist->nextsyms;
	lsymindex+=lsymlist->noofsyms;
	}
	return (lsymindex);
}


SYMR*
get_sym_ptr(long ind, long symind)
{
	LSYMS* lsymlist=local_symbols+ind;
	long symcount=lsymlist->noofsyms;
	while (symcount<=symind)
	{	lsymlist=lsymlist->nextsyms;
	symcount+=lsymlist->noofsyms;
	}
	return (lsymlist->symlist+(lsymlist->noofsyms-(symcount-symind)));
}




long
add_lsym(long ind, SYMR* newsym)
{
	LSYMS* lsymlist=local_symbols+ind;
	long lsymindex = lsymlist->noofsyms;
	nosyms++;
	while (lsymlist->nextsyms!=0)
	{  lsymlist=lsymlist->nextsyms;
	lsymindex+=lsymlist->noofsyms;
	}
	if (lsymlist->noofsyms==SYMTABSIZE)
	{	lsymlist->nextsyms=(LSYMS*)xcalloc(1,sizeof(LSYMS));
	lsymlist=lsymlist->nextsyms;
	lsymlist->symlist=(pSYMR)xcalloc(SYMTABSIZE,sizeof(SYMR));
	lsymlist->noofsyms=0;
	lsymlist->nextsyms=(LSYMS*)0;
	}
	*(lsymlist->symlist+lsymlist->noofsyms)=(*newsym);
	lsymlist->noofsyms += 1;
	return (lsymindex);
}



long
add_esym(long ind, SYMR* newsym)
{
	if (esymlist->noofsyms==SYMTABSIZE)
	{   esymlist->nextsyms=(ESYMS*)xcalloc(1,sizeof(ESYMS));
	esymlist=esymlist->nextsyms;
	esymlist->symlist=(pEXTR)xcalloc(SYMTABSIZE,sizeof(EXTR));
	esymlist->noofsyms=0;
	esymlist->nextsyms=(ESYMS*)0;
	}
	
	(esymlist->symlist+esymlist->noofsyms)->ifd = ind;
	(esymlist->symlist+esymlist->noofsyms)->asym=(*newsym);
	esymlist->noofsyms += 1;
	esymindex++;
	return (esymindex-1);
	
}

long
new_lsym(char* str, long value, short symtype,
		 short symclass, diag_type s, long filenum)
{
	SYMR newsym;
	AUXU nilaux;
	long strind, symindex;
	nilaux.isym=0;
	symindex = get_sym_index(filenum);
 	newsym.value = value;
  	newsym.st = symtype;
  	newsym.sc = symclass;
/* do the following as a switch statment */
	
	if (symtype == stEnd)
		
	{  SYMSTR symstrind;
	long isymstart;
	symstrind = pop(blockstack+filenum);
	isymstart = symstrind.sym;
	if (symstrind.str>0)
	{newsym.iss = symstrind.str;}
	else {newsym.iss = 0;}
	if (isymstart<0)
	{
		newsym.index=(-isymstart);
		get_aux_ptr(filenum,get_sym_ptr(filenum, -isymstart)->index)->isym=symindex+1;
	}
	else
	{get_sym_ptr(filenum, isymstart)->index=symindex+1;
	newsym.index=isymstart;
	}
	
	/* (((local_symbols + filenum)->symlist)+newsym.index)->index = symindex+1; */
	}
	
	else if (symtype == stFile)
	{add_aux(nilaux,filenum);
	strind=add_to_loc_strings(str,filenum);
 	newsym.iss = strind;
	push(symindex, strind, blockstack+filenum);
	/* newsym.index filled in later by stEnd  */
	}
	
	else if (symtype == stBlock)
	{if (str){strind=add_to_loc_strings(str,filenum);}
	else {strind = 0;}
	push(symindex, strind, blockstack+filenum);
 	newsym.iss = strind;
	/* newsym.index filled in later by stEnd  */
	}
	
	else if (symtype == stLabel /*|| symtype == stMember and enum???*/)
	{  newsym.index = 0;
 	newsym.iss = add_to_loc_strings(str,filenum);
	}
	
	else	if (symtype==stProc)
	{DNR* procdense=get_dense_ptr(value);
	strind=add_to_loc_strings(str,filenum);
	newsym.value=0;	/* not needed now */
/* add esym but with lsymindex as index not aux or isymMac */
	newsym.iss = add_to_ext_strings(str);
	newsym.index=symindex;
	procdense->rfd=0x7fffffff;
	procdense->index=add_esym(filenum, &newsym);
	newsym.iss=strind;
	newsym.index=add_aux(nilaux,filenum);
	push(-symindex, strind, blockstack+filenum);
	/*AUX to be filled in at stEnd */
	add_proc(symindex,filenum);	/* all are scText */
	add_aux(nilaux,filenum);	/* add nil type !! */
	}
	
	else if (symtype==stStaticProc)
	{DNR* procdense=get_dense_ptr(value);
	strind=add_to_loc_strings(str,filenum);
	newsym.iss=strind;
	newsym.value = 0;	/* not needed now */
/* add esym but with lsymindex as index not aux or isymMac */
	procdense->rfd=filenum;
	procdense->index=symindex;
	newsym.index=add_aux(nilaux,filenum);
	push(-symindex, strind, blockstack+filenum);
	add_proc(symindex, filenum);
	add_aux(nilaux,filenum);	/* add nil type !! */
	}
	
	else if (!diagnose)
	{newsym.index = 1048575;
 	newsym.iss = add_to_loc_strings(str,filenum);
	}
	
	else	{newsym.iss = add_to_loc_strings(str,filenum);
	newsym.index = add_type_to_aux(s, filenum);
	}
	
	
	return (add_lsym (filenum, &newsym));
}


long
new_lsym_d(char* str, long value, short symtype,
		   short symclass, diag_type s, long filenum)
{
	return (add_dense_no(filenum,new_lsym (str, value, symtype, symclass,s, filenum)));
}



long
new_esym(char* str, long value, short symtype,
		 short symclass, diag_type s, long filenum)
{
	SYMR newsym;
	long strind=add_to_ext_strings(str);
	newsym.iss = strind;
	newsym.value = value;
	newsym.st = symtype;
	newsym.reserved = 0;
	newsym.sc = symclass;
	
	if (((symtype==stProc) && (symclass==scNil ||symclass==scUndefined)) || (!diagnose))
		/* no diagnostics  */
	{newsym.index=1048575;newsym.value=0;}
	else {newsym.index=add_type_to_aux(s,filenum);
	}
	
	return add_esym (filenum, &newsym);
}


long
new_esym_d(char* str, long value, short symtype,
		   short symclass, diag_type s, long filenum)
{
	return (add_dense_no(0x7fffffff,new_esym(str, value, symtype, symclass, s, filenum)));
}


/********************* Auxillary information  ********************/

AUXU*
get_aux_ptr(long index, long auxind)
{
	AUXTAB* auxdata;
	long auxcount;
	auxdata=aux_symbols+index;
	auxcount=auxdata->num;
	while (auxcount <= auxind)
	{	auxdata=auxdata->moreaux;
	auxcount+=auxdata->num;
	}
	return (auxdata->auxinfo+(auxdata->num-(auxcount-auxind)));
}


long
add_aux(AUXU auxent, long index)
{
	AUXTAB* auxdata;
	long auxind;
	noaux++;
	auxdata=aux_symbols+index;
	auxind=auxdata->num;
	while (auxdata->moreaux!=0)
	{	auxdata=auxdata->moreaux;
	auxind+=auxdata->num;
	}
	if (auxdata->num==AUXTABSIZE)
	{	auxdata->moreaux=(AUXTAB*)xcalloc(1,sizeof(AUXTAB));
	auxdata=auxdata->moreaux;
	auxdata->auxinfo=(pAUXU)xcalloc(AUXTABSIZE,sizeof(AUXU));
	auxdata->moreaux=(AUXTAB*)0;
	auxdata->num=0;
	}
	
	*((auxdata->auxinfo)+auxdata->num) = auxent;
	auxdata->num+=1;
	return (auxind);
}


long
add_st_aux(long ind)
{
	AUXU straux;
	AUXU maxaux;
	long indaux;
	maxaux.count=0xffffffff;
	straux.ti.bt=btStruct;
	indaux=add_aux(straux, ind);
	add_aux(maxaux, ind);
	add_aux(maxaux, ind);
	return indaux;
}


long
add_un_aux(long ind)
{
	AUXU uniaux;
	AUXU maxaux;
	long indaux;
	maxaux.count=0xffffffff;
	uniaux.ti.bt=btUnion;
	indaux=add_aux(uniaux, ind);
	add_aux(maxaux, ind);
	add_aux(maxaux, ind);
	return indaux;
}


void
output_symtab(char* symfilename)
{
	/* end all the files */
	int i;
	for (i=0;i<numfiles;i++)	/* might need the iss */
	{new_lsym("",0,stEnd,scText,(diag_type)0,i);
	add_to_loc_strings("", i);
	}
	add_to_ext_strings("");
	makesymtab(external_strings, external_symbols, dense_numbers,
			   file_desc_table, numfiles, symfilename, esymindex, nosyms,
			   extind, stringsize, noaux, densind, proc_isym_inds, numprocs);
}
