with Asis.Elements;
with Asis.Declarations;
with Asis.Gela.Utils;
with Asis.Gela.Implicit;
with Asis.Gela.Inheritance;

with Ada.Wide_Text_IO;
package body Asis.Gela.Private_Operations is

   procedure Create_Type_Data
     (Data    : in     Package_Data;
      Info    : in     Classes.Type_Info);

   procedure Check_Dependent
     (Tipe    : in     Asis.Declaration;
      Exist   : in     Type_Data_Access;
      Data    : in     Package_Data;
      Info    : in     Classes.Type_Info;
      Point   : in out Visibility.Point);

   procedure Fill_Dependencies
     (Element : in     Asis.Declaration;
      Data    : in     Package_Data;
      Info    : in     Classes.Type_Info);

   function Find
     (Data    : in     Package_Data;
      Info    : in     Classes.Type_Info) return Type_Data_Access;

   ------------------------
   -- Check_Derived_Type --
   ------------------------

   procedure Check_Derived_Type
     (Tipe_Decl : in     Asis.Declaration;
      From      : in     Asis.Element;
      Point     : in out Visibility.Point)
   is
      use Asis.Elements;

      Def : Asis.Definition;
   begin
      case Declaration_Kind (Tipe_Decl) is
         when An_Ordinary_Type_Declaration
           | A_Private_Type_Declaration
           | A_Formal_Type_Declaration
           =>
            Def := Asis.Declarations.Type_Declaration_View (Tipe_Decl);

            case Type_Kind (Def) is
               when A_Derived_Type_Definition |
                 A_Derived_Record_Extension_Definition =>

                  Inheritance.Check_Inherited_Subprograms
                    (Tipe_Decl, From, Point);
               when others =>
                  null;
            end case;
         when others =>
            null;
      end case;
   end Check_Derived_Type;

   ---------------------
   -- Check_Dependent --
   ---------------------

   procedure Check_Dependent
     (Tipe    : in     Asis.Declaration;
      Exist   : in     Type_Data_Access;
      Data    : in     Package_Data;
      Info    : in     Classes.Type_Info;
      Point   : in out Visibility.Point)
   is
      use Type_Info_Lists;
      use Asis.Gela.Classes;
      Dependent : Cursor;
      Found     : Type_Data_Access;
      Refreshed : Type_Info;
   begin
      Dependent := First (Exist.Dependent);

      while Has_Element (Dependent) loop
         Found := Find (Data, Type_Info_Lists.Element (Dependent));

         if Found = null then
            raise Internal_Error;
         end if;

         Refreshed := Type_From_Declaration
           (Get_Declaration (Found.Info), Tipe);

         if not Is_Equal_Class (Found.Info, Refreshed) or
           Is_Limited (Found.Info) /= Is_Limited (Refreshed)
         then
            Implicit.Make_Operations
              (Tipe  => Refreshed,
               Was   => Found.Info,
               Point => Point);

            Found.Info := Refreshed;
            Check_Dependent (Tipe, Found, Data, Refreshed, Point);
         end if;

         Dependent := Next (Dependent);
      end loop;
   end Check_Dependent;

   ------------
   -- Greate --
   ------------

   function Create (Element : in Asis.Declaration) return Package_Data is
      Result : constant Package_Data := new Package_Data_Node;
   begin
      Result.Element := Element;
      return Result;
   end Create;

   ----------------
   -- Check_Type --
   ----------------

   procedure Check_Type
     (Element : in     Asis.Declaration;
      Data    : in     Package_Data;
      Point   : in out Visibility.Point)
   is
      use Asis.Elements;
      use Asis.Gela.Classes;

      Info  : constant Type_Info := Type_From_Declaration (Element, Element);
      Found : Type_Data_Access;
   begin
      if Declaration_Kind (Element) = Asis.A_Private_Type_Declaration then
         Create_Type_Data (Data, Info);
      else
         Found := Find (Data, Info);

         if Found /= null then
            if not Is_Equal_Class (Found.Info, Info) or
              Is_Limited (Found.Info) /= Is_Limited (Info)
            then
               Found.Info := Info;
               Check_Dependent (Element, Found, Data, Info, Point);
            end if;
         elsif Is_Composite (Info) then
            Fill_Dependencies (Element, Data, Info);
         end if;
      end if;
   end Check_Type;

   ----------------------
   -- Create_Type_Data --
   ----------------------

   procedure Create_Type_Data
     (Data    : in     Package_Data;
      Info    : in     Classes.Type_Info)
   is
      Result : constant Type_Data_Access := new Type_Data;
   begin
      Result.Info := Info;
      Type_Data_List.Append (Data.Types, Result);
   end Create_Type_Data;

   -----------------------
   -- Fill_Dependencies --
   -----------------------

   procedure Fill_Dependencies
     (Element : in     Asis.Declaration;
      Data    : in     Package_Data;
      Info    : in     Classes.Type_Info)
   is
      procedure Check_Component (Component_Type : Classes.Type_Info) is
         use Type_Info_Lists;
         Found : constant Type_Data_Access := Find (Data, Component_Type);
      begin
         --  If component type is subject to change:
         if Found /= null then
            --  If not in dependencies list yet:
            if not Contains (Found.Dependent, Info) then
               Append (Found.Dependent, Info);

               --  If new type not in subject_to_change list
               if Find (Data, Info) = null then
                  --  Add it to the list
                  Create_Type_Data (Data, Info);
               end if;
            end if;
         end if;
      end Check_Component;

      procedure Walk_Variant
        (Item     : in     Asis.Variant;
         Continue :    out Boolean) is
      begin
         Continue := True;
      end Walk_Variant;

      procedure Walk_Companent
        (Item     : in     Asis.Declaration;
         Continue :    out Boolean)
      is
         Component_Type : constant Classes.Type_Info :=
           Classes.Type_Of_Declaration (Item, Element);
      begin
         Check_Component (Component_Type);
         Continue := True;
      end Walk_Companent;

      procedure Walk_Components is new
        Utils.Walk_Components (Element, Walk_Variant, Walk_Companent);

      Continue : Boolean;
   begin
      if Classes.Is_Array (Info) then
         Check_Component (Classes.Get_Array_Element_Type (Info));
         --  elsif Derived?
      else
         Walk_Components (Element, Continue);
      end if;
   end Fill_Dependencies;

   ----------
   -- Find --
   ----------

   function Find
     (Data    : in     Package_Data;
      Info    : in     Classes.Type_Info) return Type_Data_Access
   is
      use Type_Data_List;
      Next : aliased Type_Data_Access;
   begin
      while Iterate (Data.Types, Next'Access) loop
         if Classes.Is_Equal (Next.Info, Info) then
            return Next;
         end if;
      end loop;

      return null;
   end Find;

   ---------------------
   -- On_Package_Body --
   ---------------------

   procedure On_Package_Body
     (Element : in     Asis.Declaration;
      Point   : in out Visibility.Point)
   is
      use Asis.Gela.Classes;

      Spec : Asis.Declaration :=
        Asis.Declarations.Corresponding_Declaration (Element);
      List : constant Asis.Declarative_Item_List :=
        Asis.Declarations.Visible_Part_Declarative_Items (Spec);
      Priv : constant Asis.Declarative_Item_List :=
        Asis.Declarations.Private_Part_Declarative_Items (Spec);
      From : Type_Info;
      To   : Type_Info;

      Body_View : constant Asis.Element :=
        Visibility.End_Of_Package (Element);
      Spec_View : Asis.Element;
   begin
      if Priv'Length = 0 then
         Spec_View := Visibility.End_Of_Package (Spec);
      else
         Spec_View := Priv (Priv'Last);
      end if;

      for J in List'Range loop
         From := Type_From_Declaration (List (J), Spec_View);
         To := Type_From_Declaration (List (J), Body_View);

         if not Is_Equal_Class (From, To) or
           Is_Limited (From) /= Is_Limited (To)
         then
            --  Ada.Wide_Text_IO.Put_Line ("Old:" & Debug_Image (From));
            --  Ada.Wide_Text_IO.Put_Line ("New:" & Debug_Image (To));
            Implicit.Make_Operations
              (Tipe  => To,
               Was   => From,
               Point => Point);
         end if;

         Check_Derived_Type (List (J), Body_View, Point);
      end loop;
   end On_Package_Body;

   ---------------------
   -- On_Private_Part --
   ---------------------

   procedure On_Private_Part
     (Element : in     Asis.Declaration;
      Point   : in out Visibility.Point)
   is
      use Asis.Gela.Classes;
      List : constant Asis.Declarative_Item_List :=
        Asis.Declarations.Visible_Part_Declarative_Items (Element);
      Priv : constant Asis.Declarative_Item_List :=
        Asis.Declarations.Private_Part_Declarative_Items (Element);
      From : Type_Info;
      To   : Type_Info;

      Spec_View : Asis.Element;
   begin
      if Priv'Length = 0 then
         Spec_View := Visibility.End_Of_Package (Element);
      else
         Spec_View := Priv (Priv'Last);
      end if;

      for J in List'Range loop
         From := Type_From_Declaration (List (J), List (List'Last));
         To   := Type_From_Declaration (List (J), Spec_View);

         if not Is_Equal_Class (From, To) or
           Is_Limited (From) /= Is_Limited (To)
         then
            Implicit.Make_Operations
              (Tipe  => To,
               Was   => From,
               Point => Point);
         end if;

         Check_Derived_Type (List (J), Spec_View, Point);
      end loop;
   end On_Private_Part;

   ----------
   -- Push --
   ----------

   procedure Push
     (Stack : in out Package_Data_Stack;
      Item  : in     Package_Data)
   is
   begin
      Prepend (Stack, Item);
   end Push;

   procedure Pop (Stack : in out Package_Data_Stack) is
      Item  : Package_Data;
   begin
      Delete_First (Stack, Item);
   end Pop;

   function Top (Stack : Package_Data_Stack) return Package_Data is
   begin
      return First (Stack);
   end Top;

   function Get_Next (Item : Package_Data) return Package_Data is
   begin
      return Item.Next;
   end Get_Next;

   function Get_Next (Item : Type_Data_Access) return Type_Data_Access is
   begin
      return Item.Next;
   end Get_Next;

   procedure Set_Next (Item, Next : Package_Data) is
   begin
      Item.Next := Next;
   end Set_Next;

   procedure Set_Next (Item, Next : Type_Data_Access) is
   begin
      Item.Next := Next;
   end Set_Next;

end Asis.Gela.Private_Operations;

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
