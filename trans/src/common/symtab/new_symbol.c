/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This file contains code to generate the alpha symbol table (the .t file).
 * This code is based on the MIPS translator file new_symbol.c
 */

#include <stddef.h>
#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <local/localtypes.h>
#include <local/expmacs.h>

#include <construct/flags.h>

#include <diag/diagtypes.h>

/*
 * Type definitions for translator produced debugging information
 * to be incorporated into a .T file
 */
#include <symtab/cross_config.h>
#include <symtab/symtab.h>
#include <symtab/symconst.h>
#include <symtab/new_symbol.h>
#include <symtab/makesymtab.h>
#include <symtab/bstack.h>

#include "type_to_aux.h"

/*
 * Procedures to accumulate symbol table records for MIPS translator
 *
 *    new_lsym
 *    new_lsym_d
 *    new_esym
 *    new_esym_d
 *
 * and to output the table
 *
 *    output_symtab(name)
 */

int numfiles;
int numprocs;	/* provided by mipstrans in call to init */


DENSETAB *dense_numbers, *densenos;
STRINGS *extstrings, *external_strings;
ESYMS *esymlist, *external_symbols;

pSYMFDR fdrlist, file_desc_table;
LSYMS *local_symbols;
STRINGS *local_strings;
AUXTAB *aux_symbols;
BSTACK *blockstack;

int *file_inds;
int *aux_inds;
int *str_inds;
int *sym_inds;

PROCSYM *proc_isym_inds;

int nosyms     = 0;
int stringsize = 0;
int nostrings  = 0;
int noaux      = 0;
int densind    = 0;
int esymindex  = 0;
int extind     = 0;

void
init_table_space(long noofiles, long noprocs)
{
    long ind = 0;
    AUXU nilaux;
    nilaux.isym = 0;
    blockstack = xcalloc(noofiles, sizeof (BSTACK));

    if (noofiles == 0) {
		failer("TDF capsule does not contain diagnostic information");
	}

    densenos = xcalloc(1, sizeof (DENSETAB));
    densenos->num          = 0;
    densenos->densenolist  = xcalloc(DENSETABSIZE, sizeof (DNR));
    densenos->moredensenos = (DENSETAB *) 0;
    dense_numbers          = densenos;

    extstrings = xcalloc(1, sizeof (STRINGS));
    extstrings->str       = xcalloc(STRINGTABSIZE, sizeof (char));
    extstrings->usage     = 0;
    extstrings->overspill = (STRINGS *) 0;
    external_strings      = extstrings;

    esymlist = xcalloc(1, sizeof (ESYMS));
    esymlist->symlist  = xcalloc(SYMTABSIZE, sizeof (EXTR));
    esymlist->noofsyms = 0;
    esymlist->nextsyms = (ESYMS *) 0;
    external_symbols   = esymlist;

    numfiles  = noofiles;
    numprocs  = noprocs;
    file_inds = xcalloc(noofiles, sizeof (int));
    aux_inds  = xcalloc(noofiles, sizeof (int));
    str_inds  = xcalloc(noofiles, sizeof (int));
    sym_inds  = xcalloc(noofiles, sizeof (int));

    if (noprocs == 0) {
		proc_isym_inds = NULL;
    } else {
		proc_isym_inds = xcalloc(noprocs, sizeof (PROCSYM));
    }

    fdrlist = xcalloc(noofiles, sizeof (SYMFDR));
    file_desc_table = fdrlist;

    local_symbols = xcalloc(noofiles, sizeof (LSYMS));
    local_symbols->symlist = xcalloc(noofiles * SYMTABSIZE, sizeof (SYMR));

    local_strings = xcalloc(noofiles, sizeof (STRINGS));
    local_strings->str = xcalloc(noofiles * STRINGTABSIZE, sizeof (char));

    aux_symbols = xcalloc(noofiles, sizeof (AUXTAB));
    aux_symbols->auxinfo = xcalloc(noofiles * AUXTABSIZE, sizeof (AUXU));

    for (ind = 0; ind < noofiles; ind++, fdrlist++) {
		fdrlist->symbols = local_symbols + ind;
		fdrlist->filestr = local_strings + ind;
		fdrlist->auxtabs = aux_symbols + ind;
		fdrlist->proc_count = 0;

		local_symbols[ind].symlist = local_symbols->symlist + ind * SYMTABSIZE;
		local_strings[ind].str     = local_strings->str     + ind * STRINGTABSIZE;

#ifdef TRANS_MIPS
		add_to_loc_strings("", ind);
#endif
		(aux_symbols + ind)->auxinfo = aux_symbols->auxinfo + ind * AUXTABSIZE;
		add_aux(nilaux, ind);	/* for each file add nilaux so no 0 */
    }

}

