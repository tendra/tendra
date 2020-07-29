/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef PRINT_INCLUDED
#define PRINT_INCLUDED


/*
    OBJECT PRINTING DECLARATIONS

    The routines in this module are used to print objects of the various
    basic types used in the program.  They are used primarily in error
    reporting, but print_pptok is also used by the stand-alone preprocessor
    action.
*/

extern int print_access(DECL_SPEC, BUFFER *, int);
extern int print_btype(BASE_TYPE, BUFFER *, int);
extern int print_ctype(CLASS_TYPE, QUALIFIER, int, BUFFER *, int);
extern int print_cv(CV_SPEC, BUFFER *, int);
extern int print_dspec(DECL_SPEC, BUFFER *, int);
extern int print_etype(ENUM_TYPE, int, BUFFER *, int);
extern int print_exp(EXP, int, BUFFER *, int);
extern int print_flt(FLOAT, BUFFER *, int);
extern int print_ftype(FLOAT_TYPE, BUFFER *, int);
extern int print_graph(GRAPH, int, BUFFER *, int);
extern int print_hashid(HASHID, int, int, BUFFER *, int);
extern int print_id_short(IDENTIFIER, QUALIFIER, BUFFER *, int);
extern int print_id_long(IDENTIFIER, QUALIFIER, BUFFER *, int);
extern int print_itype(INT_TYPE, BUFFER *, int);
extern int print_lex(int, BUFFER *, int);
extern int print_loc(LOCATION *, LOCATION *, BUFFER *, int);
extern int print_nat(NAT, int, BUFFER *, int);
extern int print_nspace(NAMESPACE, QUALIFIER, int, BUFFER *, int);
extern int print_ntype(BUILTIN_TYPE, BUFFER *, int);
extern int print_offset(OFFSET, BUFFER *, int);
extern int print_pptok(PPTOKEN *, BUFFER *, int);
extern int print_sort(TOKEN, int, BUFFER *, int);
extern int print_str(STRING, BUFFER *, int);
extern int print_tok_value(TOKEN, BUFFER *, int);
extern int print_token(IDENTIFIER, QUALIFIER, LIST(TOKEN), BUFFER *, int);
extern int print_type(TYPE, BUFFER *, int);
extern int print_type_list(LIST(TYPE), BUFFER *, int);
extern void print_char(unsigned long, int, int, BUFFER *);
extern void print_source(LOCATION *, int, int, const char *, FILE *);
extern const char *ntype_name[];
extern int print_type_alias;
extern int print_uniq_anon;
extern int print_id_desc;
extern int print_c_style;
extern BUFFER print_buff;


#endif
