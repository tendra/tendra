--
--  The following Ada grammar for Ayacc has been adapted 
--  by David Taback and Deepak Tolani from the one distributed 
--  by Herman Fischer for the use with Yacc.
--  We have made the following modifications to the Grammar.
--
--	1)  We have removed the C style comments.
--
--	2)  We have added the production
--		numeric_literal
--			: REAL_LITERAL
--			| INTEGER_LITERAL
--			;
--
--	3)  The token names have been converted to uppercase and
--	    the name TOKEN has been appendend to them. Some of the
--          names of the other tokens have also been changed.
--
--	4)  We replaced '\'' with ''' in the productions.
--
--      5)  We added tokens ERROR1 to ERROR15 that was used to interface
--          to an existing Ada lexical analyzer. These tokens are not
--          used in the productions.
--
--	6)  We added more 'error' productions to for better error recovery.
--
--  This is the orginal header given with the Yacc version of the
--  grammar.
--

------------------------------------------------------------------------------
--									    --
--			 A LALR(1) grammar for ANSI Ada*		    --
--									    --
--			 Adapted for YACC (UNIX) Inputs 		    --
--									    --
--                                                                          --
--                             Herman Fischer                               --
--                           Litton Data Systems                            --
--                       8000 Woodley Ave., ms 44-30                        --
--                              Van Nuys, CA                                --
--                                                                          --
--                              818/902-5139                                --
--                           HFischer@eclb.arpa                             --
--                        {cepu,trwrb}!litvax!fischer                       --
--                                                                          --
--                             March 26, 1984                               --
--									    --
--                   A Contribution to the Public Domain                    --
--                                   for                                    --
--            Research, Development, and Training Purposes Only             --
--                                                                          --
--       Any Corrections or Problems are to be Reported to the Author       --
--                                                                          --
--                                                                          --
--                                                                          --
--                              adapted from                                --
--                              the grammar                                 --
--                                  by:                                     --
--									    --
--            Gerry Fisher                         Philippe Charles         --
--                                                                          --
--    Computer Sciences Corporation     &             Ada  Project          --
--         4045 Hancock Street                     New York University      --
--         San Diego, CA 92121                      251 Mercer Street       --
--                                               New York, New York 10012   --
--									    --
--									    --
--    This grammar is organized in the same order as the syntax summary     --
-- in appendix E of the ANSI Ada Reference Manual.   All reserved words     --
-- are	 written  in  upper  case  letters.    The  lexical  categories     --
-- numeric_literal, string_literal, etc, are viewed as terminals.   The     --
-- rules  for  pragmas as  stated in  chapter 2,  section 8,  have been     --
-- incorporated in the grammar.   Comments are included wherever we had     --
-- to deviate from the syntax given in appendix E. Different symbols	    --
-- used here (to comply with yacc requirements) are of note:		    --
--	{,something}	is denoted ...something..			    --
--	{something}	is denoted ..something..			    --
--	[something]	is denoted .something.				    --
-- Constructs involving                                                     --
-- meta brackets, e.g., ...identifier.. are represented by a nonterminal    --
-- formed  by  concatenating  the  construct symbols ( as ...identifier..   --
-- in the example)   for  which  the  rules are given at the end.  When     --
-- reading  this  grammar,  it	is  important to  note that all symbols     --
-- appearing  in the  rules are  separated by  one or  more  blanks.  A     --
-- string  such  as   'identifier_type_mark   is  actually  a   single      --
-- nonterminal symbol defined at the end of the rules.  The '--' symbol     --
-- is used  to indicate that the rest of  the  line is a comment,  just     --
-- as in yacc programs.                                                     --
--                                                                          --
--     This grammar is presented here in a form suitable for input to a     --
-- yacc parser generator.  It has  been  processed  by the Bell System      --
-- III lex/yacc combination, and tested against over 400 ACVC tests.        --
--									    --
-- *Ada is a registered trade mark of the  Department of  Defense  (Ada     --
-- Joint Program  Office).						    --
--
--                                                           
------- Modifications made by S A McConnell <sam@iberia.cca.cr.rockwell.COM>
-- Revisions
--
--	Changes to the grammer.
--
--	1.	Rule 'paramchoice' was added to allow the capturing of a sim_expr 
--		containing a procedure call with named parameters. 
--
--	2.	Rules 'type_of_while' and 'type_of_for' were Added.
--		They are called by 'iteration_scheme'.
--
--	3.	Rule 'xrel' has been added. It is used in the modified
--		Rule 'expr' for the case when an expression is a relation.
--
--	4.	Rule '..XOR__rel..' was removed and 
--		Rule 'rel..XOR__rel..' was modified.
--
----------------------------------------------------------------------------  


%token '&' ''' '(' ')' '*' '+' ',' '-' '.' '/' ':' ';' 
%token '<' '=' '>' '|' '!'


