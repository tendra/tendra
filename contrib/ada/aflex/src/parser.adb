
package body parser is
-- build_eof_action - build the "<<EOF>>" action for the active start
--                    conditions

use text_io, misc_defs;
procedure build_eof_action is
begin
    text_io.put( temp_action_file, "when " );
    for i in 1..actvp loop
	if ( sceof(actvsc(i)) ) then
	    text_io.put( Standard_Error,
		"multiple <<EOF>> rules for start condition ");
	    tstring.put( Standard_Error, scname(actvsc(i)));
	    main_body.aflexend(1);
	else
	    sceof(actvsc(i)) := true;
	    text_io.put( temp_action_file, "YY_END_OF_BUFFER +" );
	    tstring.put( temp_action_file,  scname(actvsc(i)) );
	    text_io.put_line( temp_action_file, " + 1 " );
	    if (i /= actvp) then
	        text_io.put_line( temp_action_file, " |" );
	    else
	        text_io.put_line( temp_action_file, " =>" );
	    end if;
        end if;
    end loop;
    misc.line_directive_out( temp_action_file );
end build_eof_action;

--  yyerror - eat up an error message from the parser
-- 
--  synopsis
--     char msg[];
--     yyerror( msg );

procedure yyerror( msg : string ) is
begin
null;
end yyerror;

use  Parse_Goto, Parse_Shift_Reduce, Text_IO, misc_defs, tstring;
procedure YYParse is

   -- Rename User Defined Packages to Internal Names.
    package yy_goto_tables         renames
      Parse_Goto;
    package yy_shift_reduce_tables renames
      Parse_Shift_Reduce;
    package yy_tokens              renames
      Parse_Tokens;

   use yy_tokens, yy_goto_tables, yy_shift_reduce_tables;

   procedure yyerrok;
   procedure yyclearin;


   package yy is

       -- the size of the value and state stacks
       stack_size : constant Natural := 300;

       -- subtype rule         is natural;
       subtype parse_state  is natural;
       -- subtype nonterminal  is integer;

       -- encryption constants
       default           : constant := -1;
       first_shift_entry : constant :=  0;
       accept_code       : constant := -1001;
       error_code        : constant := -1000;

       -- stack data used by the parser
       tos                : natural := 0;
       value_stack        : array(0..stack_size) of yy_tokens.yystype;
       state_stack        : array(0..stack_size) of parse_state;

       -- current input symbol and action the parser is on
       action             : integer;
       rule_id            : rule;
       input_symbol       : yy_tokens.token;


       -- error recovery flag
       error_flag : natural := 0;
          -- indicates  3 - (number of valid shifts after an error occurs)

       look_ahead : boolean := true;
       index      : integer;

       -- Is Debugging option on or off
        DEBUG : constant boolean := FALSE;

    end yy;


    function goto_state
      (state : yy.parse_state;
       sym   : nonterminal) return yy.parse_state;

    function parse_action
      (state : yy.parse_state;
       t     : yy_tokens.token) return integer;

    pragma inline(goto_state, parse_action);


    function goto_state(state : yy.parse_state;
                        sym   : nonterminal) return yy.parse_state is
        index : integer;
    begin
        index := goto_offset(state);
        while  integer(goto_matrix(index).nonterm) /= sym loop
            index := index + 1;
        end loop;
        return integer(goto_matrix(index).newstate);
    end goto_state;


    function parse_action(state : yy.parse_state;
                          t     : yy_tokens.token) return integer is
        index      : integer;
        tok_pos    : integer;
        default    : constant integer := -1;
    begin
        tok_pos := yy_tokens.token'pos(t);
        index   := shift_reduce_offset(state);
        while integer(shift_reduce_matrix(index).t) /= tok_pos and then
              integer(shift_reduce_matrix(index).t) /= default
        loop
            index := index + 1;
        end loop;
        return integer(shift_reduce_matrix(index).act);
    end parse_action;

