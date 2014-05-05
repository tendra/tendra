# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Standard KeySym values (see 12.7)
# The various groupings, XK_MISCELLANY etc, are specified in 1.3.
# The actual KeySyms are not specified in X11.

+USE "x5/lib", "X11/X.h.ts" ;

+IFDEF ~building_libs
+IFNDEF XK_MISCELLANY
+DEFINE XK_MISCELLANY	%% %% ;
+DEFINE XK_LATIN1	%% %% ;
+DEFINE XK_LATIN2	%% %% ;
+DEFINE XK_LATIN3	%% %% ;
+DEFINE XK_LATIN4	%% %% ;
+DEFINE XK_GREEK	%% %% ;
+DEFINE XK_HEBREW	%% %% ;
+ENDIF
+ENDIF

+CONST KeySym XK_VoidSymbol ;

+IFDEF XK_MISCELLANY
+CONST KeySym XK_BackSpace, XK_Tab, XK_Linefeed, XK_Clear, XK_Return ;
+CONST KeySym XK_Pause, XK_Scroll_Lock, XK_Escape, XK_Delete, XK_Multi_key ;
+CONST KeySym XK_Kanji, XK_Muhenkan, XK_Henkan_Mode, XK_Henkan, XK_Romaji ;
+CONST KeySym XK_Hiragana, XK_Katakana, XK_Hiragana_Katakana, XK_Zenkaku ;
+CONST KeySym XK_Hankaku, XK_Zenkaku_Hankaku, XK_Touroku, XK_Massyo ;
+CONST KeySym XK_Kana_Lock, XK_Kana_Shift, XK_Eisu_Shift, XK_Eisu_toggle ;
+CONST KeySym XK_Home, XK_Left, XK_Up, XK_Right, XK_Down, XK_Prior, XK_Next ;
+CONST KeySym XK_End, XK_Begin, XK_Select, XK_Print, XK_Execute, XK_Insert ;
+CONST KeySym XK_Undo, XK_Redo, XK_Menu, XK_Find, XK_Cancel, XK_Help, XK_Break ;
+CONST KeySym XK_Mode_switch, XK_script_switch, XK_Num_Lock, XK_KP_Space ;
+CONST KeySym XK_KP_Tab, XK_KP_Enter, XK_KP_F1, XK_KP_F2, XK_KP_F3, XK_KP_F4 ;
+CONST KeySym XK_KP_Equal, XK_KP_Multiply, XK_KP_Add, XK_KP_Separator ;
+CONST KeySym XK_KP_Subtract, XK_KP_Decimal, XK_KP_Divide, XK_KP_0, XK_KP_1 ;
+CONST KeySym XK_KP_2, XK_KP_3, XK_KP_4, XK_KP_5, XK_KP_6, XK_KP_7, XK_KP_8 ;
+CONST KeySym XK_KP_9, XK_F1, XK_F2, XK_F3, XK_F4, XK_F5, XK_F6, XK_F7, XK_F8 ;
+CONST KeySym XK_F9, XK_F10, XK_F11, XK_L1, XK_F12, XK_L2, XK_F13, XK_L3 ;
+CONST KeySym XK_F14, XK_L4, XK_F15, XK_L5, XK_F16, XK_L6, XK_F17, XK_L7 ;
+CONST KeySym XK_F18, XK_L8, XK_F19, XK_L9, XK_F20, XK_L10, XK_F21, XK_R1 ;
+CONST KeySym XK_F22, XK_R2, XK_F23, XK_R3, XK_F24, XK_R4, XK_F25, XK_R5 ;
+CONST KeySym XK_F26, XK_R6, XK_F27, XK_R7, XK_F28, XK_R8, XK_F29, XK_R9 ;
+CONST KeySym XK_F30, XK_R10, XK_F31, XK_R11, XK_F32, XK_R12, XK_F33, XK_R13 ;
+CONST KeySym XK_F34, XK_R14, XK_F35, XK_R15, XK_Shift_L, XK_Shift_R ;
+CONST KeySym XK_Control_L, XK_Control_R, XK_Caps_Lock, XK_Shift_Lock ;
+CONST KeySym XK_Meta_L, XK_Meta_R, XK_Alt_L, XK_Alt_R, XK_Super_L ;
+CONST KeySym XK_Super_R, XK_Hyper_L, XK_Hyper_R ;
+ENDIF

