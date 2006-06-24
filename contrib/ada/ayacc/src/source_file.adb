-- $Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/source_file_body.a,v 1.1 88/08/08 14:29:03 arcadia Exp $ 

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

-- Module       : source_file_body.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:36:09
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxsource_file_body.ada

-- $Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/source_file_body.a,v 1.1 88/08/08 14:29:03 arcadia Exp $ 
-- $Log:	source_file_body.a,v $
--Revision 1.1  88/08/08  14:29:03  arcadia
--Initial revision
--
-- Revision 0.1  86/04/01  15:12:32  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:42:02  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

with Text_IO, Ayacc_File_Names;
use  Text_IO;
package body Source_File is

  SCCS_ID : constant String := "@(#) source_file_body.ada, Version 1.2";



  Rcs_ID : constant String := "$Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/source_file_body.a,v 1.1 88/08/08 14:29:03 arcadia Exp $";

    Input_File : File_Type;

    Max_Line_Length : constant := 260;

    type Long_STR is
	record
	    Name   : String(1..Max_Line_Length);
	    Length : Natural := 0;
	end record;

    Current_Line  : Long_STR;
    Previous_Line : Long_STR;
    Column_Number : Natural;   -- column number of current_line.
    Line_Number   : Natural;


    Get_New_Line       : Boolean := True;   
    End_of_Source_File : Boolean := False;



    procedure Open is
	use Ayacc_File_Names;
    begin
	Open(Input_File, In_File, Get_Source_File_Name);
	Current_Line  := ((others => ' '), 0);
	Previous_Line := ((others => ' '), 0);
	Column_Number := 1;
	Line_Number   := 0;
    exception
	when Name_Error | Use_Error =>
	    Put_Line("Ayacc: Error Opening """ & Get_Source_File_Name & """.");
            raise;
    end Open;


    procedure Close is
    begin
	Close(Input_File);
    end Close;


    function Is_End_of_File return Boolean is
    begin
	return End_of_File(Input_File);
    end Is_End_of_File;

    function Source_Line_Number return Natural is
    begin
	return Line_Number;
    end Source_Line_Number;


    function Maximum_Line_Length return Natural is
    begin
      return Max_Line_Length;
    end Maximum_Line_Length;


    procedure Get_Char(Ch: out Character) is
    begin

	if Get_New_Line then
	    Previous_Line := Current_Line;
	    Get_Line(Input_File, Current_Line.Name, Current_Line.Length);
	    Get_New_Line := False;
	    Column_Number := 1;
	    Line_Number := Line_Number + 1;
	end if;

	if Column_Number > Current_Line.Length then
	    if End_of_File(Input_File) then
		Ch := Eof;
		End_of_Source_File := True;
		return;
	    end if;
	    Ch := Eoln;
	    Get_New_Line := True;
	else
	    Ch := Current_Line.Name(Column_Number);
	    Column_Number := Column_Number + 1;
	end if;

    end Get_Char;


    -- Note: You can't correctly peek at next character if the last character
    -- read is a EOLN. It is assumed that the lexical analyzer won't
    -- call this function in that case.
    function Peek_Next_Char return Character is
    begin
	if Column_Number > Current_Line.Length then
	    if End_of_File(Input_File) then
		return Eof;
	    else
		return Eoln;
	    end if;
	end if;
	return Current_Line.Name(Column_Number);
    end Peek_Next_Char;



    procedure Unget_Char(Ch : in Character) is
    begin
	if Get_New_Line then
	    Get_New_Line := False;
	elsif End_of_Source_File then
	    End_of_Source_File := False;
	elsif Column_Number = 1 then
	    Put_Line("Ayacc: Error in Unget_Char, Attempt to 'unget' an EOLN");
	    raise Pushback_Error;
	else
	    Column_Number := Column_Number - 1;
	end if;
    end Unget_Char;



    procedure Print_Context_Lines is
	Ptr_Location : Integer := 0;
    begin

	    --  Print previous line followed by current line  --

	Put(Integer'Image(Line_Number-1) & Ascii.Ht);
	Put_Line(Previous_Line.Name(1..Previous_Line.Length));
	Put(Integer'Image(Line_Number) & Ascii.Ht);
	Put_Line(Current_Line.Name(1..Current_Line.Length));


        --  Correct for any tab characters so that the pointer will
        --  point to the proper location on the source line.
        for I in 1..Column_Number - 1 loop
	    if Current_Line.Name(I) = Ascii.Ht then -- Adjust for tab.
	        Ptr_Location := (((Ptr_Location / 8) + 1) * 8);
	    else
	        Ptr_Location := Ptr_Location + 1;
	    end if;
        end loop;

	Put(Ascii.Ht);
        for I in 1..Ptr_Location - 1 loop
	    Put('-');
        end loop;
        Put('^');

    end Print_Context_Lines;


    procedure Read_Line(Source_Line: out String; Last: out Natural) is
    begin
	Get_Line(Input_File, Source_Line, Last);
	Line_Number := Line_Number + 1;
    end Read_Line;


end Source_File;
