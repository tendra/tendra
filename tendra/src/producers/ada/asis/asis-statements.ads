-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  18 package Asis.Statements
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package Asis.Statements is
   pragma Preelaborate;

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Statements encapsulates a set of queries that operate on A_Statement,
--  A_Path, and An_Exception_Handler elements.
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  18.1 function Label_Names
-------------------------------------------------------------------------------

   function Label_Names (Statement : in Asis.Statement)
                         return Asis.Defining_Name_List;

-------------------------------------------------------------------------------
--  Statement   - Specifies the statement to query
--
--  Returns label_statement_identifier elements (A_Defining_Name elements)
--  that define the labels attached to the statement, in their order of
--  appearance.
--
--  Returns a Nil_Element_List if there are no labels attached to the
--  statement.
--
--  The Enclosing_Element of the A_Defining_Name elements is the statement.
--
--  Appropriate Element_Kinds:
--      A_Statement
--
--  Returns Defining_Name_Kinds:
--      A_Defining_Identifier
--
-------------------------------------------------------------------------------
--  18.2 function Assignment_Variable_Name
-------------------------------------------------------------------------------

   function Assignment_Variable_Name (Statement : in Asis.Statement)
                                      return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement   - Specifies the assignment statement to query
--
--  Returns the expression that names the left hand side of the assignment.
--
--  Appropriate Element_Kinds:
--      A_Statement
--
--  Appropriate Statement_Kinds:
--      An_Assignment_Statement
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  18.3 function Assignment_Expression
-------------------------------------------------------------------------------

   function Assignment_Expression (Statement : in Asis.Statement)
                                   return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement   - Specifies the assignment statement to query
--
--  Returns the expression from the right hand side of the assignment.
--
--  Appropriate Element_Kinds:
--      A_Statement
--

--  Appropriate Statement_Kinds:
--      An_Assignment_Statement
--
--  Returns Element_Kinds:
--      An_Expression

-------------------------------------------------------------------------------
--  18.4 function Statement_Paths
-------------------------------------------------------------------------------

   function Statement_Paths (Statement : in Asis.Statement;
                             Include_Pragmas : in Boolean := False)
                             return Asis.Path_List;

-------------------------------------------------------------------------------
--  Statement       - Specifies the statement to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns a list of the execution paths of the statement, in
--  their order of appearance.
--
--  The only pragmas returned are those preceding the first alternative in
--  a case statement.
--
--  Appropriate Statement_Kinds:
--      An_If_Statement
--      A_Case_Statement
--      A_Selective_Accept_Statement
--      A_Timed_Entry_Call_Statement
--      A_Conditional_Entry_Call_Statement
--      An_Asynchronous_Select_Statement
--
--  Returns Element_Kinds:
--      A_Path
--      A_Pragma
--
-------------------------------------------------------------------------------
--  18.5 function Condition_Expression
-------------------------------------------------------------------------------

   function Condition_Expression (Path : in Asis.Path)
                                  return Asis.Expression;

-------------------------------------------------------------------------------
--  Path - Specifies the execution path to query
--
--  Returns the condition expression for an IF path or an ELSIF path.
--
--  Appropriate Path_Kinds:
--      An_If_Path
--      An_Elsif_Path
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  18.6 function Sequence_Of_Statements
-------------------------------------------------------------------------------

   function Sequence_Of_Statements (Path            : in Asis.Path;
                                    Include_Pragmas : in Boolean := False)
                                    return Asis.Statement_List;

-------------------------------------------------------------------------------
--  Path            - Specifies the execution path to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns a list of the statements and pragmas from an execution path,
--  in their order of appearance.
--
--  Appropriate Element_Kinds:
--      A_Path
--
--  Returns Element_Kinds:
--      A_Statement
--      A_Pragma
--
-------------------------------------------------------------------------------
--  18.7 function Case_Expression
-------------------------------------------------------------------------------

   function Case_Expression (Statement : in Asis.Statement)
                              return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement   - Specifies the case statement to query
--
--  Returns the expression of the case statement that determines which
--  execution path is taken.
--
--  Appropriate Element_Kinds:
--      A_Statement
--
--  Appropriate Statement_Kinds:
--      A_Case_Statement
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  18.8 function Case_Statement_Alternative_Choices
-------------------------------------------------------------------------------

   function Case_Statement_Alternative_Choices (Path : in Asis.Path)
                                                 return Asis.Element_List;

