/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
    LEXICAL TOKEN TABLES

    This file gives the list of lexical tokens.  It is included from several
    points with the macro LEX_TOKEN defined so as to extract the desired
    information.  The arguments are as follows:

	1.  The token number, corresponding to the values given in syntax.h.
	2.  The associated token name, if any.
	3.  A value indicating the semantic class the token is likely to
	    start (see predict.c).

    The list of tokens in the grammars, syntax.sid and psyntax.sid, need
    to kept in step with this list.
*/


#ifdef LEX_TOKEN


/*
    MISCELLANEOUS TOKENS

    These tokens describe the identifiers, literals and other miscellaneous
    lexical tokens.  The target dependent conditionals are included in this
    group because they have an associated value.
*/

LEX_TOKEN(lex_unknown, "<unknown>", TOK_NONE)

LEX_TOKEN(lex_identifier, "<id>", TOK_EXP)
LEX_TOKEN(lex_type_Hname, "<type>", TOK_TYPE)
LEX_TOKEN(lex_namespace_Hname, "<namespace>", TOK_NONE)
LEX_TOKEN(lex_statement_Hname, "<stmt>", TOK_STATEMENT)
LEX_TOKEN(lex_destructor_Hname, "<destructor>", TOK_EXP)
LEX_TOKEN(lex_template_Hid, "<id>", TOK_EXP)
LEX_TOKEN(lex_template_Htype, "<type>", TOK_TYPE)

LEX_TOKEN(lex_nested_Hname, "<name>::", TOK_NESTED_NAME)
LEX_TOKEN(lex_full_Hname, "::<name>::", TOK_FULL_NAME)
LEX_TOKEN(lex_nested_Hname_Hstar, "<class>::*", TOK_NONE)
LEX_TOKEN(lex_full_Hname_Hstar, "::<class>::*", TOK_NONE)

LEX_TOKEN(lex_char_Hlit, "<char>", TOK_EXP)
LEX_TOKEN(lex_wchar_Hlit, "<wchar>", TOK_EXP)
LEX_TOKEN(lex_string_Hlit, "<string>", TOK_EXP)
LEX_TOKEN(lex_wstring_Hlit, "<wstring>", TOK_EXP)
LEX_TOKEN(lex_integer_Hlit, "<int>", TOK_EXP)

LEX_TOKEN(lex_char_Hexp, "<char>", TOK_EXP)
LEX_TOKEN(lex_wchar_Hexp, "<wchar>", TOK_EXP)
LEX_TOKEN(lex_string_Hexp, "<string>", TOK_EXP)
LEX_TOKEN(lex_wstring_Hexp, "<wstring>", TOK_EXP)
LEX_TOKEN(lex_integer_Hexp, "<int>", TOK_EXP)
LEX_TOKEN(lex_floating_Hexp, "<float>", TOK_EXP)

LEX_TOKEN(lex_complex_Hexp, "<exp>", TOK_EXP)
LEX_TOKEN(lex_complex_Hstmt, "<stmt>", TOK_STATEMENT)
LEX_TOKEN(lex_complex_Htype, "<type>", TOK_TYPE)

LEX_TOKEN(lex_hash_Hif, "#if", TOK_STATEMENT)
LEX_TOKEN(lex_hash_Helif, "#elif", TOK_STATEMENT)
LEX_TOKEN(lex_hash_Helse, "#else", TOK_STATEMENT)
LEX_TOKEN(lex_hash_Hendif, "#endif", TOK_STATEMENT)
LEX_TOKEN(lex_hash_Hpragma, "#pragma", TOK_DECLARATION)

LEX_TOKEN(lex_newline, "<newline>", TOK_NONE)
LEX_TOKEN(lex_eof, "<eof>", TOK_NONE)


/*
    C SYMBOL TOKENS

    These tokens describe the C symbols and punctuation.
*/

