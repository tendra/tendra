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
#include "rule.h"
]$;

error "cannot compute first set" {
    "cannot compute first set for production\n${production}",
    {
	"production" : "RuleP" $[
	    write_rule (ostream, closure->production);
	]$
    }, {
	"rule name" : "RuleP" $[
	    write_key (ostream, entry_key (rule_entry (closure->production)));
	]$ $[]$
    }
};

error "see to predicate" {
    "can see through to predicate '${predicate}' in production\n${production}",
    {
	"predicate" : "KeyP" $[
	    write_key (ostream, closure->predicate);
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

error "see to rule predicate" {
    "can see through to predicates in rule '${inner rule name}' in production\n${outer production}",
    {
	"inner production" : "RuleP" $[
	    write_rule (ostream, closure->inner_production);
	]$
    }, {
	"inner rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->inner_production);

	    write_key (ostream, entry_key (entry));
	]$ $[]$
    }, {
	"outer production" : "RuleP" $[
	    write_rule (ostream, closure->outer_production);
	]$
    }, {
	"outer rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->outer_production);

	    write_key (ostream, entry_key (entry));
	]$ $[]$
    }
};

error "redundant see through alt" {
    "the rule '${rule name}' has all terminals in its first set and has a redundant see through alternative",
    {
	"production" : "RuleP" $[
	    write_rule (ostream, closure->production);
	]$
    }, {
	"rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->production);

	    write_key (ostream, entry_key (entry));
	]$ $[]$
    }
};
