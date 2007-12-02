#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#


header $[
#include "arg-parse.h"
]$;

header(c) $[
#include "solve-cycles.h"
]$;

fatal "bad mode" {
    "illegal mode character '${mode}'; should be one of 'c', 'l', 't' or 'x'",
    {
	"mode" : "char" $[
	    write_char (ostream, closure->mode);
	]$
    }
};

fatal "missing files" {
    "no files specified for processing"
};

fatal "no memory" {
    "cannot allocate memory"
};

fatal "read error" {
    "error reading from file '${file name}': ${system error}",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"system error" : "int" $[
	    write_system_error (ostream);
	]$ $[
	]$
    }
};

fatal "write error" {
    "error writing to file '${file name}': ${system error}",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"system error" : "int" $[
	    write_system_error (ostream);
	]$ $[
	]$
    }
};

error "cannot open input file" {
    "cannot open input file '${file name}': ${system error}",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"system error" : "int" $[
	    write_system_error (ostream);
	]$ $[
	]$
    }
};

fatal "cannot open output file" {
    "cannot open output file '${file name}': ${system error}",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"system error" : "int" $[
	    write_system_error (ostream);
	]$ $[
	]$
    }
};

error "cannot open library file" {
    "cannot open library file '${file name}': ${system error}",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"system error" : "int" $[
	    write_system_error (ostream);
	]$ $[
	]$
    }
};

error "illegal external name" {
    "illegal external name '${name}'",
    {
	"name" : "CStringP" $[
	    write_cstring (ostream, closure->name);
	]$
    }
};
