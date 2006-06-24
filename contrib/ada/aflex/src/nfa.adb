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

-- TITLE NFA construction routines
-- AUTHOR: John Self (UCI)
-- DESCRIPTION builds the NFA.
-- NOTES this file mirrors flex as closely as possible.
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/nfaB.a,v 1.6 90/01/12 15:20:27 self Exp Locker: self $ 

with MISC_DEFS, NFA, MISC, ECS; 
with TSTRING, INT_IO, TEXT_IO, EXTERNAL_FILE_MANAGER; use MISC_DEFS, TSTRING, 
  EXTERNAL_FILE_MANAGER; 

package body NFA is 

-- add_accept - add an accepting state to a machine
--
-- accepting_number becomes mach's accepting number.

  procedure ADD_ACCEPT(MACH             : in out INTEGER; 
                       ACCEPTING_NUMBER : in INTEGER) is 
  -- hang the accepting number off an epsilon state.  if it is associated
  -- with a state that has a non-epsilon out-transition, then the state
  -- will accept BEFORE it makes that transition, i.e., one character
  -- too soon
    ASTATE : INTEGER; 
  begin
    if (TRANSCHAR(FINALST(MACH)) = SYM_EPSILON) then 
      ACCPTNUM(FINALST(MACH)) := ACCEPTING_NUMBER; 
    else 
      ASTATE := MKSTATE(SYM_EPSILON); 
      ACCPTNUM(ASTATE) := ACCEPTING_NUMBER; 
      MACH := LINK_MACHINES(MACH, ASTATE); 
    end if; 
  end ADD_ACCEPT; 


  -- copysingl - make a given number of copies of a singleton machine
  --
  --     newsng - a new singleton composed of num copies of singl
  --     singl  - a singleton machine
  --     num    - the number of copies of singl to be present in newsng

  function COPYSINGL(SINGL, NUM : in INTEGER) return INTEGER is 
    COPY : INTEGER; 
  begin
    COPY := MKSTATE(SYM_EPSILON); 

    for I in 1 .. NUM loop
      COPY := LINK_MACHINES(COPY, DUPMACHINE(SINGL)); 
    end loop; 

    return COPY; 
  end COPYSINGL; 


  -- dumpnfa - debugging routine to write out an nfa

  procedure DUMPNFA(STATE1 : in INTEGER) is 
    SYM, TSP1, TSP2, ANUM : INTEGER; 
    use TEXT_IO; 
  begin
    TEXT_IO.NEW_LINE(STANDARD_ERROR); 
    TEXT_IO.NEW_LINE(STANDARD_ERROR); 
    TEXT_IO.PUT(STANDARD_ERROR, 
      "********** beginning dump of nfa with start state "); 
    INT_IO.PUT(STANDARD_ERROR, STATE1, 0); 
    TEXT_IO.NEW_LINE(STANDARD_ERROR); 

    -- we probably should loop starting at firstst[state1] and going to
    -- lastst[state1], but they're not maintained properly when we "or"
    -- all of the rules together.  So we use our knowledge that the machine
    -- starts at state 1 and ends at lastnfa.
    for NS in 1 .. LASTNFA loop
      TEXT_IO.PUT(STANDARD_ERROR, "state # "); 
      INT_IO.PUT(STANDARD_ERROR, NS, 4); 
      TEXT_IO.PUT(ASCII.HT); 
      SYM := TRANSCHAR(NS); 
      TSP1 := TRANS1(NS); 
      TSP2 := TRANS2(NS); 
      ANUM := ACCPTNUM(NS); 

      INT_IO.PUT(STANDARD_ERROR, SYM, 5); 
      TEXT_IO.PUT(STANDARD_ERROR, ":    "); 
      INT_IO.PUT(STANDARD_ERROR, TSP1, 4); 
      TEXT_IO.PUT(STANDARD_ERROR, ","); 
      INT_IO.PUT(STANDARD_ERROR, TSP2, 4); 
      if (ANUM /= NIL) then 
        TEXT_IO.PUT(STANDARD_ERROR, "  ["); 
        INT_IO.PUT(STANDARD_ERROR, ANUM, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, "]"); 
      end if; 
      TEXT_IO.NEW_LINE(STANDARD_ERROR); 
    end loop; 

    TEXT_IO.PUT(STANDARD_ERROR, "********** end of dump"); 
    TEXT_IO.NEW_LINE(STANDARD_ERROR); 
  end DUMPNFA; 

  -- dupmachine - make a duplicate of a given machine
  --
  --     copy - holds duplicate of mach
  --     mach - machine to be duplicated
  --
  -- note that the copy of mach is NOT an exact duplicate; rather, all the
  -- transition states values are adjusted so that the copy is self-contained,
  -- as the original should have been.
  --
  -- also note that the original MUST be contiguous, with its low and high
  -- states accessible by the arrays firstst and lastst

  function DUPMACHINE(MACH : in INTEGER) return INTEGER is 
    INIT, STATE_OFFSET : INTEGER; 
    STATE              : INTEGER := 0; 
    LAST               : INTEGER := LASTST(MACH); 
    I                  : INTEGER; 
  begin
    I := FIRSTST(MACH); 
    while (I <= LAST) loop
      STATE := MKSTATE(TRANSCHAR(I)); 

      if (TRANS1(I) /= NO_TRANSITION) then 
        MKXTION(FINALST(STATE), TRANS1(I) + STATE - I); 

        if ((TRANSCHAR(I) = SYM_EPSILON) and (TRANS2(I) /= NO_TRANSITION)) then 
          MKXTION(FINALST(STATE), TRANS2(I) + STATE - I); 
        end if; 
      end if; 

      ACCPTNUM(STATE) := ACCPTNUM(I); 
      I := I + 1; 
    end loop; 

    if (STATE = 0) then 
      MISC.AFLEXFATAL("empty machine in dupmachine()"); 
    end if; 

    STATE_OFFSET := STATE - I + 1; 

    INIT := MACH + STATE_OFFSET; 
    FIRSTST(INIT) := FIRSTST(MACH) + STATE_OFFSET; 
    FINALST(INIT) := FINALST(MACH) + STATE_OFFSET; 
    LASTST(INIT) := LASTST(MACH) + STATE_OFFSET; 

    return INIT; 
  end DUPMACHINE; 

  -- finish_rule - finish up the processing for a rule
  --
  -- An accepting number is added to the given machine.  If variable_trail_rule
  -- is true then the rule has trailing context and both the head and trail
  -- are variable size.  Otherwise if headcnt or trailcnt is non-zero then
  -- the machine recognizes a pattern with trailing context and headcnt is
  -- the number of characters in the matched part of the pattern, or zero
  -- if the matched part has variable length.  trailcnt is the number of
  -- trailing context characters in the pattern, or zero if the trailing
  -- context has variable length.

  procedure FINISH_RULE(MACH                : in INTEGER; 
                        VARIABLE_TRAIL_RULE : in BOOLEAN; 
                        HEADCNT, TRAILCNT   : in INTEGER) is 
    P_MACH : INTEGER; 
    use TEXT_IO; 
  begin
    P_MACH := MACH; 
    ADD_ACCEPT(P_MACH, NUM_RULES); 

    -- we did this in new_rule(), but it often gets the wrong
    -- number because we do it before we start parsing the current rule
    RULE_LINENUM(NUM_RULES) := LINENUM; 

    TEXT_IO.PUT(TEMP_ACTION_FILE, "when "); 
    INT_IO.PUT(TEMP_ACTION_FILE, NUM_RULES, 1); 
    TEXT_IO.PUT_LINE(TEMP_ACTION_FILE, " => "); 

    if (VARIABLE_TRAIL_RULE) then 
      RULE_TYPE(NUM_RULES) := RULE_VARIABLE; 

      if (PERFORMANCE_REPORT) then 
        TEXT_IO.PUT(STANDARD_ERROR, "Variable trailing context rule at line "); 
        INT_IO.PUT(STANDARD_ERROR, RULE_LINENUM(NUM_RULES), 1); 
        TEXT_IO.NEW_LINE(STANDARD_ERROR); 
      end if; 

      VARIABLE_TRAILING_CONTEXT_RULES := TRUE; 
    else 
      RULE_TYPE(NUM_RULES) := RULE_NORMAL; 

      if ((HEADCNT > 0) or (TRAILCNT > 0)) then 

        -- do trailing context magic to not match the trailing characters
        TEXT_IO.PUT_LINE(TEMP_ACTION_FILE, 
          "yy_ch_buf(yy_cp) := yy_hold_char; -- undo effects of setting up yytext"
          ); 

        if (HEADCNT > 0) then 
          TEXT_IO.PUT(TEMP_ACTION_FILE, " yy_cp := yy_bp + "); 
          INT_IO.PUT(TEMP_ACTION_FILE, HEADCNT, 1); 
          TEXT_IO.PUT_LINE(TEMP_ACTION_FILE, ";"); 
        else 
          TEXT_IO.PUT(TEMP_ACTION_FILE, "yy_cp := yy_cp - "); 
          INT_IO.PUT(TEMP_ACTION_FILE, TRAILCNT, 1); 
          TEXT_IO.PUT_LINE(TEMP_ACTION_FILE, ";"); 
        end if; 

        TEXT_IO.PUT_LINE(TEMP_ACTION_FILE, "yy_c_buf_p := yy_cp;"); 
        TEXT_IO.PUT_LINE(TEMP_ACTION_FILE, 
          "YY_DO_BEFORE_ACTION; -- set up yytext again"); 
      end if; 
    end if; 

    MISC.LINE_DIRECTIVE_OUT(TEMP_ACTION_FILE); 
  end FINISH_RULE; 

  -- link_machines - connect two machines together
  --
  --     new    - a machine constructed by connecting first to last
  --     first  - the machine whose successor is to be last
  --     last   - the machine whose predecessor is to be first
  --
  -- note: this routine concatenates the machine first with the machine
  --  last to produce a machine new which will pattern-match first first
  --  and then last, and will fail if either of the sub-patterns fails.
  --  FIRST is set to new by the operation.  last is unmolested.

  function LINK_MACHINES(FIRST, LAST : in INTEGER) return INTEGER is 
  begin
    if (FIRST = NIL) then 
      return LAST; 
    else 
      if (LAST = NIL) then 
        return FIRST; 
      else 
        MKXTION(FINALST(FIRST), LAST); 
        FINALST(FIRST) := FINALST(LAST); 
        LASTST(FIRST) := MAX(LASTST(FIRST), LASTST(LAST)); 
        FIRSTST(FIRST) := MIN(FIRSTST(FIRST), FIRSTST(LAST)); 
        return (FIRST); 
      end if; 
    end if; 
  end LINK_MACHINES; 


  -- mark_beginning_as_normal - mark each "beginning" state in a machine
