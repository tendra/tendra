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

-- TITLE table compression routines
-- AUTHOR: John Self (UCI)
-- DESCRIPTION used for compressed tables only
-- NOTES somewhat complicated but works fast and generates efficient scanners
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/tblcmpB.a,v 1.8 90/01/12 15:20:43 self Exp Locker: self $ 

with DFA, ECS, MISC_DEFS; use MISC_DEFS; 
package body TBLCMP is 

-- bldtbl - build table entries for dfa state
--
-- synopsis
--   int state[numecs], statenum, totaltrans, comstate, comfreq;
--   bldtbl( state, statenum, totaltrans, comstate, comfreq );
--
-- State is the statenum'th dfa state.  It is indexed by equivalence class and
-- gives the number of the state to enter for a given equivalence class.
-- totaltrans is the total number of transitions out of the state.  Comstate
-- is that state which is the destination of the most transitions out of State.
-- Comfreq is how many transitions there are out of State to Comstate.
--
-- A note on terminology:
--    "protos" are transition tables which have a high probability of
-- either being redundant (a state processed later will have an identical
-- transition table) or nearly redundant (a state processed later will have
-- many of the same out-transitions).  A "most recently used" queue of
-- protos is kept around with the hope that most states will find a proto
-- which is similar enough to be usable, and therefore compacting the
-- output tables.
--    "templates" are a special type of proto.  If a transition table is
-- homogeneous or nearly homogeneous (all transitions go to the same
-- destination) then the odds are good that future states will also go
-- to the same destination state on basically the same character set.
-- These homogeneous states are so common when dealing with large rule
-- sets that they merit special attention.  If the transition table were
-- simply made into a proto, then (typically) each subsequent, similar
-- state will differ from the proto for two out-transitions.  One of these
-- out-transitions will be that character on which the proto does not go
-- to the common destination, and one will be that character on which the
-- state does not go to the common destination.  Templates, on the other
-- hand, go to the common state on EVERY transition character, and therefore
-- cost only one difference.

  procedure BLDTBL(STATE                                   : in 
                     UNBOUNDED_INT_ARRAY; 
                   STATENUM, TOTALTRANS, COMSTATE, COMFREQ : in INTEGER) is 
    EXTPTR : INTEGER; 
    subtype CARRAY is UNBOUNDED_INT_ARRAY(0 .. CSIZE + 1); 
    EXTRCT                 : array(0 .. 1) of CARRAY; 
    MINDIFF, MINPROT, I, D : INTEGER; 
    CHECKCOM               : BOOLEAN; 
    LOCAL_COMSTATE         : INTEGER; 
  begin

    -- If extptr is 0 then the first array of extrct holds the result of the
    -- "best difference" to date, which is those transitions which occur in
    -- "state" but not in the proto which, to date, has the fewest differences
    -- between itself and "state".  If extptr is 1 then the second array of
    -- extrct hold the best difference.  The two arrays are toggled
    -- between so that the best difference to date can be kept around and
    -- also a difference just created by checking against a candidate "best"
    -- proto.
    LOCAL_COMSTATE := COMSTATE; 
    EXTPTR := 0; 

    -- if the state has too few out-transitions, don't bother trying to
    -- compact its tables
    if ((TOTALTRANS*100) < (NUMECS*PROTO_SIZE_PERCENTAGE)) then 
      MKENTRY(STATE, NUMECS, STATENUM, JAMSTATE_CONST, TOTALTRANS); 
    else 

      -- checkcom is true if we should only check "state" against
      -- protos which have the same "comstate" value
      CHECKCOM := COMFREQ*100 > TOTALTRANS*CHECK_COM_PERCENTAGE; 

      MINPROT := FIRSTPROT; 
      MINDIFF := TOTALTRANS; 

      if (CHECKCOM) then 

        -- find first proto which has the same "comstate"
        I := FIRSTPROT; 
        while (I /= NIL) loop
          if (PROTCOMST(I) = LOCAL_COMSTATE) then 
            MINPROT := I; 
            TBLDIFF(STATE, MINPROT, EXTRCT(EXTPTR), MINDIFF); 
            exit; 
          end if; 
          I := PROTNEXT(I); 
        end loop; 
      else 

        -- since we've decided that the most common destination out
        -- of "state" does not occur with a high enough frequency,
        -- we set the "comstate" to zero, assuring that if this state
        -- is entered into the proto list, it will not be considered
        -- a template.
        LOCAL_COMSTATE := 0; 

        if (FIRSTPROT /= NIL) then 
          MINPROT := FIRSTPROT; 
          TBLDIFF(STATE, MINPROT, EXTRCT(EXTPTR), MINDIFF); 
        end if; 
      end if; 

      -- we now have the first interesting proto in "minprot".  If
      -- it matches within the tolerances set for the first proto,
      -- we don't want to bother scanning the rest of the proto list
      -- to see if we have any other reasonable matches.
      if (MINDIFF*100 > TOTALTRANS*FIRST_MATCH_DIFF_PERCENTAGE) then 

        -- not a good enough match.  Scan the rest of the protos 
        I := MINPROT; 
        while (I /= NIL) loop
          TBLDIFF(STATE, I, EXTRCT(1 - EXTPTR), D); 
          if (D < MINDIFF) then 
            EXTPTR := 1 - EXTPTR; 
            MINDIFF := D; 
            MINPROT := I; 
          end if; 
          I := PROTNEXT(I); 
        end loop; 
      end if; 

      -- check if the proto we've decided on as our best bet is close
      -- enough to the state we want to match to be usable
      if (MINDIFF*100 > TOTALTRANS*ACCEPTABLE_DIFF_PERCENTAGE) then 

        -- no good.  If the state is homogeneous enough, we make a
        -- template out of it.  Otherwise, we make a proto.
        if (COMFREQ*100 >= TOTALTRANS*TEMPLATE_SAME_PERCENTAGE) then 
          MKTEMPLATE(STATE, STATENUM, LOCAL_COMSTATE); 
        else 
          MKPROT(STATE, STATENUM, LOCAL_COMSTATE); 
          MKENTRY(STATE, NUMECS, STATENUM, JAMSTATE_CONST, TOTALTRANS); 
        end if; 
      else 

        -- use the proto
        MKENTRY(EXTRCT(EXTPTR), NUMECS, STATENUM, PROTTBL(MINPROT), MINDIFF); 

        -- if this state was sufficiently different from the proto
        -- we built it from, make it, too, a proto
        if (MINDIFF*100 >= TOTALTRANS*NEW_PROTO_DIFF_PERCENTAGE) then 
          MKPROT(STATE, STATENUM, LOCAL_COMSTATE); 
        end if; 

        -- since mkprot added a new proto to the proto queue, it's possible
        -- that "minprot" is no longer on the proto queue (if it happened
        -- to have been the last entry, it would have been bumped off).
        -- If it's not there, then the new proto took its physical place
        -- (though logically the new proto is at the beginning of the
        -- queue), so in that case the following call will do nothing.
        MV2FRONT(MINPROT); 
      end if; 
    end if; 
  end BLDTBL; 

  -- cmptmps - compress template table entries
  --
  --  template tables are compressed by using the 'template equivalence
  --  classes', which are collections of transition character equivalence
