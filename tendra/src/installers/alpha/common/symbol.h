/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
*/


/* 	$Id$	 */

/**/

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

short symtype ... symbol type as given in archsyms.h

short symclass ... symbol class as given in archsyms.h

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



