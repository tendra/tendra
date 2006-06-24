
-- UNIT: generic package body of VSTRINGS
--
-- FILES: vstring_body.a in publiclib
--        related file is vstring_spec.a in publiclib
--
-- PURPOSE:  An implementation of the abstract data type "variable-length
--           string."
--
-- DESCRIPTION:  This package provides a private type VSTRING.  VSTRING objects
--               are "strings" that have a length between zero and LAST, where
--               LAST is the generic parameter supplied in the package
--               instantiation.
--
--               In addition to the type VSTRING, a subtype and two constants
--               are declared.  The subtype STRINDEX is an index to a VSTRING,
--               The STRINDEX constant FIRST is an index to the first character
--               of the string, and the VSTRING constant NUL is a VSTRING of
--               length zero.  NUL is the default initial value of a VSTRING.
--
--               The following sets of functions, procedures, and operators
--               are provided as operations on the type VSTRING:
--
--               ATTRIBUTE FUNCTIONS:  LEN, MAX, STR, CHAR
--                 The attribute functions return the characteristics of
--                 a VSTRING.
--
--               COMPARISON OPERATORS: "=", "/=", "<", ">", "<=", ">="
--                 The comparison operators are the same as for the predefined
--                 type STRING.
--
--               INPUT/OUTPUT PROCEDURES: GET, GET_LINE, PUT, PUT_LINE
--                                        
--                 The input/output procedures are similar to those for the
--                 predefined type STRING, with the following exceptions:
--
--                   - GET has an optional parameter LENGTH, which indicates
--                     the number of characters to get (default is LAST).
--
--                   - GET_LINE does not have a parameter to return the length
--                     of the string (the LEN function should be used instead).
--
--               EXTRACTION FUNCTIONS: SLICE, SUBSTR, DELETE
--                 The SLICE function returns the slice of a VSTRING between
--                 two indices (equivalent to STR(X)(A .. B)).
--
--                 SUBSTR returns a substring of a VSTRING taken from a given
--                 index and extending a given length.
--
--                 The DELETE function returns the VSTRING which results from
--                 removing the slice between two indices.
--
--               EDITING FUNCTIONS: INSERT, APPEND, REPLACE
--                 The editing functions return the VSTRING which results from
--                 inserting, appending, or replacing at a given index with a
--                 VSTRING, STRING, or CHARACTER.  The index must be in the
--                 current range of the VSTRING; i.e., zero cannot be used.
--
--               CONCATENATION OPERATOR:  "&"
--                 The concatenation operator is the same as for the type
--                 STRING.  It should be used instead of APPEND when the
--                 APPEND would always be after the last character.
--
--               POSITION FUNCTIONS: INDEX, RINDEX
--                 The position functions return an index to the Nth occurrence
--                 of a VSTRING, STRING, or CHARACTER from the front or back
--                 of a VSTRING.  Zero is returned if the search is not
--                 successful.
--
--               CONVERSION FUNCTIONS AND OPERATOR: VSTR, CONVERT, "+"
--                 VSTR converts a STRING or a CHARACTER to a VSTRING.
--
--                 CONVERT is a generic function which can be instantiated to
--                 convert from any given variable-length string to another,
--                 provided the FROM type has a function equivelent to STR
--                 defined for it, and that the TO type has a function equiv-
--                 elent to VSTR defined for it.  This provides a means for
--                 converting between VSTRINGs declared in separate instant-
--                 iations of VSTRINGS.  When instantiating CONVERT for 
--                 VSTRINGs, the STR and VSTR functions are implicitly defined,
--                 provided that they have been made visible (by a use clause).
--
--                 Note:  CONVERT is NOT implicitly associated with the type 
--                 VSTRING declared in this package (since it would not be a
--                 derivable function (see RM 3.4(11))).
--
--                 Caution:  CONVERT cannot be instantiated directly with the
--                 names VSTR and STR, since the name of the subprogram being
--                 declared would hide the generic parameters with the same
--                 names (see RM 8.3(16)).  CONVERT can be instantiated with
--                 the operator "+", and any instantiation of CONVERT can
--                 subsequently be renamed VSTR or STR.
--
--                 Example:  Given two VSTRINGS instantiations X and Y:
--                   function "+" is new X.CONVERT(X.VSTRING, Y.VSTRING);
--                   function "+" is new X.CONVERT(Y.VSTRING, X.VSTRING);
--
--                   (Y.CONVERT could have been used in place of X.CONVERT)
--
--                   function VSTR(A : X.VSTRING) return Y.VSTRING renames "+";
--                   function VSTR(A : Y.VSTRING) return X.VSTRING renames "+";
--
--                 "+" is equivelent to VSTR.  It is supplied as a short-hand
--                 notation for the function.  The "+" operator cannot immed-
--                 iately follow the "&" operator; use ... & (+ ...) instead.
pragma PAGE;

