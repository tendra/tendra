/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/* 	$Id$	 */

#ifndef lint
static char vcid[] = "$Id$";
#endif /* lint */

#include "config.h"
#include "symtab.h"	
#include "makesymtab.h"	
#include "xalloc.h"
#include "flags.h"
/* type definitions for translator produced debugging 
   information to be incorporated into a .T file  */

#include "archsyms.h"

/**/


long count_syms
    PROTO_N ( ( symlist ) )
    PROTO_T ( LSYMS *symlist )
{
  long symindex = symlist->noofsyms;
  while (symlist->nextsyms!=0){  
    symlist=symlist->nextsyms;
    symindex+=symlist->noofsyms;
  }
  return symindex;
}


long count_strings
    PROTO_N ( ( list ) )
    PROTO_T ( STRINGS *list )
{
  long stringind=list->usage;
  while (list->overspill!=0){
    list=list->overspill;
    stringind+=list->usage;
  }
  return stringind;
}


long count_aux
    PROTO_N ( ( auxdata ) )
    PROTO_T ( AUXTAB *auxdata )
{
  long auxcount=auxdata->num;
  while (auxdata->moreaux!=0){
    auxdata=auxdata->moreaux;
    auxcount+=auxdata->num;
  }	
  return auxcount;
}

#define MAJOR_ASSEMBLER_VERSION 3
#define MINOR_ASSEMBLER_VERSION 11


/* 
   Function to make a symbol table from various components. 
   Sets up a .T file for use by as1 (this function is called 
   from new_symbol.c using output_symtab(name of .T file). )
   by R.R.R  3/12/90  
*/
void makesymtab
    PROTO_N ( ( extstrings,extsymbols,densenos,filedescs,numfiles,
		symtabname,noextsyms,nosyms,extstringsize,stringsize,
		noaux,densind,procinds,noprocs ) )
    PROTO_T ( STRINGS *extstrings X ESYMS* extsymbols X DENSETAB* densenos X
	      pSYMFDR filedescs X int numfiles X char* symtabname X
	      int noextsyms X int nosyms X int extstringsize X
	      int stringsize X int noaux X int densind X
	      PROCSYM* procinds X int noprocs )
{
  

/* 
   function to produce a symbol table (.T file), from information 
   supplied by the translator, including TDF diagnostics. 
   The output file and the binary assembler file (.G , made by 
   as0 on a *.s file) can then be passed to as1 
*/
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


/**************  set up new symbolic header  **********************/


  symhdrout.magic = magicSym;	/* defined in archsyms.h */
  symhdrout.vstamp = MAJOR_ASSEMBLER_VERSION*256+MINOR_ASSEMBLER_VERSION;
  symhdrout.ilineMax = 0;
  symhdrout.cbLine = 0;
  symhdrout.cbLineOffset = 0;
  symhdrout.ipdMax = noprocs;
  symhdrout.cbPdOffset = (long)sizeof(HDRR);
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
  for (j=0;j<numfiles;j++){
    PROCSYM* procindptr=procinds;
    for (i=1;i<=noprocs;i++,procindptr++){
      if (procindptr->fnum==j){
	pdr_ptr->isym=procindptr->procsymindex;
	fwrite(pdr_ptr,sizeof(PDR),1,sym_tab_file);
      }
    }
  }

/* write local symbols */

  for (i=1;i<=numfiles;i++,tempfileptr++){
    symlist=tempfileptr->symbols;
    while (symlist){
      fwrite(symlist->symlist,sizeof(SYMR), symlist->noofsyms, sym_tab_file);
      symlist=symlist->nextsyms;
    }
  }

/* write auxillary symbol entries */

  tempfileptr=filedescs;
  for (i=1;i<=numfiles;i++,tempfileptr++){
    auxdata=tempfileptr->auxtabs;
    while (auxdata){
      fwrite(auxdata->auxinfo,sizeof(AUXU),auxdata->num, sym_tab_file);
      auxdata=auxdata->moreaux;
    }
  }

/* write local strings */

  tempfileptr=filedescs;
  for (i=1;i<=numfiles;i++,tempfileptr++){
    tempstrings = tempfileptr->filestr;
    while (tempstrings){
      fwrite(tempstrings->str, sizeof(char), tempstrings->usage,sym_tab_file);
      tempstrings=tempstrings->overspill;
    }	
  }


/* write external strings */

  tempstrings=extstrings;
  while (tempstrings){
    fwrite(tempstrings->str, sizeof(char), tempstrings->usage,sym_tab_file);
    tempstrings=tempstrings->overspill;
  }


/* write file descriptors */

  tempfileptr=filedescs;
  for(i=1;i<=numfiles;i++,tempfileptr++){
    long count;
    fdrtab.adr=0;
    fdrtab.rss=1;	/* source file name at start of lsymbols */
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
    fdrtab.lang=langC;	/* C ,see archsyms.h  */
    fdrtab.fMerge=0;	/* 1 for .h files I think */
    fdrtab.fReadin=0;
    fdrtab.fBigendian=0;
    fdrtab.glevel= diagnose?GLEVEL_2 : GLEVEL_0;
    fdrtab.reserved=0;	/* what else ! */
    fdrtab.cbLineOffset=0;	/* ??? */
    fdrtab.cbLine=0;	/* ??? */

    fwrite(&fdrtab,sizeof(FDR),1,sym_tab_file);
  }

/*appears to write the right stuff so is it the right place?? */
/* write external symbols */

  while (extsymbols){
    fwrite(extsymbols->symlist, sizeof(EXTR), extsymbols->noofsyms, 
	   sym_tab_file);
    extsymbols=extsymbols->nextsyms;
  }

/* write dense nos */

  while (densenos){
    fwrite(densenos->densenolist,sizeof(DNR),densenos->num,sym_tab_file);
    densenos=densenos->moredensenos;
  }

  fclose(sym_tab_file);

  return;
  
}
