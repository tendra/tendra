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
#include "c-lexer.h"
#include "c-parser.h"
#include "key.h"
#include "types.h"
]$;

###############################################################################
## These errors are generated from the SID parser itself.  They need doing
## properly later on.
###############################################################################

fatal "c expected basic" {
    "${file name}: ${line number}: expected basic '${class name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"class name" : "CStringP" $[
	    write_cstring (ostream, closure->class_name);
	]$
    }
};

fatal "c expected non-terminal" {
    "${file name}: ${line number}: expected non-terminal '${class name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"class name" : "CStringP" $[
	    write_cstring (ostream, closure->class_name);
	]$
    }
};

## Prefix section errors:

error "c unknown prefix" {
    "${file name}: ${line number}: unknown prefix type '${prefix}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"prefix" : "NStringP" $[
	    write_nstring (ostream, closure->prefix);
	]$
    }
};

## Mapping section errors:

error "c unknown identifier" {
    "${file name}: ${line number}: unknown identifier '${identifier name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"identifier name" : "NStringP" $[
	    write_nstring (ostream, closure->identifier_name);
	]$
    }
};

error "c remapped identifier" {
    "${file name}: ${line number}: attempt to remap identifier '${identifier name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"identifier name" : "NStringP" $[
	    write_nstring (ostream, closure->identifier_name);
	]$
    }
};

error "c illegal map" {
    "${file name}: ${line number}: cannot map identifier '${identifier name}' [it must be a rule, a basic or a type]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"identifier name" : "NStringP" $[
	    write_nstring (ostream, closure->identifier_name);
	]$
    }
};

## Type tuple errors:

error "c unknown type" {
    "${file name}: ${line number}: type '${type name}' hasn't been declared",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "NStringP" $[
	    write_nstring (ostream, closure->type_name);
	]$
    }
};

## Assignement section errors:

error "c unknown assign" {
    "${file name}: ${line number}: assignment operation defined for unknown type '${type name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "NStringP" $[
	    write_nstring (ostream, closure->type_name);
	]$
    }
};

error "c assign mult def" {
    "${file name}: ${line number}: multiple assignment operations defined for type '${type name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "NStringP" $[
	    write_nstring (ostream, closure->type_name);
	]$
    }
};

error "c assign param clash" {
    "${file name}: ${line number}: assignment operation parameter clash (or missing name) for type '${type name}' [parameter = ${parameter type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }
};

error "c assign param mismatch" {
    "${file name}: ${line number}: parameter type mismatch for assignment operation on type '${type name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"correct type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->correct_type);
	]$
    }, {
	"erroneous type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->erroneous_type);
	]$
    }
};

error "c assign result clash" {
    "${file name}: ${line number}: assignment operation result clash (or missing name) for type '${type name}' [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

error "c assign result mismatch" {
    "${file name}: ${line number}: result type mismatch for assignment operation on type '${type name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"correct type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->correct_type);
	]$
    }, {
	"erroneous type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->erroneous_type);
	]$
    }
};

error "c assign formal clash" {
    "${file name}: ${line number}: assignment operation formal clash for type '${type name}' [parameter = ${parameter type}, result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

## Parameter assignment section errors:

error "c unknown param assign" {
    "${file name}: ${line number}: parameter assignment operation defined for unknown type '${type name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "NStringP" $[
	    write_nstring (ostream, closure->type_name);
	]$
    }
};

error "c param assign mult def" {
    "${file name}: ${line number}: multiple parameter assignment operations defined for type '${type name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "NStringP" $[
	    write_nstring (ostream, closure->type_name);
	]$
    }
};

error "c param assign param clash" {
    "${file name}: ${line number}: parameter assignment operation parameter clash (or missing name) for type '${type name}' [parameter = ${parameter type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }
};

error "c param assign param mismatch" {
    "${file name}: ${line number}: parameter type mismatch for parameter assignment operation on type '${type name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"correct type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->correct_type);
	]$
    }, {
	"erroneous type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->erroneous_type);
	]$
    }
};

error "c param assign result clash" {
    "${file name}: ${line number}: parameter assignment operation result clash (or missing name) for type '${type name}' [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

error "c param assign res mismatch" {
    "${file name}: ${line number}: result type mismatch for parameter assignment operation on type '${type name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"correct type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->correct_type);
	]$
    }, {
	"erroneous type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->erroneous_type);
	]$
    }
};

error "c param assign formal clash" {
    "${file name}: ${line number}: parameter assignment operation formal clash for type '${type name}' [parameter = ${parameter type}, result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

## Result assignment section errors:

error "c unknown result assign" {
    "${file name}: ${line number}: result assignment operation defined for unknown type '${type name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "NStringP" $[
	    write_nstring (ostream, closure->type_name);
	]$
    }
};

error "c result assign mult def" {
    "${file name}: ${line number}: multiple result assignment operations defined for type '${type name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "NStringP" $[
	    write_nstring (ostream, closure->type_name);
	]$
    }
};

error "c result assign param clash" {
    "${file name}: ${line number}: result assignment operation parameter clash (or missing name) for type '${type name}' [parameter = ${parameter type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }
};

error "c res assign param mismatch" {
    "${file name}: ${line number}: parameter type mismatch for result assignment operation on type '${type name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"correct type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->correct_type);
	]$
    }, {
	"erroneous type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->erroneous_type);
	]$
    }
};