+IFDEF XK_LATIN1
+CONST KeySym XK_space, XK_exclam, XK_quotedbl, XK_numbersign, XK_dollar ;
+CONST KeySym XK_percent, XK_ampersand, XK_apostrophe, XK_quoteright ;
+CONST KeySym XK_parenleft, XK_parenright, XK_asterisk, XK_plus, XK_comma ;
+CONST KeySym XK_minus, XK_period, XK_slash, XK_0, XK_1, XK_2, XK_3, XK_4 ;
+CONST KeySym XK_5, XK_6, XK_7, XK_8, XK_9, XK_colon, XK_semicolon, XK_less ;
+CONST KeySym XK_equal, XK_greater, XK_question, XK_at, XK_A, XK_B, XK_C ;
+CONST KeySym XK_D, XK_E, XK_F, XK_G, XK_H, XK_I, XK_J, XK_K, XK_L, XK_M ;
+CONST KeySym XK_N, XK_O, XK_P, XK_Q, XK_R, XK_S, XK_T, XK_U, XK_V, XK_W ;
+CONST KeySym XK_X, XK_Y, XK_Z, XK_bracketleft, XK_backslash, XK_bracketright ;
+CONST KeySym XK_asciicircum, XK_underscore, XK_grave, XK_quoteleft, XK_a ;
+CONST KeySym XK_b, XK_c, XK_d, XK_e, XK_f, XK_g, XK_h, XK_i, XK_j, XK_k ;
+CONST KeySym XK_l, XK_m, XK_n, XK_o, XK_p, XK_q, XK_r, XK_s, XK_t, XK_u ;
+CONST KeySym XK_v, XK_w, XK_x, XK_y, XK_z, XK_braceleft, XK_bar ;
+CONST KeySym XK_braceright, XK_asciitilde, XK_nobreakspace, XK_exclamdown ;
+CONST KeySym XK_cent, XK_sterling, XK_currency, XK_yen, XK_brokenbar ;
+CONST KeySym XK_section, XK_diaeresis, XK_copyright, XK_ordfeminine ;
+CONST KeySym XK_guillemotleft, XK_notsign, XK_hyphen, XK_registered ;
+CONST KeySym XK_macron, XK_degree, XK_plusminus, XK_twosuperior ;
+CONST KeySym XK_threesuperior, XK_acute, XK_mu, XK_paragraph ;
+CONST KeySym XK_periodcentered, XK_cedilla, XK_onesuperior, XK_masculine ;
+CONST KeySym XK_guillemotright, XK_onequarter, XK_onehalf, XK_threequarters ;
+CONST KeySym XK_questiondown, XK_Agrave, XK_Aacute, XK_Acircumflex ;
+CONST KeySym XK_Atilde, XK_Adiaeresis, XK_Aring, XK_AE, XK_Ccedilla ;
+CONST KeySym XK_Egrave, XK_Eacute, XK_Ecircumflex, XK_Ediaeresis, XK_Igrave ;
+CONST KeySym XK_Iacute, XK_Icircumflex, XK_Idiaeresis, XK_ETH, XK_Eth ;
+CONST KeySym XK_Ntilde, XK_Ograve, XK_Oacute, XK_Ocircumflex, XK_Otilde ;
+CONST KeySym XK_Odiaeresis, XK_multiply, XK_Ooblique, XK_Ugrave, XK_Uacute ;
+CONST KeySym XK_Ucircumflex, XK_Udiaeresis, XK_Yacute, XK_THORN, XK_Thorn ;
+CONST KeySym XK_ssharp, XK_agrave, XK_aacute, XK_acircumflex, XK_atilde ;
+CONST KeySym XK_adiaeresis, XK_aring, XK_ae, XK_ccedilla, XK_egrave ;
+CONST KeySym XK_eacute, XK_ecircumflex, XK_ediaeresis, XK_igrave, XK_iacute ;
+CONST KeySym XK_icircumflex, XK_idiaeresis, XK_eth, XK_ntilde, XK_ograve ;
+CONST KeySym XK_oacute, XK_ocircumflex, XK_otilde, XK_odiaeresis, XK_division ;
+CONST KeySym XK_oslash, XK_ugrave, XK_uacute, XK_ucircumflex, XK_udiaeresis ;
+CONST KeySym XK_yacute, XK_thorn, XK_ydiaeresis ;
+ENDIF

