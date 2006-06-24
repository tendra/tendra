-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  17 package Asis.Expressions
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package Asis.Expressions is
--   pragma Preelaborate;

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Expressions encapsulates a set of queries that operate on
--  An_Expression and An_Association elements.
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  17.1 function Corresponding_Expression_Type
-------------------------------------------------------------------------------

   function Corresponding_Expression_Type (Expression : in Asis.Expression)
                             return Asis.Declaration;

-------------------------------------------------------------------------------
--  Expression  - Specifies the expression to query
--
--  Returns the type declaration for the type or subtype of the expression.
--  This query does not "unwind" subtypes or derived types to get to the
--  Corresponding_First_Subtype or Corresponding_Parent_Subtype declarations.
--  For example, for the following program text:
--
--     type Int is range -5_000 .. 5_000;
--     type My_Int is new Int;
--     type Good_Int is new My_Int;
--     Var: Good_Int;
--
--  The type declaration for Good_Int should be returned. The "unwinding"
--  should not occur. The type declaration for either My_Int or Int should
--  not be returned.
--
--  Returns a Nil_Element if the argument Expression does not represent an Ada
--  expression having an Ada type, including the following classes:
--
--  - Naming expressions that name packages, subprograms, tasks, etc.  These
--    expressions do have a Corresponding_Name_Definition and a
--    Corresponding_Name_Declaration. Although task objects do have
--    a type, this query is limited, on purpose.  Thus, when a naming
--    expression is given to this query (for packages, subprograms,
--    tasks, etc.), this query will return Nil_Element.  As the
--    Application Note below indicates, if any further information
--    is needed, the element should be queried by
--    Corresponding_Name_Definition or Corresponding_Name_Declaration,
--    which should eventually return an A_Task_Type_Declaration element.
--
--  - When An_Identifier Element representing an attribute designator is
--    passed as the actual to this query.
--
--  - The Actual_Parameter Expression from A_Pragma_Argument_Association for
--    a Pragma may or may not have a Corresponding_Expression_Type.
--
--  - An_Attribute_Reference Element also may or may not have a
--    Corresponding_Expression_Type;
--
--  - An enumeration_aggregate which is a part of
--    enumeration_representation_clause.
--
--  Returns a Nil_Element, if the statically determinable type of Expression
--  is a class-wide type, or the Expression corresponds to an inner
--  sub-aggregate in multi-dimensional array aggregates.
--
--  |AN Application Note:
--  |AN
--  |AN If the returned declaration is Nil, an application should make its own
--  |AN analysis based on Corresponding_Name_Definition or
--  |AN Corresponding_Name_Declaration to get more information about the
--  |AN argument, including the static type resolution for class-wide
--  |AN expressions, if needed.  Use Enclosing_Element to determine if
--  |AN Expression is from pragma argument association. If for such an
--  |AN expression, Corresponding_Name_Definition raises ASIS_Failed (with a
--  |AN Status of Value_Error), this An_Expression element does not represent
--  |AN a normal Ada expression at all and does not follow normal Ada semantic
--  |AN rules.
--  |AN For example, "pragma Private_Part (Open => Yes);", the "Yes" expression
--  |AN may simply be a "keyword" that is specially recognized by the
--  |AN implementor's compilation system and may not refer to any
--  |AN declared object.
--
--  Appropriate Element_Kinds:
--      An_Expression
--
--  Returns Element_Kinds:
--      Not_An_Element
--      A_Declaration
--
--  |ER An_Integer_Literal - 2.4 - No child elements
--  |ER A_Real_Literal     - 2.4 - No child elements
--  |ER A_String_Literal   - 2.6 - No child elements
--  |ER
--  |ER A string image returned by:
--  |ER    function Value_Image
--
-------------------------------------------------------------------------------
--  17.2 function Value_Image
-------------------------------------------------------------------------------

   function Value_Image (Expression : in Asis.Expression) return Wide_String;

-------------------------------------------------------------------------------
--  Expression  - Specifies the expression to query
--
--  Returns the string image of the value of the string, integer, or real
--  literal.
--
--  For string literals, Value will return the quotes around the string
--  literal, these quotes are doubled, just as any quote appearing embedded in
--  the string literal in the program text.
--
--  The form of numbers returned by this query may vary between implementors.
--  Implementors are encouraged, but not required, to return numeric literals
--  using the same based or exponent form used in the original compilation
--  text.
--
--  Appropriate Expression_Kinds:
--      An_Integer_Literal
--      A_Real_Literal
--      A_String_Literal
--
-------------------------------------------------------------------------------
--  |ER An_Identifier          - 4.1 - No child elements
--  |ER An_Operator_Symbol     - 4.1 - No child elements
--  |ER A_Character_Literal    - 4.1 - No child elements
--  |ER An_Enumeration_Literal - 4.1 - No child elements
--  |ER
--  |ER A string image returned by:
--  |ER    function Name_Image
--  |ER
--  |ER Semantic elements returned by:
--  |ER    function Corresponding_Name_Definition
--  |ER    function Corresponding_Name_Definition_List
--  |ER    function Corresponding_Name_Declaration
--
-------------------------------------------------------------------------------
--  17.3 function Name_Image
-------------------------------------------------------------------------------

   function Name_Image (Expression : in Asis.Expression) return Program_Text;

