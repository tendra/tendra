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
 * $Id:
 */

#include "lctlex.h"
#include "lctsyntax.h"
#include <stdio.h>
#include "error.h"

int crt_lct_token ;
int saved_lct_token ;

char saved_lct_letter ;

lct_parse_tree global_lct_parse_tree ;

static char lct_token_buff [2000];
static char *lct_token_end = lct_token_buff + sizeof(lct_token_buff);

static FILE* lct_file;
struct lexi_lct_state lct_lexer_state;

static void
assign_lct_letter(int c)
{
	saved_lct_letter = c ;
}


static int 
lexi_lct_getchar() 
{
	int c =fgetc(lct_file);
	if(c == '\n') 
		crt_line_no++;
	if(c == EOF) 
		return LEXI_EOF;
	return c;
}


static int
get_lct_identifier(int a)
{
 	int c = a;
	char *t = lct_token_buff;
	do {
		*(t++) = (char)c;
		if (t == lct_token_end)
			error(ERROR_FATAL, "Buffer overflow");
		c = lexi_lct_readchar(&lct_lexer_state);
        } while(lexi_lct_group(lexi_lct_group_alphanum, c)) ;
	*t = 0;
	lexi_lct_push(&lct_lexer_state, c);

    /* Deal with keywords */
	return lexi_lct_keyword(lct_token_buff, lct_lex_identifier);
}


#include "lctlexer.c"

void 
init_lct_parse_tree (lct_parse_tree* a) 
{
	init_mytmpstring(&(a->hfileheader)) ;
	init_mytmpstring(&(a->cfileheader)) ;
	init_mytmpstring(&(a->hfiletrailer)) ;
	init_mytmpstring(&(a->cfiletrailer)) ;
}

void 
process_lctfile (char* fn) 
{

	crt_line_no = 1 ;
	if (!(lct_file=fopen(fn,"r"))) {
		error(ERROR_SERIOUS, "Can't open input file, '%s'", fn);
		return; /*error message*/
	}
	crt_file_name = fn;
	init_lct_parse_tree(&global_lct_parse_tree) ;
	lexi_lct_init(&lct_lexer_state) ;
	ADVANCE_LCT_LEXER ;

	read_lct_unit();
	fclose(lct_file);
}

void 
init_mytmpstring (mytmpstring* s) {
	s->length=0;
}

int
append_to_string (mytmpstring* s, char c) 
{
	if(s->length<2000) {
		(s->str)[(s->length)++]=c;
		return 0;
	}
	else 
		return 1;
}

