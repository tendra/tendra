/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TOK_INCLUDED
#define TOK_INCLUDED


/*
    TDF TOKEN ENCODING ROUTINES

    The routines in this module are concerned with the encoding of the
    tokens used in the TDF output.
*/

extern TOKEN make_sort(const char *, int);
extern IDENTIFIER resolve_token(IDENTIFIER, const char *, int);
extern IDENTIFIER get_special(int, int);
extern string special_name(int);
extern void set_special(int, IDENTIFIER);
extern int token_code(TOKEN);
extern int builtin_token(IDENTIFIER);
extern void define_special(int);
extern void init_tok(int);

extern ulong special_no(int);
extern BITSTREAM *enc_special(BITSTREAM *, int);
extern BITSTREAM *enc_diag_special(BITSTREAM *, int, int);
extern BITSTREAM *enc_sort(BITSTREAM *, int);
extern BITSTREAM *enc_token(BITSTREAM *, IDENTIFIER, LIST(TOKEN));
extern BITSTREAM *enc_tokdef_body(BITSTREAM *, IDENTIFIER, TOKEN);
extern BITSTREAM *enc_asm(BITSTREAM *, EXP);


/*
    BASIC TYPE TOKEN INFORMATION

    The table base_token contains the token numbers associated with the
    basic types.
*/

typedef struct {
    int tok;
    unsigned no;
    unsigned alt;
} BASE_TOKEN;

extern BASE_TOKEN base_token[];


/*
    SPECIAL TOKEN NUMBERS

    These values correspond to the special tokens.
*/

enum {
	TOK_char           =   0,
	TOK_signed_char    =   1,
	TOK_unsigned_char  =   2,
	TOK_signed_short   =   3,
	TOK_unsigned_short =   4,
	TOK_signed_int     =   5,
	TOK_unsigned_int   =   6,
	TOK_signed_long    =   7,
	TOK_unsigned_long  =   8,
	TOK_signed_llong   =   9,
	TOK_unsigned_llong =  10,

	TOK_float          =  11,
	TOK_double         =  12,
	TOK_long_double    =  13,

	TOK_bool           =  14,
	TOK_ptrdiff_t      =  15,
	TOK_size_t         =  16,
	TOK_size_t_2       =  17,
	TOK_wchar_t        =  18,

	TOK_convert        =  19,
	TOK_arith_type     =  20,
	TOK_promote        =  21,
	TOK_sign_promote   =  22,

	TOK_lit_int        =  23,
	TOK_lit_hex        =  24,
	TOK_lit_unsigned   =  25,
	TOK_lit_long       =  26,
	TOK_lit_ulong      =  27,
	TOK_lit_llong      =  28,
	TOK_lit_ullong     =  29,

	TOK_bitf_sign      =  30,

	TOK_ptr_void       =  31,
	TOK_null_pv        =  32,
	TOK_to_ptr_void    =  33,
	TOK_from_ptr_void  =  34,
	TOK_pv_test        =  35,
	TOK_pv_compare     =  36,

	TOK_ptr_to_ptr     =  37,
	TOK_f_to_pv        =  38,
	TOK_pv_to_f        =  39,
	TOK_i_to_p         =  40,
	TOK_p_to_i         =  41,
	TOK_i_to_pv        =  42,
	TOK_pv_to_i        =  43,
	TOK_ptr_rep        =  44,

	TOK_div            =  45,
	TOK_rem            =  46,

	TOK_va_t           =  47,

	TOK_pm_type        =  48,
	TOK_pm_make        =  49,
	TOK_pm_null        =  50,
	TOK_pm_offset      =  51,
	TOK_pm_cast        =  52,
	TOK_pm_uncast      =  53,
	TOK_pm_test        =  54,
	TOK_pm_compare     =  55,

	TOK_pmf_type       =  56,
	TOK_pmf_make       =  57,
	TOK_pmf_vmake      =  58,
	TOK_pmf_null       =  59,
	TOK_pmf_null2      =  60,
	TOK_pmf_delta      =  61,
	TOK_pmf_func       =  62,
	TOK_pmf_virt       =  63,
	TOK_pmf_cast       =  64,
	TOK_pmf_uncast     =  65,
	TOK_pmf_test       =  66,
	TOK_pmf_compare    =  67,

	TOK_comp_off       =  68,
	TOK_pad            =  69,
	TOK_empty_align    =  70,
	TOK_empty_shape    =  71,
	TOK_empty_offset   =  72,

	TOK_vtab_type      =  73,
	TOK_vtab_diag      =  74,
	TOK_vtab_make      =  75,
	TOK_vtab_pure      =  76,
	TOK_vtab_func      =  77,
	TOK_vtab_off       =  78,

	TOK_typeid_type    =  79,
	TOK_typeid_make    =  80,
	TOK_typeid_basic   =  81,
	TOK_typeid_ref     =  82,
	TOK_baseid_type    =  83,
	TOK_baseid_make    =  84,
	TOK_dynam_cast     =  85,

	TOK_destr_type     =  86,
	TOK_destr_global   =  87,
	TOK_destr_local    =  88,
	TOK_destr_end      =  89,
	TOK_destr_init     =  90,
	TOK_destr_null     =  91,
	TOK_destr_ptr      =  92,
	TOK_start          =  93,

	TOK_try_type       =  94,
	TOK_try_begin      =  95,
	TOK_try_end        =  96,
	TOK_except_alloc   =  97,
	TOK_except_throw   =  98,
	TOK_except_rethrow =  99,
	TOK_except_catch   = 100,
	TOK_except_value   = 101,
	TOK_except_caught  = 102,
	TOK_except_end     = 103,
	TOK_except_bad     = 104,
	TOK_except_jump    = 105,
	TOK_ptr_code       = 106,
	TOK_ptr_frame      = 107,

	TOK_asm_sequence   = 108,
	TOK_asm            = 109,
	TOK_asm_input      = 110,
	TOK_asm_output     = 111,
	TOK_asm_address    = 112,

	TOK_char_offset    = 113,
	TOK_shape_offset   = 114,
	TOK_extra_offset   = 115,
	TOK_down_cast      = 116,
	TOK_destr_cast     = 117,
	TOK_destr_test     = 118,

	TOK_no             = 119
};


#endif
