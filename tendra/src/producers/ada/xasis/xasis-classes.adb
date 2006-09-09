with Asis.Elements;
with Asis.Expressions;
with Asis.Definitions;
with Asis.Declarations;
with XASIS.Types;
with XASIS.Utils;
with XASIS.Static;

package body XASIS.Classes is

   use Asis;

   function Has_Character_Literal (Tipe : Asis.Declaration) return Boolean;
   function Is_String_Array (Def : Asis.Definition) return Boolean;

   function Type_Of_Expression (Expr : Asis.Expression) return Type_Info;
   function Is_Child_Of (Child, Parent : Type_Info) return Boolean;

   function First_Subtype (Info : Type_Info) return Type_Info;

   function Base_Type (Info : Type_Info) return Type_Info;

   ---------------
   -- Base_Type --
   ---------------

   function Base_Type (Info : Type_Info) return Type_Info is
      use Asis.Elements;

      Result : Type_Info := Info;
      Decl   : Asis.Declaration;
   begin
      if Is_Incomplete (Result) then
         Result.Element := Utils.Completion_For_Declaration (Result.Element);
         Result := Type_From_Declaration (Result.Element);
      end if;

      while not Result.Definition
        and then Utils.Is_Completion (Result.Element)
      loop
         Decl := Utils.Declaration_For_Completion (Result.Element);
         exit when Declaration_Kind (Decl) = An_Incomplete_Type_Declaration;
         Result := Type_From_Declaration (Decl);
      end loop;

      return Result;
   end Base_Type;

   -------------------
   -- First_Subtype --
   -------------------

   function First_Subtype (Info : Type_Info) return Type_Info is
      use Asis.Elements;
      use Asis.Declarations;

      Result : Type_Info := Info;
      Ind    : Asis.Definition;
      Mark   : Asis.Expression;
   begin
      while not Result.Definition
        and then Declaration_Kind (Result.Element) = A_Subtype_Declaration
      loop
         Ind  := Type_Declaration_View (Result.Element);
         Mark := Asis.Definitions.Subtype_Mark (Ind);
         Result := Type_From_Subtype_Mark (Mark);
      end loop;

      return Result;
   end First_Subtype;

   -----------------
   -- Class_Range --
   -----------------

   package body Class_Range is

      --------------
      -- Is_Class --
      --------------

      function Is_Class (Tipe : Asis.Declaration) return Boolean is
      begin
         return Is_Class (Type_From_Declaration (Tipe));
      end Is_Class;

      --------------
      -- Is_Class --
      --------------

      function Is_Class (Info : Type_Info) return Boolean is
      begin
         if With_Access and then Info.Is_Access then
            return True;
         end if;
         return Info.Class_Kind in Lower .. Upper;
      end Is_Class;

   end Class_Range;

   package Character_Class is
     new Class_Range (A_Character, A_Character);

   package Boolean_Class is
     new Class_Range (A_Boolean,   A_Boolean);

   package Signed_Class is
     new Class_Range (A_Signed_Integer, A_Signed_Integer);

   package Modular_Class is
     new Class_Range (A_Modular_Integer, A_Modular_Integer);

   package Float_Class is
     new Class_Range (A_Float_Point, A_Float_Point);

   package Ordinary_Fixed_Class is
     new Class_Range (A_Ordinary_Fixed_Point, A_Ordinary_Fixed_Point);

   package Decimal_Fixed_Class is
     new Class_Range (A_Decimal_Fixed_Point, A_Decimal_Fixed_Point);

   package Procedure_Access_Class is
     new Class_Range (A_Procedure_Access, A_Procedure_Access);

   package Function_Access_Class is
     new Class_Range (A_Function_Access, A_Function_Access);

   package Constant_Access_Class is
     new Class_Range (A_Constant_Access, A_Constant_Access);

   package Variable_Access_Class is
     new Class_Range (A_Variable_Access, A_Variable_Access, True);

   package String_Class is
     new Class_Range (A_String, A_String);

   package Record_Class is
     new Class_Range (A_Untagged_Record, A_Untagged_Record);

   package Tagged_Class is
     new Class_Range (A_Tagged, A_Tagged);

   package Task_Class is
     new Class_Range (A_Task, A_Task);

   package Protected_Class is
     new Class_Range (A_Protected, A_Protected);

   package Elementary_Class is
     new Class_Range (An_Elementary'First, An_Elementary'Last);

   package Scalar_Class is
     new Class_Range (A_Scalar'First, A_Scalar'Last);

   package Discrete_Class is
     new Class_Range (A_Discrete'First, A_Discrete'Last);

   package Enumeration_Class is
     new Class_Range (An_Enumeration'First, An_Enumeration'Last);

   package Integer_Class is
     new Class_Range (An_Integer'First, An_Integer'Last);

   package Real_Class is
     new Class_Range (A_Real'First, A_Real'Last);

   package Fixed_Class is
     new Class_Range (A_Fixed_Point'First, A_Fixed_Point'Last);

   package Numeric_Class is
     new Class_Range (A_Numeric'First, A_Numeric'Last);

   package Subprogram_Access_Class is
     new Class_Range (A_Subprogram_Access'First, A_Subprogram_Access'Last);

   package Object_Access_Class is
     new Class_Range (An_Object_Access'First, An_Object_Access'Last, True);

   package General_Access_Class is
     new Class_Range (A_General_Access'First, A_General_Access'Last, True);

   package Access_Class is
     new Class_Range (An_Access'First, An_Access'Last, True);

   package Composite_Class is
     new Class_Range (A_Composite'First, A_Composite'Last);

   package Array_Class is
     new Class_Range (An_Array'First, An_Array'Last);

   package Incomplete_Class is
     new Class_Range (An_Incomplete, An_Incomplete);

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image (Info : Type_Info) return Wide_String is
      use Asis.Elements;
      Img : constant Wide_String := Debug_Image (Info.Element) & ' ' &
        Class_Kinds'Wide_Image (Info.Class_Kind) & " Class_Wide " &
        Boolean'Wide_Image (Info.Class_Wide) & " Def " &
        Boolean'Wide_Image (Info.Definition) & " access " &
        Boolean'Wide_Image (Info.Is_Access);
   begin
      return Img;
   end Debug_Image;

   ----------------------
   -- Destination_Type --
   ----------------------

   function Destination_Type (Info : Type_Info) return Type_Info is
      use Asis.Definitions;
      use Asis.Declarations;
      Result : Type_Info;
      Def    : Asis.Definition;
      Mark   : Asis.Expression;
   begin
      if Info.Is_Access then
         Result := Info;
         Result.Is_Access := False;
      elsif Is_Object_Access (Info) then
         Def    := Type_Declaration_View (Info.Element);
         Def    := Asis.Definitions.Access_To_Object_Definition (Def);
         Mark   := Asis.Definitions.Subtype_Mark (Def);
         Result := Type_From_Subtype_Mark (Mark);
      end if;
      return Result;
   end Destination_Type;

   ----------------------------
   -- Get_Array_Element_Type --
   ----------------------------

   function Get_Array_Element_Type (Tipe : Type_Info) return Type_Info is
      use Asis.Definitions;
      use Asis.Declarations;
      Def  : Asis.Definition;
      Comp : Asis.Definition;
      Ind  : Asis.Definition;
   begin
      if Tipe.Definition then
         Def := Tipe.Element;
      else
         Def := Type_Declaration_View (Tipe.Element);
      end if;
      Comp := Array_Component_Definition (Def);
      Ind  := Component_Subtype_Indication (Comp);
      return Type_From_Indication (Ind);
   end Get_Array_Element_Type;

   --------------------------
   -- Get_Array_Index_Type --
   --------------------------

   function Get_Array_Index_Type
     (Info  : Type_Info;
      Index : Asis.List_Index := 1) return Type_Info
   is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;
      Def    : Asis.Definition;
      Mark   : Asis.Expression;
      Result : Type_Info;
   begin
      if Info.Definition then
         Def := Info.Element;
      else
         Def := Type_Declaration_View (Info.Element);
      end if;
      case Type_Kind (Def) is
         when An_Unconstrained_Array_Definition =>
            Mark := Index_Subtype_Definitions (Def) (Index);
            Result := Type_From_Subtype_Mark (Mark);
         when A_Constrained_Array_Definition =>
            Def := Discrete_Subtype_Definitions (Def) (Index);
            Result := Type_From_Discrete_Def (Def);
         when others =>
            raise XASIS_Error;
      end case;
      return Result;
   end Get_Array_Index_Type;

   ---------------------
   -- Get_Declaration --
   ---------------------

   function Get_Declaration (Info : Type_Info) return Asis.Declaration is
   begin
      if Info.Definition then
         return Asis.Nil_Element;
      else
         return Info.Element;
      end if;
   end Get_Declaration;

   --------------------
   -- Get_Definition --
   --------------------

   function Get_Definition (Info : Type_Info) return Asis.Definition is
      use Asis.Declarations;
   begin
      if Info.Definition then
         return Info.Element;
      else
         return Type_Declaration_View (Info.Element);
      end if;
   end Get_Definition;

   ---------------------------
   -- Has_Character_Literal --
   ---------------------------

   function Has_Character_Literal (Tipe : Asis.Declaration) return Boolean is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;
      List : constant Asis.Declaration_List :=
        Enumeration_Literal_Declarations (Tipe);
   begin
      for I in List'Range loop
         if Defining_Name_Kind (Names (List (I)) (1)) =
           A_Defining_Character_Literal
         then
            return True;
         end if;
      end loop;
      return False;
   end Has_Character_Literal;

   ---------------
   -- Is_Access --
   ---------------

   function Is_Access (Tipe : Asis.Declaration) return Boolean
      renames Access_Class.Is_Class;

   function Is_Access (Info : Type_Info) return Boolean
      renames Access_Class.Is_Class;

   -------------------------
   -- Is_Anonymous_Access --
   -------------------------

   function Is_Anonymous_Access (Info : Type_Info) return Boolean is
   begin
      return Info.Is_Access;
   end Is_Anonymous_Access;

   --------------
   -- Is_Array --
   --------------

   function Is_Array (Tipe : Asis.Declaration) return Boolean
      renames Array_Class.Is_Class;

   function Is_Array (Info : Type_Info) return Boolean
      renames Array_Class.Is_Class;

   --------------
   -- Is_Array --
   --------------

   function Is_Array
     (Info   : Type_Info;
      Length : Asis.List_Index) return Boolean
   is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;
      Def    : Asis.Definition;
   begin
      if Is_Array (Info) then
         if Info.Definition then
            Def := Info.Element;
         else
            Def := Type_Declaration_View (Info.Element);
         end if;
         case Type_Kind (Def) is
            when An_Unconstrained_Array_Definition =>
               return Length = Index_Subtype_Definitions (Def)'Length;
            when A_Constrained_Array_Definition =>
               return Length = Discrete_Subtype_Definitions (Def)'Length;
            when others =>
               raise XASIS_Error;
         end case;
      end if;
      return False;
   end Is_Array;

   ----------------
   -- Is_Boolean --
   ----------------

   function Is_Boolean (Tipe : Asis.Declaration) return Boolean
      renames Boolean_Class.Is_Class;

   function Is_Boolean (Info : Type_Info) return Boolean
      renames Boolean_Class.Is_Class;

   -----------------
   -- Is_Child_Of --
   -----------------

   function Is_Child_Of (Child, Parent : Type_Info) return Boolean is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;
      Child_Type : Type_Info := First_Subtype (Child);
      Child_Def  : Asis.Definition;
   begin
      Child_Type.Class_Wide := False;

      while not Is_Not_Type (Child_Type) loop
         if Is_Equal (Parent, Child_Type) then
            return True;
         end if;

         if Child_Type.Definition
           or else Declaration_Kind (Child_Type.Element) /=
                     An_Ordinary_Type_Declaration
         then
            Child_Type := Not_A_Type;
         else
            Child_Def := Type_Declaration_View (Child_Type.Element);
            if Type_Kind (Child_Def) not in A_Derived_Type_Definition ..
              A_Derived_Record_Extension_Definition
            then
               Child_Type := Not_A_Type;
            else
               Child_Def := Parent_Subtype_Indication (Child_Def);
               Child_Type := First_Subtype (Type_From_Indication (Child_Def));
            end if;
         end if;
      end loop;

      return False;
   end Is_Child_Of;

   ------------------
   -- Is_Character --
   ------------------

   function Is_Character (Tipe : Asis.Declaration) return Boolean
      renames Character_Class.Is_Class;

   function Is_Character (Info : Type_Info) return Boolean
      renames Character_Class.Is_Class;

   -------------------
   -- Is_Class_Wide --
   -------------------

   function Is_Class_Wide (Info : Type_Info) return Boolean is
   begin
      return Info.Class_Wide;
   end Is_Class_Wide;

   ------------------
   -- Is_Composite --
   ------------------

   function Is_Composite (Tipe : Asis.Declaration) return Boolean
      renames Composite_Class.Is_Class;

   function Is_Composite (Info : Type_Info) return Boolean
      renames Composite_Class.Is_Class;

   ------------------------
   -- Is_Constant_Access --
   ------------------------

   function Is_Constant_Access (Info : Type_Info) return Boolean
      renames Constant_Access_Class.Is_Class;

   ----------------
   -- Is_Covereded --
   ----------------

   function Is_Covered
     (Specific   : Type_Info;
      Class_Wide : Type_Info) return Boolean
   is
      use XASIS.Utils;
      Root : Type_Info := First_Subtype (Class_Wide);
   begin
      Root.Class_Wide := False;

      if Specific.Is_Access or Class_Wide.Is_Access then
         return False;
      elsif Is_Class_Wide (Class_Wide) and Is_Declaration (Specific) and
        Is_Declaration (Class_Wide) and Specific.Class_Kind = A_Tagged
      then
         return Is_Child_Of (Specific, Root);
      elsif Class_Wide.Class_Kind = An_Universal_Integer then
         return Is_Integer (Specific);
      elsif Class_Wide.Class_Kind = An_Universal_Real then
         return Is_Real (Specific);
      elsif Class_Wide.Class_Kind = An_Universal_Fixed then
         return Is_Fixed_Point (Specific);
      else
         return Is_Equal  (Specific, Class_Wide);
      end if;
   end Is_Covered;

   ----------------------------
   -- Is_Decimal_Fixed_Point --
   ----------------------------

   function Is_Decimal_Fixed_Point (Tipe : Asis.Declaration) return Boolean
      renames Decimal_Fixed_Class.Is_Class;

   function Is_Decimal_Fixed_Point (Info : Type_Info) return Boolean
      renames Decimal_Fixed_Class.Is_Class;

   --------------------
   -- Is_Declaration --
   --------------------

   function Is_Declaration (Info : Type_Info) return Boolean is
   begin
      return not Info.Definition;
   end Is_Declaration;

   -------------------
   -- Is_Definition --
   -------------------

   function Is_Definition (Info : Type_Info) return Boolean is
   begin
      return Info.Definition;
   end Is_Definition;

   -----------------
   -- Is_Discrete --
   -----------------

   function Is_Discrete (Tipe : Asis.Declaration) return Boolean
      renames Discrete_Class.Is_Class;

   function Is_Discrete (Info : Type_Info) return Boolean
      renames Discrete_Class.Is_Class;

   -------------------
   -- Is_Elementary --
   -------------------

   function Is_Elementary (Tipe : Asis.Declaration) return Boolean
      renames Elementary_Class.Is_Class;

   function Is_Elementary (Info : Type_Info) return Boolean
      renames Elementary_Class.Is_Class;

   --------------------
   -- Is_Enumeration --
   --------------------

   function Is_Enumeration (Tipe : Asis.Declaration) return Boolean
      renames Enumeration_Class.Is_Class;

   function Is_Enumeration (Info : Type_Info) return Boolean
      renames Enumeration_Class.Is_Class;

   --------------
   -- Is_Equal --
   --------------

   function Is_Equal (Left, Right : Type_Info) return Boolean is
      use Asis.Declarations;
      Left_Base  : constant Type_Info := Base_Type (First_Subtype (Left));
      Right_Base : constant Type_Info := Base_Type (First_Subtype (Right));
   begin
      if Left_Base.Is_Access or Right_Base.Is_Access then
         return False;
      elsif Left_Base.Definition or Right_Base.Definition then
         return False;
      elsif Left_Base.Class_Wide xor Right_Base.Class_Wide then
         return False;
      else
         return Asis.Elements.Is_Equal (Left_Base.Element, Right_Base.Element);
      end if;
   end Is_Equal;

   ----------------------
   -- Is_Expected_Type --
   ----------------------

   function Is_Expected_Type
     (Specific, Expected : Type_Info) return Boolean
   is
      Exp_Dest : Type_Info;
      Spc_Dest : Type_Info;
   begin
      if Is_Anonymous_Access (Expected) then
         if Is_Definition (Specific) then
            return False;
         end if;
         if Is_Variable_Access (Specific) then
            Exp_Dest := Destination_Type (Expected);
            Spc_Dest := Destination_Type (Specific);
            if Is_Covered (Class_Wide => Exp_Dest, Specific => Spc_Dest) then
               return True;
            elsif not Exp_Dest.Class_Wide then
               Exp_Dest.Class_Wide := True;
               return Is_Equal (Exp_Dest, Spc_Dest);
            end if;
         end if;
         return False;
      elsif Is_Class_Wide (Expected) then
         return Is_Covered (Class_Wide => Expected, Specific => Specific);
      elsif Expected.Class_Kind = An_Universal_Integer then
         return Is_Integer (Specific);
      elsif Expected.Class_Kind = An_Universal_Real then
         return Is_Real (Specific);
      elsif Expected.Class_Kind = An_Universal_Fixed then
         return Is_Fixed_Point (Specific) or else
           Specific.Class_Kind = An_Universal_Real;
      elsif Specific.Class_Kind = An_Universal_Integer and
        Is_Integer (Expected) then
         return True;
      elsif Specific.Class_Kind = An_Universal_Fixed and
        Is_Fixed_Point (Expected) then
         return True;
      elsif Specific.Class_Kind = An_Universal_Real and
        Is_Real (Expected) then
         return True;
      elsif Is_Equal  (Specific, Expected) then
         return True;
      end if;
      return False;
   end Is_Expected_Type;

   --------------------
   -- Is_Fixed_Point --
   --------------------

   function Is_Fixed_Point (Tipe : Asis.Declaration) return Boolean
      renames Fixed_Class.Is_Class;

   function Is_Fixed_Point (Info : Type_Info) return Boolean
      renames Fixed_Class.Is_Class;

   --------------------
   -- Is_Float_Point --
   --------------------

   function Is_Float_Point (Tipe : Asis.Declaration) return Boolean
      renames Float_Class.Is_Class;

   function Is_Float_Point (Info : Type_Info) return Boolean
      renames Float_Class.Is_Class;

   ------------------------
   -- Is_Function_Access --
   ------------------------

   function Is_Function_Access (Info : Type_Info) return Boolean
      renames Function_Access_Class.Is_Class;

   -----------------------
   -- Is_General_Access --
   -----------------------

   function Is_General_Access (Info : Type_Info) return Boolean
      renames General_Access_Class.Is_Class;

   -------------------
   -- Is_Incomplete --
   -------------------

   function Is_Incomplete (Info : Type_Info) return Boolean
      renames Incomplete_Class.Is_Class;

   ----------------
   -- Is_Integer --
   ----------------

   function Is_Integer (Tipe : Asis.Declaration) return Boolean
      renames Integer_Class.Is_Class;

   function Is_Integer (Info : Type_Info) return Boolean
      renames Integer_Class.Is_Class;

   ------------------------
   -- Is_Modular_Integer --
   ------------------------

   function Is_Modular_Integer (Tipe : Asis.Declaration) return Boolean
      renames Modular_Class.Is_Class;

   function Is_Modular_Integer (Info : Type_Info) return Boolean
      renames Modular_Class.Is_Class;

   -----------------
   -- Is_Not_Type --
   -----------------

   function Is_Not_Type (Info : Type_Info) return Boolean is
   begin
      return Asis.Elements.Is_Nil (Info.Element);
   end Is_Not_Type;

   ----------------
   -- Is_Numeric --
   ----------------

   function Is_Numeric (Info : Type_Info) return Boolean
      renames Numeric_Class.Is_Class;

   ----------------------
   -- Is_Object_Access --
   ----------------------

   function Is_Object_Access (Tipe : Asis.Declaration) return Boolean
      renames Object_Access_Class.Is_Class;

   function Is_Object_Access (Info : Type_Info) return Boolean
      renames Object_Access_Class.Is_Class;

   -----------------------------
   -- Is_Ordinary_Fixed_Point --
   -----------------------------

   function Is_Ordinary_Fixed_Point (Tipe : Asis.Declaration) return Boolean
      renames Ordinary_Fixed_Class.Is_Class;

   function Is_Ordinary_Fixed_Point (Info : Type_Info) return Boolean
      renames Ordinary_Fixed_Class.Is_Class;

   -------------------------
   -- Is_Procedure_Access --
   -------------------------

   function Is_Procedure_Access (Info : Type_Info) return Boolean
      renames Procedure_Access_Class.Is_Class;

   ------------------
   -- Is_Protected --
   ------------------

   function Is_Protected (Tipe : Asis.Declaration) return Boolean
      renames Protected_Class.Is_Class;

   function Is_Protected (Info : Type_Info) return Boolean
      renames Protected_Class.Is_Class;

   -------------
   -- Is_Real --
   -------------

   function Is_Real (Tipe : Asis.Declaration) return Boolean
      renames Real_Class.Is_Class;

   function Is_Real (Info : Type_Info) return Boolean
      renames Real_Class.Is_Class;

   ---------------
   -- Is_Scalar --
   ---------------

   function Is_Scalar (Tipe : Asis.Declaration) return Boolean
      renames Scalar_Class.Is_Class;

   function Is_Scalar (Info : Type_Info) return Boolean
      renames Scalar_Class.Is_Class;

   -----------------------
   -- Is_Signed_Integer --
   -----------------------

   function Is_Signed_Integer (Tipe : Asis.Declaration) return Boolean
      renames Signed_Class.Is_Class;

   function Is_Signed_Integer (Info : Type_Info) return Boolean
      renames Signed_Class.Is_Class;

   ---------------
   -- Is_String --
   ---------------

   function Is_String (Tipe : Asis.Declaration) return Boolean
      renames String_Class.Is_Class;

   function Is_String (Info : Type_Info) return Boolean
      renames String_Class.Is_Class;

   ---------------------
   -- Is_String_Array --
   ---------------------

   function Is_String_Array (Def : Asis.Definition) return Boolean is
      use Asis.Definitions;
      Comp : constant Asis.Component_Definition :=
        Array_Component_Definition (Def);
      Ind  : constant Asis.Subtype_Indication :=
        Component_Subtype_Indication (Comp);
      Info : constant Type_Info := Type_From_Indication (Ind);
   begin
      return Is_Character (Info);
   end Is_String_Array;

   --------------------------
   -- Is_Subprogram_Access --
   --------------------------

   function Is_Subprogram_Access (Tipe : Asis.Declaration) return Boolean
      renames Subprogram_Access_Class.Is_Class;

   function Is_Subprogram_Access (Info : Type_Info) return Boolean
      renames Subprogram_Access_Class.Is_Class;


   ---------------------
   -- Is_Subtype_Mark --
   ---------------------

   function Is_Subtype_Mark (Mark : Asis.Expression) return Boolean is
      Info : constant Type_Info := Type_From_Subtype_Mark (Mark);
   begin
      return not Is_Not_Type (Info);
   end Is_Subtype_Mark;

   ---------------
   -- Is_Tagged --
   ---------------

   function Is_Tagged (Tipe : Asis.Declaration) return Boolean
      renames Tagged_Class.Is_Class;

   function Is_Tagged (Info : Type_Info) return Boolean
      renames Tagged_Class.Is_Class;

   -------------
   -- Is_Task --
   -------------

   function Is_Task (Tipe : Asis.Declaration) return Boolean
      renames Task_Class.Is_Class;

   function Is_Task (Info : Type_Info) return Boolean
      renames Task_Class.Is_Class;

   -------------------------
   -- Is_Type_Declaration --
   -------------------------

   function Is_Type_Declaration (Decl : Asis.Declaration) return Boolean is
      Info : constant Type_Info := Type_From_Declaration (Decl);
   begin
      return not Is_Not_Type (Info);
   end Is_Type_Declaration;

   ------------------
   -- Is_Universal --
   ------------------

   function Is_Universal (Info : Type_Info) return Boolean is
   begin
      return Info.Class_Kind = An_Universal_Integer or
        Info.Class_Kind = An_Universal_Real or
        Info.Class_Kind = An_Universal_Fixed;
   end Is_Universal;

   ------------------------
   -- Is_Untagged_Record --
   ------------------------

   function Is_Untagged_Record (Tipe : Asis.Declaration) return Boolean
      renames Record_Class.Is_Class;

   function Is_Untagged_Record (Info : Type_Info) return Boolean
      renames Record_Class.Is_Class;

   ------------------------
   -- Is_Variable_Access --
   ------------------------

   function Is_Variable_Access (Info : Type_Info) return Boolean
      renames Variable_Access_Class.Is_Class;

   --------------------
   -- Set_Class_Wide --
   --------------------

   procedure Set_Class_Wide (Info : in out Type_Info) is
   begin
      Info.Class_Wide := True;
   end Set_Class_Wide;

   -------
   -- T --
   -------
   
   package body T is
      function Universal_Integer return Type_Info is
      begin
         return Type_From_Declaration (Types.Universal_Integer);
      end;

      function Universal_Real return Type_Info is
      begin
         return Type_From_Declaration (Types.Universal_Real);
      end Universal_Real;

      function Universal_Fixed return Type_Info is
      begin
         return Type_From_Declaration (Types.Universal_Fixed);
      end Universal_Fixed;

      function Root_Integer return Type_Info is
      begin
         return Type_From_Declaration (Types.Root_Integer);
      end Root_Integer;

      function Root_Real return Type_Info is
      begin
         return Type_From_Declaration (Types.Root_Real);
      end Root_Real;

      function System_Address return Type_Info is
      begin
         return Type_From_Declaration (Types.System_Address);
      end System_Address;

      function System_Bit_Order return Type_Info is
      begin
         return Type_From_Declaration (Types.System_Bit_Order);
      end System_Bit_Order;

      function Integer return Type_Info is
      begin
         return Type_From_Declaration (Types.Integer);
      end Integer;

      function String return Type_Info is
      begin
         return Type_From_Declaration (Types.String);
      end String;

      function Wide_String return Type_Info is
      begin
         return Type_From_Declaration (Types.Wide_String);
      end Wide_String;

      function Boolean return Type_Info is
      begin
         return Type_From_Declaration (Types.Boolean);
      end Boolean;

      function Exception_Id return Type_Info is
      begin
         return Type_From_Declaration (Types.Exception_Id);
      end Exception_Id;

      function Task_Id return Type_Info is
      begin
         return Type_From_Declaration (Types.Task_Id);
      end Task_Id;

      function Root_Storage_Pool return Type_Info is
      begin
         return Type_From_Declaration (Types.Root_Storage_Pool);
      end Root_Storage_Pool;

      function Tag return Type_Info is
      begin
         return Type_From_Declaration (Types.Tag);
      end Tag;

      function Natural return Type_Info is
      begin
         return Type_From_Declaration (Types.Natural);
      end Natural;

      function Duration return Type_Info is
      begin
         return Type_From_Declaration (Types.Duration);
      end Duration;

      function Wide_Character return Type_Info is
      begin
         return Type_From_Declaration (Types.Wide_Character);
      end Wide_Character;

      function Character return Type_Info is
      begin
         return Type_From_Declaration (Types.Character);
      end Character;

      function Root_Stream_Type return Type_Info is
      begin
         return Type_From_Declaration (Types.Root_Stream_Type);
      end Root_Stream_Type;
   end T;

   ----------------
   -- Type_Class --
   ----------------

   function Type_Class (Tipe : Asis.Definition) return Class_Kinds is
      use Asis.Elements;
      use Asis.Definitions;
   begin
      case Definition_Kind (Tipe) is
         when A_Type_Definition =>
            case Type_Kind (Tipe) is
               when A_Derived_Type_Definition =>
                  declare
                     use Asis.Definitions;
                     Element : Asis.Element;
                     Info    : Type_Info;
                  begin
                     Element := Parent_Subtype_Indication (Tipe);
                     Element := Asis.Definitions.Subtype_Mark (Element);
                     Info := Type_From_Subtype_Mark (Element);
                     return Info.Class_Kind;
                  end;
               when A_Derived_Record_Extension_Definition =>
                  return A_Tagged;
               when An_Enumeration_Type_Definition =>
                  if Has_Character_Literal (Tipe) then
                     return A_Character;
                  elsif Is_Equal (Enclosing_Element (Tipe), Types.Boolean)
                  then
                     return A_Boolean;
                  else
                     return An_Other_Enum;
                  end if;
               when A_Signed_Integer_Type_Definition =>
                  return A_Signed_Integer;
               when A_Modular_Type_Definition =>
                  return A_Modular_Integer;
               when A_Root_Type_Definition =>
                  case Root_Type_Kind (Tipe) is
                     when A_Root_Integer_Definition =>
                        return A_Signed_Integer;
                     when A_Root_Real_Definition =>
                        return A_Float_Point;
                     when A_Universal_Integer_Definition =>
                        return An_Universal_Integer;
                     when A_Universal_Real_Definition =>
                        return An_Universal_Real;
                     when A_Universal_Fixed_Definition =>
                        return An_Universal_Fixed;
                     when Not_A_Root_Type_Definition =>
                        raise XASIS_Error;
                  end case;
               when A_Floating_Point_Definition =>
                  return A_Float_Point;
               when An_Ordinary_Fixed_Point_Definition =>
                  return A_Ordinary_Fixed_Point;
               when A_Decimal_Fixed_Point_Definition =>
                  return A_Decimal_Fixed_Point;
               when An_Unconstrained_Array_Definition =>
                  if Index_Subtype_Definitions (Tipe)'Length = 1 and then
                    Is_String_Array (Tipe)
                  then
                     return A_String;
                  else
                     return An_Other_Array;
                  end if;
               when A_Constrained_Array_Definition =>
                  if Discrete_Subtype_Definitions (Tipe)'Length = 1 and then
                    Is_String_Array (Tipe)
                  then
                     return A_String;
                  else
                     return An_Other_Array;
                  end if;
               when A_Record_Type_Definition =>
                  return A_Untagged_Record;
               when A_Tagged_Record_Type_Definition =>
                  return A_Tagged;
               when An_Access_Type_Definition =>
                  case Access_Type_Kind (Tipe) is
                     when A_Pool_Specific_Access_To_Variable |
                          An_Access_To_Variable =>
                        return A_Variable_Access;
                     when An_Access_To_Constant =>
                        return A_Constant_Access;
                     when An_Access_To_Procedure |
                          An_Access_To_Protected_Procedure =>
                        return A_Procedure_Access;
                     when An_Access_To_Function |
                          An_Access_To_Protected_Function =>
                        return A_Function_Access;
                     when Not_An_Access_Type_Definition =>
                        raise XASIS_Error;
                  end case;
               when others =>
                  raise XASIS_Error;
            end case;
         when A_Task_Definition =>
            return A_Task;
         when A_Protected_Definition =>
            return A_Protected;
         when others =>
            raise XASIS_Error;
      end case;
   end Type_Class;

   ---------------------------
   -- Type_From_Declaration --
   ---------------------------

   function Type_From_Declaration (Tipe : Asis.Declaration) return Type_Info is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Definitions;
      Def    : Asis.Definition;
      Decl   : Asis.Declaration;
      Result : Type_Info;
      Base   : Type_Info;
   begin
      case Declaration_Kind (Tipe) is
         when An_Ordinary_Type_Declaration =>

            Def := Type_Declaration_View (Tipe);
            Result.Element := Tipe;
            Result.Class_Kind := Type_Class (Def);

         when A_Task_Type_Declaration |
           A_Protected_Type_Declaration =>

            Result.Element := Tipe;
            Result.Class_Kind := Type_Class (Type_Declaration_View (Tipe));

         when A_Subtype_Declaration =>
            Def    := Type_Declaration_View (Tipe);
            Result := Type_From_Indication (Def);
            Base   := Type_From_Declaration (Result.Element);
            Result.Element := Tipe;
            Result.Class_Kind := Base.Class_Kind;
            Result.Class_Wide := Result.Class_Wide or Base.Class_Wide;

         when An_Incomplete_Type_Declaration =>
            Decl := Utils.Completion_For_Declaration (Tipe);

            if Is_Nil (Decl) then
               Result.Element := Tipe;
               Result.Class_Kind := An_Incomplete;
            else
               Result := Type_From_Declaration (Decl);
            end if;

         when A_Private_Type_Declaration =>
            Result.Element := Tipe;
            Result.Class_Kind := A_Private;

         when others =>
            Result.Element := Asis.Nil_Element;
      end case;
      return Result;
   end Type_From_Declaration;

   ----------------------------
   -- Type_From_Discrete_Def --
   ----------------------------

   function Type_From_Discrete_Def (Def  : Asis.Definition) return Type_Info
   is
      use XASIS.Static;
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Expressions;
      Result : Type_Info;
      Expr   : Asis.Expression;
      Index  : Asis.List_Index;
   begin
      if Definition_Kind (Def) /= A_Discrete_Subtype_Definition then
         raise XASIS_Error;
      end if;
      case Discrete_Range_Kind (Def) is
         when A_Discrete_Subtype_Indication =>
            Result := Type_From_Indication (Def);
         when A_Discrete_Range_Attribute_Reference =>
            Expr := Range_Attribute (Def);
            Result := Type_From_Subtype_Mark (Prefix (Expr));

            if Is_Not_Type (Result) then
               Result := Type_Of_Expression (Prefix (Expr));

               if not Is_Not_Type (Result) then
                  Index := +Attribute_Designator_Expression (Expr);
                  Result := Get_Array_Index_Type (Result, Index);
               end if;
            end if;
         when A_Discrete_Simple_Expression_Range =>
            Result := Type_Of_Range (Lower_Bound (Def), Upper_Bound (Def));
         when Not_A_Discrete_Range =>
            raise XASIS_Error;
      end case;
      return Result;
   end Type_From_Discrete_Def;

   --------------------------
   -- Type_From_Indication --
   --------------------------

   function Type_From_Indication (Ind : Asis.Definition) return Type_Info is
      use Asis.Elements;
      use Asis.Expressions;
      use Asis.Definitions;
      use Asis.Declarations;

      Result    : Type_Info;
      Element   : Asis.Element;
   begin
      case Definition_Kind (Ind) is
         when A_Discrete_Subtype_Definition =>
            Result := Type_From_Discrete_Def (Ind);
         when A_Subtype_Indication  =>
            Element := Asis.Definitions.Subtype_Mark (Ind);

            --  FIXME: delete the loop latter
            Skip_Denormalized_Constraints :
               while Expression_Kind (Element) = A_Function_Call loop
                  Element := Prefix (Element);
               end loop Skip_Denormalized_Constraints;

            Result := Type_From_Subtype_Mark (Element);
         when A_Type_Definition =>
            Result.Element := Ind;
            Result.Class_Kind := Type_Class (Ind);
            Result.Definition := True;
         when others =>
            raise XASIS_Error;
      end case;
      return Result;
   end Type_From_Indication;

   ----------------------------
   -- Type_From_Subtype_Mark --
   ----------------------------

   function Type_From_Subtype_Mark (Mark : Asis.Expression) return Type_Info is
      use Asis.Elements;
      use Asis.Expressions;
      Result      : Type_Info;
      Identifier  : Asis.Expression := Mark;
      Kind        : Asis.Expression_Kinds;
      Declaration : Asis.Declaration;
      Class_Wide  : Boolean := False;
   begin
      Result.Element := Asis.Nil_Element;
      Kind := Expression_Kind (Identifier);

      while Kind = An_Attribute_Reference loop
         if Attribute_Kind (Identifier) = A_Base_Attribute then
            null;
         elsif Attribute_Kind (Identifier) = A_Class_Attribute then
            Class_Wide := True;
         else
            return Result;
         end if;
         Identifier := Prefix (Identifier);
         Kind := Expression_Kind (Identifier);
      end loop;

      if Kind = A_Selected_Component then
         Identifier := Selector (Identifier);
         Kind := Expression_Kind (Identifier);
      end if;

      if Kind /= An_Identifier then
         return Result;
      end if;
      Declaration := Corresponding_Name_Declaration (Identifier);
      Result := Type_From_Declaration (Declaration);
      Result.Class_Wide := Class_Wide;
      return Result;
   end Type_From_Subtype_Mark;

   -------------------------
   -- Type_Of_Declaration --
   -------------------------

   function Type_Of_Declaration (Decl : Asis.Declaration) return Type_Info is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;

      Result    : Type_Info;
      Element   : Asis.Element;
   begin
      case Declaration_Kind (Decl) is
         when A_Component_Declaration =>
            Element := Object_Declaration_View (Decl);
            Element := Component_Subtype_Indication (Element);
            Element := Asis.Definitions.Subtype_Mark (Element);
            Result := Type_From_Subtype_Mark (Element);

         when A_Variable_Declaration |
              A_Constant_Declaration |
              A_Deferred_Constant_Declaration |
              A_Single_Task_Declaration |
              A_Single_Protected_Declaration =>

            Element := Object_Declaration_View (Decl);

            if Definition_Kind (Element) = A_Subtype_Indication then
               Result := Type_From_Indication (Element);
            else
               Result.Element := Element;
               Result.Definition := True;
               Result.Class_Kind := Type_Class (Element);
            end if;

         when An_Integer_Number_Declaration =>
            Result.Element := Types.Universal_Integer;
            Result.Class_Kind := An_Universal_Integer;

         when A_Real_Number_Declaration =>
            Result.Element := Types.Universal_Real;
            Result.Class_Kind := An_Universal_Real;

         when An_Enumeration_Literal_Specification =>
            Element := Enclosing_Element (Decl);
            Result.Class_Kind := Type_Class (Element);
            Result.Element := Enclosing_Element (Element);

         when A_Loop_Parameter_Specification =>
            Element := Specification_Subtype_Definition (Decl);
            Result := Type_From_Discrete_Def (Element);

         when A_Discriminant_Specification |
           A_Parameter_Specification |
           An_Object_Renaming_Declaration |
           A_Formal_Object_Declaration =>

            Element := Declaration_Subtype_Mark (Decl);
            Result := Type_From_Subtype_Mark (Element);
            Result.Is_Access :=
              Trait_Kind (Decl) = An_Access_Definition_Trait;

         when others =>
            Result.Element := Nil_Element;
      end case;
      return Result;
   end Type_Of_Declaration;

   -----------------------
   -- Type_Of_Expression--
   -----------------------

   function Type_Of_Expression (Expr : Asis.Expression) return Type_Info is
      use Asis.Elements;
      use Asis.Expressions;
      Decl   : Asis.Declaration := Corresponding_Expression_Type (Expr);
      Result : Type_Info;
   begin
      if Is_Nil (Decl) then
         case Expression_Kind (Expr) is
            when An_Identifier =>
               Decl := Corresponding_Name_Declaration (Expr);
               Result := Type_Of_Declaration (Decl);
            when An_Integer_Literal =>
               Result := Type_From_Declaration (Types.Universal_Integer);
            when others =>
               raise XASIS_Error;
         end case;
      else
         Result := Type_From_Declaration (Decl);
      end if;
      return Result;
   end Type_Of_Expression;

   -------------------
   -- Type_Of_Range --
   -------------------

   function Type_Of_Range (Lower, Upper : Asis.Expression) return Type_Info is
      Left  : constant Type_Info := Type_Of_Expression (Lower);
      Right : constant Type_Info := Type_Of_Expression (Upper);
   begin
      return Type_Of_Range (Left, Right);
   end Type_Of_Range;

   -------------------
   -- Type_Of_Range --
   -------------------

   function Type_Of_Range (Lower, Upper : Type_Info) return Type_Info is
   begin
      if not Is_Universal (Upper) then
         if Is_Expected_Type (Lower, Upper) then
            return Upper;
         end if;
      elsif Is_Expected_Type (Upper, Lower) then
         return Lower;
      end if;
      return Not_A_Type;
   end Type_Of_Range;

end XASIS.Classes;



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
