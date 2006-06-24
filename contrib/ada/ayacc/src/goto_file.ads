-- $Header: /dc/uc/self/arcadia/ayacc/src/RCS/goto_file.a,v 1.2 1993/05/31 22:36:35 self Exp self $ 

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

-- Module       : goto_file.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:29:33
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxgoto_file.ada

-- $Header: /dc/uc/self/arcadia/ayacc/src/RCS/goto_file.a,v 1.2 1993/05/31 22:36:35 self Exp self $ 
-- $Log: goto_file.a,v $
-- Revision 1.2  1993/05/31  22:36:35  self
-- added exception handler when opening files
--
-- Revision 1.1  1993/05/31  22:14:38  self
-- Initial revision
--
--Revision 1.1  88/08/08  13:43:29  arcadia
--Initial revision
--
-- Revision 0.1  86/04/01  15:04:27  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:36:31  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

package Goto_File is

    procedure Open_Write;
    procedure Close_Write;
    procedure Write(S: in String); 
    procedure Write_Line(S: in String);
    procedure Write(C: in Character);

end Goto_File;