-------------------------------------------------------------------------------
--  Name  - Specifies the name to query
--
--  Returns the program text image of the name.
--
--  An_Operator_Symbol elements have names with embedded quotes """abs"""
--   (function "abs").
--
--  A_Character_Literal elements have names with embedded apostrophes "'x'"
--   (literal 'x').
--
--  An_Enumeration_Literal and An_Identifier elements have identifier names
--   "Blue" (literal Blue) "Abc" (identifier Abc).
--
--  Note: Implicit subtypes that can be encountered while traversing the
--  semantic information embedded in implicit inherited subprogram declarations
--  (Reference Manual 3.4 (17-22)) could have names that are unique in a
--  particular scope.  This is because these subtypes are Is_Part_Of_Implicit
--  declarations that do not form part of the physical text of the original
--  compilation units. Some applications may wish to carefully separate the
--  names of declarations from the names of Is_Part_Of_Implicit declaration
--  when creating symbol tables and other name-specific lookup mechanisms.
--
--  The case of names returned by this query may vary between implementors.
--  Implementors are encouraged, but not required, to return names in the
--  same case as was used in the original compilation text.
--
--  Appropriate Expression_Kinds:
--      An_Identifier
--      An_Operator_Symbol
--      A_Character_Literal
--      An_Enumeration_Literal
--
-------------------------------------------------------------------------------
--  17.4 function References
-------------------------------------------------------------------------------

   function References (Name           : in Asis.Element;
                        Within_Element : in Asis.Element;
                        Implicitly     : in Boolean := False)
                        return Asis.Name_List;

-------------------------------------------------------------------------------
--  Name    - Specifies the entity to query
--  Within_Element - Specifies the limits for the query which is limited
--                   to the Element and its children.
--
--  If the Implicitly argument is True:
--    Returns all usage references of the given entity made by both explicit
--    and implicit elements within the given limits.
--
--  If the Implicitly argument is False:
--    Returns all usage references of the given entity made only by explicit
--    elements within the given limits.
--
--  Returned references are in their order of appearance.
--
--  Appropriate Element_Kinds:
--      A_Defining_Name
--  Returns Element_Kinds:
--      An_Expression
--
--  May raise ASIS_Failed with a Status of Obsolete_Reference_Error if the
--  argument is part of an inconsistent compilation unit.
--
-------------------------------------------------------------------------------
--  17.5 function Is_Referenced
-------------------------------------------------------------------------------

   function Is_Referenced (Name           : in Asis.Element;
                           Within_Element : in Asis.Element;
                           Implicitly     : in Boolean := False)
                           return Boolean;

-------------------------------------------------------------------------------
--  Name    - Specifies the entity to query
--  Within_Element - Specifies the limits for the query which is limited
--                  to the Element and its children.
--

--  If the Implicitly argument is True:
--    Returns True if the Name is referenced by either implicit or explicit
--    elements within the given limits.
--
--  If the Implicitly argument is False:
--    Returns True only if the Name is referenced by explicit elements.
--
--  Returns False for any unexpected Element.
--
--  Expected Element_Kinds:
--      A_Defining_Name
--
--  May raise ASIS_Failed with a Status of Obsolete_Reference_Error if the
--  argument is part of an inconsistent compilation unit.
--
-------------------------------------------------------------------------------
--  17.6 function Corresponding_Name_Definition
-------------------------------------------------------------------------------

   function Corresponding_Name_Definition (Reference : in Asis.Expression)
                             return Asis.Defining_Name;

-------------------------------------------------------------------------------
--  Reference   - Specifies an expression to query
--
--  Returns the defining_identifier, defining_character_literal,
--  defining_operator_symbol, or defining_program_unit_name from the
--  declaration of the referenced entity.
--
--  - Record component references return the defining name of the
--   record discriminant or component_declaration.  For references to inherited
--   declarations of derived types, the Corresponding_Name_Definition returns
--   the defining name of the implicit inherited declaration.
--
--  - References to implicit operators and inherited subprograms will return
--    an Is_Part_Of_Implicit defining name for the operation.  The
--    Enclosing_Element of the name is an implicit declaration for the
--    operation.  The Enclosing_Element of the declaration is the associated
--    derived_type_definition.
--
--  - References to formal parameters given in calls to inherited subprograms
--    will return an Is_Part_Of_Implicit defining name for the
--    Parameter_Specification from the inherited subprogram specification.
--
--  - References to visible components of instantiated generic packages will
--    return a name from the expanded generic specification instance.
--
--  - References, within expanded generic instances, that refer to other
--    components of the same, or an enclosing, expanded generic instance,
--    return a name from the appropriate expanded specification or body
--    instance.
--
--  In case of renaming, the function returns the new name for the entity.
--
--  Returns a Nil_Element if the reference is to an implicitly declared
--  element for which the implementation does not provide declarations and
--  defining name elements.
--
--  Returns a Nil_Element if the argument is a dispatching call.
--
--  The Enclosing_Element of a non-Nil result is either a Declaration or a
--  Statement.
--
--  Appropriate Expression_Kinds:
--      An_Identifier
--      An_Operator_Symbol
--      A_Character_Literal
--      An_Enumeration_Literal
--
--  Returns Element_Kinds:
--      Not_An_Element
--      A_Defining_Name
--
--  |IP Implementation Permissions:
--  |IP
--  |IP An implementation may choose to return any part of multi-part
--  |IP declarations and definitions. Multi-part declaration/definitions
--  |IP can occur for:
--  |IP
--  |IP - Subprogram specification in package specification, package body,
--  |IP   and subunits (is separate);
--  |IP
--  |IP - Entries in package specification, package body, and subunits (is
--  |IP   separate);
--  |IP
--  |IP - Private type and full type declarations;
--  |IP
--  |IP - Incomplete type and full type declarations; and
--  |IP
--  |IP - Deferred constant and full constant declarations.
--  |IP
--  |IP No guarantee is made that the element will be the first part or
--  |IP that the determination will be made due to any visibility rules.
--  |IP An application should make its own analysis for each case based
--  |IP on which part is returned.
--  |IP
--  |IP Some implementations do not represent all forms of implicit
--  |IP declarations such that elements representing them can be easily
--  |IP provided.  An implementation can choose whether or not to construct
--  |IP and provide artificial declarations for implicitly declared elements.
--
--  |IR Implementation Requirements:
--  |IR
--  |IR Raises ASIS_Inappropriate_Element, with a Status of Value_Error, if
--  |IR passed a reference that does not have a declaration:
--  |IR
--  |IR - a reference to an attribute_designator.  Attributes are defined, but
--  |IR   have no implicit or explicit declarations;
--  |IR
--  |IR - an identifier which syntactically is placed before "=>" in a
--  |IR   pragma_argument_association which has the form of a named
--  |IR   association; such an identifier can never have a declaration;
--  |IR
--  |IR - an identifier specific to a pragma (Reference Manual, 2.8(10));
--  |IR
--  |IR     pragma Should_I_Check ( Really => Yes );
--  |IR
--  |IR In this example, both the names Really and Yes have no declaration.
--  |IR
--  |IR Raises ASIS_Inappropriate_Element, with a Status of Value_Error, if
--  |IR passed a portion of a pragma that was "ignored" by the compiler and
--  |IR which does not have (sufficient) semantic information for a proper
--  |IR return result to be computed.  For example,
--  |IR
--  |IR     pragma I_Am_Ignored (Foof);
--  |IR
--  |IR The "Foof" expression is An_Identifier but raises this exception
--  |IR if passed to Corresponding_Name_Definition if the pragma was ignored
--  |IR or unprocessed.
--  |IR
--  |IR Raises ASIS_Inappropriate_Element, with a Status of Value_Error, if
--  |IR passed a portion of a pragma that is an ambiguous reference to more
--  |IR than one entity.  For example,
--  |IR
--  |IR     pragma Inline ("+");        --  Inlines all "+" operators
--  |IR
--  |IR The "+" expression is An_Operator_Symbol but raises this
--  |IR exception if it referenced more than one "+" operator.  In this
--  |IR case, the Corresponding_Name_Definition_List query can be used to
--  |IR obtain a list of referenced entities.
--

