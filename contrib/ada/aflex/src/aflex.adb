
-- TITLE aflex - main program
--
-- AUTHOR: John Self (UCI)
-- DESCRIPTION main subprogram of aflex, calls the major routines in order
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/aflex.a,v 1.11 90/10/15 20:00:40 self Exp Locker: self $ 
--*************************************************************************** 
--                              aflex
--                          version 1.4a
--***************************************************************************
--
--                            Arcadia Project
--               Department of Information and Computer Science
--                        University of California
--                        Irvine, California 92717
--
--    Send requests for aflex information to alex-info@ics.uci.edu
--
--    Send bug reports for aflex to alex-bugs@ics.uci.edu
--
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
--
--    This program is based on the flex program written by Vern Paxson.
--
--    The following is the copyright notice from flex, from which aflex is
--    derived.
--	Copyright (c) 1989 The Regents of the University of California.
--	All rights reserved.
--
--	This code is derived from software contributed to Berkeley by
--	Vern Paxson.
--
--      The United States Government has rights in this work pursuant to
--	contract no. DE-AC03-76SF00098 between the United States Department of
--	Energy and the University of California.
--
--	Redistribution and use in source and binary forms are permitted
--	provided that the above copyright notice and this paragraph are
--	duplicated in all such forms and that any documentation,
--	advertising materials, and other materials related to such
--	distribution and use acknowledge that the software was developed
--	by the University of California, Berkeley.  The name of the
--	University may not be used to endorse or promote products derived
--	from this software without specific prior written permission.
--	THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
--	IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
--	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
--
--***************************************************************************

with MAIN_BODY, DFA, GEN, MISC_DEFS, TEXT_IO, MISC; 
with TSTRING, TEMPLATE_MANAGER, EXTERNAL_FILE_MANAGER; use MISC_DEFS, TEXT_IO, 
  TSTRING, EXTERNAL_FILE_MANAGER; 
function AFLEX return INTEGER is 
	copyright : constant string :=
    "@(#) Copyright (c) 1990 Regents of the University of California.";
    	copyright2 : constant string :=
    "All rights reserved.";
begin
  MAIN_BODY.AFLEXINIT; 

  MAIN_BODY.READIN; 
	
  if (SYNTAXERROR) then 
    MAIN_BODY.AFLEXEND(1); 
  end if; 

  if (PERFORMANCE_REPORT) then 
    if (INTERACTIVE) then 
      TEXT_IO.PUT_LINE(STANDARD_ERROR, 
        "-I (interactive) entails a minor performance penalty"); 
    end if; 


  end if; 

  if (VARIABLE_TRAILING_CONTEXT_RULES) then 
    MISC.AFLEXERROR("can't handle variable trailing context rules"); 
  end if; 

  -- convert the ndfa to a dfa
  DFA.NTOD; 

  -- generate the Ada state transition tables from the DFA
  GEN.MAKE_TABLES; 

  TEMPLATE_MANAGER.GENERATE_IO_FILE; 
  TEMPLATE_MANAGER.GENERATE_DFA_FILE; 
  MAIN_BODY.AFLEXEND(0); 
  return 0; 
exception
  when MAIN_BODY.AFLEX_TERMINATE => 
    return MAIN_BODY.TERMINATION_STATUS; 
end AFLEX; 
