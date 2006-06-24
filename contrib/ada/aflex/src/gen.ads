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

-- TITLE scanner generation
-- AUTHOR: John Self (UCI)
-- DESCRIPTION
-- NOTES does actual generation (writing) of output aflex scanners
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/genS.a,v 1.4 90/01/12 15:20:07 self Exp Locker: self $ 

with MISC_DEFS; use MISC_DEFS; 
package GEN is 
  procedure DO_INDENT; 
  procedure GEN_BACKTRACKING; 
  procedure GEN_BT_ACTION; 
  procedure GEN_FIND_ACTION; 
  procedure GEN_NEXT_COMPRESSED_STATE; 
  procedure GEN_NEXT_MATCH; 
  procedure GEN_NEXT_STATE; 
  procedure GEN_START_STATE; 
  procedure GENECS; 
  procedure GENFTBL; 
  procedure INDENT_PUTS(STR : in STRING); 
  procedure GENTABS; 
  procedure INDENT_DOWN; 
  procedure INDENT_UP; 
  procedure SET_INDENT(INDENT_VAL : in INTEGER); 
  procedure MAKE_TABLES; 
  procedure DO_SECT3_OUT; 
  procedure BODY_HEADER;
end GEN; 