--  DISCUSSION:
--
--	This package implements the type "variable-length string" (vstring)
--	using generics.  The alternative approaches are to use a discriminant 
--	record in which the discriminant controls the length of a STRING inside
--	the record, or a record containing an access type which points to a
--      string, which can be deallocated and reallocated when necessary.
--
--	Advantages of this package:
--	  * The other approaches force the vstring to be a limited private 
--          type.  Thus, their vstrings cannot appear on the left side of
--          the assignment operator; ie., their vstrings cannot be given
--          initial values or values by direct assignment.  This package
--          uses a private type; therefore, these things can be done.
--         
--	  * The other approach stores the vstring in a string whose length
--	    is determined dynamically.  This package uses a fixed length 
--          string.  This difference might be reflected in faster and more
--          consistent execution times (this has NOT been verified).
--
--	Disadvantages of this package:
--	  * Different instantiations must be used to declare vstrings with
--	    different maximum lengths (this may be desirable, since
--	    CONSTRAINT_ERROR will be raised if the maximum is exceeded).
--
--	  * A second declaration is required to give the type declared by
--	    the instantiation a name other than "VSTRING."
--
--	  * The storage required for a vstring is determined by the generic
--	    parameter LAST and not the actual length of its contents.  Thus,
--          each object is allocated the maximum amount of storage, regardless
--          of its actual size.
--
--  MISCELLANEOUS:
--     Constraint checking is done explicitly in the code; thus, it cannot
--     be suppressed.  On the other hand, constraint checking is not lost
--     if pragma suppress is supplied to the compilation (-S option) 
--     (The robustness of the explicit constraint checking has NOT been 
--     determined).
--
--     Compiling with the optimizer (-O option) may significantly reduce
--     the size (and possibly execution time) of the resulting executable.
--
--     Compiling an instantiation of VSTRINGS is roughly equivelent to
--     recompiling VSTRINGS.  Since this takes a significant amount of time,
--     and the instantiation does not depend on any other library units,
--     it is STRONGLY recommended that the instantiation be compiled
--     separately, and thus done only ONCE.
--
--  USAGE: with VSTRINGS;
--         package package_name is new VSTRINGS(maximum_length);
-- .......................................................................... --
pragma PAGE;