-------------------------------------------------------------------------------
--  Path - Specifies the case_statement_alternative execution path to query
--
--  Returns a list of the 'when <choice> | <choice>' elements, in their
--  order of appearance.
--
--  Appropriate Path_Kinds:
--      A_Case_Path
--
--  Returns Element_Kinds:
--      An_Expression
--      A_Definition
--
--  Returns Definition_Kinds:
--      A_Discrete_Range
--      An_Others_Choice
--
-------------------------------------------------------------------------------
--  18.9 function Statement_Identifier
-------------------------------------------------------------------------------

   function Statement_Identifier (Statement : in Asis.Statement)
                                   return Asis.Defining_Name;

-------------------------------------------------------------------------------
--  Statement   - Specifies the statement to query
--
--  Returns the identifier for the loop_statement or block_statement.
--
--  Returns a Nil_Element if the loop has no identifier.
--
--  The Enclosing_Element of the name is the statement.
--
--  Appropriate Statement_Kinds:
--      A_Loop_Statement
--      A_While_Loop_Statement
--      A_For_Loop_Statement
--      A_Block_Statement
--
--  Returns Defining_Name_Kinds:
--      Not_A_Defining_Name
--      A_Defining_Identifier
--
-------------------------------------------------------------------------------
--  18.10 function Is_Name_Repeated
-------------------------------------------------------------------------------

   function Is_Name_Repeated (Statement : in Asis.Statement) return Boolean;

-------------------------------------------------------------------------------
--  Statement   - Specifies the statement to query
--
--  Returns True if the name of the accept, loop, or block is repeated after
--  the end of the statement.  Always returns True for loop or block
--  statements since the name is required.
--
--  Returns False for any unexpected Element.
--
--  Expected Statement_Kinds:
--      A_Block_Statement
--      A_Loop_Statement
--      An_Accept_Statement
--
-------------------------------------------------------------------------------
--  18.11 function While_Condition
-------------------------------------------------------------------------------

   function While_Condition (Statement : in Asis.Statement)
                              return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement   - Specifies the loop statement to query
--
--  Returns the condition expression associated with the while loop.
--
--  Appropriate Element_Kinds:
--      A_Statement
--
--  Appropriate Statement_Kinds:
--      A_While_Loop_Statement
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  18.12 function For_Loop_Parameter_Specification
-------------------------------------------------------------------------------

   function For_Loop_Parameter_Specification (Statement : in Asis.Statement)
                                               return Asis.Declaration;

-------------------------------------------------------------------------------
--  Statement   - Specifies the loop statement to query
--
--  Returns the declaration of the A_Loop_Parameter_Specification.
--
--  Appropriate Statement_Kinds:
--      A_For_Loop_Statement
--
--  Returns Declaration_Kinds:
--      A_Loop_Parameter_Specification
--

-------------------------------------------------------------------------------
--  18.13 function Loop_Statements
-------------------------------------------------------------------------------

   function Loop_Statements (Statement       : in Asis.Statement;
                             Include_Pragmas : in Boolean := False)
                             return Asis.Statement_List;

-------------------------------------------------------------------------------
--  Statement       - Specifies the loop statement to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns the sequence_of_statements and any pragmas from the loop_statement,
--  in their order of appearance.
--
--  Appropriate Statement_Kinds:
--      A_Loop_Statement
--      A_While_Loop_Statement
--      A_For_Loop_Statement
--
--  Returns Element_Kinds:
--      A_Pragma
--      A_Statement
--
-------------------------------------------------------------------------------
--  18.14 function Is_Declare_Block
-------------------------------------------------------------------------------

   function Is_Declare_Block (Statement : in Asis.Statement) return Boolean;

