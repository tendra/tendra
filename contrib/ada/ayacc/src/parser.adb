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

-- Module       : parser_body.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:32:43
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxparser_body.ada

-- $Header: parser_body.a,v 0.1 86/04/01 15:10:24 ada Exp $ 
-- $Log:	parser_body.a,v $
-- Revision 0.1  86/04/01  15:10:24  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:40:31  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

-- 							--
-- The body of the parser for the specification file    -- 
-- 							--

with Text_IO;          use Text_IO; 
with Lexical_Analyzer; use Lexical_Analyzer; 
with STR_Pack;         use STR_Pack; 
with Symbol_Table;     use Symbol_Table; 
with Rule_Table;       use Rule_Table; 
with Actions_File;     use Actions_File; 
with Tokens_File;      use Tokens_File;

with String_Pkg;
package body Parser is 

  SCCS_ID : constant String := "@(#) parser_body.ada, Version 1.2";


   
     Found_Error   : Boolean := False;
     Start_Defined : Boolean := False;

     procedure Nonfatal_Error(Message: in String) is
     begin
	 Print_Context_Lines;
--RJS	 Put_Line("--- " & Message);
         New_Line;
         Put_Line ("Ayacc: " & Message);
	 Found_Error := True;
     end Nonfatal_Error;

     procedure Fatal_Error(Message: in String) is
     begin
	 Print_Context_Lines;
