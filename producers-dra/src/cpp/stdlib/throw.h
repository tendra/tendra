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


#ifndef THROW_INCLUDED
#define THROW_INCLUDED


/*
    EXCEPTION HANDLING TOKEN INTERFACE

    The following tokens give the interface between the compiler and the
    exception handling routines.
*/

#pragma token PROC ( EXP : void * :, EXP : TYPE_INFO * :, EXP : DESTRUCTOR : )\
    EXP : void : throw_exception # ~cpp.except.throw
#pragma token PROC () EXP : void : rethrow_exception # ~cpp.except.rethrow
#pragma token PROC ( EXP : TYPE_INFO * : )\
    EXP : int : catch_exception # ~cpp.except.catch

#pragma token PROC ( EXP : size_t : )\
    EXP : void * : alloc_exception # ~cpp.except.alloc

#pragma token EXP : void * : value_exception # ~cpp.except.value
#pragma token PROC () EXP : void : caught_exception # ~cpp.except.caught
#pragma token PROC () EXP : void : end_exception # ~cpp.except.end
#pragma token PROC ( INTEGER ) EXP : void : ill_exception # ~cpp.except.bad

#pragma token TYPE exception_type # ~cpp.try.type

#pragma token PROC ( EXP : JUMP_BUFFER * :, EXP : FRAME_PTR :,\
    EXP : CODE_PTR : ) STATEMENT try_begin # ~cpp.try.begin
#pragma token PROC ( EXP : JUMP_BUFFER * : ) STATEMENT try_end # ~cpp.try.end

#pragma define throw_exception catch_exception
#pragma define value_exception caught_exception end_exception ill_exception
#pragma define exception_type try_begin try_end


#endif
