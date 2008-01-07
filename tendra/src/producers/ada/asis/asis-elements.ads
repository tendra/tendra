-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  13 package Asis.Elements
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package Asis.Elements is
--   pragma Preelaborate;

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Elements encapsulates a set of queries that operate on all elements
--  and some queries specific to A_Pragma elements.
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  13.1 function Unit_Declaration
-------------------------------------------------------------------------------
--  Gateway queries between Compilation_Units and Elements.
-------------------------------------------------------------------------------

   function Unit_Declaration (Compilation_Unit : in Asis.Compilation_Unit)
                             return Asis.Declaration;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit to query
--
--  Returns the element representing the declaration of the compilation_unit.
--
--  Returns a Nil_Element if the unit is A_Nonexistent_Declaration,
--  A_Nonexistent_Body, A_Configuration_Compilation, or An_Unknown_Unit.
--
--  All Unit_Kinds are appropriate except Not_A_Unit.
--
--  Returns Declaration_Kinds:
--       Not_A_Declaration
--       A_Function_Body_Declaration
--       A_Function_Declaration
--       A_Function_Instantiation
--       A_Generic_Function_Declaration
--       A_Generic_Package_Declaration
--       A_Generic_Procedure_Declaration
--       A_Package_Body_Declaration
--       A_Package_Declaration
--       A_Package_Instantiation
--       A_Procedure_Body_Declaration
--       A_Procedure_Declaration
--       A_Procedure_Instantiation
--       A_Task_Body_Declaration
--       A_Package_Renaming_Declaration
--       A_Procedure_Renaming_Declaration
--       A_Function_Renaming_Declaration
--       A_Generic_Package_Renaming_Declaration
--       A_Generic_Procedure_Renaming_Declaration
--       A_Generic_Function_Renaming_Declaration
--       A_Protected_Body_Declaration
--
-------------------------------------------------------------------------------
--  13.2 function Enclosing_Compilation_Unit
-------------------------------------------------------------------------------

   function Enclosing_Compilation_Unit (Element : in Asis.Element)
                                       return Asis.Compilation_Unit;

-------------------------------------------------------------------------------
--  Element - Specifies an Element whose Compilation_Unit is desired
--
--  Returns the Compilation_Unit that contains the given Element.
--
--  Raises ASIS_Inappropriate_Element if the Element is a Nil_Element.
--

-------------------------------------------------------------------------------
--  13.3 function Context_Clause_Elements
-------------------------------------------------------------------------------

   function Context_Clause_Elements
               (Compilation_Unit : in Asis.Compilation_Unit;
                Include_Pragmas  : in Boolean := False)
               return Asis.Context_Clause_List;

-------------------------------------------------------------------------------
--  Compilation_Unit - Specifies the unit to query
--  Include_Pragmas  - Specifies whether pragmas are to be returned
--
--  Returns a list of with clauses, use clauses, and pragmas that explicitly
--  appear in the context clause of the compilation unit, in their order of
--  appearance.
--
--  Returns a Nil_Element_List if the unit has A_Nonexistent_Declaration,
--  A_Nonexistent_Body, or An_Unknown_Unit Unit_Kind.
--
--  |IR Implementation Requirement:
--  |IR
--  |IR All pragma Elaborate elements for this unit will appear in this list.
--  |IR Other pragmas will appear in this list, or in the Compilation_Pragmas
--  |IR list, or both.
--
--  |IP Implementation Permissions:
--  |IP
--  |IP Implementors are encouraged to use this list to return all pragmas
--  |IP whose full effect is determined by their exact textual position.
--  |IP Pragmas that do not have placement dependencies may be returned in
--  |IP either list.  Only pragmas that appear in the unit's context clause
--  |IP are returned by this query.  All other pragmas, affecting the
--  |IP compilation of this unit, are available from the Compilation_Pragmas
--  |IP query.
--
--  Ada predefined packages, such as package Standard, may or may not have
--  context-clause elements available for processing by applications.  The
--  physical existence of a package Standard is implementation specific.
--  The same is true for other Ada predefined packages, such as Ada.Text_Io and
--  Ada.Direct_Io.  The Origin query can be used to determine whether or not
--  a particular unit is an Ada Predefined unit.
--
--  |IP Implementation Permissions:
--  |IP
--  |IP Results of this query may vary across ASIS implementations.  Some
--  |IP implementations normalize all multi-name with clauses and use clauses
--  |IP into an equivalent sequence of single-name with clause and use clauses.
--  |IP Similarly, an implementation may retain only a single reference to
--  |IP a name that appeared more than once in the original context clause.
--  |IP Some implementors will return only pragma
--  |IP Elaborate elements in this list and return all other pragmas via the
--  |IP Compilation_Pragmas query.
--
--  All Unit_Kinds are appropriate except Not_A_Unit.
--
--  Returns Element_Kinds:
--       A_Pragma
--       A_Clause
--
--  Returns Clause_Kinds:
--       A_With_Clause
--       A_Use_Package_Clause
--
-------------------------------------------------------------------------------
--  13.4 function Configuration_Pragmas
-------------------------------------------------------------------------------

   function Configuration_Pragmas (The_Context : in Asis.Context)
                                return Asis.Pragma_Element_List;

-------------------------------------------------------------------------------
--  The_Context    - Specifies the Context to query
--
--  Returns a list of pragmas that apply to all future compilation_unit
--  elements compiled into The_Context.  Pragmas returned by this query should
--  have appeared in a compilation that had no compilation_unit elements.
--  To the extent that order is meaningful, the pragmas should be in
--  their order of appearance in the compilation.  (The order is implementation
--  dependent, many pragmas have the same effect regardless of order.)
--
--  Returns a Nil_Element_List if there are no such configuration pragmas.
--
--  Returns Element_Kinds:
--       A_Pragma
--
-------------------------------------------------------------------------------
--  13.5 function Compilation_Pragmas
-------------------------------------------------------------------------------

   function Compilation_Pragmas (Compilation_Unit : in Asis.Compilation_Unit)
                                return Asis.Pragma_Element_List;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit to query
