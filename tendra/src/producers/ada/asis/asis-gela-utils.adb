with XASIS.Utils;
with Asis.Elements;
with Asis.Statements;
with Asis.Definitions;
with Asis.Declarations;
with Asis.Gela.Classes;
with Asis.Gela.Element_Utils;

package body Asis.Gela.Utils is

   function Direct_Name (Name : Asis.Defining_Name) return Asis.Program_Text
     renames XASIS.Utils.Direct_Name;

   function Has_Name
     (Element     : Asis.Defining_Name;
      Direct_Name : Asis.Program_Text) return Boolean
     renames XASIS.Utils.Has_Name;

   function Overloadable
     (Element  : Asis.Defining_Name) return Boolean
     renames XASIS.Utils.Overloadable;

   function Parent_Declaration
     (Element : Asis.Element) return Asis.Declaration
     renames XASIS.Utils.Parent_Declaration;

   use Asis;
   use Asis.Gela.Classes;

   function Get_Parameter_Profile
     (Def : Asis.Element)
      return Asis.Parameter_Specification_List;

   function Get_Result_Profile
     (Def   : Asis.Element;
      Place : Asis.Element) return Type_Info;

   function In_List
     (List        : Asis.Element_List;
      Declaration : Asis.Declaration) return Boolean;

   --------------------
   -- Are_Homographs --
   --------------------

   function Are_Homographs
     (Left  : Asis.Defining_Name;
      Right : Asis.Defining_Name;
      Place : Asis.Element)
   return Boolean
   is
   begin
      pragma Assert (Elements.Element_Kind (Left) = A_Defining_Name and
                     Elements.Element_Kind (Right) = A_Defining_Name,
                     "Unexpected element in Direct_Name");

      if Has_Name (Left, Direct_Name (Right)) then
         if Overloadable (Left) and then Overloadable (Right) then
            return Are_Type_Conformant (Left, Right, Place);
         else
            return True;
         end if;
      else
         return False;
      end if;
   end Are_Homographs;

   -------------------------
   -- Are_Type_Conformant --
   -------------------------

   function Are_Type_Conformant
     (Left  : Asis.Element;
      Right : Asis.Element;
      Place : Asis.Element;
      Right_Is_Prefixed_View : Boolean := False)
     return Boolean
   is
      use Asis.Elements;

      function Equal_Designated_Types (Left, Right : Type_Info) return Boolean
      is
         D_Left, D_Right : Type_Info;
      begin
         if not Is_Anonymous_Access (Left) or else
           not Is_Anonymous_Access (Right) or else
           (Is_Subprogram_Access (Left) xor Is_Subprogram_Access (Right))
         then
            return False;
         end if;

         if Is_Subprogram_Access (Left) then
            return Destinated_Are_Type_Conformant (Left, Right);
         else
            D_Left := Destination_Type (Left);
            D_Right := Destination_Type (Right);
            return D_Left = D_Right;
         end if;
      end Equal_Designated_Types;


      Left_Result  : Type_Info := Get_Result_Profile (Left, Place);
      Right_Result : Type_Info := Get_Result_Profile (Right, Place);
   begin
      if Is_Not_Type (Left_Result) and not Is_Not_Type (Right_Result) then
         return False;
      elsif not Is_Not_Type (Left_Result) and Is_Not_Type (Right_Result) then
         return False;
      elsif not Is_Not_Type (Left_Result)
        and then not Is_Not_Type (Right_Result)
        and then not Is_Equal (Left_Result, Right_Result)
        and then not Equal_Designated_Types (Left_Result, Right_Result)
      then
         return False;
      end if;

      declare
         use Asis.Declarations;

         Left_Profile  : Asis.Parameter_Specification_List :=
           Get_Parameter_Profile (Left);
         Right_Profile : Asis.Parameter_Specification_List :=
           Get_Parameter_Profile (Right);
         Left_Param  : Asis.ASIS_Natural := 0;
         Left_Names  : Asis.ASIS_Natural := 0;
         Right_Param : Asis.ASIS_Natural := 0;
         Right_Names : Asis.ASIS_Integer := 0;
         Exit_Loop   : Boolean := False;
         Left_Type   : Type_Info;
         Right_Type  : Type_Info;
         Left_Trait  : Asis.Trait_Kinds;
         Right_Trait : Asis.Trait_Kinds;
      begin
         if Right_Is_Prefixed_View then
            Right_Names := -1;
         end if;

         loop
            if Left_Names = 0 then
               Left_Param := Left_Param + 1;

               if Left_Param in Left_Profile'Range then
                  Left_Names := Names (Left_Profile (Left_Param))'Length;
                  Left_Trait := Trait_Kind (Left_Profile (Left_Param));
                  Left_Type  :=
                    Type_Of_Declaration (Left_Profile (Left_Param), Place);
               else
                  Exit_Loop := True;
               end if;
            end if;

            while Right_Names <= 0 loop
               Right_Param := Right_Param + 1;

               if Right_Param in Right_Profile'Range then
                  Right_Names := Right_Names +
                    Names (Right_Profile (Right_Param))'Length;
                  Right_Trait := Trait_Kind (Right_Profile (Right_Param));
                  Right_Type  :=
                    Type_Of_Declaration (Right_Profile (Right_Param), Place);
               else
                  Exit_Loop := True;
                  exit;
               end if;
            end loop;

            exit when Exit_Loop;

            if Left_Trait /= Right_Trait then
               return False;
            end if;

            if not Is_Equal (Left_Type, Right_Type) and then
              not Equal_Designated_Types (Left_Type, Right_Type)
            then
               return False;
            end if;

            Left_Names  := Left_Names - 1;
            Right_Names := Right_Names - 1;
         end loop;

         if Left_Names = 0 and Right_Names = 0 then
            return True;
         else
            return False;
         end if;
      end;
   end Are_Type_Conformant;

   ---------------------------
   -- Get_Parameter_Profile --
   ---------------------------

   function Get_Parameter_Profile
     (Def : Asis.Element)
      return Asis.Parameter_Specification_List
   is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;

      Decl : Asis.Declaration := Enclosing_Element (Def);
      Kind : Asis.Declaration_Kinds := Declaration_Kind (Decl);
      Tipe : Asis.Definition;
   begin
      if Definition_Kind (Def) = An_Access_Definition then
         return Access_To_Subprogram_Parameter_Profile (Def);
      end if;

      case Kind is
         when A_Function_Declaration |
           A_Procedure_Declaration |
           A_Function_Body_Declaration |
           A_Procedure_Body_Declaration |
           A_Function_Body_Stub |
           A_Procedure_Body_Stub |
           A_Function_Renaming_Declaration |
           A_Procedure_Renaming_Declaration |
           An_Entry_Declaration |
           A_Formal_Function_Declaration |
           A_Formal_Procedure_Declaration =>

            return Parameter_Profile (Decl);
         when A_Generic_Function_Renaming_Declaration |
           A_Generic_Procedure_Renaming_Declaration |
           A_Function_Instantiation |
           A_Procedure_Instantiation =>

            declare
               Unwind : constant Asis.Declaration :=
                 Corresponding_Declaration (Decl);
               Name : constant Asis.Defining_Name_List := Names (Unwind);
            begin
               return Get_Parameter_Profile (Name (1));
            end;

         when An_Ordinary_Type_Declaration =>
            Tipe := Type_Declaration_View (Decl);
            case Access_Type_Kind (Tipe) is
               when Access_To_Subprogram_Definition =>
                  return Access_To_Subprogram_Parameter_Profile (Tipe);
               when others =>
                  return Nil_Element_List;
            end case;

         when A_Variable_Declaration |
           A_Constant_Declaration |
           A_Component_Declaration |
           A_Discriminant_Specification |
           A_Parameter_Specification |
           A_Formal_Object_Declaration =>

            declare
               Def : constant Asis.Definition :=
                 Object_Declaration_Subtype (Decl);
            begin
               case Access_Definition_Kind (Def) is
                  when An_Anonymous_Access_To_Procedure |
                    An_Anonymous_Access_To_Protected_Procedure |
                    An_Anonymous_Access_To_Function |
                    An_Anonymous_Access_To_Protected_Function
                    =>
                     return Access_To_Subprogram_Parameter_Profile (Def);
                  when others =>
                     return Nil_Element_List;
               end case;
            end;

         when Not_A_Declaration =>
            if Statement_Kind (Decl) = An_Accept_Statement then
               return Statements.Accept_Parameters (Decl);
            else
               return Nil_Element_List;
            end if;

         when others =>
            return Nil_Element_List;
      end case;
   end Get_Parameter_Profile;

   ------------------------
   -- Get_Result_Profile --
   ------------------------

   function Get_Result_Profile
     (Def   : Asis.Element;
      Place : Asis.Element)
     return Type_Info
   is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;

      Decl : Asis.Declaration := Enclosing_Element (Def);
      Kind : Asis.Declaration_Kinds := Declaration_Kind (Decl);
      Tipe : Asis.Definition;
   begin
      if Definition_Kind (Def) = An_Access_Definition then
         if Access_Definition_Kind (Def) in An_Anonymous_Access_To_Function ..
           An_Anonymous_Access_To_Protected_Function
         then
            return Type_From_Indication
              (Access_To_Function_Result_Subtype (Def), Place);
         else
            return Not_A_Type;
         end if;
      end if;

      case Kind is
         when A_Function_Declaration |
           A_Function_Body_Declaration |
           A_Function_Body_Stub |
           A_Function_Renaming_Declaration |
           A_Generic_Function_Declaration |
           A_Formal_Function_Declaration =>

            return Type_From_Indication (Result_Subtype (Decl), Place);
         when An_Enumeration_Literal_Specification =>
            return Type_Of_Declaration (Decl, Place);

         when A_Generic_Function_Renaming_Declaration |
           A_Function_Instantiation =>

            declare
               Unwind : constant Asis.Declaration :=
                 Corresponding_Declaration (Decl);
               Name : constant Asis.Defining_Name_List := Names (Unwind);
            begin
               return Get_Result_Profile (Name (1), Place);
            end;

         when An_Ordinary_Type_Declaration =>
            Tipe := Type_Declaration_View (Decl);
            case Access_Type_Kind (Tipe) is
               when An_Access_To_Function | An_Access_To_Protected_Function =>
                  return Type_From_Indication
                    (Access_To_Function_Result_Subtype (Tipe), Place);
               when others =>
                  return Not_A_Type;
            end case;

         when A_Variable_Declaration |
           A_Constant_Declaration |
           A_Component_Declaration |
           A_Discriminant_Specification |
           A_Parameter_Specification |
           A_Formal_Object_Declaration =>

            declare
               Def : constant Asis.Definition :=
                 Object_Declaration_Subtype (Decl);
            begin
               case Access_Definition_Kind (Def) is
                  when An_Anonymous_Access_To_Function |
                    An_Anonymous_Access_To_Protected_Function =>
                     return Type_From_Indication
                       (Access_To_Function_Result_Subtype (Def), Place);
                  when others =>
                     return Not_A_Type;
               end case;
            end;

         when others =>
            return Not_A_Type;
      end case;
   end Get_Result_Profile;

   -------------
   -- In_List --
   -------------

   function In_List
     (List        : Asis.Element_List;
      Declaration : Asis.Declaration) return Boolean is
   begin
      for I in List'Range loop
         if Asis.Elements.Is_Equal (List (I), Declaration) then
            return True;
         end if;
      end loop;
      return False;
   end In_List;

   -----------------------
   -- In_Context_Clause --
   -----------------------

   function In_Context_Clause (Clause : Asis.Clause) return Boolean is
      use Asis.Elements;
      Unit : Asis.Compilation_Unit := Enclosing_Compilation_Unit (Clause);
      List : Asis.Element_List := Context_Clause_Elements (Unit);
   begin
      return In_List (List, Clause);
   end In_Context_Clause;

   ---------------------
   -- In_Visible_Part --
   ---------------------

   function In_Visible_Part
     (Declaration : Asis.Declaration) return Boolean
   is
      use Asis;
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Definitions;

      Parent      : Asis.Declaration := Parent_Declaration (Declaration);
      Parent_Kind : Asis.Declaration_Kinds := Declaration_Kind (Parent);
      Decl_Kind   : Asis.Declaration_Kinds := Declaration_Kind (Declaration);
      Expr        : Asis.Expression;
   begin
      case Parent_Kind is
         when Asis.A_Procedure_Declaration        |
            Asis.A_Function_Declaration           |
            Asis.A_Procedure_Body_Declaration     |
            Asis.A_Function_Body_Declaration      |
            Asis.A_Procedure_Renaming_Declaration |
            Asis.A_Function_Renaming_Declaration  |
            Asis.An_Entry_Declaration =>

            return Decl_Kind = Asis.A_Parameter_Specification;

         when Asis.An_Ordinary_Type_Declaration =>

            return Decl_Kind = Asis.A_Discriminant_Specification or
              Decl_Kind = Asis.A_Component_Declaration or
              Decl_Kind = Asis.An_Enumeration_Literal_Specification;

         when Asis.A_Generic_Function_Declaration |
            Asis.A_Generic_Procedure_Declaration =>

            return In_List (Generic_Formal_Part (Parent), Declaration) or
              Decl_Kind = Asis.A_Parameter_Specification;

         when Asis.A_Generic_Package_Declaration =>

            return In_List (Generic_Formal_Part (Parent), Declaration) or
              In_List (Visible_Part_Declarative_Items (Parent), Declaration);

         when Asis.A_Package_Declaration =>

            if Is_Part_Of_Instance (Parent) then
               if Decl_Kind in A_Formal_Declaration then
                  Expr := Element_Utils.Generic_Actual (Declaration);

                  if Expression_Kind (Expr) = A_Box_Expression then
                     return True;
                  end if;
               end if;
            end if;

            return In_List
              (Visible_Part_Declarative_Items (Parent), Declaration);

         when Asis.A_Single_Task_Declaration |
           Asis.A_Single_Protected_Declaration =>

            declare
               Def : Asis.Definition := Object_Declaration_View (Parent);
            begin
               return In_List (Visible_Part_Items (Def), Declaration);
            end;

         when Asis.A_Task_Type_Declaration |
           Asis.A_Protected_Type_Declaration =>

            declare
               Def : Asis.Definition := Type_Declaration_View (Parent);
               D   : Asis.Definition := Discriminant_Part (Parent);
            begin
               return In_List (Visible_Part_Items (Def), Declaration) or else
                 (Definition_Kind (D) = A_Known_Discriminant_Part and then
                  In_List (Discriminants (D), Declaration));
            end;

         when others =>
            return False;
      end case;

   end In_Visible_Part;

   ---------------------
   -- Is_Limited_Type --
   ---------------------

   function Is_Limited_Type (Tipe : Asis.Definition) return Boolean is
      use Asis.Elements;
   begin
      case Definition_Kind (Tipe) is
         when A_Private_Type_Definition |
           A_Tagged_Private_Type_Definition
           =>
            return Has_Limited (Tipe);
         when others =>
            null;
      end case;

      case Type_Kind (Tipe) is
         when A_Derived_Type_Definition |
              A_Derived_Record_Extension_Definition |
              A_Record_Type_Definition |
              A_Tagged_Record_Type_Definition
               =>
            case Trait_Kind (Tipe) is
               when A_Limited_Trait |
                    A_Limited_Private_Trait |
                    An_Abstract_Limited_Trait |
                    An_Abstract_Limited_Private_Trait =>
                  return True;
               when others =>
                  return False;
            end case;
         when An_Interface_Type_Definition =>
            return Interface_Kind (Tipe) /= An_Ordinary_Interface;
         when others =>
            null;
      end case;

      case Formal_Type_Kind (Tipe) is
         when A_Formal_Private_Type_Definition |
           A_Formal_Tagged_Private_Type_Definition =>
            case Trait_Kind (Tipe) is
               when A_Limited_Trait |
                    A_Limited_Private_Trait |
                    An_Abstract_Limited_Trait |
                    An_Abstract_Limited_Private_Trait =>
                  return True;
               when others =>
                  return False;
            end case;
         when A_Formal_Interface_Type_Definition =>
            return Interface_Kind (Tipe) /= An_Ordinary_Interface;
         when others =>
            null;
      end case;

      return False;
   end Is_Limited_Type;

   ---------------------
   -- Walk_Components --
   ---------------------

   procedure Walk_Components
     (Item     : Asis.Element;
      Continue :    out Boolean)
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Definitions;
      Walk_Error : exception;
   begin
      case Element_Kind (Item) is
