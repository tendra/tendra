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
#include "table.h"
]$;

error "rule not used" {
    "rule '${rule name}' is never used",
    {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }
};

error "basic not used" {
    "basic '${basic name}' is never used",
    {
	"basic name" : "KeyP" $[
	    write_key (ostream, closure->basic_name);
	]$
    }
};

error "action not used" {
    "action '${action name}' is never used",
    {
	"action name" : "KeyP" $[
	    write_key (ostream, closure->action_name);
	]$
    }
};

error "type not used" {
    "type '${type name}' is never used",
    {
	"type name" : "KeyP" $[
	    write_key (ostream, closure->type_name);
	]$
    }
};

error "non local not used" {
    "non local name '${non local name name}' is never used",
    {
	"non local name name" : "KeyP" $[
	    write_key (ostream, closure->non_local_name_name);
	]$
    }
};

error "rule not defined" {
    "rule '${rule name}' is never defined",
    {
	"rule name" : "KeyP" $[
	    write_key (ostream, closure->rule_name);
	]$
    }
};

fatal "too many terminals" {
    "too many terminals in grammar"
};
