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

fatal "bad tab width" {
    "bad tab width '${tab width}'",
    {
	"tab width" : "CStringP" $[
	    write_cstring (ostream, closure->tab_width);
	]$
    }
};

fatal "bad factor limit" {
    "bad factor limit '${factor limit}'",
    {
	"factor limit" : "CStringP" $[
	    write_cstring (ostream, closure->factor_limit);
	]$
    }
};

fatal "bad inlining phase" {
    "bad inlining phase '${phase}'",
    {
	"phase" : "CStringP" $[
	    write_cstring (ostream, closure->phase);
	]$
    }
};

fatal "bad language" {
    "unknown language '${language name}' (should be 'ansi-c', 'pre-ansi-c', 'ossg-c' or 'test')",
    {
	"language name" : "CStringP" $[
	    write_cstring (ostream, closure->language_name);
	]$
    }
};

fatal "bad language option" {
    "language '${language name}' doesn't understand option '${option}'",
    {
	"language name" : "CStringP" $[
	    write_cstring (ostream, closure->language_name);
	]$
    }, {
	"option" : "CStringP" $[
	    write_cstring (ostream, closure->option);
	]$
    }
};

fatal "bad split size" {
    "bad split size '${split size}'",
    {
	"split size" : "CStringP" $[
	    write_cstring (ostream, closure->split_size);
	]$
    }
};

fatal "usage" {
    "language '${language name}' requires ${number input files} input files and ${number output files} output files\n${usage}",
    {
	"language name" : "CStringP" $[
	    write_cstring (ostream, closure->language_name);
	]$
    }, {
	"number input files" : "unsigned" $[
	    write_unsigned (ostream, closure->number_input_files);
	]$
    }, {
	"number output files" : "unsigned" $[
	    write_unsigned (ostream, closure->number_output_files);
	]$
    }, {
	"usage" : "ArgUsageP" $[
	    write_arg_usage (ostream, closure->usage);
	]$
    }
};

fatal "cannot open dump file" {
    "cannot open dump file '${file name}': ${system error}",
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

fatal "multiple dump files" {
    "more than one dump file specified"
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

fatal "cannot open input file" {
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
