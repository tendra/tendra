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

-- TITLE main body
-- AUTHOR: John Self (UCI)
-- DESCRIPTION driver routines for aflex.  Calls drivers for all
-- high level routines from other packages.
-- $Header: /dc/uc/self/arcadia/aflex/ada/src/RCS/mainB.a,v 1.26 1992/12/29 22:46:15 self Exp self $ 

with MISC_DEFS, MISC, COMMAND_LINE_INTERFACE, DFA, ECS, GEN, TEXT_IO, PARSER; 
with MAIN_BODY, TSTRING, PARSE_TOKENS, SKELETON_MANAGER, EXTERNAL_FILE_MANAGER; 
with EXTERNAL_FILE_MANAGER, INT_IO; use MISC_DEFS, COMMAND_LINE_INTERFACE, 
  TSTRING, EXTERNAL_FILE_MANAGER; 

package body MAIN_BODY is 
  OUTFILE_CREATED    : BOOLEAN := FALSE; 
  AFLEX_VERSION      : CONSTANT STRING := "1.4a"; 
  STARTTIME, ENDTIME : VSTRING; 

  -- aflexend - terminate aflex
  --
  -- note
  --    This routine does not return.

  procedure AFLEXEND(STATUS : in INTEGER) is 
    use TEXT_IO; 
    TBLSIZ : INTEGER; 
  begin
    TERMINATION_STATUS := STATUS; 

    TEXT_IO.PUT_LINE("end " & TSTRING.STR(MISC.BASENAME) &";");

    -- we'll return this value of the OS.
    if (IS_OPEN(SKELFILE)) then 
      CLOSE(SKELFILE); 
    end if; 

    if (IS_OPEN(TEMP_ACTION_FILE)) then 
      DELETE(TEMP_ACTION_FILE); 
    end if; 

    if (IS_OPEN(DEF_FILE)) then 
      DELETE(DEF_FILE); 
    end if; 

    if (BACKTRACK_REPORT) then 
      if (NUM_BACKTRACKING = 0) then 
        TEXT_IO.PUT_LINE(BACKTRACK_FILE, "No backtracking."); 
      else 
        if (FULLTBL) then 
          INT_IO.PUT(BACKTRACK_FILE, NUM_BACKTRACKING, 0); 
          TEXT_IO.PUT_LINE(BACKTRACK_FILE, 
            " backtracking (non-accepting) states."); 
        else 
          TEXT_IO.PUT_LINE(BACKTRACK_FILE, "Compressed tables always backtrack."
            ); 
        end if; 
      end if; 

      CLOSE(BACKTRACK_FILE); 
    end if; 

    if (PRINTSTATS) then 
      ENDTIME := MISC.AFLEX_GETTIME; 

      TEXT_IO.PUT_LINE(STANDARD_ERROR, "aflex version " & AFLEX_VERSION & 
        " usage statistics:"); 

      TSTRING.PUT_LINE(STANDARD_ERROR, "  started at " & STARTTIME & 
        ", finished at " & ENDTIME); 
      TEXT_IO.PUT(STANDARD_ERROR, "  "); 
      INT_IO.PUT(STANDARD_ERROR, LASTNFA, 0); 
      TEXT_IO.PUT(STANDARD_ERROR, '/'); 
      INT_IO.PUT(STANDARD_ERROR, CURRENT_MNS, 0); 
      TEXT_IO.PUT_LINE(STANDARD_ERROR, "  NFA states"); 

      TEXT_IO.PUT(STANDARD_ERROR, "  "); 
      INT_IO.PUT(STANDARD_ERROR, LASTDFA, 0); 
      TEXT_IO.PUT(STANDARD_ERROR, '/'); 
      INT_IO.PUT(STANDARD_ERROR, CURRENT_MAX_DFAS, 0); 
      TEXT_IO.PUT(STANDARD_ERROR, " DFA states ("); 
      INT_IO.PUT(STANDARD_ERROR, TOTNST, 0); 
      TEXT_IO.PUT(STANDARD_ERROR, "  words)"); 

      TEXT_IO.PUT(STANDARD_ERROR, "  "); 
      INT_IO.PUT(STANDARD_ERROR, NUM_RULES - 1, 0); 

      -- - 1 for def. rule
      TEXT_IO.PUT_LINE(STANDARD_ERROR, "  rules"); 

      if (NUM_BACKTRACKING = 0) then 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, "  No backtracking"); 
      else 
        if (FULLTBL) then 
          TEXT_IO.PUT(STANDARD_ERROR, "  "); 
          INT_IO.PUT(STANDARD_ERROR, NUM_BACKTRACKING, 0); 
          TEXT_IO.PUT_LINE(STANDARD_ERROR, 
            "  backtracking (non-accepting) states"); 
        else 
          TEXT_IO.PUT_LINE(STANDARD_ERROR, " compressed tables always backtrack"
            ); 
        end if; 
      end if; 

      if (BOL_NEEDED) then 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, "  Beginning-of-line patterns used"); 
      end if; 

      TEXT_IO.PUT(STANDARD_ERROR, "  "); 
      INT_IO.PUT(STANDARD_ERROR, LASTSC, 0); 
      TEXT_IO.PUT(STANDARD_ERROR, '/'); 
      INT_IO.PUT(STANDARD_ERROR, CURRENT_MAX_SCS, 0); 
      TEXT_IO.PUT_LINE(STANDARD_ERROR, " start conditions"); 

      TEXT_IO.PUT(STANDARD_ERROR, "  "); 
      INT_IO.PUT(STANDARD_ERROR, NUMEPS, 0); 
      TEXT_IO.PUT(STANDARD_ERROR, " epsilon states, "); 
      INT_IO.PUT(STANDARD_ERROR, EPS2, 0); 
      TEXT_IO.PUT_LINE(STANDARD_ERROR, "  double epsilon states"); 

      if (LASTCCL = 0) then 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, "  no character classes"); 
      else 
        TEXT_IO.PUT(STANDARD_ERROR, "  "); 
        INT_IO.PUT(STANDARD_ERROR, LASTCCL, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, '/'); 
        INT_IO.PUT(STANDARD_ERROR, CURRENT_MAXCCLS, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, " character classes needed "); 
        INT_IO.PUT(STANDARD_ERROR, CCLMAP(LASTCCL) + CCLLEN(LASTCCL), 0); 
        TEXT_IO.PUT(STANDARD_ERROR, '/'); 
        INT_IO.PUT(STANDARD_ERROR, CURRENT_MAX_CCL_TBL_SIZE, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, " words of storage, "); 
        INT_IO.PUT(STANDARD_ERROR, CCLREUSE, 0); 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, "reused"); 
      end if; 

      TEXT_IO.PUT(STANDARD_ERROR, "  "); 
      INT_IO.PUT(STANDARD_ERROR, NUMSNPAIRS, 0); 
      TEXT_IO.PUT_LINE(STANDARD_ERROR, " state/nextstate pairs created"); 

      TEXT_IO.PUT(STANDARD_ERROR, "  "); 
      INT_IO.PUT(STANDARD_ERROR, NUMUNIQ, 0); 
      TEXT_IO.PUT(STANDARD_ERROR, '/'); 
      INT_IO.PUT(STANDARD_ERROR, NUMDUP, 0); 
      TEXT_IO.PUT_LINE(STANDARD_ERROR, " unique/duplicate transitions"); 

      if (FULLTBL) then 
        TBLSIZ := LASTDFA*NUMECS; 
        TEXT_IO.PUT(STANDARD_ERROR, "  "); 
        INT_IO.PUT(STANDARD_ERROR, TBLSIZ, 0); 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, " table entries"); 
      else 
        TBLSIZ := 2*(LASTDFA + NUMTEMPS) + 2*TBLEND; 

        TEXT_IO.PUT(STANDARD_ERROR, "  "); 
        INT_IO.PUT(STANDARD_ERROR, LASTDFA + NUMTEMPS, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, '/'); 
        INT_IO.PUT(STANDARD_ERROR, CURRENT_MAX_DFAS, 0); 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, " base-def entries created"); 

        TEXT_IO.PUT(STANDARD_ERROR, "  "); 
        INT_IO.PUT(STANDARD_ERROR, TBLEND, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, '/'); 
        INT_IO.PUT(STANDARD_ERROR, CURRENT_MAX_XPAIRS, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, " (peak "); 
        INT_IO.PUT(STANDARD_ERROR, PEAKPAIRS, 0); 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, ") nxt-chk entries created"); 

        TEXT_IO.PUT(STANDARD_ERROR, "  "); 
        INT_IO.PUT(STANDARD_ERROR, NUMTEMPS*NUMMECS, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, '/'); 
        INT_IO.PUT(STANDARD_ERROR, CURRENT_MAX_TEMPLATE_XPAIRS, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, " (peak "); 
        INT_IO.PUT(STANDARD_ERROR, NUMTEMPS*NUMECS, 0); 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, ") template nxt-chk entries created"); 

        TEXT_IO.PUT(STANDARD_ERROR, "  "); 
        INT_IO.PUT(STANDARD_ERROR, NUMMT, 0); 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, " empty table entries"); 
        TEXT_IO.PUT(STANDARD_ERROR, "  "); 
        INT_IO.PUT(STANDARD_ERROR, NUMPROTS, 0); 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, " protos created"); 
        TEXT_IO.PUT(STANDARD_ERROR, "  "); 
        INT_IO.PUT(STANDARD_ERROR, NUMTEMPS, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, " templates created, "); 
        INT_IO.PUT(STANDARD_ERROR, TMPUSES, 0); 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, "uses"); 
      end if; 

      if (USEECS) then 
        TBLSIZ := TBLSIZ + CSIZE; 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, "  "); 
        INT_IO.PUT(STANDARD_ERROR, NUMECS, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, '/'); 
        INT_IO.PUT(STANDARD_ERROR, CSIZE, 0); 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, " equivalence classes created"); 
      end if; 

      if (USEMECS) then 
        TBLSIZ := TBLSIZ + NUMECS; 
        TEXT_IO.PUT(STANDARD_ERROR, "  "); 
        INT_IO.PUT(STANDARD_ERROR, NUMMECS, 0); 
        TEXT_IO.PUT(STANDARD_ERROR, '/'); 
        INT_IO.PUT(STANDARD_ERROR, CSIZE, 0); 
        TEXT_IO.PUT_LINE(STANDARD_ERROR, " meta-equivalence classes created"); 
      end if; 

      TEXT_IO.PUT(STANDARD_ERROR, "  "); 
      INT_IO.PUT(STANDARD_ERROR, HSHCOL, 0); 
      TEXT_IO.PUT(STANDARD_ERROR, " ("); 
      INT_IO.PUT(STANDARD_ERROR, HSHSAVE, 0); 
      TEXT_IO.PUT_LINE(STANDARD_ERROR, " saved) hash collisions, "); 
      INT_IO.PUT(STANDARD_ERROR, DFAEQL, 0); 
      TEXT_IO.PUT_LINE(STANDARD_ERROR, " DFAs equal"); 

      TEXT_IO.PUT(STANDARD_ERROR, "  "); 
      INT_IO.PUT(STANDARD_ERROR, NUM_REALLOCS, 0); 
      TEXT_IO.PUT_LINE(STANDARD_ERROR, " sets of reallocations needed"); 
      TEXT_IO.PUT(STANDARD_ERROR, "  "); 
      INT_IO.PUT(STANDARD_ERROR, TBLSIZ, 0); 
      TEXT_IO.PUT_LINE(STANDARD_ERROR, " total table entries needed"); 
    end if; 

    if (STATUS /= 0) then 
      raise AFLEX_TERMINATE; 
    end if; 
  end AFLEXEND; 

  -- aflexinit - initialize aflex

  procedure AFLEXINIT is 
    use TEXT_IO, TSTRING; 
    SAWCMPFLAG, USE_STDOUT : BOOLEAN; 
    OUTPUT_SPEC_FILE       : FILE_TYPE; 
    INPUT_FILE             : FILE_TYPE; 
    I                      : INTEGER; 
    ARG_CNT                : INTEGER; 
    FLAG_POS               : INTEGER; 
    ARG                    : VSTRING; 
    SKELNAME               : VSTRING; 
    SKELNAME_USED          : BOOLEAN := FALSE; 
  begin
    PRINTSTATS := FALSE; 
    SYNTAXERROR := FALSE; 
    TRACE := FALSE; 
    SPPRDFLT := FALSE; 
    INTERACTIVE := FALSE; 
    CASEINS := FALSE; 
    BACKTRACK_REPORT := FALSE; 
    PERFORMANCE_REPORT := FALSE; 
    DDEBUG := FALSE; 
    FULLTBL := FALSE; 
    CONTINUED_ACTION := FALSE; 
    GEN_LINE_DIRS := TRUE; 
    USEMECS := TRUE; 
    USEECS := TRUE; 

    SAWCMPFLAG := FALSE; 
    USE_STDOUT := FALSE; 

    -- read flags
    COMMAND_LINE_INTERFACE.INITIALIZE_COMMAND_LINE; 

    -- load up argv
    EXTERNAL_FILE_MANAGER.INITIALIZE_FILES; 

    -- do external files setup

    -- loop through the list of arguments
    ARG_CNT := 1; 
    while (ARG_CNT <= ARGC - 1) loop
      if ((CHAR(ARGV(ARG_CNT), 1) /= '-') or (LEN(ARGV(ARG_CNT)) < 2)) then 
        exit; 
      end if; 

      -- loop through the flags in this argument.
      ARG := ARGV(ARG_CNT); 
      FLAG_POS := 2; 
      while (FLAG_POS <= LEN(ARG)) loop
        case CHAR(ARG, FLAG_POS) is 
          when 'b' => 
            BACKTRACK_REPORT := TRUE; 
          when 'd' => 
            DDEBUG := TRUE; 
          when 'f' => 
            USEECS := FALSE; 
            USEMECS := FALSE; 
            FULLTBL := TRUE; 
          when 'I' => 
            INTERACTIVE := TRUE; 
          when 'i' => 
            CASEINS := TRUE; 
          when 'L' => 
            GEN_LINE_DIRS := FALSE; 
          when 'p' => 
            PERFORMANCE_REPORT := TRUE; 
          when 'S' => 
            if (FLAG_POS /= 2) then 
              MISC.AFLEXERROR("-S flag must be given separately"); 
            end if; 
            SKELNAME := SLICE(ARG, FLAG_POS + 1, LEN(ARG)); 
            SKELNAME_USED := TRUE; 
            goto GET_NEXT_ARG; 
          when 's' => 
            SPPRDFLT := TRUE; 
          when 't' => 
            USE_STDOUT := TRUE; 
          when 'T' => 
            TRACE := TRUE; 
          when 'v' => 
            PRINTSTATS := TRUE; 
