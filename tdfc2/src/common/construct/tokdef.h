/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TOKDEF_INCLUDED
#define TOKDEF_INCLUDED


/*
    TDF TOKEN DECLARATIONS

    The routines in this module are concerned with the definition of TDF
    tokens.
*/

extern int define_exp_token(IDENTIFIER, EXP, int);
extern int define_func_token(IDENTIFIER, IDENTIFIER);
extern int define_mem_token(IDENTIFIER, OFFSET, TYPE, int);
extern int define_nat_token(IDENTIFIER, NAT);
extern int define_templ_token(IDENTIFIER, IDENTIFIER);
extern int define_type_token(IDENTIFIER, TYPE, int);
extern int define_token_macro(IDENTIFIER, IDENTIFIER);
extern int define_mem_macro(IDENTIFIER, TYPE);
extern int defining_token(IDENTIFIER);

extern LIST(TOKEN) make_token_args(IDENTIFIER, LIST(IDENTIFIER), ERROR *);
extern int save_token_args(LIST(IDENTIFIER), LIST(TOKEN));
extern void restore_token_args(LIST(IDENTIFIER), int);
extern int merge_token_args(LIST(IDENTIFIER), int, int);
extern void assign_token(IDENTIFIER, TOKEN);
extern int is_bound_tok(TOKEN, int);
extern TOKEN find_tokdef(IDENTIFIER);
extern void init_token_args(void);

extern PPTOKEN *skip_token_args(IDENTIFIER);
extern EXP parse_exp_token(IDENTIFIER, PPTOKEN *);
extern OFFSET parse_mem_token(IDENTIFIER, PPTOKEN *);
extern TYPE parse_type_token(IDENTIFIER, PPTOKEN *);
extern int unify_id(IDENTIFIER, IDENTIFIER, int);

extern IDENTIFIER unify_id_pending;
extern int in_proc_token;
extern int force_template;
extern int force_tokdef;
extern int expand_tokdef;
extern TYPE redef_type;


#endif
