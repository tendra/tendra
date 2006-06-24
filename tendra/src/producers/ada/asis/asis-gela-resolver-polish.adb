with Asis.Elements;
with Asis.Statements;
with Asis.Definitions;
with Asis.Expressions;
with Asis.Declarations;

with XASIS.Utils;
with Asis.Gela.Errors;
with Asis.Gela.Visibility;
with Asis.Gela.Element_Utils;

package body Asis.Gela.Resolver.Polish is

   procedure Each_Function_Call (Element : Asis.Element);
   procedure Each_Goto (Element : Asis.Element);

   procedure Set_Normalized_Profile
     (Call   : Asis.Element;
      Name   : Asis.Expression;
      Params : Asis.Association_List);

   ------------------
   -- Each_Element --
   ------------------

   procedure Each_Element (Element : Asis.Element) is
      use Asis.Elements;
   begin
      case Element_Kind (Element) is
         when An_Expression =>
            case Expression_Kind (Element) is
               when A_Function_Call =>
                  Each_Function_Call (Element);
               when others =>
                  null;
            end case;
         when A_Statement =>
            case Statement_Kind (Element) is
               when A_Goto_Statement =>
                  Each_Goto (Element);
               when A_Procedure_Call_Statement | An_Entry_Call_Statement =>
                  Set_Normalized_Profile
                    (Element,
                     Statements.Called_Name (Element),
                     Statements.Call_Statement_Parameters (Element));
               when others =>
                  null;
            end case;
         when others =>
            null;
      end case;
   end Each_Element;

   ------------------------
   -- Each_Function_Call --
   ------------------------

   procedure Each_Function_Call (Element : Asis.Element) is
      use Asis.Expressions;
      Name : constant Asis.Expression := Prefix (Element);
      Decl : constant Asis.Declaration :=
        XASIS.Utils.Selected_Name_Declaration (Name, False);
      Params : constant Asis.Association_List :=
        Function_Call_Parameters (Element);
   begin
      if Assigned (Decl) then
         Element_Utils.Set_Called_Function (Element, Decl, False);
      end if;

      if Function_Call_Parameters (Element, True)'Length = 0 then
         Set_Normalized_Profile (Element, Name, Params);
      end if;
   end Each_Function_Call;

   ----------------------------
   -- Set_Normalized_Profile --
   ----------------------------

   procedure Set_Normalized_Profile
     (Call   : Asis.Element;
      Name   : Asis.Expression;
      Params : Asis.Association_List)
   is
      use Asis.Expressions;
      function Get_Profile
        (With_Args : Boolean)
        return Asis.Parameter_Specification_List
      is
         use Asis.Elements;
         use Asis.Definitions;

         Tipe : Asis.Declaration;
         Decl : Asis.Declaration;
         Def  : Asis.Declaration;
      begin
         if Expression_Kind (Name) = An_Attribute_Reference then
            return Asis.Nil_Element_List;
         end if;

         if With_Args then
            Tipe := Corresponding_Expression_Type (Name);
         end if;

         if Is_Nil (Tipe)
           and then Expression_Kind (Name) = An_Explicit_Dereference
         then
            Tipe := Corresponding_Expression_Type (Prefix (Name));
         end if;

         if Is_Nil (Tipe) then
            Decl :=
              XASIS.Utils.Selected_Name_Declaration (Name, False);
            return XASIS.Utils.Get_Profile (Decl);
         else
            Def := Asis.Declarations.Type_Declaration_View (Tipe);
            return Access_To_Subprogram_Parameter_Profile (Def);
         end if;
      end Get_Profile;

      Profile : constant Asis.Parameter_Specification_List :=
        Get_Profile (Params'Length > 0);
   begin
      if Profile'Length = 0 then
         return;
      end if;

      Element_Utils.Set_Normalized_Params (Call, Params, Profile);
   end Set_Normalized_Profile;

   ---------------
   -- Each_Goto --
   ---------------

   procedure Each_Goto (Element : Asis.Element) is
      use Asis.Statements;
      use Asis.Gela.Errors;
      Name : constant Asis.Expression := Goto_Label (Element);
      Stmt : Asis.Statement;
   begin
      Visibility.Try_To_Resolve_Goto (Name, Element);
      Stmt := XASIS.Utils.Selected_Name_Declaration (Name, False);

      if Assigned (Stmt) then
         Element_Utils.Set_Corresponding_Statement
           (Stmt   => Element,
            Target => Stmt);
      else
         Report (Name, Error_Unknown_Name);
      end if;
   end Each_Goto;

end Asis.Gela.Resolver.Polish;


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