%token ARROW DOUBLE_DOT DOUBLE_STAR ASSIGNMENT INEQUALITY 
%token GREATER_THAN_OR_EQUAL LESS_THAN_OR_EQUAL
%token LEFT_LABEL_BRACKET RIGHT_LABEL_BRACKET 
%token BOX



%token ABORT_TOKEN ABS_TOKEN ACCEPT_TOKEN  ACCESS_TOKEN
%token ALL_TOKEN  AND_TOKEN ARRAY_TOKEN AT_TOKEN

%token BEGIN_TOKEN  BODY_TOKEN

%token CASE_TOKEN  CONSTANT_TOKEN

%token DECLARE_TOKEN DELAY_TOKEN DELTA_TOKEN DIGITS_TOKEN DO_TOKEN 

%token ELSE_TOKEN ELSIF_TOKEN END_TOKEN  ENTRY_TOKEN EXCEPTION_TOKEN 
%token EXIT_TOKEN 

%token FOR_TOKEN FUNCTION_TOKEN 

%token GENERIC_TOKEN  GOTO_TOKEN

%token IF_TOKEN IN_TOKEN  IS_TOKEN

%token LIMITED_TOKEN LOOP_TOKEN 

%token MOD_TOKEN

%token NEW_TOKEN NOT_TOKEN  NULL_TOKEN

%token OF_TOKEN OR_TOKEN OTHERS_TOKEN OUT_TOKEN  

%token PACKAGE_TOKEN PRAGMA_TOKEN  PRIVATE_TOKEN PROCEDURE_TOKEN  

%token RAISE_TOKEN  RANGE_TOKEN RECORD_TOKEN REM_TOKEN RENAMES_TOKEN 
%token RETURN_TOKEN REVERSE_TOKEN

%token SELECT_TOKEN  SEPARATE_TOKEN SUBTYPE_TOKEN

%token TASK_TOKEN TERMINATE_TOKEN THEN_TOKEN TYPE_TOKEN 

%token USE_TOKEN

%token WHEN_TOKEN WHILE_TOKEN WITH_TOKEN

%token XOR_TOKEN

%token  IDENTIFIER 
%token INTEGER_LITERAL REAL_LITERAL

%token CHARACTER_LITERAL STRING_LITERAL 

%token ERROR1 ERROR2  ERROR3  ERROR4  ERROR5  ERROR6  ERROR7  ERROR8
%token ERROR9 ERROR10 ERROR11 ERROR12 ERROR13 ERROR14 ERROR15

%start compilation

{ 
   subtype yystype is integer;
}


%%



prag	:
	PRAGMA_TOKEN IDENTIFIER .arg_ascs ';' ;

arg_asc	      :
	expr
   |	IDENTIFIER ARROW expr  ;
               

--   Added       
numeric_literal
	: REAL_LITERAL
	| INTEGER_LITERAL
    	;



basic_d  :
	object_d
   |	ty_d	       |  subty_d
   |	subprg_d       |  pkg_d
   |	task_d	       |  gen_d
   |	excptn_d       |  gen_inst
   |    renaming_d     |  number_d
   |    error ';' ;



object_d  :
      idents ':'           subty_ind ._ASN_expr. ';'
 |    idents ':'  CONSTANT_TOKEN subty_ind ._ASN_expr. ';'
 |    idents ':'           c_arr_def ._ASN_expr. ';'
 |    idents ':'  CONSTANT_TOKEN c_arr_def ._ASN_expr. ';' ;


number_d  :
	idents ':' CONSTANT_TOKEN ASSIGNMENT expr ';' ;


idents	 :  IDENTIFIER ...ident..	;



ty_d  :
	full_ty_d
   |	incomplete_ty_d
   |	priv_ty_d  ;

full_ty_d  :
        TYPE_TOKEN IDENTIFIER            IS_TOKEN ty_def ';'
   |    TYPE_TOKEN IDENTIFIER discr_part IS_TOKEN ty_def ';' ;


ty_def	 :
	enum_ty_def		|  integer_ty_def
   |	real_ty_def			|  array_ty_def
   |	rec_ty_def 		|  access_ty_def
   |	derived_ty_def ;



subty_d  :
	SUBTYPE_TOKEN IDENTIFIER IS_TOKEN subty_ind ';' ;