-------------------------------------------------------------------------------
--  Statement   - Specifies the statement to query
--
--  Returns True if the statement is a block_statement and it was created with
--  the use of the "declare" reserved word.  The presence or absence of any
--  declarative_item elements is not relevant.
--
--  Returns False if the "declare" reserved word does not appear in the
--  block_statement, or for any unexpected Element.
--
--  Expected Statement_Kinds::
--      A_Block_Statement
--
-------------------------------------------------------------------------------
--  18.15 function Block_Declarative_Items
-------------------------------------------------------------------------------

   function Block_Declarative_Items
            (Statement       : in Asis.Statement;
             Include_Pragmas : in Boolean := False)
             return Asis.Declarative_Item_List;

-------------------------------------------------------------------------------
--  Statement       - Specifies the block statement to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns a list of the declarations, representation_clause elements,
--  pragmas, and use_clause elements in the declarative_part of the
--  block_statement, in their order of appearance.
--
--  Returns a Nil_Element_List if there are no declarative items.
--
--  Appropriate Statement_Kinds:
--      A_Block_Statement
--
--  Returns Element_Kinds:
--      A_Declaration
--      A_Pragma
--      A_Clause
--

-------------------------------------------------------------------------------
--  18.16 function Block_Statements
-------------------------------------------------------------------------------

   function Block_Statements (Statement       : in Asis.Statement;
                              Include_Pragmas : in Boolean := False)
                              return Asis.Statement_List;

-------------------------------------------------------------------------------
--  Statement       - Specifies the block statement to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns a list of the statements and pragmas for the block_statement, in
--  their order of appearance.
--
--  Returns a Nil_Element_List if there are no statements or pragmas.  This
--  can only occur for a block_statement obtained from the obsolescent query
--  Body_Block_Statement when its argument is a package_body
--  that has no sequence_of_statements.
--
--  Appropriate Statement_Kinds:
--      A_Block_Statement
--
--  Returns Element_Kinds:
--      A_Pragma
--      A_Statement
--
-------------------------------------------------------------------------------
--  18.17 function Block_Exception_Handlers
-------------------------------------------------------------------------------

   function Block_Exception_Handlers (Statement : in Asis.Statement;
                                      Include_Pragmas : in Boolean := False)
                                      return Asis.Exception_Handler_List;

-------------------------------------------------------------------------------
--  Statement       - Specifies the block statement to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns a list of the exception_handler elements of the block_statement,
--  in their order of appearance.
--
--  The only pragmas returned are those following the reserved word "exception"
--  and preceding the reserved word "when" of first exception handler.
--
--  Returns a Nil_Element_List if there are no exception_handler elements.
--
--  Appropriate Statement_Kinds:
--      A_Block_Statement
--
--  Returns Element_Kinds:
--      An_Exception_Handler
--      A_Pragma
--
-------------------------------------------------------------------------------
--  18.18 function Exit_Loop_Name
-------------------------------------------------------------------------------

   function Exit_Loop_Name (Statement : in Asis.Statement)
                            return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement   - Specifies the exit statement to query
--
--  Returns the name of the exited loop.
--
--  Returns a Nil_Element if no loop name is present.
--
--  Appropriate Statement_Kinds:
--      An_Exit_Statement
--

--  Returns Expression_Kinds:
--      Not_An_Expression
--      An_Identifier
--      A_Selected_Component
--
-------------------------------------------------------------------------------
--  18.19 function Exit_Condition
-------------------------------------------------------------------------------

   function Exit_Condition (Statement : in Asis.Statement)
                            return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement   - Specifies the exit statement to query
--
--  Returns the "when" condition of the exit statement.
--
--  Returns a Nil_Element if no condition is present.
--
--  Appropriate Statement_Kinds:
--      An_Exit_Statement
--
--  Returns Element_Kinds:
--      Not_An_Element
--      An_Expression
--
-------------------------------------------------------------------------------
--  18.20 function Corresponding_Loop_Exited
-------------------------------------------------------------------------------

   function Corresponding_Loop_Exited (Statement : in Asis.Statement)
                                       return Asis.Statement;

-------------------------------------------------------------------------------
--  Statement   - Specifies the exit statement to query
--
--  Returns the loop statement exited by the exit statement.
--
--  Appropriate Statement_Kinds:
--      An_Exit_Statement
--
--  Returns Element_Kinds:
--      A_Loop_Statement
--      A_While_Loop_Statement
--      A_For_Loop_Statement
--
-------------------------------------------------------------------------------
--  18.21 function Return_Expression
-------------------------------------------------------------------------------

   function Return_Expression (Statement : in Asis.Statement)
                               return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement   - Specifies the return statement to query