LEX_TOKEN(lex_and_H1, "&", TOK_EXP)
LEX_TOKEN(lex_and_Heq_H1, "&=", TOK_NONE)
LEX_TOKEN(lex_arrow, "->", TOK_NONE)
LEX_TOKEN(lex_assign, "=", TOK_NONE)
LEX_TOKEN(lex_backslash, "\\", TOK_NONE)
LEX_TOKEN(lex_close_Hbrace_H1, "}", TOK_NONE)
LEX_TOKEN(lex_close_Hround, ")", TOK_NONE)
LEX_TOKEN(lex_close_Hsquare_H1, "]", TOK_NONE)
LEX_TOKEN(lex_colon, ":", TOK_NONE)
LEX_TOKEN(lex_comma, ",", TOK_NONE)
LEX_TOKEN(lex_compl_H1, "~", TOK_EXP)
LEX_TOKEN(lex_div, "/", TOK_NONE)
LEX_TOKEN(lex_div_Heq, "/=", TOK_NONE)
LEX_TOKEN(lex_dot, ".", TOK_NONE)
LEX_TOKEN(lex_ellipsis, "...", TOK_NONE)
LEX_TOKEN(lex_eq, "==", TOK_NONE)
LEX_TOKEN(lex_greater, ">", TOK_NONE)
LEX_TOKEN(lex_greater_Heq, ">=", TOK_NONE)
LEX_TOKEN(lex_hash_H1, "#", TOK_NONE)
LEX_TOKEN(lex_hash_Hhash_H1, "##", TOK_NONE)
LEX_TOKEN(lex_less, "<", TOK_NONE)
LEX_TOKEN(lex_less_Heq, "<=", TOK_NONE)
LEX_TOKEN(lex_logical_Hand_H1, "&&", TOK_NONE)
LEX_TOKEN(lex_logical_Hor_H1, "||", TOK_NONE)
LEX_TOKEN(lex_lshift, "<<", TOK_NONE)
LEX_TOKEN(lex_lshift_Heq, "<<=", TOK_NONE)
LEX_TOKEN(lex_minus, "-", TOK_EXP)
LEX_TOKEN(lex_minus_Heq, "-=", TOK_NONE)
LEX_TOKEN(lex_minus_Hminus, "--", TOK_EXP)
LEX_TOKEN(lex_not_H1, "!", TOK_EXP)
LEX_TOKEN(lex_not_Heq_H1, "!=", TOK_NONE)
LEX_TOKEN(lex_open_Hbrace_H1, "{", TOK_NONE)
LEX_TOKEN(lex_open_Hround, "(", TOK_NONE)
LEX_TOKEN(lex_open_Hsquare_H1, "[", TOK_NONE)
LEX_TOKEN(lex_or_H1, "|", TOK_NONE)
LEX_TOKEN(lex_or_Heq_H1, "|=", TOK_NONE)
LEX_TOKEN(lex_plus, "+", TOK_EXP)
LEX_TOKEN(lex_plus_Heq, "+=", TOK_NONE)
LEX_TOKEN(lex_plus_Hplus, "++", TOK_EXP)
LEX_TOKEN(lex_question, "?", TOK_NONE)
LEX_TOKEN(lex_rem, "%", TOK_NONE)
LEX_TOKEN(lex_rem_Heq, "%=", TOK_NONE)
LEX_TOKEN(lex_rshift, ">>", TOK_NONE)
LEX_TOKEN(lex_rshift_Heq, ">>=", TOK_NONE)
LEX_TOKEN(lex_semicolon, ";", TOK_NONE)
LEX_TOKEN(lex_star, "*", TOK_EXP)
LEX_TOKEN(lex_star_Heq, "*=", TOK_NONE)
LEX_TOKEN(lex_xor_H1, "^", TOK_NONE)
LEX_TOKEN(lex_xor_Heq_H1, "^=", TOK_NONE)


/*
    ADDITIONAL C++ SYMBOL TOKENS

    These tokens describe the additional C++ symbols.
*/

