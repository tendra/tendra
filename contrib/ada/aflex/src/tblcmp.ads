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
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/tblcmpS.a,v 1.3 90/01/12 15:20:47 self Exp Locker: self $ 

with MISC_DEFS; use MISC_DEFS; 

package TBLCMP is 

-- bldtbl - build table entries for dfa state

  procedure BLDTBL(STATE                                   : in 
                     UNBOUNDED_INT_ARRAY; 
                   STATENUM, TOTALTRANS, COMSTATE, COMFREQ : in INTEGER); 

  procedure CMPTMPS; 

  -- expand_nxt_chk - expand the next check arrays

  procedure EXPAND_NXT_CHK; 

  -- find_table_space - finds a space in the table for a state to be placed

  function FIND_TABLE_SPACE(STATE    : in UNBOUNDED_INT_ARRAY; 
                            NUMTRANS : in INTEGER) return INTEGER; 

  -- inittbl - initialize transition tables

  procedure INITTBL; 

  -- mkdeftbl - make the default, "jam" table entries

  procedure MKDEFTBL; 

  -- mkentry - create base/def and nxt/chk entries for transition array

  procedure MKENTRY(STATE                                   : in 
                      UNBOUNDED_INT_ARRAY; 
                    NUMCHARS, STATENUM, DEFLINK, TOTALTRANS : in INTEGER); 

  -- mk1tbl - create table entries for a state (or state fragment) which
  --            has only one out-transition

  procedure MK1TBL(STATE, SYM, ONENXT, ONEDEF : in INTEGER); 

  -- mkprot - create new proto entry

  procedure MKPROT(STATE              : in UNBOUNDED_INT_ARRAY; 
                   STATENUM, COMSTATE : in INTEGER); 

-- mktemplate - create a template entry based on a state, and connect the state
  --              to it

  procedure MKTEMPLATE(STATE              : in UNBOUNDED_INT_ARRAY; 
                       STATENUM, COMSTATE : in INTEGER); 

  -- mv2front - move proto queue element to front of queue

  procedure MV2FRONT(QELM : in INTEGER); 

  -- place_state - place a state into full speed transition table

  procedure PLACE_STATE(STATE              : in UNBOUNDED_INT_ARRAY; 
                        STATENUM, TRANSNUM : in INTEGER); 

  -- stack1 - save states with only one out-transition to be processed later

  procedure STACK1(STATENUM, SYM, NEXTSTATE, DEFLINK : in INTEGER); 

  -- tbldiff - compute differences between two state tables

  procedure TBLDIFF(STATE  : in UNBOUNDED_INT_ARRAY; 
                    PR     : in INTEGER; 
                    EXT    : out UNBOUNDED_INT_ARRAY; 
                    RESULT : out INTEGER); 

end TBLCMP; 