--
--  Returns the expression in the return statement.
--
--  Returns a Nil_Element if no expression is present.
--
--  Appropriate Statement_Kinds:
--      A_Return_Statement
--
--  Returns Element_Kinds:
--      Not_An_Element
--      An_Expression
--
-------------------------------------------------------------------------------
--  18.xx function Return_Object_Specification
-------------------------------------------------------------------------------

   function Return_Object_Specification (Statement : Asis.Statement)
                                         return Asis.Declaration;

-------------------------------------------------------------------------------
--  Statement specifies the extended return statement to query.
--
--  Returns the specification of the return object.
--
--  Appropriate Statement_Kinds:
--      An_Extended_Return_Statement
--
--  Returns Declaration_Kinds:
--      A_Return_Object_Specification
--
-------------------------------------------------------------------------------
--  18.xx function Extended_Return_Statements
-------------------------------------------------------------------------------

   function Extended_Return_Statements
     (Statement       : Asis.Statement;
      Include_Pragmas : Boolean := False)
      return Asis.Statement_List;

-------------------------------------------------------------------------------
--  Statement specifies the extended return statement to query.
--  Include_Pragmas specifies whether pragmas are to be returned.
--
--  Returns a list of the statements and pragmas from the extended return
--  statement, in their order of appearance.
--
--  Returns a Nil_Element_List if the argument extended return statement does
--  not include handled_sequence_of_statements.
--
--  Appropriate Statement_Kinds:
--      An_Extended_Return_Statement
--
--  Returns Element_Kinds:
--      A_Statement
--      A_Pragma
--
-------------------------------------------------------------------------------
--  18.xx function Extended_Return_Exception_Handlers
-------------------------------------------------------------------------------

   function Extended_Return_Exception_Handlers
     (Statement       : Asis.Statement;
      Include_Pragmas : Boolean := False)
      return Asis.Exception_Handler_List;

-------------------------------------------------------------------------------
--  Statement specifies the extended return statement to query.
--  Include_Pragmas specifies whether pragmas are to be returned.
--
--  Returns a list of the exception_handler elements of the extended return
--  statement, in their order of appearance.
--
--  The only pragmas returned are those following the reserved word "exception"
--  and preceding the reserved word "when" of first exception handler.
--
--  Returns a Nil_Element_List if there are no exception_handler elements.
--
--  Appropriate Statement_Kinds:
--      An_Extended_Return_Statement
--
--  Returns Element_Kinds:
--      An_Exception_Handler
--      A_Pragma
--
-------------------------------------------------------------------------------
--  18.22 function Goto_Label
-------------------------------------------------------------------------------

   function Goto_Label (Statement : in Asis.Statement)
                        return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement   - Specifies the goto statement to query
--
--  Returns the expression reference for the label, as specified by the goto
--  statement.
--
--  Appropriate Statement_Kinds:
--      A_Goto_Statement
--
--  Returns Expression_Kinds:
--      An_Identifier
--
-------------------------------------------------------------------------------
--  18.23 function Corresponding_Destination_Statement
-------------------------------------------------------------------------------

   function Corresponding_Destination_Statement
       (Statement : in Asis.Statement)
        return Asis.Statement;

-------------------------------------------------------------------------------
--  Statement  - Specifies the goto statement to query
--
--  Returns the target statement specified by the goto statement.
--
--  Appropriate Statement_Kinds:
--      A_Goto_Statement
--
--  Returns Element_Kinds:
--      A_Statement
--
--  |AN Application Note:
--  |AN
--  |AN The Reference Manual allows a pragma between a statement and a label
--  |AN attached to it. If so, when the label is passed as an actual parameter
--  |AN to this query, the query returns the statement, but not the label. The
--  |AN only way for an application to know that there are any pragmas between
--  |AN a statement and its label is to get the spans of these program
--  |AN elements and analyze the corresponding positions in the source text.
--
-------------------------------------------------------------------------------
--  18.24 function Called_Name
-------------------------------------------------------------------------------

   function Called_Name (Statement : in Asis.Statement)
                         return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement  - Specifies the procedure call or entry call statement to query