package body VSTRINGS is

  -- local declarations

  FILL_CHAR : constant CHARACTER := ASCII.NUL;

  procedure FORMAT(THE_STRING : in out VSTRING; OLDLEN : in STRINDEX := LAST) is
    -- fill the string with FILL_CHAR to null out old values

    begin -- FORMAT (Local Procedure)
      THE_STRING.VALUE(THE_STRING.LEN + 1 .. OLDLEN) := 
                                        (others => FILL_CHAR);
    end FORMAT;


  -- bodies of visible operations

  function LEN(FROM : VSTRING) return STRINDEX is

    begin -- LEN
      return(FROM.LEN);
    end LEN;


  function MAX(FROM : VSTRING) return STRINDEX is
    begin -- MAX
      return(LAST);
    end MAX;


  function STR(FROM : VSTRING) return STRING is
    begin -- STR
      return(FROM.VALUE(FIRST .. FROM.LEN));
    end STR;


  function CHAR(FROM : VSTRING; POSITION : STRINDEX := FIRST)
                 return CHARACTER is

    begin -- CHAR
      if POSITION not in FIRST .. FROM.LEN
        then raise CONSTRAINT_ERROR;
       end if;
      return(FROM.VALUE(POSITION));
    end CHAR;


  function "<" (LEFT: VSTRING; RIGHT: VSTRING) return BOOLEAN is
    begin -- "<"
      return(LEFT.VALUE < RIGHT.VALUE);
    end "<";


  function ">" (LEFT: VSTRING; RIGHT: VSTRING) return BOOLEAN is
    begin -- ">"
      return(LEFT.VALUE > RIGHT.VALUE);
    end ">";


  function "<=" (LEFT: VSTRING; RIGHT: VSTRING) return BOOLEAN is
    begin -- "<="
      return(LEFT.VALUE <= RIGHT.VALUE);
    end "<=";


  function ">=" (LEFT: VSTRING; RIGHT: VSTRING) return BOOLEAN is
    begin -- ">="
      return(LEFT.VALUE >= RIGHT.VALUE);
    end ">=";


  procedure PUT(FILE : in FILE_TYPE; ITEM : in VSTRING) is
    begin -- PUT
      PUT(FILE, ITEM.VALUE(FIRST .. ITEM.LEN));
    end PUT;

  procedure Put(ITEM : in VSTRING) is
    begin -- PUT
      PUT(ITEM.VALUE(FIRST .. ITEM.LEN));
    end PUT;


  procedure PUT_LINE(FILE : in FILE_TYPE; ITEM : in VSTRING) is
    begin -- PUT_LINE
      PUT_LINE(FILE, ITEM.VALUE(FIRST .. ITEM.LEN));
    end PUT_LINE;

  procedure PUT_LINE(ITEM : in VSTRING) is
    begin -- PUT_LINE
      PUT_LINE(ITEM.VALUE(FIRST .. ITEM.LEN));
    end PUT_LINE;


  procedure GET(FILE : in FILE_TYPE; ITEM : out VSTRING;
                LENGTH : in STRINDEX := LAST) is
    begin -- GET
      if LENGTH not in FIRST .. LAST
        then raise CONSTRAINT_ERROR;
       end if;

      ITEM := NUL;
      for INDEX in FIRST .. LENGTH loop
        GET(FILE, ITEM.VALUE(INDEX));
        ITEM.LEN := INDEX;
       end loop;
    end GET;

  procedure GET(ITEM : out VSTRING; LENGTH : in STRINDEX := LAST) is
    begin -- GET
      if LENGTH not in FIRST .. LAST
        then raise CONSTRAINT_ERROR;
       end if;

      ITEM := NUL;
      for INDEX in FIRST .. LENGTH loop
        GET(ITEM.VALUE(INDEX));
        ITEM.LEN := INDEX;
       end loop;
    end GET;


  procedure GET_LINE(FILE : in FILE_TYPE; ITEM : in out VSTRING) is

    OLDLEN : constant STRINDEX := ITEM.LEN;

    begin -- GET_LINE
      GET_LINE(FILE, ITEM.VALUE, ITEM.LEN);
      FORMAT(ITEM, OLDLEN);
    end GET_LINE;
       
  procedure GET_LINE(ITEM : in out VSTRING) is

    OLDLEN : constant STRINDEX := ITEM.LEN;

    begin -- GET_LINE
      GET_LINE(ITEM.VALUE, ITEM.LEN);
      FORMAT(ITEM, OLDLEN);
    end GET_LINE;


  function SLICE(FROM : VSTRING; FRONT, BACK : STRINDEX) return VSTRING is

    begin -- SLICE
      if ((FRONT not in FIRST .. FROM.LEN) or else 
         (BACK not in FIRST .. FROM.LEN)) and then FRONT <= BACK
        then raise CONSTRAINT_ERROR;
       end if;

      return(Vstr(FROM.VALUE(FRONT .. BACK)));
    end SLICE;


  function SUBSTR(FROM : VSTRING; START, LENGTH : STRINDEX) return VSTRING is

    begin -- SUBSTR
      if (START not in FIRST .. FROM.LEN) or else
         ((START + LENGTH - 1 not in FIRST .. FROM.LEN)
          and then (LENGTH > 0))
        then raise CONSTRAINT_ERROR;
       end if;

      return(Vstr(FROM.VALUE(START .. START + LENGTH -1)));
    end SUBSTR;


  function DELETE(FROM : VSTRING; FRONT, BACK : STRINDEX) return VSTRING is

    TEMP : VSTRING := FROM;

    begin -- DELETE
      if ((FRONT not in FIRST .. FROM.LEN) or else
         (BACK not in FIRST .. FROM.LEN)) and then FRONT <= BACK
        then raise CONSTRAINT_ERROR;
       end if;

      if FRONT > BACK then return(FROM); end if;
      TEMP.LEN := FROM.LEN - (BACK - FRONT) - 1;

      TEMP.VALUE(FRONT .. TEMP.LEN) := FROM.VALUE(BACK + 1 .. FROM.LEN);
      FORMAT(TEMP, FROM.LEN);
      return(TEMP);
    end DELETE;


  function INSERT(TARGET: VSTRING; ITEM: VSTRING;
                  POSITION : STRINDEX := FIRST) return VSTRING is

    TEMP : VSTRING;

    begin -- INSERT
      if POSITION not in FIRST .. TARGET.LEN
        then raise CONSTRAINT_ERROR;
       end if;

      if TARGET.LEN + ITEM.LEN > LAST
        then raise CONSTRAINT_ERROR;
        else TEMP.LEN := TARGET.LEN + ITEM.LEN;
       end if;

      TEMP.VALUE(FIRST .. POSITION - 1) := TARGET.VALUE(FIRST .. POSITION - 1);
      TEMP.VALUE(POSITION .. (POSITION + ITEM.LEN - 1)) :=
        ITEM.VALUE(FIRST .. ITEM.LEN);
      TEMP.VALUE((POSITION + ITEM.LEN) .. TEMP.LEN) :=
        TARGET.VALUE(POSITION .. TARGET.LEN);

      return(TEMP);
    end INSERT;

  function INSERT(TARGET: VSTRING; ITEM: STRING;
                  POSITION : STRINDEX := FIRST) return VSTRING is
    begin -- INSERT
      return INSERT(TARGET, VSTR(ITEM), POSITION);
    end INSERT;
  
  function INSERT(TARGET: VSTRING; ITEM: CHARACTER;
                  POSITION : STRINDEX := FIRST) return VSTRING is
    begin -- INSERT
      return INSERT(TARGET, VSTR(ITEM), POSITION);
    end INSERT;


  function APPEND(TARGET: VSTRING; ITEM: VSTRING; POSITION : STRINDEX)
                  return VSTRING is

    TEMP : VSTRING;
    POS : STRINDEX := POSITION;

    begin -- APPEND
      if POSITION not in FIRST .. TARGET.LEN
        then raise CONSTRAINT_ERROR;
       end if;

      if TARGET.LEN + ITEM.LEN > LAST
        then raise CONSTRAINT_ERROR;
        else TEMP.LEN := TARGET.LEN + ITEM.LEN;
       end if;

      TEMP.VALUE(FIRST .. POS) := TARGET.VALUE(FIRST .. POS);
      TEMP.VALUE(POS + 1 .. (POS + ITEM.LEN)) := ITEM.VALUE(FIRST .. ITEM.LEN);
      TEMP.VALUE((POS + ITEM.LEN + 1) .. TEMP.LEN) :=
        TARGET.VALUE(POS + 1 .. TARGET.LEN);

      return(TEMP);
    end APPEND;

  function APPEND(TARGET: VSTRING; ITEM: STRING; POSITION : STRINDEX)
                  return VSTRING is
    begin -- APPEND
      return APPEND(TARGET, VSTR(ITEM), POSITION);
    end APPEND;

  function APPEND(TARGET: VSTRING; ITEM: CHARACTER; POSITION : STRINDEX)
                  return VSTRING is
    begin -- APPEND
      return APPEND(TARGET, VSTR(ITEM), POSITION);
    end APPEND;


  function APPEND(TARGET: VSTRING; ITEM: VSTRING) return VSTRING is
    begin -- APPEND
      return(APPEND(TARGET, ITEM, TARGET.LEN));
    end APPEND;

  function APPEND(TARGET: VSTRING; ITEM: STRING) return VSTRING is
    begin -- APPEND
      return(APPEND(TARGET, VSTR(ITEM), TARGET.LEN));
    end APPEND;

  function APPEND(TARGET: VSTRING; ITEM: CHARACTER) return VSTRING is
    begin -- APPEND
      return(APPEND(TARGET, VSTR(ITEM), TARGET.LEN));
    end APPEND;


  function REPLACE(TARGET: VSTRING; ITEM: VSTRING;
                   POSITION : STRINDEX := FIRST) return VSTRING is

    TEMP : VSTRING;

    begin -- REPLACE
      if POSITION not in FIRST .. TARGET.LEN
        then raise CONSTRAINT_ERROR;
       end if;

      if POSITION + ITEM.LEN - 1 <= TARGET.LEN
        then TEMP.LEN := TARGET.LEN;
        elsif POSITION + ITEM.LEN - 1 > LAST
          then raise CONSTRAINT_ERROR;
          else TEMP.LEN := POSITION + ITEM.LEN - 1;
       end if;

      TEMP.VALUE(FIRST .. POSITION - 1) := TARGET.VALUE(FIRST .. POSITION - 1);
      TEMP.VALUE(POSITION .. (POSITION + ITEM.LEN - 1)) := 
        ITEM.VALUE(FIRST .. ITEM.LEN);
      TEMP.VALUE((POSITION + ITEM.LEN) .. TEMP.LEN) :=
        TARGET.VALUE((POSITION + ITEM.LEN) .. TARGET.LEN);

      return(TEMP);
    end REPLACE;

  function REPLACE(TARGET: VSTRING; ITEM: STRING;
                   POSITION : STRINDEX := FIRST) return VSTRING is
    begin -- REPLACE
      return REPLACE(TARGET, VSTR(ITEM), POSITION);
    end REPLACE;

  function REPLACE(TARGET: VSTRING; ITEM: CHARACTER;
                   POSITION : STRINDEX := FIRST) return VSTRING is
    begin -- REPLACE
      return REPLACE(TARGET, VSTR(ITEM), POSITION);
    end REPLACE;


  function "&"(LEFT:VSTRING; RIGHT : VSTRING) return VSTRING is

    TEMP : VSTRING;

    begin -- "&"
      if LEFT.LEN + RIGHT.LEN > LAST
        then raise CONSTRAINT_ERROR;
        else TEMP.LEN := LEFT.LEN + RIGHT.LEN;
       end if;

      TEMP.VALUE(FIRST .. TEMP.LEN) := LEFT.VALUE(FIRST .. LEFT.LEN) &
        RIGHT.VALUE(FIRST .. RIGHT.LEN);
      return(TEMP);
    end "&";

  function "&"(LEFT:VSTRING; RIGHT : STRING) return VSTRING is
    begin -- "&"
      return LEFT & VSTR(RIGHT);
    end "&";

  function "&"(LEFT:VSTRING; RIGHT : CHARACTER) return VSTRING is
    begin -- "&"
      return LEFT & VSTR(RIGHT);
    end "&";

  function "&"(LEFT : STRING; RIGHT : VSTRING) return VSTRING is
    begin -- "&"
      return VSTR(LEFT) & RIGHT;
    end "&";

  function "&"(LEFT : CHARACTER; RIGHT : VSTRING) return VSTRING is
    begin -- "&"
      return VSTR(LEFT) & RIGHT;
    end "&";


  Function INDEX(WHOLE : VSTRING; PART : VSTRING; OCCURRENCE : NATURAL := 1)
                 return STRINDEX is

    NOT_FOUND : constant NATURAL := 0;
    INDEX : NATURAL := FIRST;
    COUNT : NATURAL := 0;

    begin -- INDEX
      if PART = NUL then return(NOT_FOUND); -- by definition
        end if;

      while INDEX + PART.LEN - 1 <= WHOLE.LEN and then COUNT < OCCURRENCE loop
        if WHOLE.VALUE(INDEX .. PART.LEN + INDEX - 1) =
           PART.VALUE(1 .. PART.LEN)
          then COUNT := COUNT + 1;
         end if;
        INDEX := INDEX + 1;
       end loop;

      if COUNT = OCCURRENCE
        then return(INDEX - 1);
        else return(NOT_FOUND);
       end if;
    end INDEX;

  Function INDEX(WHOLE : VSTRING; PART : STRING; OCCURRENCE : NATURAL := 1)
                 return STRINDEX is

    begin -- Index
      return(Index(WHOLE, VSTR(PART), OCCURRENCE));
    end INDEX;


  Function INDEX(WHOLE : VSTRING; PART : CHARACTER; OCCURRENCE : NATURAL := 1)
                 return STRINDEX is

    begin -- Index
      return(Index(WHOLE, VSTR(PART), OCCURRENCE));
    end INDEX;


  function RINDEX(WHOLE: VSTRING; PART:VSTRING; OCCURRENCE:NATURAL := 1) 
                 return STRINDEX is

    NOT_FOUND : constant NATURAL := 0;
    INDEX : INTEGER := WHOLE.LEN - (PART.LEN -1);
    COUNT : NATURAL := 0;

    begin -- RINDEX
      if PART = NUL then return(NOT_FOUND); -- by definition
        end if;

      while INDEX >= FIRST and then COUNT < OCCURRENCE loop
        if WHOLE.VALUE(INDEX .. PART.LEN + INDEX - 1) =
           PART.VALUE(1 .. PART.LEN)
          then COUNT := COUNT + 1;
         end if;
        INDEX := INDEX - 1;
       end loop;

      if COUNT = OCCURRENCE
        then
          if COUNT > 0
            then return(INDEX + 1);
            else return(NOT_FOUND);
           end if;
        else return(NOT_FOUND);
       end if;
    end RINDEX;

  Function RINDEX(WHOLE : VSTRING; PART : STRING; OCCURRENCE : NATURAL := 1)
                 return STRINDEX is

    begin -- Rindex
      return(RINDEX(WHOLE, VSTR(PART), OCCURRENCE));
    end RINDEX;


  Function RINDEX(WHOLE : VSTRING; PART : CHARACTER; OCCURRENCE : NATURAL := 1)
                 return STRINDEX is

    begin -- Rindex
      return(RINDEX(WHOLE, VSTR(PART), OCCURRENCE));
    end RINDEX;


  function VSTR(FROM : CHARACTER) return VSTRING is
    
    TEMP : VSTRING;

    begin -- VSTR
      if LAST < 1
        then raise CONSTRAINT_ERROR;
        else TEMP.LEN := 1;
       end if;

      TEMP.VALUE(FIRST) := FROM;
      return(TEMP);
    end VSTR;


  function VSTR(FROM : STRING) return VSTRING is

    TEMP : VSTRING;

    begin -- VSTR
      if FROM'LENGTH > LAST
        then raise CONSTRAINT_ERROR;
        else TEMP.LEN := FROM'LENGTH;
       end if;

      TEMP.VALUE(FIRST .. FROM'LENGTH) := FROM;
      return(TEMP);
    end VSTR;

  Function "+" (FROM : STRING) return VSTRING is
    begin -- "+"
      return(VSTR(FROM));
    end "+";

  Function "+" (FROM : CHARACTER) return VSTRING is
    begin
     return(VSTR(FROM));
    end "+";


  function CONVERT(X : FROM) return TO is

    begin -- CONVERT
      return(VSTR(STR(X)));
    end CONVERT;   
end VSTRINGS;
-- .......................................................................... --
--
-- DISTRIBUTION AND COPYRIGHT:
--                                                           
-- This software is released to the Public Domain (note:
--   software released to the Public Domain is not subject
--   to copyright protection).
-- Restrictions on use or distribution:  NONE
--                                                           
-- DISCLAIMER:
--                                                           
-- This software and its documentation are provided "AS IS" and
-- without any expressed or implied warranties whatsoever.
-- No warranties as to performance, merchantability, or fitness
-- for a particular purpose exist.
--
-- Because of the diversity of conditions and hardware under
-- which this software may be used, no warranty of fitness for
-- a particular purpose is offered.  The user is advised to
-- test the software thoroughly before relying on it.  The user
-- must assume the entire risk and liability of using this
-- software.
--
-- In no event shall any person or organization of people be
-- held responsible for any direct, indirect, consequential
-- or inconsequential damages or lost profits.