-------------------------------------------------------------------------------
--  17.7 function Corresponding_Name_Definition_List
-------------------------------------------------------------------------------

   function Corresponding_Name_Definition_List (Reference : in Asis.Element)
                                   return Asis.Defining_Name_List;

-------------------------------------------------------------------------------
--  Reference   - Specifies an entity reference to query
--
--  Exactly like Corresponding_Name_Definition except it returns a list.
--  The list will almost always have a length of one.  The exception to this
--  is the case where an expression in a pragma is ambiguous and reference
--  more than one entity.  For example,
--
--      pragma Inline ("+");        --  Inlines all "+" operators
--
--  The "+" expression is An_Operator_Symbol but could reference more than one
--  "+" operator.  In this case, the resulting list includes all referenced
--  entities.
--
--  Appropriate Expression_Kinds:
--      An_Identifier
--      An_Operator_Symbol
--      A_Character_Literal
--      An_Enumeration_Literal
--
--  Returns Element_Kinds:
--      A_Defining_Name
--
-------------------------------------------------------------------------------
--  17.8 function Corresponding_Name_Declaration
-------------------------------------------------------------------------------

   function Corresponding_Name_Declaration (Reference : in Asis.Expression)
                              return Asis.Element;

-------------------------------------------------------------------------------
--  Reference   - Specifies the entity reference to query
--
--  Returns the declaration that declared the entity named by the given
--  reference.  The result is exactly the same as:
--
--      Result := Corresponding_Name_Definition (Reference);
--      if not Is_Nil (Result) then
--          Result := Enclosing_Element (Result);
--      end if;
--      return Result;
--
--  See the comments for Corresponding_Name_Definition for details.
--  The result is either a Declaration or a Statement.  Statements result
--  from references to statement labels, loop identifiers, and block
--  identifiers.
--
--  Appropriate Element_Kinds:
--      An_Expression
--
--  Appropriate Expression_Kinds:
--      An_Identifier
--      An_Operator_Symbol
--      A_Character_Literal
--      An_Enumeration_Literal
--
--  Returns Element_Kinds:
--      A_Declaration
--      A_Statement
--
--  Predefined types, exceptions, operators in package Standard can be
--  checked by testing that the enclosing Compilation_Unit is standard.
--
--  |ER------------------------------------------------------------------------
--  |ER An_Explicit_Dereference - 4.1
--  |CR
--  |CR Child elements returned by: function Prefix
--

-------------------------------------------------------------------------------
--  17.9 function Prefix
-------------------------------------------------------------------------------

   function Prefix (Expression : in Asis.Expression) return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies the name expression to query
--
--  Returns the prefix (the construct to the left of: the rightmost unnested
--  left parenthesis in function_call elements and indexed_component elements
--  or slice elements, the rightmost 'dot' for selected_component elements,
--  or the rightmost tick for attribute_reference elements).
--
--  Returns the operator_symbol for infix operator function calls.  The infix
--  form A + B is equivalent to the prefix form "+"(A, B).
--
--  Appropriate Expression_Kinds:
--      An_Explicit_Dereference       P.ALL
--      An_Attribute_Reference        Priv'Base'First
--      A_Function_Call               Abc(...) or Integer'Image(...)
--      An_Indexed_Component          An_Array(3)
--      A_Selected_Component          A.B.C
--      A_Slice                       An_Array(3 .. 5)
--
--  Returns Expression_Kinds:
--      An_Expression
--
--  |ER------------------------------------------------------------------------
--  |ER An_Indexed_Component - 4.1.1
--  |ER
--  |CR
--  |CR Child elements returned by:
--  |CR    function Prefix
--  |CR    function Index_Expressions
--  |CR
--
-------------------------------------------------------------------------------
--  17.10 function Index_Expressions
-------------------------------------------------------------------------------

   function Index_Expressions (Expression : in Asis.Expression)
                               return Asis.Expression_List;

