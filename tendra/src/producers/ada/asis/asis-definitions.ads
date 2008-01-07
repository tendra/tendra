-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  16 package Asis.Definitions
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package Asis.Definitions is
   pragma Preelaborate;

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Definitions encapsulates a set of queries that operate on
--  A_Definition and An_Association elements.
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  16.1 function Corresponding_Type_Operators
-------------------------------------------------------------------------------
--  |ER A_Type_Definition - 3.2.1
-------------------------------------------------------------------------------

   function Corresponding_Type_Operators
            (Type_Definition : in Asis.Type_Definition)
                return Asis.Declaration_List;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the type to query
--
--  Returns a list of operators.  These include all predefined operators, and
--  all user-defined operator overloads, that have been implicitly or
--  explicitly declared for the type. (Reference Manual 7.3.1(2))
--
--  This list includes only operators appropriate for the type, from the set:
--      and or xor = /= < <= > >= + - & * / mod rem ** abs not
--
--  Returns a Nil_Element_List if there are no predefined or overloaded
--  operators for the type.
--
--  Returns a Nil_Element_List if the implementation does not provide
--  such implicit declarations.
--
--  The Enclosing_Element for each implicit declaration is the declaration
--  (type or object) that declared the type.
--
--  For limited private types, if a user-defined equality operator has
--  been defined, an Ada implementation has two choices when dealing with an
--  instance of the "/=" operator.  a) treat A/=B as NOT(A=B), b) implicitly
--  create a "/=" operator.  Implementations that take the second alternative
--  will include this implicit inequality operation in their result.
--  Implementations that choose the first alternative are encouraged to hide
--  this choice beneath the ASIS interface and to "fake" an inequality
--  operation.  Failing that, the function call, representing the NOT
--  operation, must have Is_Part_Of_Implicit = True so that an ASIS application
--  can tell the  difference between a user-specified NOT(A=B) and an
--  implementation-specific A/=B transformation.
--
--  Appropriate Definition_Kinds:
--      A_Type_Definition
--      A_Private_Type_Definition
--      A_Tagged_Private_Type_Definition
--      A_Private_Extension_Definition
--      A_Task_Definition
--      A_Protected_Definition
--      A_Formal_Type_Definition
--
--  Returns Declaration_Kinds:
--      A_Function_Declaration
--      A_Function_Body_Declaration
--      A_Function_Body_Stub
--      A_Function_Renaming_Declaration
--      A_Function_Instantiation
--      A_Formal_Function_Declaration
--
--  |IP Implementation Permissions:
--  |IP
--  |IP The result may or may not include language defined operators that have
--  |IP been overridden by user-defined overloads.  Operators that are totally
--  |IP hidden, in all contexts, by user-defined operators may be omitted from
--  |IP the list.
--  |IP
--  |IP Some implementations do not represent all forms of implicit
--  |IP declarations such that elements representing them can be easily
--  |IP provided.  An implementation can choose whether or not to construct
--  |IP and provide artificial declarations for implicitly declared elements.
--
--  |ER------------------------------------------------------------------------
--  |ER A_Derived_Type_Definition - 3.4
--  |CR
--  |CR Child elements returned by:
--  |CR   function Parent_Subtype_Indication
--  |ER------------------------------------------------------------------------
--  |ER A_Derived_Record_Extension_Definition - 3.4
--  |CR
--  |CR Child elements returned by:
--  |CR   function Parent_Subtype_Indication
--  |CR   function Record_Definition
--
-------------------------------------------------------------------------------
--  16.2 function Parent_Subtype_Indication
-------------------------------------------------------------------------------

   function Parent_Subtype_Indication
                  (Type_Definition : in Asis.Type_Definition)
                        return Asis.Subtype_Indication;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the derived_type_definition to query
--
--  Returns the parent_subtype_indication following the reserved word "new".
--
--  Appropriate Type_Kinds:
--      A_Derived_Type_Definition
--      A_Derived_Record_Extension_Definition
--
--  Returns Definition_Kinds:
--      A_Subtype_Indication
--
-------------------------------------------------------------------------------
--  16.3 function Record_Definition
-------------------------------------------------------------------------------

   function Record_Definition (Type_Definition : in Asis.Type_Definition)
                               return Asis.Definition;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the definition to query
--
--  Returns the record definition of the type_definition.
--
--  Appropriate Type_Kinds:
--      A_Derived_Record_Extension_Definition
--      A_Record_Type_Definition
--      A_Tagged_Record_Type_Definition
--
--  Returns Definition_Kinds:
--      A_Record_Definition
--      A_Null_Record_Definition
--
-------------------------------------------------------------------------------
--  16.4 function Implicit_Inherited_Declarations
-------------------------------------------------------------------------------

   function Implicit_Inherited_Declarations
                  (Definition : in Asis.Definition)
                      return Asis.Declaration_List;

-------------------------------------------------------------------------------
--  Definition - Specifies the derived type to query
--
--  Returns a list of Is_Part_Of_Implicit inherited enumeration literals,
--  discriminants, components, protected subprograms, or entries of a
--  derived_type_definition whose parent type is an enumeration type, or a
--  composite type other than an array type.  See Reference Manual 3.4(10-14).
--
--  Returns a Nil_Element_List if the root type of derived_type_definition is
--  not an enumeration, record, task, or protected type.
--
--  Returns a Nil_Element_List if the implementation does not provide
--  such implicit declarations.
--
--  The Enclosing_Element for each of the implicit declarations is the
--  Declaration argument.
--
--  Appropriate Definition_Kinds:
--      A_Type_Definition
--      A_Private_Extension_Definition
--      A_Formal_Type_Definition
--
--  Appropriate Type_Kinds:
--      A_Derived_Type_Definition
--      A_Derived_Record_Extension_Definition
--
--  Appropriate Formal_Type_Kinds:
--      A_Formal_Derived_Type_Definition
--
--  Returns Declaration_Kinds:
--
--      An_Enumeration_Literal_Specification
--      A_Discriminant_Specification
--      A_Component_Declaration
--      A_Procedure_Declaration
--      A_Function_Declaration
--      An_Entry_Declaration
--
--  |IP Implementation Permissions:
--  |IP
--  |IP Some implementations do not represent all forms of implicit
--  |IP declarations such that elements representing them can be easily
--  |IP provided.  An implementation can choose whether or not to construct
--  |IP and provide artificial declarations for implicitly declared elements.
--
--  |AN Application Note:
--  |AN
--  |AN This query returns only implicit inherited entry declarations for
--  |AN derived task types.  All representation clauses and pragmas associated
--  |AN with the entries of the original task type (the root type of the
--  |AN derived task type) apply to the inherited entries.  Those are available
--  |AN by examining the original type or by calling Corresponding_Pragmas and
--  |AN Corresponding_Representation_Clauses.  These functions will return the
--  |AN pragmas and clauses from the original type.
--
-------------------------------------------------------------------------------
--  16.5 function Implicit_Inherited_Subprograms
-------------------------------------------------------------------------------

   function Implicit_Inherited_Subprograms
                (Definition : in Asis.Definition)
                return Asis.Declaration_List;

