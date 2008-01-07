/*
 * Automatically generated from the files:
 *	./c-parser.sid
 * and
 *	./c-parser.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */


/*
 * Copyright (c) 2003-2004, The Tendra Project <http://www.ten15.org/>
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
 *  		 Crown Copyright (c) 1997
 *
 *  This TenDRA(r) Computer Program is subject to Copyright
 *  owned by the United Kingdom Secretary of State for Defence
 *  acting through the Defence Evaluation and Research Agency
 *  (DERA).  It is made available to Recipients with a
 *  royalty-free licence for its use, reproduction, transfer
 *  to other parties and amendment for any purpose not excluding
 *  product development provided that any such use et cetera
 *  shall be deemed to be acceptance of the following conditions:-
 *
 *      (1) Its Recipients shall ensure that this Notice is
 *      reproduced upon any copies or amended versions of it;
 *
 *      (2) Any amended version of it shall be clearly marked to
 *      show both the nature of and the organisation responsible
 *      for the relevant amendment or amendments;
 *
 *      (3) Its onward transfer from a recipient to another
 *      party shall be deemed to be that party's acceptance of
 *      these conditions;
 *
 *      (4) DERA gives no warranty or assurance as to its
 *      quality or suitability for any purpose and DERA accepts
 *      no liability whatsoever in relation to any use to which
 *      it may be put.
 *
 * $TenDRA$
 */


#ifndef H_C_PARSER
#define H_C_PARSER

#include "config.h"
#include "c-lexer.h"
#include "c-out-info.h"
#include "table.h"


extern CLexerStreamP	c_current_stream;
extern COutputInfoP	c_current_out_info;
extern TableP		c_current_table;


/* BEGINNING OF FUNCTION DECLARATIONS */

extern void c_parse_grammar (void);

/* BEGINNING OF TERMINAL DEFINITIONS */

#define CP_open_Htuple (18)
#define CP_sid_Hidentifier (8)
#define CP_code (16)
#define CP_blt_Hmaps (1)
#define CP_blt_Hassignments (2)
#define CP_arrow (17)
#define CP_reference (21)
#define CP_begin_Haction (13)
#define CP_c_Hidentifier (9)
#define CP_eof (22)
#define CP_blt_Hparam_Hassign (20)
#define CP_blt_Hterminals (3)
#define CP_blt_Hresult_Hassign (7)
#define CP_terminator (12)
#define CP_separator (10)
#define CP_blt_Hprefixes (0)
#define CP_blt_Hheader (4)
#define CP_blt_Hactions (5)
#define CP_end_Haction (15)
#define CP_blt_Htrailer (6)
#define CP_define (14)
#define CP_typemark (11)
#define CP_close_Htuple (19)

/* BEGINNING OF TRAILER */



#endif /* !defined (H_C_PARSER) */


/* END OF FILE */
