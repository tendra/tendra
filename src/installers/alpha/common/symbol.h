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


/* 	$Id: symbol.h,v 1.1.1.1 1998/01/17 15:56:00 release Exp $	 */

/*
$Log: symbol.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/23  10:39:31  john
 * Entered into CVS
 *
 * Revision 1.3  1995/01/31  14:27:39  john
 * Minor change
 *
*/

#include "common_types.h"

void init_table_space PROTO_S ((int, int));
    /* parameters - number of files to be translated and total number of
       procedures. Sets up tables for symbol table etc storage	*/

int get_sym_index PROTO_S ((int));
    /* returns the index into the symbol table for the given file	*/

int add_dense_no PROTO_S ((int, int));
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


int new_lsym PROTO_S ((char *,int,int,int,diag_type,int));
/* adds symbol to local symbol table */

int new_lsym_d PROTO_S ((char *,int,int,int,diag_type,int));
/* adds symbol to local symbol table and returns its dense number */

int new_esym PROTO_S ((char *,int,int,int,diag_type,int));
/* adds symbol to external symbol table */

int new_esym_d PROTO_S ((char *,int,int,int,diag_type,int));
/* adds symbol to external symbol table and returns its dense number */


/* procedure to make the symbol table file given its name */

void output_symtab PROTO_S ((char*));



