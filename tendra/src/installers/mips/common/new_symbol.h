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
$Date: 1998/02/04 10:43:44 $
$Revision: 1.2 $
$Log: new_symbol.h,v $
 * Revision 1.2  1998/02/04  10:43:44  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/08/16  15:45:41  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
#include "common_types.h"

extern void init_table_space PROTO_S (( long, long ));
/* parameters - number of files to be translated and total number of procedures. Sets up tables for symbol table etc storage	*/

extern long get_sym_index PROTO_S (( long ));
/* returns the index into the symbol table for the given file	*/

extern long add_dense_no PROTO_S (( long, long ));
/* returns a dense number (index into dense number table) corresponding to the parameters filenum and symbol table index */

extern long add_aux PROTO_S (( AUXU, long ));
/* returns index into auxillary table after adding the AUXU to the table for the file number parameter */

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


extern long new_lsym PROTO_S (( char*, long, short, short, diag_type, long ));
/* adds symbol to local symbol table */

extern long new_lsym_d PROTO_S (( char*, long, short, short, diag_type, long ));
/* adds symbol to local symbol table and returns its dense number */

extern long new_esym PROTO_S (( char*, long v, short, short, diag_type, long ));
/* adds symbol to external symbol table */

extern long new_esym_d PROTO_S (( char*, long, short, short, diag_type, long ));
/* adds symbol to external symbol table and returns its dense number */


extern void output_symtab PROTO_S (( char* ));
/* procedure to make the symbol table file given its name */


extern long add_lsym PROTO_S (( long, SYMR* ));
extern long add_string PROTO_S (( char*, STRINGS* ));
extern long add_st_aux PROTO_S (( long ));
extern long add_to_ext_strings PROTO_S (( char* ));
extern long add_to_loc_strings PROTO_S (( char*, int ));
extern long add_un_aux PROTO_S (( long ));
extern void add_proc PROTO_S (( long, long ));

extern AUXU* get_aux_ptr PROTO_S ((long, long));
extern DNR* get_dense_ptr PROTO_S (( long ));
extern long add_esym PROTO_S (( long, SYMR* ));
extern SYMR* get_sym_ptr PROTO_S (( long, long ));
