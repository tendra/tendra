with Ada.Characters.Handling;

with Asis.Clauses;
with Asis.Elements;
with Asis.Declarations;
with Asis.Compilation_Units;

with Asis.Gela.Utils;
with Asis.Gela.Errors;
with Asis.Gela.Elements;
with Asis.Gela.Element_Utils;

with XASIS.Utils;

package body Asis.Gela.Visibility.Utils is

   function Find_Body_Stub
     (Body_Decl : Asis.Declaration;
      Subunit   : Asis.Declaration) return Asis.Declaration;

   function Find_Corresponding_Declaration
     (Completion : Asis.Defining_Name;
      Point      : Visibility.Point) return Asis.Defining_Name;

   function Find_In_With_Or_Parent
     (Unit : Asis.Compilation_Unit;
      Name : Wide_String) return Boolean;

   function Find_Name_Internal
     (Name             : Asis.Program_Text;
      Until_Item       : Region_Item_Access;
      No_Parent_Region : Boolean := False)
      return Region_Item_Access;

   procedure Unhide_Region_Item
     (Defining_Name : in     Asis.Defining_Name;
      Point         : in     Visibility.Point);

   procedure Is_Char_Literal
     (Name         : in     Asis.Program_Text;
      Is_Wide_Wide :    out Boolean;
      Is_Wide_Char :    out Boolean;
      Is_Char      :    out Boolean);

   ----------------------
   -- Check_Completion --
   ----------------------

   procedure Check_Completion
     (Declaration : Asis.Declaration;
      Point       : Visibility.Point)
   is
      Completion_For : Asis.Defining_Name;
   begin
      declare
         List : constant Asis.Defining_Name_List :=
           Asis.Declarations.Names (Declaration);
      begin
         for I in List'Range loop
            Completion_For :=
              Find_Corresponding_Declaration (List (I), Point);
            Element_Utils.Set_Completion (Completion_For, Declaration);
         end loop;
      end;
   end Check_Completion;

   --------------
   -- Find_All --
   --------------

   procedure Find_All
     (Item             : in     Region_Item_Access;
      Index            : in out ASIS_Natural;
      Result           : in out Asis.Defining_Name_List;
      Unit             : in     Asis.Compilation_Unit;
      Point            : in     Visibility.Point;
      No_Parent_Region : in     Boolean := False)
   is
      use type Asis.List_Index;

      function Completion_Not_Exists return Boolean;

      function Unit_Withed
        (Item : Region_Item_Access;
         Unit : Asis.Compilation_Unit) return Boolean;

      function Completion_Not_Exists return Boolean is
         use XASIS.Utils;
         use Asis.Elements;

         Comp   : Asis.Declaration := Completion_For_Name (Item.Defining_Name);
         Decl   : Asis.Declaration;
         Found  : Boolean := False;
      begin
         if not Assigned (Comp) then
            return True;
         end if;

         for I in 1 .. Index loop
            Decl := Enclosing_Element (Result (I));
            if Is_Equal (Comp, Decl) then
               Found := True;
               exit;
            end if;
         end loop;
         return not Found;
      end Completion_Not_Exists;

      function Unit_Withed
        (Item : Region_Item_Access;
         Unit : Asis.Compilation_Unit) return Boolean
      is
         use Asis.Elements;
         use Asis.Compilation_Units;

         Decl_Unit  : Asis.Compilation_Unit :=
           Enclosing_Compilation_Unit (Item.Defining_Name);
         Unit_Name  : Wide_String := Unit_Full_Name (Decl_Unit);
      begin
         return Find_In_With_Or_Parent (Unit, Unit_Name);
      end Unit_Withed;

      function Not_Overridden return Boolean is
      begin
         for I in 1 .. Index loop
            if Is_Equal (Item.Defining_Name,
                         Element_Utils.Override (Result (I)))
            then
               return False;
            end if;
         end loop;
         return True;
      end Not_Overridden;

      function Is_Hidden
        (First  : Asis.Defining_Name;
         Second : Asis.Defining_Name) return Boolean
      is
         use Asis.Elements;
         Decl_1   : Asis.Declaration := Enclosing_Element (First);
         Decl_2   : Asis.Declaration := Enclosing_Element (Second);
         Parent_1 : Asis.Declaration;
         Parent_2 : Asis.Declaration;
         Comp     : Asis.Declaration;
         Kind     : Asis.Declaration_Kinds := Declaration_Kind (Decl_1);
      begin
         if Declaration_Kind (Decl_2) /= Kind then
            return False;
         end if;

         if Kind = A_Parameter_Specification then
            Parent_1 := Enclosing_Element (Decl_1);
            Parent_2 := Enclosing_Element (Decl_2);
         elsif Kind = A_Discriminant_Specification then
            Parent_1 := Enclosing_Element (Enclosing_Element (Decl_1));
            Parent_2 := Enclosing_Element (Enclosing_Element (Decl_2));
         else
            return False;
         end if;

         --  How about Accert statement ???

         if Declaration_Kind (Parent_1) in A_Body_Stub then
            Comp := Asis.Declarations.Corresponding_Subunit (Parent_1);
            if Is_Equal (Comp, Parent_2) then
               return True;
            end if;
         end if;

         Comp := XASIS.Utils.Completion_For_Declaration (Parent_1);
         return Is_Equal (Comp, Parent_2);
      end Is_Hidden;

      function Not_Hidden return Boolean is
      begin
         for I in 1 .. Index loop
            if Is_Hidden (Item.Defining_Name, Result (I)) then
               return False;
            end if;
         end loop;
         return True;
      end Not_Hidden;

   begin
      if (Item.Kind /= Definition or else not Item.Still_Hidden)
        and then Completion_Not_Exists
        and then Not_Overridden
        and then Not_Hidden
        and then Visible_From (Item, Point.Item)
        and then (Item.Kind /= Definition
                  or else not Item.Library_Unit
                  or else Unit_Withed (Item, Unit))
      then
         Index := Index + 1;
         Result (Index) := Item.Defining_Name;
      end if;

      if No_Parent_Region and then Item.Prev = null then
        return;
      end if;

      if Item.Prev /= null then
         Find_All (Item.Prev, Index, Result, Unit, Point, No_Parent_Region);
      elsif Item.Up /= null then
         Find_All (Item.Up, Index, Result, Unit, Point, No_Parent_Region);
      end if;
   end Find_All;

   --------------------
   -- Find_Body_Stub --
   --------------------

   function Find_Body_Stub
     (Body_Decl : Asis.Declaration;
      Subunit   : Asis.Declaration) return Asis.Declaration
   is
      use Asis.Elements;
      use Asis.Gela.Errors;
      use Asis.Declarations;

      List : Asis.Element_List := Body_Declarative_Items (Body_Decl);
      Name : constant Asis.Program_Text :=
        XASIS.Utils.Declaration_Direct_Name (Subunit);
   begin
      for I in List'Range loop
         if Declaration_Kind (List (I)) in A_Body_Stub
           and then XASIS.Utils.Has_Defining_Name (List (I), Name)
         then
            return List (I);
         end if;
      end loop;

      Report (Subunit, Error_No_Such_Stub);

      return Asis.Nil_Element;
   end Find_Body_Stub;

   ------------------------------------
   -- Find_Corresponding_Declaration --
   ------------------------------------

   function Find_Corresponding_Declaration
     (Completion : Asis.Defining_Name;
      Point      : Visibility.Point) return Asis.Defining_Name
   is
      use XASIS.Utils;
      use Asis.Elements;
      use Asis.Gela.Utils;

      Possible : Asis.Defining_Name_List :=
        Visibility.Lookup_In_Region (Completion, Point, Point);
      Index    : ASIS_Natural := 0;
      Decl     : Asis.Declaration;
   begin
      for I in Possible'Range loop
         Decl := Enclosing_Element (Possible (I));

         if not Overloadable (Possible (I)) or else
           (not Asis.Elements.Is_Part_Of_Implicit (Possible (I)) and then
            Are_Type_Conformant (Possible (I), Completion, Completion))
         then
            Index := I;
            exit;
         end if;
      end loop;

      if Index = 0 then
         return Nil_Element;
      end if;

      return Possible (Index);
   end Find_Corresponding_Declaration;

   ----------------------------
   -- Find_In_With_Or_Parent --
   ----------------------------

   function Find_In_With_Or_Parent
     (Unit : Asis.Compilation_Unit;
      Name : Wide_String) return Boolean
   is
      use Asis.Clauses;
      use Asis.Elements;
      use XASIS.Utils;
      use Asis.Compilation_Units;

      function With_Has_Name (Element : Asis.Element;
                              Name    : Program_Text)
                             return Boolean
      is
         Item : Asis.Element := Element;
      begin
         loop
            if Are_Equal_Identifiers (Name_Image (Item), Name) then
               return True;
            end if;

            if Expression_Kind (Item.all) = A_Selected_Component then
               Item := Prefix (Item.all);
            else
               return False;
            end if;
         end loop;
      end With_Has_Name;

      Next    : Asis.Compilation_Unit;
      Clauses : constant Context_Clause_List := Context_Clause_Elements (Unit);
      Unit_Name : Wide_String := Compilation_Units.Unit_Full_Name (Unit);
   begin
      if Are_Equal_Identifiers (Unit_Name, Name) then
         return True;
      end if;

      for I in Clauses'Range loop
         if Clause_Kind (Clauses (I)) = A_With_Clause then
            declare
               Names : constant Name_List := Clause_Names (Clauses (I));
            begin
               for J in Names'Range loop
                  if With_Has_Name (Names (J), Name) then
                     return True;
                  end if;
               end loop;
            end;
         end if;
      end loop;

      case Unit_Class (Unit) is
         when A_Separate_Body =>
            Next := Corresponding_Subunit_Parent_Body (Unit);
         when A_Private_Body | A_Public_Body =>
            Next := Corresponding_Declaration (Unit);
         when others =>
            Next := Corresponding_Parent_Declaration (Unit);
      end case;

      if Is_Nil (Next) then
         return False;
      else
         return Find_In_With_Or_Parent (Next, Name);
      end if;
   end Find_In_With_Or_Parent;

   ---------------
   -- Find_Name --
   ---------------

   function Find_Name
     (Name             : Asis.Program_Text;
      Point            : Visibility.Point;
      No_Parent_Region : Boolean := False)
      return Region_Item_Access
   is
   begin
      if Point.Item = null then
         return null;
      end if;

      return Find_Name_Internal (Name, Point.Item, No_Parent_Region);
   end Find_Name;

   ------------------------
   -- Find_Name_Internal --
   ------------------------

   function Find_Name_Internal
     (Name             : Asis.Program_Text;
      Until_Item       : Region_Item_Access;
      No_Parent_Region : Boolean := False)
     return Region_Item_Access
   is
      Item              : Region_Item_Access := Until_Item;
      Part              : Part_Access        := Item.Part;
      Region            : Region_Access      := Part.Region;
      Stored_Item       : Region_Item_Access;
      Is_Wide_Wide      : Boolean;
      Is_Wide_Char      : Boolean;
      Is_Char           : Boolean;

      procedure Fix_Item_Prev is
      begin
         --  Find the same name in the same region
         Item.Prev := Find_Name_Internal
           (Name             => Name,
            Until_Item       => Item.Next,
            No_Parent_Region => True);

         --  Find the same name in upper regions
         if Stored_Item.Part.Parent_Item /= null then
            Item.Up := Find_Name_Internal
              (Name       => Name,
               Until_Item => Stored_Item.Part.Parent_Item);
         end if;

         --  Count names in the same region
         if Item.Prev = null then
            Item.Count := 0;
         else
            Item.Count := Item.Prev.Count;

            if Item.Prev.Up /= null then
               Item.Count := Item.Count - Item.Prev.Up.Count;
            end if;
         end if;

         --  Increment count by names in upper regions
         if Item.Up /= null then
            Item.Count := Item.Count + Item.Up.Count;
         end if;

         --  Count this name too
         Item.Count := Item.Count + 1;
      end Fix_Item_Prev;
   begin
      Is_Char_Literal (Name, Is_Wide_Wide, Is_Wide_Char, Is_Char);

      --  loop over regions (Region)
      while Region /= null loop
         Stored_Item       := Item;

         --  loop over region items (Item)
         while Item /= null loop
            case Item.Kind is
               when Definition =>
                  if XASIS.Utils.Has_Name (Item.Defining_Name, Name) then
                     if Item.Count = 0 then
                        Fix_Item_Prev;
                     end if;

                     return Item;
                  end if;

               when Char | Wide_Char | Wide_Wide_Char =>
                  if Is_Wide_Wide or
                    (Is_Wide_Char and Item.Kind in Char .. Wide_Char) or
                    (Is_Char and Item.Kind = Char)
                  then
                     Fix_Item_Prev;

                     return Item;
                  end if;
               when others =>
                  null;
            end case;

            Item := Item.Next;

            if Item = null then
               Part := Part.Next;

               if Part /= null then
                  Item := Part.Last_Item;
               end if;
            end if;
         end loop;

         if No_Parent_Region then
            return null;
         end if;

         Item   := Stored_Item.Part.Parent_Item;

         if Item /= null then
            Part   := Item.Part;

            if Region.Library_Unit and Part.Kind in A_Children_Part then
               Item := Part.Last_Item;
            end if;

            Region := Part.Region;
         else
            Part   := null;
            Region := null;
         end if;
      end loop;

      return null;
   end Find_Name_Internal;

   ------------------------
   -- Find_Parent_Region --
   ------------------------

   procedure Find_Parent_Region
     (Unit      : in     Asis.Compilation_Unit;
      Point     :    out Visibility.Point)
   is
      use Asis.Elements;
      use Asis.Compilation_Units;

      Parent : Asis.Compilation_Unit;
      Decl   : Asis.Declaration;
      Item   : Region_Item_Access;
   begin
      if Unit_Kind (Unit) in Asis.A_Subunit then
         Parent := Corresponding_Subunit_Parent_Body (Unit);
         Decl   := Unit_Declaration (Parent);
         Decl   := Find_Body_Stub (Decl, Unit_Declaration (Unit));
         Item   := Get_Place (Decl);
         Point  := (Item => Item.Part.Parent_Item);
      else
         Parent := Corresponding_Parent_Declaration (Unit);

         if Is_Nil (Parent) then
            Point := (Item => Top_Region.First_Part.Last_Item);
         else
            Decl  := Unit_Declaration (Parent);
            Point := Find_Region (Decl);
         end if;
      end if;
   end Find_Parent_Region;

   -----------------
   -- Find_Region --
   -----------------

   function Find_Region (Element : Asis.Element) return Visibility.Point is
      Item : Region_Item_Access := Get_Place (Element);
   begin
      return (Item => Item.Part.Region.Last_Part.Last_Item);
   end Find_Region;

   ---------------
   -- Get_Place --
   ---------------

   function Get_Place
     (Point : in Asis.Element) return Region_Item_Access
   is
      use Asis.Gela.Elements;
      Element    : Asis.Element := Point;
      Item       : Region_Item_Access;
   begin
      while Item = null loop
         case Element_Kind (Element.all) is
            when Asis.A_Declaration =>
               Item := Place (Declaration_Node (Element.all));
            when Asis.An_Exception_Handler =>
               Item := Place (Exception_Handler_Node (Element.all));
            when Asis.A_Statement =>
               Item := Place (Statement_Node (Element.all));
            when Asis.A_Defining_Name =>
               Item := Place (Defining_Name_Node (Element.all));
            when Asis.A_Clause =>
               Item := Place (Clause_Node (Element.all));
            when others =>
               null;
         end case;

         if Item = null then
            Element := Enclosing_Element (Element.all);
         end if;
      end loop;

      return Item;
   end Get_Place;

   ---------------------------
   -- Goto_Enclosing_Region --
   ---------------------------

   function Goto_Enclosing_Region
     (Stmt  : in Asis.Statement)
      return Visibility.Point
     renames Find_Region;

   ---------------------
   -- Is_Char_Literal --
   ---------------------

   procedure Is_Char_Literal
     (Name         : in     Asis.Program_Text;
      Is_Wide_Wide :    out Boolean;
      Is_Wide_Char :    out Boolean;
      Is_Char      :    out Boolean)
   is
      use Ada.Characters.Handling;
   begin
      if Name (Name'First) = ''' then
         Is_Wide_Wide := True;
         Is_Wide_Char := Wide_Character'Pos (Name (Name'First + 1)) not in
           16#D800# .. 16#DFFF#;
         Is_Char      := Is_Character (Name (Name'First + 1));
      else
         Is_Wide_Wide := False;
         Is_Wide_Char := False;
         Is_Char      := False;
      end if;
   end Is_Char_Literal;

   -----------------
   -- Is_Declared --
   -----------------

   function Is_Declared (Name : in Asis.Defining_Name) return Boolean is
      use Asis.Gela.Elements;
      Name_Node  : Defining_Name_Ptr  := Defining_Name_Ptr (Name);
      Name_Place : Region_Item_Access := Place (Name_Node.all);
   begin
      return Name_Place /= null;
   end Is_Declared;

   -----------------
   -- Is_Template --
   -----------------

   function Is_Template (Decl : Asis.Declaration) return Boolean is
      use Asis.Elements;
      use Asis.Declarations;

      Template      : Asis.Declaration;
   begin
      if Is_Part_Of_Instance (Decl) then
         Template := Enclosing_Element (Decl);

         case Declaration_Kind (Template) is
            when A_Generic_Instantiation |
              A_Formal_Package_Declaration |
              A_Formal_Package_Declaration_With_Box =>
               return True;
            when others =>
               null;
         end case;
      end if;

      return False;
   end Is_Template;

   ------------------------
   -- Is_Top_Declaration --
   ------------------------

   function Is_Top_Declaration (Element : Asis.Element) return Boolean is
      use Asis.Elements;
      use Asis.Compilation_Units;

      Enclosing_Unit : constant Compilation_Unit :=
        Enclosing_Compilation_Unit (Element);
   begin
      return Is_Identical (Element, Unit_Declaration (Enclosing_Unit));
   end Is_Top_Declaration;

   ---------------------
   -- Is_Visible_Decl --
   ---------------------

   function Is_Visible_Decl (Tipe : in Asis.Declaration) return Boolean is
      Item : Region_Item_Access;
      List : Asis.Defining_Name_List := Asis.Declarations.Names (Tipe);
   begin
      if List'Length = 0 then
         return True;
      else
         Item := Get_Place (List (1));
         return Is_Visible (Item.Part.Kind);
      end if;
   end Is_Visible_Decl;

   ---------------------
   -- Need_New_Region --
   ---------------------

   function Need_New_Region (Element : Asis.Element) return Boolean is
      use type Asis.Type_Kinds;
      use type Asis.Element_Kinds;
      use type Asis.Statement_Kinds;
      use type Asis.Definition_Kinds;
      use type Asis.Declaration_Kinds;

      Kind : Asis.Element_Kinds := Asis.Elements.Element_Kind (Element);
      Tipe : Asis.Definition;
      Enum : Asis.Type_Kinds;
      Stmt : Asis.Statement_Kinds;
      Def  : Asis.Definition_Kinds;
      Decl : Asis.Declaration_Kinds;
   begin
      if Kind = Asis.An_Exception_Handler then
         return True;
      elsif Kind = Asis.A_Declaration then
         --  if XASIS.Utils.Is_Completion (Element) then
         --     return False;
         --  end if;

         Decl := Asis.Elements.Declaration_Kind (Element);

         if Decl = Asis.An_Ordinary_Type_Declaration then
            Tipe := Asis.Declarations.Type_Declaration_View (Element);
            Def := Asis.Elements.Definition_Kind (Tipe);

            if Def = Asis.A_Type_Definition then
               Enum := Asis.Elements.Type_Kind (Tipe);

               if Enum = Asis.An_Enumeration_Type_Definition then
                  return False;
               end if;
            end if;
         elsif Decl = Asis.A_Return_Object_Specification  then
            return False;
         end if;

         return True;
      elsif Kind /= Asis.A_Statement then
         return False;
      end if;

      Stmt := Asis.Elements.Statement_Kind (Element);

      if Stmt in Asis.A_Loop_Statement .. Asis.A_Block_Statement
        or Stmt = Asis.An_Accept_Statement
        or Stmt = Asis.An_Extended_Return_Statement
      then
         return True;
      end if;

      return False;
   end Need_New_Region;

   --------------------
   -- Set_Name_Place --
   --------------------

   procedure Set_Name_Place
     (Element : in Asis.Defining_Name;
      Point   : in Visibility.Point)
   is
      use Asis.Gela.Elements;
      Place : Region_Item_Access := Point.Item;
   begin
      Set_Place (Defining_Name_Node (Element.all), Place);
   end Set_Name_Place;

   ---------------
   -- Set_Place --
   ---------------

   procedure Set_Place
     (Element : in Asis.Element;
      Point   : in Visibility.Point)
   is
      use Asis.Gela.Elements;
      Place : Region_Item_Access := Point.Item;
   begin
      case Element_Kind (Element.all) is
         when Asis.A_Declaration =>
            Set_Place (Declaration_Node (Element.all), Place);
         when Asis.An_Exception_Handler =>
            Set_Place (Exception_Handler_Node (Element.all), Place);
         when Asis.A_Statement =>
            Set_Place (Statement_Node (Element.all), Place);
         when Asis.A_Clause =>
            Set_Place (Clause_Node (Element.all), Place);
         when others =>
            null;
      end case;
   end Set_Place;

   ---------------------
   -- Strip_Homograph --
   ---------------------

   procedure Strip_Homograph
     (Index            : in out Asis.List_Index;
      Result           : in out Asis.Defining_Name_List;
      Place            : in     Asis.Element)
   is
      use Asis.Gela.Utils;

      Passed : Asis.List_Index := 1;
      Failed : Boolean;
   begin
      for I in 2 .. Index loop
         Failed := False;

         for J in 1 .. Passed loop
            if Are_Homographs (Result (J), Result (I), Place) then
               Failed := True;
               exit;
            end if;
         end loop;

         if not Failed then
            Passed := Passed + 1;
            Result (Passed) := Result (I);
         end if;
      end loop;

      Index := Passed;
   end Strip_Homograph;

   ------------------------
   -- Unhide_Declaration --
   ------------------------

   procedure Unhide_Declaration
     (Element : in     Asis.Element;
      Point   : in     Visibility.Point)
   is
      Kind : Asis.Element_Kinds := Asis.Elements.Element_Kind (Element);
   begin
      pragma Assert (Kind = Asis.A_Declaration,
                     "Wrong construct in Unhide_Declaration");

      declare
         Names : Asis.Defining_Name_List :=
           Asis.Declarations.Names (Element);
      begin
         for I in Names'Range loop
            Unhide_Region_Item (Names (I), Point);
         end loop;
      end;
   end Unhide_Declaration;

   ------------------------
   -- Unhide_Region_Item --
   ------------------------

   procedure Unhide_Region_Item
     (Defining_Name : in     Asis.Defining_Name;
      Point         : in     Visibility.Point)
   is
      Item  : Region_Item_Access := Get_Place (Defining_Name);
   begin
      if Item.Kind = Definition and then
        Is_Equal (Item.Defining_Name, Defining_Name)
      then
         Item.Still_Hidden := False;
      end if;
   end Unhide_Region_Item;

   ------------------
   -- Visible_From --
   ------------------

   function Visible_From
     (Name  : in Region_Item_Access;
      Place : in Region_Item_Access)
      return Boolean
   is
      function Find_In_Region
        (Name         : in Region_Item_Access;
         Place        : in Region_Item_Access;
         With_Private : in Boolean) return Boolean
      is
         Place_Item   : Region_Item_Access := Place;
         Part         : Part_Access := Place_Item.Part;
      begin
         while Place_Item /= null loop
            if Place_Item = Name then
               if With_Private or Is_Visible (Name.Part.Kind) then
                  return True;
               else
                  return False;
               end if;
            end if;

            Place_Item := Place_Item.Next;

            if Place_Item = null then
               Part := Part.Next;

               if Part /= null then
                  Place_Item := Part.Last_Item;
               end if;
            end if;
         end loop;

         return False;
      end Find_In_Region;

      Name_Item    : Region_Item_Access := Name;
      Place_Item   : Region_Item_Access := Place;
      With_Private : Boolean := True;
      From_Visible : Boolean := Is_Visible (Place.Part.Kind);
      Pl_Reg       : Region_Access  := Place_Item.Part.Region;
   begin
      while Pl_Reg.Depth < Name_Item.Part.Region.Depth loop
         if not Is_Visible (Name_Item.Part.Kind) then
            return False;
         end if;

         Name_Item := Name_Item.Part.Parent_Item;
      end loop;

      while Pl_Reg.Depth > Name_Item.Part.Region.Depth loop
         if Pl_Reg.Library_Unit and Pl_Reg.Public_Child and From_Visible then
            With_Private := False;
         else
            With_Private := True;
         end if;

         Place_Item   := Place_Item.Part.Parent_Item;

         if Pl_Reg.Library_Unit and Place_Item.Part.Kind in A_Children_Part
         then
            Place_Item := Place_Item.Part.Last_Item;
         end if;

         From_Visible := Is_Visible (Place_Item.Part.Kind);
         Pl_Reg       := Place_Item.Part.Region;
      end loop;

      loop
         if Pl_Reg = Name_Item.Part.Region then
            return Find_In_Region (Name_Item, Place_Item, With_Private);
         end if;

         if not Is_Visible (Name_Item.Part.Kind) then
            return False;
         end if;

         if Pl_Reg.Library_Unit and Pl_Reg.Public_Child and From_Visible then
            With_Private := False;
         else
            With_Private := True;
         end if;

         if Pl_Reg.Library_Unit then
            Pl_Reg       := Place_Item.Part.Parent_Item.Part.Region;
            Place_Item   := Pl_Reg.Last_Part.Last_Item;
         else
            Place_Item   := Place_Item.Part.Parent_Item;
            Pl_Reg       := Place_Item.Part.Region;
         end if;

         From_Visible := Is_Visible (Place_Item.Part.Kind);
         Name_Item    := Name_Item.Part.Parent_Item;
      end loop;
   end Visible_From;

   ------------------
   -- Visible_From --
   ------------------

   function Visible_From
     (Name  : in Asis.Defining_Name;
      Point : in Asis.Element)
      return Boolean
   is
      use Asis.Elements;
      use Asis.Gela.Elements;

      function Child_Declaration_Part
        (Point    : Region_Item_Access;
         Element  : Asis.Element;
         Kind     : Part_Kinds) return Part_Access;

      --  Find child region marked by Element abd return
      --  Visible specification part.

      ----------------------------
      -- Child_Declaration_Part --
      ----------------------------

      function Child_Declaration_Part
        (Point    : Region_Item_Access;
         Element  : Asis.Element;
         Kind     : Part_Kinds) return Part_Access
      is
         Result : Region_Access := Point.Part.Region.First_Child;
         Part   : Part_Access;
      begin
         Search_Child_Region:
            while Result /= null loop
               Part := Result.Last_Part;

               while Part /= null loop
                  if Is_Equal (Part.Element, Element) then
                     exit Search_Child_Region;
                  end if;

                  Part := Part.Next;
               end loop;

               Result := Result.Next;

            end loop Search_Child_Region;

         if Result = null then
            return null;
         end if;

         Part := Result.Last_Part;

         while Part /= null loop
            if Part.Kind = Kind then
               return Part;
            end if;

            Part := Part.Next;
         end loop;

         return null;
      end Child_Declaration_Part;


      Name_Node  : Defining_Name_Ptr  := Defining_Name_Ptr (Name);
      Name_Place : Region_Item_Access := Place (Name_Node.all);
      Item       : Region_Item_Access := Get_Place (Point);
      Part       : Part_Access;
      Decl_Kind  : constant Asis.Declaration_Kinds :=
        Declaration_Kind (Enclosing_Element (Point));
   begin
      if Element_Kind (Point) = A_Defining_Name then
         if Decl_Kind = A_Package_Declaration then
            --  This is a special element to point to end of package
            Part := Child_Declaration_Part
              (Point   => Item,
               Element => Enclosing_Element (Point),
               Kind    => A_Private_Part);

            Item := Part.Last_Item;
         elsif Decl_Kind = A_Package_Body_Declaration then
            Part := Child_Declaration_Part
              (Point   => Item,
               Element => Enclosing_Element (Point),
               Kind    => A_Body_Part);

            Item := Part.Last_Item;
         end if;
      end if;

      if Name_Place = null then
         --  Name have not been processed yet
         return False;
      else
         return Visible_From (Name_Place, Item);
      end if;
   end Visible_From;

begin
   Top_Region.Last_Part := Top_Region.First_Part'Access;
   Top_Region.First_Part.Region    := Top_Region'Access;
   Top_Region.First_Part.Kind      := A_Public_Children_Part;
   Top_Region.First_Part.Last_Item := Top_Region.First_Part.Dummy_Item'Access;
   Top_Region.First_Part.Dummy_Item.Part := Top_Region.First_Part'Access;
end Asis.Gela.Visibility.Utils;



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