LEX_TOKEN(lex_arrow_Hstar, "->*", TOK_NONE)
LEX_TOKEN(lex_colon_Hcolon, "::", TOK_FULL_NAME)
LEX_TOKEN(lex_dot_Hstar, ".*", TOK_NONE)


/*
    ADDITIONAL SYMBOL TOKENS

    These tokens describe the additional extension symbols.
*/

LEX_TOKEN(lex_abs, "+?", TOK_EXP)
LEX_TOKEN(lex_max, ">?", TOK_NONE)
LEX_TOKEN(lex_min, "<?", TOK_NONE)


/*
    DIGRAPH TOKENS

    These tokens describe the digraphs.
*/

LEX_TOKEN(lex_close_Hbrace_H2, "%>", TOK_NONE)
LEX_TOKEN(lex_close_Hsquare_H2, ":>", TOK_NONE)
LEX_TOKEN(lex_hash_H2, "%:", TOK_NONE)
LEX_TOKEN(lex_hash_Hhash_H2, "%:%:", TOK_NONE)
LEX_TOKEN(lex_open_Hbrace_H2, "<%", TOK_NONE)
LEX_TOKEN(lex_open_Hsquare_H2, "<:", TOK_NONE)


/*
    C KEYWORD TOKENS

    These tokens describe the C keywords.
*/

LEX_TOKEN(lex_auto, "auto", TOK_DECL_SPEC)
LEX_TOKEN(lex_break, "break", TOK_STATEMENT)
LEX_TOKEN(lex_case, "case", TOK_STATEMENT)
LEX_TOKEN(lex_char, "char", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_const, "const", TOK_TYPE_SPEC)
LEX_TOKEN(lex_continue, "continue", TOK_STATEMENT)
LEX_TOKEN(lex_default, "default", TOK_STATEMENT)
LEX_TOKEN(lex_do, "do", TOK_STATEMENT)
LEX_TOKEN(lex_double, "double", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_else, "else", TOK_STATEMENT)
LEX_TOKEN(lex_enum, "enum", TOK_TYPE_KEY)
LEX_TOKEN(lex_extern, "extern", TOK_EXTERN)
LEX_TOKEN(lex_float, "float", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_for, "for", TOK_STATEMENT)
LEX_TOKEN(lex_goto, "goto", TOK_STATEMENT)
LEX_TOKEN(lex_if, "if", TOK_STATEMENT)
LEX_TOKEN(lex_int, "int", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_long, "long", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_register, "register", TOK_DECL_SPEC)
LEX_TOKEN(lex_return, "return", TOK_STATEMENT)
LEX_TOKEN(lex_short, "short", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_signed, "signed", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_sizeof, "sizeof", TOK_EXP)
LEX_TOKEN(lex_static, "static", TOK_DECL_SPEC)
LEX_TOKEN(lex_struct, "struct", TOK_TYPE_KEY)
LEX_TOKEN(lex_switch, "switch", TOK_STATEMENT)
LEX_TOKEN(lex_typedef, "typedef", TOK_DECL_SPEC)
LEX_TOKEN(lex_union, "union", TOK_TYPE_KEY)
LEX_TOKEN(lex_unsigned, "unsigned", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_void, "void", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_volatile, "volatile", TOK_TYPE_SPEC)
LEX_TOKEN(lex_while, "while", TOK_STATEMENT)


/*
    ADDITIONAL C++ KEYWORD TOKENS

    These tokens describe the additional C++ keywords.
*/

