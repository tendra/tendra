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

-- TITLE NFA construction routines
-- AUTHOR: John Self (UCI)
-- DESCRIPTION builds the NFA.
-- NOTES this file mirrors flex as closely as possible.
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/nfaS.a,v 1.4 90/01/12 15:20:30 self Exp Locker: self $ 

package NFA is 
  procedure ADD_ACCEPT(MACH             : in out INTEGER; 
                       ACCEPTING_NUMBER : in INTEGER); 
  function COPYSINGL(SINGL, NUM : in INTEGER) return INTEGER; 
  procedure DUMPNFA(STATE1 : in INTEGER); 
  function DUPMACHINE(MACH : in INTEGER) return INTEGER; 
  procedure FINISH_RULE(MACH                : in INTEGER; 
                        VARIABLE_TRAIL_RULE : in BOOLEAN; 
                        HEADCNT, TRAILCNT   : in INTEGER); 
  function LINK_MACHINES(FIRST, LAST : in INTEGER) return INTEGER; 
  procedure MARK_BEGINNING_AS_NORMAL(MACH : in INTEGER); 
  function MKBRANCH(FIRST, SECOND : in INTEGER) return INTEGER; 
  function MKCLOS(STATE : in INTEGER) return INTEGER; 
  function MKOPT(MACH : in INTEGER) return INTEGER; 
  function MKOR(FIRST, SECOND : in INTEGER) return INTEGER; 
  function MKPOSCL(STATE : in INTEGER) return INTEGER; 
  function MKREP(MACH, LB, UB : in INTEGER) return INTEGER; 
  function MKSTATE(SYM : in INTEGER) return INTEGER; 
  procedure MKXTION(STATEFROM, STATETO : in INTEGER); 
  procedure NEW_RULE; 
end NFA; 