--         when An_Expression =>
--            Walk_Components (To_Type (Item).Declaration, Continue);
         when A_Declaration =>
            case Declaration_Kind (Item) is
               when An_Incomplete_Type_Declaration =>
                  declare
                     Discr : Asis.Element := Discriminant_Part (Item);
                  begin
                     if not Is_Nil (Discr) then
                        Walk_Components (Discr, Continue);
                        if not Continue then
                           return;
                        end if;
                     end if;
                  end;

               when An_Ordinary_Type_Declaration
                 | A_Task_Type_Declaration
                 | A_Protected_Type_Declaration
                 | A_Private_Type_Declaration
                 | A_Private_Extension_Declaration
                 | A_Formal_Type_Declaration =>

                  declare
                     Discr : Asis.Element := Discriminant_Part (Item);
                     View  : Asis.Element := Type_Declaration_View (Item);
                  begin
                     if not Is_Nil (Discr) then
                        Walk_Components (Discr, Continue);
                        if not Continue then
                           return;
                        end if;
                     end if;

                     Walk_Components (View, Continue);
                  end;

               when A_Discriminant_Specification | A_Component_Declaration =>
                  Walk_Component (Item, Continue);

               when others =>
                  raise Walk_Error;
            end case;
         when A_Definition =>
            case Definition_Kind (Item) is
               when A_Subtype_Indication =>
                  declare
                     --  Get type view and walk it's declaration
                     Def  : constant Asis.Definition :=
                       Get_Type_Def (Type_From_Indication (Item, Place));
                  begin
                     Walk_Components
                       (Enclosing_Element (Def),
                        Continue);
                  end;
               when A_Type_Definition =>
                  case Type_Kind (Item) is
                     when A_Derived_Record_Extension_Definition =>

                        Walk_Components
                          (Asis.Definitions.Parent_Subtype_Indication (Item),
                           Continue);

                        if not Continue then
                           return;
                        end if;

                        Walk_Components
                          (Asis.Definitions.Record_Definition (Item),
                           Continue);

                     when A_Derived_Type_Definition =>

                        Walk_Components
                          (Asis.Definitions.Parent_Subtype_Indication (Item),
                           Continue);

                     when A_Record_Type_Definition |
                       A_Tagged_Record_Type_Definition =>

                        Walk_Components
                          (Asis.Definitions.Record_Definition (Item),
                           Continue);

                     when An_Interface_Type_Definition =>
                        Continue := True;

                     when others =>
                        raise Walk_Error;
                  end case;
               when A_Record_Definition | A_Variant =>
                  if Definition_Kind (Item) = A_Variant then
                     Walk_Variant (Item, Continue);
                     if not Continue then
                        return;
                     end if;
                  end if;
                  declare
                     List  : Asis.Record_Component_List :=
                       Record_Components (Item);
                  begin
                     for I in List'Range loop
                        case Element_Kind (List (I)) is
                           when A_Declaration | A_Definition =>
                              Walk_Components (List (I), Continue);
                           when others =>
                              raise Walk_Error;
                        end case;

                        if not Continue then
                           return;
                        end if;
                     end loop;
                  end;
               when A_Variant_Part =>
                  declare
                     List  : Asis.Variant_List := Variants (Item);
                  begin
                     for I in List'Range loop
                        Walk_Components (List (I), Continue);
                        if not Continue then
                           return;
                        end if;
                     end loop;
                  end;
               when A_Known_Discriminant_Part =>
                  declare
                     List : Asis.Discriminant_Specification_List :=
                       Discriminants (Item);
                  begin
                     for I in List'Range loop
                        Walk_Components (List (I), Continue);
                        if not Continue then
                           return;
                        end if;
                     end loop;
                  end;
               when A_Null_Record_Definition
                 | A_Null_Component
                 | A_Private_Type_Definition
                 | A_Tagged_Private_Type_Definition
                 | A_Private_Extension_Definition
                 | A_Task_Definition
                 | A_Protected_Definition
                 | A_Formal_Type_Definition
                 | An_Unknown_Discriminant_Part
                 =>

                  Continue := True;
               when others =>
                  raise Walk_Error;
            end case;
         when others =>
            raise Walk_Error;
      end case;
   end Walk_Components;

end Asis.Gela.Utils;



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