LEX_TOKEN(lex_asm, "asm", TOK_ASM)
LEX_TOKEN(lex_bool, "bool", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_catch, "catch", TOK_STATEMENT)
LEX_TOKEN(lex_class, "class", TOK_TYPE_KEY)
LEX_TOKEN(lex_const_Hcast, "const_cast", TOK_EXP)
LEX_TOKEN(lex_delete, "delete", TOK_EXP)
LEX_TOKEN(lex_dynamic_Hcast, "dynamic_cast", TOK_EXP)
LEX_TOKEN(lex_explicit, "explicit", TOK_DECL_SPEC)
LEX_TOKEN(lex_export, "export", TOK_DECLARATION)
LEX_TOKEN(lex_false, "false", TOK_EXP)
LEX_TOKEN(lex_friend, "friend", TOK_DECL_SPEC)
LEX_TOKEN(lex_inline, "inline", TOK_DECL_SPEC)
LEX_TOKEN(lex_mutable, "mutable", TOK_DECL_SPEC)
LEX_TOKEN(lex_namespace, "namespace", TOK_DECLARATION)
LEX_TOKEN(lex_new, "new", TOK_EXP)
LEX_TOKEN(lex_operator, "operator", TOK_EXP)
LEX_TOKEN(lex_private, "private", TOK_NONE)
LEX_TOKEN(lex_protected, "protected", TOK_NONE)
LEX_TOKEN(lex_public, "public", TOK_NONE)
LEX_TOKEN(lex_reinterpret_Hcast, "reinterpret_cast", TOK_EXP)
LEX_TOKEN(lex_static_Hcast, "static_cast", TOK_EXP)
LEX_TOKEN(lex_template, "template", TOK_DECLARATION)
LEX_TOKEN(lex_this, "this", TOK_EXP)
LEX_TOKEN(lex_throw, "throw", TOK_NONE)
LEX_TOKEN(lex_true, "true", TOK_EXP)
LEX_TOKEN(lex_try, "try", TOK_STATEMENT)
LEX_TOKEN(lex_typeid, "typeid", TOK_EXP)
LEX_TOKEN(lex_typename, "typename", TOK_TYPE_KEY)
LEX_TOKEN(lex_using, "using", TOK_DECLARATION)
LEX_TOKEN(lex_virtual, "virtual", TOK_DECL_SPEC)
LEX_TOKEN(lex_wchar_Ht, "wchar_t", TOK_SIMPLE_TYPE)


/*
    ISO KEYWORD TOKENS

    These tokens describe the ISO keywords which give alternative
    representations of various symbols.
*/

LEX_TOKEN(lex_and_H2, "bitand", TOK_EXP)
LEX_TOKEN(lex_and_Heq_H2, "and_eq", TOK_NONE)
LEX_TOKEN(lex_compl_H2, "compl", TOK_EXP)
LEX_TOKEN(lex_logical_Hand_H2, "and", TOK_NONE)
LEX_TOKEN(lex_logical_Hor_H2, "or", TOK_NONE)
LEX_TOKEN(lex_not_H2, "not", TOK_EXP)
LEX_TOKEN(lex_not_Heq_H2, "not_eq", TOK_NONE)
LEX_TOKEN(lex_or_H2, "bitor", TOK_NONE)
LEX_TOKEN(lex_or_Heq_H2, "or_eq", TOK_NONE)
LEX_TOKEN(lex_xor_H2, "xor", TOK_NONE)
LEX_TOKEN(lex_xor_Heq_H2, "xor_eq", TOK_NONE)


/*
    NON-STANDARD KEYWORD TOKENS

    These keywords represent the non-standard keywords.
*/

