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

-- TITLE DFA construction routines
-- AUTHOR: John Self (UCI)
-- DESCRIPTION converts non-deterministic finite automatons to finite ones.
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/dfaB.a,v 1.18 90/01/12 15:19:48 self Exp Locker: self $ 

with DFA, INT_IO, MISC_DEFS, TEXT_IO, MISC, TBLCMP, CCL, EXTERNAL_FILE_MANAGER; 
with ECS, NFA, TSTRING, GEN, SKELETON_MANAGER; use MISC_DEFS, 
  EXTERNAL_FILE_MANAGER; 

package body DFA is 
  use TSTRING; 
  -- check_for_backtracking - check a DFA state for backtracking
  --
  -- ds is the number of the state to check and state[) is its out-transitions,
  -- indexed by equivalence class, and state_rules[) is the set of rules
  -- associated with this state

  DID_STK_INIT : BOOLEAN := FALSE; 
  STK          : INT_PTR; 

  procedure CHECK_FOR_BACKTRACKING(DS    : in INTEGER; 
                                   STATE : in UNBOUNDED_INT_ARRAY) is 
    use MISC_DEFS; 
  begin
    if (DFAACC(DS).DFAACC_STATE = 0) then 

      -- state is non-accepting
      NUM_BACKTRACKING := NUM_BACKTRACKING + 1; 

      if (BACKTRACK_REPORT) then 
        TEXT_IO.PUT(BACKTRACK_FILE, "State #"); 
        INT_IO.PUT(BACKTRACK_FILE, DS, 1); 
        TEXT_IO.PUT(BACKTRACK_FILE, "is non-accepting -"); 
        TEXT_IO.NEW_LINE(BACKTRACK_FILE); 

        -- identify the state
        DUMP_ASSOCIATED_RULES(BACKTRACK_FILE, DS); 

        -- now identify it further using the out- and jam-transitions
        DUMP_TRANSITIONS(BACKTRACK_FILE, STATE); 
        TEXT_IO.NEW_LINE(BACKTRACK_FILE); 
      end if; 
    end if; 
  end CHECK_FOR_BACKTRACKING; 


  -- check_trailing_context - check to see if NFA state set constitutes
  --                          "dangerous" trailing context
  --
  -- NOTES
  --    Trailing context is "dangerous" if both the head and the trailing
  --  part are of variable size \and/ there's a DFA state which contains
  --  both an accepting state for the head part of the rule and NFA states
  --  which occur after the beginning of the trailing context.
  --  When such a rule is matched, it's impossible to tell if having been
  --  in the DFA state indicates the beginning of the trailing context
  --  or further-along scanning of the pattern.  In these cases, a warning
  --  message is issued.
  --
  --    nfa_states[1 .. num_states) is the list of NFA states in the DFA.
  --    accset[1 .. nacc) is the list of accepting numbers for the DFA state.

  procedure CHECK_TRAILING_CONTEXT(NFA_STATES : in INT_PTR; 
                                   NUM_STATES : in INTEGER; 
                                   ACCSET     : in INT_PTR; 
                                   NACC       : in INTEGER) is 
    NS, AR              : INTEGER; 
    STATE_VAR, TYPE_VAR : STATE_ENUM; 

    use MISC_DEFS, MISC, TEXT_IO; 
  begin
    for I in 1 .. NUM_STATES loop
      NS := NFA_STATES(I); 
      TYPE_VAR := STATE_TYPE(NS); 
      AR := ASSOC_RULE(NS); 

      if ((TYPE_VAR = STATE_NORMAL) or (RULE_TYPE(AR) /= RULE_VARIABLE)) then 
        null; 

      -- do nothing
      else 
        if (TYPE_VAR = STATE_TRAILING_CONTEXT) then 

          -- potential trouble.  Scan set of accepting numbers for
          -- the one marking the end of the "head".  We assume that
          -- this looping will be fairly cheap since it's rare that
          -- an accepting number set is large.
          for J in 1 .. NACC loop
            if (CHECK_YY_TRAILING_HEAD_MASK(ACCSET(J)) /= 0) then 
              TEXT_IO.PUT(STANDARD_ERROR, 
                "aflex: Dangerous trailing context in rule at line "); 
              INT_IO.PUT(STANDARD_ERROR, RULE_LINENUM(AR), 1); 
              TEXT_IO.NEW_LINE(STANDARD_ERROR); 
              return; 
            end if; 
          end loop; 
        end if; 
      end if; 
    end loop; 
  end CHECK_TRAILING_CONTEXT; 


  -- dump_associated_rules - list the rules associated with a DFA state
  --
  -- goes through the set of NFA states associated with the DFA and
  -- extracts the first MAX_ASSOC_RULES unique rules, sorts them,
  -- and writes a report to the given file

  procedure DUMP_ASSOCIATED_RULES(F  : in FILE_TYPE; 
                                  DS : in INTEGER) is 
    J                    : INTEGER; 
    NUM_ASSOCIATED_RULES : INTEGER := 0; 
    RULE_SET             : INT_PTR; 
    SIZE, RULE_NUM       : INTEGER; 
  begin
    RULE_SET := new UNBOUNDED_INT_ARRAY(0 .. MAX_ASSOC_RULES + 1); 
    SIZE := DFASIZ(DS); 

    for I in 1 .. SIZE loop
      RULE_NUM := RULE_LINENUM(ASSOC_RULE(DSS(DS)(I))); 

      J := 1; 
      while (J <= NUM_ASSOCIATED_RULES) loop
        if (RULE_NUM = RULE_SET(J)) then 
          exit; 
        end if; 
        J := J + 1; 
      end loop; 
      if (J > NUM_ASSOCIATED_RULES) then 

        --new rule
        if (NUM_ASSOCIATED_RULES < MAX_ASSOC_RULES) then 
          NUM_ASSOCIATED_RULES := NUM_ASSOCIATED_RULES + 1; 
          RULE_SET(NUM_ASSOCIATED_RULES) := RULE_NUM; 
        end if; 
      end if; 
    end loop; 

    MISC.BUBBLE(RULE_SET, NUM_ASSOCIATED_RULES); 

    TEXT_IO.PUT(F, " associated rules:"); 

    for I in 1 .. NUM_ASSOCIATED_RULES loop
      if (I mod 8 = 1) then 
        TEXT_IO.NEW_LINE(F); 
      end if; 

      TEXT_IO.PUT(F, ASCII.HT); 
      INT_IO.PUT(F, RULE_SET(I), 1); 
    end loop; 

    TEXT_IO.NEW_LINE(F); 
  exception
    when STORAGE_ERROR => 
      MISC.AFLEXFATAL("dynamic memory failure in dump_associated_rules()"); 
  end DUMP_ASSOCIATED_RULES; 


  -- dump_transitions - list the transitions associated with a DFA state
  --
  -- goes through the set of out-transitions and lists them in human-readable
  -- form (i.e., not as equivalence classes); also lists jam transitions
  -- (i.e., all those which are not out-transitions, plus EOF).  The dump
  -- is done to the given file.

  procedure DUMP_TRANSITIONS(F     : in FILE_TYPE; 
                             STATE : in UNBOUNDED_INT_ARRAY) is 
    EC           : INTEGER; 
    OUT_CHAR_SET : C_SIZE_BOOL_ARRAY; 
  begin
    for I in 1 .. CSIZE loop
      EC := ECGROUP(I); 

      if (EC < 0) then 
        EC :=  -EC; 
      end if; 

      OUT_CHAR_SET(I) := (STATE(EC) /= 0); 
    end loop; 

    TEXT_IO.PUT(F, " out-transitions: "); 

    CCL.LIST_CHARACTER_SET(F, OUT_CHAR_SET); 

    -- now invert the members of the set to get the jam transitions
    for I in 1 .. CSIZE loop
      OUT_CHAR_SET(I) := not OUT_CHAR_SET(I); 
    end loop; 

    TEXT_IO.NEW_LINE(F); 
    TEXT_IO.PUT(F, "jam-transitions: EOF "); 

    CCL.LIST_CHARACTER_SET(F, OUT_CHAR_SET); 

    TEXT_IO.NEW_LINE(F); 
  end DUMP_TRANSITIONS; 


  -- epsclosure - construct the epsilon closure of a set of ndfa states
  --
  -- NOTES
  --    the epsilon closure is the set of all states reachable by an arbitrary
  --  number of epsilon transitions which themselves do not have epsilon
  --  transitions going out, unioned with the set of states which have non-null
  --  accepting numbers.  t is an array of size numstates of nfa state numbers.
