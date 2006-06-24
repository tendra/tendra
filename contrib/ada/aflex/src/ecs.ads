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

-- TITLE equivalence class
-- AUTHOR: John Self (UCI)
-- DESCRIPTION finds equivalence classes so DFA will be smaller
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/ecsS.a,v 1.4 90/01/12 15:19:57 self Exp Locker: self $ 

with MISC_DEFS; use MISC_DEFS; 
package ECS is 
  procedure CCL2ECL; 
  procedure CRE8ECS(FWD, BCK : in out C_SIZE_ARRAY; 
                    NUM      : in INTEGER; 
                    RESULT   : out INTEGER); 
  procedure MKECCL(CCLS     : in out CHAR_ARRAY; 
                   LENCCL   : in INTEGER; 
                   FWD, BCK : in out UNBOUNDED_INT_ARRAY; 
                   LLSIZ    : in INTEGER); 
  procedure MKECHAR(TCH      : in INTEGER; 
                    FWD, BCK : in out C_SIZE_ARRAY); 
end ECS; 
