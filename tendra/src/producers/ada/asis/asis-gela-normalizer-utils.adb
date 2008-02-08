with XASIS.Utils;
with XASIS.Pragmas;
with Asis.Elements;
with Asis.Gela.Lists;
with Asis.Gela.Errors;
with Asis.Gela.Replace;
with Asis.Declarations;
with Asis.Gela.Element_Utils;
with Asis.Gela.Elements.Expr;
with Asis.Gela.Elements.Decl;
with Asis.Gela.Elements.Defs;
with Asis.Gela.Elements.Expr;
with Asis.Gela.Elements.Stmt;
with Asis.Gela.Elements.Helpers;
with Asis.Gela.Elements.Def_Names;
with Asis.Gela.Elements.Defs.Types;
with Asis.Gela.Elements.Defs.Formal;
with Ada.Characters.Handling;

package body Asis.Gela.Normalizer.Utils is

   function To_Defining_Unit_Name
     (Compount_Name : Asis.Element)
     return Asis.Element;

   function To_Defining_Operator_Symbol
     (Symbol : Asis.Element)
     return Asis.Defining_Name;

   function To_Defining_Identifier
     (Identifier : Asis.Identifier)
     return Asis.Defining_Name;

   function Get_Attribute_Kind
     (Item : Asis.Identifier) return Asis.Attribute_Kinds;

   function Get_Trait_Kind (Element : Asis.Element) return Asis.Trait_Kinds;
   function Is_Attribute_Expression (Element : Asis.Element) return Boolean;
   function To_Expression_List (Item : Asis.Element) return Asis.Element;
   function Is_Aggregate (Element : Asis.Expression) return Boolean;

   package H renames Asis.Gela.Elements.Helpers;

   -----------------------------
   -- Aggregate_To_Expression --
   -----------------------------

   procedure Aggregate_To_Expression (Aggregate : in out Asis.Expression) is
      use Asis.Gela.Elements.Expr;
      use Lists.Primary_Association_Lists;

      Aggr         : Record_Aggregate_Node renames
        Record_Aggregate_Node (Aggregate.all);

      Associations : constant List :=
        List (Record_Component_Associations_List (Aggr));
      Association  : constant Asis.Element := Get_Item (Associations, 1);
   begin
      Aggregate := Component_Expression (Association.all);
   end Aggregate_To_Expression;

   ---------------------------
   -- Check_Back_Identifier --
   ---------------------------

   procedure Check_Back_Identifier (Element : Asis.Element) is
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Elements.Def_Names;

      procedure Check_Name (Start, Back : Wide_String) is
      begin
         if not XASIS.Utils.Are_Equal_Identifiers (Start, Back) then
            Errors.Report
              (Item => Element, -- Back_Identifier_Element,
               What => Errors.Error_Syntax_Bad_Back_Identifier,
               Argument1 => Start,
               Argument2 => Back);
         end if;
      end Check_Name;

      Node             : Node_Type renames Node_Type (Element.all);
      Back_Identifier  : constant Asis.Element      := Compound_Name (Node);
      Name             : constant Asis.Element_List := Names (Element);
      Start_Identifier : Asis.Defining_Name;
      Img              : constant Wide_String :=
        Element_Utils.Compound_Name_Image (Back_Identifier);

   begin
      if Name'Length >= 1 then
         Start_Identifier := Name (1);
      end if;

      if Assigned (Start_Identifier) then
         if Assigned (Back_Identifier) then
            Set_Is_Name_Repeated (Node, True);

            if Element_Kind (Start_Identifier.all) = An_Expression then
               Check_Name (Name_Image (Start_Identifier.all), Img);
            else
               Check_Name (Defining_Name_Image (Start_Identifier.all), Img);
            end if;
         else
            Set_Is_Name_Repeated (Node, False);
         end if;
      else
         Set_Is_Name_Repeated (Node, False);

         if Assigned (Back_Identifier) then
            Errors.Report (Item => Element, -- Back_Identifier_Element,
                           What => Errors.Error_Syntax_Back_Identifier_Exists,
                           Argument1 => Img);
         end if;
      end if;
   end Check_Back_Identifier;

   -------------------------
   -- Check_Empty_Generic --
   -------------------------

   procedure Check_Empty_Generic (Element : Asis.Element) is
      use Asis.Gela.Elements.Decl;
      use Lists.Primary_Declaration_Lists;

      Ptr  : constant Generic_Package_Renaming_Declaration_Ptr :=
        Generic_Package_Renaming_Declaration_Ptr (Element);

      Empty : constant List := List (Empty_Generic_Part_List (Ptr.all));
   begin
      if Length (Empty.all) > 0 then
         Errors.Report (Item => Element, -- Get_Item (Empty.all, 1),
                        What => Errors.Error_Syntax_Not_Empty_Generic);
      end if;
      Set_Empty_Generic_Part (Ptr.all, Nil_Element);
   end Check_Empty_Generic;

   -------------------------
   -- Check_Empty_Profile --
   -------------------------

   procedure Check_Empty_Profile (Element : in out Asis.Element) is
      use Lists.Primary_Parameter_Lists;

      Profile : constant List := List (Element);
   begin
      if Profile /= null then
         if Length (Profile.all) > 0 then
            Errors.Report (Item => Element, -- Get_Item (Profile.all, 1),
                           What => Errors.Error_Syntax_Not_Empty_Profile);
         end if;
      end if;
   end Check_Empty_Profile;

   ------------------------
   -- Check_Empty_Result --
   ------------------------

   procedure Check_Empty_Result (Profile : in out Asis.Element) is
   begin
      if Assigned (Profile) then
         Errors.Report (Item => Profile,
                        What => Errors.Error_Syntax_Not_Empty_Result);
      end if;
   end Check_Empty_Result;

   ----------------------------------
   -- Create_Incomplete_Definition --
   ----------------------------------

   procedure Create_Incomplete_Definition (Element : Asis.Declaration) is
      use Asis.Gela.Elements.Decl;
      use Asis.Gela.Elements.Defs;

      Node  : Incomplete_Type_Declaration_Node renames
        Incomplete_Type_Declaration_Node (Element.all);
      Child : Incomplete_Type_Definition_Ptr :=
        new Incomplete_Type_Definition_Node;
   begin
      Set_Type_Declaration_View (Node, Asis.Element (Child));
   end Create_Incomplete_Definition;

   -------------------------------
   -- Drop_Range_Attr_Reference --
   -------------------------------

   procedure Drop_Range_Attr_Reference (Element : Asis.Element) is
      Node  : Node_Type renames Node_Type (Element.all);
      Child : constant Asis.Element := Range_Attribute (Element.all);
      Attr  : constant Asis.Element := Range_Attribute (Child.all);
   begin
      Set_Range_Attribute (Node, Attr);
   end Drop_Range_Attr_Reference;

   -----------------------------------
   -- Drop_Range_Subtype_Indication --
   -----------------------------------

   procedure Drop_Range_Subtype_Indication (Element : Asis.Element) is
      Node  : Node_Type renames Node_Type (Element.all);
      Child : constant Asis.Element := Get_Subtype_Mark (Element.all);
      Attr  : constant Asis.Element := Get_Subtype_Mark (Child.all);
   begin
      Set_Subtype_Mark (Node, Attr);
   end Drop_Range_Subtype_Indication;

   ------------------------
   -- Get_Attribute_Kind --
   ------------------------

   function Get_Attribute_Kind
     (Item : Asis.Identifier) return Asis.Attribute_Kinds
   is
      use Ada.Characters.Handling;
      Name   : constant String := To_String (Name_Image (Item.all));
      Text1  : constant String := "A_"  & Name & "_Attribute";
      Text2  : constant String := "An_" & Name & "_Attribute";
      Upper1 : constant String := To_Upper (Text1);
      Upper2 : constant String := To_Upper (Text2);
   begin
      for I in An_Access_Attribute .. A_Write_Attribute loop
         declare
            Attr_I : constant String := Attribute_Kinds'Image (I);
         begin
            if Attr_I = Upper1 or Attr_I = Upper2 then
               return I;
            end if;
         end;
      end loop;
      return An_Unknown_Attribute;
   end Get_Attribute_Kind;

   --------------------
   -- Get_Trait_Kind --
   --------------------

   function Get_Trait_Kind (Element : Asis.Element) return Asis.Trait_Kinds is
      Trait : Trait_Kinds := Trait_Kind (Element.all);
   begin
      case Definition_Kind (Element.all) is
         when A_Tagged_Private_Type_Definition =>
            if Has_Abstract (Element.all) then
               if Has_Limited (Element.all) then
                  Trait := An_Abstract_Limited_Private_Trait;
               else
                  Trait := An_Abstract_Private_Trait;
               end if;
            elsif Has_Limited (Element.all) then
               Trait := A_Limited_Private_Trait;
            else
               Trait := A_Private_Trait;
            end if;

         when A_Private_Extension_Definition =>
            if Has_Abstract (Element.all) then
               Trait := An_Abstract_Private_Trait;
            else
               Trait := A_Private_Trait;
            end if;

         when A_Private_Type_Definition =>
            if Has_Limited (Element.all) then
               Trait := A_Limited_Private_Trait;
            else
               Trait := A_Private_Trait;
            end if;

         when A_Type_Definition =>
            case Type_Definition_Kind (Element.all) is
               when A_Tagged_Record_Type_Definition |
                 A_Derived_Type_Definition |
                 A_Derived_Record_Extension_Definition
                 =>
                  if Has_Abstract (Element.all) then
                     if Has_Limited (Element.all) then
                        Trait := An_Abstract_Limited_Trait;
                     else
                        Trait := An_Abstract_Trait;
                     end if;
                  elsif Has_Limited (Element.all) then
                     Trait := A_Limited_Trait;
                  end if;

               when others =>
                  null;
            end case;

         when A_Formal_Type_Definition =>
            case Formal_Type_Definition_Kind (Element.all) is
               when A_Formal_Derived_Type_Definition =>
                  if Has_Private (Element.all) then
                     if Has_Abstract (Element.all) then
                        Trait := An_Abstract_Private_Trait;
                     else
                        Trait := A_Private_Trait;
                     end if;
                  elsif Has_Abstract (Element.all) then
                     Trait := An_Abstract_Trait;
                  end if;

               when A_Formal_Private_Type_Definition =>
                  if Has_Limited (Element.all) then
                     Trait := A_Limited_Private_Trait;
                  else
                     Trait := A_Private_Trait;
                  end if;

               when A_Formal_Tagged_Private_Type_Definition =>
                  if Has_Abstract (Element.all) then
                     if Has_Limited (Element.all) then
                        Trait := An_Abstract_Limited_Private_Trait;
                     else
                        Trait := An_Abstract_Private_Trait;
                     end if;
                  elsif Has_Limited (Element.all) then
                     Trait := A_Limited_Private_Trait;
                  else
                     Trait := A_Private_Trait;
                  end if;

               when others =>
                  null;
            end case;

         when others =>
            null;
      end case;

      return Trait;
   end Get_Trait_Kind;

   ------------------
   -- Is_Aggregate --
   ------------------

   function Is_Aggregate (Element : Asis.Expression) return Boolean is
      use Asis.Gela.Elements.Expr;
      use Lists.Primary_Association_Lists;

      Aggregate    : Record_Aggregate_Ptr;
      Associations : List;
      Association  : Asis.Element;
      Expr         : Asis.Expression;
   begin
      if Expression_Kind (Element.all) /= A_Record_Aggregate then
         return True;
      else
         Aggregate    := Record_Aggregate_Ptr (Element);
         Associations :=
           List (Record_Component_Associations_List (Aggregate.all));

         if Length (Associations.all) /= 1 then
            return True;
         end if;

         Association := Get_Item (Associations, 1);

         if Record_Component_Choices (Association.all)'Length > 0 then
            return True;
         end if;

         Expr := Component_Expression (Association.all);

         if Element_Kind (Expr.all) /= An_Expression then
            return True;
         end if;
      end if;

      return False;
   end Is_Aggregate;

   -----------------------------
   -- Is_Attribute_Expression --
   -----------------------------

   function Is_Attribute_Expression (Element : Asis.Element) return Boolean is
      use XASIS.Utils;

      Id   : Asis.Element;
      Attr : constant Asis.Element := Prefix (Element.all);
   begin
      if Is_Prefix_Call (Element.all) and then
        Expression_Kind (Attr.all) = An_Attribute_Reference
      then
         Id := Attribute_Designator_Identifier (Attr.all);

         if Are_Equal_Identifiers (Name_Image (Id.all), "first") or
           Are_Equal_Identifiers (Name_Image (Id.all), "last")   or
           Are_Equal_Identifiers (Name_Image (Id.all), "length") or
           Are_Equal_Identifiers (Name_Image (Id.all), "range")
         then
            return True;
         end if;
      end if;

      return False;
   end Is_Attribute_Expression;

   ---------------------------
   -- Normalize_Access_Type --
   ---------------------------

   procedure Normalize_Access_Type (Element : Asis.Element) is
      use Asis.Gela.Elements.Helpers;
      use Asis.Gela.Elements.Defs.Types;
      use Lists.Primary_Parameter_Lists;

      Node     : Access_Type_Node renames Access_Type_Node (Element.all);
      Modifier : constant Asis.Element := General_Access_Modifier (Node);
      Profile  : constant Function_Profile_Ptr :=
        Function_Profile_Ptr (Access_To_Function_Result_Subtype (Node));
      Params   : constant List := List
        (Access_To_Subprogram_Parameter_Profile_List (Node));
   begin
      if Assigned (Get_Access_To_Object_Definition (Node)) then
         if not Assigned (Modifier) then
            Set_Access_Type_Kind (Node, A_Pool_Specific_Access_To_Variable);
         else
            declare
               Token : Token_Node renames
                 Token_Node (Modifier.all);
            begin
               if Length (Token) = 3 then  --  "all"
                  Set_Access_Type_Kind (Node, An_Access_To_Variable);
               else                        --  "constant"
                  Set_Access_Type_Kind (Node, An_Access_To_Constant);
               end if;
            end;
         end if;
      elsif Profile /= null then
         if Assigned (Modifier) then
            Set_Access_Type_Kind (Node, An_Access_To_Protected_Function);
         else
            Set_Access_Type_Kind (Node, An_Access_To_Function);
         end if;

         Set_Access_To_Function_Result_Subtype
           (Node, Result_Profile (Profile.all));

         Set_Access_To_Subprogram_Parameter_Profile
           (Node, Parameter_Profile_List (Profile.all));
      else
         if Assigned (Modifier) then
            Set_Access_Type_Kind (Node, An_Access_To_Protected_Procedure);
         else
            Set_Access_Type_Kind (Node, An_Access_To_Procedure);
         end if;

         if Length (Params.all) = 0 then
            declare
               Pos : Text_Position := Start_Position (Params.all);
            begin
               Pos.Column := Pos.Column + 8;
               Set_End_Position (Node, Pos);
            end;
         end if;
      end if;
   end Normalize_Access_Type;

   -----------------------------------
   -- Normalize_Attribute_Reference --
   -----------------------------------

   procedure Normalize_Attribute_Reference (Element : Asis.Element) is
      use Asis.Gela.Elements.Expr;

      Node  : Attribute_Reference_Node renames
        Attribute_Reference_Node (Element.all);

      Identifier : constant Asis.Identifier :=
        Attribute_Designator_Identifier (Element.all);
      Pref       : constant Asis.Element    := Prefix (Element.all);
   begin
      Set_Attribute_Kind (Node, Get_Attribute_Kind (Identifier));
      if Pref.all in Lists.Primary_Identifier_Lists.List_Node then
         Set_Prefix (Node, Element_Utils.To_Unit_Name (Pref));
      end if;
   end Normalize_Attribute_Reference;

   ----------------------------------
   -- Normalize_Formal_Access_Type --
   ----------------------------------

   procedure Normalize_Formal_Access_Type (Element : Asis.Element) is
      use Asis.Gela.Elements.Defs.Types;
      use Asis.Gela.Elements.Defs.Formal;

      Node  : Formal_Access_Type_Node renames
        Formal_Access_Type_Node (Element.all);
      Def   : constant Asis.Element := Access_Definition (Node);
      Child : Access_Type_Node renames Access_Type_Node (Def.all);
   begin
      Normalize_Access_Type (Def);
      Set_Access_Type_Kind (Node, Access_Type_Kind (Child));

      Set_Access_To_Object_Definition
        (Node, Get_Access_To_Object_Definition (Child));

      Set_Access_To_Subprogram_Parameter_Profile
        (Node, Access_To_Subprogram_Parameter_Profile_List (Child));

      Set_Access_To_Function_Result_Subtype
        (Node, Access_To_Function_Result_Subtype (Child));

      Set_Access_Definition (Node, Asis.Nil_Element);
   end Normalize_Formal_Access_Type;

   -----------------------------
   -- Normalize_Function_Call --
   -----------------------------

   procedure Normalize_Function_Call
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is

      use Asis.Gela.Elements.Expr;

      Node  : Function_Call_Node renames Function_Call_Node (Element.all);
      Child : constant Asis.Element := Record_Aggregate (Node);
      Rec   : constant Record_Aggregate_Ptr  := Record_Aggregate_Ptr (Child);
      Args  : Asis.Element;
   begin
      if Assigned (Child) then
         Args := Record_Component_Associations_List (Rec.all);
         Set_Function_Call_Parameters (Node, Args);
      end if;

      if Is_Attribute_Expression (Element) then
         declare
            Pref : constant Asis.Element := Prefix (Element.all);
            Attr : Attribute_Reference_Node renames
              Attribute_Reference_Node (Pref.all);
         begin
            Set_Attribute_Designator_Expressions
              (Attr, To_Expression_List (Args));

            Set_End_Position (Attr, End_Position (Element.all));
