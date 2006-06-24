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

-- Module       : lexical_analyzer_body.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:30:42
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxlexical_analyzer_body.ada

-- $Header: lexical_analyzer_body.a,v 0.1 86/04/01 15:05:27 ada Exp $ 
-- $Log:	lexical_analyzer_body.a,v $
-- Revision 0.1  86/04/01  15:05:27  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:37:05  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

with Actions_File, Source_File, STR_Pack, Tokens_File, Text_IO;
use  Actions_File, Source_File, STR_Pack, Tokens_File, Text_IO;
package body Lexical_Analyzer is

  SCCS_ID : constant String := "@(#) lexical_analyzer_body.adadisk21~/rschm/hasee/sccs/ayacc, Version 1.2";



  Rcs_ID : constant String := "$Header: lexical_analyzer_body.a,v 0.1 86/04/01 15:05:27 ada Exp $";

    Max_Lexeme_Length : constant := 80;

    Current_Line_Number: Natural := 1;

    Lexeme_Text : STR(Max_Lexeme_Length);



    function Get_Lexeme_Text return String is
    begin
	return Value_of(Lexeme_Text);
    end Get_Lexeme_Text;


    function Line_Number return Natural is
    begin
	return Source_Line_Number;
    end Line_Number;


    procedure Skip_Comment is
	Ch: Character;
    begin
	loop
	    Get_Char(Ch);
	    if Ch = Eof then
		Unget_Char(Ch);
		exit;
	    elsif Ch = Eoln then
		Current_Line_Number := Current_Line_Number + 1;
		exit;
	    end if;
	end loop;
    end Skip_Comment;





    function Get_Token return Ayacc_Token is
	Ch: Character;
    begin
	loop
	    Assign("", To => Lexeme_Text);
	    loop
		Get_Char(Ch);
		if Ch = Eoln then
		    Current_Line_Number := Current_Line_Number + 1;
		end if;
		exit when Ch /= ' '   and then
			  Ch /= Eoln  and then
			  Ch /= Ascii.Ht;
	    end loop;

	    case Ch is
		when '-' =>
		    Get_Char(Ch);
		    if Ch = '-' then
			Skip_Comment;
		    else
			raise Illegal_Token;
		    end if;
		when ':' =>
		    Append(Ch, To => Lexeme_Text);
		    return Colon;
		when ';' =>
		    Append(Ch, To => Lexeme_Text);
		    return Semicolon;
		when ',' =>
		    Append(Ch, To => Lexeme_Text);
		    return Comma;
		when '%' =>
		    Append(Ch, To => Lexeme_Text);
		    if Peek_Next_Char = '%' then
			Get_Char(Ch);
			Append(Ch, To => Lexeme_Text);
			return Mark;
		    else
			loop
			    Get_Char(Ch);
			    if Ch not in 'A'..'Z' and then
			       Ch not in 'a'..'z' then
				Unget_Char(Ch);
				exit;
			    end if;
			    Append(Ch, To => Lexeme_Text);
			end loop;
			Upper_Case(Lexeme_Text);
			if Value_of(Lexeme_Text) = "%TOKEN" then
			    return Token;
			elsif Value_of(Lexeme_Text) = "%START" then
			    return Start;
			elsif Value_of(Lexeme_Text) = "%LEFT" then
			    return Left;
			elsif Value_of(Lexeme_Text) = "%RIGHT" then
			    return Right;
			elsif Value_of(Lexeme_Text) = "%NONASSOC" then
			    return Nonassoc;
			elsif Value_of(Lexeme_Text) = "%PREC" then
			    return Prec;
                        elsif Value_of (Lexeme_Text) = "%WITH" then
                            return With_Clause;
                        elsif Value_of (Lexeme_Text) = "%USE" then
                            return Use_Clause;
			else
			    raise Illegal_Token;
			end if;
		    end if;
		when '|' =>
		    Append(Ch, To => Lexeme_Text);
		    return Vertical_Bar;
		when '{' =>
		    Append(Ch, To => Lexeme_Text);
		    return Left_Brace;
		when Eof =>
		    return Eof_Token;
		when ''' =>
		    Append(Ch, To => Lexeme_Text);
		    Get_Char(Ch);
		    if Ch /= Eof and Ch /= Eoln then
			Append(Ch, To => Lexeme_Text);
			Get_Char(Ch);
			if Ch /= ''' then
			    raise Illegal_Token;
			else
			    Append(Ch, To => Lexeme_Text);
			end if;
			return Character_Literal;
		    end if;
		when  'A'..'Z' | 'a'..'z' | '.' | '_' =>
		    Append(Ch, To => Lexeme_Text);
		    loop
			Get_Char(Ch);
			if Ch in 'a'..'z' or else
			   Ch in 'A'..'Z' or else
			   Ch in '0'..'9' or else
			   Ch = '.'       or else
			   Ch = '_'
			then
			    Append(Ch, To => Lexeme_Text);
			else
			    Unget_Char(Ch);
			    exit;
			end if;
		    end loop;
		    Upper_Case(Lexeme_Text);
		    return Identifier;
		when others =>
		    raise Illegal_Token;
	    end case;
	end loop;
    end Get_Token;



    procedure Handle_Action(Rule, Rule_Length : Integer) is 
        Char   : Character;
        Base   : Integer;
    begin
	Actions_File.Writeln;
        Actions_File.Write("when " & Integer'Image(Rule) & " =>");
	Actions_File.Writeln;
	Actions_File.Write("--#line " & Integer'Image(Current_Line_Number));
	Actions_File.Writeln;
        loop
            Get_Char(Char);
            if Char = '-' and then Peek_Next_Char = '-' then 
		loop 
		    Actions_File.Write(Char);
		    Get_Char(Char);
		    exit when Char = Eoln; 
		end loop; 
	    end if;
       
            case Char is
                when '"' =>  
                    Actions_File.Write(Char); 
                    loop
                        Get_Char(Char);
                        Actions_File.Write(Char); 
                        exit when Char = '"';
                    end loop;
		    
		-- handle special case '"' where there is no matching ".
		when ''' => 
                    Actions_File.Write(Char); 
		    if Peek_Next_Char= '"' then
		      Get_Char(Char);
		      if Peek_Next_Char = ''' then
                        Actions_File.Write(Char); -- '"'
			Get_Char(Char);   -- '''
                        Actions_File.Write(Char); 
		      else
			UnGet_Char(Char);  -- '"'
		      end if;
		    end if;    
                when '$' =>
                    Actions_File.Writeln;

                    Get_Char(Char);
                    if Char = '$' then
                        Actions_File.Write("yyval"); 
                    elsif Char in '0'..'9' then 
                        Base := Character'Pos(Char) - Character'Pos('0');
                        while Peek_Next_Char in '0'..'9' loop 
                            Get_Char(Char);
                            Base := Base * 10 + 
                                    Character'Pos(Char) - Character'Pos('0');
                        end loop;
                        if Base > Rule_Length then
                            Put_Line("Ayacc: Illegal use of $"&Integer'Image(Base));
                            raise Illegal_Token;
                        end if;
                        Base := Base - Rule_Length;
                        if Base = 0 then 
                            Actions_File.Write("yy.value_stack(yy.tos)"); 
                        else 
                            Actions_File.Write("yy.value_stack(yy.tos" & 
                                   Integer'Image(Base) & ")");
                        end if;
                    else
                        Put_Line("Ayacc: Illegal symbol following $");
                        raise Illegal_Token;
                    end if; 

                when Eoln => 
                    Actions_File.Writeln; 
                    Current_Line_Number := Current_Line_Number + 1;  
    
                when '}'  => 
                    exit;

                when others =>  
                    Actions_File.Write(Char);
            end case;  

        end loop; 
        Actions_File.Writeln;  
    end Handle_Action; 

    procedure Dump_Declarations is 
        Ch   : Character;
        Text : STR(Source_File.Maximum_Line_Length);
    begin 
        Assign("", To => Text); 
        loop 
            Get_Char(Ch); 
            exit when Ch = '}' ;

            case Ch is 
                when  '-'   => Append(Ch, To => Text);  
                               if Peek_Next_Char = '-' then 
	                           loop
	                               Get_Char(Ch);
                                       Append(Ch, To => Text);      
                                       exit when Peek_Next_Char = Eoln or
                                                 Peek_Next_Char = Eof; 
	                           end loop;
                               end if;
                when  '"'   => Append(Ch, To => Text); 
                               loop 
                                   Get_Char(Ch); 
                                   if Ch = Eoln or Ch = Eof then 
                                       raise Illegal_Token; 
                                   end if;
                                   Append(Ch, To => Text); 
                                   exit when Ch = '"'; 
                               end loop; 
                when Eoln   => Tokens_File.Writeln(Value_of(Text)); 
                               Assign("", To => Text); 
                               Current_Line_Number := Current_Line_Number + 1; 
                when Eof    => exit;  
                when others => Append(Ch, To => Text); 
            end case; 
        end loop;
        Tokens_File.Writeln(Value_of(Text)); 
    end Dump_Declarations; 

end Lexical_Analyzer; 