subty_ind  :	ty_mk .constrt. ;


ty_mk  :  expanded_n ;


constrt  :
	rng_c
   |	fltg_point_c  |  fixed_point_c
   |	aggr ;




derived_ty_def	 :  NEW_TOKEN subty_ind ;



rng_c  :  RANGE_TOKEN rng ;

rng  :
	name
|	sim_expr DOUBLE_DOT sim_expr	;



enum_ty_def	      :
	'(' enum_lit_spec
			...enum_lit_spec.. ')' ;


enum_lit_spec  :  enum_lit ;

enum_lit  : IDENTIFIER  |  CHARACTER_LITERAL ;



integer_ty_def	 :  rng_c ;



real_ty_def	      :
	fltg_point_c  |  fixed_point_c ;



fltg_point_c  :
	fltg_accuracy_def .rng_c. ;


fltg_accuracy_def	  :
	DIGITS_TOKEN sim_expr ;



fixed_point_c	:
	fixed_accuracy_def .rng_c. ;


fixed_accuracy_def	   :
	DELTA_TOKEN sim_expr ;



array_ty_def	       :
	uncnstrnd_array_def		|  c_arr_def ;


uncnstrnd_array_def		:
        ARRAY_TOKEN '(' idx_subty_def ...idx_subty_def.. ')' OF_TOKEN
					 subty_ind ;


c_arr_def	      :
	ARRAY_TOKEN idx_c OF_TOKEN subty_ind ;


idx_subty_def     :     name  RANGE_TOKEN BOX ;


idx_c  :  '(' dscr_rng ...dscr_rng.. ')' ;


dscr_rng	:   
    	rng
    	|	name rng_c	;




rec_ty_def 	:
	RECORD_TOKEN
	    cmpons
	END_TOKEN RECORD_TOKEN ;


cmpons	:
	..prag.. ..cmpon_d.. cmpon_d ..prag..
   |	..prag.. ..cmpon_d.. variant_part ..prag..
   |    ..prag.. NULL_TOKEN ';' ..prag.. ;


cmpon_d  :
     idents ':' cmpon_subty_def ._ASN_expr. ';'  ;


cmpon_subty_def	      :  subty_ind ;




discr_part  :
        '(' discr_spec ...discr_spec.. ')' ;


discr_spec  :
	idents ':' ty_mk ._ASN_expr. ;




variant_part  :
	CASE_TOKEN sim_n IS_TOKEN
	      ..prag.. variant ..variant..
        END_TOKEN CASE_TOKEN ';' ;


variant  :
	WHEN_TOKEN choice ..or_choice.. ARROW
	    cmpons ;

-- paramchoice was added to allow the capturing of a sim_expr containing
--   a procedure call with named parameters. 
paramchoice  : sim_expr
   	| name rng_c
	| sim_expr DOUBLE_DOT sim_expr
	| OTHERS_TOKEN
	| error
    	;

--choice is used by the when branch of a case statement sim_expr which was 
-- causing problems for the named parameter of a procedure call 

choice  : sim_expr
   	| name rng_c
	| sim_expr DOUBLE_DOT sim_expr
	| OTHERS_TOKEN
	| error
    	;




access_ty_def 	:  ACCESS_TOKEN subty_ind ;



incomplete_ty_d  :
        TYPE_TOKEN IDENTIFIER ';'
   |    TYPE_TOKEN IDENTIFIER discr_part ';'  ;


decl_part	  :
	..basic_decl_item..
   |    ..basic_decl_item.. body ..later_decl_item.. ;

basic_decl_item 	:
	basic_d
   |	rep_cl  |  use_cl	;


later_decl_item 	:  body
   |	subprg_d	|  pkg_d
   |	task_d	|  gen_d
   |	use_cl		|  gen_inst   ;

body  :  proper_body  |  body_stub  ;

proper_body  :
	 subprg_body  |  pkg_body  |  task_body ;




name  :  sim_n
   |    CHARACTER_LITERAL  |  op_symbol
   |	idxed_cmpon
   |	selected_cmpon |  attribute ;


sim_n  :	IDENTIFIER   ;


prefix	:  name  ;




idxed_cmpon  :
    	prefix aggr  ;






selected_cmpon  :  prefix '.' selector  ;

selector  :  sim_n
   |    CHARACTER_LITERAL  |  op_symbol  |  ALL_TOKEN  ;




