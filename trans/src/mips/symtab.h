/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*  S Y M B O L   T A B L E   P R O D U C T I O N   

by R. R. Rowlingson

Type definitions for the MIPS TDF translator to produce a .T , file (symbol table) suitable for as1.

*/

#include "cross_config.h"

#include "sym.h"

/********************************************************************
The following types store the symbolic information for each table
in the .T file. They consist of a count of the number of elements
(num,noofsyms) or size (usage) in the case of strings. This is followed
by a pointer to a fixed number of elements of the appropriate type . The
size of this space is given by the appropriate macro at the end of this file.
Consequently, when the number of elements in the table exceeds this fixed size
a new array is set up and pointed to by the nextsyms or overspill field.
This mechanism is transparent to the caller of the symbol table routines
given in new_symbol.c
********************************************************************/

/* array of local symbols and number of entries */
typedef struct lsymsd	{long noofsyms;
			pSYMR symlist;
			struct lsymsd *nextsyms;
			} LSYMS;

/* array of external symbols, pEXTR is a pointer to a SYMR and some additional context information */
typedef struct	esymsd	{long noofsyms;
			pEXTR symlist;
			struct esymsd *nextsyms;
			} ESYMS;

/* array of strings, need one for externals and one for each file's locals */
typedef struct strings	{long usage;	/* including end of string chars */
			char* str;
			struct strings *overspill;
			} STRINGS;

/* auxillary information, each AUXU differs according to the type of the symbol */
typedef struct auxtabd	{long num;
			pAUXU auxinfo;
			struct auxtabd *moreaux;
			} AUXTAB;

/* dense numbers */
typedef struct dtab	{long num;
			pDNR densenolist;
			struct dtab *moredensenos;
			} DENSETAB;

/* file descriptors */
typedef struct	{long num;
		pFDR filelist;
		} FILETAB;

/* File description info, 1 for each file. Will be converted to FDR for the symbol table by adding indices etc */

typedef struct symfdrd	{STRINGS* filestr;
			LSYMS* symbols;
			AUXTAB* auxtabs;
			short proc_count;
			} SYMFDR, *pSYMFDR;


/* type for recording isyms and filenums for each proc */
typedef struct {long fnum;
		long procsymindex;
		} PROCSYM;

/* this macro is only used by the symbol table printer and is not a genuine
part of the installer */
#define IFAUXINFO(X) (((X>=1)&&(X<5))||(X==6)||(X==9)||(X==10)||(X==14))

/* The following are the units of space allocated for the various tables */

#define STRINGTABSIZE 500	/* for each file */
#define SYMTABSIZE 200		/*  "         "  */
#define AUXTABSIZE  200		/*  "          " */
#define DENSETABSIZE 200	/* one for all files */
