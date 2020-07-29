/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef BASIC_INCLUDED
#define BASIC_INCLUDED

/*
 * Basic types token interface
 *
 * These tokens describe the interface between the compiler and the
 * library giving the basic types such as bool, pointers to members
 * and pointers to member functions.
 */

#pragma token VARIETY bool_type # ~cpp.bool
#pragma token TYPE ptr_mem_type # ~cpp.pm.type
#pragma token TYPE ptr_mem_func_type # ~cpp.pmf.type
#pragma token TYPE vtable_diag # ~cpp.vtab.diag

#pragma interface bool_type ptr_mem_type ptr_mem_func_type vtable_diag


/*
 * Run-Time Type Information token interface
 *
 * These tokens describe the interface between the compiler and the
 * library used in the run-time type information routines.
 */

#pragma extend interface "offset.h"

#pragma token TYPE typeid_type # ~cpp.typeid.type
#pragma token TYPE baseid_type # ~cpp.baseid.type

#pragma token PROC ( INTEGER, EXP : char * :, EXP : baseid_type * : ) \
	EXP : typeid_type : typeid_make # ~cpp.typeid.make

#pragma token PROC ( INTEGER ) \
	EXP : typeid_type * : typeid_basic # ~cpp.typeid.basic

#pragma token PROC ( EXP : typeid_type * :, EXP : OFFSET :, \
	EXP : baseid_type * :, INTEGER, INTEGER )\
	EXP : baseid_type : baseid_make # ~cpp.baseid.make

#pragma token PROC ( EXP : VTABLE ** :, EXP : typeid_type * : ) \
	EXP : void * : dyn_cast # ~cpp.dynam.cast

#pragma interface typeid_type typeid_make typeid_basic baseid_make dyn_cast


/*
 * Termination function token interface
 *
 * These tokens describe interface between the compiler and the library
 * used in termination functions.
 */

#pragma token TYPE destr_type # ~cpp.destr.type
#pragma token PROC () STATEMENT destr_init # ~cpp.destr.init
#pragma token PROC ( EXP : destr_type * :, EXP : CLASS * :, \
	EXP : DESTRUCTOR : ) STATEMENT destr_global # ~cpp.destr.global
#pragma token PROC ( EXP : destr_type * :, EXP : CLASS * :, \
	EXP : DESTRUCTOR : ) STATEMENT destr_local # ~cpp.destr.local
#pragma token PROC ( EXP : destr_type * : ) \
	STATEMENT destr_end # ~cpp.destr.end
#pragma token EXP const : destr_type : destr_null # ~cpp.destr.null
#pragma token PROC ( EXP : destr_type * : ) \
	EXP : CLASS * : destr_ptr # ~cpp.destr.ptr
#pragma token FUNC int ( EXITER ) : destr_atexit # ~cpp.destr.atexit
#pragma token STATEMENT destr_main # ~cpp.start

#pragma interface destr_type destr_init destr_global destr_local
#pragma interface destr_end destr_null destr_ptr destr_atexit destr_main

#endif

