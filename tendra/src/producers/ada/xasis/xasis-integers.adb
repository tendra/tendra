with Ada.Strings.Fixed;
with Ada.Strings.Maps.Constants;

package body XASIS.Integers is

   type Small is mod 2**16;
   type Digit is mod 2**8;

   function X (Char : Character) return Digit;
   function X (Char : Character) return Small;
   function X (First, Second : Character) return Small;
   function X (Item : Digit)     return Character;

   pragma Inline (X);

   type Buffer is array (Positive range <>) of Character;

   procedure Add
     (Left   : in     Buffer;
      Right  : in     Buffer;
      Result :    out Buffer;
      Last   :    out Positive;
      Mult   : in     Digit := 1);

   procedure Add
     (Left   : in     Buffer;
      Right  : in     Buffer;
      Result :    out Buffer;
      Last   :    out Positive;
      Mult   : in     Digit := 1;
      Carry  :    out Digit);

   procedure Subtract
     (Left   : in     Buffer;
      Right  : in     Buffer;
      Result :    out Buffer;
      Last   :    out Positive;
      Mult   : in     Digit := 1);

   procedure Subtract
     (Left   : in     Buffer;
      Right  : in     Buffer;
      Result :    out Buffer;
      Last   :    out Positive;
      Mult   : in     Digit := 1;
      Carry  :    out Digit);

   procedure Multiply
     (Left   : in     Buffer;
      Right  : in     Buffer;
      Result :    out Buffer;
      Last   :    out Positive);

   procedure Normalize_For_Devide
     (Left   : in out Buffer;
      Right  : in out Buffer;
      Mult   :    out Digit);

   procedure Devide
     (Left   : in out Buffer;
      Right  : in     Buffer;
      Result :    out Digit);

   procedure Devide
     (Left   : in     Value;
      Right  : in     Value;
      Result :    out Value;
      Rest   : in     Boolean := False);

   procedure Initialize
     (Text   : in     String;
      Result :    out Buffer;
      Last   :    out Positive;
      Base   : in     Digit := 10);

   function Signed_Add
     (Left_Text   : Buffer;
      Right_Text  : Buffer)
      return Value;

   function Less
     (Left_Text   : Buffer;
      Right_Text  : Buffer)
      return Boolean;

   function To_Small (Text : Buffer) return Small;

   procedure Change_Sign (Sign : in out Character);

   procedure Fast_Devide
     (Left   : in     Buffer;
      Right  : in     Digit;
      Result :    out Buffer;
      Last   :    out Natural;
      Rest   :    out Digit);

   function Get_Last (Text : Buffer) return Positive;

   function Get_Sign (Left, Right : Character) return Character;

   function To_Value (Text : Buffer) return Value;

   generic
      with function Op (Left, Right : Digit) return Digit;
   function Logic (Left, Right : Value) return Value;

   Buffer_Overflow : exception;

   function Simple_Literal
     (Text : String;
      Base : Positive := 10)
      return Value;

   ---------
   -- "*" --
   ---------

   function "*" (Left, Right : Value) return Value is
      Left_Text   : constant Buffer := Buffer (To_String (Left));
      Right_Text  : constant Buffer := Buffer (To_String (Right));
      Result_Last : Positive := 1;
      Result_Text : Buffer (1 .. Left_Text'Length + Right_Text'Length - 1);
   begin
      Result_Text (1) := Get_Sign (Left_Text (1), Right_Text (1));
      Multiply
        (Left   => Left_Text (2 .. Left_Text'Last),
         Right  => Right_Text (2 .. Right_Text'Last),
         Result => Result_Text (2 .. Result_Text'Last),
         Last   => Result_Last);
      return To_Value (Result_Text (1 .. Result_Last));
   end "*";

   ----------
   -- "**" --
   ----------

   function "**" (Left, Right : Value) return Value is
      Right_Text  : constant Buffer := Buffer (To_String (Right));
      Power       : Small := To_Small (Right_Text (2 .. Right_Text'Last));
      Last        : constant Positive :=
        ((Length (Left) - 1) * Natural (Power)) + 1;
      Mult_Last   : Positive := Length (Left);
      Result_Last : Positive := 2;
      Result_Text : Buffer (1 .. Positive'Max (Last, 2));
      Temp_Text   : Buffer (1 .. Last);
      Mult_Text   : Buffer (1 .. Positive'Max (Last, Mult_Last));
   begin
      if Right_Text (1) = '-' then
         raise XASIS_Error;
      end if;
      if (Power and 1) /= 0 and then Element (Left, 1) = '-' then
         Result_Text (1) := '-';
      else
         Result_Text (1) := '+';
      end if;
      Mult_Text (1 .. Mult_Last) := Buffer (To_String (Left));
      Result_Text (2) := X (1);
      while Power > 0 loop
         if (Power and 1) /= 0 then
            Temp_Text (2 .. Result_Last) := Result_Text (2 .. Result_Last);
            Multiply
              (Left   => Temp_Text (2 .. Result_Last),
               Right  => Mult_Text (2 .. Mult_Last),
               Result => Result_Text (2 .. Result_Text'Last),
               Last   => Result_Last);
            Power := Power - 1;
         else
            Temp_Text (2 .. Mult_Last) := Mult_Text (2 .. Mult_Last);
            Multiply
              (Left   => Temp_Text (2 .. Mult_Last),
               Right  => Temp_Text (2 .. Mult_Last),
               Result => Mult_Text (2 .. Mult_Text'Last),
               Last   => Mult_Last);
            Power := Power / 2;
         end if;
      end loop;
      return To_Value (Result_Text (1 .. Result_Last));
   end "**";

   ---------
   -- "+" --
   ---------

   function "+" (Left, Right : Value) return Value is
      Left_Text  : constant Buffer := Buffer (To_String (Left));
      Right_Text : constant Buffer := Buffer (To_String (Right));
   begin
      return Signed_Add (Left_Text, Right_Text);
   end "+";

   ---------
   -- "-" --
   ---------

   function "-" (Left : Value) return Value is
      Left_Text : Buffer := Buffer (To_String (Left));
   begin
      Change_Sign (Left_Text (1));
      return To_Value (Left_Text);
   end "-";

   ---------
   -- "-" --
   ---------

   function "-" (Left, Right : Value) return Value is
      Left_Text  : constant Buffer := Buffer (To_String (Left));
      Right_Text : Buffer := Buffer (To_String (Right));
   begin
      Change_Sign (Right_Text (1));
      return Signed_Add (Left_Text, Right_Text);
   end "-";

   ---------
   -- "/" --
   ---------

   function "/" (Left, Right : Value) return Value is
      Result : Value;
   begin
      Devide (Left, Right, Result);
      return Result;
   end "/";

   ---------
   -- "<" --
   ---------

   function "<" (Left, Right : Value) return Boolean is
      Left_Text  : constant Buffer := Buffer (To_String (Left));
      Right_Text : constant Buffer := Buffer (To_String (Right));
   begin
      if Left_Text (1) = '+' and Right_Text (1) = '+' then
         return Less (Left_Text (2 .. Left_Text'Last),
                      Right_Text (2 .. Right_Text'Last));
      elsif Left_Text (1) = '+' and Right_Text (1) = '-' then
         return False;
      elsif Left_Text (1) = '-' and Right_Text (1) = '+' then
         return True;
      else
         return Less (Right_Text (2 .. Right_Text'Last),
                      Left_Text (2 .. Left_Text'Last));
      end if;
   end "<";

   ----------
   -- "<=" --
   ----------

   function "<=" (Left, Right : Value) return Boolean is
   begin
      return Left = Right or else Left < Right;
   end "<=";

   ---------
   -- "=" --
   ---------

   function "=" (Left, Right : Value) return Boolean is
      use type U.Unbounded_String;
   begin
      return U.Unbounded_String (Left) = U.Unbounded_String (Right);
   end "=";

   ---------
   -- ">" --
   ---------

   function ">" (Left, Right : Value) return Boolean is
   begin
      return not (Left <= Right);
   end ">";

   ----------
   -- ">=" --
   ----------

   function ">=" (Left, Right : Value) return Boolean is
   begin
      return not (Left < Right);
   end ">=";

   -----------
   -- "abs" --
   -----------

   function "abs" (Left : Value) return Value is
      Sign : constant Character := Element (Left, 1);
   begin
      if Sign = '-' then
         return Overwrite (Left, 1, (1 => '+'));
      else
         return Left;
      end if;
   end "abs";

   -----------
   -- Logic --
   -----------

   function Logic (Left, Right : Value) return Value is
      Left_Text   : constant Buffer := Buffer (To_String (Left));
      Right_Text  : constant Buffer := Buffer (To_String (Right));
      Temp        : Digit;
      Length      : constant Positive :=
        Positive'Max (Left_Text'Last, Right_Text'Last);
      Result_Last : Positive := 1;
      Result_Text : Buffer (1 .. Length);
   begin
      Result_Text (1) := '+';
      if Left_Text (1) /= '+' or Right_Text (1) /= '+' then
         raise XASIS_Error;
      end if;
      for I in 2 .. Length loop
         if I in Right_Text'Range then
            Temp := X (Right_Text (I));
         else
            Temp := 0;
         end if;
         if I in Left_Text'Range then
            Temp := Op (X (Left_Text (I)), Temp);
         end if;
         Result_Text (I) := X (Temp);
      end loop;
      Result_Last := Get_Last (Result_Text);
      return To_Value (Result_Text (1 .. Result_Last));
   end Logic;

   -----------
   -- "and" --
   -----------

   function And_Logic is new Logic ("and");

   function "and" (Left, Right : Value) return Value
     renames And_Logic;

   -----------
   -- "mod" --
   -----------

   function "mod" (Left, Right : Value) return Value is
      Result : Value;
   begin
      Devide (Left, Right, Result, True);

      if Element (Left, 1) = Element (Right, 1) or Result = Zero then
         return Result;
      else
         return Result + Right;
      end if;
   end "mod";

   -----------
   -- "not" --
   -----------

   function "not" (Left : Value) return Value is
      Left_Text : Buffer := Buffer (To_String (Left));
      Left_Last : Positive := 1;
   begin
      if Left_Text (1) /= '+' then
         raise XASIS_Error;
      end if;
      for I in 2 .. Left_Text'Last loop
         Left_Text (I) := X (not X (Left_Text (I)));
      end loop;
      Left_Last := Get_Last (Left_Text);
      return To_Value (Left_Text (1 .. Left_Last));
   end "not";

   ----------
   -- "or" --
   ----------

   function Or_Logic is new Logic ("or");

   function "or" (Left, Right : Value) return Value
     renames Or_Logic;

   -----------
   -- "rem" --
   -----------

   function "rem" (Left, Right : Value) return Value is
      Result : Value;
   begin
      Devide (Left, Right, Result, True);
      return Result;
   end "rem";

   -----------
   -- "xor" --
   -----------

   function Xor_Logic is new Logic ("xor");

   function "xor" (Left, Right : Value) return Value
     renames Xor_Logic;

   ---------
   -- Add --
   ---------

   procedure Add
     (Left   : in     Buffer;
      Right  : in     Buffer;
      Result :    out Buffer;
      Last   :    out Positive;
      Mult   : in     Digit := 1)
   is
      Carry : Digit;
   begin
      Add (Left, Right, Result, Last, Mult, Carry);
      if Carry /= 0 then
         Last := Last + 1;
         if Last > Result'Last then
            raise Buffer_Overflow;
         end if;
         Result (Last) := X (Carry);
      end if;
   end Add;

   ---------
   -- Add --
   ---------

   procedure Add
     (Left   : in     Buffer;
      Right  : in     Buffer;
      Result :    out Buffer;
      Last   :    out Positive;
      Mult   : in     Digit := 1;
      Carry  :    out Digit)
   is
      Temp  : Small;
      Max   : constant Natural := Positive'Max (Left'Length, Right'Length);
   begin
      if Max > Result'Length then
         raise Buffer_Overflow;
      end if;
      Carry := 0;
      for I in 0 .. Max - 1 loop
         if I < Right'Length then
            Temp := X (Right (Right'First + I)) * Small (Mult);
         else
            Temp := 0;
         end if;
         if I < Left'Length then
            Temp := X (Left (Left'First + I)) + Temp;
         end if;
         Temp := Temp + Small (Carry);
         Result (Result'First + I) := X (Digit (Temp mod Digit'Modulus));
         Carry := Digit (Temp / Digit'Modulus);
      end loop;
      Last := Result'First + Max - 1;
   end Add;

   -----------------
   -- Change_Sign --
   -----------------

   procedure Change_Sign (Sign : in out Character) is
   begin
      if Sign = '+' then
         Sign := '-';
      else
         Sign := '+';
      end if;
   end Change_Sign;

   ------------
   -- Devide --
   ------------

   procedure Devide
     (Left   : in out Buffer;
      Right  : in     Buffer;
      Result :    out Digit)
   is
      function Get_Digit (Left, Right : Buffer) return Digit;

      function Get_Digit (Left, Right : Buffer) return Digit is
         Temp   : Small;
         Result : Small;
      begin
         if Left (Left'Last) = Right (Right'Last) then
            Result := 255;
         else
            Result := X (Left (Left'Last), Left (Left'Last - 1));
            Result := Result / X (Right (Right'Last));
         end if;
         loop
            Temp := X (Left (Left'Last), Left (Left'Last - 1));
            Temp := Temp - Result * X (Right (Right'Last));
            exit when Temp >= 256;
            Temp := Temp * 256 + X (Left (Left'Last - 2));
            exit when Result * X (Right (Right'Last - 1)) <= Temp;
            Result := Result - 1;
         end loop;
         return Digit (Result);
      end Get_Digit;

      Carry : Digit;
      Last  : Positive;
   begin
      Result := Get_Digit (Left, Right);
      Subtract
        (Left   => Left,
         Right  => Right,
         Result => Left,
         Last   => Last,
         Mult   => Result,
         Carry  => Carry);

      if Carry /= 0 then
         Result := Result - 1;
         Add
           (Left   => Left,
            Right  => Right,
            Result => Left,
            Last   => Last,
            Carry  => Carry);
      end if;
   end Devide;

   ------------
   -- Devide --
   ------------

   procedure Devide
     (Left   : in     Value;
      Right  : in     Value;
      Result :    out Value;
      Rest   : in     Boolean := False)
   is
      Left_Length : constant Integer :=
        Integer'Max (Length (Left), Length (Right) + 1);
      Left_Text   : Buffer (1 .. Left_Length) := (others => X (0));
      Right_Text  : Buffer := Buffer (To_String (Right));
      Index       : Natural := Left_Text'Length - Right_Text'Length + 1;
      Result_Text : Buffer (1 .. Left_Text'Length - Right_Text'Length + 1);
      Last        : Positive;
      Temp        : Digit;
      Mult        : Digit;
   begin
      Left_Text (1 .. Length (Left)) := Buffer (To_String (Left));

      if Right_Text'Length = 1 then
         raise Buffer_Overflow;
      elsif Right_Text'Length = 2 then
         declare
            Result_Text : Buffer (Left_Text'Range);
         begin
            Fast_Devide
              (Left   => Left_Text (2 .. Left_Text'Last),
               Right  => X (Right_Text (2)),
               Result => Result_Text (2 .. Result_Text'Last),
               Last   => Last,
               Rest   => Temp);

            if Rest then
               Result_Text (1) := Left_Text (1);
               Result_Text (2) := X (Temp);
               Result := To_Value (Result_Text (1 .. 2));
            else
               Result_Text (1) := Get_Sign (Left_Text (1), Right_Text (1));
               Result := To_Value (Result_Text (1 .. Last));
            end if;

            return;
         end;
      end if;

      Normalize_For_Devide
        (Left   => Left_Text (2 .. Left_Text'Last),
         Right  => Right_Text (2 .. Right_Text'Last),
         Mult   => Mult);

      while Index >= 2 loop
         Devide
           (Left   => Left_Text (Index .. Index + Right_Text'Length - 1),
            Right  => Right_Text (2 .. Right_Text'Last),
            Result => Temp);
         Result_Text (Index) := X (Temp);
         Index := Index - 1;
      end loop;

      if Rest then
         Fast_Devide
           (Left   => Left_Text (2 .. Right_Text'Length + 1),
            Right  => Mult,
            Result => Left_Text (2 .. Right_Text'Length + 1),
            Last   => Last,
            Rest   => Temp);
         Result := To_Value (Left_Text (1 .. Last));
      else
         Result_Text (1) := Get_Sign (Left_Text (1), Right_Text (1));
         Last := Get_Last (Result_Text);
         Result := To_Value (Result_Text (1 .. Last));
      end if;
   end Devide;

   -----------------
   -- Fast_Devide --
   -----------------

   procedure Fast_Devide
     (Left   : in     Buffer;
      Right  : in     Digit;
      Result :    out Buffer;
      Last   :    out Natural;
      Rest   :    out Digit)
   is
      Temp   : Small := 0;
   begin
      for I in reverse Left'Range loop
         Temp := Temp * 256 + X (Left (I));
         Result (I) := X (Digit (Temp / Small (Right)));
         Temp := Temp mod Small (Right);
      end loop;
      Rest := Digit (Temp);
      Last := Get_Last (Result);
   end Fast_Devide;

   --------------
   -- Get_Last --
   --------------

   function Get_Last (Text : Buffer) return Positive is
   begin
      for I in reverse Text'Range loop
         if Text (I) /= X (0) then
            return I;
         end if;
      end loop;

      return Text'First - 1;
   end Get_Last;

   --------------
   -- Get_Sign --
   --------------

   function Get_Sign (Left, Right : Character) return Character is
   begin
      if Left = Right then
         return '+';
      else
         return '-';
      end if;
   end Get_Sign;

   -----------
   -- Image --
   -----------

   function Image (Left : Value) return String is
      Text        : Buffer := Buffer (To_String (Left));
      Text_Last   : Natural := Text'Last;
      Result_Text : String (1 .. Text'Length * 3);
      First       : Positive := Result_Text'Last + 1;
      Rest        : Digit;
   begin
      if Text_Last = 1 then
         return "0";
      end if;

      while Text_Last >= 2 loop
         Fast_Devide
           (Left   => Text (2 .. Text_Last),
            Right  => 10,
            Result => Text (2 .. Text_Last),
            Last   => Text_Last,
            Rest   => Rest);
         First := First - 1;
         Result_Text (First) := X (Rest + Character'Pos ('0'));
      end loop;

      if Text (1) = '-' then
         First := First - 1;
         Result_Text (First) := '-';
      end if;

      return Result_Text (First .. Result_Text'Last);
   end Image;

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize
     (Text   : in     String;
      Result :    out Buffer;
      Last   :    out Positive;
      Base   : in     Digit := 10)
   is
      Left   : Buffer (Result'First .. Result'First);
      Temp   : Character;
      Stop   : Natural := Result'First - 1;
      Skip   : Boolean := False;
   begin
      for I in Text'Range loop
         Temp := Text (I);
         case Temp is
            when '0' .. '9' =>
               Left (Result'First) := X (X (Temp) - Character'Pos ('0'));
            when 'a' .. 'f' =>
               Left (Result'First) := X (X (Temp) - Character'Pos ('a') + 10);
            when 'A' .. 'F' =>
               Left (Result'First) := X (X (Temp) - Character'Pos ('A') + 10);
            when '_' | '.' | '#' =>
               Skip := True;
            when others =>
               raise XASIS_Error;
         end case;
         if Skip then
            Skip := False;
         else
            Add (Left, Result (Result'First .. Stop), Result, Stop, Base);
         end if;
      end loop;
      Last := Stop;
   end Initialize;

   ----------
   -- Less --
   ----------

   function Less
     (Left_Text   : Buffer;
      Right_Text  : Buffer)
      return Boolean is
   begin
      if Left_Text'Length = Right_Text'Length then
         for I in reverse Left_Text'Range loop
            if Left_Text (I) < Right_Text (I) then
               return True;
            elsif Left_Text (I) > Right_Text (I) then
               return False;
            end if;
         end loop;
         return False;
      elsif Left_Text'Length > Right_Text'Length then
         if Left_Text (Left_Text'Last) = X (0) then
            raise XASIS_Error;
         end if;
         return False;
      else
         if Right_Text (Right_Text'Last) = X (0) then
            raise XASIS_Error;
         end if;
         return True;
      end if;
   end Less;

   --------------------
   -- Simple_Literal --
   --------------------

   function Simple_Literal
     (Text : String;
      Base : Positive := 10)
      return Value
   is
      Result_Text : Buffer (1 .. Text'Length / 2 + 2);
      Result_Last : Positive;
      I           : constant Positive := Text'First;
   begin
      if Text (I) = '-' or Text (I) = '+' then
         Result_Text (1) := Text (I);
         Initialize (Text (Text'First + 1 .. Text'Last),
           Result_Text (2 .. Result_Text'Last), Result_Last, Digit (Base));
      elsif Text (I) = ' ' then
         Result_Text (1) := '+';
         Initialize (Text (Text'First + 1 .. Text'Last),
           Result_Text (2 .. Result_Text'Last), Result_Last, Digit (Base));
      else
         Result_Text (1) := '+';
         Initialize (Text,
           Result_Text (2 .. Result_Text'Last), Result_Last, Digit (Base));
      end if;
      return To_Value (Result_Text (1 .. Result_Last));
   end Simple_Literal;

   -------------
   -- Literal --
   -------------

   function Literal (Text : String) return Value is
      use Ada.Strings.Fixed;
      use Ada.Strings.Maps.Constants;
      Base   : Positive := 10;
      Sharp  : Natural := Index (Text, "#");
      E      : Natural := Index (Text, "E", Mapping => Upper_Case_Map);
      Result : Value;
      Exp    : Value;
   begin
      if Sharp /= 0 then
         Base := Positive'Value (Text (Text'First .. Sharp - 1));
      else
         Sharp := Text'First - 1;
      end if;
      if E /= 0 then
         Exp := Simple_Literal (Text (E + 1 .. Text'Last));
      else
         E := Text'Last + 1;
         Exp := Zero;
      end if;
      Result := Simple_Literal (Text (Sharp + 1 .. E - 1), Base);
      if Exp /= Zero then
         Exp := To_Value ('+' & X (Digit (Base))) ** Exp;
         Result := Result * Exp;
      end if;
      return Result;
   end Literal;

   --------------
   -- Multiply --
   --------------

   procedure Multiply
     (Left   : in     Buffer;
      Right  : in     Buffer;
      Result :    out Buffer;
      Last   :    out Positive)
   is
      Temp   : Digit;
      Length : Natural := Result'First - 1;
      Mult   : Buffer (Result'Range);
   begin
      for I in Left'Range loop
         Temp := X (Left (I));
         Mult (I .. I + Right'Length - 1) := Right;
         Mult (Mult'First .. I - 1) := (others => X (0));
         Add
           (Left   => Result (Result'First .. Length),
            Right  => Mult (Mult'First .. I + Right'Length - 1),
            Result => Result,
            Last   => Length,
            Mult   => Temp);
      end loop;
      Last := Length;
   end Multiply;

   --------------------------
   -- Normalize_For_Devide --
   --------------------------

   procedure Normalize_For_Devide
     (Left   : in out Buffer;
      Right  : in out Buffer;
      Mult   :    out Digit)
   is
      Zero : constant Buffer (Left'First .. Left'First - 1) :=
        (others => X (0));
      Last : Positive;
   begin
      Mult := Digit (Small'(256) / (X (Right (Right'Last)) + 1));
      if Mult = 1 then
         Left (Left'Last) := X (0);
      else
         Add
           (Left   => Zero,
            Right  => Left,
            Result => Left,
            Last   => Last,
            Mult   => Mult);

         Add
           (Left   => Zero,
            Right  => Right,
            Result => Right,
            Last   => Last,
            Mult   => Mult);
      end if;
   end Normalize_For_Devide;

   ----------------
   -- Signed_Add --
   ----------------

   function Signed_Add
     (Left_Text   : Buffer;
      Right_Text  : Buffer)
      return Value
   is
      Length      : constant Positive :=
        Positive'Max (Left_Text'Last, Right_Text'Last) + 1;
      Result_Last : Positive := 1;
      Result_Text : Buffer (1 .. Length);
   begin
      if Left_Text (1) = Right_Text (1) then
         Result_Text (1) := Left_Text (1);
         Add
           (Left   => Left_Text (2 .. Left_Text'Last),
            Right  => Right_Text (2 .. Right_Text'Last),
            Result => Result_Text (2 .. Result_Text'Last),
            Last   => Result_Last);
      else
         if Less (Left_Text (2 .. Left_Text'Last),
                  Right_Text (2 .. Right_Text'Last))
         then
            Result_Text (1) := Right_Text (1);
            Subtract
              (Left   => Right_Text  (2 .. Right_Text'Last),
               Right  => Left_Text   (2 .. Left_Text'Last),
               Result => Result_Text (2 .. Result_Text'Last),
               Last   => Result_Last);
         else
            Result_Text (1) := Left_Text (1);
            Subtract
              (Left   => Left_Text (2 .. Left_Text'Last),
               Right  => Right_Text (2 .. Right_Text'Last),
               Result => Result_Text (2 .. Result_Text'Last),
               Last   => Result_Last);
         end if;
      end if;
      return To_Value (Result_Text (1 .. Result_Last));
   end Signed_Add;

   --------------
   -- Subtract --
   --------------

   procedure Subtract
     (Left   : in     Buffer;
      Right  : in     Buffer;
      Result :    out Buffer;
      Last   :    out Positive;
      Mult   : in     Digit := 1)
   is
      Carry : Digit;
   begin
      Subtract (Left, Right, Result, Last, Mult, Carry);
      if Carry /= 0 then
         Last := Last + 1;
         if Last > Result'Last then
            raise Buffer_Overflow;
         end if;
         Result (Last) := X (-Carry);
      end if;
   end Subtract;

   --------------
   -- Subtract --
   --------------

   procedure Subtract
     (Left   : in     Buffer;
      Right  : in     Buffer;
      Result :    out Buffer;
      Last   :    out Positive;
      Mult   : in     Digit := 1;
      Carry  :    out Digit)
   is
      Temp  : Small;
      Max   : constant Positive := Positive'Max (Left'Length, Right'Length);
   begin
      if Max > Result'Length then
         raise Buffer_Overflow;
      end if;
      Carry := 0;
      for I in 0 .. Max - 1 loop
         if I < Right'Length then
            Temp := X (Right (Right'First + I)) * Small (Mult);
         else
            Temp := 0;
         end if;
         if I < Left'Length then
            Temp := X (Left (Left'First + I)) - Temp;
         else
            Temp := - Temp;
         end if;
         Temp := Temp - Small (Carry);
         Result (Result'First + I) := X (Digit (Temp mod Digit'Modulus));
         Carry := -Digit (Temp / Digit'Modulus);
      end loop;
      Last := Result'First + Max - 1;
   end Subtract;

   ---------------
   -- To_Value --
   ---------------

   function To_Value (Text : Buffer) return Value is
      Last : constant Positive := Get_Last (Text);
   begin
      if Text'First >= Last then
         return Zero;
      else
         return To_Unbounded_String (String (Text (Text'First .. Last)));
      end if;
   end To_Value;

   --------------
   -- To_Small --
   --------------

   function To_Small (Text : Buffer) return Small is
      Result : Small := 0;
   begin
      for I in reverse Text'Range loop
         Result := Result * 256 + X (Text (I));
      end loop;
      return Result;
   end To_Small;

   -------
   -- X --
   -------

   function X (Char : Character) return Digit is
   begin
      return Character'Pos (Char);
   end X;

   -------
   -- X --
   -------

   function X (Char : Character) return Small is
   begin
      return Character'Pos (Char);
   end X;

   -------
   -- X --
   -------

   function X (First, Second : Character) return Small is
   begin
      return Character'Pos (First) * 256 + Character'Pos (Second);
   end X;

   -------
   -- X --
   -------

   function X (Item : Digit) return Character is
   begin
      return Character'Val (Item);
   end X;

end XASIS.Integers;



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
