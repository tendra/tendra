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

-- Module       : str_pack.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:36:46
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxstr_pack.ada

-- $Header: str_pack.a,v 0.1 86/04/01 15:13:01 ada Exp $ 
-- $Log:	str_pack.a,v $
-- Revision 0.1  86/04/01  15:13:01  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:42:23  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  


package STR_Pack is
    --  This package contains the type declarations and procedures
    --  for the minimal string minipulation needed by ayacc.

    Maximum : constant := 1024;  --RJS 120;
    subtype Index is Integer range 0 .. Maximum;

    type STR(Maximum_Length : Index) is limited private;

    function  Length_of (S: STR)  return Integer;
    function  Value_of  (S: STR)  return String;
    function  Is_Empty  (S: STR)  return Boolean;

    procedure Assign (Value: in STR;       To: in out STR);
    procedure Assign (Value: in String;    To: in out STR);
    procedure Assign (Value: in Character; To: in out STR);

    procedure Append (Tail: in Character; To: in out STR);
    procedure Append (Tail: in String;    To: in out STR);
    procedure Append (Tail: in STR;       To: in out STR);

    procedure Upper_Case(S: in out STR);
    procedure Lower_Case(S: in out STR);

    function  Upper_Case (S : in STR) return STR;
    function  Lower_Case (S : in STR) return STR;

--RJS
    pragma inline (length_of, --RJS value_of,
                   is_empty,
                   append);

private

    type STR(Maximum_Length : Index) is
	record
	    Name   : String(1..Maximum_Length);
	    Length : Index := 0;
	end record;

end STR_Pack;