+IFDEF XK_LATIN2
+CONST KeySym XK_Aogonek, XK_breve, XK_Lstroke, XK_Lcaron, XK_Sacute ;
+CONST KeySym XK_Scaron, XK_Scedilla, XK_Tcaron, XK_Zacute, XK_Zcaron ;
+CONST KeySym XK_Zabovedot, XK_aogonek, XK_ogonek, XK_lstroke, XK_lcaron ;
+CONST KeySym XK_sacute, XK_caron, XK_scaron, XK_scedilla, XK_tcaron ;
+CONST KeySym XK_zacute, XK_doubleacute, XK_zcaron, XK_zabovedot, XK_Racute ;
+CONST KeySym XK_Abreve, XK_Lacute, XK_Cacute, XK_Ccaron, XK_Eogonek ;
+CONST KeySym XK_Ecaron, XK_Dcaron, XK_Dstroke, XK_Nacute, XK_Ncaron ;
+CONST KeySym XK_Odoubleacute, XK_Rcaron, XK_Uring, XK_Udoubleacute ;
+CONST KeySym XK_Tcedilla, XK_racute, XK_abreve, XK_lacute, XK_cacute ;
+CONST KeySym XK_ccaron, XK_eogonek, XK_ecaron, XK_dcaron, XK_dstroke ;
+CONST KeySym XK_nacute, XK_ncaron, XK_odoubleacute, XK_udoubleacute ;
+CONST KeySym XK_rcaron, XK_uring, XK_tcedilla, XK_abovedot ;
+ENDIF

+IFDEF XK_LATIN3
+CONST KeySym XK_Hstroke, XK_Hcircumflex, XK_Iabovedot, XK_Gbreve ;
+CONST KeySym XK_Jcircumflex, XK_hstroke, XK_hcircumflex, XK_idotless ;
+CONST KeySym XK_gbreve, XK_jcircumflex, XK_Cabovedot, XK_Ccircumflex ;
+CONST KeySym XK_Gabovedot, XK_Gcircumflex, XK_Ubreve, XK_Scircumflex ;
+CONST KeySym XK_cabovedot, XK_ccircumflex, XK_gabovedot, XK_gcircumflex ;
+CONST KeySym XK_ubreve, XK_scircumflex ;
+ENDIF

+IFDEF XK_LATIN4
+CONST KeySym XK_kra, XK_kappa, XK_Rcedilla, XK_Itilde, XK_Lcedilla ;
+CONST KeySym XK_Emacron, XK_Gcedilla, XK_Tslash, XK_rcedilla, XK_itilde ;
+CONST KeySym XK_lcedilla, XK_emacron, XK_gcedilla, XK_tslash, XK_ENG ;
+CONST KeySym XK_eng, XK_Amacron, XK_Iogonek, XK_Eabovedot, XK_Imacron ;
+CONST KeySym XK_Ncedilla, XK_Omacron, XK_Kcedilla, XK_Uogonek, XK_Utilde ;
+CONST KeySym XK_Umacron, XK_amacron, XK_iogonek, XK_eabovedot, XK_imacron ;
+CONST KeySym XK_ncedilla, XK_omacron, XK_kcedilla, XK_uogonek, XK_utilde ;
+CONST KeySym XK_umacron ;
+ENDIF

+IFDEF XK_KATAKANA
+CONST KeySym XK_overline, XK_kana_fullstop, XK_kana_openingbracket ;
+CONST KeySym XK_kana_closingbracket, XK_kana_comma, XK_kana_conjunctive ;
+CONST KeySym XK_kana_middledot, XK_kana_WO, XK_kana_a, XK_kana_i ;
+CONST KeySym XK_kana_u, XK_kana_e, XK_kana_o, XK_kana_ya, XK_kana_yu ;
+CONST KeySym XK_kana_yo, XK_kana_tsu, XK_kana_tu, XK_prolongedsound ;
+CONST KeySym XK_kana_A, XK_kana_I, XK_kana_U, XK_kana_E, XK_kana_O ;
+CONST KeySym XK_kana_KA, XK_kana_KI, XK_kana_KU, XK_kana_KE, XK_kana_KO ;
+CONST KeySym XK_kana_SA, XK_kana_SHI, XK_kana_SU, XK_kana_SE, XK_kana_SO ;
+CONST KeySym XK_kana_TA, XK_kana_CHI, XK_kana_TI, XK_kana_TSU ;
+CONST KeySym XK_kana_TU, XK_kana_TE, XK_kana_TO, XK_kana_NA, XK_kana_NI ;
+CONST KeySym XK_kana_NU, XK_kana_NE, XK_kana_NO, XK_kana_HA, XK_kana_HI ;
+CONST KeySym XK_kana_FU, XK_kana_HU, XK_kana_HE, XK_kana_HO, XK_kana_MA ;
+CONST KeySym XK_kana_MI, XK_kana_MU, XK_kana_ME, XK_kana_MO, XK_kana_YA ;
+CONST KeySym XK_kana_YU, XK_kana_YO, XK_kana_RA, XK_kana_RI, XK_kana_RU ;
+CONST KeySym XK_kana_RE, XK_kana_RO, XK_kana_WA, XK_kana_N ;
+CONST KeySym XK_voicedsound, XK_semivoicedsound, XK_kana_switch ;
+ENDIF

