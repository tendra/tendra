/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 112 "syntax.act"


	/* $Id$ */

	/*
	 * Copyright 2011, The TenDRA Project.
	 * Copyright 1997, United Kingdom Secretary of State for Defence.
	 *
	 * See doc/copyright/ for the full copyright terms.
	 */

	#ifndef SYNTAX_INCLUDED
	#define SYNTAX_INCLUDED

	#include <adt/zone.h>

	extern char *token_prefix;
	typedef struct zone * zoneP;

#line 33 "syntax.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_lex(zoneP);

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lex_arg_Hnb_Hof_Hchars (32)
#define lex_sid_Hident (1)
#define lex_arg_Hchar_Hnb (31)
#define lex_keyword (7)
#define lex_arg_Hreturn (33)
#define lex_range (24)
#define lex_comma (27)
#define lex_action_Hkw (35)
#define lex_digit (5)
#define lex_unknown (29)
#define lex_ident (0)
#define lex_close (14)
#define lex_string (2)
#define lex_equal (19)
#define lex_colon (22)
#define lex_range_Hclosed_Hopen (26)
#define lex_token (9)
#define lex_white (10)
#define lex_lower (4)
#define lex_arrow (17)
#define lex_upper (3)
#define lex_group (6)
#define lex_nothing_Hmarker (28)
#define lex_open (13)
#define lex_begin_Haction (36)
#define lex_eof (18)
#define lex_zone (12)
#define lex_ref (23)
#define lex_plus (20)
#define lex_close_Hbrace (16)
#define lex_semicolon (21)
#define lex_arg_Hchar_Hstring (30)
#define lex_type_Hkw (38)
#define lex_open_Hbrace (15)
#define lex_range_Hclosed_Hclosed (25)
#define lex_end_Haction (37)
#define lex_default (11)
#define lex_mapping (8)
#define lex_arg_Hignore (34)

/* BEGINNING OF TRAILER */

#line 764 "syntax.act"

	#endif
#line 86 "syntax.h"

/* END OF FILE */