-------------------------------------------------------------------------------
--  Definition - Specifies the derived type to query
--
--  Returns the list of user-defined inherited primitive subprograms that have
--  been implicitly declared for the derived_type_definition.
--
--  The list result does not include hidden inherited subprograms (Reference
--  Manual 8.3).
--
--  Returns a Nil_Element_List if there are no inherited subprograms for the
--  derived type.
--
--  Returns a Nil_Element_List if the implementation does not provide
--  such implicit declarations.
--
--  The Enclosing_Element for each of the subprogram declarations is the
--  Definition argument.
--
--  Appropriate Definition_Kinds:
--      A_Type_Definition
--      A_Private_Extension_Definition
--      A_Formal_Type_Definition
--
--  Appropriate Type_Kinds:
--      A_Derived_Type_Definition
--      A_Derived_Record_Extension_Definition
--      An_Interface_Type_Definition (by Gela)
--
--  Appropriate Formal_Type_Kinds:
--      A_Formal_Derived_Type_Definition
--      A_Formal_Interface_Type_Definition (by Gela)
--
--  Returns Declaration_Kinds:
--      A_Function_Declaration
--      A_Procedure_Declaration
--
--  |IP Implementation Permissions:
--  |IP
--  |IP Some implementations do not represent all forms of implicit
--  |IP declarations such that elements representing them can be easily
--  |IP provided.  An implementation can choose whether or not to construct
--  |IP and provide artificial declarations for implicitly declared elements.
--
-------------------------------------------------------------------------------
--  16.6 function Corresponding_Parent_Subtype
-------------------------------------------------------------------------------

   function Corresponding_Parent_Subtype
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Declaration;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the derived_type_definition to query
--
--  Returns the parent subtype declaration of the derived_type_definition.
--  The parent subtype is defined by the parent_subtype_indication.
--
--  Appropriate Type_Kinds:
--      A_Derived_Type_Definition
--      A_Derived_Record_Extension_Definition
--
--  Returns Declaration_Kinds:
--      An_Ordinary_Type_Declaration
--      A_Task_Type_Declaration
--      A_Protected_Type_Declaration
--      A_Subtype_Declaration
--      A_Formal_Type_Declaration
--      An_Incomplete_Type_Declaration
--      A_Private_Type_Declaration
--      A_Private_Extension_Declaration
--
-------------------------------------------------------------------------------
--  16.7 function Corresponding_Root_Type
-------------------------------------------------------------------------------

   function Corresponding_Root_Type
                     (Type_Definition : in Asis.Type_Definition)
                      return Asis.Declaration;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the derived_type_definition to query
--
--  This function recursively unwinds all type derivations and subtyping to
--  arrive at a full_type_declaration that is neither a derived type nor a
--  subtype.
--
--  In case of numeric types, this function always returns some user-defined
--  type, not an implicitly defined root type corresponding to
--  A_Root_Type_Definition. The only ways to get implicitly declared numeric
--  root or universal types are to ask for the type of a universal expression
--  or from the parameter and result profile of a predefined operation working
--  with numeric types.
--
--  Appropriate Type_Kinds:
--      A_Derived_Type_Definition
--      A_Derived_Record_Extension_Definition
--
--  Returns Declaration_Kinds:
--      An_Ordinary_Type_Declaration
--      A_Task_Type_Declaration
--      A_Protected_Type_Declaration
--      A_Formal_Type_Declaration
--      A_Private_Type_Declaration
--      A_Private_Extension_Declaration
--
-------------------------------------------------------------------------------
--  16.8 function Corresponding_Type_Structure
-------------------------------------------------------------------------------

   function Corresponding_Type_Structure
                  (Type_Definition : in Asis.Type_Definition)
                      return Asis.Declaration;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the derived_type_definition to query
--
--  Returns the type structure from which the specified type definition has
--  been derived.  This function will recursively unwind derivations and
--  subtyping until the type_declaration derives a change of representation or
--  is no longer derived.  See Reference Manual 13.6.
--
--  Appropriate Type_Kinds:
--      A_Derived_Type_Definition
--      A_Derived_Record_Extension_Definition
--
--  Returns Declaration_Kinds:
--      An_Ordinary_Type_Declaration
--      A_Task_Type_Declaration
--      A_Protected_Type_Declaration
--      A_Formal_Type_Declaration
--      A_Private_Type_Declaration
--      A_Private_Extension_Declaration
--
--  |ER------------------------------------------------------------------------
--  |ER An_Enumeration_Type_Definition - 3.5.1
--  |CR
--  |CR Child elements returned by:
--  |CR   function Enumeration_Literal_Declarations
--
-------------------------------------------------------------------------------
--  16.9 function Enumeration_Literal_Declarations
-------------------------------------------------------------------------------

   function Enumeration_Literal_Declarations
                (Type_Definition : in Asis.Type_Definition)
                return Asis.Declaration_List;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the enumeration type definition to query
