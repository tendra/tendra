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
#include "entry.h"
]$;

error "bad id substitution" {
    "${file name}: ${line number}: substituted identifier '${identifier name}' is not a parameter or result",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$
    }, {
	"identifier name" : "EntryP" $[
	    write_key (ostream, entry_key (closure->identifier_name));
	]$
    }
};

error "bad mod id substitution" {
    "${file name}: ${line number}: substituted mutable identifier '${identifier name}' is not a parameter",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$
    }, {
	"identifier name" : "EntryP" $[
	    write_key (ostream, entry_key (closure->identifier_name));
	]$
    }
};

error "mod id in assign" {
    "${file name}: ${line number}: substituted mutable identifier '${identifier name}' in assignment operator definition",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$
    }, {
	"identifier name" : "EntryP" $[
	    write_key (ostream, entry_key (closure->identifier_name));
	]$
    }
};

error "bad ref id substitution" {
    "${file name}: ${line number}: substituted reference identifier '${identifier name}' is not a parameter",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$
    }, {
	"identifier name" : "EntryP" $[
	    write_key (ostream, entry_key (closure->identifier_name));
	]$
    }
};

error "ref id in param op" {
    "${file name}: ${line number}: substituted address of identifier '${identifier name}' in parameter assignment operator definition",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$
    }, {
	"identifier name" : "EntryP" $[
	    write_key (ostream, entry_key (closure->identifier_name));
	]$
    }
};

error "bad label substitution" {
    "${file name}: ${line number}: substituted label '${identifier name}' in unparameterised block",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$
    }, {
	"identifier name" : "EntryP" $[
	    write_key (ostream, entry_key (closure->identifier_name));
	]$
    }
};

error "bad exception substitution" {
    "${file name}: ${line number}: substituted exception call in unsuitable code block",
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

error "bad advance substitution" {
    "${file name}: ${line number}: substituted lexer advance call in unsuitable code block",
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

error "bad terminal substitution" {
    "${file name}: ${line number}: substituted current terminal call in unsuitable code block",
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

error "code undefined result" ("code" : "GenericP") {
    "${file name}: ${line number}: code result '${identifier name}' is not defined",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_code_file ((CCodeP) code);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_code_line ((CCodeP) code);
	]$
    }, {
	"identifier name" : "EntryP" $[
	    write_key (ostream, entry_key (closure->identifier_name));
	]$
    }
};
