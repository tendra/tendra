-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  10 package Asis.Compilation_Units
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

with Asis.Ada_Environments.Containers;
package Asis.Compilation_Units is
--   pragma Preelaborate;

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Compilation_Units encapsulates a set of queries that implement the
--  ASIS Compilation_Unit abstraction.
--
--  More than one compilation unit may be manipulated at one time.  (The exact
--  number is subject to implementation specific limitations.)
--
--  A specific Compilation_Unit value is valid (usable) for as long as the ASIS
--  Context variable, used to create it, remains open.  Once an ASIS Context is
--  closed, all associated Compilation_Unit values become invalid.  It is
--  erroneous to use an invalid Compilation_Unit value.
--
-------------------------------------------------------------------------------
--  10.1 function Unit_Kind
-------------------------------------------------------------------------------

   function Unit_Kind (Compilation_Unit : in Asis.Compilation_Unit)
                      return Asis.Unit_Kinds;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the compilation unit to query
--
--  Returns the Unit_Kinds value of the compilation unit.
--  Returns Not_A_Unit for a Nil_Compilation_Unit.
--
--  All Unit_Kinds are expected.
--
--  Returns An_Unknown_Unit for any compilation unit that exists, but that
--  does not have semantic element information available through ASIS.
--
--  Returns a nonexistent kind for units that have name-only entries in the
--  environment Context.  Such entries may exist for names because:
--
--  - They represent an illegal compilation unit added to the environment.
--
--  - They are referenced by some existing unit, but the program text for the
--    referenced unit has never been supplied, compiled, or otherwise
--    inserted into the environment.
--
--  - They represent a separate subunit that has never been supplied,
--    compiled, or otherwise inserted into the environment.
--
--  - The unit may have existed at one time but the semantic information is no
--    longer available.  It may be inconsistent, have been removed by some
--    user or Ada environment operations, or simply have been lost as the
--    result of some sort of failure.
--
-------------------------------------------------------------------------------
--  10.2 function Unit_Class
-------------------------------------------------------------------------------

   function Unit_Class (Compilation_Unit : in Asis.Compilation_Unit)
                       return Asis.Unit_Classes;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the compilation unit to query
--
--  Returns the Unit_Classes value of the compilation unit.
--  Returns Not_A_Class for a Nil_Compilation_Unit.
--
--  All Unit_Kinds are expected.
--

-------------------------------------------------------------------------------
--  10.3 function Unit_Origin
-------------------------------------------------------------------------------

   function Unit_Origin (Compilation_Unit : in Asis.Compilation_Unit)
                   return Asis.Unit_Origins;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the compilation unit to query
--
--  Returns the Unit_Origins value of the unit.
--  Returns Not_An_Origin for a compilation_unit whose Unit_Kind is
--  Not_A_Unit, An_Unknown_Unit, A_Nonexistent_Declaration, or
--  A_Nonexistent_Body.
--
--  All Unit_Kinds are expected.
--
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
--  10.4 function Enclosing_Context
-------------------------------------------------------------------------------

   function Enclosing_Context (Compilation_Unit : in Asis.Compilation_Unit)
                              return Asis.Context;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit whose Context is required
--
--  Returns the Context containing the compilation unit.
--
--  Compilation units always remember the ASIS Context and Container from
--  which they were obtained.
--
--  Because Context is limited private, this function is only intended to be
--  used to supply a Context parameter for other queries.  This conveniently
--  eliminates the need to make the original Context visible at the place of
--  each call where a Context parameter is required.
--
--  Two Compilation_Unit values, that represent the same physical compilation
--  units (same Ada implementor Context implementation unit value) will test as
--  Is_Equal, but not Is_Identical, if they were obtained from different open
--  ASIS Context variables.
--
--  Raises ASIS_Inappropriate_Compilation_Unit if the unit is a
--  Nil_Compilation_Unit.
--
-------------------------------------------------------------------------------
--  10.5 function Enclosing_Container
-------------------------------------------------------------------------------

   function Enclosing_Container (Compilation_Unit : in Asis.Compilation_Unit)
                           return Asis.Ada_Environments.Containers.Container;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit whose Container is required
--
--  Returns the Container of the Context containing the compilation unit.
--  Compilation units always remember the ASIS Context and Container from
--  which they were obtained.
--
--  Raises ASIS_Inappropriate_Compilation_Unit if the unit is a
--  Nil_Compilation_Unit.
--

-------------------------------------------------------------------------------
--  10.6 function Library_Unit_Declaration
-------------------------------------------------------------------------------

   function Library_Unit_Declaration (Name        : in Wide_String;
                                      The_Context : in Asis.Context)
                                      return Asis.Compilation_Unit;

