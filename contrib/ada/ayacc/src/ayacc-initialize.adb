-- $Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/ayacc_separates.a,v 1.1 88/08/08 12:07:39 arcadia Exp $ 
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

-- Module       : ayacc_separates.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:28:51
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxayacc_separates.ada

-- $Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/ayacc_separates.a,v 1.1 88/08/08 12:07:39 arcadia Exp $ 
-- $Log:	ayacc_separates.a,v $
--Revision 1.1  88/08/08  12:07:39  arcadia
--Initial revision
--
-- Revision 0.0  86/02/19  18:36:14  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  
-- Revision 0.1  88/03/16  
-- Additional argument added to allow user to specify file extension
-- to be used for generated Ada files.  -- kn


with String_Pkg;  use String_Pkg;

separate (Ayacc)
procedure Initialize is
  use Ayacc_File_Names, Options;

  Input_File, Extension, Options : String_Type := Create ("");

  type Switch is ( On , Off );

  C_Lex_Flag,
  Debug_Flag,
  Summary_Flag,
-- UMASS CODES :
  Error_Recovery_Flag,
-- END OF UMASS CODES.
  Verbose_Flag : Switch;

  Invalid_Command_Line : exception;

  procedure Get_Arguments (File           : out String_Type;
                           C_Lex          : out Switch; 
                           Debug          : out Switch;
                           Summary        : out Switch;
                           Verbose        : out Switch;
-- UMASS CODES : 
			   Error_Recovery : out Switch;
-- END OF UMASS CODES.
			   Extension      : out String_Type) is separate;
  
begin

  Get_Arguments (Input_File,
                 C_Lex_Flag,
                 Debug_Flag,
                 Summary_Flag,
                 Verbose_Flag,
-- UMASS CODES :
                 Error_Recovery_Flag,
-- END OF UMASS CODES.
		 Extension);

  New_Line;
  Put_Line ("  Ayacc (File           => """ & Value (Input_File) & """,");
  Put_Line ("         C_Lex          => " & 
                        Value (Mixed (Switch'Image(C_Lex_Flag))) & ',');
  Put_Line ("         Debug          => " & 
                        Value (Mixed (Switch'Image(Debug_Flag))) & ',');
  Put_Line ("         Summary        => " & 
                        Value (Mixed (Switch'Image(Summary_Flag))) & ',');
  Put_Line ("         Verbose        => " & 
                        Value (Mixed (Switch'Image(Verbose_Flag))) & ",");
-- UMASS CODES :
  Put_Line ("         Error_Recovery => " &
                        Value (Mixed (Switch'Image(Error_Recovery_Flag))) & ");");
-- END OF UMASS CODES.
  New_Line;

  if C_Lex_Flag = On then
    Options := Options & Create ("i");
  end if;

  if Debug_Flag = On then
    Options := Options & Create ("d");
  end if;

  if Summary_Flag = On then
    Options := Options & Create ("s");
  end if;

  if Verbose_Flag = On then
    Options := Options & Create ("v");
  end if;

-- UMASS CODES :
  if Error_Recovery_Flag = On then
    Options := Options & Create ("e");
  end if;
-- END OF UMASS CODES.

  Set_File_Names (Value (Input_File), Value(Extension));
  Set_Options    (Value (Options));

exception
  when Invalid_Command_Line =>
    raise Illegal_Argument_List;
end Initialize;
