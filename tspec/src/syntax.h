/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 146 "syntax.act"


	/* $Id$ */

	/*
	 * Copyright 2011, The TenDRA Project.
	 * Copyright 1997, United Kingdom Secretary of State for Defence.
	 *
	 * See doc/copyright/ for the full copyright terms.
	 */

	#ifndef SYNTAX_INCLUDED
	#define SYNTAX_INCLUDED

	typedef object *SID_COMMAND;

#line 30 "syntax.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_spec(SID_COMMAND *);

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lex_double (34)
#define lex_ifdef (17)
#define lex_protect (52)
#define lex_base_Hapi (7)
#define lex_field (14)
#define lex_endif (11)
#define lex_assign (60)
#define lex_promote (51)
#define lex_number (1)
#define lex_lvalue (40)
#define lex_open_Hround (56)
#define lex_comma (62)
#define lex_macro (21)
#define lex_unknown (74)
#define lex_insert (5)
#define lex_float (37)
#define lex_subset (25)
#define lex_extern (36)
#define lex_string (2)
#define lex_arith (31)
#define lex_equal (66)
#define lex_colon (61)
#define lex_char (32)
#define lex_name (0)
#define lex_token (26)
#define lex_struct (44)
#define lex_const (33)
#define lex_weak (49)
#define lex_else (10)
#define lex_union (45)
#define lex_func (15)
#define lex_info (20)
#define lex_minus (68)
#define lex_long (39)
#define lex_short (42)
#define lex_void (47)
#define lex_enum (35)
#define lex_eof (73)
#define lex_star (72)
#define lex_dot_Hdot (64)
#define lex_nat (22)
#define lex_type (27)
#define lex_close_Hbrace (55)
#define lex_dot (63)
#define lex_variable (3)
#define lex_enumerate (12)
#define lex_int (38)
#define lex_set (23)
#define lex_exp (13)
#define lex_use (29)
#define lex_if (16)
#define lex_semicolon (71)
#define lex_implement (19)
#define lex_building (50)
#define lex_build_Hinsert (6)
#define lex_statement (24)
#define lex_close_Hsquare (59)
#define lex_or (69)
#define lex_unsigned (46)
#define lex_open_Hbrace (54)
#define lex_volatile (48)
#define lex_special (53)
#define lex_exclaim (67)
#define lex_ellipsis (65)
#define lex_define (9)
#define lex_constant (8)
#define lex_ifndef (18)
#define lex_close_Hround (57)
#define lex_typedef (28)
#define lex_defmin (30)
#define lex_comment (4)
#define lex_open_Hsquare (58)
#define lex_scalar (41)
#define lex_signed (43)
#define lex_question (70)

/* BEGINNING OF TRAILER */

#line 841 "syntax.act"


	#endif

#line 121 "syntax.h"

/* END OF FILE */