--
--  Returns a list of the literals declared in an enumeration_type_definition,
--  in their order of appearance.
--
--  Appropriate Type_Kinds:
--      An_Enumeration_Type_Definition
--
--  Returns Declaration_Kinds:
--      An_Enumeration_Literal_Specification
--
--  |ER------------------------------------------------------------------------
--  |ER A_Signed_Integer_Type_Definition - 3.5.4
--  |CR
--  |CR Child elements returned by:
--  |CR   function Integer_Constraint
--

-------------------------------------------------------------------------------
--  16.10 function Integer_Constraint
-------------------------------------------------------------------------------

   function Integer_Constraint
                (Type_Definition : in Asis.Type_Definition)
                return Asis.Range_Constraint;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the signed_integer_type_definition to query
--
--  Returns the range_constraint of the signed_integer_type_definition.
--
--  Appropriate Type_Kinds:
--      A_Signed_Integer_Type_Definition
--
--  Returns Constraint_Kinds:
--      A_Simple_Expression_Range
--
--  |ER------------------------------------------------------------------------
--  |ER A_Modular_Type_Definition - 3.5.4
--  |CR
--  |CR Child elements returned by:
--  |CR   function Mod_Static_Expression
--
-------------------------------------------------------------------------------
--  16.11 function Mod_Static_Expression
-------------------------------------------------------------------------------

   function Mod_Static_Expression
                (Type_Definition : in Asis.Type_Definition)
                return Asis.Expression;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the modular_type_definition to query
--
--  Returns the static_expression following the reserved word "mod".
--
--  Appropriate Type_Kinds:
--      A_Modular_Type_Definition
--
--  Returns Element_Kinds:
--      An_Expression
--
--  |ER------------------------------------------------------------------------
--  |ER A_Floating_Point_Definition - 3.5.7
--  |CR
--  |CR Child elements returned by:
--  |CR   functions Digits_Expression and Real_Range_Constraint
--
--  |ER------------------------------------------------------------------------
--  |ER A_Decimal_Fixed_Point_Definition - 3.5.9
--  |CR
--  |CR Child elements returned by:
--  |CR   functions Digits_Expression, Delta_Expression, and
--  |CR   Real_Range_Constraint
--
-------------------------------------------------------------------------------
--  16.12 function Digits_Expression
-------------------------------------------------------------------------------

   function Digits_Expression (Definition : in Asis.Definition)
                               return Asis.Expression;

-------------------------------------------------------------------------------
--  Definition  - Specifies the definition to query
--
--  Returns the static_expression following the reserved word "digits".
--
--  Appropriate Type_Kinds:
--      A_Floating_Point_Definition
--      A_Decimal_Fixed_Point_Definition
--
--  Appropriate Definition_Kinds:
--      A_Constraint
--          Appropriate Constraint_Kinds:
--               A_Digits_Constraint
--
--  Returns Element_Kinds:
--      An_Expression
--
--  |ER------------------------------------------------------------------------
--  |ER An_Ordinary_Fixed_Point_Definition - 3.5.9
--  |CR
--  |CR Child elements returned by:
--  |CR   function Delta_Expression
--
-------------------------------------------------------------------------------
--  16.13 function Delta_Expression
-------------------------------------------------------------------------------

   function Delta_Expression (Definition : in Asis.Definition)
                              return Asis.Expression;

-------------------------------------------------------------------------------
--  Definition  - Specifies the definition to query
--
--  Returns the static_expression following the reserved word "delta".
--
--  Appropriate Type_Kinds:
--      An_Ordinary_Fixed_Point_Definition
--      A_Decimal_Fixed_Point_Definition
--
--  Appropriate Definition_Kinds:
--      A_Constraint
--          Appropriate Constraint_Kinds:
--               A_Delta_Constraint
--
--  Returns Element_Kinds:
--      An_Expression
--
-------------------------------------------------------------------------------
--  16.14 function Real_Range_Constraint
-------------------------------------------------------------------------------

   function Real_Range_Constraint
             (Definition : in Asis.Definition) return Asis.Range_Constraint;

-------------------------------------------------------------------------------
--  Definition  - Specifies the definition to query
--
--  Returns the real_range_specification range_constraint of the definition.
--
--  Returns a Nil_Element if there is no explicit range_constraint.
--
--  Appropriate Type_Kinds:
--      A_Floating_Point_Definition
--      An_Ordinary_Fixed_Point_Definition
--      A_Decimal_Fixed_Point_Definition
--
--  Appropriate Definition_Kinds:
--      A_Constraint
--          Appropriate Constraint_Kinds:
--               A_Digits_Constraint
--               A_Delta_Constraint
--
--  Returns Constraint_Kinds:
--      Not_A_Constraint
--      A_Simple_Expression_Range
--
--  |ER------------------------------------------------------------------------
--  |ER An_Unconstrained_Array_Definition 3.6
--  |CR
--  |CR Child elements returned by:
--  |CR   functions Index_Subtype_Definitions and Array_Component_Definition
--

-------------------------------------------------------------------------------
--  16.15 function Index_Subtype_Definitions
-------------------------------------------------------------------------------

   function Index_Subtype_Definitions
                (Type_Definition : in Asis.Type_Definition)
                return Asis.Expression_List;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the array_type_definition to query
--
--  Returns a list of the index_subtype_definition subtype mark names for
--  an unconstrained_array_definition, in their order of appearance.
--
--  Appropriate Type_Kinds:
--      An_Unconstrained_Array_Definition
--
--  Appropriate Formal_Type_Kinds:
--      A_Formal_Unconstrained_Array_Definition
--
--  Returns Expression_Kinds:
--      An_Identifier
--      A_Selected_Component
--
--  |ER------------------------------------------------------------------------
--  |ER A_Constrained_Array_Definition 3.6
--  |CR
--  |CR Child elements returned by:
--  |CR   function Discrete_Subtype_Definitions
--  |CR   function Array_Component_Definition
--
-------------------------------------------------------------------------------
--  16.16 function Discrete_Subtype_Definitions
-------------------------------------------------------------------------------

   function Discrete_Subtype_Definitions
                        (Type_Definition : in Asis.Type_Definition)
                              return Asis.Definition_List;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the array_type_definition to query
