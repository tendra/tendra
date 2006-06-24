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

-- TITLE external_file_manager
-- AUTHOR: John Self (UCI)
-- DESCRIPTION opens external files for other functions
-- NOTES This package opens external files, and thus may be system dependent
--       because of limitations on file names.
--       This version is for the VADS 5.5 Ada development system.
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/file_managerS.a,v 1.4 90/01/12 15:20:00 self Exp Locker: self $ 

with TEXT_IO; use TEXT_IO; 
package EXTERNAL_FILE_MANAGER is 
  procedure GET_IO_SPEC_FILE(F : in out FILE_TYPE); 
  procedure GET_IO_BODY_FILE(F : in out FILE_TYPE); 
  procedure GET_DFA_SPEC_FILE(F : in out FILE_TYPE); 
  procedure GET_DFA_BODY_FILE(F : in out FILE_TYPE); 
  procedure GET_SCANNER_SPEC_FILE(F : in out FILE_TYPE); 
  procedure GET_SCANNER_BODY_FILE(F : in out FILE_TYPE); 
  procedure GET_BACKTRACK_FILE(F : in out FILE_TYPE); 
  procedure INITIALIZE_FILES; 
end EXTERNAL_FILE_MANAGER; 
