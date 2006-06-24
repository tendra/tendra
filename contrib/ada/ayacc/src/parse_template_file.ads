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

-- Module       : parse_template_file_.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:33:46
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxparse_template_file_.ada

-- $Header: parse_template_file.a,v 0.1 86/04/01 15:09:47 ada Exp $ 
-- $Log:	parse_template_file.a,v $
-- Revision 0.1  86/04/01  15:09:47  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:40:09  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

package Parse_Template_File is

    Eof : constant Character := Ascii.Nul;

    procedure Open; 
    procedure Read (S: out String; Length : out Integer);
    procedure Close;
    function  Is_End_of_File return Boolean;

end Parse_Template_File;
