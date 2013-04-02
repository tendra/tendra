/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef STATEMENT_INCLUDED
#define STATEMENT_INCLUDED


/*
    STATEMENT CONSTRUCTION DECLARATIONS

    The routines in this module are used in the construction of the
    basic language statements.
*/

extern EXP begin_case_stmt(EXP, int);
extern EXP begin_compound_stmt(int);
extern EXP begin_default_stmt(int);
extern EXP begin_do_stmt(void);
extern EXP begin_for_stmt(void);
extern EXP begin_hash_if_stmt(EXP, EXP);
extern EXP begin_if_stmt(EXP);
extern EXP begin_switch_stmt(EXP);
extern EXP begin_while_stmt(EXP);

extern void mark_compound_stmt(EXP);
extern EXP add_compound_stmt(EXP, EXP);
extern EXP cont_hash_if_stmt(EXP, EXP, EXP);
extern EXP cont_if_stmt(EXP, EXP);
extern EXP init_for_stmt(EXP, EXP *);
extern EXP cond_for_stmt(EXP, EXP, EXP);

extern EXP end_case_stmt(EXP, EXP);
extern EXP end_compound_stmt(EXP);
extern EXP end_default_stmt(EXP, EXP);
extern EXP end_do_stmt(EXP, EXP, EXP);
extern EXP end_for_stmt(EXP, EXP);
extern EXP end_hash_if_stmt(EXP, EXP);
extern EXP end_if_stmt(EXP, EXP);
extern EXP end_switch_stmt(EXP, EXP, int);
extern EXP end_while_stmt(EXP, EXP);

extern EXP make_break_stmt(void);
extern EXP make_continue_stmt(void);
extern EXP make_decl_stmt(MEMBER, MEMBER, int *);
extern EXP make_temp_decl(MEMBER, MEMBER, EXP);
extern EXP make_exp_stmt(EXP);
extern EXP make_return_stmt(EXP, int);
extern EXP make_discard_exp(EXP);
extern EXP make_reach_stmt(EXP, int);
extern EXP fall_return_stmt(void);
extern EXP find_return_exp(EXP, IDENTIFIER *, int);
extern EXP check_return_exp(EXP, int);

extern EXP bind_temporary(EXP);
extern void begin_cond(void);
extern EXP end_cond(void);
extern EXP inject_cond(EXP, EXP);
extern TYPE make_cond_type(TYPE);
extern EXP check_cond(EXP, EXP *, int);
extern EXP check_control(EXP, EXP *, EXP *);
extern void check_empty_stmt(int);
extern EXP make_if_cond(EXP, EXP);
extern EXP make_else_cond(EXP);
extern IDENTIFIER find_case(LIST(NAT), LIST(IDENTIFIER), NAT);
extern EXP make_asm(EXP, LIST(EXP));

extern void set_parent_stmt(EXP, EXP);
extern EXP get_parent_stmt(EXP);
extern STACK(EXP) crt_loop_stack;
extern NAMESPACE block_namespace;
extern unsigned crt_condition;
extern int record_location;
extern int unreached_code;
extern int unreached_last;
extern int unreached_prev;
extern int unreached_fall;
extern int suppress_fall;
extern EXP crt_hash_cond;
extern LOCATION stmt_loc;


#endif
