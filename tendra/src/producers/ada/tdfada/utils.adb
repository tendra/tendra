with XASIS.Static;
with XASIS.Pragmas;

with Asis.Elements;
with Asis.Iterator;
with Asis.Extensions;
with Asis.Expressions;

package body Utils is

   ------------------
   -- By_Copy_Type --
   ------------------

   function By_Copy_Type (Tipe : XASIS.Classes.Type_Info) return Boolean is
      use XASIS.Classes;
   begin
      if Is_Elementary (Tipe) then
         return True;
      end if;

      return False;
   end By_Copy_Type;

   ----------------
   -- Convention --
   ----------------

   function Convention (Decl : Asis.Declaration) return Conventions is
   begin
      if Asis.Elements.Is_Part_Of_Implicit (Decl) then
         return Intrinsic;
      else
         return Ada;
      end if;
   end Convention;

   --------------------------
   --  External_Name_Image --
   --------------------------

   function External_Name_Image
     (Name : Asis.Defining_Name)
     return Asis.Program_Text
   is
      use XASIS.Pragmas;

      Pragmas : constant Asis.Pragma_Element_List :=
        Find_Pragmas (Name, (Asis.An_Export_Pragma, Asis.An_Import_Pragma));
      Image   : Asis.Expression;
   begin
      if Pragmas'Length > 0 then
         Image := Parameter (Pragmas (Pragmas'First), External_Name);

         if not Asis.Elements.Is_Nil (Image) then
            declare
               Result : constant Asis.Program_Text :=
                 Asis.Expressions.Value_Image (Image);
            begin
               --  Dequote:
               return Result (Result'First + 1 .. Result'Last - 1);
            end;
         end if;
      end if;

      return Asis.Extensions.Unique_Name (Name);
   end External_Name_Image;

   ---------------------
   -- Has_Nested_Proc --
   ---------------------

   function Has_Nested_Proc (Proc : Asis.Declaration) return Boolean is

      procedure Pre_Action
        (Element :        Asis.Element;
         Control : in out Asis.Traverse_Control;
         State   : in out Boolean)
      is
         use Asis;
         use Asis.Elements;
      begin
         case Declaration_Kind (Element) is
            when A_Task_Type_Declaration
              | A_Protected_Type_Declaration
              | A_Single_Task_Declaration
              | A_Single_Protected_Declaration
              | A_Procedure_Declaration
              | A_Function_Declaration
              | A_Procedure_Body_Declaration
              | A_Function_Body_Declaration
              | A_Task_Body_Declaration
              | A_Protected_Body_Declaration
              | A_Procedure_Body_Stub
              | A_Function_Body_Stub
              | A_Package_Body_Stub
              | A_Task_Body_Stub
              | A_Protected_Body_Stub
              | A_Generic_Procedure_Declaration
              | A_Generic_Function_Declaration
              =>
               if not Is_Equal (Element, Proc) then
                  State := True;
                  Control := Terminate_Immediately;
               end if;
            when others =>
               null;
         end case;
      end Pre_Action;

      procedure Post_Action
        (Element :        Asis.Element;
         Control : in out Asis.Traverse_Control;
         State   : in out Boolean) is
      begin
         null;
      end Post_Action;

      procedure Walk is new
        Asis.Iterator.Traverse_Element (Boolean, Pre_Action, Post_Action);

      Result  : Boolean := False;
      Control : Asis.Traverse_Control := Asis.Continue;
   begin
      Walk (Proc, Control, Result);
      return Result;
   end Has_Nested_Proc;

   ---------------
   -- Is_Static --
   ---------------

   function Is_Static (Expr : Asis.Expression) return Boolean renames
     Asis.Extensions.Is_Static_Expression;

   ----------------
   -- Is_Defined --
   ----------------

   function Is_Defined (Expr : Asis.Expression) return Boolean is
      use XASIS.Static;
      Val : Value := Evaluate (Expr);
   begin
      return Val /= Undefined;
   end Is_Defined;

   ---------------------------
   -- Out_By_Copy_Parameter --
   ---------------------------

   function Out_By_Copy_Parameter (Param  : Asis.Declaration) return Boolean is
      use Asis;
      use XASIS.Classes;
   begin
      return Elements.Mode_Kind (Param) in An_Out_Mode .. An_In_Out_Mode
        and then By_Copy_Type (Type_Of_Declaration (Param));
   end Out_By_Copy_Parameter;

end Utils;


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
