/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TOKEN_INCLUDED
#define TOKEN_INCLUDED


/*
    TDF TOKEN DECLARATIONS

    The routines in this module are concerned with the construction of
    TDF tokens.
*/

extern IDENTIFIER make_token_decl(TOKEN, int, IDENTIFIER, IDENTIFIER);
extern IDENTIFIER make_tok_param(TOKEN, int, IDENTIFIER);
extern IDENTIFIER prog_tok_param(IDENTIFIER, TYPE, unsigned, LIST(IDENTIFIER));

extern TOKEN begin_proc_token(void);
extern TOKEN cont_proc_token(TOKEN, LIST(IDENTIFIER), LIST(IDENTIFIER));
extern TOKEN end_proc_token(TOKEN, TOKEN);
extern void set_proc_token(LIST(IDENTIFIER));

extern TOKEN make_func_token(TYPE);
extern TOKEN make_type_token(BASE_TYPE);
extern TOKEN make_exp_token(TYPE, int, int);
extern TOKEN make_member_token(TYPE, TYPE, DECL_SPEC);
extern TOKEN func_proc_token(TOKEN);
extern int type_token_key(BASE_TYPE);

extern EXP expand_exp(EXP, int, int);
extern NAT expand_nat(NAT, int, int, ERROR *);
extern OFFSET expand_offset(OFFSET, int);
extern TYPE expand_type(TYPE, int);
extern TOKEN expand_sort(TOKEN, int, int);
extern CLASS_TYPE expand_ctype(CLASS_TYPE, int, TYPE *);
extern LIST(TOKEN) expand_args(LIST(TOKEN), int, int);
extern LIST(TYPE) expand_exceptions(LIST(TYPE), int, int *);
extern TOKEN expand_templ_sort(TOKEN, int);
extern void reset_templ_sort(TOKEN);
extern int expand_anon_bitfield;

extern EXP apply_exp_token(IDENTIFIER, LIST(TOKEN), int);
extern NAT apply_nat_token(IDENTIFIER, LIST(TOKEN));
extern OFFSET apply_mem_token(IDENTIFIER, LIST(TOKEN));
extern TYPE apply_type_token(IDENTIFIER, LIST(TOKEN), IDENTIFIER);
extern TOKEN apply_token(IDENTIFIER, LIST(TOKEN));

extern IDENTIFIER find_token(IDENTIFIER);
extern IDENTIFIER find_tag_token(IDENTIFIER);
extern IDENTIFIER find_mem_token(IDENTIFIER, IDENTIFIER);
extern IDENTIFIER find_func_token(IDENTIFIER, unsigned);
extern IDENTIFIER find_ext_token(IDENTIFIER);
extern IDENTIFIER tok_member(IDENTIFIER, TYPE, int);
extern void token_interface(IDENTIFIER, int);
extern int crt_interface;


#endif
