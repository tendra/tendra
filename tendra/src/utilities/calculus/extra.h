/*
    		 Crown Copyright (c) 1997
    
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


#ifndef EXTRA_INCLUDED
#define EXTRA_INCLUDED


/*
    EXTRA CALCULUS TOKEN SPECIFICATIONS

    This file contains the specifications for calculus-like tokens used
    within the program.
*/

#if calculus_SPECIFICATION

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e1,\
	EXP : LIST ( t ) : e2, EXP : SIZE ( t ) : e3 |\
	EXP e1, EXP e2, EXP e3\
    } EXP : LIST ( t ) : ADD_list #

#pragma interface ADD_list

#endif


/*
    EXTRA CALCULUS TOKEN IMPLEMENTATIONS

    The token specified above are implemented as follows.  The token
    definitions are implementation specific.  The functions used are
    defined in calculus.c.
*/

#if calculus_IMPLEMENTATION

extern calculus *add_calculus_list PROTO_S ( ( calculus *, calculus *, int ) ) ;

#define ADD_list( X, Y, Z )	add_calculus_list ( ( X ), ( Y ), ( Z ) )

#endif


#endif
