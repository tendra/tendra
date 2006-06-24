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

-- Module       : options.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:31:39
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxoptions.ada

-- $Header: options.a,v 0.1 86/04/01 15:08:15 ada Exp $ 
-- $Log:	options.a,v $
-- Revision 0.1  86/04/01  15:08:15  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:37:34  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

package Options is

    procedure Set_Options(S: in String);
    -- SET_OPTIONS sets the debug and verbose flags according
    -- the the string S.
    -- If S contains the characters 'v' or 'V', the verbose
    -- option is set.
    -- If S contains the charactars 'c' or 'C', the vebose conflicts
    -- option is set.
    -- If S contains the characters 'd' or 'D', the debug
    -- option is set.
    -- If S contains the characters 's' or 'S', the summary option
    -- is set.
-- UMASS CODES :
    -- If S contains the characters 'e' or 'E', the error recovery 
    -- extension option is set.
-- END OF UMASS CODES.

    function Verbose return Boolean;
    -- Returns TRUE if the verbose file is to be created.

    function Verbose_Conflict return Boolean;
    -- Returns TRUE if only the states involved in conflicts
    -- are to printed.

    function Debug return Boolean;
    -- Returns TRUE if the YYPARSE procedure should generate
    -- debugging output.

    function Summary return Boolean;
    -- Returns TRUE if a summary of statistics of the generated
    -- parser should be printed.

    function Interface_to_C return Boolean;

    function Loud return Boolean;
    -- Returns TRUE if Ayacc should output useless and annoying information
    -- while it is running.

-- UMASS CODES :
    function Error_Recovery_Extension return Boolean;
    -- Returns TRUE if the codes of error recovery extension should
    -- be generated.
-- END OF UMASS CODES.

    Illegal_Option: exception;

end Options;
