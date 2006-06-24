-- Copyright (c) 1990 Regents of the University of California.
-- All rights reserved.
--
-- This software was developed by John Self of the Arcadia project
-- at the University of California, Irvine.
--
-- Redistribution and use in source and binary forms are permitted
-- provided that the above copyright notice and this paragraph are
-- duplicated in all such forms and that any documentation,
-- advertising materials, and other materials related to such
-- distribution and use acknowledge that the software was developed
-- by the University of California, Irvine.  The name of the
-- University may not be used to endorse or promote products derived
-- from this software without specific prior written permission.
-- THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
-- IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
-- WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.

-- TITLE miscellaneous definitions
-- AUTHOR: John Self (UCI)
-- DESCRIPTION contains all global variables used in aflex.
--             also some subprograms which are commonly used.
-- NOTES The real purpose of this file is to contain all miscellaneous
--       items (functions, MACROS, variables definitions) which were at the
--       top level of flex.
-- $Header: /co/ua/self/arcadia/alex/ada/RCS/misc_defsS.a,v 1.8 90/01/04 13:39:
-- 33 self Exp Locker: self $ 

-- 02/16/98 Wolfgang Lohmann(lohmi@acm.org):
-- Changed constant CSize from 127 to Pos(Last Char) for porting to gnat

with TEXT_IO, TSTRING;
use TEXT_IO, TSTRING;

package MISC_DEFS is

-- UMASS CODES :
  Ayacc_Extension_Flag : Boolean := False;
  -- Indicates whether or not aflex generated codes will be
  -- used by Ayacc extension. Ayacc extension has more power
  -- in error recovery. True means that generated codes will
  -- be used by Ayacc extension.
