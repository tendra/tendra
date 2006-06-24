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

-- Module       : symbol_table_body.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:37:53
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxsymbol_table_body.ada

-- $Header: symbol_table_body.a,v 0.1 86/04/01 15:13:55 ada Exp $ 
-- $Log:	symbol_table_body.a,v $
-- Revision 0.1  86/04/01  15:13:55  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:54:02  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

package body Symbol_Table is 

  SCCS_ID : constant String := "@(#) symbol_table_body.ada, Version 1.2";


    
    Next_Free_Terminal     : Grammar_Symbol :=  0;
    Next_Free_Nonterminal  : Grammar_Symbol := -1;

    Start_Symbol_Pos, End_Symbol_Pos : Grammar_Symbol;

    type String_Pointer is access String;

    type Table_Entry(ID : Grammar_Symbol);
    type Entry_Pointer is access Table_Entry;

    type Table_Entry(ID :Grammar_Symbol) is
	record
	    Name : String_Pointer;
	    Next : Entry_Pointer;
	    case ID is
		when 0..Grammar_Symbol'Last =>   -- Terminal
		    Prec  : Precedence;
		    Assoc : Associativity;
		when others =>                   -- Nonterminal
		    null;
	    end case;
	end record;

    Hash_Table_Size : constant := 613;    -- A large prime number

    type Hash_Index is range 0..Hash_Table_Size-1;

    Hash_Table : array(Hash_Index) of Entry_Pointer;


    --
    --    Create a 'dynamic' array for looking up an entry
    --    for a given grammar_symbol.
    --


    Block_Size : constant Grammar_Symbol := 100;
    type Lookup_Array is 
	array(Grammar_Symbol range 0..Block_Size-1) of Entry_Pointer;
    type Block;
    type Block_Pointer is access Block;
    type Block is
	record
	    Lookup : Lookup_Array;
	    Next   : Block_Pointer := null;
	end record;


    -- have separate blocks for terminals and nonterminals.

    Terminal_Blocks, Nonterminal_Blocks : Block_Pointer := new Block;

    procedure Make_Lookup_Table_Entry
	(ID        : in Grammar_Symbol;
	 Entry_Ptr : in Entry_Pointer) is

	ID_Block     : Block_Pointer;
	Block_Number : Integer;

    begin
	if ID >= 0  then
	    ID_Block := Terminal_Blocks;
	else
	    ID_Block := Nonterminal_Blocks;
	end if;
	Block_Number := Integer (abs ID / Block_Size);

	for I in 1..Block_Number loop
	    if ID_Block.Next = null then
		ID_Block.Next := new Block;
	    end if;
	    ID_Block := ID_Block.Next;
	end loop;
	ID_Block.Lookup((abs ID) mod Block_Size) := Entry_Ptr;
    end Make_Lookup_Table_Entry;

    function Get_Lookup_Table_Entry(ID: Grammar_Symbol) return Entry_Pointer is
	ID_Block : Block_Pointer;
    begin
	if ID >= 0 then
	    ID_Block := Terminal_Blocks;
	else
	    ID_Block := Nonterminal_Blocks;
	end if;
	for I in 1.. abs ID / Block_Size loop
	    ID_Block := ID_Block.Next;
	end loop;
	return ID_Block.Lookup((abs ID) mod Block_Size);
    end Get_Lookup_Table_Entry;



    -- some day someone should put in a good hash function.
    function Hash_Value (S : String) return Hash_Index is
	H   : Integer;
	Mid : Integer;
    begin
	Mid := (S'First + S'Last) / 2;
	H := ((Character'Pos(S(S'First)) +
	       Character'Pos(S(Mid)) +
	       Character'Pos(S(S'Last)))
	       * S'Length * 16 ) mod Hash_Table_Size;
	return Hash_Index(H);
    end Hash_Value;



    function Insert_Identifier (Name: in String) return Grammar_Symbol is

	Index : Hash_Index;
	Entry_Ptr : Entry_Pointer;

    begin

	Index := Hash_Value(Name);

	Entry_Ptr := Hash_Table(Index);

	if Entry_Ptr = null then

	    Entry_Ptr           :=  new Table_Entry(Next_Free_Nonterminal);
	    Entry_Ptr.Name      :=  new String(1..Name'Length);
	    Entry_Ptr.Name.all  :=  Name;
	    Hash_Table(Index)   :=  Entry_Ptr;

	    Make_Lookup_Table_Entry(Next_Free_Nonterminal, Entry_Ptr);
	    Next_Free_Nonterminal  :=  Next_Free_Nonterminal - 1;
	
	else

	    loop
		if Entry_Ptr.Name.all = Name then
		    return Entry_Ptr.ID;
		end if;
		if Entry_Ptr.Next = null then
		    exit;
		end if;
		Entry_Ptr := Entry_Ptr.Next;
	    end loop;

	    Entry_Ptr.Next         := new Table_Entry(Next_Free_Nonterminal);
	    Entry_Ptr              := Entry_Ptr.Next;
	    Entry_Ptr.Name         :=  new String(1..Name'Length);
	    Entry_Ptr.Name.all     :=  Name;

	    Make_Lookup_Table_Entry(Next_Free_Nonterminal, Entry_Ptr);
	    Next_Free_Nonterminal  :=  Next_Free_Nonterminal - 1;

	end if;

	return Next_Free_Nonterminal + 1;

    end Insert_Identifier;

    function Insert_Terminal
	(Name  :  String;
	 Prec  :  Precedence := 0; 
	 Assoc :  Associativity := Undefined) return Grammar_Symbol is

	Index : Hash_Index;
	Entry_Ptr : Entry_Pointer;

    begin

	Index := Hash_Value(Name);

	Entry_Ptr := Hash_Table(Index);

	if Entry_Ptr = null then

	    Entry_Ptr           :=  new Table_Entry(Next_Free_Terminal);
	    Entry_Ptr.Name      :=  new String(1..Name'Length);
	    Entry_Ptr.Name.all  :=  Name;
	    Entry_Ptr.Assoc     :=  Assoc;
	    Entry_Ptr.Prec      :=  Prec;
	    Hash_Table(Index)   :=  Entry_Ptr;

	    Make_Lookup_Table_Entry(Next_Free_Terminal, Entry_Ptr);
	    Next_Free_Terminal  :=  Next_Free_Terminal + 1;
	
	else

	    loop
		if Entry_Ptr.Name.all = Name then
		    if Entry_Ptr.ID < 0 then    -- Look out for nonterminals
			raise Illegal_Entry;
		    end if;
		    if Prec /= 0 then
			if Entry_Ptr.Prec /= 0 then
			    raise Redefined_Precedence_Error;
			end if;
			Entry_Ptr.Prec  := Prec;
			Entry_Ptr.Assoc := Assoc;
		    end if;
		    return Entry_Ptr.ID;
		end if;
		if Entry_Ptr.Next = null then
		    exit;
		end if;
		Entry_Ptr := Entry_Ptr.Next;
	    end loop;

	    Entry_Ptr.Next      := new Table_Entry(Next_Free_Terminal);
	    Entry_Ptr           := Entry_Ptr.Next;
	    Entry_Ptr.Name      :=  new String(1..Name'Length);
	    Entry_Ptr.Name.all  :=  Name;
	    Entry_Ptr.Assoc     :=  Assoc;
	    Entry_Ptr.Prec      :=  Prec;
	    
	    Make_Lookup_Table_Entry(Next_Free_Terminal, Entry_Ptr);
	    Next_Free_Terminal  :=  Next_Free_Terminal + 1;

	end if;

	return Next_Free_Terminal - 1;

    end Insert_Terminal;

    function Get_Associativity (ID: Grammar_Symbol) return Associativity is
    begin
	return Get_Lookup_Table_Entry(ID).Assoc;
    end;

    function Get_Precedence    (ID: Grammar_Symbol) return Precedence is
    begin
	return Get_Lookup_Table_Entry(ID).Prec;
    end;

    function Get_Symbol_Name   (ID: Grammar_Symbol) return String is
    begin
	return Get_Lookup_Table_Entry(ID).Name.all;
    end;


    function First_Symbol (Kind: Symbol_Type) return Grammar_Symbol is
    begin
	if Kind = Terminal then
	    return 0;
	else
	    return Next_Free_Nonterminal + 1;
	end if;
    end;

    function Last_Symbol (Kind: Symbol_Type) return Grammar_Symbol is
    begin
	if Kind = Terminal then
	    return Next_Free_Terminal - 1;
	else
	    return -1;
	end if;
    end;

    function First_Terminal  return Grammar_Symbol is
    begin
	return 0;
    end;

    function Last_Terminal   return Grammar_Symbol is
    begin
	return Next_Free_Terminal - 1;
    end;

    function Start_Symbol return Grammar_Symbol is
    begin
	return Start_Symbol_Pos;
    end;

    function End_Symbol   return Grammar_Symbol is
    begin
	return End_Symbol_Pos;
    end;

    function Is_Terminal    (ID: Grammar_Symbol) return Boolean is
    begin
	return ID >= 0;
    end;

    function Is_Nonterminal (ID: Grammar_Symbol) return Boolean is
    begin
	return ID < 0;
    end;

begin
    End_Symbol_Pos   := Insert_Terminal("END_OF_INPUT");
    Start_Symbol_Pos := Insert_Identifier("$accept");
    -- declare a dummy symbol to insert the "error" token.
    declare
	Dummy_Sym : Grammar_Symbol;
    begin
	Dummy_Sym := Insert_Terminal("ERROR");
    end;
end Symbol_Table;