-- UMASS CODES :
--    Added an flag to indicate whether or not the aflex generated
--    codes will be used by Ayacc extension. Ayacc extension has
--    more power in error recovery.
          when 'E' =>
            Ayacc_Extension_Flag := TRUE;
-- END OF UMASS CODES.
          when others => 
            MISC.AFLEXERROR("unknown flag " & CHAR(ARG, FLAG_POS)); 
        end case; 
        FLAG_POS := FLAG_POS + 1; 
      end loop; 
      <<GET_NEXT_ARG>> ARG_CNT := ARG_CNT + 1; 

    -- go on to next argument from list.
    end loop; 

    if (FULLTBL and USEMECS) then 
      MISC.AFLEXERROR("full table and -cm don't make sense together"); 
    end if; 

    if (FULLTBL and INTERACTIVE) then 
      MISC.AFLEXERROR("full table and -I are (currently) incompatible"); 
    end if; 

    if (ARG_CNT < ARGC) then 
      begin
        if (ARG_CNT - ARGC > 1) then 
          MISC.AFLEXERROR("extraneous argument(s) given"); 
        end if; 

        -- Tell aflex where to read input from.
        INFILENAME := ARGV(ARG_CNT); 
        OPEN(INPUT_FILE, IN_FILE, STR(ARGV(ARG_CNT))); 
        SET_INPUT(INPUT_FILE); 
      exception
        when NAME_ERROR => 
          MISC.AFLEXFATAL("can't open " & INFILENAME); 
      end; 
    end if; 

    if (not USE_STDOUT) then 
      EXTERNAL_FILE_MANAGER.GET_SCANNER_SPEC_FILE(OUTPUT_SPEC_FILE); 
      OUTFILE_CREATED := TRUE; 
    end if; 

    if (BACKTRACK_REPORT) then 
      EXTERNAL_FILE_MANAGER.GET_BACKTRACK_FILE(BACKTRACK_FILE); 
    end if; 

    LASTCCL := 0; 
    LASTSC := 0; 


    --initialize the statistics
    STARTTIME := MISC.AFLEX_GETTIME; 

    begin

      -- open the skeleton file
      if (SKELNAME_USED) then 
        OPEN(SKELFILE, IN_FILE, STR(SKELNAME)); 
        SKELETON_MANAGER.SET_EXTERNAL_SKELETON; 
      end if; 
    exception
      when USE_ERROR | NAME_ERROR => 
        MISC.AFLEXFATAL("couldn't open skeleton file " & SKELNAME); 
    end; 

    -- without a third argument create make an anonymous temp file.
    begin
      CREATE(TEMP_ACTION_FILE, OUT_FILE); 
      CREATE(DEF_FILE, OUT_FILE); 
    exception
      when USE_ERROR | NAME_ERROR => 
        MISC.AFLEXFATAL("can't create temporary file"); 
    end; 

    LASTDFA := 0; 
    LASTNFA := 0; 
    NUM_RULES := 0; 
    NUMAS := 0; 
    NUMSNPAIRS := 0; 
    TMPUSES := 0; 
    NUMECS := 0; 
    NUMEPS := 0; 
    EPS2 := 0; 
    NUM_REALLOCS := 0; 
    HSHCOL := 0; 
    DFAEQL := 0; 
    TOTNST := 0; 
    NUMUNIQ := 0; 
    NUMDUP := 0; 
    HSHSAVE := 0; 
    EOFSEEN := FALSE; 
    DATAPOS := 0; 
    DATALINE := 0; 
    NUM_BACKTRACKING := 0; 
    ONESP := 0; 
    NUMPROTS := 0; 
    VARIABLE_TRAILING_CONTEXT_RULES := FALSE; 
    BOL_NEEDED := FALSE; 

    LINENUM := 1; 
    SECTNUM := 1; 
    FIRSTPROT := NIL; 

    -- used in mkprot() so that the first proto goes in slot 1
    -- of the proto queue

    LASTPROT := 1; 

    if (USEECS) then 
    -- set up doubly-linked equivalence classes
      ECGROUP(1) := NIL; 

      for CNT in 2 .. CSIZE loop
        ECGROUP(CNT) := CNT - 1; 
        NEXTECM(CNT - 1) := CNT; 
      end loop; 

      NEXTECM(CSIZE) := NIL; 
    else 
    -- put everything in its own equivalence class
      for CNT in 1 .. CSIZE loop
        ECGROUP(CNT) := CNT; 
        NEXTECM(CNT) := BAD_SUBSCRIPT;  -- to catch errors
      end loop; 
    end if; 

    SET_UP_INITIAL_ALLOCATIONS; 


  end AFLEXINIT; 

  -- readin - read in the rules section of the input file(s)
  procedure READIN is 
  begin
    SKELETON_MANAGER.SKELOUT; 

    MISC.LINE_DIRECTIVE_OUT; 

    PARSER.YYPARSE; 

    if (USEECS) then 
      ECS.CRE8ECS(NEXTECM, ECGROUP, CSIZE, NUMECS); 
      ECS.CCL2ECL; 
    else 
      NUMECS := CSIZE; 
    end if; 
	
  exception
    when PARSE_TOKENS.SYNTAX_ERROR => 
      MISC.AFLEXERROR("fatal parse error at line " & INTEGER'IMAGE(LINENUM)); 
      MAIN_BODY.AFLEXEND(1); 
  end READIN; 

  -- set_up_initial_allocations - allocate memory for internal tables
  procedure SET_UP_INITIAL_ALLOCATIONS is 
  begin
    CURRENT_MNS := INITIAL_MNS; 
    FIRSTST := ALLOCATE_INTEGER_ARRAY(CURRENT_MNS); 
    LASTST := ALLOCATE_INTEGER_ARRAY(CURRENT_MNS); 
    FINALST := ALLOCATE_INTEGER_ARRAY(CURRENT_MNS); 
    TRANSCHAR := ALLOCATE_INTEGER_ARRAY(CURRENT_MNS); 
    TRANS1 := ALLOCATE_INTEGER_ARRAY(CURRENT_MNS); 
    TRANS2 := ALLOCATE_INTEGER_ARRAY(CURRENT_MNS); 
    ACCPTNUM := ALLOCATE_INTEGER_ARRAY(CURRENT_MNS); 
    ASSOC_RULE := ALLOCATE_INTEGER_ARRAY(CURRENT_MNS); 
    STATE_TYPE := ALLOCATE_STATE_ENUM_ARRAY(CURRENT_MNS); 

    CURRENT_MAX_RULES := INITIAL_MAX_RULES; 
    RULE_TYPE := ALLOCATE_RULE_ENUM_ARRAY(CURRENT_MAX_RULES); 
    RULE_LINENUM := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_RULES); 

    CURRENT_MAX_SCS := INITIAL_MAX_SCS; 
    SCSET := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_SCS); 
    SCBOL := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_SCS); 
    SCXCLU := ALLOCATE_BOOLEAN_ARRAY(CURRENT_MAX_SCS); 
    SCEOF := ALLOCATE_BOOLEAN_ARRAY(CURRENT_MAX_SCS); 
    SCNAME := ALLOCATE_VSTRING_ARRAY(CURRENT_MAX_SCS); 
    ACTVSC := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_SCS); 

    CURRENT_MAXCCLS := INITIAL_MAX_CCLS; 
    CCLMAP := ALLOCATE_INTEGER_ARRAY(CURRENT_MAXCCLS); 
    CCLLEN := ALLOCATE_INTEGER_ARRAY(CURRENT_MAXCCLS); 
    CCLNG := ALLOCATE_INTEGER_ARRAY(CURRENT_MAXCCLS); 

    CURRENT_MAX_CCL_TBL_SIZE := INITIAL_MAX_CCL_TBL_SIZE; 
    CCLTBL := ALLOCATE_CHARACTER_ARRAY(CURRENT_MAX_CCL_TBL_SIZE); 

    CURRENT_MAX_DFA_SIZE := INITIAL_MAX_DFA_SIZE; 

    CURRENT_MAX_XPAIRS := INITIAL_MAX_XPAIRS; 
    NXT := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_XPAIRS); 
    CHK := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_XPAIRS); 

    CURRENT_MAX_TEMPLATE_XPAIRS := INITIAL_MAX_TEMPLATE_XPAIRS; 
    TNXT := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_TEMPLATE_XPAIRS); 

    CURRENT_MAX_DFAS := INITIAL_MAX_DFAS; 
    BASE := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_DFAS); 
    DEF := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_DFAS); 
    DFASIZ := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_DFAS); 
    ACCSIZ := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_DFAS); 
    DHASH := ALLOCATE_INTEGER_ARRAY(CURRENT_MAX_DFAS); 
    DSS := ALLOCATE_INT_PTR_ARRAY(CURRENT_MAX_DFAS); 
    DFAACC := ALLOCATE_DFAACC_UNION(CURRENT_MAX_DFAS); 
  end SET_UP_INITIAL_ALLOCATIONS; 
end MAIN_BODY; 