LEX_TOKEN(lex_accept, "accept", TOK_NONE)
LEX_TOKEN(lex_after, "after", TOK_NONE)
LEX_TOKEN(lex_alignof, "alignof", TOK_EXP)
LEX_TOKEN(lex_all, "all", TOK_NONE)
LEX_TOKEN(lex_allow, "allow", TOK_NONE)
LEX_TOKEN(lex_ambiguous, "ambiguous", TOK_NONE)
LEX_TOKEN(lex_analysis, "analysis", TOK_NONE)
LEX_TOKEN(lex_anonymous, "anonymous", TOK_NONE)
LEX_TOKEN(lex_argument, "argument", TOK_NONE)
LEX_TOKEN(lex_arith_Hcap, "ARITHMETIC", TOK_NONE)
LEX_TOKEN(lex_array, "array", TOK_NONE)
LEX_TOKEN(lex_as, "as", TOK_NONE)
LEX_TOKEN(lex_assert, "assert", TOK_NONE)
LEX_TOKEN(lex_assignment, "assignment", TOK_NONE)
LEX_TOKEN(lex_begin, "begin", TOK_NONE)
LEX_TOKEN(lex_bitfield, "bitfield", TOK_NONE)
LEX_TOKEN(lex_block, "block", TOK_NONE)
LEX_TOKEN(lex_bottom, "bottom", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_cast, "cast", TOK_NONE)
LEX_TOKEN(lex_character, "character", TOK_NONE)
LEX_TOKEN(lex_class_Hcap, "CLASS", TOK_NONE)
LEX_TOKEN(lex_code, "code", TOK_NONE)
LEX_TOKEN(lex_comment, "comment", TOK_NONE)
LEX_TOKEN(lex_compatible, "compatible", TOK_NONE)
LEX_TOKEN(lex_complete, "complete", TOK_NONE)
LEX_TOKEN(lex_compute, "compute", TOK_NONE)
LEX_TOKEN(lex_conditional, "conditional", TOK_NONE)
LEX_TOKEN(lex_conversion, "conversion", TOK_NONE)
LEX_TOKEN(lex_decimal, "decimal", TOK_NONE)
LEX_TOKEN(lex_decl, "declaration", TOK_NONE)
LEX_TOKEN(lex_define, "define", TOK_NONE)
LEX_TOKEN(lex_define_Hcap, "DEFINE", TOK_NONE)
LEX_TOKEN(lex_defined, "defined", TOK_EXP)
LEX_TOKEN(lex_definition, "definition", TOK_NONE)
LEX_TOKEN(lex_depth, "depth", TOK_NONE)
LEX_TOKEN(lex_directive, "directive", TOK_NONE)
LEX_TOKEN(lex_directory, "directory", TOK_NONE)
LEX_TOKEN(lex_disallow, "disallow", TOK_NONE)
LEX_TOKEN(lex_discard, "discard", TOK_EXP)
LEX_TOKEN(lex_dollar, "dollar", TOK_NONE)
LEX_TOKEN(lex_either, "either", TOK_NONE)
LEX_TOKEN(lex_elif, "elif", TOK_EXP)
LEX_TOKEN(lex_ellipsis_Hexp, "...", TOK_NONE)
LEX_TOKEN(lex_end, "end", TOK_NONE)
LEX_TOKEN(lex_endif, "endif", TOK_EXP)
LEX_TOKEN(lex_environment, "environment", TOK_NONE)
LEX_TOKEN(lex_equality, "equality", TOK_NONE)
LEX_TOKEN(lex_error, "error", TOK_NONE)
LEX_TOKEN(lex_escape, "escape", TOK_NONE)
LEX_TOKEN(lex_exhaustive, "exhaustive", TOK_NONE)
LEX_TOKEN(lex_exp_Hcap, "EXP", TOK_NONE)
LEX_TOKEN(lex_explain, "explain", TOK_DECLARATION)
LEX_TOKEN(lex_extend, "extend", TOK_NONE)
LEX_TOKEN(lex_external, "external", TOK_NONE)
LEX_TOKEN(lex_extra, "extra", TOK_NONE)
LEX_TOKEN(lex_fall, "fall", TOK_NONE)
LEX_TOKEN(lex_file, "file", TOK_NONE)
LEX_TOKEN(lex_float_Hcap, "FLOAT", TOK_NONE)
LEX_TOKEN(lex_forward, "forward", TOK_NONE)
LEX_TOKEN(lex_func_Hcap, "FUNC", TOK_NONE)
LEX_TOKEN(lex_function, "function", TOK_NONE)
LEX_TOKEN(lex_hexadecimal, "hexadecimal", TOK_NONE)
LEX_TOKEN(lex_hiding, "hiding", TOK_NONE)
LEX_TOKEN(lex_ident, "ident", TOK_NONE)
LEX_TOKEN(lex_identif, "identifier", TOK_NONE)
LEX_TOKEN(lex_ifdef, "ifdef", TOK_EXP)
LEX_TOKEN(lex_ifndef, "ifndef", TOK_EXP)
LEX_TOKEN(lex_ignore, "ignore", TOK_NONE)
LEX_TOKEN(lex_implement, "implement", TOK_NONE)
LEX_TOKEN(lex_implicit, "implicit", TOK_NONE)
LEX_TOKEN(lex_import, "import", TOK_NONE)
LEX_TOKEN(lex_include, "include", TOK_NONE)
LEX_TOKEN(lex_includes, "includes", TOK_NONE)
LEX_TOKEN(lex_include_Hnext, "include_next", TOK_NONE)
LEX_TOKEN(lex_incompatible, "incompatible", TOK_NONE)
LEX_TOKEN(lex_incomplete, "incomplete", TOK_NONE)
LEX_TOKEN(lex_indented, "indented", TOK_NONE)
LEX_TOKEN(lex_initialization, "initialization", TOK_NONE)
LEX_TOKEN(lex_integer, "integer", TOK_NONE)
LEX_TOKEN(lex_interface, "interface", TOK_NONE)
LEX_TOKEN(lex_internal, "internal", TOK_NONE)
LEX_TOKEN(lex_into, "into", TOK_NONE)
LEX_TOKEN(lex_int_Hcap, "INTEGER", TOK_NONE)
LEX_TOKEN(lex_keyword, "keyword", TOK_NONE)
LEX_TOKEN(lex_limit, "limit", TOK_NONE)
LEX_TOKEN(lex_line, "line", TOK_NONE)
LEX_TOKEN(lex_linkage, "linkage", TOK_NONE)
LEX_TOKEN(lex_lit, "literal", TOK_NONE)
LEX_TOKEN(lex_longlong, "longlong", TOK_NONE)
LEX_TOKEN(lex_lvalue, "lvalue", TOK_NONE)
LEX_TOKEN(lex_macro, "macro", TOK_NONE)
LEX_TOKEN(lex_main, "main", TOK_NONE)
LEX_TOKEN(lex_member, "member", TOK_NONE)
LEX_TOKEN(lex_member_Hcap, "MEMBER", TOK_NONE)
LEX_TOKEN(lex_name, "name", TOK_NONE)
LEX_TOKEN(lex_nat_Hcap, "NAT", TOK_NONE)
LEX_TOKEN(lex_nested, "nested", TOK_NONE)
LEX_TOKEN(lex_nline, "nline", TOK_NONE)
LEX_TOKEN(lex_no, "no", TOK_NONE)
LEX_TOKEN(lex_no_Hdef, "no_def", TOK_NONE)
LEX_TOKEN(lex_object, "object", TOK_NONE)
LEX_TOKEN(lex_octal, "octal", TOK_NONE)
LEX_TOKEN(lex_of, "of", TOK_NONE)
LEX_TOKEN(lex_off, "off", TOK_NONE)
LEX_TOKEN(lex_on, "on", TOK_NONE)
LEX_TOKEN(lex_option, "option", TOK_NONE)
LEX_TOKEN(lex_overflow, "overflow", TOK_NONE)
LEX_TOKEN(lex_overload, "overload", TOK_DECL_SPEC)
LEX_TOKEN(lex_pointer, "pointer", TOK_NONE)
LEX_TOKEN(lex_postpone, "postpone", TOK_NONE)
LEX_TOKEN(lex_pragma, "pragma", TOK_NONE)
LEX_TOKEN(lex_precedence, "precedence", TOK_NONE)
LEX_TOKEN(lex_preserve, "preserve", TOK_NONE)
LEX_TOKEN(lex_printf, "printf", TOK_NONE)
LEX_TOKEN(lex_proc_Hcap, "PROC", TOK_NONE)
LEX_TOKEN(lex_promote, "promote", TOK_NONE)
LEX_TOKEN(lex_promoted, "promoted", TOK_NONE)
LEX_TOKEN(lex_prototype, "prototype", TOK_NONE)
LEX_TOKEN(lex_ptrdiff_Ht, "ptrdiff_t", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_qualifier, "qualifier", TOK_NONE)
LEX_TOKEN(lex_quote, "quote", TOK_NONE)
LEX_TOKEN(lex_reachable, "reachable", TOK_STATEMENT)
LEX_TOKEN(lex_reference, "reference", TOK_NONE)
LEX_TOKEN(lex_reject, "reject", TOK_NONE)
LEX_TOKEN(lex_representation, "representation", TOK_NONE)
LEX_TOKEN(lex_reset, "reset", TOK_NONE)
LEX_TOKEN(lex_resolution, "resolution", TOK_NONE)
LEX_TOKEN(lex_rvalue, "rvalue", TOK_NONE)
LEX_TOKEN(lex_scalar_Hcap, "SCALAR", TOK_NONE)
LEX_TOKEN(lex_scanf, "scanf", TOK_NONE)
LEX_TOKEN(lex_set, "set", TOK_EXP)
LEX_TOKEN(lex_size_Ht, "size_t", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_size_Ht_H2, "__size_t", TOK_SIMPLE_TYPE)
LEX_TOKEN(lex_sort, "sort", TOK_NONE)
LEX_TOKEN(lex_std, "std", TOK_NONE)
LEX_TOKEN(lex_stmt_Hcap, "STATEMENT", TOK_NONE)
LEX_TOKEN(lex_string, "string", TOK_NONE)
LEX_TOKEN(lex_struct_Hcap, "STRUCT", TOK_NONE)
LEX_TOKEN(lex_suspend, "suspend", TOK_NONE)
LEX_TOKEN(lex_tag, "tag", TOK_NONE)
LEX_TOKEN(lex_tag_Hcap, "TAG", TOK_NONE)
LEX_TOKEN(lex_tendra, "TenDRA", TOK_NONE)
LEX_TOKEN(lex_text, "text", TOK_NONE)
LEX_TOKEN(lex_this_Hname, "<this>", TOK_EXP)
LEX_TOKEN(lex_token, "token", TOK_NONE)
LEX_TOKEN(lex_type, "type", TOK_NONE)
LEX_TOKEN(lex_type_Hcap, "TYPE", TOK_NONE)
LEX_TOKEN(lex_typeof, "typeof", TOK_NONE)
LEX_TOKEN(lex_un_Hknown, "unknown", TOK_NONE)
LEX_TOKEN(lex_unassert, "unassert", TOK_NONE)
LEX_TOKEN(lex_undef, "undef", TOK_NONE)
LEX_TOKEN(lex_unify, "unify", TOK_NONE)
LEX_TOKEN(lex_union_Hcap, "UNION", TOK_NONE)
LEX_TOKEN(lex_unmatched, "unmatched", TOK_NONE)
LEX_TOKEN(lex_unpostpone, "unpostpone", TOK_NONE)
LEX_TOKEN(lex_unreachable, "unreachable", TOK_STATEMENT)
LEX_TOKEN(lex_unused, "unused", TOK_EXP)
LEX_TOKEN(lex_use, "use", TOK_NONE)
LEX_TOKEN(lex_value, "value", TOK_NONE)
LEX_TOKEN(lex_variable, "variable", TOK_NONE)
LEX_TOKEN(lex_variety_Hcap, "VARIETY", TOK_NONE)
LEX_TOKEN(lex_volatile_Ht, "volatile_t", TOK_NONE)
LEX_TOKEN(lex_vtable, "vtable", TOK_EXP)
LEX_TOKEN(lex_warning, "warning", TOK_NONE)
LEX_TOKEN(lex_weak, "weak", TOK_NONE)
LEX_TOKEN(lex_writeable, "writeable", TOK_NONE)
LEX_TOKEN(lex_zzzz, "<dummy>", TOK_NONE)


