

separate (Ayacc)
procedure Print_Statistics is
    use Text_IO, Parse_Table, Rule_Table, Symbol_Table;
begin

    if Options.Summary then

	Put_Line(Rule'Image(Last_Rule - First_Rule + 1) & " Productions");

	Put_Line(Grammar_Symbol'Image
	  (Last_Symbol(Nonterminal) - First_Symbol(Nonterminal) + 1) &
	   " Nonterminals");

	Put_Line(Grammar_Symbol'Image
	  (Last_Symbol(Terminal) - First_Symbol(Terminal) + 1) &
	   " Terminals");

	Put_Line(Integer'Image(Number_of_States) & " States");

	Put_Line (Integer'Image(Shift_Reduce_Conflicts) &
		  " Shift/Reduce conflicts");

	Put_Line (Integer'Image(Reduce_Reduce_Conflicts) &
		  " Reduce/Reduce conflicts");

    else

	if Shift_Reduce_Conflicts /= 0 then
	    Put_Line (Integer'Image(Shift_Reduce_Conflicts) &
		      " Shift/Reduce Conflicts");
	end if;
	if Reduce_Reduce_Conflicts /= 0 then
	    Put_Line (Integer'Image(Reduce_Reduce_Conflicts) &
		      " Reduce/Reduce Conflicts");
	end if;

    end if;

end Print_Statistics;
