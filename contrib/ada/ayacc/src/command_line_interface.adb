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

-- Module       : command_line_interface.ada
-- Component of : common_library
-- Version      : 1.2
-- Date         : 11/21/86  16:02:24
-- SCCS File    : disk21~/rschm/hasee/sccs/common_library/sccs/sxcommand_line_interface.ada

with Text_IO; use Text_IO;
with String_scanner;
----------------------------------------------------------------

Package body command_line_interface is

  SCCS_ID : constant String := "@(#) command_line_interface.addisk21~/rschm/hasee/sccs/common_library, Version 1.2";


--| Provides primitives for getting at the command line arguments.

--| Overview

Package sp renames String_pkg;
Package ss renames String_scanner;

type Name_value is                  --| Name/Value pair
  record
    Name:  sp.String_type;          --| Name of value
    Value: sp.String_type;          --| Value associated with name
    Was_retrieved: boolean:=FALSE;  --| Flag indicating whether name-value
  end record;                       --  association has been retrieved by tool

type Token_type is (Ada_ID,Word,Bound_to,None);

Package Token_type_IO is new Enumeration_IO(Token_type);
use Token_type_IO;


  Maximum_Command_Length : constant := 1024;

  subtype Command_Line_Type is String (1 .. Maximum_Command_Length);

  Arg_string : Command_Line_Type;   --| String obtained from operating system
                                  
  N_arg_count: Argument_count;      --| Count of named args 
  P_arg_count: Argument_count;      --| Count of positional args 

  Rejected: boolean := FALSE;

  Tool_Name : String_Type;

Named_args: array(argument_index)
   of Name_value;
    
Positional_args: array(argument_index)
   of sp.String_type;


  procedure Read_Command_Line
    (Command_Args : out Command_Line_Type) is separate;
  --**
  --| Description: Read_Command_Line is the machine dependent interface to
  --|   the Operating System Command Line.
  --**

----------------------------------------------------------------

-- Local functions:

  procedure Set_Tool_Name (To : in String) is
  begin
    Tool_Name := Create (To & ": ");
  end Set_Tool_Name;


  procedure CLI_Error (Error_Message : in String) is
  begin
    New_Line;
    Put_Line (Value (Tool_Name) & Error_Message);
  end CLI_Error;


procedure Get_token(
  Scan_string : in out ss.Scanner;
  Argument : in out sp.String_type;
  Kind: in out Token_type
  ) is

  Last_arg: sp.String_type;
  Last_kind: Token_type;
  Found: boolean;
  Delimeter: sp.String_type;
  Delim_string: ss.Scanner;
  More_commas: boolean := FALSE;
  Tail: sp.String_type;
  
