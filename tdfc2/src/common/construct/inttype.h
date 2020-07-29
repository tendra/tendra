/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef INTTYPE_INCLUDED
#define INTTYPE_INCLUDED


/*
    TYPE REPRESENTING FUNDAMENTAL TYPE INFORMATION

    This type is used to represent the fundamental information about a
    built-in type.
*/

typedef struct {
	BASE_TYPE rep;
	unsigned min_bits;
	unsigned max_bits;
	BASE_TYPE sign;
	int key;
	TYPE set;
} BASE_INFO;


/*
    INTEGRAL TYPE DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of the integral C and C++ types.
*/

extern void init_itypes(int);
extern void term_itypes(void);
extern void set_char_sign(BASE_TYPE);
extern void set_promote_type(TYPE, TYPE, BUILTIN_TYPE);
extern void compute_promote_type(IDENTIFIER);
extern void set_builtin_type(BASE_TYPE, TYPE);
extern void set_long_long_type(int);
extern void set_exact_types(void);
extern unsigned find_type_size(TYPE, unsigned *, BASE_TYPE *);
extern BUILTIN_TYPE is_builtin_type(TYPE, int);
extern TYPE make_itype(INT_TYPE, INT_TYPE);
extern TYPE make_ftype(FLOAT_TYPE, FLOAT_TYPE);
extern TYPE arith_itype(TYPE, TYPE, EXP, EXP);
extern TYPE arith_ftype(TYPE, TYPE);
extern TYPE promote_itype(INT_TYPE, INT_TYPE);
extern TYPE promote_ftype(FLOAT_TYPE, FLOAT_TYPE);
extern TYPE apply_itype_token(IDENTIFIER, LIST(TOKEN));
extern TYPE apply_ftype_token(IDENTIFIER, LIST(TOKEN));
extern INT_TYPE expand_itype(INT_TYPE);
extern BASE_TYPE key_type(int);

extern LIST(TYPE) all_llong_types;
extern LIST(TYPE) all_prom_types;
extern LIST(TYPE) all_int_types;
extern BASE_INFO basetype_info[];

extern int min_builtin_cast;
extern int safe_builtin_cast;
extern int max_builtin_cast;

extern unsigned char builtin_casts[ORDER_ntype][ORDER_ntype];
#define builtin_cast(A, B)	((int)builtin_casts[A][B])


#endif