void
add_proc(long sympos, long filenum)
{
	static int symcount = 0;

	pSYMFDR fdrlist = file_desc_table + filenum;
	fdrlist->proc_count += 1;

	proc_isym_inds[symcount].procsymindex = sympos;
	proc_isym_inds[symcount].fnum = filenum;

	symcount++;
}

/*
 * String procedures
 */

long
add_string(char *str, STRINGS * list)
{
	long stringind;
	size_t length;

	stringind = list->usage;
	length = strlen(str) + 1;

	while (list->overspill != 0) {
		list = list->overspill;
		stringind += list->usage;
	}

	if ((list->usage + length) > STRINGTABSIZE) {
		list->overspill = xcalloc(1, sizeof (STRINGS));
		list = list->overspill;
		list->str = xcalloc(STRINGTABSIZE, sizeof (char));
		list->usage = length;
		strcpy(list->str, str);
	} else {
		strcpy(list->str + list->usage, str);
		list->usage += length;
	}

	return stringind;
}

long
add_to_loc_strings(char *locstr, int index)
{
	stringsize += strlen(locstr) + 1;
	nostrings++;

	return add_string(locstr, local_strings + index);
}



long
add_to_ext_strings(char *extstr)
{
	long posind = extind;

	add_string(extstr, extstrings);
	extind += strlen(extstr) + 1;

	return posind;
}

/*
 * Dense numbers
 */

long
add_dense_no(long rfd, long index)
{
	DNR *curr_dense;
	DENSETAB *denseptr = densenos;

	while (denseptr->moredensenos) {
		denseptr = denseptr->moredensenos;
	}

	if (denseptr->num == DENSETABSIZE) {
		denseptr->moredensenos = xcalloc(1, sizeof (DENSETAB));

		denseptr = denseptr->moredensenos;
		denseptr->num = 0;
		denseptr->densenolist  = xcalloc(DENSETABSIZE, sizeof (DNR));
		denseptr->moredensenos = (DENSETAB *) 0;
	}

	curr_dense = (denseptr->densenolist) + denseptr->num;
	curr_dense->rfd = rfd;
	curr_dense->index = index;
	denseptr->num += 1;
	densind++;

	return densind - 1;
}

DNR *
get_dense_ptr(long densind)
{
	DENSETAB *denseptr = densenos;
	long densecount = denseptr->num;

	while (densecount <= densind) {
		denseptr = denseptr->moredensenos;
		densecount += denseptr->num;
	}

	return denseptr->densenolist + (denseptr->num - (densecount - densind));
}

/*
 * Symbol procedures
 */

long
get_sym_index(long ind)
{
	LSYMS *lsymlist = local_symbols + ind;
	long lsymindex = lsymlist->noofsyms;

	while (lsymlist->nextsyms != 0) {
		lsymlist = lsymlist->nextsyms;
		lsymindex += lsymlist->noofsyms;
	}

	return lsymindex;
}

SYMR *
get_sym_ptr(long ind, long symind)
{
	LSYMS *lsymlist = local_symbols + ind;
	long symcount = lsymlist->noofsyms;

	while (symcount <= symind) {
		lsymlist = lsymlist->nextsyms;
		symcount += lsymlist->noofsyms;
	}

	return lsymlist->symlist + (lsymlist->noofsyms - (symcount - symind));
}