--          Set_Enclosing_Compilation_Unit (Attr, State.Unit);
--          Set_Enclosing_Element (Attr, Enclosing_Element (Element.all));
            Set_Prefix (Node, Nil_Element);
--          State.Parent := Pref;
            Element := Pref;
            Normalize_Attribute_Reference (Element);
         end;
      end if;
   end Normalize_Function_Call;

   ----------------------------------
   -- Normalize_Handled_Statements --
   ----------------------------------

   procedure Normalize_Handled_Statements (Element : Asis.Element) is
      use Asis.Gela.Lists;
      use Asis.Gela.Elements.Helpers;

      Node  : Node_Type renames Node_Type (Element.all);
      Stmts : constant Handled_Statements_Ptr :=
        Handled_Statements_Ptr (Handled_Statements (Node));
   begin
      if Stmts /= null then
         Set_Statements (Node, Statements_List (Stmts.all));
         Set_Exception_Handlers (Node, Exception_Handlers_List (Stmts.all));
         Set_Statements (Stmts.all, Nil_Element);
         Set_Exception_Handlers (Stmts.all, Nil_Element);
      end if;
   end Normalize_Handled_Statements;

   ------------------------------
   -- Normalize_Component_List --
   ------------------------------

   procedure Normalize_Component_List (Element : Asis.Element)
   is
      use Lists;
      use Asis.Gela.Elements.Defs;
      use Primary_Statement_Lists;
      use Primary_Declaration_Lists;
      Node    : Node_Type renames Node_Type (Element.all);
      Item    : constant Primary_Declaration_Lists.List :=
        Primary_Declaration_Lists.List (Record_Components_List (Node));
      Child   : Asis.Element;
      List    : Primary_Statement_Lists.List;
      Index   : Positive := 1;
   begin
      while Index <= Length (Item.all) loop
         Child := Get_Item (Item, Index);
         List  := null;

         if Definition_Kind (Child.all) = A_Null_Component then
            List := Primary_Statement_Lists.List
              (Pragmas_List (Null_Component_Node (Child.all)));

         elsif Definition_Kind (Child.all) = A_Variant_Part then
            List := Primary_Statement_Lists.List
              (End_Pragmas_List (Variant_Part_Node (Child.all)));
         end if;

         if List /= null then
            while Length (List.all) > 0 loop
               Child := Get_Item (List, 1);
               Remove (List.all, Child);
               Add (Item.all, Child);
            end loop;
         end if;

         Index := Index + 1;
      end loop;
   end Normalize_Component_List;

   ------------------------------------
   -- Normalize_Overriding_Indicator --
   ------------------------------------

   procedure Normalize_Overriding_Indicator (Element : Asis.Element) is
      Node      : Node_Type renames Node_Type (Element.all);
      Indicator : Asis.Element := Overriding_Indicator (Node);
   begin
      if not Assigned (Indicator) then
         Set_Overriding_Indicator_Kind (Node, No_Overriding_Indicator);
      else
         declare
            use Asis.Gela.Elements.Helpers;
            Token : Token_Node renames Token_Node (Indicator.all);
         begin
            if Length (Token) = 3 then  --  "not"
               Set_Overriding_Indicator_Kind
                 (Node, An_Indicator_of_Not_Overriding);
            else                        --  ""
               Set_Overriding_Indicator_Kind
                 (Node, An_Indicator_of_Overriding);
            end if;
         end;
      end if;
   end Normalize_Overriding_Indicator;

   -------------------------------
   -- Normalize_Pragma_Argument --
   -------------------------------

   procedure Normalize_Pragma_Argument (Element : in out Asis.Expression) is
      use Asis.Elements;
      use XASIS.Pragmas;

      Parent     : constant Asis.Element := Enclosing_Element (Element);
      The_Pragma : constant Asis.Pragma_Element := Enclosing_Element (Parent);
   begin
      case Pragma_Kind (The_Pragma) is
         when An_Export_Pragma | An_Import_Pragma =>
            if Is_Equal (Element, Parameter (The_Pragma, External_Name))
              or Is_Equal (Element, Parameter (The_Pragma, Link_Name))
            then
               Replace.Operator_Symbol_To_String_Literal (Element);
            end if;

         when A_Linker_Options_Pragma =>
            Replace.Operator_Symbol_To_String_Literal (Element);

         when others =>
            null;
      end case;
   end Normalize_Pragma_Argument;

   ------------------------------
   -- Normalize_Procedure_Call --
   ------------------------------

   procedure Normalize_Procedure_Call (Element : Asis.Element) is
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Elements.Stmt;

      Node  : Procedure_Call_Statement_Node renames
        Procedure_Call_Statement_Node (Element.all);

      Funct : constant Asis.Element := Called_Name (Element.all);
      Aggr  : Asis.Element;
      Rec   : Record_Aggregate_Ptr;
      Args  : Asis.Element;
   begin
      if Expression_Kind (Funct.all) = A_Function_Call then
         Aggr := Record_Aggregate (Function_Call_Node (Funct.all));
         Rec  := Record_Aggregate_Ptr (Aggr);
         Args := Record_Component_Associations_List (Rec.all);
         Set_Call_Statement_Parameters (Node, Args);
         Set_Called_Name (Node, Prefix (Funct.all));
      end if;
   end Normalize_Procedure_Call;

   ------------------------------------
   -- Normalize_Qualified_Expression --
   ------------------------------------

   procedure Normalize_Qualified_Expression (Element : Asis.Element) is
      use Asis.Gela.Elements.Expr;

      Aggr : Asis.Expression :=
        Converted_Or_Qualified_Expression (Element.all);
   begin
      if not Is_Aggregate (Aggr) then
         Aggregate_To_Expression (Aggr);

         Set_Converted_Or_Qualified_Expression
           (Qualified_Expression_Node (Element.all), Aggr);
      end if;
   end Normalize_Qualified_Expression;

   --------------------------------
   -- Normalize_Record_Aggregate --
   --------------------------------

   procedure Normalize_Record_Aggregate
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Element_Utils;

      Replace : Parenthesized_Expression_Ptr;
   begin
      if not Is_Aggregate (Element) then
         Replace := new Parenthesized_Expression_Node;
         Copy_Element (Element, Asis.Element (Replace));
         Aggregate_To_Expression (Element);
         Set_Expression_Parenthesized (Replace.all, Element);
         Element := Asis.Element (Replace);
      end if;
   end Normalize_Record_Aggregate;

   --------------------------------------
   -- Normalize_Enumeration_Rep_Clause --
   --------------------------------------

   procedure Normalize_Enumeration_Rep_Clause (Element : in out Asis.Element)
   is
   begin
      Replace.To_Enumeration_Rep_Clause (Element);
   end Normalize_Enumeration_Rep_Clause;

   ----------------------
   -- Set_Default_Kind --
   ----------------------

   procedure Set_Default_Kind (Element : Asis.Element) is
      use Asis.Gela.Elements.Decl;
      use Asis.Gela.Elements.Helpers;

      Default : constant Asis.Element :=
        Formal_Subprogram_Default (Element.all);
      Ptr     : constant Formal_Procedure_Declaration_Ptr :=
        Formal_Procedure_Declaration_Ptr (Element);
   begin
      if not Assigned (Default) then
         Set_Default_Kind (Ptr.all, A_Nil_Default);
      elsif Default.all in Token_Node then
         Set_Default_Kind (Ptr.all, A_Box_Default);
         Set_Formal_Subprogram_Default (Ptr.all, Nil_Element);
      else
         Set_Default_Kind (Ptr.all, A_Name_Default);
      end if;
   end Set_Default_Kind;

   ------------------------
   -- Set_Enum_Positions --
   ------------------------

   procedure Set_Enum_Positions
     (List : Asis.Declaration_List)
   is
      use Asis.Gela.Elements.Def_Names;

      Name : Asis.Defining_Name;
   begin
      for I in List'Range loop
         Name := Names (List (I).all) (1);

         case Defining_Name_Kind (Name.all) is
            when A_Defining_Character_Literal
              | A_Defining_Enumeration_Literal =>

               declare
                  Node : Defining_Enumeration_Literal_Node'Class renames
                    Defining_Enumeration_Literal_Node'Class (Name.all);
                  Img  : constant Wide_String :=
                    Asis.Asis_Integer'Wide_Image (I - 1);
               begin
                  Set_Position_Number_Image      (Node, Img);
                  Set_Representation_Value_Image (Node, Img);
               end;
            when others =>
               raise Internal_Error;
         end case;
      end loop;
   end Set_Enum_Positions;

   ----------------------------
   -- Set_Generic_Unit_Names --
   ----------------------------

   procedure Set_Generic_Unit_Names (Element : Asis.Element) is
      use Asis.Gela.Elements.Decl;

      Node     : Node_Type renames Node_Type (Element.all);
      Gen_Name : constant Asis.Element := Generic_Unit_Name (Element.all);
   begin
      Set_Generic_Unit_Name (Node, Element_Utils.To_Unit_Name (Gen_Name));
   end Set_Generic_Unit_Names;

   ---------------------
   -- Set_Has_Private --
   ---------------------

   procedure Set_Has_Private (Element : Asis.Element) is
      Node : Node_Type renames Node_Type (Element.all);
      List : constant Asis.Element := Private_Part_Items_List (Node);
   begin
      Set_Is_Private_Present (Node, Assigned (List));
   end Set_Has_Private;

   -------------------
   -- Set_Mode_Kind --
   -------------------

   procedure Set_Mode_Kind (Element : Asis.Element) is
      use Asis.Gela.Elements.Decl;
      use Lists.Primary_Token_Lists;
      use Asis.Gela.Elements.Helpers;

      Node   : Formal_Object_Declaration_Node renames
        Formal_Object_Declaration_Node (Element.all);
      Modes  : constant List := List (Mode_Element (Node));
   begin
      if Modes = null then
         Set_Mode_Kind (Node, A_Default_In_Mode);
         return;
      end if;

      case Length (Modes.all) is
         when 0 =>
            Set_Mode_Kind (Node, A_Default_In_Mode);
         when 2 =>
            Set_Mode_Kind (Node, An_In_Out_Mode);
         when others =>
            declare
               First : constant Asis.Element := Get_Item (Modes, 1);
               Token : constant Token_Ptr := Token_Ptr (First);
            begin
               if Length (Token.all) = 2 then  --  "in"
                  Set_Mode_Kind (Node, An_In_Mode);
               else                            --  "out"
                  Set_Mode_Kind (Node, An_Out_Mode);
               end if;
            end;
      end case;
      Set_Mode_Element (Node, Nil_Element);
   end Set_Mode_Kind;

   ---------------
   -- Set_Names --
   ---------------

   procedure Set_Names
     (Element : Asis.Element;
      Name    : Asis.Defining_Name := Asis.Nil_Element)
   is
      use Asis.Gela.Elements;
      use Lists.Primary_Defining_Name_Lists;

      Ptr    : constant Declaration_Ptr := Declaration_Ptr (Element);
      To_Set : Asis.Defining_Name;
      Items  : List;
   begin
      if Assigned (Name) then
         To_Set := Name;
      else
         To_Set := Asis.Gela.Elements.Name (Ptr.all);
      end if;

      if Assigned (To_Set) then
         To_Set := To_Defining_Unit_Name (To_Set);

