

with Ayacc_File_Names, Text_IO, Source_File, Str_pack;
use Ayacc_File_Names, Text_IO;


package body Error_Report_File is
--
-- TITLE:       package body Error_Report_File
--    Output the code which allows users to see what the error token was.
--    This is for non-correctable errors.
--    Also in this package: The declaration of user actions for correctable
--    (continuable) errors.
--
-- LANGUAGE:
--    Ada
--
-- PERSONNEL:
--    AUTHOR: Benjamin Hurwitz
--    DATE: Jul 27 1990
--
-- OVERVIEW:
--    Parse the last section of the .y file, looking for
--    %report_continuable_error and the related procedures.  From these,
--    generate procedure bodies which will be called from yyparse when
--    there is an error which has been corrected.  Since the errors get
--    corrected, yyerror does not get called.
--    
  
  max_line_length : constant integer := 370;

  The_File : File_Type;                   -- Where the error report goes

  Text   : String(1..max_line_length);    -- Current line from source file
  Length : Natural := 1;                  -- and its length
            

  -- types of lines found in the continuable error report section
  type user_defined_thing is (with_thing,
			      use_thing, 
			      init_thing, 
			      report_thing,
			      finish_thing,
			      line_thing,
			      eof_thing);

--
-- TITLE:
--    Get Next Thing : Classify a line of text from the user defined error
--    report section of the .y file
--
-- OVERVIEW:
--    Read one line of the .y file, classifying it.
--    In the case of a %use or %with line, set the global variables Text and
--    Length to the tail of the line after the %use or %with.
-- ...................................................
  procedure get_next_thing(thing : in out user_defined_thing) is
    use str_pack;
    with_string : constant string := "%WITH";
    use_string  : constant string := "%USE";
    init_string : constant string := "%INITIALIZE_ERROR_REPORT";
    finish_string: constant string:= "%TERMINATE_ERROR_REPORT";
    report_string: constant string:= "%REPORT_ERROR";
    temp : STR(max_line_length);
  begin
  	if thing = eof_thing or else Source_File.is_end_of_file then
	  thing := eof_thing;
	  return;
	end if;
	
	Source_File.Read_Line(Text, Length);
	if length >= use_string'length then
	   assign(text(1..use_string'length), temp);
	   if value_of(upper_case(temp)) = use_string then
	        thing := use_thing;
	        length := length - use_string'length;
	        text(1..length) := text((use_string'length + 1)..
		                        length + use_string'length);
		return;
	   end if;
	end if;
	if length >= with_string'length then
	   assign(text(1..with_string'length), temp);	   
	   if Value_of(upper_case(temp)) = with_string then
	        thing := with_thing;
	        length := length - with_string'length;
	        text(1..length) := text((with_string'length + 1)..
		                        length + with_string'length);
		return;
	   end if;
	 end if;
	if length >= init_string'length then
	   assign(text(1..init_string'length), temp);	   	  
	    if Value_of(str_pack.upper_case(temp)) = init_string then
	      thing := init_thing;
	      return;
	    end if;
        end if;
	if length >= finish_string'length then
	   assign(text(1..finish_string'length), temp);	   	  	  
	   if value_of(str_pack.upper_case(temp)) = finish_string then
	      thing := finish_thing;
	      return;
	   end if;
	end if;
	if length >= report_string'length then
	   assign(text(1..report_string'length), temp);
	   if value_of(str_pack.upper_case(temp)) = report_string then
	     thing := report_thing;
	     return;
	   end if;
	end if;
	thing := line_thing;
  end get_next_thing;
			   


--
-- TITLE:       procedure Write_Line
--    Write out a line to the Error Report generated ada file.
--
-- OVERVIEW:
--    
-- ...................................................
    procedure Write_Line(S: in String) is
    begin
        Put_Line(The_File, S);
    end Write_Line;

--
-- TITLE:
--    Write the body of one of the user-defined procedures
--
-- OVERVIEW:
--    If User is True it means the user is defining the procedure body.  So 
--    copy it from the source file.  Otherwise provide a null body.
-- ...................................................
    procedure write_thing(user : in boolean; 
      	      	      	  thing : in out user_defined_thing) is
    begin
      if user then
	loop
	  get_next_thing(thing);
	  exit when thing /= line_thing;
	  Write_Line(Text(1..length));
        end loop;
      else
        Write_Line("begin");
	Write_Line("  null;");
	Write_Line("end;");
      end if;
      Write_Line("");
    end write_thing;

--
-- TITLE:
--    Write the error report initialization function
--
-- OVERVIEW:
--    Write the header & then then body
-- ...................................................
    procedure write_init(user : in boolean;
			 thing : in out user_defined_thing) is
    begin
      Write_Line("procedure Initialize_User_Error_Report is");
      write_thing(user, thing);
    end write_init;

--
-- TITLE:
--    Write the error report completion function
--
-- OVERVIEW:
--    Write the header & then then body
-- ...................................................

    procedure write_finish(user : in boolean; 
			   thing : in out user_defined_thing) is
    begin
      Write_Line("procedure Terminate_User_Error_Report is");
      write_thing(user, thing);
    end write_finish;

--
-- TITLE:
--    Write the error report function
--
-- OVERVIEW:
--    Write out the header with signature and then the body.
-- ...................................................
    procedure write_report(user : in boolean;
      	      	      	   thing : in out user_defined_thing) is
    begin
      Write_Line("procedure Report_Continuable_Error ");
      Write_Line("    (Line_Number : in Natural;");
      Write_Line("    Offset      : in Natural;");
      Write_Line("    Finish      : in Natural;");
      Write_Line("    Message     : in String;");
      Write_Line("    Error       : in Boolean)  is");
      write_thing(user, thing);
    end write_report;

--
-- TITLE:       procedure Write_File
--    Create & open the Error_Report file, dump its contents.
--
-- PERSONNEL:
--    AUTHOR: Benjamin Hurwitz
--    DATE: Mar 11 1990
--
-- OVERVIEW:
--    The file being created will be used to report errors which yyparse
--    encounters.  Some of them it can correct, and some it cannot.
--    There are different mechanisms for reporting each of these.  There
--    is default reporting of corrected errors; messages are written
--    into the .lis file (Put, Put_Line).  Also,
--    the user can define his/her own error reporting of correctable errors
--    in the last section of the .y file.  If so, we here construct the
--    error report file so as to use these procedures.
--    Also in this package are variables and routines to
--    manipulate error information which the user can call from yyerror,
--    the procedure called when a non-correctable error is encountered.

--    The things generated which vary with runs of Ayacc is the names
--    of the Ada units, the packages With'ed and Used by the generated
--    error report package body and the bodies of the user-defined error report
--    routines for continuable errors.
--
-- NOTES:
--    This procedure is exported from the package.
--
-- SUBPROGRAM BODY:
--    
  procedure Write_File is
    current_thing : user_defined_thing := line_thing;
    wrote_init   : boolean := false;
    wrote_finish : boolean := false;
    wrote_report : boolean := false;
  begin
    Create(The_File, Out_File, Get_Error_Report_File_Name & "ds");
    Write_Line("package " & Error_Report_Unit_Name & " is"); 
    Write_Line("");
    Write_Line("    Syntax_Error : Exception;");
    Write_Line("    Syntax_Warning : Exception;");
    Write_Line("    Total_Errors : Natural := 0;   -- number of syntax errors found." );
    Write_Line("    Total_Warnings : Natural := 0; -- number of syntax warnings found." );						 
    Write_Line("        ");
    Write_Line("    procedure Report_Continuable_Error(Line_Number : in Natural;");
    Write_Line("                                       Offset      : in Natural;");
    Write_Line("                                       Finish      : in Natural;");
    Write_Line("                                       Message     : in String;");
    Write_Line("                                       Error       : in Boolean);");
    Write_Line("");
    Write_Line("    procedure Initialize_Output;");
    Write_Line("");
    Write_Line("    procedure Finish_Output;");
    Write_Line("");
    Write_Line("    procedure Put(S: in String);");
    Write_Line("");
    Write_Line("    procedure Put(C: in Character);");
    Write_Line("");
    Write_Line("    procedure Put_Line(S: in String);");
    Write_Line("");
    Write_Line("end " & Error_Report_Unit_Name & ";");
    Close(The_File);
	
    Create(The_File, Out_File, Get_Error_Report_File_Name & "db");
    Write_Line("with Text_IO;");
    -- Get %with's & %use's from source file
    loop
      get_next_thing(current_thing);
      if current_thing = with_thing then
        Write_Line("With " & text(1..length));
      elsif current_thing = use_thing then
        Write_Line("Use " & text(1..length));
      elsif current_thing = line_thing then
	null;
      else
	exit;
      end if;
    end loop;
    Write_Line("");
    Write_Line("package body " & Error_Report_Unit_Name & " is");
    Write_Line("");
    Write_Line("    The_File : Text_io.File_Type;");
    Write_Line("");
    -- Get user declarations of error reporting procedures from source file
    while(current_thing /= eof_thing) loop
      if current_thing = init_thing then
	Write_init(true, current_thing);
	wrote_init := true;
      elsif current_thing = finish_thing then
	Write_finish(true, current_thing);
	wrote_finish := true;
      elsif current_thing = report_thing then
        Write_report(true, current_thing);
	wrote_report := true;
      else
	get_next_thing(current_thing);
      end if;
    end loop;
    if not wrote_init then
      Write_init(false, current_thing);
    end if;
    if not wrote_finish then
      Write_finish(false, current_thing);
    end if;
    if not wrote_report then
      Write_report(false, current_thing);
    end if;
    Write_Line("");
    Write_Line("    procedure Initialize_Output is");
    Write_Line("      begin");
    Write_Line("        Text_io.Create(The_File, Text_io.Out_File, " & 
      '"' & Get_Listing_File_Name & '"' & ");");
    Write_Line("        initialize_user_error_report;");
    Write_Line("      end Initialize_Output;");
    Write_Line("");
    Write_Line("    procedure Finish_Output is");
    Write_Line("      begin");
    Write_Line("        Text_io.Close(The_File);");
    Write_Line("        terminate_user_error_report;");
    Write_Line("      end Finish_Output;");
    Write_Line("");
    Write_Line("    procedure Put(S: in String) is");
    Write_Line("    begin");
    Write_Line("      Text_io.put(The_File, S);");
    Write_Line("    end Put;");
    Write_Line("");
    Write_Line("    procedure Put(C: in Character) is");
    Write_Line("    begin");
    Write_Line("      Text_io.put(The_File, C);");
    Write_Line("    end Put;");
    Write_Line("");
    Write_Line("    procedure Put_Line(S: in String) is");
    Write_Line("    begin");
    Write_Line("      Text_io.put_Line(The_File, S);");
    Write_Line("    end Put_Line;");
    Write_Line("");
    Write_Line("");
    Write_Line("end " & Error_Report_Unit_Name & ";");
    Close(The_File);
  end Write_File;
-- ...................................................


begin
  null;
end Error_Report_File;
