with XASIS.Utils;
with Asis.Elements;
with Asis.Gela.Lists;
with Asis.Gela.Debug;
with Asis.Gela.Errors;
with Asis.Gela.Elements;
with Asis.Gela.Elements.Defs;
with Asis.Gela.Elements.Decl;
with Asis.Gela.Elements.Expr;
with Asis.Gela.Elements.Assoc;
with Ada.Characters.Handling;
with Asis.Gela.Elements.Stmt;
with Asis.Gela.Elements.Def_Names;
with Asis.Gela.Elements.Expr.Utils;
with Asis.Gela.Elements.Defs.Types;
with Asis.Gela.Elements.Defs.Formal;

package body Asis.Gela.Element_Utils is

   function Pragma_Kind (Name : Wide_String) return Pragma_Kinds;

   -------------------------
   -- Add_Name_Definition --
   -------------------------

   procedure Add_Defining_Name
     (Item : Asis.Element;
      Name : Asis.Element)
   is
      use Asis.Gela.Elements;
      use Asis.Gela.Elements.Expr;
   begin
      Add_To_Corresponding_Name_Definition_List
        (Base_Identifier_Node (Item.all), Name);
      Add_To_References
        (Defining_Name_Node'Class (Name.all), Item);
   end Add_Defining_Name;

   ------------------------------
   -- Add_Inherited_Subprogram --
   ------------------------------

   procedure Add_Inherited_Subprogram
     (Tipe : Asis.Definition;
      Proc : Asis.Declaration)
   is
      use Asis.Gela.Elements.Defs;
      use Asis.Gela.Elements.Defs.Types;
      use Asis.Gela.Elements.Defs.Formal;
   begin
      case Definition_Kind (Tipe.all) is
         when A_Type_Definition =>
            case Asis.Elements.Type_Kind (Tipe) is
               when A_Derived_Type_Definition |
                 A_Derived_Record_Extension_Definition
                 =>
                  Add_To_Implicit_Inherited_Subprograms
                    (Derived_Type_Node'Class (Tipe.all), Proc);
               when An_Interface_Type_Definition =>
                  Add_To_Implicit_Inherited_Subprograms
                    (Interface_Type_Node'Class (Tipe.all), Proc);
               when others =>
                  raise Internal_Error;
            end case;
         when A_Private_Extension_Definition =>
            Add_To_Implicit_Inherited_Subprograms
              (Private_Extension_Definition_Node'Class (Tipe.all), Proc);
         when A_Formal_Type_Definition =>
            case Asis.Elements.Formal_Type_Kind (Tipe) is
               when A_Formal_Derived_Type_Definition =>
                  Add_To_Implicit_Inherited_Subprograms
                    (Formal_Derived_Type_Node'Class (Tipe.all), Proc);
               when A_Formal_Interface_Type_Definition =>
                  Add_To_Implicit_Inherited_Subprograms
                    (Formal_Interface_Type_Node'Class (Tipe.all), Proc);
               when others =>
                  raise Internal_Error;
            end case;
         when others =>
            raise Internal_Error;
      end case;
   end Add_Inherited_Subprogram;

   ----------------
   -- Add_Pragma --
   ----------------

   procedure Add_Pragma
     (Item       : Asis.Element;
      The_Pragma : Asis.Pragma_Element)
   is
      use Asis.Gela.Elements;
   begin
      case Element_Kind (Item.all) is
         when A_Declaration =>
            Add_To_Corresponding_Pragmas
              (Declaration_Node (Item.all), The_Pragma);
         when A_Statement =>
            Add_To_Corresponding_Pragmas
              (Statement_Node (Item.all), The_Pragma);
         when others =>
            raise Internal_Error;
      end case;
   end Add_Pragma;

   --------------------
   -- Add_To_Visible --
   --------------------

   procedure Add_To_Visible
     (Declaration : Asis.Element;
      Item        : Asis.Element;
      Before      : Asis.Program_Text := "")
   is
      use Asis.Gela.Elements.Decl;
      use Lists.Primary_Declaration_Lists;

      Decl  : Package_Declaration_Node renames
        Package_Declaration_Node (Declaration.all);

      Items : constant List :=
        List (Visible_Part_Declarative_Items_List (Decl));
      Next  : Asis.Element;
      Prev  : Asis.Element;
   begin
      if Before = "" then
         Add (Items.all, Item);
      else
         for I in 1 .. Length (Items.all) loop
            Next := Get_Item (Items, I);

            if Element_Kind (Next.all) = A_Declaration
              and then XASIS.Utils.Has_Defining_Name (Next, Before)
            then
               Add_After (Items.all, Prev, Item);
               exit;
            end if;

            Prev := Next;
         end loop;
      end if;
   end Add_To_Visible;

   -----------------------
   -- Add_Type_Operator --
   -----------------------

   procedure Add_Type_Operator
     (Tipe : Asis.Definition;
      Oper : Asis.Declaration)
   is
      use Asis.Gela.Elements.Defs;
   begin
      case Definition_Kind (Tipe.all) is
         when A_Type_Definition =>
            Add_To_Corresponding_Type_Operators
              (Type_Definition_Node'Class (Tipe.all), Oper);
         when A_Formal_Type_Definition =>
            Add_To_Corresponding_Type_Operators
              (Formal_Type_Definition_Node'Class (Tipe.all), Oper);
         when A_Private_Type_Definition
           | A_Tagged_Private_Type_Definition
           | A_Private_Extension_Definition =>
            Add_To_Corresponding_Type_Operators
              (Private_Type_Definition_Node'Class (Tipe.all), Oper);
         when A_Task_Definition
           | A_Protected_Definition =>
            Add_To_Corresponding_Type_Operators
              (Protected_Definition_Node'Class (Tipe.all), Oper);
         when others =>
            raise Internal_Error;
      end case;
   end Add_Type_Operator;

   --------------------------------
   -- Base_Subprogram_Derivation --
   --------------------------------

   function Base_Subprogram_Derivation
     (Proc : Asis.Declaration) return Asis.Declaration
   is
      use Asis.Gela.Elements;

      Current : Asis.Declaration;
      Next    : Asis.Declaration := Proc;
      Name    : Asis.Defining_Name;
   begin
      while Assigned (Next) loop
         Current := Next;

         if Is_Part_Of_Inherited (Current.all) then
            Next := Corresponding_Subprogram_Derivation (Current.all);
         else
            Name := Names (Current.all) (1);
            Name := Override (Defining_Name_Node'Class (Name.all));

            if Assigned (Name) then
               Next := Enclosing_Element (Name.all);
            else
               Next := Asis.Nil_Element;
            end if;
         end if;
      end loop;

      return Current;
   end Base_Subprogram_Derivation;

   -------------------------
   -- Compound_Name_Image --
   -------------------------

   function Compound_Name_Image
     (Compount_Name : Asis.Element)
     return Wide_String
   is
      use Asis.Gela.Lists.Primary_Identifier_Lists;
      use type Unbounded_Wide_String;

      Identifiers : List;
      Image       : Unbounded_Wide_String;
      Next        : Asis.Element;
   begin
      if not Assigned (Compount_Name) then
         return "";
      elsif Element_Kind (Compount_Name.all) = A_Defining_Name then
         return Defining_Name_Image (Compount_Name.all);
      elsif Expression_Kind (Compount_Name.all) in
        An_Identifier .. An_Operator_Symbol
      then
         return Name_Image (Compount_Name.all);
      elsif Expression_Kind (Compount_Name.all) = A_Selected_Component then
         return Compound_Name_Image (Prefix (Compount_Name.all))
           & "." & Name_Image (Selector (Compount_Name.all).all);
      end if;

      Identifiers := List (Compount_Name);
      for I in 1 .. Length (Identifiers.all) loop
         if I /= 1 then
            Image := Image & ".";
         end if;
         Next  := Get_Item (Identifiers, I);
         Image := Image & Name_Image (Next.all);
      end loop;
      return Ada.Strings.Wide_Unbounded.To_Wide_String (Image);
   end Compound_Name_Image;

   ------------------
   -- Copy_Element --
   ------------------

   procedure Copy_Element
     (Source : Asis.Element;
      Target : Asis.Element)
   is
      use Asis.Gela.Elements;

      Dst : Base_Element_Node renames Base_Element_Node (Target.all);
   begin
      Set_Enclosing_Element    (Dst, Enclosing_Element (Source.all));
      Set_Is_Part_Of_Implicit  (Dst, Is_Part_Of_Implicit (Source.all));
      Set_Is_Part_Of_Inherited (Dst, Is_Part_Of_Inherited (Source.all));
      Set_Is_Part_Of_Instance  (Dst, Is_Part_Of_Instance (Source.all));
      Set_Start_Position       (Dst, Start_Position (Source.all));
      Set_End_Position         (Dst, End_Position (Source.all));

      Set_Enclosing_Compilation_Unit
        (Dst, Enclosing_Compilation_Unit (Source.all));
   end Copy_Element;

   --------------
   -- Override --
   --------------

   function Override (Defining_Name : Asis.Element) return Asis.Element is
      use Asis.Gela.Elements;
   begin
      if Element_Kind (Defining_Name.all) = A_Defining_Name then
         return Override (Defining_Name_Node (Defining_Name.all));
      else
         Raise_Inappropriate_Element;
         return Asis.Nil_Element;
      end if;
   end Override;

   -----------------
   -- Pragma_Kind --
   -----------------

   function Pragma_Kind (Name : Wide_String) return Pragma_Kinds is
      use Ada.Characters.Handling;

      Text1  : constant String := "A_"  & To_String (Name) & "_Pragma";
      Text2  : constant String := "An_" & To_String (Name) & "_Pragma";
      Upper1 : constant String := To_Upper (Text1);
      Upper2 : constant String := To_Upper (Text2);
   begin
      for I in An_All_Calls_Remote_Pragma .. A_Volatile_Components_Pragma loop
         declare
            Pragma_I : constant String := To_Upper (Pragma_Kinds'Image (I));
         begin
            if Pragma_I = Upper1 or Pragma_I = Upper2 then
               return I;
            end if;
         end;
      end loop;
      return An_Unknown_Pragma;
   end Pragma_Kind;

   --------------------------
   -- Remove_Defining_Name --
   --------------------------

   procedure Remove_Defining_Name
     (Item : Asis.Element;
      Name : Asis.Element)
   is
      use Asis.Gela.Elements;
      use Asis.Gela.Elements.Expr.Utils;
   begin
      Remove_From_Corresponding_Name_Definition_List
        (Elements.Expr.Base_Identifier_Node (Item.all), Name);
      Remove_From_References
        (Defining_Name_Node (Name.all), Item);
   end Remove_Defining_Name;

   -------------------------
   -- Set_Called_Function --
   -------------------------

   procedure Set_Called_Function
     (Call       : Asis.Element;
      Name       : Asis.Declaration;
      Dispatched : Boolean)
   is
      use Asis.Elements;

      function Is_Disp return Boolean is
      begin
         case Declaration_Kind (Name) is
            when
              A_Procedure_Declaration
              | A_Function_Declaration
              | A_Procedure_Renaming_Declaration
              | A_Function_Renaming_Declaration =>
               return Is_Dispatching_Operation (Name.all);
            when
              A_Procedure_Body_Declaration
              | A_Function_Body_Declaration
              | A_Procedure_Body_Stub
              | A_Function_Body_Stub =>
               return False;
               -- return Is_Dispatching_Operation
               --   (Corresponding_Declaration (Name.all).all);
               -- because Corresponding_Declaration (Name.all) may be null

            when
              A_Procedure_Instantiation
              | A_Function_Instantiation
              | A_Formal_Procedure_Declaration
              | A_Formal_Function_Declaration
              | An_Entry_Declaration
              | A_Generic_Procedure_Declaration
              | A_Generic_Function_Declaration =>
               return False;  --  TODO Check it

            when others =>
               return False;
         end case;
      end Is_Disp;

      function Check_Name return Boolean is
      begin
         case Declaration_Kind (Name) is
            when A_Procedure_Declaration |
              A_Function_Declaration |
              A_Procedure_Body_Declaration |
              A_Function_Body_Declaration |
              A_Procedure_Renaming_Declaration |
              A_Function_Renaming_Declaration |
              A_Procedure_Body_Stub |
              A_Function_Body_Stub |
              A_Procedure_Instantiation |
              A_Function_Instantiation |
              A_Formal_Function_Declaration |
              A_Formal_Procedure_Declaration |
              A_Generic_Procedure_Declaration |
              A_Generic_Function_Declaration |
              An_Entry_Declaration =>
               return True;
            when others =>
               return False;
         end case;
      end Check_Name;

   begin
      case Statement_Kind (Call.all) is
         when Not_A_Statement =>
            declare
               use Asis.Gela.Elements.Expr;
               Node : Function_Call_Node'Class renames
                 Function_Call_Node'Class (Call.all);
            begin
               Set_Is_Dispatching_Call (Node, Dispatched);

               if Check_Name then
                  Set_Corresponding_Called_Function (Node, Name);
                  Set_Is_Call_On_Dispatching_Operation (Node, Is_Disp);
               end if;
            end;
         when A_Procedure_Call_Statement =>
            declare
               use Asis.Gela.Elements.Stmt;
               Node : Procedure_Call_Statement_Node renames
                 Procedure_Call_Statement_Node (Call.all);
            begin
               Set_Is_Dispatching_Call (Node, Dispatched);

               if Check_Name then
                  Set_Corresponding_Called_Entity (Node, Name);

                  Set_Is_Call_On_Dispatching_Operation (Node, Is_Disp);
               end if;
            end;
         when An_Entry_Call_Statement =>
            declare
               use Asis.Gela.Elements.Stmt;
               Node : Base_Call_Statement_Node'Class renames
                 Base_Call_Statement_Node'Class (Call.all);
            begin
               if Check_Name then
                  Set_Corresponding_Called_Entity (Node, Name);
               end if;
            end;
         when An_Accept_Statement =>
            declare
               use Asis.Gela.Elements.Stmt;
               Node : Accept_Statement_Node renames
                 Accept_Statement_Node (Call.all);
            begin
               Set_Corresponding_Entry (Node, Name);
            end;
         when others =>
            raise Internal_Error;
      end case;
   end Set_Called_Function;

   --------------------
   -- Set_Completion --
   --------------------

   procedure Set_Completion
     (Declaration : Asis.Defining_Name;
      Completion  : Asis.Declaration)
   is
      use Asis.Gela.Elements;
      use Asis.Gela.Elements.Decl;

      Parent    : Asis.Declaration;
      Decl_Kind : Asis.Declaration_Kinds;

      Comp_Kind : constant Asis.Declaration_Kinds :=
        Asis.Elements.Declaration_Kind (Completion);

   begin

      if Asis.Elements.Is_Nil (Declaration) then
         if XASIS.Utils.Must_Be_Completion (Completion) then
            Errors.Report (Item => Completion,
                           What => Errors.Error_Must_Be_Completion);
         end if;
         return;
      end if;

      Parent    := Asis.Elements.Enclosing_Element (Declaration);
      Decl_Kind := Asis.Elements.Declaration_Kind (Parent);

      case Decl_Kind is
         when An_Incomplete_Type_Declaration =>
            Set_Corresponding_Type_Declaration
              (Incomplete_Type_Declaration_Node'Class (Parent.all),
               Completion);

            Set_Corresponding_Type_Declaration
              (Ordinary_Type_Declaration_Node'Class (Completion.all),
               Parent);

         when A_Protected_Type_Declaration =>
            Set_Corresponding_Body
              (Protected_Type_Declaration_Node'Class (Parent.all),
               Completion);

            if Comp_Kind = A_Protected_Body_Declaration then
               Set_Corresponding_Declaration
                 (Protected_Body_Declaration_Node'Class (Completion.all),
                  Parent);
            else
               Set_Corresponding_Declaration
                 (Protected_Body_Stub_Node'Class (Completion.all),
                  Parent);
            end if;

         when A_Single_Protected_Declaration =>
            Set_Corresponding_Body
              (Single_Protected_Declaration_Node'Class (Parent.all),
               Completion);

            if Comp_Kind = A_Protected_Body_Declaration then
               Set_Corresponding_Declaration
                 (Protected_Body_Declaration_Node'Class (Completion.all),
                  Parent);
            else
               Set_Corresponding_Declaration
                 (Protected_Body_Stub_Node'Class (Completion.all),
                  Parent);
            end if;

         when A_Task_Type_Declaration =>
            Set_Corresponding_Body
              (Task_Type_Declaration_Node'Class (Parent.all),
               Completion);

            if Comp_Kind = A_Task_Body_Declaration then
               Set_Corresponding_Declaration
                 (Base_Body_Declaration_Node'Class (Completion.all),
                  Parent);
            else
               Set_Corresponding_Declaration
                 (Task_Body_Stub_Node'Class (Completion.all),
                  Parent);
            end if;

         when A_Single_Task_Declaration =>
            Set_Corresponding_Body
              (Single_Task_Declaration_Node'Class (Parent.all),
               Completion);

            if Comp_Kind = A_Task_Body_Declaration then
               Set_Corresponding_Declaration
                 (Base_Body_Declaration_Node'Class (Completion.all),
                  Parent);
            else
               Set_Corresponding_Declaration
                 (Task_Body_Stub_Node'Class (Completion.all),
                  Parent);
            end if;

         when A_Package_Declaration =>
            if Comp_Kind = A_Package_Declaration then
               Set_Corresponding_Declaration
                 (Package_Declaration_Node'Class (Parent.all),
                  Completion);
           else
               Set_Corresponding_Body
                 (Package_Declaration_Node'Class (Parent.all),
                  Completion);
            end if;

            if Comp_Kind = A_Package_Body_Declaration then
               Set_Corresponding_Declaration
                 (Base_Body_Declaration_Node'Class (Completion.all),
                  Parent);
            elsif Comp_Kind = A_Package_Declaration then
               Set_Corresponding_Declaration
                 (Package_Declaration_Node'Class (Completion.all),
                  Parent);
            else
               Set_Corresponding_Declaration
                 (Package_Body_Stub_Node'Class (Completion.all),
                  Parent);
            end if;

         when A_Generic_Package_Declaration =>
            Set_Corresponding_Body
              (Generic_Package_Declaration_Node'Class (Parent.all),
               Completion);

            if Comp_Kind = A_Package_Body_Declaration then
               Set_Corresponding_Declaration
                 (Base_Body_Declaration_Node'Class (Completion.all),
                  Parent);
            else
               Set_Corresponding_Declaration
                 (Package_Body_Stub_Node'Class (Completion.all),
                  Parent);
            end if;

         when A_Procedure_Declaration |
              A_Function_Declaration  |
              An_Entry_Declaration    |
              A_Generic_Procedure_Declaration |
              A_Generic_Function_Declaration =>

            Set_Corresponding_Body
              (Base_Callable_Declaration_Node'Class (Parent.all),
               Completion);

            if Comp_Kind = A_Procedure_Renaming_Declaration or
              Comp_Kind = A_Function_Renaming_Declaration
            then
               Set_Corresponding_Declaration
                 (Procedure_Renaming_Declaration_Node'Class (Completion.all),
                  Parent);
            else
               Set_Corresponding_Declaration
                 (Base_Body_Declaration_Node'Class (Completion.all),
                  Parent);
            end if;

         when A_Procedure_Body_Stub |
              A_Function_Body_Stub =>

            Set_Corresponding_Subunit
              (Procedure_Body_Stub_Node'Class (Parent.all),
               Completion);

            Set_Corresponding_Body_Stub
              (Base_Body_Declaration_Node'Class (Completion.all),
               Parent);

         when A_Package_Body_Stub |
           A_Task_Body_Stub =>

            Set_Corresponding_Subunit
              (Package_Body_Stub_Node'Class (Parent.all),
               Completion);

            Set_Corresponding_Body_Stub
              (Base_Body_Declaration_Node'Class (Completion.all),
               Parent);

         when A_Protected_Body_Stub =>

            Set_Corresponding_Subunit
              (Package_Body_Stub_Node'Class (Parent.all),
               Completion);

            Set_Corresponding_Body_Stub
              (Protected_Body_Declaration_Node (Completion.all),
               Parent);

         when A_Private_Type_Declaration | A_Private_Extension_Declaration =>
            Set_Corresponding_Type_Declaration
              (Ordinary_Type_Declaration_Node'Class (Parent.all),
               Completion);

            Set_Corresponding_Type_Declaration
              (Ordinary_Type_Declaration_Node'Class (Completion.all),
               Parent);

         when A_Deferred_Constant_Declaration =>
            Set_Corresponding_Constant_Declaration
              (Defining_Name_Node'Class (Declaration.all),
               Completion);

            Set_Corresponding_Constant_Declaration
              (Defining_Name_Node'Class
                (XASIS.Utils.Get_Defining_Name
                  (Completion, XASIS.Utils.Direct_Name (Declaration)).all),
               Parent);

         when others =>
            null;

      end case;
   end Set_Completion;

   ----------------------
   -- Set_Derived_Type --
   ----------------------

   procedure Set_Derived_Type
     (Tipe   : Asis.Type_Definition;
      Parent : Asis.Declaration;
      Root   : Asis.Declaration;
      Struct : Asis.Declaration)
   is
      use Asis.Gela.Elements.Defs.Types;
      Node   : Derived_Type_Node'Class renames
        Derived_Type_Node'Class (Tipe.all);
   begin
      Set_Corresponding_Parent_Subtype (Node, Parent);
      Set_Corresponding_Root_Type (Node, Root);
      Set_Corresponding_Type_Structure (Node, Struct);
   end Set_Derived_Type;

   ------------------------------------
   -- Set_Enclosing_Compilation_Unit --
   ------------------------------------

   procedure Set_Enclosing_Compilation_Unit
     (Item   : Asis.Element;
      Unit   : Asis.Compilation_Unit)
   is
      use Asis.Gela.Elements;

      Element : Base_Element_Node renames
        Base_Element_Node (Item.all);
   begin
      Set_Enclosing_Compilation_Unit (Element, Unit);
   end Set_Enclosing_Compilation_Unit;

   ---------------------------
   -- Set_Enclosing_Element --
   ---------------------------

   procedure Set_Enclosing_Element
     (Item   : Asis.Element;
      Parent : Asis.Element)
   is
      use Asis.Gela.Elements;

      Element : Base_Element_Node renames
        Base_Element_Node (Item.all);
   begin
      Set_Enclosing_Element (Element, Parent);
   end Set_Enclosing_Element;

   ---------------------------------
   -- Set_Corresponding_Statement --
   ---------------------------------

   procedure Set_Corresponding_Statement
     (Stmt   : Asis.Statement;
      Target : Asis.Statement)
   is
      use Asis.Gela.Elements.Stmt;
   begin
      if Statement_Kind (Stmt.all) = An_Exit_Statement then
         Set_Corresponding_Loop_Exited
           (Exit_Statement_Node (Stmt.all), Target);
      else
         Set_Corresponding_Destination_Statement
           (Goto_Statement_Node (Stmt.all), Target);
      end if;
   end Set_Corresponding_Statement;

   --------------------------
   -- Set_Name_Declaration --
   --------------------------

   procedure Set_Name_Declaration
     (Item : Asis.Element;
      Name : Asis.Declaration)
   is
      use Asis.Gela.Elements.Expr;
   begin
      Set_Corresponding_Name_Declaration
        (Base_Identifier_Node (Item.all), Name);
   end Set_Name_Declaration;

   ---------------------------
   -- Set_Normalized_Params --
   ---------------------------

   procedure Set_Normalized_Params
     (Call    : Asis.Element;
      Param   : Asis.Association_List;
      Profile : Asis.Parameter_Specification_List)
   is
      use XASIS.Utils;
      use Asis.Elements;

      procedure Add (Name   : Asis.Defining_Name;
                     Expr   : Asis.Expression;
                     Is_Def : Boolean := False)
      is
         use Asis.Gela.Elements.Expr;
         use Asis.Gela.Elements.Stmt;
         use Asis.Gela.Elements.Assoc;

         Result : constant Parameter_Association_Ptr :=
           new Parameter_Association_Node;
      begin
         Set_Enclosing_Element    (Result.all, Call);
         Set_Is_Part_Of_Implicit  (Result.all, True);
         Set_Is_Part_Of_Inherited
           (Result.all, Is_Part_Of_Inherited (Call.all));
         Set_Is_Part_Of_Instance
           (Result.all, Is_Part_Of_Instance (Call.all));
         Set_Start_Position       (Result.all, (1, 1));
         Set_End_Position         (Result.all, (0, 0));

         Set_Enclosing_Compilation_Unit
           (Result.all, Enclosing_Compilation_Unit (Call.all));

         Set_Is_Normalized (Result.all, True);
         Set_Is_Defaulted_Association (Result.all, Is_Def);
         Set_Formal_Parameter (Result.all, Name);
         Set_Actual_Parameter (Result.all, Expr);

         if Expression_Kind (Call) = A_Function_Call then
            Add_To_Normalized_Function_Call_Parameters
              (Function_Call_Node (Call.all),
               Asis.Element (Result));
         else
            Add_To_Normalized_Call_Statement_Parameters
              (Base_Call_Statement_Node'Class (Call.all),
               Asis.Element (Result));
         end if;
      end Add;

      Index : Asis.List_Index := 1;
   begin
      for I in Profile'Range loop
         declare
            Found : Boolean := False;
            List  : constant Asis.Defining_Name_List :=
              Names (Profile (I).all);
         begin
            for J in List'Range loop
               if Index in Param'Range
                 and then Is_Nil (Formal_Parameter (Param (Index).all))
               then
                  Add (List (J), Actual_Parameter (Param (Index).all));
                  Index := Index + 1;
               else
                  Index := Param'Last + 1;

                  for K in Param'Range loop
                     if not Is_Nil (Formal_Parameter (Param (K).all))
                       and then Named_By (Formal_Parameter (Param (K).all),
                                          Direct_Name (List (J)))
                     then
                        Add (List (J), Actual_Parameter (Param (K).all));
                        Found := True;
                     end if;
                  end loop;

                  if not Found then
                     Add (Name => List (J),
                          Expr => Initialization_Expression (Profile (I).all),
                          Is_Def => True);
                  end if;
               end if;
            end loop;
         end;
      end loop;
   end Set_Normalized_Params;

   ------------------
   -- Set_Override --
   ------------------

   procedure Set_Override
     (Defining_Name : Asis.Element;
      Homograph     : Asis.Element)
   is
      use Asis.Gela.Elements;
   begin
      if Element_Kind (Defining_Name.all) = A_Defining_Name then
         Set_Override (Defining_Name_Node (Defining_Name.all), Homograph);
      else
         Raise_Inappropriate_Element;
      end if;
   end Set_Override;

   ---------------------
   -- Set_Pragma_Kind --
   ---------------------

   procedure Set_Pragma_Kind (Element : Asis.Pragma_Element) is
      use Asis.Gela.Elements;
      Item    : constant Pragma_Ptr := Pragma_Ptr (Element);
      Kind    : constant Asis.Pragma_Kinds :=
        Pragma_Kind (Pragma_Name_Image (Element.all));
   begin
      Set_Pragma_Kind (Item.all, Kind);
   end Set_Pragma_Kind;

   ------------------------------
   -- Set_Representation_Value --
   ------------------------------

   procedure Set_Representation_Value
     (Enum   : Asis.Declaration;
      Value  : Wide_String)
   is
      use Asis.Gela.Elements.Def_Names;
      Name : constant Asis.Defining_Name :=
        XASIS.Utils.Declaration_Name (Enum);
      Node : Defining_Enumeration_Literal_Node'Class renames
        Defining_Enumeration_Literal_Node'Class (Name.all);
   begin
      Set_Representation_Value_Image (Node, Value);
   end Set_Representation_Value;

   ------------------
   -- Set_Resolved --
   ------------------

   procedure Set_Resolved
     (Element : Asis.Element;
      List    : Asis.Defining_Name_List)
   is
      use Asis.Gela.Elements.Expr;

      Node : Base_Identifier_Node renames
        Base_Identifier_Node (Element.all);
      Old  : constant Asis.Element_List :=
        Corresponding_Name_Definition_List (Node);
   begin
      pragma Assert (Debug.Run (Element, Debug.Set_Resolved) or else
                     Debug.Dump (List));

--      Clear_Defining_Names (Element);
      for I in Old'Range loop
         Remove_Defining_Name (Element, Old (I));
      end loop;

      for I in List'Range loop
         Add_Defining_Name (Element, List (I));
      end loop;

      if List'Length = 1 then
         Set_Corresponding_Name_Declaration
           (Node, Enclosing_Element (List (1).all));

         if Expression_Kind (Element.all) = An_Operator_Symbol then
            Set_Operator_Kind
              (Operator_Symbol_Node (Element.all),
               Operator_Kind (List (1).all));
         end if;
      end if;
   end Set_Resolved;

   ------------------
   -- To_Unit_Name --
   ------------------

   function To_Unit_Name
     (Compount_Name : Asis.Element)
     return Asis.Element
   is
      use Asis.Gela.Elements.Expr;
      use Lists.Primary_Identifier_Lists;

      Identifiers : List;
      Unit_Name   : Asis.Element;
      Current     : Asis.Element;
   begin
--      if Compount_Name.all not in List_Node then
      if not Is_List (Compount_Name.all) then
         return Compount_Name;
      end if;

      Identifiers := List (Compount_Name);
      Current     := Get_Item (Identifiers, 1);

      for I in 2 .. Length (Identifiers.all) loop
         declare
            Comp : constant Selected_Component_Ptr :=
              new Selected_Component_Node;
            Next : constant Asis.Element := Get_Item (Identifiers, I);
         begin
            Set_Prefix (Comp.all, Current);
            Set_Start_Position (Comp.all, Start_Position (Current.all));
            Set_Selector (Comp.all, Next);
            Set_End_Position (Comp.all, End_Position (Next.all));
            Current := Asis.Element (Comp);
         end;
      end loop;

      Unit_Name := Current;

      while Length (Identifiers.all) > 0 loop
         Current := Get_Item (Identifiers, 1);
         Remove (Identifiers.all, Current);
      end loop;

      return Unit_Name;

   end To_Unit_Name;

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
