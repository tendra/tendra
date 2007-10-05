/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 123 "syntax.act"

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


#ifndef SYNTAX_INCLUDED
#define SYNTAX_INCLUDED

#include "char.h"
extern char *sid_prefix ;
typedef zone* zoneP;

#line 52 "tmp.syntax.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_lex(zoneP);

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lex_arg_Hchar_Hnb (31)
#define lex_keyword (7)
#define lex_range (25)
#define lex_comma (26)
#define lex_digit (5)
#define lex_unknown (28)
#define lex_close (16)
#define lex_sid_Hidentifier (1)
#define lex_string (2)
#define lex_equal (21)
#define lex_colon (24)
#define lex_token (9)
#define lex_white (10)
#define lex_identifier (0)
#define lex_else (14)
#define lex_lower (4)
#define lex_arrow (19)
#define lex_upper (3)
#define lex_group (6)
#define lex_nothing_Hmarker (27)
#define lex_open (15)
#define lex_eof (20)
#define lex_zone (12)
#define lex_plus (22)
#define lex_close_Hbrace (18)
#define lex_if (13)
#define lex_semicolon (23)
#define lex_arg_Hchar_Hstring (30)
#define lex_open_Hbrace (17)
#define lex_default (11)
#define lex_arg_Hchar_Hvoid (32)
#define lex_mapping (8)
#define lex_arg_Hchar_Hlist (29)

/* BEGINNING OF TRAILER */

#line 596 "syntax.act"

#endif
#line 99 "tmp.syntax.h"

/* END OF FILE */
