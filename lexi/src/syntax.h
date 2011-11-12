/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	/Users/kate/svn/tendra1/obj-regen/bin/sid
 */
/* BEGINNING OF HEADER */

#line 176 "syntax.act"


#ifndef SYNTAX_INCLUDED
#define SYNTAX_INCLUDED

#include "adt/zone.h"

extern char *token_prefix ;
typedef zone* zoneP;

#line 53 "syntax.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_lex(zoneP);

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lex_arg_Hnb_Hof_Hchars (33)
#define lex_arg_Hchar_Hnb (32)
#define lex_keyword (8)
#define lex_range (25)
#define lex_comma (28)
#define lex_action_Hkw (36)
#define lex_digit (5)
#define lex_unknown (30)
#define lex_close (15)
#define lex_sid_Hidentifier (1)
#define lex_string (2)
#define lex_equal (20)
#define lex_colon (23)
#define lex_arg_Hreturn_Hterminal (34)
#define lex_range_Hclosed_Hopen (27)
#define lex_token (10)
#define lex_white (11)
#define lex_identifier (0)
#define lex_lower (4)
#define lex_arrow (18)
#define lex_upper (3)
#define lex_group (7)
#define lex_nothing_Hmarker (29)
#define lex_open (14)
#define lex_reference (24)
#define lex_begin_Haction (37)
#define lex_eof (19)
#define lex_zone (13)
#define lex_plus (21)
#define lex_close_Hbrace (17)
#define lex_semicolon (22)
#define lex_arg_Hchar_Hstring (31)
#define lex_type_Hkw (39)
#define lex_copyright (6)
#define lex_open_Hbrace (16)
#define lex_range_Hclosed_Hclosed (26)
#define lex_end_Haction (38)
#define lex_default (12)
#define lex_mapping (9)
#define lex_arg_Hignore (35)

/* BEGINNING OF TRAILER */

#line 974 "syntax.act"

#endif
#line 107 "syntax.h"

/* END OF FILE */
