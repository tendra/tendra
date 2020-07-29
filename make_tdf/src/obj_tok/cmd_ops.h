/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef CMD_OPS_H_INCLUDED
#define CMD_OPS_H_INCLUDED

/* Operations for union COMMAND */

#pragma token PROC(EXP : COMMAND :) EXP : unsigned : TAG_cmd #
#pragma interface TAG_cmd


/* Operations for component line of union COMMAND */

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(int) : cmd_line #
#pragma interface cmd_line

/* Operations for field simple of union COMMAND */

#pragma token EXP const : unsigned : cmd_simple_tag #
#pragma token PROC(EXP : COMMAND :) EXP : int : IS_cmd_simple #
#pragma interface cmd_simple_tag IS_cmd_simple

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(string) : cmd_simple_text #
#pragma interface cmd_simple_text

#pragma token PROC(\
	EXP : int :,\
	EXP : string :,\
	EXP lvalue : COMMAND :\
    ) STATEMENT MAKE_cmd_simple #
#pragma interface MAKE_cmd_simple

#pragma token PROC(\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP : COMMAND :\
    ) STATEMENT DECONS_cmd_simple #
#pragma interface DECONS_cmd_simple

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP : COMMAND :\
    ) STATEMENT DESTROY_cmd_simple #
#pragma interface DESTROY_cmd_simple


/* Operations for field compound of union COMMAND */

#pragma token EXP const : unsigned : cmd_compound_tag #
#pragma token PROC(EXP : COMMAND :) EXP : int : IS_cmd_compound #
#pragma interface cmd_compound_tag IS_cmd_compound

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(LIST(COMMAND)) : cmd_compound_seq #
#pragma interface cmd_compound_seq

#pragma token PROC(\
	EXP : int :,\
	EXP : LIST(COMMAND) :,\
	EXP lvalue : COMMAND :\
    ) STATEMENT MAKE_cmd_compound #
#pragma interface MAKE_cmd_compound

#pragma token PROC(\
	EXP lvalue : int :,\
	EXP lvalue : LIST(COMMAND) :,\
	EXP : COMMAND :\
    ) STATEMENT DECONS_cmd_compound #
#pragma interface DECONS_cmd_compound

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : LIST(COMMAND) :,\
	EXP : COMMAND :\
    ) STATEMENT DESTROY_cmd_compound #
#pragma interface DESTROY_cmd_compound


/* Operations for field loop of union COMMAND */

#pragma token EXP const : unsigned : cmd_loop_tag #
#pragma token PROC(EXP : COMMAND :) EXP : int : IS_cmd_loop #
#pragma interface cmd_loop_tag IS_cmd_loop

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(string) : cmd_loop_control #
#pragma interface cmd_loop_control

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(COMMAND) : cmd_loop_body #
#pragma interface cmd_loop_body

#pragma token PROC(\
	EXP : int :,\
	EXP : string :,\
	EXP : COMMAND :,\
	EXP lvalue : COMMAND :\
    ) STATEMENT MAKE_cmd_loop #
#pragma interface MAKE_cmd_loop

#pragma token PROC(\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : COMMAND :,\
	EXP : COMMAND :\
    ) STATEMENT DECONS_cmd_loop #
#pragma interface DECONS_cmd_loop

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : COMMAND :,\
	EXP : COMMAND :\
    ) STATEMENT DESTROY_cmd_loop #
#pragma interface DESTROY_cmd_loop


/* Operations for field cond of union COMMAND */

#pragma token EXP const : unsigned : cmd_cond_tag #
#pragma token PROC(EXP : COMMAND :) EXP : int : IS_cmd_cond #
#pragma interface cmd_cond_tag IS_cmd_cond

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(string) : cmd_cond_control #
#pragma interface cmd_cond_control

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(COMMAND) : cmd_cond_true_code #
#pragma interface cmd_cond_true_code

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(COMMAND) : cmd_cond_false_code #
#pragma interface cmd_cond_false_code

#pragma token PROC(\
	EXP : int :,\
	EXP : string :,\
	EXP : COMMAND :,\
	EXP : COMMAND :,\
	EXP lvalue : COMMAND :\
    ) STATEMENT MAKE_cmd_cond #
#pragma interface MAKE_cmd_cond

#pragma token PROC(\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : COMMAND :,\
	EXP lvalue : COMMAND :,\
	EXP : COMMAND :\
    ) STATEMENT DECONS_cmd_cond #
#pragma interface DECONS_cmd_cond

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : COMMAND :,\
	EXP lvalue : COMMAND :,\
	EXP : COMMAND :\
    ) STATEMENT DESTROY_cmd_cond #
#pragma interface DESTROY_cmd_cond


/* Operations for field use of union COMMAND */

#pragma token EXP const : unsigned : cmd_use_tag #
#pragma token PROC(EXP : COMMAND :) EXP : int : IS_cmd_use #
#pragma interface cmd_use_tag IS_cmd_use

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(string) : cmd_use_sort #
#pragma interface cmd_use_sort

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(string) : cmd_use_cons #
#pragma interface cmd_use_cons

#pragma token PROC(\
	EXP : int :,\
	EXP : string :,\
	EXP : string :,\
	EXP lvalue : COMMAND :\
    ) STATEMENT MAKE_cmd_use #
#pragma interface MAKE_cmd_use

#pragma token PROC(\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP : COMMAND :\
    ) STATEMENT DECONS_cmd_use #
#pragma interface DECONS_cmd_use

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP : COMMAND :\
    ) STATEMENT DESTROY_cmd_use #
#pragma interface DESTROY_cmd_use


/* Operations for field special of union COMMAND */

#pragma token EXP const : unsigned : cmd_special_tag #
#pragma token PROC(EXP : COMMAND :) EXP : int : IS_cmd_special #
#pragma interface cmd_special_tag IS_cmd_special

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(string) : cmd_special_sort #
#pragma interface cmd_special_sort

#pragma token PROC(EXP : COMMAND :)\
    EXP : PTR(string) : cmd_special_cons #
#pragma interface cmd_special_cons

#pragma token PROC(\
	EXP : int :,\
	EXP : string :,\
	EXP : string :,\
	EXP lvalue : COMMAND :\
    ) STATEMENT MAKE_cmd_special #
#pragma interface MAKE_cmd_special

#pragma token PROC(\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP : COMMAND :\
    ) STATEMENT DECONS_cmd_special #
#pragma interface DECONS_cmd_special

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP : COMMAND :\
    ) STATEMENT DESTROY_cmd_special #
#pragma interface DESTROY_cmd_special


#endif
