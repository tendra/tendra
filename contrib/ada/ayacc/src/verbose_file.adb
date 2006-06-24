-- $Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/verbose_file_body.a,v 1.1 88/08/08 14:44:42 arcadia Exp $ 

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

-- Module       : verbose_file_body.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:38:50
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxverbose_file_body.ada

-- $Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/verbose_file_body.a,v 1.1 88/08/08 14:44:42 arcadia Exp $ 
-- $Log:	verbose_file_body.a,v $
--Revision 1.1  88/08/08  14:44:42  arcadia
--Initial revision
--
-- Revision 0.1  86/04/01  15:14:46  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:54:37  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  


with Text_IO, Ayacc_File_Names;
use  Text_IO;
package body Verbose_File is

  SCCS_ID : constant String := "@(#) verbose_file_body.ada, Version 1.2";



  Rcs_ID : constant String := "$Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/verbose_file_body.a,v 1.1 88/08/08 14:44:42 arcadia Exp $";

    V_File : File_Type;		-- The verbose file
    procedure Open is
	use Ayacc_File_Names;
    begin
	Create(V_File, Out_File, Get_Verbose_File_Name);
    end Open;

    procedure Close is
    begin
	Close(V_File);
    end Close;


    procedure Write(Ch : in Character) is
    begin
	Put(V_File, Ch);
    end Write;

    procedure Write(S : in String) is
    begin
	Put(V_File, S);
    end Write;

    procedure Write_Line(S : in String := "") is
    begin
	Put_Line(V_File, S);
    end Write_Line;


    procedure Print_Grammar_Symbol(Sym: in Grammar_Symbol) is
    begin
	Put(V_File, Get_Symbol_Name(Sym));
    end;

    procedure Print_Item(Item_1 : in Item) is
    begin
	Put(V_File, "(" & Rule'Image(Item_1.Rule_ID) & ")  ");
	Put(V_File, Get_Symbol_Name(Get_LHS(Item_1.Rule_ID)) & Ascii.Ht & ": ");
	if Item_1.Dot_Position = 0 then
	    Put(V_File, "_ ");
	end if;
	for I in 1..Length_of(Item_1.Rule_ID) loop
	    Put(V_File, Get_Symbol_Name(Get_RHS(Item_1.Rule_ID, I)));
	    Put(V_File, " ");
	    if I = Item_1.Dot_Position then
		Put(V_File, "_ ");
	    end if;
	end loop;
    end Print_Item;

    procedure Print_Item_Set(Set_1: in Item_Set) is
	use Item_Set_Pack;
	Iterator  : Item_Iterator;
	Temp_Item : Item;
    begin
	Initialize(Iterator, Set_1);
	while More(Iterator) loop
	    Next(Iterator, Temp_Item);
	    Print_Item(Temp_Item);
	    New_Line(V_File);
	end loop;
    end Print_Item_Set;


    procedure Print_Rule(R : in Rule) is
    begin
	Put(V_File, "(" & Rule'Image(R) & ")  ");
	Put(V_File, Get_Symbol_Name(Get_LHS(R)) & Ascii.Ht & ": ");
	for I in 1..Length_of(R) loop
	    Put(V_File, Get_Symbol_Name(Get_RHS(R, I)));
	    Put(V_File, " ");
	end loop;
    end Print_Rule;

end Verbose_File;
