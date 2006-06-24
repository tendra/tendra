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

-- Module       : lexical_analyzer.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:30:26
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxlexical_analyzer.ada

-- $Header: lexical_analyzer.a,v 0.1 86/04/01 15:05:14 ada Exp $ 
-- $Log:	lexical_analyzer.a,v $
-- Revision 0.1  86/04/01  15:05:14  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:36:57  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

with Source_File;
package Lexical_Analyzer is 


    function Get_Lexeme_Text return String;   -- Scanned text.


    type Ayacc_Token is
	(Token, Start,
	 Left, Right, Nonassoc, Prec,
         With_Clause, Use_Clause,
	 Identifier, Character_Literal, 
         Comma, Colon, Semicolon, Vertical_Bar, Left_Brace,
	 Mark, Eof_Token);

    
    function Get_Token return Ayacc_Token;
    
    
    function Line_Number return Natural;  -- Current line of source file

    
    procedure Handle_Action(Rule, Rule_Length : Integer); 


    procedure Print_Context_Lines renames Source_File.Print_Context_Lines;


    procedure Dump_Declarations; 


    Illegal_Token         : exception;


end Lexical_Analyzer;