-------------------------------------------------------------------------------
--  Expression  - Specifies an indexed_component to query
--
--  Returns the list of expressions (possibly only one) within the parenthesis,
--  in their order of appearance.
--
--  Appropriate Expression_Kinds:
--      An_Indexed_Component
--
--  Returns Element_Kinds:
--      An_Expression
--
--  |ER------------------------------------------------------------------------
--  |ER A_Slice - 4.1.2
--  |CR
--  |CR Child elements returned by:
--  |CR    function Prefix
--  |CR    function Slice_Range
--  |CR
--

-------------------------------------------------------------------------------
--  17.11 function Slice_Range
-------------------------------------------------------------------------------

   function Slice_Range (Expression : in Asis.Expression)
                         return Asis.Discrete_Range;

-------------------------------------------------------------------------------
--  Expression  - Specifies the slice to query
--
--  Returns the discrete range of the slice.
--
--  Appropriate Expression_Kinds:
--      A_Slice
--
--  Returns Definition_Kinds:
--      A_Discrete_Range
--
-------------------------------------------------------------------------------
--  17.12 function Selector
-------------------------------------------------------------------------------

   function Selector (Expression : in Asis.Expression)
                      return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies the selected_component to query
--
--  Returns the selector (the construct to the right of the rightmost 'dot' in
--  the selected_component).
--
--  Appropriate Expression_Kinds:
--      A_Selected_Component
--
--  Returns Expression_Kinds:
--      An_Identifier
--      An_Operator_Symbol
--      A_Character_Literal
--      An_Enumeration_Literal
--
-------------------------------------------------------------------------------
--  17.13 function Attribute_Designator_Identifier
-------------------------------------------------------------------------------

   function Attribute_Designator_Identifier
            (Expression : in Asis.Expression)
                return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies an attribute_reference expression to query
--
--  Returns the identifier of the attribute_designator (the construct to the
--  right of the rightmost tick of the attribute_reference).  The Prefix of
--  the attribute_reference can itself be an attribute_reference as in
--  T'BASE'FIRST where the prefix is T'BASE and the attribute_designator name
--  is FIRST.
--
--  Attribute_designator reserved words "access", "delta", and "digits" are
--  treated as An_Identifier.
--
--  Appropriate Expression_Kinds:
--      An_Attribute_Reference
--
--  Returns Expression_Kinds:
--      An_Identifier
--

-------------------------------------------------------------------------------
--  17.14 function Attribute_Designator_Expressions
-------------------------------------------------------------------------------

   function Attribute_Designator_Expressions
            (Expression : in Asis.Expression)
                return Asis.Expression_List;

-------------------------------------------------------------------------------
--  Expression  - Specifies an attribute expression to query
--
--  Returns the static expressions associated with the optional argument of
--  the attribute_designator.  Expected predefined attributes are A'First(N),
--  A'Last(N), A'Length(N), and A'Range(N).
--
--  Returns a Nil_Element_List if there are no arguments.
--
--  Appropriate Expression_Kinds:
--      An_Attribute_Reference
--          Appropriate Attribute_Kinds:
--               A_First_Attribute
--               A_Last_Attribute
--               A_Length_Attribute
--               A_Range_Attribute
--               An_Implementation_Defined_Attribute
--               An_Unknown_Attribute
--
--  Returns Element_Kinds:
--      An_Expression
--
--  |IP Implementation Permissions:
--  |IP
--  |IP This query returns a list to support implementation-defined attributes
--  |IP that may have more than one static_expression.
--
-------------------------------------------------------------------------------
--  17.15 function Record_Component_Associations
-------------------------------------------------------------------------------

   function Record_Component_Associations
                  (Expression : in Asis.Expression;
                   Normalized : in Boolean := False)
                   return Asis.Association_List;

-------------------------------------------------------------------------------
--  Expression  - Specifies an aggregate expression to query
--  Normalized  - Specifies whether the normalized form is desired
--
--  Returns a list of the record_component_association elements of a
--  record_aggregate or an extension_aggregate.
--
--  Returns a Nil_Element_List if the aggregate is of the form (null record).
--
--  An unnormalized list contains all needed associations ordered as they
--  appear in the program text.  Each unnormalized association has an optional
--  list of discriminant_selector_name elements, and an explicit expression.
--
--  A normalized list contains artificial associations representing all
--  needed components in an order matching the declaration order of the
--  needed components.
--
--  Each normalized association represents a one on one mapping of a
--  component to the explicit expression.  A normalized association has one
--  A_Defining_Name component that denotes the discriminant_specification or
--  component_declaration, and one An_Expression component that is the
--  expression.
--
--  Appropriate Expression_Kinds:
--      A_Record_Aggregate
--      An_Extension_Aggregate
--
--  Returns Association_Kinds:
--      A_Record_Component_Association
--
--  |IR Implementation Requirements:
--  |IR
--  |IR Normalized associations are Is_Normalized and Is_Part_Of_Implicit.
--  |IR Normalized associations are never Is_Equal to unnormalized
--  |IR  associations.
--
--  |IP Implementation Permissions:
--  |IP
--  |IP An implementation may choose to normalize its internal representation
--  |IP to use the defining_identifier element instead of the
--  |IP component_selector_name element.
--  |IP
--  |IP If so, this query will return Is_Normalized associations even if
--  |IP Normalized is False, and the query
--  |IP Record_Component_Associations_Normalized will return True.
--
-------------------------------------------------------------------------------
--  17.16 function Extension_Aggregate_Expression
-------------------------------------------------------------------------------

   function Extension_Aggregate_Expression
                              (Expression : in Asis.Expression)
                               return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies an extension_aggregate expression to query
