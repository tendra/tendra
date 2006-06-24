------------------------------------------------------------------------------
--                           G E L A   X A S I S                            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Helper functions

with Asis;

package XASIS.Utils is

   function Are_Equal_Identifiers
     (Left, Right : Asis.Program_Text)
     return Boolean;

   function Declaration_Direct_Name
     (Item : Asis.Declaration) return Asis.Program_Text;

   function Declaration_Name
     (Item : Asis.Declaration) return Asis.Defining_Name;

   function Direct_Name (Name : Asis.Defining_Name) return Asis.Program_Text;

   function Has_Defining_Name
     (Declaration : Asis.Declaration;
      Direct_Name : Asis.Program_Text) return Boolean;

   function Has_Name
     (Element     : Asis.Defining_Name;
      Direct_Name : Asis.Program_Text) return Boolean;

   function Get_Defining_Name
     (Declaration : Asis.Declaration;
      Direct_Name : Asis.Program_Text) return Asis.Defining_Name;

   function Named_By
     (Element : Asis.Expression;
      Name    : Asis.Program_Text) return Boolean;

   function Name_Image (Name : Asis.Expression) return Asis.Program_Text;

   function External_Name_Image
     (Name : Asis.Defining_Name)
     return Asis.Program_Text;

   function External_Image
     (Decl : Asis.Declaration)
     return Asis.Program_Text;

   --  Expected:
   --   An_Identifier
   --   A_Selected_Component
   --   An_Operator_Symbol
   --   A_Character_Literal
   --   An_Enumeration_Literal

   function Overloadable
     (Element  : Asis.Defining_Name)
      return Boolean;

   function Overloadable_Declaration
     (Element  : Asis.Declaration)
      return Boolean;

   -----------------
   --  Completion --
   -----------------

   function Can_Be_Completion
     (Declaration : Asis.Declaration) return Boolean;

   function Must_Be_Completion
     (Declaration : Asis.Declaration) return Boolean;

   function Is_Completion
     (Declaration : Asis.Declaration) return Boolean;

   function Declaration_For_Completion
     (Declaration : Asis.Declaration) return Asis.Declaration;

   function Completion_For_Declaration
     (Declaration : Asis.Declaration) return Asis.Declaration;

   function Completion_For_Name
     (Name : Asis.Defining_Name) return Asis.Declaration;

   function Parent_Declaration
     (Element : Asis.Element) return Asis.Declaration;

   function Check_Callable_Name (Name : Asis.Declaration) return Boolean;

   function Get_Profile (Name : Asis.Declaration)
     return Asis.Parameter_Specification_List;

   function Get_Result_Profile (Name : Asis.Declaration)
     return Asis.Expression;

   function Parameterless (Name : Asis.Declaration) return Boolean;

   function Is_Empty_Profile
     (List : Asis.Parameter_Specification_List) return Boolean;

   procedure Dump_Tree
     (Unit      : Asis.Compilation_Unit;
      File_Name : String);

   function Operator_Kind
     (Name_Image : Asis.Program_Text;
      Binary     : Boolean := True)
      return Asis.Operator_Kinds;

   function Debug_Image (Element : in Asis.Element) return Asis.Program_Text;

   function Selected_Name_Selector
     (Expr      : Asis.Expression;
      Skip_Attr : Boolean) return Asis.Expression;

   function Selected_Name_Declaration
     (Expr      : Asis.Expression;
      Skip_Attr : Boolean) return Asis.Declaration;

   function Is_Child_Of (Child, Parent : Asis.Element) return Boolean;

   function Has_Representation_Item (Tipe : Asis.Declaration) return Boolean;

   function Is_Entry_Family (Decl : Asis.Declaration) return Boolean;

   function Is_Parameter_Specification
     (Decl : Asis.Declaration) return Boolean;

   function Lexic_Level (Name : Asis.Defining_Name) return Positive;

   function Is_Expanded_Name (Expr : Asis.Expression) return Boolean;

   function Is_Package_Name (Name : Asis.Defining_Name) return Boolean;

   function Is_Enclosing_Named_Construct
     (Element : Asis.Element;
      Name    : Asis.Defining_Name) return Boolean;

   function Is_Predefined_Operator (Decl : Asis.Declaration) return Boolean;

end XASIS.Utils;


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
