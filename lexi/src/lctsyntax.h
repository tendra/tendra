/*
 * Automatically generated from the files:
 *	lctsyntax.sid
 * and
 *	lctsyntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 146 "lctsyntax.act"

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
 #ifndef LCT_SYNTAX_HEADER_INCLUDED
 #define LCT_SYNTAX_HEADER_INCLUDED

#include "ccode.h"
#include "adt.h"

#include "adt/tree.h"

typedef struct lct_parse_tree_tag {
	int headersdefined;
	int trailersdefined;
	CcodeT hfileheader;
	CcodeT cfileheader;
	CcodeT hfiletrailer;
	CcodeT cfiletrailer;
} lct_parse_tree;

extern lexer_parse_tree* lxi_top_level;
extern lct_parse_tree global_lct_parse_tree ;

extern void init_lct_parse_tree(lct_parse_tree*);
#line 66 "lctsyntax.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_lct_unit(void);

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lct_lex_lone_Hcode_Hat (14)
#define lct_lex_code_Hreference (20)
#define lct_lex_code_Hend (13)
#define lct_lex_code_Heof (16)
#define lct_lex_trailer_Hkw (1)
#define lct_lex_comma (9)
#define lct_lex_action_Hkw (3)
#define lct_lex_unknown (22)
#define lct_lex_close (11)
#define lct_lex_colon (5)
#define lct_lex_code_Hat (15)
#define lct_lex_identifier (18)
#define lct_lex_arrow (6)
#define lct_lex_open (10)
#define lct_lex_reference (4)
#define lct_lex_eof (17)
#define lct_lex_semicolon (8)
#define lct_lex_map_Hkw (2)
#define lct_lex_code_Hstring (21)
#define lct_lex_define (7)
#define lct_lex_code_Hidentifier (19)
#define lct_lex_code_Hstart (12)
#define lct_lex_header_Hkw (0)

/* BEGINNING OF TRAILER */

#line 459 "lctsyntax.act"

#endif
#line 103 "lctsyntax.h"

/* END OF FILE */
