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
#include "action.h"
#include "basic.h"
#include "dstring.h"
#include "entry.h"
#include "name.h"
#include "parser.h"
#include "rule.h"
#include "table.h"
#include "type.h"
#include "types.h"
]$;

###############################################################################
## These errors are generated from the SID parser itself.  They need doing
## properly later on.
###############################################################################

fatal "expected basic" {
    "${file name}: ${line number}: expected terminal '${class name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"class name" : "CStringP" $[
	    write_cstring (ostream, closure->class_name);
	]$
    }
};

fatal "expected non-terminal" {
    "${file name}: ${line number}: expected non-terminal '${class name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"class name" : "CStringP" $[
	    write_cstring (ostream, closure->class_name);
	]$
    }
};

###############################################################################
## These errors are generated whilst parsing the grammar.
###############################################################################

## Duplicate identifier errors:

error "duplicate action" {
    "${file name}: ${line number}: identifier '${identifier name}' redeclared as action",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"identifier name" : "NStringP" $[
	    write_nstring (ostream, closure->identifier_name);
	]$
    }
};

error "duplicate basic" {
    "${file name}: ${line number}: identifier '${identifier name}' redeclared as terminal",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"identifier name" : "NStringP" $[
	    write_nstring (ostream, closure->identifier_name);
	]$
    }
};

error "duplicate rule" {
    "${file name}: ${line number}: identifier '${identifier name}' redeclared as rule",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"identifier name" : "NStringP" $[
	    write_nstring (ostream, closure->identifier_name);
	]$
    }
};

error "duplicate type" {
    "${file name}: ${line number}: identifier '${identifier name}' redeclared as type",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"identifier name" : "NStringP" $[
	    write_nstring (ostream, closure->identifier_name);
	]$
    }
};

error "duplicate non local" {
    "${file name}: ${line number}: identifier '${identifier name}' redeclared as non local",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"identifier name" : "NStringP" $[
	    write_nstring (ostream, closure->identifier_name);
	]$
    }
};

## Unknown identifier errors:

error "unknown action" {
    "${file name}: ${line number}: action '${action name}' hasn't been declared",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"action name" : "NStringP" $[
	    write_nstring (ostream, closure->action_name);
	]$
    }
};

error "unknown rule" {
    "${file name}: ${line number}: rule '${rule name}' hasn't been declared or defined",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "NStringP" $[
	    write_nstring (ostream, closure->rule_name);
	]$
    }
};

error "unknown type" {
    "${file name}: ${line number}: type '${type name}' hasn't been declared",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"type name" : "NStringP" $[
	    write_nstring (ostream, closure->type_name);
	]$
    }
};

error "unknown rule or basic" {
    "${file name}: ${line number}: identifier '${identifier name}' hasn't been declared or defined",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"identifier name" : "NStringP" $[
	    write_nstring (ostream, closure->identifier_name);
	]$
    }
};

## Result type mismatch errors:

error "identity mismatch" {
    "${file name}: ${line number}: type mismatch for identity [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "initialiser result mismatch" {
    "${file name}: ${line number}: result type mismatch for initialiser of non local name '${name name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"name name" : "KeyP" $[
	    write_key (ostream, closure->name_name);
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

error "action result call mismatch" {
    "${file name}: ${line number}: result type mismatch for invocation of action '${action name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "basic result call mismatch" {
    "${file name}: ${line number}: result type mismatch for invocation of terminal '${terminal name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "rule result call mismatch" {
    "${file name}: ${line number}: result type mismatch for invocation of rule '${rule name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
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

## Parameter type mismatch errors:

error "initialiser param mismatch" {
    "${file name}: ${line number}: parameter type mismatch for initialiser of non local name '${name name}' [${erroneous type} should be ${correct type}, ${correct ref type} or ()]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"name name" : "KeyP" $[
	    write_key (ostream, closure->name_name);
	]$
    }, {
	"correct type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->correct_type);
	]$
    }, {
	"correct ref type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->correct_ref_type);
	]$
    }, {
	"erroneous type" : "TypeTupleP" $[
	    write_type_types (ostream, closure->erroneous_type);
	]$
    }
};

