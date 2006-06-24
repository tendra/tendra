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

-- Module       : symbol_info_body.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:37:23
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxsymbol_info_body.ada

-- $Header: symbol_info_body.a,v 0.1 86/04/01 15:13:25 ada Exp $ 
-- $Log:	symbol_info_body.a,v $
-- Revision 0.1  86/04/01  15:13:25  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:46:56  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  


with Text_IO;
package body Symbol_Info is

  SCCS_ID : constant String := "@(#) symbol_info_body.ada, Version 1.2";



  Rcs_ID : constant String := "$Header: symbol_info_body.a,v 0.1 86/04/01 15:13:25 ada Exp $";

    type Nullables_Array is array (Grammar_Symbol range <>) of Boolean;
    type Nullables_Array_Pointer is access Nullables_Array;

    Nullables : Nullables_Array_Pointer;

    --
    --  initializes the elements of the array pointed to by 
    --  NULLABLES to false if they cannot derive the empty
    --  string and TRUE if they can derive the empty string.
    --
    procedure Find_Nullables is
	Sym_Position      : Natural;
	Nonterminal_Sym   : Grammar_Symbol;
	RHS_Sym           : Grammar_Symbol;
	No_More_Added     : Boolean;
	Rule_Length       : Natural;
    begin

--&  Verdix 4.06 bug
--&	nullables.all := (nullables.all'range => false);
--&  bug fix
	for S in Nullables.all'range loop
	    Nullables(S) := False;
	end loop;
--&  end bug fix

	-- First determine the symbols that are trivially nullable.
	for R in First_Rule..Last_Rule loop
	    if Length_of(R) = 0 then
		Nullables(Get_LHS(R)) := True;
	    end if;
	end loop;

	loop
	    No_More_Added := True;
	    for R in First_Rule..Last_Rule loop
		Nonterminal_Sym := Get_LHS(R);
		if not Nullables(Nonterminal_Sym) then
		    Sym_Position := 1;
		    Rule_Length := Length_of(R);
		    while Sym_Position <= Rule_Length loop
			RHS_Sym := Get_RHS(R, Sym_Position);
			exit when Is_Terminal(RHS_Sym) or else
			          not Nullables(RHS_Sym);
			Sym_Position := Sym_Position + 1;
		    end loop;
		    if Sym_Position > Rule_Length then 
			Nullables(Nonterminal_Sym) := True;
			No_More_Added := False;
		    end if;
		end if;
	    end loop;
	    exit when No_More_Added;
	end loop;

    end Find_Nullables;


    function Is_Nullable(Sym: Grammar_Symbol) return Boolean is
    begin
	return Nullables(Sym);
    end Is_Nullable;

    procedure Make_Rules_Null_Position is
	Null_Position : Integer;
	RHS_Sym       : Grammar_Symbol;
    begin

	for R in First_Rule..Last_Rule loop

	    Null_Position := Length_of(R);

	    while Null_Position /= 0 loop
		RHS_Sym := Get_RHS(R, Null_Position);
		if Is_Terminal(RHS_Sym) or else not Nullables(RHS_Sym) then
		    exit;
		end if;
		Null_Position := Null_Position - 1;
	    end loop;

	    Set_Null_Pos(R, Null_Position);

	end loop;

    end Make_Rules_Null_Position;


    procedure Find_Rule_Yields is
	use Text_IO;  -- To report undefined nonterminals

	Found_Undefined_Nonterminal: Boolean := False;
	Current_Index : Yield_Index;
    begin
	    --  First initialize the arrays to the correct size  --
	
	Nonterminal_Yield := new Rule_Array
	    (Yield_Index(First_Rule)..Yield_Index(Last_Rule));

	Nonterminal_Yield_Index := new Offset_Array
	    (First_Symbol(Nonterminal)..Last_Symbol(Nonterminal) + 1);

	Current_Index := Yield_Index(First_Rule);
	for Sym in First_Symbol(Nonterminal)..Last_Symbol(Nonterminal) loop
	    Nonterminal_Yield_Index(Sym) := Current_Index;
	    for R in First_Rule..Last_Rule loop
		if Get_LHS(R) = Sym then
		    Nonterminal_Yield(Current_Index) := R;
		    Current_Index := Current_Index + 1;
		end if;
	    end loop;
	    if Nonterminal_Yield_Index(Sym) = Current_Index then
		Found_Undefined_Nonterminal := True;
		Put_Line ("Ayacc: Nonterminal " & Get_Symbol_Name(Sym) &
		          " does not appear on the " &
                          "left hand side of any rule.");
	    end if;
	end loop;

	Nonterminal_Yield_Index(Last_Symbol(Nonterminal) + 1) := Current_Index;
	-- So you can easily determine the end of the list in loops
	-- bye comparing the index to the index of sym+1.

	if Found_Undefined_Nonterminal then
	    raise Undefined_Nonterminal;
	end if;

    end Find_Rule_Yields;
	    

    -- First detect nonterminals that can't be derived from the start symbol.
    -- Then detect nonterminals that don't derive any token string.
    --
    -- NOTE: We should use Digraph to do this stuff when we
    --       have time to put it in.
    procedure Check_Grammar is
	use Text_IO;    -- to report errors

	type Nonterminal_Array is array (Grammar_Symbol range <>) of Boolean;

	Ok : Nonterminal_Array
	    (First_Symbol(Nonterminal)..Last_Symbol(Nonterminal));

	More         : Boolean;
	I            : Natural;
	Rule_Length  : Natural;
	Found_Error  : Boolean := False;

	RHS_Sym, LHS_Sym: Grammar_Symbol;

	Bad_Grammar : exception;  -- Move this somewhere else!!!

    begin

	    -- check if each nonterminal is deriveable from the start symbol --

       -- To be added! We should use digraph for this


	    -- check if each nonterminal can derive a terminal string. --

--& Verdix 4.06 bug
--&     ok := (ok'range => false);
--& bug fix
        for S in Ok'range loop
	    Ok(S) := False;
	end loop;
--& end bug fix
   
	More := True;
	while More loop
	    More := False;
	    for R in First_Rule..Last_Rule loop
		LHS_Sym := Get_LHS(R);
		if not Ok(LHS_Sym) then
		    I := 1;
		    Rule_Length := Length_of(R);
		    while I <= Rule_Length loop
			RHS_Sym := Get_RHS(R, I);
			if Is_Nonterminal(RHS_Sym) and then
			    not Ok(RHS_Sym)
			then
			    exit;
			end if;
			I := I + 1;
		    end loop;
		    if I > Rule_Length then -- nonterminal can derive terminals
			Ok(LHS_Sym) := True;
			More := True;
		    end if;
		end if;
	    end loop;
	end loop;

	for J in Ok'range loop
	    if not Ok(J) then
		Put_Line ("Ayacc: Nonterminal " & Get_Symbol_Name(J) &
		          " does not derive a terminal string");
		Found_Error := True;
	    end if;
	end loop;

	if Found_Error then
	    raise Bad_Grammar;
	end if;

    end Check_Grammar;

	    

    procedure Initialize is
    begin

	Nullables := new Nullables_Array
	    (First_Symbol(Nonterminal) .. Last_Symbol(Nonterminal));

	Find_Rule_Yields;
	Check_Grammar;
	Find_Nullables;
	Make_Rules_Null_Position;

    end Initialize;


end Symbol_Info;
