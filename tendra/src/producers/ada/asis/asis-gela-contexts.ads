------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Object Oriented implementation of Context.

with Asis.Gela.Lists;                use Asis.Gela.Lists;
with Asis.Gela.Compilations;
with Ada.Strings.Wide_Unbounded;

package Asis.Gela.Contexts is

   type Concrete_Context_Node is new Context_Node with private;

   procedure Associate
     (The_Context : access Concrete_Context_Node;
      Name        : in     Wide_String;
      Parameters  : in     Wide_String);

   procedure Open       (The_Context : in out Concrete_Context_Node);
   procedure Close      (The_Context : in out Concrete_Context_Node);
   procedure Dissociate (The_Context : in out Concrete_Context_Node);

   function Is_Open (The_Context : Concrete_Context_Node) return Boolean;

   function Is_Equal
     (Left  : in Concrete_Context_Node;
      Right : in Concrete_Context_Node)
      return Boolean;

   function Has_Associations (The_Context : Concrete_Context_Node)
      return Boolean;

   function Context_Name (The_Context : Concrete_Context_Node)
      return Wide_String;

   function Parameters (The_Context : Concrete_Context_Node)
      return Wide_String;

   function Debug_Image (The_Context : Concrete_Context_Node)
      return Wide_String;

   function Configuration_Pragmas
     (The_Context : in Concrete_Context_Node)
      return Asis.Pragma_Element_List;

   function Library_Unit_Declaration
     (Name        : in Wide_String;
      The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit;

   function Compilation_Unit_Body
     (Name        : in Wide_String;
      The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit;

   function Library_Unit_Declarations
     (The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit_List;

   function Compilation_Unit_Bodies
     (The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit_List;

   function Context_Compilation_Units
     (The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit_List;

   function Corresponding_Children
     (Library_Unit : in Asis.Compilation_Unit;
      The_Context  : in Concrete_Context_Node)
      return Asis.Compilation_Unit_List;

   function Corresponding_Parent_Declaration
     (Library_Unit : in Asis.Compilation_Unit;
      The_Context  : in Concrete_Context_Node)
      return Asis.Compilation_Unit;

   function Corresponding_Declaration
     (Library_Item : in Asis.Compilation_Unit;
      The_Context  : in Concrete_Context_Node)
      return Asis.Compilation_Unit;

   function Corresponding_Body
     (Library_Item : in Asis.Compilation_Unit;
      The_Context  : in Concrete_Context_Node)
      return Asis.Compilation_Unit;

   function Subunits
     (Parent_Body : in Asis.Compilation_Unit;
      The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit_List;

   function Corresponding_Subunit_Parent_Body
     (Subunit     : in Asis.Compilation_Unit;
      The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit;

   function Corresponding_Body
     (Declaration : in Asis.Declaration;
      The_Context : in Concrete_Context_Node)
      return Asis.Declaration;

   function Corresponding_Body_Stub
     (Subunit     : in Asis.Declaration;
      The_Context : in Concrete_Context_Node)
      return Asis.Declaration;

   function Corresponding_Declaration
     (Declaration : in Asis.Declaration;
      The_Context : in Concrete_Context_Node)
      return Asis.Declaration;

   function Corresponding_Subunit
     (Body_Stub   : in Asis.Declaration;
      The_Context : in Concrete_Context_Node)
      return Asis.Declaration;

   function Corresponding_Type_Declaration
     (Declaration : in Asis.Declaration;
      The_Context : in Concrete_Context_Node)
      return Asis.Declaration;

   function Current_File
     (The_Context : in Concrete_Context_Node)
      return Wide_String;

   function Current_Unit
     (The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit;

   function New_Compilation_Unit
     (The_Context : access Concrete_Context_Node)
     return Asis.Compilation_Unit;

   procedure Make_Configuration_Unit
     (The_Context : in out Concrete_Context_Node);

   procedure Report_Error
     (The_Context : in out Concrete_Context_Node;
      The_Unit    : in     Compilation_Unit;
      Where       : in     Text_Position;
      Text        : in     Wide_String;
      Level       : in     Error_Level);

   function Check_Appropriate
     (The_Context : in Concrete_Context_Node)
     return Boolean;

   procedure Set_Check_Appropriate
     (The_Context : in out Concrete_Context_Node;
      Value       : in     Boolean);

private

   package U renames Ada.Strings.Wide_Unbounded;

   type Concrete_Context_Node is new Context_Node with record
      This                      : Context;
      Next                      : Context;
      Context_Name              : U.Unbounded_Wide_String;
      Parameters                : U.Unbounded_Wide_String;
      Current_File              : U.Unbounded_Wide_String;
      Current_Unit              : Asis.Compilation_Unit;
      Is_Open                   : Boolean := False;
      Has_Associations          : Boolean := False;
      Check_Appropriate         : Boolean := True;
      Error                     : Error_Level;
      Configuration_Pragmas     : Secondary_Pragma_Lists.List_Node;
      Library_Unit_Declarations : Secondary_Unit_Lists.List_Node;
      Compilation_Unit_Bodies   : Secondary_Unit_Lists.List_Node;
      Compilation               : Primary_Unit_Lists.List;
      Compilation_List          : Gela.Compilations.Compilation_List;
      Configuration_Unit        : Asis.Compilation_Unit;
   end record;

end Asis.Gela.Contexts;


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