--                            as being a "normal" (i.e., not trailing context-
  --                            associated) states
  --
  -- The "beginning" states are the epsilon closure of the first state

  procedure MARK_BEGINNING_AS_NORMAL(MACH : in INTEGER) is 
  begin
    case (STATE_TYPE(MACH)) is 
      when STATE_NORMAL => 

        -- oh, we've already visited here
        return; 

      when STATE_TRAILING_CONTEXT => 
        STATE_TYPE(MACH) := STATE_NORMAL; 

        if (TRANSCHAR(MACH) = SYM_EPSILON) then 
          if (TRANS1(MACH) /= NO_TRANSITION) then 
            MARK_BEGINNING_AS_NORMAL(TRANS1(MACH)); 
          end if; 

          if (TRANS2(MACH) /= NO_TRANSITION) then 
            MARK_BEGINNING_AS_NORMAL(TRANS2(MACH)); 
          end if; 
        end if; 
      when others => 
        MISC.AFLEXERROR("bad state type in mark_beginning_as_normal()"); 
    end case; 
  end MARK_BEGINNING_AS_NORMAL; 

  -- mkbranch - make a machine that branches to two machines
  --
  --     branch - a machine which matches either first's pattern or second's
--     first, second - machines whose patterns are to be or'ed (the | operator)
  --
  -- note that first and second are NEITHER destroyed by the operation.  Also,
  -- the resulting machine CANNOT be used with any other "mk" operation except
  -- more mkbranch's.  Compare with mkor()
  function MKBRANCH(FIRST, SECOND : in INTEGER) return INTEGER is 
    EPS : INTEGER; 
  begin
    if (FIRST = NO_TRANSITION) then 
      return SECOND; 
    else 
      if (SECOND = NO_TRANSITION) then 
        return FIRST; 
      end if; 
    end if; 

    EPS := MKSTATE(SYM_EPSILON); 

    MKXTION(EPS, FIRST); 
    MKXTION(EPS, SECOND); 

    return EPS; 
  end MKBRANCH; 


  -- mkclos - convert a machine into a closure
  --
  --     new - a new state which matches the closure of "state"

  function MKCLOS(STATE : in INTEGER) return INTEGER is 
  begin
    return NFA.MKOPT(MKPOSCL(STATE)); 
  end MKCLOS; 


  -- mkopt - make a machine optional
  --
  --     new  - a machine which optionally matches whatever mach matched
  --     mach - the machine to make optional
  --
  -- notes:
  --     1. mach must be the last machine created
  --     2. mach is destroyed by the call

  function MKOPT(MACH : in INTEGER) return INTEGER is 
    EPS    : INTEGER; 
    RESULT : INTEGER; 
  begin
    RESULT := MACH; 
    if (not SUPER_FREE_EPSILON(FINALST(RESULT))) then 
      EPS := NFA.MKSTATE(SYM_EPSILON); 
      RESULT := NFA.LINK_MACHINES(RESULT, EPS); 
    end if; 

    -- can't skimp on the following if FREE_EPSILON(mach) is true because
    -- some state interior to "mach" might point back to the beginning
    -- for a closure
    EPS := NFA.MKSTATE(SYM_EPSILON); 
    RESULT := NFA.LINK_MACHINES(EPS, RESULT); 

    NFA.MKXTION(RESULT, FINALST(RESULT)); 

    return RESULT; 
  end MKOPT; 


  -- mkor - make a machine that matches either one of two machines
  --
  --     new - a machine which matches either first's pattern or second's