--
--  Returns the list of Discrete_Subtype_Definition elements of a
--  constrained_array_definition, in their order of appearance.
--
--  Appropriate Type_Kinds:
--      A_Constrained_Array_Definition
--
--  Appropriate Formal_Type_Kinds:
--      A_Formal_Constrained_Array_Definition
--
--  Returns Definition_Kinds:
--      A_Discrete_Subtype_Definition
--
-------------------------------------------------------------------------------
--  16.17 function Array_Component_Definition
-------------------------------------------------------------------------------

   function Array_Component_Definition
                (Type_Definition : in Asis.Type_Definition)
                return Asis.Component_Definition;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the array_type_definition to query
--
--  Returns the Component_Definition of the array_type_definition.
--
--  Appropriate Type_Kinds:
--      An_Unconstrained_Array_Definition
--      A_Constrained_Array_Definition
--
--  Appropriate Formal_Type_Kinds:
--      A_Formal_Unconstrained_Array_Definition
--      A_Formal_Constrained_Array_Definition
--
--  Returns Definition_Kinds:
--      A_Component_Definition
--
--  |ER------------------------------------------------------------------------
--  |ER A_Record_Type_Definition - 3.8
--  |ER A_Tagged_Record_Type_Definition - 3.8
--  |CR
--  |CR Child elements returned by:
--  |CR   function Record_Definition
--  |ER------------------------------------------------------------------------
--  |ER An_Access_Type_Definition - 3.10
--  |CR
--  |CR Child elements returned by:
--  |CR   function Access_To_Object_Definition
--  |CR   function Access_To_Subprogram_Parameter_Profile
--  |CR   function Access_To_Function_Result_Profile (obsolete)
--
-------------------------------------------------------------------------------
--  16.18 function Access_To_Object_Definition
-------------------------------------------------------------------------------

   function Access_To_Object_Definition
                   (Type_Definition : in Asis.Type_Definition)
                         return Asis.Subtype_Indication;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the Access_Type_Definition to query
--
--  Returns the subtype_indication following the reserved word "access".
--
--  Appropriate Type_Kinds:
--      An_Access_Type_Definition.
--
--  Appropriate Formal_Type_Kinds:
--      A_Formal_Access_Type_Definition
--
--  Appropriate Access_Type_Kinds:
--      A_Pool_Specific_Access_To_Variable
--      An_Access_To_Variable
--      An_Access_To_Constant
--
--  Returns Element_Kinds:
--      A_Subtype_Indication
--
-------------------------------------------------------------------------------
--  16.xx function Anonymous_Access_To_Object_Subtype_Mark
-------------------------------------------------------------------------------

   function Anonymous_Access_To_Object_Subtype_Mark
     (Definition : Asis.Definition)
      return Asis.Name;

-------------------------------------------------------------------------------
--  Definition - Specifies the anonymous access definition to query.
--
--  Returns the subtype_mark following the reserved word(s) "access" or
--  "access constant".
--
--  Appropriate Definition_Kinds:
--     An_Access_Definition.
--
--  Appropriate Access_Definition_Kinds:
--     An_Anonymous_Access_To_Variable
--     An_Anonymous_Access_To_Constant
--
--  Returns Expression_Kinds:
--     An_Identifier
--     A_Selected_Component
--     An_Attribute_Reference
--
-------------------------------------------------------------------------------
--  16.19 function Access_To_Subprogram_Parameter_Profile
-------------------------------------------------------------------------------

   function Access_To_Subprogram_Parameter_Profile
                   (Type_Definition : in Asis.Type_Definition)
                         return Asis.Parameter_Specification_List;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the Access_Type_Definition to query
--
--  Returns a list of parameter_specification elements in the formal part of
--  the parameter_profile in the access_to_subprogram_definition.
--
--  Returns a Nil_Element_List if the parameter_profile has no formal part.
--
--  Results of this query may vary across ASIS implementations.  Some
--  implementations normalize all multiple name parameter_specification
--  elements into an equivalent sequence of corresponding single name
--  parameter_specification elements.  See Reference Manual 3.3.1(7).
--
--  Appropriate Type_Kinds:
--      An_Access_Type_Definition.
--      A_Formal_Access_Type_Definition.
--
--
--  Appropriate Access_Type_Kinds:
--      An_Access_To_Procedure
--      An_Access_To_Protected_Procedure
--      An_Access_To_Function
--      An_Access_To_Protected_Function
--
--  Appropriate Access_Definition_Kinds
--     An_Anonymous_Access_To_Procedure
--     An_Anonymous_Access_To_Protected_Procedure
--     An_Anonymous_Access_To_Function
--     An_Anonymous_Access_To_Protected_Function
--
--  Returns Declaration_Kinds:
--      A_Parameter_Specification
--
-------------------------------------------------------------------------------
--  16.20 function Access_To_Function_Result_Subtype
-------------------------------------------------------------------------------

   function Access_To_Function_Result_Subtype
     (Definition : in Asis.Definition)
      return Asis.Definition;

-------------------------------------------------------------------------------
--  Definition specifies the Access_Type_Definition or
--  Access_Definition to query.
--
--  Returns a definition that corresponds to the result subtype of the
--  access-to-function type, as specified by a subtype_indication (with
--  no specified constraint) or an access_definition.
--
--  Appropriate Definition_Kinds:
--     A_Type_Definition
--     An_Access_Definition
--
--  Appropriate Type_Kinds:
--     An_Access_Type_Definition
--     A_Formal_Access_Type_Definition
--
--  Appropriate Access_Type_Kinds:
--     An_Access_To_Function
--     An_Access_To_Protected_Function
--
--  Appropriate Access_Definition_Kinds:
--     An_Anonymous_Access_To_Function
--     An_Anonymous_Access_To_Protected_Function
--
--  Returns Definition_Kinds:
--     A_Subtype_Indication
--     An_Access_Definition
--
-------------------------------------------------------------------------------
--  16.20 function Access_To_Function_Result_Profile (obsolete)
-------------------------------------------------------------------------------

   function Access_To_Function_Result_Profile
                   (Type_Definition : in Asis.Type_Definition)
                         return Asis.Expression;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the Access_Type_Definition to query
