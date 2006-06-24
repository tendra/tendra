------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Help with manipulation of Element

package Asis.Gela.Element_Utils is

   function Compound_Name_Image
     (Compount_Name : Asis.Element)
     return Wide_String;

   procedure Set_Enclosing_Element
     (Item   : Asis.Element;
      Parent : Asis.Element);

   procedure Set_Enclosing_Compilation_Unit
     (Item   : Asis.Element;
      Unit   : Asis.Compilation_Unit);

   function To_Unit_Name
     (Compount_Name : Asis.Element)
     return Asis.Element;

   procedure Copy_Element
     (Source : Asis.Element;
      Target : Asis.Element);

   procedure Set_Resolved
     (Element : Asis.Element;
      List    : Asis.Defining_Name_List);

   procedure Set_Override
     (Defining_Name : Asis.Element;
      Homograph     : Asis.Element);

   function Override (Defining_Name : Asis.Element) return Asis.Element;

   procedure Add_To_Visible
     (Declaration : Asis.Element;
      Item        : Asis.Element;
      Before      : Asis.Program_Text := "");

   procedure Add_Defining_Name
     (Item : Asis.Element;
      Name : Asis.Element);

   procedure Remove_Defining_Name
     (Item : Asis.Element;
      Name : Asis.Element);

   procedure Set_Name_Declaration
     (Item : Asis.Element;
      Name : Asis.Declaration);

   procedure Set_Pragma_Kind  (Element : Asis.Pragma_Element);

   procedure Add_Type_Operator
     (Tipe : Asis.Definition;
      Oper : Asis.Declaration);

   procedure Add_Inherited_Subprogram
     (Tipe : Asis.Definition;
      Proc : Asis.Declaration);

   function Base_Subprogram_Derivation
     (Proc : Asis.Declaration) return Asis.Declaration;

   procedure Add_Pragma
     (Item       : Asis.Element;
      The_Pragma : Asis.Pragma_Element);

   procedure Set_Derived_Type
     (Tipe   : Asis.Type_Definition;
      Parent : Asis.Declaration;
      Root   : Asis.Declaration;
      Struct : Asis.Declaration);

   procedure Set_Called_Function
     (Call       : Asis.Element;
      Name       : Asis.Declaration;
      Dispatched : Boolean);

   procedure Set_Corresponding_Statement
     (Stmt   : Asis.Statement;
      Target : Asis.Statement);

   procedure Set_Completion
     (Declaration : Asis.Defining_Name;
      Completion  : Asis.Declaration);

   procedure Set_Normalized_Params
     (Call    : Asis.Element;
      Param   : Asis.Association_List;
      Profile : Asis.Parameter_Specification_List);

   procedure Set_Representation_Value
     (Enum   : Asis.Declaration;
      Value  : Wide_String);

end Asis.Gela.Element_Utils;


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
