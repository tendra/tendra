/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/tools/pl/syntax.sid
 * and
 *	/u/g/release/Source/src/tools/pl/syntax.act
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

extern int do_pp;
extern int search_for_toks;
extern unsigned long MAJOR_NO ;
extern unsigned long MINOR_NO ;

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_label PROTO_S ((void));
extern void read_variety PROTO_S ((void));
extern void read_shape PROTO_S ((void));
extern void read_string PROTO_S ((void));
extern void read_signed_nat PROTO_S ((void));
extern void read_token PROTO_S ((void));
extern void read_error_code PROTO_S ((void));
extern void read_bool PROTO_S ((void));
extern void read_ntest PROTO_S ((void));
extern void read_bitfield_variety PROTO_S ((void));
extern void read_tag PROTO_S ((void));
extern void read_nat_option PROTO_S ((void));
extern void read_floating_variety PROTO_S ((void));
extern void read_nat PROTO_S ((void));
extern void read_alignment PROTO_S ((void));
extern void read_error_code_list PROTO_S ((void));
extern void read_exp PROTO_S ((void));
extern void read_error_treatment PROTO_S ((void));
extern void read_al_tag PROTO_S ((void));
extern void read_exp_list PROTO_S ((void));
extern void read_transfer_mode PROTO_S ((void));
extern void read_rounding_mode PROTO_S ((void));
extern void read_access PROTO_S ((void));
extern void read_program PROTO_S ((void));

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lex_error__treatment__cons (38)
#define lex_exp__tok (43)
#define lex_e__term (34)
#define lex_tokdef (114)
#define lex_transfer__mode__cons (118)
#define lex_rounding__mode__cons (89)
#define lex_access__cons (0)
#define lex_qstring (85)
#define lex_equals (36)
#define lex_comma (25)
#define lex_varpar (129)
#define lex_error__treatment__sort (39)
#define lex_goesto (51)
#define lex_minexp (67)
#define lex_al__tag__sort (4)
#define lex_ident (54)
#define lex_maxexp (66)
#define lex_notaterminal (72)
#define lex_error__treatment__tok (40)
#define lex_signed__term (101)
#define lex_double__term (32)
#define lex_al__tag__tok (5)
#define lex_ccurl (20)
#define lex_al__tagdef (6)
#define lex_base (12)
#define lex_colon (24)
#define lex_transfer__mode__sort (119)
#define lex_rounding__mode__sort (90)
#define lex_variety__cons (126)
#define lex_access__sort (1)
#define lex_untidy (122)
#define lex_transfer__mode__tok (120)
#define lex_logop (63)
#define lex_rounding__mode__tok (91)
#define lex_offset__query (77)
#define lex_relop (87)
#define lex_access__tok (2)
#define lex_hash (52)
#define lex_keep (57)
#define lex_common__term (26)
#define lex_ocurl (76)
#define lex_same (92)
#define lex_shape__cons (94)
#define lex_point (80)
#define lex_label__sort (59)
#define lex_lab (58)
#define lex_semi (93)
#define lex_string__cons (104)
#define lex_float__den (44)
#define lex_character (22)
#define lex_float__query (45)
#define lex_label__tok (60)
#define lex_float__term (46)
#define lex_variety__sort (127)
#define lex_cons (28)
#define lex_bar (11)
#define lex_proc (81)
#define lex_string__term (106)
#define lex_case__term (19)
#define lex_query (86)
#define lex_signed__nat__cons (98)
#define lex_variety__tok (128)
#define lex_crd (29)
#define lex_token__cons (115)
#define lex_char__term (21)
#define lex_eof (35)
#define lex_star (103)
#define lex_shape__sort (95)
#define lex_error__code__cons (37)
#define lex_bool__cons (16)
#define lex_shape__tok (96)
#define lex_struct__term (108)
#define lex_line__term (62)
#define lex_let (61)
#define lex_ord (78)
#define lex_string__sort (105)
#define lex_tail__call__term (112)
#define lex_ntest__cons (73)
#define lex_bitfield__variety__cons (13)
#define lex_csq (30)
#define lex_rep (88)
#define lex_minus__term (68)
#define lex_var (124)
#define lex_string__tok (107)
#define lex_long__term (64)
#define lex_short__term (97)
#define lex_signed__nat__sort (99)
#define lex_use (123)
#define lex_token__sort (116)
#define lex_proc__query (82)
#define lex_signed__nat__tok (100)
#define lex_tag__cons (109)
#define lex_osq (79)
#define lex_token__tok (117)
#define lex_commondec__term (27)
#define lex_ptr (83)
#define lex_size__term (102)
#define lex_bool__sort (17)
#define lex_floating__variety__cons (47)
#define lex_nat__cons (69)
#define lex_alignment__cons (7)
#define lex_dotdotdot (31)
#define lex_ntest__sort (74)
#define lex_bitfield__variety__sort (14)
#define lex_bool__tok (18)
#define lex_ntest__tok (75)
#define lex_bitfield__variety__tok (15)
#define lex_general (50)
#define lex_exp__cons (41)
#define lex_int__den (55)
#define lex_mantissa (65)
#define lex_int__term (56)
#define lex_tag__sort (110)
#define lex_dynamic (33)
#define lex_tag__tok (111)
#define lex_floating__variety__sort (48)
#define lex_nat__sort (70)
#define lex_alignment__sort (8)
#define lex_ptr__query (84)
#define lex_floating__variety__tok (49)
#define lex_nat__tok (71)
#define lex_alignment__tok (9)
#define lex_vardec (125)
#define lex_exp__sort (42)
#define lex_check__stack (23)
#define lex_arithop (10)
#define lex_iddec (53)
#define lex_addrop (3)
#define lex_tokdec (113)
#define lex_unsigned__term (121)

/* BEGINNING OF TRAILER */


#endif

/* END OF FILE */
