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
#include "istream.h"
]$;

###############################################################################
## These errors are used by the lexical analyser:
###############################################################################

error "illegal character" ("istream" : "IStreamP") {
    "${file name}: ${line number}: illegal character '${character}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }, {
	"character" : "char" $[
	    write_escaped_char (ostream, closure->character);
	]$
    }
};

error "illegal comment character" ("istream" : "IStreamP") {
    "${file name}: ${line number}: illegal comment character '${character}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }, {
	"character" : "char" $[
	    write_escaped_char (ostream, closure->character);
	]$
    }
};

error "eof in comment" ("istream" : "IStreamP") {
    "${file name}: ${line number}: end of file in comment",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "unknown builtin" ("istream" : "IStreamP") {
    "${file name}: ${line number}: unknown builtin '%${builtin}%'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }, {
	"builtin" : "CStringP" $[
	    write_cstring (ostream, closure->builtin);
	]$
    }
};

error "null character in builtin" ("istream" : "IStreamP") {
    "${file name}: ${line number}: null character in builtin",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

error "eof in builtin" ("istream" : "IStreamP") {
    "${file name}: ${line number}: end of file in builtin",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

error "newline in builtin" ("istream" : "IStreamP") {
    "${file name}: ${line number}: newline in builtin",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

error "expected hash" ("istream" : "IStreamP") {
    "${file name}: ${line number}: second character missing from '##' operator",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

error "expected pipe" ("istream" : "IStreamP") {
    "${file name}: ${line number}: second character missing from '||' operator",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};
