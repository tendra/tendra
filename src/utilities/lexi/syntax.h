/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/utilities/lexi/syntax.sid
 * and
 *	/u/g/release/Source/src/utilities/lexi/syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */


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

extern char *sid_prefix ;


/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_lex PROTO_S ((void));

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lex_keyword (7)
#define lex_digit (5)
#define lex_unknown (22)
#define lex_close (14)
#define lex_sid_Hidentifier (1)
#define lex_string (2)
#define lex_equal (19)
#define lex_token (9)
#define lex_white (10)
#define lex_identifier (0)
#define lex_else (12)
#define lex_lower (4)
#define lex_arrow (17)
#define lex_upper (3)
#define lex_group (6)
#define lex_open (13)
#define lex_eof (18)
#define lex_plus (20)
#define lex_close_Hbrace (16)
#define lex_if (11)
#define lex_semicolon (21)
#define lex_open_Hbrace (15)
#define lex_mapping (8)

/* BEGINNING OF TRAILER */


#endif

/* END OF FILE */
