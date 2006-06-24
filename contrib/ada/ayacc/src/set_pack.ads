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

-- Module       : set_pack.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:34:47
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxset_pack.ada

-- $Header: set_pack.a,v 0.1 86/04/01 15:11:51 ada Exp $ 
-- $Log:	set_pack.a,v $
-- Revision 0.1  86/04/01  15:11:51  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:41:22  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

-- Uses the predefined equality operator "=" on variables of type Universe
generic

    type Universe is private;
    with function "<" (Element_1, Element_2: Universe) return Boolean;

package Set_Pack is

    type Set  is  limited private;

    procedure Make_Null (Set_1: in out Set);

    procedure Insert (Element : in Universe; Into  : in out Set);
    procedure Insert (Set_1   : in Set;      Into  : in out Set);
    procedure Delete (Element : in Universe; From  : in out Set);
    procedure Assign (Object  : in out Set;  Value : in Set);

    -- Nulls value ! 
    procedure Fassign(Object  : in out Set;  Value : in out Set); 

    function  Is_Member (Element: Universe; Of_Set: Set) return Boolean;
    function  Is_Empty  (Set_1: Set) return Boolean;
    function  Size_of   (Set_1: Set) return Natural;

    function "=" (Set_1 : Set; Set_2 : Set) return Boolean;


    type Set_Iterator is limited private;

    procedure Initialize (Iterator : in out Set_Iterator; Using : in Set);
    function  More (Iterator: Set_Iterator) return Boolean;
    procedure Next (Iterator: in out Set_Iterator; Element: out Universe);

    No_More_Elements : exception;
    -- raised if you call NEXT when MORE is false.


--RJS
    pragma inline(is_empty, size_of, more, next);

private

    type Cell;
    type Link is access Cell;

    type Set is
	record
	    Size : Natural;
	    Head : Link     := null;
	end record;

    type Set_Iterator is new Link;

end Set_Pack;
