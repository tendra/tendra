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
#include "exception.h"
]$;

internal "exception unhandled" {
    "unhandled exception '${except name}' thrown from line ${line number}, file '${file name}'",
    {
	"except name" : "ExceptionP" $[
	    write_cstring (ostream, exception_name (closure->except_name));
	]$
    }, {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$
    }
};

internal "exception corrupt handler" {
    "corrupt exception handler installed at line ${line number}, file '${file name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$
    }
};

internal "assertion failed" {
    "assertion '${assertion}' failed at line ${line number}, file '${file name}'",
    {
	"assertion" : "CStringP" $[
	    write_cstring (ostream, closure->assertion);
	]$
    }, {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$
    }
};

internal "dalloc multi deallocate" {
    "memory block ${block address} allocated at line ${allocation line number} in '${allocation file name}' is deallocated more than once (second deallocation at line ${line number} in file '${file name}'",
    {
	"block address" : "GenericP" $[
	    write_pointer (ostream, closure->block_address);
	]$
    }, {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$
    }, {
	"allocation file name" : "CStringP" $[
	    write_cstring (ostream, closure->allocation_file_name);
	]$
    }, {
	"allocation line number" : "unsigned" $[
	    write_unsigned (ostream, closure->allocation_line_number);
	]$
    }
};

internal "dalloc corrupt block" {
    "memory block ${block address} is corrupt at deallocation (deallocation at line ${line number} in file '${file name}'",
    {
	"block address" : "GenericP" $[
	    write_pointer (ostream, closure->block_address);
	]$
    }, {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$
    }
};
