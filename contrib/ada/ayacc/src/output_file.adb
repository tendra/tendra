-- $Header: /dc/uc/self/arcadia/ayacc/src/RCS/output_file_body.a,v 1.2 1993/05/31 22:36:35 self Exp self $ 

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

-- Module       : output_file_body.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:32:10
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxoutput_file_body.ada

-- $Header: /dc/uc/self/arcadia/ayacc/src/RCS/output_file_body.a,v 1.2 1993/05/31 22:36:35 self Exp self $ 
-- $Log: output_file_body.a,v $
-- Revision 1.2  1993/05/31  22:36:35  self
-- added exception handler when opening files
--
-- Revision 1.1  1993/05/31  22:05:03  self
-- Initial revision
--
--Revision 1.1  88/08/08  14:16:40  arcadia
--Initial revision
--
-- Revision 0.1  86/04/01  15:08:26  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:37:50  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

with Actions_File, Ayacc_File_Names, Lexical_Analyzer, Options, Parse_Table, 
     Parse_Template_File, Source_File, Text_IO;

use  Actions_File, Ayacc_File_Names, Lexical_Analyzer, Options, Parse_Table, 
     Parse_Template_File, Source_File, Text_IO;

package body Output_File is  

  SCCS_ID : constant String := "@(#) output_file_body.ada, Version 1.2";


       
    Outfile : File_Type; 

    procedure Open_Spec is 
    begin 
       Create(Outfile, Out_File, Get_Out_File_Name & "ds"); 
    exception
       when Name_Error | Use_Error =>
            Put_Line("Ayacc: Error Opening """ & Get_Out_File_Name & "ds" & """.");
            raise;
    end Open_Spec; 

    procedure Close is 
    begin 
       Put_Line (Outfile, "end " & Main_Unit_Name & ";");
       Close(Outfile); 
    end Close; 

    procedure Open_Body is 
    begin 
       Create(Outfile, Out_File, Get_Out_File_Name & "db"); 
    exception
       when Name_Error | Use_Error =>
            Put_Line("Ayacc: Error Opening """ & Get_Out_File_Name & "db" & """.");
            raise;
    end Open_Body; 


    -- Make the parser body section by reading the source --
    -- and template files and merging them appropriately  --

    procedure Make_Output_File  is 
        Text   : String(1..260); 
        Length : Natural;
        I      : Integer; 
-- UMASS CODES :
    Umass_Codes : Boolean := False;
    -- Indicates whether or not current line of the template
    -- is the Umass codes.
    UCI_Codes_Deleted : Boolean := False;
    -- Indicates whether or not current line of the template
    -- is UCI codes which should be deleted in Ayacc-extension.
-- END OF UMASS CODES.

       procedure Copy_Chunk is
       begin
         while not Source_File.Is_End_of_File loop  
            Source_File.Read_Line(Text, Length);
            if Length > 1 then 
                I := 1; 
                while (I < Length - 1 and then Text(I) = ' ') loop 
                    I := I + 1; 
                end loop;  
	        if Text(I..I+1) = "##" then 
	            exit;
	        end if;
            end if; 
	    Put_Line(Outfile, Text(1..Length)); 
         end loop; 
       end Copy_Chunk;

    begin 
        Open_Spec; -- Open the output file.
        -- Read the first part of the source file up to '##'
        -- or to end of file.
        -- This is inteded to be put before the spec files package
        -- clause
	Copy_Chunk;

	-- Emit the package clause
        Put_Line (Outfile, "package " & Main_Unit_Name & " is ");

        -- Read the second part of the source file up to '##'
        -- or to end of file.
        -- This is inteded to be put into the spec file
	Copy_Chunk;

	Close; --  The spec file

        Open_Body; -- Open the output file.
        
        -- Read the third part of the source file up to '##'
        -- or to end of file.
        -- This is inteded to be put before the body files package
        -- clause
        Copy_Chunk;
	Put_Line (Outfile, "with " & Main_Unit_Name & ".Goto_Table;");
	Put_Line (Outfile, "use  " & Main_Unit_Name & ".Goto_Table;");
	Put_Line (Outfile, "with " & Main_Unit_Name & ".Tokens;");
	Put_Line (Outfile, "use  " & Main_Unit_Name & ".Tokens;");
	Put_Line (Outfile, "with " & Main_Unit_Name & ".Shift_Reduce;");
	Put_Line (Outfile, "use  " & Main_Unit_Name & ".Shift_Reduce;");
	New_Line (Outfile);
        Put_Line (Outfile, "package body " & Main_Unit_Name & " is ");	
	Put_line (Outfile, "   package " & Main_Unit_Name & "_Goto renames " &
	                   Main_Unit_Name & ".Goto_Table;");
	Put_line (Outfile, "   package " & Main_Unit_Name & "_Tokens renames " &
	                   Main_Unit_Name & ".Tokens;");
	Put_line (Outfile, "   package " & Main_Unit_Name & "_Shift_Reduce " &
	                   " renames " & Main_Unit_Name & 
	                   ".Shift_Reduce;");
        -- Read the fourth part of the source file up to '##'
        -- or to end of file.
        Copy_Chunk;

        Parse_Template_File.Open; 

        -- Copy the header from the parse template 
        loop 
            Parse_Template_File.Read(Text,Length); 
            if Length > 1 and then Text(1..2) = "%%" then 
                exit; 
            else 

-- UMASS CODES :
--   In the template, the codes between "-- UMASS CODES : " and
--   "-- END OF UMASS CODES." are specific to be used by Ayacc-extension.
--   Also the codes between "-- UCI CODES DELETED : " and
--   "-- END OF UCI CODES DELETED." should only be generated in
--   Ayacc and should be deleted in Ayacc-extension.
--   Ayacc-extension has more power in error recovery. So we 
--   generate Umass codes only when Error_Recovery_Extension is True.
--   And we delete the necessary UCI codes when Error_Recovery_
--   Extension is True.
                if Length = 16 and then Text(1..16) = "-- UMASS CODES :" then
                  Umass_Codes := True;
                end if;

                if Length = 22 and then Text(1..22) = "-- UCI CODES DELETED :" then
                  UCI_CODES_Deleted := True;
                  Parse_Template_File.Read(Text,Length);
                  -- We read next line because we do not want to generate
                  -- the comment "-- UCI CODES DELETED :" anyway.
                elsif Length = 28 and then Text(1..28) = "-- END OF UCI CODES DELETED." then
                  UCI_CODES_Deleted := False;
                  Parse_Template_File.Read(Text,Length);
                  -- We read next line because we do not want to generate
                  -- the comment "-- END OF UCI CODES DELETED :" anyway.
                end if;

                if Options.Error_Recovery_Extension then
                  -- Do not generate UCI codes which should be deleted.
                  if not UCI_CODES_Deleted then
                    PUT_LINE(Outfile,Text(1..Length)); 
                  end if;
                else
                  -- Do not generate UMASS codes.
                  if not Umass_Codes then
                    PUT_LINE(Outfile,Text(1..Length));
                  end if;
                end if;

                if Length = 22 and then Text(1..22) = "-- END OF UMASS CODES." then
                  Umass_Codes := False;
                end if;

-- END OF UMASS CODES.

-- UCI CODES commented out :
--   The following line is commented out because it is done in Umass codes.
--              Put_Line(Outfile, Text(1..Length)); 

            end if; 
        end loop; 

        Put_Line (Outfile, "    package yy_goto_tables         renames");
        Put_Line (Outfile, "      " & Goto_Tables_Unit_Name & ';');

        Put_Line (Outfile, "    package yy_shift_reduce_tables renames");
        Put_Line (Outfile, "      " & Shift_Reduce_Tables_Unit_Name & ';');

        Put_Line (Outfile, "    package yy_tokens              renames");
        Put_Line (Outfile, "      " & Tokens_Unit_Name & ';');

-- UMASS CODES :
        if Options.Error_Recovery_Extension then
          Put_Line (OutFile, "    -- UMASS CODES :" );
          Put_Line (Outfile, "    package yy_error_report renames");
	  Put_Line (OutFile, "      " & Error_Report_Unit_Name & ";");
	  Put_Line (OutFile, "    -- END OF UMASS CODES." );
        end if;
-- END OF UMASS CODES.

        -- Copy the first half of the parse template 
        loop 
            Parse_Template_File.Read(Text,Length); 
            if Length > 1 and then Text(1..2) = "%%" then 
                exit; 
            else 

-- UMASS CODES :
--   In the template, the codes between "-- UMASS CODES : " and
--   "-- END OF UMASS CODES." are specific to be used by Ayacc-extension.
--   Also the codes between "-- UCI CODES DELETED : " and
--   "-- END OF UCI CODES DELETED." should only be generated in
--   Ayacc and should be deleted in Ayacc-extension.
--   Ayacc-extension has more power in error recovery. So we 
--   generate Umass codes only when Error_Recovery_Extension is True.
--   And we delete the necessary UCI codes when Error_Recovery_
--   Extension is True.
                if Length = 16 and then Text(1..16) = "-- UMASS CODES :" then
                  Umass_Codes := True;
                end if;

                if Length = 22 and then Text(1..22) = "-- UCI CODES DELETED :" then
                  UCI_CODES_Deleted := True;
                  Parse_Template_File.Read(Text,Length);
                  -- We read next line because we do not want to generate
                  -- the comment "-- UCI CODES DELETED :" anyway.
                elsif Length = 28 and then Text(1..28) = "-- END OF UCI CODES DELETED." then
                  UCI_CODES_Deleted := False;
                  Parse_Template_File.Read(Text,Length);
                  -- We read next line because we do not want to generate
                  -- the comment "-- END OF UCI CODES DELETED :" anyway.
                end if;

                if Options.Error_Recovery_Extension then
                  -- Do not generate UCI codes which should be deleted.
                  if not UCI_CODES_Deleted then
                    PUT_LINE(Outfile,Text(1..Length)); 
                  end if;
                else
                  -- Do not generate UMASS codes.
                  if not Umass_Codes then
                    PUT_LINE(Outfile,Text(1..Length));
                  end if;
                end if;

                if Length = 22 and then Text(1..22) = "-- END OF UMASS CODES." then
                  Umass_Codes := False;
                end if;

-- END OF UMASS CODES.

-- UCI CODES commented out :
--   The following line is commented out because it is done in Umass codes.
--              Put_Line(Outfile, Text(1..Length)); 

            end if; 
        end loop; 

        -- Copy declarations and procedures needed in the parse template
        Put_Line (Outfile,"        DEBUG : constant boolean := " &
                          Boolean'Image (Options.Debug) & ';'); 

        -- Consume Template Up To User Action Routines.
        loop 
            Parse_Template_File.Read(Text,Length); 
            if Length > 1 and then Text(1..2) = "%%" then 
                exit; 
            else 

-- UMASS CODES :
--   In the template, the codes between "-- UMASS CODES : " and
--   "-- END OF UMASS CODES." are specific to be used by Ayacc-extension.
--   Also the codes between "-- UCI CODES DELETED : " and
--   "-- END OF UCI CODES DELETED." should only be generated in
--   Ayacc and should be deleted in Ayacc-extension.
--   Ayacc-extension has more power in error recovery. So we 
--   generate Umass codes only when Error_Recovery_Extension is True.
--   And we delete the necessary UCI codes when Error_Recovery_
--   Extension is True.
                if Length = 16 and then Text(1..16) = "-- UMASS CODES :" then
                  Umass_Codes := True;
                end if;

                if Length = 22 and then Text(1..22) = "-- UCI CODES DELETED :" then
                  UCI_CODES_Deleted := True;
                  Parse_Template_File.Read(Text,Length);
                  -- We read next line because we do not want to generate
                  -- the comment "-- UCI CODES DELETED :" anyway.
                elsif Length = 28 and then Text(1..28) = "-- END OF UCI CODES DELETED." then
                  UCI_CODES_Deleted := False;
                  Parse_Template_File.Read(Text,Length);
                  -- We read next line because we do not want to generate
                  -- the comment "-- END OF UCI CODES DELETED :" anyway.
                end if;

                if Options.Error_Recovery_Extension then
                  -- Do not generate UCI codes which should be deleted.
                  if not UCI_CODES_Deleted then
                    PUT_LINE(Outfile,Text(1..Length)); 
                  end if;
                else
                  -- Do not generate UMASS codes.
                  if not Umass_Codes then
                    PUT_LINE(Outfile,Text(1..Length));
                  end if;
                end if;

                if Length = 22 and then Text(1..22) = "-- END OF UMASS CODES." then
                  Umass_Codes := False;
                end if;

-- END OF UMASS CODES.

-- UCI CODES commented out :
--   The following line is commented out because it is done in Umass codes.
--              Put_Line(Outfile, Text(1..Length)); 

            end if; 
        end loop; 

        Actions_File.Open(Actions_File.Read_File); 
        loop 
            exit when Actions_File.Is_End_of_File; 
            Actions_File.Read_Line(Text,Length);            
            Put_Line(Outfile, Text(1..Length)); 
        end loop; 
        Actions_File.Delete; 

        -- Finish writing the template file 
        loop 
            exit when Parse_Template_File.Is_End_of_File; 
            Parse_Template_File.Read(Text,Length);            

-- UMASS CODES :
--   In the template, the codes between "-- UMASS CODES : " and
--   "-- END OF UMASS CODES." are specific to be used by Ayacc-extension.
--   Also the codes between "-- UCI CODES DELETED : " and
--   "-- END OF UCI CODES DELETED." should only be generated in
--   Ayacc and should be deleted in Ayacc-extension.
--   Ayacc-extension has more power in error recovery. So we 
--   generate Umass codes only when Error_Recovery_Extension is True.
--   And we delete the necessary UCI codes when Error_Recovery_
--   Extension is True.
            if Length = 16 and then Text(1..16) = "-- UMASS CODES :" then
              Umass_Codes := True;
            end if;

            if Length = 22 and then Text(1..22) = "-- UCI CODES DELETED :" then
              UCI_CODES_Deleted := True;
              Parse_Template_File.Read(Text,Length);
              -- We read next line because we do not want to generate
              -- the comment "-- UCI CODES DELETED :" anyway.
            elsif Length = 28 and then Text(1..28) = "-- END OF UCI CODES DELETED." then
              UCI_CODES_Deleted := False;
              Parse_Template_File.Read(Text,Length);
              -- We read next line because we do not want to generate
              -- the comment "-- END OF UCI CODES DELETED :" anyway.
            end if;

            if Options.Error_Recovery_Extension then
              -- Do not generate UCI codes which should be deleted.
              if not UCI_CODES_Deleted then
                PUT_LINE(Outfile,Text(1..Length)); 
              end if;
            else
              -- Do not generate UMASS codes.
              if not Umass_Codes then
                PUT_LINE(Outfile,Text(1..Length));
              end if;
            end if;

            if Length = 22 and then Text(1..22) = "-- END OF UMASS CODES." then
              Umass_Codes := False;
            end if;

-- END OF UMASS CODES.

-- UCI CODES commented out :
--   The following line is commented out because it is done in Umass codes.
--          Put_Line(Outfile, Text(1..Length)); 

        end loop; 
        Parse_Template_File.Close; 
        
        -- Copy rest of input file after ## 
        while not Source_File.Is_End_of_File loop  
	    Source_File.Read_Line(Text, Length);
-- UMASS CODES :
--    If the generated codes has the extension of
--    error recovery, there may be another section
--    for error reporting. So we return if we find "%%".
            if Options.Error_Recovery_Extension then
              if Length > 1 and then Text(1..2) = "%%" then
                exit;
              end if;
            end if;
-- END OF UMASS CODES.
	    Put_Line(Outfile, Text(1..Length));
        end loop;
 
        Close;
    end Make_Output_File; 
end Output_File; 