--
--  Returns a list of pragmas that apply to the compilation of the unit.
--  To the extent that order is meaningful, the pragmas should be in
--  their order of appearance in the compilation.  (The order is implementation
--  dependent, many pragmas have the same effect regardless of order.)
--
--  There are two sources for the pragmas that appear in this list:
--
--  - Program unit pragmas appearing at the place of a compilation_unit.
--    See Reference Manual 10.1.5(4).
--
--  - Configuration pragmas appearing before the first
--    compilation_unit of a compilation.  See Reference Manual 10.1.5(8).
--
--  This query does not return Elaborate pragmas from the unit context
--  clause of the compilation unit; they do not apply to the compilation,
--  only to the unit.
--
--  Use the Context_Clause_Elements query to obtain a list of all pragmas
--  (including Elaborate pragmas) from the context clause of a compilation
--  unit.
--
--  Pragmas from this query may be duplicates of some or all of the
--  non-Elaborate pragmas available from the Context_Clause_Elements query.
--  Such duplication is simply the result of the textual position of the
--  pragma--globally effective pragmas may appear textually within the context
--  clause of a particular unit, and be returned as part of the Context_Clause
--  for that unit.
--
--  Ada predefined packages, such as package Standard, may or may not have
--  pragmas available for processing by applications.  The physical
--  existence of a package Standard is implementation specific.  The same
--  is true for other Ada predefined packages, such as Ada.Text_Io and
--  Ada.Direct_Io. The Origin query can be used to determine whether or
--  not a particular unit is an Ada Predefined unit.
--
--  Returns a Nil_Element_List if the compilation unit:
--
--  - has no such applicable pragmas.
--
--  - is an An_Unknown_Unit, A_Nonexistent_Declaration, or A_Nonexistent_Body.
--
--  All Unit_Kinds are appropriate except Not_A_Unit.
--
--  Returns Element_Kinds:
--       A_Pragma
--

-------------------------------------------------------------------------------
--  Element_Kinds Hierarchy
--
--         Element_Kinds Value      Subordinate Kinds
-------------------------------------------------------------------------------
--
--    Key: Read "->" as "can be further categorized by its"
--
--         A_Pragma              -> Pragma_Kinds
--
--         A_Defining_Name       -> Defining_Name_Kinds
--                                          -> Operator_Kinds
--
--         A_Declaration         -> Declaration_Kinds
--                                          -> Declaration_Origin
--                                          -> Mode_Kinds
--                                          -> Subprogram_Default_Kinds
--
--         A_Definition          -> Definition_Kinds
--                                          -> Trait_Kinds
--                                          -> Type_Kinds
--                                          -> Formal_Type_Kinds
--                                              -> Access_Type_Kinds
--                                              -> Root_Type_Kinds
--                                          -> Constraint_Kinds
--                                          -> Discrete_Range_Kinds
--
--         An_Expression         -> Expression_Kinds
--                                          -> Operator_Kinds
--                                          -> Attribute_Kinds
--
--         An_Association        -> Association_Kinds
--
--         A_Statement           -> Statement_Kinds
--
--         A_Path                -> Path_Kinds
--
--         A_Clause              -> Clause_Kinds
--                                          -> Representation_Clause_Kinds
--
--         An_Exception_Handler
--
-------------------------------------------------------------------------------
--  13.6 function Element_Kind
-------------------------------------------------------------------------------

   function Element_Kind (Element : in Asis.Element)
                          return Asis.Element_Kinds;

-------------------------------------------------------------------------------
--  Element - Specifies the element to query
--
--  Returns the Element_Kinds value of Element.
--  Returns Not_An_Element for a Nil_Element.
--
--  All element kinds are expected.
--
-------------------------------------------------------------------------------
--  13.7 function Pragma_Kind
-------------------------------------------------------------------------------
   function Pragma_Kind (Pragma_Element : in Asis.Pragma_Element)
                        return Asis.Pragma_Kinds;

-------------------------------------------------------------------------------
--  Pragma_Element  - Specifies the element to query
--
--  Returns the Pragma_Kinds value of Pragma_Element.
--  Returns Not_A_Pragma for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Element_Kinds:
--       A_Pragma
--
-------------------------------------------------------------------------------
--  13.8 function Defining_Name_Kind
-------------------------------------------------------------------------------

   function Defining_Name_Kind (Defining_Name : in Asis.Defining_Name)
                               return Asis.Defining_Name_Kinds;

-------------------------------------------------------------------------------
--  Defining_Name   - Specifies the element to query
--
--  Returns the Defining_Name_Kinds value of the Defining_Name.
--
--  Returns Not_A_Defining_Name for any unexpected element such as a
--  Nil_Element, A_Clause, or A_Statement.
--
--  Expected Element_Kinds:
--       A_Defining_Name
--
-------------------------------------------------------------------------------
--  13.9 function Declaration_Kind
-------------------------------------------------------------------------------

   function Declaration_Kind (Declaration : in Asis.Declaration)
                             return Asis.Declaration_Kinds;

-------------------------------------------------------------------------------
--  Declaration   - Specifies the element to query
--
--  Returns the Declaration_Kinds value of the Declaration.
--
--  Returns Not_A_Declaration for any unexpected element such as a
--  Nil_Element, A_Definition, or A_Statement.
--
--  Expected Element_Kinds:
--       A_Declaration
--
-------------------------------------------------------------------------------
--  13.10 function Trait_Kind
-------------------------------------------------------------------------------

   function Trait_Kind (Element : in Asis.Element)
                       return Asis.Trait_Kinds;

-------------------------------------------------------------------------------
--  Element   - Specifies the Element to query
--
--  Returns the Trait_Kinds value of the Element.
--
--  Returns Not_A_Trait for any unexpected element such as a
--  Nil_Element, A_Statement, or An_Expression.
--
--  Expected Declaration_Kinds:
--      A_Private_Type_Declaration
--      A_Private_Extension_Declaration
--      A_Variable_Declaration
--      A_Constant_Declaration
--      A_Deferred_Constant_Declaration
--      A_Discriminant_Specification
--      A_Loop_Parameter_Specification
--      A_Procedure_Declaration
--      A_Function_Declaration
--      A_Parameter_Specification
--
--  Expected Definition_Kinds:
--      A_Component_Definition
--      A_Private_Type_Definition
--      A_Tagged_Private_Type_Definition
--      A_Private_Extension_Definition
--