error "c result assign result clash" {
    "${file name}: ${line number}: result assignment operation result clash (or missing name) for type '${type name}' [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

error "c res assign result mismatch" {
    "${file name}: ${line number}: result type mismatch for result assignment operation on type '${type name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"correct type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->correct_type);
	]$
    }, {
	"erroneous type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->erroneous_type);
	]$
    }
};

error "c result assign formal clash" {
    "${file name}: ${line number}: result assignment operation formal clash for type '${type name}' [parameter = ${parameter type}, result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

## Action section errors:

error "c unknown action" {
    "${file name}: ${line number}: definition for unknown action '${action name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"action name" : "NStringP" $[
	    write_nstring (ostream, closure->action_name);
	]$
    }
};

error "c action mult def" {
    "${file name}: ${line number}: multiple definitions for action '${action name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"action name" : "NStringP" $[
	    write_nstring (ostream, closure->action_name);
	]$
    }
};

error "c action param clash" {
    "${file name}: ${line number}: parameter clash (or missing name) for action '${action name}' [parameter = ${parameter type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"action name" : "KeyP" $[
	    write_key (ostream, closure->action_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }
};

error "c action param mismatch" {
    "${file name}: ${line number}: parameter type mismatch for action '${action name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"action name" : "KeyP" $[
	    write_key (ostream, closure->action_name);
	]$
    }, {
	"correct type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->correct_type);
	]$
    }, {
	"erroneous type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->erroneous_type);
	]$
    }
};

error "c action result clash" {
    "${file name}: ${line number}: result clash (or missing name) for action '${action name}' [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"action name" : "KeyP" $[
	    write_key (ostream, closure->action_name);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

error "c action result mismatch" {
    "${file name}: ${line number}: result type mismatch for action '${action name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"action name" : "KeyP" $[
	    write_key (ostream, closure->action_name);
	]$
    }, {
	"correct type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->correct_type);
	]$
    }, {
	"erroneous type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->erroneous_type);
	]$
    }
};

error "c action formal clash" {
    "${file name}: ${line number}: formal clash for action '${action name}' [parameter = ${parameter type}, result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"action name" : "KeyP" $[
	    write_key (ostream, closure->action_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

## Terminal section errors:

error "c unknown basic" {
    "${file name}: ${line number}: extraction operation defined for unknown terminal '${terminal name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"terminal name" : "NStringP" $[
	    write_nstring (ostream, closure->terminal_name);
	]$
    }
};

error "c basic mult def" {
    "${file name}: ${line number}: multiple extraction operations defined for terminal '${terminal name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"terminal name" : "NStringP" $[
	    write_nstring (ostream, closure->terminal_name);
	]$
    }
};

error "c basic param clash" {
    "${file name}: ${line number}: extraction operation parameter clash (or missing name) for terminal '${terminal name}' [parameter = ${parameter type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"terminal name" : "KeyP" $[
	    write_key (ostream, closure->terminal_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }
};

error "c basic param mismatch" {
    "${file name}: ${line number}: parameter type mismatch for extraction operation on terminal '${terminal name}' [${erroneous type} should be ()]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"terminal name" : "KeyP" $[
	    write_key (ostream, closure->terminal_name);
	]$
    }, {
	"erroneous type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->erroneous_type);
	]$
    }
};

error "c basic result clash" {
    "${file name}: ${line number}: extraction operation result clash (or missing name) for terminal '${terminal name}' [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"terminal name" : "KeyP" $[
	    write_key (ostream, closure->terminal_name);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

error "c basic result mismatch" {
    "${file name}: ${line number}: result type mismatch for extraction operation on terminal '${terminal name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"terminal name" : "KeyP" $[
	    write_key (ostream, closure->terminal_name);
	]$
    }, {
	"correct type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->correct_type);
	]$
    }, {
	"erroneous type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->erroneous_type);
	]$
    }
};

error "c basic formal clash" {
    "${file name}: ${line number}: extraction operation formal clash for terminal '${terminal name}' [parameter = ${parameter type}, result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"terminal name" : "KeyP" $[
	    write_key (ostream, closure->terminal_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

error "c basic has no result" {
    "${file name}: ${line number}: extraction operation defined for terminal '${terminal name}' that returns nothing",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }, {
	"terminal name" : "NStringP" $[
	    write_nstring (ostream, closure->terminal_name);
	]$
    }
};

## Parse errors:

error "c expected identifier" {
    "${file name}: ${line number}: expected identifier",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected c identifier" {
    "${file name}: ${line number}: expected C identifier",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected separator" {
    "${file name}: ${line number}: expected ','",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected open tuple" {
    "${file name}: ${line number}: expected '('",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected close tuple" {
    "${file name}: ${line number}: expected ')'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected arrow" {
    "${file name}: ${line number}: expected '->'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected terminator" {
    "${file name}: ${line number}: expected ';'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected end action" {
    "${file name}: ${line number}: expected '>'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected define" {
    "${file name}: ${line number}: expected '='",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected code" {
    "${file name}: ${line number}: expected code block",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected blt header" {
    "${file name}: ${line number}: expected '%header%'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected blt terminals" {
    "${file name}: ${line number}: expected '%terminals%'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected blt actions" {
    "${file name}: ${line number}: expected '%actions%'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected blt trailer" {
    "${file name}: ${line number}: expected '%trailer%'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};

error "c expected eof" {
    "${file name}: ${line number}: expected end of file",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = c_lexer_stream_name (c_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = c_lexer_stream_line (c_current_stream);
	]$
    }
};
