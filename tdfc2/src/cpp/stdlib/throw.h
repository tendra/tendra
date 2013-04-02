/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