--
--  Returns the name of the called procedure or entry.  The name of an entry
--  family takes the form of An_Indexed_Component.
--
--  Appropriate Statement_Kinds:
--      An_Entry_Call_Statement
--      A_Procedure_Call_Statement
--
--  Returns Element_Kinds:
--      An_Expression
--

-------------------------------------------------------------------------------
--  18.25 function Corresponding_Called_Entity
-------------------------------------------------------------------------------

   function Corresponding_Called_Entity (Statement : in Asis.Statement)
                                         return Asis.Declaration;

-------------------------------------------------------------------------------
--  Statement   - Specifies the procedure_call_statement or
--               entry_call_statement to query
--
--  Returns the declaration of the procedure or entry denoted by the call.
--
--  Returns a Nil_Element if the:
--
--  - prefix of the call denotes an access to a procedure implicit
--   or explicit dereference,
--
--  - argument is a dispatching call,
--
--  - argument is a call to a dispatching operation of a tagged type which
--   is not statically determined.
--
--  If procedure_prefix denotes an attribute_reference, and if the
--  corresponding attribute is (re)defined by an attribute definition clause,
--  an implementation is encouraged, but not required, to return the
--  definition of the corresponding subprogram whose name is used after "use"
--  in this attribute definition clause. If an implementation cannot return
--  such a subprogram definition, a Nil_Element should be returned. For an
--  attribute reference which is not (re)defined by an attribute definition
--  clause, a Nil_Element should be returned.
--
--  Appropriate Statement_Kinds:
--      An_Entry_Call_Statement
--      A_Procedure_Call_Statement
--
--  Returns Declaration_Kinds:
--      Not_A_Declaration
--      A_Procedure_Declaration
--      A_Procedure_Body_Declaration
--      A_Procedure_Body_Stub
--      A_Procedure_Renaming_Declaration
--      A_Procedure_Instantiation
--      A_Formal_Procedure_Declaration
--      An_Entry_Declaration
--      A_Generic_Procedure_Declaration
--
--  |IP Implementation Permissions
--  |IP
--  |IP An implementation may choose to return any part of multi-part
--  |IP declarations and definitions. Multi-part declaration/definitions
--  |IP can occur for:
--  |IP
--  |IP    - Subprogram specification in package specification, package body,
--  |IP      and subunits (is separate);
--  |IP    - Entries in package specification, package body, and subunits
--  |IP      (is separate);
--  |IP    - Private type and full type declarations;
--  |IP    - Incomplete type and full type declarations; and
--  |IP    - Deferred constant and full constant declarations.
--  |IP
--  |IP No guarantee is made that the element will be the first part or
--  |IP that the determination will be made due to any visibility rules.
--  |IP An application should make its own analysis for each case based
--  |IP on which part is returned.
--

-------------------------------------------------------------------------------
--  18.26 function Call_Statement_Parameters
-------------------------------------------------------------------------------

   function Call_Statement_Parameters (Statement  : in Asis.Statement;
                                       Normalized : in Boolean := False)
                                       return Asis.Association_List;