--
--  Returns the subtype_mark expression for the return type for the access
--  function.
--
--  Appropriate Type_Kinds:
--      An_Access_Type_Definition
--      A_Formal_Access_Type_Definition
--
--  Appropriate Access_Type_Kinds:
--      An_Access_To_Function
--      An_Access_To_Protected_Function
--
--  Returns Expression_Kinds:
--      An_Identifier
--      A_Selected_Component
--
--  |ER------------------------------------------------------------------------
--  |ER A_Root_Type_Definition - 3.5.4(9), 3.5.6(2) - No child elements
--  |ER------------------------------------------------------------------------
--  |ER A_Subtype_Indication - 3.3.2
--  |CR
--  |CR Child elements returned by:
--  |CR   function Subtype_Mark
--  |CR   function Subtype_Constraint
--
-------------------------------------------------------------------------------
--  16.21 function Subtype_Mark
-------------------------------------------------------------------------------

   function Subtype_Mark (Definition : in Asis.Definition)
                          return Asis.Expression;

-------------------------------------------------------------------------------
--  Definition  - Specifies the definition to query
--
--  Returns the subtype_mark expression of the definition.
--
--  Appropriate Definition_Kinds:
--      A_Subtype_Indication
--      A_Discrete_Subtype_Definition
--          Appropriate Discrete_Range_Kinds:
--               A_Discrete_Subtype_Indication
--      A_Discrete_Range
--          Appropriate Discrete_Range_Kinds:
--               A_Discrete_Subtype_Indication
--      A_Formal_Type_Definition
--          Appropriate Formal_Type_Kinds:
--               A_Formal_Derived_Type_Definition
--
--  Returns Expression_Kinds:
--      An_Identifier
--      A_Selected_Component
--      An_Attribute_Reference
--

-------------------------------------------------------------------------------
--  16.22 function Subtype_Constraint
-------------------------------------------------------------------------------

   function Subtype_Constraint (Definition : in Asis.Definition)
                                return Asis.Constraint;

-------------------------------------------------------------------------------
--  Definition  - Specifies the definition to query
--
--  Returns the constraint of the subtype_indication.
--
--  Returns a Nil_Element if no explicit constraint is present.
--
--  Appropriate Definition_Kinds:
--      A_Subtype_Indication
--      A_Discrete_Subtype_Definition
--          Appropriate Discrete_Range_Kinds:
--               A_Discrete_Subtype_Indication
--      A_Discrete_Range
--          Appropriate Discrete_Range_Kinds:
--               A_Discrete_Subtype_Indication
--
--  Returns Definition_Kinds:
--      Not_A_Definition
--      A_Constraint
--
--  |AN Application Note:
--  |AN
--  |AN When an unconstrained subtype indication for a type having
--  |AN discriminants with default values is used, a Nil_Element is
--  |AN returned by this function.  Use the queries Subtype_Mark, and
--  |AN Corresponding_Name_Declaration [, and Corresponding_First_Subtype]
--  |AN to obtain the declaration defining the defaults.
--
--  |ER------------------------------------------------------------------------
--  |ER A_Constraint - 3.2.2
--  |ER
--  |ER A_Simple_Expression_Range - 3.5
--  |CR
--  |CR Child elements returned by:
--  |CR   function Lower_Bound
--  |CR   function Upper_Bound
--
-------------------------------------------------------------------------------
--  16.23 function Lower_Bound
-------------------------------------------------------------------------------
   function Lower_Bound (Constraint : in Asis.Range_Constraint)
                         return Asis.Expression;

-------------------------------------------------------------------------------
--  Constraint  - Specifies the range_constraint or discrete_range to query
--
--  Returns the simple_expression for the lower bound of the range.
--
--  Appropriate Constraint_Kinds:
--      A_Simple_Expression_Range
--
--  Appropriate Discrete_Range_Kinds:
--      A_Discrete_Simple_Expression_Range
--
--  Returns Element_Kinds:
--      An_Expression
--

-------------------------------------------------------------------------------
--  16.24 function Upper_Bound
-------------------------------------------------------------------------------

   function Upper_Bound (Constraint : in Asis.Range_Constraint)
                         return Asis.Expression;

-------------------------------------------------------------------------------
--  Constraint  - Specifies the range_constraint or discrete_range to query
--
--  Returns the simple_expression for the upper bound of the range.
--
--  Appropriate Constraint_Kinds:
--      A_Simple_Expression_Range
--
--  Appropriate Discrete_Range_Kinds:
--      A_Discrete_Simple_Expression_Range
--
--  Returns Element_Kinds:
--      An_Expression
--
--  |ER------------------------------------------------------------------------
--  |ER A_Range_Attribute_Reference - 3.5
--  |CR
--  |CR Child elements returned by:
--  |CR   function Range_Attribute
--
-------------------------------------------------------------------------------
--  16.25 function Range_Attribute
-------------------------------------------------------------------------------

   function Range_Attribute (Constraint : in Asis.Range_Constraint)
                             return Asis.Expression;

-------------------------------------------------------------------------------
--  Constraint  - Specifies the range_attribute_reference or
--               discrete_range attribute_reference to query
--
--  Returns the range_attribute_reference expression of the range.
--
--  Appropriate Constraint_Kinds:
--      A_Range_Attribute_Reference
--
--  Appropriate Discrete_Range_Kinds:
--      A_Discrete_Range_Attribute_Reference
--
--  Returns Expression_Kinds:
--      An_Attribute_Reference
--
--  |ER------------------------------------------------------------------------
--  |ER A_Digits_Constraint - 3.5.9
--  |CR
--  |CR Child elements returned by:
--  |CR   function Digits_Expression
--  |CR   function Real_Range_Constraint
--  |ER------------------------------------------------------------------------
--  |ER A_Delta_Constraint - J.3
--  |CR
--  |CR Child elements returned by:
--  |CR   function Delta_Expression
--  |CR   function Real_Range_Constraint
--  |CR------------------------------------------------------------------------
--  |ER An_Index_Constraint - 3.6.1
--  |CR
--  |CR Child elements returned by:
--  |CR   function Discrete_Ranges
--