+IFDEF XK_ARABIC
+CONST KeySym XK_Arabic_comma, XK_Arabic_semicolon, XK_Arabic_question_mark ;
+CONST KeySym XK_Arabic_hamza, XK_Arabic_maddaonalef, XK_Arabic_hamzaonalef ;
+CONST KeySym XK_Arabic_hamzaonwaw, XK_Arabic_hamzaunderalef ;
+CONST KeySym XK_Arabic_hamzaonyeh, XK_Arabic_alef, XK_Arabic_beh ;
+CONST KeySym XK_Arabic_tehmarbuta, XK_Arabic_teh, XK_Arabic_theh ;
+CONST KeySym XK_Arabic_jeem, XK_Arabic_hah, XK_Arabic_khah, XK_Arabic_dal ;
+CONST KeySym XK_Arabic_thal, XK_Arabic_ra, XK_Arabic_zain, XK_Arabic_seen ;
+CONST KeySym XK_Arabic_sheen, XK_Arabic_sad, XK_Arabic_dad, XK_Arabic_tah ;
+CONST KeySym XK_Arabic_zah, XK_Arabic_ain, XK_Arabic_ghain ;
+CONST KeySym XK_Arabic_tatweel, XK_Arabic_feh, XK_Arabic_qaf ;
+CONST KeySym XK_Arabic_kaf, XK_Arabic_lam, XK_Arabic_meem ;
+CONST KeySym XK_Arabic_noon, XK_Arabic_ha, XK_Arabic_heh, XK_Arabic_waw ;
+CONST KeySym XK_Arabic_alefmaksura, XK_Arabic_yeh, XK_Arabic_fathatan ;
+CONST KeySym XK_Arabic_dammatan, XK_Arabic_kasratan, XK_Arabic_fatha ;
+CONST KeySym XK_Arabic_damma, XK_Arabic_kasra, XK_Arabic_shadda ;
+CONST KeySym XK_Arabic_sukun, XK_Arabic_switch ;
+ENDIF