-------------------------------------------------------------------------------
--  Statement   - Specifies the procedure_call_statement or
--               entry_call_statement to query
--  Normalized  - Specifies whether the normalized form is desired
--
--  Returns a list of parameter_association elements of the call.
--
--  Returns a Nil_Element_List if there are no parameter_association elements.
--
--  An unnormalized list contains only explicit associations ordered as they
--  appear in the program text.  Each unnormalized association has an optional
--  formal_parameter_selector_name and an explicit_actual_parameter component.
--
--  A normalized list contains artificial associations representing all
--  explicit and default associations.  It has a length equal to the number of
--  parameter_specification elements of the formal_part of the
--  parameter_and_result_profile.  The order of normalized associations matches
--  the order of parameter_specification elements.
--
--  Each normalized association represents a one on one mapping of a
--  parameter_specification elements to the explicit or default expression.
--  A normalized association has one A_Defining_Name component that denotes the
--  parameter_specification, and one An_Expression component that is either the
--  explicit_actual_parameter or a default_expression.
--
--  If the prefix of the call denotes an access to a procedure implicit or
--  explicit deference, normalized associations are constructed on the basis
--  of the formal_part of the parameter_profile from the corresponding
--  access_to_subprogram definition.
--
--  Returns Nil_Element for normalized associations in the case where
--  the called procedure can be determined only dynamically (dispatching
--  calls). ASIS cannot produce any meaningful result in this case.
--
--  The exception ASIS_Inappropriate_Element is raised when the procedure
--  call is an attribute reference and Is_Normalized is True.
--
--  Appropriate Statement_Kinds:
--      An_Entry_Call_Statement
--      A_Procedure_Call_Statement
--
--  Returns Element_Kinds:
--      A_Parameter_Association
--
--  |IR Implementation Requirements:
--  |IR
--  |IR Normalized associations are Is_Normalized and Is_Part_Of_Implicit.
--  |IR Normalized associations provided by default are
--  |IR Is_Defaulted_Association.
--  |IR Normalized associations are never Is_Equal to unnormalized
--  |IR associations.
--
--  |IP Implementation Permissions:
--  |IP
--  |IP An implementation may choose to always include default parameters in
--  |IP its internal representation.
--  |IP
--  |IP An implementation may also choose to normalize its representation
--  |IP to use defining_identifier elements rather than
--  |IP formal_parameter_selector_name elements.
--  |IP
--  |IP In either case, this query will return Is_Normalized associations even
--  |IP if Normalized is False, and the query
--  |IP Call_Statement_Parameters_Normalized will return True.
--

-------------------------------------------------------------------------------
--  18.27 function Accept_Entry_Index
-------------------------------------------------------------------------------

   function Accept_Entry_Index (Statement : in Asis.Statement)
                                return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement   - Specifies the accept statement to query
--
--  Returns the entry index expression in the accept statement.
--
--  Returns a Nil_Element if the statement has no explicit entry index,
--
--  Appropriate Statement_Kinds:
--      An_Accept_Statement
--
--  Returns Element_Kinds:
--      Not_An_Element
--      An_Expression
--
-------------------------------------------------------------------------------
--  18.28 function Accept_Entry_Direct_Name
-------------------------------------------------------------------------------

   function Accept_Entry_Direct_Name (Statement : in Asis.Statement)
                                      return Asis.Name;

-------------------------------------------------------------------------------
--  Statement   - Specifies the accept statement to query
--
--  Returns the direct name of the entry.  The name follows the reserved word
--  "accept".
--
--  Appropriate Statement_Kinds:
--      An_Accept_Statement
--
--  Returns Expression_Kinds:
--      An_Identifier
--
-------------------------------------------------------------------------------
--  18.29 function Accept_Parameters
-------------------------------------------------------------------------------

   function Accept_Parameters (Statement : in Asis.Statement)
                               return Asis.Parameter_Specification_List;

-------------------------------------------------------------------------------
--  Statement   - Specifies the accept statement to query
--
--  Returns a list of parameter specifications in the formal part of the
--  accept statement, in their order of appearance.
--
--  Returns a Nil_Element_List if the accept_statement has no parameters.
--
--  Results of this query may vary across ASIS implementations.  Some
--  implementations normalize all multiple name parameter specifications into
--  an equivalent sequence of corresponding single name parameter
--  specifications.  See Reference Manual 3.3.1(7).
--
--  Appropriate Statement_Kinds:
--      An_Accept_Statement
--
--  Returns Declaration_Kinds:
--      A_Parameter_Specification
--

-------------------------------------------------------------------------------
--  18.30 function Accept_Body_Statements
-------------------------------------------------------------------------------
   function Accept_Body_Statements (Statement       : in Asis.Statement;
                                    Include_Pragmas : in Boolean := False)
                                    return Asis.Statement_List;

-------------------------------------------------------------------------------
--  Statement       - Specifies the accept statement to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns the list of statements and pragmas from the body of the accept
--  statement, in their order of appearance.
--
--  Appropriate Statement_Kinds:
--      An_Accept_Statement
--
--  Returns Element_Kinds:
--      A_Pragma
--      A_Statement
--
-------------------------------------------------------------------------------
--  18.31 function Accept_Body_Exception_Handlers
-------------------------------------------------------------------------------

   function Accept_Body_Exception_Handlers
                 (Statement       : in Asis.Statement;
                  Include_Pragmas : in Boolean := False)
                  return Asis.Statement_List;

