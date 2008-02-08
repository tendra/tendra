with Asis.Clauses;
with Asis.Elements;
with Asis.Statements;
with Asis.Declarations;
with Asis.Compilation_Units;

with Asis.Gela.Debug;
with Asis.Gela.Utils;
with Asis.Gela.Classes;
with Asis.Gela.Errors;
with Asis.Gela.Element_Utils;
with Asis.Gela.Visibility.Utils;
with Asis.Gela.Private_Operations;

with XASIS.Types;
with XASIS.Utils;
with Ada.Wide_Text_IO;

package body Asis.Gela.Visibility.Create is

   procedure Find_Homograph
     (Defining_Name : in     Asis.Defining_Name;
      Point         : in     Visibility.Point;
      Homograph     :    out Asis.Defining_Name;
      Prev          :    out Region_Item_Access);

   procedure Region_Item
     (Defining_Name : in     Asis.Defining_Name;
      Point         : in out Visibility.Point;
      Tipe          : in     Asis.Declaration;
      Overridden    :    out Boolean);

   function Is_Public_Unit (Element : in Asis.Declaration) return Boolean;

   function Is_Overridden
     (First, Second : Asis.Defining_Name)
      return Boolean;

   procedure Is_Character
     (Name         : in     Asis.Defining_Name;
      Is_Wide_Char :    out Boolean;
      Is_Char      :    out Boolean);

   function Is_Library_Unit_Decl
     (Element : Asis.Element) return Boolean;

   --------------
   -- New_Part --
   --------------

   procedure New_Part
     (Region        : in  Region_Access;
      Kind          : in  Part_Kinds;
      Parent_Item   : in  Region_Item_Access;
      Element       : in  Asis.Element;
      Check_Private : in  Boolean;
      Result        : out Part_Access)
   is
      use Asis.Elements;

      --------------------------------
      -- Is_Private_Part_Of_Package --
      --------------------------------

      function Is_Private_Part_Of_Package return Boolean is
         Parent : Asis.Element := Enclosing_Element (Element);
      begin
         if Kind = A_Private_Part and
           Declaration_Kind (Parent) = A_Package_Declaration
         then
            return True;
         else
            return False;
         end if;
      end Is_Private_Part_Of_Package;

      Part  : Part_Access;
      Next  : Part_Access := Region.Last_Part;
      Prev  : Part_Access;
      Start : Point;
   begin
      --  Iterate over region parts
      --  Invariant: (Prev = null and Next = Region.Last_Part)
      --          or (Prev != null and Prev.Next = Next)
      while Next /= null loop
         if Next.Kind = Kind then
            Result := Next;
            return;
         end if;

         exit when Next.Kind < Kind;

         Prev := Next;
         Next := Prev.Next;
      end loop;

      if Region.First_Part.Region = null then
         Part := Region.First_Part'Access;
      else
         Part := new Part_Node;
      end if;

      Part.Dummy_Item.Part  := Part;
      Part.Region           := Region;
      Part.Next             := Next;
      Part.Kind             := Kind;
      Part.Parent_Item      := Parent_Item;
      Part.Last_Item        := Part.Dummy_Item'Access;
      Part.Element          := Element;

      if Prev = null then
         Region.Last_Part := Part;
      else
         Prev.Next := Part;
      end if;

      if Check_Private and then Is_Private_Part_Of_Package then
         Start := (Item => Part.Last_Item);

         --  if not empty private part:
         if Element_Kind (Element) /= A_Defining_Name then
            Utils.Set_Place (Element, Start);
            --  set place to private part to enable visibility check when
            --  we call Type_From_Declaration (List (J), Spec_View);
            --  where Spec_View is this Element (first in private part).
         end if;

         Private_Operations.On_Private_Part
           (Enclosing_Element (Element), Start);
      end if;

      Result := Part;
   end New_Part;

   ------------
   -- Region --
   ------------

   procedure Region
     (Element : in     Asis.Element;
      Point   : in out Visibility.Point)
   is
      use Asis.Elements;

      function Debug_Image return Wide_String is
         Spaces : constant Wide_String (1 .. 20) := (others => ' ');
         Depth : Natural := 0;
      begin
         if Point.Item.Part.Region /= null then
            Depth := Point.Item.Part.Region.Depth;
         end if;

         return Spaces (1 .. 2 * Depth) &
           Debug_Image (Element) &
           " ==> " &
           Debug_Image (Point.Item.Part.Region.First_Part.Element);
      end Debug_Image;

      pragma Assert (Debug.Run (Element, Debug.Create_Region)
                     or else Debug.Dump (Debug_Image));

      Child        : Region_Access := new Region_Node;
      Part         : Part_Access;
      Kind         : Part_Kinds;
   begin
      Child.Next         := Point.Item.Part.Region.First_Child;
      Child.Depth        := Point.Item.Part.Region.Depth + 1;

      if Is_Part_Of_Implicit (Element) then
         Kind := A_Public_Limited_View_Part;
      else
         Kind := A_Visible_Part;
      end if;

      if Is_Nil (Enclosing_Element (Element)) then
         Child.Library_Unit := True;
         Child.Public_Child := Is_Public_Unit (Element);
      else
         Child.Library_Unit := False;
         Child.Public_Child := True;
      end if;

      New_Part
        (Region        => Child,
         Kind          => Kind,
         Parent_Item   => Point.Item,
         Element       => Element,
         Check_Private => False,
         Result        => Part);

      Point.Item.Part.Region.First_Child := Child;

      Point  := (Item => Part.Last_Item);
   end Region;

   -----------------------
   -- Completion_Region --
   -----------------------

   procedure Completion_Region
     (Element     : in     Asis.Element;
      Point       : in out Visibility.Point;
      Is_Instance : in     Boolean;
      RR_Clause   : in     Boolean)
   is
      use Asis.Declarations;
      Name          : Asis.Expression;
      Decl          : Asis.Declaration;
      Prev          : Visibility.Point;
      Next          : Part_Access;
      Kind          : Part_Kinds;
   begin
      if RR_Clause then
         Name := Representation_Clause_Name (Element.all);
         Decl := Corresponding_Name_Declaration (Name.all);
      elsif Is_Instance then
         Decl := Asis.Elements.Enclosing_Element (Element);
      elsif Is_Subunit (Element) then
         Decl := Corresponding_Body_Stub (Element);

         if XASIS.Utils.Is_Completion (Decl) then
            Decl := XASIS.Utils.Declaration_For_Completion (Decl);
         end if;
      else
         Decl := XASIS.Utils.Declaration_For_Completion (Element);
      end if;

      if Asis.Elements.Declaration_Kind (Element) = A_Package_Declaration then
         Kind := A_Visible_Part;
      else
         Kind := A_Body_Part;
      end if;

      Prev := Utils.Find_Region (Decl);

      New_Part
        (Region        => Prev.Item.Part.Region,
         Kind          => Kind,
         Parent_Item   => Point.Item,
         Element       => Element,
         Check_Private => False,
         Result        => Next);

      Point.Item := Next.Last_Item;
   end Completion_Region;

