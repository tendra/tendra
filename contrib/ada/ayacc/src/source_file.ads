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

-- Module       : source_file.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:35:54
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxsource_file.ada

-- $Header: source_file.a,v 0.1 86/04/01 15:12:23 ada Exp $ 
-- $Log:	source_file.a,v $
-- Revision 0.1  86/04/01  15:12:23  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:41:53  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  


package Source_File is

    --.  This package provides input from the source file to the lexical
    --.  analyzer.
    --.  UNGET will work to unget up to one character. You can unget more
    --.  characters until you try to unget an EOLN where the exception
    --.  PUSHBACK_ERROR is raised.
    --.  The next character in the input stream
    --.  can be looked at using PEEK_NEXT_CHAR without affecting the input
    --.  stream.


    procedure  Open;
    procedure  Close;

    procedure  Get_Char   (Ch: out Character);
    procedure  Unget_Char (Ch: in Character);

    function   Peek_Next_Char      return  Character;
    function   Is_End_of_File      return  Boolean;
    function   Source_Line_Number  return  Natural;

--RJS: Added to make internal Ayacc buffers consistent with
--     source line length. ----v
    function Maximum_Line_Length return Natural;

    Eof  : constant Character := Ascii.Nul;
    Eoln : constant Character := Ascii.Lf;


    procedure Print_Context_Lines;
    --.  Prints the previous line followed by the current line 
    --.  followed by a pointer to the position of the source file.
    --.  Intended for printing error messages.

    procedure Read_Line(Source_Line: out String; Last: out Natural);

    --.  Used to dump the contents of the
    --.  source file one line at a time. It is intended to be be used
    --.  to dump the Ada section code (after the third %%) of the 
    --.  source file.


    Pushback_Error : exception;

end Source_File;
