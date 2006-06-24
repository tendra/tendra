

with STR_Pack;
use  STR_Pack;

with String_Pkg;
package body Ayacc_File_Names is

  SCCS_ID : constant String := "@(#) file_names.ada, Version 1.2";



  Rcs_ID : constant String := "$Header: /cf/ua/arcadia/alex-ayacc/ayacc/src/RCS/file_names.a,v 1.2 88/11/28 13:38:59 arcadia Exp $";

    Max_Name_Length : constant := 50;

    Source_File_Name       : STR(Max_Name_Length);
    Out_File_Name          : STR(Max_Name_Length);
    Verbose_File_Name      : STR(Max_Name_Length);
    Template_File_Name     : STR(Max_Name_Length);
    Actions_File_Name      : STR(Max_Name_Length);
    Shift_Reduce_File_Name : STR(Max_Name_Length);
    Goto_File_Name         : STR(Max_Name_Length);
    Tokens_File_Name       : STR(Max_Name_Length);
-- UMASS CODES :
    Error_Report_File_Name : STR(Max_Name_Length);
    Listing_File_Name      : STR(Max_Name_Length);
-- END OF UMASS CODES.
    C_Lex_File_Name        : STR(Max_Name_Length);
    Include_File_Name      : STR(Max_Name_Length);
 

