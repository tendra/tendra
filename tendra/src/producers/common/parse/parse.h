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
 *    		 Crown Copyright (c) 1997, 1998
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


#ifndef PARSE_INCLUDED
#define PARSE_INCLUDED


/*
 *    TYPE REPRESENTING A PARSER STATE
 *
 *    This type is used to represent the information to be saved before the
 *    separate compilation of any saved preprocessing tokens and restored
 *    afterwards.
 */

typedef struct pstate_tag {
	LOCATION loc;
	OPTIONS *opts;
	int flag [10];
	DECL_SPEC dspec [2];
	NAMESPACE nspace [2];
	STACK (NAMESPACE) nstack [3];
} PARSE_STATE;


/*
 *    TOKEN EXPANSION STATES
 *
 *    These values are used as arguments to expand_token to indicate the
 *    current parsing state.
 */

#define EXPAND_NORMAL			0
#define EXPAND_AHEAD			1
#define EXPAND_RESCAN			2
#define EXPAND_TEMPLATE			3
#define EXPAND_IDENTIFIER		4
#define EXPAND_COLON_COLON		5
#define EXPAND_CHECK_COLON		6
#define EXPAND_DESTRUCTOR		7
#define EXPAND_STRING			8


/*
 *    TOKEN PARSER DECLARATIONS
 *
 *    The routines in this module are concerned with reading the next lexical
 *    token from the input file.  They include expand_token which is the top
 *    level lexical analysis and preprocessing routine.
 */

extern void init_parser(PPTOKEN *);
extern int expand_token(int);
extern int expand_preproc(int);
extern void rescan_template(NAMESPACE);
extern PPTOKEN *patch_tokens(int);
extern PPTOKEN *restore_parser(void);
extern PPTOKEN *read_loc_tokens(PPTOKEN *);
extern void snip_tokens(PPTOKEN *, PPTOKEN *);
extern void save_state(PARSE_STATE *, int);
extern void restore_state(PARSE_STATE *);
extern int crt_state_depth;


/*
 *    CURRENT TOKEN INFORMATION
 *
 *    These variables are used to store information about the current lexical
 *    token as read by expand_token.  crt_lex_token gives the current token
 *    number, with any additional information being stored in crt_token.
 *    last_lex_token gives the previous value of crt_lex_token.  Finally
 *    saved_lex_token is used as a temporary store in exception handling.
 */

extern PPTOKEN *crt_token;
extern NAMESPACE crt_lookup;
extern int crt_lex_token;
extern int saved_lex_token;
extern int last_lex_token;
extern int have_syntax_error;


/*
 *    PARSER MACROS
 *
 *    These macros are used by the SID parser to access the output of the
 *    lexical analysis and preprocessing routines.  CURRENT_TERMINAL gives
 *    the value of the current lexical token.  ADVANCE_LEXER reads the next
 *    lexical token.  RESCAN_LEXER rescans the current token.  SAVE_LEXER
 *    and RESTORE_LEXER are used in exception handling.
 */

#define CURRENT_TERMINAL	crt_lex_token
#define RESTORE_LEXER		crt_lex_token = saved_lex_token;
#define next_token()		expand_token (EXPAND_AHEAD)
#define RESCAN_LEXER		crt_lex_token = expand_token (EXPAND_RESCAN)

#define ADVANCE_LEXER\
	{\
	last_lex_token = crt_lex_token;\
	crt_lex_token = expand_token (EXPAND_NORMAL);\
	}


#define SAVE_LEXER(T)\
	{\
	saved_lex_token = crt_lex_token;\
	crt_lex_token = (T);\
	}


#endif