-------------------------------------------------------------------------------
--  Statement       - Specifies the accept statement to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns the list of exception handlers and pragmas from the body of the
--  accept statement, in their order of appearance.
--
--  Appropriate Statement_Kinds:
--      An_Accept_Statement
--
--  Returns Element_Kinds:
--      A_Pragma
--      An_Exception_Handler
--
-------------------------------------------------------------------------------
--  18.32 function Corresponding_Entry
-------------------------------------------------------------------------------

   function Corresponding_Entry (Statement : in Asis.Statement)
                                 return Asis.Declaration;

-------------------------------------------------------------------------------
--  Statement   - Specifies the accept statement to query
--
--  Returns the declaration of the entry accepted in this statement.
--
--  Appropriate Statement_Kinds:
--      An_Accept_Statement
--
--  Returns Declaration_Kinds:
--      An_Entry_Declaration
--

-------------------------------------------------------------------------------
--  18.33 function Requeue_Entry_Name
-------------------------------------------------------------------------------

   function Requeue_Entry_Name (Statement : in Asis.Statement)
                                return Asis.Name;

-------------------------------------------------------------------------------
--  Statement   - Specifies the requeue statement to query
--
--  Returns the name of the entry requeued by the statement.
--  The name follows the reserved word "requeue".
--
--  Appropriate Statement_Kinds:
--      A_Requeue_Statement
--      A_Requeue_Statement_With_Abort
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  18.34 function Delay_Expression
-------------------------------------------------------------------------------

   function Delay_Expression (Statement : in Asis.Statement)
                              return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement   - Specifies the delay statement to query
--
--  Returns the expression for the duration of the delay.
--
--  Appropriate Statement_Kinds:
--      A_Delay_Until_Statement
--      A_Delay_Relative_Statement
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  18.35 function Guard
-------------------------------------------------------------------------------

   function Guard (Path : in Asis.Path)
                   return Asis.Expression;

-------------------------------------------------------------------------------
--  Path - Specifies the select statement execution path to query
--
--  Returns the conditional expression guard for the path.
--
--  Returns a Nil_Element if there is no guard, or if the path is from a
--  timed_entry_call, a conditional_entry_call, or an asynchronous_select
--  statement where a guard is not legal.
--
--  Appropriate Path_Kinds:
--      A_Select_Path
--      An_Or_Path
--
--  Returns Element_Kinds:
--      Not_An_Element
--      An_Expression
--

-------------------------------------------------------------------------------
--  18.36 function Aborted_Tasks
-------------------------------------------------------------------------------

   function Aborted_Tasks (Statement : in Asis.Statement)
                           return Asis.Expression_List;

-------------------------------------------------------------------------------
--  Statement    - Specifies the abort statement to query
--
--  Returns a list of the task names from the ABORT statement, in their order
--  of appearance.
--
--  Appropriate Statement_Kinds:
--      An_Abort_Statement
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  18.37 function Choice_Parameter_Specification
-------------------------------------------------------------------------------

   function Choice_Parameter_Specification
       (Handler : in Asis.Exception_Handler)
        return Asis.Declaration;

-------------------------------------------------------------------------------
--  Handler - Specifies the exception handler to query
--
--  Returns the choice parameter specification following the reserved word
--  "when" in the exception handler.
--
--  Returns a Nil_Element if there is no explicit choice parameter.
--
--  Appropriate Element_Kinds:
--    An_Exception_Handler
--
--  Returns Declaration_Kinds:
--      Not_A_Declaration
--      A_Choice_Parameter_Specification
--
-------------------------------------------------------------------------------
--  18.38 function Exception_Choices
-------------------------------------------------------------------------------

   function Exception_Choices (Handler : in Asis.Exception_Handler)
                               return Asis.Element_List;

-------------------------------------------------------------------------------
--  Handler - Specifies the exception handler to query
--
--  Returns a list of the 'when <choice> | <choice>' elements, in their
--  order of appearance.  Choices are either the exception name expression or
--  an others choice.
--
--  Appropriate Element_Kinds:
--    An_Exception_Handler
--
--  Returns Expression_Kinds:
--      An_Identifier
--      A_Selected_Component
--
--  Returns Definition_Kinds:
--      An_Others_Choice
--

