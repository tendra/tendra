# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$LINKAGE = "C++" ;
$NAMESPACE = "" ;

+USE "cpp", "cstdlib.ts" ;
+USE "cpp", "exception.ts" ;

+SUBSET "bad_alloc" := {
    # This is done as a subset because it is in the std namespace
    $LINKAGE = "C++" ;
    $NAMESPACE = "std" ;
%%
// EXCEPTION THROWN BY BAD NEW OPERATION
class bad_alloc : public exception {
    // Implementation dependent details
public :
    bad_alloc () throw () ;
    bad_alloc ( const bad_alloc & ) throw () ;
    bad_alloc &operator= ( const bad_alloc & ) throw () ;
    virtual ~bad_alloc () throw () ;
    virtual const char *what () const throw () ;
} ;

// SURROGATE NO-EXCEPTION CLASS
struct nothrow_t {} ;
extern const nothrow_t nothrow ;

// NEW HANDLERS
typedef void ( *new_handler ) () ;
new_handler set_new_handler ( new_handler ) throw () ;
%%
} ;

%%
// STANDARD ALLOCATION OPERATORS
void *operator new ( std::size_t ) throw ( std::bad_alloc ) ;
void *operator new [] ( std::size_t ) throw ( std::bad_alloc ) ;
void operator delete ( void * ) throw () ;
void operator delete [] ( void * ) throw () ;

// NO-EXCEPTION ALLOCATION OPERATORS
void *operator new ( std::size_t, const std::nothrow_t & ) throw () ;
void *operator new [] ( std::size_t, const std::nothrow_t & ) throw () ;
void operator delete ( void *, const std::nothrow_t & ) throw () ;
void operator delete [] ( void *, const std::nothrow_t & ) throw () ;

// PLACEMENT ALLOCATION OPERATORS
inline void *operator new ( std::size_t, void *p ) throw () { return ( p ) ; }
inline void *operator new [] ( std::size_t, void *p ) throw () { return ( p ) ; }
inline void operator delete ( void *, void * ) throw () { return ; }
inline void operator delete [] ( void *, void * ) throw () { return ; }
%%
