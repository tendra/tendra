/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: release $
$Date: 1998/02/04 10:43:43 $
$Revision: 1.2 $
$Log: new_symbol.c,v $
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


void init_table_space
    PROTO_N ( (noofiles, noprocs) )
    PROTO_T ( long noofiles X long noprocs )
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


void add_proc
    PROTO_N ( (sympos, filenum) )
    PROTO_T ( long sympos X long filenum )
{
	static long symcount=0;
	pSYMFDR fdrlist=file_desc_table+filenum;
	fdrlist->proc_count+=1;
	(proc_isym_inds+symcount)->procsymindex=sympos;
	(proc_isym_inds+symcount)->fnum=filenum;
	symcount++;
}




/*********************  STRING procedures  ********************/


long add_string
    PROTO_N ( (str, list) )
    PROTO_T ( char* str X STRINGS* list )
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


long add_to_loc_strings
    PROTO_N ( (locstr,index) )
    PROTO_T ( char* locstr X int index )
{
	stringsize+=strlen(locstr)+1;
	nostrings++;
	return(add_string(locstr, local_strings+index));
}



long add_to_ext_strings
    PROTO_N ( (extstr) )
    PROTO_T ( char* extstr )
{
	long posind=extind;
	add_string(extstr, extstrings);
	extind+=strlen(extstr)+1;
	return(posind);
}


/******************  DENSE NUMBERS  ********************/



long add_dense_no
    PROTO_N ( (rfd, index) )
    PROTO_T ( long rfd X long index )
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
	return (densind-1);
}

DNR* get_dense_ptr
    PROTO_N ( (densind) )
    PROTO_T ( long densind )
{
	DENSETAB* denseptr = densenos;
	long densecount=denseptr->num;
	while (densecount<=densind)
	   {denseptr=denseptr->moredensenos;
	    densecount+=denseptr->num;
	    }
	return(denseptr->densenolist+(denseptr->num-(densecount-densind)));
}


/********************  SYMBOL PROCEDURES  ********************/

long get_sym_index
    PROTO_N ( (ind) )
    PROTO_T ( long ind )
{
	LSYMS* lsymlist=local_symbols+ind;
	long lsymindex = lsymlist->noofsyms;
	while (lsymlist->nextsyms!=0)
		   {  lsymlist=lsymlist->nextsyms;
		      lsymindex+=lsymlist->noofsyms;
		   }
	return (lsymindex);
}


SYMR* get_sym_ptr
    PROTO_N ( (ind, symind) )
    PROTO_T ( long ind X long symind )
{
	LSYMS* lsymlist=local_symbols+ind;
	long symcount=lsymlist->noofsyms;
	while (symcount<=symind)
	   {	lsymlist=lsymlist->nextsyms;
		symcount+=lsymlist->noofsyms;
	   }
	return(lsymlist->symlist+(lsymlist->noofsyms-(symcount-symind)));
}




long add_lsym
    PROTO_N ( (ind, newsym) )
    PROTO_T ( long ind X SYMR* newsym )
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



long add_esym
    PROTO_N ( (ind, newsym) )
    PROTO_T ( long ind X SYMR* newsym )
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
	    return(esymindex-1);

}

long new_lsym
    PROTO_N ( (str, value, symtype,symclass, s, filenum) )
    PROTO_T ( char* str X long value X short symtype X short symclass X diag_type s X long filenum )
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

   else if (!diagnose )
	{newsym.index = 1048575;
 	newsym.iss = add_to_loc_strings(str,filenum);
	}

   else	{newsym.iss = add_to_loc_strings(str,filenum);
	newsym.index = add_type_to_aux(s, filenum);
	}


   return(add_lsym (filenum, &newsym));
}


long new_lsym_d
    PROTO_N ( (str, value, symtype, symclass, s, filenum) )
    PROTO_T ( char* str X long value X short symtype X short symclass X diag_type s X long filenum )
{
	return(add_dense_no(filenum,new_lsym (str, value, symtype, symclass,s, filenum)));
}



long new_esym
    PROTO_N ( (str,value, symtype, symclass, s, filenum) )
    PROTO_T ( char* str X long value X short symtype X short symclass X diag_type s X long filenum )
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


long new_esym_d
    PROTO_N ( (str, value, symtype, symclass, s, filenum) )
    PROTO_T ( char* str X long value X short symtype X short symclass X diag_type s X long filenum )
{
	return(add_dense_no(0x7fffffff,new_esym(str, value, symtype, symclass, s, filenum)));
}


/********************* Auxillary information  ********************/

AUXU* get_aux_ptr
    PROTO_N ( (index, auxind) )
    PROTO_T ( long index X long auxind )
{
	AUXTAB* auxdata;
	long auxcount;
	auxdata=aux_symbols+index;
	auxcount=auxdata->num;
	while (auxcount <= auxind)
	   {	auxdata=auxdata->moreaux;
		auxcount+=auxdata->num;
	   }
	return(auxdata->auxinfo+(auxdata->num-(auxcount-auxind)));
}


long add_aux
    PROTO_N ( (auxent, index) )
    PROTO_T ( AUXU auxent X long index )
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


long add_st_aux
    PROTO_N ( (ind) )
    PROTO_T ( long ind )
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


long add_un_aux
    PROTO_N ( (ind) )
    PROTO_T ( long ind )
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


void output_symtab
    PROTO_N ( (symfilename) )
    PROTO_T ( char* symfilename )
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