--  Expected Type_Kinds:
--      A_Derived_Type_Definition
--      A_Derived_Record_Extension_Definition
--      A_Record_Type_Definition
--      A_Tagged_Record_Type_Definition
--
--  Expected Formal_Type_Kinds:
--      A_Formal_Private_Type_Definition
--      A_Formal_Tagged_Private_Type_Definition
--      A_Formal_Derived_Type_Definition
--
-------------------------------------------------------------------------------
--  13.11 function Declaration_Origin
-------------------------------------------------------------------------------

   function Declaration_Origin (Declaration : in Asis.Declaration)
                               return Asis.Declaration_Origins;

-------------------------------------------------------------------------------
--  Declaration   - Specifies the Declaration to query
--
--  Returns the Declaration_Origins value of the Declaration.
--
--  Returns Not_A_Declaration_Origin for any unexpected element such as a
--  Nil_Element, A_Definition, or A_Clause.
--
--  Expected Element_Kinds:
--       A_Declaration
--
-------------------------------------------------------------------------------
--  13.12 function Mode_Kind
-------------------------------------------------------------------------------

   function Mode_Kind (Declaration : in Asis.Declaration)
                                return Asis.Mode_Kinds;

-------------------------------------------------------------------------------
--  Declaration   - Specifies the element to query
--
--  Returns the Mode_Kinds value of the Declaration.
--
--  Returns A_Default_In_Mode for an access parameter.
--
--  Returns Not_A_Mode for any unexpected element such as a
--  Nil_Element, A_Definition, or A_Statement.
--
--  Expected Declaration_Kinds:
--       A_Parameter_Specification
--       A_Formal_Object_Declaration
--
-------------------------------------------------------------------------------
--  13.13 function Default_Kind
-------------------------------------------------------------------------------

   function Default_Kind (Declaration : in Asis.Generic_Formal_Parameter)
                         return Asis.Subprogram_Default_Kinds;

-------------------------------------------------------------------------------
--  Declaration   - Specifies the element to query
--
--  Returns the Subprogram_Default_Kinds value of the Declaration.
--
--  Returns Not_A_Default for any unexpected element such as a
--  Nil_Element, A_Definition, or A_Statement.
--
--  Expected Declaration_Kinds:
--       A_Formal_Function_Declaration
--       A_Formal_Procedure_Declaration
--

-------------------------------------------------------------------------------
--  13.14 function Definition_Kind
-------------------------------------------------------------------------------

   function Definition_Kind (Definition : in Asis.Definition)
                            return Asis.Definition_Kinds;

-------------------------------------------------------------------------------
--  Definition   - Specifies the Definition to query
--
--  Returns the Definition_Kinds value of the Definition.
--
--  Returns Not_A_Definition for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Element_Kinds:
--       A_Definition
--
-------------------------------------------------------------------------------
--  13.15 function Type_Kind
-------------------------------------------------------------------------------

   function Type_Kind (Definition : in Asis.Type_Definition)
                                 return Asis.Type_Kinds;

-------------------------------------------------------------------------------
--  Definition   - Specifies the Type_Definition to query
--
--  Returns the Type_Kinds value of the Definition.
--
--  Returns Not_A_Type_Definition for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Definition_Kinds:
--       A_Type_Definition
--
-------------------------------------------------------------------------------
--  13.16 function Formal_Type_Kind
-------------------------------------------------------------------------------

   function Formal_Type_Kind
                (Definition : in Asis.Formal_Type_Definition)
                 return Asis.Formal_Type_Kinds;

-------------------------------------------------------------------------------
--  Definition   - Specifies the Formal_Type_Definition to query
--
--  Returns the Formal_Type_Kinds value of the Definition.
--
--  Returns Not_A_Formal_Type_Definition for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Definition_Kinds:
--       A_Formal_Type_Definition
--
-------------------------------------------------------------------------------
--  13.17 function Access_Type_Kind
-------------------------------------------------------------------------------

   function Access_Type_Kind
                (Definition : in Asis.Access_Type_Definition)
                 return Asis.Access_Type_Kinds;

-------------------------------------------------------------------------------
--  Definition   - Specifies the Access_Type_Definition to query
--
--  Returns the Access_Type_Kinds value of the Definition.
--
--  Returns Not_An_Access_Type_Definition for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Type_Kinds:
--       An_Access_Type_Definition
--
-------------------------------------------------------------------------------
--  13.xx function Interface_Kind
-------------------------------------------------------------------------------

   function Interface_Kind
     (Definition : Asis.Definition)
      return Asis.Interface_Kinds;

-------------------------------------------------------------------------------
--  Definition   - Specifies the Definition to query.
--
--  Returns the Interface_Kinds value of the Definition.
--
--  Returns Not_An_Interface for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Definition_Kinds:
--     A_Type_Definition
--     A_Formal_Type_Definition
--
--  Expected Type_Kinds:
--     An_Interface_Type_Definition
--
--  Expected Formal_Type_Kinds:
--     A_Formal_Interface_Type_Definition
--
-------------------------------------------------------------------------------
--  13.xx function Access_Definition_Kind
-------------------------------------------------------------------------------

   function Access_Definition_Kind      -- 3.3.1(2) / 3.10(6)
     (Definition : Asis.Definition)
      return Asis.Access_Definition_Kinds;

-------------------------------------------------------------------------------
--  Definition - Specifies the Definition to query.
--
--  Returns the Access_Definition_Kinds value of the Definition.
--
--  Returns Not_An_Access_Definition for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Definition_Kinds:
--     An_Access_Definition
--
-------------------------------------------------------------------------------
--  13.xx function Has_Null_Exclusion
-------------------------------------------------------------------------------

   function Has_Null_Exclusion  -- 3.2.2(3/2), 3.7(5/2), 3.10 (2/2,6/2),
     (Element : Asis.Element)   -- 6.1(13/2,15/2), 8.5.1(2/2), 12.4(2/2)
      return Boolean;

