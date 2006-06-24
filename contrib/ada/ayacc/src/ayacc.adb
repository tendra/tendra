-- $Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/ayacc.a,v 1.1 88/08/08 12:07:07 arcadia Exp $ 
--************************************************************************ 
--                              ayacc
--                           version 1.1
--
--***********************************************************************
--
--                            Arcadia Project
--               Department of Information and Computer Science
--                        University of California
--                        Irvine, California 92717
--
-- Copyright (c) 1990 Regents of the University of California.
-- All rights reserved.
--
--    The primary authors of ayacc were David Taback and Deepak Tolani.
--    Enhancements were made by Ronald J. Schmalz.
--    Further enhancements were made by Yidong Chen.
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

-- Module       : ayacc.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:28:24
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxayacc.ada

-- $Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/ayacc.a,v 1.1 88/08/08 12:07:07 arcadia Exp $ 
-- $Log:	ayacc.a,v $
--Revision 1.1  88/08/08  12:07:07  arcadia
--Initial revision
--
-- Revision 0.1  86/04/01  15:04:07  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  19:00:49  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

with Source_File,
     Ayacc_File_Names,
     Options,
     Parser,
     Tokens_File,
     Output_File,
     Parse_Table,
     Text_IO,
--     u_env,	  -- For getting the command line arguments

     Symbol_Table, -- Used for statistics only
     Rule_Table;   -- Used for statistics only

-- UMASS CODES :
with Error_Report_File;
-- END OF UMASS CODES.

procedure Ayacc is

    Rcs_ID : constant String := "$Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/ayacc.a,v 1.1 88/08/08 12:07:07 arcadia Exp $";

    copyright : constant string :=
    "@(#) Copyright (c) 1990 Regents of the University of California.";
    copyright2 : constant string :=
    "All rights reserved.";
    Illegal_Argument_List : exception;

    use Text_IO;
    procedure Initialize       is separate;
    procedure Print_Statistics is separate;

begin

    Initialize;

    Source_File.Open;
    Tokens_File.Open;

    Parser.Parse_Declarations;
    Parser.Parse_Rules;
    Parse_Table.Make_Parse_Table;
    Output_File.Make_Output_File;
    Tokens_File.Complete_Tokens_Package;

-- UMASS CODES :
--  Generate the error report file if the codes
--  of error recovery extension should be generated.
    if Options.Error_Recovery_Extension then
      Error_Report_File.Write_File;
    end if;
-- END OF UMASS CODES.

    Source_File.Close;
    Tokens_File.Close;

    if Options.Interface_to_C then
	Tokens_File.Make_C_Lex_Package;
    end if;

    Print_Statistics;

exception


    when Ayacc_File_Names.Illegal_File_Name =>
	Put_Line("Ayacc: Illegal Filename.");

    when Options.Illegal_Option | Illegal_Argument_List =>
        null;

    when Parser.Syntax_Error =>   -- Error has already been reported.
	Source_File.Close;

    when Text_IO.Name_Error | Text_IO.Use_Error =>
        null;  -- Error has already been reported.

    when others =>
        Put_Line ("Ayacc: Internal Error, Please Submit an LCR.");
end Ayacc;