error "action param call mismatch" {
    "${file name}: ${line number}: parameter type mismatch for invocation of action '${action name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "basic param call mismatch" {
    "${file name}: ${line number}: parameter type mismatch for invocation of terminal '${terminal name}' [${erroneous type} should be ()])",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "basic param mismatch" {
    "${file name}: ${line number}: parameter type mismatch for declaration of terminal '${terminal name}' [${erroneous type} should be ()])",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "rule param call mismatch" {
    "${file name}: ${line number}: parameter type mismatch for invocation of rule '${rule name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
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

## Other mismatches:

error "rule param mismatch" {
    "${file name}: ${line number}: parameter type mismatch for production '${rule name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
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

error "rule result mismatch" {
    "${file name}: ${line number}: result type mismatch for production '${rule name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
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

error "action param mismatch" {
    "${file name}: ${line number}: parameter type mismatch for action '${action name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "action result mismatch" {
    "${file name}: ${line number}: result type mismatch for action '${action name}' [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "alt result mismatch" {
    "${file name}: ${line number}: result formals are not defined in alternative ${alternative} of production '${rule name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }, {
	"alternative" : "unsigned" $[
	    write_unsigned (ostream, closure->alternative);
	]$
    }
};

error "handler result mismatch" {
    "${file name}: ${line number}: result formals are not defined in exception handler alternative of production '${rule name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }
};

## Predicate related errors:

error "multi predicate return" {
    "${file name}: ${line number}: result contains more than one predicate result symbol",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "predicate type" {
    "${file name}: ${line number}: predicate type mismatch [${erroneous type} should be ${correct type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"correct type" : "EntryP" $[
	    write_key (ostream, entry_key (closure->correct_type));
	]$
    }, {
	"erroneous type" : "EntryP" $[
	    write_key (ostream, entry_key (closure->erroneous_type));
	]$
    }
};

error "predicate" {
    "${file name}: ${line number}: predicate result symbol used in result of something other than an action",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

## Miscellaneous errors:

error "undefined assignment" {
    "${file name}: ${line number}: assignment to undefined name '${name name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"name name" : "NStringP" $[
	    write_nstring (ostream, closure->name_name);
	]$
    }
};

error "rule already defined" {
    "${file name}: ${line number}: production '${rule name}' is already defined",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }
};

error "rule formal clash" {
    "${file name}: ${line number}: parameter and result names are not disjoint for production '${rule name}' [parameter = ${parameter type}, result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
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

error "rule param clash"  {
    "${file name}: ${line number}: parameter names are not disjoint (or are missing) for production '${rule name}' [parameter = ${parameter type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }
};

error "rule result clash"  {
    "${file name}: ${line number}: result names are not disjoint (or are missing) for production '${rule name}' [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

error "identity result clash"  {
    "${file name}: ${line number}: result names are not disjoint for identity [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

error "action result call clash"  {
    "${file name}: ${line number}: result names are not disjoint for invocation of action '${action name}' [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "basic result call clash"  {
    "${file name}: ${line number}: result names are not disjoint for invocation of terminal '${terminal name}' [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "rule result call clash"  {
    "${file name}: ${line number}: result names are not disjoint for invocation of rule '${rule name}' [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

error "undefined name"  {
    "${file name}: ${line number}: undefined parameter name '${identifier name}' in alternative ${alternative} of production '${rule name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"identifier name" : "KeyP" $[
	    write_key (ostream, closure->identifier_name);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }, {
	"alternative" : "unsigned" $[
	    write_unsigned (ostream, closure->alternative);
	]$
    }
};

error "redefined name"  {
    "${file name}: ${line number}: redefined name '${identifier name}' in alternative ${alternative} of production '${rule name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"identifier name" : "KeyP" $[
	    write_key (ostream, closure->identifier_name);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }, {
	"alternative" : "unsigned" $[
	    write_unsigned (ostream, closure->alternative);
	]$
    }
};

error "multiple empty alts" {
    "${file name}: ${line number}: production '${rule name}' has multiple empty alternatives",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }
};

fatal "too many alternatives" {
    "${file name}: ${line number}: too many alternatives in grammar",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "mult entry" {
    "${file name}: ${line number}: rule '${rule name}' occurs in the entry list more than once",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }
};

error "rule param has names" {
    "${file name}: ${line number}: parameter of declaration of rule '${rule name}' has names [parameter = ${parameter type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }
};

error "rule result has names" {
    "${file name}: ${line number}: result of declaration of rule '${rule name}' has names [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

error "rule result has refs" {
    "${file name}: ${line number}: result of declaration or definition of rule '${rule name}' has references [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }, {
	"result type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->result_type, FALSE);
	]$
    }
};

error "action param has names" {
    "${file name}: ${line number}: parameter of declaration of action '${action name}' has names [parameter = ${parameter type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "action result has names" {
    "${file name}: ${line number}: result of declaration of action '${action name}' has names [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "action result has refs" {
    "${file name}: ${line number}: result of declaration of action '${action name}' has references [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "basic param has names" {
    "${file name}: ${line number}: parameter of declaration of terminal '${terminal name}' has names [parameter = ${parameter type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "basic result has names" {
    "${file name}: ${line number}: result of declaration of terminal '${terminal name}' has names [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "basic result has refs" {
    "${file name}: ${line number}: result of declaration of terminal '${terminal name}' has references [result = ${result type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
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

error "identity param has refs" {
    "${file name}: ${line number}: cannot take address of identity parameters in alternative ${alternative} of production '${rule name}' [parameter = ${parameter type}]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"parameter type" : "TypeTupleP" $[
	    write_type_names (ostream, closure->parameter_type, FALSE);
	]$
    }, {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }, {
	"alternative" : "unsigned" $[
	    write_unsigned (ostream, closure->alternative);
	]$
    }
};

