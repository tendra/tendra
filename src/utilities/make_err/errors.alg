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
