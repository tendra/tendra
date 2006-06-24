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

-- TITLE  miscellaneous aflex routines
-- AUTHOR: John Self (UCI)
-- DESCRIPTION
-- NOTES contains functions used in various places throughout aflex.
-- $Header: /dc/uc/self/arcadia/aflex/ada/src/RCS/miscB.a,v 1.22 1991/07/01 21:30:37 self Exp self $ 

with MISC_DEFS, TSTRING, TEXT_IO, MISC, MAIN_BODY; 
with INT_IO, CALENDAR, EXTERNAL_FILE_MANAGER; use MISC, MISC_DEFS, TEXT_IO, 
  EXTERNAL_FILE_MANAGER; 

package body MISC is 
  use TSTRING; 
  -- action_out - write the actions from the temporary file to lex.yy.c

  procedure ACTION_OUT is 
    BUF : VSTRING; 
  begin
    while (not TEXT_IO.END_OF_FILE(TEMP_ACTION_FILE)) loop
      TSTRING.GET_LINE(TEMP_ACTION_FILE, BUF); 
      if ((TSTRING.LEN(BUF) >= 2) and then ((CHAR(BUF, 1) = '%') and (CHAR(BUF, 
        2) = '%'))) then 
        exit; 
      else 
        TSTRING.PUT_LINE(BUF); 
      end if; 
    end loop; 
  end ACTION_OUT; 

  -- bubble - bubble sort an integer array in increasing order
  --
  -- description
  --   sorts the first n elements of array v and replaces them in
  --   increasing order.
  --
  -- passed
  --   v - the array to be sorted
  --   n - the number of elements of 'v' to be sorted

  procedure BUBBLE(V : in INT_PTR; 
                   N : in INTEGER) is 
    K : INTEGER; 
  begin
    for I in reverse 2 .. N loop
      for J in 1 .. I - 1 loop
        if (V(J) > V(J + 1)) then 

          -- compare
          K := V(J); 

          -- exchange
          V(J) := V(J + 1); 
          V(J + 1) := K; 
        end if; 
      end loop; 
    end loop; 
  end BUBBLE; 


  -- clower - replace upper-case letter to lower-case

  function CLOWER(C : in INTEGER) return INTEGER is 
  begin
    if (ISUPPER(CHARACTER'VAL(C))) then 
      return TOLOWER(C); 
    else 
      return C; 
    end if; 
  end CLOWER; 


  -- cshell - shell sort a character array in increasing order
  --
  -- description
  --   does a shell sort of the first n elements of array v.
  --
  -- passed
  --   v - array to be sorted
  --   n - number of elements of v to be sorted

  procedure CSHELL(V : in out CHAR_ARRAY; 
                   N : in INTEGER) is 
    GAP, J, JG  : INTEGER; 
    K           : CHARACTER; 
    LOWER_BOUND : INTEGER := V'FIRST; 
  begin
    GAP := N/2; 
    while GAP > 0 loop
      for I in GAP .. N - 1 loop
        J := I - GAP; 
        while (J >= 0) loop
          JG := J + GAP; 

          if (V(J + LOWER_BOUND) <= V(JG + LOWER_BOUND)) then 
            exit; 
          end if; 

          K := V(J + LOWER_BOUND); 
          V(J + LOWER_BOUND) := V(JG + LOWER_BOUND); 
          V(JG + LOWER_BOUND) := K; 
          J := J - GAP; 
        end loop; 
      end loop; 
      GAP := GAP/2; 
    end loop; 
  end CSHELL; 


  -- dataend - finish up a block of data declarations

  procedure DATAEND is 
  begin
    if (DATAPOS > 0) then 
      DATAFLUSH; 

      -- add terminator for initialization
      TEXT_IO.PUT_LINE("    ) ;"); 
      TEXT_IO.NEW_LINE; 

      DATALINE := 0; 
    end if; 
  end DATAEND; 


  -- dataflush - flush generated data statements

  procedure DATAFLUSH(FILE : in FILE_TYPE) is 
  begin
    TEXT_IO.NEW_LINE(FILE); 
    DATALINE := DATALINE + 1; 
    if (DATALINE >= NUMDATALINES) then 

      -- put out a blank line so that the table is grouped into
      -- large blocks that enable the user to find elements easily
      TEXT_IO.NEW_LINE(FILE); 
      DATALINE := 0; 
    end if; 

    -- reset the number of characters written on the current line
    DATAPOS := 0; 
  end DATAFLUSH; 

  procedure DATAFLUSH is 
  begin
    DATAFLUSH(CURRENT_OUTPUT); 
  end DATAFLUSH; 
  -- aflex_gettime - return current time

  function AFLEX_GETTIME return VSTRING is 
    use TSTRING, CALENDAR; 
    CURRENT_TIME                                            : TIME; 
    CURRENT_YEAR                                            : YEAR_NUMBER; 
    CURRENT_MONTH                                           : MONTH_NUMBER; 
    CURRENT_DAY                                             : DAY_NUMBER; 
    CURRENT_SECONDS                                         : DAY_DURATION; 
    MONTH_STRING, HOUR_STRING, MINUTE_STRING, SECOND_STRING : VSTRING; 
    HOUR, MINUTE, SECOND                                    : INTEGER; 
    SECONDS_PER_HOUR                                        : constant 
      DAY_DURATION := 3600.0; 
  begin
    CURRENT_TIME := CLOCK; 
    SPLIT(CURRENT_TIME, CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY, 
      CURRENT_SECONDS); 
    case CURRENT_MONTH is 
      when 1 => 
        MONTH_STRING := VSTR("Jan"); 
      when 2 => 
        MONTH_STRING := VSTR("Feb"); 
      when 3 => 
        MONTH_STRING := VSTR("Mar"); 
      when 4 => 
        MONTH_STRING := VSTR("Apr"); 
      when 5 => 
        MONTH_STRING := VSTR("May"); 
      when 6 => 
        MONTH_STRING := VSTR("Jun"); 
      when 7 => 
        MONTH_STRING := VSTR("Jul"); 
      when 8 => 
        MONTH_STRING := VSTR("Aug"); 
      when 9 => 
        MONTH_STRING := VSTR("Sep"); 
      when 10 => 
        MONTH_STRING := VSTR("Oct"); 
      when 11 => 
        MONTH_STRING := VSTR("Nov"); 
      when 12 => 
        MONTH_STRING := VSTR("Dec"); 
    end case; 

    HOUR := INTEGER(CURRENT_SECONDS)/INTEGER(SECONDS_PER_HOUR);
    MINUTE := INTEGER((CURRENT_SECONDS - (HOUR*SECONDS_PER_HOUR))/60); 
    SECOND := INTEGER(CURRENT_SECONDS - HOUR*SECONDS_PER_HOUR - MINUTE*60.0); 

    if (HOUR >= 10) then 
      HOUR_STRING := VSTR(INTEGER'IMAGE(HOUR)); 
    else 
      HOUR_STRING := VSTR("0" & INTEGER'IMAGE(HOUR)); 
    end if; 

    if (MINUTE >= 10) then 
      MINUTE_STRING := VSTR(INTEGER'IMAGE(MINUTE)(2 .. INTEGER'IMAGE(MINUTE)'
        LENGTH)); 
    else 
      MINUTE_STRING := VSTR("0" & INTEGER'IMAGE(MINUTE)(2 .. INTEGER'IMAGE(
        MINUTE)'LENGTH)); 
    end if; 

    if (SECOND >= 10) then 
      SECOND_STRING := VSTR(INTEGER'IMAGE(SECOND)(2 .. INTEGER'IMAGE(SECOND)'
        LENGTH)); 
    else 
      SECOND_STRING := VSTR("0" & INTEGER'IMAGE(SECOND)(2 .. INTEGER'IMAGE(
        SECOND)'LENGTH)); 
    end if; 

    return MONTH_STRING & VSTR(INTEGER'IMAGE(CURRENT_DAY)) & HOUR_STRING & ":"
      & MINUTE_STRING & ":" & SECOND_STRING & INTEGER'IMAGE(CURRENT_YEAR); 
  end AFLEX_GETTIME; 

  -- aflexerror - report an error message and terminate
  -- overloaded function, one for vstring, one for string.
  procedure AFLEXERROR(MSG : in VSTRING) is 
    use TEXT_IO; 
  begin
    TSTRING.PUT(STANDARD_ERROR, "aflex: " & MSG); 
    TEXT_IO.NEW_LINE(STANDARD_ERROR); 
    MAIN_BODY.AFLEXEND(1); 
  end AFLEXERROR; 

  procedure AFLEXERROR(MSG : in STRING) is 
    use TEXT_IO; 
  begin
    TEXT_IO.PUT(STANDARD_ERROR, "aflex: " & MSG); 
    TEXT_IO.NEW_LINE(STANDARD_ERROR); 
    MAIN_BODY.AFLEXEND(1); 
  end AFLEXERROR; 

  -- aflexfatal - report a fatal error message and terminate
  -- overloaded function, one for vstring, one for string.
  procedure AFLEXFATAL(MSG : in VSTRING) is 
    use TEXT_IO; 
  begin
    TSTRING.PUT(STANDARD_ERROR, "aflex: fatal internal error " & MSG); 
    TEXT_IO.NEW_LINE(STANDARD_ERROR); 
    MAIN_BODY.AFLEXEND(1); 
  end AFLEXFATAL; 

  procedure AFLEXFATAL(MSG : in STRING) is 
    use TEXT_IO; 
  begin
    TEXT_IO.PUT(STANDARD_ERROR, "aflex: fatal internal error " & MSG); 
    TEXT_IO.NEW_LINE(STANDARD_ERROR); 
    MAIN_BODY.AFLEXEND(1); 
  end AFLEXFATAL; 

  -- basename - find the basename of a file
  function BASENAME return VSTRING is 
    END_CHAR_POS : INTEGER := LEN(INFILENAME);
    START_CHAR_POS : INTEGER;
  begin
    if (END_CHAR_POS = 0) then 
      -- if reading standard input give everything this name
      return VSTR("aflex_yy"); 
    end if; 
    
    -- find out where the end of the basename is    
    while ((END_CHAR_POS >= 1) and then
           (CHAR(INFILENAME, END_CHAR_POS) /= '.')) loop
      END_CHAR_POS := END_CHAR_POS - 1; 
    end loop; 

    -- find out where the beginning of the basename is    
    START_CHAR_POS := END_CHAR_POS; -- start at the end of the basename
    while ((START_CHAR_POS > 1) and then
           (CHAR(INFILENAME, START_CHAR_POS) /= '/')) loop
    	START_CHAR_POS := START_CHAR_POS - 1; 
    end loop; 

    if (CHAR(INFILENAME, START_CHAR_POS) = '/') then
    	START_CHAR_POS := START_CHAR_POS + 1;
    end if;
    
    if (END_CHAR_POS >= 1) then 
      return SLICE(INFILENAME, START_CHAR_POS,  END_CHAR_POS - 1); 
    else 
      return INFILENAME; 
    end if; 
  end BASENAME; 

  -- line_directive_out - spit out a "# line" statement

  procedure LINE_DIRECTIVE_OUT(OUTPUT_FILE_NAME : in FILE_TYPE) is 
  begin
    if (GEN_LINE_DIRS) then 
      TEXT_IO.PUT(OUTPUT_FILE_NAME, "--# line "); 
      INT_IO.PUT(OUTPUT_FILE_NAME, LINENUM, 1); 
      TEXT_IO.PUT(OUTPUT_FILE_NAME, " """); 
      TSTRING.PUT(OUTPUT_FILE_NAME, INFILENAME); 
      TEXT_IO.PUT_LINE(OUTPUT_FILE_NAME, """"); 
    end if; 
  end LINE_DIRECTIVE_OUT; 


  procedure LINE_DIRECTIVE_OUT is 
  begin
    if (GEN_LINE_DIRS) then 
      TEXT_IO.PUT("--# line "); 
      INT_IO.PUT(LINENUM, 1); 
      TEXT_IO.PUT(" """); 
      TSTRING.PUT(INFILENAME); 
      TEXT_IO.PUT_LINE(""""); 
    end if; 
  end LINE_DIRECTIVE_OUT; 

  -- all_upper - returns true if a string is all upper-case
  function ALL_UPPER(STR : in VSTRING) return BOOLEAN is 
  begin
    for I in 1 .. LEN(STR) loop
      if (not ((CHAR(STR, I) >= 'A') and (CHAR(STR, I) <= 'Z'))) then 
        return FALSE; 
      end if; 
    end loop; 
    return TRUE; 
  end ALL_UPPER; 

  -- all_lower - returns true if a string is all lower-case
  function ALL_LOWER(STR : in VSTRING) return BOOLEAN is 
  begin
    for I in 1 .. LEN(STR) loop
      if (not ((CHAR(STR, I) >= 'a') and (CHAR(STR, I) <= 'z'))) then 
        return FALSE; 
      end if; 
    end loop; 
    return TRUE; 
  end ALL_LOWER; 

  -- mk2data - generate a data statement for a two-dimensional array
  --
  --  generates a data statement initializing the current 2-D array to "value"

  procedure MK2DATA(FILE  : in FILE_TYPE; 
                    VALUE : in INTEGER) is 
  begin

    if (DATAPOS >= NUMDATAITEMS) then 
      TEXT_IO.PUT(FILE, ','); 
      DATAFLUSH(FILE); 
    end if; 

    if (DATAPOS = 0) then 

      -- indent
      TEXT_IO.PUT(FILE, "    "); 
    else 
      TEXT_IO.PUT(FILE, ','); 
    end if; 

    DATAPOS := DATAPOS + 1; 

    INT_IO.PUT(FILE, VALUE, 5); 
  end MK2DATA; 

  procedure MK2DATA(VALUE : in INTEGER) is 
  begin
    MK2DATA(CURRENT_OUTPUT, VALUE); 
  end MK2DATA; 

  --
  --  generates a data statement initializing the current array element to
  --  "value"

  procedure MKDATA(VALUE : in INTEGER) is 
  begin
    if (DATAPOS >= NUMDATAITEMS) then 
      TEXT_IO.PUT(','); 
      DATAFLUSH; 
    end if; 

    if (DATAPOS = 0) then 

      -- indent
      TEXT_IO.PUT("    "); 
    else 
      TEXT_IO.PUT(','); 
    end if; 

    DATAPOS := DATAPOS + 1; 

    INT_IO.PUT(VALUE, 5); 
  end MKDATA; 


  -- myctoi - return the integer represented by a string of digits

  function MYCTOI(NUM_ARRAY : in VSTRING) return INTEGER is 
    TOTAL : INTEGER := 0; 
    CNT   : INTEGER := TSTRING.FIRST; 
  begin
    while (CNT <= TSTRING.LEN(NUM_ARRAY)) loop
      TOTAL := TOTAL*10; 
      TOTAL := TOTAL + CHARACTER'POS(CHAR(NUM_ARRAY, CNT)) - CHARACTER'POS('0')
        ; 
      CNT := CNT + 1; 
    end loop; 
    return TOTAL; 
  end MYCTOI; 


  -- myesc - return character corresponding to escape sequence

  function MYESC(ARR : in VSTRING) return CHARACTER is 
    use TEXT_IO; 
  begin
    case (CHAR(ARR, TSTRING.FIRST + 1)) is 
      when 'a' => 
        return ASCII.BEL; 
      when 'b' => 
        return ASCII.BS; 
      when 'f' => 
        return ASCII.FF; 
      when 'n' => 
        return ASCII.LF; 
      when 'r' => 
        return ASCII.CR; 
      when 't' => 
        return ASCII.HT; 
      when 'v' => 
        return ASCII.VT; 

      when '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' => 

        -- \<octal>
        declare
          C, ESC_CHAR : CHARACTER; 
          SPTR        : INTEGER := TSTRING.FIRST + 1; 
        begin
          ESC_CHAR := OTOI(TSTRING.SLICE(ARR, TSTRING.FIRST + 1, TSTRING.LEN(ARR
            ))); 
          if (ESC_CHAR = ASCII.NUL) then 
            MISC.SYNERR("escape sequence for null not allowed"); 
            return ASCII.SOH; 
          end if; 

          return ESC_CHAR; 
        end; 
      when others => 
        return CHAR(ARR, TSTRING.FIRST + 1); 
    end case; 
  end MYESC; 


  -- otoi - convert an octal digit string to an integer value

  function OTOI(STR : in VSTRING) return CHARACTER is 
    TOTAL : INTEGER := 0; 
    CNT   : INTEGER := TSTRING.FIRST; 
  begin
    while (CNT <= TSTRING.LEN(STR)) loop
      TOTAL := TOTAL*8; 
      TOTAL := TOTAL + CHARACTER'POS(CHAR(STR, CNT)) - CHARACTER'POS('0'); 
      CNT := CNT + 1; 
    end loop; 
    return CHARACTER'VAL(TOTAL); 
  end OTOI; 


  -- readable_form - return the the human-readable form of a character
  --
  -- The returned string is in static storage.

  function READABLE_FORM(C : in CHARACTER) return VSTRING is 
  begin
    if ((CHARACTER'POS(C) >= 0 and CHARACTER'POS(C) < 32) or (C = ASCII.DEL))
      then 
      case C is 
        when ASCII.LF => 
          return (VSTR("\n")); 

        -- Newline
        when ASCII.HT => 
          return (VSTR("\t")); 

        -- Horizontal Tab
        when ASCII.FF => 
          return (VSTR("\f")); 

        -- Form Feed
        when ASCII.CR => 
          return (VSTR("\r")); 

        -- Carriage Return
        when ASCII.BS => 
          return (VSTR("\b")); 

        -- Backspace
        when others => 
          return VSTR("\" & INTEGER'IMAGE(CHARACTER'POS(C))); 
      end case; 
    elsif (C = ' ') then 
      return VSTR("' '"); 
    else 
      return VSTR(C); 
    end if; 
  end READABLE_FORM; 

  -- transition_struct_out - output a yy_trans_info structure
  --
  -- outputs the yy_trans_info structure with the two elements, element_v and
  -- element_n.  Formats the output with spaces and carriage returns.

  procedure TRANSITION_STRUCT_OUT(ELEMENT_V, ELEMENT_N : in INTEGER) is 
  begin
    INT_IO.PUT(ELEMENT_V, 7); 
    TEXT_IO.PUT(", "); 
    INT_IO.PUT(ELEMENT_N, 5); 
    TEXT_IO.PUT(","); 
    DATAPOS := DATAPOS + TRANS_STRUCT_PRINT_LENGTH; 

    if (DATAPOS >= 75) then 
      TEXT_IO.NEW_LINE; 

      DATALINE := DATALINE + 1; 
      if (DATALINE mod 10 = 0) then 
        TEXT_IO.NEW_LINE; 
      end if; 

      DATAPOS := 0; 
    end if; 
  end TRANSITION_STRUCT_OUT; 

  function SET_YY_TRAILING_HEAD_MASK(SRC : in INTEGER) return INTEGER is 
  begin
    if (CHECK_YY_TRAILING_HEAD_MASK(SRC) = 0) then 
      return SRC + YY_TRAILING_HEAD_MASK; 
    else 
      return SRC; 
    end if; 
  end SET_YY_TRAILING_HEAD_MASK; 

  function CHECK_YY_TRAILING_HEAD_MASK(SRC : in INTEGER) return INTEGER is 
  begin
    if (SRC >= YY_TRAILING_HEAD_MASK) then 
      return YY_TRAILING_HEAD_MASK; 
    else 
      return 0; 
    end if; 
  end CHECK_YY_TRAILING_HEAD_MASK; 

  function SET_YY_TRAILING_MASK(SRC : in INTEGER) return INTEGER is 
  begin
    if (CHECK_YY_TRAILING_MASK(SRC) = 0) then 
      return SRC + YY_TRAILING_MASK; 
    else 
      return SRC; 
    end if; 
  end SET_YY_TRAILING_MASK; 

  function CHECK_YY_TRAILING_MASK(SRC : in INTEGER) return INTEGER is 
  begin

-- this test is whether both bits are on, or whether onlyy TRAIL_MASK is set
    if ((SRC >= YY_TRAILING_HEAD_MASK + YY_TRAILING_MASK) or ((
      CHECK_YY_TRAILING_HEAD_MASK(SRC) = 0) and (SRC >= YY_TRAILING_MASK)))
      then 
      return YY_TRAILING_MASK; 
    else 
      return 0; 
    end if; 
  end CHECK_YY_TRAILING_MASK; 

  function ISLOWER(C : in CHARACTER) return BOOLEAN is 
  begin
    return (C in 'a' .. 'z'); 
  end ISLOWER; 


  function ISUPPER(C : in CHARACTER) return BOOLEAN is 
  begin
    return (C in 'A' .. 'Z'); 
  end ISUPPER; 

  function ISDIGIT(C : in CHARACTER) return BOOLEAN is 
  begin
    return (C in '0' .. '9'); 
  end ISDIGIT; 

  function TOLOWER(C : in INTEGER) return INTEGER is 
  begin
    return C - CHARACTER'POS('A') + CHARACTER'POS('a'); 
  end TOLOWER; 

  procedure SYNERR(STR : in STRING) is 
    use TEXT_IO; 
  begin
    SYNTAXERROR := TRUE; 
    TEXT_IO.PUT(STANDARD_ERROR, "Syntax error at line "); 
    INT_IO.PUT(STANDARD_ERROR, LINENUM); 
    TEXT_IO.PUT(STANDARD_ERROR, STR); 
    TEXT_IO.NEW_LINE(STANDARD_ERROR); 
  end SYNERR; 

end MISC; 
