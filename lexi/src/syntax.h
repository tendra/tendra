/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 82 "syntax.act"


	#ifndef SYNTAX_H
	#define SYNTAX_H

	#include <adt/zone.h>

	extern char *token_prefix;
	typedef struct zone * zoneP;

#line 24 "syntax.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_lex(zoneP);

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lxi_kw_Hmapping (34)
#define lxi_sid_Hident (1)
#define lxi_arg_Hchar_Hnum (24)
#define lxi_arg_Hreturn (26)
#define lxi_range (17)
#define lxi_comma (20)
#define lxi_kw_Haction (32)
#define lxi_digit (5)
#define lxi_unknown (22)
#define lxi_ident (0)
#define lxi_close (7)
#define lxi_string (2)
#define lxi_equal (12)
#define lxi_kw_Hkeyword (33)
#define lxi_colon (15)
#define lxi_range_Hclosed_Hopen (19)
#define lxi_white (38)
#define lxi_lower (4)
#define lxi_arrow (10)
#define lxi_upper (3)
#define lxi_open (6)
#define lxi_kw_Htoken (35)
#define lxi_begin_Haction (28)
#define lxi_eof (11)
#define lxi_ref (16)
#define lxi_kw_Hgroup (31)
#define lxi_plus (13)
#define lxi_close_Hbrace (9)
#define lxi_semicolon (14)
#define lxi_kw_Hzone (36)
#define lxi_arg_Hchar_Hstring (23)
#define lxi_kw_Htype (30)
#define lxi_discard (21)
#define lxi_open_Hbrace (8)
#define lxi_arg_Hchar_Hcount (25)
#define lxi_range_Hclosed_Hclosed (18)
#define lxi_end_Haction (29)
#define lxi_default (37)
#define lxi_arg_Hignore (27)

/* BEGINNING OF TRAILER */

#line 747 "syntax.act"


	#endif

#line 79 "syntax.h"

/* END OF FILE */
