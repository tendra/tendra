-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  21  package Asis.Ids
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

with Ada.Strings.Wide_Unbounded;
package Asis.Ids is

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Ids provides support for permanent unique Element "Identifiers" (Ids).
--  An Id is an efficient way for a tool to reference an ASIS element.  The Id
--  is permanent from session to session provided that the Ada compilation
--  environment is unchanged.
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  This package encapsulates a set of operations and queries that implement
--  the ASIS Id abstraction.  An Id is a way of identifying a particular
--  Element, from a particular Compilation_Unit, from a particular Context.
--  Ids can be written to files.  Ids can be read from files and converted into
--  an Element value with the use of a suitable open Context.
--
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  21.1 type Id
-------------------------------------------------------------------------------
--  The Ada element Id abstraction (a private type).
--
--  The Id type is a distinct abstract type representing permanent "names"
--  that correspond to specific Element values.
--
--  These names can be written to files, retrieved at a later time, and
--  converted to Element values.
-------------------------------------------------------------------------------
--  ASIS Ids are a means of identifying particular Element values obtained from
--  a particular physical compilation unit.  Ids are "relative names".  Each Id
--  value is valid (is usable, makes sense, can be interpreted) only in the
--  context of an appropriate open ASIS Context.
--
--  Id shall be an undiscriminated private type, or, shall be derived from an
--  undiscriminated private type.  It shall be declared as a new type or as a
--  subtype of an existing type.
-------------------------------------------------------------------------------

   type Id is private;
   Nil_Id : constant Id;

   function "=" (Left  : in Id;
                 Right : in Id)
                 return Boolean is abstract;


-------------------------------------------------------------------------------
--  21.2        function Hash
-------------------------------------------------------------------------------

   function Hash (The_Id : in Id) return Asis.ASIS_Integer;

-------------------------------------------------------------------------------
--  21.3        function "<"
-------------------------------------------------------------------------------

   function "<" (Left  : in Id;
                 Right : in Id) return Boolean;

-------------------------------------------------------------------------------
--  21.4        function ">"
-------------------------------------------------------------------------------

   function ">" (Left  : in Id;
                 Right : in Id) return Boolean;


-------------------------------------------------------------------------------
--  21.5        function Is_Nil
-------------------------------------------------------------------------------

   function Is_Nil (Right : in Id) return Boolean;

-------------------------------------------------------------------------------
--  Right   - Specifies the Id to check
--
--  Returns True if the Id is the Nil_Id.
--
-------------------------------------------------------------------------------
--  21.6        function Is_Equal
-------------------------------------------------------------------------------

   function Is_Equal (Left  : in Id;
                      Right : in Id) return Boolean;

-------------------------------------------------------------------------------
--  Left    - Specifies the left Id to compare
--  Right   - Specifies the right Id to compare
--
--  Returns True if Left and Right represent the same physical Id, from the
--  same physical compilation unit.  The two Ids convert
--  to Is_Identical Elements when converted with the same open ASIS Context.
--
-------------------------------------------------------------------------------
--  21.7        function Create_Id
-------------------------------------------------------------------------------

   function Create_Id (Element : in Asis.Element) return Id;

-------------------------------------------------------------------------------
--  Element - Specifies any Element value whose Id is desired
--
--  Returns a unique Id value corresponding to this Element, from the
--  corresponding Enclosing_Compilation_Unit and the corresponding
--  Enclosing_Context.  The Id value will not be equal ("=") to the Id value
--  for any other Element value unless the two Elements are Is_Identical.
--
--  Nil_Id is returned for a Nil_Element.
--
--  All Element_Kinds are appropriate.
--
-------------------------------------------------------------------------------
--  21.8        function Create_Element
-------------------------------------------------------------------------------

   function Create_Element (The_Id      : in Id;
                            The_Context : in Asis.Context)
                          return Asis.Element;

-------------------------------------------------------------------------------
--  The_Id      - Specifies the Id to be converted to an Element
--  The_Context - Specifies the Context containing the Element with this Id
--
--  Returns the Element value corresponding to The_Id.  The_Id shall
--  correspond to an Element available from a Compilation_Unit contained by
--  (referencible through) The_Context.
--
--  Raises ASIS_Inappropriate_Element if the Element value is not available
--  though The_Context.  The Status is Value_Error and the Diagnosis
--  string will attempt to indicate the reason for the failure.  (e.g., "Unit
--  is inconsistent", "No such unit", "Element is inconsistent (Unit
--  inconsistent)", etc.)
--

-------------------------------------------------------------------------------
--  21.9        function Debug_Image
-------------------------------------------------------------------------------

   function Debug_Image (The_Id : in Id) return Wide_String;

-------------------------------------------------------------------------------
--  The_Id  - Specifies an Id to convert
--
--  Returns a string value containing implementation-defined debug
--  information associated with the Id.
--
--  The return value uses Asis.Text.Delimiter_Image to separate the lines
--  of multi-line results.  The return value does not end with
--  Asis.Text.Delimiter_Image.
--
--  These values are intended for two purposes.  They are suitable for
--  inclusion in problem reports sent to the ASIS implementor.  They can
--  be presumed to contain information useful when debugging the
--  implementation itself. They are also suitable for use by the ASIS
--  application when printing simple application debugging messages during
--  application development.  They are intended to be, to some worthwhile
--  degree, intelligible to the user.
--
-------------------------------------------------------------------------------

private
   package W renames Ada.Strings.Wide_Unbounded;

   type Id is record
      Hash : Asis.ASIS_Integer;
      Unit : W.Unbounded_Wide_String;
   end record;

   Nil_Id : constant Id := (0, W.Null_Unbounded_Wide_String);

end Asis.Ids;


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