--  classes which always appear together in templates - really meta-equivalence
  --  classes.  until this point, the tables for templates have been stored
  --  up at the top end of the nxt array; they will now be compressed and have
  --  table entries made for them.

  procedure CMPTMPS is 
    TMPSTORAGE        : C_SIZE_ARRAY; 
    TOTALTRANS, TRANS : INTEGER; 
  begin
    PEAKPAIRS := NUMTEMPS*NUMECS + TBLEND; 

    if (USEMECS) then 

      -- create equivalence classes base on data gathered on template
      -- transitions
      ECS.CRE8ECS(TECFWD, TECBCK, NUMECS, NUMMECS); 
    else 
      NUMMECS := NUMECS; 
    end if; 

    if (LASTDFA + NUMTEMPS + 1 >= CURRENT_MAX_DFAS) then 
      DFA.INCREASE_MAX_DFAS; 
    end if; 

    -- loop through each template
    for I in 1 .. NUMTEMPS loop
      TOTALTRANS := 0; 

      -- number of non-jam transitions out of this template
      for J in 1 .. NUMECS loop
        TRANS := TNXT(NUMECS*I + J); 

        if (USEMECS) then 

          -- the absolute value of tecbck is the meta-equivalence class
          -- of a given equivalence class, as set up by cre8ecs
          if (TECBCK(J) > 0) then 
            TMPSTORAGE(TECBCK(J)) := TRANS; 

            if (TRANS > 0) then 
              TOTALTRANS := TOTALTRANS + 1; 
            end if; 
          end if; 
        else 
          TMPSTORAGE(J) := TRANS; 

          if (TRANS > 0) then 
            TOTALTRANS := TOTALTRANS + 1; 
          end if; 
        end if; 
      end loop; 

      -- it is assumed (in a rather subtle way) in the skeleton that
      -- if we're using meta-equivalence classes, the def[] entry for
      -- all templates is the jam template, i.e., templates never default
      -- to other non-jam table entries (e.g., another template)

      -- leave room for the jam-state after the last real state
      MKENTRY(TMPSTORAGE, NUMMECS, LASTDFA + I + 1, JAMSTATE_CONST, TOTALTRANS)
        ; 
    end loop; 
  end CMPTMPS; 

  -- expand_nxt_chk - expand the next check arrays

  procedure EXPAND_NXT_CHK is 
    OLD_MAX : INTEGER := CURRENT_MAX_XPAIRS; 
  begin
    CURRENT_MAX_XPAIRS := CURRENT_MAX_XPAIRS + MAX_XPAIRS_INCREMENT; 

    NUM_REALLOCS := NUM_REALLOCS + 1; 

    REALLOCATE_INTEGER_ARRAY(NXT, CURRENT_MAX_XPAIRS); 
    REALLOCATE_INTEGER_ARRAY(CHK, CURRENT_MAX_XPAIRS); 

    for I in OLD_MAX .. CURRENT_MAX_XPAIRS loop
      CHK(I) := 0; 
    end loop; 
  end EXPAND_NXT_CHK; 

  -- find_table_space - finds a space in the table for a state to be placed
  --
  -- State is the state to be added to the full speed transition table.
  -- Numtrans is the number of out-transitions for the state.
  --
