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


#ifndef IMPLEMENT_INCLUDED
#define IMPLEMENT_INCLUDED


/*
    STANDARD HEADERS

    The following standard headers are required: cstdlib for size_t and
    new for bad_alloc.  Also longjump.h is included.
*/

#define __CPP_NATIVE_ATEXIT
#include <cstdlib>
#include <new>
using namespace std ;
#pragma extend interface "longjump.h"


/*
    IMPLEMENTATION NAMESPACE

    The types and functions declared in this module describe the interface
    between the language support library and the compiler.  They are all
    declared in the __IMPL namespace.
*/

namespace __IMPL {


    /*
	BOOLEAN TYPE

	This type gives the underlying representation of bool.
    */

    typedef int BOOLEAN ;


    /*
	TYPE REPRESENTING A POINTER TO MEMBER

	A pointer to data member is represented by an integer giving the
	offset of the member from the start of the structure (in bytes),
	plus one.  The one is to allow a value of zero to be used for the
	null pointer to member.
    */

    typedef int PTR_MEMBER ;


    /*
	TYPE REPRESENTING A GENERIC FUNCTION POINTER

	This type is used to stand for a generic pointer to function.
    */

    typedef void ( *FUNCTION ) () ;


    /*
	TYPE REPRESENTING A POINTER TO MEMBER FUNCTION

	This type is used to represent a pointer to member function.  It
	consists of a base class offset, an index into the virtual function
	table (or -1 for non-virtual functions, or 0 for null pointer to
	member functions) and either a pointer to function or an offset
	giving the location of the virtual function table.
    */

    struct PTR_MEM_FUNC {
	short delta ;
	short index ;
	union {
	    FUNCTION func ;
	    short off ;
	} u ;
    } ; 


    /*
	TYPE REPRESENTING A VIRTUAL FUNCTION TABLE

	This type is used to represent a virtual function table.  This
	consists of any array of pointers to the virtual member functions.
	The first entry is a dummy, the space being occupied by a pointer
	to the run-time type information and a offset back to the start
	of the object (this extra entry corresponds to the value of
	VIRTUAL_EXTRA in interface.h).  In general there can be any number
	of virtual functions (see vtable.p), the example implementation
	is for a single function.
    */

    struct TYPE_INFO ;

    struct VTABLE_EXTRA {
	TYPE_INFO *rtti ;
	short off ;
    } ;

    union VTABLE_1 {
	PTR_MEM_FUNC funcs [2] ;
	VTABLE_EXTRA extra ;
    } ;

    typedef VTABLE_1 VTABLE ;


    /*
	TYPE REPRESENTING A RUN-TIME TYPE INFORMATION STRUCTURE

	This type is used to represent the run-time type information
	associated with a type.  This consists of a string, giving the
	type name and a list of base class information structures.
	Because the std::type_info class has a virtual destructor
	a virtual function containing one element is also required,
	otherwise the elements must correspond exactly to those of
	std::type_info.
    */

    struct BASE_INFO {
	TYPE_INFO *rtti ;
	int off ;
	BASE_INFO *next ;
	int access ;
	int virt ;
    } ;

    struct TYPE_INFO {
	int code ;
	const char *name ;
	BASE_INFO *base ;
	VTABLE_1 *vptr ;
    } ;


    /*
	TYPE REPRESENTING A LIST OF DESTRUCTORS

	This type is used to represent a list of destructor functions.  It
	consists of a pointer to the argument, a pointer to the destructor
	function and a pointer to the next element of the list.
    */

    struct CLASS ;
    typedef void ( *DESTRUCTOR ) ( CLASS *, int ) ;

    struct DTOR_LIST {
	DTOR_LIST *next ;
	CLASS *arg ;
	DESTRUCTOR func ;
    } ;


    /*
	TYPE REPRESENTING A LONG JUMP BUFFER

	This type is used to represent a long jump buffer.  It consists
	of a linked list of frame pointers and code pointers (as defined
	in longjump.h.
    */

    struct JUMP_BUFFER {
	JUMP_BUFFER *next ;
	DTOR_LIST *dtors ;
	FRAME_PTR frame ;
	CODE_PTR label ;
    } ;


    /*
	TYPE REPRESENTING AN EXCEPTION

	This type is used to represent an exception.  It consists of the
	type information for the value being thrown, two pointers to the
	value (the second of which may be changed via a base class
	conversion when catching an exception), a pointer to the current
	long jump buffer, and a flag which is set to true during stack
	unwinding.
    */

    struct EXCEPTION {
	TYPE_INFO *type ;
	DESTRUCTOR dtor ;
	void *value [2] ;
	JUMP_BUFFER *buf [3] ;
	bool unwinding ;
	bool allocated ;
    } ;
}

using namespace __IMPL ;


/*
    EXTERNALLY VISIBLE OBJECTS

    This list gives the externally visible objects and functions used
    in the standard token library.  They are all given C linkage to avoid
    name mangling problems.  Note that the macro __TCPPLUS_ti_vtbl, which
    represents the virtual function table of std::type_info, is dependent
    on the name mangling conventions.
*/

#define __TCPPLUS_ti_vtbl	__vt__Q23std9type_info

extern "C" {
    typedef void ( *EXITER ) ( void ) ;
    void __TCPPLUS_init () ;
    void __TCPPLUS_term () ;
    int __TCPPLUS_atexit ( EXITER ) ;
    void *__TCPPLUS_new ( size_t ) throw ( bad_alloc ) ;
    void *__TCPPLUS_new_nothrow ( size_t ) throw () ;
    void __TCPPLUS_delete ( void * ) throw () ;
    void __TCPPLUS_pure () ;
    void __TCPPLUS_type_info ( VTABLE * ) ;
    void *__TCPPLUS_dynamic_cast ( VTABLE **, TYPE_INFO * ) ;
    void *__TCPPLUS_catch_cast ( void *, TYPE_INFO *, TYPE_INFO *, int, int ) ;
    int __TCPPLUS_catch ( TYPE_INFO * ) ;
    void __TCPPLUS_throw ( void *, TYPE_INFO *, DESTRUCTOR ) ;
    void __TCPPLUS_handled () ;
    void __TCPPLUS_unexpected ( int ) ;
    void *__TCPPLUS_alloc_except ( size_t ) ;
    void __TCPPLUS_assert ( const char *, int ) ;
    extern DTOR_LIST *__TCPPLUS_dtors ;
    extern VTABLE_1 __TCPPLUS_ti_vtbl ;
    extern TYPE_INFO __TCPPLUS_typeid [] ;
    extern EXCEPTION __TCPPLUS_except ;
}


/*
    ASSERTIONS

    These macros may be used in debugging mode to catch internal run-time
    errors.
*/

#ifdef DEBUG
#define ASSERT( X )	if ( !( X ) ) __TCPPLUS_assert ( __FILE__, __LINE__ )
#else
#define ASSERT( X )
#endif


#endif