-------------------------------------------------------------------------------
--  16.26 function Discrete_Ranges
-------------------------------------------------------------------------------

   function Discrete_Ranges (Constraint : in Asis.Constraint)
                             return Asis.Discrete_Range_List;

-------------------------------------------------------------------------------
--  Constraint  - Specifies the array index_constraint to query
--
--  Returns the list of discrete_range components for an index_constraint,
--  in their order of appearance.
--
--  Appropriate Constraint_Kinds:
--      An_Index_Constraint
--
--  Returns Definition_Kinds:
--      A_Discrete_Range
--
--  |ER------------------------------------------------------------------------
--  |ER A_Discriminant_Constraint - 3.7.1
--  |CR
--  |CR Child elements returned by:
--  |CR   function Discriminant_Associations
--
-------------------------------------------------------------------------------
--  16.27 function Discriminant_Associations
-------------------------------------------------------------------------------

   function Discriminant_Associations
                (Constraint : in Asis.Constraint;
                 Normalized : in Boolean := False)
                return Asis.Discriminant_Association_List;

-------------------------------------------------------------------------------
--  Constraint  - Specifies the discriminant_constraint to query
--  Normalized  - Specifies whether the normalized form is desired
--
--  Returns a list of the discriminant_association elements of the
--  discriminant_constraint.
--
--  Returns a Nil_Element_List if there are no discriminant_association
--  elements.
--
--  An unnormalized list contains only explicit associations ordered as they
--  appear in the program text.  Each unnormalized association has a list of
--  discriminant_selector_name elements and an explicit expression.
--
--  A normalized list contains artificial associations representing all
--  explicit associations.  It has a length equal to the number of
--  discriminant_specification elements of the known_discriminant_part.
--  The order of normalized associations matches the order of
--  discriminant_specification elements.
--
--  Each normalized association represents a one on one mapping of a
--  discriminant_specification to the explicit expression.  A normalized
--  association has one A_Defining_Name component that denotes the
--  discriminant_specification, and one An_Expression component that is the
--  explicit expression.
--
--  Appropriate Constraint_Kinds:
--      A_Discriminant_Constraint
--
--  Returns Association_Kinds:
--      A_Discriminant_Association
--
--  |IR Implementation Requirements:
--  |IR
--  |IR Normalized associations are Is_Normalized and Is_Part_Of_Implicit.
--  |IR Normalized associations are never Is_Equal to unnormalized
--  |IR associations.
--

--  |IP Implementation Permissions:
--  |IP
--  |IP An implementation may choose to normalize its internal representation
--  |IP to use the defining_identifier element instead of the
--  |IP discriminant_selector_name element.
--  |IP
--  |IP If so, this query will return Is_Normalized associations even if
--  |IP Normalized is False, and the query Discriminant_Associations_Normalized
--  |IP will return True.
--
--  |AN Application Note:
--  |AN
--  |AN It is not possible to obtain either a normalized or unnormalized
--  |AN Discriminant_Association list for an unconstrained record or derived
--  |AN subtype_indication where the discriminant_association elements are
--  |AN supplied by default; there is no constraint to query, and a
--  |AN Nil_Element is returned from the query Subtype_Constraint.
--
--  |ER------------------------------------------------------------------------
--  |ER A_Component_Definition - 3.6
--  |CR
--  |CR Child elements returned by:
--  |CR   function Component_Subtype_Indication
--
-------------------------------------------------------------------------------
--  16.28 function Component_Subtype_Indication
-------------------------------------------------------------------------------

   function Component_Subtype_Indication
            (Component_Definition : in Asis.Component_Definition)
                return Asis.Subtype_Indication;

-------------------------------------------------------------------------------
--  Component_Definition - Specifies the Component_Definition to query
--
--  Returns the subtype_indication of the Component_Definition.
--
--  Appropriate Definition_Kinds:
--      A_Component_Definition
--
--  Returns Definition_Kinds:
--      A_Subtype_Indication
--
--  |ER------------------------------------------------------------------------
--  |ER A_Discrete_Subtype_Definition - 3.6
--  |ER A_Discrete_Range - 3.6.1
--  |ER
--  |ER A_Discrete_Subtype_Indication
--  |CR
--  |CR Child elements returned by:
--  |CR   function Subtype_Mark
--  |CR   function Subtype_Constraint
--  |CR
--  |CR A_Discrete_Simple_Expression_Range
--  |CR
--  |CR Child elements returned by:
--  |CR   function Lower_Bound
--  |CR   function Upper_Bound
--  |ER
--  |ER------------------------------------------------------------------------
--  |ER A_Discrete_Range_Attribute_Reference - 3.5
--  |CR
--  |CR Child elements returned by:
--  |CR   function Range_Attribute
--  |ER------------------------------------------------------------------------
--  |ER An_Unknown_Discriminant_Part - 3.7 - No child elements
--  |ER------------------------------------------------------------------------
--  |ER A_Known_Discriminant_Part - 3.7
--  |CR
--  |CR Child elements returned by:
--  |CR   function Discriminants
--

-------------------------------------------------------------------------------
--  16.29 function Discriminants
-------------------------------------------------------------------------------

   function Discriminants (Definition : in Asis.Definition)
                           return Asis.Discriminant_Specification_List;

-------------------------------------------------------------------------------
--  Definition - Specifies the known_discriminant_part to query
--
--  Returns a list of discriminant_specification elements, in their order
--  of appearance.
--
--  Results of this query may vary across ASIS implementations.  Some
--  implementations normalize all multi-name discriminant_specification
--  elements into an equivalent sequence of single name
--  discriminant_specification elements.  See Reference Manual 3.3.1(7).
--
--  Appropriate Definition_Kinds:
--      A_Known_Discriminant_Part
--
--  Returns Declaration_Kinds:
--      A_Discriminant_Specification
--
--  |ER------------------------------------------------------------------------
--  |ER A_Record_Definition - 3.8
--  |CR
--  |CR Child elements returned by:
--  |CR   function Record_Components
--  |CR   function Implicit_Components
--
-------------------------------------------------------------------------------
--  16.30 function Record_Components
-------------------------------------------------------------------------------

   function Record_Components (Definition : in Asis.Definition;
                               Include_Pragmas : in Boolean := False)
                               return Asis.Record_Component_List;

