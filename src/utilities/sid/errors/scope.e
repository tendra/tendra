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
#include "key.h"
#include "parser.h"
]$;

error "shadows non local" {
    "${file name}: ${line number}: the name '${name name}' shadows the non local name '${non local name name}' in rule '${rule name}'",
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
	"non local name name" : "KeyP" $[
	    write_key (ostream, closure->non_local_name_name);
	]$
    }, {
	"production" : "RuleP" $[
	    write_rule (ostream, closure->production);
	]$
    }, {
	"rule name" : "RuleP" $[
	    write_key (ostream, entry_key (rule_entry (closure->production)));
	]$ $[]$
    }
};

error "shadows global" {
    "${file name}: ${line number}: the name '${name name}' shadows a global name in rule '${rule name}'",
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
	"production" : "RuleP" $[
	    write_rule (ostream, closure->production);
	]$
    }, {
	"rule name" : "RuleP" $[
	    write_key (ostream, entry_key (rule_entry (closure->production)));
	]$ $[]$
    }
};
