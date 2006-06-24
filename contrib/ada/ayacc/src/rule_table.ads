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

-- Module       : rule_table.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:34:14
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxrule_table.ada

-- $Header: rule_table.a,v 0.1 86/04/01 15:11:37 ada Exp $ 
-- $Log:	rule_table.a,v $
-- Revision 0.1  86/04/01  15:11:37  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:40:56  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

with Symbol_Table;
use  Symbol_Table;  
package Rule_Table is
    -- This package is used to store and access the rules
    -- of the input grammar.

    Max_Rules  : constant := 1_000;       -- An arbitrary upper bound.
                                          -- if you raise this above 3_000
                                          -- you will also need to make
                                          -- changes in parse_table_body
                                          -- and parse_template_file.
    type Rule is range 0..Max_Rules - 1;


    function  Make_Rule(LHS: Grammar_Symbol) return Rule;

    procedure Append_RHS(R: in Rule; RHS: in Grammar_Symbol);

    function  Get_LHS (R: Rule)                      return Grammar_Symbol;
    function  Get_RHS (R: Rule; Position: Positive)  return Grammar_Symbol;

    function  Get_Null_Pos         (R: Rule)  return Natural;
    function  Get_Rule_Precedence  (R: Rule)  return Precedence;

    function  Length_of(R: Rule) return Natural;

    function  First_Rule return Rule;
    function  Last_Rule  return Rule;

    function  Number_of_Rules return Natural;

    procedure Set_Rule_Precedence (R: in Rule; Prec:     in Precedence); 
    procedure Set_Null_Pos        (R: in Rule; Position: in Natural); 

    procedure Handle_Nested_Rule (Current_Rule : in out Rule); 


--RJS    pragma inline(get_lhs, get_null_pos, get_rule_precedence, length_of);
    --& pragma inline(first_rule, last_rule);
   
end Rule_Table;
