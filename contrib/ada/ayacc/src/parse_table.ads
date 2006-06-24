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

-- Module       : parse_table.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:32:58
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxparse_table.ada

-- $Header: parse_table.a,v 0.1 86/04/01 15:08:33 ada Exp $ 
-- $Log:	parse_table.a,v $
-- Revision 0.1  86/04/01  15:08:33  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:37:58  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

--  This package build the shift reduce table and the goto table and
--  writes it to the shift_reduce_file, and goto_file. If the verbose option
--  is set, the states generated and their coresponding actions are written
--  to the verobose_file.
--  The parse table produced is an LALR(1) parse table.
--  The number of conflicts resulting from the grammar
--  can be determinied by calling the funciton REDUCE_REDUCE_CONFLICTS and
--  SHIFT_REDUCE_CONFLICTS, after calling MAKE_PARSE_TABLE.

package Parse_Table is

    procedure Make_Parse_Table;

    -- These functions must be called AFTER Make_parse_Table

    function  Shift_Reduce_Conflicts      return  Natural;
    function  Reduce_Reduce_Conflicts     return  Natural;
    function  Number_of_States            return  Natural;
    function  Size_of_Goto_Table          return  Natural;
    function  Size_of_Action_Table        return  Natural;

end Parse_Table;