-- find_table_space() returns the position of the start of the first block (in
  -- chk) able to accommodate the state
  --
-- In determining if a state will or will not fit, find_table_space() must take
  -- into account the fact that an end-of-buffer state will be added at [0],
  -- and an action number will be added in [-1].

  function FIND_TABLE_SPACE(STATE    : in UNBOUNDED_INT_ARRAY; 
                            NUMTRANS : in INTEGER) return INTEGER is 
  -- firstfree is the position of the first possible occurrence of two
  -- consecutive unused records in the chk and nxt arrays

    I                                              : INTEGER; 
    STATE_PTR, CHK_PTR, PTR_TO_LAST_ENTRY_IN_STATE : INT_PTR; 
    CNT, SCNT                                      : INTEGER; 
    -- if there are too many out-transitions, put the state at the end of
    -- nxt and chk
  begin
    if (NUMTRANS > MAX_XTIONS_FULL_INTERIOR_FIT) then 

      -- if table is empty, return the first available spot in chk/nxt,
      -- which should be 1
      if (TBLEND < 2) then 
        return (1); 
      end if; 

      I := TBLEND - NUMECS; 

    -- start searching for table space near the
    -- end of chk/nxt arrays
    else 
      I := FIRSTFREE; 

    -- start searching for table space from the
    -- beginning (skipping only the elements
    -- which will definitely not hold the new
    -- state)
    end if; 

    loop

      -- loops until a space is found
      if (I + NUMECS > CURRENT_MAX_XPAIRS) then 
        EXPAND_NXT_CHK; 
      end if; 

      -- loops until space for end-of-buffer and action number are found
      loop
        if (CHK(I - 1) = 0) then 

          -- check for action number space
          if (CHK(I) = 0) then 

            -- check for end-of-buffer space
            exit; 
          else 
            I := I + 2; 

          -- since i != 0, there is no use checking to
          -- see if (++i) - 1 == 0, because that's the
          -- same as i == 0, so we skip a space
          end if; 
        else 
          I := I + 1; 
        end if; 

        if (I + NUMECS > CURRENT_MAX_XPAIRS) then 
          EXPAND_NXT_CHK; 
        end if; 
      end loop; 

      -- if we started search from the beginning, store the new firstfree for
      -- the next call of find_table_space()
      if (NUMTRANS <= MAX_XTIONS_FULL_INTERIOR_FIT) then 
        FIRSTFREE := I + 1; 
      end if; 

      -- check to see if all elements in chk (and therefore nxt) that are
      -- needed for the new state have not yet been taken
      CNT := I + 1; 
      SCNT := 1; 
      while (CNT /= I + NUMECS + 1) loop
        if ((STATE(SCNT) /= 0) and (CHK(CNT) /= 0)) then 
          exit; 
        end if; 
        SCNT := SCNT + 1; 
        CNT := CNT + 1; 
      end loop; 

      if (CNT = I + NUMECS + 1) then 
        return I; 
      else 
        I := I + 1; 
      end if; 
    end loop; 
  end FIND_TABLE_SPACE; 

  -- inittbl - initialize transition tables
  --
