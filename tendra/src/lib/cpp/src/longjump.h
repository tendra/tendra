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


#ifndef LONGJUMP_INCLUDED
#define LONGJUMP_INCLUDED


/*
    LONG JUMP TOKEN INTERFACE

    The following tokens give the interface to the TDF long_jump construct.
    The definitions are built into the compiler.
*/

#pragma token TYPE CODE_PTR # ~cpp.ptr.code
#pragma token TYPE FRAME_PTR # ~cpp.ptr.frame
#pragma token PROC ( EXP : FRAME_PTR :, EXP : CODE_PTR : )\
    EXP : void : long_jump # ~cpp.except.jump

#pragma interface CODE_PTR FRAME_PTR
#pragma interface long_jump


#endif
