/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 97 "syntax.act"


	#ifndef SYNTAX_H
	#define SYNTAX_H

	#include <adt/zone.h>

	extern char *token_prefix;
	typedef struct zone * zoneP;

#line 24 "syntax.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_lex(zoneP);

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lex_kw_Hmapping (34)
#define lex_sid_Hident (1)
#define lex_arg_Hchar_Hnum (24)
#define lex_arg_Hreturn (26)
#define lex_range (17)
#define lex_comma (20)
#define lex_kw_Haction (32)
#define lex_digit (5)
#define lex_unknown (22)
#define lex_ident (0)
#define lex_close (7)
#define lex_string (2)
#define lex_equal (12)
#define lex_kw_Hkeyword (33)
#define lex_colon (15)
#define lex_range_Hclosed_Hopen (19)
#define lex_white (38)
#define lex_lower (4)
#define lex_arrow (10)
#define lex_upper (3)
#define lex_nothing_Hmarker (21)
#define lex_open (6)
#define lex_kw_Htoken (35)
#define lex_begin_Haction (28)
#define lex_eof (11)
#define lex_ref (16)
#define lex_kw_Hgroup (31)
#define lex_plus (13)
#define lex_close_Hbrace (9)
#define lex_semicolon (14)
#define lex_kw_Hzone (36)
#define lex_arg_Hchar_Hstring (23)
#define lex_kw_Htype (30)
#define lex_open_Hbrace (8)
#define lex_arg_Hchar_Hcount (25)
#define lex_range_Hclosed_Hclosed (18)
#define lex_end_Haction (29)
#define lex_default (37)
#define lex_arg_Hignore (27)

/* BEGINNING OF TRAILER */

#line 801 "syntax.act"


	#endif

#line 79 "syntax.h"

/* END OF FILE */
