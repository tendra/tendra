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

-- Module       : ragged.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:34:00
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxragged.ada

-- $Header: ragged.a,v 0.1 86/04/01 15:11:22 ada Exp $ 
-- $Log:	ragged.a,v $
-- Revision 0.1  86/04/01  15:11:22  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:40:45  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

-- Remeber to get rid of rval as soon as all bugs have been eliminated 
-- from routines that use this package.

generic 
    type Row_Index is (<>); 
    type Col_Index is (<>); 
    type Item is limited private;  
    with procedure Null_Value(Value : in out Item); 

package Ragged is 

    -- Cell and index should be private but for efficency and for subtle 
    -- problems that arise when type item is implemeted as a limited private 
    -- in an external package, cell and index are kept visible.

    type Cell; 
    type Index       is access Cell;
    pragma Controlled(Index); 

    type Hidden_Type is limited private;

    type Cell is   
        record 
            Value  : Item; 
            Hidden : Hidden_Type; 
        end record; 

    -- Use for retrieving the value of array(x,y). Raises value range 
    -- error if no such location has been allocated yet.
    -- eg: value := rval(x,y).value; 

    function  Rval(X: Row_Index; Y: Col_Index) return Index; 


    -- Use for setting a value in array(x,y). Allocates new storage 
    -- if the location does not exist yet. Can also use it if you 
    -- require a preinitialization value
    -- eg: lval(x,y).value := value; 
    --     if lval(x,y).value = 0 then ... 

    function  Lval(X: Row_Index; Y: Col_Index) return Index; 
    

    procedure Make_Array(Lower, Upper: Row_Index); 


    procedure Initialize(Iterator : out Index; Row : Row_Index); 


    procedure Next(Iterator : in out Index);  


    procedure Free_Array; 

    Value_Range_Error : exception; 

private 
    type Hidden_Type is 
        record 
           Column : Col_Index; 
           Next   : Index;
        end record;

end Ragged;  
