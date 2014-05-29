/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdint.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <main/flags.h>

/*
 * Type definitions for translator produced debugging information to be
 * incorporated into a .T file
 */

#include <symtab/cross_config.h>
#include <symtab/symtab.h>
#include <symtab/makesymtab.h>
#include <symtab/symconst.h>

long
count_syms(LSYMS *symlist)
{
	long symindex = symlist->noofsyms;

	while (symlist->nextsyms != 0) {
		symlist = symlist->nextsyms;
		symindex += symlist->noofsyms;
	}

	return symindex;
}

long
count_strings(STRINGS *list)
{
	long stringind;

	stringind = list->usage;
	while (list->overspill != 0) {
		list = list->overspill;
		stringind += list->usage;
	}

	return stringind;
}

long
count_aux(AUXTAB *auxdata)
{
	long auxcount;

	auxcount = auxdata->num;
	while (auxdata->moreaux != 0){
		auxdata = auxdata->moreaux;
		auxcount += auxdata->num;
	}

	return auxcount;
}

#define MAJOR_ASSEMBLER_VERSION 3
#define MINOR_ASSEMBLER_VERSION 11

/*
 * Function to make a symbol table from various components
 * supplied by the translator, including TDF diagnostics.
 *
 * Sets up a .T file for use by as1 (this function is called from new_symbol.c
 * using output_symtab().)
 *
 * The output file and the binary assembler file (.G, made by
 * as0 on a *.s file) can then be passed to as1
 */
