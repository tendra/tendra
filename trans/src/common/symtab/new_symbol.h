/*
 * Copyright 2002-2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SYMTAB_NEWSYMBOL_H
#define SYMTAB_NEWSYMBOL_H

#include <construct/installtypes.h>

/*
 * Parameters - number of files to be translated and total number of
 * procedures. Sets up tables for symbol table etc storage.
 */
void init_table_space(long, long);

/*
 * Returns the index into the symbol table for the given file
 */
long get_sym_index(long);

/*
 * Returns a dense number (index into dense number table) corresponding
 * to the parameters filenum and symbol table index.
 */
long add_dense_no(long, long);

/*
 * The following four procedures take parameters:
 *
 *   char *string   - identifier of symbol
 *   long value     - value required in symbol table
 *   short symtype  - symbol type as given in sym.h
 *   short symclass - symbol class as given in sym.h
 *
 * type s ... typeof the symbol (except for stFile, stEnd etc) - This is
 * converted to an AUXU which is added to the auxillary table. Structs and
 * unions must correspond to a type previously entered in the symbol table
 * which can be found by find_aux. Bitfields are negative shapes with
 * size = abs and btUInt in auxillary table. For a symtype stProc or
 * stStaticProc this shape should be the return type.
 *
 *   long filenum - index for the file
 */

/* adds symbol to local symbol table */
long new_lsym(char *, long, short, short, diag_type, long);

/* adds symbol to local symbol table and returns its dense number */
long new_lsym_d(char *, long, short, short, diag_type, long);

/* adds symbol to external symbol table */
long new_esym(char *, long, short, short, diag_type, long);

/* adds symbol to external symbol table and returns its dense number */
long new_esym_d(char *, long, short, short, diag_type, long);

extern long add_lsym(long, SYMR *);
extern long add_string(char*, STRINGS *);
extern long add_st_aux(long);
extern long add_to_ext_strings(char *);
extern long add_to_loc_strings(char *, int);
extern long add_un_aux(long);
extern void add_proc(long, long);

/*
 * Auxillary information
 */
extern AUXU * get_aux_ptr(long, long);
extern DNR * get_dense_ptr(long);
extern long add_esym(long, SYMR*);
extern SYMR * get_sym_ptr(long, long);

/*
 * Returns index into auxillary table after adding the AUXU to the table
 * for the file number parameter.
 */
extern long add_aux(AUXU, long);

/*
 * Procedure to make the symbol table file given its name.
 */
void output_symtab(FILE *);

#endif