--
--  Returns the ancestor_part expression preceding the reserved word with in
--  the extension_aggregate.
--
--  Appropriate Expression_Kinds:
--      An_Extension_Aggregate
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  17.17 function Array_Component_Associations
-------------------------------------------------------------------------------

   function Array_Component_Associations
                  (Expression : in Asis.Expression)
                        return Asis.Association_List;

-------------------------------------------------------------------------------
--  Expression  - Specifies an array aggregate expression to query
--
--  Returns a list of the Array_Component_Associations in an array aggregate.
--
--  Appropriate Expression_Kinds:
--      A_Positional_Array_Aggregate
--      A_Named_Array_Aggregate
--
--  Returns Association_Kinds:
--      An_Array_Component_Association
--
--  |AN Application Note:
--  |AN
--  |AN While positional_array_aggregate elements do not have
--  |AN array_component_association elements defined by Ada syntax, ASIS treats
--  |AN A_Positional_Array_Aggregate as if it were A_Named_Array_Aggregate.
--  |AN The An_Array_Component_Association elements returned will have
--  |AN Array_Component_Choices that are a Nil_Element_List for all positional
--  |AN expressions except an others choice.
--

-------------------------------------------------------------------------------
--  17.18 function Array_Component_Choices
-------------------------------------------------------------------------------

   function Array_Component_Choices
            (Association : in Asis.Association)
                return Asis.Expression_List;

-------------------------------------------------------------------------------
--  Association - Specifies the component association to query
--
--  If the Association is from a named_array_aggregate:
--
--  - Returns the discrete_choice_list order of appearance.  The choices are
--    either An_Expression or A_Discrete_Range elements, or a single
--    An_Others_Choice element.
--
--  If the Association is from a positional_array_aggregate:
--
--  - Returns a single An_Others_Choice if the association is an others
--    choice (others => expression).
--
--  - Returns a Nil_Element_List otherwise.
--
--  Appropriate Association_Kinds:
--      An_Array_Component_Association
--
--  Returns Element_Kinds:
--      A_Definition
--      An_Expression
--
--  Returns Definition_Kinds:
--      A_Discrete_Range
--      An_Others_Choice
--
-------------------------------------------------------------------------------
--  17.19 function Record_Component_Choices
-------------------------------------------------------------------------------

   function Record_Component_Choices
            (Association : in Asis.Association)
                return Asis.Expression_List;

-------------------------------------------------------------------------------
--  Association - Specifies the component association to query
--
--  If the Association argument is from an unnormalized list:
--
--  - If the Association is a named component association:
--
--   o Returns the component_choice_list order of appearance.  The choices are
--     either An_Identifier elements representing component_selector_name
--     elements, or a single An_Others_Choice element.
--
--   o The Enclosing_Element of the choices is the Association argument.
--
--  - If the Association is a positional component association:
--
--   o Returns a Nil_Element_List.
--
--  If the Association argument is from a Normalized list:
--
--  - Returns a list containing a single choice:
--
--   o A_Defining_Name element representing the defining_identifier of
--     the component_declaration.
--
--   o The Enclosing_Element of the A_Defining_Name is the
--     component_declaration.
--
--  Normalized lists contain artificial ASIS An_Association elements that
--  provide one formal A_Defining_Name => An_Expression pair per
--  association.  These artificial associations are Is_Normalized.  Their
--  component A_Defining_Name is not Is_Normalized.
--
--  Appropriate Association_Kinds:
--      A_Record_Component_Association
--
--  Returns Element_Kinds:
--      A_Defining_Name             --  Is_Normalized(Association)
--      An_Expression               --  not Is_Normalized(Association)
--           Returns Expression_Kinds:
--                An_Identifier
--      A_Definition
--           Returns Definition_Kinds:
--                An_Others_Choice
--
-------------------------------------------------------------------------------
--  17.20 function Component_Expression
-------------------------------------------------------------------------------

   function Component_Expression (Association : in Asis.Association)
                                  return Asis.Expression;

-------------------------------------------------------------------------------
--  Association - Specifies the component association to query
--
--  Returns the expression of the record_component_association or
--  array_component_association.
--
--  The Enclosing_Element of the expression is the Association argument.
--
--  Normalized lists contain artificial ASIS An_Association elements that
--  provide one formal A_Defining_Name => An_Expression pair per
--  association.  These artificial associations are Is_Normalized.  Their
--  component An_Expression elements are not Is_Normalized.
--
--  Appropriate Association_Kinds:
--      A_Record_Component_Association
--      An_Array_Component_Association
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  17.21 function Formal_Parameter
-------------------------------------------------------------------------------

   function Formal_Parameter (Association : in Asis.Association)
                              return Asis.Element;

-------------------------------------------------------------------------------
--  Association - Specifies the association to query
--
--  If the Association argument is from an unnormalized list:
--
--  - If the Association is given in named notation:
--
--   Returns An_Identifier representing the formal_parameter_selector_name,
--   generic_formal_parameter_selector_name, or pragma_argument_identifier.
--
--   The Enclosing_Element of the An_Identifier element is the Association
--   argument.
--
--  - If the Association is given in positional notation:
--
--   Returns a Nil_Element.
--
--  If the Association argument is from a Normalized list:
--
--  - Returns A_Defining_Name representing the defining_identifier of the
--    parameter_specification or generic_formal_parameter_declaration.
--    Pragma_argument_association elements are not available in normalized
--    form.
--
--  - The Enclosing_Element of the A_Defining_Name is the
--    parameter_specification or generic_formal_parameter_declaration element.
--
--  Normalized lists contain artificial ASIS An_Association elements that
--  provide one formal A_Defining_Name => An_Expression pair per
--  association.  These artificial associations are Is_Normalized.  Their
--  component A_Defining_Name elements are not Is_Normalized.
--
--  Appropriate Association_Kinds:
--      A_Parameter_Association
--      A_Generic_Association
--      A_Pragma_Argument_Association
--
--  Returns Element_Kinds:
--      Not_An_Element
--      An_Operator_Symbol
--      A_Defining_Name             --  Is_Normalized(Association)
--      An_Expression               --  not Is_Normalized(Association)
--           Returns Expression_Kinds:
--                 An_Identifier
--
-------------------------------------------------------------------------------
--  17.22 function Actual_Parameter
-------------------------------------------------------------------------------

   function Actual_Parameter (Association : in Asis.Association)
                              return Asis.Expression;

