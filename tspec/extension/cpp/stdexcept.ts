# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$LINKAGE = "C++" ;
$NAMESPACE = "std" ;

+USE "cpp", "exception.ts", "except" ;

%%
// DUMMY STRING TYPE
typedef const char *_string ;

// BASE CLASS FOR LOGICAL ERROR EXCEPTIONS
class logic_error : public exception {
public :
    logic_error ( const _string & ) ;
} ;

// DOMAIN ERROR EXCEPTIONS
class domain_error : public logic_error {
public :
    domain_error ( const _string & ) ;
} ;

// INVALID ARGUMENT EXCEPTIONS
class invalid_argument : public logic_error {
public :
    invalid_argument ( const _string & ) ;
} ;

// LENGTH ERROR EXCEPTIONS
class length_error : public logic_error {
public :
    length_error ( const _string & ) ;
} ;

// OUT OF RANGE ERROR EXCEPTIONS
class out_of_range : public logic_error {
public :
    out_of_range ( const _string & ) ;
} ;

// BASE CLASS FOR RUNTIME ERROR EXCEPTIONS
class runtime_error : public exception {
public :
    runtime_error ( const _string & ) ;
} ;

// RANGE ERROR EXCEPTIONS
class range_error : public runtime_error {
public :
    range_error ( const _string & ) ;
} ;

// OVERFLOW ERROR EXCEPTIONS
class overflow_error : public runtime_error {
public :
    overflow_error ( const _string & ) ;
} ;
%%