-------------------------------------------------------------------------------
--  Definition - Specifies the record_definition or variant to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns a list of the components and pragmas of the record_definition or
--  variant, in their order of appearance.
--
--  Declarations are not returned for implementation-defined components of the
--  record_definition.  See Reference Manual 13.5.1 (15).  These components are
--  not normally visible to the ASIS application.  However, they can be
--  obtained with the query Implicit_Components.
--
--  Appropriate Definition_Kinds:
--      A_Record_Definition
--      A_Variant
--
--  Returns Element_Kinds:
--      A_Pragma
--      A_Declaration
--      A_Definition
--      A_Clause
--
--  Returns Declaration_Kinds:
--      A_Component_Declaration
--
--  Returns Definition_Kinds:
--      A_Null_Component
--      A_Variant_Part
--
--  Returns Representation_Clause_Kinds:
--      An_Attribute_Definition_Clause
--

-------------------------------------------------------------------------------
--  16.31 function Implicit_Components
-------------------------------------------------------------------------------

   function Implicit_Components
                    (Definition : in Asis.Definition)
                        return Asis.Record_Component_List;

-------------------------------------------------------------------------------
--  Definition - Specifies the record_definition or variant to query
--
--  Returns a list of all implicit implementation-defined components of the
--  record_definition or variant.  The Enclosing_Element of each component is
--  the Definition argument.  Each component is Is_Part_Of_Implicit.
--
--  Returns a Nil_Element_List if there are no implicit implementation-defined
--  components or if the ASIS implementation does not support such
--  implicit declarations.
--
--  Appropriate Definition_Kinds:
--      A_Record_Definition
--      A_Variant
--
--  Returns Element_Kinds:
--      A_Declaration
--
--  Returns Declaration_Kinds:
--      A_Component_Declaration
--
--  |IP Implementation Permissions:
--  |IP
--  |IP Some implementations do not represent all forms of implicit
--  |IP declarations such that elements representing them can be easily
--  |IP provided.  An implementation can choose whether or not to construct
--  |IP and provide artificial declarations for implicitly declared elements.
--  |IP
--  |IP Use the query Implicit_Components_Supported to determine if the
--  |IP implementation provides implicit record components.
--
--  |ER------------------------------------------------------------------------
--  |ER A_Null_Record_Definition - 3.8 - No child elements
--  |ER------------------------------------------------------------------------
--  |ER A_Variant_Part - 3.8.1
--  |CR
--  |CR Child elements returned by:
--  |CR   function Discriminant_Direct_Name
--  |CR   function Variants
--
-------------------------------------------------------------------------------
--  16.32 function Discriminant_Direct_Name
-------------------------------------------------------------------------------

   function Discriminant_Direct_Name
                (Variant_Part : in Asis.Record_Component)
                return Asis.Name;

-------------------------------------------------------------------------------
--  Variant_Part    - Specifies the variant_part to query
--
--  Returns the Discriminant_Direct_Name of the variant_part.
--
--  Appropriate Definition_Kinds:
--      A_Variant_Part
--
--  Returns Expression_Kinds:
--      An_Identifier
--

-------------------------------------------------------------------------------
--  16.33 function Variants
-------------------------------------------------------------------------------

   function Variants (Variant_Part    : in Asis.Record_Component;
                      Include_Pragmas : in Boolean := False)
                      return Asis.Variant_List;

-------------------------------------------------------------------------------
--  Variant_Part    - Specifies the variant_part to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns a list of variants that make up the record component, in their
--  order of appearance.
--
--  The only pragmas returned are those following the reserved word "is"
--  and preceding the reserved word "when" of first variant, and those between
--  following variants.
--
--  Appropriate Definition_Kinds:
--      A_Variant_Part
--
--  Returns Element_Kinds:
--      A_Pragma
--      A_Definition
--
--  Returns Definition_Kinds:
--      A_Variant
--
--  |ER------------------------------------------------------------------------
--  |ER A_Variant - 3.8.1
--  |CR
--  |CR Child elements returned by:
--  |CR   function Variant_Choices
--  |CR   function Record_Components
--  |CR   function Implicit_Components
--
-------------------------------------------------------------------------------
--  16.34 function Variant_Choices
-------------------------------------------------------------------------------

   function Variant_Choices (Variant : in Asis.Variant)
                             return Asis.Element_List;

-------------------------------------------------------------------------------
--  Variant - Specifies the variant to query
--
--  Returns the discrete_choice_list elements, in their order of appearance.
--  Choices are either an expression, a discrete range, or an others choice.
--
--  Appropriate Definition_Kinds:
--      A_Variant
--
--  Returns Element_Kinds:
--      An_Expression
--      A_Definition
--
--  Returns Definition_Kinds:
--      A_Discrete_Range
--      An_Others_Choice
--
--  |ER------------------------------------------------------------------------
--  |ER A_Private_Type_Definition - 7.3 - No child elements
--  |ER A_Tagged_Private_Type_Definition - 7.3 - No child elements
--  |ER------------------------------------------------------------------------
--  |ER A_Private_Extension_Definition - 7.3
--  |CR
--  |CR Child elements returned by:
--  |CR   function Ancestor_Subtype_Indication
--

-------------------------------------------------------------------------------
--  16.35 function Ancestor_Subtype_Indication
-------------------------------------------------------------------------------

   function Ancestor_Subtype_Indication
                   (Definition : in Asis.Definition)
                         return Asis.Subtype_Indication;