-------------------------------------------------------------------------------
--  Association   - Specifies the association to query
--
--  If the Association argument is from an unnormalized list:
--
--  - Returns An_Expression representing:
--
--   o the explicit_actual_parameter of a parameter_association.
--
--   o the explicit_generic_actual_parameter of a generic_association.
--
--   o the name or expression of a pragma_argument_association.
--
--  - The Enclosing_Element of An_Expression is the Association argument.
--
--  If the Association argument is from a Normalized list:
--
--  - If the Association is given explicitly:
--
--   o Returns An_Expression representing:
--
--     + the explicit_actual_parameter of a parameter_association.
--
--     + the explicit_generic_actual_parameter of a generic_association.
--
--   o The Enclosing_Element of An_Expression is the Association argument.
--
--  - If the Association is given by default:
--
--   o Returns An_Expression representing:
--
--     + the corresponding default_expression of the Is_Normalized
--       A_Parameter_Association.
--
--     + the corresponding default_expression or default_name of the
--       Is_Normalized A_Generic_Association.
--
--   o The Enclosing_Element of the An_Expression element is the
--     parameter_specification or generic_formal_parameter_declaration that
--     contains the default_expression or default_name, except for the case
--     when this An_Expression element is an implicit naming expression
--     representing the actual subprogram selected at the place of the
--     instantiation for A_Box_Default.  In the latter case, the
--     Enclosing_Element for such An_Expression is the instantiation.
--
--   o Normalized lists contain artificial ASIS An_Association elements that
--     provide one formal A_Defining_Name => An_Expression pair per
--     association.  These artificial associations are Is_Normalized.
--     Artificial associations of default associations are
--     Is_Defaulted_Association.  Their component An_Expression elements are
--     not Is_Normalized and are not Is_Defaulted_Association.
--
--  If the argument is A_Pragma_Argument_Association, then this function may
--  return any expression to support implementation-defined pragmas.
--
--  Appropriate Association_Kinds:
--      A_Parameter_Association
--      A_Generic_Association
--      A_Pragma_Argument_Association
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  17.23 function Discriminant_Selector_Names
-------------------------------------------------------------------------------

   function Discriminant_Selector_Names
                (Association : in Asis.Discriminant_Association)
                return Asis.Expression_List;

-------------------------------------------------------------------------------
--  Association - Specifies the discriminant association to query
--
--  If the Association argument is from an unnormalized list:
--
--  - If the Association is a named discriminant_association:
--
--   o Returns a list of the An_Identifier discriminant_selector_name elements
--     in order of appearance.
--
--   o The Enclosing_Element of the names is the Association argument.
--
--  - If the Association is a positional discriminant_association:
--
--   o Returns a Nil_Element_List.
--
--  If the Association argument is from a Normalized list:
--
--  - Returns a list containing a single A_Defining_Name element representing
--    the defining_identifier of the discriminant_specification.
--
--  - The Enclosing_Element of the A_Defining_Name is the
--    discriminant_specification.
--
--  - Normalized lists contain artificial ASIS An_Association elements that
--    provide one formal A_Defining_Name => An_Expression pair per
--    association.  These artificial associations are Is_Normalized.  Their
--    component A_Defining_Name elements are not Is_Normalized.
--
--  Appropriate Association_Kinds:
--      A_Discriminant_Association
--
--  Returns Element_Kinds:
--      A_Defining_Name             --  Is_Normalized(Association)
--      An_Expression               --  not Is_Normalized(Association)
--           Returns Expression_Kinds:
--                An_Identifier
--

-------------------------------------------------------------------------------
--  17.24 function Discriminant_Expression
-------------------------------------------------------------------------------

   function Discriminant_Expression
                (Association : in Asis.Discriminant_Association)
                return Asis.Expression;

-------------------------------------------------------------------------------
--  Association - Specifies the discriminant_association to query
--
--  If the Association argument is from an unnormalized list:
--
--  - Returns An_Expression representing the expression of the
--   discriminant_association.
--
--  - The Enclosing_Element of An_Expression is the Association argument.
--
--  If the Association argument is from a Normalized list:
--
--  - If the Association is given explicitly:
--
--   o Returns An_Expression representing the expression of the
--     discriminant_association.
--
--   o The Enclosing_Element of An_Expression is the Association argument.
--
--  - If the Association is given by default:
--
--   o Returns An_Expression representing:
--
--     + the corresponding default_expression of the Is_Normalized
--       A_Discriminant_Association.
--
--   o The Enclosing_Element of the An_Expression element is the
--     discriminant_specification that contains the default_expression.
--
--  - Normalized lists contain artificial ASIS An_Association elements that
--    provide one formal A_Defining_Name => An_Expression pair per
--    association.  These artificial associations are Is_Normalized.
--    Artificial associations of default associations are
--    Is_Defaulted_Association.  Their component An_Expression elements are
--    not Is_Normalized and are not Is_Defaulted_Association.
--
--  Appropriate Association_Kinds:
--      A_Discriminant_Association
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  17.25 function Is_Normalized
-------------------------------------------------------------------------------

   function Is_Normalized (Association : in Asis.Association) return Boolean;

