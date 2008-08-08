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

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "error/error.h"
#include "xalloc/xalloc.h"

#include "lex.h"
#include "lexer.h"
#include "syntax.h"


/*
    INPUT FILE

    This is the file from which the lexical routine read their input.
*/

static FILE *lex_input;


/*
    MAPPINGS AND DECLARATIONS FOR AUTOMATICALLY GENERATED SECTION

    These macros give the mappings between the actions used in the
    automatically generated lexical analyser and the routines defined
    in this file.
*/

static int lexi_getchar(void);

#define lexi_unknown_token	lex_unknown

static int read_arg_char_nb(int) ;

/*
    AUTOMATICALLY GENERATED SECTION

    The main body of the lexical analyser is automatically generated.
*/

struct lexi_state lexer_state;
#include "lexer.c"


/*
    GET THE NEXT CHARACTER

    This routine reads the next character, either from the pending buffer
    or from the input file.
*/

static int
lexi_getchar(void)
{
    int c;
    c = fgetc(lex_input);
    if (c == '\n')crt_line_no++;
    if (c == EOF) return LEXI_EOF;
    c &= 0xff;
    return c;
}


/*
    TOKEN BUFFER

    This buffer is used by read_token to hold the values of identifiers
    and strings.
*/

char token_buff [2000];
char *token_end = token_buff + sizeof(token_buff);
unsigned int number_buffer;

/*
    CURRENT TOKEN

    These variables are used by the parser to hold the current and former
    lexical tokens.
*/

int crt_lex_token;
int saved_lex_token;


/*
    PROCESS FILE

    This routine processes the input file nm.
*/

void
process_file(char *nm,lexer_parse_tree* top_level)
{
    crt_line_no = 1;
    if (nm == NULL || !strcmp(nm, "-")) {
	crt_file_name = "<stdin>";
	lex_input = stdin;
	nm = NULL;
    } else {
	crt_file_name = nm;
	lex_input = fopen(nm, "r");
	if (lex_input == NULL) {
	    error(ERROR_SERIOUS, "Can't open input file, '%s'", nm);
	    return;
	}
    }
	lexi_init(&lexer_state);
    ADVANCE_LXI_LEXER;
    read_lex(top_level->global_zone);
    if (nm)fclose(lex_input);
    return;
}
