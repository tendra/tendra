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


fatal "too many factorisations" {
    "too many productions (${number productions}) created during factorisation",
    {
	"number productions" : "unsigned" $[
	    write_unsigned (ostream, closure->number_productions);
	]$
    }
};

error "factor handler mismatch" {
    "the rule '${inner rule name}' cannot be expanded into '${outer rule name}' as the exception handlers don't match",
    {
	"inner rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->inner_rule_name);

	    write_key (ostream, entry_key (entry));
	]$
    }, {
	"outer rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->outer_rule_name);

	    write_key (ostream, entry_key (entry));
	]$
    }, {
	"inner production" : "RuleP" $[
	    write_rule (ostream, closure->inner_rule_name);
	]$ $[]$
    }, {
	"outer production" : "RuleP" $[
	    write_rule (ostream, closure->outer_rule_name);
	]$ $[]$
    }
};

error "factor nl entry" {
    "the rule '${inner rule name}' cannot be expanded into '${outer rule name}' as it contains non local name definitions",
    {
	"inner rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->inner_rule_name);

	    write_key (ostream, entry_key (entry));
	]$
    }, {
	"outer rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->outer_rule_name);

	    write_key (ostream, entry_key (entry));
	]$
    }, {
	"inner production" : "RuleP" $[
	    write_rule (ostream, closure->inner_rule_name);
	]$ $[]$
    }, {
	"outer production" : "RuleP" $[
	    write_rule (ostream, closure->outer_rule_name);
	]$ $[]$
    }
};
