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
#include "basic.h"
#include "entry-list.h"
#include "rule.h"
]$;

error "first set collision" {
    "collision of terminal(s) ${terminal names} in rule '${rule name}'",
    {
	"rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->rule_name);

	    write_key (ostream, entry_key (entry));
	]$
    }, {
	"production" : "RuleP" $[
	    write_rule (ostream, closure->rule_name);
	]$ $[]$
    }, {
	"terminal names" : "BasicClosureP" $[
	    write_basics (ostream, closure->terminal_names);
	]$
    }
};

error "predicate collision" {
    "collision of predicate '${predicate name}' in rule '${rule name}'",
    {
	"rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->rule_name);

	    write_key (ostream, entry_key (entry));
	]$
    }, {
	"production" : "RuleP" $[
	    write_rule (ostream, closure->rule_name);
	]$ $[]$
    }, {
	"predicate name" : "KeyP" $[
	    write_key (ostream, closure->predicate_name);
	]$
    }
};

error "predicate list collision" {
    "collision of predicates ${predicate names} in rule '${rule name}'",
    {
	"rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->rule_name);

	    write_key (ostream, entry_key (entry));
	]$
    }, {
	"production" : "RuleP" $[
	    write_rule (ostream, closure->rule_name);
	]$ $[]$
    }, {
	"predicate names" : "EntryListP" $[
	    write_entry_list (ostream, closure->predicate_names);
	]$
    }
};

error "follow set collision" {
    "the terminal(s) ${terminal names} can start rule '${rule name}' which is see through, and the same terminal(s) may appear in the following situations:\n${clashes}",
    {
	"rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->rule_name);

	    write_key (ostream, entry_key (entry));
	]$
    }, {
	"production" : "RuleP" $[
	    write_rule (ostream, closure->rule_name);
	]$ $[]$
    }, {
	"terminal names" : "BasicClosureP" $[
	    write_basics (ostream, closure->terminal_names);
	]$
    }, {
	"clashes" : "ClashListP" $[
	    write_clashes (ostream, closure->clashes);
	]$
    }
};

error "predicate follow set coll" {
    "the predicate(s) ${predicate names} can start rule '${rule name}' which is see through, and the same predicate(s) may appear in the following situations:${clashes}",
    {
	"rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->rule_name);

	    write_key (ostream, entry_key (entry));
	]$
    }, {
	"production" : "RuleP" $[
	    write_rule (ostream, closure->rule_name);
	]$ $[]$
    }, {
	"predicate names" : "EntryListP" $[
	    write_entry_list (ostream, closure->predicate_names);
	]$
    }, {
	"clashes" : "ClashListP" $[
	    write_clashes (ostream, closure->clashes);
	]$
    }
};

error "multiple see through alts" {
    "the rule '${rule name}' contains more than one see through alternative",
    {
	"rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->rule_name);

	    write_key (ostream, entry_key (entry));
	]$
    }, {
	"production" : "RuleP" $[
	    write_rule (ostream, closure->rule_name);
	]$ $[]$
    }
};
