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

-- TITLE character classes routines
-- AUTHOR: John Self (UCI)
-- DESCRIPTION routines for character classes like [abc]
-- $Header: /dc/uc/self/arcadia/aflex/ada/src/RCS/cclB.a,v 1.7 1993/04/27 23:17:15 self Exp $ 

with MISC_DEFS, TEXT_IO, MISC, TSTRING; use MISC_DEFS, TEXT_IO; 
package body CCL is 

-- ccladd - add a single character to a ccl
  procedure CCLADD(CCLP : in INTEGER; 
                   CH   : in CHARACTER) is 
    IND, LEN, NEWPOS : INTEGER; 
  begin
    LEN := CCLLEN(CCLP); 
    IND := CCLMAP(CCLP); 

    -- check to see if the character is already in the ccl
    for I in 0 .. LEN - 1 loop
      if (CCLTBL(IND + I) = CH) then 
        return; 
      end if; 
    end loop; 

    NEWPOS := IND + LEN; 

    if (NEWPOS >= CURRENT_MAX_CCL_TBL_SIZE) then 
      CURRENT_MAX_CCL_TBL_SIZE := CURRENT_MAX_CCL_TBL_SIZE + 
        MAX_CCL_TBL_SIZE_INCREMENT; 

      NUM_REALLOCS := NUM_REALLOCS + 1; 

      REALLOCATE_CHARACTER_ARRAY(CCLTBL, CURRENT_MAX_CCL_TBL_SIZE); 
    end if; 

    CCLLEN(CCLP) := LEN + 1; 
    CCLTBL(NEWPOS) := CH; 

  end CCLADD; 

  -- cclinit - make an empty ccl

  function CCLINIT return INTEGER is 
  begin
    LASTCCL := LASTCCL + 1; 
    if (LASTCCL >= CURRENT_MAXCCLS) then 
      CURRENT_MAXCCLS := CURRENT_MAXCCLS + MAX_CCLS_INCREMENT; 

      NUM_REALLOCS := NUM_REALLOCS + 1; 

      REALLOCATE_INTEGER_ARRAY(CCLMAP, CURRENT_MAXCCLS); 
      REALLOCATE_INTEGER_ARRAY(CCLLEN, CURRENT_MAXCCLS); 
      REALLOCATE_INTEGER_ARRAY(CCLNG, CURRENT_MAXCCLS); 
    end if; 

    if (LASTCCL = 1) then 

      -- we're making the first ccl
      CCLMAP(LASTCCL) := 0; 

    else 

      -- the new pointer is just past the end of the last ccl.  Since
      -- the cclmap points to the \first/ character of a ccl, adding the
      -- length of the ccl to the cclmap pointer will produce a cursor
      -- to the first free space
      CCLMAP(LASTCCL) := CCLMAP(LASTCCL - 1) + CCLLEN(LASTCCL - 1); 
    end if; 

    CCLLEN(LASTCCL) := 0; 
    CCLNG(LASTCCL) := 0; 

    -- ccl's start out life un-negated
    return LASTCCL; 
  end CCLINIT; 

  -- cclnegate - negate a ccl

  procedure CCLNEGATE(CCLP : in INTEGER) is 
  begin
    CCLNG(CCLP) := 1; 
  end CCLNEGATE; 

  -- list_character_set - list the members of a set of characters in CCL form
  --
  -- writes to the given file a character-class representation of those
  -- characters present in the given set.  A character is present if it
  -- has a non-zero value in the set array.

  procedure LIST_CHARACTER_SET(F    : in FILE_TYPE; 
                               CSET : in C_SIZE_BOOL_ARRAY) is 
    I, START_CHAR : INTEGER; 
  begin
    TEXT_IO.PUT(F, '['); 

    I := 1; 
    while (I <= CSIZE) loop
      if (CSET(I)) then 
        START_CHAR := I; 

        TEXT_IO.PUT(F, ' '); 

        TSTRING.PUT(F, MISC.READABLE_FORM(CHARACTER'VAL(I))); 

        I := I + 1; 
        while ((I <= CSIZE) and then (CSET(I))) loop
          I := I + 1; 
        end loop; 

        if (I - 1 > START_CHAR) then 

          -- this was a run
          TEXT_IO.PUT(F, "-"); 
          TSTRING.PUT(F, MISC.READABLE_FORM(CHARACTER'VAL(I - 1))); 
        end if; 

        TEXT_IO.PUT(F, ' '); 
      end if; 
      I := I + 1; 
    end loop; 

    TEXT_IO.PUT(F, ']'); 
  end LIST_CHARACTER_SET; 
end CCL; 
