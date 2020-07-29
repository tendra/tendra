/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
    TYPE ALGEBRA FOR TDF GENERATOR TOOL

    This algebra describes the types used by the TDF generator tool.
*/

ALGEBRA tdf:


/*
    PRIMITIVE TYPES

    The primitive types, from which everything else is built are integers
    and strings.
*/

int = "int" ;
unsigned = "unsigned" ;
string = "char *" ;


/*
    TYPE REPRESENTING A TDF CONSTRUCT PARAMETER

    A construct parameter consists of a parameter name and a parameter
    sort.  The brk and align arguments give alignment information.
*/

union PARAMETER (par) = {
    string name ;
    SORT type ;
    int brk ;
    int align ;
    int intro ;
} + {
    basic -> {
	/* empty */
    }
} ;


/*
    TYPE REPRESENTING A TDF CONSTRUCT

    A construct consists of a construct name, an encoding value, a result
    sort and a list of parameters.
*/

union CONSTRUCT (cons) = {
    string name ;
    unsigned encode ;
    SORT res ;
    LIST PARAMETER pars ;
    unsigned kind ;
} + {
    basic -> {
	/* empty */
    }
} ;


/*
    TYPE REPRESENTING A TDF SORT

    A sort is defined in two parts, a sort name and any associated sort
    information.  This is to allow sorts to be used before they are
    defined.  A sort can be a built-in sort (such as tdfstring), a basic
    sort consisting of a list of constructs, a dummy sort with only a
    single construct, a list sort, a simple list sort or an optional sort.
*/

union SORT_INFO (info) = {
    string name ;
} + {
    builtin -> {
	/* empty */
    },
    basic -> {
	unsigned bits ;
	unsigned extend ;
	unsigned max ;
	LIST CONSTRUCT cons ;
	CONSTRUCT sortname ;
    },
    dummy -> {
	CONSTRUCT cons ;
    },
    clist, slist, option -> {
	SORT arg ;
    }
} ;

union SORT (sort) = {
    string name ;
    string caps ;
    string link ;
    string unit ;
    int code ;
    int mark ;
    int special ;
    int edge ;
    SORT_INFO info ;
} + {
    basic -> {
	/* empty */
    }
} ;


/*
    TYPE REPRESENTING A TDF LINKAGE ITEM

    A linkage item consists of a sort and an associated linkage name.
*/

union LINKAGE (link) = {
    string name ;
    SORT type ;
} + {
    basic -> {
	/* empty */
    }
} ;


/*
    TYPE REPRESENTING THE TDF SPECIFICATION

    The specification consists of a version number, a list of sorts, plus
    lists of linkable entities.
*/

union SPECIFICATION (spec) = {
    unsigned major, minor ;
    LIST SORT sorts ;
    LIST LINKAGE vars ;
    LIST LINKAGE eqns ;
    LIST LINKAGE foreign ;
} + {
    basic -> {
	/* empty */
    }
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
    },
    use -> {
	string sort ;
	string cons ;
    },
    special -> {
	string sort ;
	string cons ;
    }
} ;