/*
    MISCELLANEOUS SYMBOLS

    These tokens describe certain symbols which are used in various
    circumstances.
*/

LEX_TOKEN(lex_array_Hop, "[]", TOK_NONE)
LEX_TOKEN(lex_builtin_Hfile, "#file", TOK_NONE)
LEX_TOKEN(lex_builtin_Hline, "#line", TOK_NONE)
LEX_TOKEN(lex_close_Htemplate, ">", TOK_NONE)
LEX_TOKEN(lex_cond_Hop, "?:", TOK_NONE)
LEX_TOKEN(lex_delete_Hfull, "::delete", TOK_NONE)
LEX_TOKEN(lex_delete_Harray, "delete[]", TOK_NONE)
LEX_TOKEN(lex_delete_Harray_Hfull, "::delete[]", TOK_NONE)
LEX_TOKEN(lex_func_Hop, "()", TOK_NONE)
LEX_TOKEN(lex_hash_Hop, "#", TOK_NONE)
LEX_TOKEN(lex_hash_Hhash_Hop, "##", TOK_NONE)
LEX_TOKEN(lex_inset_Hstart, "#pragma", TOK_NONE)
LEX_TOKEN(lex_inset_Hend, "<newline>", TOK_NONE)
LEX_TOKEN(lex_macro_Harg, "<argument>", TOK_NONE)
LEX_TOKEN(lex_new_Hfull, "::new", TOK_NONE)
LEX_TOKEN(lex_new_Harray, "new[]", TOK_NONE)
LEX_TOKEN(lex_new_Harray_Hfull, "::new[]", TOK_NONE)
LEX_TOKEN(lex_open_Hinit, "(", TOK_NONE)
LEX_TOKEN(lex_open_Htemplate, "<", TOK_NONE)
LEX_TOKEN(lex_zzzzzz, "<dummy>", TOK_NONE)


