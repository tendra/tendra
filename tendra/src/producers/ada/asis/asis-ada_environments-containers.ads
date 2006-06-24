-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  9    package Asis.Ada_Environments.Containers
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package Asis.Ada_Environments.Containers is

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Ada_Environments.Containers
--
--  If an Ada implementation supports the notion of a program library or
--  "library" as specified in Subclause 10(2) of the Ada Reference Manual,
--  then an ASIS Context value can be mapped onto one or more implementor
--  libraries represented by Containers.
--
-------------------------------------------------------------------------------
--  9.1  type Container
-------------------------------------------------------------------------------
--
--  The Container abstraction is a logical collection of compilation units.
--  For example, one container might hold compilation units which include Ada
--  predefined library units, another container might hold implementation-
--  defined packages. Alternatively, there might be 26 containers, each holding
--  compilation units that begin with their respective letter of the alphabet.
--  The point is that no implementation-independent semantics are associated
--  with a container; it is simply a logical collection.
--
--  ASIS implementations shall minimally map the Asis.Context to a list of
--  one ASIS Container whose Name is that of the Asis.Context Name.
-------------------------------------------------------------------------------

   type Container is private;
   Nil_Container : constant Container;

   function "=" (Left  : in Container;
                 Right : in Container)
                 return Boolean is abstract;

-------------------------------------------------------------------------------
--  9.2  type Container_List
-------------------------------------------------------------------------------

   type Container_List is
      array (List_Index range <>) of Container;

-------------------------------------------------------------------------------
--  9.3  function Defining_Containers
-------------------------------------------------------------------------------

   function Defining_Containers (The_Context : in Asis.Context)
      return Container_List;

-------------------------------------------------------------------------------
--  The_Context - Specifies the Context to define
--
--  Returns a Container_List value that defines the single environment Context.
--  Each Container will have an Enclosing_Context that Is_Identical to the
--  argument The_Context.  The order of Container values in the list is not
--  defined.
--
--  Returns a minimal list of length one if the ASIS Ada implementation does
--  not support the concept of a program library.  In this case, the Container
--  will have the same name as the given Context.
--
--  Raises ASIS_Inappropriate_Context if The_Context is not open.
--

-------------------------------------------------------------------------------
--  9.4  function Enclosing_Context
-------------------------------------------------------------------------------

   function Enclosing_Context (The_Container : in Container)
      return Asis.Context;

-------------------------------------------------------------------------------
--  The_Container - Specifies the Container to query
--
--  Returns the Context value associated with the Container.
--
--  Returns the Context for which the Container value was originally obtained.
--  Container values obtained through the Defining_Containers query will always
--  remember the Context from which they were defined.
--
--  Because Context is limited private, this function is only intended to be
--  used to supply a Context parameter for other queries.
--
--  Raises ASIS_Inappropriate_Container if the Container is a Nil_Container.
--
-------------------------------------------------------------------------------
--  9.5  function Library_Unit_Declaration
-------------------------------------------------------------------------------

   function Library_Unit_Declarations (The_Container : in Container)
                                      return Asis.Compilation_Unit_List;

-------------------------------------------------------------------------------
--  The_Container - Specifies the Container to query
--
--  Returns a list of all library_unit_declaration and
--  library_unit_renaming_declaration  elements contained in the Container.
--  Individual units will appear only once in an order that is not defined.
--
--  A Nil_Compilation_Unit_List is returned if there are no declarations of
--  library units within the Container.
--
--  This query will never return a unit with A_Configuration_Compilation or
--  a Nonexistent unit kind. It will never return a unit with A_Procedure_Body
--  or A_Function_Body unit kind even though the unit is interpreted as both
--  the declaration and body of a library procedure or library function.
--  (Reference Manual 10.1.4(4).
--
--  All units in the result will have an Enclosing_Container value that
--  Is_Identical to the Container.
--
--  Raises ASIS_Inappropriate_Context if the Enclosing_Context(Container)
--  is not open.
--

-------------------------------------------------------------------------------
--  9.6  function Compilation_Unit_Bodies
-------------------------------------------------------------------------------

   function Compilation_Unit_Bodies (The_Container : in Container)
                                    return Asis.Compilation_Unit_List;

-------------------------------------------------------------------------------
--  The_Container - Specifies the Container to query
--
--  Returns a list of all library_unit_body and subunit elements contained in
--  the Container.  Individual units will appear only once in an order that is
--  not defined.
--
--  A Nil_Compilation_Unit_List is returned if there are no bodies within the
--  Container.
--
--  This query will never return a unit with A_Configuration_Compilation or
--  a nonexistent unit kind.
--
--  All units in the result will have an Enclosing_Container value that
--  Is_Identical to the Container.
--
--  Raises ASIS_Inappropriate_Context if the Enclosing_Context(Container)
--  is not open.
--
-------------------------------------------------------------------------------
--  9.7  function Compilation_Units
-------------------------------------------------------------------------------

   function Compilation_Units (The_Container : in Container)
                              return Asis.Compilation_Unit_List;

-------------------------------------------------------------------------------
--  The_Container - Specifies the Container to query
--
--  Returns a list of all compilation units contained in the Container.
--  Individual units will appear only once in an order that is not defined.
--
--  A Nil_Compilation_Unit_List is returned if there are no units within the
--  Container.
--
--  This query will never return a unit with A_Configuration_Compilation or
--  a nonexistent unit kind.
--
--  All units in the result will have an Enclosing_Container value that
--  Is_Identical to the Container.
--
--  Raises ASIS_Inappropriate_Context if the Enclosing_Context(Container)
--  is not open.
--
-------------------------------------------------------------------------------
--  9.8  function Is_Equal
-------------------------------------------------------------------------------

   function Is_Equal (Left  : in Container;
                      Right : in Container) return Boolean;

-------------------------------------------------------------------------------
--  Left    - Specifies the first Container
--  Right   - Specifies the second Container
--
--  Returns True if Left and Right designate Container values that contain the
--  same set of compilation units.  The Container values may have been defined
--  from different Context values.
--

-------------------------------------------------------------------------------
--  9.9  function Is_Identical
-------------------------------------------------------------------------------

   function Is_Identical (Left  : in Container;
                          Right : in Container) return Boolean;

-------------------------------------------------------------------------------
--  Left    - Specifies the first Container
--  Right   - Specifies the second Container
--
--  Returns True if Is_Equal(Left, Right) and the Container values have been
--  defined from Is_Equal Context values.
--
-------------------------------------------------------------------------------
--  9.10 function Name
-------------------------------------------------------------------------------

   function Name (The_Container : in Container) return Wide_String;

-------------------------------------------------------------------------------
--  The_Container - Specifies the Container to name
--
--  Returns the Name value associated with the Container.
--
--  Returns a null string if the Container is a Nil_Container.
--
-------------------------------------------------------------------------------

private

   type Container is record
      The_Context : Asis.Context;
   end record;

   Nil_Container : constant Container := (The_Context => Asis.Nil_Context);

end Asis.Ada_Environments.Containers;


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
