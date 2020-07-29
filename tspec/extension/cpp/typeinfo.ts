# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$LINKAGE = "C++" ;
$NAMESPACE = "std" ;

+USE "cpp", "exception.ts", "except" ;

%%
// CLASS RETURNED BY TYPEID OPERATOR
class type_info {
    // Implementation dependent details
    class __base_info {} ;
    int __code ;
    const char *__name ;
    __base_info *__base ;
public :
    virtual ~type_info () ;
    bool operator== ( const type_info & ) const ;
    bool operator!= ( const type_info & ) const ;
    bool before ( const type_info & ) const ;
    const char *name () const ;
private :
    type_info ( const type_info & ) ;
    type_info &operator= ( const type_info & ) ;
} ;

// EXCEPTION THROWN BY BAD DYNAMIC_CAST
class bad_cast : public exception {
    // Implementation dependent details
public :
    bad_cast () throw () ;
    bad_cast ( const bad_cast & ) throw () ;
    bad_cast &operator= ( const bad_cast & ) throw () ;
    virtual ~bad_cast () throw () ;
    virtual const char *what () const throw () ;
} ;

// EXCEPTION THROWN BY BAD TYPEID
class bad_typeid : public exception {
    // Implementation dependent details
public :
    bad_typeid () throw () ;
    bad_typeid ( const bad_typeid & ) throw () ;
    bad_typeid &operator= ( const bad_typeid & ) throw () ;
    virtual ~bad_typeid () throw () ;
    virtual const char *what () const throw () ;
} ;
%%