--     first, second - machines whose patterns are to be or'ed (the | operator)
  --
  -- note that first and second are both destroyed by the operation
  -- the code is rather convoluted because an attempt is made to minimize
  -- the number of epsilon states needed

  function MKOR(FIRST, SECOND : in INTEGER) return INTEGER is 
    EPS, OREND : INTEGER; 
    P_FIRST    : INTEGER; 
  begin
    P_FIRST := FIRST; 
    if (P_FIRST = NIL) then 
      return SECOND; 
    else 
      if (SECOND = NIL) then 
        return P_FIRST; 
      else 

        -- see comment in mkopt() about why we can't use the first state
        -- of "first" or "second" if they satisfy "FREE_EPSILON"
        EPS := MKSTATE(SYM_EPSILON); 

        P_FIRST := LINK_MACHINES(EPS, P_FIRST); 

        MKXTION(P_FIRST, SECOND); 

        if ((SUPER_FREE_EPSILON(FINALST(P_FIRST))) and (ACCPTNUM(FINALST(P_FIRST
          )) = NIL)) then 
          OREND := FINALST(P_FIRST); 
          MKXTION(FINALST(SECOND), OREND); 
        else 
          if ((SUPER_FREE_EPSILON(FINALST(SECOND))) and (ACCPTNUM(FINALST(SECOND
            )) = NIL)) then 
            OREND := FINALST(SECOND); 
            MKXTION(FINALST(P_FIRST), OREND); 
          else 
            EPS := MKSTATE(SYM_EPSILON); 
            P_FIRST := LINK_MACHINES(P_FIRST, EPS); 
            OREND := FINALST(P_FIRST); 

            MKXTION(FINALST(SECOND), OREND); 
          end if; 
        end if; 
      end if; 
    end if; 

    FINALST(P_FIRST) := OREND; 
    return P_FIRST; 
  end MKOR; 


  -- mkposcl - convert a machine into a positive closure
  --
  --    new - a machine matching the positive closure of "state"

  function MKPOSCL(STATE : in INTEGER) return INTEGER is 
    EPS : INTEGER; 
  begin
    if (SUPER_FREE_EPSILON(FINALST(STATE))) then 
      MKXTION(FINALST(STATE), STATE); 
      return (STATE); 
    else 
      EPS := MKSTATE(SYM_EPSILON); 
      MKXTION(EPS, STATE); 
      return (LINK_MACHINES(STATE, EPS)); 
    end if; 
  end MKPOSCL; 

  -- mkrep - make a replicated machine
  --
  --    new - a machine that matches whatever "mach" matched from "lb"
  --          number of times to "ub" number of times
  --
  -- note
