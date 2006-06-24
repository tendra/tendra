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

-- Module       : lr0_machine.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:30:58
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxlr0_machine.ada

-- $Header: lr0_machine.a,v 0.1 86/04/01 15:06:19 ada Exp $ 
-- $Log:	lr0_machine.a,v $
-- Revision 0.1  86/04/01  15:06:19  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:37:14  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

with Rule_Table, Symbol_Table, Set_Pack;
use  Rule_Table, Symbol_Table;
package LR0_Machine is

    type Parse_State   is   range -1..5_000;
    Null_Parse_State   :    constant Parse_State := -1;

    type Item is
	record
	    Rule_ID      : Rule;
	    Dot_Position : Natural;
	end record;

    type Transition is
	record
	    Symbol   : Grammar_Symbol;
	    State_ID : Parse_State;
	end record;

    function "<" (Item_1,  Item_2  : Item)        return Boolean;
    function "<" (Trans_1, Trans_2 : Transition)  return Boolean;


    package Parse_State_Set_Pack     is new Set_Pack(Parse_State,    "<");
    package Item_Set_Pack            is new Set_Pack(Item,           "<");
    package Transition_Set_Pack      is new Set_Pack(Transition,     "<");
    package Grammar_Symbol_Set_Pack  is new Set_Pack(Grammar_Symbol, "<");

    subtype Parse_State_Set          is Parse_State_Set_Pack.Set;
    subtype Item_Set                 is Item_Set_Pack.Set;
    subtype Transition_Set           is Transition_Set_Pack.Set;
    subtype Grammar_Symbol_Set       is Grammar_Symbol_Set_Pack.Set;

    subtype Parse_State_Iterator     is Parse_State_Set_Pack.Set_Iterator; 
    subtype Item_Iterator            is Item_Set_Pack.Set_Iterator; 
    subtype Transition_Iterator      is Transition_Set_Pack.Set_Iterator; 
    subtype Grammar_Symbol_Iterator  is Grammar_Symbol_Set_Pack.Set_Iterator;


    procedure LR0_Initialize;    -- must be called first.

    function First_Parse_State  return  Parse_State;
    function Last_Parse_State   return  Parse_State;


    function Get_Goto
	(State_ID : Parse_State;
	 Sym      : Grammar_Symbol) return Parse_State;


    -- Returns the predecessor states of STATE_ID and the item I.
    -- Must be called with PRED_SET empty!
    procedure Get_Pred_Set
	(State_ID : in Parse_State;
	 I        : in Item;
	 Pred_Set : in out Parse_State_Set);




    type Transition_Type is (Terminals, Nonterminals, Grammar_Symbols);

    procedure Get_Transitions
	(State_ID : in     Parse_State;
	 Kind     : in     Transition_Type;
	 Set_1    : in out Transition_Set);

    procedure Get_Transition_Symbols
	(State_ID : in     Parse_State;
	 Kind     : in     Transition_Type;
	 Set_1    : in out Grammar_Symbol_Set);

    procedure Get_Kernel
	(State_ID : in     Parse_State;
	 Set_1    : in out Item_Set);

    procedure Closure (Set_1 : in out Item_Set);



    --
    --  The following routines allow the user to iterate over the 
    --  items in the kernel of a particular state.
    --

    type Kernel_Iterator is limited private;
    procedure Initialize
            (Iterator : in out Kernel_Iterator;
	     State_ID : in Parse_State);

    function  More(Iterator : Kernel_Iterator) return Boolean;
    procedure Next(Iterator : in out Kernel_Iterator; I : out Item);


    --
    --  The following routines allow the user to iterate over the 
    --  nonterminal transitions of a particular state
    --
    type Nt_Transition_Iterator is limited private;
    procedure Initialize
	(Iterator : in out Nt_Transition_Iterator;
	 State_ID : in Parse_State);

    function  More (Iterator : Nt_Transition_Iterator) return Boolean;
    procedure Next 
	(Iterator : in out Nt_Transition_Iterator;
	 Trans : out Transition);


    -- The following routines allow iteration over the Terminal transitions
    -- of a particular state.

    type T_Transition_Iterator is limited private;  -- For Terminals
    procedure Initialize
	(Iterator : in out T_Transition_Iterator;
	 State_ID : in Parse_State);

    function  More (Iterator : T_Transition_Iterator) return Boolean;
    procedure Next 
	(Iterator : in out T_Transition_Iterator;
	 Trans : out Transition);



    To_Many_States      : exception;
    No_More_Iterations  : exception;
    State_Out_of_Bounds : exception;

--RJS    pragma inline(more); --DEC Ada Bug: , next);

private

    type Item_Array_Index is range 0..5_000; -- An arbitrarily big number
    type Item_Array;
    type Item_Array_Pointer is access Item_Array;
    type Kernel_Iterator is
	record
	    Kernel  : Item_Array_Pointer;
	    Curser  : Item_Array_Index;
	end record;


    type Transition_Array;
    type Transition_Array_Pointer is access Transition_Array;
    type Nt_Transition_Iterator is
	record
	    Nonterm_Trans : Transition_Array_Pointer;
	    Curser        : Integer;  -- Use a derived type instead ???
	end record;

    type T_Transition_Iterator is
	record
	    Term_Trans  : Transition_Array_Pointer;
	    Curser      : Integer;
	end record;

end LR0_Machine;