begin

  if Rejected then
	Argument := Last_arg;
	Kind := Last_kind;
	Rejected := FALSE;
  else	
	if ss.Is_sequence(" ,",Scan_string) then
		ss.Scan_sequence(" ,",Scan_string,Found,Delimeter);
		Delim_string := ss.Make_scanner(Delimeter);
		loop
			ss.Skip_space(Delim_string);
			exit when not ss.More(Delim_string);
			ss.Forward(Delim_string);
			if More_commas then
                           CLI_Error ("Missing Positional Argument.");
			   raise missing_positional_arg;
			end if;
			More_commas := TRUE;
		end loop;
	end if;
   	if ss.Is_Ada_Id(Scan_string) then
		ss.Scan_Ada_Id(Scan_string,Found,Argument);
		if ss.Is_Literal("=>",Scan_string) or 
		   ss.Is_Literal("""",Scan_string) or 
		   ss.Is_sequence(" ,",Scan_string) or
		   not ss.More(Scan_string) then 
			Kind := Ada_ID;
		else
			if ss.Is_not_sequence(" ,",Scan_string) then
				ss.Scan_not_sequence(" ,",Scan_string,Found,Tail);
				Argument := sp."&"(Argument,Tail);
				Kind := Word;
			else
				ss.Scan_word(Scan_string,Found,Tail);
				Argument := sp."&"(Argument,Tail);
				Kind := Word;
			end if;
		end if;
	elsif ss.Is_Literal("=>",Scan_string) then
		ss.Scan_Literal("=>",Scan_string,Found);
		Argument := sp.Create("=>");
		Kind := Bound_to;
	elsif ss.Is_quoted(Scan_string) then
		ss.Scan_quoted(Scan_string,Found,Argument);
		Kind := Word;
	elsif ss.Is_enclosed('(',')',Scan_string) then
		ss.Scan_enclosed('(',')',Scan_string,Found,Argument);
		Kind := Word;
	elsif ss.Is_not_sequence(" ,",Scan_string) then
		ss.Scan_not_sequence(" ,",Scan_string,Found,Argument);
		Kind := Word;
   	elsif ss.Is_word(Scan_string) then
		ss.Scan_word(Scan_string,Found,Argument);
		Kind := Word;
	else
	  	Argument := sp.Create("");
		Kind := None;
	end if;
	Last_kind := Kind;
	Last_arg := Argument;
  end if;
end Get_token;

-----------------------------------------------------------------------

procedure Save_named(
  Name : in sp.String_type;
  Value : in sp.String_type
  ) is

begin
  N_arg_count := N_arg_count + 1;
  Named_args(N_arg_count).Name := Name;
  Named_args(N_arg_count).Value := Value;
end Save_named;

procedure Save_positional(
  Value : in sp.String_type
  ) is

begin
  if N_arg_count > 0 then
    CLI_Error ("Invalid Parameter Order, " &
               "Positional arguments must precede Named.");
    raise invalid_parameter_order;
  end if;
  P_arg_count := P_arg_count + 1;
  Positional_args(P_arg_count) := Value;
end Save_positional;

procedure Reject_token is

begin
  Rejected := TRUE;
end Reject_token;

----------------------------------------------------------------

procedure Initialize (Tool_Name : in String) is

begin

  Set_Tool_Name (To => Tool_Name);

  declare

     type State_type is (Have_nothing,Have_Ada_ID,Have_bound_to);

     Start_Index : integer;    --| 
     End_Index: integer;       --| Indices of characters in argument string

     Scan_string: ss.Scanner;  --| Scanned argument string
     Argument: sp.String_Type; --| Argument scanned from argument string
     Kind: Token_type;         --| Kind of argument- WORD, =>, Ada_ID
     Old_arg: sp.String_Type;  --| Previously scanned argument 
     Found: boolean;

     State: State_type := Have_nothing;
     --| State of argument in decision tree 
   
  begin

     Start_Index := Arg_string'first;
     End_Index   := Arg_string'first;

     N_arg_count := 0;
     P_arg_count := 0;

     -- Get the command line from the operating system
     Read_Command_Line (Arg_String);

     -- Remove trailing blanks and final semicolon  
     for i in reverse Arg_string'range loop
	if Arg_string(i) /= ' ' then
	    if Arg_string(i) = ';' then
		End_Index := i - 1;
	    else
		End_Index := i;
	    end if;
	    exit;
	end if;
     end loop;

     Skip_Leading_White_Space :
     for i in Arg_String'First .. End_Index
     loop
       if Arg_String (i) /= ' '      and then
          Arg_String (i) /= Ascii.HT then

          Start_Index := i;
          exit Skip_Leading_White_Space;

       end if;
     end loop Skip_Leading_White_Space;


     Verify_Balanced_Parentheses :
     declare
       Left_Parens  : Natural := 0;
       Right_Parens : Natural := 0;
     begin

       for i in Start_Index .. End_Index
       loop

         if Arg_String (i) = '(' then
           Left_Parens := Left_Parens + 1;
         elsif Arg_String (i) = ')' then
           Right_Parens := Right_Parens + 1;
         end if;

       end loop;

       if Left_Parens /= Right_Parens then
         CLI_Error ("Unbalanced Parentheses.");
         raise Unbalanced_Parentheses;
       end if;

     end Verify_Balanced_Parentheses;

     -- Convert argument string to scanner and remove enclosing parantheses

     Scan_string :=  ss.Make_scanner(sp.Create(
                       Arg_string(Start_Index .. End_Index)));

     if ss.Is_enclosed('(',')',Scan_string) then
	ss.Mark(Scan_string);
	ss.Scan_enclosed('(',')',Scan_string,Found,Argument); 
	ss.Skip_Space(Scan_string);
	if not ss.More(Scan_string) then
		ss.Destroy_Scanner(Scan_string);
		Scan_string :=  ss.Make_scanner(Argument);
	else
		ss.Restore(Scan_string);
	end if;
     end if;

     -- Parse argument string and save arguments 
     loop 
	Get_token(Scan_string,Argument,Kind);
	case State is
		when Have_nothing =>
			case Kind is
				when Ada_ID => 
					Old_arg := Argument;
					State := Have_Ada_ID;
				when Word => 
					Save_positional(Argument);
					State := Have_nothing;
				when Bound_to => 
					State := Have_nothing;
                                        CLI_Error ("Invalid Named Association.");
					raise invalid_named_association;
				when None => 
					null;
			end case;
		when Have_Ada_ID =>
			case Kind is
				when Ada_ID => 
					Save_positional(Old_arg);
					Old_arg := Argument;
					State := Have_Ada_ID;
				when Word => 
					Save_positional(Old_arg);
					Save_positional(Argument);
					State := Have_nothing;
				when Bound_to => 
					State := Have_bound_to;
				when None =>
					Save_positional(Old_arg);
			end case;
		when Have_bound_to => 
			case Kind is
				when Ada_ID | Word => 
					Save_named(Old_arg,Argument);
					State := Have_nothing;
				when Bound_to => 
					State := Have_bound_to;
                                        CLI_Error ("Invalid Named Association.");
					raise invalid_named_association;
				when None => 
                                        CLI_Error ("Invalid Named Association.");
					raise invalid_named_association;

			end case;
	end case;
	exit when Kind = None;
     end loop;
  end;
end Initialize;

--------------------------------------------------------------------------

function Named_arg_count	--| Return number of named arguments
  return Argument_count is

begin
  return N_arg_count;
end;

----------------------------------------------------------------

function Positional_arg_count	--| Return number of positional arguments
  return Argument_count is

begin
  return P_arg_count;
end;

----------------------------------------------------------------

function Positional_arg_value(	--| Return an argument value
  N: Argument_index     	--| Position of desired argument
  ) return string is	        --| Raises: no_arg

--| Effects: Return the Nth argument.  If there is no argument at
--| position N, no_arg is raised.

--| N/A: modifies, errors

begin
  if N > P_arg_count then
     CLI_Error ("Internal Error, Argument" & Argument_Index'Image (N) &
                " does not exist.  Please submit an LCR.");
     raise no_arg;   
  else
     return sp.Value(Positional_args(N));
  end if;
end;

----------------------------------------------------------------

function Positional_arg_value(	--| Return an argument value
  N: Argument_index     	--| Position of desired argument
  ) return sp.String_type is	--| Raises: no_arg

--| Effects: Return the Nth argument.  If there is no argument at
--| position N, no_arg is raised.

--| N/A: modifies, errors

begin
  if N > P_arg_count then
     CLI_Error ("Internal Error, Argument" & Argument_Index'Image (N) &
                " does not exist.  Please submit an LCR.");
     raise no_arg;   
  else
     return Positional_args(N);
  end if;
end;

----------------------------------------------------------------

function Named_arg_value(--| Return a named argument value
  Name: string;
  Default: string
  ) return string is

--| Effects: Return the value associated with Name on the command
--| line.  If there was none, return Default.

begin
  for i in 1..N_arg_count
  loop
     if sp.Equal(sp.Upper(Named_args(i).Name),sp.Upper(sp.Create(Name))) then
        Named_args(i).Was_retrieved := TRUE;
	return sp.Value(Named_args(i).Value);
     end if;
  end loop;
  return Default;
end;

function Named_arg_value(--| Return a named argument value
  Name: string;
  Default: string
  ) return String_Type is

--| Effects: Return the value associated with Name on the command
--| line.  If there was none, return Default.

begin
  return Create (Named_Arg_Value (Name, Default));
end Named_Arg_Value;

----------------------------------------------------------------

function Named_arg_value(--| Return a named argument value
  Name: string;
  Default: sp.String_type
  ) return sp.String_type is

--| Effects: Return the value associated with Name on the command
--| line.  If there was none, return Default.

begin
  for i in 1..N_arg_count
  loop
     if sp.Equal(sp.Upper(Named_args(i).Name),sp.Upper(sp.Create(Name))) then
        Named_args(i).Was_retrieved := TRUE;
	return Named_args(i).Value;
     end if;
  end loop;
  return Default;
end;

----------------------------------------------------------------

function Arguments	--| Return the entire argument string
  return string is

--| Effects: Return the entire command line, except for the name
--| of the command itself.

begin
  return Arg_string;
end;

----------------------------------------------------------------

  function Parse_Aggregate (Aggregate_Text : in String)
                                                    return String_Lists.List is
    type State_type is (Have_Nothing,
                        Have_Ada_ID,
                        Have_Bound_To);

    First : Natural := Aggregate_Text'First;
    Last  : Natural := Aggregate_Text'Last;

    Component_List : String_Lists.List := String_Lists.Create;

    Argument    : sp.String_Type; --| Argument scanned from argument string
    Kind        : Token_type;     --| Kind of argument- WORD, =>, Ada_ID
    Scan_string : ss.Scanner;     --| Scanned argument string

    Aggregate_Contents       : String_Type;
    Enclosed_Aggregate_Found : Boolean := False;

  begin

    if Aggregate_Text'Length > 0 then

      Scan_String := SS.Make_Scanner (Create (Aggregate_Text (First .. Last)));

      SS.Scan_Enclosed ( '(', ')',
                        Scan_String,
                        Found  => Enclosed_Aggregate_Found,
                        Result => Aggregate_Contents,
                        Skip   => True);
 
      if Enclosed_Aggregate_Found then
        SS.Destroy_Scanner (Scan_String);
        Scan_String := SS.Make_Scanner (Aggregate_Contents);
      end if;

      Parse_Aggregate_String :
      loop 

         Get_token(Scan_string, Argument, Kind);

         exit Parse_Aggregate_String when Kind = None;

         String_Lists.Attach (Component_List, Argument);

      end loop Parse_Aggregate_String;

    end if;

    return Component_List;

  end Parse_Aggregate;

  function Parse_Aggregate 
    (Aggregate_Text : in String_Type)
    return String_Lists.List is 
  begin
    return Parse_Aggregate (Value (Aggregate_Text));
  end Parse_Aggregate;

----------------------------------------------------------------

  function Convert (Parameter_Text : in String) return Parameter_Type is
  begin
    return Parameter_Type'Value (Parameter_Text);
  exception
    when Constraint_Error =>
      CLI_Error ("Invalid Parameter, """ &
                 Value (Mixed (Parameter_Text)) &
                 """ is not a legal value for type " &
                 Value (Mixed (Type_Name)) & '.');
      raise Invalid_Parameter;
  end Convert;

----------------------------------------------------------------

procedure Finalize is   --| Raises: unreferenced_named_arg

begin
  for i in 1..Named_arg_count loop
    if Named_args(i).Was_retrieved = FALSE then
      CLI_Error ("Invalid Parameter Association, " &
                 Value (Mixed (Named_Args (i).Name)) &
                 " is not a valid Formal Parameter.");
      raise unreferenced_named_arg;
    end if;
  end loop;
end Finalize;

-------------------------------------------------------------------

end command_line_interface;