--RJS	 Put_Line("--- " & Message);
         New_Line;
         Put_Line ("Ayacc: " & Message);
	 raise Syntax_Error;
     end Fatal_Error;

     procedure Augment_Grammar(Users_Start_Symbol : in Grammar_Symbol) is  
     -- Inserts S' -> S $end as a rule in the rule table.
         Start_Sym      : Grammar_Symbol; 
         Augmented_Rule : Rule;  
     begin 
         Start_Defined  := True; 
         Augmented_Rule := Make_Rule(Start_Symbol); 
         Append_RHS(Augmented_Rule, Users_Start_Symbol);  
	 Append_RHS(Augmented_Rule, End_Symbol);
     end Augment_Grammar; 

 
   -- 							--
   -- A recursive descent parser for the rules in the   -- 
   -- grammar.                                          -- 
 
   procedure Parse_Rules is
      T : Ayacc_Token;  
      Current_Rule : Rule;  
      LHS          : Grammar_Symbol; 
  
      --						--
      -- Gets an action from the file and writes it to  -- 
      -- the actions file. 				--
      -- 						--  

      --  						--
      --          Parses a sequence of Symbols          --
      -- 						-- 
      procedure Symbols is 
          ID               : Grammar_Symbol; 
          Got_Action       : Boolean := False; 
          Precedence_Level : Precedence; 
      begin
          loop 
              T := Get_Token;
              exit when T = Vertical_Bar or T = Semicolon or T = Prec; 

              -- Do we have an action in the middle of a rule? 
              if Got_Action then 
                  Got_Action := T = Left_Brace; 
                  Handle_Nested_Rule(Current_Rule);
              end if; 

              case T is  
                  -- Update the current rule 
                  when Character_Literal => 
                      ID := Insert_Terminal(Get_Lexeme_Text);
                      Append_RHS(Current_Rule, ID); 

                  -- Update the current rule and add to symbol table
                  when Identifier => 
                      ID := Insert_Identifier(Get_Lexeme_Text);
                      Append_RHS(Current_Rule, ID); 

                  -- Got an action      
                  when Left_Brace => 
                      Handle_Action(Integer(Current_Rule), 
                                    Integer(Length_of(Current_Rule)));
                      Got_Action := True; 
            
                  when others => 
                      Fatal_Error("Unexpected symbol"); 
              end case;   
  
          end loop; 

          if T = Prec then 

              if Got_Action then 
                  Fatal_Error("%prec cannot be preceded by an action");
                  raise Syntax_Error; 
              end if; 

              T := Get_Token; 
              if T /= Identifier and T /= Character_Literal then 
                  Fatal_Error("Expecting a terminal after %prec"); 
              end if; 

              ID := Insert_Identifier(Get_Lexeme_Text); 
              if Is_Nonterminal(ID) then 
                  Fatal_Error("Expecting a terminal after %prec"); 
              end if; 
    
              Precedence_Level := Get_Precedence(ID); 
              if Precedence_Level = 0 then 
                  Fatal_Error("Terminal following %prec has no precedence"); 
              else 
                  Set_Rule_Precedence(Current_Rule, Precedence_Level);  
              end if; 

              T := Get_Token; 
              case T is 
                  when Left_Brace => 
                      Handle_Action(Integer(Current_Rule), 
                                    Integer(Length_of(Current_Rule)));
                      T := Get_Token; 
                  when Semicolon | Vertical_Bar => 
                      null; 
                  when others => 
                      Fatal_Error("Illegal token following %prec"); 
              end case;  
          end if; 

      end Symbols;

      -- 							--
      -- 		Parse an Ayacc grammar rule 		-- 
      -- 							--
      procedure Rule is 
      begin
          T := Get_Token; 
          if T /= Colon then
               Fatal_Error("Expecting a colon after the LHS of the rule");
          else
               Current_Rule := Make_Rule(LHS); 
               Symbols;
          end if; 
          while (T = Vertical_Bar) loop 
               -- Make a new rule with the current LHS grammar symbol  
               Current_Rule := Make_Rule(LHS); 
               Symbols; 
          end loop; 
          if T /= Semicolon then
               Fatal_Error("Expecting a semicolon"); 
          end if; 
      end Rule;


      -- 							--
      -- 		Parse a sequence of grammar rules       -- 
      -- 							--
      procedure Rules is 
      begin
          T := Get_Token;
          if T = Identifier then 
              -- Make the left hand side of the rule 
	      LHS := Insert_Identifier(Get_Lexeme_Text);
	      if Is_Terminal(LHS) then 
		  Fatal_Error("Terminals cannot be on the LHS of a rule"); 
	      end if;             
              if not Start_Defined then 
                 Augment_Grammar(LHS); 
              end if;  
              Rule;
              Rules;
          elsif T /= Mark then
              Fatal_Error("Expecting next section"); 
          end if; 
      end Rules;
   
   begin -- parse_rules 

       Actions_File.Initialize; 
       Rules; 
       Actions_File.Finish;  

       -- Check for empty grammars. If the grammar is empty then
       -- create a rule S -> $end.
       if not Start_Defined then
	   Append_RHS(Make_Rule(Start_Symbol), End_Symbol);
       end if;
   
       exception 
	   when Illegal_Token => 
	       Fatal_Error("illegal token");
   end Parse_Rules; 



   -- 								--
   -- 		Parse the declarations section of the source    -- 
   -- 								--

    procedure Parse_Declarations is

	Precedence_Level : Precedence := 0;
        Next_Token       : Ayacc_Token;
	ID               : Grammar_Symbol;

	procedure Parse_Start_Symbol is
	    Users_Start_Symbol : Grammar_Symbol;
	begin

	    if Start_Defined then
		Fatal_Error("The start symbol has been defined already.");
	    end if;

	    if Next_Token /= Identifier then
		if Next_Token = Lexical_Analyzer.Eof_Token then
		    Fatal_Error("Unexpected end of file before first '%%'");
		else
		    Fatal_Error("Expecting identifier");
		end if;
	    end if;

	    Users_Start_Symbol := Insert_Identifier(Get_Lexeme_Text);
	    if Is_Nonterminal(Users_Start_Symbol) then
		Augment_Grammar(Users_Start_Symbol); 
	    else
		Fatal_Error("Attempt to define terminal as start_symbol");
	    end if;
	    Next_Token := Get_Token;

	end Parse_Start_Symbol;

	procedure Parse_Token_List(Precedence_Value    : in Precedence;
				   Associativity_Value : in Associativity) is
	    Temp_Sym : Grammar_Symbol;
	begin
	    loop
		if Next_Token /= Identifier and then
		   Next_Token /= Character_Literal then
		    if Next_Token = Lexical_Analyzer.Eof_Token then
			Fatal_Error("Unexpected end of file before first '%%'");
		    else
			Fatal_Error("Expecting token declaration");
		    end if;
		end if;

		Temp_Sym := Insert_Terminal(Get_Lexeme_Text,
					    Precedence_Value,
					    Associativity_Value);

		Next_Token := Get_Token;
		if Next_Token = Comma then
		    Next_Token := Get_Token;
		elsif Next_Token = Semicolon then
		    Next_Token := Get_Token;
		    exit;
		elsif Next_Token /= Identifier and then
		      Next_Token /= Character_Literal then
		    exit;
		end if;
	    end loop;
	    exception
		when Illegal_Entry => 
		    -- I think only trying to insert the "start symbol"
		    -- in a token list will cause this exception
		    Fatal_Error("Illegal symbol as token");
	end Parse_Token_List;
       

	procedure Parse_Package_Name_List(Context_Clause : in Ayacc_Token) is
          use String_Pkg;
	begin

          if Tokens_Package_Header_Has_Been_Generated then

            Fatal_Error ("Context Clause Specifications May Not " &
                                "Appear After Ada Declarations.");

          else

            case Context_Clause is
              when With_Clause =>
                Tokens_File.Write ("with ");
              when Use_Clause  =>
                Tokens_File.Write ("use  ");
              when others      =>
                Fatal_Error ("Illegal Context Clause Specification");
            end case;

	    loop
		if Next_Token /= Identifier then
		    if Next_Token = Lexical_Analyzer.Eof_Token then
			Fatal_Error("Unexpected end of file before first '%%'");
		    else
			Fatal_Error("Expecting Package Name");
		    end if;
		end if;

                Tokens_File.Write (' ' & Value (Mixed (Get_Lexeme_Text)));
		Next_Token := Get_Token;

		if Next_Token = Comma then
		    Next_Token := Get_Token;
                    Tokens_File.Write (",");
		elsif Next_Token = Semicolon then
		    Next_Token := Get_Token;
                    Tokens_File.Writeln (";");
		    exit;
		elsif Next_Token /= Identifier then
                    Tokens_File.Writeln (";");
		    exit;
                else
                    Tokens_File.Write (",");
		end if;
	    end loop;

          end if;

	end Parse_Package_Name_List;
       

    begin

	Next_Token := Get_Token; 

	loop
	    case Next_Token is
		when Start =>
		    Next_Token := Get_Token;
		    Parse_Start_Symbol;
		    if Next_Token = Semicolon then
		        Next_Token := Get_Token;
		    end if;
		when Token =>
		    Next_Token := Get_Token;
		    Parse_Token_List(0, Undefined);
		when Nonassoc =>
		    Next_Token := Get_Token;
		    Precedence_Level := Precedence_Level + 1;
		    Parse_Token_List(Precedence_Level, Nonassociative);
		when Right =>
		    Next_Token := Get_Token;
		    Precedence_Level := Precedence_Level + 1;
		    Parse_Token_List(Precedence_Level, Right_Associative);
		when Left =>
		    Next_Token := Get_Token;
		    Precedence_Level := Precedence_Level + 1;
		    Parse_Token_List(Precedence_Level, Left_Associative);
		when Mark =>
		    exit;
		when Lexical_Analyzer.Eof_Token =>
		    Fatal_Error("Unexpected end of file before first %%");
		when Left_Brace =>
                    Start_Tokens_Package;
		    Dump_Declarations;  -- to the TOKENS file.
                    Next_Token := Get_Token;
                when With_Clause =>
                    Next_Token := Get_Token;
                    Parse_Package_Name_List (With_Clause);
                when Use_Clause  =>
                    Next_Token := Get_Token;
                    Parse_Package_Name_List (Use_Clause);
		when others =>
		    Fatal_Error("Unexpected symbol");
	    end case;
	end loop;

    exception
	when Illegal_Token =>
	    Fatal_Error("Bad symbol");
	when Redefined_Precedence_Error =>
	    Fatal_Error("Attempt to redefine precedence");
    end Parse_Declarations; 

end Parser; 