-------------------------------------------------------------------------------
--  Name        - Specifies the defining program unit name
--  The_Context - Specifies a program Context environment
--
--  Returns the library_unit_declaration or library_unit_renaming_declaration
--  with the name, contained in The_Context.
--
--  This query will never return a unit with A_Configuration_Compilation or
--  a nonexistent unit kind. It will never return a unit with A_Procedure_Body
--  or A_Function_Body unit kind even though the unit is interpreted as both
--  the declaration and body of a library procedure or library function.
--  (Reference Manual 10.1.4(4).
--
--  A Nil_Compilation_Unit is returned if no such declaration exists.
--
--  Any non-Nil result will have an Enclosing_Context value that Is_Identical
--  to the Context.  Never returns a unit with a nonexistent unit kind.
--
-------------------------------------------------------------------------------
--  10.7 function Compilation_Unit_Body
-------------------------------------------------------------------------------

   function Compilation_Unit_Body (Name        : in Wide_String;
                                   The_Context : in Asis.Context)
                                   return Asis.Compilation_Unit;

-------------------------------------------------------------------------------
--  Name        - Specifies the defining_program_unit_name
--  The_Context - Specifies a program Context environment
--
--  Returns the library_unit_body or subunit with the name, contained
--  in the library.
--
--  A Nil_Compilation_Unit is returned if no such body exists.
--
--  Any non-Nil result will have an Enclosing_Context value that Is_Identical
--  to The_Context.  Never returns a unit with a nonexistent unit kind.
--
-------------------------------------------------------------------------------
--  10.8 function Library_Unit_Declarations
-------------------------------------------------------------------------------

   function Library_Unit_Declarations (The_Context : in Asis.Context)
                                      return Asis.Compilation_Unit_List;

-------------------------------------------------------------------------------
--  The_Context - Specifies a program Context environment
--
--  Returns a list of all library_unit_declaration and
--  library_unit_renaming_declaration elements contained in The_Context.
--  Individual units will appear only once in an order that is not defined.
--
--  A Nil_Compilation_Unit_List is returned if there are no declarations of
--  library units within The_Context.
--
--  This query will never return a unit with A_Configuration_Compilation or
--  a nonexistent unit kind. It will never return a unit with A_Procedure_Body
--  or A_Function_Body unit kind even though the unit is interpreted as both
--  the declaration and body of a library procedure or library function.
--  (Reference Manual 10.1.4(4).
--
--  All units in the result will have an Enclosing_Context value that
--  Is_Identical to The_Context.
--
-------------------------------------------------------------------------------
--  10.9 function Compilation_Unit_Bodies
-------------------------------------------------------------------------------

   function Compilation_Unit_Bodies (The_Context : in Asis.Context)
                                    return Asis.Compilation_Unit_List;

-------------------------------------------------------------------------------
--  The_Context - Specifies a program Context environment
--
--  Returns a list of all library_unit_body and subunit elements contained in
--  The_Context.  Individual units will appear only once in an order that
--  is not defined.
--
--  A Nil_Compilation_Unit_List is returned if there are no bodies within
--  The_Context.
--
--  This query will never return a unit with A_Configuration_Compilation or
--  a nonexistent unit kind.
--
--  All units in the result will have an Enclosing_Context value that
--  Is_Identical to The_Context.
--
-------------------------------------------------------------------------------
--  10.10 function Compilation_Units
-------------------------------------------------------------------------------

   function Compilation_Units (The_Context : in Asis.Context)
                              return Asis.Compilation_Unit_List;

-------------------------------------------------------------------------------
--  The_Context - Specifies a program Context environment
--
--  Returns a list of all compilation units contained in The_Context.
--  Individual units will appear only once in an order that is not defined.
--
--  A Nil_Compilation_Unit_List is returned if there are no units within
--  The_Context.
--
--  This query will never return a unit with A_Configuration_Compilation or
--  a nonexistent unit kind.
--
--  All units in the result will have an Enclosing_Context value that
--  Is_Identical to The_Context.
--
-------------------------------------------------------------------------------
--  10.11 function Corresponding_Children
-------------------------------------------------------------------------------

   function Corresponding_Children (Library_Unit : in Asis.Compilation_Unit)
                     return Asis.Compilation_Unit_List;

   function Corresponding_Children (Library_Unit : in Asis.Compilation_Unit;
                                    The_Context  : in Asis.Context)
                     return Asis.Compilation_Unit_List;

-------------------------------------------------------------------------------
--  Library_Unit - Specifies the library unit whose children are desired
--  The_Context  - Specifies a program Context environment
--
--  Returns a list of the child units for the given parent library unit.
--
--  Both the declaration and body (if any) of each child unit are returned.
--  Descendants beyond immediate children (i.e., children of children) are not
--  returned by this query.
--
--  Use the compilation unit relationship queries
--  with a Relation_Kinds of Descendants to create a list of children, children
--  of children, and so on.
--
--  Returns a Nil_Compilation_Unit_List for all library unit arguments that
--  do not have any child units contained in The_Context.
--
--  These two function calls will always produce identical results:
--
--      Units := Corresponding_Children ( Unit );
--      Units := Corresponding_Children ( Unit, Enclosing_Context ( Unit ));
--
--  Any non-Nil result will have an Enclosing_Context value that Is_Identical
--  to The_Context.
--
--  The Enclosing_Context for any non-Nil result will always be The_Context,
--  regardless of the Enclosing_Context value for the Library_Unit argument.
--  This query is one means of obtaining (Is_Equal) child units
--  from separate ASIS Context values whose underlying implementations
--  overlap.
--
--  Appropriate Unit_Kinds:
--       A_Package
--       A_Generic_Package
--       A_Package_Instance
--
--  Returns Unit_Kinds:
--       A_Procedure
--       A_Function
--       A_Package
--       A_Generic_Procedure
--       A_Generic_Function
--       A_Generic_Package
--       A_Procedure_Instance
--       A_Function_Instance
--       A_Package_Instance
--       A_Procedure_Renaming
--       A_Function_Renaming
--       A_Package_Renaming
--       A_Generic_Procedure_Renaming
--       A_Generic_Function_Renaming
--       A_Generic_Package_Renaming
--       A_Procedure_Body
--       A_Function_Body
--       A_Package_Body
--       An_Unknown_Unit
--
--  If the declaration of a child is inconsistent with the argument of the
--  query, neither the declaration nor the body is returned.  If the
--  declaration of a child is consistent with the argument, but the body
--  is not, the declaration is returned, and for the body, the result of
--  the Corresponding_Body query applied to the declaration is returned.
--
-------------------------------------------------------------------------------
--  10.12 function Corresponding_Parent_Declaration
-------------------------------------------------------------------------------

   function Corresponding_Parent_Declaration
               (Library_Unit : in Asis.Compilation_Unit)
               return Asis.Compilation_Unit;

   function Corresponding_Parent_Declaration
               (Library_Unit : in Asis.Compilation_Unit;
                The_Context  : in Asis.Context)
               return Asis.Compilation_Unit;

-------------------------------------------------------------------------------
--  Library_Unit - Specifies the unit whose parent is desired
--  The_Context  - Specifies a program Context environment
--
--  Returns the parent unit of the given library unit.
--
--  Returns a Nil_Compilation_Unit if the Library_Unit argument represents
--  package Standard.  Root Library_Unit arguments return the package Standard.
--
--  Returns A_Nonexistent_Declaration when the Library_Unit has a
--  parent_unit_name denoted in the defining_program_unit_name but the parent
--  unit is not contained in The_Context.
--
--  These two function calls will always produce identical results:
--
--      Unit := Corresponding_Parent_Declaration ( Unit );
--      Unit := Corresponding_Parent_Declaration ( Unit,
--                                                 Enclosing_Context ( Unit ));
--
--  Any non-Nil result will have an Enclosing_Context value that Is_Identical
--  to The_Context.
--
--  The Enclosing_Context for any non-Nil result will always be The_Context,
--  regardless of the Enclosing_Context value for the Library_Unit
--  argument.  This query is one means of obtaining (Is_Equal) parent units
--  from separate ASIS Context values whose underlying implementations
--  overlap.
--
--  Appropriate Unit_Kinds:
--       A_Procedure
--       A_Function
--       A_Package
--       A_Generic_Procedure
--       A_Generic_Function
--       A_Generic_Package
--       A_Procedure_Instance
--       A_Function_Instance
--       A_Package_Instance
--       A_Procedure_Renaming
--       A_Function_Renaming
--       A_Package_Renaming
--       A_Generic_Procedure_Renaming
--       A_Generic_Function_Renaming
--       A_Generic_Package_Renaming
--       A_Procedure_Body
--       A_Function_Body
--       A_Package_Body
--
--  Returns Unit_Kinds:
--       Not_A_Unit
--       A_Package
--       A_Generic_Package
--       A_Package_Instance
--       A_Nonexistent_Declaration
--       An_Unknown_Unit
--
--  If a parent is inconsistent with a child passed as the argument,
--  A_Nonexistent_Declaration shall be returned.
--
-------------------------------------------------------------------------------
--  10.13 function Corresponding_Declaration
-------------------------------------------------------------------------------

   function Corresponding_Declaration
               (Library_Item : in Asis.Compilation_Unit)
               return Asis.Compilation_Unit;

   function Corresponding_Declaration
               (Library_Item : in Asis.Compilation_Unit;
                The_Context  : in Asis.Context)
               return Asis.Compilation_Unit;

-------------------------------------------------------------------------------
--  Library_Item - Specifies the library_item whose declaration is desired
--  The_Context  - Specifies a program Context environment
--
--  Returns the corresponding library_unit_declaration, if any, for the
--  library_unit_body.  The corresponding library unit is the unit upon which
--  the library_unit_body depends semantically.
--
--  Returns a unit that Is_Equal to the argument if:
--
--  - the argument is a library_unit_declaration,
--    a library_unit_renaming_declaration, or a subunit.
--
--  - the argument is A_Nonexistent_Declaration or A_Nonexistent_Body.
--
--  Returns a Nil_Compilation_Unit for library_unit_body arguments that do
--  not have a corresponding library unit contained in The_Context.
--
--  All Unit_Kinds are appropriate except Not_A_Unit.
--
--  Appropriate Unit_Kinds:
--       A_Procedure_Body
--       A_Function_Body
--       A_Package_Body
--       An_Unknown_Unit            -- See Implementation Permissions
--
--  Appropriate Unit_Kinds returning the argument Library_Item:
--       A_Procedure
--       A_Function
--       A_Package
--       A_Generic_Procedure
--       A_Generic_Function
--       A_Generic_Package
--       A_Procedure_Instance
--       A_Function_Instance
--       A_Package_Instance
--       A_Procedure_Renaming
--       A_Function_Renaming
--       A_Package_Renaming
--       A_Generic_Procedure_Renaming
--       A_Generic_Function_Renaming
--       A_Generic_Package_Renaming
--       A_Procedure_Body_Subunit
--       A_Function_Body_Subunit
--       A_Package_Body_Subunit
--       A_Task_Body_Subunit
--       A_Protected_Body_Subunit
--       A_Nonexistent_Declaration
--       A_Nonexistent_Body
--
--  Returns all Unit Kinds.
--
--  If the declaration of an argument Element is inconsistent with the
--  argument, A_Nonexistent_Declaration shall be returned. (For a unit
--  A_Procedure_Body or A_Function_Body kind, the solution may be in any
--  case, to return Nil_Compilation_Unit if the unit is of
--  A_Public_Declaration_And_Body kind.)
--
--  |IR Implementation Requirements:
--  |IR
--  |IR Any non-Nil result will have an Enclosing_Context value that
--  |IR Is_Identical to The_Context.
--  |IR
--  |IR These two function calls will always produce identical results:
--  |IR
--  |IR    Unit := Corresponding_Declaration( Unit );
--  |IR    Unit := Corresponding_Declaration( Unit, Enclosing_Context( Unit ));
--  |IR
--  |IR The Enclosing_Context for any non-Nil result will always be
--  |IR The_Context, regardless of the Enclosing_Context value for the
--  |IR Library_Item argument.  This query is one means of obtaining
--  |IR corresponding (Is_Equal) units from separate ASIS Context values
--  |IR whose underlying implementations overlap.
--
--  |IP Implementation Permissions:
--  |IP
--  |IP The handling of An_Unknown_Unit is implementation specific.  The
--  |IP expected use for An_Unknown_Unit is to hide proprietary implementation
--  |IP details contained within unit bodies.  In these cases, it should be
--  |IP possible to obtain an appropriate library_unit_declaration when
--  |IP starting with An_Unknown_Unit.  Some implementors may choose to simply
--  |IP return the An_Unknown_Unit argument in all cases.
--

-------------------------------------------------------------------------------
--  10.14 function Corresponding_Body
-------------------------------------------------------------------------------

   function Corresponding_Body
               (Library_Item : in Asis.Compilation_Unit)
               return Asis.Compilation_Unit;

   function Corresponding_Body
               (Library_Item : in Asis.Compilation_Unit;
                The_Context  : in Asis.Context)
               return Asis.Compilation_Unit;

-------------------------------------------------------------------------------
--  Library_Item - Specifies the library_item whose body is desired
--  The_Context  - Specifies a program Context environment
--
--  Returns the corresponding library_unit_body, if any, for the
--  library_unit_declaration.  The corresponding library_unit_body is the unit
--  that depends semantically on the library_unit_declaration.
--
--  Returns a unit that Is_Equal to the argument if:
--
--  - the argument is a an instance of a library_unit_declaration,
--    a library_unit_body, a library_unit_renaming_declaration, or a subunit.
--
--  - the argument is A_Nonexistent_Declaration or A_Nonexistent_Body.
--
--  Returns a Nil_Compilation_Unit for library_unit_declaration arguments that
--  do not have a corresponding library_unit_body contained in The_Context.
--
--  All Unit_Kinds are appropriate except Not_A_Unit.
--
--  Appropriate Unit_Kinds:
--       A_Procedure
--       A_Function
--       A_Package
--       A_Generic_Procedure
--       A_Generic_Function
--       A_Generic_Package
--       An_Unknown_Unit            -- See Implementation Permissions
--
--  Appropriate Unit_Kinds returning the argument Library_Item:
--       A_Procedure_Body
--       A_Function_Body
--       A_Package_Body
--       A_Procedure_Instance
--       A_Function_Instance
--       A_Package_Instance
--       A_Procedure_Renaming
--       A_Function_Renaming
--       A_Package_Renaming
--       A_Generic_Procedure_Renaming
--       A_Generic_Function_Renaming
--       A_Generic_Package_Renaming
--       A_Procedure_Body_Subunit
--       A_Function_Body_Subunit
--       A_Package_Body_Subunit
--       A_Task_Body_Subunit
--       A_Protected_Body_Subunit
--       A_Nonexistent_Declaration
--       A_Nonexistent_Body
--
--  Returns all Unit Kinds.
--
--  If the argument Element requires a body to be presented to make up a
--  complete partition containing this Element, but The_Context  does not
--  contain the corresponding body, or the body contained in The_Context
--  is inconsistent with the argument Element, A_Nonexistent_Body shall
--  be returned.
--
--  |IR Implementation Requirements:
--  |IR
--  |IR Any non-Nil result will have an Enclosing_Context value that
--  |IR Is_Identical to The_Context.
--  |IR
--  |IR These two function calls will always produce identical results:
--  |IR
--  |IR     Unit := Corresponding_Body( Unit );
--  |IR     Unit := Corresponding_Body( Unit, Enclosing_Context ( Unit ));
--  |IR
--  |IR The Enclosing_Context for any non-Nil result will always be
--  |IR The_Context, regardless of the Enclosing_Context value for the
--  |IR Library_Item argument.  This query is one means of obtaining
--  |IR corresponding (Is_Equal) units from separate ASIS Context values
--  |IR whose underlying implementations overlap.
--
--  |IP Implementation Permissions:
--  |IP
--  |IP The handling of An_Unknown_Unit is implementation specific.  The
--  |IP expected use for An_Unknown_Unit is to hide proprietary implementation
--  |IP details contained within unit bodies.  In some cases, it could be
--  |IP possible to obtain an appropriate library_unit_body when starting with
--  |IP An_Unknown_Unit.  Some implementors may choose to simply return the
--  |IP An_Unknown_Unit argument in all cases.
--
-------------------------------------------------------------------------------
--  10.15 function Is_Nil
-------------------------------------------------------------------------------

   function Is_Nil (Right : in Asis.Compilation_Unit)
                   return Boolean;

-------------------------------------------------------------------------------
--  Right   - Specifies the unit to test
--
--  Returns True if the compilation_unit is a Nil_Compilation_Unit.
--
-------------------------------------------------------------------------------
--  10.16 function Is_Nil
-------------------------------------------------------------------------------

   function Is_Nil (Right : in Asis.Compilation_Unit_List)
                   return Boolean;

-------------------------------------------------------------------------------
--  Right   - Specifies the unit list to test
--
--  Returns True if the compilation_unit list has a length of zero.
--
-------------------------------------------------------------------------------
--  10.17 function Is_Equal
-------------------------------------------------------------------------------

   function Is_Equal (Left  : in Asis.Compilation_Unit;
                      Right : in Asis.Compilation_Unit) return Boolean;

-------------------------------------------------------------------------------
--  Left    - Specifies the first unit to compare
--  Right   - Specifies the second unit to compare
--
--  Returns True if Left and Right represent the same physical compilation unit
--  or if both are Nil_Compilation_Unit values.  The two units may or may not
--  be from the same ASIS Context variable. ("The same physical compilation
--  unit" have the same version, as defined by Reference Manual E.3(5)
--  and the same program text.)
--
--  Two nonexistent units are Is_Equal if they have the same Name and
--  Unit_Kind.
--

-------------------------------------------------------------------------------
--  10.18 function Is_Identical
-------------------------------------------------------------------------------

   function Is_Identical (Left  : in Asis.Compilation_Unit;
                          Right : in Asis.Compilation_Unit) return Boolean;

-------------------------------------------------------------------------------
--  Left    - Specifies the first unit to compare
--  Right   - Specifies the second unit to compare
--
--  Returns True if Left and Right represent the same physical compilation
--  unit, from the same open ASIS Context variable, or, if both are
--  Nil_Compilation_Unit values. ("The same physical compilation
--  unit" have the same version, as defined by Reference Manual E.3(5)
--  and the same program text.)
--
--  Two nonexistent units are Is_Identical if they have the same
--  Unique_Name and the same Enclosing_Context.
--
-------------------------------------------------------------------------------
--  10.19 function Unit_Full_Name
-------------------------------------------------------------------------------

   function Unit_Full_Name (Compilation_Unit : in Asis.Compilation_Unit)
                           return Wide_String;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit whose name is desired
--
--  Returns the string image of the fully expanded Ada name of the given
--  compilation unit.  This may be a simple name ("A") of a root library
--  unit, or an expanded name ("A.B") of a subunit or non-root child unit.
--  An expanded name shall contain the full parent_unit_name as its prefix.

--  Returns a null string only if A_Configuration_Compilation or a
--  Nil_Compilation_Unit is given.
--
--  The case of names returned by this query may vary between implementations.
--  Implementors are encouraged, but not required, to return names in the
--  same case as was used in the original compilation text.
--
--  All Unit_Kinds are appropriate.
--
-------------------------------------------------------------------------------
--  10.20 function Unique_Name
-------------------------------------------------------------------------------

   function Unique_Name
         (Compilation_Unit : in Asis.Compilation_Unit)
               return Wide_String;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit whose name is desired
--
--  Returns a string that uniquely identifies the given compilation unit
--  within the underlying Ada Context implementation.  The result may vary
--  depending on the ASIS implementation.  The unique name may include the name
--  and parameters of the Context, file system paths, library files, version
--  numbers, kind, or any other information that an implementation may need
--  to uniquely identify the compilation unit.
--
--  Returns a null string only if a Nil_Compilation_Unit is given.
--
--  All Unit_Kinds are appropriate.
--

-------------------------------------------------------------------------------
--  10.21 function Exist
-------------------------------------------------------------------------------

   function Exists (Compilation_Unit : in Asis.Compilation_Unit)
                   return Boolean;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit to test
--
--  Returns False for any unit with Not_A_Unit or nonexistent kind.
--  Returns True for all other unit kinds.
--
--  All Unit_Kinds are expected.
--
-------------------------------------------------------------------------------
--  10.22 function Can_Be_Main_Program
-------------------------------------------------------------------------------

   function Can_Be_Main_Program (Compilation_Unit : in Asis.Compilation_Unit)
                                return Boolean;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit to test
--
--  Returns True if the Compilation_Unit exists and is a subprogram
--  library_unit_declaration, library_unit_renaming_declaration, or
--  library_unit_body that can be used as a main subprogram.  See Reference
--  Manual 10.2(7).
--
--  Returns False otherwise.
--
--  Results of this function may vary according to the requirements an Ada
--  implementation may impose on a main subprogram.
--
--  All Unit_Kinds are expected.
--
-------------------------------------------------------------------------------
--  10.23 function Is_Body_Required
-------------------------------------------------------------------------------

   function Is_Body_Required (Compilation_Unit : in Asis.Compilation_Unit)
                                return Boolean;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit to test
--
--  Returns True if the Compilation_Unit exists and is a library
--  package_declaration that requires a body.  See Reference Manual 7.2(4).
--
--  All Unit_Kinds are expected.
--
-------------------------------------------------------------------------------
--  10.24 function Text_Name
-------------------------------------------------------------------------------

   function Text_Name (Compilation_Unit : in Asis.Compilation_Unit)
                     return Wide_String;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit whose text name is desired
--
--  Returns the name of the text, or other structure, that was the source
--  of the compilation that resulted in this Compilation_Unit.  Returns a
--  null string if the unit has a Nil or nonexistent kind, or if the text
--  name is not available for any reason.
--

--  Ada has no concept of source or text file.
--  Text_Name availability is a required feature of ASIS.
--  Results of this function may vary among implementations.
--
--  All Unit_Kinds are appropriate.
--
-------------------------------------------------------------------------------
--  10.25 function Text_Form
-------------------------------------------------------------------------------

   function Text_Form (Compilation_Unit : in Asis.Compilation_Unit)
                           return Wide_String;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit whose text form is desired
--
--  Returns the Form parameter (as for Text_Io.Open) for the text, or
--  other structure, that was the source of the compilation that resulted in
--  this Compilation_Unit.  Returns a null string if the unit has a Nil or
--  nonexistent kind, if the text was created with an empty Form parameter,
--  or if the text Form parameter value is not available for any reason.
--
--  Ada has no concept of source or text file.
--  Text_Form availability is a required feature of ASIS.
--  Results of this function may vary among implementations.
--
--  All Unit_Kinds are appropriate.
--
-------------------------------------------------------------------------------
--  10.26 function Object_Name
-------------------------------------------------------------------------------

   function Object_Name (Compilation_Unit : in Asis.Compilation_Unit)
                           return Wide_String;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit whose object name is desired
--
--  Returns the name of the object, or other structure, that contains the
--  binary result of the compilation for this Compilation_Unit.  Returns
--  a null string if the unit has a Nil or nonexistent kind, or if the
--  object name is not available for any reason.
--
--  All Unit_Kinds are appropriate.
--
-------------------------------------------------------------------------------
--  10.27 function Object_Form
-------------------------------------------------------------------------------

   function Object_Form (Compilation_Unit : in Asis.Compilation_Unit)
                             return Wide_String;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit whose object form is desired
--
--  Returns the Form parameter (as for Text_Io.Open) for the object, or
--  other structure, that was the machine-code result of the compilation of
--  this Compilation_Unit.  Returns a null string if the unit has a Nil or
--  nonexistent kind, if the object was created with an empty Form parameter,
--  or if the object Form parameter value is not available for any reason.
--
--  All Unit_Kinds are appropriate.
--

-------------------------------------------------------------------------------
--  10.28 function Compilation_Command_Line_Options
-------------------------------------------------------------------------------

   function Compilation_Command_Line_Options
               (Compilation_Unit : in Asis.Compilation_Unit)
               return Wide_String;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit to query
--
--  Returns the command line options used to compile the Compilation_Unit.
--  Returns null string if the unit has a Nil or nonexistent unit kind, or
--  if the command line options are not available for any reason.
--
--  All Unit_Kinds are appropriate.
--
-------------------------------------------------------------------------------
--  10.29 function Has_Attribute
-------------------------------------------------------------------------------

   function Has_Attribute (Compilation_Unit : in Asis.Compilation_Unit;
                           Attribute        : in Wide_String) return Boolean;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit to query
--  Attribute           - Specifies the name of the attribute to query
--
--  Returns True if the compilation unit has the given attribute.
--
--  Returns False if the unit is a Nil_Compilation_Unit argument, the
--  Attribute does not exist, or the implementation does not support
--  attributes.
--
--  All Unit_Kinds are expected.
--
--  Results of this query may vary across ASIS implementations.
--
-------------------------------------------------------------------------------
--  10.30 function Attribute_Value_Delimiter
-------------------------------------------------------------------------------

   function Attribute_Value_Delimiter return Wide_String;

-------------------------------------------------------------------------------
--  Returns the string used as a delimiter separating individual values
--  within the string Attribute_Values of a compilation unit.
--
--  Results of this query may vary across ASIS implementations.  The result
--  can be a null string for implementations that do not support attributes,
--  or that do not support more than one attribute.
--
-------------------------------------------------------------------------------
--  10.31 function Attribute_Values
-------------------------------------------------------------------------------

   function Attribute_Values
               (Compilation_Unit : in Asis.Compilation_Unit;
                Attribute        : in Wide_String)
               return Wide_String;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit to query
--  Attribute           - Specifies the name of the attribute to query
--
--  Returns a string containing zero or more images of values that are
--  associated with the given attribute.  When more than one value is returned,
--  the Attribute_Value_Delimiter string is used to separate the individual
--  values.  Returns a null string if the unit is a Nil_Compilation_Unit
--  argument, the unit has no values for this Attribute, or the implementation
--  does not support attributes.
--
--  All Unit_Kinds are appropriate.
--
--  Results of this query may vary across ASIS implementations.
--
-------------------------------------------------------------------------------
--  10.32 function Subunits
-------------------------------------------------------------------------------

   function Subunits (Parent_Body : in Asis.Compilation_Unit)
                     return Asis.Compilation_Unit_List;

   function Subunits (Parent_Body : in Asis.Compilation_Unit;
                      The_Context : in Asis.Context)
                     return Asis.Compilation_Unit_List;

-------------------------------------------------------------------------------
--  Parent_Body - Specifies the parent unit to query
--  The_Context - Specifies the program Context to use for context
--
--  Returns a complete list of subunit values, with one value for each body
--  stub that appears in the given Parent_Body.  Returns a
--  Nil_Compilation_Unit_List if the parent unit does not contain any body
--  stubs.  Every unit in the result will have an Enclosing_Context that
--  Is_Identical to The_Context.
--
--  These two function calls will always produce identical results:
--
--      SUnits := Subunits ( PUnit );
--      SUnits := Subunits ( PUnit, Enclosing_Context ( PUnit ));
--
--  The result may include unit values with a nonexistent unit kind.  It
--  includes values for subunits that exist in The_Context as
--  well as values for subunits that do not exist, but whose name can be
--  deduced from the body stub and the name of the parent unit.  These
--  nonexistent units are known to be library_unit_body elements so their unit
--  kind is A_Nonexistent_Body.
--
--  Subunit lists are also available through the Semantic_Dependence_Order
--  query using the Family relation.
--
--  Raises ASIS_Inappropriate_Compilation_Unit if the unit is a
--  Nil_Compilation_Unit.
--
--  If a subunit is absent or if it is inconsistent with the argument Element,
--  A_Nonexistent_Body shall be returned for it.
--
--  Returns Unit_Kinds:
--       A_Nonexistent_Body
--       A_Procedure_Body_Subunit
--       A_Function_Body_Subunit
--       A_Package_Body_Subunit
--       A_Task_Body_Subunit
--       A_Protected_Body_Subunit
--
-------------------------------------------------------------------------------
--  10.33 function Corresponding_Subunit_Parent_Body
-------------------------------------------------------------------------------

   function Corresponding_Subunit_Parent_Body
              (Subunit : in Asis.Compilation_Unit)
               return Asis.Compilation_Unit;

   function Corresponding_Subunit_Parent_Body
              (Subunit     : in Asis.Compilation_Unit;
               The_Context : in Asis.Context)
               return Asis.Compilation_Unit;

-------------------------------------------------------------------------------
--  Subunit     - Specifies the subunit to query
--  The_Context - Specifies the program Context to use for context
--

--  Returns the Compilation_Unit containing the body stub of the given Subunit.
--  Returns a Nil_Compilation_Unit if the subunit parent is not contained in
--  The_Context.  Any non-Nil result will have an Enclosing_Context value that
--  Is_Identical to The_Context.
--
--  These two function calls will always produce identical results:
--
--      PUnit := Corresponding_Subunit_Parent_Body ( SUnit );
--      PUnit := Corresponding_Subunit_Parent_Body ( SUnit,
--                                         Enclosing_Context ( SUnit ));
--
--  Appropriate Unit_Kinds:
--       A_Procedure_Body_Subunit
--       A_Function_Body_Subunit
--       A_Package_Body_Subunit
--       A_Task_Body_Subunit
--       A_Protected_Body_Subunit
--
--  Returns Unit_Kinds:
--       A_Procedure_Body
--       A_Function_Body
--       A_Package_Body
--       A_Procedure_Body_Subunit
--       A_Function_Body_Subunit
--       A_Package_Body_Subunit
--       A_Task_Body_Subunit
--       A_Protected_Body_Subunit
--
--  If the corresponding body does not exist in The_Context, or if it exists,
--  but is inconsistent with the argument Element, then A_Nonexistent_Body
--  shall be returned.
--
-------------------------------------------------------------------------------
--  To locate the parent of a subunit that is not itself a subunit,
--  repeatedly call Corresponding_Subunit_Parent_Body until a unit that
--  is not a subunit is returned.
--
-------------------------------------------------------------------------------
--  10.34 function Debug_Image
-------------------------------------------------------------------------------

   function Debug_Image (Compilation_Unit : in Asis.Compilation_Unit)
                        return Wide_String;

-------------------------------------------------------------------------------
--  Compilation_Unit  - Specifies a unit to convert
--
--  Returns a string value containing implementation-defined debug
--  information associated with the compilation unit.
--
--  The return value uses Asis.Text.Delimiter_Image to separate the lines
--  of multi-line results.  The return value does not end with
--  Asis.Text.Delimiter_Image.
--
--  These values are intended for two purposes.  They are suitable for
--  inclusion in problem reports sent to the ASIS implementor.  They can be
--  presumed to contain information useful when debugging the implementation
--  itself. They are also suitable for use by the ASIS application when
--  printing simple application debugging messages during application
--  development.  They are intended to be, to some worthwhile degree,
--  intelligible to the user.
--
-------------------------------------------------------------------------------

end Asis.Compilation_Units;


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
