/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
    TYPE ALGEBRA FOR CALCULUS TOOL

    This algebra describes the types used by the calculus tool.
*/

ALGEBRA calculus (1.2):


/*
    PRIMITIVE TYPES

    The primitive types, from which everything else is built are integers
    and strings.
*/

int =			"int" ;
number =		"unsigned long" ;
string =		"char *" ;


/*
    IDENTITY TYPES

    Convenient shorthands are introduced for most pointer types, along
    with some aliases used in the disk reading and writing routines.
*/

name_string =		string ;
zero_int =		int ;
int_P =			PTR int ;
number_P =		PTR number ;
string_P =		PTR string ;
ARGUMENT_P =		PTR ARGUMENT ;
CLASS_ID_P =		PTR CLASS_ID ;
CLASS_ID_P_P =		PTR CLASS_ID_P ;
COMPONENT_P =		PTR COMPONENT ;
ECONST_P =		PTR ECONST ;
ENUM_P =		PTR ENUM ;
FIELD_P =		PTR FIELD ;
IDENTITY_P =		PTR IDENTITY ;
MAP_P =			PTR MAP ;
PRIMITIVE_P =		PTR PRIMITIVE ;
STRUCTURE_P =		PTR STRUCTURE ;
TYPE_P =		PTR TYPE ;
TYPE_P_P =		PTR TYPE_P ;
UNION_P =		PTR UNION ;


/*
    OVERALL ALGEBRA DEFINITION

    A complete algebra consists of a name, lists of primitives, identities,
    enumerations, structures and unions, plus a list of all types used in
    the algebra definition.
*/

struct ALGEBRA_DEFN (alg) = {
    string name ;
    int major_no, minor_no ;
    LIST PRIMITIVE_P primitives ;
    LIST IDENTITY_P identities ;
    LIST ENUM_P enumerations ;
    LIST STRUCTURE_P structures ;
    LIST UNION_P unions ;
    LIST TYPE_P types ;
} ;


/*
    CLASS IDENTIFIERS

    Each type defined by the algebra has an associated class identifier
    giving its name (both long and short forms).  These names may also
    be qualified by a hash symbol or a colon. 
*/

struct CLASS_ID (cid) = {
    string name ;
    string name_aux ;
    int flag ;
    name_string file ;
    int line ;
} ;


/*
    PRIMITIVE TYPES

    A primitive type consists of a class identifier, giving the name of
    the type, and a string, giving the type definition.
*/

struct PRIMITIVE (prim) = {
    CLASS_ID_P id ;
    string defn ;
} ;


/*
    ENUMERATION CONSTANTS

    An enumeration constant consists of an enumerator name and an associated
    integral value.
*/

struct ECONST (ec) = {
    string name ;
    number value ;
} ;


/*
    ENUMERATION TYPES

    An enumeration type consists of a class identifier, giving the type
    name, the list of enumeration constants comprising the type, and
    the order of the type (one more than the largest constant).
*/

struct ENUM (en) = {
    CLASS_ID_P id ;
    LIST ECONST_P consts ;
    number order ;
    int lists ;
} ;


/*
    IDENTITY TYPES

    A type identity consists of a class identifier, and the type which is
    named by this identifier.
*/

struct IDENTITY (ident) = {
    CLASS_ID_P id ;
    TYPE_P defn ;
} ;


/*
    STRUCTURE COMPONENTS

    A structure component consists of a string, giving the component name,
    and the associated component type.  A default value may also be
    provided.
*/

struct COMPONENT (cmp) = {
    string name ;
    TYPE_P type ;
    string value ;
} ;


/*
    STRUCTURE TYPES

    A structure type consists of a class identifier, giving the type name,
    and a list of structure components.
*/

struct STRUCTURE (str) = {
    CLASS_ID_P id ;
    STRUCTURE_P base ;
    LIST COMPONENT_P defn ;
    zero_int output ;
} ;


/*
    UNION FIELDS

    A union field consists of a string, giving the field name, and the list
    of structure components comprising the field.  The field name may be
    qualified by a hash symbol.  A field may be the first element of a
    set.  In this case the int of elements in the set is given by the
    set field.
*/

struct FIELD (fld) = {
    string name ;
    int tag ;
    int flag ;
    int set ;
    FIELD_P base ;
    LIST COMPONENT_P defn ;
} ;


/*
    UNION MAP ARGUMENTS

    A union map argument consists of a string, giving the argument name,
    plus an associated argument type.
*/

struct ARGUMENT (arg) = {
    string name ;
    TYPE_P type ;
} ;


/*
    UNION MAPS

    A union map consists of a string, giving the map name, plus the map
    return type and a list of map arguments.  The map name may be qualified
    by a hash symbol.
*/

struct MAP (map) = {
    string name ;
    int flag ;
    TYPE_P ret_type ;
    LIST ARGUMENT_P args ;
} ;


/*
    UNION TYPES

    A union type consists of a class identifier, giving the type name,
    plus lists of structure components (giving those components common
    to all the union fields), union fields and union maps.  The int
    of union fields is recorded for convenience.
*/

struct UNION (un) = {
    CLASS_ID_P id ;
    UNION_P base ;
    LIST COMPONENT_P s_defn ;
    LIST FIELD_P u_defn ;
    LIST MAP_P map ;
    int no_fields ;
} ;


/*
    TYPES

    A type can be either one of the types defined by the algebra (a
    primitive, an identity, an enumeration, a structure or a union),
    a quoted C type, or a type derived from these using the PTR, LIST,
    VEC and VEC_PTR type constructors.  To allow types to be used before
    they are defined, undefined types are also permitted.  Note that
    all the real types are aliased.
*/

union TYPE (type) = {
    zero_int size ;
} + {
    #	primitive ->			{ PRIMITIVE_P prim ; },
    #	ident ->			{ IDENTITY_P id ; },
    #	enumeration ->			{ ENUM_P en ; },
    #	structure ->			{ STRUCTURE_P struc ; },
    #	onion ->			{ UNION_P un ; },
    #	ptr, list, stack, vec, vec_ptr ->
					{ TYPE_P sub ; },
    	quote ->			{ string defn ; },
    	undef ->			{ string name ; }
} ;


/*
    COMMANDS

    A command for a template file consists of either a simple string,
    a list of commands, a conditional or a loop.
*/

union COMMAND (cmd) = {
    int line ;
} + {
    simple -> {
	string text ;
    },
    compound -> {
	LIST COMMAND seq ;
    },
    loop -> {
	string control ;
	COMMAND body ;
    },
    cond -> {
	string control ;
	COMMAND true_code ;
	COMMAND false_code ;
    }
} ;