-- Initializes "firstfree" to be one beyond the end of the table.  Initializes
  -- all "chk" entries to be zero.  Note that templates are built in their
  -- own tbase/tdef tables.  They are shifted down to be contiguous
  -- with the non-template entries during table generation.

  procedure INITTBL is 
  begin
    for I in 0 .. CURRENT_MAX_XPAIRS loop
      CHK(I) := 0; 
    end loop; 

    TBLEND := 0; 
    FIRSTFREE := TBLEND + 1; 
    NUMTEMPS := 0; 

    if (USEMECS) then 

      -- set up doubly-linked meta-equivalence classes
      -- these are sets of equivalence classes which all have identical
      -- transitions out of TEMPLATES
      TECBCK(1) := NIL; 

      for I in 2 .. NUMECS loop
        TECBCK(I) := I - 1; 
        TECFWD(I - 1) := I; 
      end loop; 

      TECFWD(NUMECS) := NIL; 
    end if; 
  end INITTBL; 

  -- mkdeftbl - make the default, "jam" table entries

  procedure MKDEFTBL is 
  begin
    JAMSTATE := LASTDFA + 1; 

    TBLEND := TBLEND + 1; 

    -- room for transition on end-of-buffer character
    if (TBLEND + NUMECS > CURRENT_MAX_XPAIRS) then 
      EXPAND_NXT_CHK; 
    end if; 

    -- add in default end-of-buffer transition
    NXT(TBLEND) := END_OF_BUFFER_STATE; 
    CHK(TBLEND) := JAMSTATE; 

    for I in 1 .. NUMECS loop
      NXT(TBLEND + I) := 0; 
      CHK(TBLEND + I) := JAMSTATE; 
    end loop; 

    JAMBASE := TBLEND; 

    BASE(JAMSTATE) := JAMBASE; 
    DEF(JAMSTATE) := 0; 

    TBLEND := TBLEND + NUMECS; 
    NUMTEMPS := NUMTEMPS + 1; 
  end MKDEFTBL; 

  -- mkentry - create base/def and nxt/chk entries for transition array
  --
  -- "state" is a transition array "numchars" characters in size, "statenum"
  -- is the offset to be used into the base/def tables, and "deflink" is the
  -- entry to put in the "def" table entry.  If "deflink" is equal to
  -- "JAMSTATE", then no attempt will be made to fit zero entries of "state"
  -- (i.e., jam entries) into the table.  It is assumed that by linking to
  -- "JAMSTATE" they will be taken care of.  In any case, entries in "state"
  -- marking transitions to "SAME_TRANS" are treated as though they will be
  -- taken care of by whereever "deflink" points.  "totaltrans" is the total
