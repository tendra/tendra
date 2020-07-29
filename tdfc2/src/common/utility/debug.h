/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef NDEBUG
#ifndef DEBUG_INCLUDED
#define DEBUG_INCLUDED


/*
    DEBUGGING ROUTINE DECLARATIONS

    The routines in this module are designed to aid in program development;
    they do not form part of the program proper.  They are only defined if
    the standard macro NDEBUG is not defined.
*/

extern void DEBUG_access(DECL_SPEC);
extern void DEBUG_btype(BASE_TYPE);
extern void DEBUG_cinfo(CLASS_INFO);
extern void DEBUG_ctype(CLASS_TYPE);
extern void DEBUG_cusage(CLASS_USAGE);
extern void DEBUG_cv(CV_SPEC);
extern void DEBUG_dspec(DECL_SPEC);
extern void DEBUG_etype(ENUM_TYPE);
extern void DEBUG_exp(EXP);
extern void DEBUG_flt(FLOAT);
extern void DEBUG_ftype(FLOAT_TYPE);
extern void DEBUG_func(IDENTIFIER);
extern void DEBUG_graph(GRAPH);
extern void DEBUG_hashid(HASHID);
extern void DEBUG_hash_table(string);
extern void DEBUG_id(IDENTIFIER);
extern void DEBUG_id_long(IDENTIFIER);
extern void DEBUG_inst(INSTANCE);
extern void DEBUG_itype(INT_TYPE);
extern void DEBUG_lex(int);
extern void DEBUG_loc(LOCATION *);
extern void DEBUG_mangle(IDENTIFIER);
extern void DEBUG_member(MEMBER);
extern void DEBUG_members(NAMESPACE);
extern void DEBUG_nat(NAT);
extern void DEBUG_nspace(NAMESPACE);
extern void DEBUG_ntest(NTEST);
extern void DEBUG_ntype(BUILTIN_TYPE);
extern void DEBUG_offset(OFFSET);
extern void DEBUG_pptok(PPTOKEN *);
extern void DEBUG_pptoks(PPTOKEN *);
extern void DEBUG_sort(TOKEN);
extern void DEBUG_stmt(EXP);
extern void DEBUG_str(STRING);
extern void DEBUG_type(TYPE);
extern void DEBUG_unmangle(const char *);
extern void DEBUG_virt(VIRTUAL);

extern void DEBUG_source(int);
extern void DEBUG_where(void);

#if c_class_IMPLEMENTATION
extern void debug(c_class *);
#endif

#define DEBUG_file	stdout
#define DEBUG_text(A)	fputs_v((A), DEBUG_file)
#define DEBUG_mark	fprintf_v(DEBUG_file, "%s: %d\n", __FILE__, __LINE__)

extern int print_exp_aux(EXP, int, BUFFER *, int);
extern int print_offset_aux(OFFSET, BUFFER *, int);
extern void debug_option(char *);
extern int debugging;


#endif
#endif
