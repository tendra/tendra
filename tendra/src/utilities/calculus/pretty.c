/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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


#define calculus_IO_ROUTINES
#include "config.h"
#include "calculus.h"
#include "common.h"
#include "error.h"
#include "pretty.h"


/*
 *    AUTOMATICALLY GENERATED PRETTY PRINTING ROUTINES
 *
 *    The main pretty printing routines are automatically generated.  The
 *    various macros are used to customise these routines.
 */

#define OUTPUT_int(A, B)	fprintf_v ((A), "%d", (B))
#define OUTPUT_number(A, B)	fprintf_v ((A), "%lu", (B))
#define OUTPUT_string(A, B)	fprintf_v ((A), "\"%s\"", (B))

#ifndef DEBUG
#define BAD_PRINT_OP				0
#define PRINT_alg(A, B, C, D)			ASSERT (BAD_PRINT_OP)
#define PRINT_list_ptr_en(A, B, C, D)		ASSERT (BAD_PRINT_OP)
#define PRINT_list_ptr_ident(A, B, C, D)	ASSERT (BAD_PRINT_OP)
#define PRINT_list_ptr_prim(A, B, C, D)	ASSERT (BAD_PRINT_OP)
#define PRINT_list_ptr_str(A, B, C, D)	ASSERT (BAD_PRINT_OP)
#define PRINT_list_ptr_un(A, B, C, D)		ASSERT (BAD_PRINT_OP)
#define PRINT_ptr_int(A, B, C, D)		ASSERT (BAD_PRINT_OP)
#define PRINT_ptr_number(A, B, C, D)		ASSERT (BAD_PRINT_OP)
#define PRINT_ptr_ptr_cid(A, B, C, D)		ASSERT (BAD_PRINT_OP)
#define PRINT_ptr_ptr_type(A, B, C, D)	ASSERT (BAD_PRINT_OP)
#define PRINT_ptr_string(A, B, C, D)		ASSERT (BAD_PRINT_OP)
#endif

#include "print_def.h"


/*
 *    PRETTY PRINT AN ALGEBRA
 *
 *    This routine pretty prints the entire algebra type list into the
 *    file named nm.
 */

void
pretty_file(char *nm)
{
    int old_indent_step;
    int old_ptr_depth;
    int old_list_expand;
	
    /* Open file */
    FILE *f;
    if (streq (nm, ".")) {
		f = stdout;
    } else {
		f = fopen (nm, "w");
		if (f == NULL) {
			error (ERROR_SERIOUS, "Can't open output file, '%s'", nm);
			return;
		}
    }
	
    /* Save values */
    old_indent_step = print_indent_step;
    old_ptr_depth = print_ptr_depth;
    old_list_expand = print_list_expand;
    print_indent_step = 2;
    print_ptr_depth = 10000;
    print_list_expand = 1;
	
    /* Print the algebra */
    PRINT_string (f, algebra->name, "name", 0);
    PRINT_int (f, algebra->major_no, "major_no", 0);
    PRINT_int (f, algebra->minor_no, "minor_no", 0);
    fputc_v ('\n', f);
    PRINT_list_ptr_type (f, algebra->types, "types", 0);
	
    /* Restore values */
    clear_calculus_alias ();
    print_indent_step = old_indent_step;
    print_ptr_depth = old_ptr_depth;
    print_list_expand = old_list_expand;
	
    /* Close file */
    if (f != stdout) fclose_v (f);
    return;
}
