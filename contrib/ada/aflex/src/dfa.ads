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

-- TITLE DFA construction routines
-- AUTHOR: John Self (UCI)
-- DESCRIPTION converts non-deterministic finite automatons to finite ones.
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/dfaS.a,v 1.4 90/01/12 15:19:52 self Exp Locker: self $ 

with MISC_DEFS; 
with TEXT_IO; 
package DFA is 
  use MISC_DEFS, TEXT_IO; 
  procedure CHECK_FOR_BACKTRACKING(DS    : in INTEGER; 
                                   STATE : in UNBOUNDED_INT_ARRAY); 
  procedure CHECK_TRAILING_CONTEXT(NFA_STATES : in INT_PTR; 
                                   NUM_STATES : in INTEGER; 
                                   ACCSET     : in INT_PTR; 
                                   NACC       : in INTEGER); 

  procedure DUMP_ASSOCIATED_RULES(F  : in FILE_TYPE; 
                                  DS : in INTEGER); 

  procedure DUMP_TRANSITIONS(F     : in FILE_TYPE; 
                             STATE : in UNBOUNDED_INT_ARRAY); 

  procedure EPSCLOSURE(T                  : in out INT_PTR; 
                       NS_ADDR            : in out INTEGER; 
                       ACCSET             : in out INT_PTR; 
                       NACC_ADDR, HV_ADDR : out INTEGER; 
                       RESULT             : out INT_PTR); 

  procedure INCREASE_MAX_DFAS; 

  procedure NTOD; 

  procedure SNSTODS(SNS           : in INT_PTR; 
                    NUMSTATES     : in INTEGER; 
                    ACCSET        : in INT_PTR; 
                    NACC, HASHVAL : in INTEGER; 
                    NEWDS_ADDR    : out INTEGER; 
                    RESULT        : out BOOLEAN); 

  function SYMFOLLOWSET(DS              : in INT_PTR; 
                        DSIZE, TRANSSYM : in INTEGER; 
                        NSET            : in INT_PTR) return INTEGER; 

  procedure SYMPARTITION(DS        : in INT_PTR; 
                         NUMSTATES : in INTEGER; 
                         SYMLIST   : in out C_SIZE_BOOL_ARRAY; 
                         DUPLIST   : in out C_SIZE_ARRAY); 
end DFA; 
