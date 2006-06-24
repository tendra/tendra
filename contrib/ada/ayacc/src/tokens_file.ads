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

-- Module       : tokens_file.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:38:10
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxtokens_file.ada

-- $Header: tokens_file.a,v 0.1 86/04/01 15:14:22 ada Exp $ 
-- $Log:	tokens_file.a,v $
-- Revision 0.1  86/04/01  15:14:22  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:54:11  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  


package Tokens_File is

    procedure Open;

    procedure Start_Tokens_Package;
    function Tokens_Package_Header_Has_Been_Generated return Boolean;
    --| Returns:  True iff Start_Tokens_Package has been called.

    procedure Complete_Tokens_Package;

    procedure Make_C_Lex_Package;  -- yylex that interfaces to C!!!
				   -- Creates the #define also!!
    procedure Close;

    procedure Write (S : in String);
    procedure Writeln(S: in String); 

end Tokens_File;