-- END OF UMASS CODES.

  -- various definitions that were in parse.y
  PAT, SCNUM, EPS, HEADCNT, TRAILCNT, ANYCCL, LASTCHAR, ACTVP, RULELEN : INTEGER
    ;
  TRLCONTXT, XCLUFLG, CCLSORTED, VARLENGTH, VARIABLE_TRAIL_RULE : BOOLEAN;

  MADEANY : BOOLEAN := FALSE;  -- whether we've made the '.' character class 
  PREVIOUS_CONTINUED_ACTION : BOOLEAN; -- whether the previous rule's action wa
                                       -- s '|'

  -- maximum line length we'll have to deal with 
  MAXLINE : constant INTEGER := 1024;

  -- These typees are needed for the various allocators.
  type UNBOUNDED_INT_ARRAY is array ( INTEGER range <> ) of INTEGER;
  type INT_PTR is access UNBOUNDED_INT_ARRAY;
  type INT_STAR is access INTEGER;
  type UNBOUNDED_INT_STAR_ARRAY is array ( INTEGER range <> ) of INT_PTR;
  type INT_STAR_PTR is access UNBOUNDED_INT_STAR_ARRAY;
  type UNBOUNDED_VSTRING_ARRAY is array ( INTEGER range <> ) of VSTRING;
  type VSTRING_PTR is access UNBOUNDED_VSTRING_ARRAY;
  type BOOLEAN_ARRAY is array ( INTEGER range <> ) of BOOLEAN;
  type BOOLEAN_PTR is access BOOLEAN_ARRAY;
  type CHAR_ARRAY is array ( INTEGER range <> ) of CHARACTER;
  type CHAR_PTR is access CHAR_ARRAY;

  -- different types of states; values are useful as masks, as well, for
  -- routines like check_trailing_context()

  type STATE_ENUM is (STATE_NORMAL, STATE_TRAILING_CONTEXT);

  type UNBOUNDED_STATE_ENUM_ARRAY is array ( INTEGER range <> ) of STATE_ENUM;
  type STATE_ENUM_PTR is access UNBOUNDED_STATE_ENUM_ARRAY;

  -- different types of rules
  type RULE_ENUM is (RULE_NORMAL, RULE_VARIABLE);

  type UNBOUNDED_RULE_ENUM_ARRAY is array ( INTEGER range <> ) of RULE_ENUM;
  type RULE_ENUM_PTR is access UNBOUNDED_RULE_ENUM_ARRAY;

  type DFAACC_TYPE is
    record
      DFAACC_SET : INT_PTR;
      DFAACC_STATE : INTEGER;
    end record;

  type UNBOUNDED_DFAACC_ARRAY is array ( INTEGER range <> ) of DFAACC_TYPE;
  type DFAACC_PTR is access UNBOUNDED_DFAACC_ARRAY;

  -- maximum size of file name 

  FILENAMESIZE : constant INTEGER := 1024;

  function MIN (X, Y : in INTEGER) return INTEGER;
  function MAX (X, Y : in INTEGER) return INTEGER;

  -- special chk[] values marking the slots taking by end-of-buffer and action
  -- numbers

  EOB_POSITION : constant INTEGER := - 1;
  ACTION_POSITION : constant INTEGER := - 2;

  -- number of data items per line for -f output
  NUMDATAITEMS : constant INTEGER := 10;

  -- number of lines of data in -f output before inserting a blank line for
  -- readability.

  NUMDATALINES : constant INTEGER := 10;

  -- transition_struct_out() definitions
  TRANS_STRUCT_PRINT_LENGTH : constant INTEGER := 15;

  -- returns true if an nfa state has an epsilon out-transition slot
  -- that can be used.  This definition is currently not used.

  function FREE_EPSILON ( STATE : in INTEGER) return BOOLEAN;

  -- returns true if an nfa state has an epsilon out-transition character
  -- and both slots are free

  function SUPER_FREE_EPSILON (STATE : in INTEGER) return BOOLEAN;

  -- maximum number of NFA states that can comprise a DFA state.  It's real
  -- big because if there's a lot of rules, the initial state will have a
  -- huge epsilon closure.

  INITIAL_MAX_DFA_SIZE : constant INTEGER := 750;
  MAX_DFA_SIZE_INCREMENT : constant INTEGER := 750;

  -- a note on the following masks.  They are used to mark accepting numbers
  -- as being special.  As such, they implicitly limit the number of accepting
  -- numbers (i.e., rules) because if there are too many rules the rule numbers
  -- will overload the mask bits.  Fortunately, this limit is \large/ (0x2000 ==
  -- 8192) so unlikely to actually cause any problems.  A check is made in
  -- new_rule() to ensure that this limit is not reached.

  -- mask to mark a trailing context accepting number
  -- #define YY_TRAILING_MASK 0x2000
  YY_TRAILING_MASK : constant INTEGER := 16#2000#;


  -- mask to mark the accepting number of the "head" of a trailing context rule
  -- #define YY_TRAILING_HEAD_MASK 0x4000
  YY_TRAILING_HEAD_MASK : constant INTEGER := 16#4000#;

  -- maximum number of rules, as outlined in the above note
  MAX_RULE : constant INTEGER := YY_TRAILING_MASK - 1;


  -- NIL must be 0.  If not, its special meaning when making equivalence classes
  -- (it marks the representative of a given e.c.) will be unidentifiable

  NIL : constant INTEGER := 0;

  JAM : constant INTEGER := - 1; -- to mark a missing DFA transition 
  NO_TRANSITION : constant INTEGER := NIL;
  UNIQUE : constant INTEGER := - 1; -- marks a symbol as an e.c. representative
  INFINITY : constant INTEGER := - 1; -- for x{5,} constructions

  -- size of input alphabet - should be size of ASCII set
  --CSIZE : constant INTEGER := 127;
  -- 98/02/21 Wolfgang Lohmann
  CSIZE : constant INTEGER := Character'Pos(Character'Last);

  INITIAL_MAX_CCLS : constant INTEGER := 100; -- max number of unique character
                                              --  classes
  MAX_CCLS_INCREMENT : constant INTEGER := 100;

  -- size of table holding members of character classes
  INITIAL_MAX_CCL_TBL_SIZE : constant INTEGER := 500;
  MAX_CCL_TBL_SIZE_INCREMENT : constant INTEGER := 250;
  INITIAL_MAX_RULES : constant INTEGER := 100;
  -- default maximum number of rules
  MAX_RULES_INCREMENT : constant INTEGER := 100;

  INITIAL_MNS : constant INTEGER := 2000; -- default maximum number of nfa stat
                                          -- es
  MNS_INCREMENT : constant INTEGER := 1000; -- amount to bump above by if it's 
                                            -- not enough

  INITIAL_MAX_DFAS : constant INTEGER := 1000; -- default maximum number of dfa
                                               --  states
  MAX_DFAS_INCREMENT : constant INTEGER := 1000;

  JAMSTATE_CONST : constant INTEGER := - 32766; -- marks a reference to the sta
                                                -- te that always jams

  -- enough so that if it's subtracted from an NFA state number, the result
  -- is guaranteed to be negative

  MARKER_DIFFERENCE : constant INTEGER := 32000;
  MAXIMUM_MNS : constant INTEGER := 31999;

  -- maximum number of nxt/chk pairs for non-templates
  INITIAL_MAX_XPAIRS : constant INTEGER := 2000;
  MAX_XPAIRS_INCREMENT : constant INTEGER := 2000;

  -- maximum number of nxt/chk pairs needed for templates
  INITIAL_MAX_TEMPLATE_XPAIRS : constant INTEGER := 2500;
  MAX_TEMPLATE_XPAIRS_INCREMENT : constant INTEGER := 2500;

  SYM_EPSILON : constant INTEGER := 0; -- to mark transitions on the symbol eps
                                       -- ilon

  INITIAL_MAX_SCS : constant INTEGER := 40; -- maximum number of start conditio
                                            -- ns
  MAX_SCS_INCREMENT : constant INTEGER := 40; -- amount to bump by if it's not 
                                              -- enough

  ONE_STACK_SIZE : constant INTEGER := 500; -- stack of states with only one ou
                                            -- t-transition
  SAME_TRANS : constant INTEGER := - 1; -- transition is the same as "default" 
                                        -- entry for state

  -- the following percentages are used to tune table compression:
  --
  -- the percentage the number of out-transitions a state must be of the
  -- number of equivalence classes in order to be considered for table
  -- compaction by using protos

  PROTO_SIZE_PERCENTAGE : constant INTEGER := 15;

  -- the percentage the number of homogeneous out-transitions of a state
  -- must be of the number of total out-transitions of the state in order
  -- that the state's transition table is first compared with a potential 
  -- template of the most common out-transition instead of with the first
  --proto in the proto queue

  CHECK_COM_PERCENTAGE : constant INTEGER := 50;

  -- the percentage the number of differences between a state's transition
  -- table and the proto it was first compared with must be of the total
  -- number of out-transitions of the state in order to keep the first
  -- proto as a good match and not search any further

  FIRST_MATCH_DIFF_PERCENTAGE : constant INTEGER := 10;

  -- the percentage the number of differences between a state's transition
  -- table and the most similar proto must be of the state's total number
  -- of out-transitions to use the proto as an acceptable close match

  ACCEPTABLE_DIFF_PERCENTAGE : constant INTEGER := 50;

  -- the percentage the number of homogeneous out-transitions of a state
  -- must be of the number of total out-transitions of the state in order
  -- to consider making a template from the state

  TEMPLATE_SAME_PERCENTAGE : constant INTEGER := 60;

  -- the percentage the number of differences between a state's transition
  -- table and the most similar proto must be of the state's total number
  -- of out-transitions to create a new proto from the state

  NEW_PROTO_DIFF_PERCENTAGE : constant INTEGER := 20;

  -- the percentage the total number of out-transitions of a state must be
  -- of the number of equivalence classes in order to consider trying to
  -- fit the transition table into "holes" inside the nxt/chk table.

  INTERIOR_FIT_PERCENTAGE : constant INTEGER := 15;

  -- size of region set aside to cache the complete transition table of
  -- protos on the proto queue to enable quick comparisons

  PROT_SAVE_SIZE : constant INTEGER := 2000;

  MSP : constant INTEGER := 50; -- maximum number of saved protos (protos on th
                                -- e proto queue)

  -- maximum number of out-transitions a state can have that we'll rummage
  -- around through the interior of the internal fast table looking for a
  -- spot for it

  MAX_XTIONS_FULL_INTERIOR_FIT : constant INTEGER := 4;

  -- maximum number of rules which will be reported as being associated
  -- with a DFA state

  MAX_ASSOC_RULES : constant INTEGER := 100;

  -- number that, if used to subscript an array, has a good chance of producing
  -- an error; should be small enough to fit into a short

  BAD_SUBSCRIPT : constant INTEGER := - 32767;

  -- Declarations for global variables.

  -- variables for symbol tables:
  -- sctbl - start-condition symbol table
  -- ndtbl - name-definition symbol table
  -- ccltab - character class text symbol table

  type HASH_ENTRY;
  type HASH_LINK is access HASH_ENTRY;
  type HASH_ENTRY is
    record
      PREV, NEXT : HASH_LINK;
      NAME, STR_VAL : VSTRING;
      INT_VAL : INTEGER;
    end record;

  type HASH_TABLE is array ( INTEGER range <> ) of HASH_LINK;

  NAME_TABLE_HASH_SIZE : constant INTEGER := 101;
  START_COND_HASH_SIZE : constant INTEGER := 101;
  CCL_HASH_SIZE : constant INTEGER := 101;

  subtype NDTBL_TYPE is HASH_TABLE (0 .. NAME_TABLE_HASH_SIZE - 1);
  NDTBL : NDTBL_TYPE;
  subtype SCTBL_TYPE is HASH_TABLE (0 .. START_COND_HASH_SIZE - 1);
  SCTBL : SCTBL_TYPE;
  subtype CCLTAB_TYPE is HASH_TABLE (0 .. CCL_HASH_SIZE);
  CCLTAB : CCLTAB_TYPE;

  -- variables for flags:
  -- printstats - if true (-v), dump statistics
  -- syntaxerror - true if a syntax error has been found
  -- eofseen - true if we've seen an eof in the input file
  -- ddebug - if true (-d), make a "debug" scanner
  -- trace - if true (-T), trace processing
  -- spprdflt - if true (-s), suppress the default rule
  -- interactive - if true (-I), generate an interactive scanner
  -- caseins - if true (-i), generate a case-insensitive scanner
  -- useecs - if true (-ce flag), use equivalence classes
  -- fulltbl - if true (-cf flag), don't compress the DFA state table
  -- usemecs - if true (-cm flag), use meta-equivalence classes
  -- gen_line_dirs - if true (i.e., no -L flag), generate #line directives
  -- performance_report - if true (i.e., -p flag), generate a report relating
  --   to scanner performance
  -- backtrack_report - if true (i.e., -b flag), generate "lex.backtrack" file
  --   listing backtracking states
  -- continued_action - true if this rule's action is to "fall through" to
  --                    the next rule's action (i.e., the '|' action)

  PRINTSTATS, DDEBUG, SPPRDFLT,
  INTERACTIVE, CASEINS, USEECS, FULLTBL, USEMECS,
  GEN_LINE_DIRS, PERFORMANCE_REPORT, BACKTRACK_REPORT,
  TRACE, EOFSEEN, CONTINUED_ACTION : BOOLEAN;

  SYNTAXERROR : BOOLEAN;

  -- variables used in the aflex input routines:
  -- datapos - characters on current output line
  -- dataline - number of contiguous lines of data in current data
  --    statement.  Used to generate readable -f output
  -- skelfile - the skeleton file
  -- yyin - input file
  -- temp_action_file - temporary file to hold actions
  -- backtrack_file - file to summarize backtracking states to
  -- infilename - name of input file
  -- linenum - current input line number

  DATAPOS, DATALINE, LINENUM : INTEGER;

  SKELFILE, YYIN, TEMP_ACTION_FILE, BACKTRACK_FILE, DEF_FILE : FILE_TYPE;
  INFILENAME : VSTRING;

  -- variables for stack of states having only one out-transition:
  -- onestate - state number
  -- onesym - transition symbol
  -- onenext - target state
  -- onedef - default base entry
  -- onesp - stack pointer

  ONESTATE, ONESYM, ONENEXT, ONEDEF : array (0 .. ONE_STACK_SIZE - 1) of INTEGER
    ;
  ONESP : INTEGER;


  -- variables for nfa machine data:
  -- current_mns - current maximum on number of NFA states
  -- num_rules - number of the last accepting state; also is number of
  --             rules created so far
  -- current_max_rules - current maximum number of rules
  -- lastnfa - last nfa state number created
  -- firstst - physically the first state of a fragment
  -- lastst - last physical state of fragment
  -- finalst - last logical state of fragment
  -- transchar - transition character
  -- trans1 - transition state
  -- trans2 - 2nd transition state for epsilons
  -- accptnum - accepting number
  -- assoc_rule - rule associated with this NFA state (or 0 if none)
  -- state_type - a STATE_xxx type identifying whether the state is part
  --              of a normal rule, the leading state in a trailing context
  --              rule (i.e., the state which marks the transition from
  --              recognizing the text-to-be-matched to the beginning of
  --              the trailing context), or a subsequent state in a trailing
  --              context rule
  -- rule_type - a RULE_xxx type identifying whether this a a ho-hum
  --             normal rule or one which has variable head & trailing
  --             context
  -- rule_linenum - line number associated with rule

  CURRENT_MNS, NUM_RULES, CURRENT_MAX_RULES, LASTNFA : INTEGER;
  FIRSTST, LASTST, FINALST, TRANSCHAR, TRANS1, TRANS2 : INT_PTR;
  ACCPTNUM, ASSOC_RULE, RULE_LINENUM : INT_PTR;
  RULE_TYPE : RULE_ENUM_PTR;
  STATE_TYPE : STATE_ENUM_PTR;

  -- global holding current type of state we're making

  CURRENT_STATE_ENUM : STATE_ENUM;

  -- true if the input rules include a rule with both variable-length head
  -- and trailing context, false otherwise

  VARIABLE_TRAILING_CONTEXT_RULES : BOOLEAN;


  -- variables for protos:
  -- numtemps - number of templates created
  -- numprots - number of protos created
  -- protprev - backlink to a more-recently used proto
  -- protnext - forward link to a less-recently used proto
  -- prottbl - base/def table entry for proto
  -- protcomst - common state of proto
  -- firstprot - number of the most recently used proto
  -- lastprot - number of the least recently used proto
  -- protsave contains the entire state array for protos

  NUMTEMPS, NUMPROTS, FIRSTPROT, LASTPROT : INTEGER;
  PROTPREV, PROTNEXT, PROTTBL, PROTCOMST : array (0 .. MSP - 1) of INTEGER;
  PROTSAVE : array (0 .. PROT_SAVE_SIZE - 1) of INTEGER;


  -- variables for managing equivalence classes:
  -- numecs - number of equivalence classes
  -- nextecm - forward link of Equivalence Class members
  -- ecgroup - class number or backward link of EC members
  -- nummecs - number of meta-equivalence classes (used to compress
  --   templates)
  -- tecfwd - forward link of meta-equivalence classes members
  -- * tecbck - backward link of MEC's

  NUMECS, NUMMECS : INTEGER;
  subtype C_SIZE_ARRAY is UNBOUNDED_INT_ARRAY (0 .. CSIZE);
  type C_SIZE_BOOL_ARRAY is array (0 .. CSIZE) of BOOLEAN;
  NEXTECM, ECGROUP, TECFWD, TECBCK : C_SIZE_ARRAY;


  -- variables for start conditions:
  -- lastsc - last start condition created
  -- current_max_scs - current limit on number of start conditions
  -- scset - set of rules active in start condition
  -- scbol - set of rules active only at the beginning of line in a s.c.
  -- scxclu - true if start condition is exclusive
  -- sceof - true if start condition has EOF rule
  -- scname - start condition name
  -- actvsc - stack of active start conditions for the current rule

  LASTSC, CURRENT_MAX_SCS : INTEGER;
  SCSET, SCBOL : INT_PTR;
  SCXCLU, SCEOF : BOOLEAN_PTR;
  ACTVSC : INT_PTR;
  SCNAME : VSTRING_PTR;


  -- variables for dfa machine data:
  -- current_max_dfa_size - current maximum number of NFA states in DFA
  -- current_max_xpairs - current maximum number of non-template xtion pairs
  -- current_max_template_xpairs - current maximum number of template pairs
  -- current_max_dfas - current maximum number DFA states
  -- lastdfa - last dfa state number created
  -- nxt - state to enter upon reading character
  -- chk - check value to see if "nxt" applies
  -- tnxt - internal nxt table for templates
  -- base - offset into "nxt" for given state
  -- def - where to go if "chk" disallows "nxt" entry
  -- tblend - last "nxt/chk" table entry being used
  -- firstfree - first empty entry in "nxt/chk" table
  -- dss - nfa state set for each dfa
  -- dfasiz - size of nfa state set for each dfa
  -- dfaacc - accepting set for each dfa state (or accepting number, if
  --    -r is not given)
  -- accsiz - size of accepting set for each dfa state
  -- dhash - dfa state hash value
  -- numas - number of DFA accepting states created; note that this
  --    is not necessarily the same value as num_rules, which is the analogous
  --    value for the NFA
  -- numsnpairs - number of state/nextstate transition pairs
  -- jambase - position in base/def where the default jam table starts
  -- jamstate - state number corresponding to "jam" state
  -- end_of_buffer_state - end-of-buffer dfa state number

  CURRENT_MAX_DFA_SIZE, CURRENT_MAX_XPAIRS : INTEGER;
  CURRENT_MAX_TEMPLATE_XPAIRS, CURRENT_MAX_DFAS : INTEGER;
  LASTDFA, LASTTEMP : INTEGER;
  NXT, CHK, TNXT : INT_PTR;
  BASE, DEF , DFASIZ : INT_PTR;
  TBLEND, FIRSTFREE : INTEGER;
  DSS : INT_STAR_PTR;
  DFAACC : DFAACC_PTR;

  -- type declaration for dfaacc_type moved above

  ACCSIZ, DHASH : INT_PTR;
  END_OF_BUFFER_STATE, NUMSNPAIRS, JAMBASE, JAMSTATE, NUMAS : INTEGER;

  -- variables for ccl information:
  -- lastccl - ccl index of the last created ccl
  -- current_maxccls - current limit on the maximum number of unique ccl's
  -- cclmap - maps a ccl index to its set pointer
  -- ccllen - gives the length of a ccl
  -- cclng - true for a given ccl if the ccl is negated
  -- cclreuse - counts how many times a ccl is re-used
  -- current_max_ccl_tbl_size - current limit on number of characters needed
  --	to represent the unique ccl's
  -- ccltbl - holds the characters in each ccl - indexed by cclmap

  CURRENT_MAX_CCL_TBL_SIZE, LASTCCL, CURRENT_MAXCCLS, CCLREUSE : INTEGER;
  CCLMAP, CCLLEN, CCLNG : INT_PTR;

  CCLTBL : CHAR_PTR;


  -- variables for miscellaneous information:
  -- starttime - real-time when we started
  -- endtime - real-time when we ended
  -- nmstr - last NAME scanned by the scanner
  -- sectnum - section number currently being parsed
  -- nummt - number of empty nxt/chk table entries
  -- hshcol - number of hash collisions detected by snstods
  -- dfaeql - number of times a newly created dfa was equal to an old one
  -- numeps - number of epsilon NFA states created
  -- eps2 - number of epsilon states which have 2 out-transitions
  -- num_reallocs - number of times it was necessary to realloc() a group
  --		  of arrays
  -- tmpuses - number of DFA states that chain to templates
  -- totnst - total number of NFA states used to make DFA states
  -- peakpairs - peak number of transition pairs we had to store internally
  -- numuniq - number of unique transitions
  -- numdup - number of duplicate transitions
  -- hshsave - number of hash collisions saved by checking number of states
  -- num_backtracking - number of DFA states requiring back-tracking
  -- bol_needed - whether scanner needs beginning-of-line recognition

  NMSTR : VSTRING;
  SECTNUM, NUMMT, HSHCOL, DFAEQL, NUMEPS, EPS2, NUM_REALLOCS : INTEGER;
  TMPUSES, TOTNST, PEAKPAIRS, NUMUNIQ, NUMDUP, HSHSAVE : INTEGER;
  NUM_BACKTRACKING : INTEGER;
  BOL_NEEDED : BOOLEAN;

  function ALLOCATE_INTEGER_ARRAY (SIZE : in INTEGER) return INT_PTR;

  function ALLOCATE_INT_PTR_ARRAY (SIZE : in INTEGER) return INT_STAR_PTR;



  function ALLOCATE_VSTRING_ARRAY (SIZE : in INTEGER) return VSTRING_PTR;

  function ALLOCATE_DFAACC_UNION (SIZE : in INTEGER) return DFAACC_PTR;

  function  ALLOCATE_CHARACTER_ARRAY (SIZE : in INTEGER) return CHAR_PTR;

  function ALLOCATE_RULE_ENUM_ARRAY (SIZE : in INTEGER) return RULE_ENUM_PTR;

  function ALLOCATE_STATE_ENUM_ARRAY (SIZE : in INTEGER) return STATE_ENUM_PTR;

  function ALLOCATE_BOOLEAN_ARRAY (SIZE : in INTEGER) return BOOLEAN_PTR;

  procedure REALLOCATE_INTEGER_ARRAY (ARR : in out INT_PTR;
       SIZE : in INTEGER);

  procedure REALLOCATE_INT_PTR_ARRAY (ARR : in out INT_STAR_PTR;
       SIZE : in INTEGER);

  procedure REALLOCATE_VSTRING_ARRAY (ARR : in out VSTRING_PTR;
        SIZE : in INTEGER);

  procedure REALLOCATE_DFAACC_UNION (ARR : in out DFAACC_PTR;
      SIZE : in INTEGER);

  procedure REALLOCATE_CHARACTER_ARRAY (ARR : in out CHAR_PTR;
       SIZE : in INTEGER);

  procedure REALLOCATE_RULE_ENUM_ARRAY (ARR : in out RULE_ENUM_PTR;
       SIZE : in INTEGER);

  procedure REALLOCATE_STATE_ENUM_ARRAY (ARR : in out STATE_ENUM_PTR;
       SIZE : in INTEGER);

  procedure REALLOCATE_BOOLEAN_ARRAY (ARR : in out BOOLEAN_PTR;
       SIZE : in INTEGER);

end MISC_DEFS;