attribute  :  prefix ''' attribute_designator ;


attribute_designator :
	sim_n 
   |	DIGITS_TOKEN
   |	DELTA_TOKEN
   |	RANGE_TOKEN	  ;





aggr  :
    	'(' cmpon_asc  ...cmpon_asc.. ')' ;


cmpon_asc        :
    	expr
   |	paramchoice ..or_paramchoice.. ARROW expr
   |	sim_expr DOUBLE_DOT sim_expr
   |	name rng_c ;




expr  :
	rel..AND__rel..  |  rel..AND__THEN__rel..
   |	rel..OR__rel.. |  rel..OR__ELSE__rel..
   |	rel..XOR__rel..  
   |    xrel  ;

xrel  : sim_expr .relal_op__sim_expr.
   |	sim_expr.NOT.IN__rng_or_sim_expr.NOT.IN__ty_mk 
   ;


rel  :
    	sim_expr .relal_op__sim_expr.
   |	sim_expr.NOT.IN__rng_or_sim_expr.NOT.IN__ty_mk ;


sim_expr  :
	.unary_add_op.term..binary_add_op__term.. ;


term  :  factor..mult_op__factor..  ;

factor  :  pri ._EXP___pri.  |	ABS_TOKEN pri  |     NOT_TOKEN '(' expr ')'
        |	NOT_TOKEN qualified_expr   
        |	NOT_TOKEN name             
        ;


pri  :
	numeric_literal   |  NULL_TOKEN
   |	allocator  |  qualified_expr 
   |     name 
   |	aggr ;

   
relal_op  :  '='  
	  |  INEQUALITY  
	  |  '<'  
	  |  LESS_THAN_OR_EQUAL  
	  |  '>'  
	  |  GREATER_THAN_OR_EQUAL  ;


binary_add_op  :  '+'  |  '-'  |  '&'  ;

	       	       
unary_add_op  :  '+'  |  '-' ;


mult_op  :  '*'  |  '/'  |  MOD_TOKEN  |  REM_TOKEN  ;



qualified_expr	:
	ty_mkaggr_or_ty_mkPexprP_ ;




allocator  :
	NEW_TOKEN ty_mk
   |	NEW_TOKEN ty_mk aggr
   |    NEW_TOKEN ty_mk ''' aggr  ;




seq_of_stmts	: ..prag.. stmt ..stmt..  { null; } -- Because of bug
    	    	;

	
stmt  :
	..label.. sim_stmt  |  ..label.. compound_stmt
   |    error    ';'  ;

sim_stmt  :	null_stmt
   |	assignment_stmt   |  exit_stmt
   |	return_stmt	  |  goto_stmt
   |	delay_stmt	  |  abort_stmt
   |	raise_stmt	  |  code_stmt
   |    name ';' ;



compound_stmt  :
	if_stmt   |  case_stmt
   |	loop_stmt	  |  block_stmt
   |	accept_stmt  |	select_stmt  ;


label  :  LEFT_LABEL_BRACKET sim_n RIGHT_LABEL_BRACKET  ;


null_stmt  :  NULL_TOKEN ';'  ;



assignment_stmt  :  name ASSIGNMENT expr ';' ;



if_stmt  :
	IF_TOKEN cond THEN_TOKEN 
	    seq_of_stmts
	..ELSIF__cond__THEN__seq_of_stmts..
	.ELSE__seq_of_stmts.
        END_TOKEN IF_TOKEN ';' ;


cond  :  expr ;



case_stmt	:
	CASE_TOKEN expr IS_TOKEN
    	    case_stmt_alt..case_stmt_alt.. 
        END_TOKEN CASE_TOKEN ';' ;


case_stmt_alt  :
	WHEN_TOKEN choice ..or_choice.. ARROW 
    	    seq_of_stmts ;



loop_stmt	:
	.sim_nC.
	    .iteration_scheme. LOOP_TOKEN
		seq_of_stmts
            END_TOKEN LOOP_TOKEN .sim_n. ';' ;

type_of_while
          : cond 
          | error
          ;

type_of_for
          : loop_prm_spec | error
          ;

iteration_scheme
	: WHILE_TOKEN type_of_while
	| FOR_TOKEN type_of_for
        ;
--
--iteration_scheme
--	: WHILE_TOKEN 
--          cond 
--	| WHILE_TOKEN error
--	| FOR_TOKEN 
--          loop_prm_spec
--	| FOR_TOKEN error
--	;

loop_prm_spec  :
	IDENTIFIER IN_TOKEN .REVERSE. dscr_rng ;



