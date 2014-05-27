/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <construct/installtypes.h>

void init_table_space(int, int);
    /* parameters - number of files to be translated and total number of
       procedures. Sets up tables for symbol table etc storage	*/

int get_sym_index(int);
    /* returns the index into the symbol table for the given file	*/

int add_dense_no(int, int);
    /* returns a dense number (index into dense number table) corresponding
       to the parameters filenum and symbol table index */

/* The following 4 procedures take parameters:-

char* string ... identifier of symbol

long value ...  value required in symbol table

short symtype ... symbol type as given in sym.h

short symclass ... symbol class as given in sym.h

type s ... typeof the symbol (except for stFile, stEnd etc) - this is
converted to an AUXU which is added to the auxillary table. Structs and
unions must correspond to a type previously entered in the symbol table
which can be found by find_aux. Bitfields are negative shapes with
size = abs and btUInt in auxillary table. For a symtype stProc or
stStaticProc this shape should be the return type.

long filenum ... index for the file
*/


int new_lsym(char *,int,int,int,diag_type,int);
/* adds symbol to local symbol table */

int new_lsym_d(char *,int,int,int,diag_type,int);
/* adds symbol to local symbol table and returns its dense number */

int new_esym(char *,int,int,int,diag_type,int);
/* adds symbol to external symbol table */

int new_esym_d(char *,int,int,int,diag_type,int);
/* adds symbol to external symbol table and returns its dense number */


/* procedure to make the symbol table file given its name */

void output_symtab(char*);

