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
#include "dstring.h"
#include "name-key.h"
]$;

header(c) $[
#include "solve-cycles.h"
]$;

fatal "tld multiple debug files" {
    "more than one debug file specified"
};

fatal "tld cannot open debug file" {
    "cannot open debug file '${file name}': ${system error}",
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

fatal "tld multiple output files" {
    "more than one output file specified"
};

fatal "tld multiple unit files" {
    "more than one unit set file specified"
};

error "multiply renamed name" {
    "${shape name} '${name}' is renamed multiple times",
    {
	"shape name" : "NStringP" $[
	    write_nstring (ostream, closure->shape_name);
	]$
    }, {
	"name" : "NameKeyP" $[
	    write_name_key (ostream, closure->name);
	]$
    }
};