--         if To_Set.all in List_Node then
         if Is_List (To_Set.all) then
            Set_Names (Ptr.all, To_Set);
         elsif Element_Kind (To_Set.all) = A_Defining_Name then
            Items := new List_Node;
            Add (Items.all, To_Set);
            Set_Names (Ptr.all, Asis.Element (Items));
         end if;
      end if;
   end Set_Names;

   ----------------------
   -- Set_Formal_Array --
   ----------------------

   procedure Set_Formal_Array (Element : Asis.Element) is
      Node  : Node_Type renames Node_Type (Element.all);
      Def   : constant Asis.Element := Array_Definition (Node);
      Child : Array_Type renames Array_Type (Def.all);
   begin
      Set_Index_Subtype_Definitions
        (Node, Index_Subtype_Definitions_List (Child));

      Set_Array_Component_Definition
        (Node, Array_Component_Definition (Def.all));
   end Set_Formal_Array;

   ------------------------
   -- Set_Start_Position --
   ------------------------

   procedure Set_Start_Position
     (Element, Source : Asis.Element)
   is
      use Asis.Gela.Elements;
      Node : Base_Element_Node renames Base_Element_Node (Element.all);
   begin
      Set_Start_Position (Node, Start_Position (Source.all));
   end Set_Start_Position;

   --------------------
   -- Set_Trait_Kind --
   --------------------

   procedure Set_Trait_Kind (Element : Asis.Element) is
      Kind : Trait_Kinds;
      Node : Node_Type renames Node_Type (Element.all);
   begin
      if Element_Kind (Element.all) = A_Declaration then
         Kind := Get_Trait_Kind (Type_Declaration_View (Element.all));
      else
         Kind := Get_Trait_Kind (Element);
      end if;

      Set_Trait_Kind (Node, Kind);
   end Set_Trait_Kind;

   ----------------------------------
   -- Split_Function_Specification --
   ----------------------------------

   procedure Split_Function_Specification (Element : Asis.Element) is

      use Lists.Primary_Parameter_Lists;
      use Asis.Gela.Elements.Helpers;
      use Asis.Gela.Elements.Def_Names;

      Node         : Node_Type renames Node_Type (Element.all);
      Spec_Element : constant Asis.Element := Specification (Node);
      Spec         : constant Function_Specification_Ptr :=
        Function_Specification_Ptr (Spec_Element);
      Prof         : constant Function_Profile_Ptr :=
        Function_Profile_Ptr (Profile (Spec.all));
      Name         : Asis.Defining_Name;
      Params       : Lists.Primary_Parameter_Lists.List;
   begin
      Name := To_Defining_Unit_Name (H.Names (Spec.all));
      Set_Names (Element, Name);

      if Defining_Name_Kind (Name.all) = A_Defining_Operator_Symbol then
         Set_Names (Spec.all, Nil_Element);
      end if;

      if Prof = null then
         return;
      end if;

      Params := List (Parameter_Profile_List (Prof.all));
      Set_Parameter_Profile (Node, Asis.Element (Params));

      Set_Result_Subtype (Node, Result_Profile (Prof.all));

      Set_Parameter_Profile (Prof.all, null);
      Set_Result_Profile (Prof.all, Nil_Element);

      if Defining_Name_Kind (Name.all) = A_Defining_Operator_Symbol then
         declare
            use Asis.Gela.Elements.Def_Names;
            Img    : constant Asis.Program_Text :=
              Defining_Name_Image (Name.all);
            Binary : constant Boolean := Length (Params.all) = 2
              or else (Length (Params.all) = 1
                and then Names (Get_Item (Params, 1).all)'Length = 2);
            Kind   : constant Asis.Operator_Kinds :=
              XASIS.Utils.Operator_Kind (Img, Binary);
         begin
            Set_Operator_Kind
              (Defining_Operator_Symbol_Node (Name.all), Kind);
         end;
      end if;
   end Split_Function_Specification;

   -------------------
   -- Split_Profile --
   -------------------

   procedure Split_Profile (Element : Asis.Element) is

      use Lists.Primary_Parameter_Lists;
      use Asis.Gela.Elements.Helpers;

      Node         : Node_Type renames Node_Type (Element.all);
      Prof         : constant Function_Profile_Ptr :=
        Function_Profile_Ptr (Result_Subtype (Node));

      Params       : Lists.Primary_Parameter_Lists.List;
   begin
      Params := List (Parameter_Profile_List (Prof.all));
      Set_Parameter_Profile (Node, Asis.Element (Params));
      Set_Result_Subtype (Node, Result_Profile (Prof.all));
   end Split_Profile;

   ---------------------------------
   -- Split_Package_Specification --
   ---------------------------------

   procedure Split_Package_Specification (Element : Asis.Element)
   is
      use Asis.Gela.Elements.Helpers;
      use Lists.Primary_Declaration_Lists;

      Node : Node_Type renames Node_Type (Element.all);

      Spec : constant Package_Specification_Ptr :=
        Package_Specification_Ptr (Specification (Node));

      Priv : constant Asis.Element :=
        Asis.Element (H.Private_Part_Declarative_Items_List (Spec.all));

      Vis  : constant Asis.Element :=
        Asis.Element (H.Visible_Part_Declarative_Items_List (Spec.all));

      Back : constant Asis.Element := H.Compound_Name (Spec.all);
      Img  : constant Wide_String :=
        Element_Utils.Compound_Name_Image (Back);
   begin
      Set_Visible_Part_Declarative_Items (Node, Vis);
      Set_Visible_Part_Declarative_Items (Spec.all, Nil_Element);

      Set_Private_Part_Declarative_Items (Node, Priv);
      Set_Private_Part_Declarative_Items (Spec.all, Nil_Element);

      Set_Is_Private_Present (Node, Assigned (Priv));

      Set_Names (Element, To_Defining_Unit_Name (Names (Spec.all)));

      Set_Compound_Name (Spec.all, Nil_Element);

      if Assigned (Back) then
         Set_Is_Name_Repeated (Node, True);

         if not XASIS.Utils.Are_Equal_Identifiers
           (Element_Utils.Compound_Name_Image (Names (Element.all) (1)), Img)
         then
            Errors.Report
              (Item => Element, -- Back,
               What => Errors.Error_Syntax_Bad_Back_Identifier,
               Argument1 => Defining_Name_Image (Names (Element.all) (1).all),
               Argument2 => Img);
         end if;
      else
         Set_Is_Name_Repeated (Node, False);
      end if;
   end Split_Package_Specification;

   -----------------------------------
   -- Split_Procedure_Specification --
   -----------------------------------

   procedure Split_Procedure_Specification (Element : Asis.Element) is
      use Asis.Gela.Elements.Helpers;
      use Lists.Primary_Parameter_Lists;

      Node         : Node_Type renames Node_Type (Element.all);
      Spec_Element : constant Asis.Element := Specification (Node);
      Spec         : constant Procedure_Specification_Ptr :=
        Procedure_Specification_Ptr (Spec_Element);
      Name         : Asis.Defining_Name;
   begin
      Name := To_Defining_Unit_Name (H.Names (Spec.all));
      Set_Names (Element, Name);
      Set_Parameter_Profile (Node, Profile (Spec.all));
   end Split_Procedure_Specification;

   ----------------------------
   -- To_Defining_Identifier --
   ----------------------------

   function To_Defining_Identifier
     (Identifier : Asis.Identifier)
     return Asis.Defining_Name
   is
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Elements.Def_Names;

      Ident       : constant Identifier_Ptr := Identifier_Ptr (Identifier);
      Def_Ident   : constant Defining_Identifier_Ptr :=
        new Defining_Identifier_Node;
   begin
      Set_Defining_Name_Image (Def_Ident.all, Name_Image (Ident.all));
      Set_Start_Position (Def_Ident.all, Start_Position (Ident.all));
      Set_End_Position (Def_Ident.all, End_Position (Ident.all));
      return Asis.Defining_Name (Def_Ident);
   end To_Defining_Identifier;

   ---------------------------------
   -- To_Defining_Operator_Symbol --
   ---------------------------------

   function To_Defining_Operator_Symbol
     (Symbol : Asis.Element)
     return Asis.Defining_Name
   is
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Elements.Def_Names;

      Oper        : constant Operator_Symbol_Ptr :=
        Operator_Symbol_Ptr (Symbol);
      Def_Oper    : constant Defining_Operator_Symbol_Ptr :=
        new Defining_Operator_Symbol_Node;
   begin
      Set_Defining_Name_Image (Def_Oper.all, Name_Image (Oper.all));
      Set_Start_Position (Def_Oper.all, Start_Position (Oper.all));
      Set_End_Position (Def_Oper.all, End_Position (Oper.all));
      return Asis.Defining_Name (Def_Oper);
   end To_Defining_Operator_Symbol;

   ---------------------------
   -- To_Defining_Unit_Name --
   ---------------------------

   function To_Defining_Unit_Name
     (Compount_Name : Asis.Element)
     return Asis.Element
   is
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Elements.Def_Names;
      use Lists.Primary_Identifier_Lists;

      Identifiers : List;
      Unit_Name   : Asis.Element;
      Last        : Asis.Element;
      Current     : Asis.Element;
      Image       : constant Wide_String :=
        Element_Utils.Compound_Name_Image (Compount_Name);
   begin
      if Expression_Kind (Compount_Name.all) = An_Operator_Symbol then
         return To_Defining_Operator_Symbol (Compount_Name);
      elsif not Is_List (Compount_Name.all) then
--      elsif Compount_Name.all not in List_Node then
         return Compount_Name;
      end if;

      Identifiers := List (Compount_Name);

      Last := Get_Item (Identifiers, Length (Identifiers.all));
      Last := To_Defining_Identifier (Last);

      if Length (Identifiers.all) = 1 then
         Unit_Name := Last;
      else
         Current := Get_Item (Identifiers, 1);

         for I in 2 .. Length (Identifiers.all) - 1 loop
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

         declare
            Def_Name : constant Defining_Expanded_Name_Ptr :=
              new Defining_Expanded_Name_Node;
         begin
            Set_Defining_Prefix (Def_Name.all, Current);
            Set_Start_Position (Def_Name.all, Start_Position (Current.all));
            Set_Defining_Selector (Def_Name.all, Last);
            Set_End_Position (Def_Name.all, End_Position (Last.all));
            Set_Defining_Name_Image (Def_Name.all, Image);
            Unit_Name := Asis.Element (Def_Name);
         end;

         while Length (Identifiers.all) > 1 loop
            Current := Get_Item (Identifiers, 1);
            Remove (Identifiers.all, Current);
         end loop;
      end if;

      return Unit_Name;
   end To_Defining_Unit_Name;

   ------------------------
   -- To_Expression_List --
   ------------------------

   function To_Expression_List (Item : Asis.Element) return Asis.Element is
      use Asis.Gela.Errors;
      use Lists.Primary_Expression_Lists;
      use Lists.Primary_Association_Lists;

      Args   : constant Lists.Primary_Association_Lists.List :=
        Lists.Primary_Association_Lists.List (Item);

      Result : constant Lists.Primary_Expression_Lists.List :=
        new Lists.Primary_Expression_Lists.List_Node;
   begin
      for I in 1 .. Length (Args.all) loop
         declare
            Association : constant Asis.Element := Get_Item (Args, I);
            Formal      : constant Asis.Element_List :=
              Record_Component_Choices (Association.all);
            Actual      : constant Asis.Element :=
              Component_Expression (Association.all);
         begin
            if Formal'Length > 0 then
               Report (Item, -- Formal (1),
                       Error_Syntax_Assoc_In_Attribute);
            end if;

            --  Set_Component_Expression (Association, Nil_Element);
            Add (Result.all, Actual);
         end;
      end loop;

      return Asis.Element (Result);
   end To_Expression_List;

   --------------------------
   -- To_Deferred_Constant --
   --------------------------

   procedure To_Deferred_Constant (Element : in out Asis.Element) is
      use Asis.Gela.Elements.Decl;

      Node    : Constant_Declaration_Node renames
        Constant_Declaration_Node (Element.all);
      Result : constant Deferred_Constant_Declaration_Ptr :=
        new Deferred_Constant_Declaration_Node;
   begin
      Element_Utils.Copy_Element (Element, Asis.Element (Result));
      Set_Object_Declaration_Subtype
        (Result.all, Object_Declaration_Subtype (Element.all));
      Elements.Decl.Set_Trait_Kind (Result.all, Trait_Kind (Element.all));
      Set_Names (Result.all, Names_List (Node));
      Set_Declaration_Origin (Result.all, Declaration_Origin (Element.all));
      Element := Asis.Element (Result);
   end To_Deferred_Constant;

end Asis.Gela.Normalizer.Utils;


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
