/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LABEL_INCLUDED
#define LABEL_INCLUDED


/*
    LABEL DECLARATIONS

    The routines in this module are concerned with labels and labelled
    statements.
*/

extern EXP begin_label_stmt(IDENTIFIER, int);
extern EXP end_label_stmt(EXP, EXP);
extern EXP make_goto_stmt(IDENTIFIER);
extern EXP make_jump_stmt(IDENTIFIER, EXP);
extern IDENTIFIER postlude_label(void);
extern IDENTIFIER find_postlude_label(void);
extern NAT find_case_nat(IDENTIFIER);
extern int used_label(IDENTIFIER);
extern unsigned check_labels(void);
extern EXP solve_labels(EXP);
extern EXP solve_switch (EXP);
extern void end_solve_stmts(void);
extern LIST(EXP) all_solve_stmts;
extern LIST(EXP) all_try_blocks;
extern NAMESPACE label_namespace;


#endif