#endif /* LEX_TOKEN */


/*
    TOKEN GROUPS

    These macros give the bounds for the various groups of tokens.
*/

#ifndef FIRST_TOKEN

#define FIRST_TOKEN		lex_unknown
#define LAST_TOKEN		lex_zzzzzz

#define FIRST_SYMBOL		lex_and_H1
#define LAST_SYMBOL		lex_open_Hsquare_H2

#define FIRST_C_SYMBOL		lex_and_H1
#define LAST_C_SYMBOL		lex_xor_Heq_H1

#define FIRST_CPP_SYMBOL	lex_arrow_Hstar
#define LAST_CPP_SYMBOL		lex_dot_Hstar

#define FIRST_EXTRA_SYMBOL	lex_abs
#define LAST_EXTRA_SYMBOL	lex_min

#define FIRST_DIGRAPH		lex_close_Hbrace_H2
#define LAST_DIGRAPH		lex_open_Hsquare_H2

#define FIRST_C_KEYWORD		lex_auto
#define LAST_C_KEYWORD		lex_while

#define FIRST_CPP_KEYWORD	lex_asm
#define LAST_CPP_KEYWORD	lex_wchar_Ht

#define FIRST_ISO_KEYWORD	lex_and_H2
#define LAST_ISO_KEYWORD	lex_xor_Heq_H2

#define FIRST_PP_KEYWORD	lex_hash_Hif
#define LAST_PP_KEYWORD		lex_hash_Hpragma

#define FIRST_KEYWORD		lex_auto
#define LAST_KEYWORD		lex_zzzz

#define FIRST_COMPLEX_TOKEN	lex_unknown
#define LAST_COMPLEX_TOKEN	lex_hash_Hpragma

#endif /* FIRST_TOKEN */
