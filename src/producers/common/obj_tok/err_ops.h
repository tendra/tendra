/*
    		 Crown Copyright (c) 1997, 1998
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.2)
*/

#ifndef ERR_OPS_H_INCLUDED
#define ERR_OPS_H_INCLUDED

/* Operations for union ERROR */

#pragma token PROC ( EXP : ERROR : ) EXP : unsigned : TAG_err #
#pragma interface TAG_err


/* Operations for component severity of union ERROR */

#pragma token PROC ( EXP : ERROR : )\
    EXP : PTR ( int ) : err_severity #
#pragma interface err_severity

/* Operations for field simple of union ERROR */

#pragma token EXP const : unsigned : err_simple_tag #
#pragma token PROC ( EXP : ERROR : ) EXP : int : IS_err_simple #
#pragma interface err_simple_tag IS_err_simple

#pragma token PROC ( EXP : ERROR : )\
    EXP : PTR ( int ) : err_simple_number #
#pragma interface err_simple_number

#pragma token PROC ( EXP : ERROR : )\
    EXP : PTR ( unsigned ) : err_simple_size #
#pragma interface err_simple_size

#pragma token PROC (\
	EXP : int :,\
	EXP : int :,\
	EXP lvalue : ERROR :\
    ) STATEMENT MAKE_err_simple #
#pragma interface MAKE_err_simple

#pragma token PROC (\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : unsigned :,\
	EXP : ERROR :\
    ) STATEMENT DECONS_err_simple #
#pragma interface DECONS_err_simple

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : unsigned :,\
	EXP : ERROR :\
    ) STATEMENT DESTROY_err_simple #
#pragma interface DESTROY_err_simple


/* Operations for field compound of union ERROR */

#pragma token EXP const : unsigned : err_compound_tag #
#pragma token PROC ( EXP : ERROR : ) EXP : int : IS_err_compound #
#pragma interface err_compound_tag IS_err_compound

#pragma token PROC ( EXP : ERROR : )\
    EXP : PTR ( ERROR ) : err_compound_head #
#pragma interface err_compound_head

#pragma token PROC ( EXP : ERROR : )\
    EXP : PTR ( ERROR ) : err_compound_tail #
#pragma interface err_compound_tail

#pragma token PROC (\
	EXP : int :,\
	EXP : ERROR :,\
	EXP : ERROR :,\
	EXP lvalue : ERROR :\
    ) STATEMENT MAKE_err_compound #
#pragma interface MAKE_err_compound

#pragma token PROC (\
	EXP lvalue : int :,\
	EXP lvalue : ERROR :,\
	EXP lvalue : ERROR :,\
	EXP : ERROR :\
    ) STATEMENT DECONS_err_compound #
#pragma interface DECONS_err_compound

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : ERROR :,\
	EXP lvalue : ERROR :,\
	EXP : ERROR :\
    ) STATEMENT DESTROY_err_compound #
#pragma interface DESTROY_err_compound


#endif