error "ignored basic call" {
    "${file name}: ${line number}: invocation of ignored terminal '${terminal name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"terminal name" : "NStringP" $[
	    write_nstring (ostream, closure->terminal_name);
	]$
    }
};

error "ambiguous call" {
    "${file name}: ${line number}: identifier '${identifier name}' used in ambiguous context [may be name, rule or terminal]",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"identifier name" : "NStringP" $[
	    write_nstring (ostream, closure->identifier_name);
	]$
    }
};

error "global scope non local" {
    "${file name}: ${line number}: definition of non local name '${name name}' at global scope",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }, {
	"name name" : "NStringP" $[
	    write_nstring (ostream, closure->name_name);
	]$
    }
};

## Parse errors:

error "expected typemark" {
    "${file name}: ${line number}: expected ':'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected identifier" {
    "${file name}: ${line number}: expected identifier",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected tuple defn" {
    "${file name}: ${line number}: expected identifier or ':'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected terminal decn" {
    "${file name}: ${line number}: expected identifier or '!'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected separator" {
    "${file name}: ${line number}: expected ','",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected open tuple" {
    "${file name}: ${line number}: expected '('",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected close tuple" {
    "${file name}: ${line number}: expected ')'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected arrow" {
    "${file name}: ${line number}: expected '->'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected terminator" {
    "${file name}: ${line number}: expected ';'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected lhs name" {
    "${file name}: ${line number}: expected identifier, '?' or '!'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected rhs name" {
    "${file name}: ${line number}: expected identifier or '&'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected begin action" {
    "${file name}: ${line number}: expected '<'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected end action" {
    "${file name}: ${line number}: expected '>'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected end scope" {
    "${file name}: ${line number}: expected ']'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected tuple or term" {
    "${file name}: ${line number}: expected tuple or ';'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected item rhs" {
    "${file name}: ${line number}: expected item right hand side",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected define" {
    "${file name}: ${line number}: expected '='",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected tuple def or term" {
    "${file name}: ${line number}: expected tuple, '=' or ';'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected begin rule" {
    "${file name}: ${line number}: expected '{'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected end rule" {
    "${file name}: ${line number}: expected '}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected item" {
    "${file name}: ${line number}: expected item",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected alternative" {
    "${file name}: ${line number}: expected alternative",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected other defn" {
    "${file name}: ${line number}: expected rule declaration or rule or non local name definition",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected production defn" {
    "${file name}: ${line number}: expected rule declaration or definition, or action declaration",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected blt types" {
    "${file name}: ${line number}: expected '%types%'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected blt terminals" {
    "${file name}: ${line number}: expected '%terminals%'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected blt productions" {
    "${file name}: ${line number}: expected '%productions%'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected blt entry" {
    "${file name}: ${line number}: expected '%entry%'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected eof" {
    "${file name}: ${line number}: expected end of file",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};

error "expected terminator or define" {
    "${file name}: ${line number}: expected ';' or '='",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = lexer_stream_name (sid_current_stream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = lexer_stream_line (sid_current_stream);
	]$
    }
};