long
add_lsym(long ind, SYMR * newsym)
{
	LSYMS *lsymlist = local_symbols + ind;
	long lsymindex = lsymlist->noofsyms;

	nosyms++;

	while (lsymlist->nextsyms != 0) {
		lsymlist = lsymlist->nextsyms;
		lsymindex += lsymlist->noofsyms;
	}

	if (lsymlist->noofsyms == SYMTABSIZE) {
		lsymlist->nextsyms = xcalloc(1, sizeof (LSYMS));
		lsymlist = lsymlist->nextsyms;
		lsymlist->symlist = xcalloc(SYMTABSIZE, sizeof (SYMR));
		lsymlist->noofsyms = 0;
		lsymlist->nextsyms = (LSYMS *) 0;
	}

	lsymlist->symlist[lsymlist->noofsyms] = (*newsym);
	lsymlist->noofsyms += 1;

	return lsymindex;
}

long
add_esym(long ind, SYMR * newsym)
{
	if (esymlist->noofsyms == SYMTABSIZE) {
		esymlist->nextsyms = xcalloc(1, sizeof (ESYMS));
		esymlist = esymlist->nextsyms;
		esymlist->symlist = xcalloc(SYMTABSIZE, sizeof (EXTR));
		esymlist->noofsyms = 0;
		esymlist->nextsyms = (ESYMS *) 0;
	}

	esymlist->symlist[esymlist->noofsyms].ifd = ind;
	esymlist->symlist[esymlist->noofsyms].asym = (*newsym);
	esymlist->noofsyms += 1;
	esymindex++;

	return esymindex - 1;
}

long
new_lsym(char *chars, long value, short symtype, short symclass, diag_type s, long filenum)
{
	SYMR newsym;
	AUXU nilaux;
	long strind, symindex;
	nilaux.isym = 0;
	symindex = get_sym_index(filenum);
	newsym.value = value;
	newsym.st = symtype;
	newsym.sc = symclass;

	switch (symtype) {
	case stEnd: {
		SYMSTR symstrind;
		long isymstart;
		symstrind = pop(blockstack + filenum);
		isymstart = symstrind.sym;

		if (symstrind.str > 0) {
			newsym.iss = symstrind.str;
		} else {
			newsym.iss = 0;
		}

		if (isymstart < 0) {
			newsym.index = (-isymstart);
			get_aux_ptr(filenum, get_sym_ptr(filenum, -isymstart)->index)->isym =
			symindex + 1;
		} else {
			get_sym_ptr(filenum, isymstart)->index = symindex + 1;
			newsym.index = isymstart;
		}

		/* (((local_symbols + filenum)->symlist)+newsym.index)->index = symindex+1; */
		break;
	}

	case stFile:
		add_aux(nilaux, filenum);
		strind = add_to_loc_strings(chars, filenum);
		newsym.iss = strind;
		push(symindex, strind, blockstack + filenum);
		/* newsym.index filled in later by stEnd  */
		break;

	case stBlock:
		if (chars) {
			strind = add_to_loc_strings(chars, filenum);
		} else {
			strind = 0;
		}
		push(symindex, strind, blockstack + filenum);
		newsym.iss = strind;
		/* newsym.index filled in later by stEnd  */
		break;

	case stLabel: /* case stMember and enum??? */
		newsym.index = 0;
		newsym.iss = add_to_loc_strings(chars, filenum);
		break;

	case stProc: {
		DNR *procdense = get_dense_ptr(value);

		strind = add_to_loc_strings(chars, filenum);
		newsym.value = 0;	/* not needed now */

		/* add esym but with lsymindex as index not aux or isymMac */
		newsym.iss = add_to_ext_strings(chars);
		newsym.index = symindex;
		procdense->rfd = 0x7fffffff;
		procdense->index = add_esym(filenum, &newsym);
		newsym.iss = strind;
		newsym.index = add_aux(nilaux, filenum);
		push(-symindex, strind, blockstack + filenum);

		/* AUX to be filled in at stEnd */
		add_proc(symindex, filenum);	/* all are scText */
		add_aux(nilaux, filenum);	/* add nil type !! */
		break;
	}

	case stStaticProc: {
		DNR *procdense = get_dense_ptr(value);

		strind = add_to_loc_strings(chars, filenum);
		newsym.iss = strind;
		newsym.value = 0;	/* not needed now */

		/* add esym but with lsymindex as index not aux or isymMac */
		procdense->rfd = filenum;
		procdense->index = symindex;
		newsym.index = add_aux(nilaux, filenum);
		push(-symindex, strind, blockstack + filenum);
		add_proc(symindex, filenum);
		add_aux(nilaux, filenum);	/* add nil type !! */
		break;
	}

	default:
		if (diag == DIAG_NONE) {
			newsym.index = 1048575;
			newsym.iss = add_to_loc_strings(chars, filenum);
		} else {
			newsym.iss = add_to_loc_strings(chars, filenum);
			newsym.index = add_type_to_aux(s, filenum);
		}
		break;
	}

	return add_lsym(filenum, &newsym);
}

