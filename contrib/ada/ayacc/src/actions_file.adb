-- $Header: /dc/uc/self/arcadia/ayacc/src/RCS/actions_file_body.a,v 1.2 1993/05/31 22:36:35 self Exp self $ 
-- $Header: /dc/uc/self/arcadia/ayacc/src/RCS/actions_file_body.a,v 1.2 1993/05/31 22:36:35 self Exp self $ 

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

-- Module       : actions_file_body.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:28:04
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxactions_file_body.ada

-- $Header: /dc/uc/self/arcadia/ayacc/src/RCS/actions_file_body.a,v 1.2 1993/05/31 22:36:35 self Exp self $ 
-- $Log: actions_file_body.a,v $
-- Revision 1.2  1993/05/31  22:36:35  self
-- added exception handler when opening files
--
-- Revision 1.1  1993/05/31  22:13:57  self
-- Initial revision
--
--Revision 1.1  88/08/08  14:54:53  arcadia
--Initial revision
--
--Revision 1.1  88/08/08  12:04:56  arcadia
--Initial revision

--Revision 0.1  86/04/01  15:29:59  ada
-- This version fixes some minor bugs with empty grammars 
-- and $$ expansion. It also uses vads5.1b enhancements 
-- such as pragma inline. 
-- 

with Ayacc_File_Names;
use  Ayacc_File_Names;
package body Actions_File is

  SCCS_ID : constant String := "@(#) actions_file_body.ada, Version 1.2";


    
    -- The maximum length of the text that an action can expand into. 
    Maximum_Action_Length : constant Count  := 1000; 

    The_File : File_Type; 

    procedure Open(Mode: in File_Mode) is
    begin
	if Mode = Read_File then 
           Open(The_File, In_File, Get_Actions_File_Name);
        else 
           Create(The_File, Out_File, Get_Actions_File_Name); 
--RJS           Set_Line_Length(The_File, To => Maximum_Action_Length);  
        end if; 
	exception
           when Name_Error | Use_Error =>
               Put_Line("Ayacc: Error Opening """ & Get_Actions_File_Name & """.");
               raise;
    end Open;

    procedure Close is
    begin
       Close(The_File);
    end Close;

    procedure Delete is 
    begin 
        Delete(The_File); 
    end Delete; 

    procedure Read_Line(S: out String; Last: out Natural) is 
    begin
        Get_Line(The_File, S, Last);  
    end; 

    procedure Write(S: in String) is 
    begin 
        Put(The_File, S);    
    end; 

    procedure Write(C: in Character) is 
    begin 
        Put(The_File, C);    
    end; 

    procedure Writeln is 
    begin 
    	New_Line(The_File); 
    end; 
	

    function Is_End_of_File return Boolean is
    begin
	return End_of_File(The_File);
    end Is_End_of_File;

    procedure Initialize is 
    begin  
       Open(Write_File); 
    end Initialize; 

    procedure Finish is 
    begin 
       Close;          
    end Finish; 

end Actions_File;