-------------------------------------------------------------------------------
--  Definition - Specifies the definition to query
--
--  Returns the ancestor_subtype_indication following the reserved word "new"
--  in the private_extension_declaration.
--
--  Appropriate Definition_Kinds:
--      A_Private_Extension_Definition
--
--  Returns Definition_Kinds:
--      A_Subtype_Indication
--
--  |ER------------------------------------------------------------------------
--  |ER A_Task_Definition - 9.1
--  |ER A_Protected_Definition - 9.4
--  |CR
--  |CR Child elements returned by:
--  |CR   functions Visible_Part_Items and Private_Part_Items
--
-------------------------------------------------------------------------------
--  16.36 function Visible_Part_Items
-------------------------------------------------------------------------------

   function Visible_Part_Items
                (Definition : in Asis.Definition;
                 Include_Pragmas : in Boolean := False)
                return Asis.Declarative_Item_List;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the type_definition to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns a list of declarations, representation clauses, and pragmas
--  in the visible part of the task or protected definition, in their order
--  of appearance.  The list does not include discriminant_specification
--  elements of the known_discriminant_part, if any, of the protected type
--  or task type declaration.
--
--  Returns a Nil_Element_List if there are no items.
--
--  Appropriate Definition_Kinds:
--      A_Task_Definition
--      A_Protected_Definition
--
--  Returns Element_Kinds:
--      A_Pragma
--      A_Declaration
--      A_Clause
--
-------------------------------------------------------------------------------
--  16.37 function Private_Part_Items
-------------------------------------------------------------------------------

   function Private_Part_Items
                (Definition : in Asis.Definition;
                 Include_Pragmas : in Boolean := False)
                 return Asis.Declarative_Item_List;

-------------------------------------------------------------------------------
--  Type_Definition - Specifies the task type definition to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns a list of declarations, representation clauses, and pragmas in
--  the private part of the task or protected definition, in their order
--  of appearance.
--
--  Returns a Nil_Element_List if there are no items.
--
--  Appropriate Definition_Kinds:
--      A_Task_Definition
--      A_Protected_Definition
--
--  Returns Element_Kinds:
--      A_Pragma
--      A_Declaration
--      A_Clause
--
-------------------------------------------------------------------------------
--  16.38 function Is_Private_Present
-------------------------------------------------------------------------------

   function Is_Private_Present
                (Definition : in Asis.Definition) return Boolean;

-------------------------------------------------------------------------------
--  Definition - Specifies the definition to query
--
--  Returns True if the argument is a task_definition or a protected_definition
--  that has a reserved word "private" marking the beginning of a
--  (possibly empty) private part.
--
--  Returns False for any definition without a private part.
--  Returns False for any unexpected Element.
--
--  Expected Definition_Kinds:
--      A_Task_Definition
--      A_Protected_Definition
--
--  |ER------------------------------------------------------------------------
--  |ER A_Formal_Type_Definition - 12.5
--  |ER
--  |ER A_Formal_Private_Type_Definition         - 12.5.1 - No child elements
--  |ER A_Formal_Tagged_Private_Type_Definition  - 12.5.1 - No child elements
--  |ER
--  |ER A_Formal_Derived_Type_Definition
--  |CR Child elements returned by:
--  |CR   function Subtype_Mark
--
--  |ER------------------------------------------------------------------------
--  |ER A_Formal_Discrete_Type_Definition        - 12.5.2 - No child elements
--  |ER A_Formal_Signed_Integer_Type_Definition  - 12.5.2 - No child elements
--  |ER A_Formal_Modular_Type_Definition         - 12.5.2 - No child elements
--  |ER A_Formal_Floating_Point_Definition       - 12.5.2 - No child elements
--  |ER A_Formal_Ordinary_Fixed_Point_Definition - 12.5.2 - No child elements
--  |ER A_Formal_Decimal_Fixed_Point_Definition  - 12.5.2 - No child elements
--  |ER------------------------------------------------------------------------
--  |ER A_Formal_Unconstrained_Array_Definition  - 12.5.3
--  |CR
--  |CR Child elements returned by:
--  |CR   function Index_Subtype_Definitions
--  |CR   function Array_Component_Definition
--  |ER------------------------------------------------------------------------
--  |ER A_Formal_Constrained_Array_Definition    - 12.5.3
--  |CR
--  |CR Child elements returned by:
--  |CR   function Discrete_Subtype_Definitions
--  |CR   function Array_Component_Definition
--  |ER------------------------------------------------------------------------
--  |ER A_Formal_Access_Type_Definition          - 12.5.4
--  |CR
--  |CR Child elements returned by:
--  |CR   function Access_To_Object_Definition
--  |CR   function Access_To_Subprogram_Parameter_Profile
--  |CR   function Access_To_Function_Result_Profile
--
-------------------------------------------------------------------------------
--  16.xx function Progenitor_List
-------------------------------------------------------------------------------

   function Progenitor_List
     (Type_Definition : Asis.Definition)
      return Asis.Name_List;

-------------------------------------------------------------------------------
--  Type_Definition - specifies the definition to query.
--
--  Returns a list of subtype marks making up the interface_list in the
--  argument definition, in their order of appearance.
--
--  Appropriate Type_Kinds:
--     A_Derived_Record_Extension_Definition
--     An_Interface_Type_Definition
--
--  Appropriate Formal_Type_Kinds:
--     A_Formal_Derived_Type_Definition
--     A_Formal_Interface_Type_Definition
--
--  Returns Expression_Kinds:
--     An_Identifier
--     A_Selected_Component
--
-------------------------------------------------------------------------------
--  16.xx function Is_Task_Definition_Present
-------------------------------------------------------------------------------

   function Is_Task_Definition_Present
     (Definition : in Asis.Definition)
      return Boolean;

-------------------------------------------------------------------------------
--  Defintion specifies the definition element to query.
--
--  Returns True if the element has a task definition.
--
--  Returns False for any other Element including a Nil_Element.
--
--  Note: Is_Task_Definition_Present is used to determine whether the
--  original text was "Task T;" (for which it returns False) or
--  "Task T is end T;" (for which it returns True).
--
--  Expected Definition_Kinds:
--     A_Task_Definition
--
-------------------------------------------------------------------------------


end Asis.Definitions;



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