--   if "ub" is INFINITY then "new" matches "lb" or more occurrences of "mach"

  function MKREP(MACH, LB, UB : in INTEGER) return INTEGER is 
    BASE_MACH, TAIL, COPY : INTEGER; 
    P_MACH                : INTEGER; 
  begin
    P_MACH := MACH; 
    BASE_MACH := COPYSINGL(P_MACH, LB - 1); 

    if (UB = INFINITY) then 
      COPY := DUPMACHINE(P_MACH); 
      P_MACH := LINK_MACHINES(P_MACH, LINK_MACHINES(BASE_MACH, MKCLOS(COPY))); 
    else 
      TAIL := MKSTATE(SYM_EPSILON); 

      for I in LB .. UB - 1 loop
        COPY := DUPMACHINE(P_MACH); 
        TAIL := MKOPT(LINK_MACHINES(COPY, TAIL)); 
      end loop; 

      P_MACH := LINK_MACHINES(P_MACH, LINK_MACHINES(BASE_MACH, TAIL)); 
    end if; 

    return P_MACH; 
  end MKREP; 

  -- mkstate - create a state with a transition on a given symbol
  --
  --     state - a new state matching sym
  --     sym   - the symbol the new state is to have an out-transition on
  --
  -- note that this routine makes new states in ascending order through the
  -- state array (and increments LASTNFA accordingly).  The routine DUPMACHINE
  -- relies on machines being made in ascending order and that they are
  -- CONTIGUOUS.  Change it and you will have to rewrite DUPMACHINE (kludge
  -- that it admittedly is)

  function MKSTATE(SYM : in INTEGER) return INTEGER is 
  begin
    LASTNFA := LASTNFA + 1; 
    if (LASTNFA >= CURRENT_MNS) then 
      CURRENT_MNS := CURRENT_MNS + MNS_INCREMENT; 
      if (CURRENT_MNS >= MAXIMUM_MNS) then 
        MISC.AFLEXERROR("input rules are too complicated (>= " & INTEGER'IMAGE(
          CURRENT_MNS) & " NFA states) )"); 
      end if; 

      NUM_REALLOCS := NUM_REALLOCS + 1; 

      REALLOCATE_INTEGER_ARRAY(FIRSTST, CURRENT_MNS); 
      REALLOCATE_INTEGER_ARRAY(LASTST, CURRENT_MNS); 
      REALLOCATE_INTEGER_ARRAY(FINALST, CURRENT_MNS); 
      REALLOCATE_INTEGER_ARRAY(TRANSCHAR, CURRENT_MNS); 
      REALLOCATE_INTEGER_ARRAY(TRANS1, CURRENT_MNS); 
      REALLOCATE_INTEGER_ARRAY(TRANS2, CURRENT_MNS); 
      REALLOCATE_INTEGER_ARRAY(ACCPTNUM, CURRENT_MNS); 
      REALLOCATE_INTEGER_ARRAY(ASSOC_RULE, CURRENT_MNS); 
      REALLOCATE_STATE_ENUM_ARRAY(STATE_TYPE, CURRENT_MNS); 
    end if; 

    FIRSTST(LASTNFA) := LASTNFA; 
    FINALST(LASTNFA) := LASTNFA; 
    LASTST(LASTNFA) := LASTNFA; 
    TRANSCHAR(LASTNFA) := SYM; 
    TRANS1(LASTNFA) := NO_TRANSITION; 
    TRANS2(LASTNFA) := NO_TRANSITION; 
    ACCPTNUM(LASTNFA) := NIL; 
    ASSOC_RULE(LASTNFA) := NUM_RULES; 
    STATE_TYPE(LASTNFA) := CURRENT_STATE_ENUM; 

    -- fix up equivalence classes base on this transition.  Note that any
    -- character which has its own transition gets its own equivalence class.
    -- Thus only characters which are only in character classes have a chance
    -- at being in the same equivalence class.  E.g. "a|b" puts 'a' and 'b'
    -- into two different equivalence classes.  "[ab]" puts them in the same
    -- equivalence class (barring other differences elsewhere in the input).
    if (SYM < 0) then 

      -- we don't have to update the equivalence classes since that was
      -- already done when the ccl was created for the first time
      null; 
    else 
      if (SYM = SYM_EPSILON) then 
        NUMEPS := NUMEPS + 1; 
      else 
        if (USEECS) then 
          ECS.MKECHAR(SYM, NEXTECM, ECGROUP); 
        end if; 
      end if; 
    end if; 

    return LASTNFA; 
  end MKSTATE; 

  -- mkxtion - make a transition from one state to another
  --
  --     statefrom - the state from which the transition is to be made
  --     stateto   - the state to which the transition is to be made

  procedure MKXTION(STATEFROM, STATETO : in INTEGER) is 
  begin
    if (TRANS1(STATEFROM) = NO_TRANSITION) then 
      TRANS1(STATEFROM) := STATETO; 
    else 
      if ((TRANSCHAR(STATEFROM) /= SYM_EPSILON) or (TRANS2(STATEFROM) /= 
        NO_TRANSITION)) then 
        MISC.AFLEXFATAL("found too many transitions in mkxtion()"); 
      else 

        -- second out-transition for an epsilon state
        EPS2 := EPS2 + 1; 
        TRANS2(STATEFROM) := STATETO; 
      end if; 
    end if; 
  end MKXTION; 

  -- new_rule - initialize for a new rule
  --
  -- the global num_rules is incremented and the any corresponding dynamic
  -- arrays (such as rule_type()) are grown as needed.

  procedure NEW_RULE is 
  begin
    NUM_RULES := NUM_RULES + 1; 
    if (NUM_RULES >= CURRENT_MAX_RULES) then 
      NUM_REALLOCS := NUM_REALLOCS + 1; 
      CURRENT_MAX_RULES := CURRENT_MAX_RULES + MAX_RULES_INCREMENT; 
      REALLOCATE_RULE_ENUM_ARRAY(RULE_TYPE, CURRENT_MAX_RULES); 
      REALLOCATE_INTEGER_ARRAY(RULE_LINENUM, CURRENT_MAX_RULES); 
    end if; 

    if (NUM_RULES > MAX_RULE) then 
      MISC.AFLEXERROR("too many rules  (> " & INTEGER'IMAGE(MAX_RULE) & ")!"); 
    end if; 

    RULE_LINENUM(NUM_RULES) := LINENUM; 
  end NEW_RULE; 

end NFA; 
