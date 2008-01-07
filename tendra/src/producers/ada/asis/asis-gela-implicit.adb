with XASIS.Utils;
with XASIS.Types;
with Asis.Gela.Classes;
with Asis.Declarations;
with Asis.Gela.Lists;
with Asis.Gela.Elements;
with Asis.Gela.Elements.Decl;
with Asis.Gela.Elements.Expr;
with Asis.Gela.Element_Utils;
with Asis.Gela.Elements.Def_Names;
with Asis.Gela.Elements.Defs.Types;

package body Asis.Gela.Implicit is

   package S renames Standard;

   procedure Process_Standard (Unit : Asis.Compilation_Unit);

   procedure Find_Declaration
     (Unit   : in     Asis.Compilation_Unit;
      Result :    out Asis.Declaration;
      Name   : in     Program_Text);

   procedure Init_Implicit
     (Element : in out Elements.Base_Element_Node'Class;
      Parent  : in     Asis.Element);

   function Is_Root (Decl : Asis.Declaration) return S.Boolean;

   procedure Make_Operation
     (Point    : in out Visibility.Point;
      Decl     : Asis.Declaration;
      Name     : Wide_String;
      Args     : Positive := 2;
      Result   : Asis.Declaration := Asis.Nil_Element;
      Right    : Asis.Declaration := Asis.Nil_Element;
      Left     : Asis.Declaration := Asis.Nil_Element;
      Dispatch : Boolean := False);

   function Need_Logical  (Tipe : Classes.Type_Info) return S.Boolean;
   function Need_Ordering (Tipe : Classes.Type_Info) return S.Boolean;

   procedure Hide_Implementation_Defined
     (Decl   : in     Asis.Declaration);

   procedure Hide_Implementation_Defined
     (Unit   : in     Asis.Compilation_Unit;
      Name   : in     Program_Text);

   The_System_Address          : Asis.Declaration;
   The_System_Bit_Order        : Asis.Declaration;
   The_Task_Id                 : Asis.Declaration;
   The_Exception_Id            : Asis.Declaration;
   The_Root_Storage_Pool       : Asis.Declaration;
   The_Tag                     : Asis.Declaration;
   The_Root_Stream_Type        : Asis.Declaration;

   The_Universal_Integer   : Asis.Declaration;
   The_Universal_Real      : Asis.Declaration;
   The_Universal_Fixed     : Asis.Declaration;
   The_Universal_Access    : Asis.Declaration;
   The_Root_Integer        : Asis.Declaration;
   The_Root_Real           : Asis.Declaration;
   The_String              : Asis.Declaration;
   The_Wide_String         : Asis.Declaration;
   The_Wide_Wide_String    : Asis.Declaration;
   The_Float               : Asis.Declaration;
   The_Boolean             : Asis.Declaration;
   The_Duration            : Asis.Declaration;
   The_Integer             : Asis.Declaration;
   The_Natural             : Asis.Declaration;
   The_Wide_Character      : Asis.Declaration;
   The_Wide_Wide_Character : Asis.Declaration;
   The_Character           : Asis.Declaration;

   ----------------------
   -- Create_Root_Type --
   ----------------------

   procedure Create_Root_Type
     (Unit   : in     Asis.Compilation_Unit;
      Kind   : in     Root_Type_Kinds;
      Result :    out Asis.Declaration;
      Before : in     Program_Text)
   is
      use Asis.Gela.Elements.Decl;
      use Asis.Gela.Elements.Defs.Types;

      The_Unit         : constant Asis.Declaration :=
        Unit_Declaration (Unit.all);
      Root_Definition  : constant Root_Type_Ptr := new Root_Type_Node;
      Root_Declaration : constant Ordinary_Type_Declaration_Ptr :=
        new Ordinary_Type_Declaration_Node;
   begin
      Result := Element (Root_Declaration);
      Init_Implicit (Root_Declaration.all, The_Unit);
      Set_Type_Declaration_View (Root_Declaration.all,
        Element (Root_Definition));

      Set_Declaration_Origin (Root_Declaration.all,
        An_Implicit_Predefined_Declaration);

      Init_Implicit (Root_Definition.all, Result);
      Set_Root_Type_Kind (Root_Definition.all, Kind);
      Element_Utils.Add_To_Visible (The_Unit, Result, Before);
   end Create_Root_Type;

   ----------------------
   -- Find_Declaration --
   ----------------------

   procedure Find_Declaration
     (Unit   : in     Asis.Compilation_Unit;
      Result :    out Asis.Declaration;
      Name   : in     Program_Text)
   is
      use Asis.Declarations;
      The_Unit : constant Asis.Declaration := Unit_Declaration (Unit.all);
      Items    : constant Asis.Declarative_Item_List :=
        Visible_Part_Declarative_Items (The_Unit);
   begin
      for I in Items'Range loop
         if Element_Kind (Items (I).all) = A_Declaration
           and then XASIS.Utils.Has_Defining_Name (Items (I), Name)
         then
            Result := Items (I);
            return;
         end if;
      end loop;
   end Find_Declaration;

   ------------------
   -- Hide_Element --
   ------------------

   procedure Hide_Element (Item : Asis.Expression) is
      use Asis.Gela.Elements;
   begin
      if Assigned (Item) then
         Set_Is_Part_Of_Implicit (Base_Element_Node (Item.all), True);
      end if;
   end Hide_Element;

   ---------------------------------
   -- Hide_Implementation_Defined --
   ---------------------------------

   procedure Hide_Implementation_Defined (Decl : Asis.Declaration) is
      Def : Asis.Definition;
   begin
      case Declaration_Kind (Decl.all) is
         when An_Ordinary_Type_Declaration
           | A_Subtype_Declaration=>

            Def := Type_Declaration_View (Decl.all);

            case Definition_Kind (Def.all) is
               when A_Subtype_Indication =>

                  Def := Subtype_Constraint (Def.all);
                  Hide_Element (Lower_Bound (Def.all));
                  Hide_Element (Upper_Bound (Def.all));

               when A_Type_Definition =>
                  case Type_Definition_Kind (Def.all) is
                     when An_Enumeration_Type_Definition =>
                        declare
                           List : constant Asis.Declaration_List :=
                             Enumeration_Literal_Declarations (Def.all);
                        begin
                           for J in List'Range loop
                              Hide_Element (List (J));
                           end loop;
                        end;
                     when A_Signed_Integer_Type_Definition =>
                        Def := Integer_Constraint (Def.all);
                        Hide_Element (Lower_Bound (Def.all));
                        Hide_Element (Upper_Bound (Def.all));

                     when A_Modular_Type_Definition =>
                        Hide_Element (Mod_Static_Expression (Def.all));

                     when A_Floating_Point_Definition =>
                        Hide_Element (Digits_Expression (Def.all));
                        Def := Real_Range_Constraint (Def.all);

                        if Assigned (Def) then
                           Hide_Element (Lower_Bound (Def.all));
                           Hide_Element (Upper_Bound (Def.all));
                        end if;

                     when An_Ordinary_Fixed_Point_Definition =>
                        Hide_Element (Delta_Expression (Def.all));
                        Def := Real_Range_Constraint (Def.all);

                        if Assigned (Def) then
                           Hide_Element (Lower_Bound (Def.all));
                           Hide_Element (Upper_Bound (Def.all));
                        end if;

                     when A_Decimal_Fixed_Point_Definition =>
                        Hide_Element (Digits_Expression (Def.all));
                        Hide_Element (Delta_Expression (Def.all));
                        Def := Real_Range_Constraint (Def.all);

                        if Assigned (Def) then
                           Hide_Element (Lower_Bound (Def.all));
                           Hide_Element (Upper_Bound (Def.all));
                        end if;

                     when others =>
                        raise Internal_Error;
                  end case;

               when others =>
                  raise Internal_Error;
            end case;

         when A_Constant_Declaration
           | An_Integer_Number_Declaration
           | A_Real_Number_Declaration =>

            Hide_Element (Initialization_Expression (Decl.all));

         when others =>
            raise Internal_Error;
      end case;
   end Hide_Implementation_Defined;

   ---------------------------------
   -- Hide_Implementation_Defined --
   ---------------------------------

   procedure Hide_Implementation_Defined
     (Unit   : in     Asis.Compilation_Unit;
      Name   : in     Program_Text)
   is
      Decl : Asis.Declaration;
   begin
      Find_Declaration (Unit, Decl, Name);
      Hide_Implementation_Defined (Decl);
   end Hide_Implementation_Defined;

   -------------
   -- Is_Root --
   -------------

   function Is_Root (Decl : Asis.Declaration) return S.Boolean is
      Def : constant Asis.Definition := Type_Declaration_View (Decl.all);
   begin
      return Type_Definition_Kind (Def.all) = Asis.A_Root_Type_Definition;
   end Is_Root;

   -----------------------------
   -- Make_Not_Equal_Operator --
   -----------------------------

   procedure Make_Not_Equal_Operator
     (Equal : Asis.Declaration;
      Point : in out Visibility.Point)
   is
      use Asis.Gela.Classes;
      use Asis.Declarations;

      Dispatch   : Boolean := False;
      Left_Info  : Type_Info;
      Right_Info : Type_Info;
      List : constant Asis.Parameter_Specification_List :=
        Parameter_Profile (Equal);
   begin
      Left_Info  := Type_Of_Declaration (List (1), Equal);

      if List'Length = 2 then
         Right_Info := Type_Of_Declaration (List (2), Equal);
      else
         Right_Info := Left_Info;
      end if;

      if Declaration_Kind (Equal.all)
        in A_Procedure_Declaration .. A_Function_Declaration
      then
         Dispatch := Is_Dispatching_Operation (Equal.all);
      end if;

      Make_Operation
        (Point    => Point,
         Decl     => Equal,
         Name     => """/=""",
         Result   => The_Boolean,
         Right    => Get_Declaration (Right_Info),
         Left     => Get_Declaration (Left_Info),
         Dispatch => Dispatch);
   end Make_Not_Equal_Operator;

   --------------------
   -- Make_Operation --
   --------------------

   procedure Make_Operation
     (Point    : in out Visibility.Point;
      Decl     : Asis.Declaration;
      Name     : Wide_String;
      Args     : Positive := 2;
      Result   : Asis.Declaration := Asis.Nil_Element;
      Right    : Asis.Declaration := Asis.Nil_Element;
      Left     : Asis.Declaration := Asis.Nil_Element;
      Dispatch : Boolean := False)
   is
      use Asis.Gela.Lists;
      use XASIS.Utils;
      use Asis.Gela.Elements;
      use Asis.Gela.Element_Utils;
      use Asis.Gela.Elements.Decl;
      use Asis.Gela.Elements.Defs;
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Elements.Def_Names;

      D_Name : constant Asis.Element_List := Names (Decl.all);
      Img    : constant Asis.Program_Text := Declaration_Direct_Name (Decl);
      Def    : Asis.Element;
      Func   : constant Function_Declaration_Ptr :=
        new Function_Declaration_Node;
      Ident  : Identifier_Ptr;
      Mark   : Subtype_Indication_Ptr;
      Param  : Parameter_Specification_Ptr;
      P_Name : Defining_Identifier_Ptr;
      F_Name : constant Defining_Operator_Symbol_Ptr :=
        new Defining_Operator_Symbol_Node;
      Items  : Primary_Defining_Name_Lists.List :=
        new Primary_Defining_Name_Lists.List_Node;
      Params : constant Primary_Parameter_Lists.List :=
        new Primary_Parameter_Lists.List_Node;

      Overriden    : Boolean;
      Decl_Is_Type : Boolean := True;
   begin
      case Declaration_Kind (Decl.all) is
         when An_Ordinary_Type_Declaration
           | A_Task_Type_Declaration
           | A_Protected_Type_Declaration
           | A_Private_Type_Declaration
           | A_Private_Extension_Declaration
           | A_Subtype_Declaration
           | A_Formal_Type_Declaration =>

            Def          := Type_Declaration_View (Decl.all);
            Decl_Is_Type := True;
            Set_Corresponding_Type (Func.all, Def);

         when A_Function_Declaration =>
            Decl_Is_Type := False;
            Set_Corresponding_Equality_Operator (Func.all, Decl);
            Set_Corresponding_Equality_Operator
              (Function_Declaration_Node (Decl.all), Asis.Element (Func));

         when A_Formal_Function_Declaration =>
            Decl_Is_Type := False;

         when others =>
            raise Internal_Error;
      end case;

      Init_Implicit (Func.all, Decl);
      Set_Declaration_Origin (Func.all, An_Implicit_Predefined_Declaration);

      Init_Implicit (F_Name.all, Asis.Element (Func));
      Set_Defining_Name_Image (F_Name.all, Name);
      Elements.Def_Names.Set_Operator_Kind (F_Name.all,
        Operator_Kind (Name, Args = 2));

      Primary_Defining_Name_Lists.Add (Items.all, Asis.Element (F_Name));

      Set_Names (Func.all, Asis.Element (Items));

      for I in 1 .. Args loop
         Param := new Parameter_Specification_Node;
         Init_Implicit (Param.all, Asis.Element (Func));
         Set_Trait_Kind (Param.all, An_Ordinary_Trait);
         Set_Declaration_Origin (Param.all,
           An_Implicit_Predefined_Declaration);

         P_Name := new Defining_Identifier_Node;
         Init_Implicit (P_Name.all, Asis.Element (Param));

         if I = Args then
            Set_Defining_Name_Image (P_Name.all, "Right");
         else
            Set_Defining_Name_Image (P_Name.all, "Left");
         end if;

         Items := new Primary_Defining_Name_Lists.List_Node;
         Primary_Defining_Name_Lists.Add (Items.all, Asis.Element (P_Name));

         Set_Names (Param.all, Asis.Element (Items));
         Set_Mode_Kind (Param.all, A_Default_In_Mode);

         Mark := new Subtype_Indication_Node;
         Init_Implicit (Mark.all, Asis.Element (Param));

         Ident := new Identifier_Node;
         Init_Implicit (Ident.all, Asis.Element (Mark));

         if I = Args and then Assigned (Right) then
            declare
               Right_Img : constant Asis.Program_Text :=
                 Declaration_Direct_Name (Right);
               R_Name : constant Asis.Element_List := Names (Right.all);
            begin
               Set_Name_Image (Ident.all, Right_Img);

               if R_Name'Length > 0 then
                  Add_Defining_Name (Asis.Element (Ident), R_Name (1));
               end if;

               Set_Name_Declaration (Asis.Element (Ident), Right);
            end;
         elsif I /= Args and then Assigned (Left) then
            declare
               Left_Img : constant Asis.Program_Text :=
                 Declaration_Direct_Name (Left);
               L_Name : constant Asis.Element_List := Names (Left.all);
            begin
               Set_Name_Image (Ident.all, Left_Img);

               if L_Name'Length > 0 then
                  Add_Defining_Name (Asis.Element (Ident), L_Name (1));
               end if;

               Set_Name_Declaration (Asis.Element (Ident), Left);
            end;
         else
            Set_Name_Image (Ident.all, Img);

            if D_Name'Length > 0 then
               Add_Defining_Name (Asis.Element (Ident), D_Name (1));
            end if;

            Set_Name_Declaration (Asis.Element (Ident), Decl);
         end if;

         Set_Subtype_Mark (Mark.all, Asis.Element (Ident));
         Set_Object_Declaration_Subtype (Param.all, Asis.Element (Mark));

         Primary_Parameter_Lists.Add (Params.all, Asis.Element (Param));
      end loop;

      Set_Parameter_Profile (Func.all, Asis.Element (Params));
      Set_Is_Dispatching_Operation (Func.all, Dispatch);

      Mark := new Subtype_Indication_Node;
      Init_Implicit (Mark.all, Asis.Element (Func));

      Ident := new Identifier_Node;
      Init_Implicit (Ident.all, Asis.Element (Mark));

      if not Assigned (Result) then
         Set_Name_Image (Ident.all, Img);

         if D_Name'Length > 0 then
            Add_Defining_Name (Asis.Element (Ident), D_Name (1));
         end if;

         Set_Name_Declaration (Asis.Element (Ident), Decl);
      else
         declare
            Result_Img : constant Asis.Program_Text :=
              Declaration_Direct_Name (Result);
            R_Name     : constant Asis.Element_List := Names (Result.all);
         begin
            Set_Name_Image (Ident.all, Result_Img);

            if R_Name'Length > 0 then
               Add_Defining_Name (Asis.Element (Ident), R_Name (1));
            end if;

            Set_Name_Declaration (Asis.Element (Ident), Result);
         end;
      end if;

      Set_Subtype_Mark (Mark.all, Asis.Element (Ident));
      Set_Result_Subtype (Func.all, Asis.Element (Mark));

      Visibility.New_Implicit_Declaration
        (Asis.Element (Func), Point, Decl, Overriden);

      if not Overriden and then Decl_Is_Type then
         Element_Utils.Add_Type_Operator (Def, Asis.Element (Func));
      end if;
   end Make_Operation;

   ---------------------
   -- Make_Operations --
   ---------------------

   procedure Make_Operations
     (Decl  : Asis.Declaration;
      Point : in out Visibility.Point)
   is
      use Asis.Gela.Classes;

      Comp : Asis.Declaration;
      Tipe : constant Type_Info := Type_From_Declaration (Decl, Decl);
   begin
      if Is_Universal (Tipe) then
         if Is_Fixed_Point (Tipe) then
            Make_Operation (Point, Decl, """*""");
            Make_Operation (Point, Decl, """/""");
         elsif Is_Access (Tipe) then
            Make_Operation (Point, Decl, """=""", Result => The_Boolean);
            Make_Operation (Point, Decl, """/=""", Result => The_Boolean);
         end if;
         return;
      end if;

      if Need_Logical (Tipe) then
         Make_Operation (Point, Decl, """and""");
         Make_Operation (Point, Decl, """or""");
         Make_Operation (Point, Decl, """xor""");
         Make_Operation (Point, Decl, """not""", 1);
      end if;
      if not Is_Limited (Tipe) then
         Make_Operation (Point, Decl, """=""", Result => The_Boolean,
                         Dispatch => Is_Tagged (Tipe));
         Make_Operation (Point, Decl, """/=""", Result => The_Boolean,
                         Dispatch => Is_Tagged (Tipe));
      end if;
      if Need_Ordering (Tipe) then
         Make_Operation (Point, Decl, """<""", Result => The_Boolean);
         Make_Operation (Point, Decl, """<=""", Result => The_Boolean);
         Make_Operation (Point, Decl, """>""", Result => The_Boolean);
         Make_Operation (Point, Decl, """>=""", Result => The_Boolean);
      end if;
      if Is_Numeric (Tipe) then
         Make_Operation (Point, Decl, """+""");
         Make_Operation (Point, Decl, """-""");
         Make_Operation (Point, Decl, """+""", 1);
         Make_Operation (Point, Decl, """-""", 1);
         Make_Operation (Point, Decl, """abs""", 1);
      end if;
      if Is_Array (Tipe, 1) then
         Comp := Get_Declaration (Get_Array_Element_Type (Tipe));
         if not Is_Limited (Tipe) then
            Make_Operation (Point, Decl, """&""");
            Make_Operation (Point, Decl, """&""", Right => Comp);
            Make_Operation (Point, Decl, """&""", Left => Comp);
            Make_Operation (Point, Decl, """&""", Right => Comp, Left => Comp);
         end if;
      end if;
      if Is_Integer (Tipe) then
         Make_Operation (Point, Decl, """*""");
         Make_Operation (Point, Decl, """/""");
         Make_Operation (Point, Decl, """mod""");
         Make_Operation (Point, Decl, """rem""");
         Make_Operation (Point, Decl, """**""", Right => The_Natural);
      elsif Is_Float_Point (Tipe) then
         Make_Operation (Point, Decl, """*""");
         Make_Operation (Point, Decl, """/""");
         Make_Operation (Point, Decl, """**""", Right => The_Integer);
         if Is_Root (Decl) then
            Make_Operation (Point, Decl, """*""", Right => The_Root_Integer);
            Make_Operation (Point, Decl, """*""", Left => The_Root_Integer);
            Make_Operation (Point, Decl, """/""", Right => The_Root_Integer);
         end if;
      elsif Is_Fixed_Point (Tipe) then
         Make_Operation (Point, Decl, """*""", Right => The_Integer);
         Make_Operation (Point, Decl, """*""", Left => The_Integer);
         Make_Operation (Point, Decl, """/""", Right => The_Integer);
      end if;
   end Make_Operations;

   ------------------
   -- Need_Logical --
   ------------------

   function Need_Logical (Tipe : Classes.Type_Info) return S.Boolean is
      use Asis.Gela.Classes;
   begin
      if Is_Boolean (Tipe) then
         return True;
      elsif Is_Modular_Integer (Tipe) then
         return True;
      elsif Is_Boolean_Array (Tipe) then
         return True;
      end if;
      return False;
   end Need_Logical;

   -------------------
   -- Need_Ordering --
   -------------------

   function Need_Ordering (Tipe : Classes.Type_Info) return S.Boolean is
      use Asis.Gela.Classes;
   begin
      if Is_Scalar (Tipe) then
         return True;
      elsif Is_Discrete_Array (Tipe) then
         return True;
      end if;
      return False;
   end Need_Ordering;

   -------------------
   -- Init_Implicit --
   -------------------

   procedure Init_Implicit
     (Element : in out Elements.Base_Element_Node'Class;
      Parent  : in     Asis.Element)
   is
      use Asis.Gela.Elements;

      The_Unit : constant Asis.Compilation_Unit :=
        Enclosing_Compilation_Unit (Parent.all);
   begin
      Set_Enclosing_Element (Element, Parent);
      Set_Is_Part_Of_Implicit (Element, True);
      Set_Start_Position (Element, (1, 1));
      Set_End_Position (Element, (0, 0));
      Set_Enclosing_Compilation_Unit (Element, The_Unit);
   end Init_Implicit;

   ----------------------
   -- Process_Standard --
   ----------------------

   procedure Process_Standard (Unit : Asis.Compilation_Unit) is
   begin
      Find_Declaration (Unit, The_String,   "String");
      Find_Declaration (Unit, The_Wide_String,        "Wide_String");
      Find_Declaration (Unit, The_Wide_Wide_String,   "Wide_Wide_String");
      Find_Declaration (Unit, The_Boolean,  "Boolean");
      Find_Declaration (Unit, The_Integer,  "Integer");
      Find_Declaration (Unit, The_Natural,  "Natural");
      Find_Declaration (Unit, The_Duration, "Duration");
      Find_Declaration (Unit, The_Float,    "Float");
      Find_Declaration (Unit, The_Character,           "Character");
      Find_Declaration (Unit, The_Wide_Character,      "Wide_Character");
      Find_Declaration (Unit, The_Wide_Wide_Character, "Wide_Wide_Character");

      Create_Root_Type (Unit, A_Universal_Integer_Definition,
                        The_Universal_Integer, "Integer");

      Create_Root_Type (Unit, A_Root_Integer_Definition,
                        The_Root_Integer, "Integer");

      Create_Root_Type (Unit, A_Universal_Real_Definition,
                        The_Universal_Real, "Float");

      Create_Root_Type (Unit, A_Universal_Fixed_Definition,
                        The_Universal_Fixed, "Float");

      Create_Root_Type (Unit, A_Root_Real_Definition,
                        The_Root_Real, "Float");

      Create_Root_Type (Unit, A_Universal_Access_Definition,
                        The_Universal_Access, "Character");

      Hide_Implementation_Defined (The_Character);
      Hide_Implementation_Defined (The_Wide_Character);
      Hide_Implementation_Defined (The_Wide_Wide_Character);
      Hide_Implementation_Defined (The_Integer);
      Hide_Implementation_Defined (The_Float);
      Hide_Implementation_Defined (The_Duration);

      XASIS.Types.Initialize
        (Universal_Integer   => The_Universal_Integer,
         Universal_Real      => The_Universal_Real,
         Universal_Fixed     => The_Universal_Fixed,
         Universal_Access    => The_Universal_Access,
         Root_Integer        => The_Root_Integer,
         Root_Real           => The_Root_Real,
         String              => The_String,
         Wide_String         => The_Wide_String,
         Wide_Wide_String    => The_Wide_Wide_String,
         Float               => The_Float,
         Boolean             => The_Boolean,
         Duration            => The_Duration,
         Integer             => The_Integer,
         Natural             => The_Natural,
         Wide_Wide_Character => The_Wide_Wide_Character,
         Wide_Character      => The_Wide_Character,
         Character           => The_Character);
   end Process_Standard;

   ------------------
   -- Process_Unit --
   ------------------

   procedure Process_Unit (Unit : Asis.Compilation_Unit) is
      use XASIS.Utils;
      Name : constant Wide_String := Unit_Full_Name (Unit.all);
   begin
      if Are_Equal_Identifiers (Name, "Standard") then

         Process_Standard (Unit);

      elsif Are_Equal_Identifiers (Name, "System") then

         Find_Declaration (Unit, The_System_Address,   "Address");
         Find_Declaration (Unit, The_System_Bit_Order, "Bit_Order");
         XASIS.Types.Initialize
           (System_Address   => The_System_Address,
            System_Bit_Order => The_System_Bit_Order);
         Hide_Implementation_Defined (Unit, "System_Name");
         Hide_Implementation_Defined (Unit, "Min_Int");
         Hide_Implementation_Defined (Unit, "Max_Int");
         Hide_Implementation_Defined (Unit, "Max_Binary_Modulus");
         Hide_Implementation_Defined (Unit, "Max_Nonbinary_Modulus");
         Hide_Implementation_Defined (Unit, "Max_Base_Digits");
         Hide_Implementation_Defined (Unit, "Max_Digits");
         Hide_Implementation_Defined (Unit, "Max_Mantissa");
         Hide_Implementation_Defined (Unit, "Fine_Delta");
         Hide_Implementation_Defined (Unit, "Tick");
         Hide_Implementation_Defined (Unit, "Storage_Unit");
         Hide_Implementation_Defined (Unit, "Word_Size");
         Hide_Implementation_Defined (Unit, "Memory_Size");
         Hide_Implementation_Defined (Unit, "Any_Priority");
         Hide_Implementation_Defined (Unit, "Priority");

      elsif Are_Equal_Identifiers (Name, "System.Storage_Pools") then

         Find_Declaration (Unit, The_Root_Storage_Pool, "Root_Storage_Pool");
         XASIS.Types.Initialize
           (Root_Storage_Pool => The_Root_Storage_Pool);

      elsif Are_Equal_Identifiers (Name, "System.Storage_Elements") then
         Hide_Implementation_Defined (Unit, "Storage_Offset");
         Hide_Implementation_Defined (Unit, "Storage_Element");
         Hide_Implementation_Defined (Unit, "Integer_Address");

      elsif Are_Equal_Identifiers (Name, "Interfaces.C") then
         Hide_Implementation_Defined (Unit, "CHAR_BIT");
         Hide_Implementation_Defined (Unit, "SCHAR_MIN");
         Hide_Implementation_Defined (Unit, "SCHAR_MAX");
         Hide_Implementation_Defined (Unit, "UCHAR_MAX");
         Hide_Implementation_Defined (Unit, "int");
         Hide_Implementation_Defined (Unit, "short");
         Hide_Implementation_Defined (Unit, "long");
         Hide_Implementation_Defined (Unit, "unsigned");
         Hide_Implementation_Defined (Unit, "unsigned_short");
         Hide_Implementation_Defined (Unit, "unsigned_long");
         Hide_Implementation_Defined (Unit, "ptrdiff_t");
         Hide_Implementation_Defined (Unit, "size_t");
         Hide_Implementation_Defined (Unit, "C_float");
         Hide_Implementation_Defined (Unit, "double");
         Hide_Implementation_Defined (Unit, "long_double");

      elsif Are_Equal_Identifiers (Name, "Ada.Command_Line") then
         Hide_Implementation_Defined (Unit, "Exit_Status");

      elsif Are_Equal_Identifiers (Name, "Ada.Direct_IO")
        or else Are_Equal_Identifiers (Name, "Ada.Streams.Stream_IO")
      then
         Hide_Implementation_Defined (Unit, "Count");

      elsif Are_Equal_Identifiers (Name, "Ada.Text_IO")
        or else Are_Equal_Identifiers (Name, "Ada.Wide_Text_IO")
      then
         Hide_Implementation_Defined (Unit, "Count");
         Hide_Implementation_Defined (Unit, "Field");

      elsif Are_Equal_Identifiers (Name, "Ada.Numerics.Discrete_Random")
        or else Are_Equal_Identifiers (Name, "Ada.Numerics.Float_Random")
      then
         Hide_Implementation_Defined (Unit, "Max_Image_Width");

      elsif Are_Equal_Identifiers (Name, "Ada.Storage_IO") then
         Hide_Implementation_Defined (Unit, "Buffer_Size");

      elsif Are_Equal_Identifiers (Name, "Ada.Streams") then
         Hide_Implementation_Defined (Unit, "Stream_Element");
         Hide_Implementation_Defined (Unit, "Stream_Element_Offset");
         Find_Declaration (Unit, The_Root_Stream_Type, "Root_Stream_Type");
         XASIS.Types.Initialize_Root_Stream (The_Root_Stream_Type);
      elsif Are_Equal_Identifiers (Name, "Ada.Exceptions") then
         Find_Declaration (Unit, The_Exception_Id, "Exception_Id");
         XASIS.Types.Initialize_Exception_Id (The_Exception_Id);
      elsif Are_Equal_Identifiers (Name, "Ada.Task_Identification") then
         Find_Declaration (Unit, The_Task_Id, "Task_Id");
         XASIS.Types.Initialize_Task_Id (The_Task_Id);
      elsif Are_Equal_Identifiers (Name, "Ada.Tags") then
         Find_Declaration (Unit, The_Tag, "Tag");
         XASIS.Types.Initialize_Tag (The_Tag);
      end if;
   end Process_Unit;

end Asis.Gela.Implicit;



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