+IFDEF XK_CYRILLIC
+CONST KeySym XK_Serbian_dje, XK_Macedonia_gje, XK_Cyrillic_io ;
+CONST KeySym XK_Ukrainian_ie, XK_Ukranian_je, XK_Macedonia_dse ;
+CONST KeySym XK_Ukrainian_i, XK_Ukranian_i, XK_Ukrainian_yi ;
+CONST KeySym XK_Ukranian_yi, XK_Cyrillic_je, XK_Serbian_je ;
+CONST KeySym XK_Cyrillic_lje, XK_Serbian_lje, XK_Cyrillic_nje ;
+CONST KeySym XK_Serbian_nje, XK_Serbian_tshe, XK_Macedonia_kje ;
+CONST KeySym XK_Byelorussian_shortu, XK_Cyrillic_dzhe, XK_Serbian_dze ;
+CONST KeySym XK_numerosign, XK_Serbian_DJE, XK_Macedonia_GJE ;
+CONST KeySym XK_Cyrillic_IO, XK_Ukrainian_IE, XK_Ukranian_JE ;
+CONST KeySym XK_Macedonia_DSE, XK_Ukrainian_I, XK_Ukranian_I ;
+CONST KeySym XK_Ukrainian_YI, XK_Ukranian_YI, XK_Cyrillic_JE ;
+CONST KeySym XK_Serbian_JE, XK_Cyrillic_LJE, XK_Serbian_LJE ;
+CONST KeySym XK_Cyrillic_NJE, XK_Serbian_NJE, XK_Serbian_TSHE ;
+CONST KeySym XK_Macedonia_KJE, XK_Byelorussian_SHORTU ;
+CONST KeySym XK_Cyrillic_DZHE, XK_Serbian_DZE, XK_Cyrillic_yu ;
+CONST KeySym XK_Cyrillic_a, XK_Cyrillic_be, XK_Cyrillic_tse ;
+CONST KeySym XK_Cyrillic_de, XK_Cyrillic_ie, XK_Cyrillic_ef ;
+CONST KeySym XK_Cyrillic_ghe, XK_Cyrillic_ha, XK_Cyrillic_i ;
+CONST KeySym XK_Cyrillic_shorti, XK_Cyrillic_ka, XK_Cyrillic_el ;
+CONST KeySym XK_Cyrillic_em, XK_Cyrillic_en, XK_Cyrillic_o ;
+CONST KeySym XK_Cyrillic_pe, XK_Cyrillic_ya, XK_Cyrillic_er ;
+CONST KeySym XK_Cyrillic_es, XK_Cyrillic_te, XK_Cyrillic_u ;
+CONST KeySym XK_Cyrillic_zhe, XK_Cyrillic_ve, XK_Cyrillic_softsign ;
+CONST KeySym XK_Cyrillic_yeru, XK_Cyrillic_ze, XK_Cyrillic_sha ;
+CONST KeySym XK_Cyrillic_e, XK_Cyrillic_shcha, XK_Cyrillic_che ;
+CONST KeySym XK_Cyrillic_hardsign, XK_Cyrillic_YU, XK_Cyrillic_A ;
+CONST KeySym XK_Cyrillic_BE, XK_Cyrillic_TSE, XK_Cyrillic_DE ;
+CONST KeySym XK_Cyrillic_IE, XK_Cyrillic_EF, XK_Cyrillic_GHE ;
+CONST KeySym XK_Cyrillic_HA, XK_Cyrillic_I, XK_Cyrillic_SHORTI ;
+CONST KeySym XK_Cyrillic_KA, XK_Cyrillic_EL, XK_Cyrillic_EM ;
+CONST KeySym XK_Cyrillic_EN, XK_Cyrillic_O, XK_Cyrillic_PE ;
+CONST KeySym XK_Cyrillic_YA, XK_Cyrillic_ER, XK_Cyrillic_ES ;
+CONST KeySym XK_Cyrillic_TE, XK_Cyrillic_U, XK_Cyrillic_ZHE ;
+CONST KeySym XK_Cyrillic_VE, XK_Cyrillic_SOFTSIGN, XK_Cyrillic_YERU ;
+CONST KeySym XK_Cyrillic_ZE, XK_Cyrillic_SHA, XK_Cyrillic_E ;
+CONST KeySym XK_Cyrillic_SHCHA, XK_Cyrillic_CHE, XK_Cyrillic_HARDSIGN ;
+ENDIF

