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


#ifndef BASIC_INCLUDED
#define BASIC_INCLUDED


/*
    BASIC TYPES TOKEN INTERFACE

    These tokens describe the interface between the compiler and the
    library giving the basic types such as bool, pointers to members
    and pointers to member functions.
*/

#pragma token VARIETY bool_type # ~cpp.bool
#pragma token TYPE ptr_mem_type # ~cpp.pm.type
#pragma token TYPE ptr_mem_func_type # ~cpp.pmf.type
#pragma token TYPE vtable_diag # ~cpp.vtab.diag

#pragma interface bool_type ptr_mem_type ptr_mem_func_type vtable_diag


/*
    RUN-TIME TYPE INFORMATION TOKEN INTERFACE

    These tokens describe the interface between the compiler and the
    library used in the run-time type information routines.
*/

#pragma extend interface "offset.h"

#pragma token TYPE typeid_type # ~cpp.typeid.type
#pragma token TYPE baseid_type # ~cpp.baseid.type

#pragma token PROC ( INTEGER, EXP : char * :, EXP : baseid_type * : )\
    EXP : typeid_type : typeid_make # ~cpp.typeid.make

#pragma token PROC ( INTEGER )\
    EXP : typeid_type * : typeid_basic # ~cpp.typeid.basic

#pragma token PROC ( EXP : typeid_type * :, EXP : OFFSET :,\
    EXP : baseid_type * :, INTEGER, INTEGER )\
    EXP : baseid_type : baseid_make # ~cpp.baseid.make

#pragma token PROC ( EXP : VTABLE ** :, EXP : typeid_type * : )\
    EXP : void * : dyn_cast # ~cpp.dynam.cast

#pragma interface typeid_type typeid_make typeid_basic baseid_make dyn_cast


/*
    TERMINATION FUNCTION TOKEN INTERFACE

    These tokens describe interface between the compiler and the library
    used in termination functions.
*/

#pragma token TYPE destr_type # ~cpp.destr.type
#pragma token PROC () STATEMENT destr_init # ~cpp.destr.init
#pragma token PROC ( EXP : destr_type * :, EXP : CLASS * :,\
    EXP : DESTRUCTOR : ) STATEMENT destr_global # ~cpp.destr.global
#pragma token PROC ( EXP : destr_type * :, EXP : CLASS * :,\
    EXP : DESTRUCTOR : ) STATEMENT destr_local # ~cpp.destr.local
#pragma token PROC ( EXP : destr_type * : )\
    STATEMENT destr_end # ~cpp.destr.end
#pragma token EXP const : destr_type : destr_null # ~cpp.destr.null
#pragma token PROC ( EXP : destr_type * : )\
    EXP : CLASS * : destr_ptr # ~cpp.destr.ptr
#pragma token FUNC int ( EXITER ) : destr_atexit # ~cpp.destr.atexit
#pragma token STATEMENT destr_main # ~cpp.start

#pragma interface destr_type destr_init destr_global destr_local
#pragma interface destr_end destr_null destr_ptr destr_atexit destr_main


#endif