-------------------------------------------------------------------------------
--  Association - Specifies the association to query
--
--  Returns True if the association is a normalized, artificially created
--  association returned by the queries Discriminant_Associations,
--  Generic_Actual_Part, Call_Statement_Parameters,
--  Record_Component_Associations, or Function_Call_Parameters where
--  Normalized => True (or the operation returns Is_Normalized associations
--  even if Normalized => False).  See the Implementation Permissions for
--  these queries.
--
--  Returns False for any unexpected Element.
--

--  Expected Association_Kinds:
--      A_Discriminant_Association
--      A_Record_Component_Association
--      A_Parameter_Association
--      A_Generic_Association
--
-------------------------------------------------------------------------------
--  17.26 function Is_Defaulted_Association
-------------------------------------------------------------------------------

   function Is_Defaulted_Association
        (Association : in Asis.Association) return Boolean;

-------------------------------------------------------------------------------
--  Association - Specifies the association to query
--
--  Returns True if the association is a normalized, artificially created
--  association returned by the queries Discriminant_Associations,
--  Generic_Actual_Part, Record_Component_Associations,
--  Call_Statement_Parameters, or Function_Call_Parameters where
--  Normalized => True (or the operation returns default associations even if
--  Normalized => False) and the association contains a default expression.
--  A default expression is one that is implicitly supplied by the language
--  semantics and that was not explicitly supplied (typed) by the user.
--
--  Returns False for any unexpected Element.
--
--  Expected Association_Kinds:
--      A_Parameter_Association
--      A_Generic_Association
--
--  |AN Application Note:
--  |AN
--  |AN Always returns False for discriminant associations.  Defaulted
--  |AN discriminant associations occur only when the discriminant constraint
--  |AN is completely missing from a subtype indication.  Consequently, it is
--  |AN not possible to obtain a (normalized) discriminant constraint list for
--  |AN such subtype indications.  Always returns False for component
--  |AN associations.  Aggregates cannot have defaulted components.
--
-------------------------------------------------------------------------------
--  17.27 function Expression_Parenthesized
-------------------------------------------------------------------------------

   function Expression_Parenthesized (Expression : in Asis.Expression)
                                      return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies the parenthesized expression to query
--
--  Returns the expression within the parenthesis.  This operation unwinds
--  only one set of parenthesis at a time, so the result may itself be
--  A_Parenthesized_Expression.
--
--  A_Parenthesized_Expression kind corresponds only to the (expression)
--  alternative in the syntax notion of primary in Reference Manual 4.4.  For
--  example, an expression of a type_conversion is A_Parenthesized_Expression
--  only if it is similar to the form subtype_mark((expression)) where it has
--  at least one set of its own parenthesis.
--
--  Appropriate Expression_Kinds:
--      A_Parenthesized_Expression
--
--  Returns Element_Kinds:
--      An_Expression
--

-------------------------------------------------------------------------------
--  17.28 function Is_Prefix_Call
-------------------------------------------------------------------------------

   function Is_Prefix_Call (Expression : in Asis.Expression) return Boolean;

-------------------------------------------------------------------------------
--  Expression  - Specifies the function call expression to query
--
--  Returns True if the function call is in prefix form.
--
--  Returns False for any unexpected Element.
--
--  For example,
--
--       Foo (A, B);   --  Returns TRUE
--       "<" (A, B);   --  Returns TRUE
--       ... A < B ... --  Returns FALSE
--
--  Expected Expression_Kinds:
--      A_Function_Call
--
-------------------------------------------------------------------------------
--  17.29 function Corresponding_Called_Function
-------------------------------------------------------------------------------

   function Corresponding_Called_Function
            (Expression : in Asis.Expression)
                return Asis.Declaration;

-------------------------------------------------------------------------------
--  Expression  - Specifies the function_call to query
--
--  Returns the declaration of the called function.
--
--  Returns a Nil_Element if the:
--
--  - function_prefix denotes a predefined operator for which the
--    implementation does not provide an artificial function declaration,
--
--  - prefix of the call denotes an access to a function implicit or explicit
--    dereference,
--
--  - argument is a dispatching call.
--
--  If function_prefix denotes an attribute_reference, and if the corresponding
--  attribute is (re)defined by an attribute definition clause, an
--  implementation is encouraged, but not required, to return the definition
--  of the corresponding subprogram whose name is used after "use" in this
--  attribute definition clause. If an implementation cannot return such a
--  subprogram definition, a Nil_Element should be returned. For an attribute
--  reference which is not (re)defined by an attribute definition clause,
--  a Nil_Element should be returned.
--
--  Appropriate Expression_Kinds:
--      A_Function_Call
--
--  Returns Declaration_Kinds:
--      Not_A_Declaration
--      A_Function_Declaration
--      A_Function_Body_Declaration
--      A_Function_Body_Stub
--      A_Function_Renaming_Declaration
--      A_Function_Instantiation
--      A_Formal_Function_Declaration
--      A_Generic_Function_Declaration
--
--  |IP Implementation Permissions:
--  |IP
--  |IP An implementation may choose to return any part of multi-part
--  |IP declarations and definitions. Multi-part declaration/definitions can
--  |IP occur for:
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
--  |IP
--  |IP An implementation can choose whether or not to construct and provide
--  |IP artificial implicit declarations for predefined operators.
--
-------------------------------------------------------------------------------
--  17.30 function Function_Call_Parameters
-------------------------------------------------------------------------------

   function Function_Call_Parameters (Expression : in Asis.Expression;
                                      Normalized : in Boolean := False)
                                      return Asis.Association_List;

