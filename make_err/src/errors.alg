/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
    TYPE ALGEBRA FOR ERRORS TOOL

    This algebra describes the types used by the errors tool.
*/

ALGEBRA errors:


/*
    PRIMITIVE TYPES

    The primitive types, from which everything else is built are integers
    and strings.
*/

int = "int" ;
string = "char *" ;


/*
    NUMBERED IDENTIFIERS

    Keys, properties, types and usages are all examples of numbered
    identifiers.  These consist of a string and an associated number.
*/

union NAME (name) = {
    string id ;
    int number ;
} + {
    basic -> {
	/* empty */
    }
} ;

KEY = NAME ;
PROPERTY = NAME ;
TYPE = NAME ;
USAGE = NAME ;


/*
    MESSAGE COMPONENT

    A message component can be either a parameter name or a string.
*/

union MESSAGE (msg) = {
    /* empty */
} + {
    param -> {
	PARAM arg ;
    },
    text -> {
	string arg ;
    }
} ;


/*
    MESSAGE MAPPING

    A message mapping associates a list of message components with a key.
*/

union MAP (map) = {
    KEY key ;
    LIST MESSAGE msg ;
    LIST MESSAGE alt_msg ;
} + {
    basic -> {
	/* empty */
    }
} ;


/*
    MESSAGE PARAMETER

    A message parameter consists of a name, the type associated with that
    name, and a parameter number.
*/

union PARAM (param) = {
    TYPE type ;
    string name ;
    int number ;
} + {
    basic -> {
	/* empty */
    }
} ;


/*
    DATABASE ENTRY

    A database entry consists of two entry names, a list of message
    parameters, an associated usage and list of properties, plus a list
    of message maps.
*/

union ENTRY (entry) = {
    string name ;
    string alt_name ;
    LIST PARAM signature ;
    USAGE use ;
    USAGE alt_use ;
    LIST PROPERTY props ;
    LIST MAP maps ;
} + {
    basic -> {
	/* empty */
    }
} ;
