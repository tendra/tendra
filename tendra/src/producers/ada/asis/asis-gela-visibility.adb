with Ada.Wide_Text_IO;

with Asis.Elements;
with Asis.Iterator;
with Asis.Statements;
with Asis.Gela.Lists;
with Asis.Gela.Errors;
with Asis.Expressions;
with Asis.Declarations;
with Asis.Gela.Debug;
with Asis.Gela.Utils;
with Asis.Gela.Element_Utils;
with Asis.Gela.Visibility.Utils;
with Asis.Gela.Visibility.Create;

with XASIS.Utils;

with Gela.Containers.Stacks;          use Gela;

package body Asis.Gela.Visibility is

   type Stack_Item is record
      Element : Asis.Element;
      Point   : Visibility.Point;
   end record;

   package Region_Stacks is new Containers.Stacks (Stack_Item);
   use Region_Stacks;

   Region_Stack : Stack;

   procedure Enter_Each_Construction
     (Element : in     Asis.Element;
      Point   : in out Visibility.Point);

   procedure Resolve_Profile
     (Construct : in     Asis.Element;
      Point     : in out Visibility.Point);

   procedure Resolve_RR_Name
     (Construct : in     Asis.Element;
      Point     : in out Visibility.Point);

   procedure Pre_Op (Element : in     Asis.Element;
                     Control : in out Asis.Traverse_Control;
                     State   : in out Visibility.Point);

   procedure Post_Op (Element : in     Asis.Element;
                      Control : in out Asis.Traverse_Control;
                      State   : in out Visibility.Point);

   procedure Resolve_Names is
      new Asis.Iterator.Traverse_Element
        (State_Information => Visibility.Point,
         Pre_Operation     => Pre_Op,
         Post_Operation    => Post_Op);

   function Get_Name (Element : Asis.Element) return Asis.Program_Text;

   function Lookup_Operators
     (Item : Asis.Element;
      Tipe : Asis.Declaration) return Asis.Defining_Name_List;

   function Print_Region (Point  : Visibility.Point) return Boolean;

   procedure Print_Region
     (Point  : Visibility.Point;
      Prefix : Wide_String := "";
      Mark   : Visibility.Point);

   --------------------
   -- End_Of_Package --
   --------------------

   function End_Of_Package
     (The_Package : Asis.Declaration)
     return Asis.Element
   is
      use Asis.Elements;
   begin
      case Declaration_Kind (The_Package) is
         when A_Package_Declaration |
           A_Package_Body_Declaration =>
            return Declarations.Names (The_Package) (1);
         when others =>
            raise Internal_Error;
      end case;
   end End_Of_Package;

   ------------------------
   -- Enter_Construction --
   ------------------------

   procedure Enter_Construction
     (Element : in     Asis.Element;
      Point   : in out Visibility.Point)
   is
   begin
      if not Utils.Is_Top_Declaration (Element) then
         Enter_Each_Construction (Element, Point);
      end if;
   end Enter_Construction;

   -----------------------------
   -- Enter_Each_Construction --
   -----------------------------

   procedure Enter_Each_Construction
     (Element : in     Asis.Element;
      Point   : in out Visibility.Point)
   is
      use Asis.Elements;

      procedure Try_Unhide_Parent is
         Decl : constant Asis.Declaration :=
           XASIS.Utils.Parent_Declaration (Element);
      begin
         if not Is_Nil (Decl) then
            case Declaration_Kind (Decl) is
               when A_Package_Declaration |
                 A_Generic_Package_Declaration |
                 A_Procedure_Body_Declaration |
                 A_Function_Body_Declaration =>

                 Utils.Unhide_Declaration (Decl, Point);

               when others =>
                  null;
            end case;
         end if;
      end Try_Unhide_Parent;

      Kind        : constant Asis.Element_Kinds := Element_Kind (Element);
      Stmt        : Asis.Statement_Kinds;
      Needed      : Boolean := False;
      Is_Compl    : Boolean := False;
      Is_Instance : Boolean := False;
      RR_Clause   : Boolean := False;
      Overridden  : Boolean := False;
   begin
      Utils.Set_Place (Element, Point);

      case Kind is
         when Asis.A_Declaration =>
            Try_Unhide_Parent;
            Resolve_Profile (Element, Point);
            Needed := True;

            if XASIS.Utils.Can_Be_Completion (Element) then
               Utils.Check_Completion (Element, Point);
               Is_Compl := XASIS.Utils.Is_Completion (Element)
                 or Asis.Declarations.Is_Subunit (Element);
            end if;

            if Utils.Is_Template (Element) then
               Is_Instance := True;
            end if;
         when Asis.An_Exception_Handler =>
            Needed := True;
         when Asis.A_Statement =>
            Try_Unhide_Parent;
            Resolve_Profile (Element, Point);
            Stmt := Asis.Elements.Statement_Kind (Element);

            if Stmt in Asis.A_Loop_Statement .. Asis.A_Block_Statement or
              Stmt = Asis.An_Accept_Statement or
              Stmt = Asis.An_Extended_Return_Statement
            then
               Needed := True;
            end if;

         when A_Definition =>
            case Definition_Kind (Element) is
               when A_Record_Definition |
                 A_Null_Record_Definition |
                 A_Task_Definition |
                 A_Protected_Definition =>

                  Utils.Unhide_Declaration
                    (XASIS.Utils.Parent_Declaration (Element), Point);

               when others =>
                  null;
            end case;

         when A_Pragma =>
            Try_Unhide_Parent;

         when A_Clause =>
            case Representation_Clause_Kind (Element) is
               when A_Record_Representation_Clause =>
                  Resolve_RR_Name (Element, Point);
                  RR_Clause := True;
                  Needed := True;
               when others =>
                  null;
            end case;
         when others =>
            null;
      end case;

      Create.Region_Items (Element, Point, Asis.Nil_Element, Overridden);

      if Overridden then
         Errors.Report (Element, Errors.Error_Name_Redeclaration);
      end if;

      if not Needed then
         return;
      end if;

      if Utils.Need_New_Region (Element) or RR_Clause then
         if Is_Compl or Is_Instance or RR_Clause then
            Push (Region_Stack, (Element, Point));
            Create.Completion_Region (Element, Point, Is_Instance, RR_Clause);
         else
            Push (Region_Stack, (Element, Point));
            Create.Region (Element, Point);
         end if;
      end if;

      if Kind /= A_Defining_Name then
         Utils.Set_Place (Element, Point);  --  set place to deeper region
      end if;
   end Enter_Each_Construction;

   ----------------
   -- Enter_Unit --
   ----------------

   function Enter_Unit (Unit : Asis.Compilation_Unit) return Point is
      Point   : Visibility.Point;
      Element : Asis.Element;
   begin
      Utils.Find_Parent_Region (Unit, Point);
      Element := Asis.Elements.Unit_Declaration (Unit);
      Enter_Each_Construction (Element, Point);

      return Point;
   end Enter_Unit;

   --------------
   -- Get_Name --
   --------------

   function Get_Name (Element : Asis.Element) return Asis.Program_Text is
   begin
      if Asis.Elements.Element_Kind (Element) = An_Expression then
         return Asis.Expressions.Name_Image (Element);
      else
         return XASIS.Utils.Direct_Name (Element);
      end if;
   end Get_Name;

   -----------------
   -- Is_Declared --
   -----------------

   function Is_Declared (Name : in Asis.Defining_Name) return Boolean
     renames Utils.Is_Declared;

   ------------------------
   -- Leave_Construction --
   ------------------------

   procedure Leave_Construction
     (Element : in     Asis.Element;
      Point   : in out Visibility.Point)
   is
      use XASIS.Utils;
      use Asis.Elements;

      Kind      : constant Asis.Element_Kinds := Element_Kind (Element);
      Item      : Stack_Item;
      Part      : Part_Access;
   begin
      case Kind is
         when Asis.A_Declaration  =>
            Utils.Unhide_Declaration (Element, Point);

            case Declaration_Kind (Element) is
               when A_Package_Declaration =>
                  if Point.Item.Part.Kind = A_Visible_Part and not
                    Is_Part_Of_Implicit (Element)
                  then
                     Create.New_Part
                       (Region        => Point.Item.Part.Region,
                        Kind          => A_Private_Part,
                        Parent_Item   => Point.Item.Part.Parent_Item,
                        Element       => Declaration_Name (Element),
                        Check_Private => True,
                        Result        => Part);
                  end if;
               when others =>
                  null;
            end case;
         when Asis.A_Clause =>
            Create.Use_Clause (Element, Point);

         when others =>
            null;
      end case;

      if not Is_Empty (Region_Stack)
        and then Is_Equal (Top (Region_Stack).Element, Element)
      then
         Pop (Region_Stack, Item);
         Point := Item.Point;
      elsif Utils.Need_New_Region (Element) then
         raise Internal_Error;
      end if;
   end Leave_Construction;

   ------------
   -- Lookup --
   ------------

   function Lookup
     (Item  : Asis.Element;
      Point : Visibility.Point)
      return Asis.Defining_Name_List
   is
      pragma Assert (Debug.Run (Item, Debug.Lookup)
                     or else Print_Region (Point));

      Direct : constant Asis.Defining_Name_List := Lookup_Direct (Item, Point);
   begin
      return Direct & Lookup_Use (Item, Direct, Point);
   end Lookup;

   -------------------
   -- Lookup_Direct --
   -------------------

   function Lookup_Direct
     (Item  : Asis.Element;
      Point : Visibility.Point)
      return Asis.Defining_Name_List
   is
      use Asis.Elements;

      Name  : constant Asis.Program_Text  := Get_Name (Item);
      First : constant Region_Item_Access := Utils.Find_Name (Name, Point);
      Unit  : constant Asis.Compilation_Unit :=
        Enclosing_Compilation_Unit (Item);
   begin
      if First = null then
         return Asis.Nil_Element_List;
      end if;

      declare
         Result : Asis.Defining_Name_List (1 .. First.Count);
         Index  : Asis.ASIS_Natural := 0;
      begin
         Utils.Find_All (First, Index, Result, Unit, Point);

         if Index /= 0 then
            Utils.Strip_Homograph (Index, Result, Item);
         end if;

         return Result (1 .. Index);
      end;
   end Lookup_Direct;

   -----------------------------
   -- Lookup_In_Parent_Region --
   -----------------------------

   function Lookup_In_Parent_Region
     (Item    : Asis.Element;
      Element : Asis.Element) return Asis.Defining_Name_List
   is
      Point : Visibility.Point := Utils.Find_Region (Element);
   begin
      Point :=
        (Item => Point.Item.Part.Parent_Item.Part.Region.Last_Part.Last_Item);

      return Lookup_In_Region (Item, Point);
   end Lookup_In_Parent_Region;

   ----------------------
   -- Lookup_In_Region --
   ----------------------

   function Lookup_In_Region
     (Item  : Asis.Element;
      Point : Visibility.Point)
      return Asis.Defining_Name_List
   is
      use Asis.Elements;

      Name  : constant Asis.Program_Text     := Get_Name (Item);
      Unit  : constant Asis.Compilation_Unit :=
        Enclosing_Compilation_Unit (Item);
      First : constant Region_Item_Access :=
        Utils.Find_Name (Name, Point, No_Parent_Region => True);
   begin
      if First = null or else First.Part.Region /= Point.Item.Part.Region then
         return Asis.Nil_Element_List;
      end if;

      declare
         Result : Asis.Defining_Name_List (1 .. First.Count);
         Index  : Asis.ASIS_Natural := 0;
      begin
         Utils.Find_All
           (First, Index, Result, Unit, Point, No_Parent_Region => True);

         return Result (1 .. Index);
      end;
   end Lookup_In_Region;

   ----------------------
   -- Lookup_In_Region --
   ----------------------

   function Lookup_In_Region
     (Item    : Asis.Element;
      Element : Asis.Element)
      return Asis.Defining_Name_List
   is
      Point : constant Visibility.Point := Utils.Find_Region (Element);
   begin
      return Lookup_In_Region (Item, Point);
   end Lookup_In_Region;

   ----------------------
   -- Lookup_Operators --
   ----------------------

   function Lookup_Operators
     (Item : Asis.Element;
      Tipe : Asis.Declaration) return Asis.Defining_Name_List
   is
      Name   : constant Asis.Program_Text  := Get_Name (Item);
      Def    : constant Asis.Definition :=
        Asis.Declarations.Type_Declaration_View (Tipe);
      List   : constant Asis.Declaration_List :=
        Corresponding_Type_Operators (Def.all);
      --  Asis.Definitions.Corresponding_Type_Operators (Def);
      --  because we want Private_Type_Definition, etc
      Result : Asis.Defining_Name_List (List'Range);
      Index  : Asis.List_Index := 1;
   begin
      for I in List'Range loop
         Result (Index) := XASIS.Utils.Get_Defining_Name (List (I), Name);
         if Assigned (Result (Index))
           and then Visible_From (Result (Index), Item)
         then
            Index := Index + 1;
         end if;
      end loop;

      return Result (1 .. Index - 1);
   end Lookup_Operators;

   ----------------
   -- Lookup_Use --
   ----------------

   function Lookup_Use
     (Item   : Asis.Element;
      Direct : Asis.Defining_Name_List;
      Point  : Visibility.Point)
      return Asis.Defining_Name_List
   is
      use Asis.Gela.Utils;
      use Asis.Gela.Lists.Secondary_Definition_Lists;

      procedure Check_And_Add
        (Local : in     Asis.Defining_Name_List;
         List  : in out List_Node;
         Item  : in     Asis.Defining_Name;
         Fail  :    out Boolean)
      is
      begin
         for I in Local'Range loop
            if Are_Homographs (Local (I), Item, Lookup_Use.Item) then
               Fail := False;
               return;
            end if;
         end loop;

         for I in 1 .. Length (List) loop
            if Is_Equal (Get (List, I), Item) then
               Fail := False;
               return;
            end if;
         end loop;

         if Length (List) = 1 then
            if not XASIS.Utils.Overloadable (Get (List, 1)) then
               Fail := True;
               return;
            end if;
         end if;

         if not XASIS.Utils.Overloadable (Item) and Length (List) > 0 then
            Fail := True;
            return;
         end if;

         Add (List, Item);
         Fail := False;
      end Check_And_Add;

      List         : List_Node;
      Next         : Region_Item_Access := Point.Item;
      Part         : Part_Access        := Next.Part;
      Region       : Region_Access      := Part.Region;
      Stored_Item  : Region_Item_Access;
      With_Private : Boolean := True;
      From_Visible : Boolean;
      Fail         : Boolean;
   begin
      --  loop over regions (Region)
      while Region /= null loop
         Stored_Item  := Next;
         From_Visible := Is_Visible (Next.Part.Kind);

         --  loop over region items (Item)
         while Next /= null loop
            if not With_Private
              and Region.Library_Unit
              and not Is_Visible (Next.Part.Kind)
            then
               null;
            elsif Next.Kind = Use_Package then
               declare
                  Names : constant Asis.Defining_Name_List :=
                    Lookup_In_Region (Item, Next.Declaration);
               begin
                  for I in Names'Range loop
                     Check_And_Add (Direct, List, Names (I), Fail);

                     if Fail then
                        return Asis.Nil_Element_List;
                     end if;
                  end loop;
               end;
            elsif Next.Kind = Use_Type then
               declare
                  Names : constant Asis.Defining_Name_List :=
                    Lookup_Operators (Item, Next.Declaration);
               begin
                  for I in Names'Range loop
                     Check_And_Add (Direct, List, Names (I), Fail);

                     if Fail then
                        return Asis.Nil_Element_List;
                     end if;
                  end loop;
               end;
            end if;

            Next := Next.Next;

            if Next = null then
               Part := Part.Next;

               if Part /= null then
                  Next := Part.Last_Item;
               end if;
            end if;
         end loop;

         if Region.Library_Unit
           and Region.Public_Child
           and From_Visible
         then
            With_Private := False;
         else
            With_Private := True;
         end if;

         Next := Stored_Item.Part.Parent_Item;

         if Next /= null then
            Part := Next.Part;
            Region := Part.Region;
         else
            Part   := null;
            Region := null;
         end if;
      end loop;

      return To_Element_List (List);
   end Lookup_Use;

   ------------------------------
   -- New_Implicit_Declaration --
   ------------------------------

   procedure New_Implicit_Declaration
     (Element    : in     Asis.Declaration;
      Point      : in out Visibility.Point;
      Tipe       : in     Asis.Declaration;
      Overridden :    out Boolean)
   is
   begin
      Utils.Set_Place (Element, Point);
      Create.Region_Items (Element, Point, Tipe, Overridden);

      if not Overridden then
         Utils.Unhide_Declaration (Element, Point);
      end if;
   end New_Implicit_Declaration;

   -------------
   -- Post_Op --
   -------------

   procedure Post_Op (Element : in     Asis.Element;
                      Control : in out Asis.Traverse_Control;
                      State   : in out Visibility.Point) is
   begin
      null;
   end Post_Op;

   ------------
   -- Pre_Op --
   ------------

   procedure Pre_Op (Element : in     Asis.Element;
                     Control : in out Asis.Traverse_Control;
                     State   : in out Visibility.Point)
   is
      Expr : constant Expression_Kinds :=
        Asis.Elements.Expression_Kind (Element);
   begin
      if (Expr = An_Identifier or
        Expr = An_Operator_Symbol or
        Expr = A_Character_Literal) and
        not Elements.Is_Part_Of_Implicit (Element) and
        not Elements.Is_Part_Of_Instance (Element)
      then
         Try_To_Resolve (Element, State);
      end if;
   end Pre_Op;

   ------------------
   -- Print_Region --
   ------------------

   function Print_Region (Point  : Visibility.Point) return Boolean is
   begin
      Print_Region ((Item => Utils.Top_Region.First_Part.Last_Item),
                    Mark => Point);
      return True;
   end Print_Region;

   ------------------
   -- Print_Region --
   ------------------

   procedure Print_Region
     (Point  : Visibility.Point;
      Prefix : Wide_String := "";
      Mark   : Visibility.Point)
   is
      use Asis.Elements;
      use Ada.Wide_Text_IO;
      Item     : Region_Item_Access := Point.Item;
      Part     : constant Part_Access := Item.Part;
      Region   : Region_Access := Part.Region;
      Part_I   : Part_Access := Region.Last_Part;
      Lib_Unit : Wide_Character := ' ';
      Public   : Wide_Character := ' ';
      Current  : Wide_Character := ' ';
      Visible  : Wide_Character := ' ';
      Depth    : constant Wide_String := Integer'Wide_Image (Region.Depth);
   begin
      if Point.Item = null then
         return;
      end if;

      if Region.Library_Unit then
         Lib_Unit := 'L';
      end if;
      if Region.Public_Child then
         Public := 'P';
      end if;

      Put_Line (Prefix & "<region lib='" & Lib_Unit &
                "' pub='" & Public & "' depth='" & Depth & "'>");

      while Part_I /= null loop
         Put_Line (Prefix & "<part kind='" &
                   Part_Kinds'Wide_Image (Part_I.Kind) & "'>");

         Put_Line (Prefix & " <element img='" &
                   Debug_Image (Part_I.Element) & "'/>");

         if Part_I.Parent_Item /= null then
            Put_Line (Prefix & "<parent name='" &
                      Debug_Image (Part_I.Parent_Item.Defining_Name) &
                      "'/>");
         end if;

         Item := Part_I.Last_Item;

         while Item /= null loop
            if Item = Mark.Item then
               Current := 'C';
            else
               Current := ' ';
            end if;

            case Item.Kind is
               when Definition | Char | Wide_Char =>
                  if Item.Kind = Definition and then Item.Still_Hidden then
                     Visible := 'H';
                  else
                     Visible := ' ';
                  end if;

                  if Item.Kind = Definition and then Item.Library_Unit then
                     Lib_Unit := 'L';
                  else
                     Lib_Unit := ' ';
                  end if;

                  Put_Line (Prefix & "<item cur='" & Current
                            & "' vis='" & Visible & "' lib='" & Lib_Unit
                            & "' name='" & Debug_Image (Item.Defining_Name)
                            & "' cnt='"
                            & ASIS_Natural'Wide_Image (Item.Count)
                            & "'/>");
               when Use_Package =>
                  Put_Line (Prefix & "<use_pkg cur='" & Current
                            & "' decl='"
                            & Debug_Image (Item.Declaration) & "'/>");
               when Use_Type =>
                  Put_Line (Prefix & "<use_type cur='"  & Current
                            & "' decl='"
                            & Debug_Image (Item.Declaration) & "'/>");
               when Dummy =>
                  Put_Line (Prefix & "<dummy cur='" & Current & "'/>");
            end case;

            Item := Item.Next;
         end loop;

         Put_Line (Prefix & "</part>");
         Part_I := Part_I.Next;
      end loop;

      Region := Region.First_Child;

      while Region /= null loop
         Print_Region ((Item => Region.First_Part.Last_Item),
                       Prefix & "   ", Mark);
         Region := Region.Next;
      end loop;

      Put_Line (Prefix & "</region>");
   end Print_Region;

   ------------------
   -- Print_Region --
   ------------------

   procedure Print_Region
     (Point  : Visibility.Point;
      Prefix : Wide_String := "")
   is
   begin
      Print_Region (Point, Prefix, (Item => null));
   end Print_Region;

   ---------------------------
   -- Print_Standard_Region --
   ---------------------------

   procedure Print_Standard_Region is
   begin
      Print_Region ((Item => Utils.Top_Region.First_Part.Last_Item));
   end Print_Standard_Region;

   ---------------------
   -- Resolve_Profile --
   ---------------------

   procedure Resolve_Profile
     (Construct : in     Asis.Element;
      Point     : in out Visibility.Point)
   is
      use Asis.Elements;
      use Asis.Statements;
      use Asis.Declarations;

      Control : Asis.Traverse_Control  := Continue;

      procedure Resolve_Profile (List : Asis.Parameter_Specification_List) is
         Mark : Asis.Expression;
      begin
         for I in List'Range loop
            Mark := Object_Declaration_Subtype (List (I));
            Resolve_Names (Mark, Control, Point);
         end loop;
      end Resolve_Profile;

      Kind    : constant Asis.Declaration_Kinds :=
        Declaration_Kind (Construct);
   begin
      if Kind = A_Function_Declaration or
         Kind = A_Function_Body_Declaration or
         Kind = A_Function_Renaming_Declaration or
         Kind = A_Function_Body_Stub or
         Kind = A_Generic_Function_Declaration or
         Kind = A_Formal_Function_Declaration
      then
         Resolve_Names (Result_Subtype (Construct), Control, Point);
      end if;

      if Kind = A_Function_Declaration or
         Kind = A_Function_Body_Declaration or
         Kind = A_Function_Renaming_Declaration or
         Kind = A_Function_Body_Stub or
         Kind = A_Generic_Function_Declaration or
         Kind = A_Formal_Function_Declaration or
         Kind = A_Procedure_Declaration or
         Kind = A_Procedure_Body_Declaration or
         Kind = A_Procedure_Renaming_Declaration or
         Kind = An_Entry_Declaration or
         Kind = An_Entry_Body_Declaration or
         Kind = A_Procedure_Body_Stub or
         Kind = A_Generic_Procedure_Declaration or
         Kind = A_Formal_Procedure_Declaration
      then
         Resolve_Profile (Parameter_Profile (Construct));
      elsif Statement_Kind (Construct) = An_Accept_Statement then
         Resolve_Profile (Accept_Parameters (Construct));
      end if;
   end Resolve_Profile;

   ---------------------
   -- Resolve_RR_Name --
   ---------------------

   procedure Resolve_RR_Name
     (Construct : in     Asis.Element;
      Point     : in out Visibility.Point)
   is
      Name    : constant Asis.Expression :=
        Representation_Clause_Name (Construct.all);
      Control : Asis.Traverse_Control  := Continue;
   begin
      Resolve_Names (Name, Control, Point);
   end Resolve_RR_Name;

   ----------------------
   -- Set_Not_Declared --
   ----------------------

   procedure Set_Not_Declared (Name : in Asis.Defining_Name) is
   begin
      Utils.Set_Name_Place (Name, (Item => null));
   end Set_Not_Declared;

   --------------------
   -- Try_To_Resolve --
   --------------------

   procedure Try_To_Resolve
     (Element : Asis.Expression;
      Point   : Visibility.Point)
   is
      use Asis.Elements;
      use Asis.Expressions;

      type Resolution is record
         Allowed   : Boolean;
         In_Region : Boolean;
         Construct : Asis.Element;
      end record;

      procedure Check (Result : out Resolution);

      procedure Set_Region
        (Result : in out Resolution;
         Parent : in     Asis.Expression);

      function Is_Enclosing_Named_Construct
        (Parent  : Asis.Element;
         Name    : Asis.Defining_Name) return Boolean;

      procedure Check (Result : out Resolution) is
         Parent : constant Asis.Element := Enclosing_Element (Element);
      begin
         Result.Allowed   := True;
         Result.In_Region := False;

         case Element_Kind (Parent) is
            when A_Pragma =>
               Result.Allowed := False;
            when An_Association =>
               case Association_Kind (Parent) is
                  when A_Record_Component_Association |
                       An_Array_Component_Association =>
--                   if not Is_Equal (Element, Component_Expression (Parent))
--                   then
--                      Result.Allowed := False;
--                   end if;
                     null;
                  when others =>
                     if not Is_Equal (Element, Actual_Parameter (Parent)) then
                        Result.Allowed := False;
                     end if;
               end case;
            when An_Expression =>
               case Expression_Kind (Parent) is
                  when A_Selected_Component =>
                     if Is_Equal (Element, Selector (Parent)) then
                        Set_Region (Result, Prefix (Parent));
                     end if;
                  when An_Attribute_Reference =>
                     if Is_Equal (Element,
                                  Attribute_Designator_Identifier (Parent))
                     then
                        Result.Allowed := False;
                     end if;
                  when others =>
                     null;
               end case;
            when others =>
               null;
         end case;
      end Check;

      function Is_Enclosing_Named_Construct
        (Parent  : Asis.Element;
         Name    : Asis.Defining_Name) return Boolean
      is
         use Asis.Statements;
         use Asis.Declarations;

         Declaration : Asis.Declaration   := Nil_Element;
         Parent_Name : Asis.Defining_Name := Nil_Element;
      begin
         if Is_Nil (Parent) then
            return False;
         end if;
         case Element_Kind (Parent) is
            when A_Declaration =>
               case Declaration_Kind (Parent) is
                  when A_Task_Type_Declaration |
                    A_Protected_Type_Declaration |
                    A_Single_Task_Declaration |
                    A_Single_Protected_Declaration |
                    A_Procedure_Declaration |
                    A_Function_Declaration |
                    A_Procedure_Body_Declaration |
                    A_Function_Body_Declaration |
                    A_Task_Body_Declaration |
                    A_Protected_Body_Declaration |
                    An_Entry_Declaration |
                    An_Entry_Body_Declaration |
                    A_Generic_Procedure_Declaration |
                    A_Generic_Function_Declaration |
                    An_Ordinary_Type_Declaration =>

                     Parent_Name := Names (Parent) (1);

                  when others =>
                     null;
               end case;
            when A_Statement =>
               case Statement_Kind (Parent) is
                  when A_Loop_Statement .. A_Block_Statement =>
                     Parent_Name := Statement_Identifier (Parent);
                  when An_Accept_Statement =>
                     Declaration := Corresponding_Name_Declaration (
                       Accept_Entry_Direct_Name (Parent));
                     Parent_Name := Names (Declaration) (1);
                  when others =>
                     null;
               end case;
            when others =>
               null;
         end case;
         if Is_Equal (Parent_Name, Name) then
            return True;
         else
            return Is_Enclosing_Named_Construct
              (Enclosing_Element (Parent), Name);
         end if;
      end Is_Enclosing_Named_Construct;

      procedure Set_Region
        (Result : in out Resolution;
         Parent : in     Asis.Expression)
      is
         Identifier : Asis.Expression;
      begin
         Result.Allowed   := False;

         case Expression_Kind (Parent) is
            when An_Identifier =>
               Identifier := Parent;
            when A_Selected_Component =>
               Identifier := Selector (Parent);
            when others =>
               return;
         end case;

         declare
            use Asis.Declarations;

            Target : constant Asis.Declaration :=
              Corresponding_Name_Declaration (Identifier);
         begin
            if Declaration_Kind (Target) in A_Renaming_Declaration then
               Set_Region (Result,
                           Corresponding_Base_Entity (Target));
               return;
            end if;
         end;

         declare
            Names : constant Asis.Defining_Name_List :=
              Corresponding_Name_Definition_List (Identifier);
            Found : Boolean := False;
         begin
            for I in Names'Range loop
               if XASIS.Utils.Is_Package_Name (Names (I)) or else
                 XASIS.Utils.Is_Enclosing_Named_Construct (Parent, Names (I))
               then
                  if not Found then
                     Found := True;
                     Result.Construct := Enclosing_Element (Names (I));
                     Result.In_Region := True;
                     Result.Allowed   := True;
                  else
                     Result.Allowed   := False;
                  --     Put_Line ("Ambigous prefix");
                  end if;
               end if;
            end loop;
         end;
      end Set_Region;

      Res  : Resolution;
      Expr : constant Expression_Kinds :=
        Asis.Elements.Expression_Kind (Element);
   begin

      pragma Assert (Expr = An_Identifier or
                     Expr = An_Operator_Symbol or
                     Expr = A_Character_Literal,
                     "Unexpected element in Try_To_Resolve");

      Check (Res);

      if not Res.Allowed then
         return;
      end if;

      if Res.In_Region then
         Element_Utils.Set_Resolved
           (Element, Lookup_In_Region (Element, Res.Construct));
      else
         Element_Utils.Set_Resolved
           (Element, Lookup (Element, Point));
      end if;
   end Try_To_Resolve;

   -------------------------
   -- Try_To_Resolve_Goto --
   -------------------------

   procedure Try_To_Resolve_Goto
     (Element : Asis.Expression;
      Stmt    : Asis.Statement)
   is
      Point : constant Visibility.Point := Utils.Goto_Enclosing_Region (Stmt);
   begin
      Try_To_Resolve (Element, Point);
   end Try_To_Resolve_Goto;

   ------------------
   -- Visible_From --
   ------------------

   function Visible_From
     (Name  : in Asis.Defining_Name;
      Point : in Asis.Identifier) return Boolean
     renames Utils.Visible_From;

   -----------------
   -- Unique_Name --
   -----------------

   function Unique_Name (Name  : in Asis.Defining_Name) return Wide_String is
      use Asis.Elements;

      function Get_Parent (Reg : Region_Access) return Region_Access is
      begin
         if Reg = Utils.Top_Region'Access then
            return null;
         else
            return Reg.Last_Part.Parent_Item.Part.Region;
         end if;
      end Get_Parent;

      function Count_Siblings (Reg : Region_Access) return Positive is
         Parent  : constant Region_Access := Get_Parent (Reg);
         Current : Region_Access := Parent.First_Child;
         Result  : Positive := 1;
      begin
         while Current /= Reg loop
            Result := Result + 1;
            Current := Current.Next;
         end loop;

         return Result;
      end Count_Siblings;

      function Region_Name (Reg : Region_Access) return Wide_String is
         use XASIS.Utils;

         Parent  : constant Region_Access := Get_Parent (Reg);
      begin
         if Parent = null or Parent = Utils.Top_Region'Access then
            return "";
         elsif Element_Kind (Reg.First_Part.Element) = A_Declaration then
            return Unique_Name (Declaration_Name (Reg.First_Part.Element))
              & ".";
         else
            declare
               Img : Wide_String := Positive'Wide_Image (Count_Siblings (Reg));
            begin
               Img (1) := '_';
               return Region_Name (Parent) & Img & '.';
            end;
         end if;
      end Region_Name;

      --  Go from completion to declaration
      function Declaration_Name return Asis.Defining_Name is
         use XASIS.Utils;

         Comp : Asis.Declaration := Enclosing_Element (Name);
         Decl : Asis.Declaration;
      begin
         if Is_Completion (Comp) then
            Decl := Declaration_For_Completion (Comp);
            return Get_Defining_Name (Decl, Direct_Name (Name));
         else
            return Name;
         end if;
      end Declaration_Name;

      Target   : constant Asis.Defining_Name := Declaration_Name;
      Item     : constant Region_Item_Access := Utils.Get_Place (Target);
      Point    : constant Visibility.Point := (Item => Item);
      Reg      : constant Region_Access := Item.Part.Region;
      Reg_Name : constant Wide_String := Region_Name (Reg);
      Result   : constant Asis.Defining_Name_List :=
        Lookup_In_Region (Target, Point);
   begin
      if Result'Length = 1 then
         return Reg_Name & XASIS.Utils.Direct_Name (Target);
      else
         declare
            Img : Wide_String := Positive'Wide_Image (Result'Length);
         begin
            Img (1) := '$';
            return Reg_Name & XASIS.Utils.Direct_Name (Target) & Img;
         end;
      end if;
   end Unique_Name;

end Asis.Gela.Visibility;



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
