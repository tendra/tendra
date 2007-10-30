with Asis.Elements;
with Asis.Definitions;
with Asis.Expressions;
with Asis.Declarations;
with Asis.Gela.Visibility;
with Asis.Gela.Utils;
with XASIS.Utils;
with XASIS.Types;

package body Asis.Gela.Classes is

   function Get_Base_Type (Decl  : Asis.Declaration) return Asis.Declaration;

   function Get_Type_View
     (Decl  : Asis.Declaration;
      Place : Asis.Element) return Asis.Declaration;

   function Type_Class
     (Tipe  : Asis.Definition;
      Place : Asis.Element) return Class_Kinds;

   function Declaration_Class
     (Tipe  : Asis.Element;
      Place : Asis.Element) return Class_Kinds;

   function Has_Character_Literal (Tipe : Asis.Declaration) return Boolean;

   function Type_Of_Expression (Expr : Asis.Expression) return Type_Info;

   -------------------------
   -- Conform_Access_Type --
   -------------------------

   function Conform_Access_Type
     (Decl : Asis.Declaration;
      Tipe : Type_Info)
      return Boolean
   is
      use Asis.Elements;
      use Asis.Gela.Utils;
      use Asis.Declarations;
      List      : constant Asis.Defining_Name_List := Names (Decl);
      Type_Decl : constant Asis.Declaration := Tipe.Type_View;
      Place     : constant Asis.Element := Tipe.Place;
   begin
      if Tipe.Is_Declaration and then not Is_Nil (Type_Decl) then
         return Are_Type_Conformant (List (1), Names (Type_Decl) (1), Place);
      else
         return False;
      end if;
   end Conform_Access_Type;

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image (Info : Type_Info) return Wide_String is
      use Asis.Elements;
      Img : constant Wide_String :=
        "class => " & Class_Kinds'Wide_Image (Info.Class_Kind)
        & " base => " & Debug_Image (Info.Base_Type)
        & " decl => " & Boolean'Wide_Image (Info.Is_Declaration)
        & " wide => " & Boolean'Wide_Image (Info.Is_Class_Wide)
        & " access => " & Boolean'Wide_Image (Info.Is_Access)
        & " view => " & Debug_Image (Info.Type_View)
        & " subtype => " & Debug_Image (Info.Subtipe);
   begin
      return Img;
   end Debug_Image;

   -----------------------
   -- Declaration_Class --
   -----------------------

   function Declaration_Class
     (Tipe  : Asis.Element;
      Place : Asis.Element) return Class_Kinds
   is
      use Asis.Elements;
      use Asis.Declarations;
   begin
      case Declaration_Kind (Tipe) is
         when An_Incomplete_Type_Declaration =>
            return An_Incomplete;
         when A_Private_Type_Declaration =>
            return A_Private;
         when others =>
            return Type_Class (Type_Declaration_View (Tipe), Place);
      end case;
   end Declaration_Class;

   ----------------------
   -- Destination_Type --
   ----------------------

   function Destination_Type (Tipe : Type_Info) return Type_Info is
      use Asis.Definitions;
      use Asis.Declarations;

      Result : Type_Info;
      Def    : Asis.Definition;
   begin
      if Tipe.Is_Access then
         Result := Tipe;
         Result.Is_Access := False;
      elsif Is_Object_Access (Tipe) then
         Def    := Type_Declaration_View (Tipe.Type_View);
         Def    := Asis.Definitions.Access_To_Object_Definition (Def);
         Result := Type_From_Indication (Def, Tipe.Place);
      end if;

      return Result;
   end Destination_Type;

   --------------------
   -- Find_Component --
   --------------------

   function Find_Component
     (Tipe : Type_Info;
      Name : Asis.Program_Text)
      return Asis.Declaration
   is
      use XASIS.Utils;
      use Asis.Gela.Utils;

      Result : Asis.Declaration;

      procedure Walk_Variant
        (Item     : in     Asis.Variant;
         Continue :    out Boolean) is
      begin
         Continue := True;
      end Walk_Variant;

      procedure Walk_Companent
        (Item     : in     Asis.Declaration;
         Continue :    out Boolean) is
      begin
         if Has_Defining_Name (Item, Name) then
            Result := Item;
            Continue := False;
         else
            Continue := True;
         end if;
      end Walk_Companent;

      procedure Search is new
        Walk_Components (Tipe.Place, Walk_Variant, Walk_Companent);

      Continue : Boolean;
      Decl     : constant Asis.Declaration := Tipe.Type_View;
   begin
      if not Assigned (Decl) then
         return Asis.Nil_Element;
      end if;

      Search (Decl, Continue);

      return Result;
   end Find_Component;

   ----------------------------
   -- Get_Array_Element_Type --
   ----------------------------

   function Get_Array_Element_Type
     (Def   : Asis.Definition;
      Place : Asis.Element) return Type_Info
   is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;

      Comp : constant Asis.Definition := Array_Component_Definition (Def);
      Ind  : constant Asis.Definition := Component_Subtype_Indication (Comp);
   begin
      return Type_From_Indication (Ind, Place);
   end Get_Array_Element_Type;

   ----------------------------
   -- Get_Array_Element_Type --
   ----------------------------

   function Get_Array_Element_Type (Tipe : Type_Info) return Type_Info is
      Def : constant Asis.Definition := Get_Type_Def (Tipe);
   begin
      return Get_Array_Element_Type (Def, Tipe.Place);
   end Get_Array_Element_Type;

   --------------------------
   -- Get_Array_Index_Type --
   --------------------------

   function Get_Array_Index_Type
     (Tipe  : Type_Info;
      Index : Asis.List_Index := 1)
      return Type_Info
   is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;

      Def    : Asis.Definition;
      Mark   : Asis.Expression;
      Result : Type_Info;
   begin
      Def  := Get_Type_Def (Tipe);

      case Type_Kind (Def) is
         when An_Unconstrained_Array_Definition =>
            Mark := Index_Subtype_Definitions (Def) (Index);
            Result := Type_From_Subtype_Mark (Mark, Tipe.Place);
         when A_Constrained_Array_Definition =>
            Def := Discrete_Subtype_Definitions (Def) (Index);
            Result := Type_From_Discrete_Def (Def, Tipe.Place);
         when others =>
            raise Internal_Error;
      end case;

      return Result;
   end Get_Array_Index_Type;

   -------------------
   -- Get_Base_Type --
   -------------------

   function Get_Base_Type (Decl : Asis.Declaration) return Asis.Declaration is
      use Asis.Declarations;
      Result : Asis.Declaration := Decl;
   begin
      while XASIS.Utils.Is_Completion (Result)
      loop
         Result := XASIS.Utils.Declaration_For_Completion (Result);
      end loop;

      return Result;
   end Get_Base_Type;

   ---------------------
   -- Get_Declaration --
   ---------------------

   function Get_Declaration (Info : Type_Info) return Asis.Declaration is
   begin
      if Info.Is_Declaration then
         return Info.Type_View;
      else
         return Asis.Nil_Element;
      end if;
   end Get_Declaration;

   -----------------
   -- Get_Limited --
   -----------------

   function Get_Limited (Info : Type_Info) return Boolean is

      Result : Boolean := False;

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
         Comp : constant Type_Info := Type_From_Declaration (Item, Info.Place);
      begin
         if Is_Limited (Comp) then
            Result := True;
            Continue := False;
         else
            Continue := True;
         end if;
      end Walk_Companent;

      procedure Search is new
        Gela.Utils.Walk_Components (Info.Place, Walk_Variant, Walk_Companent);

      Continue : Boolean := True;
      Parent   : Type_Info;
   begin
      if not Is_Composite (Info) then
         return False;
      end if;

      if Gela.Utils.Is_Limited_Type (Get_Type_Def (Info)) then
         return True;
      end if;

      if Is_Array (Info) then
         return Is_Limited (Get_Array_Element_Type (Info));
      end if;

      Parent := Parent_Type (Info);

      if not Is_Not_Type (Parent) then
         return Is_Limited (Parent);
      end if;

      Search (Info.Type_View, Continue);

      return Result;
   end Get_Limited;

   ---------------
   -- Get_Place --
   ---------------

   function Get_Place (Info : Type_Info) return Asis.Element is
   begin
      return Info.Place;
   end Get_Place;

   ------------------
   -- Get_Type_Def --
   ------------------

   function Get_Type_Def (Tipe : Type_Info) return Asis.Definition is
      use Asis.Elements;
      use Asis.Declarations;
   begin
      if Tipe.Is_Declaration then
         return Type_Declaration_View (Tipe.Type_View);
      else
         return Object_Declaration_View (Enclosing_Element (Tipe.Base_Type));
      end if;
   end Get_Type_Def;

   -------------------
   -- Get_Type_View --
   -------------------

   function Get_Type_View
     (Decl  : Asis.Declaration;
      Place : Asis.Element) return Asis.Declaration
   is
      Temp   : Asis.Declaration;
      Result : Asis.Declaration := Decl;
      Kind   : Asis.Declaration_Kinds;
      Name   : Asis.Defining_Name;
   begin
      loop
         Temp := XASIS.Utils.Completion_For_Declaration (Result);
         exit when not Assigned (Temp);
         Name := Asis.Declarations.Names (Temp) (1);
         exit when not Visibility.Visible_From (Name, Place);
         Kind := Asis.Elements.Declaration_Kind (Temp);
         exit when Kind = A_Task_Body_Declaration or
           Kind = A_Protected_Body_Declaration;
         Result := Temp;
      end loop;

      return Result;
   end Get_Type_View;

   -----------------
   -- Get_Subtype --
   -----------------

   function Get_Subtype (Info : Type_Info) return Asis.Declaration is
   begin
      return Info.Subtipe;
   end Get_Subtype;

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

   function Is_Access (Info : Type_Info) return Boolean is
   begin
      return Info.Is_Access or else Info.Class_Kind in An_Access;
   end Is_Access;

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

   function Is_Array (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind in An_Array;
   end Is_Array;

   --------------
   -- Is_Array --
   --------------

   function Is_Array
     (Tipe   : Type_Info;
      Length : Asis.List_Index)
      return Boolean
   is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;

      Def    : Asis.Definition;
   begin
      if Is_Array (Tipe) then
         Def  := Get_Type_Def (Tipe);

         case Definition_Kind (Def) is
            when A_Type_Definition =>
               case Type_Kind (Def) is
                  when An_Unconstrained_Array_Definition =>
                     return Length = Index_Subtype_Definitions (Def)'Length;
                  when A_Constrained_Array_Definition =>
                     return Length = Discrete_Subtype_Definitions (Def)'Length;
                  when others =>
                     raise Internal_Error;
               end case;
            when A_Formal_Type_Definition =>
               case Formal_Type_Kind (Def) is
                  when A_Formal_Unconstrained_Array_Definition =>
                     return Length = Index_Subtype_Definitions (Def)'Length;
                  when A_Formal_Constrained_Array_Definition =>
                     return Length = Discrete_Subtype_Definitions (Def)'Length;
                  when others =>
                     raise Internal_Error;
               end case;
            when others =>
               raise Internal_Error;
         end case;
      end if;

      return False;
   end Is_Array;

   ----------------
   -- Is_Boolean --
   ----------------

   function Is_Boolean (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = A_Boolean;
   end Is_Boolean;

   ----------------------
   -- Is_Boolean_Array --
   ----------------------

   function Is_Boolean_Array (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = A_Boolean_Array;
   end Is_Boolean_Array;

   ------------------
   -- Is_Character --
   ------------------

   function Is_Character (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = A_Character;
   end Is_Character;

   -----------------
   -- Is_Child_Of --
   -----------------

   function Is_Child_Of (Child, Parent : Type_Info) return Boolean is
      Child_Type : Type_Info := Child;
   begin
      Child_Type.Is_Class_Wide := False;

      while not Is_Not_Type (Child_Type) loop
         if Is_Equal (Parent, Child_Type) then
            return True;
         end if;

         Child_Type := Parent_Type (Child_Type);
      end loop;

      return False;
   end Is_Child_Of;

   -------------------
   -- Is_Class_Wide --
   -------------------

   function Is_Class_Wide (Info : Type_Info) return Boolean is
   begin
      return Info.Is_Class_Wide;
   end Is_Class_Wide;

   ------------------
   -- Is_Composite --
   ------------------

   function Is_Composite (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind in A_Composite;
   end Is_Composite;

   ------------------------
   -- Is_Constant_Access --
   ------------------------

   function Is_Constant_Access (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access
        and then Info.Class_Kind = A_Constant_Access;
   end Is_Constant_Access;

   ----------------
   -- Is_Covered --
   ----------------

   function Is_Covered
     (Specific   : Type_Info;
      Class_Wide : Type_Info)
      return Boolean
   is
      use XASIS.Utils;

      Root : Type_Info := Class_Wide;
   begin
      Root.Is_Class_Wide := False;

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

   function Is_Decimal_Fixed_Point (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access
        and then Info.Class_Kind = A_Decimal_Fixed_Point;
   end Is_Decimal_Fixed_Point;

   --------------------
   -- Is_Declaration --
   --------------------

   function Is_Declaration (Info : Type_Info) return Boolean is
   begin
      return Info.Is_Declaration;
   end Is_Declaration;

   -------------------
   -- Is_Definition --
   -------------------

   function Is_Definition (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Declaration;
   end Is_Definition;

   -----------------
   -- Is_Discrete --
   -----------------

   function Is_Discrete (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind in A_Discrete;
   end Is_Discrete;

   -----------------------
   -- Is_Discrete_Array --
   -----------------------

   function Is_Discrete_Array (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind in A_Discrete_Array;
   end Is_Discrete_Array;

   -------------------
   -- Is_Elementary --
   -------------------

   function Is_Elementary (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind in An_Elementary;
   end Is_Elementary;

   --------------------
   -- Is_Enumeration --
   --------------------

   function Is_Enumeration (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind in An_Enumeration;
   end Is_Enumeration;

   --------------
   -- Is_Equal --
   --------------

   function Is_Equal (Left, Right : Type_Info) return Boolean is
      use Asis.Declarations;
   begin
      if Left.Is_Access or Right.Is_Access then
         return False;
      elsif Left.Is_Class_Wide /= Right.Is_Class_Wide then
         return False;
      else
         return Asis.Elements.Is_Equal (Left.Base_Type, Right.Base_Type);
      end if;
   end Is_Equal;

   ----------------------
   -- Is_Expected_Type --
   ----------------------

   function Is_Expected_Type
     (Specific : Type_Info;
      Expected : Type_Info)
      return Boolean
   is
      Exp_Dest : Type_Info;
      Spc_Dest : Type_Info;
   begin
      if Is_Anonymous_Access (Expected) then
         if not Specific.Is_Declaration then
            return False;
         end if;

         if Is_Variable_Access (Specific) then
            Exp_Dest := Destination_Type (Expected);
            Spc_Dest := Destination_Type (Specific);

            if Is_Covered (Class_Wide => Exp_Dest, Specific => Spc_Dest) then
               return True;
            elsif not Exp_Dest.Is_Class_Wide then
               Exp_Dest.Is_Class_Wide := True;
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
      elsif Specific.Class_Kind = An_Universal_Integer
        and Is_Integer (Expected)
      then
         return True;
      elsif Specific.Class_Kind = An_Universal_Fixed
        and Is_Fixed_Point (Expected)
      then
         return True;
      elsif Specific.Class_Kind = An_Universal_Real
        and Is_Real (Expected)
      then
         return True;
      elsif Is_Equal  (Specific, Expected) then
         return True;
      else
         Exp_Dest := Expected;
         Exp_Dest.Is_Class_Wide := True;
         return Is_Equal  (Specific, Exp_Dest);  --  T'Class
      end if;
   end Is_Expected_Type;

   --------------------
   -- Is_Fixed_Point --
   --------------------

   function Is_Fixed_Point (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind in A_Fixed_Point;
   end Is_Fixed_Point;

   --------------------
   -- Is_Float_Point --
   --------------------

   function Is_Float_Point (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = A_Float_Point;
   end Is_Float_Point;

   ------------------------
   -- Is_Function_Access --
   ------------------------

   function Is_Function_Access (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access
        and then Info.Class_Kind = A_Function_Access;
   end Is_Function_Access;

   -----------------------
   -- Is_General_Access --
   -----------------------

   function Is_General_Access (Info : Type_Info) return Boolean is
   begin
      return Info.Is_Access or else Info.Class_Kind in A_General_Access;
   end Is_General_Access;

   -------------------
   -- Is_Incomplete --
   -------------------

   function Is_Incomplete (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = An_Incomplete;
   end Is_Incomplete;

   ----------------
   -- Is_Integer --
   ----------------

   function Is_Integer (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind in An_Integer;
   end Is_Integer;

   ----------------
   -- Is_Limited --
   ----------------

   function Is_Limited (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Is_Limited;
   end Is_Limited;

   ------------------------
   -- Is_Modular_Integer --
   ------------------------

   function Is_Modular_Integer (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = A_Modular_Integer;
   end Is_Modular_Integer;

   -----------------
   -- Is_Not_Type --
   -----------------

   function Is_Not_Type (Info : Type_Info) return Boolean is
   begin
      return Asis.Elements.Is_Nil (Info.Base_Type);
   end Is_Not_Type;

   ----------------
   -- Is_Numeric --
   ----------------

   function Is_Numeric (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind in A_Numeric;
   end Is_Numeric;

   ----------------------
   -- Is_Object_Access --
   ----------------------

   function Is_Object_Access (Info : Type_Info) return Boolean is
   begin
      return Info.Is_Access or else Info.Class_Kind in An_Object_Access;
   end Is_Object_Access;

   -----------------------------
   -- Is_Ordinary_Fixed_Point --
   -----------------------------

   function Is_Ordinary_Fixed_Point (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access
        and then Info.Class_Kind = A_Ordinary_Fixed_Point;
   end Is_Ordinary_Fixed_Point;

   -------------------------
   -- Is_Procedure_Access --
   -------------------------

   function Is_Procedure_Access (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access
        and then Info.Class_Kind = A_Procedure_Access;
   end Is_Procedure_Access;

   ------------------
   -- Is_Protected --
   ------------------

   function Is_Protected (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = A_Protected;
   end Is_Protected;

   -------------
   -- Is_Real --
   -------------

   function Is_Real (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind in A_Real;
   end Is_Real;

   ---------------
   -- Is_Scalar --
   ---------------

   function Is_Scalar (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind in A_Scalar;
   end Is_Scalar;

   -----------------------
   -- Is_Signed_Integer --
   -----------------------

   function Is_Signed_Integer (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = A_Signed_Integer;
   end Is_Signed_Integer;

   ---------------
   -- Is_String --
   ---------------

   function Is_String (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = A_String;
   end Is_String;

   --------------------------
   -- Is_Subprogram_Access --
   --------------------------

   function Is_Subprogram_Access (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access
        and then Info.Class_Kind in A_Subprogram_Access;
   end Is_Subprogram_Access;

   ---------------------
   -- Is_Subtype_Mark --
   ---------------------

   function Is_Subtype_Mark (Mark : Asis.Expression) return Boolean is
      Info : constant Type_Info := Type_From_Subtype_Mark (Mark, Mark);
   begin
      return not Is_Not_Type (Info);
   end Is_Subtype_Mark;

   ---------------
   -- Is_Tagged --
   ---------------

   function Is_Tagged (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = A_Tagged;
   end Is_Tagged;

   -------------
   -- Is_Task --
   -------------

   function Is_Task (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = A_Task;
   end Is_Task;

   -------------------------
   -- Is_Type_Declaration --
   -------------------------

   function Is_Type_Declaration (Decl : Asis.Declaration) return Boolean is
      Info : constant Type_Info := Type_From_Declaration (Decl, Decl);
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

   function Is_Untagged_Record (Info : Type_Info) return Boolean is
   begin
      return not Info.Is_Access and then Info.Class_Kind = A_Untagged_Record;
   end Is_Untagged_Record;

   ------------------------
   -- Is_Variable_Access --
   ------------------------

   function Is_Variable_Access (Info : Type_Info) return Boolean is
   begin
      return Info.Is_Access or else Info.Class_Kind = A_Variable_Access;
   end Is_Variable_Access;

   -----------------
   -- Parent_Type --
   -----------------

   function Parent_Type (Tipe : Type_Info) return Type_Info is
      Def  : Asis.Definition := Get_Type_Def (Tipe);
      Kind : constant Asis.Type_Kinds := Asis.Elements.Type_Kind (Def);
   begin
      if Elements.Definition_Kind (Def) = A_Private_Extension_Definition then
         Def := Asis.Definitions.Ancestor_Subtype_Indication (Def);
      elsif Kind = A_Derived_Type_Definition
        or Kind = A_Derived_Record_Extension_Definition
      then
         Def := Asis.Definitions.Parent_Subtype_Indication (Def);
      else
         return Not_A_Type;
      end if;

      return Type_From_Indication (Def, Tipe.Place);
   end Parent_Type;

   ----------------
   -- Set_Access --
   ----------------

   procedure Set_Access
     (Info  : in out Type_Info;
      Value : in     Boolean)
   is
   begin
      Info.Is_Access := Value;
   end Set_Access;

   --------------------
   -- Set_Class_Wide --
   --------------------

   procedure Set_Class_Wide (Info : in out Type_Info) is
   begin
      Info.Is_Class_Wide := True;
   end Set_Class_Wide;

   ---------------------
   -- Top_Parent_Type --
   ---------------------

   function Top_Parent_Type (Tipe : Type_Info) return Type_Info is
      Result : Type_Info := Tipe;
      Parent : Type_Info := Parent_Type (Tipe);
   begin
      while not Is_Not_Type (Parent) loop
         Result := Parent;
         Parent := Parent_Type (Parent);
      end loop;

      return Result;
   end Top_Parent_Type;

   ----------------
   -- Type_Class --
   ----------------

   function Type_Class
     (Tipe  : Asis.Element;
      Place : Asis.Element) return Class_Kinds
   is
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
                     Info := Type_From_Subtype_Mark (Element, Place);
                     return Info.Class_Kind;
                  end;
               when A_Derived_Record_Extension_Definition =>
                  return A_Tagged;
               when An_Enumeration_Type_Definition =>
                  if Has_Character_Literal (Tipe) then
                     return A_Character;
                  elsif Is_Equal (Enclosing_Element (Tipe),
                                  XASIS.Types.Boolean)
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
                        raise Internal_Error;
                  end case;
               when A_Floating_Point_Definition =>
                  return A_Float_Point;
               when An_Ordinary_Fixed_Point_Definition =>
                  return A_Ordinary_Fixed_Point;
               when A_Decimal_Fixed_Point_Definition =>
                  return A_Decimal_Fixed_Point;
               when An_Unconstrained_Array_Definition =>
                  if Index_Subtype_Definitions (Tipe)'Length = 1 then
                     declare
                        Comp : constant Type_Info :=
                          Get_Array_Element_Type (Tipe, Place);
                     begin
                        if Is_Character (Comp) then
                           return A_String;
                        elsif Is_Boolean (Comp) then
                           return A_Boolean_Array;
                        elsif Is_Discrete (Comp) then
                           return A_Other_Discrete_Array;
                        end if;
                     end;
                  end if;

                  return An_Other_Array;

               when A_Constrained_Array_Definition =>
                  if Discrete_Subtype_Definitions (Tipe)'Length = 1 then
                     declare
                        Comp : constant Type_Info :=
                          Get_Array_Element_Type (Tipe, Place);
                     begin
                        if Is_Character (Comp) then
                           return A_String;
                        elsif Is_Boolean (Comp) then
                           return A_Boolean_Array;
                        elsif Is_Discrete (Comp) then
                           return A_Other_Discrete_Array;
                        end if;
                     end;
                  end if;

                  return An_Other_Array;

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
                        raise Internal_Error;
                  end case;
               when others =>
                  raise Internal_Error;
            end case;
         when A_Task_Definition =>
            return A_Task;
         when A_Protected_Definition =>
            return A_Protected;
         when A_Private_Extension_Definition =>
            return A_Tagged;
         when A_Formal_Type_Definition =>
            case Formal_Type_Kind (Tipe) is
               when A_Formal_Private_Type_Definition =>
                  return A_Private;
               when A_Formal_Tagged_Private_Type_Definition =>
                  return A_Tagged;
               when A_Formal_Derived_Type_Definition =>
                  declare
                     use Asis.Definitions;
                     Element : Asis.Element;
                     Info    : Type_Info;
                  begin
                     Element := Definitions.Subtype_Mark (Tipe);
                     Info := Type_From_Subtype_Mark (Element, Place);
                     return Info.Class_Kind;
                  end;
               when A_Formal_Discrete_Type_Definition =>
                  return An_Other_Enum;
               when A_Formal_Signed_Integer_Type_Definition =>
                  return A_Signed_Integer;
               when A_Formal_Modular_Type_Definition =>
                  return A_Modular_Integer;
               when A_Formal_Floating_Point_Definition =>
                  return A_Float_Point;
               when A_Formal_Ordinary_Fixed_Point_Definition =>
                  return A_Ordinary_Fixed_Point;
               when A_Formal_Decimal_Fixed_Point_Definition =>
                  return A_Decimal_Fixed_Point;
               when A_Formal_Unconstrained_Array_Definition
                 | A_Formal_Constrained_Array_Definition =>
                  return An_Other_Array;
               when A_Formal_Access_Type_Definition =>
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
                        raise Internal_Error;
                  end case;
               when others =>
                  raise Internal_Error;
            end case;
         when others =>
            raise Internal_Error;
      end case;
   end Type_Class;

   ---------------------------
   -- Type_From_Declaration --
   ---------------------------

   function Type_From_Declaration
     (Tipe  : Asis.Declaration;
      Place : Asis.Element)
      return Type_Info
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Definitions;
      Def    : Asis.Definition;
      Result : Type_Info;
   begin
      case Declaration_Kind (Tipe) is
         when An_Ordinary_Type_Declaration |
           A_Task_Type_Declaration |
           A_Protected_Type_Declaration |
           An_Incomplete_Type_Declaration |
           A_Private_Type_Declaration |
           A_Private_Extension_Declaration |
           A_Formal_Type_Declaration =>

            Result.Base_Type      := Get_Base_Type (Tipe);
            Result.Type_View      := Get_Type_View (Result.Base_Type, Place);
            Result.Class_Kind     :=
              Declaration_Class (Result.Type_View, Place);
            Result.Subtipe        := Tipe;
            Result.Place          := Place;
            Result.Is_Limited     := Get_Limited (Result);

         when A_Subtype_Declaration =>
            Def    := Type_Declaration_View (Tipe);
            Result := Type_From_Indication (Def, Place);

         when A_Task_Body_Declaration
           | A_Protected_Body_Declaration
           =>
            return Type_From_Declaration
              (XASIS.Utils.Declaration_For_Completion (Tipe), Place);
         when others =>
            Result := Not_A_Type;
      end case;

      return Result;
   end Type_From_Declaration;

   ----------------------------
   -- Type_From_Discrete_Def --
   ----------------------------

   function Type_From_Discrete_Def
     (Def   : Asis.Definition;
      Place : Asis.Element)
      return Type_Info
   is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Expressions;

      Result : Type_Info;
      Expr   : Asis.Expression;
      Index  : Asis.List_Index;
   begin
      case Discrete_Range_Kind (Def) is
         when A_Discrete_Subtype_Indication =>
            Result := Type_From_Indication (Def, Place);
         when A_Discrete_Range_Attribute_Reference =>
            Expr := Range_Attribute (Def);
            Result := Type_From_Subtype_Mark (Prefix (Expr), Place);

            if Is_Not_Type (Result) then
               Result := Type_Of_Expression (Prefix (Expr));

               if Is_Object_Access (Result) then
                  Result := Destination_Type (Result);
               end if;

               if not Is_Not_Type (Result) then
                  Index  := 1;  --  FIXME Index := Calculate (N);
                  Result := Get_Array_Index_Type (Result, Index);
               end if;
            end if;
         when A_Discrete_Simple_Expression_Range =>
            Result := Type_Of_Range (Lower_Bound (Def), Upper_Bound (Def));
         when Not_A_Discrete_Range =>
            raise Internal_Error;
      end case;

      return Result;
   end Type_From_Discrete_Def;

   --------------------------
   -- Type_From_Indication --
   --------------------------

   function Type_From_Indication
     (Ind   : Asis.Definition;
      Place : Asis.Element)
      return Type_Info
   is
      use Asis.Elements;
      use Asis.Expressions;
      use Asis.Definitions;
      use Asis.Declarations;

      Result    : Type_Info;
      Element   : Asis.Element;
      Kind      : constant Asis.Definition_Kinds := Definition_Kind (Ind);
   begin
      case Kind is
         when A_Discrete_Subtype_Definition
           | A_Subtype_Indication  =>

            if Kind = A_Discrete_Subtype_Definition
              and then Discrete_Range_Kind (Ind) /=
                         A_Discrete_Subtype_Indication
            then
               return Type_From_Discrete_Def (Ind, Place);
            end if;

            Element := Asis.Definitions.Subtype_Mark (Ind);

            --  FIXME: delete the loop latter
            Skip_Denormalized_Constraints :
               while Expression_Kind (Element) = A_Function_Call loop
                  Element := Prefix (Element);
               end loop Skip_Denormalized_Constraints;

            Result := Type_From_Subtype_Mark (Element, Place);
         when A_Type_Definition =>
            Result.Is_Declaration := True;
            Result.Class_Kind     := Type_Class (Ind, Place);
            Result.Base_Type      := Ind;
            Result.Place          := Place;
            raise Internal_Error;

         when others =>
            raise Internal_Error;
      end case;

      return Result;
   end Type_From_Indication;

   ----------------------------
   -- Type_From_Subtype_Mark --
   ----------------------------

   function Type_From_Subtype_Mark
     (Mark  : Asis.Expression;
      Place : Asis.Element)
      return Type_Info
   is
      use Asis.Elements;
      use Asis.Expressions;

      Result      : Type_Info;
      Identifier  : Asis.Expression := Mark;
      Kind        : Asis.Expression_Kinds;
      Declaration : Asis.Declaration;
      Class_Wide  : Boolean := False;
   begin
      Kind := Expression_Kind (Identifier);

      while Kind = An_Attribute_Reference loop
         if Attribute_Kind (Identifier) = A_Base_Attribute then
            null;
         elsif Attribute_Kind (Identifier) = A_Class_Attribute then
            Class_Wide := True;
         else
            return Not_A_Type;
         end if;

         Identifier := Prefix (Identifier);
         Kind := Expression_Kind (Identifier);
      end loop;

      Declaration := XASIS.Utils.Selected_Name_Declaration (Identifier, False);

      if not Assigned (Declaration) then
         return Not_A_Type;
      end if;

      Result               := Type_From_Declaration (Declaration, Place);
      Result.Is_Class_Wide := Result.Is_Class_Wide or Class_Wide;

      return Result;
   end Type_From_Subtype_Mark;

   -------------------------
   -- Type_Of_Declaration --
   -------------------------

   function Type_Of_Declaration
     (Decl  : Asis.Declaration;
      Place : Asis.Element)
      return Type_Info
   is
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
            Result := Type_From_Indication (Element, Place);

         when A_Variable_Declaration |
              A_Constant_Declaration |
              A_Deferred_Constant_Declaration |
              A_Single_Task_Declaration |
              A_Single_Protected_Declaration =>

            Element := Object_Declaration_View (Decl);

            if Definition_Kind (Element) = A_Subtype_Indication then
               Result := Type_From_Indication (Element, Place);
            else
               Result := Type_Of_Name (Names (Decl)(1), Place);
            end if;

         when An_Integer_Number_Declaration =>
            Result.Class_Kind := An_Universal_Integer;
            Result.Base_Type  := XASIS.Types.Universal_Integer;
            Result.Type_View  := Result.Base_Type;
            Result.Subtipe    := Result.Base_Type;
            Result.Place      := Place;

         when A_Real_Number_Declaration =>
            Result.Class_Kind := An_Universal_Real;
            Result.Base_Type  := XASIS.Types.Universal_Real;
            Result.Type_View  := Result.Base_Type;
            Result.Subtipe    := Result.Base_Type;
            Result.Place      := Place;

         when An_Enumeration_Literal_Specification =>
            Element := Enclosing_Element (Decl);
            Element := Enclosing_Element (Element);
            Result := Type_From_Declaration (Element, Place);

         when A_Loop_Parameter_Specification =>
            Element := Specification_Subtype_Definition (Decl);
            Result := Type_From_Discrete_Def (Element, Place);

         when A_Discriminant_Specification |
           A_Parameter_Specification |
           An_Object_Renaming_Declaration |
           A_Formal_Object_Declaration =>

            Element := Declaration_Subtype_Mark (Decl);
            Result := Type_From_Subtype_Mark (Element, Place);
            Result.Is_Access :=
              Trait_Kind (Decl) = An_Access_Definition_Trait;

         when others =>
            Result := Not_A_Type;
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
               Result := Type_Of_Declaration (Decl, Expr);
            when An_Integer_Literal =>
               Result :=
                 Type_From_Declaration (XASIS.Types.Universal_Integer, Expr);
            when A_Selected_Component =>
               Result := Type_Of_Expression (Selector (Expr));
            when others =>
               raise Internal_Error;
         end case;
      else
         Result := Type_From_Declaration (Decl, Expr);
      end if;

      return Result;
   end Type_Of_Expression;

   ------------------
   -- Type_Of_Name --
   ------------------

   function Type_Of_Name
     (Name  : Asis.Defining_Name;
      Place : Asis.Element) return Type_Info
   is
      use Asis.Elements;

      Decl   : constant Asis.Declaration :=
        Asis.Elements.Enclosing_Element (Name);
      Def    : Asis.Definition;
      Result : Type_Info;
   begin
      case Declaration_Kind (Decl) is
         when A_Variable_Declaration |
              A_Constant_Declaration |
              A_Deferred_Constant_Declaration |
              A_Single_Task_Declaration |
              A_Single_Protected_Declaration =>

            Def := Asis.Declarations.Object_Declaration_View (Decl);

            if Definition_Kind (Def) /= A_Subtype_Indication then
               Result.Is_Declaration := False;
               Result.Class_Kind     := Type_Class (Def, Place);
               Result.Base_Type      := Name;
               Result.Place          := Place;
               Result.Is_Limited     := Get_Limited (Result);

               return Result;
            end if;
         when others =>
            null;
      end case;

      return Type_Of_Declaration (Decl, Place);
   end Type_Of_Name;

   -------------------
   -- Type_Of_Range --
   -------------------

   function Type_Of_Range
     (Lower, Upper : Asis.Expression)
      return Type_Info
   is
      Left  : constant Type_Info := Type_Of_Expression (Lower);
      Right : constant Type_Info := Type_Of_Expression (Upper);
   begin
      return Type_Of_Range (Left, Right);
   end Type_Of_Range;

   -------------------
   -- Type_Of_Range --
   -------------------

   function Type_Of_Range
     (Lower, Upper : Type_Info)
      return Type_Info
   is
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

end Asis.Gela.Classes;



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
