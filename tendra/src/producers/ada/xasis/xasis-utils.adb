with Ada.Characters.Handling;

with Asis.Text;
with Asis.Elements;
with Asis.Iterator;
with Asis.Statements;
with Asis.Definitions;
with Asis.Expressions;
with Asis.Declarations;
with Asis.Compilation_Units;

with Ada.Wide_Text_IO;
with Ada.Strings.Wide_Fixed;
with Ada.Strings.Wide_Unbounded;
with XASIS.Types;

package body XASIS.Utils is

   use Asis;

   function Get_Parameter_Profile
     (Def : Asis.Defining_Name)
      return Asis.Parameter_Specification_List;

   ---------------------------
   -- Are_Equal_Identifiers --
   ---------------------------

   function Are_Equal_Identifiers
     (Left, Right : Asis.Program_Text) return Boolean
   is
      use Ada.Characters.Handling;
      L : constant String := To_Lower (To_String (Left));
      R : constant String := To_Lower (To_String (Right));
   begin
      if Left (Left'First) = ''' then
         return Left = Right;
      else
         if R = "false" then
            return L = R;
         end if;
         return To_Lower (To_String (Left)) = To_Lower (To_String (Right));
      end if;
   end Are_Equal_Identifiers;

   -----------------------
   -- Can_Be_Completion --
   -----------------------

   function Can_Be_Completion (Declaration : Asis.Declaration) return Boolean
   is
      use Asis;
      Kind : constant Asis.Declaration_Kinds :=
        Asis.Elements.Declaration_Kind (Declaration);
   begin
      case Kind is
         when An_Ordinary_Type_Declaration =>
            return True;
         when A_Protected_Body_Declaration =>
            return True;
         when A_Task_Body_Declaration =>
            return True;
         when A_Package_Body_Declaration =>
            return True;
         when A_Procedure_Body_Declaration =>
            return True;
         when A_Function_Body_Declaration =>
            return True;
         when A_Procedure_Renaming_Declaration =>
            return True;
         when A_Function_Renaming_Declaration =>
            return True;
         when A_Constant_Declaration =>
            return True;
         when An_Entry_Body_Declaration =>
            return True;
         when A_Procedure_Body_Stub =>
            return True;
         when A_Function_Body_Stub =>
            return True;
         when A_Package_Body_Stub =>
            return True;
         when A_Task_Body_Stub =>
            return True;
         when A_Protected_Body_Stub =>
            return True;
         when A_Package_Declaration =>
            --  Can be completion for implicit limited view
            return not Asis.Elements.Is_Part_Of_Implicit (Declaration);
         when others =>
            return False;
      end case;
   end Can_Be_Completion;

   -------------------------
   -- Check_Callable_Name --
   -------------------------

   function Check_Callable_Name (Name : Asis.Declaration) return Boolean is
      use Asis.Elements;
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
           A_Formal_Procedure_Declaration =>
            return True;
         when An_Entry_Declaration =>
            return not Is_Entry_Family (Name);
         when others =>
            return False;
      end case;
   end Check_Callable_Name;

   --------------------------------
   -- Completion_For_Declaration --
   --------------------------------

   function Completion_For_Declaration
     (Declaration : Asis.Declaration) return Asis.Declaration
   is
      use Asis.Elements;
      use Asis.Declarations;
   begin
      case Declaration_Kind (Declaration) is
         when An_Incomplete_Type_Declaration |
              A_Private_Type_Declaration     |
              A_Private_Extension_Declaration =>
            return Corresponding_Type_Declaration (Declaration);

         when A_Generic_Package_Declaration   |
              A_Generic_Procedure_Declaration |
              A_Generic_Function_Declaration  |
              An_Entry_Declaration            |
              A_Protected_Type_Declaration    |
              A_Single_Protected_Declaration  |
              A_Task_Type_Declaration         |
              A_Single_Task_Declaration       |
              A_Procedure_Declaration         |
              A_Function_Declaration  =>
            return Corresponding_Body (Declaration);

         when A_Package_Declaration =>
            if Is_Part_Of_Implicit (Declaration) then
               return Corresponding_Declaration (Declaration);
            else
               return Corresponding_Body (Declaration);
            end if;

         when others =>
            return Nil_Element;
      end case;
   end Completion_For_Declaration;

   -------------------------
   -- Completion_For_Name --
   -------------------------

   function Completion_For_Name
     (Name : Asis.Defining_Name) return Asis.Declaration
   is
      use Asis.Elements;
      use Asis.Declarations;

      Parent : constant Asis.Element := Enclosing_Element (Name);
   begin
      if Declaration_Kind (Parent) = A_Deferred_Constant_Declaration then
         return Corresponding_Constant_Declaration (Name);
      else
         return Completion_For_Declaration (Parent);
      end if;
   end Completion_For_Name;

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image (Element : in Asis.Element) return Asis.Program_Text is
      use Asis;
      use Asis.Elements;
      use Asis.Expressions;
      use Asis.Declarations;

      function Image return Wide_String is
      begin
         case Element_Kind (Element) is
            when A_Defining_Name =>
               return Defining_Name_Image (Element);
            when An_Expression =>
               case Expression_Kind (Element) is
                  when An_Integer_Literal
                    | A_Real_Literal
                    | A_String_Literal =>
                     return Value_Image (Element);
                  when An_Identifier
                    | An_Operator_Symbol
                    | A_Character_Literal
                    | An_Enumeration_Literal =>
                     return Name_Image (Element);
                  when others =>
                     return "";
               end case;
            when A_Declaration =>
               declare
                  List : constant Asis.Element_List := Names (Element);
               begin
                  if List'Length > 0 then
                     return Defining_Name_Image (List (List'First));
                  else
                     return "";
                  end if;
               end;
            when others =>
               return "";
         end case;
      end Image;

      function Kind_Image return Wide_String is
      begin
         case Elements.Element_Kind (Element) is
            when A_Pragma =>
               return "Pragma_Kind:"
                  & Pragma_Kinds'Wide_Image (Elements.Pragma_Kind (Element));

            when A_Defining_Name =>
               return "Defining_Name_Kind:"
                 & Defining_Name_Kinds'Wide_Image
                 (Elements.Defining_Name_Kind (Element));

            when A_Declaration =>
               return "Declaration_Kind:"
                 & Declaration_Kinds'Wide_Image
                 (Elements.Declaration_Kind (Element));

            when A_Definition =>
               case Elements.Definition_Kind (Element) is
                  when A_Type_Definition =>
                     return "Type_Kind:"
                       & Type_Kinds'Wide_Image
                       (Elements.Type_Kind (Element));

                  when A_Constraint =>
                     return "Constraint_Kind:"
                        & Constraint_Kinds'Wide_Image
                        (Elements.Constraint_Kind (Element));

                  when A_Discrete_Subtype_Definition =>
                     return "S-Discrete_Range_Kind:"
                        & Discrete_Range_Kinds'Wide_Image
                        (Elements.Discrete_Range_Kind (Element));

                  when A_Discrete_Range =>
                     return "Discrete_Range_Kind:"
                        & Discrete_Range_Kinds'Wide_Image
                        (Elements.Discrete_Range_Kind (Element));

                  when A_Formal_Type_Definition =>
                     return "Formal_Type_Kind:"
                        & Formal_Type_Kinds'Wide_Image
                        (Elements.Formal_Type_Kind (Element));

                  when An_Access_Definition =>
                     return "Access_Definition_Kind:"
                        & Access_Definition_Kinds'Wide_Image
                        (Elements.Access_Definition_Kind (Element));

                  when others =>
                     return "Definition_Kind:"
                        & Definition_Kinds'Wide_Image
                        (Elements.Definition_Kind (Element));
               end case;

            when An_Expression =>
               return "Expression_Kind:"
                  & Expression_Kinds'Wide_Image
                  (Elements.Expression_Kind (Element));

            when An_Association =>
               return "Association_Kind:"
                  & Association_Kinds'Wide_Image
                  (Elements.Association_Kind (Element));

            when A_Statement =>
               return "Statement_Kind:"
                  & Statement_Kinds'Wide_Image
                  (Elements.Statement_Kind (Element));

            when A_Path =>
               return "Path_Kind:"
                  & Path_Kinds'Wide_Image
                  (Elements.Path_Kind (Element));

            when A_Clause =>
               case Elements.Clause_Kind (Element) is
                  when A_Representation_Clause =>
                     return "Representation_Clause_Kind:"
                       & Representation_Clause_Kinds'Wide_Image
                       (Elements.Representation_Clause_Kind (Element));

                  when others =>
                     return "Clause_Kind:"
                       & Clause_Kinds'Wide_Image
                       (Elements.Clause_Kind (Element));
               end case;

            when others =>
               return "Element_Kind:"
                 & Element_Kinds'Wide_Image (Elements.Element_Kind (Element));
         end case;
      end Kind_Image;

      function Span_Image return Wide_String is
         use Asis.Text;
         function Img (X : Asis.ASIS_Natural) return Wide_String is
            Image   : constant Wide_String :=
              Asis.ASIS_Natural'Wide_Image (X);
         begin
            return Image (2 .. Image'Last);
         end Img;

         X : constant Span := Element_Span (Element);

      begin
         return " [" & Img (X.First_Line)
           & ":" & Img (X.First_Column)
           & ".." & Img (X.Last_Line)
           & ":" & Img (X.Last_Column)
           & "]";
      end Span_Image;

      function File_Name return Wide_String is
         use Ada.Strings;
         Name  : constant Wide_String :=
           Compilation_Units.Text_Name (Enclosing_Compilation_Unit (Element));
         Slash : Natural := Wide_Fixed.Index (Name, "/", Backward);
      begin
         if Slash = 0 then
            return Name;
         else
            return Name (Slash + 1 .. Name'Last);
         end if;
      end  File_Name;

      function Explicit_Parent return Asis.Element is
         Result : Asis.Element := Enclosing_Element (Element);
      begin
         while Is_Part_Of_Implicit (Result)
           or Is_Part_Of_Inherited (Result)
           or Is_Part_Of_Instance (Result)
         loop
            Result := Enclosing_Element (Result);
         end loop;

         return Result;
      end Explicit_Parent;

      function Generic_Element_Image return Wide_String is
      begin
         if Element_Kind (Element) = A_Defining_Name then
            return "of "
              & Debug_Image (Corresponding_Generic_Element (Element));
         else
            return "";
         end if;
      end Generic_Element_Image;

   begin
      if not Is_Nil (Element) then
         if Is_Part_Of_Instance (Element) then
            return Kind_Image
              & " "
              & Image
              & " instance "
              & Generic_Element_Image
              & " in "
              & Debug_Image (Explicit_Parent);
         elsif Is_Part_Of_Inherited (Element) then
            return Kind_Image
              & " "
              & Image
              & " inherited in "
              & Debug_Image (Explicit_Parent);
         elsif Is_Part_Of_Implicit (Element) then
            return Kind_Image
              & " "
              & Image
              & " implicit of "
              & Debug_Image (Explicit_Parent);
         else
            return Kind_Image
              & " "
              & Image
              & " at "
              & File_Name
              & Span_Image;
         end if;
      else
         return "[Not_An_Element]";
      end if;
   end Debug_Image;

   -----------------------------
   -- Declaration_Direct_Name --
   -----------------------------

   function Declaration_Direct_Name
     (Item : Asis.Declaration) return Asis.Program_Text
   is
      Name : constant Asis.Defining_Name := Declaration_Name (Item);
   begin
      if Asis.Elements.Is_Nil (Name) then
         return "";
      else
         return Direct_Name (Name);
      end if;
   end Declaration_Direct_Name;

   ----------------------
   -- Declaration_Name --
   ----------------------

   function Declaration_Name
     (Item : Asis.Declaration) return Asis.Defining_Name
   is
      Names : constant Asis.Defining_Name_List :=
        Asis.Declarations.Names (Item);
   begin
      if Names'Length = 1 then
         return Names (1);
      else
         return Asis.Nil_Element;
      end if;
   end Declaration_Name;

   --------------------------------
   -- Declaration_For_Completion --
   --------------------------------

   function Declaration_For_Completion
     (Declaration : Asis.Declaration) return Asis.Declaration
   is
      use Asis;
      use Asis.Elements;
      use Asis.Declarations;

      Kind : constant Asis.Declaration_Kinds := Declaration_Kind (Declaration);
   begin
      case Kind is
         when An_Ordinary_Type_Declaration =>
            return Corresponding_Type_Declaration (Declaration);
         when A_Protected_Body_Declaration =>
            return Corresponding_Declaration (Declaration);
         when A_Task_Body_Declaration =>
            return Corresponding_Declaration (Declaration);
         when A_Package_Body_Declaration =>
            return Corresponding_Declaration (Declaration);
         when A_Procedure_Body_Declaration =>
            return Corresponding_Declaration (Declaration);
         when A_Function_Body_Declaration =>
            return Corresponding_Declaration (Declaration);
         when A_Procedure_Renaming_Declaration =>
            return Corresponding_Declaration (Declaration);
         when A_Function_Renaming_Declaration =>
            return Corresponding_Declaration (Declaration);
         when A_Procedure_Body_Stub =>
            return Corresponding_Declaration (Declaration);
         when A_Function_Body_Stub =>
            return Corresponding_Declaration (Declaration);
         when A_Package_Body_Stub =>
            return Corresponding_Declaration (Declaration);
         when A_Task_Body_Stub =>
            return Corresponding_Declaration (Declaration);
         when A_Protected_Body_Stub =>
            return Corresponding_Declaration (Declaration);
         when A_Constant_Declaration =>
            declare
               Names : constant Asis.Defining_Name_List :=
                 Asis.Declarations.Names (Declaration);
               Result : Asis.Element;
            begin
               for I in Names'Range loop
                  Result := Corresponding_Constant_Declaration (Names (I));
                  if not Is_Nil (Result) then
                     return Result;
                  end if;
               end loop;
            end;
            return Nil_Element;
         when A_Package_Declaration =>
            if Is_Part_Of_Implicit (Declaration) then
               return Nil_Element;
            else
               return Corresponding_Declaration (Declaration);
            end if;
         when An_Entry_Body_Declaration =>
            return Corresponding_Declaration (Declaration);
         when others =>
            return Nil_Element;
      end case;
   end Declaration_For_Completion;

   -----------------
   -- Direct_Name --
   -----------------

   function Direct_Name (Name : Asis.Defining_Name) return Asis.Program_Text
   is
      use Asis.Elements;
      use Asis.Declarations;
      Def : Asis.Definition := Name;
   begin
      pragma Assert (Element_Kind (Name) = A_Defining_Name,
                     "Unexpected element in Direct_Name");

      if Defining_Name_Kind (Def) = A_Defining_Expanded_Name then
         Def := Defining_Selector (Def);
      end if;

      return Defining_Name_Image (Def);

   end Direct_Name;

   ---------------
   -- Dump_Tree --
   ---------------

   procedure Dump_Tree
     (Unit      : Asis.Compilation_Unit;
      File_Name : String)
   is
      use Ada.Wide_Text_IO;

      procedure Pre_Op
        (Element : in     Asis.Element;
         Control : in out Asis.Traverse_Control;
         State   : in out File_Type);

      procedure Post_Op
        (Element : in     Asis.Element;
         Control : in out Asis.Traverse_Control;
         State   : in out File_Type);

      procedure Dump_Element is
         new Asis.Iterator.Traverse_Element
           (State_Information => File_Type,
            Pre_Operation     => Pre_Op,
            Post_Operation    => Post_Op);

      procedure Pre_Op
        (Element : in     Asis.Element;
         Control : in out Asis.Traverse_Control;
         State   : in out File_Type) is
      begin
         Put_Line (State, "<n i='" &
                   Asis.Elements.Debug_Image (Element) & "'>");
      end Pre_Op;

      procedure Post_Op
        (Element : in     Asis.Element;
         Control : in out Asis.Traverse_Control;
         State   : in out File_Type) is
      begin
         Put_Line (State, "</n>");
      end Post_Op;

      File    : File_Type;
      Control : Asis.Traverse_Control := Continue;
      Decl    : constant Asis.Element :=
        Asis.Elements.Unit_Declaration (Unit);
      Clauses : constant Asis.Element_List :=
        Asis.Elements.Context_Clause_Elements (Unit);
   begin
      Create (File, Name => File_Name);
      Put_Line (File, "<u>");
      for I in Clauses'Range loop
         Dump_Element (Clauses (I), Control, File);
      end loop;
      Dump_Element (Decl, Control, File);
      Put_Line (File, "</u>");
      Close (File);
   end Dump_Tree;

   --------------------
   -- External_Image --
   --------------------

   function External_Image
     (Decl : Asis.Declaration)
     return Asis.Program_Text
   is
      List : constant Asis.Defining_Name_List :=
        Asis.Declarations.Names (Decl);
   begin
      if List'Length > 0 then
         return External_Name_Image (List (1));
      else
         declare
            Def  : constant Asis.Definition :=
              Asis.Declarations.Type_Declaration_View (Decl);
            Kind : constant Asis.Root_Type_Kinds :=
              Asis.Elements.Root_Type_Kind (Def);
         begin
            return Asis.Root_Type_Kinds'Wide_Image (Kind);
         end;
      end if;
   end External_Image;

   -------------------------
   -- External_Name_Image --
   -------------------------

   function External_Name_Image
     (Name : Asis.Defining_Name) return Asis.Program_Text
     renames Direct_Name;

   -------------------
   -- Get_Ancestors --
   -------------------

   function Get_Ancestors (Decl  : Asis.Declaration) return Asis.Name_List is
   begin
      case Asis.Elements.Declaration_Kind (Decl) is
         when An_Ordinary_Type_Declaration =>
            declare
               Def  : constant Asis.Definition :=
                 Asis.Declarations.Type_Declaration_View (Decl);
            begin
               case Asis.Elements.Type_Kind (Def) is
                  when A_Derived_Type_Definition =>
                     declare
                        use Asis.Definitions;
                        Ind  : constant Asis.Subtype_Indication :=
                          Parent_Subtype_Indication (Def);
                        Mark : constant  Asis.Expression :=
                          Asis.Definitions.Subtype_Mark (Ind);
                     begin
                        return (1 => Mark);
                     end;

                  when A_Derived_Record_Extension_Definition =>
                     declare
                        use Asis.Definitions;
                        Ind  : constant Asis.Subtype_Indication :=
                          Parent_Subtype_Indication (Def);
                        Mark : constant  Asis.Expression :=
                          Asis.Definitions.Subtype_Mark (Ind);
                     begin
                        return Mark & Progenitor_List (Def);
                     end;
                  when An_Interface_Type_Definition =>
                     return Asis.Definitions.Progenitor_List (Def);
                  when others =>
                     null;
               end case;
            end;
         when A_Task_Type_Declaration | A_Protected_Type_Declaration =>
            return Asis.Declarations.Progenitor_List (Decl);
         when A_Private_Extension_Declaration =>
            declare
               Def  : constant Asis.Definition :=
                 Asis.Declarations.Type_Declaration_View (Decl);
               Ind  : constant Asis.Subtype_Indication :=
                 Asis.Definitions.Ancestor_Subtype_Indication (Def);
               Mark : constant  Asis.Expression :=
                 Asis.Definitions.Subtype_Mark (Ind);
            begin
               return Mark & Asis.Declarations.Progenitor_List (Decl);
            end;
         when A_Formal_Type_Declaration =>
            declare
               Def  : constant Asis.Definition :=
                 Asis.Declarations.Type_Declaration_View (Decl);
            begin
               case Asis.Elements.Formal_Type_Kind (Def) is
                  when A_Formal_Derived_Type_Definition =>
                     declare
                        use Asis.Definitions;
                        Mark : constant  Asis.Expression :=
                          Asis.Definitions.Subtype_Mark (Def);
                     begin
                        return Mark & Progenitor_List (Def);
                     end;
                  when A_Formal_Interface_Type_Definition =>
                     return Asis.Definitions.Progenitor_List (Def);
                  when others =>
                     null;
               end case;
            end;
         when others =>
            null;
      end case;

      return Asis.Nil_Element_List;
   end Get_Ancestors;

   ---------------------------
   -- Get_Attribute_Profile --
   ---------------------------

   function Get_Attribute_Profile
     (Tipe : Asis.Declaration;
      Kind : Asis.Attribute_Kinds) return Asis.Element_List is
   begin
      case Kind is
         when A_Mod_Attribute
           | A_Val_Attribute =>
            return (1 => XASIS.Types.Universal_Integer);
         when A_Value_Attribute =>
            return (1 => XASIS.Types.String);
         when An_Adjacent_Attribute
           | A_Copy_Sign_Attribute
           | A_Max_Attribute
           | A_Min_Attribute
           | A_Remainder_Attribute
           =>
            return (1 | 2 => Tipe);
         when A_Ceiling_Attribute
           | An_Exponent_Attribute
           | A_Floor_Attribute
           | A_Fraction_Attribute
           | An_Image_Attribute
           | A_Machine_Attribute
           | A_Machine_Rounding_Attribute
           | A_Model_Attribute
           | A_Pos_Attribute
           | A_Pred_Attribute
           | A_Rounding_Attribute
           | A_Succ_Attribute
           | A_Truncation_Attribute
           | An_Unbiased_Rounding_Attribute
           | A_Wide_Image_Attribute
           | A_Wide_Wide_Image_Attribute
           =>
            return (1 => Tipe);
         when A_Compose_Attribute
           | A_Leading_Part_Attribute
           | A_Scaling_Attribute
           =>
            return (1 => Tipe, 2 => XASIS.Types.Universal_Integer);
         when A_Round_Attribute =>
            return (1 => XASIS.Types.Universal_Real);
         when A_Wide_Value_Attribute =>
            return (1 => XASIS.Types.Wide_String);
         when A_Wide_Wide_Value_Attribute =>
            return (1 => XASIS.Types.Wide_Wide_String);
         when An_Input_Attribute =>
            return (1 => XASIS.Types.Root_Stream_Type);
         when A_Read_Attribute
           | A_Write_Attribute
           | An_Output_Attribute =>
            return (1 => XASIS.Types.Root_Stream_Type,
                    2 => Tipe);
         when others =>
            raise XASIS_Error;
      end case;
   end Get_Attribute_Profile;

   -----------------------
   -- Get_Defining_Name --
   -----------------------

   function Get_Defining_Name
     (Declaration : Asis.Declaration;
      Direct_Name : Asis.Program_Text) return Asis.Defining_Name
   is
      Names : constant Asis.Defining_Name_List :=
        Asis.Declarations.Names (Declaration);
   begin
      for I in Names'Range loop
         if Has_Name (Names(I), Direct_Name) then
            return Names (I);
         end if;
      end loop;
      return Asis.Nil_Element;
   end Get_Defining_Name;

   ---------------------------
   -- Get_Parameter_Profile --
   ---------------------------

   function Get_Parameter_Profile
     (Def : Asis.Defining_Name)
      return Asis.Parameter_Specification_List
   is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;

      Decl : constant Asis.Declaration := Enclosing_Element (Def);
      Kind : constant Asis.Declaration_Kinds := Declaration_Kind (Decl);
      Tipe : Asis.Definition;
   begin
      case Kind is
         when A_Function_Declaration |
           A_Procedure_Declaration |
           A_Function_Body_Declaration |
           A_Procedure_Body_Declaration |
           A_Function_Body_Stub |
           A_Procedure_Body_Stub |
           A_Function_Renaming_Declaration |
           A_Procedure_Renaming_Declaration |
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

         when others =>
            return Nil_Element_List;
      end case;
   end Get_Parameter_Profile;

   -----------------
   -- Get_Profile --
   -----------------

   function Get_Profile (Name : Asis.Declaration)
     return Asis.Parameter_Specification_List
   is
      use Asis.Elements;
      use Asis.Declarations;
      Decl : Asis.Declaration;
   begin
      case Declaration_Kind (Name) is
         when A_Procedure_Declaration |
              A_Function_Declaration |
              A_Procedure_Body_Declaration |
              A_Function_Body_Declaration |
              A_Procedure_Renaming_Declaration |
              A_Function_Renaming_Declaration |
              An_Entry_Declaration |
              A_Procedure_Body_Stub |
              A_Function_Body_Stub |
              A_Formal_Function_Declaration |
              A_Formal_Procedure_Declaration =>

               return Parameter_Profile (Name);

         when A_Procedure_Instantiation |
              A_Function_Instantiation =>

            Decl := Corresponding_Declaration (Name);
            return Parameter_Profile (Decl);

         when others =>
            return Nil_Element_List;
      end case;
   end Get_Profile;

   ------------------------
   -- Get_Result_Profile --
   ------------------------

   function Get_Result_Profile (Name : Asis.Declaration)
     return Asis.Expression
   is
      use Asis.Elements;
      use Asis.Declarations;
      Decl   : Asis.Declaration;
   begin
      case Declaration_Kind (Name) is
         when A_Function_Declaration |
              A_Function_Body_Declaration |
              A_Function_Renaming_Declaration |
              A_Function_Body_Stub |
              A_Formal_Function_Declaration =>

            return Result_Profile (Name);

         when A_Function_Instantiation =>

            Decl := Corresponding_Declaration (Name);
            return Result_Profile (Decl);

         when others =>
            return Nil_Element;
      end case;
   end Get_Result_Profile;

   ------------------------
   -- Get_Result_Subtype --
   ------------------------

   function Get_Result_Subtype
     (Name : Asis.Declaration) return Asis.Definition
   is
      use Asis.Elements;
      use Asis.Declarations;
      Decl   : Asis.Declaration;
   begin
      case Declaration_Kind (Name) is
         when A_Function_Declaration |
              A_Function_Body_Declaration |
              A_Function_Renaming_Declaration |
              A_Function_Body_Stub |
              A_Formal_Function_Declaration =>

            return Result_Subtype (Name);

         when A_Function_Instantiation =>

            Decl := Corresponding_Declaration (Name);
            return Result_Subtype (Decl);

         when others =>
            return Nil_Element;
      end case;
   end Get_Result_Subtype;

   -----------------------
   -- Has_Defining_Name --
   -----------------------

   function Has_Defining_Name
     (Declaration : Asis.Declaration;
      Direct_Name : Asis.Program_Text) return Boolean
   is
      use Asis.Elements;
   begin
      return not Is_Nil (Get_Defining_Name (Declaration, Direct_Name));
   end Has_Defining_Name;

   --------------
   -- Has_Name --
   --------------

   function Has_Name
     (Element     : Asis.Defining_Name;
      Direct_Name : Asis.Program_Text) return Boolean
   is
      use Asis.Declarations;
   begin
      pragma Assert (Elements.Element_Kind (Element) = A_Defining_Name,
                     "Unexpected element in Has_Name");

      return Are_Equal_Identifiers (XASIS.Utils.Direct_Name (Element),
                                    Direct_Name);
   end Has_Name;

   -----------------------------
   -- Has_Representation_Item --
   -----------------------------

   function Has_Representation_Item (Tipe : Asis.Declaration) return Boolean is
      use Asis.Elements;
      use Asis.Declarations;

      function Is_Representation_Pragma
        (Element : Asis.Pragma_Element) return Boolean is
      begin
         case Pragma_Kind (Element) is
            when An_Asynchronous_Pragma
              | An_Atomic_Pragma
              | An_Atomic_Components_Pragma
              | A_Controlled_Pragma
              | A_Convention_Pragma
              | A_Discard_Names_Pragma
              | An_Export_Pragma
              | An_Import_Pragma
              | A_Pack_Pragma
              | A_Volatile_Pragma
              | A_Volatile_Components_Pragma =>

               return True;

            when others =>
               return False;
         end case;
      end Is_Representation_Pragma;

      RC : constant Asis.Representation_Clause_List :=
        Corresponding_Representation_Clauses (Tipe);
      RP : constant Asis.Pragma_Element_List :=
        Corresponding_Pragmas (Tipe);
   begin
      for I in RP'Range loop
         if Is_Representation_Pragma (RP (I)) then
            return True;
         end if;
      end loop;

      return RC'Length > 0;
   end Has_Representation_Item;

   -----------------
   -- Is_Child_Of --
   -----------------

   function Is_Child_Of (Child, Parent : Asis.Element) return Boolean is
      use Asis.Elements;
      Next : Asis.Element := Child;
   begin
      while not Is_Nil (Next) loop
         if Is_Equal (Next, Parent) then
            return True;
         end if;

         Next := Enclosing_Element (Next);
      end loop;

      return False;
   end Is_Child_Of;

   -------------------
   -- Is_Completion --
   -------------------

   function Is_Completion
     (Declaration : Asis.Declaration) return Boolean
   is
      use Asis.Elements;
   begin
      return not Is_Nil (Declaration_For_Completion (Declaration));
   end Is_Completion;

   ----------------------
   -- Is_Empty_Profile --
   ----------------------

   function Is_Empty_Profile
     (List : Asis.Parameter_Specification_List) return Boolean
   is
      use Asis.Declarations;
   begin
      for I in List'Range loop
         if Asis.Elements.Is_Nil (Initialization_Expression (List (I))) then
            return False;
         end if;
      end loop;
      return True;
   end Is_Empty_Profile;

   ---------------------
   -- Is_Entry_Family --
   ---------------------

   function Is_Entry_Family (Decl : Asis.Declaration) return Boolean is
      use Asis.Elements;
      use Asis.Declarations;
   begin
      return Declaration_Kind (Decl) = An_Entry_Declaration
        and then not Is_Nil (Entry_Family_Definition (Decl));
   end Is_Entry_Family;

   ----------------------
   -- Is_Expanded_Name --
   ----------------------

   function Is_Expanded_Name (Expr : Asis.Expression) return Boolean is
      use Asis.Elements;
      use Asis.Expressions;

      Id : constant Asis.Expression :=
        Selected_Name_Selector (Prefix (Expr), False);
   begin
      case Expression_Kind (Id) is
         when An_Identifier
           | An_Operator_Symbol
           | A_Character_Literal
           | An_Enumeration_Literal =>
            declare
               Name : constant Asis.Defining_Name :=
                 Corresponding_Name_Definition (Id);
            begin
               return Is_Package_Name (Name)
                 or else Is_Enclosing_Named_Construct (Expr, Name);
            end;
         when others =>
            return False;
      end case;
   end Is_Expanded_Name;

   ---------------------
   -- Is_Package_Name --
   ---------------------

   function Is_Package_Name (Name : Asis.Defining_Name) return Boolean is
      use Asis.Elements;

      Decl : constant Asis.Declaration := Enclosing_Element (Name);
      Kind : constant Asis.Declaration_Kinds := Declaration_Kind (Decl);
   begin
      return Kind = A_Package_Declaration or
        Kind = A_Package_Body_Declaration or
        Kind = A_Package_Renaming_Declaration or
        Kind = A_Package_Instantiation or
        Kind = A_Formal_Package_Declaration or
        Kind = A_Formal_Package_Declaration_With_Box;
   end Is_Package_Name;

   ----------------------------------
   -- Is_Enclosing_Named_Construct --
   ----------------------------------

   function Is_Enclosing_Named_Construct
     (Element : Asis.Element;
      Name    : Asis.Defining_Name) return Boolean
   is
      use Asis.Elements;
      use Asis.Statements;
      use Asis.Expressions;
      use Asis.Declarations;

      Parent      : Asis.Element       := Element;
      Parent_Name : Asis.Defining_Name := Nil_Element;
   begin
      while not Is_Nil (Parent) loop
         Parent_Name := Nil_Element;

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

                     Parent_Name := Declaration_Name (Parent);

                  when others =>
                     null;
               end case;
            when A_Statement =>
               case Statement_Kind (Parent) is
                  when A_Loop_Statement .. A_Block_Statement =>
                     Parent_Name := Statement_Identifier (Parent);

                  when An_Accept_Statement =>
                     Parent_Name := Corresponding_Name_Definition
                       (Accept_Entry_Direct_Name (Parent));
                  when others =>
                     null;
               end case;
            when others =>
               null;
         end case;

         if Is_Equal (Parent_Name, Name) then
            return True;
         else
            Parent := Enclosing_Element (Parent);
         end if;
      end loop;

      return False;
   end Is_Enclosing_Named_Construct;

   --------------------------------
   -- Is_Parameter_Specification --
   --------------------------------

   function Is_Parameter_Specification
     (Decl : Asis.Declaration) return Boolean
   is
      use Asis.Elements;
   begin
      return Declaration_Kind (Decl) = A_Parameter_Specification;
   end Is_Parameter_Specification;

   ----------------------------
   -- Is_Predefined_Operator --
   ----------------------------

   function Is_Predefined_Operator (Decl : Asis.Declaration) return Boolean is
      use Asis.Elements;
      Name : constant Asis.Defining_Name := Declaration_Name (Decl);
      Kind : constant Asis.Operator_Kinds := Operator_Kind (Name);
   begin
      return Kind /= Not_An_Operator
        and then Is_Part_Of_Implicit (Decl)
        and then not Is_Part_Of_Inherited (Decl);
   end Is_Predefined_Operator;

   ---------------------
   -- Last_Constraint --
   ---------------------

   function Last_Constraint
     (Decl : Asis.Declaration) return Asis.Declaration
   is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;
      View : constant Asis.Definition := Type_Declaration_View (Decl);
   begin
      if Definition_Kind (View) /= A_Subtype_Indication then
         return Decl;
      end if;

      if Is_Nil (Subtype_Constraint (View)) then
         return Corresponding_Last_Constraint (Decl);
      else
         return Decl;
      end if;
   end Last_Constraint;

   -----------------
   -- Lexic_Level --
   -----------------

   function Lexic_Level (Name : Asis.Defining_Name) return Positive is
      use Asis.Elements;
      use Asis.Declarations;

      Result : Positive := 1;
      Decl   : Asis.Declaration := Parent_Declaration (Name);
   begin
      while not Is_Nil (Decl) loop
         if Is_Subunit (Decl) then
            Decl := Corresponding_Body_Stub (Decl);
         else
            Decl := Parent_Declaration (Decl);
         end if;

         case Declaration_Kind (Decl) is
            when A_Procedure_Declaration
              | A_Function_Declaration
              | A_Procedure_Body_Declaration
              | A_Function_Body_Declaration
              | An_Entry_Declaration
              | An_Entry_Body_Declaration
              =>
               Result := Result + 1;
            when others =>
               null;
         end case;
      end loop;

      return Result;
   end Lexic_Level;

   ------------------------
   -- Must_Be_Completion --
   ------------------------

   function Must_Be_Completion (Declaration : Asis.Declaration) return Boolean
   is
      use Asis;
      Kind : constant Asis.Declaration_Kinds :=
        Asis.Elements.Declaration_Kind (Declaration);
   begin
      case Kind is
         when A_Protected_Body_Declaration =>
            return True;
         when A_Task_Body_Declaration =>
            return True;
         when A_Package_Body_Declaration =>
            return True;
         when An_Entry_Body_Declaration =>
            return True;
         when A_Package_Body_Stub =>
            return True;
         when A_Task_Body_Stub =>
            return True;
         when A_Protected_Body_Stub =>
            return True;
         when others =>
            return False;
      end case;
   end Must_Be_Completion;

   ----------------
   -- Name_Image --
   ----------------

   function Name_Image (Name : Asis.Expression) return Asis.Program_Text
   is
      use Asis.Elements;
      Kind : constant Asis.Expression_Kinds := Expression_Kind (Name);
   begin
      case Kind is
         when An_Identifier | An_Operator_Symbol |
           A_Character_Literal | An_Enumeration_Literal =>
            return Asis.Expressions.Name_Image (Name);
         when A_Selected_Component =>
            declare
               A : constant Asis.Element := Asis.Expressions.Prefix (Name);
               B : constant Asis.Element := Asis.Expressions.Selector (Name);
            begin
               return Name_Image (A) & "." & Asis.Expressions.Name_Image (B);
            end;
         when others =>
            raise XASIS_Error;
      end case;
   end Name_Image;

   --------------
   -- Named_By --
   --------------

   function Named_By
     (Element : Asis.Expression;
      Name    : Asis.Program_Text) return Boolean is
   begin
      return Are_Equal_Identifiers (Name_Image (Element), Name);
   end Named_By;

   -------------------
   -- Operator_Kind --
   -------------------

   function Operator_Kind
     (Name_Image : Asis.Program_Text;
      Binary     : Boolean := True)
      return Asis.Operator_Kinds
   is
      use Ada.Strings.Wide_Unbounded;

      function U (Text : Wide_String) return Unbounded_Wide_String
        renames To_Unbounded_Wide_String;

      type Info is record
         Image  : Unbounded_Wide_String;
         Binary : Boolean;
      end record;

      Names : constant array (An_And_Operator .. A_Not_Operator)
        of Info :=
        (An_And_Operator                    => (U ("""and"""), True),
         An_Or_Operator                     => (U ("""or"""), True),
         An_Xor_Operator                    => (U ("""xor"""), True),
         An_Equal_Operator                  => (U ("""="""), True),
         A_Not_Equal_Operator               => (U ("""/="""), True),
         A_Less_Than_Operator               => (U ("""<"""), True),
         A_Less_Than_Or_Equal_Operator      => (U ("""<="""), True),
         A_Greater_Than_Operator            => (U (""">"""), True),
         A_Greater_Than_Or_Equal_Operator   => (U (""">="""), True),
         A_Plus_Operator                    => (U ("""+"""), True),
         A_Minus_Operator                   => (U ("""-"""), True),
         A_Concatenate_Operator             => (U ("""&"""), True),
         A_Unary_Plus_Operator              => (U ("""+"""), False),
         A_Unary_Minus_Operator             => (U ("""-"""), False),
         A_Multiply_Operator                => (U ("""*"""), True),
         A_Divide_Operator                  => (U ("""/"""), True),
         A_Mod_Operator                     => (U ("""mod"""), True),
         A_Rem_Operator                     => (U ("""rem"""), True),
         An_Exponentiate_Operator           => (U ("""**"""), True),
         An_Abs_Operator                    => (U ("""abs"""), False),
         A_Not_Operator                     => (U ("""not"""), False));

   begin
      for I in Names'Range loop
         if (Binary = True or else Binary = Names (I).Binary) and then
           Are_Equal_Identifiers (Name_Image, To_Wide_String (Names (I).Image))
         then
            return I;
         end if;
      end loop;

      return Not_An_Operator;
   end Operator_Kind;

   ------------------
   -- Overloadable --
   ------------------

   function Overloadable
     (Element  : Asis.Defining_Name)
      return Boolean
   is
      use Asis.Elements;
      Parent : constant Asis.Element := Enclosing_Element (Element);
   begin
      pragma Assert (Element_Kind (Element) = A_Defining_Name,
                     "Unexpected element in Overloadable");

      if Element_Kind (Parent) = A_Statement then
         return False;
      else
         return Overloadable_Declaration (Parent);
      end if;
   end Overloadable;

   ------------------------------
   -- Overloadable_Declaration --
   ------------------------------

   function Overloadable_Declaration
     (Element  : Asis.Declaration)
      return Boolean
   is
      use Asis.Elements;
      Kind : constant Declaration_Kinds := Declaration_Kind (Element);
   begin
      pragma Assert (Kind /= Not_A_Declaration,
                     "Unexpected element in Overloadable_Declaration");

      return Kind = An_Enumeration_Literal_Specification or
        Kind = A_Procedure_Declaration or
        Kind = A_Function_Declaration or
        Kind = A_Procedure_Body_Declaration or
        Kind = A_Function_Body_Declaration or
        Kind = A_Procedure_Renaming_Declaration or
        Kind = A_Function_Renaming_Declaration or
        Kind = A_Generic_Procedure_Renaming_Declaration or
        Kind = A_Generic_Function_Renaming_Declaration or
        Kind = A_Procedure_Body_Stub or
        Kind = A_Function_Body_Stub or
        Kind = A_Formal_Procedure_Declaration or
        Kind = A_Formal_Function_Declaration or
        Kind = A_Procedure_Instantiation or
        Kind = A_Function_Instantiation;
   end Overloadable_Declaration;

   -------------------
   -- Parameterless --
   -------------------

   function Parameterless (Name : Asis.Declaration) return Boolean is
--      use Asis.Declarations;
   begin
      return Check_Callable_Name (Name) and then
        Is_Empty_Profile (Get_Profile (Name));
   end Parameterless;

   ------------------------
   -- Parent_Declaration --
   ------------------------

   function Parent_Declaration
     (Element : Asis.Element) return Asis.Declaration
   is
      use Asis.Elements;
      use type Asis.Element_Kinds;
      Parent : Asis.Element := Enclosing_Element (Element);
   begin
      while not Is_Nil (Parent) and then
        Element_Kind (Parent) /= Asis.A_Declaration
      loop
         Parent := Enclosing_Element (Parent);
      end loop;
      return Parent;
   end Parent_Declaration;

   -------------------------------
   -- Selected_Name_Declaration --
   -------------------------------

   function Selected_Name_Declaration
     (Expr      : Asis.Expression;
      Skip_Attr : Boolean;
      Unwind    : Boolean := False) return Asis.Declaration
   is
      use Asis.Elements;
      use Asis.Expressions;

      Mark : Asis.Expression;
   begin
      Mark := Selected_Name_Selector (Expr, Skip_Attr);

      case Expression_Kind (Mark) is
         when An_Identifier
           | An_Operator_Symbol
           | A_Character_Literal
           | An_Enumeration_Literal =>
            if Unwind then
               return Unwind_Renamed (Corresponding_Name_Declaration (Mark));
            else
               return Corresponding_Name_Declaration (Mark);
            end if;
         when others =>
            return Asis.Nil_Element;
      end case;
   end Selected_Name_Declaration;

   ----------------------------
   -- Selected_Name_Selector --
   ----------------------------

   function Selected_Name_Selector
     (Expr      : Asis.Expression;
      Skip_Attr : Boolean) return Asis.Expression
   is
      use Asis.Elements;
      use Asis.Expressions;
      Mark : Asis.Expression := Expr;
   begin
      if Skip_Attr then
         while Expression_Kind (Mark) = An_Attribute_Reference loop
            Mark := Prefix (Mark);
         end loop;
      end if;

      if Expression_Kind (Mark) = A_Selected_Component then
         Mark := Selector (Mark);
      end if;

      return Mark;
   end Selected_Name_Selector;

   ------------
   -- Unique --
   ------------

   function Unique (List : Asis.Element_List) return Asis.Element_List is
      Result : Asis.Element_List (1 .. List'Length);
      Index  : Asis.ASIS_Natural := 0;
      Found  : Boolean;
   begin
      if List'Length = 0 then
         return List;
      end if;

      for J in List'Range loop
         Found := False;

         for N in 1 .. Index loop
            if Asis.Elements.Is_Equal (List (J), Result (N)) then
               Found := True;
               exit;
            end if;
         end loop;

         if not Found then
            Index := Index + 1;
            Result (Index) := List (J);
         end if;
      end loop;

      return Result (1 .. Index);
   end Unique;

   --------------------
   -- Unwind_Renamed --
   --------------------

   function Unwind_Renamed (Item : Asis.Declaration)
                           return Asis.Declaration
   is
      use Asis.Declarations;
      Next : Asis.Declaration;
      Kind : constant Asis.Declaration_Kinds :=
        Asis.Elements.Declaration_Kind (Item);
   begin
      case Kind is
         when A_Renaming_Declaration =>
            Next := Selected_Name_Declaration
              (Renamed_Entity (Item), False, Unwind => True);
            return Next;
         when others =>
            return Item;
      end case;
   end Unwind_Renamed;

end XASIS.Utils;



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