-------------------------------------------------------------------------------
--  18.39 function Handler_Statements
-------------------------------------------------------------------------------

   function Handler_Statements (Handler         : in Asis.Exception_Handler;
                                Include_Pragmas : in Boolean := False)
                                return Asis.Statement_List;

-------------------------------------------------------------------------------
--  Handler         - Specifies the exception handler to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns the list of statements and pragmas from the body of the
--  exception handler, in their order of appearance.
--
--  Appropriate Element_Kinds:
--    An_Exception_Handler
--
--  Returns Element_Kinds:
--      A_Pragma
--      A_Statement
--
-------------------------------------------------------------------------------
--  18.40 function Raised_Exception
-------------------------------------------------------------------------------

   function Raised_Exception (Statement : in Asis.Statement)
                              return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement - Specifies the raise statement to query
--
--  Returns the expression that names the raised exception.
--
--  Returns a Nil_Element if there is no explicitly named exception.
--
--  Appropriate Statement_Kinds:
--      A_Raise_Statement
--
--  Returns Expression_Kinds:
--      Not_An_Expression
--      An_Identifier
--      A_Selected_Component
--
-------------------------------------------------------------------------------
--  18.xx function Raise_Statement_Message
-------------------------------------------------------------------------------

   function Raise_Statement_Message  -- 13.3(2)
     (Statement : Asis.Statement)
      return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement specifies the raise statement to query.
--
--  Returns the string expression that is associated with the raised
--  exception and follows the WITH keyword in the raise statement.
--
--  Returns a Nil_Element if there is no string expression.
--
--  Appropriate Statement_Kinds:
--      A_Raise_Statement
--
--  Returns Element_Kinds:
--      Not_An_Element
--      An_Expression
--
-------------------------------------------------------------------------------
--  18.41 function Qualified_Expression
-------------------------------------------------------------------------------

   function Qualified_Expression (Statement : in Asis.Statement)
                                  return Asis.Expression;

-------------------------------------------------------------------------------
--  Statement  - Specifies the code statement to query
--
--  Returns the qualified aggregate expression representing the code statement.
--
--  Appropriate Statement_Kinds:
--      A_Code_Statement
--
--  Returns Expression_Kinds:
--      A_Qualified_Expression
--

-------------------------------------------------------------------------------
--  18.42 function Is_Dispatching_Call
-------------------------------------------------------------------------------

   function Is_Dispatching_Call (Call : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Call - Specifies the element to query.
--
--  Returns True if the controlling tag of Call is dynamically determined.
--
--  This function shall always return False when
--  pragma Restrictions(No_Dispatch) applies.
--
--  Returns False for any unexpected Element.
--
--  Expected Expression_Kinds:
--    A_Function_Call
--
--  Expected Statement_Kinds:
--    A_Procedure_Call_Statement
--
-------------------------------------------------------------------------------
--  18.43 function Is_Call_On_Dispatching_Operation
-------------------------------------------------------------------------------

   function Is_Call_On_Dispatching_Operation (Call : in Asis.Element)
                                              return Boolean;

-------------------------------------------------------------------------------
--  Call - Specifies the element to query.
--
--  Returns True if the name or prefix of Call denotes the declaration of a
--  primitive operation of a tagged type.
--
--  Returns False for any unexpected Element.
--
--  Expected Element_Kinds:
--    A_Function_Call
--    A_Procedure_Call_Statement
--
-------------------------------------------------------------------------------

end Asis.Statements;



------------------------------------------------------------------------------
--  Copyright (c) 2006, Maxim Reznik
--  All rights reserved.
--
--  Redistribution and use in source and binary forms, with or without
--  modification, are permitted provided that the following conditions are met:
--
--     * Redistributions of source code must retain the above copyright notice,
--     * this list of conditions and the following disclaimer.
--     * Redistributions in binary form must reproduce the above copyright
--     * notice, this list of conditions and the following disclaimer in the
--     * documentation and/or other materials provided with the distribution.
--
--  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
--  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
--  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
--  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
--  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
--  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
--  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
--  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
--  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
--  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
--  POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------
