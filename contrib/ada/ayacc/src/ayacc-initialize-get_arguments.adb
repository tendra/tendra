
with Command_Line_Interface; use Command_Line_Interface; 
with String_Pkg;             use String_Pkg;
--VAX with Vms_Lib; 

separate (Ayacc.Initialize)
procedure Get_Arguments (File           : out String_Type;
                         C_Lex          : out Switch; 
                         Debug          : out Switch;
                         Summary        : out Switch;
                         Verbose        : out Switch;
-- UMASS CODES :
                         Error_Recovery : out Switch;
-- END OF UMASS CODES.
			 Extension      : out String_Type) is 

  C_Lex_Argument   : String_Type;
  Debug_Argument   : String_Type;
  Summary_Argument : String_Type;
  Verbose_Argument : String_Type;
-- UMASS CODES :
  Error_Recovery_Argument : String_Type;
-- END OF UMASS CODES.

  Positional     : Natural := 0; 

  -- Number of positional parameters
  Total          : Natural := 0; 

  -- Total number of parameters
  Max_Parameters : constant := 6;

  Incorrect_Call : exception; 

  function Convert_Switch is new
    Convert (Parameter_Type => Switch,
             Type_Name      => "Switch");

  procedure Put_Help_Message is
  begin
    New_Line;
    Put_Line ("  -- Ayacc: An Ada Parser Generator.");
    New_Line; 
    Put_Line ("  type Switch is (On, Off);");
    New_Line;
    Put_Line ("  procedure Ayacc (File           : in String;"); 
    Put_Line ("                   C_Lex          : in Switch := Off;");
    Put_Line ("                   Debug          : in Switch := Off;");
    Put_Line ("                   Summary        : in Switch := On;");
    Put_Line ("                   Verbose        : in Switch := Off;"); 
-- UMASS CODES :
    Put_Line ("                   Error_Recovery : in Switch := Off);");
-- END OF UMASS CODES.
    New_Line; 
    Put_Line ("  -- File       Specifies the Ayacc Input Source File."); 
    Put_Line ("  -- C_Lex      Specifies the Generation of a 'C' Lex Interface.");
    Put_Line ("  -- Debug      Specifies the Production of Debugging Output"); 
    Put_Line ("  --              By the Generated Parser.");
    Put_Line ("  -- Summary    Specifies the Printing of Statistics About the");
    Put_Line ("  --              Generated Parser.");
    Put_Line ("  -- Verbose    Specifies the Production of a Human Readable");
    Put_Line ("  --              Report of States in the Generated Parser.");
-- UMASS CODES :
    Put_Line ("  -- Error_Recovery  Specifies the Generation of extension of");
    Put_Line ("  --                   error recovery.");
-- END OF UMASS CODES.
    New_Line;
  end Put_Help_Message; 

begin

--VAX   Vms_Lib.Set_Error; 
  Command_Line_Interface.Initialize (Tool_Name => "Ayacc"); 

  Positional := Positional_Arg_Count; 
  Total := Named_Arg_Count + Positional; 

  if Total = 0 then
    raise Incorrect_Call;
  elsif Total > Max_Parameters then 
    Put_Line ("Ayacc: Too many parameters."); 
    raise Incorrect_Call; 
  end if; 

  -- Get named values
  File             := Named_Arg_Value ("File",      "");
  C_Lex_Argument   := Named_Arg_Value ("C_Lex",     "Off");
  Debug_Argument   := Named_Arg_Value ("Debug",     "Off");
  Summary_Argument := Named_Arg_Value ("Summary",   "On");
  Verbose_Argument := Named_Arg_Value ("Verbose",   "Off");
-- UMASS CODES :
  Error_Recovery_Argument := Named_Arg_Value ("Error_Recovery",   "Off");
-- END OF UMASS CODES.
  Extension        := Named_Arg_Value ("Extension", ".a");

  -- Get any positional associations
  if Positional >= 1 then 
    File := Positional_Arg_Value (1); 
    if Positional >= 2 then 
      C_Lex_Argument := Positional_Arg_Value (2);
      if Positional >= 3 then
        Debug_Argument := Positional_Arg_Value (3);
        if Positional >= 4 then
          Summary_Argument := Positional_Arg_Value (4);
          if Positional >= 5 then
            Verbose_Argument := Positional_Arg_Value (5);
-- UMASS CODES :
            if Positional = Max_Parameters then
              Error_Recovery_Argument := Positional_Arg_Value (5);
            end if;
-- END OF UMASS CODES.
          end if;
        end if;
      end if;
    end if; 
  end if; 

  Command_Line_Interface.Finalize; 

  C_Lex   := Convert_Switch (Value (C_Lex_Argument));
  Debug   := Convert_Switch (Value (Debug_Argument));
  Summary := Convert_Switch (Value (Summary_Argument));
  Verbose := Convert_Switch (Value (Verbose_Argument));
-- UMASS CODES :
  Error_Recovery := Convert_Switch (Value (Error_Recovery_Argument));
-- END OF UMASS CODES.

exception

  when Incorrect_Call          | Invalid_Parameter         |
       Invalid_Parameter_Order | Missing_Positional_Arg    |
       Unreferenced_Named_Arg  | Invalid_Named_Association |
       Unbalanced_Parentheses  => 

    Put_Help_Message ; 
    raise Invalid_Command_Line ; 

end Get_Arguments; 
