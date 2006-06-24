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

-- Module       : symbol_table.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:37:38
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxsymbol_table.ada

-- $Header: symbol_table.a,v 0.1 86/04/01 15:13:41 ada Exp $ 
-- $Log:	symbol_table.a,v $
-- Revision 0.1  86/04/01  15:13:41  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:47:05  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  


package Symbol_Table is 
    
    type  Symbol_Type    is  (Start, Nonterminal, Terminal);  

    type  Grammar_Symbol is range -5_000..5_000;
    type  Precedence     is range 0..5_000;  

    type  Associativity  is (Left_Associative, Right_Associative, 
                             Nonassociative, Undefined);

    function Insert_Identifier(Name: in String) return Grammar_Symbol; 

    function Insert_Terminal  (Name: String;
			       Prec: Precedence := 0; 
                               Assoc: Associativity := Undefined)
	     return Grammar_Symbol; 

    function Get_Associativity(ID: Grammar_Symbol) return Associativity;
    function Get_Precedence   (ID: Grammar_Symbol) return Precedence;
    function Get_Symbol_Name  (ID: Grammar_Symbol) return String; 

    function First_Symbol     (Kind: Symbol_Type) return Grammar_Symbol;
    function Last_Symbol      (Kind: Symbol_Type) return Grammar_Symbol;

    function Start_Symbol return Grammar_Symbol;  
    function End_Symbol   return Grammar_Symbol; 

    function Is_Terminal    (ID: Grammar_Symbol) return Boolean;
    function Is_Nonterminal (ID: Grammar_Symbol) return Boolean;

    Illegal_Entry, Redefined_Precedence_Error : exception;

--RJS    pragma inline(is_terminal, is_nonterminal);

end Symbol_Table;  
