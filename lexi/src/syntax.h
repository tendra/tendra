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

#define lex_arg_Hnb_Hof_Hchars (33)
#define lex_arg_Hchar_Hnb (32)
#define lex_keyword (8)
#define lex_range (26)
#define lex_comma (27)
#define lex_digit (5)
#define lex_unknown (29)
#define lex_close (17)
#define lex_sid_Hidentifier (1)
#define lex_string (2)
#define lex_equal (22)
#define lex_colon (25)
#define lex_token (10)
#define lex_white (11)
#define lex_identifier (0)
#define lex_else (15)
#define lex_lower (4)
#define lex_arrow (20)
#define lex_upper (3)
#define lex_group (7)
#define lex_nothing_Hmarker (28)
#define lex_open (16)
#define lex_eof (21)
#define lex_zone (13)
#define lex_plus (23)
#define lex_close_Hbrace (19)
#define lex_if (14)
#define lex_semicolon (24)
#define lex_arg_Hchar_Hstring (31)
#define lex_copyright (6)
#define lex_open_Hbrace (18)
#define lex_default (12)
#define lex_arg_Hchar_Hvoid (34)
#define lex_mapping (9)
#define lex_arg_Hchar_Hlist (30)

/* BEGINNING OF TRAILER */

#line 622 "syntax.act"

#endif
#line 101 "tmp.syntax.h"

/* END OF FILE */
