-- Copyright (c) 1990 Regents of the University of California.
-- All rights reserved.
--
--    The primary authors of ayacc were David Taback and Deepak Tolani.
--    Enhancements were made by Ronald J. Schmalz.
--
--    Send requests for ayacc information to ayacc-info@ics.uci.edu
--    Send bug reports for ayacc to ayacc-bugs@ics.uci.edu
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

-- Module       : actions_file.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:27:44
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxactions_file.ada

-- $Header: actions_file.a,v 0.1 86/04/01 15:03:51 ada Exp $ 
-- $Log:	actions_file.a,v $
-- Revision 0.1  86/04/01  15:03:51  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:35:43  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  



with Text_IO; use  Text_IO;

package Actions_File is

   
	
    --								--
    --  Standard file access routines for the file containing   -- 
    --  the procedure user_action which associates rules to the --
    --  user executable code. 					--
    -- 								--  


    type File_Mode is (Read_File, Write_File); 

    procedure Open(Mode: in File_Mode);
    procedure Write(C: in Character); 
    procedure Write(S: in String); 
    procedure Writeln; 
    procedure Read_Line(S: out String; Last: out Natural);
    procedure Close;
    procedure Delete;

    --  Initializes and finishes the decalarations for the      --
    --  procedure user_action.                                  -- 

    procedure Initialize; 
    procedure Finish; 

    function Is_End_of_File return Boolean;

end Actions_File;
