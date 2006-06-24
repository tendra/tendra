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

-- TITLE command line interface
-- AUTHOR: John Self (UCI)
-- DESCRIPTION command line interface body for use with the VERDIX VADS system.
-- NOTES this file is system dependent
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/command_lineS.a,v 1.3 90/01/12 15:19:46 self Exp Locker: self $ 

with TSTRING; use TSTRING; 

package COMMAND_LINE_INTERFACE is 

  MAX_NUMBER_ARGS : INTEGER := 32; 

  type COMMAND_VECTOR is array(0 .. MAX_NUMBER_ARGS) of VSTRING; 

  procedure INITIALIZE_COMMAND_LINE;
 
  ARGV : COMMAND_VECTOR; 

  ARGC : INTEGER; 

end COMMAND_LINE_INTERFACE; 