-------------------------------------------------------------------------------
--  Expression  - Specifies the function call expression to query
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
--  A normalized association has one A_Defining_Name component that denotes
--  the parameter_specification, and one An_Expression component that is
--  either the explicit_actual_parameter or a default_expression.
--
--  If the prefix of the call denotes an access to a function implicit or
--  explicit deference, normalized associations are constructed on the basis
--  of the formal_part of the parameter_and_result_profile from the
--  corresponding access_to_subprogram definition.

--  Returns Nil_Element for normalized associations in the case where
--  the called function can be determined only dynamically (dispatching
--  calls). ASIS cannot produce any meaningful result in this case.

--  The exception ASIS_Inappropriate_Element is raised when the function
--  call is an attribute reference and Is_Normalized is True.
--
--  Appropriate Expression_Kinds:
--      A_Function_Call
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
--  |IP Function_Call_Parameters_Normalized will return True.
--
-------------------------------------------------------------------------------
--  17.31 function Short_Circuit_Operation_Left_Expression
-------------------------------------------------------------------------------

   function Short_Circuit_Operation_Left_Expression
                (Expression : in Asis.Expression)
                return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies the short circuit operation to query
--
--  Returns the expression preceding the reserved words "and then" or
--  "or else" in the short circuit expression.
--
--  Appropriate Expression_Kinds:
--      An_And_Then_Short_Circuit
--      An_Or_Else_Short_Circuit
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  17.32 function Short_Circuit_Operation_Right_Expression
-------------------------------------------------------------------------------

   function Short_Circuit_Operation_Right_Expression
                (Expression : in Asis.Expression)
                return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies the short circuit operation to query
--
--  Returns the expression following the reserved words "or else" or
--  "and then" in the short circuit expression.
--
--  Appropriate Expression_Kinds:
--      An_And_Then_Short_Circuit
--      An_Or_Else_Short_Circuit
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  17.33 function Membership_Test_Expression
-------------------------------------------------------------------------------

   function Membership_Test_Expression (Expression : in Asis.Expression)
                                        return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies the membership test operation to query
--
--  Returns the expression on the left hand side of the membership test.
--
--  Appropriate Expression_Kinds:
--      An_In_Range_Membership_Test
--      A_Not_In_Range_Membership_Test
--      An_In_Type_Membership_Test
--      A_Not_In_Type_Membership_Test
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  17.34 function Membership_Test_Range
-------------------------------------------------------------------------------

   function Membership_Test_Range
                (Expression : in Asis.Expression)
                return Asis.Range_Constraint;

-------------------------------------------------------------------------------
--  Expression  - Specifies the membership test operation to query
--
--  Returns the range following the reserved words "in" or "not in" from the
--  membership test.
--
--  Appropriate Expression_Kinds:
--      An_In_Range_Membership_Test
--      A_Not_In_Range_Membership_Test
--
--  Returns Constraint_Kinds:
--      A_Range_Attribute_Reference
--      A_Simple_Expression_Range
--
-------------------------------------------------------------------------------
--  17.35 function Membership_Test_Subtype_Mark
-------------------------------------------------------------------------------

   function Membership_Test_Subtype_Mark
                (Expression : in Asis.Expression)
                return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies the membership test operation to query
--
--  Returns the subtype_mark expression following the reserved words "in" or
--  "not in" from the membership test.
--
--  Appropriate Expression_Kinds:
--      An_In_Type_Membership_Test
--      A_Not_In_Type_Membership_Test
--
--  Returns Expression_Kinds:
--      An_Identifier
--      A_Selected_Component
--      An_Attribute_Reference
--
-------------------------------------------------------------------------------
--  17.36 function Converted_Or_Qualified_Subtype_Mark
-------------------------------------------------------------------------------

   function Converted_Or_Qualified_Subtype_Mark
                   (Expression : in Asis.Expression)
                       return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies the type conversion or qualified expression to
--  query.
--
--  Returns the subtype_mark expression that converts or qualifies the
--  expression.
--
--  Appropriate Expression_Kinds:
--      A_Type_Conversion
--      A_Qualified_Expression
--
--  Returns Expression_Kinds:
--      An_Identifier
--      A_Selected_Component
--      An_Attribute_Reference
--

-------------------------------------------------------------------------------
--  17.37 function Converted_Or_Qualified_Expression
-------------------------------------------------------------------------------

   function Converted_Or_Qualified_Expression
                   (Expression : in Asis.Expression)
                       return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies the type conversion or qualified expression to
--  query
--
--  Returns the expression being converted or qualified.
--
--  Appropriate Expression_Kinds:
--      A_Type_Conversion
--      A_Qualified_Expression
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  17.38 function Allocator_Subtype_Indication
-------------------------------------------------------------------------------

   function Allocator_Subtype_Indication (Expression : in Asis.Expression)
                                           return Asis.Subtype_Indication;

-------------------------------------------------------------------------------
--  Expression  - Specifies the allocator expression to query
--
--  Returns the subtype indication for the object being allocated.
--
--  Appropriate Expression_Kinds:
--      An_Allocation_From_Subtype
--
--  Returns Definition_Kinds:
--      A_Subtype_Indication
--
-------------------------------------------------------------------------------
--  17.39 function Allocator_Qualified_Expression
-------------------------------------------------------------------------------

   function Allocator_Qualified_Expression (Expression : in Asis.Expression)
                                             return Asis.Expression;

-------------------------------------------------------------------------------
--  Expression  - Specifies the allocator expression to query
--
--  Returns the qualified expression for the object being allocated.
--
--  Appropriate Expression_Kinds:
--      An_Allocation_From_Qualified_Expression
--
--  Returns Expression_Kinds:
--      A_Qualified_Expression
--



-------------------------------------------------------------------------------

end Asis.Expressions;



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
