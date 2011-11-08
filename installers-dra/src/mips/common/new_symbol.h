/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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

extern void init_table_space(long, long);
/* parameters - number of files to be translated and total number of procedures. Sets up tables for symbol table etc storage	*/

extern long get_sym_index(long);
/* returns the index into the symbol table for the given file	*/

extern long add_dense_no(long, long);
/* returns a dense number (index into dense number table) corresponding to the parameters filenum and symbol table index */

extern long add_aux(AUXU, long);
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


extern long new_lsym(char*, long, short, short, diag_type, long);
/* adds symbol to local symbol table */

extern long new_lsym_d(char*, long, short, short, diag_type, long);
/* adds symbol to local symbol table and returns its dense number */

extern long new_esym(char*, long v, short, short, diag_type, long);
/* adds symbol to external symbol table */

extern long new_esym_d(char*, long, short, short, diag_type, long);
/* adds symbol to external symbol table and returns its dense number */


extern void output_symtab(char*);
/* procedure to make the symbol table file given its name */


extern long add_lsym(long, SYMR*);
extern long add_string(char*, STRINGS*);
extern long add_st_aux(long);
extern long add_to_ext_strings(char*);
extern long add_to_loc_strings(char*, int);
extern long add_un_aux(long);
extern void add_proc(long, long);

extern AUXU* get_aux_ptr(long, long);
extern DNR* get_dense_ptr(long);
extern long add_esym(long, SYMR*);
extern SYMR* get_sym_ptr(long, long);
