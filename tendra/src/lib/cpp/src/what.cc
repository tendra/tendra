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


#include <exception>
#include <new>
#include <typeinfo>
using namespace std ;


/*
    EXCEPTION BASE CLASS

    This routines give the definitions of the member function of the
    exception class.
*/

exception::exception () throw ()
{
    return ;
}

exception::exception ( const exception & ) throw ()
{
    return ;
}

exception &exception::operator= ( const exception & ) throw ()
{
    return ( *this ) ;
}

exception::~exception () throw ()
{
    return ;
}

const char *exception::what () const throw ()
{
    return ( "exception" ) ;
}


/*
    BAD EXCEPTION CLASS

    This routines give the definitions of the member function of the
    bad_exception class.
*/

bad_exception::bad_exception () throw ()
{
    return ;
}

bad_exception::bad_exception ( const bad_exception & ) throw ()
{
    return ;
}

bad_exception &bad_exception::operator= ( const bad_exception & ) throw ()
{
    return ( *this ) ;
}

bad_exception::~bad_exception () throw ()
{
    return ;
}

const char *bad_exception::what () const throw ()
{
    return ( "bad_exception" ) ;
}


/*
    BAD ALLOCATION EXCEPTION CLASS

    This routines give the definitions of the member function of the
    bad_alloc class.
*/

bad_alloc::bad_alloc () throw ()
{
    return ;
}

bad_alloc::bad_alloc ( const bad_alloc & ) throw ()
{
    return ;
}

bad_alloc &bad_alloc::operator= ( const bad_alloc & ) throw ()
{
    return ( *this ) ;
}

bad_alloc::~bad_alloc () throw ()
{
    return ;
}

const char *bad_alloc::what () const throw ()
{
    return ( "bad_alloc" ) ;
}


/*
    BAD DYNAMIC CAST EXCEPTION CLASS

    This routines give the definitions of the member function of the
    bad_cast class.
*/

bad_cast::bad_cast () throw ()
{
    return ;
}

bad_cast::bad_cast ( const bad_cast & ) throw ()
{
    return ;
}

bad_cast &bad_cast::operator= ( const bad_cast & ) throw ()
{
    return ( *this ) ;
}

bad_cast::~bad_cast () throw ()
{
    return ;
}

const char *bad_cast::what () const throw ()
{
    return ( "bad_cast" ) ;
}


/*
    BAD TYPEID EXCEPTION CLASS

    This routines give the definitions of the member function of the
    bad_typeid class.
*/

bad_typeid::bad_typeid () throw ()
{
    return ;
}

bad_typeid::bad_typeid ( const bad_typeid & ) throw ()
{
    return ;
}

bad_typeid &bad_typeid::operator= ( const bad_typeid & ) throw ()
{
    return ( *this ) ;
}

bad_typeid::~bad_typeid () throw ()
{
    return ;
}

const char *bad_typeid::what () const throw ()
{
    return ( "bad_typeid" ) ;
}
