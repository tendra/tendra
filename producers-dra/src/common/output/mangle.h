/* $Id$ */

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

#define MANGLE_char		'c'
#define MANGLE_short		's'
#define MANGLE_int		'i'
#define MANGLE_long		'l'
#define MANGLE_llong		'x'
#define MANGLE_float		'f'
#define MANGLE_double		'd'
#define MANGLE_ldouble		'r'
#define MANGLE_void		'v'
#define MANGLE_bottom		'u'
#define MANGLE_bool		'b'
#define MANGLE_ptrdiff_t	'y'
#define MANGLE_size_t		'z'
#define MANGLE_wchar_t		'w'
#define MANGLE_signed		'S'
#define MANGLE_unsigned		'U'

#define MANGLE_ptr		'P'
#define MANGLE_ref		'R'
#define MANGLE_ptr_mem		'M'
#define MANGLE_func		'F'
#define MANGLE_weak		'W'
#define MANGLE_array		'A'
#define MANGLE_bitfield		'B'
#define MANGLE_arith		'a'
#define MANGLE_literal		'n'
#define MANGLE_octal		'O'
#define MANGLE_hex		'X'
#define MANGLE_promote		'p'
#define MANGLE_unpromote	'q'

#define MANGLE_const		'C'
#define MANGLE_volatile		'V'
#define MANGLE_c_lang		'L'

#define MANGLE_nat		'I'
#define MANGLE_stmt		'V'
#define MANGLE_type		'Z'
#define MANGLE_self		'X'
#define MANGLE_repeat		'T'
#define MANGLE_multi		'N'
#define MANGLE_template		't'
#define MANGLE_templ_param	'm'
#define MANGLE_func_templ	'G'
#define MANGLE_ellipsis		'e'
#define MANGLE_neg		'h'
#define MANGLE_op		'o'
#define MANGLE_qual		'Q'
#define MANGLE_unicode4		'k'
#define MANGLE_unicode8		'K'

#define MANGLE_sep		'_'
#define MANGLE_colon		':'
#define MANGLE_comma		','
#define MANGLE_dot		'.'
#define MANGLE_error		'*'

#define MANGLE_WORTH		10


#endif
