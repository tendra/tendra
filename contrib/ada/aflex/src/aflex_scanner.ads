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

-- TITLE  scanner parser interface
-- AUTHOR: John Self (UCI)
-- DESCRIPTION causes parser to call augmented version of YYLex.
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/aflex_scanner.a,v 1.3 90/01/12 15:19:33 self Exp Locker: self $ 

with PARSE_TOKENS, SCANNER; use PARSE_TOKENS, SCANNER; 

package AFLEX_SCANNER is 
  function YYLEX return TOKEN; 
end AFLEX_SCANNER; 