void
makesymtab(STRINGS *extstrings, ESYMS *extsymbols, DENSETAB *densenos,
	pSYMFDR filedescs, int numfiles, FILE *f,
	int noextsyms, int nosyms, int extstringsize,
	int stringsize, int noaux, int densind,
	PROCSYM *procinds, int noprocs)
{
	LSYMS *symlist;

	HDRR symhdrout; /* symbolic header */
	FDR fdrtab;
	PDR *pdr_ptr;
	STRINGS *tempstrings;
	AUXTAB *auxdata;
	pSYMFDR tempfileptr;
	int i, j;

	long stroff  = 0;
	long symoff  = 0;
	long procoff = 0;
	long auxoff  = 0;

	/*
	 * Set up new symbolic header
	 */

	symhdrout.magic  = magicSym;	/* defined in symconst.h */
	symhdrout.vstamp = MAJOR_ASSEMBLER_VERSION * 256 + MINOR_ASSEMBLER_VERSION;

	symhdrout.ilineMax      = 0;
	symhdrout.cbLine        = 0;
	symhdrout.cbLineOffset  = 0;
	symhdrout.ipdMax        = noprocs;
	symhdrout.cbPdOffset    = (long) sizeof (HDRR);
	symhdrout.isymMax       = nosyms;
	symhdrout.cbSymOffset   = symhdrout.cbPdOffset + noprocs*sizeof(PDR);
	symhdrout.ioptMax       = 0;
	symhdrout.cbOptOffset   = 0;
	symhdrout.iauxMax       = noaux;
	symhdrout.cbAuxOffset   = symhdrout.cbSymOffset + nosyms*sizeof(SYMR);
	symhdrout.issMax        = stringsize;
	symhdrout.cbSsOffset    = symhdrout.cbAuxOffset + noaux*sizeof(AUXU);
	symhdrout.issExtMax     = extstringsize;
	symhdrout.cbSsExtOffset = symhdrout.cbSsOffset  + stringsize;
	symhdrout.ifdMax        = numfiles;
	symhdrout.cbFdOffset    = symhdrout.cbSsExtOffset + extstringsize;
	symhdrout.crfd          = 0;
	symhdrout.cbRfdOffset   = 0;	/* something may need to be done here */
	symhdrout.iextMax       = noextsyms;
	symhdrout.cbExtOffset   = symhdrout.cbFdOffset + symhdrout.ifdMax*sizeof(FDR);

	/* Dense numbers */
	symhdrout.idnMax     = densind;
	symhdrout.cbDnOffset = symhdrout.cbExtOffset + symhdrout.iextMax*sizeof(EXTR);

	/* write header to output file */
	fwrite(&symhdrout, sizeof (HDRR), 1, f);

	/*
	 * Write the tables to the file
	 */

	tempfileptr = filedescs;

	/* Initialise proc info */
	pdr_ptr = (PDR *) xcalloc(1, sizeof (PDR));
	for (j = 0; j < numfiles; j++) {
		PROCSYM *procindptr = procinds;
		for (i = 1; i <= noprocs; i++, procindptr++) {
			if (procindptr->fnum == j) {
				pdr_ptr->isym = procindptr->procsymindex;
				fwrite(pdr_ptr, sizeof(PDR), 1, f);
			}
		}
	}

	/* Write local symbols */
	for (i = 1; i <= numfiles; i++, tempfileptr++) {
		symlist = tempfileptr->symbols;
		while (symlist) {
			fwrite(symlist->symlist, sizeof (SYMR), symlist->noofsyms, f);
			symlist = symlist->nextsyms;
		}
	}

	/* Write auxillary symbol entries */
	tempfileptr = filedescs;
	for (i = 1; i <= numfiles; i++, tempfileptr++) {
		auxdata = tempfileptr->auxtabs;
		while (auxdata) {
			fwrite(auxdata->auxinfo, sizeof (AUXU), auxdata->num, f);
			auxdata = auxdata->moreaux;
		}
	}

	/* Write local strings */
	tempfileptr = filedescs;
	for (i = 1; i <= numfiles; i++, tempfileptr++) {
		tempstrings = tempfileptr->filestr;
		while (tempstrings) {
			fwrite(tempstrings->str, sizeof (char), tempstrings->usage, f);
			tempstrings = tempstrings->overspill;
		}
	}

	/* Write external strings */
	tempstrings = extstrings;
	while (tempstrings) {
		fwrite(tempstrings->str, sizeof (char), tempstrings->usage, f);
		tempstrings = tempstrings->overspill;
	}

	/* Write file descriptors */
	tempfileptr = filedescs;
	for (i = 1; i <= numfiles; i++, tempfileptr++) {
		long count;

		fdrtab.adr = 0;
		fdrtab.rss = 1; /* source file name at start of lsymbols */
		fdrtab.issBase = stroff;

		count = count_strings(tempfileptr->filestr);
		stroff += count;

		fdrtab.cbSs = count;
		count = count_syms(tempfileptr->symbols);

		fdrtab.isymBase = symoff;
		symoff += count;

		fdrtab.csym      = count;
		fdrtab.ilineBase = 0;
		fdrtab.cline     = 0;
		fdrtab.ioptBase  = 0;
		fdrtab.copt      = 0;
		fdrtab.ipdFirst  = procoff;

		procoff += tempfileptr->proc_count;
		fdrtab.cpd = tempfileptr->proc_count;
		fdrtab.iauxBase = auxoff;
		count = count_aux(tempfileptr->auxtabs);
		auxoff += count;

		fdrtab.caux         = count;
		fdrtab.rfdBase      = 0;
		fdrtab.crfd         = 0;
		fdrtab.lang         = langC; /* C ,see symconst.h  */
		fdrtab.fMerge       = 0;     /* 1 for .h files I think */
		fdrtab.fReadin      = 0;
		fdrtab.fBigendian   = 0;
		fdrtab.glevel       = diag != DIAG_NONE ? GLEVEL_2 : GLEVEL_0;
		fdrtab.reserved     = 0; /* what else ! */
		fdrtab.cbLineOffset = 0; /* ??? */
		fdrtab.cbLine       = 0; /* ??? */

		fwrite(&fdrtab, sizeof (FDR), 1, f);
	}

	/*
	 * Appears to write the right stuff so is it the right place?
	 */

	/* Write external symbols */
	while (extsymbols) {
		fwrite(extsymbols->symlist, sizeof (EXTR), extsymbols->noofsyms, f);
		extsymbols = extsymbols->nextsyms;
	}

	/* Write dense nos */
	while (densenos) {
		fwrite(densenos->densenolist, sizeof (DNR), densenos->num, f);
		densenos = densenos->moredensenos;
	}
}