----------------------

   ----------------
   -- Check_Part --
   ----------------

   procedure Check_Part
     (Item    : in Region_Item_Access;
      Kind    : in Part_Kinds;
      Element : in Asis.Element)
   is
      Part  : Part_Access;
      Next  : Region_Item_Access := Item;
   begin
      if Item.Part.Kind /= Kind then
         New_Part
           (Region        => Item.Part.Region,
            Kind          => Kind,
            Parent_Item   => Item.Part.Parent_Item,
            Element       => Element,
            Result        => Part,
            Check_Private => True);

         Item.Part := Part;
      else
         Part      := Item.Part;
      end if;

      Item.Next      := Part.Last_Item;
      Part.Last_Item := Item;
   end Check_Part;

   --------------------
   -- Find_Homograph --
   --------------------

   procedure Find_Homograph
     (Defining_Name : in     Asis.Defining_Name;
      Point         : in     Visibility.Point;
      Homograph     :    out Asis.Defining_Name;
      Prev          :    out Region_Item_Access)
   is
      use Asis.Gela.Utils;
      Name : constant Asis.Program_Text :=
        XASIS.Utils.Direct_Name (Defining_Name);
      Decl : constant Asis.Element :=
        Asis.Elements.Enclosing_Element (Defining_Name);
   begin
      Prev := Utils.Find_Name (Name, Point, No_Parent_Region => True);

      if Prev = null or else Prev.Count = 0 or else
        Asis.Elements.Declaration_Kind (Decl) in
        A_Procedure_Instantiation .. A_Function_Instantiation
      then
         --  Instantiation hasn't expanded at this moment yet, so we can't
         --  check it's profile and find homographs
         Homograph := Asis.Nil_Element;
         return;
      end if;

      declare
         Item  : aliased Visibility.Region_Item (Definition);
         Index : Asis.ASIS_Natural := 0;
         Unit  : constant Asis.Compilation_Unit :=
           Asis.Elements.Enclosing_Compilation_Unit (Defining_Name);
         List  : Asis.Defining_Name_List (1 .. Prev.Count + 1);
      begin
         Item.Part          := Point.Item.Part;
         Item.Next          := Point.Item.Part.Last_Item;
         Item.Defining_Name := Defining_Name;
         Item.Count         := Prev.Count + 1;
         Item.Prev          := Prev;
         Item.Still_Hidden  := False;

         Utils.Find_All (Item'Unchecked_Access,
                         Index, List, Unit,
                         (Item => Item'Unchecked_Access),
                         True);

         for I in 1 .. Index loop
            if not Asis.Elements.Is_Equal (Defining_Name, List (I))
              and then Are_Homographs (Defining_Name, List (I), Decl)
            then
               Homograph := List (I);
               return;
            end if;
         end loop;

         Homograph := Asis.Nil_Element;
      end;
   end Find_Homograph;

   ------------------
   -- Is_Character --
   ------------------

   Char : Classes.Type_Info;
   Wide : Classes.Type_Info;

   procedure Is_Character
     (Name         : in     Asis.Defining_Name;
      Is_Wide_Char :    out Boolean;
      Is_Char      :    out Boolean)
   is
      use Asis.Elements;
      Kind : constant Asis.Defining_Name_Kinds := Defining_Name_Kind (Name);
      Decl : Asis.Declaration := Enclosing_Element (Name);
      Tipe : Classes.Type_Info;
   begin
      Is_Wide_Char := False;
      Is_Char := False;

      if Kind /= A_Defining_Character_Literal then
         return;
      end if;

      if Classes.Is_Not_Type (Char) then
         Char := Classes.Type_From_Declaration (XASIS.Types.Character,
                                                XASIS.Types.Character);
         Wide := Classes.Type_From_Declaration (XASIS.Types.Wide_Character,
                                                XASIS.Types.Wide_Character);
      end if;

      Decl := Enclosing_Element (Enclosing_Element (Decl));
      Tipe := Classes.Type_From_Declaration (Decl, Decl);

      if Classes.Is_Child_Of (Tipe, Char) then
         Is_Wide_Char := True;
         Is_Char := True;
         return;
      elsif Classes.Is_Child_Of (Tipe, Wide) then
         Is_Wide_Char := True;
         Is_Char := False;
         return;
      end if;
   end Is_Character;

   --------------------------
   -- Is_Library_Unit_Decl --
   --------------------------

   function Is_Library_Unit_Decl
     (Element : Asis.Element) return Boolean
   is
      use Asis.Elements;
      use Asis.Compilation_Units;

      Class          : Unit_Classes;
      Enclosing_Unit : constant Compilation_Unit :=
        Enclosing_Compilation_Unit (Element);
   begin
      if Utils.Is_Top_Declaration (Element) then
         Class := Unit_Class (Enclosing_Unit);

         return Class = A_Public_Declaration or else
           Class = A_Public_Declaration_And_Body or else
           Class = A_Private_Declaration;
      else
         return False;
      end if;
   end Is_Library_Unit_Decl;

   -------------------
   -- Is_Overridden --
   -------------------

   function Is_Overridden
     (First  : Asis.Defining_Name;
      Second : Asis.Defining_Name)
      return Boolean
   is
      -- If First Overridden by Second
      use Asis.Elements;
   begin
      if not Is_Part_Of_Implicit (First) then
         --  If redeclaration
         return False;
      elsif not Is_Part_Of_Implicit (Second) then
         return True;
      elsif Is_Part_Of_Inherited (Second) then
         return True;
      elsif Operator_Kind (Second) = A_Not_Equal_Operator then
         --  This case not in RM, but when user defines "=" there is
         --  an implicit declaration of "/=" and it should override
         --  predefined "/=".
         return True;
      else
         return False;
      end if;
   end Is_Overridden;

   --------------------
   -- Is_Public_Unit --
   --------------------

   function Is_Public_Unit (Element : in Asis.Declaration) return Boolean is
      use Asis.Compilation_Units;
      use type Asis.Unit_Classes;
      Unit  : constant Asis.Compilation_Unit :=
        Asis.Elements.Enclosing_Compilation_Unit (Element);
      Class : constant Asis.Unit_Classes := Unit_Class (Unit);
   begin
      if Class = Asis.A_Private_Declaration then
         return False;
      end if;

      return True;
   end Is_Public_Unit;

   -----------------
   -- Region_Item --
   -----------------

   procedure Region_Item
     (Defining_Name : in     Asis.Defining_Name;
      Point         : in out Visibility.Point;
      Tipe          : in     Asis.Declaration;
      Overridden    :    out Boolean)
   is
      use Asis.Elements;
      use type Asis.List_Index;

      Item         : Region_Item_Access;
      Prev         : Region_Item_Access;
      Homograph    : Asis.Defining_Name;
      Is_Wide_Char : Boolean;
      Is_Char      : Boolean;
      Library_Unit : Boolean := False;
      Part_Kind    : Part_Kinds;
      Decl         : constant Asis.Element :=
        Enclosing_Element (Defining_Name);
   begin
      Overridden := False;

      if Asis.Declarations.Is_Subunit (Decl) or Utils.Is_Template (Decl) then
         return;
      end if;

      Find_Homograph (Defining_Name, Point, Homograph, Prev);

      if Assigned (Homograph) then
         Overridden := not Is_Overridden (Homograph, Defining_Name);

         if Overridden then
            return;
         end if;

         Element_Utils.Set_Override (Defining_Name, Homograph);
      end if;

      Is_Character (Defining_Name, Is_Wide_Char, Is_Char);

      if Is_Wide_Char then
         if Is_Char then
            Item := new Visibility.Region_Item (Visibility.Char);
         else
            Item := new Visibility.Region_Item (Visibility.Wide_Char);
         end if;
      else
         Item := new Visibility.Region_Item (Definition);
         Item.Still_Hidden  := Element_Kind (Decl) /= A_Statement;
         Item.Library_Unit  := Is_Library_Unit_Decl (Decl);
         Item.Prev          := Prev;
         Library_Unit       := Item.Library_Unit;

         if Prev /= null then
            Item.Count := Prev.Count + 1;
         else
            Item.Count := 0;
         end if;
      end if;

      Item.Defining_Name := Defining_Name;
      Item.Part          := Point.Item.Part;

      Part_Kind := Point.Item.Part.Kind;

      if Library_Unit then
         if Is_Part_Of_Implicit (Decl) then
            if Is_Public_Unit (Decl) then
               Part_Kind := A_Public_Limited_View_Part;
            else
               Part_Kind := A_Private_Limited_View_Part;
            end if;
         else
            if Is_Public_Unit (Decl) then
               Part_Kind := A_Public_Children_Part;
            else
               Part_Kind := A_Private_Children_Part;
            end if;
         end if;
      elsif not Assigned (Tipe) and then
        Part_Kind = A_Visible_Part and then
        not Gela.Utils.In_Visible_Part (Decl)
      then
         Part_Kind := A_Private_Part;
      end if;

      Check_Part (Item, Part_Kind, Decl);

      Point.Item     := Item;

      Utils.Set_Name_Place (Defining_Name, Point);
   end Region_Item;

   ------------------
   -- Region_Items --
   ------------------

   procedure Region_Items
     (Element    : in     Asis.Element;
      Point      : in out Visibility.Point;
      Tipe       : in     Asis.Declaration;
      Overridden :    out Boolean)
   is
      use type Asis.Element_Kinds;
   begin
      Overridden := False;

      case Asis.Elements.Element_Kind (Element) is
         when Asis.A_Declaration =>
            declare
               Names : constant Asis.Defining_Name_List :=
                 Asis.Declarations.Names (Element);
            begin
               for I in Names'Range loop
                  Create.Region_Item (Names (I), Point, Tipe, Overridden);

                  if Overridden then
                     return;
                  end if;
               end loop;
            end;

         when A_Statement =>
            declare
               Names : constant Asis.Defining_Name_List :=
                 Asis.Statements.Label_Names (Element);
            begin
               for I in Names'Range loop
                  Create.Region_Item (Names (I), Point, Tipe, Overridden);

                  if Overridden then
                     return;
                  end if;
               end loop;
            end;

         when others =>
            null;
      end case;
   end Region_Items;

   ----------------
   -- Use_Clause --
   ----------------

   procedure Use_Clause
     (Element : in     Asis.Element;
      Point   : in out Visibility.Point)
   is
      use Asis.Elements;

      Kind      : Item_Kinds;
   begin
      case Clause_Kind (Element) is
         when A_Use_Package_Clause =>
            Kind := Use_Package;
         when A_Use_Type_Clause =>
            Kind := Use_Type;
         when others =>
            return;
      end case;

      declare
         use XASIS.Utils;
         use Asis.Gela.Utils;
         use Asis.Gela.Errors;
         Declaration : Asis.Declaration;
         Item        : Region_Item_Access;
         Name_List   : constant Asis.Name_List :=
           Clauses.Clause_Names (Element);
         Visible     : constant Boolean :=
           In_Visible_Part (Element) or else
           In_Context_Clause (Element);
      begin
         for I in Name_List'Range loop
            Declaration      :=
              Unwind_Renamed (Selected_Name_Declaration (Name_List (I), True));
            Item             := new Visibility.Region_Item (Kind);
            Item.Part        := Point.Item.Part;
            Point.Item       := Item;

            if Kind = Use_Package then
               Item.Declaration := Declaration;
            else
               Item.Tipe := Classes.Type_From_Declaration
                 (Declaration, Element);
            end if;

            if not Visible and Item.Part.Kind = A_Visible_Part then
               Check_Part (Item, A_Private_Part, Element);
            else
               Item.Next := Item.Part.Last_Item;
               Item.Part.Last_Item := Item;
            end if;

            if not Assigned (Declaration) then
               Report (Name_List (I), Error_Unknown_Name);
            end if;
         end loop;
      end;
   end Use_Clause;

end Asis.Gela.Visibility.Create;



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