+IFDEF XK_GREEK
+CONST KeySym XK_Greek_ALPHAaccent, XK_Greek_EPSILONaccent ;
+CONST KeySym XK_Greek_ETAaccent, XK_Greek_IOTAaccent ;
+CONST KeySym XK_Greek_IOTAdiaeresis, XK_Greek_OMICRONaccent ;
+CONST KeySym XK_Greek_UPSILONaccent, XK_Greek_UPSILONdieresis ;
+CONST KeySym XK_Greek_OMEGAaccent, XK_Greek_accentdieresis ;
+CONST KeySym XK_Greek_horizbar, XK_Greek_alphaaccent ;
+CONST KeySym XK_Greek_epsilonaccent, XK_Greek_etaaccent ;
+CONST KeySym XK_Greek_iotaaccent, XK_Greek_iotadieresis ;
+CONST KeySym XK_Greek_iotaaccentdieresis, XK_Greek_omicronaccent ;
+CONST KeySym XK_Greek_upsilonaccent, XK_Greek_upsilondieresis ;
+CONST KeySym XK_Greek_upsilonaccentdieresis, XK_Greek_omegaaccent ;
+CONST KeySym XK_Greek_ALPHA, XK_Greek_BETA, XK_Greek_GAMMA ;
+CONST KeySym XK_Greek_DELTA, XK_Greek_EPSILON, XK_Greek_ZETA ;
+CONST KeySym XK_Greek_ETA, XK_Greek_THETA, XK_Greek_IOTA ;
+CONST KeySym XK_Greek_KAPPA, XK_Greek_LAMDA, XK_Greek_LAMBDA ;
+CONST KeySym XK_Greek_MU, XK_Greek_NU, XK_Greek_XI, XK_Greek_OMICRON ;
+CONST KeySym XK_Greek_PI, XK_Greek_RHO, XK_Greek_SIGMA, XK_Greek_TAU ;
+CONST KeySym XK_Greek_UPSILON, XK_Greek_PHI, XK_Greek_CHI ;
+CONST KeySym XK_Greek_PSI, XK_Greek_OMEGA, XK_Greek_alpha ;
+CONST KeySym XK_Greek_beta, XK_Greek_gamma, XK_Greek_delta ;
+CONST KeySym XK_Greek_epsilon, XK_Greek_zeta, XK_Greek_eta ;
+CONST KeySym XK_Greek_theta, XK_Greek_iota, XK_Greek_kappa ;
+CONST KeySym XK_Greek_lamda, XK_Greek_lambda, XK_Greek_mu ;
+CONST KeySym XK_Greek_nu, XK_Greek_xi, XK_Greek_omicron ;
+CONST KeySym XK_Greek_pi, XK_Greek_rho, XK_Greek_sigma ;
+CONST KeySym XK_Greek_finalsmallsigma, XK_Greek_tau, XK_Greek_upsilon ;
+CONST KeySym XK_Greek_phi, XK_Greek_chi, XK_Greek_psi ;
+CONST KeySym XK_Greek_omega, XK_Greek_switch ;
+ENDIF

+IFDEF XK_TECHNICAL
+CONST KeySym XK_leftradical, XK_topleftradical, XK_horizconnector ;
+CONST KeySym XK_topintegral, XK_botintegral, XK_vertconnector ;
+CONST KeySym XK_topleftsqbracket, XK_botleftsqbracket ;
+CONST KeySym XK_toprightsqbracket, XK_botrightsqbracket ;
+CONST KeySym XK_topleftparens, XK_botleftparens, XK_toprightparens ;
+CONST KeySym XK_botrightparens, XK_leftmiddlecurlybrace ;
+CONST KeySym XK_rightmiddlecurlybrace, XK_topleftsummation ;
+CONST KeySym XK_botleftsummation, XK_topvertsummationconnector ;
+CONST KeySym XK_botvertsummationconnector, XK_toprightsummation ;
+CONST KeySym XK_botrightsummation, XK_rightmiddlesummation ;
+CONST KeySym XK_lessthanequal, XK_notequal, XK_greaterthanequal ;
+CONST KeySym XK_integral, XK_therefore, XK_variation, XK_infinity ;
+CONST KeySym XK_nabla, XK_approximate, XK_similarequal, XK_ifonlyif ;
+CONST KeySym XK_implies, XK_identical, XK_radical, XK_includedin ;
+CONST KeySym XK_includes, XK_intersection, XK_union, XK_logicaland ;
+CONST KeySym XK_logicalor, XK_partialderivative, XK_function ;
+CONST KeySym XK_leftarrow, XK_uparrow, XK_rightarrow, XK_downarrow ;
+ENDIF

+IFDEF XK_SPECIAL
+CONST KeySym XK_blank, XK_soliddiamond, XK_checkerboard, XK_ht ;
+CONST KeySym XK_ff, XK_cr, XK_lf, XK_nl, XK_vt, XK_lowrightcorner ;
+CONST KeySym XK_uprightcorner, XK_upleftcorner, XK_lowleftcorner ;
+CONST KeySym XK_crossinglines, XK_horizlinescan1, XK_horizlinescan3 ;
+CONST KeySym XK_horizlinescan5, XK_horizlinescan7, XK_horizlinescan9 ;
+CONST KeySym XK_leftt, XK_rightt, XK_bott, XK_topt, XK_vertbar ;
+ENDIF