-------------------------------------------------------------------------------
--  Element - Specifies the element to check.
--
--  Checks if the argument element has a null_exclusion specifier.
--
--  Returns False for any unexpected element such as a Nil_Element,
--  A_Statement or A_Clause.
--
--  Expected Definition_Kinds:
--     A_Type_Definition
--     An_Access_Definition
--     A_Subtype_Indication
--
--  Expected Type_Kinds:
--     An_Access_Type_Definition
--
--  Expected Declaration_Kinds:
--     A_Discriminant_Specification
--     A_Parameter_Specification
--     A_Formal_Object_Declaration
--     An_Object_Renaming_Declaration
--
-------------------------------------------------------------------------------
--  13.18 function Root_Type_Kind
-------------------------------------------------------------------------------

   function Root_Type_Kind
                (Definition : in Asis.Root_Type_Definition)
                 return Asis.Root_Type_Kinds;

-------------------------------------------------------------------------------
--  Definition   - Specifies the Root_Type_Definition to query
--
--  Returns the Root_Type_Kinds value of the Definition.
--
--  Returns Not_A_Root_Type_Definition for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Type_Kinds:
--       A_Root_Type_Definition
--
-------------------------------------------------------------------------------
--  13.19 function Constraint_Kind
-------------------------------------------------------------------------------

   function Constraint_Kind
                (Definition : in Asis.Constraint)
                 return Asis.Constraint_Kinds;

-------------------------------------------------------------------------------
--  Definition   - Specifies the constraint to query
--
--  Returns the Constraint_Kinds value of the Definition.
--
--  Returns Not_A_Constraint for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Definition_Kinds:
--       A_Constraint
--
-------------------------------------------------------------------------------
--  13.20 function Discrete_Range_Kind
-------------------------------------------------------------------------------

   function Discrete_Range_Kind
                (Definition : in Asis.Discrete_Range)
                 return Asis.Discrete_Range_Kinds;

-------------------------------------------------------------------------------
--  Definition   - Specifies the discrete_range to query
--
--  Returns the Discrete_Range_Kinds value of the Definition.
--
--  Returns Not_A_Discrete_Range for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Definition_Kinds:
--       A_Discrete_Subtype_Definition
--       A_Discrete_Range
--

-------------------------------------------------------------------------------
--  13.21 function Expression_Kind
-------------------------------------------------------------------------------

   function Expression_Kind (Expression : in Asis.Expression)
                            return Asis.Expression_Kinds;

-------------------------------------------------------------------------------
--  Expression   - Specifies the Expression to query
--
--  Returns the Expression_Kinds value of the Expression.
--
--  Returns Not_An_Expression for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Element_Kinds:
--       An_Expression
--
-------------------------------------------------------------------------------
--  13.22 function Operator_Kind
-------------------------------------------------------------------------------

   function Operator_Kind (Element : in Asis.Element)
                          return Asis.Operator_Kinds;

-------------------------------------------------------------------------------
--  Element   - Specifies the Element to query
--
--  Returns the Operator_Kinds value of the A_Defining_Name or An_Expression
--  element.
--
--  Returns Not_An_Operator for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Defining_Name_Kinds:
--       A_Defining_Operator_Symbol
--
--  Expected Expression_Kinds:
--       An_Operator_Symbol
--
-------------------------------------------------------------------------------
--  13.23 function Attribute_Kind
-------------------------------------------------------------------------------

   function Attribute_Kind (Expression : in Asis.Expression)
                           return Asis.Attribute_Kinds;

-------------------------------------------------------------------------------
--  Expression   - Specifies the Expression to query
--
--  Returns the Attribute_Kinds value of the Expression.
--
--  Returns Not_An_Attribute for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Expression_Kinds:
--       An_Attribute_Reference
--
-------------------------------------------------------------------------------
--  13.24 function Association_Kind
-------------------------------------------------------------------------------

   function Association_Kind (Association : in Asis.Association)
                             return Asis.Association_Kinds;

-------------------------------------------------------------------------------
--  Association   - Specifies the Association to query
--
--  Returns the Association_Kinds value of the Association.
--

--  Returns Not_An_Association for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Element_Kinds:
--       An_Association
--
-------------------------------------------------------------------------------
--  13.25 function Statement_Kind
-------------------------------------------------------------------------------

   function Statement_Kind (Statement : in Asis.Statement)
                           return Asis.Statement_Kinds;

-------------------------------------------------------------------------------
--  Statement   - Specifies the element to query
--
--  Returns the Statement_Kinds value of the statement.
--
--  Returns Not_A_Statement for any unexpected element such as a
--  Nil_Element, A_Definition, or A_Declaration.
--
--  Expected Element_Kinds:
--       A_Statement
--
-------------------------------------------------------------------------------
--  13.26 function Path_Kind
-------------------------------------------------------------------------------

   function Path_Kind (Path : in Asis.Path) return Asis.Path_Kinds;

-------------------------------------------------------------------------------
--  Path   - Specifies the Path to query
--
--  Returns the Path_Kinds value of the Path.
--
--  Returns Not_A_Path for any unexpected element such as a
--  Nil_Element, A_Statement, or A_Declaration.
--
--  Expected Element_Kinds:
--       A_Path
--
-------------------------------------------------------------------------------
--  13.27 function Clause_Kind
-------------------------------------------------------------------------------

   function Clause_Kind (Clause : in Asis.Clause)
                        return Asis.Clause_Kinds;

-------------------------------------------------------------------------------
--  Clause   - Specifies the element to query
--
--  Returns the Clause_Kinds value of the Clause.
--
--  Returns Not_A_Clause for any unexpected element such as a
--  Nil_Element, A_Definition, or A_Declaration.
--
--  Expected Element_Kinds:
--       A_Clause
--
-------------------------------------------------------------------------------
--  13.28 function Representation_Clause_Kind
-------------------------------------------------------------------------------

   function Representation_Clause_Kind
                (Clause : in Asis.Representation_Clause)
                 return Asis.Representation_Clause_Kinds;