block_stmt  :
	.sim_nC.
	    .DECLARE__decl_part.
	    BEGIN_TOKEN
		seq_of_stmts
	    .EXCEPTION__excptn_handler..excptn_handler...
            END_TOKEN .sim_n. ';' ;



exit_stmt	:
        EXIT_TOKEN .expanded_n. .WHEN__cond. ';' ;
	
	
	
return_stmt  :  RETURN_TOKEN .expr. ';' ;



goto_stmt  :  GOTO_TOKEN expanded_n ';' ;




subprg_d  :  subprg_spec ';'  ;


subprg_spec  :
	PROCEDURE_TOKEN  IDENTIFIER .fml_part.
   |	FUNCTION_TOKEN  designator .fml_part. RETURN_TOKEN ty_mk  ;


designator  :  IDENTIFIER  | op_symbol  ;


op_symbol      :  STRING_LITERAL  ;


fml_part  :
        '(' prm_spec .._.prm_spec.. ')' ;


prm_spec  :
	idents ':' mode ty_mk ._ASN_expr.  ;


mode  :  .IN.  |  IN_TOKEN OUT_TOKEN  |  OUT_TOKEN   ;




subprg_body  :
	subprg_spec IS_TOKEN
	    .decl_part.
	BEGIN_TOKEN
            seq_of_stmts
	.EXCEPTION__excptn_handler..excptn_handler...
        END_TOKEN .designator. ';' ;



pkg_d  :  pkg_spec ';'  ;

pkg_spec  :
	PACKAGE_TOKEN IDENTIFIER IS_TOKEN
	    ..basic_decl_item..
	.PRIVATE..basic_decl_item...
	END_TOKEN .sim_n.   ;


pkg_body  :
	PACKAGE_TOKEN BODY_TOKEN sim_n IS_TOKEN
	    .decl_part.
	    .BEGIN__seq_of_stmts.EXCEPTION__excptn_handler..excptn_handler...
	END_TOKEN .sim_n. ';'   ;




priv_ty_d  :
	TYPE_TOKEN IDENTIFIER            IS_TOKEN .LIMITED. PRIVATE_TOKEN ';'
      | TYPE_TOKEN IDENTIFIER discr_part IS_TOKEN .LIMITED. PRIVATE_TOKEN ';' ;





use_cl  :  USE_TOKEN expanded_n ...expanded_n.. ';'  ;




renaming_d  :
        idents ':' ty_mk      RENAMES_TOKEN name ';'
   |    idents ':' EXCEPTION_TOKEN      RENAMES_TOKEN expanded_n ';'
   |    PACKAGE_TOKEN IDENTIFIER        RENAMES_TOKEN expanded_n ';'
   |    subprg_spec  RENAMES_TOKEN name ';'   ;




task_d  :  task_spec ';'  ;

task_spec  :
	TASK_TOKEN .TYPE. IDENTIFIER
	    .IS..ent_d_..rep_cl_END.sim_n.
	    ;

task_body  :
        TASK_TOKEN BODY_TOKEN sim_n IS_TOKEN   
	    .decl_part.
	BEGIN_TOKEN
	    seq_of_stmts
	.EXCEPTION__excptn_handler..excptn_handler...
        END_TOKEN .sim_n. ';' ;



ent_d  :
	ENTRY_TOKEN IDENTIFIER .fml_part. ';'
   |    ENTRY_TOKEN IDENTIFIER '(' dscr_rng ')' .fml_part. ';'  ;


ent_call_stmt  :
        ..prag.. name ';' ;


accept_stmt  :
	ACCEPT_TOKEN sim_n .Pent_idx_P..fml_part.
            .DO__seq_of_stmts__END.sim_n.. ';' ;


ent_idx  :	expr   ;



delay_stmt  :  DELAY_TOKEN sim_expr ';' ;



select_stmt  :	selec_wait
   |	condal_ent_call	|  timed_ent_call  ;



selec_wait	:
	SELECT_TOKEN
	    select_alt
	    ..OR__select_alt..
	    .ELSE__seq_of_stmts.
        END_TOKEN SELECT_TOKEN ';' ;


select_alt  :
	.WHEN__condARROW.selec_wait_alt  ;


selec_wait_alt  :  accept_alt
   |	delay_alt  |  terminate_alt  ;


accept_alt  :
	accept_stmt.seq_of_stmts.  ;


delay_alt  :
	delay_stmt.seq_of_stmts.  ;


terminate_alt  :  TERM_stmt   ;



condal_ent_call	:
	SELECT_TOKEN
	    ent_call_stmt
	    .seq_of_stmts.
	ELSE_TOKEN
	    seq_of_stmts
        END_TOKEN SELECT_TOKEN ';' ;