-- error recovery stuff

    procedure handle_error is
      temp_action : integer;
    begin

      if yy.error_flag = 3 then -- no shift yet, clobber input.
      if yy.debug then
          text_io.put_line("Ayacc.YYParse: Error Recovery Clobbers " &
                   yy_tokens.token'image(yy.input_symbol));
      end if;
        if yy.input_symbol = yy_tokens.end_of_input then  -- don't discard,
        if yy.debug then
            text_io.put_line("Ayacc.YYParse: Can't discard END_OF_INPUT, quiting...");
        end if;
        raise yy_tokens.syntax_error;
        end if;

            yy.look_ahead := true;   -- get next token
        return;                  -- and try again...
    end if;

    if yy.error_flag = 0 then -- brand new error
        yyerror("Syntax Error");
    end if;

    yy.error_flag := 3;

    -- find state on stack where error is a valid shift --

    if yy.debug then
        text_io.put_line("Ayacc.YYParse: Looking for state with error as valid shift");
    end if;

    loop
        if yy.debug then
          text_io.put_line("Ayacc.YYParse: Examining State " &
               yy.parse_state'image(yy.state_stack(yy.tos)));
        end if;
        temp_action := parse_action(yy.state_stack(yy.tos), error);

            if temp_action >= yy.first_shift_entry then
                if yy.tos = yy.stack_size then
                    text_io.put_line(" Stack size exceeded on state_stack");
                    raise yy_Tokens.syntax_error;
                end if;
                yy.tos := yy.tos + 1;
                yy.state_stack(yy.tos) := temp_action;
                exit;
            end if;

        Decrement_Stack_Pointer :
        begin
          yy.tos := yy.tos - 1;
        exception
          when Constraint_Error =>
            yy.tos := 0;
        end Decrement_Stack_Pointer;

        if yy.tos = 0 then
          if yy.debug then
            text_io.put_line("Ayacc.YYParse: Error recovery popped entire stack, aborting...");
          end if;
          raise yy_tokens.syntax_error;
        end if;
    end loop;

    if yy.debug then
        text_io.put_line("Ayacc.YYParse: Shifted error token in state " &
              yy.parse_state'image(yy.state_stack(yy.tos)));
    end if;

    end handle_error;

   -- print debugging information for a shift operation
   procedure shift_debug(state_id: yy.parse_state; lexeme: yy_tokens.token) is
   begin
       text_io.put_line("Ayacc.YYParse: Shift "& yy.parse_state'image(state_id)&" on input symbol "&
               yy_tokens.token'image(lexeme) );
   end;

   -- print debugging information for a reduce operation
   procedure reduce_debug(rule_id: rule; state_id: yy.parse_state) is
   begin
       text_io.put_line("Ayacc.YYParse: Reduce by rule "&rule'image(rule_id)&" goto state "&
               yy.parse_state'image(state_id));
   end;

   -- make the parser believe that 3 valid shifts have occured.
   -- used for error recovery.
   procedure yyerrok is
   begin
       yy.error_flag := 0;
   end yyerrok;

   -- called to clear input symbol that caused an error.
   procedure yyclearin is
   begin
       -- yy.input_symbol := yylex;
       yy.look_ahead := true;
   end yyclearin;


begin
    -- initialize by pushing state 0 and getting the first input symbol
    yy.state_stack(yy.tos) := 0;


    loop

        yy.index := shift_reduce_offset(yy.state_stack(yy.tos));
        if integer(shift_reduce_matrix(yy.index).t) = yy.default then
            yy.action := integer(shift_reduce_matrix(yy.index).act);
        else
            if yy.look_ahead then
                yy.look_ahead   := false;

                yy.input_symbol := yylex;
            end if;
            yy.action :=
             parse_action(yy.state_stack(yy.tos), yy.input_symbol);
        end if;


        if yy.action >= yy.first_shift_entry then  -- SHIFT

            if yy.debug then
                shift_debug(yy.action, yy.input_symbol);
            end if;

            -- Enter new state
            if yy.tos = yy.stack_size then
                text_io.put_line(" Stack size exceeded on state_stack");
                raise yy_Tokens.syntax_error;
            end if;
            yy.tos := yy.tos + 1;
            yy.state_stack(yy.tos) := yy.action;
              yy.value_stack(yy.tos) := yylval;

        if yy.error_flag > 0 then  -- indicate a valid shift
            yy.error_flag := yy.error_flag - 1;
        end if;

            -- Advance lookahead
            yy.look_ahead := true;

        elsif yy.action = yy.error_code then       -- ERROR

            handle_error;

        elsif yy.action = yy.accept_code then
            if yy.debug then
                text_io.put_line("Ayacc.YYParse: Accepting Grammar...");
            end if;
            exit;

        else -- Reduce Action

            -- Convert action into a rule
            yy.rule_id  := -1 * yy.action;

            -- Execute User Action
            -- user_action(yy.rule_id);


                case yy.rule_id is

when  1 =>
--#line  44
 -- add default rule

			pat := ccl.cclinit;
			ccl.cclnegate( pat );

			def_rule := nfa.mkstate( -pat );

			nfa.finish_rule( def_rule, false, 0, 0 );

			for i in 1 .. lastsc loop
			    scset(i) := nfa.mkbranch( scset(i), def_rule );
			end loop;
			
			if ( spprdflt ) then
			    text_io.put(temp_action_file,
					"raise AFLEX_SCANNER_JAMMED;");
			else
			    text_io.put( temp_action_file, "ECHO" );

			text_io.put_line( temp_action_file, ";" );
			end if;
			

when  2 =>
--#line  69

			-- initialize for processing rules

       			-- create default DFA start condition
			sym.scinstal( tstring.vstr("INITIAL"), false );
			

when  5 =>
--#line  80
 misc.synerr( "unknown error processing section 1" );

when  7 =>
--#line  87

			 -- these productions are separate from the s1object
			 -- rule because the semantics must be done before
			 -- we parse the remainder of an s1object
			

			xcluflg := false;
			

when  8 =>
--#line  97
 xcluflg := true; 

when  9 =>
--#line  101
 sym.scinstal( nmstr, xcluflg ); 

when  10 =>
--#line  104
 sym.scinstal( nmstr, xcluflg ); 

when  11 =>
--#line  107
 misc.synerr( "bad start condition list" ); 

when  14 =>
--#line  115

			-- initialize for a parse of one rule
			trlcontxt := false;
			variable_trail_rule := false;
			varlength := false;
			trailcnt := 0;
			headcnt := 0;
			rulelen := 0;
			current_state_enum := STATE_NORMAL;
			previous_continued_action := continued_action;
			nfa.new_rule;
			

when  15 =>
--#line  130

			pat := nfa.link_machines( 
yy.value_stack(yy.tos-1), 
yy.value_stack(yy.tos) );
			nfa.finish_rule( pat, variable_trail_rule,
				     headcnt, trailcnt );

			for i in 1 .. actvp loop
			    scbol(actvsc(i)) :=
				nfa.mkbranch( scbol(actvsc(i)), pat );
			end loop;	
				
			if ( not bol_needed ) then
			    bol_needed := true;

			    if ( performance_report ) then
				text_io.put( Standard_Error,
			"'^' operator results in sub-optimal performance");
			        text_io.new_line(Standard_Error);
    	    	    	    end if;
			end if;
			

when  16 =>
--#line  152

			pat := nfa.link_machines( 
yy.value_stack(yy.tos-1), 
yy.value_stack(yy.tos) );
			nfa.finish_rule( pat, variable_trail_rule,
				     headcnt, trailcnt );

			for i in 1 .. actvp loop
			    scset(actvsc(i)) := 
				nfa.mkbranch( scset(actvsc(i)), pat );
			end loop;
		        

when  17 =>
--#line  163

			pat := nfa.link_machines( 
yy.value_stack(yy.tos-1), 
yy.value_stack(yy.tos) );
			nfa.finish_rule( pat, variable_trail_rule,
				     headcnt, trailcnt );

			-- add to all non-exclusive start conditions,
			-- including the default (0) start condition

			for i in 1 .. lastsc loop
			    if ( not scxclu(i) ) then
				scbol(i) := nfa.mkbranch( scbol(i), pat );
			    end if;	
			end loop;

			if ( not bol_needed ) then
			    bol_needed := true;

			    if ( performance_report ) then
				text_io.put( Standard_Error,
			"'^' operator results in sub-optimal performance");
			        text_io.new_line(Standard_Error);
			    end if;
			end if;
    	    	    	

when  18 =>
--#line  188

			pat := nfa.link_machines( 
yy.value_stack(yy.tos-1), 
yy.value_stack(yy.tos) );
			nfa.finish_rule( pat, variable_trail_rule,
				     headcnt, trailcnt );

			for i in 1 .. lastsc loop
			    if ( not scxclu(i) ) then
				scset(i) := nfa.mkbranch( scset(i), pat );
			    end if;
			end loop;
			

when  19 =>
--#line  201
 build_eof_action; 

when  20 =>
--#line  204

			-- this EOF applies only to the INITIAL start cond.
			actvp := 1;
			actvsc(actvp) := 1;
			build_eof_action;
			

when  21 =>
--#line  212
 misc.synerr( "unrecognized rule" ); 

when  23 =>
--#line  219

			scnum := sym.sclookup( nmstr );
			if (scnum = 0 ) then
		            text_io.put( Standard_Error,
					 "undeclared start condition ");
		            tstring.put( Standard_Error, nmstr );
			    main_body.aflexend( 1 );
			else
			  actvp := actvp + 1;
			    actvsc(actvp) := scnum;
			end if;
			

when  24 =>
--#line  233

			scnum := sym.sclookup( nmstr );
			if (scnum = 0 ) then
		            text_io.put( Standard_Error,
					"undeclared start condition ");
		            tstring.put( Standard_Error,	 nmstr );
			    main_body.aflexend ( 1 );
			else
			    actvp := 1;
			    actvsc(actvp) := scnum;
			end if;
			

when  25 =>
--#line  247
 misc.synerr( "bad start condition list" ); 

when  26 =>
--#line  251

			if trlcontxt then
			    misc.synerr( "trailing context used twice" );
			    
yyval := nfa.mkstate( SYM_EPSILON );
			else
			    trlcontxt := true;

			    if ( not varlength ) then
				headcnt := rulelen;
			    end if;

			    rulelen := rulelen + 1;
			    trailcnt := 1;

			    eps := nfa.mkstate( SYM_EPSILON );
			    
yyval := nfa.link_machines( eps,
					  nfa.mkstate( CHARACTER'POS(ASCII.LF) ) );
    	    	    	end if;
			

when  27 =>
--#line  272

		        
yyval := nfa.mkstate( SYM_EPSILON );

			if ( trlcontxt ) then
			    if ( varlength and (headcnt = 0) ) then
				-- both head and trail are variable-length
				variable_trail_rule := true;
			    else
				trailcnt := rulelen;
			    end if;
    	    	    	end if;
		        

when  28 =>
--#line  287

			varlength := true;

			
yyval := nfa.mkor( 
yy.value_stack(yy.tos-2), 
yy.value_stack(yy.tos) );
			

when  29 =>
--#line  294

			if ( transchar(lastst(
yy.value_stack(yy.tos))) /= SYM_EPSILON ) then
			    -- provide final transition \now/ so it
			    -- will be marked as a trailing context
			    -- state

			    
yy.value_stack(yy.tos) := nfa.link_machines( 
yy.value_stack(yy.tos), nfa.mkstate( SYM_EPSILON ) );
			end if;

			nfa.mark_beginning_as_normal( 
yy.value_stack(yy.tos) );
			current_state_enum := STATE_NORMAL;

			if ( previous_continued_action ) then
			    -- we need to treat this as variable trailing
			    -- context so that the backup does not happen
			    -- in the action but before the action switch
			    -- statement.  If the backup happens in the
			    -- action, then the rules "falling into" this
			    -- one's action will *also* do the backup,
			    -- erroneously.

			    	if ( (not varlength) or  headcnt /= 0 ) then
				     text_io.put( Standard_Error,
                              "alex: warning - trailing context rule at line");
                                     int_io.put(Standard_Error, linenum);
				     text_io.put( Standard_Error,
                           "made variable because of preceding '|' action" );
                                     int_io.put(Standard_Error, linenum);
    	    	    	    	end if;

			    -- mark as variable
			    varlength := true;
			    headcnt := 0;
    	    	    	end if;
			
			if ( varlength and (headcnt = 0) ) then
			    -- variable trailing context rule
			    -- mark the first part of the rule as the accepting
			    -- "head" part of a trailing context rule

			    -- by the way, we didn't do this at the beginning
			    -- of this production because back then
			    -- current_state_enum was set up for a trail
			    -- rule, and add_accept() can create a new
			    -- state ...

			    nfa.add_accept( 
yy.value_stack(yy.tos-1),
    	    	    	    	   misc.set_yy_trailing_head_mask(num_rules) );
    	    	    	end if;

			
yyval := nfa.link_machines( 
yy.value_stack(yy.tos-1), 
yy.value_stack(yy.tos) );
			

when  30 =>
--#line  348
 
yyval := 
yy.value_stack(yy.tos); 

when  31 =>
--#line  353

			-- this rule is separate from the others for "re" so
			-- that the reduction will occur before the trailing
			-- series is parsed

			if ( trlcontxt ) then
			    misc.synerr( "trailing context used twice" );
			else
			    trlcontxt := true;
			end if;    

			if ( varlength ) then
			    -- we hope the trailing context is fixed-length
			    varlength := false;
			else
			    headcnt := rulelen;
			end if;    

			rulelen := 0;

			current_state_enum := STATE_TRAILING_CONTEXT;
			
yyval := 
yy.value_stack(yy.tos-1);
			

when  32 =>
--#line  379

			-- this is where concatenation of adjacent patterns
			-- gets done

			
yyval := nfa.link_machines( 
yy.value_stack(yy.tos-1), 
yy.value_stack(yy.tos) );
			

when  33 =>
--#line  387
 
yyval := 
yy.value_stack(yy.tos); 

when  34 =>
--#line  391

			varlength := true;

			
yyval := nfa.mkclos( 
yy.value_stack(yy.tos-1) );
			

when  35 =>
--#line  398

			varlength := true;

			
yyval := nfa.mkposcl( 
yy.value_stack(yy.tos-1) );
			

when  36 =>
--#line  405

			varlength := true;

			
yyval := nfa.mkopt( 
yy.value_stack(yy.tos-1) );
			

when  37 =>
--#line  412

			varlength := true;

			if ( (
yy.value_stack(yy.tos-3) > 
yy.value_stack(yy.tos-1)) or (
yy.value_stack(yy.tos-3) < 0) ) then
			    misc.synerr( "bad iteration values" );
			    
yyval := 
yy.value_stack(yy.tos-5);
			else
			    if ( 
yy.value_stack(yy.tos-3) = 0 ) then
				
yyval := nfa.mkopt( nfa.mkrep( 
yy.value_stack(yy.tos-5), 
yy.value_stack(yy.tos-3), 
yy.value_stack(yy.tos-1) ) );
			    else
				
yyval := nfa.mkrep( 
yy.value_stack(yy.tos-5), 
yy.value_stack(yy.tos-3), 
yy.value_stack(yy.tos-1) );
			    end if;
    	    	    	end if;
			

when  38 =>
--#line  428

			varlength := true;

			if ( 
yy.value_stack(yy.tos-2) <= 0 ) then
			    misc.synerr( "iteration value must be positive" );
			    
yyval := 
yy.value_stack(yy.tos-4);
			else
			    
yyval := nfa.mkrep( 
yy.value_stack(yy.tos-4), 
yy.value_stack(yy.tos-2), INFINITY );
			end if;    
			

when  39 =>
--#line  440

			-- the singleton could be something like "(foo)",
			-- in which case we have no idea what its length
			-- is, so we punt here.

			varlength := true;

			if ( 
yy.value_stack(yy.tos-1) <= 0 ) then
			    misc.synerr( "iteration value must be positive" );
			    
yyval := 
yy.value_stack(yy.tos-3);
			else
			    
yyval := nfa.link_machines( 
yy.value_stack(yy.tos-3), nfa.copysingl( 
yy.value_stack(yy.tos-3), 
yy.value_stack(yy.tos-1) - 1 ) );
			end if;    
			

when  40 =>
--#line  456

			if ( not madeany ) then
			    -- create the '.' character class
			    anyccl := ccl.cclinit;
			    ccl.ccladd( anyccl, ASCII.LF );
			    ccl.cclnegate( anyccl );

			    if ( useecs ) then
				ecs.mkeccl(
		       ccltbl(cclmap(anyccl)..cclmap(anyccl) + ccllen(anyccl)),
					ccllen(anyccl), nextecm,
					ecgroup, CSIZE );
			    end if;
			    madeany := true;
    	    	    	end if;

			rulelen := rulelen + 1;

			
yyval := nfa.mkstate( -anyccl );
			

when  41 =>
--#line  478

			if ( not cclsorted ) then
			    -- sort characters for fast searching.  We use a
			    -- shell sort since this list could be large.

--			    misc.cshell( ccltbl + cclmap($1), ccllen($1) );
		      misc.cshell( ccltbl(cclmap(
yy.value_stack(yy.tos))..cclmap(
yy.value_stack(yy.tos)) + ccllen(
yy.value_stack(yy.tos))),
				   ccllen(
yy.value_stack(yy.tos)) );
			end if;

			if ( useecs ) then
		    ecs.mkeccl( ccltbl(cclmap(
yy.value_stack(yy.tos))..cclmap(
yy.value_stack(yy.tos)) + ccllen(
yy.value_stack(yy.tos))),
				ccllen(
yy.value_stack(yy.tos)),nextecm, ecgroup, CSIZE );
			end if;
				     
			rulelen := rulelen + 1;

			
yyval := nfa.mkstate( -
yy.value_stack(yy.tos) );
			

when  42 =>
--#line  499

			rulelen := rulelen + 1;

			
yyval := nfa.mkstate( -
yy.value_stack(yy.tos) );
			

when  43 =>
--#line  506
 
yyval := 
yy.value_stack(yy.tos-1); 

when  44 =>
--#line  509
 
yyval := 
yy.value_stack(yy.tos-1); 

when  45 =>
--#line  512

			rulelen := rulelen + 1;

			if ( 
yy.value_stack(yy.tos) = CHARACTER'POS(ASCII.NUL) ) then
			    misc.synerr( "null in rule" );
			end if;    

			if ( caseins and (
yy.value_stack(yy.tos) >= CHARACTER'POS('A')) and (
yy.value_stack(yy.tos) <= CHARACTER'POS('Z')) ) then
			    
yy.value_stack(yy.tos) := misc.clower( 
yy.value_stack(yy.tos) );
			end if;

			
yyval := nfa.mkstate( 
yy.value_stack(yy.tos) );
			

when  46 =>
--#line  528
 
yyval := 
yy.value_stack(yy.tos-1); 

when  47 =>
--#line  531

			-- *Sigh* - to be compatible Unix lex, negated ccls
			-- match newlines
			ccl.cclnegate( 
yy.value_stack(yy.tos-1) );
			
yyval := 
yy.value_stack(yy.tos-1);
			

when  48 =>
--#line  540

			if ( 
yy.value_stack(yy.tos-2) > 
yy.value_stack(yy.tos) ) then
			    misc.synerr( "negative range in character class" );
			else
			    if ( caseins ) then
				if ( (
yy.value_stack(yy.tos-2) >= CHARACTER'POS('A')) and (
yy.value_stack(yy.tos-2) <= CHARACTER'POS('Z')) ) then
				    
yy.value_stack(yy.tos-2) := misc.clower( 
yy.value_stack(yy.tos-2) );
				end if;					    
				if ( (
yy.value_stack(yy.tos) >= CHARACTER'POS('A')) and (
yy.value_stack(yy.tos) <= CHARACTER'POS('Z')) ) then
				    
yy.value_stack(yy.tos) := misc.clower( 
yy.value_stack(yy.tos) );
				end if;    
    	    	    	    end if;

			    for i in 
yy.value_stack(yy.tos-2) .. 
yy.value_stack(yy.tos) loop
			        ccl.ccladd( 
yy.value_stack(yy.tos-3), CHARACTER'VAL(i) );
    	    	    	    end loop;
			    
			    -- keep track if this ccl is staying in
			    -- alphabetical order

			    cclsorted := cclsorted and (
yy.value_stack(yy.tos-2) > lastchar);
			    lastchar := 
yy.value_stack(yy.tos);
    	    	    	end if;
			
			
yyval := 
yy.value_stack(yy.tos-3);
			

when  49 =>
--#line  568

			if ( caseins ) then
			    if ( (
yy.value_stack(yy.tos) >= CHARACTER'POS('A')) and (
yy.value_stack(yy.tos) <= CHARACTER'POS('Z')) ) then
				
yy.value_stack(yy.tos) := misc.clower( 
yy.value_stack(yy.tos) );
    	    	    	    end if;
			end if;    
			ccl.ccladd( 
yy.value_stack(yy.tos-1), CHARACTER'VAL(
yy.value_stack(yy.tos)) );
			cclsorted := cclsorted and (
yy.value_stack(yy.tos) > lastchar);
			lastchar := 
yy.value_stack(yy.tos);
			
yyval := 
yy.value_stack(yy.tos-1);
			

when  50 =>
--#line  581

			cclsorted := true;
			lastchar := 0;
			
yyval := ccl.cclinit;
			

when  51 =>
--#line  589

			if ( caseins ) then
			    if ( (
yy.value_stack(yy.tos) >= CHARACTER'POS('A')) and (
yy.value_stack(yy.tos) <= CHARACTER'POS('Z')) ) then
				
yy.value_stack(yy.tos) := misc.clower( 
yy.value_stack(yy.tos) );
			    end if;
			end if;    

			rulelen := rulelen + 1;

			
yyval := nfa.link_machines( 
yy.value_stack(yy.tos-1), nfa.mkstate( 
yy.value_stack(yy.tos) ) );
			

when  52 =>
--#line  602
 
yyval := nfa.mkstate( SYM_EPSILON ); 

                    when others => null;
                end case;


            -- Pop RHS states and goto next state
            yy.tos      := yy.tos - rule_length(yy.rule_id) + 1;
            if yy.tos > yy.stack_size then
                text_io.put_line(" Stack size exceeded on state_stack");
                raise yy_Tokens.syntax_error;
            end if;
            yy.state_stack(yy.tos) := goto_state(yy.state_stack(yy.tos-1) ,
                                 get_lhs_rule(yy.rule_id));

              yy.value_stack(yy.tos) := yyval;

            if yy.debug then
                reduce_debug(yy.rule_id,
                    goto_state(yy.state_stack(yy.tos - 1),
                               get_lhs_rule(yy.rule_id)));
            end if;

        end if;


    end loop;


end yyparse;
end parser;
