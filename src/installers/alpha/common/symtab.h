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


/* 	$Id: symtab.h,v 1.2 1998/02/04 10:43:33 release Exp $	 */

/*  S Y M B O L   T A B L E   P R O D U C T I O N   

by R. R. Rowlingson

Type definitions for the MIPS TDF translator to produce a .T , file (symbol table) suitable for as1.

*/

#include "cross_config.h"
#ifndef CROSS_INCLUDE
#include <sym.h>
#else
#include CROSS_INCLUDE/sym.h>
#endif

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





