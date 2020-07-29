/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef OUTPUT_INCLUDED
#define OUTPUT_INCLUDED

#include <stdio.h>

/*
 * LOOP VARIABLES
 *
 * These variables are used in the LOOP macros below as loop counters.
 * It should not be necessary to access them directly, instead the
 * CRT macros below should be used.
 */

extern LIST(ECONST_P)crt_ec;
extern LIST(ENUM_P)crt_en;
extern LIST(IDENTITY_P)crt_id;
extern LIST(PRIMITIVE_P)crt_prim;
extern LIST(STRUCTURE_P)crt_str;
extern LIST(UNION_P)crt_union;
extern LIST(COMPONENT_P)crt_cmp;
extern LIST(FIELD_P)crt_fld;
extern LIST(MAP_P)crt_map;
extern LIST(ARGUMENT_P)crt_arg;
extern LIST(TYPE_P)crt_type;


/*
 * LOOP MACROS
 *
 * The LOOP macros are used to scan over all elements of a list.  The
 * CRT macros give the effective loop counters.  Thus, for example,
 * LOOP_ENUM is a for statement which makes CRT_ENUM scan over all the
 * enumeration types.
 */

#define LOOP_LIST(X, Y)\
 for ((X) = (Y); !IS_NULL_list(X); (X) = TAIL_list(X))

#define LOOP_ENUM\
    LOOP_LIST(crt_en, algebra->enumerations)

#define LOOP_IDENTITY\
    LOOP_LIST(crt_id, algebra->identities)

#define LOOP_PRIMITIVE\
    LOOP_LIST(crt_prim, algebra->primitives)

#define LOOP_STRUCTURE\
    LOOP_LIST(crt_str, algebra->structures)

#define LOOP_UNION\
    LOOP_LIST(crt_union, algebra->unions)

#define LOOP_ENUM_CONST\
    LOOP_LIST(crt_ec, DEREF_list(en_consts(CRT_ENUM)))

#define LOOP_STRUCTURE_COMPONENT\
    LOOP_LIST(crt_cmp, DEREF_list(str_defn(CRT_STRUCTURE)))

#define LOOP_UNION_COMPONENT\
    LOOP_LIST(crt_cmp, DEREF_list(un_s_defn(CRT_UNION)))

#define LOOP_UNION_FIELD\
    LOOP_LIST(crt_fld, DEREF_list(un_u_defn(CRT_UNION)))

#define LOOP_FIELD_COMPONENT\
    LOOP_LIST(crt_cmp, DEREF_list(fld_defn(CRT_FIELD)))

#define LOOP_UNION_MAP\
    LOOP_LIST(crt_map, DEREF_list(un_map(CRT_UNION)))

#define LOOP_MAP_ARGUMENT\
    LOOP_LIST(crt_arg, DEREF_list(map_args(CRT_MAP)))

#define LOOP_TYPE\
    LOOP_LIST(crt_type, algebra->types)

#define CRT_ENUM	DEREF_ptr(HEAD_list(crt_en))
#define CRT_IDENTITY	DEREF_ptr(HEAD_list(crt_id))
#define CRT_PRIMITIVE	DEREF_ptr(HEAD_list(crt_prim))
#define CRT_STRUCTURE	DEREF_ptr(HEAD_list(crt_str))
#define CRT_UNION	DEREF_ptr(HEAD_list(crt_union))
#define CRT_ECONST	DEREF_ptr(HEAD_list(crt_ec))
#define CRT_COMPONENT	DEREF_ptr(HEAD_list(crt_cmp))
#define CRT_FIELD	DEREF_ptr(HEAD_list(crt_fld))
#define CRT_MAP		DEREF_ptr(HEAD_list(crt_map))
#define CRT_ARGUMENT	DEREF_ptr(HEAD_list(crt_arg))
#define CRT_TYPE	DEREF_ptr(HEAD_list(crt_type))

#define HAVE_ENUM	(!IS_NULL_list(crt_en))
#define HAVE_IDENTITY	(!IS_NULL_list(crt_id))
#define HAVE_PRIMITIVE	(!IS_NULL_list(crt_prim))
#define HAVE_STRUCTURE	(!IS_NULL_list(crt_str))
#define HAVE_UNION	(!IS_NULL_list(crt_union))
#define HAVE_ECONST	(!IS_NULL_list(crt_ec))
#define HAVE_COMPONENT	(!IS_NULL_list(crt_cmp))
#define HAVE_FIELD	(!IS_NULL_list(crt_fld))
#define HAVE_MAP	(!IS_NULL_list(crt_map))
#define HAVE_ARGUMENT	(!IS_NULL_list(crt_arg))
#define HAVE_TYPE	(!IS_NULL_list(crt_type))


/*
 * DECLARATIONS FOR BASIC OUTPUT ROUTINES
 */

extern int unique;
extern int const_tokens;
extern int have_varargs;
extern int output_c_code;
extern int verbose_output;
extern FILE *output_file;
extern void flush_output(void);
extern void open_file(char *, char *, char *);
extern void close_file(void);
extern void output_type(TYPE_P);
extern number ilog2(number);

extern void output(char *, ...);

#define comment(X)	output("/* %e */\n\n", (X))


#endif
