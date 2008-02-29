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

#include "exds/common.h"
#include "exds/dstring.h"
#include "lctlexer.h"
#include "char.h"

extern void process_lctfile(lexer_parse_tree*, char*);

extern int crt_lct_token ;
extern int saved_lct_token ;
extern char lct_token_buff [2000];

extern struct lexi_lct_state lct_lexer_state;

extern char saved_lct_letter ;

/* 
   This custom string will be replaced
   with nstring from eds library as as soon
   as it is extracted from 
*/

typedef struct lct_parse_tree_tag {
	int headersdefined;
	int trailersdefined;
	NStringT hfileheader;
	NStringT cfileheader;
	NStringT hfiletrailer;
	NStringT cfiletrailer;
} lct_parse_tree;

extern lct_parse_tree global_lct_parse_tree ;

extern void init_lct_parse_tree(lct_parse_tree*);

/*
     PARSER MACROS
*/

#define CURRENT_LCT_TERMINAL	crt_lct_token
#define ADVANCE_LCT_LEXER		crt_lct_token = lexi_lct_read_token(&lct_lexer_state)
#define SAVE_LCT_LEXER(T)       (saved_lct_token = crt_lct_token,\
                                  crt_lct_token = (T))
#define RESTORE_LCT_LEXER          (crt_lct_token = saved_lct_token)


