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
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/command_lineB.a,v 1.3 90/01/12 15:19:44 self Exp Locker: self $ 

-- 02/14/98 Wolfgang Lohmann (lohmi@acm.org)
-- changes marked with --wl

with TSTRING; use TSTRING; 
--wl with A_STRINGS; use A_STRINGS; 
--wl:
with Ada.Command_Line;      use Ada.Command_Line;

--wl with COMMAND_LINE; 

package body COMMAND_LINE_INTERFACE is 
  procedure INITIALIZE_COMMAND_LINE is 
  begin
    ARGV(0) := VSTR(Ada.Command_Line.COMMAND_name);
    for I in 1 .. Ada.COMMAND_LINE.ARGument_Count 	--wl -1 
    loop
      ARGV(I) := VSTR(Ada.COMMAND_LINE.ARGument(I)); 
    end loop; 
    ARGC := Ada.COMMAND_LINE.ARGument_Count +1 ;  --wl 
  end INITIALIZE_COMMAND_LINE; 
end COMMAND_LINE_INTERFACE; 
