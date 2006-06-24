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

-- TITLE equivalence class
-- AUTHOR: John Self (UCI)
-- DESCRIPTION finds equivalence classes so DFA will be smaller
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/ecsB.a,v 1.7 90/01/12 15:19:54 self Exp Locker: self $ 

with MISC_DEFS; 
with MISC; use MISC_DEFS; 
package body ECS is 

-- ccl2ecl - convert character classes to set of equivalence classes

  procedure CCL2ECL is 
    use MISC_DEFS; 
    ICH, NEWLEN, CCLP, CCLMEC : INTEGER; 
  begin
    for I in 1 .. LASTCCL loop

      -- we loop through each character class, and for each character
      -- in the class, add the character's equivalence class to the
      -- new "character" class we are creating.  Thus when we are all
      -- done, character classes will really consist of collections
      -- of equivalence classes
      NEWLEN := 0; 
      CCLP := CCLMAP(I); 

      for CCLS in 0 .. CCLLEN(I) - 1 loop
        ICH := CHARACTER'POS(CCLTBL(CCLP + CCLS)); 
        CCLMEC := ECGROUP(ICH); 
        if (CCLMEC > 0) then 
          CCLTBL(CCLP + NEWLEN) := CHARACTER'VAL(CCLMEC); 
          NEWLEN := NEWLEN + 1; 
        end if; 
      end loop; 

      CCLLEN(I) := NEWLEN; 
    end loop; 
  end CCL2ECL; 


  -- cre8ecs - associate equivalence class numbers with class members
  --  fwd is the forward linked-list of equivalence class members.  bck
  --  is the backward linked-list, and num is the number of class members.
  --  Returned is the number of classes.

  procedure CRE8ECS(FWD, BCK : in out C_SIZE_ARRAY; 
                    NUM      : in INTEGER; 
                    RESULT   : out INTEGER) is 
    J, NUMCL : INTEGER; 
  begin
    NUMCL := 0; 

    -- create equivalence class numbers.  From now on, abs( bck(x) )
    -- is the equivalence class number for object x.  If bck(x)
    -- is positive, then x is the representative of its equivalence
    -- class.
    for I in 1 .. NUM loop
      if (BCK(I) = NIL) then 
        NUMCL := NUMCL + 1; 
        BCK(I) := NUMCL; 
        J := FWD(I); 
        while (J /= NIL) loop
          BCK(J) :=  -NUMCL; 
          J := FWD(J); 
        end loop; 
      end if; 
    end loop; 
    RESULT := NUMCL; 
    return; 
  end CRE8ECS; 


  -- mkeccl - update equivalence classes based on character class xtions
  -- where ccls contains the elements of the character class, lenccl is the
  -- number of elements in the ccl, fwd is the forward link-list of equivalent
  -- characters, bck is the backward link-list, and llsiz size of the link-list

  procedure MKECCL(CCLS     : in out CHAR_ARRAY; 
                   LENCCL   : in INTEGER; 
                   FWD, BCK : in out UNBOUNDED_INT_ARRAY; 
                   LLSIZ    : in INTEGER) is 
    use MISC_DEFS, MISC; 
    CCLP, OLDEC, NEWEC, CCLM, I, J : INTEGER; 
    PROC_ARRAY                     : BOOLEAN_PTR; 
  begin

    -- note that it doesn't matter whether or not the character class is
    -- negated.  The same results will be obtained in either case.
    CCLP := CCLS'FIRST; 

    -- this array tells whether or not a character class has been processed.
    PROC_ARRAY := new BOOLEAN_ARRAY(CCLS'FIRST .. CCLS'LAST); 
    for CCL_INDEX in CCLS'FIRST .. CCLS'LAST loop
      PROC_ARRAY(CCL_INDEX) := FALSE; 
    end loop; 

    while (CCLP < LENCCL + CCLS'FIRST) loop
      CCLM := CHARACTER'POS(CCLS(CCLP)); 
      OLDEC := BCK(CCLM); 
      NEWEC := CCLM; 

      J := CCLP + 1; 

      I := FWD(CCLM); 
      while ((I /= NIL) and (I <= LLSIZ)) loop

        -- look for the symbol in the character class
        while ((J < LENCCL + CCLS'FIRST) and ((CCLS(J) <= CHARACTER'VAL(I)) or 
          PROC_ARRAY(J))) loop
          if (CCLS(J) = CHARACTER'VAL(I)) then 

            -- we found an old companion of cclm in the ccl.
            -- link it into the new equivalence class and flag it as
            -- having been processed
            BCK(I) := NEWEC; 
            FWD(NEWEC) := I; 
            NEWEC := I; 
            PROC_ARRAY(J) := TRUE; 

            -- set flag so we don't reprocess

            -- get next equivalence class member
            -- continue 2
            goto NEXT_PT; 
          end if; 
          J := J + 1; 
        end loop; 

        -- symbol isn't in character class.  Put it in the old equivalence
        -- class
        BCK(I) := OLDEC; 

        if (OLDEC /= NIL) then 
          FWD(OLDEC) := I; 
        end if; 

        OLDEC := I; 
        <<NEXT_PT>> I := FWD(I); 
      end loop; 

      if ((BCK(CCLM) /= NIL) or (OLDEC /= BCK(CCLM))) then 
        BCK(CCLM) := NIL; 
        FWD(OLDEC) := NIL; 
      end if; 

      FWD(NEWEC) := NIL; 

      -- find next ccl member to process
      CCLP := CCLP + 1; 

      while ((CCLP < LENCCL + CCLS'FIRST) and PROC_ARRAY(CCLP)) loop

        -- reset "doesn't need processing" flag
        PROC_ARRAY(CCLP) := FALSE; 
        CCLP := CCLP + 1; 
      end loop; 
    end loop; 
  exception
    when STORAGE_ERROR => 
      MISC.AFLEXFATAL("dynamic memory failure in mkeccl()"); 
  end MKECCL; 


  -- mkechar - create equivalence class for single character

  procedure MKECHAR(TCH      : in INTEGER; 
                    FWD, BCK : in out C_SIZE_ARRAY) is 
  begin

    -- if until now the character has been a proper subset of
    -- an equivalence class, break it away to create a new ec
    if (FWD(TCH) /= NIL) then 
      BCK(FWD(TCH)) := BCK(TCH); 
    end if; 

    if (BCK(TCH) /= NIL) then 
      FWD(BCK(TCH)) := FWD(TCH); 
    end if; 

    FWD(TCH) := NIL; 
    BCK(TCH) := NIL; 
  end MKECHAR; 

end ECS; 