--  Upon return, t holds the epsilon closure and numstates is updated.  accset
  --  holds a list of the accepting numbers, and the size of accset is given
  --  by nacc.  t may be subjected to reallocation if it is not large enough
  --  to hold the epsilon closure.
  --
  --    hashval is the hash value for the dfa corresponding to the state set

  procedure EPSCLOSURE(T                  : in out INT_PTR; 
                       NS_ADDR            : in out INTEGER; 
                       ACCSET             : in out INT_PTR; 
                       NACC_ADDR, HV_ADDR : out INTEGER; 
                       RESULT             : out INT_PTR) is 
    NS, TSP                                      : INTEGER; 
    NUMSTATES, NACC, HASHVAL, TRANSSYM, NFACCNUM : INTEGER; 
    STKEND                                       : INTEGER; 
    STKPOS                                       : INTEGER; 
    procedure MARK_STATE(STATE : in INTEGER) is 
    begin
      TRANS1(STATE) := TRANS1(STATE) - MARKER_DIFFERENCE; 
    end MARK_STATE; 
    pragma INLINE(MARK_STATE); 

    function IS_MARKED(STATE : in INTEGER) return BOOLEAN is 
    begin
      return TRANS1(STATE) < 0; 
    end IS_MARKED; 
    pragma INLINE(IS_MARKED); 

    procedure UNMARK_STATE(STATE : in INTEGER) is 
    begin
      TRANS1(STATE) := TRANS1(STATE) + MARKER_DIFFERENCE; 
    end UNMARK_STATE; 
    pragma INLINE(UNMARK_STATE); 


    procedure CHECK_ACCEPT(STATE : in INTEGER) is 
    begin
      NFACCNUM := ACCPTNUM(STATE); 
      if (NFACCNUM /= NIL) then 
        NACC := NACC + 1; 
        ACCSET(NACC) := NFACCNUM; 
      end if; 
    end CHECK_ACCEPT; 
    pragma INLINE(CHECK_ACCEPT); 

    procedure DO_REALLOCATION is 
    begin
      CURRENT_MAX_DFA_SIZE := CURRENT_MAX_DFA_SIZE + MAX_DFA_SIZE_INCREMENT; 
      NUM_REALLOCS := NUM_REALLOCS + 1; 
      REALLOCATE_INTEGER_ARRAY(T, CURRENT_MAX_DFA_SIZE); 
      REALLOCATE_INTEGER_ARRAY(STK, CURRENT_MAX_DFA_SIZE); 
    end DO_REALLOCATION; 
    pragma INLINE(DO_REALLOCATION); 


    procedure PUT_ON_STACK(STATE : in INTEGER) is 
    begin
      STKEND := STKEND + 1; 
      if (STKEND >= CURRENT_MAX_DFA_SIZE) then 
        DO_REALLOCATION; 
      end if; 
      STK(STKEND) := STATE; 
      MARK_STATE(STATE); 
    end PUT_ON_STACK; 
    pragma INLINE(PUT_ON_STACK); 

    procedure ADD_STATE(STATE : in INTEGER) is 
    begin
      NUMSTATES := NUMSTATES + 1; 
      if (NUMSTATES >= CURRENT_MAX_DFA_SIZE) then 
        DO_REALLOCATION; 
      end if; 
      T(NUMSTATES) := STATE; 
      HASHVAL := HASHVAL + STATE; 
    end ADD_STATE; 
    pragma INLINE(ADD_STATE); 

    procedure STACK_STATE(STATE : in INTEGER) is 
    begin
      PUT_ON_STACK(STATE); 
      CHECK_ACCEPT(STATE); 
      if ((NFACCNUM /= NIL) or (TRANSCHAR(STATE) /= SYM_EPSILON)) then 
        ADD_STATE(STATE); 
      end if; 
    end STACK_STATE; 
    pragma INLINE(STACK_STATE); 

  begin
    NUMSTATES := NS_ADDR; 
    if (not DID_STK_INIT) then 
      STK := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_DFA_SIZE); 
      DID_STK_INIT := TRUE; 
    end if; 

    NACC := 0; 
    STKEND := 0; 
    HASHVAL := 0; 

    for NSTATE in 1 .. NUMSTATES loop
      NS := T(NSTATE); 

      -- the state could be marked if we've already pushed it onto
      -- the stack
      if (not IS_MARKED(NS)) then 
        PUT_ON_STACK(NS); 
        null; 
      end if; 

      CHECK_ACCEPT(NS); 
      HASHVAL := HASHVAL + NS; 
    end loop; 


    STKPOS := 1; 
    while (STKPOS <= STKEND) loop
      NS := STK(STKPOS); 
      TRANSSYM := TRANSCHAR(NS); 

      if (TRANSSYM = SYM_EPSILON) then 
        TSP := TRANS1(NS) + MARKER_DIFFERENCE; 

        if (TSP /= NO_TRANSITION) then 
          if (not IS_MARKED(TSP)) then 
            STACK_STATE(TSP); 
          end if; 

          TSP := TRANS2(NS); 

          if (TSP /= NO_TRANSITION) then 
            if (not IS_MARKED(TSP)) then 
              STACK_STATE(TSP); 
            end if; 
          end if; 
        end if; 
      end if; 
      STKPOS := STKPOS + 1; 
    end loop; 

    -- clear out "visit" markers
    for CHK_STKPOS in 1 .. STKEND loop
      if (IS_MARKED(STK(CHK_STKPOS))) then 
        UNMARK_STATE(STK(CHK_STKPOS)); 
      else 
        MISC.AFLEXFATAL("consistency check failed in epsclosure()"); 
      end if; 
    end loop; 

    NS_ADDR := NUMSTATES; 
    HV_ADDR := HASHVAL; 
    NACC_ADDR := NACC; 

    RESULT := T; 
  end EPSCLOSURE; 


  -- increase_max_dfas - increase the maximum number of DFAs

  procedure INCREASE_MAX_DFAS is 
  begin
    CURRENT_MAX_DFAS := CURRENT_MAX_DFAS + MAX_DFAS_INCREMENT; 

    NUM_REALLOCS := NUM_REALLOCS + 1; 

    REALLOCATE_INTEGER_ARRAY(BASE, CURRENT_MAX_DFAS); 
    REALLOCATE_INTEGER_ARRAY(DEF, CURRENT_MAX_DFAS); 
    REALLOCATE_INTEGER_ARRAY(DFASIZ, CURRENT_MAX_DFAS); 
    REALLOCATE_INTEGER_ARRAY(ACCSIZ, CURRENT_MAX_DFAS); 
    REALLOCATE_INTEGER_ARRAY(DHASH, CURRENT_MAX_DFAS); 
    REALLOCATE_INT_PTR_ARRAY(DSS, CURRENT_MAX_DFAS); 
    REALLOCATE_DFAACC_UNION(DFAACC, CURRENT_MAX_DFAS); 
  end INCREASE_MAX_DFAS; 


  -- ntod - convert an ndfa to a dfa
  --
  --  creates the dfa corresponding to the ndfa we've constructed.  the
  --  dfa starts out in state #1.

  procedure NTOD is 

    ACCSET                                             : INT_PTR; 
    DS, NACC, NEWDS                                    : INTEGER; 
    DUPLIST, TARGFREQ, TARGSTATE, STATE                : C_SIZE_ARRAY; 
    SYMLIST                                            : C_SIZE_BOOL_ARRAY; 
    HASHVAL, NUMSTATES, DSIZE                          : INTEGER; 
    NSET, DSET                                         : INT_PTR; 
    TARGPTR, TOTALTRANS, I, J, COMSTATE, COMFREQ, TARG : INTEGER; 
    NUM_START_STATES, TODO_HEAD, TODO_NEXT             : INTEGER; 
    SNSRESULT                                          : BOOLEAN; 
    FULL_TABLE_TEMP_FILE                               : FILE_TYPE; 
    BUF                                                : VSTRING; 
    NUM_NXT_STATES                                     : INTEGER; 
    use TEXT_IO; 

    -- this is so find_table_space(...) will know where to start looking in
    -- chk/nxt for unused records for space to put in the state
  begin
    ACCSET := ALLOCATE_INTEGER_ARRAY(NUM_RULES + 1); 
    NSET := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_DFA_SIZE); 

    -- the "todo" queue is represented by the head, which is the DFA
    -- state currently being processed, and the "next", which is the
    -- next DFA state number available (not in use).  We depend on the
    -- fact that snstods() returns DFA's \in increasing order/, and thus
    -- need only know the bounds of the dfas to be processed.
    TODO_HEAD := 0; 
    TODO_NEXT := 0; 

    for CNT in 0 .. CSIZE loop
      DUPLIST(CNT) := NIL; 
      SYMLIST(CNT) := FALSE; 
    end loop; 

    for CNT in 0 .. NUM_RULES loop
      ACCSET(CNT) := NIL; 
    end loop; 

    if (TRACE) then 
      NFA.DUMPNFA(SCSET(1)); 
      TEXT_IO.NEW_LINE(STANDARD_ERROR); 
      TEXT_IO.NEW_LINE(STANDARD_ERROR); 
      TEXT_IO.PUT(STANDARD_ERROR, "DFA Dump:"); 
      TEXT_IO.NEW_LINE(STANDARD_ERROR); 
      TEXT_IO.NEW_LINE(STANDARD_ERROR); 
    end if; 

    TBLCMP.INITTBL; 

    if (FULLTBL) then 
      GEN.DO_SECT3_OUT; 

      GEN.BODY_HEADER;

      -- output user code up to ##
      SKELETON_MANAGER.SKELOUT; 

      -- declare it "short" because it's a real long-shot that that
      -- won't be large enough
      begin -- make a temporary file to write yy_nxt array into
        CREATE(FULL_TABLE_TEMP_FILE, OUT_FILE); 
      exception
        when USE_ERROR | NAME_ERROR => 
          MISC.AFLEXFATAL("can't create temporary file"); 
      end; 

      NUM_NXT_STATES := 1; 
      TEXT_IO.PUT(FULL_TABLE_TEMP_FILE, "( "); 
      -- generate 0 entries for state #0
      for CNT in 0 .. NUMECS loop
        MISC.MK2DATA(FULL_TABLE_TEMP_FILE, 0); 
      end loop; 

      TEXT_IO.PUT(FULL_TABLE_TEMP_FILE, " )"); 
      -- force extra blank line next dataflush()
      DATALINE := NUMDATALINES; 
    end if; 

    -- create the first states

    NUM_START_STATES := LASTSC*2; 

    for CNT in 1 .. NUM_START_STATES loop
      NUMSTATES := 1; 

      -- for each start condition, make one state for the case when
      -- we're at the beginning of the line (the '%' operator) and
      -- one for the case when we're not

      if (CNT mod 2 = 1) then 
        NSET(NUMSTATES) := SCSET((CNT/2) + 1); 
      else 
        NSET(NUMSTATES) := NFA.MKBRANCH(SCBOL(CNT/2), SCSET(CNT/2)); 
      end if; 

      DFA.EPSCLOSURE(NSET, NUMSTATES, ACCSET, NACC, HASHVAL, NSET); 

      SNSTODS(NSET, NUMSTATES, ACCSET, NACC, HASHVAL, DS, SNSRESULT); 
      if (SNSRESULT) then 
        NUMAS := NUMAS + NACC; 
        TOTNST := TOTNST + NUMSTATES; 
        TODO_NEXT := TODO_NEXT + 1; 

        if (VARIABLE_TRAILING_CONTEXT_RULES and (NACC > 0)) then 
          CHECK_TRAILING_CONTEXT(NSET, NUMSTATES, ACCSET, NACC); 
        end if; 
      end if; 
    end loop; 

    SNSTODS(NSET, 0, ACCSET, 0, 0, END_OF_BUFFER_STATE, SNSRESULT); 
    if (not SNSRESULT) then 
      MISC.AFLEXFATAL("could not create unique end-of-buffer state"); 
    end if; 
    NUMAS := NUMAS + 1; 
    NUM_START_STATES := NUM_START_STATES + 1; 
    TODO_NEXT := TODO_NEXT + 1; 

    while (TODO_HEAD < TODO_NEXT) loop
      NUM_NXT_STATES := NUM_NXT_STATES + 1; 
      TARGPTR := 0; 
      TOTALTRANS := 0; 

      for STATE_CNT in 1 .. NUMECS loop
        STATE(STATE_CNT) := 0; 
      end loop; 

      TODO_HEAD := TODO_HEAD + 1; 
      DS := TODO_HEAD; 

      DSET := DSS(DS); 
      DSIZE := DFASIZ(DS); 

      if (TRACE) then 
        TEXT_IO.PUT(STANDARD_ERROR, "state # "); 
        INT_IO.PUT(STANDARD_ERROR, DS, 1); 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, ":"); 
      end if; 

      SYMPARTITION(DSET, DSIZE, SYMLIST, DUPLIST); 

      for SYM in 1 .. NUMECS loop
        if (SYMLIST(SYM)) then 
          SYMLIST(SYM) := FALSE; 

          if (DUPLIST(SYM) = NIL) then 
          -- symbol has unique out-transitions
            NUMSTATES := SYMFOLLOWSET(DSET, DSIZE, SYM, NSET); 
            DFA.EPSCLOSURE(NSET, NUMSTATES, ACCSET, NACC, HASHVAL, NSET); 

            SNSTODS(NSET, NUMSTATES, ACCSET, NACC, HASHVAL, NEWDS, SNSRESULT); 
            if (SNSRESULT) then 
              TOTNST := TOTNST + NUMSTATES; 
              TODO_NEXT := TODO_NEXT + 1; 
              NUMAS := NUMAS + NACC; 

              if (VARIABLE_TRAILING_CONTEXT_RULES and (NACC > 0)) then 
                CHECK_TRAILING_CONTEXT(NSET, NUMSTATES, ACCSET, NACC); 
              end if; 
            end if; 

            STATE(SYM) := NEWDS; 

            if (TRACE) then 
              TEXT_IO.PUT(STANDARD_ERROR, ASCII.HT); 
              INT_IO.PUT(STANDARD_ERROR, SYM, 1); 
              TEXT_IO.PUT(STANDARD_ERROR, ASCII.HT); 
              INT_IO.PUT(STANDARD_ERROR, NEWDS, 1); 
              TEXT_IO.NEW_LINE(STANDARD_ERROR); 
            end if; 

            TARGPTR := TARGPTR + 1; 
            TARGFREQ(TARGPTR) := 1; 
            TARGSTATE(TARGPTR) := NEWDS; 
            NUMUNIQ := NUMUNIQ + 1; 
          else 
          -- sym's equivalence class has the same transitions
          -- as duplist(sym)'s equivalence class

            TARG := STATE(DUPLIST(SYM)); 
            STATE(SYM) := TARG; 
            if (TRACE) then 
              TEXT_IO.PUT(STANDARD_ERROR, ASCII.HT); 
              INT_IO.PUT(STANDARD_ERROR, SYM, 1); 
              TEXT_IO.PUT(STANDARD_ERROR, ASCII.HT); 
              INT_IO.PUT(STANDARD_ERROR, TARG, 1); 
              TEXT_IO.NEW_LINE(STANDARD_ERROR); 
            end if; 

            -- update frequency count for destination state

            I := 1; 

            while (TARGSTATE(I) /= TARG) loop
              I := I + 1; 
            end loop; 

            TARGFREQ(I) := TARGFREQ(I) + 1; 
            NUMDUP := NUMDUP + 1; 
          end if; 

          TOTALTRANS := TOTALTRANS + 1; 
          DUPLIST(SYM) := NIL; 
        end if; 
      end loop; 

      NUMSNPAIRS := NUMSNPAIRS + TOTALTRANS; 

      if (CASEINS and not USEECS) then 
        I := CHARACTER'POS('A'); 
        J := CHARACTER'POS('a'); 
        while (I < CHARACTER'POS('Z')) loop
          STATE(I) := STATE(J); 
          I := I + 1; 
          J := J + 1; 
        end loop; 
      end if; 

      if (DS > NUM_START_STATES) then 
        CHECK_FOR_BACKTRACKING(DS, STATE); 
      end if; 

      if (FULLTBL) then 
      -- supply array's 0-element
        TEXT_IO.PUT(FULL_TABLE_TEMP_FILE, ","); 
        MISC.DATAFLUSH(FULL_TABLE_TEMP_FILE); 
        TEXT_IO.PUT(FULL_TABLE_TEMP_FILE, "( "); 
        if (DS = END_OF_BUFFER_STATE) then 
          MISC.MK2DATA(FULL_TABLE_TEMP_FILE,  -END_OF_BUFFER_STATE); 
        else 
          MISC.MK2DATA(FULL_TABLE_TEMP_FILE, END_OF_BUFFER_STATE); 
        end if; 

        for CNT in 1 .. NUMECS loop
        -- jams are marked by negative of state number
          if ((STATE(CNT) /= 0)) then 
            MISC.MK2DATA(FULL_TABLE_TEMP_FILE, STATE(CNT)); 
          else 
            MISC.MK2DATA(FULL_TABLE_TEMP_FILE,  -DS); 
          end if; 
        end loop; 

        TEXT_IO.PUT(FULL_TABLE_TEMP_FILE, " )"); 
        -- force extra blank line next dataflush()
        DATALINE := NUMDATALINES; 
      else 
        if (DS = END_OF_BUFFER_STATE) then 
        -- special case this state to make sure it does what it's
        -- supposed to, i.e., jam on end-of-buffer
          TBLCMP.STACK1(DS, 0, 0, JAMSTATE_CONST); 
        else  -- normal, compressed state
        -- determine which destination state is the most common, and
        -- how many transitions to it there are
          COMFREQ := 0; 
          COMSTATE := 0; 

          for CNT in 1 .. TARGPTR loop
            if (TARGFREQ(CNT) > COMFREQ) then 
              COMFREQ := TARGFREQ(CNT); 
              COMSTATE := TARGSTATE(CNT); 
            end if; 
          end loop; 

          TBLCMP.BLDTBL(STATE, DS, TOTALTRANS, COMSTATE, COMFREQ); 
        end if; 
      end if; 
    end loop; 

    if (FULLTBL) then 
      TEXT_IO.PUT("yy_nxt : constant array(0.."); 
      INT_IO.PUT(NUM_NXT_STATES - 1, 1); 
      TEXT_IO.PUT_LINE(" , character'first..character'last) of short :="); 
      TEXT_IO.PUT_LINE("   ("); 

      RESET(FULL_TABLE_TEMP_FILE, IN_FILE); 
      while (not END_OF_FILE(FULL_TABLE_TEMP_FILE)) loop
        TSTRING.GET_LINE(FULL_TABLE_TEMP_FILE, BUF); 
        TSTRING.PUT_LINE(BUF); 
      end loop; 
      DELETE(FULL_TABLE_TEMP_FILE); 

      MISC.DATAEND; 
    else 
      TBLCMP.CMPTMPS;  -- create compressed template entries

      -- create tables for all the states with only one out-transition
      while (ONESP > 0) loop
        TBLCMP.MK1TBL(ONESTATE(ONESP), ONESYM(ONESP), ONENEXT(ONESP), ONEDEF(
          ONESP)); 
        ONESP := ONESP - 1; 
      end loop; 

      TBLCMP.MKDEFTBL; 
    end if; 
  end NTOD; 

  -- snstods - converts a set of ndfa states into a dfa state
  --
  -- on return, the dfa state number is in newds.
  procedure SNSTODS(SNS           : in INT_PTR; 
                    NUMSTATES     : in INTEGER; 
                    ACCSET        : in INT_PTR; 
                    NACC, HASHVAL : in INTEGER; 
                    NEWDS_ADDR    : out INTEGER; 
                    RESULT        : out BOOLEAN) is 
    DIDSORT : BOOLEAN := FALSE; 
    J       : INTEGER; 
    NEWDS   : INTEGER; 
    OLDSNS  : INT_PTR; 
  begin
    for I in 1 .. LASTDFA loop
      if (HASHVAL = DHASH(I)) then 
        if (NUMSTATES = DFASIZ(I)) then 
          OLDSNS := DSS(I); 

          if (not DIDSORT) then 
          -- we sort the states in sns so we can compare it to
          -- oldsns quickly.  we use bubble because there probably
          -- aren't very many states

            MISC.BUBBLE(SNS, NUMSTATES); 
            DIDSORT := TRUE; 
          end if; 

          J := 1; 
          while (J <= NUMSTATES) loop
            if (SNS(J) /= OLDSNS(J)) then 
              exit; 
            end if; 
            J := J + 1; 
          end loop; 

          if (J > NUMSTATES) then 
            DFAEQL := DFAEQL + 1; 
            NEWDS_ADDR := I; 
            RESULT := FALSE; 
            return; 
          end if; 

          HSHCOL := HSHCOL + 1; 
        else 
          HSHSAVE := HSHSAVE + 1; 
        end if; 
      end if; 
    end loop; 
    -- make a new dfa

    LASTDFA := LASTDFA + 1; 
    if (LASTDFA >= CURRENT_MAX_DFAS) then 
      INCREASE_MAX_DFAS; 
    end if; 

    NEWDS := LASTDFA; 

    DSS(NEWDS) := new UNBOUNDED_INT_ARRAY(0 .. NUMSTATES + 1); 

    -- if we haven't already sorted the states in sns, we do so now, so that
    -- future comparisons with it can be made quickly

    if (not DIDSORT) then 
      MISC.BUBBLE(SNS, NUMSTATES); 
    end if; 

    for I in 1 .. NUMSTATES loop
      DSS(NEWDS)(I) := SNS(I); 
    end loop; 

    DFASIZ(NEWDS) := NUMSTATES; 
    DHASH(NEWDS) := HASHVAL; 

    if (NACC = 0) then 
      DFAACC(NEWDS).DFAACC_STATE := 0; 
      ACCSIZ(NEWDS) := 0; 
    else 
    -- find lowest numbered rule so the disambiguating rule will work
      J := NUM_RULES + 1; 

      for I in 1 .. NACC loop
        if (ACCSET(I) < J) then 
          J := ACCSET(I); 
        end if; 
      end loop; 

      DFAACC(NEWDS).DFAACC_STATE := J; 
    end if; 

    NEWDS_ADDR := NEWDS; 
    RESULT := TRUE; 
    return; 

  exception
    when STORAGE_ERROR => 
      MISC.AFLEXFATAL("dynamic memory failure in snstods()"); 
  end SNSTODS; 

  -- symfollowset - follow the symbol transitions one step
  function SYMFOLLOWSET(DS              : in INT_PTR; 
                        DSIZE, TRANSSYM : in INTEGER; 
                        NSET            : in INT_PTR) return INTEGER is 
    NS, TSP, SYM, LENCCL, CH, NUMSTATES, CCLLIST : INTEGER; 
  begin
    NUMSTATES := 0; 

    for I in 1 .. DSIZE loop
    -- for each nfa state ns in the state set of ds
      NS := DS(I); 
      SYM := TRANSCHAR(NS); 
      TSP := TRANS1(NS); 

      if (SYM < 0) then 
      -- it's a character class
        SYM :=  -SYM; 
        CCLLIST := CCLMAP(SYM); 
        LENCCL := CCLLEN(SYM); 

        if (CCLNG(SYM) /= 0) then 
          for J in 0 .. LENCCL - 1 loop
          -- loop through negated character class
            CH := CHARACTER'POS(CCLTBL(CCLLIST + J)); 

            if (CH > TRANSSYM) then 
              exit;  -- transsym isn't in negated ccl
            else 
              if (CH = TRANSSYM) then 
                goto BOTTOM;  -- next 2
              end if; 
            end if; 
          end loop; 

          -- didn't find transsym in ccl
          NUMSTATES := NUMSTATES + 1; 
          NSET(NUMSTATES) := TSP; 
        else 
          for J in 0 .. LENCCL - 1 loop
            CH := CHARACTER'POS(CCLTBL(CCLLIST + J)); 

            if (CH > TRANSSYM) then 
              exit; 
            else 
              if (CH = TRANSSYM) then 
                NUMSTATES := NUMSTATES + 1; 
                NSET(NUMSTATES) := TSP; 
                exit; 
              end if; 
            end if; 
          end loop; 
        end if; 
      else 
        if ((SYM >= CHARACTER'POS('A')) and (SYM <= CHARACTER'POS('Z')) and 
          CASEINS) then 
          MISC.AFLEXFATAL("consistency check failed in symfollowset"); 
        else 
          if (SYM = SYM_EPSILON) then 
            null;  -- do nothing
          else 
            if (ECGROUP(SYM) = TRANSSYM) then 
              NUMSTATES := NUMSTATES + 1; 
              NSET(NUMSTATES) := TSP; 
            end if; 
          end if; 
        end if; 
      end if; 

      <<BOTTOM>> null; 
    end loop; 
    return NUMSTATES; 
  end SYMFOLLOWSET; 

  -- sympartition - partition characters with same out-transitions
  procedure SYMPARTITION(DS        : in INT_PTR; 
                         NUMSTATES : in INTEGER; 
                         SYMLIST   : in out C_SIZE_BOOL_ARRAY; 
                         DUPLIST   : in out C_SIZE_ARRAY) is 
    TCH, J, NS, LENCCL, CCLP, ICH : INTEGER; 
    DUPFWD                        : C_SIZE_ARRAY; 

  -- partitioning is done by creating equivalence classes for those
  -- characters which have out-transitions from the given state.  Thus
  -- we are really creating equivalence classes of equivalence classes.
  begin
    for I in 1 .. NUMECS loop
    -- initialize equivalence class list
      DUPLIST(I) := I - 1; 
      DUPFWD(I) := I + 1; 
    end loop; 

    DUPLIST(1) := NIL; 
    DUPFWD(NUMECS) := NIL; 
    DUPFWD(0) := 0; 

    for I in 1 .. NUMSTATES loop
      NS := DS(I); 
      TCH := TRANSCHAR(NS); 

      if (TCH /= SYM_EPSILON) then 
        if ((TCH <  -LASTCCL) or (TCH > CSIZE)) then 
          MISC.AFLEXFATAL("bad transition character detected in sympartition()")
            ; 
        end if; 

        if (TCH > 0) then 
        -- character transition
          ECS.MKECHAR(ECGROUP(TCH), DUPFWD, DUPLIST); 
          SYMLIST(ECGROUP(TCH)) := TRUE; 
        else 
        -- character class
          TCH :=  -TCH; 

          LENCCL := CCLLEN(TCH); 
          CCLP := CCLMAP(TCH); 
          ECS.MKECCL(CCLTBL(CCLP .. CCLP + LENCCL), LENCCL, DUPFWD, DUPLIST, 
            NUMECS); 

          if (CCLNG(TCH) /= 0) then 
            J := 0; 

            for K in 0 .. LENCCL - 1 loop
              ICH := CHARACTER'POS(CCLTBL(CCLP + K)); 

              J := J + 1; 
              while (J < ICH) loop
                SYMLIST(J) := TRUE; 
                J := J + 1; 
              end loop; 
            end loop; 

            J := J + 1; 
            while (J <= NUMECS) loop
              SYMLIST(J) := TRUE; 
              J := J + 1; 
            end loop; 
          else 
            for K in 0 .. LENCCL - 1 loop
              ICH := CHARACTER'POS(CCLTBL(CCLP + K)); 
              SYMLIST(ICH) := TRUE; 
            end loop; 
          end if; 
        end if; 
      end if; 
    end loop; 
  end SYMPARTITION; 
end DFA; 
