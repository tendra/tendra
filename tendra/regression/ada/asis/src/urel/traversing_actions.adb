with Print_Element;
with Asis.Elements;
with Asis.Statements;
with Asis.Expressions;
with Asis.Compilation_Units;
with Asis.Compilation_Units.Relations;
with Ada.Wide_Text_IO;

package body Traversing_Actions is

   procedure Print_Relationship
     (Element : Asis.Element;
      Result  : Asis.Compilation_Units.Relations.Relationship);

   function To_List
     (Item : Asis.Association)
     return Asis.Compilation_Unit_List;

   function Library_Unit_Declaration
     (Item : Asis.Association)
     return Asis.Compilation_Unit_List;

   function Compilation_Unit_Body
     (Item : Asis.Association)
     return Asis.Compilation_Unit_List;

   function To_Relation (Item : Asis.Association) return Asis.Relation_Kinds;

   function Function_Call_To_List
     (Call : Asis.Expression)
     return Asis.Compilation_Unit_List;

   use Asis.Elements;
   use Asis.Statements;
   use Asis.Expressions;

   ---------------------------
   -- Compilation_Unit_Body --
   ---------------------------

   function Compilation_Unit_Body
     (Item : Asis.Association)
     return Asis.Compilation_Unit_List
   is
      use Asis;

      Arg   : constant Asis.Expression := Actual_Parameter (Item);
      Image : constant Asis.Program_Text := Value_Image (Arg);
      Name  : constant Asis.Program_Text := Image (2 .. Image'Last - 1);
      Unit  : constant Asis.Compilation_Unit :=
        Enclosing_Compilation_Unit (Arg);

      Context : constant Asis.Context :=
        Compilation_Units.Enclosing_Context (Unit);
   begin
      return (1 => Compilation_Units.Compilation_Unit_Body (Name, Context));
   end Compilation_Unit_Body;

   ---------------------------
   -- Function_Call_To_List --
   ---------------------------

   function Function_Call_To_List
     (Call : Asis.Expression)
     return Asis.Compilation_Unit_List
   is
      use type Asis.Compilation_Unit_List;

      Name  : constant Asis.Expression := Prefix (Call);
      Image : constant Asis.Program_Text := Name_Image (Name);
      List  : constant Asis.Association_List :=
        Function_Call_Parameters (Call);
   begin
      if Image = """+""" then
         return To_List (List (1)) & To_List (List (2));
      elsif Image = "Library_Unit_Declaration" then
         return Library_Unit_Declaration (List (1));
      elsif Image = "Compilation_Unit_Body" then
         return Compilation_Unit_Body (List (1));
      else
         raise Constraint_Error;
      end if;
   end Function_Call_To_List;

   ------------------------------
   -- Library_Unit_Declaration --
   ------------------------------

   function Library_Unit_Declaration
     (Item : Asis.Association)
     return Asis.Compilation_Unit_List
   is
      use Asis;

      Arg   : constant Asis.Expression   := Actual_Parameter (Item);
      Image : constant Asis.Program_Text := Value_Image (Arg);
      Name  : constant Asis.Program_Text := Image (2 .. Image'Last - 1);
      Unit  : constant Asis.Compilation_Unit :=
        Enclosing_Compilation_Unit (Arg);

      Context : constant Asis.Context :=
        Compilation_Units.Enclosing_Context (Unit);
   begin
      return
        (1 => Compilation_Units.Library_Unit_Declaration (Name, Context));
   end Library_Unit_Declaration;

   -----------------
   -- Post_Action --
   -----------------

   procedure Post_Action
     (Element :        Asis.Element;
      Control : in out Asis.Traverse_Control;
      State   : in out Traversal_State)
   is
   begin
      null;
   end Post_Action;

   ----------------
   -- Pre_Action --
   ----------------

   procedure Pre_Action
     (Element :        Asis.Element;
      Control : in out Asis.Traverse_Control;
      State   : in out Traversal_State)
   is
      use Asis;
      use Asis.Compilation_Units.Relations;
   begin
      if Statement_Kind (Element) = A_Procedure_Call_Statement then
         declare
            Unit    : constant Asis.Compilation_Unit :=
              Enclosing_Compilation_Unit (Element);

            Context : constant Asis.Context :=
              Asis.Compilation_Units.Enclosing_Context (Unit);

            Name    : constant Asis.Expression := Called_Name (Element);
            List    : constant Asis.Association_List :=
              Call_Statement_Parameters (Element);
         begin
            if Expression_Kind (Name) = An_Identifier then
               if Name_Image (Name) = "Semantic_Dependence_Order" then
                  Print_Relationship
                    (Element,
                     Semantic_Dependence_Order (To_List (List (1)),
                                                To_List (List (2)),
                                                Context,
                                                To_Relation (List (3))));
               elsif Name_Image (Name) = "Elaboration_Order" then
                  Print_Relationship
                    (Element,
                     Elaboration_Order (To_List (List (1)), Context));
               end if;
            end if;

            Control := Abandon_Children;
         end;
      end if;
   end Pre_Action;

   ------------------------
   -- Print_Relationship --
   ------------------------

   procedure Print_Relationship
     (Element : Asis.Element;
      Result  : Asis.Compilation_Units.Relations.Relationship)
   is
      use Asis.Compilation_Units;
   begin
      Print_Element (Element);
      Ada.Wide_Text_IO.New_Line;
      Ada.Wide_Text_IO.Put_Line ("Consistent:");

      for J in 1 .. Result.Consistent_Length loop
         Ada.Wide_Text_IO.Put_Line
           ("  " & Unique_Name (Result.Consistent (J)));
      end loop;

      Ada.Wide_Text_IO.Put_Line ("End of Consistent.");
      Ada.Wide_Text_IO.Put_Line ("Inconsistent:");

      for J in 1 .. Result.Inconsistent_Length loop
         Ada.Wide_Text_IO.Put_Line
           ("  " & Unique_Name (Result.Inconsistent (J)));
      end loop;

      Ada.Wide_Text_IO.Put_Line ("End of Inconsistent.");
      Ada.Wide_Text_IO.Put_Line ("Missing:");

      for J in 1 .. Result.Missing_Length loop
         Ada.Wide_Text_IO.Put_Line
           ("  " & Unique_Name (Result.Missing (J)));
      end loop;

      Ada.Wide_Text_IO.Put_Line ("End of Missing.");
      Ada.Wide_Text_IO.Put_Line ("Circular:");

      for J in 1 .. Result.Circular_Length loop
         Ada.Wide_Text_IO.Put_Line
           ("  " & Unique_Name (Result.Circular (J)));
      end loop;

      Ada.Wide_Text_IO.Put_Line ("End of Circular.");
      Ada.Wide_Text_IO.New_Line;
   end Print_Relationship;

   -----------------
   -- To_Relation --
   -----------------

   function To_Relation (Item : Asis.Association) return Asis.Relation_Kinds is
      use Asis.Expressions;
      Name  : constant Asis.Expression := Actual_Parameter (Item);
      Image : constant Asis.Program_Text := Name_Image (Name);
   begin
      return Asis.Relation_Kinds'Wide_Value (Image);
   end To_Relation;

   -------------
   -- To_List --
   -------------

   function To_List
     (Item : Asis.Association)
     return Asis.Compilation_Unit_List
   is
      Arg  : constant Asis.Expression := Actual_Parameter (Item);
   begin
      case Expression_Kind (Arg) is
         when Asis.A_Function_Call =>
            return Function_Call_To_List (Arg);
         when Asis.An_Identifier =>
            return Asis.Nil_Compilation_Unit_List;
         when others =>
            Ada.Wide_Text_IO.Put_Line ("Unexpected Element:");
            Print_Element (Arg);
            raise Constraint_Error;
      end case;
   end To_List;

end Traversing_Actions;

------------------------------------------------------------------------------
--  Copyright (c) 2008, Maxim Reznik
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
