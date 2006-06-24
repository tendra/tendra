-- $Header: /dc/uc/self/arcadia/ayacc/src/RCS/tokens_file_body.a,v 1.2 1993/05/31 22:36:35 self Exp self $ 

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

-- Module       : tokens_file_body.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:38:23
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxtokens_file_body.ada

-- $Header: /dc/uc/self/arcadia/ayacc/src/RCS/tokens_file_body.a,v 1.2 1993/05/31 22:36:35 self Exp self $ 
-- $Log: tokens_file_body.a,v $
-- Revision 1.2  1993/05/31  22:36:35  self
-- added exception handler when opening files
--
-- Revision 1.1  1993/05/31  22:14:38  self
-- Initial revision
--
--Revision 1.1  88/08/08  14:43:01  arcadia
--Initial revision
--
-- Revision 0.1  86/04/01  15:14:29  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:54:19  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  


with Ayacc_File_Names, Source_File, Symbol_Table, Text_IO;

with String_Pkg;
package body Tokens_File is

  SCCS_ID : constant String := "@(#) tokens_file_body.ada, Version 1.2";



  Rcs_ID : constant String := "$Header: /dc/uc/self/arcadia/ayacc/src/RCS/tokens_file_body.a,v 1.2 1993/05/31 22:36:35 self Exp self $";

  Package_Header_Generated : Boolean := False;


    T_File: Text_IO.File_Type;

    procedure Open is
	use Text_IO;
    begin
	Create(T_File, Out_File, Ayacc_File_Names.Get_Tokens_File_Name);
	exception
             when Name_Error | Use_Error =>
                  Put_Line("Ayacc: Error Opening """ & Ayacc_File_Names.Get_Tokens_File_Name & """.");
                  raise;
    end Open;


    function Tokens_Package_Header_Has_Been_Generated return Boolean is
    begin
      return Package_Header_Generated;
    end Tokens_Package_Header_Has_Been_Generated;

    procedure Start_Tokens_Package is
    begin
      if not Package_Header_Generated then
        Writeln("package " & Ayacc_File_Names.Tokens_Unit_Name & " is");
        Writeln("");
        Package_Header_Generated := True;
      end if;
    end Start_Tokens_Package;


    procedure Close is
	use Text_IO;
    begin
	Close(T_File);
    end Close;

    procedure Write(S: in String) is
	use Text_IO;
    begin
	Put(T_File,S);
    end Write;

    procedure Writeln(S: in String) is
	use Text_IO;
    begin
	Put_Line(T_File,S);
    end Writeln;



    procedure Complete_Tokens_Package is

	Tokens_On_Line: Natural := 1;
        use String_Pkg;
	use Symbol_Table;

    begin

      if not Package_Header_Generated then
        Start_Tokens_Package;
      end if;

        Writeln("    YYLVal, YYVal : YYSType; "); 
	Writeln("    type Token is");
	Write("        (");

	for I in First_Symbol(Terminal)..Last_Symbol(Terminal)-1 loop
	    if Tokens_On_Line = 4 then
		Write(Value (Mixed (Get_Symbol_Name(I))));         
		Writeln(",");
		Write("         ");
		Tokens_On_Line := 1;
	    else
		Write(Value (Mixed (Get_Symbol_Name(I))));
		Write(", ");
	    end if;
	    Tokens_On_Line := Tokens_On_Line + 1;
	end loop;

	Write(Value (Mixed (Get_Symbol_Name(Last_Symbol(Terminal)))));
	Writeln(" );");
	Writeln("");
	Writeln("    Syntax_Error : exception;");
	Writeln("");
	Writeln("end " & Ayacc_File_Names.Tokens_Unit_Name & ";");

    end Complete_Tokens_Package;


    procedure Make_C_Lex_Package is
	use Symbol_Table, Text_IO;

	The_Define_File : File_Type;
	The_Ada_File    : File_Type;

	type Symbol_Rec is
	    record
		Name   : String(1..Source_File.Maximum_Line_Length);
		Length : Natural;
	    end record;

	Sym_Name : Symbol_Rec;

	function Convert(S : String) return Symbol_Rec is
	    Result : Symbol_Rec;
	begin
	    Result.Name(1..S'Length) := S;
	    Result.Length := S'Length;
	    return Result;
	end;

    begin

	Create(The_Ada_File, Out_File, Ayacc_File_Names.Get_C_Lex_File_Name & "ds");

	Put_Line(The_Ada_File, "with "  & Ayacc_File_Names.Tokens_Unit_Name &
                               ";  use " & Ayacc_File_Names.Tokens_Unit_Name & ";");
	Put_Line(The_Ada_File, "package " & Ayacc_File_Names.C_Lex_Unit_Name & " is");
	Put_Line(The_Ada_File, "    function YYLex return Token;");
	Put_Line(The_Ada_File, "end " & Ayacc_File_Names.C_Lex_Unit_Name & ";");
	Close(The_Ada_File);

	Create(The_Ada_File, Out_File, Ayacc_File_Names.Get_C_Lex_File_Name & "db");

	Put_Line(The_Ada_File, "package body " & Ayacc_File_Names.C_Lex_Unit_Name & " is");
	New_Line(The_Ada_File);
	Put_Line(The_Ada_File, "    function Get_Token return Integer;");
	New_Line(The_Ada_File);
	Put_Line(The_Ada_File, "    pragma Interface(C, Get_Token);");
	New_Line(The_Ada_File);
        Put_Line(The_Ada_File, "    type Table is array(0..255) of Token;"); 
        Put_Line(The_Ada_File, "    Literals : constant Table := Table'("); 
        Put_Line(The_Ada_File, "        0 => End_of_Input,");  

	Create(The_Define_File, Out_File, Ayacc_File_Names.Get_Include_File_Name);

	Put_Line(The_Define_File, "/* C_Lex Token Definition for type " &
                                  Ayacc_File_Names.Tokens_Unit_Name & ".Token; */");
        New_Line (The_Define_File);

	for I in First_Symbol(Terminal)..Last_Symbol(Terminal) loop
	    Sym_Name := Convert(Get_Symbol_Name(I));
	    if Sym_Name.Name(1) /= ''' then
		Put(The_Define_File,"#define ");
		Put(The_Define_File, Sym_Name.Name(1..Sym_Name.Length));
		Put_Line(The_Define_File, "  " & Grammar_Symbol'Image(I + 256));
	    else
		Put(The_Ada_File, "       " & 
                    Integer'Image(Character'Pos(Sym_Name.Name(2))) & " => ");
		Put(The_Ada_File, Sym_Name.Name(1..Sym_Name.Length) & ',');
                New_Line(The_Ada_File); 
	    end if;
	end loop;

        Put_Line(The_Ada_File, "        others => Error); "); 
        New_Line(The_Ada_File); 

	Put_Line(The_Ada_File, "    function YYLex return Token is");
	Put_Line(The_Ada_File, "        Token_Value : Integer;");
	Put_Line(The_Ada_File, "    begin");
	Put_Line(The_Ada_File, "        Token_Value := Get_Token;");
	Put_Line(The_Ada_File, "        if Token_Value > 255 then");
	Put_Line(The_Ada_File, "            return Token'Val(Token_Value-256);");
        Put_Line(The_Ada_File, "        else                        "); 
        Put_Line(The_Ada_File, "            return Literals(Token_Value);     "); 
        Put_Line(The_Ada_File, "        end if; "); 
        Put_Line(The_Ada_File, "    end YYLex; "); 




	Put_Line(The_Ada_File, "end " & Ayacc_File_Names.C_Lex_Unit_Name & ";");
	Close(The_Ada_File);
	Close(The_Define_File);
    end;

end Tokens_File;
