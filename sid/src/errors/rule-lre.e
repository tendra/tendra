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

error "left recursion type mismatch" {
    "the parameter or result types of the left recursive calls in the following productions do not match:\n${productions}",
    {
	"productions" : "RuleP" $[
	    RuleP rule = closure->productions;

	    for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		write_newline (ostream);
		write_rule (ostream, rule);
	    }
	]$
    }, {
	"rule names" : "RuleP" $[
	    RuleP    rule = closure->productions;
	    CStringP sep  = "";

	    for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		RuleP next = rule_get_next_in_reverse_dfs (rule);

		write_cstring (ostream, sep);
		write_char (ostream, '\'');
		write_key (ostream, entry_key (rule_entry (rule)));
		write_char (ostream, '\'');
		if (next != NIL (RuleP)) {
		    if (rule_get_next_in_reverse_dfs (next)) {
			sep = ", ";
		    } else {
			sep = " & ";
		    }
		}
	    }
	]$ $[]$
    }
};

error "left rec handler mismatch" {
    "the exception handlers in the left recursion involving the following productions do not match:\n${productions}",
    {
	"productions" : "RuleP" $[
	    RuleP rule = closure->productions;

	    for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		write_newline (ostream);
		write_rule (ostream, rule);
	    }
	]$
    }, {
	"rule names" : "RuleP" $[
	    RuleP    rule = closure->productions;
	    CStringP sep  = "";

	    for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		RuleP next = rule_get_next_in_reverse_dfs (rule);

		write_cstring (ostream, sep);
		write_char (ostream, '\'');
		write_key (ostream, entry_key (rule_entry (rule)));
		write_char (ostream, '\'');
		if (next != NIL (RuleP)) {
		    if (rule_get_next_in_reverse_dfs (next)) {
			sep = ", ";
		    } else {
			sep = " & ";
		    }
		}
	    }
	]$ $[]$
    }
};

error "left recursion name mismatch" {
    "the argument names of the left recursive calls in the following productions do not match:\n${productions}",
    {
	"productions" : "RuleP" $[
	    RuleP rule = closure->productions;

	    for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		write_newline (ostream);
		write_rule (ostream, rule);
	    }
	]$
    }, {
	"rule names" : "RuleP" $[
	    RuleP    rule = closure->productions;
	    CStringP sep  = "";

	    for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		RuleP next = rule_get_next_in_reverse_dfs (rule);

		write_cstring (ostream, sep);
		write_char (ostream, '\'');
		write_key (ostream, entry_key (rule_entry (rule)));
		write_char (ostream, '\'');
		if (next != NIL (RuleP)) {
		    if (rule_get_next_in_reverse_dfs (next)) {
			sep = ", ";
		    } else {
			sep = " & ";
		    }
		}
	    }
	]$ $[]$
    }
};

error "out of scope non local" {
    "a non local name in the rule '${using rule name}' is not in scope in the rule '${out of scope rule name}' in the left recursive cycle involving the following productions:\n${productions}",
    {
	"using production" : "RuleP" $[
	    write_rule (ostream, closure->using_production);
	]$
    }, {
	"using rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->using_production);

	    write_key (ostream, entry_key (entry));
	]$ $[]$
    }, {
	"out of scope production" : "RuleP" $[
	    write_rule (ostream, closure->out_of_scope_production);
	]$
    }, {
	"out of scope rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->out_of_scope_production);

	    write_key (ostream, entry_key (entry));
	]$ $[]$
    }, {
	"productions" : "RuleP" $[
	    RuleP rule = closure->productions;

	    for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		write_newline (ostream);
		write_rule (ostream, rule);
	    }
	]$
    }, {
	"rule names" : "RuleP" $[
	    RuleP    rule = closure->productions;
	    CStringP sep  = "";

	    for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		RuleP next = rule_get_next_in_reverse_dfs (rule);

		write_cstring (ostream, sep);
		write_char (ostream, '\'');
		write_key (ostream, entry_key (rule_entry (rule)));
		write_char (ostream, '\'');
		if (next != NIL (RuleP)) {
		    if (rule_get_next_in_reverse_dfs (next)) {
			sep = ", ";
		    } else {
			sep = " & ";
		    }
		}
	    }
	]$ $[]$
    }
};

error "left recursion nl entry" {
    "the rule '${rule name}' declares non local names in the left recursive cycle with more than one entry point involving the following productions:\n${productions}",
    {
	"production" : "RuleP" $[
	    write_rule (ostream, closure->production);
	]$
    }, {
	"rule name" : "RuleP" $[
	    EntryP entry = rule_entry (closure->production);

	    write_key (ostream, entry_key (entry));
	]$ $[]$
    }, {
	"productions" : "RuleP" $[
	    RuleP rule = closure->productions;

	    for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		write_newline (ostream);
		write_rule (ostream, rule);
	    }
	]$
    }, {
	"rule names" : "RuleP" $[
	    RuleP    rule = closure->productions;
	    CStringP sep  = "";

	    for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		RuleP next = rule_get_next_in_reverse_dfs (rule);

		write_cstring (ostream, sep);
		write_char (ostream, '\'');
		write_key (ostream, entry_key (rule_entry (rule)));
		write_char (ostream, '\'');
		if (next != NIL (RuleP)) {
		    if (rule_get_next_in_reverse_dfs (next)) {
			sep = ", ";
		    } else {
			sep = " & ";
		    }
		}
	    }
	]$ $[]$
    }
};

error "cycle no terminator" {
    "no cycle termination for the left recursive set involving the following rules: ${rule names}",
    {
	"rule names" : "RuleP" $[
	    RuleP    rule = closure->rule_names;
	    CStringP sep  = "";

	    for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		RuleP next = rule_get_next_in_reverse_dfs (rule);

		write_cstring (ostream, sep);
		write_char (ostream, '\'');
		write_key (ostream, entry_key (rule_entry (rule)));
		write_char (ostream, '\'');
		if (next != NIL (RuleP)) {
		    if (rule_get_next_in_reverse_dfs (next)) {
			sep = ", ";
		    } else {
			sep = " & ";
		    }
		}
	    }
	]$
    }
};
