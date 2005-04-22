/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */


/*
    		 Crown Copyright (c) 1997, 1998
    
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


/* BEGINNING OF FUNCTION DECLARATIONS */

#ifndef __SID_SPLIT
extern void parse_init(IDENTIFIER, EXP *);
extern void parse_tok_type(TYPE *);
extern void parse_type_param(IDENTIFIER *);
extern void parse_type(TYPE *);
extern void parse_file(TYPE, DECL_SPEC);
extern void parse_offset(OFFSET, TYPE, OFFSET *, TYPE *);
extern void parse_nat(EXP *);
extern void parse_param(TYPE, int, IDENTIFIER *);
extern void parse_func(EXP *);
extern void parse_id(IDENTIFIER *);
extern void parse_exp(EXP *);
extern void parse_stmt(EXP *);
extern void parse_mem_type(TYPE *);
extern void parse_operator(IDENTIFIER *);
extern void parse_decl(TYPE, DECL_SPEC);
#else /* __SID_SPLIT */
extern void ZR509(BASE_TYPE *);
extern void ZR1398(NAMESPACE *, IDENTIFIER *, IDENTIFIER *);
extern void ZR1145(EXP, EXP *);
extern void ZR1017(NAMESPACE);
extern void ZR908(TYPE, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *);
extern void ZR415(void);
extern void ZR476(NAMESPACE, IDENTIFIER *);
extern void ZR946(IDENTIFIER, TYPE *, int *);
extern void ZR1402(NAMESPACE *, IDENTIFIER *, IDENTIFIER *);
extern void ZR971(TYPE, int, IDENTIFIER *);
extern void ZR1149(TYPE, TYPE *);
extern void ZR436(EXP *);
extern void ZR1405(NAMESPACE *, IDENTIFIER *, IDENTIFIER *);
extern void ZR426(NAMESPACE *);
extern void ZR699(EXP *);
extern void ZR517(NAMESPACE, IDENTIFIER *);
extern void ZR906(TYPE, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *);
extern void parse_init(IDENTIFIER, EXP *);
extern void ZR1027(TYPE, DECL_SPEC);
extern void ZR952(TYPE *);
extern void ZR681(EXP, EXP *);
extern void ZR842(void);
extern void ZR1284(EXP *);
extern void ZR1008(DECL_SPEC, BASE_TYPE, TYPE, ACCESS_LIST);
extern void ZR1033(TYPE, DECL_SPEC, EXP *);
extern void ZR1286(EXP *);
extern void ZR1002(IDENTIFIER, SID_LIST_EXP *);
extern void ZR776(EXP *);
extern void ZR1161(TYPE, IDENTIFIER, TYPE *, IDENTIFIER *);
extern void ZR503(IDENTIFIER *);
extern void ZR1019(EXP, EXP *, EXP *);
extern void ZR1289(EXP *, EXP *);
extern void ZR472(IDENTIFIER *);
extern void ZR761(int, IDENTIFIER *);
extern void ZR817(BASE_TYPE *);
extern void ZR999(IDENTIFIER, SID_LIST_EXP *);
extern void ZR1290(EXP *, SID_LIST_EXP *);
extern void ZR834(EXP *);
extern void parse_tok_type(TYPE *);
extern void ZR1291(EXP *);
extern void ZR616(void);
extern void ZR620(EXP *);
extern void ZR1016(NAMESPACE);
extern void ZR644(EXP *);
extern void ZR1167(EXP, EXP *);
extern void ZR583(int *);
extern void parse_type_param(IDENTIFIER *);
extern void ZR832(TYPE, DECL_SPEC);
extern void ZR413(void);
extern void ZR553(int, EXP *);
extern void ZR593(int, EXP *);
extern void ZR917(TYPE *, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *);
extern void ZR477(IDENTIFIER *);
extern void ZR771(EXP *);
extern void ZR1072(TYPE, DECL_SPEC, EXP *);
extern void ZR1429(int *, int *, int *, EXP *);
extern void ZR959(TYPE *, IDENTIFIER *);
extern void ZR1430(int *, EXP *);
extern void ZR1431(int *);
extern void ZR1177(TYPE, IDENTIFIER, int, TYPE *, IDENTIFIER *, int *);
extern void ZR961(TYPE, TYPE *, IDENTIFIER *);
extern void ZR1056(EXP *);
extern void ZR1432(int *);
extern void ZR569(TYPE, EXP *);
extern void ZR632(EXP *);
extern void ZR944(int, TYPE *);
extern void ZR1433(IDENTIFIER *, EXP *);
extern void ZR942(IDENTIFIER *);
extern void parse_type(TYPE *);
extern void ZR1096(IDENTIFIER *);
extern void ZR1127(OFFSET, TYPE, OFFSET *, TYPE *);
extern void ZR473(IDENTIFIER *);
extern void ZR991(TYPE *);
extern void ZR1029(EXP *);
extern void ZR1436(EXP *, EXP *);
extern void ZR940(TYPE *, IDENTIFIER *, int *);
extern void ZR611(EXP *);
extern void ZR736(EXP *, EXP *);
extern void ZR987(TYPE *);
extern void ZR863(IDENTIFIER);
extern void ZR950(TYPE, TYPE *, IDENTIFIER *, int *);
extern void ZR1004(int, IDENTIFIER, EXP *);
extern void parse_file(TYPE, DECL_SPEC);
extern void ZR1439(EXP *);
extern void ZR1312(NAMESPACE *, IDENTIFIER *, IDENTIFIER *);
extern void ZR1024(EXP *);
extern void ZR1110(int *);
extern void parse_offset(OFFSET, TYPE, OFFSET *, TYPE *);
extern void ZR1440(EXP *);
extern void ZR1313(NAMESPACE *, IDENTIFIER *);
extern void parse_nat(EXP *);
extern void ZR649(EXP *);
extern void parse_param(TYPE, int, IDENTIFIER *);
extern void ZR1315(NAMESPACE *, NAMESPACE *, IDENTIFIER *);
extern void ZR1188(EXP, EXP, int, EXP *, EXP *, int *);
extern void ZR873(BASE_TYPE *, TYPE *, CV_SPEC *);
extern void ZR502(IDENTIFIER *);
extern void ZR1104(SID_LIST_TYPE *);
extern void ZR1317(NAMESPACE *, NAMESPACE *, IDENTIFIER *);
extern void ZR484(IDENTIFIER *);
extern void ZR951(TYPE *);
extern void parse_func(EXP *);
extern void ZR516(IDENTIFIER *, BASE_TYPE *);
extern void ZR833(void);
extern void ZR1319(int *);
extern void ZR1192(EXP, EXP *);
extern void ZR504(IDENTIFIER *);
extern void ZR894(DECL_SPEC *);
extern void ZR1320(int *);
extern void parse_id(IDENTIFIER *);
extern void ZR1321(int *);
extern void ZR581(EXP *);
extern void ZR872(TYPE, BASE_TYPE *, TYPE *, CV_SPEC *);
extern void ZR941(int *);
extern void ZR955(TYPE, TYPE *);
extern void ZR1196(EXP, EXP *);
extern void ZR417(void);
extern void ZR1324(TYPE *, BASE_TYPE *, BASE_TYPE *, TYPE *, CV_SPEC *);
extern void ZR1325(TYPE *, BASE_TYPE *, TYPE *, CV_SPEC *);
extern void ZR866(IDENTIFIER);
extern void ZR1326(int *);
extern void ZR735(EXP *);
extern void ZR1023(EXP *);
extern void ZR1126(OFFSET, TYPE, OFFSET *, TYPE *);
extern void ZR1327(int *);
extern void ZR1200(EXP, EXP *);
extern void ZR614(EXP *);
extern void ZR838(TYPE, DECL_SPEC);
extern void ZR1328(DECL_SPEC *);
extern void ZR737(EXP *);
extern void ZR1075(BASE_TYPE *, DECL_SPEC *, TYPE *, ACCESS_LIST *, int *, IDENTIFIER *);
extern void ZR568(TYPE *, int *);
extern void ZR622(EXP *);
extern void ZR1076(BASE_TYPE *, DECL_SPEC *, TYPE *, ACCESS_LIST *);
extern void parse_exp(EXP *);
extern void ZR1204(EXP, EXP *);
extern void ZR687(TYPE, DECL_SPEC, EXP *);
extern void ZR635(EXP *);
extern void ZR953(EXP *);
extern void parse_stmt(EXP *);
extern void ZR1087(DECL_SPEC, TYPE, BASE_TYPE, ACCESS_LIST, int);
extern void ZR1208(EXP, EXP *);
extern void ZR548(TYPE *, int *);
extern void ZR643(EXP *);
extern void ZR686(TYPE, DECL_SPEC);
extern void ZR1028(void);
extern void ZR451(int *);
extern void ZR1339(TYPE *, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *);
extern void ZR1212(EXP, EXP *);
extern void ZR416(void);
extern void ZR498(SID_LIST_EXP *);
extern void ZR1467(IDENTIFIER *, EXP *);
extern void ZR1340(void);
extern void ZR1595(EXP *, EXP *);
extern void ZR496(EXP *);
extern void ZR1469(IDENTIFIER *, EXP *);
extern void ZR500(SID_LIST_EXP *);
extern void ZR1216(EXP, EXP *);
extern void ZR628(EXP *);
extern void ZR752(EXP *);
extern void ZR1471(IDENTIFIER *, EXP *);
extern void ZR1344(NAMESPACE *, IDENTIFIER *);
extern void ZR552(TYPE *, EXP *, int *);
extern void ZR698(EXP *, EXP *, int *);
extern void ZR785(CV_SPEC *);
extern void ZR1599(void);
extern void ZR1472(NAMESPACE *, EXP *);
extern void ZR1345(NAMESPACE *, IDENTIFIER *);
extern void ZR1022(EXP, EXP *);
extern void ZR1473(NAMESPACE *, EXP *);
extern void ZR1346(IDENTIFIER *);
extern void ZR1092(BASE_TYPE *, DECL_SPEC *, TYPE *, ACCESS_LIST *, IDENTIFIER *);
extern void ZR1474(EXP *);
extern void ZR1220(EXP, EXP *);
extern void ZR788(CV_SPEC *);
extern void ZR1602(NAMESPACE *, IDENTIFIER *);
extern void ZR712(EXP *);
extern void ZR1603(NAMESPACE *, IDENTIFIER *);
extern void ZR1604(IDENTIFIER *);
extern void ZR847(int *);
extern void ZR990(TYPE *);
extern void ZR1224(EXP, EXP *);
extern void ZR427(NAMESPACE *);
extern void ZR662(void);
extern void ZR784(CV_SPEC *);
extern void ZR835(void);
extern void ZR596(void);
extern void ZR1084(DECL_SPEC, TYPE, BASE_TYPE, ACCESS_LIST, int, IDENTIFIER *);
extern void ZR428(NAMESPACE *);
extern void ZR1228(EXP, EXP *);
extern void ZR998(IDENTIFIER, EXP *);
extern void ZR1089(TYPE, DECL_SPEC);
extern void ZR608(EXP *);
extern void ZR949(TYPE *, IDENTIFIER *, int *);
extern void ZR713(EXP *);
extern void ZR491(EXP *);
extern void ZR571(SID_LIST_EXP *, TYPE *, int *);
extern void ZR676(EXP, EXP *);
extern void ZR1232(EXP, EXP *);
extern void ZR899(DECL_SPEC *);
extern void ZR661(EXP *);
extern void ZR1236(EXP, EXP *);
extern void ZR954(TYPE *);
extern void ZR1365(DECL_SPEC *, TYPE *, BASE_TYPE *, ACCESS_LIST *, int *, IDENTIFIER *, IDENTIFIER *);
extern void ZR770(EXP);
extern void ZR738(EXP *);
extern void ZR1240(EXP, EXP *);
extern void ZR639(void);
extern void ZR1368(DECL_SPEC *, TYPE *, BASE_TYPE *, ACCESS_LIST *, int *, IDENTIFIER *, IDENTIFIER *);
extern void ZR669(EXP *);
extern void ZR1077(EXP *);
extern void ZR1125(OFFSET, TYPE, OFFSET *, TYPE *);
extern void ZR508(IDENTIFIER *);
extern void ZR762(EXP);
extern void ZR1030(void);
extern void ZR601(EXP *);
extern void ZR1371(TYPE *, IDENTIFIER *);
extern void ZR475(NAMESPACE, int *);
extern void ZR827(DECL_SPEC *);
extern void ZR1052(void);
extern void ZR869(IDENTIFIER *);
extern void parse_mem_type(TYPE *);
extern void ZR1252(TYPE *, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *);
extern void parse_operator(IDENTIFIER *);
extern void ZR1083(EXP *);
extern void ZR1254(TYPE *, DECL_SPEC *, BASE_TYPE *, TYPE *, CV_SPEC *, EXP *);
extern void ZR626(EXP *);
extern void ZR1382(TYPE *, TYPE *);
extern void ZR1255(void);
extern void ZR1001(IDENTIFIER *, SID_LIST_EXP *);
extern void ZR751(EXP *);
extern void ZR808(BASE_TYPE *, TYPE *);
extern void ZR1383(TYPE *);
extern void ZR648(SID_LIST_EXP *);
extern void ZR975(int *);
extern void ZR1384(SID_LIST_TYPE *);
extern void ZR1257(void);
extern void ZR437(EXP *);
extern void ZR939(SID_LIST_TYPE *);
extern void parse_decl(TYPE, DECL_SPEC);
extern void ZR1258(EXP *);
extern void ZR1259(EXP *);
extern void ZR624(EXP *);
extern void ZR678(EXP *);
extern void ZR499(SID_LIST_EXP *);
extern void ZR418(void);
extern void ZR630(EXP *);
extern void ZR651(EXP *);
extern void ZR1115(IDENTIFIER *);
extern void ZR1262(EXP *, EXP *);
extern void ZR926(TYPE *);
extern void ZR1264(EXP *, EXP *);
extern void ZR845(void);
extern void ZR1062(TYPE, DECL_SPEC, EXP *);
extern void ZR617(EXP *);
extern void ZR1009(DECL_SPEC, BASE_TYPE, TYPE, ACCESS_LIST);
extern void ZR1266(NAMESPACE *, EXP *);
extern void ZR1139(TYPE, TYPE *);
extern void ZR885(BASE_TYPE *, TYPE *, CV_SPEC *, BASE_TYPE *, TYPE *, CV_SPEC *);
extern void ZR1394(NAMESPACE *, IDENTIFIER *);
extern void ZR1267(NAMESPACE *, EXP *);
extern void ZR1268(EXP *);
extern void ZR605(EXP *);
extern int ZI0;
#endif /* __SID_SPLIT */

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lex_double (102)
#define lex_arith_Hcap (176)
#define lex_macro_Harg (347)
#define lex_hash_Helse (28)
#define lex_private (142)
#define lex_incompatible (241)
#define lex_new_Harray_Hfull (350)
#define lex_ifdef (232)
#define lex_reject (290)
#define lex_compute (192)
#define lex_dollar (206)
#define lex_tendra (308)
#define lex_unreachable (322)
#define lex_vtable (329)
#define lex_inline (137)
#define lex_public (144)
#define lex_namespace_Hname (3)
#define lex_hash_H1 (51)
#define lex_either (207)
#define lex_hash_H2 (90)
#define lex_catch (128)
#define lex_const_Hcast (130)
#define lex_pointer (275)
#define lex_inset_Hstart (345)
#define lex_full_Hname (9)
#define lex_nested (263)
#define lex_suspend (305)
#define lex_break (95)
#define lex_begin (181)
#define lex_ignore (234)
#define lex_volatile_Ht (328)
#define lex_assign (36)
#define lex_endif (211)
#define lex_hash_Hhash_Hop (344)
#define lex_keyword (250)
#define lex_promote (282)
#define lex_wstring_Hlit (15)
#define lex_static (117)
#define lex_virtual (155)
#define lex_extend (219)
#define lex_this_Hname (310)
#define lex_minus_Hminus (61)
#define lex_lvalue (256)
#define lex_struct_Hcap (304)
#define lex_inset_Hend (346)
#define lex_lshift (57)
#define lex_open_Hround (65)
#define lex_false (135)
#define lex_block (183)
#define lex_scanf (296)
#define lex_wstring_Hexp (20)
#define lex_comma (42)
#define lex_union_Hcap (319)
#define lex_wchar_Hlit (13)
#define lex_func_Hcap (226)
#define lex_and_H1 (33)
#define lex_lshift_Heq (58)
#define lex_typeid (152)
#define lex_rvalue (294)
#define lex_string_Hlit (14)
#define lex_rshift (75)
#define lex_sizeof (116)
#define lex_and_H2 (157)
#define lex_unknown (0)
#define lex_wchar_Hexp (18)
#define lex_after (169)
#define lex_macro (257)
#define lex_precedence (278)
#define lex_undef (317)
#define lex_type_Hname (2)
#define lex_switch (119)
#define lex_assert (179)
#define lex_octal (268)
#define lex_ptrdiff_Ht (285)
#define lex_ident (230)
#define lex_printf (280)
#define lex_string_Hexp (19)
#define lex_and_Heq_H1 (34)
#define lex_reinterpret_Hcast (145)
#define lex_depth (201)
#define lex_unused (323)
#define lex_char_Hlit (12)
#define lex_rshift_Heq (76)
#define lex_arrow_Hstar (82)
#define lex_float (106)
#define lex_class (129)
#define lex_and_Heq_H2 (158)
#define lex_bottom (184)
#define lex_nline (264)
#define lex_open_Hinit (351)
#define lex_extern (105)
#define lex_decl (196)
#define lex_proc_Hcap (281)
#define lex_string (303)
#define lex_typeof (314)
#define lex_while (125)
#define lex_conditional (193)
#define lex_new_Harray (349)
#define lex_char_Hexp (17)
#define lex_code (188)
#define lex_option (272)
#define lex_reachable (288)
#define lex_colon (41)
#define lex_case (96)
#define lex_import (237)
#define lex_char (97)
#define lex_value (325)
#define lex_logical_Hand_H1 (55)
#define lex_fall (222)
#define lex_tag_Hcap (307)
#define lex_logical_Hand_H2 (160)
#define lex_allow (172)
#define lex_array (177)
#define lex_elif (208)
#define lex_file (223)
#define lex_limit (251)
#define lex_name (261)
#define lex_hash_Hif (26)
#define lex_return (113)
#define lex_token (311)
#define lex_close_Hbrace_H1 (38)
#define lex_export (134)
#define lex_reset (292)
#define lex_close_Hbrace_H2 (88)
#define lex_compatible (190)
#define lex_extra (221)
#define lex_main (258)
#define lex_destructor_Hname (5)
#define lex_nat_Hcap (262)
#define lex_type_Hcap (313)
#define lex_struct (118)
#define lex_using (154)
#define lex_close_Htemplate (337)
#define lex_identifier (1)
#define lex_const (98)
#define lex_line (252)
#define lex_weak (331)
#define lex_else (103)
#define lex_delete_Harray_Hfull (341)
#define lex_union (121)
#define lex_statement_Hname (4)
#define lex_cast (185)
#define lex_error (214)
#define lex_arrow (35)
#define lex_bool (127)
#define lex_stmt_Hcap (302)
#define lex_unify (318)
#define lex_minus (59)
#define lex_new_Hfull (348)
#define lex_definition (200)
#define lex_int_Hcap (249)
#define lex_array_Hop (334)
#define lex_not_H1 (62)
#define lex_quote (287)
#define lex_backslash (37)
#define lex_long (111)
#define lex_not_H2 (162)
#define lex_exp_Hcap (217)
#define lex_dot_Hstar (84)
#define lex_short (114)
#define lex_namespace (139)
#define lex_character (186)
#define lex_minus_Heq (60)
#define lex_void (123)
#define lex_cond_Hop (338)
#define lex_hash_Hop (343)
#define lex_reference (289)
#define lex_not_Heq_H1 (63)
#define lex_abs (85)
#define lex_enum (104)
#define lex_throw (149)
#define lex_not_Heq_H2 (163)
#define lex_incomplete (242)
#define lex_interface (246)
#define lex_end (210)
#define lex_less (53)
#define lex_xor_H1 (80)
#define lex_this (148)
#define lex_wchar_Ht (156)
#define lex_xor_H2 (166)
#define lex_all (171)
#define lex_eof (32)
#define lex_close_Hsquare_H1 (40)
#define lex_plus_Hplus (71)
#define lex_auto (94)
#define lex_goto (108)
#define lex_star (78)
#define lex_close_Hsquare_H2 (89)
#define lex_into (248)
#define lex_no_Hdef (266)
#define lex_off (270)
#define lex_func_Hop (342)
#define lex_environment (212)
#define lex_tag (306)
#define lex_less_Heq (54)
#define lex_xor_Heq_H1 (81)
#define lex_xor_Heq_H2 (167)
#define lex_size_Ht_H2 (299)
#define lex_unmatched (320)
#define lex_or_H1 (67)
#define lex_assignment (180)
#define lex_open_Hbrace_H1 (64)
#define lex_star_Heq (79)
#define lex_or_H2 (164)
#define lex_open_Hbrace_H2 (92)
#define lex_asm (126)
#define lex_true (150)
#define lex_un_Hknown (315)
#define lex_nested_Hname_Hstar (10)
#define lex_div (44)
#define lex_type (312)
#define lex_open_Htemplate (352)
#define lex_or_Heq_H1 (68)
#define lex_rem (73)
#define lex_min (87)
#define lex_dynamic_Hcast (132)
#define lex_directive (202)
#define lex_writeable (332)
#define lex_plus (69)
#define lex_or_Heq_H2 (165)
#define lex_max (86)
#define lex_text (309)
#define lex_delete_Harray (340)
#define lex_dot (46)
#define lex_for (107)
#define lex_bitfield (182)
#define lex_qualifier (286)
#define lex_div_Heq (45)
#define lex_rem_Heq (74)
#define lex_lit (254)
#define lex_sort (300)
#define lex_plus_Heq (70)
#define lex_new (140)
#define lex_variable (326)
#define lex_int (110)
#define lex_std (301)
#define lex_builtin_Hfile (335)
#define lex_conversion (194)
#define lex_exhaustive (216)
#define lex_set (297)
#define lex_logical_Hor_H1 (56)
#define lex_use (324)
#define lex_semicolon (77)
#define lex_if (109)
#define lex_logical_Hor_H2 (161)
#define lex_hash_Hpragma (30)
#define lex_protected (143)
#define lex_indented (243)
#define lex_implement (235)
#define lex_ambiguous (173)
#define lex_define_Hcap (198)
#define lex_do (101)
#define lex_decimal (195)
#define lex_defined (199)
#define lex_template_Htype (7)
#define lex_as (178)
#define lex_builtin_Hline (336)
#define lex_of (269)
#define lex_floating_Hexp (22)
#define lex_eq (48)
#define lex_open_Hsquare_H1 (66)
#define lex_open_Hsquare_H2 (93)
#define lex_nested_Hname (8)
#define lex_include_Hnext (240)
#define lex_hash_Hhash_H1 (52)
#define lex_hash_Hhash_H2 (91)
#define lex_delete_Hfull (339)
#define lex_directory (203)
#define lex_resolution (293)
#define lex_includes (239)
#define lex_template_Hid (6)
#define lex_hash_Hendif (29)
#define lex_no (265)
#define lex_on (271)
#define lex_scalar_Hcap (295)
#define lex_complete (191)
#define lex_discard (205)
#define lex_linkage (253)
#define lex_member_Hcap (260)
#define lex_size_Ht (298)
#define lex_try (151)
#define lex_implicit (236)
#define lex_zzzzzz (353)
#define lex_template (147)
#define lex_overload (274)
#define lex_unsigned (122)
#define lex_internal (247)
#define lex_unpostpone (321)
#define lex_alignof (170)
#define lex_disallow (204)
#define lex_volatile (124)
#define lex_longlong (255)
#define lex_explicit (133)
#define lex_static_Hcast (146)
#define lex_ellipsis_Hexp (209)
#define lex_identif (231)
#define lex_typename (153)
#define lex_argument (175)
#define lex_external (220)
#define lex_include (238)
#define lex_default (100)
#define lex_analysis (174)
#define lex_ellipsis (47)
#define lex_colon_Hcolon (83)
#define lex_continue (99)
#define lex_register (112)
#define lex_zzzz (333)
#define lex_integer_Hlit (16)
#define lex_function (227)
#define lex_variety_Hcap (327)
#define lex_greater (49)
#define lex_mutable (138)
#define lex_define (197)
#define lex_integer_Hexp (21)
#define lex_complex_Htype (25)
#define lex_ifndef (233)
#define lex_promoted (283)
#define lex_full_Hname_Hstar (11)
#define lex_operator (141)
#define lex_preserve (279)
#define lex_close_Hround (39)
#define lex_initialization (244)
#define lex_integer (245)
#define lex_greater_Heq (50)
#define lex_accept (168)
#define lex_equality (213)
#define lex_escape (215)
#define lex_complex_Hstmt (24)
#define lex_typedef (120)
#define lex_explain (218)
#define lex_hash_Helif (27)
#define lex_newline (31)
#define lex_delete (131)
#define lex_hiding (229)
#define lex_comment (189)
#define lex_complex_Hexp (23)
#define lex_forward (225)
#define lex_overflow (273)
#define lex_object (267)
#define lex_unassert (316)
#define lex_warning (330)
#define lex_friend (136)
#define lex_member (259)
#define lex_pragma (277)
#define lex_compl_H1 (43)
#define lex_class_Hcap (187)
#define lex_float_Hcap (224)
#define lex_hexadecimal (228)
#define lex_prototype (284)
#define lex_question (72)
#define lex_signed (115)
#define lex_compl_H2 (159)
#define lex_postpone (276)
#define lex_representation (291)

/* BEGINNING OF TRAILER */




/*
    DUMMY LEXICAL TOKEN VALUES

    These values are used as lexical token values in certain circumstances
    but do not represent actual tokens.  Note that they are all negative.
*/

#define lex_ignore_token	-1
#define lex_end_condition	-2
#define lex_included		-3


#endif

/* END OF FILE */