-------------------------------------------------------------------------------
--  Clause   - Specifies the element to query
--
--  Returns the Representation_Clause_Kinds value of the Clause.
--
--  Returns Not_A_Representation_Clause for any unexpected element such as a
--  Nil_Element, A_Definition, or A_Declaration.
--
--  Expected Clause_Kinds:
--       A_Representation_Clause
--
-------------------------------------------------------------------------------
--  13.xx function Has_Limited
-------------------------------------------------------------------------------

   function Has_Limited (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element specifies the Element to query.
--
--  Returns True if the reserved word Limited appears in the Element.
--
--  Returns True for declarations explicitly defined as limited, limited
--  private, abstract limited, or abstract limited private.
--
--  Returns True for context clauses qualified as limited.
--
--  Expected Element_Kinds:
--    A_Declaration
--    A_Definition
--    A_Clause
--
--  Expected Declaration_Kinds:
--    A_Type_Declaration
--    A_Private_Type_Declaration
--    A_Private_Extension_Declaration
--
--  Expected Definition_Kinds:
--    A_Type_Definition
--    A_Private_Type_Definition
--    A_Tagged_Private_Type_Definition
--    A_Private_Extension_Definition
--    An_Interface_Type_Definition
--    A_Tagged_Record_Type_Definition          (Added by Gela)
--    A_Record_Type_Definition                 (Added by Gela)
--    A_Derived_Type_Definition                (Added by Gela)
--    A_Derived_Record_Extension_Definition    (Added by Gela)
--
--  Expected Formal_Type_Kinds:
--    A_Formal_Private_Type_Definition
--    A_Formal_Tagged_Private_Type_Definition
--    A_Formal_Derived_Type_Definition
---   A_Formal_Interface_Type_Definition       (Added by Gela)
--
--  Expected Clause_Kinds:
--    A_With_Clause
--
--  Returns False for any other element, including a Nil_Element.
--
-------------------------------------------------------------------------------
--  13.xx function Has_Private
-------------------------------------------------------------------------------

   function Has_Private (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element specifies the element to query.
--
--  Returns True if the reserved word Private appears in the Element.
--
--  Returns True for declarations explicitly defined as private, limited
--  private, abstract private,
--  and abstract limited private.
--
--  Returns True for a context clause qualified as private.
--
--  Returns False for any unexpected Element_Kind, including a Nil_Element.
--
--  Expected Declaration_Kinds:
--    A_Type_Declaration
--    A_Private_Type_Declaration
--
--  Expected Definition_Kinds:
--    A_Type_Definition
--    A_Private_Type_Definition
--    A_Tagged_Private_Type_Definition
--    A_Private_Extension_Definition
--
--  Expected Formal_Type_Kinds:
--    A_Formal_Private_Type_Definition
--    A_Formal_Tagged_Private_Type_Definition
--    A_Formal_Derived_Type_Definition (Added by Gela)
--
--  Expected Clause_Kinds:
--    A_With_Clause
--
--  Returns False for any other Element including a Nil_Element.
--
-------------------------------------------------------------------------------
--  13.xx function Has_Abstract
-------------------------------------------------------------------------------

   function Has_Abstract (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element specifies the element to query.
--
--  Returns True if the reserved word Abstract appears in the Element.
--
--  Expected Declaration_Kinds:
--    A_Type_Declaration
--    A_Private_Type_Declaration
--    A_Private_Extension_Declaration
--    A_Procedure_Declaration
--    A_Function_Declaration
--
--  Expected Definition_Kinds:
--    A_Type_Definition
--    A_Private_Type_Definition                (Gela: couldn't be abstract)
--    A_Tagged_Private_Type_Definition
--    A_Private_Extension_Definition
--    An_Interface_Type_Definition             (Gela: couldn't have abstract)
--    A_Tagged_Record_Type_Definition          (Added by Gela)
--    A_Derived_Type_Definition                (Added by Gela)
--    A_Derived_Record_Extension_Definition    (Added by Gela)
--
--  Expected Formal_Type_Kinds:
--    A_Formal_Private_Type_Definition         (Gela: couldn't have abstract)
--    A_Formal_Tagged_Private_Type_Definition
--    A_Formal_Derived_Type_Definition
--
--
--  Returns False for any other element, including a Nil_Element.
--
-------------------------------------------------------------------------------
--  13.xx function Has_Reverse
-------------------------------------------------------------------------------

   function Has_Reverse (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element specifies the Element to query.
--
--  Returns True if the reserved word Reverse appears in the Element.
--
--  Expected Declaration_Kinds:
--    A_Loop_Parameter_Specification
--
--  Returns False for any other Element including a Nil_Element.
--
-------------------------------------------------------------------------------
--  13.xx function Has_Aliased
-------------------------------------------------------------------------------

   function Has_Aliased (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element specifies the Element to query.
--
--  Returns True if the reserved word Aliased appears in the element.
--
--  Expected Declaration_Kinds:
--    A_Variable_Declaration
--    A_Constant_Declaration
--    A_Deferred_Constant_Declaration
--    A_Return_Object_Specification
--
--  Expected Definition_Kinds:
--    A_Component_Definition
--
--  Returns False for any other Element, including a Nil_Element.
--
-------------------------------------------------------------------------------
--  13.xx function Has_Synchronized
-------------------------------------------------------------------------------

   function Has_Synchronized (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element specifies the Element to query.
--
--  Returns true if the reserved word Synchronized appears in the
--  element.
--
--  Expected Definition_Kinds:
--    A_Private_Extension_Definition
--    An_Interface_Type_Definition
--    A_Formal_Derived_Type_Definition (Added by Gela)
--
--  Returns False for any other Element including a Nil_Element.
--
-------------------------------------------------------------------------------
--  13.xx function Has_Protected
-------------------------------------------------------------------------------

   function Has_Protected (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element specifies the Element to query.
--
--  Returns true if the reserved word Protected appears in the element.
--
--  Expected Definition_Kinds:
--    An_Interface_Type_Definition
--    A_Protected_Definition
--
--  Expected Declaration_Kinds
--    A_Protected_Type_Declaration
--    A_Single_Protected_Declaration
--    A_Protected_Body_Declaration
--
--  Returns False for any other Element including a Nil_Element.
--
-------------------------------------------------------------------------------
--  13.xx function Has_Task
-------------------------------------------------------------------------------

   function Has_Task (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element specifies the Element to query.
--
--  Returns true if the reserved word Task appears in the element.
--
--  Expected Definition_Kinds:
--    An_Interface_Type_Definition
--    A_Task_Definition
--
--  Expected Declaration_Kinds
--    A_Task_Type_Declaration
--    A_Single_task_Declaration
--    A_Task_Body_Declaration
--
--  Returns False for any other Element including a Nil_Element.
--
-------------------------------------------------------------------------------
-- 13.xx function Is_Null_Procedure
-------------------------------------------------------------------------------

   function Is_Null_Procedure (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element specifies the element to query.
--
--  Returns True for a declaration of a procedure or formal procedure that is
--  declared as null.
--
--  Returns False for any other Element including a Nil_Element.
--
--  Expected Element_Kinds:
--    A_Declaration
--
--  Expected Declaration_Kinds:
--    A_Procedure_Declaration
--    A_Formal_Procedure_Declaration
--
-------------------------------------------------------------------------------
-- 13.xx function Is_Abstract_Subprogram
-------------------------------------------------------------------------------

   function Is_Abstract_Subprogram (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element specifies the element to query.
--
--  Returns True for a declaration of a subprogram or formal subprogram that
--  is declared as abstract.
--
--  Returns False for any other Element including a Nil_Element.
--
--  Expected Element_Kinds:
--    A_Declaration
--
--  Expected Declaration_Kinds:
--    A_Procedure_Declaration
--    A_Function_Declaration
--    A_Formal_Procedure_Declaration
--    A_Formal_Function_Declaration
--
-------------------------------------------------------------------------------
--  13.29 function Is_Nil
-------------------------------------------------------------------------------

   function Is_Nil (Right : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Right   - Specifies the element to check
--
--  Returns True if the program element is the Nil_Element.
--
-------------------------------------------------------------------------------
--  13.30 function Is_Nil
-------------------------------------------------------------------------------

   function Is_Nil (Right : in Asis.Element_List) return Boolean;

-------------------------------------------------------------------------------
--  Right   - Specifies the element list to check
--
--  Returns True if the element list has a length of zero.
--
-------------------------------------------------------------------------------
--  13.31 function Is_Equal
-------------------------------------------------------------------------------

   function Is_Equal (Left  : in Asis.Element;
                      Right : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Left    - Specifies the left element to compare
--  Right   - Specifies the right element to compare
--
--  Returns True if Left and Right represent the same physical element,
--  from the same physical compilation unit.  The two elements may or
--  may not be from the same open ASIS Context variable.
--
--  Implies:
--
--       Is_Equal (Enclosing_Compilation_Unit (Left),
--                 Enclosing_Compilation_Unit (Right)) = True
--
-------------------------------------------------------------------------------
--  13.32 function Is_Identical
-------------------------------------------------------------------------------

   function Is_Identical (Left  : in Asis.Element;
                          Right : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Left    - Specifies the left element
--  Right   - Specifies the right element
--
--  Returns True if Left and Right represent the same physical element,
--  from the same physical compilation unit, from the same open ASIS
--  Context variable.
--
--  Implies:
--
--       Is_Identical (Enclosing_Compilation_Unit (Left),
--                     Enclosing_Compilation_Unit (Right)) = True
--

-------------------------------------------------------------------------------
--  13.33 function Is_Part_Of_Implicit
-------------------------------------------------------------------------------

   function Is_Part_Of_Implicit (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element - Specifies the element to query
--
--  Returns True for any Element that is, or that forms part of, any
--  implicitly declared or specified program Element structure.
--
--  Returns True for any implicit generic child unit specifications or their
--  subcomponents. Reference Manual 10.1.1(19).
--
--  Returns False for a Nil_Element, or any Element that correspond to text
--  which was specified explicitly (typed, entered, written).
--
--  Generic instance specifications and bodies, while implicit, are treated
--  as a special case.  These elements will not normally test as
--  Is_Part_Of_Implicit.  Rather, they are Is_Part_Of_Instance.  They only test
--  as Is_Part_Of_Implicit if one of the following rules applies.  This is
--  done so that it is possible to determine whether a declaration, which
--  happens to occur within an instance, is an implicit result of
--  another declaration which occurs explicitly within the generic template.
--
--  Implicit Elements are those that represent these portions of the Ada
--  language:
--
--  - Reference Manual 4.5.(9)
--
--    o All predefined operator declarations and their component elements are
--      Is_Part_Of_Implicit
--
--  - Reference Manual 3.4(16)
--
--    o Implicit predefined operators of the derived type.
--
--  - Reference Manual 3.4(17-22)
--
--    o Implicit inherited subprogram declarations and their component elements
--      are Is_Part_Of_Implicit
--
--  - Reference Manual 6.4(9) and 12.3(7)
--
--    o Implicit actual parameter expressions (defaults).
--
--    o The A_Parameter_Association that includes a defaulted parameter value
--      Is_Normalized and also Is_Part_Of_Implicit.  The Formal_Parameter and
--      the Actual_Parameter values from such Associations are not
--      Is_Part_Of_Implicit unless they are from default initializations for an
--      inherited subprogram declaration and have an Enclosing_Element that is
--      the parameter specification of the subprogram declaration. (Those
--      elements are shared with (were created by) the original subprogram
--      declaration, or they are naming expressions representing the actual
--      generic subprogram selected at the place of an instantiation for
--      A_Box_Default.)
--
--    o All A_Parameter_Association Kinds from a Normalized list are
--      Is_Part_Of_Implicit.
--
--  - Reference Manual 6.6 (6)
--
--    o Inequality operator declarations for limited private types are
--      Is_Part_Of_Implicit.
--
--    o Depending on the ASIS implementation, a "/=" appearing in the
--      compilation may result in a "NOT" and an "=" in the internal
--      representation.  These two elements test as Is_Part_Of_Implicit
--      because they do not represent text from the original compilation
--      text.
--
--  - Reference Manual 12.3 (16)
--
--    o implicit generic instance specifications and bodies are not
--      Is_Part_Of_Implicit; they are Is_Part_Of_Instance and are only
--      implicit if some other rule makes them so.
--

-------------------------------------------------------------------------------
--  13.34 function Is_Part_Of_Inherited
-------------------------------------------------------------------------------

   function Is_Part_Of_Inherited (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element - Specifies the element to query
--
--  Returns True for any Element that is, or that forms part of, an
--  inherited primitive subprogram declaration.
--
--  Returns False for any other Element including a Nil_Element.
--
-------------------------------------------------------------------------------
--  13.35 function Is_Part_Of_Instance
-------------------------------------------------------------------------------

   function Is_Part_Of_Instance (Element : in Asis.Element) return Boolean;

-------------------------------------------------------------------------------
--  Element - Specifies the element to test
--
--  Returns True if the Element is part of an implicit generic specification
--  instance or an implicit generic body instance.
--
--  Returns False for explicit, inherited, and predefined Elements that are
--  not the result of a generic expansion.
--
--  Returns False for any implicit generic child unit specifications or
--  their subcomponents. Reference Manual 10.1.1(19).
--
--  Returns False for a Nil_Element.
--
--  Instantiations are not themselves Is_Part_Of_Instance unless they are
--  encountered while traversing a generic instance.
--
-------------------------------------------------------------------------------
--  13.36 function Enclosing_Element
-------------------------------------------------------------------------------

   function Enclosing_Element (Element : in Asis.Element) return Asis.Element;

   function Enclosing_Element (Element                    : in Asis.Element;
                               Expected_Enclosing_Element : in Asis.Element)
                           return Asis.Element;

-------------------------------------------------------------------------------
--  Element - Specifies the element to query
--  Expected_Enclosing_Element - Specifies an enclosing element expected to
--  contain the element
--
--  Returns the Element that immediately encloses the given element.  This
--  query is intended to exactly reverse any single parent-to-child element
--  traversal.  For any structural query that returns a subcomponent of an
--  element (or that returns a list of subcomponent elements), the original
--  element can be determined by passing the subcomponent element to this
--  query.
--
--  |AN Application Note:
--  |AN
--  |AN Semantic queries (queries that test the meaning of a program rather
--  |AN than its structure) return Elements that usually do not have the
--  |AN original argument Element as their parent.
--

--  Returns a Nil_Element if:
--
--  - the element is the declaration part of a compilation unit
--    (Unit_Declaration).
--
--  - the element is with clause or use clause of a context clause
--    (Context_Clause_Elements).
--
--  - the element is a pragma for a compilation unit
--    (Compilation_Pragmas and Context_Clause_Elements).
--
--  Use Enclosing_Compilation_Unit to get the enclosing compilation unit for
--  any element value other than Nil_Element.
--
--  Raises ASIS_Inappropriate_Element if the Element is a Nil_Element.
--
--  Examples:
--
--  - Given a A_Declaration/A_Full_Type_Declaration in the declarative region
--    of a block statement, returns the A_Statement/A_Block_Statement Element
--    that encloses the type declaration.
--
--  - Given A_Statement, from the sequence of statements within a loop
--    statement, returns the enclosing A_Statement/A_Loop_Statement.
--
--  - Given the An_Expression/An_Identifier selector from an expanded name,
--    returns the An_Expression/A_Selected_Component that represents the
--    combination of the prefix, the dot, and the selector.
--
--  - Given the A_Declaration corresponding to the implicit redeclaration of
--    a child generic for an instantiated parent generic, returns the expanded
--    generic specific template from the parent generic instantiation
--    corresponding to any implicit generic child unit specification given as
--    an argument. Reference Manual 10.1.1(19).
--
--  |AN Application Note:
--  |AN
--  |AN The optional Expected_Enclosing_Element parameter is used only to opti-
--  |AN mizethis query.  This speed up is only present for ASIS implementations
--  |AN where the underlying implementor's environment does not have "parent
--  |AN pointers". For these implementations, this query is implemented as a
--  |AN "search". The Enclosing_Compilation_Unit is searched for the argument
--  |AN Element. The Expected_Enclosing_Element parameter provides a means of
--  |AN shortening the search.
--  |AN Note: If the argument Element is not a sub-element of the
--  |AN Expected_Enclosing_Element parameter, or if the
--  |AN Expected_Enclosing_Element is a Nil_Element, the result of the
--  |AN call is a Nil_Element.
--  |AN
--  |AN Implementations that do not require the Expected_Enclosing_Element
--  |AN parameter may ignore it.  They are encouraged, but not required, to
--  |AN testthe Expected_Enclosing_Element parameter and to determine if it
--  |AN is an invalid Element value (its associated Environment Context may
--  |AN be closed)
--  |AN
--  |AN Portable applications should not use the Expected_Enclosing_Element
--  |AN parameter since it can lead to unexpected differences when porting an
--  |AN application between ASIS implementations where one implementation uses
--  |AN the parameter and the other implementation does not.  Passing a "wrong"
--  |AN Expected_Enclosing_Element to an implementation that ignores it, is
--  |AN harmless. Passing a "wrong" Expected_Enclosing_Element to an
--  |AN implementation that may utilize it, can lead to an unexpected
--  |AN Nil_Element result.
--

-------------------------------------------------------------------------------
--  13.37 function Pragmas
-------------------------------------------------------------------------------

   function Pragmas (The_Element : in Asis.Element)
                    return Asis.Pragma_Element_List;

-------------------------------------------------------------------------------
--  The_Element - Specifies the element to query
--
--  Returns the list of pragmas, in their order of appearance, that appear
--  directly within the given The_Element.  Returns only those pragmas that are
--  immediate component elements of the given The_Element.  Pragmas embedded
--  within other component elements are not returned.  For example, returns
--  the pragmas in a package specification, in the statement list of a loop,
--  or in a record component list.
--
--  This query returns exactly those pragmas that are returned by the
--  various queries, that accept these same argument kinds, and that
--  return Declaration_List and Statement_List, where the inclusion of
--  Pragmas is controlled by an Include_Pragmas parameter.
--
--  Returns a Nil_Element_List if there are no pragmas.
--
--  Appropriate Element_Kinds:
--    A_Path                       (pragmas from the statement list +
--                                  pragmas immediately preceding the
--                                  reserved word "when" of the first
--                                  alternative)
--    An_Exception_Handler         (pragmas from the statement list + pragmas
--                                  immediately preceding the reserved word
--                                  "when" of the first exception handler)
--
--  Appropriate Declaration_Kinds:
--
--  A_Procedure_Body_Declaration (pragmas from declarative region + statements)
--  A_Function_Body_Declaration  (pragmas from declarative region + statements)
--  A_Package_Declaration        (pragmas from visible + private declarative
--                                regions)
--  A_Package_Body_Declaration   (pragmas from declarative region + statements)
--  A_Task_Body_Declaration      (pragmas from declarative region + statements)
--  A_Protected_Body_Declaration (pragmas from declarative region)
--  An_Entry_Body_Declaration    (pragmas from declarative region + statements)
--  A_Generic_Procedure_Declaration (pragmas from formal declarative region)
--  A_Generic_Function_Declaration  (pragmas from formal declarative region)
--  A_Generic_Package_Declaration   (pragmas from formal + visible +
--                                     private declarative regions)
--
--  Appropriate Definition_Kinds:
--    A_Record_Definition             (pragmas from the component list)
--    A_Variant_Part                  (pragmas immediately preceding the
--                                     first reserved word "when" + between
--                                     variants)
--    A_Variant                       (pragmas from the component list)
--    A_Task_Definition               (pragmas from visible + private
--                                     declarative regions)
--    A_Protected_Definition          (pragmas from visible + private
--                                     declarative regions)
--
--  Appropriate Statement_Kinds:
--    A_Loop_Statement           (pragmas from statement list)
--    A_While_Loop_Statement     (pragmas from statement list)
--    A_For_Loop_Statement       (pragmas from statement list)
--    A_Block_Statement          (pragmas from declarative region + statements)
--    An_Accept_Statement        (pragmas from statement list +
--
--  Appropriate Representation_Clause_Kinds:
--    A_Record_Representation_Clause  (pragmas from component specifications)
--
--  Returns Element_Kinds:
--    A_Pragma
--

-------------------------------------------------------------------------------
--  13.38 function Corresponding_Pragmas
-------------------------------------------------------------------------------

   function Corresponding_Pragmas (Element : in Asis.Element)
                                  return Asis.Pragma_Element_List;

-------------------------------------------------------------------------------
--  Element - Specifies the element to query
--
--  Returns the list of pragmas semantically associated with the given element,
--  in their order of appearance, or, in any order that does not affect their
--  relative interpretations.  These are pragmas that directly affect the
--  given element.  For example, a pragma Pack affects the type it names.
--
--  Returns a Nil_Element_List if there are no semantically associated pragmas.
--
--  |AN Application Note:
--  |AN
--  |AN If the argument is a inherited entry declaration from a derived task
--  |AN type, all pragmas returned are elements taken from the original task
--  |AN type's declarative item list.  Their Enclosing_Element is the original
--  |AN type definition and not the derived type definition.
--
--  Appropriate Element_Kinds:
--       A_Declaration
--       A_Statement
--
--  Returns Element_Kinds:
--       A_Pragma
--
-------------------------------------------------------------------------------
--  13.39 function Pragma_Name_Image
-------------------------------------------------------------------------------

   function Pragma_Name_Image
           (Pragma_Element : in Asis.Pragma_Element) return Program_Text;

-------------------------------------------------------------------------------
--  Pragma_Element  - Specifies the element to query
--
--  Returns the program text image of the simple name of the pragma.
--
--  The case of names returned by this query may vary between implementors.
--  Implementors are encouraged, but not required, to return names in the
--  same case as was used in the original compilation text.
--
--  Appropriate Element_Kinds:
--       A_Pragma
--
-------------------------------------------------------------------------------
--  13.40 function Pragma_Argument_Associations
-------------------------------------------------------------------------------

   function Pragma_Argument_Associations
           (Pragma_Element : in Asis.Pragma_Element)
               return Asis.Association_List;

-------------------------------------------------------------------------------
--  Pragma_Element - Specifies the element to query
--
--  Returns a list of the Pragma_Argument_Associations of the pragma, in their
--  order of appearance.
--
--  Appropriate Element_Kinds:
--       A_Pragma
--
--  Returns Element_Kinds:
--       A_Pragma_Argument_Association
--

-------------------------------------------------------------------------------
--  13.41 function Debug_Image
-------------------------------------------------------------------------------

   function Debug_Image (Element : in Asis.Element) return Wide_String;

-------------------------------------------------------------------------------
--  Element - Specifies the program element to convert
--
--  Returns a string value containing implementation-defined debug
--  information associated with the element.
--
--  The return value uses Asis.Text.Delimiter_Image to separate the lines
--  of multi-line results.  The return value does not end with
--  Asis.Text.Delimiter_Image.
--
--  These values are intended for two purposes.  They are suitable for
--  inclusion in problem reports sent to the ASIS implementor.  They can
--  be presumed to contain information useful when debugging the implementation
--  itself. They are also suitable for use by the ASIS application when
--  printing simple application debugging messages during application
--  development.  They are intended to be, to some worthwhile degree,
--  intelligible to the user.
--
-------------------------------------------------------------------------------
--  13.42 function Hash
-------------------------------------------------------------------------------

   function Hash (Element : in Asis.Element) return Asis.ASIS_Integer;

--  The purpose of the hash function is to provide a convenient name for an
--  object of type Asis.Element in order to facilitate application defined I/O
--  and/or other application defined processing.
--
--  The hash function maps Asis.Element objects into N discrete classes
--  ("buckets") of objects.  A good hash function is uniform across its range.
--  It is important to note that the distribution of objects in the
--  application's domain will affect the distribution of the hash function.
--  A good hash measured against one domain will not necessarily be good when
--  fed objects from a different set.
--
--  A continuous uniform hash can be divided by any N and provide a uniform
--  distribution of objects to each of the N discrete classes. A hash value is
--  not unique for each hashed Asis.Element. The application is responsible for
--  handling name collisions of the hashed value.
--
--  The hash function returns a hashed value of type ASIS_Integer. If desired,
--  a user could easily map ASIS_Integer'Range to any smaller range for the
--  hash based on application constraints (i.e., the application implementor
--  can tune the time-space tradeoffs by choosing a small table, implying
--  slower lookups within each "bucket", or a large table, implying faster
--  lookups within each "bucket").

-------------------------------------------------------------------------------

end Asis.Elements;


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
