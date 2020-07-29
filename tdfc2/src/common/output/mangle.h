/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef MANGLE_INCLUDED
#define MANGLE_INCLUDED


/*
    NAME MANGLING DECLARATIONS

    The routines in this module are concerned with name mangling.
*/

extern string mangle_name(IDENTIFIER, int, int);
extern string mangle_literal(INT_TYPE);
extern string mangle_diag(IDENTIFIER, int);
extern string mangle_common(string, IDENTIFIER);
extern string mangle_typeid(const char *, CLASS_TYPE);
extern string mangle_tname(const char *, TYPE);
extern string mangle_vtable(const char *, GRAPH);
extern string mangle_anon(void);
extern string mangle_init(void);
extern unsigned long mangle_length;
extern char mangle_ntype[][3];
extern int mangle_signature;
extern int mangle_objects;
extern BUFFER mangle_buff;
extern ulong common_no;


/*
    NAME MANGLING CODES

    This macros give the encodings used in the mangling routines.  The
    built-in integral and floating-point types are given in the array
    mangle_ntype.
*/

enum {
	MANGLE_char        = 'c',
	MANGLE_short       = 's',
	MANGLE_int         = 'i',
	MANGLE_long        = 'l',
	MANGLE_llong       = 'x',
	MANGLE_float       = 'f',
	MANGLE_double      = 'd',
	MANGLE_ldouble     = 'r',
	MANGLE_void        = 'v',
	MANGLE_bottom      = 'u',
	MANGLE_bool        = 'b',
	MANGLE_ptrdiff_t   = 'y',
	MANGLE_size_t      = 'z',
	MANGLE_wchar_t     = 'w',
	MANGLE_signed      = 'S',
	MANGLE_unsigned    = 'U',

	MANGLE_ptr         = 'P',
	MANGLE_ref         = 'R',
	MANGLE_ptr_mem     = 'M',
	MANGLE_func        = 'F',
	MANGLE_weak        = 'W',
	MANGLE_array       = 'A',
	MANGLE_bitfield    = 'B',
	MANGLE_arith       = 'a',
	MANGLE_literal     = 'n',
	MANGLE_octal       = 'O',
	MANGLE_hex         = 'X',
	MANGLE_promote     = 'p',
	MANGLE_unpromote   = 'q',

	MANGLE_const       = 'C',
	MANGLE_volatile    = 'V',
	MANGLE_c_lang      = 'L',

	MANGLE_nat         = 'I',
	MANGLE_stmt        = 'V',
	MANGLE_type        = 'Z',
	MANGLE_self        = 'X',
	MANGLE_repeat      = 'T',
	MANGLE_multi       = 'N',
	MANGLE_template    = 't',
	MANGLE_templ_param = 'm',
	MANGLE_func_templ  = 'G',
	MANGLE_ellipsis    = 'e',
	MANGLE_neg         = 'h',
	MANGLE_op          = 'o',
	MANGLE_qual        = 'Q',
	MANGLE_unicode4    = 'k',
	MANGLE_unicode8    = 'K',

	MANGLE_sep         = '_',
	MANGLE_colon       = ':',
	MANGLE_comma       = ',',
	MANGLE_dot         = '.',
	MANGLE_error       = '*'
};

#define MANGLE_WORTH 10


#endif
