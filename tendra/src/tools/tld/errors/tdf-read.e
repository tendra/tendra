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
#include "tdf-read.h"
]$;

header(c) $[
#include "solve-cycles.h"
]$;

error "unexpected eof in tdf" ("reader" : "TDFReaderP") {
    "${file name}: byte ${byte number}: unexpected end of file",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = tdf_reader_name (reader);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = tdf_reader_byte (reader);
	]$
    }
};

error "tdf integer too big in tdf" ("reader" : "TDFReaderP") {
    "${file name}: byte ${byte number}: TDF integer is too large for this machine",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = tdf_reader_name (reader);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = tdf_reader_byte (reader);
	]$
    }
};

error "unsupported char size in tdf" ("reader" : "TDFReaderP") {
    "${file name}: byte ${byte number}: string character size ${character size} is not supported on this machine",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = tdf_reader_name (reader);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = tdf_reader_byte (reader);
	]$
    }, {
	"character size" : "unsigned" $[
	    write_unsigned (ostream, closure->character_size);
	]$
    }
};

error "bad name type in tdf" ("reader" : "TDFReaderP") {
    "${file name}: byte ${byte number}: name type ${name type} is unknown",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = tdf_reader_name (reader);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = tdf_reader_byte (reader);
	]$
    }, {
	"name type" : "unsigned" $[
	    write_unsigned (ostream, closure->name_type);
	]$
    }
};

error "expected eof in tdf" ("reader" : "TDFReaderP") {
    "${file name}: byte ${byte number}: expected end of file",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = tdf_reader_name (reader);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = tdf_reader_byte (reader);
	]$
    }
};