+IFDEF XK_PUBLISHING
+CONST KeySym XK_emspace, XK_enspace, XK_em3space, XK_em4space ;
+CONST KeySym XK_digitspace, XK_punctspace, XK_thinspace, XK_hairspace ;
+CONST KeySym XK_emdash, XK_endash, XK_signifblank, XK_ellipsis ;
+CONST KeySym XK_doubbaselinedot, XK_onethird, XK_twothirds ;
+CONST KeySym XK_onefifth, XK_twofifths, XK_threefifths, XK_fourfifths ;
+CONST KeySym XK_onesixth, XK_fivesixths, XK_careof, XK_figdash ;
+CONST KeySym XK_leftanglebracket, XK_decimalpoint, XK_rightanglebracket ;
+CONST KeySym XK_marker, XK_oneeighth, XK_threeeighths, XK_fiveeighths ;
+CONST KeySym XK_seveneighths, XK_trademark, XK_signaturemark ;
+CONST KeySym XK_trademarkincircle, XK_leftopentriangle ;
+CONST KeySym XK_rightopentriangle, XK_emopencircle, XK_emopenrectangle ;
+CONST KeySym XK_leftsinglequotemark, XK_rightsinglequotemark ;
+CONST KeySym XK_leftdoublequotemark, XK_rightdoublequotemark ;
+CONST KeySym XK_prescription, XK_minutes, XK_seconds, XK_latincross ;
+CONST KeySym XK_hexagram, XK_filledrectbullet, XK_filledlefttribullet ;
+CONST KeySym XK_filledrighttribullet, XK_emfilledcircle, XK_emfilledrect ;
+CONST KeySym XK_enopencircbullet, XK_enopensquarebullet ;
+CONST KeySym XK_openrectbullet, XK_opentribulletup, XK_opentribulletdown ;
+CONST KeySym XK_openstar, XK_enfilledcircbullet, XK_enfilledsqbullet ;
+CONST KeySym XK_filledtribulletup, XK_filledtribulletdown ;
+CONST KeySym XK_leftpointer, XK_rightpointer, XK_club, XK_diamond ;
+CONST KeySym XK_heart, XK_maltesecross, XK_dagger, XK_doubledagger ;
+CONST KeySym XK_checkmark, XK_ballotcross, XK_musicalsharp ;
+CONST KeySym XK_musicalflat, XK_malesymbol, XK_femalesymbol ;
+CONST KeySym XK_telephone, XK_telephonerecorder, XK_phonographcopyright ;
+CONST KeySym XK_caret, XK_singlelowquotemark, XK_doublelowquotemark ;
+CONST KeySym XK_cursor ;
+ENDIF

+IFDEF XK_APL
+CONST KeySym XK_leftcaret, XK_rightcaret, XK_downcaret, XK_upcaret ;
+CONST KeySym XK_overbar, XK_downtack, XK_upshoe, XK_downstile ;
+CONST KeySym XK_underbar, XK_jot, XK_quad, XK_uptack, XK_circle ;
+CONST KeySym XK_upstile, XK_downshoe, XK_rightshoe, XK_leftshoe ;
+CONST KeySym XK_lefttack, XK_righttack ;
+ENDIF

+IFDEF XK_HEBREW
+CONST KeySym XK_hebrew_doublelowline, XK_hebrew_aleph, XK_hebrew_bet ;
+CONST KeySym XK_hebrew_beth, XK_hebrew_gimel, XK_hebrew_gimmel ;
+CONST KeySym XK_hebrew_dalet, XK_hebrew_daleth, XK_hebrew_he ;
+CONST KeySym XK_hebrew_waw, XK_hebrew_zain, XK_hebrew_zayin ;
+CONST KeySym XK_hebrew_chet, XK_hebrew_het, XK_hebrew_tet ;
+CONST KeySym XK_hebrew_teth, XK_hebrew_yod, XK_hebrew_finalkaph ;
+CONST KeySym XK_hebrew_kaph, XK_hebrew_lamed, XK_hebrew_finalmem ;
+CONST KeySym XK_hebrew_mem, XK_hebrew_finalnun, XK_hebrew_nun ;
+CONST KeySym XK_hebrew_samech, XK_hebrew_samekh, XK_hebrew_ayin ;
+CONST KeySym XK_hebrew_finalpe, XK_hebrew_pe, XK_hebrew_finalzade ;
+CONST KeySym XK_hebrew_finalzadi, XK_hebrew_zade, XK_hebrew_zadi ;
+CONST KeySym XK_hebrew_qoph, XK_hebrew_kuf, XK_hebrew_resh ;
+CONST KeySym XK_hebrew_shin, XK_hebrew_taw, XK_hebrew_taf ;
+CONST KeySym XK_Hebrew_switch ;
+ENDIF
