-- $Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/file_names.a,v 1.2 88/11/28 13:38:59 arcadia Exp $ 

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

-- Module       : file_names.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:29:16
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxfile_names.ada

-- $Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/file_names.a,v 1.2 88/11/28 13:38:59 arcadia Exp $ 
-- $Log:	file_names.a,v $
--Revision 1.2  88/11/28  13:38:59  arcadia
--Modified Get_Unit_Name function to accept legal Ada identifiers.
--
--Revision 1.1  88/08/08  12:11:56  arcadia
--Initial revision
--

-- Revision 0,2  88/03/16  
-- Set file names modified to include a file extension parameter.

-- Revision 0.1  86/04/01  15:04:19  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:36:22  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

    -- The collection of all file names used by Ayacc -- 

with Ada.Characters.Handling; use Ada.Characters.Handling;

package Ayacc_File_Names is

    procedure Set_File_Names(Input_File, Extension: in String);
    -- Sets the initial value of the file names
    -- according to the INPUT_FILE.

    function  Get_Source_File_Name        return String;
    function  Get_Out_File_Name           return String;
    function  Get_Verbose_File_Name       return String;
    function  Get_Template_File_Name      return String;
    function  Get_Actions_File_Name       return String;
    function  Get_Shift_Reduce_File_Name  return String;
    function  Get_Goto_File_Name          return String;
    function  Get_Tokens_File_Name        return String;
-- UMASS CODES :
    function  Get_Error_Report_File_Name  return String;
    function  Get_Listing_File_Name       return String;
-- END OF UMASS CODES.
    function  Get_C_Lex_File_Name	  return String;
    function  Get_Include_File_Name	  return String;


--RJS ==========================================

  function C_Lex_Unit_Name               return String;
  function Goto_Tables_Unit_Name         return String;
  function Shift_Reduce_Tables_Unit_Name return String;
  function Tokens_Unit_Name              return String;
  function Main_Unit_Name                return String;
 
-- UMASS CODES :
  function Error_Report_Unit_Name        return String;
-- END OF UMASS CODES.
--RJS ==========================================


    Illegal_File_Name: exception;
    -- Raised if the file name does not end with ".y"

end Ayacc_File_Names;