long
new_lsym_d(char *str, long value, short symtype, short symclass, diag_type s, long filenum)
{
	return add_dense_no(filenum, new_lsym(str, value, symtype, symclass, s, filenum));
}

long
new_esym(char *str, long value, short symtype, short symclass, diag_type s, long filenum)
{
	SYMR newsym;
	long strind = add_to_ext_strings(str);

	newsym.iss = strind;
	newsym.value = value;
	newsym.st = symtype;
	newsym.reserved = 0;
	newsym.sc = symclass;

	if ((symtype == stProc && (symclass == scNil || symclass == scUndefined)) || diag == DIAG_NONE) {
		/* no diagnostics  */
		newsym.index = 1048575;
		newsym.value = 0;
	} else {
		newsym.index = add_type_to_aux(s, filenum);
	}

	return add_esym(filenum, &newsym);
}

long
new_esym_d(char *str, long value, short symtype, short symclass, diag_type s, long filenum)
{
	return add_dense_no(0x7fffffff, new_esym(str, value, symtype, symclass, s, filenum));
}

/*
 * Auxillary information
 */
AUXU *
get_aux_ptr(long index, long auxind)
{
	AUXTAB *auxdata;
	long auxcount;

	auxdata  = aux_symbols + index;
	auxcount = auxdata->num;

	while (auxcount < auxind) {
		auxdata = auxdata->moreaux;
		auxcount += auxdata->num;
	}

	return auxdata->auxinfo + (auxdata->num - (auxcount - auxind));
}

long
add_aux(AUXU auxent, long index)
{
	AUXTAB *auxdata;
	long auxind;

	noaux++;
	auxdata = aux_symbols + index;
	auxind = auxdata->num;

	while (auxdata->moreaux != 0) {
		auxdata = auxdata->moreaux;
		auxind += auxdata->num;
	}

	if (auxdata->num == AUXTABSIZE) {
		auxdata->moreaux = xcalloc(1, sizeof (AUXTAB));

		auxdata = auxdata->moreaux;
		auxdata->auxinfo = xcalloc(AUXTABSIZE, sizeof (AUXU));
		auxdata->moreaux = (AUXTAB *) 0;
		auxdata->num = 0;
	}

	auxdata->auxinfo[auxdata->num] = auxent;

	auxdata->num += 1;
	auxind++;

	return auxind - 1;
}

long
add_st_aux(long ind)
{
	AUXU straux;
	AUXU maxaux;
	long indaux;

	maxaux.count = 0xffffffff;
	straux.ti.bt = btStruct;
	indaux = add_aux(straux, ind);

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

	maxaux.count = 0xffffffff;
	uniaux.ti.bt = btUnion;
	indaux = add_aux(uniaux, ind);

	add_aux(maxaux, ind);
	add_aux(maxaux, ind);

	return indaux;
}

void
output_symtab(char *symfilename)
{
	int i;

	for (i = 0; i < numfiles; i++) {	/* might need the iss */
		new_lsym("", 0, stEnd, scText, (diag_type) 0, i);
	}

	makesymtab(external_strings, external_symbols, dense_numbers,
		file_desc_table, numfiles, symfilename, esymindex, nosyms,
		extind, stringsize, noaux, densind, proc_isym_inds, numprocs);
}