timed_ent_call  :
	SELECT_TOKEN
	    ent_call_stmt
	    .seq_of_stmts.
	OR_TOKEN
	    delay_alt
        END_TOKEN SELECT_TOKEN ';' ;



abort_stmt  :  ABORT_TOKEN name ...name.. ';'  ;



compilation  :	..compilation_unit..   ;


compilation_unit  :
	context_cl library_unit
   |    context_cl secondary_unit ;

library_unit  :
	subprg_d	|  pkg_d
   |	gen_d	|  gen_inst
   |	subprg_body     ;


secondary_unit	:
	library_unit_body  |  subunit	;


library_unit_body  :
	pkg_body_or_subprg_body  ;




context_cl      : ..with_cl..use_cl.... ;


with_cl  :  WITH_TOKEN sim_n ...sim_n.. ';'  ;



body_stub  :
        subprg_spec IS_TOKEN SEPARATE_TOKEN ';'
   |    PACKAGE_TOKEN BODY_TOKEN sim_n IS_TOKEN SEPARATE_TOKEN ';'
   |    TASK_TOKEN BODY_TOKEN sim_n    IS_TOKEN SEPARATE_TOKEN ';'   ;


subunit  :  SEPARATE_TOKEN '(' expanded_n ')'  proper_body;




excptn_d  :  idents ':' EXCEPTION_TOKEN ';' ;



excptn_handler	:
	WHEN_TOKEN excptn_choice ..or_excptn_choice.. ARROW
	    seq_of_stmts  ;


excptn_choice  :  expanded_n  |	OTHERS_TOKEN    ;



raise_stmt  :  RAISE_TOKEN .expanded_n. ';' ;




gen_d  :  gen_spec ';'  ;

gen_spec  :
	gen_fml_part subprg_spec
   |	gen_fml_part pkg_spec  ;


gen_fml_part  :	GENERIC_TOKEN ..gen_prm_d..  ;


gen_prm_d  :
	idents ':' .IN.OUT.. ty_mk ._ASN_expr. ';'
   |    TYPE_TOKEN IDENTIFIER IS_TOKEN gen_ty_def ';'
   |	priv_ty_d
   |    WITH_TOKEN subprg_spec .IS_BOX_. ';' ;


gen_ty_def	 :
        '(' BOX ')'  |  RANGE_TOKEN BOX  |  DIGITS_TOKEN BOX  |  DELTA_TOKEN BOX
   |	array_ty_def	       |  access_ty_def	   ;



gen_inst  :
	PACKAGE_TOKEN IDENTIFIER IS_TOKEN
            NEW_TOKEN expanded_n .gen_act_part. ';'
   |	PROCEDURE__ident__IS_
            NEW_TOKEN expanded_n .gen_act_part. ';'
   |	FUNCTION_TOKEN  designator IS_TOKEN
	    NEW_TOKEN expanded_n .gen_act_part. ';'  ;


gen_act_part  :
        '(' gen_asc ...gen_asc.. ')'              ;


gen_asc	     :
	.gen_fml_prmARROW.gen_act_prm ;


gen_fml_prm  :
	sim_n  |  op_symbol  ;

gen_act_prm  :
  expr_or_name_or_subprg_n_or_ent_n_or_ty_mk
    	;
	 


rep_cl  :
	ty_rep_cl  |  address_cl  ;

ty_rep_cl  :  length_cl
   |	enum_rep_cl
   |	rec_rep_cl	    ;



length_cl  :  FOR_TOKEN attribute USE_TOKEN sim_expr ';' ;




enum_rep_cl  :
        FOR__ty_sim_n__USE_ aggr ';' ;




rec_rep_cl	:
	FOR__ty_sim_n__USE_
	    RECORD_TOKEN .algt_cl.
		..cmpon_cl..
            END_TOKEN RECORD_TOKEN ';'   ;


algt_cl  :     AT_TOKEN MOD_TOKEN sim_expr ';' ;


cmpon_cl  :
        name AT_TOKEN sim_expr RANGE_TOKEN rng ';' ;




address_cl  :  FOR_TOKEN sim_n USE_TOKEN AT_TOKEN sim_expr ';'  ;



code_stmt  :  ty_mk_rec_aggr ';' ;





..prag..  :
   |	..prag.. prag  ;

.arg_ascs :
   |    '(' arg_ascs ')' ;

arg_ascs :
	arg_asc
   |    arg_ascs ',' arg_asc ;




._ASN_expr.	:
   |	ASSIGNMENT expr  ;

