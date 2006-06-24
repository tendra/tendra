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
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/misc_defsB.a,v 1.5 90/01/12 15:20:21 self Exp Locker: self $ 

package body MISC_DEFS is 

-- returns true if an nfa state has an epsilon out-transition slot
-- that can be used.  This definition is currently not used.

  function FREE_EPSILON(STATE : in INTEGER) return BOOLEAN is 
  begin
    return ((TRANSCHAR(STATE) = SYM_EPSILON) and (TRANS2(STATE) = NO_TRANSITION)
      and (FINALST(STATE) /= STATE)); 
  end FREE_EPSILON; 

  -- returns true if an nfa state has an epsilon out-transition character
  -- and both slots are free

  function SUPER_FREE_EPSILON(STATE : in INTEGER) return BOOLEAN is 
  begin
    return ((TRANSCHAR(STATE) = SYM_EPSILON) and (TRANS1(STATE) = NO_TRANSITION)
      ); 
  end SUPER_FREE_EPSILON; 

  function ALLOCATE_INTEGER_ARRAY(SIZE : in INTEGER) return INT_PTR is 
  begin
    return new UNBOUNDED_INT_ARRAY(0 .. SIZE); 
  end ALLOCATE_INTEGER_ARRAY; 

  procedure REALLOCATE_INTEGER_ARRAY(ARR  : in out INT_PTR; 
                                     SIZE : in INTEGER) is 
    NEW_ARR : INT_PTR; 
  begin
    NEW_ARR := ALLOCATE_INTEGER_ARRAY(SIZE); 
    NEW_ARR(0 .. ARR'LAST) := ARR(0 .. ARR'LAST); 
    ARR := NEW_ARR; 
  end REALLOCATE_INTEGER_ARRAY; 

  procedure REALLOCATE_STATE_ENUM_ARRAY(ARR  : in out STATE_ENUM_PTR; 
                                        SIZE : in INTEGER) is 
    NEW_ARR : STATE_ENUM_PTR; 
  begin
    NEW_ARR := ALLOCATE_STATE_ENUM_ARRAY(SIZE); 
    NEW_ARR(0 .. ARR'LAST) := ARR(0 .. ARR'LAST); 
    ARR := NEW_ARR; 
  end REALLOCATE_STATE_ENUM_ARRAY; 

  procedure REALLOCATE_RULE_ENUM_ARRAY(ARR  : in out RULE_ENUM_PTR; 
                                       SIZE : in INTEGER) is 
    NEW_ARR : RULE_ENUM_PTR; 
  begin
    NEW_ARR := ALLOCATE_RULE_ENUM_ARRAY(SIZE); 
    NEW_ARR(0 .. ARR'LAST) := ARR(0 .. ARR'LAST); 
    ARR := NEW_ARR; 
  end REALLOCATE_RULE_ENUM_ARRAY; 

  function ALLOCATE_INT_PTR_ARRAY(SIZE : in INTEGER) return INT_STAR_PTR is 
  begin
    return new UNBOUNDED_INT_STAR_ARRAY(0 .. SIZE); 
  end ALLOCATE_INT_PTR_ARRAY; 

  function ALLOCATE_RULE_ENUM_ARRAY(SIZE : in INTEGER) return RULE_ENUM_PTR is 
  begin
    return new UNBOUNDED_RULE_ENUM_ARRAY(0 .. SIZE); 
  end ALLOCATE_RULE_ENUM_ARRAY; 

  function ALLOCATE_STATE_ENUM_ARRAY(SIZE : in INTEGER) return STATE_ENUM_PTR
    is 
  begin
    return new UNBOUNDED_STATE_ENUM_ARRAY(0 .. SIZE); 
  end ALLOCATE_STATE_ENUM_ARRAY; 

  function ALLOCATE_BOOLEAN_ARRAY(SIZE : in INTEGER) return BOOLEAN_PTR is 
  begin
    return new BOOLEAN_ARRAY(0 .. SIZE); 
  end ALLOCATE_BOOLEAN_ARRAY; 

  function ALLOCATE_VSTRING_ARRAY(SIZE : in INTEGER) return VSTRING_PTR is 
  begin
    return new UNBOUNDED_VSTRING_ARRAY(0 .. SIZE); 
  end ALLOCATE_VSTRING_ARRAY; 

  function ALLOCATE_DFAACC_UNION(SIZE : in INTEGER) return DFAACC_PTR is 
  begin
    return new UNBOUNDED_DFAACC_ARRAY(0 .. SIZE); 
  end ALLOCATE_DFAACC_UNION; 

  procedure REALLOCATE_INT_PTR_ARRAY(ARR  : in out INT_STAR_PTR; 
                                     SIZE : in INTEGER) is 
    NEW_ARR : INT_STAR_PTR; 
  begin
    NEW_ARR := ALLOCATE_INT_PTR_ARRAY(SIZE); 
    NEW_ARR(0 .. ARR'LAST) := ARR(0 .. ARR'LAST); 
    ARR := NEW_ARR; 
  end REALLOCATE_INT_PTR_ARRAY; 

  procedure REALLOCATE_CHARACTER_ARRAY(ARR  : in out CHAR_PTR; 
                                       SIZE : in INTEGER) is 
    NEW_ARR : CHAR_PTR; 
  begin
    NEW_ARR := ALLOCATE_CHARACTER_ARRAY(SIZE); 
    NEW_ARR(0 .. ARR'LAST) := ARR(0 .. ARR'LAST); 
    ARR := NEW_ARR; 
  end REALLOCATE_CHARACTER_ARRAY; 

  procedure REALLOCATE_VSTRING_ARRAY(ARR  : in out VSTRING_PTR; 
                                     SIZE : in INTEGER) is 
    NEW_ARR : VSTRING_PTR; 
  begin
    NEW_ARR := ALLOCATE_VSTRING_ARRAY(SIZE); 
    NEW_ARR(0 .. ARR'LAST) := ARR(0 .. ARR'LAST); 
    ARR := NEW_ARR; 
  end REALLOCATE_VSTRING_ARRAY; 

  function ALLOCATE_CHARACTER_ARRAY(SIZE : in INTEGER) return CHAR_PTR is 
  begin
    return new CHAR_ARRAY(0 .. SIZE); 
  end ALLOCATE_CHARACTER_ARRAY; 

  procedure REALLOCATE_DFAACC_UNION(ARR  : in out DFAACC_PTR; 
                                    SIZE : in INTEGER) is 
    NEW_ARR : DFAACC_PTR; 
  begin
    NEW_ARR := ALLOCATE_DFAACC_UNION(SIZE); 
    NEW_ARR(0 .. ARR'LAST) := ARR(0 .. ARR'LAST); 
    ARR := NEW_ARR; 
  end REALLOCATE_DFAACC_UNION; 

  procedure REALLOCATE_BOOLEAN_ARRAY(ARR  : in out BOOLEAN_PTR; 
                                     SIZE : in INTEGER) is 
    NEW_ARR : BOOLEAN_PTR; 
  begin
    NEW_ARR := ALLOCATE_BOOLEAN_ARRAY(SIZE); 
    NEW_ARR(0 .. ARR'LAST) := ARR(0 .. ARR'LAST); 
    ARR := NEW_ARR; 
  end REALLOCATE_BOOLEAN_ARRAY; 

  function MAX(X, Y : in INTEGER) return INTEGER is 
  begin
    if (X > Y) then 
      return X; 
    else 
      return Y; 
    end if; 
  end MAX; 

  function MIN(X, Y : in INTEGER) return INTEGER is 
  begin
    if (X < Y) then 
      return X; 
    else 
      return Y; 
    end if; 
  end MIN; 

end MISC_DEFS; 
