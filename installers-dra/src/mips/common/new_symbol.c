/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include "config.h"
#include "cross_config.h"

#ifndef CROSS_INCLUDE
#include <symconst.h>
#else
#include CROSS_INCLUDE/symconst.h>
#endif

#include <construct/flags.h>

#include "symtab.h"
#include "bstack.h"
#include "type_to_aux.h"
#include "makesymtab.h"
#include "new_symbol.h"

#include <diag/diagtypes.h>

extern char * init_NAME;

/* Procedures to accumulate symbol table records for MIPS translator

new_lsym
new_lsym_d
new_esym
new_esym_d

and to output the table

output_symtab(name)

by R.R.R.  25/1/91	*/

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

	if (noprocs == 0) {
		proc_isym_inds = NULL;
	} else {
		proc_isym_inds = xcalloc(noprocs, sizeof (PROCSYM));
	}

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
	return stringind;
}


long
add_to_loc_strings(char* locstr, int index)
{
	stringsize+=strlen(locstr)+1;
	nostrings++;
	return add_string(locstr, local_strings+index);
}



long
add_to_ext_strings(char* extstr)
{
	long posind=extind;
	add_string(extstr, extstrings);
	extind+=strlen(extstr)+1;
	return posind;
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
	if(denseptr->num==DENSETABSIZE)
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
	return densind-1;
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
	return denseptr->densenolist+(denseptr->num-(densecount-densind));
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
	return lsymindex;
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
	return lsymlist->symlist+(lsymlist->noofsyms-(symcount-symind));
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
	return lsymindex;
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
	    return esymindex-1;

}

long
new_lsym(char* str, long value, short symtype, short symclass, diag_type s, long filenum)
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

   else if (symtype == stLabel /*|| symtype == stMember and enum???*/ )
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

   else if (diag == DIAG_NONE)
	{newsym.index = 1048575;
 	newsym.iss = add_to_loc_strings(str,filenum);
	}

   else	{newsym.iss = add_to_loc_strings(str,filenum);
	newsym.index = add_type_to_aux(s, filenum);
	}


   return add_lsym (filenum, &newsym);
}


long
new_lsym_d(char* str, long value, short symtype, short symclass, diag_type s, long filenum)
{
	return add_dense_no(filenum,new_lsym (str, value, symtype, symclass,s, filenum));
}



long
new_esym(char* str, long value, short symtype, short symclass, diag_type s, long filenum)
{
   SYMR newsym;
   long strind=add_to_ext_strings(str);
   newsym.iss = strind;
   newsym.value = value;
   newsym.st = symtype;
   newsym.reserved = 0;
   newsym.sc = symclass;

	if (((symtype==stProc) && (symclass==scNil ||symclass==scUndefined)) || (diag == DIAG_NONE))
		/* no diagnostics  */
		{newsym.index=1048575;newsym.value=0;}
	else {newsym.index=add_type_to_aux(s,filenum);
		}

   return add_esym (filenum, &newsym);
}


long
new_esym_d(char* str, long value, short symtype, short symclass, diag_type s, long filenum)
{
	return add_dense_no(0x7fffffff,new_esym(str, value, symtype, symclass, s, filenum));
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
	return auxdata->auxinfo+(auxdata->num-(auxcount-auxind));
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
	return auxind;
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
