# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$LINKAGE = "C++" ;
$NAMESPACE = "std" ;

+SUBSET "except" := {
    $LINKAGE = "C++" ;
    $NAMESPACE = "" ;
%%
// BASE CLASS FOR STANDARD EXCEPTIONS
class exception {
    // Implementation dependent details
public :
    exception () throw () ;
    exception ( const exception & ) throw () ;
    exception &operator= ( const exception & ) throw () ;
    virtual ~exception () throw () ;
    virtual const char *what () const throw () ;
} ;

// SPECIAL EXCEPTION SPECIFICATION CLASS
class bad_exception : public exception {
    // Implementation dependent details
public :
    bad_exception () throw () ;
    bad_exception ( const bad_exception & ) throw () ;
    bad_exception &operator= ( const bad_exception & ) throw () ;
    virtual ~bad_exception () throw () ;
    virtual const char *what () const throw () ;
} ;

// UNEXPECTED EXCEPTION HANDLERS
typedef void ( *unexpected_handler ) () ;
unexpected_handler set_unexpected ( unexpected_handler ) throw () ;
void unexpected () ;

// TERMINATE HANDLERS
typedef void ( *terminate_handler ) () ;
terminate_handler set_terminate ( terminate_handler ) throw () ;
void terminate () ;

// STACK UNWINDING FLAG
bool uncaught_exception () ;
%%
} ;
