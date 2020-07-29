/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED


/*
    EXCEPTION HANDLING DECLARATIONS

    The routines in this module are concerned with exception handling.
*/

extern EXP make_throw_exp(EXP, int);
extern EXP make_throw_arg(TYPE, int);
extern EXP begin_catch_stmt(EXP, IDENTIFIER);
extern EXP end_catch_stmt(EXP, EXP);
extern EXP begin_try_stmt(int);
extern EXP cont_try_stmt(EXP, EXP);
extern EXP end_try_stmt(EXP, int);
extern void inject_try_stmt(EXP);
extern void end_try_blocks(IDENTIFIER);
extern IDENTIFIER make_except_decl(DECL_SPEC, TYPE, IDENTIFIER, int);
extern int check_func_throw(TYPE, IDENTIFIER);
extern int check_throw(TYPE, int);
extern void start_try_check(LIST(TYPE));
extern EXP end_try_check(IDENTIFIER, EXP);
extern int check_try_block(EXP);

extern int eq_except(TYPE, TYPE);
extern int in_type_set(LIST(TYPE), TYPE);
extern int eq_type_set(LIST(TYPE), LIST(TYPE), int);
extern LIST(TYPE) union_type_set(LIST(TYPE), LIST(TYPE));
extern LIST(TYPE) cons_type_set(LIST(TYPE), TYPE);
extern LIST(TYPE) uniq_type_set(LIST(TYPE));
extern TYPE check_except_type(TYPE, int);
extern TYPE exception_type(TYPE, int);
extern void init_exception(void);
extern STACK(EXP) crt_try_blocks;
extern LIST(TYPE) empty_type_set;
extern LIST(TYPE) univ_type_set;
extern int in_func_handler;


#endif