-- number of transitions out of the state.  If it is below a certain threshold,
  -- the tables are searched for an interior spot that will accommodate the
  -- state array.

  procedure MKENTRY(STATE                                   : in 
                      UNBOUNDED_INT_ARRAY; 
                    NUMCHARS, STATENUM, DEFLINK, TOTALTRANS : in INTEGER) is 
    I, MINEC, MAXEC, BASEADDR, TBLBASE, TBLLAST : INTEGER; 
  begin
    if (TOTALTRANS = 0) then 

      -- there are no out-transitions
      if (DEFLINK = JAMSTATE_CONST) then 
        BASE(STATENUM) := JAMSTATE_CONST; 
      else 
        BASE(STATENUM) := 0; 
      end if; 

      DEF(STATENUM) := DEFLINK; 
      return; 
    end if; 

    MINEC := 1; 
    while (MINEC <= NUMCHARS) loop
      if (STATE(MINEC) /= SAME_TRANS) then 
        if ((STATE(MINEC) /= 0) or (DEFLINK /= JAMSTATE_CONST)) then 
          exit; 
        end if; 
      end if; 
      MINEC := MINEC + 1; 
    end loop; 

    if (TOTALTRANS = 1) then 

      -- there's only one out-transition.  Save it for later to fill
      -- in holes in the tables.
      STACK1(STATENUM, MINEC, STATE(MINEC), DEFLINK); 
      return; 
    end if; 

    MAXEC := NUMCHARS; 
    while (MAXEC >= 1) loop
      if (STATE(MAXEC) /= SAME_TRANS) then 
        if ((STATE(MAXEC) /= 0) or (DEFLINK /= JAMSTATE_CONST)) then 
          exit; 
        end if; 
      end if; 
      MAXEC := MAXEC - 1; 
    end loop; 

    -- Whether we try to fit the state table in the middle of the table
    -- entries we have already generated, or if we just take the state
    -- table at the end of the nxt/chk tables, we must make sure that we
    -- have a valid base address (i.e., non-negative).  Note that not only are
    -- negative base addresses dangerous at run-time (because indexing the
    -- next array with one and a low-valued character might generate an
    -- array-out-of-bounds error message), but at compile-time negative
    -- base addresses denote TEMPLATES.

    -- find the first transition of state that we need to worry about.
    if (TOTALTRANS*100 <= NUMCHARS*INTERIOR_FIT_PERCENTAGE) then 

      -- attempt to squeeze it into the middle of the tabls
      BASEADDR := FIRSTFREE; 

      while (BASEADDR < MINEC) loop

        -- using baseaddr would result in a negative base address below
        -- find the next free slot
        BASEADDR := BASEADDR + 1; 
        while (CHK(BASEADDR) /= 0) loop
          BASEADDR := BASEADDR + 1; 
        end loop; 
      end loop; 

      if (BASEADDR + MAXEC - MINEC >= CURRENT_MAX_XPAIRS) then 
        EXPAND_NXT_CHK; 
      end if; 

      I := MINEC; 
      while (I <= MAXEC) loop
        if (STATE(I) /= SAME_TRANS) then 
          if ((STATE(I) /= 0) or (DEFLINK /= JAMSTATE_CONST)) then 
            if (CHK(BASEADDR + I - MINEC) /= 0) then 

              -- baseaddr unsuitable - find another
              BASEADDR := BASEADDR + 1; 
              while ((BASEADDR < CURRENT_MAX_XPAIRS) and (CHK(BASEADDR) /= 0))
                loop
                BASEADDR := BASEADDR + 1; 
              end loop; 

              if (BASEADDR + MAXEC - MINEC >= CURRENT_MAX_XPAIRS) then 
                EXPAND_NXT_CHK; 
              end if; 

              -- reset the loop counter so we'll start all
              -- over again next time it's incremented
              I := MINEC - 1; 
            end if; 
          end if; 
        end if; 
        I := I + 1; 
      end loop; 
    else 

      -- ensure that the base address we eventually generate is
      -- non-negative
      BASEADDR := MAX(TBLEND + 1, MINEC); 
    end if; 

    TBLBASE := BASEADDR - MINEC; 
    TBLLAST := TBLBASE + MAXEC; 

    if (TBLLAST >= CURRENT_MAX_XPAIRS) then 
      EXPAND_NXT_CHK; 
    end if; 

    BASE(STATENUM) := TBLBASE; 
    DEF(STATENUM) := DEFLINK; 

    for J in MINEC .. MAXEC loop
      if (STATE(J) /= SAME_TRANS) then 
        if ((STATE(J) /= 0) or (DEFLINK /= JAMSTATE_CONST)) then 
          NXT(TBLBASE + J) := STATE(J); 
          CHK(TBLBASE + J) := STATENUM; 
        end if; 
      end if; 
    end loop; 

    if (BASEADDR = FIRSTFREE) then 

      -- find next free slot in tables
      FIRSTFREE := FIRSTFREE + 1; 
      while (CHK(FIRSTFREE) /= 0) loop
        FIRSTFREE := FIRSTFREE + 1; 
      end loop; 
    end if; 

    TBLEND := MAX(TBLEND, TBLLAST); 
  end MKENTRY; 

  -- mk1tbl - create table entries for a state (or state fragment) which
  --            has only one out-transition

  procedure MK1TBL(STATE, SYM, ONENXT, ONEDEF : in INTEGER) is 
  begin
    if (FIRSTFREE < SYM) then 
      FIRSTFREE := SYM; 
    end if; 

    while (CHK(FIRSTFREE) /= 0) loop
      FIRSTFREE := FIRSTFREE + 1; 
      if (FIRSTFREE >= CURRENT_MAX_XPAIRS) then 
        EXPAND_NXT_CHK; 
      end if; 
    end loop; 

    BASE(STATE) := FIRSTFREE - SYM; 
    DEF(STATE) := ONEDEF; 
    CHK(FIRSTFREE) := STATE; 
    NXT(FIRSTFREE) := ONENXT; 

    if (FIRSTFREE > TBLEND) then 
      TBLEND := FIRSTFREE; 
      FIRSTFREE := FIRSTFREE + 1; 

      if (FIRSTFREE >= CURRENT_MAX_XPAIRS) then 
        EXPAND_NXT_CHK; 
      end if; 
    end if; 
  end MK1TBL; 

  -- mkprot - create new proto entry

  procedure MKPROT(STATE              : in UNBOUNDED_INT_ARRAY; 
                   STATENUM, COMSTATE : in INTEGER) is 
    SLOT, TBLBASE : INTEGER; 
  begin
    NUMPROTS := NUMPROTS + 1; 
    if ((NUMPROTS >= MSP) or (NUMECS*NUMPROTS >= PROT_SAVE_SIZE)) then 

      -- gotta make room for the new proto by dropping last entry in
      -- the queue
      SLOT := LASTPROT; 
      LASTPROT := PROTPREV(LASTPROT); 
      PROTNEXT(LASTPROT) := NIL; 
    else 
      SLOT := NUMPROTS; 
    end if; 

    PROTNEXT(SLOT) := FIRSTPROT; 

    if (FIRSTPROT /= NIL) then 
      PROTPREV(FIRSTPROT) := SLOT; 
    end if; 

    FIRSTPROT := SLOT; 
    PROTTBL(SLOT) := STATENUM; 
    PROTCOMST(SLOT) := COMSTATE; 

    -- copy state into save area so it can be compared with rapidly
    TBLBASE := NUMECS*(SLOT - 1); 

    for I in 1 .. NUMECS loop
      PROTSAVE(TBLBASE + I) := STATE(I + STATE'FIRST); 
    end loop; 
  end MKPROT; 

-- mktemplate - create a template entry based on a state, and connect the state
  --              to it

  procedure MKTEMPLATE(STATE              : in UNBOUNDED_INT_ARRAY; 
                       STATENUM, COMSTATE : in INTEGER) is 
    NUMDIFF, TMPBASE : INTEGER; 
    TMP              : C_SIZE_ARRAY; 
    subtype TARRAY is CHAR_ARRAY(0 .. CSIZE); 
    TRANSSET : TARRAY; 
    TSPTR    : INTEGER; 
  begin
    NUMTEMPS := NUMTEMPS + 1; 

    TSPTR := 0; 

    -- calculate where we will temporarily store the transition table
    -- of the template in the tnxt[] array.  The final transition table
    -- gets created by cmptmps()
    TMPBASE := NUMTEMPS*NUMECS; 

    if (TMPBASE + NUMECS >= CURRENT_MAX_TEMPLATE_XPAIRS) then 
      CURRENT_MAX_TEMPLATE_XPAIRS := CURRENT_MAX_TEMPLATE_XPAIRS + 
        MAX_TEMPLATE_XPAIRS_INCREMENT; 

      NUM_REALLOCS := NUM_REALLOCS + 1; 

      REALLOCATE_INTEGER_ARRAY(TNXT, CURRENT_MAX_TEMPLATE_XPAIRS); 
    end if; 

    for I in 1 .. NUMECS loop
      if (STATE(I) = 0) then 
        TNXT(TMPBASE + I) := 0; 
      else 
        TRANSSET(TSPTR) := CHARACTER'VAL(I); 
        TSPTR := TSPTR + 1; 
        TNXT(TMPBASE + I) := COMSTATE; 
      end if; 
    end loop; 

    if (USEMECS) then 
      ECS.MKECCL(TRANSSET, TSPTR, TECFWD, TECBCK, NUMECS); 
    end if; 

    MKPROT(TNXT(TMPBASE .. CURRENT_MAX_TEMPLATE_XPAIRS),  -NUMTEMPS, COMSTATE); 

    -- we rely on the fact that mkprot adds things to the beginning
    -- of the proto queue
    TBLDIFF(STATE, FIRSTPROT, TMP, NUMDIFF); 
    MKENTRY(TMP, NUMECS, STATENUM,  -NUMTEMPS, NUMDIFF); 
  end MKTEMPLATE; 

  -- mv2front - move proto queue element to front of queue

  procedure MV2FRONT(QELM : in INTEGER) is 
  begin
    if (FIRSTPROT /= QELM) then 
      if (QELM = LASTPROT) then 
        LASTPROT := PROTPREV(LASTPROT); 
      end if; 

      PROTNEXT(PROTPREV(QELM)) := PROTNEXT(QELM); 

      if (PROTNEXT(QELM) /= NIL) then 
        PROTPREV(PROTNEXT(QELM)) := PROTPREV(QELM); 
      end if; 

      PROTPREV(QELM) := NIL; 
      PROTNEXT(QELM) := FIRSTPROT; 
      PROTPREV(FIRSTPROT) := QELM; 
      FIRSTPROT := QELM; 
    end if; 
  end MV2FRONT; 

  -- place_state - place a state into full speed transition table
  --
  -- State is the statenum'th state.  It is indexed by equivalence class and
  -- gives the number of the state to enter for a given equivalence class.
  -- Transnum is the number of out-transitions for the state.

  procedure PLACE_STATE(STATE              : in UNBOUNDED_INT_ARRAY; 
                        STATENUM, TRANSNUM : in INTEGER) is 
    I        : INTEGER; 
    POSITION : INTEGER := FIND_TABLE_SPACE(STATE, TRANSNUM); 
  begin

    -- base is the table of start positions
    BASE(STATENUM) := POSITION; 

    -- put in action number marker; this non-zero number makes sure that
    -- find_table_space() knows that this position in chk/nxt is taken
    -- and should not be used for another accepting number in another state
    CHK(POSITION - 1) := 1; 

    -- put in end-of-buffer marker; this is for the same purposes as above
    CHK(POSITION) := 1; 

    -- place the state into chk and nxt
    I := 1; 
    while (I <= NUMECS) loop
      if (STATE(I) /= 0) then 
        CHK(POSITION + I) := I; 
        NXT(POSITION + I) := STATE(I); 
      end if; 
      I := I + 1; 
    end loop; 

    if (POSITION + NUMECS > TBLEND) then 
      TBLEND := POSITION + NUMECS; 
    end if; 
  end PLACE_STATE; 

  -- stack1 - save states with only one out-transition to be processed later
  --
  -- if there's room for another state one the "one-transition" stack, the
  -- state is pushed onto it, to be processed later by mk1tbl.  If there's
  -- no room, we process the sucker right now.

  procedure STACK1(STATENUM, SYM, NEXTSTATE, DEFLINK : in INTEGER) is 
  begin
    if (ONESP >= ONE_STACK_SIZE - 1) then 
      MK1TBL(STATENUM, SYM, NEXTSTATE, DEFLINK); 
    else 
      ONESP := ONESP + 1; 
      ONESTATE(ONESP) := STATENUM; 
      ONESYM(ONESP) := SYM; 
      ONENEXT(ONESP) := NEXTSTATE; 
      ONEDEF(ONESP) := DEFLINK; 
    end if; 
  end STACK1; 

  -- tbldiff - compute differences between two state tables
  --
  -- "state" is the state array which is to be extracted from the pr'th
  -- proto.  "pr" is both the number of the proto we are extracting from
  -- and an index into the save area where we can find the proto's complete
  -- state table.  Each entry in "state" which differs from the corresponding
  -- entry of "pr" will appear in "ext".
  -- Entries which are the same in both "state" and "pr" will be marked
  -- as transitions to "SAME_TRANS" in "ext".  The total number of differences
  -- between "state" and "pr" is returned as function value.  Note that this
  -- number is "numecs" minus the number of "SAME_TRANS" entries in "ext".

  procedure TBLDIFF(STATE  : in UNBOUNDED_INT_ARRAY; 
                    PR     : in INTEGER; 
                    EXT    : out UNBOUNDED_INT_ARRAY; 
                    RESULT : out INTEGER) is 
    SP      : INTEGER := 0; 
    EP      : INTEGER := 0; 
    NUMDIFF : INTEGER := 0; 
    PROTP   : INTEGER; 
  begin
    PROTP := NUMECS*(PR - 1); 

    for I in reverse 1 .. NUMECS loop
      PROTP := PROTP + 1; 
      SP := SP + 1; 
      if (PROTSAVE(PROTP) = STATE(SP)) then 
        EP := EP + 1; 
        EXT(EP) := SAME_TRANS; 
      else 
        EP := EP + 1; 
        EXT(EP) := STATE(SP); 
        NUMDIFF := NUMDIFF + 1; 
      end if; 
    end loop; 

    RESULT := NUMDIFF; 
    return; 
  end TBLDIFF; 

end TBLCMP; 