...ident..  :
   |    ...ident.. ',' IDENTIFIER   ;

.constrt.  :
   |	constrt   ;


expanded_n  :
    	IDENTIFIER 
   |    expanded_n '.' IDENTIFIER   ;


...enum_lit_spec.. :
   |    ...enum_lit_spec.. ','
		enum_lit_spec ;

.rng_c.  :
   |	rng_c	;

...idx_subty_def..	       :
   |    ...idx_subty_def.. ',' idx_subty_def  ;


...dscr_rng.. :
   |    ...dscr_rng.. ',' dscr_rng  ;




..cmpon_d.. :
   |    ..cmpon_d.. cmpon_d ..prag..    ;

...discr_spec..	:
   |    ...discr_spec.. ';' discr_spec  ;



..variant..  :
   |	..variant.. variant  ;

..or_choice.. :
   |    ..or_choice.. '|' choice    
   |    ..or_choice.. '!' choice    ;


--
-- paramchoice was added to allow the capturing of a sim_expr containing
-- named parameters.
--
..or_paramchoice.. :
   |    ..or_paramchoice.. '|' paramchoice    
   |    ..or_paramchoice.. '!' paramchoice    ;

..basic_decl_item..	    :
	..prag..
   |	..basic_decl_item.. basic_decl_item ..prag.. ;

..later_decl_item..      :
	..prag..
   |   ..later_decl_item.. later_decl_item ..prag..  ;








...cmpon_asc..  :
   |    ...cmpon_asc.. ',' cmpon_asc ;



rel..AND__rel..  :
	rel AND_TOKEN rel
   |	rel..AND__rel.. AND_TOKEN rel	 ;

rel..OR__rel.. :
	rel OR_TOKEN rel
   |	rel..OR__rel.. OR_TOKEN rel ;

rel..XOR__rel.. : 
	rel XOR_TOKEN rel
   |	rel..XOR__rel.. XOR_TOKEN rel  ;

rel..AND__THEN__rel..  :
    rel AND_TOKEN THEN_TOKEN rel
   |	rel..AND__THEN__rel.. AND_TOKEN THEN_TOKEN rel  ;

rel..OR__ELSE__rel..	:
	rel OR_TOKEN ELSE_TOKEN rel
   |	rel..OR__ELSE__rel.. OR_TOKEN ELSE_TOKEN rel  ;

.relal_op__sim_expr.  :
   |	relal_op sim_expr  ;

sim_expr.NOT.IN__rng_or_sim_expr.NOT.IN__ty_mk	:
	sim_expr .NOT. IN_TOKEN rng ;


.NOT.  :
   |	NOT_TOKEN    ;

.unary_add_op.term..binary_add_op__term..  :
	term
   |	unary_add_op term
   |	.unary_add_op.term..binary_add_op__term..
    	binary_add_op term  ;

factor..mult_op__factor..	:
	factor
   |	factor..mult_op__factor.. mult_op factor ;

._EXP___pri.  :
   |	DOUBLE_STAR pri ;