--RJS ==========================================

  function End_of_Unit_Name (Name : in String) return Natural is
    Dot_Position : Natural := Name'Last;
  begin
    while Dot_Position >= Name'First and then
          Name (Dot_Position) /= '.'
    loop
      Dot_Position := Dot_Position - 1;
    end loop;
    return Dot_Position - 1;
  end End_of_Unit_Name;


  function Get_Unit_Name (Filename : in String) return String is

  -- modified to check for valid Ada identifiers. 11/28/88 kn

    Filename_Without_Extension : String :=
      Filename (Filename'First .. End_of_Unit_Name (Filename));

    End_of_Directory : Natural := Filename_Without_Extension'Last + 1;


    function Is_Alphabetic (Ch : in Character) return Boolean is
    begin
      return Ch in 'A' .. 'Z' or else
             Ch in 'a' .. 'z';
    end Is_Alphabetic;

    function Is_AlphaNum_or_Underscore (Ch : in Character) return Boolean is
    begin
      return Is_Alphabetic(Ch) or else
             Ch in '0' .. '9'  or else
             Ch = '_' or else Ch = '-';
    end Is_AlphaNum_or_Underscore;

  use String_Pkg;

  begin
    -- find end of directory
    for Pos in reverse Filename_Without_Extension'FIRST..
		       Filename_Without_Extension'LAST loop
      exit when Filename_Without_Extension(Pos) = '/';
      End_Of_Directory := Pos;
    end loop;

    if End_Of_Directory <= Filename_Without_Extension'LAST and then
       Is_Alphabetic (Filename_Without_Extension (End_of_Directory)) then

       Check_Remaining_Characters :
       for i in End_Of_Directory + 1 .. Filename_Without_Extension'LAST 
       loop
	 if not Is_AlphaNum_or_Underscore (Filename_Without_Extension(i)) then
	   return "";
         elsif Filename_Without_Extension(i) = '-' then
           Filename_Without_Extension(i) := '.';
	 end if;
       end loop Check_Remaining_Characters;

       return Value (Mixed (Filename_Without_Extension (End_of_Directory ..
                            Filename_Without_Extension'Last)));
    else
      return "";
    end if;

  end Get_Unit_Name;


  function C_Lex_Unit_Name return String is
    Filename : constant String := Value_of (Upper_Case (C_Lex_File_Name));
  begin
    return Get_Unit_Name (Filename);
  end C_Lex_Unit_Name;


  function Goto_Tables_Unit_Name return String is
    Filename : constant String := Value_of (Upper_Case (Goto_File_Name));
  begin
    return Get_Unit_Name (Filename);
  end Goto_Tables_Unit_Name;


  function Shift_Reduce_Tables_Unit_Name return String is
    Filename : constant String := Value_of (Upper_Case (Shift_Reduce_File_Name));
  begin
    return Get_Unit_Name (Filename);
  end Shift_Reduce_Tables_Unit_Name;


  function Tokens_Unit_Name return String is
    Filename : constant String := Value_of (Upper_Case (Tokens_File_Name));
  begin
    return Get_Unit_Name (Filename);
  end Tokens_Unit_Name;

  function Main_Unit_Name return String is
    Filename : constant String := Value_of (Upper_Case (Out_File_Name));
  begin
    return Get_Unit_Name (Filename);
  end Main_Unit_Name;

-- UMASS CODES :
  function Error_Report_Unit_Name return String is
    Filename : constant String := Value_of (Upper_Case (Error_Report_File_Name));
  begin
    return Get_Unit_Name (Filename);
  end Error_Report_Unit_Name;
-- END OF UMASS CODES.

--RJS ==========================================


    function  Get_Source_File_Name return String is
    begin
	return Value_of(Source_File_Name);
    end;

    function  Get_Out_File_Name return String is
    begin
	return Value_of(Out_File_Name);
    end;

    function  Get_Verbose_File_Name return String is
    begin
	return Value_of(Verbose_File_Name);
    end;

    function  Get_Template_File_Name return String is
    begin
	return Value_of(Template_File_Name);
    end;

    function  Get_Actions_File_Name return String is
    begin
	return Value_of(Actions_File_Name);
    end;

    function  Get_Shift_Reduce_File_Name return String is
    begin
	return Value_of(Shift_Reduce_File_Name);
    end;

    function  Get_Goto_File_Name return String is
    begin
	return Value_of(Goto_File_Name);
    end;

    function  Get_Tokens_File_Name return String is
    begin
	return Value_of(Tokens_File_Name);
    end;

-- UMASS CODES :
    function  Get_Error_Report_File_Name return String is
    begin
	return Value_of(Error_Report_File_Name);
    end;

    function  Get_Listing_File_Name return String is
    begin
	return Value_of(Listing_File_Name);
    end;
-- END OF UMASS CODES.

    function Get_C_Lex_File_Name return String is
    begin
	return Value_of(C_Lex_File_Name);
    end;

    function Get_Include_File_Name return String is
    begin
	return Value_of(Include_File_Name);
    end;



    procedure Set_File_Names(Input_File, Extension: in String) is
	Base: STR(Max_Name_Length);
    begin

	if Input_File'Length < 3 or else
	   (Input_File(Input_File'Last) /= 'y' and then
	    Input_File(Input_File'Last) /= 'Y') or else
	   Input_File(Input_File'Last - 1) /= '.'
	then
	    raise Illegal_File_Name;
	end if;

	Assign(Input_File(Input_File'First..Input_File'Last-2), To => Base);

	Assign(Input_File, To => Source_File_Name);

	Assign(Base, To => Out_File_Name);
	Append(Extension, To => Out_File_Name);

	Assign(Base,       To => Verbose_File_Name);
        Append(".verbose", To => Verbose_File_Name); 

	Assign(Base,        To => Tokens_File_Name);
        Append("-tokens" & Extension & "ds", To => Tokens_File_Name); 

-- UMASS CODES :
	Assign(Base,        To => Error_Report_File_Name);
        Append("-error_report" & Extension, To => Error_Report_File_Name); 

	Assign(Base,        To => Listing_File_Name);
        Append(".lis", To => Listing_File_Name); 
-- END OF UMASS CODES.

	Assign("yyparse.template", To => Template_File_Name);

	Assign(Base,    To => Actions_File_Name);
	Append(".accs", To => Actions_File_Name);

	Assign(Base,              To => Shift_Reduce_File_Name);
	Append("-shift_reduce" & Extension & "ds", To => Shift_Reduce_File_Name);

	Assign(Base,      To => Goto_File_Name);
	Append("-goto_table" & Extension & "ds", To => Goto_File_Name);

	Assign(Base,       To => C_Lex_File_Name);
	Append("-c_lex" & Extension, To => C_Lex_File_Name);

	Assign(Base, To => Include_File_Name);
	Append(".h", To => Include_File_Name);

    end Set_File_Names;

end Ayacc_File_Names;
