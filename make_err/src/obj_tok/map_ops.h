/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef MAP_OPS_H_INCLUDED
#define MAP_OPS_H_INCLUDED

/* Operations for union MAP */

#pragma token PROC(EXP : MAP :) EXP : unsigned : TAG_map #
#pragma interface TAG_map


/* Operations for component key of union MAP */

#pragma token PROC(EXP : MAP :)\
    EXP : PTR(KEY) : map_key #
#pragma interface map_key

/* Operations for component msg of union MAP */

#pragma token PROC(EXP : MAP :)\
    EXP : PTR(LIST(MESSAGE)) : map_msg #
#pragma interface map_msg

/* Operations for component alt_msg of union MAP */

#pragma token PROC(EXP : MAP :)\
    EXP : PTR(LIST(MESSAGE)) : map_alt_msg #
#pragma interface map_alt_msg

/* Operations for field basic of union MAP */

#pragma token EXP const : unsigned : map_basic_tag #
#pragma token PROC(EXP : MAP :) EXP : int : IS_map_basic #
#pragma interface map_basic_tag IS_map_basic

#pragma token PROC(\
	EXP : KEY :,\
	EXP : LIST(MESSAGE) :,\
	EXP : LIST(MESSAGE) :,\
	EXP lvalue : MAP :\
    ) STATEMENT MAKE_map_basic #
#pragma interface MAKE_map_basic

#pragma token PROC(\
	EXP lvalue : KEY :,\
	EXP lvalue : LIST(MESSAGE) :,\
	EXP lvalue : LIST(MESSAGE) :,\
	EXP : MAP :\
    ) STATEMENT DECONS_map_basic #
#pragma interface DECONS_map_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : KEY :,\
	EXP lvalue : LIST(MESSAGE) :,\
	EXP lvalue : LIST(MESSAGE) :,\
	EXP : MAP :\
    ) STATEMENT DESTROY_map_basic #
#pragma interface DESTROY_map_basic


#endif