ty_mkaggr_or_ty_mkPexprP_  :
        prefix ''' aggr ;









..stmt..  :
	..prag..
   |	..stmt.. stmt ..prag.. ;


..label..   :
   |	..label.. label  ;



..ELSIF__cond__THEN__seq_of_stmts..  :
   |	..ELSIF__cond__THEN__seq_of_stmts..
		ELSIF_TOKEN cond THEN_TOKEN
		    seq_of_stmts   ;

.ELSE__seq_of_stmts.	:
   |	ELSE_TOKEN
	    seq_of_stmts    ;

case_stmt_alt..case_stmt_alt.. :
	    ..prag..
            case_stmt_alt  
	    ..case_stmt_alt..  ;

..case_stmt_alt..	:
   |	..case_stmt_alt.. case_stmt_alt ;

.sim_nC.	:
   |    sim_n ':' ;

.sim_n. :
   |	sim_n  ;

.iteration_scheme.  :
   |	iteration_scheme  ;

.REVERSE. :
   |	REVERSE_TOKEN   ;

.DECLARE__decl_part.	     :
   |	DECLARE_TOKEN
	    decl_part		;

.EXCEPTION__excptn_handler..excptn_handler... :
   |	EXCEPTION_TOKEN
	    ..prag.. excptn_handlers	 ;

excptn_handlers	:
	excptn_handler
   |	excptn_handlers excptn_handler   ;

.expanded_n.  :
   |	expanded_n  ;

.WHEN__cond.  :
   |	WHEN_TOKEN cond ;

.expr.	:
   |	expr   ;



.fml_part.  :
   |	fml_part  ;

.._.prm_spec..  :
   |    .._.prm_spec.. ';' prm_spec  ;

.IN.  :
   |	IN_TOKEN	  ;

.decl_part.	    :  decl_part	 ;


.designator.  :
   |    designator    ;



.PRIVATE..basic_decl_item... :
   |	PRIVATE_TOKEN
	    ..basic_decl_item.. ;

.BEGIN__seq_of_stmts.EXCEPTION__excptn_handler..excptn_handler...
				:
   |	BEGIN_TOKEN
	    seq_of_stmts
	.EXCEPTION__excptn_handler..excptn_handler...  ;

.LIMITED.  :
   |	LIMITED_TOKEN    ;

...expanded_n.. :
   |    ...expanded_n.. ',' expanded_n  ;



.TYPE.	:
   |	TYPE_TOKEN   ;

.IS..ent_d_..rep_cl_END.sim_n.  :
   |	IS_TOKEN
	    ..ent_d..
	    ..rep_cl..
	END_TOKEN .sim_n.	      ;


..ent_d..  :
	..prag..
   |	..ent_d.. ent_d ..prag..	;

..rep_cl..  :
   |	..rep_cl.. rep_cl ..prag..	;


.Pent_idx_P..fml_part.  :
	.fml_part.
   |    '(' ent_idx ')' .fml_part.  ;

.DO__seq_of_stmts__END.sim_n..  :
   |	DO_TOKEN
	  seq_of_stmts
	END_TOKEN .sim_n.  ;

..OR__select_alt..  :
   |	..OR__select_alt.. OR_TOKEN select_alt	;

.WHEN__condARROW.selec_wait_alt  :
	selec_wait_alt
   |	WHEN_TOKEN cond ARROW selec_wait_alt  ;

accept_stmt.seq_of_stmts.  :
	..prag.. accept_stmt .seq_of_stmts.  ;

delay_stmt.seq_of_stmts.  :
	..prag.. delay_stmt .seq_of_stmts. ;

TERM_stmt   :  ..prag.. TERMINATE_TOKEN ';' ..prag..  ;

.seq_of_stmts.	:
	..prag..
   |	seq_of_stmts	;

...name..	:
   |    ...name.. ',' name  ;




..compilation_unit..  :
	..prag..
   |	..compilation_unit.. compilation_unit ..prag.. ;

pkg_body_or_subprg_body   :  pkg_body  ;


..with_cl..use_cl.... :
   |	..with_cl..use_cl.... with_cl use_cls ;


use_cls  :
	..prag..
   |	use_cls use_cl ..prag..  ;

...sim_n..  :
   |    ...sim_n.. ',' sim_n  ;




..or_excptn_choice.. :
   |    ..or_excptn_choice.. '|' excptn_choice 
   |    ..or_excptn_choice.. '!' excptn_choice ;




..gen_prm_d..  :
   |	..gen_prm_d.. gen_prm_d ;

.IN.OUT..  :
	.IN.
   |	IN_TOKEN OUT_TOKEN	 ;

.IS_BOX_.	:
   |	IS_TOKEN name
   |	IS_TOKEN BOX ;

PROCEDURE__ident__IS_	   :  subprg_spec IS_TOKEN ;


.gen_act_part.  :
   |	gen_act_part ;

...gen_asc.. :
   |    ...gen_asc.. ',' gen_asc ;

.gen_fml_prmARROW.gen_act_prm  :
	gen_act_prm
   |	gen_fml_prm ARROW gen_act_prm  ;

expr_or_name_or_subprg_n_or_ent_n_or_ty_mk
				:  expr ; 




FOR__ty_sim_n__USE_  :
	FOR_TOKEN sim_n USE_TOKEN	;


.algt_cl.  :
	..prag..
   |    ..prag.. algt_cl ..prag..   ;

..cmpon_cl..  :
   |    ..cmpon_cl.. cmpon_cl ..prag..  ;

ty_mk_rec_aggr  :  qualified_expr      ;
 

%%

##
    procedure YYParse;
    echo : boolean := false;
    number_of_errors : natural := 0;
##
with  ada_lex.io, ada_parse.error_report,
      ada_lex, text_io;
use   ada_lex.IO, ada_lex, text_io;
##

    procedure yyerror(s: in string := "syntax error") is
    begin
	number_of_errors := number_of_errors + 1;
	put("<<< *** ");
	put_line(s);
    end yyerror;

##%procedure_parse
